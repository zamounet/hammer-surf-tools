#ifndef SCRIPTFUNCS_H
#define SCRIPTFUNCS_H

// typedef void (*TransScale_t)(void *this_, Vec3 *ref, Vec3 *scale);
typedef void (*TransScale_t)(void *this_, Vec3 *ref, Vec3 *scale);
extern TransScale_t TransScale;

typedef void (*TransMove_t)(void *this_, Vec3 *delta);
extern TransMove_t TransMove;

// typedef void (*TransRotate_t)(void *this_, Vec3 *ref, Euler *angles);
// angle/ref args are swapped in the script version
typedef void (*TransRotate_t)(void *this_, Euler *angles, Vec3 *ref);
extern TransRotate_t TransRotate;

extern void **ScriptDataPtr;

#define SCRIPT_DATA_OFFSET_NAME 0
#define SCRIPT_DATA_OFFSET_FUNC 0x48
#define SCRIPT_DATA_SIZE 0x68
// ptr, capacity, len
#define SCRIPT_DATA_ARRAY_SIZE_OFFSET (sizeof(size_t) * 2)

bool script_data_init();

#endif // SCRIPTFUNCS_H
