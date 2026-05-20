#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
int main()
{
    int server_fd,client_fd;
    struct sockaddr_in server_addr,client_addr;
    socklen_t addr_len=sizeof(client_addr);
    int A[10][10],B[10][10],C[10][10]={0};
    int r1,c1,r2,c2;
    server_fd=socket(AF_INET,SOCK_STREAM,0);
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(8053);
    server_addr.sin_addr.s_addr=INADDR_ANY;
    bind(server_fd,(struct sockaddr*)&server_addr,sizeof(server_addr));
    listen(server_fd,1);
    printf("waiting for connection\n");
    client_fd=accept(server_fd,(struct sockaddr*)&client_addr,&addr_len);
    printf("connected to client\n");
    recv(client_fd,&r1,sizeof(r1),0);
    recv(client_fd,&r2,sizeof(r2),0);
    recv(client_fd,&c1,sizeof(c1),0);
    recv(client_fd,&c2,sizeof(c2),0);
    recv(client_fd,A,sizeof(A),0);
    recv(client_fd,B,sizeof(B),0);
        for(int i=0;i<r1;i++)
        {
                for(int j=0;j<c2;j++)
                {
                        for(int k=0;k<c1;k++)
                        {
                                C[i][j]+=A[i][k]*B[k][j];
                        }
                }
        }
    send(client_fd,C,sizeof(C),0);
    close(client_fd);
    close(server_fd);
    return 0;
}