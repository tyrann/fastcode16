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

// Initialize the logging framework
void _init_logging(char* file_name);
void _log_console(char* msg, ...);
void _log_file(char* msg, ...);

// Enable or disable console and file logging
#ifdef ENABLE_CONSOLE_LOG

#define _LOG(msg, ...) \
{ \
    _LOG_CONSOLE(msg, ...); \
    _LOG_FILE(msg, ...); \
} \

// Enable or disable LOG_DEBUG macro according to the
// choosen LOG_LEVEL.
#if LOG_LEVEL <= LOG_LEVEL_DEBUG
#define LOG_DEBUG(msg, ...) _LOG(msg, __VA_ARGS__)
#else
#define LOG_DEBUG(msg, ...)
#endif

// Enable or disable LOG_INFO macro according to the
// choosen LOG_LEVEL.
#if LOG_LEVEL <= LOG_LEVEL_INFO
#define LOG_INFO(msg, ...) _LOG(msg, __VA_ARGS__)
#else
#define LOG_INFO(msg, ...)
#endif

// Enable or disable LOG_ERROR macro according to the
// choosen LOG_LEVEL.
#if LOG_LEVEL <= LOG_LEVEL_ERROR
#define LOG_ERROR(msg, ...) _LOG(msg, __VA_ARGS__)
#else
#define LOG_ERROR(msg, ...)
#endif

#endif