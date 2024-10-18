#ifndef SERVER_HEADER_H
#define SERVER_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdbool.h>
#include <stdarg.h>
#include <pthread.h>  // Include pthread library


enum {
    LOG_LEVEL_FATAL,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_DEBUG
};

extern const char *log_levels[];

#define LOG(level, message, ...) printf("[%s] " message "\n", log_levels[level], ##__VA_ARGS__)

void sendToClient(int client_socket, const char *message);
void handleIncomingCall(int client_socket, int my_id, int client_id);
void newClient(int client_socket, FILE *csv_file, int client_id, char choice, char global, char num_groups[]);
void openFile(int client_socket, int client_id, char choice, char global, char num_groups[]);
void processCommand(int client_socket);
void updateFile(int client_socket, FILE *csv_file, int len, int c, int client_id, char choice, int global, char num_groups[]);
void warningToClient(int client_socket, int c, int choice);
void *handleClient(void *arg);  // Declare thread function
void logCall(int caller_id, int receiver_id);

extern pthread_mutex_t file_mutex;

#endif // SERVER_HEADER_H


