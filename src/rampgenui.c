#include "rampgen.h"
#include "rampgenui.h"
#include "util.h"
#include "hooks.h"

static RampGenCmd cmd;
static HWND dlg;
static RampOrientation orientation;
static bool generating;

static AppendDirection default_direction = DIR_PLUS;
static char default_curve = 'l';

static void commit(bool select) {
    CMapDoc *doc = GetActiveMapDoc();
    if (doc && orientation.segment_list) {
        if (select) {
            CMapObjectList list;
            list.items = (CMapClass **)orientation.segment_list;
            list.length = (int)arrlen(orientation.segment_list);
            CSelection_SelectObjectList(doc->m_pSelection, &list, scClear | scSelect);
        }
        arrfree(orientation.segment_list);
    }
}

static INT_PTR dlg_proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_INITDIALOG:
            SendDlgItemMessage(hDlg, IDC_DEGREES, UDM_SETRANGE32, 1, 100);
            SendDlgItemMessage(hDlg, IDC_DEGREES, UDM_SETPOS32, 0, (int)cmd.degrees);

            SendDlgItemMessage(hDlg, IDC_SEGMENTS, UDM_SETRANGE32, 1, 1000);
            SendDlgItemMessage(hDlg, IDC_SEGMENTS, UDM_SETPOS32, 0, cmd.segments);

            SendDlgItemMessage(hDlg, IDC_SEGMENT_WIDTH, UDM_SETRANGE32, 0, 2048);
            SendDlgItemMessage(hDlg, IDC_SEGMENT_WIDTH, UDM_SETPOS32, 0, (int)cmd.segment_width);
            // TODO: snap to 16 grid
            UDACCEL accel = { 0, 16 }; // 16 unit step - TODO: doesnt work with scroll?
            SendDlgItemMessage(hDlg, IDC_SEGMENT_WIDTH, UDM_SETACCEL, 1, (LPARAM)&accel);

            // TODO: initialize by cmd.curve
            if (cmd.curve == 'l') {
                CheckDlgButton(hDlg, IDC_CURVE_LEFT, BST_CHECKED);
            } else if (cmd.curve == 'r') {
                CheckDlgButton(hDlg, IDC_CURVE_RIGHT, BST_CHECKED);
            } else if (cmd.curve == 'u') {
                CheckDlgButton(hDlg, IDC_CURVE_UP, BST_CHECKED);
            } else if (cmd.curve == 'd') {
                CheckDlgButton(hDlg, IDC_CURVE_DOWN, BST_CHECKED);
            }
            CheckDlgButton(hDlg, cmd.direction == DIR_PLUS ? IDC_DIRECTION_PLUS : IDC_DIRECTION_MINUS, BST_CHECKED);

            rampgen(&cmd, &orientation, true, &generating);

            return true;

        case WM_NOTIFY:
            NMHDR *hdr = (NMHDR*)lParam;
            if (hdr->code == UDN_DELTAPOS) {
                if (hdr->idFrom == IDC_DEGREES || hdr->idFrom == IDC_SEGMENTS || hdr->idFrom == IDC_SEGMENT_WIDTH) {
                    NMUPDOWN *ud = (NMUPDOWN*)lParam;
                    if (hdr->idFrom == IDC_DEGREES) {
                        cmd.degrees = (float)(ud->iPos + ud->iDelta);
                    }
                    else if (hdr->idFrom == IDC_SEGMENTS) {
                        cmd.segments = ud->iPos + ud->iDelta;
                    }
                    else if (hdr->idFrom == IDC_SEGMENT_WIDTH) {
                        cmd.segment_width = (float)(ud->iPos + ud->iDelta);
                    }

                    rampgen(&cmd, &orientation, false, &generating);
                    return true;
                }
            }
            break;

        case WM_COMMAND:
            if (HIWORD(wParam) == BN_CLICKED) {
                int id = LOWORD(wParam);

                if (id == IDC_CURVE_LEFT || id == IDC_CURVE_RIGHT || id == IDC_CURVE_UP || id == IDC_CURVE_DOWN) {
                    if (id == IDC_CURVE_LEFT) {
                        cmd.curve = 'l';
                    } else if (id == IDC_CURVE_RIGHT) {
                        cmd.curve = 'r';
                    } else if (id == IDC_CURVE_UP) {
                        cmd.curve = 'u';
                    } else /* if (id == IDC_CURVE_DOWN) */ {
                        cmd.curve = 'd';
                    }
                    rampgen(&cmd, &orientation, false, &generating);
                    return true;
                } else if (id == IDC_DIRECTION_PLUS || id == IDC_DIRECTION_MINUS) {
                    cmd.direction = id == IDC_DIRECTION_PLUS ? DIR_PLUS : DIR_MINUS;
                    rampgen(&cmd, &orientation, false, &generating);
                    return true;
                } else if (id == IDCANCEL || id == IDOK) {
                    if (id == IDCANCEL) {
                        rampgen_undo();
                        commit(false);
                    } else if (id == IDOK) {
                        commit(true);
                    }
                    DestroyWindow(hDlg);
                    dlg = nullptr;
                    return true;
                }
            }
            break;
        // case WM_CLOSE:
        //     DestroyWindow(hDlg);
        //     dlg = nullptr;
        //     return true;
        // case WM_KEYDOWN:
        //     if (wParam == VK_ESCAPE)
        //     {
        //         DestroyWindow(hDlg);
        //         dlg = nullptr;
        //         return true;
        //     }
        //     break;
    }

    return false;
}

void do_ramp_generator() {
    CMapSolid *ramp = get_selected_ramp();
    if (!ramp) {
        return;
    }

#ifdef RAMPGEN_DEBUG
    cmd = (RampGenCmd){ramp, 3.0f, 1, default_curve, default_direction};
#else
    cmd = (RampGenCmd){ramp, 3.0f, 30, default_curve, default_direction};
#endif

    if (!ramp_orientation(&cmd, &orientation)) {
        AfxMessageBoxF(MB_OK, "Brush must have a surfable face running along x or y.");
        return;
    }

    // TODO: do in WM_INITDIALOG?
    Vec3 orig_size;
    BBoxSize(&ramp->base.m_Render2DBox, &orig_size);
    float width = orig_size.v[orientation.axis];
    cmd.segment_width = width;

    dlg = CreateDialogA(
        GetHInstance(),
        MAKEINTRESOURCE(IDD_RAMPGEN),
        GetMainWndHwnd(),
        dlg_proc
    );
    if (dlg) {
        ShowWindow(dlg, SW_SHOW);
    }
}

// called from CHistory_MarkUndoPosition hook
// ie when the user makes changes after a ramp gen, close
void rampgen_close() {
    if (dlg && !generating) {
        // changes are comitted but selection is left alone
        commit(false);
        DestroyWindow(dlg);
        dlg = nullptr;
    }
}
