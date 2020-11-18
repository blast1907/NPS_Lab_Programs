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


void str_echo(int connfd)
{
	int n;
	int bufsize=2048;
	char *buffer=(char *)malloc(bufsize);
	printf("The connection descriptor is %d\n",connfd);;
	again:
		while((n=recv(connfd,buffer,bufsize,0))>0){
			printf("Server received %ld characters\n",strlen(buffer));
			//send(connfd,buffer,n,0);
			printf("Command Received : %s\n",buffer);
			system(buffer);
		}
		if(n<0)
			goto again;
}
int main()
{



	struct sockaddr_in serv_addr,cli_addr;
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=INADDR_ANY;
	serv_addr.sin_port = htons(6798);
	int listenfd,connfd;
	int pid;
	if((listenfd=socket(AF_INET,SOCK_STREAM,0))>0)
		printf("The socket was created\n");

	//printf("The address before bind is %s and port number %d\n",inet_ntoa(address.sin_addr),ntohs(address.sin_port));

	if(bind(listenfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))==0)
		printf("Binding Servers Socket\n");

	printf("The address after bind, IP is %s and port number is %d\n",inet_ntoa(serv_addr.sin_addr),ntohs(serv_addr.sin_port));

	listen(listenfd,3);

	while(1)
	{
		socklen_t cli_addrlen=sizeof(cli_addr);
		connfd=accept(listenfd,(struct sockaddr*)&cli_addr, &cli_addrlen);
		if(connfd > 0)
		{
			printf("The client's IP is %s and port is %d\n",inet_ntoa(cli_addr.sin_addr),ntohs(cli_addr.sin_port));
			printf("The server's IP is %s\n",inet_ntoa(serv_addr.sin_addr));
			if((pid=fork())==0)
			{
				printf("Server with pid %d is ready, which is forked from pid %d \n",getpid(),getppid());
				close(listenfd);
				str_echo(connfd);
				exit(0);
			}
			close(connfd);
		}
	}
	return 0;
}
