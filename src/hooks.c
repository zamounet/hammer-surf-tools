#include "hooks.h"
#include "patterns.h"
#include "triggergen.h"
#include "hammerfuncs.h"
#include "measure.h"
#include "contextmenu.h"
#include "hotkeys.h"

static CMapDoc *active_map_doc;

AfxWndProc_t orig_AfxWndProc;
Clipper3D_DrawBrushExtents_t orig_Clipper3D_DrawBrushExtents;
// CFaceEditSheet_ClickFace_t orig_CFaceEditSheet_ClickFace;
EnableMenuItem_t orig_EnableMenuItem;
Selection3D_RenderTool2D_t orig_Selection3D_RenderTool2D;
SetActiveMapDoc_t orig_SetActiveMapDoc;
LoadMenuW_t orig_LoadMenuW;
LoadAcceleratorsA_t orig_LoadAcceleratorsA;
// SetFocus_t orig_SetFocus;

LRESULT hook_AfxWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
    LRESULT result = orig_AfxWndProc(hWnd, Msg, wParam, lParam);

    if (Msg == WM_COMMAND) {
        UINT cmd = LOWORD(wParam);
        menu_check_command(cmd);
    }

    return result;
}

// hook because GetActiveMapDoc is compiled away
void hook_SetActiveMapDoc(void *doc) {
    /* log_msg("[hook] SetActiveMapDoc %p\n", doc); */
    orig_SetActiveMapDoc(doc);
    active_map_doc = doc;
}

// enum {
//     cfToggle    = 0x01,			// toggle - if selected, then unselect
//     cfSelect    = 0x02,			// select
//     cfUnselect  = 0x04,			// unselect
//     cfClear     = 0x08,			// clear face list
//     cfEdgeAlign = 0x10			// align face texture coordinates to 3d view alignment - should be here???
// };

// void hook_CFaceEditSheet_ClickFace(void *this_, CMapClass *pSolid, int faceIndex, int cmd, int clickMode) {
//     orig_CFaceEditSheet_ClickFace(this_, pSolid, faceIndex, cmd, clickMode);
// }

// fix an annoyance
// void *hook_SetFocus(void *this_) {
//     /* log_msg("[hook SetFocus %p\n", this_); */
//
//     void *mainWnd = GetMainWnd();
//
//     if (mainWnd) {
//         void *ObjectProperties = *(void **)(mainWnd + CMAINFRAME_OFFSET_OBJECTPROPERTIES);
//
//         if (ObjectProperties) {
//             if (this_ != ObjectProperties) {
//                 HWND properties_hwnd = *(HWND *)(ObjectProperties + COBJECTPROPERTIES_OFFSET_HWND);
//                 bool visible = IsWindowVisible(properties_hwnd);
//
//                 if (visible) {
//                     // log_msg("[hook] blocking SetFocus while ObjectProperties visible %p %p\n", this_, ObjectProperties);
//                     return nullptr;
//                 }
//             }
//         }
//     }
//
//     return orig_SetFocus(this_);
// }

bool hook_EnableMenuItem(HMENU hMenu, UINT uIDEnableItem, UINT uEnable) {
    uEnable = decide_menu_item_enabled(hMenu, uIDEnableItem, uEnable);
    return orig_EnableMenuItem(hMenu, uIDEnableItem, uEnable);
}

HMENU hook_LoadMenuW(HINSTANCE hInstance, LPCWSTR lpMenuName) {
    HMENU menu = orig_LoadMenuW(hInstance, lpMenuName);
    check_add_menus(menu, lpMenuName);
    return menu;
}

HACCEL hook_LoadAcceleratorsA(HINSTANCE hInstance, LPCSTR lpTableName) {
    HACCEL accel = orig_LoadAcceleratorsA(hInstance, lpTableName);
    accel = check_add_hotkeys(accel, lpTableName);
    return accel;
}

void hook_Selection3D_RenderTool2D(void *this_, void *pRender) {
    orig_Selection3D_RenderTool2D(this_, pRender);
    measure_render_2d(this_, pRender);
}

void hook_Clipper3D_DrawBrushExtents(void *this_, void *pRender, void *pSolid, int nFlags) {
    orig_Clipper3D_DrawBrushExtents(this_, pRender, pSolid, nFlags);
    measure_clipper_plane(this_, pRender);
}

CMapDoc *GetActiveMapDoc() {
    return active_map_doc;
}
