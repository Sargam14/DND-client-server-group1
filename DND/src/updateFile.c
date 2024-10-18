#include "../include/server_header.h"

extern const char *log_levels[];

void updateFile(int client_socket, FILE *csv_file, int len, int c, int client_id, char choice, int global, char num_groups[]) {
    fseek(csv_file, -len, SEEK_CUR);
    fprintf(csv_file, "%d,%c,%c,%s\n", client_id, choice, global, num_groups);
    fflush(csv_file);
    if (c == 'A') {
        LOG(LOG_LEVEL_INFO, "Previously it was activated, now it's DEACTIVATED");
        sendToClient(client_socket, "Previously it was activated, now it's DEACTIVATED\n");
    } else {
        LOG(LOG_LEVEL_INFO, "Previously it was deactivated, now it's ACTIVATED");
        sendToClient(client_socket, "Previously it was deactivated, now it's ACTIVATED\n");
    }
}


