#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
int main()
{
        int server_fd;
        struct sockaddr_in server_addr,client_addr;
        socklen_t len=sizeof(server_addr);
        char buffer[1024];
        int bytes;
        char time;
        server_fd=socket(AF_INET,SOCK_DGRAM,0);
        server_addr.sin_family=AF_INET;
        server_addr.sin_port=htons(8053);
        server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
        memset(buffer,0,sizeof(buffer));
        sendto(server_fd,&time,sizeof(time)-1,0,(struct sockaddr*)&server_addr,len);
        bytes=recvfrom(server_fd,buffer,sizeof(buffer)-1,0,(struct sockaddr*)&server_addr,&len);
        buffer[bytes]='\0';
        printf("%s",buffer);
        close(server_fd);
        return 0;
}
