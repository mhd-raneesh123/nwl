#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    int num, original, reversed, remainder, result;

    // 1. Create TCP socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // 2. Bind the socket
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    
    // 3. Listen for connections
    listen(server_fd, 1);
    printf("TCP Server waiting for connection on port %d...\n", PORT);
    
    // 4. Accept the connection
    client_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);
    printf("Client connected successfully.\n");

    // Receive the number from the client
    recv(client_socket, &num, sizeof(num), 0);
    printf("Received number to check: %d\n", num);

    // Palindrome check logic (Mathematical reversal)
    original = num;
    reversed = 0;
    
    while (num > 0) {
        remainder = num % 10;
        reversed = (reversed * 10) + remainder;
        num /= 10;
    }

    // Determine the result (1 if true, 0 if false)
    if (original == reversed) {
        result = 1;
        printf("Analysis: It IS a palindrome.\n");
    } else {
        result = 0;
        printf("Analysis: It is NOT a palindrome.\n");
    }

    // Send the result back to the client
    send(client_socket, &result, sizeof(result), 0);
    printf("Result sent to client. Closing connection.\n");

    close(client_socket);
    close(server_fd);
    return 0;
}
