#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
int main()
{
    int sock;
    struct sockaddr_in server_addr;
    int number;
    sock=socket(AF_INET,SOCK_STREAM,0);
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(8053);
    server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    connect(sock,(struct sockaddr*)&server_addr,sizeof(server_addr));
    while(1)
    {
        printf("enter the number\n");
        printf("\nclient:");
        scanf("%d",&number);
        send(sock,&number,sizeof(number),0);
        recv(sock,&number,sizeof(number),0);
        printf("\nserver:%d\n",number);
    }
    close(sock);
    return 0;
}
