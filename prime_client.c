#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
int main()
{
        int sockfd;
        struct sockaddr_in server_addr;
        socklen_t addr_len=sizeof(server_addr);
        char buffer[1024];
        sockfd=socket(AF_INET,SOCK_DGRAM,0);
        server_addr.sin_family=AF_INET;
        server_addr.sin_port=htons(8053);
        server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
        while(1)
        {
                int num;
                memset(buffer,0,sizeof(buffer));
                printf("enter a number\n");
                scanf("%d",&num);
                printf("client :");
                sendto(sockfd,&num,sizeof(num),0,(struct sockaddr*)&server_addr,addr_len);
                recvfrom(sockfd,buffer,sizeof(buffer),0,(struct sockaddr*)&server_addr,&addr_len);
                printf("\nserver :%s",buffer);
        }
        close(sockfd);
        return 0;
}