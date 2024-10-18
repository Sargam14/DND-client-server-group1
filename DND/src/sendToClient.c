#include "../include/server_header.h"

void sendToClient(int client_socket, const char *message) {
    write(client_socket, message, strlen(message));
}


