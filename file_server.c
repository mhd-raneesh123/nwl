#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>
int main()
{
        int server_fd,client_fd;
        struct sockaddr_in server_addr,client_addr;
        socklen_t len=sizeof(client_addr);
        char buffer[4096],fname[1024],content[1024];
        int bytes;
        server_fd=socket(AF_INET,SOCK_STREAM,0);
        server_addr.sin_family=AF_INET;
        server_addr.sin_port=htons(8053);
        server_addr.sin_addr.s_addr=INADDR_ANY;
        bind(server_fd,(struct sockaddr*)&server_addr,sizeof(server_addr));
        listen(server_fd,1);
        client_fd=accept(server_fd,(struct sockaddr*)&client_addr,&len);
        printf("connected\n");
        while(1)
        {
                if(fork()==0){
                bytes=recv(client_fd,fname,sizeof(fname)-1,0);
                fname[bytes]='\0';
                FILE *fp=fopen(fname,"r");
                bytes=fread(content,1,sizeof(content)-1,fp);
                content[bytes]='\0';
                if(fp)
                        sprintf(buffer,"pid:%d   content:%s",getpid(),content);
                else
                        sprintf(buffer,"pid:%d   %s:FILE NOT FOUND",getpid(),fname);
                send(client_fd,buffer,strlen(buffer),0);
                fclose(fp);
                }
        }
        close(client_fd);
        close(server_fd);
        return 0;
}
