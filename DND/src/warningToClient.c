#include "../include/server_header.h"

extern const char *log_levels[];

void warningToClient(int client_socket, int c, int choice) {
    if (choice == 'A' && c == 'A') {
        LOG(LOG_LEVEL_WARNING, "Already Activated, please deactivate first.\n");
        sendToClient(client_socket, "Already Activated, please deactivate first\n");
    } else if (choice == 'D' && c == 'D') {
        LOG(LOG_LEVEL_WARNING, "Already Deactivated, please activate first.\n");
        sendToClient(client_socket, "Already Deactivated, please activate first\n");
    }
}


