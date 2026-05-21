#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main() {
    int sock_fd;
    struct sockaddr_in server_addr;
    char fname[1024], buffer[4096];
    int bytes;

    // 1. Create socket
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        perror("Socket creation failed");
        return -1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8053);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // 2. Connect to server
    if (connect(sock_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        return -1;
    }
    printf("Connected to File Server.\n\n");

    // 3. Loop to request multiple files
    while (1) {
        printf("Enter filename (or type 'exit' to quit): ");
        scanf("%s", fname);

        if (strcmp(fname, "exit") == 0) {
            break;
        }

        // Send filename to server
        send(sock_fd, fname, strlen(fname), 0);

        // Receive response (PID + Content or Error)
        memset(buffer, 0, sizeof(buffer));
        bytes = recv(sock_fd, buffer, sizeof(buffer) - 1, 0);
        
        if (bytes <= 0) {
            printf("Server disconnected.\n");
            break;
        }
        
        buffer[bytes] = '\0';
        printf("\n--- Server Response ---\n%s\n-----------------------\n\n", buffer);
    }

    close(sock_fd);
    return 0;
}
