#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    int num, result;

    // 1. Create TCP socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        return -1;
    }
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // 2. Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection to server failed");
        return -1;
    }
    printf("Connected to server.\n\n");

    // Get input from user
    printf("Enter a positive number to check for palindrome: ");
    scanf("%d", &num);

    // Send the number to the server
    send(sock, &num, sizeof(num), 0);

    // Wait to receive the validation result
    recv(sock, &result, sizeof(result), 0);

    // Print the final result based on the server's response
    printf("\n--- Server Response ---\n");
    if (result == 1) {
        printf("The number %d is a PALINDROME.\n", num);
    } else {
        printf("The number %d is NOT a palindrome.\n", num);
    }

    close(sock);
    return 0;
}
