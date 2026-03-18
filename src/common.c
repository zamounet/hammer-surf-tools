#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wconversion"
#define STB_DS_IMPLEMENTATION
#include <stb_ds.h>
#pragma GCC diagnostic pop

#define DVECTOR_IMPLEMENTATION
#include <dvector.h>

// TODO: cwd changes on windows and log goes to hammerplusplus/

void log_msg(const char *fmt, ...) {
#ifdef TEST_PATTERNS
    va_list va;
    va_start(va, fmt);
    vprintf(fmt, va);
    va_end(va);
#else
    FILE *f = fopen("surf-tools.log", "a");
    if (!f)
        return;

    va_list va;
    va_start(va, fmt);
    vfprintf(f, fmt, va);
    va_end(va);

    fclose(f);
#endif
}
