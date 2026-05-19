#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int bsize, current = 0, rate, cycle = 1, temp, n, i;

    printf("Bucket Size: ");
    scanf("%d", &bsize);

    printf("Output Rate: ");
    scanf("%d", &rate);

    printf("Num of packets: ");
    scanf("%d", &n);


    int packets[n];
    printf("Packet Sizes:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &packets[i]);
    }

    printf("\nLeaky Bucket Simulation\n");

    i = 0;
    while (current > 0 || i < n) {
        sleep(1);
        printf("\nCycle %d [Current Queue Size = %d]:\n", cycle, current);

        // Incoming packet processing
        if (i < n) {
            printf("Incoming: %d\n", packets[i]);
            if (packets[i] <= bsize - current) {
                current += packets[i];
                printf("Accepted\n");
            } else {
                printf("Rejected\n");
            }
            i++; // Move to the next packet
        } else {
            printf("Incoming: NA\n");
        }

        // Outgoing packet processing
        temp = current - rate;
        if (temp <= 0) {
            printf("Outgoing: %d\n", current);
            current = 0;
        } else {
            current -= rate;
            printf("Outgoing: %d\n", rate);
        }

        cycle++; // Update cycle count
    }

    return 0;
}
