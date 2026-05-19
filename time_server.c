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
        socklen_t len=sizeof(client_addr);
        char buffer[1024];
        int bytes;
        server_fd=socket(AF_INET,SOCK_DGRAM,0);
        server_addr.sin_family=AF_INET;
        server_addr.sin_port=htons(8053);
        server_addr.sin_addr.s_addr=INADDR_ANY;
        bind(server_fd,(struct sockaddr*)&server_addr,sizeof(server_addr));
        printf("udp started\n");
        memset(buffer,0,sizeof(buffer));
        bytes=recvfrom(server_fd,buffer,sizeof(buffer)-1,0,(struct sockaddr*)&client_addr,&len);
        buffer[bytes]='\0';
        time_t now=time(NULL);
        now+=19800;
        struct tm *ist_time = gmtime(&now);
        sprintf(buffer,"Current time is:%s\n",asctime(ist_time));
        sendto(server_fd,buffer,strlen(buffer),0,(struct sockaddr*)&client_addr,len);
        printf("time sended\n");
        close(server_fd);
        return 0;
}
