#ifndef CONTEXTMENU_H
#define CONTEXTMENU_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

typedef HMENU (*LoadMenuW_t)(HINSTANCE hInstance, LPCWSTR lpMenuName);
extern LoadMenuW_t orig_LoadMenuW;
HMENU hook_LoadMenuW(HINSTANCE hInstance, LPCWSTR lpMenuName);

UINT decide_menu_item_enabled(HMENU hMenu, UINT uIDEnableItem, UINT uEnable);

#endif // CONTEXTMENU_H
