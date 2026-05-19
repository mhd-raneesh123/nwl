#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<math.h>
#include<arpa/inet.h>
int main()
{
        int sockfd;
        struct sockaddr_in server_addr,client_addr;
        socklen_t addr_len=sizeof(client_addr);
        int num;
        char buffer[1024];
        sockfd=socket(AF_INET,SOCK_DGRAM,0);
        server_addr.sin_family=AF_INET;
        server_addr.sin_port=htons(8053);
        server_addr.sin_addr.s_addr=INADDR_ANY;
        bind(sockfd,(struct sockaddr*)&server_addr,addr_len);
        printf("udp started\n");
        while(1)
        {
                memset(buffer,0,sizeof(buffer));
                recvfrom(sockfd,&num,sizeof(num),0,(struct sockaddr*)&client_addr,&addr_len);
                int isprime=0;
                for(int i=2;i<=sqrt(num);i++)
                {
                        if(num%i==0)
                        {
                                isprime=1;
                        }
                }
                if(isprime==1)
                {       sprintf(buffer,"%d is composite\n",num);}
                else
                {
                        sprintf(buffer,"%d is prime\n",num);
                }
                sendto(sockfd,buffer,strlen(buffer),0,(struct sockaddr*)&client_addr,addr_len);
        }
        close(sockfd);
        return 0;
}