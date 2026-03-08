#ifndef CONTEXTMENU_H
#define CONTEXTMENU_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

UINT decide_menu_item_enabled(HMENU hMenu, UINT uIDEnableItem, UINT uEnable);
void menu_check_command(UINT cmd);
void check_add_menus(HMENU menu, const void *lpMenuName);

#endif // CONTEXTMENU_H
