#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>

#define PORT 8080

int main() {
    int sock;
    struct sockaddr_in addr;
    char buffer[1024];
    socklen_t addr_size = sizeof(addr);

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    struct timeval tv;
    tv.tv_sec = 2;
    tv.tv_usec = 0;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    int frame_id = 0;
    int total_frames = 5;

    printf("Starting Stop and Wait ARQ Sender...\n\n");

    while (frame_id < total_frames) {
        sprintf(buffer, "Frame %d", frame_id);
        sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr*)&addr, addr_size);
        printf("[+] Sent: %s\n", buffer);
        memset(buffer, 0, sizeof(buffer));
        int n = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr*)&addr, &addr_size);

        if (n < 0) {
            
            printf("[-] Timeout! Did not receive ACK for %d. Retransmitting...\n", frame_id);
        } else {
            
            printf("[+] Received: %s\n\n", buffer);
            frame_id++; 
        }
    }

    printf("All frames sent successfully!\n");
    close(sock);
    return 0;
}
