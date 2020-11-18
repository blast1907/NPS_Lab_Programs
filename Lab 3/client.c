#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<netinet/in.h>
#include<string.h>

void str_cli(FILE *fp,int sockfd)
{
	int bufsize=2048;
	char* send_buffer=(char*)malloc(bufsize);
	char* recv_buffer=(char*)malloc(bufsize);
	while(fgets(send_buffer,bufsize,fp)!=NULL)
	{
		printf("Sending %ld characters\n",strlen(send_buffer));
		send(sockfd,send_buffer,(bufsize),0);
		
		/*if(recv(sockfd,recv_buffer,bufsize,0)>0)
			fputs(recv_buffer,stdout);*/
	}
	printf("\nEOF\n");
}

int main(int argc,char *argv[])
{
	int create_socket;
	struct sockaddr_in serv_addr;
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(6798);
	inet_pton(AF_INET,argv[1],&serv_addr.sin_addr);

	if((create_socket=socket(AF_INET,SOCK_STREAM,0))>0)
		printf("The socket was created\n");

	if(connect(create_socket,(struct sockaddr *)&serv_addr, sizeof(serv_addr))==0)
		str_cli(stdin,create_socket);
	return close(create_socket);
}
