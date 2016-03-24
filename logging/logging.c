#include <stdarg.h>
#include <stdio.h>
#include <string.h>

void _log_console(const char* tag, const char* function, int line, const char* msg, ...)
{    
    // Enable access to variadic arguments
    va_list argptr;
	va_start(argptr, msg);
    
    // Print title and message to the console
    const char* title_frmt = "[%s] %s:%d: ";
    printf(title_frmt, tag, function, line);
    vprintf(msg, argptr);
    printf("\n");
    
    // End access to variadic arguments
    va_end(argptr);
}