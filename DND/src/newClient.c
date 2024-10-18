#include "../include/server_header.h"

extern const char *log_levels[];

void newClient(int client_socket, FILE *csv_file, int client_id, char choice, char global, char num_groups[]) {
    // Move file pointer to the end to append new data
    fseek(csv_file, 0, SEEK_END);
    fprintf(csv_file, "%d,%c,%c,%s\n", client_id, choice, global, num_groups);
    LOG(LOG_LEVEL_DEBUG, "Data entered in file successfully");
    if (choice == 'A') {
        LOG(LOG_LEVEL_INFO, "DND Activated Successfully");
        sendToClient(client_socket, "New User, DND Activated Successfully\n");
    } else if (choice == 'D') {
        LOG(LOG_LEVEL_INFO, "DND Deactivated Successfully");
        sendToClient(client_socket, "New User, DND Deactivated Successfully\n");
    }
    fflush(csv_file);
}


