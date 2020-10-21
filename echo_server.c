#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<netinet/in.h>
void str_echo(int connfd)
{
	int n;
	int bufsize=1024;
	char *buffer=(char *)malloc(bufsize);
	again:
		while((n=recv(connfd,buffer,bufsize,0))>0)
			send(connfd,buffer,n,0);
		if(n<0)
			goto again;
}
int main()
{



	struct sockaddr_in address;
	address.sin_family=AF_INET;
	address.sin_addr.s_addr=INADDR_ANY;
	address.sin_port = htons(15001);
	int listenfd,connfd;
	int pid;
	if((listenfd=socket(AF_INET,SOCK_STREAM,0))>0)
		printf("The socket was created");

	printf("The address before bind is %s \n",inet_ntoa(address.sin_addr));

	if(bind(listenfd,(struct sockaddr *)&address,sizeof(address))==0)
		printf("Binding Socket\n");

	printf("The address after the bind is %s \n",inet_ntoa(address.sin_addr));

	listen(listenfd,3);
	printf("The server is listening");

	while(1)
	{
		socklen_t addrlen=sizeof(address);
		connfd=accept(listenfd,(struct sockaddr*)&address, &addrlen);
		if(connfd > 0)
		{
			printf("The client %s is conected\n",inet_ntoa(address.sin_addr));
		}
		if((pid=fork())==0)
		{
			printf("Inside Child");
			close(listenfd);
			str_echo(connfd);
			exit(0);
		}
		close(connfd);
	}
	return 0;
}
