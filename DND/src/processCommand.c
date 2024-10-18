#include "../include/server_header.h"

void processCommand(int client_socket) {
    int client_id;
    char choice;
    char num_groups[50] = "NA";
    char global = '-';

    // Reading client info-----------
    read(client_socket, &client_id, sizeof(client_id));
    read(client_socket, &choice, sizeof(choice));

    if (choice == 'H') {
        int target_client_id;
        read(client_socket, &target_client_id, sizeof(target_client_id));
        handleIncomingCall(client_socket, client_id, target_client_id);
    } else if (choice == 'L') {
        sendCallLog(client_socket, client_id);
    } else {
        if (choice == 'A') {
            read(client_socket, &global, sizeof(global));
        }
        if (choice == 'A' && global == 'S') {
            read(client_socket, &num_groups, sizeof(num_groups));
        }
        openFile(client_socket, client_id, choice, global, num_groups);
    }
}

void sendCallLog(int client_socket, int client_id) {
    pthread_mutex_lock(&file_mutex);

    FILE *log_file = fopen("/home2/user06/DND/call_log.csv", "r");
    if (log_file == NULL) {
        LOG(LOG_LEVEL_FATAL, "Error opening call log file!\n");
        pthread_mutex_unlock(&file_mutex);
        return;
    }

    char line[256];
    char buffer[4096] = ""; // Initialize an empty buffer
    bool found_logs = false;

    while (fgets(line, sizeof(line), log_file)) {
        int stored_client_id;
        sscanf(line, "%d,", &stored_client_id);
        if (stored_client_id == client_id) {
            strcat(buffer, line); // Concatenate each line to the buffer
            found_logs = true;
        }
    }
    fclose(log_file);

    if (!found_logs) {
        snprintf(buffer, sizeof(buffer), "No call logs found for client ID %d\n", client_id);
    }

    // Send the call log buffer to the client
    write(client_socket, buffer, strlen(buffer));

    pthread_mutex_unlock(&file_mutex);
}


