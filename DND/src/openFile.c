#include "../include/server_header.h"

void openFile(int client_socket, int client_id, char choice, char global, char num_groups[]) {
    pthread_mutex_lock(&file_mutex);

    FILE *csv_file;
    csv_file = fopen("/home2/user06/DND/data.csv", "r+");
	perror("fopen");
    if (csv_file == NULL) {
        LOG(LOG_LEVEL_FATAL, "Error opening file!\n");
        pthread_mutex_unlock(&file_mutex);
        exit(1);
    }
    bool isNewClient = true;
    int stored_client_id;
    rewind(csv_file);
    int id;
    char c, g;
    char num[50];
    char line[256];
    while (fgets(line, sizeof(line), csv_file)) {
        int len = strlen(line);
        char *token = strtok(line, ",");
        if (token != NULL) {
            id = atoi(token);
            if (id == client_id) {
                isNewClient = false;
                token = strtok(NULL, ",");
                if (token != NULL) {
                    c = token[0];
                    if (choice == c) {
                        warningToClient(client_socket, c, choice);
                        break;
                    } else {
                        updateFile(client_socket, csv_file, len, c, client_id, choice, global, num_groups);
                        break;
                    }
                }
            }
        }
    }
    if (isNewClient) {
        newClient(client_socket, csv_file, client_id, choice, global, num_groups);
    }
    fclose(csv_file);

    pthread_mutex_unlock(&file_mutex);
}


