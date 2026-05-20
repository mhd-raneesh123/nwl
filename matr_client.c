#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
int main()
{
    int server_fd;
    struct sockaddr_in server_addr;
    socklen_t addr_len=sizeof(server_addr);
    int A[10][10]={0},B[10][10]={0},C[10][10]={0};
    int r1,c1,r2,c2;
    server_fd=socket(AF_INET,SOCK_STREAM,0);
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(8053);
    server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    connect(server_fd,(struct sockaddr*)&server_addr,sizeof(server_addr));
    printf("connected to server\n");
        printf("enter the r1 and c1 of matrix A: ");
        scanf("%d %d",&r1,&c1);
        printf("\nenter the r2 and c2 of matrix B: ");
        scanf("%d %d",&r2,&c2);
        if(c1!=r2)
        {
                printf("cannot perform multiplication\n");
                close(server_fd);
                return -1;
        }
    send(server_fd,&r1,sizeof(r1),0);
    send(server_fd,&r2,sizeof(r2),0);
    send(server_fd,&c1,sizeof(c1),0);
    send(server_fd,&c2,sizeof(c2),0);
        printf("enter the matrix A\n");
        for(int i=0;i<r1;i++)
        {
                for(int j=0;j<c1;j++)
                {
                        scanf("%d",&A[i][j]);
                }
        }
        printf("enter the matrix B\n");
        for(int i=0;i<r2;i++)
        {
                for(int j=0j;j<c2;j++)
                {
                        scanf("%d",&B[i][j]);
                }
        }
    send(server_fd,A,sizeof(A),0);
    send(server_fd,B,sizeof(B),0);
        recv(server_fd,C,sizeof(C),0);
        printf("result:\n");
        for(int i=0;i<r1;i++)
        {
                for(int j=0;j<c2;j++)
                {

                        printf("%d\t",C[i][j]);
                }
                printf("\n");
        }
    close(server_fd);
    return 0;
}