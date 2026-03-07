#ifndef HOTKEYS_H
#define HOTKEYS_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// typedef struct {
//     char *name;
//     int key;
//     int key2;
//     int modifier;
//     int modifier2;
// } Hotkey;

typedef HACCEL (*LoadAcceleratorsA_t)(HINSTANCE hInstance, LPCSTR lpTableName);
// typedef void (*SetupHotkeys_t)(void *this_, HACCEL src_accel, int which);
// typedef void (*RegisterHotkey_t)(void *this_, int idx, Hotkey *hotkey);

extern LoadAcceleratorsA_t orig_LoadAcceleratorsA;
// extern SetupHotkeys_t orig_SetupHotkeys;
// extern RegisterHotkey_t orig_RegisterHotkey;

HACCEL hook_LoadAcceleratorsA(HINSTANCE hInstance, LPCSTR lpTableName);
// void hook_SetupHotkeys(void *this_, HACCEL src_accel, int which);
// void hook_RegisterHotkey(void *this_, int idx, Hotkey *hotkey);

#endif // HOTKEYS_H
