#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 8080

int main() {
    int sock;
    struct sockaddr_in server_addr, client_addr;
    char buffer[1024];
    socklen_t addr_size = sizeof(client_addr);

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    printf("Go-Back-N Receiver started. Waiting for frames...\n\n");

    srand(time(0)); 
    int expected_seq_num = 0; // The strict sequence number we want next

    while (1) {
        memset(buffer, 0, sizeof(buffer));
        
        recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr*)&client_addr, &addr_size);
        
        int frame_seq;
        sscanf(buffer, "Frame %d", &frame_seq);
        printf("Received: %s\n", buffer);

        // Simulate network unreliability (25% chance to drop the packet)
        if (rand() % 100 < 25) {
            printf("    -> SIMULATED DROP! Ignoring Frame %d\n", frame_seq);
            continue; 
        }

        if (frame_seq == expected_seq_num) {
            // Success: In-order frame received
            memset(buffer, 0, sizeof(buffer));
            sprintf(buffer, "ACK %d", expected_seq_num);
            sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr*)&client_addr, addr_size);
            printf("    -> Accepted! Sent: %s\n", buffer);
            expected_seq_num++; // Increment to expect the next one
        } else {
            // Failure: Out-of-order frame received (e.g., Frame 2 lost, received Frame 3)
            printf("    -> Out of order! Expected Frame %d. Discarding...\n", expected_seq_num);
            
            // Resend ACK for the highest correctly received in-order frame
            if (expected_seq_num > 0) {
                memset(buffer, 0, sizeof(buffer));
                sprintf(buffer, "ACK %d", expected_seq_num - 1);
                sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr*)&client_addr, addr_size);
                printf("    -> Resent Cumulative: %s\n", buffer);
            }
        }
    }

    close(sock);
    return 0;
}
