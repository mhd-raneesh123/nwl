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
    printf("Receiver started. Waiting for frames...\n\n");

    srand(time(0)); 

    while (1) {
        memset(buffer, 0, sizeof(buffer));
        
        
        recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr*)&client_addr, &addr_size);
        
        
        int frame_id;
        sscanf(buffer, "Frame %d", &frame_id);
        printf("Received: %s\n", buffer);

        if (rand() % 10 < 3) {
            printf("    -> SIMULATED DROP! Ignoring frame %d (No ACK sent)\n", frame_id);
            continue; 
        }

        memset(buffer, 0, sizeof(buffer));
        sprintf(buffer, "ACK %d", frame_id);
        sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr*)&client_addr, addr_size);
        printf("    -> Sent: %s\n", buffer);
    }

    close(sock);
    return 0;
}
