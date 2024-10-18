#include "../include/client_header.h"
#define PORT 9316

const char *log_levels[] = {
    "FATAL",
    "INFO",
    "WARNING",
    "DEBUG"
};

int main() {
    int client_socket;
    struct sockaddr_in server_address;

    // Create socket
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        LOG(LOG_LEVEL_FATAL, "Socket Creation Failed!\n");
        exit(EXIT_FAILURE);
    }

    // Initialize server address
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Connect to server
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        LOG(LOG_LEVEL_FATAL, "Connection failed!\n");
        exit(EXIT_FAILURE);
    }

    int client_id;
    char choice, global = '-';
    char num_groups[50] = "NA";

    system("clear");
    LOG(LOG_LEVEL_INFO, "Connection established.\n");
        printf("\n=============================\n");
        printf("   DO NOT DISTURB MENU\n");
        printf("=============================\n");

    printf("Enter client ID: ");
    scanf("%d", &client_id);

    if(!(client_id >=0 && client_id <=100000)){
	LOG(LOG_LEVEL_FATAL, "Please Enter Number Only !\n");
        exit(EXIT_FAILURE);
    }

    getchar(); // Clear newline character from buffer

        printf("=============================\n");
        printf("A - Activate DND\n");
        printf("D - Deactivate DND\n");
        printf("H - Call\n");
	printf("L - Call log\n");
        printf("=============================\n");
        printf("Enter your choice: ");

    scanf("%c", &choice);
    getchar();

    if (choice == 'H') {
        printf("Enter client ID you want to call: ");
        int target_client_id;
        scanf("%d", &target_client_id);
        getchar();

        // Send data to server
        write(client_socket, &client_id, sizeof(client_id));
        write(client_socket, &choice, sizeof(choice));
        write(client_socket, &target_client_id, sizeof(target_client_id));
    } else if(choice == 'A' || choice == 'D') {
        if (choice == 'A') {
            printf("Enter S for selective & G for global:\n");
            scanf("%c", &global);
            getchar();
            if (global == 'S') {
                printf("Enter comma separated numbers you want to block: ");
                scanf("%49s", num_groups);
                getchar();
            }
        }

        // Send data to server
        write(client_socket, &client_id, sizeof(client_id));
        write(client_socket, &choice, sizeof(choice));
        write(client_socket, &global, sizeof(global));
        write(client_socket, &num_groups, sizeof(num_groups));
    }
    else if (choice == 'L') {
        // Send data to server
        write(client_socket, &client_id, sizeof(client_id));
        write(client_socket, &choice, sizeof(choice));
	        // Receive and print messages from the server (which is the call log)
        char buffer[4096];
        ssize_t bytes_received;
        while ((bytes_received = read(client_socket, buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytes_received] = '\0'; // Null-terminate the buffer
            printf("%s\n", buffer); // Print to standard output (console)
        }
    }
    else{
        LOG(LOG_LEVEL_FATAL, "Enter Valid Option!\n");
        exit(EXIT_FAILURE);
    }

    // Receive and print messages from the server
    char buffer[1024];
    ssize_t bytes_received;
    while ((bytes_received = read(client_socket, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_received] = '\0'; // Null-terminate the buffer
        printf("%s\n", buffer); // Print to standard output (console)
    }

    // Close socket
    close(client_socket);

    return 0;
}


