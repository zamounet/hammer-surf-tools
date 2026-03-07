#ifndef PATTERNS_H
#define PATTERNS_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct {
    const char *name;
    const uint8_t *pattern;
    const char *mask;
    void **out;
    void *hook;
    int offset;
    bool rel;
    bool optional;
}  Pattern_t;

bool scan_all(uint8_t *base, size_t size);

#endif // PATTERNS_H
