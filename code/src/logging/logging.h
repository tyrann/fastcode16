#ifndef __LOGGING_H_
#define __LOGGING_H_

// Define log levels
#define LOG_LEVEL_NOTHING 0 // Log nothing
#define LOG_LEVEL_ERROR 1   // Log only error messages
#define LOG_LEVEL_INFO 2    // Log errors and information
#define LOG_LEVEL_DEBUG 3   // Log everything, including debug information 

// In case no log level is specified use LOG_LEVEL_DEBUG as default
#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_LEVEL_DEBUG
#endif

// Log a message to the console.
void __log_console(const char* tag, const char* function, int line, const char* msg, ...);
// TODO: Implement if file logging required
// void __log_file(const char* tag, const char* function, int line, const char* msg, ...);

// Enable or disable console and file logging
#ifndef DISABLE_CONSOLE_LOG
#define __LOG_CONSOLE(tag, function, line, msg, ...) \
    __log_console(tag, function, line, msg, ##__VA_ARGS__)
#else
#define __LOG_CONSOLE(tag, function, line, msg, ...)
#endif

/* // TODO: Uncomment if file logging required
#ifndef DISABLE_FILE_LOG
#define __LOG_FILE(tag, function, line, msg, ...) \
    __log_console(tag, function, line, msg, ##__VA_ARGS__)
#else
#define __LOG_FILE(tag, function, line, msg, ...)
#endif */

// Call all supported loggers
#define __LOG(tag, function, line, msg, ...) \
{ \
    __LOG_CONSOLE(tag, function, line, msg, ##__VA_ARGS__); \
    /* TODO: Uncomment if file logging required */ \
    /* __LOG_FILE(tag, function, line, msg, ##__VA_ARGS__); */ \
}

// Enable or disable LOG_DEBUG macro according to the
// choosen LOG_LEVEL.
#if LOG_LEVEL >= LOG_LEVEL_DEBUG
#define LOG_DEBUG(msg, ...) \
    __LOG("DEBUG", __FUNCTION__, __LINE__, msg, ##__VA_ARGS__)
#else
#define LOG_DEBUG(msg, ...)
#endif

// Enable or disable LOG_INFO macro according to the
// choosen LOG_LEVEL.
#if LOG_LEVEL >= LOG_LEVEL_INFO
#define LOG_INFO(msg, ...) \
    __LOG("INFO", __FUNCTION__, __LINE__, msg, ##__VA_ARGS__)
#else
#define LOG_INFO(msg, ...)
#endif

// Enable or disable LOG_ERROR macro according to the
// choosen LOG_LEVEL.
#if LOG_LEVEL >= LOG_LEVEL_ERROR
#define LOG_ERROR(msg, ...) \
    __LOG("ERROR", __FUNCTION__, __LINE__, msg, ##__VA_ARGS__)
#else
#define LOG_ERROR(msg, ...)
#endif

#endif