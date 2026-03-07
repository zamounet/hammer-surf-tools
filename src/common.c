#include <stdarg.h>
#include <stdio.h>

void log_msg(const char *fmt, ...)
{
    FILE *f = fopen("surf-tools.log", "a");
    if (!f)
        return;

    va_list va;
    va_start(va, fmt);
    vfprintf(f, fmt, va);
    va_end(va);

    fclose(f);
}
