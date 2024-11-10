#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_MSG 1024

void handle_client(int client_socket) {
    char msg[MAX_MSG];
    FILE *log_file;
    int len;

    // Read data from the client
    ssize_t num_bytes = recv(client_socket, msg, MAX_MSG - 1, 0);
    if (num_bytes < 0) {
        perror("Error reading from socket");
        close(client_socket);
        return;
    }

    msg[num_bytes] = '\0'; // null-terminate the string and strip the newline at the end
    char *newline_pos = strchr(msg, '\n');
    if (newline_pos) {
        *newline_pos = '\0';  // remove the newline character
    }
    len = strlen(msg);
    printf("Received: %s\n", msg);

    //########## YOUR CODE HERE ############
    //### Validate the the PoW in the message
    //### Stril the PoW from the message
    //### Read the last hash from loghead.txt
    //### Create the full line for the log entry
    //### Compute its hash
    //### Append the line to the log
    //### Update loghead.txt
    //### Add error checking
    //#######################################

    log_file = fopen("log.txt", "a");
    if (log_file == NULL) {
        perror("Error opening log file");
        close(client_socket);
        return;
    }
    printf("logging: \"%s\"\n", msg);
    fprintf(log_file, "%s\n", msg);
    fclose(log_file);

    // Send confirmation message back to the client
    const char *response_msg = "ok\n";
    send(client_socket, response_msg, strlen(response_msg), 0);
    close(client_socket);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    // Create the server socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Could not create socket");
        exit(EXIT_FAILURE);
    }

    // Bind the server to an available port
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = 0;  // System assigns any available port

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // Get the assigned port number and print it
    socklen_t len = sizeof(server_addr);
    if (getsockname(server_socket, (struct sockaddr*)&server_addr, &len) == -1) {
        perror("getsockname failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }
    int port = ntohs(server_addr.sin_port);
    printf("Server listening on port: %d\n", port);

    // Start listening for connections
    if (listen(server_socket, 5) < 0) {
        perror("Listen failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // Continuously accept and handle clients
    while (1) {
        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_len);
        if (client_socket < 0) {
            perror("Accept failed");
            continue;
        }

        printf("Client connected\n");
        handle_client(client_socket);
    }

    close(server_socket);
    return 0;
}
