#ifndef CLIENT_HEADER_H
#define CLIENT_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <stdbool.h>

extern const char *log_levels[];

#define LOG_LEVEL_FATAL 0
#define LOG_LEVEL_INFO 1
#define LOG_LEVEL_WARNING 2
#define LOG_LEVEL_DEBUG 3

#define LOG(level, message) printf("[%s] %s", log_levels[level], message)

#endif // CLIENT_HEADER_H


