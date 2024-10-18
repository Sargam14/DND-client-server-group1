#include "../include/server_header.h"
#include <pthread.h>
#define PORT 9316


const char *log_levels[] = {
    "FATAL",
    "INFO",
    "WARNING",
    "DEBUG"
};

pthread_mutex_t file_mutex = PTHREAD_MUTEX_INITIALIZER;

void* handle_client(void* arg) {
    int client_socket = *(int*)arg;
    free(arg);
    processCommand(client_socket);
    close(client_socket);
    return NULL;
}

int main() {
    int server_socket, *client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t addrlen = sizeof(server_address);

    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        LOG(LOG_LEVEL_FATAL, "Socket creation failed!\n");
        exit(EXIT_FAILURE);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        LOG(LOG_LEVEL_FATAL, "Bind failed!\n");
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 10) < 0) {
        LOG(LOG_LEVEL_FATAL, "Listen failed!\n");
        exit(EXIT_FAILURE);
    }

    LOG(LOG_LEVEL_INFO, "Server listening on port %d...\n", PORT);

    while (1) {
        client_socket = malloc(sizeof(int));
        if ((*client_socket = accept(server_socket, (struct sockaddr *)&client_address, &addrlen)) < 0) {
            LOG(LOG_LEVEL_FATAL, "Accept error!\n");
            free(client_socket);
            exit(EXIT_FAILURE);
        }

        pthread_t tid;
        pthread_create(&tid, NULL, handle_client, client_socket);
        pthread_detach(tid);
    }

    pthread_mutex_destroy(&file_mutex);
    close(server_socket);
    return 0;
}

