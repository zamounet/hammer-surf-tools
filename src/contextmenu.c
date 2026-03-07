#include "common.h"
#include "contextmenu.h"

LoadMenuW_t orig_LoadMenuW;

static void add_menus(HMENU hPopup, int pos) {
    HMENU hSubMenu = CreatePopupMenu();
    AppendMenuA(hSubMenu, MF_STRING, CMD_CURVED_RAMP_GENERATOR, "Curved Ramp Generator\tCtrl+Alt+Shift+S");
    AppendMenuA(hSubMenu, MF_STRING, CMD_ANGLEFIX,              "Anglefix\tCtrl+Alt+Shift+A");
    AppendMenuA(hSubMenu, MF_STRING, CMD_TRIGGER_GENERATOR,     "Trigger Generator\tCtrl+Alt+Shift+T");

    InsertMenuA(
        hPopup,
        (uint32_t)pos,
        MF_BYPOSITION | MF_POPUP,
        (UINT_PTR)hSubMenu,
        "Surf Tools"
    );
}

HMENU hook_LoadMenuW(HINSTANCE hInstance, LPCWSTR lpMenuName) {
    HMENU menu = orig_LoadMenuW(hInstance, lpMenuName);

    if (lpMenuName == (void *)IDR_POPUPS) {
        HMENU hPopup = GetSubMenu(menu, 0); // "Object"
        int count = GetMenuItemCount(hPopup);
        int second_last = count - 1;
        add_menus(hPopup, second_last);
        InsertMenuA(hPopup, (uint32_t)second_last + 1, MF_BYPOSITION | MF_SEPARATOR, 0, nullptr);
    } else if (lpMenuName == (void *)IDR_FORGEMAPTYPE) {
        HMENU hPopup = GetSubMenu(menu, 4); // "Tools"
        int count = GetMenuItemCount(hPopup);
        add_menus(hPopup, count - 3);
    }

    return menu;
}
