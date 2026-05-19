#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<arpa/inet.h>
int main()
{
        int server_fd,client_fd;
        struct sockaddr_in server_addr,client_addr;
        socklen_t len=sizeof(client_addr);
        int num,fact=1;
        server_fd=socket(AF_INET,SOCK_STREAM,0);
        server_addr.sin_family=AF_INET;
        server_addr.sin_port=htons(8053);
        server_addr.sin_addr.s_addr=INADDR_ANY;
        bind(server_fd,(struct sockaddr*)&server_addr,sizeof(server_addr));
        listen(server_fd,1);
        printf("waiting..\n");
        client_fd=accept(server_fd,(struct sockaddr*)&client_addr,&len);
        printf("connected\n");
        while(1)
        {
                recv(client_fd,&num,sizeof(num),0);
                for(int i=1;i<=num;i++)
                {
                        fact*=i;
                }
                printf("sending the factorial of %d\n",num);
                send(client_fd,&fact,sizeof(fact),0);
        }
        close(client_fd);
        close(server_fd);
        return 0;
}