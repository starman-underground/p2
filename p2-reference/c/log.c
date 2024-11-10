#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <port> <message>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int port = atoi(argv[1]);
    char *message = argv[2];

    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    // Create a socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Could not create socket");
        exit(EXIT_FAILURE);
    }

    // Set up the server address structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to the server
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    // ######################
    // ### message is our original message
    // ### Convert any whitespace to spaces
    // ### Modify the messsage to include the proof-of-work (Pow+':'+message)
    // ######################

    // Send the message with a newline at the end
    snprintf(buffer, sizeof(buffer), "%s\n", message);
    if (send(client_socket, buffer, strlen(buffer), 0) < 0) {
        perror("Send failed");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    // Receive the server's response
    ssize_t num_bytes = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
    if (num_bytes < 0) {
        perror("Error receiving data from server");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    // Null-terminate and print the response
    buffer[num_bytes] = '\0';
    printf("Server response: %s", buffer);

    close(client_socket);
    return 0;
}

