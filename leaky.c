#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int bsize, current = 0, rate, cycle = 1, temp, n, i;
    int rejected_amount = 0;

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
        rejected_amount = 0;

        
        if (i < n) {
            printf("Incoming: %d\n", packets[i]);
            if (packets[i] <= bsize - current) {
                current += packets[i];
                printf("Status: Accepted\n");
                printf("Rejected Amount: 0\n");
            } else {
                rejected_amount = packets[i];
                printf("Status: Rejected\n");
                printf("Rejected Amount: %d\n", rejected_amount);
            }
            i++; 
        } else {
            printf("Incoming: NA\n");
            printf("Rejected Amount: 0\n");
        }

        
        temp = current - rate;
        if (temp <= 0) {
            printf("Outgoing: %d\n", current);
            current = 0;
        } else {
            current -= rate;
            printf("Outgoing: %d\n", rate);
        }

        cycle++; 
    }

    return 0;
}