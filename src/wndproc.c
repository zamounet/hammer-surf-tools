#include "wndproc.h"
#include "rampgen.h"
#include "contextmenu.h"
#include "anglefix.h"
#include "triggergen.h"

AfxWndProc_t orig_AfxWndProc;

LRESULT hook_AfxWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
    LRESULT result = orig_AfxWndProc(hWnd, Msg, wParam, lParam);

    UINT cmd = LOWORD(wParam);
    // log_msg("[hook] AfxWndProc %p %d %p %p %x cmd=%d\n", hWnd, Msg, wParam, lParam, 42069, cmd);

    if (Msg == WM_COMMAND) {
        /* UINT cmd = LOWORD(wParam); */

        if (cmd == CMD_CURVED_RAMP_GENERATOR) {
            do_ramp_generator();
        } else if (cmd == CMD_ANGLEFIX) {
            do_anglefix();
        } else if (cmd == CMD_TRIGGER_GENERATOR) {
            do_trigger_generator();
        }
    }

    return result;
}
