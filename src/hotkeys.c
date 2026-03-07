#include "common.h"
#include "hotkeys.h"

LoadAcceleratorsA_t orig_LoadAcceleratorsA;
// SetupHotkeys_t orig_SetupHotkeys;
// RegisterHotkey_t orig_RegisterHotkey;

static const ACCEL hotkey1 = { FCONTROL | FALT | FSHIFT, 'S', (uint16_t)CMD_CURVED_RAMP_GENERATOR };
static const ACCEL hotkey2 = { FCONTROL | FALT | FSHIFT, 'A', (uint16_t)CMD_ANGLEFIX};
static const ACCEL hotkey3 = { FCONTROL | FALT | FSHIFT, 'T', (uint16_t)CMD_TRIGGER_GENERATOR };

static const ACCEL hotkeys[] = { hotkey1, hotkey2, hotkey3 };

HACCEL hook_LoadAcceleratorsA(HINSTANCE hInstance, LPCSTR lpTableName) {
    HACCEL accel = orig_LoadAcceleratorsA(hInstance, lpTableName);

    if (lpTableName == MAKEINTRESOURCE(129)) { // TODO: const
        int count = CopyAcceleratorTableA(accel, nullptr, 0);
        int extra_hotkeys = ARRAY_LEN(hotkeys);

        LPACCEL new_accel = malloc(sizeof(ACCEL) * (size_t)(count + extra_hotkeys));
        CopyAcceleratorTableA(accel, new_accel, count);

        for (auto i = 0; i < extra_hotkeys; i++) {
            new_accel[count + i] = hotkeys[i];
        }

        // log_msg("hook_LoadAcceleratorsA: %p %d = %d %p\n", hInstance, lpTableName, count, accel);

        accel = CreateAcceleratorTableA(new_accel, count + extra_hotkeys);
        free(new_accel);
    }

    return accel;
}
