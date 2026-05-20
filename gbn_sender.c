#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>

#define PORT 8080
#define WINDOW_SIZE 4    // Max unacknowledged frames allowed
#define TOTAL_FRAMES 10  // Total frames to send

int main() {
    int sock;
    struct sockaddr_in addr;
    char buffer[1024];
    socklen_t addr_size = sizeof(addr);

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int base = 0;          // Oldest unacknowledged frame
    int next_seq_num = 0;  // Next frame to be sent

    printf("Starting Go-Back-N ARQ Sender...\n");
    printf("Window Size: %d | Total Frames: %d\n\n", WINDOW_SIZE, TOTAL_FRAMES);

    while (base < TOTAL_FRAMES) {
        // 1. Send frames as long as the window is not full
        while (next_seq_num < base + WINDOW_SIZE && next_seq_num < TOTAL_FRAMES) {
            sprintf(buffer, "Frame %d", next_seq_num);
            sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr*)&addr, addr_size);
            printf("[+] Sent: %s\n", buffer);
            next_seq_num++;
        }

        // 2. Prepare the timer for the 'base' frame
        fd_set read_fds;
        FD_ZERO(&read_fds);
        FD_SET(sock, &read_fds);

        struct timeval timeout;
        timeout.tv_sec = 2; // 2 second timeout
        timeout.tv_usec = 0;

        // 3. Wait for ACKs or Timeout using select()
        int activity = select(sock + 1, &read_fds, NULL, NULL, &timeout);

        if (activity == 0) {
            // TIMEOUT: Go Back N!
            printf("[-] Timeout! No ACK for Frame %d. Going back to retransmit window...\n", base);
            next_seq_num = base; // Reset the sequence number back to the base to resend all
        } else {
            // ACK RECEIVED
            memset(buffer, 0, sizeof(buffer));
            recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr*)&addr, &addr_size);
            
            int ack_num;
            sscanf(buffer, "ACK %d", &ack_num);
            
            // Go-Back-N uses Cumulative ACKs (ACK 3 means 0, 1, 2, and 3 are all received)
            if (ack_num >= base) {
                printf("[+] Received: ACK %d. Sliding window forward.\n\n", ack_num);
                base = ack_num + 1; // Slide the window forward
            } else {
                printf("[!] Received duplicate ACK %d (Ignored)\n", ack_num);
            }
        }
    }

    printf("\nAll frames sent successfully using Go-Back-N!\n");
    close(sock);
    return 0;
}
