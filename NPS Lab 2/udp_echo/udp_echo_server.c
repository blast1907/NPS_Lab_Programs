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

void str_echo(int sockfd,struct sockaddr* cli_address)
{
    int n;
    int bufsize = 1024;
    char *buffer = malloc(bufsize);
	  int addrlen= sizeof(struct sockaddr_in);
	  
	while(1)
  {
    n=recvfrom(sockfd,buffer,bufsize,0,cli_address,&addrlen);
  	sendto(sockfd,buffer,n,0,cli_address,addrlen);
  }
}
int main()
{
  int sockfd; 
  struct sockaddr_in serv_address,cli_address;

  if ((sockfd = socket(AF_INET,SOCK_DGRAM,0)) > 0) //sockfd
    printf("The socket was created\n");

    serv_address.sin_family = AF_INET;
    serv_address.sin_addr.s_addr = INADDR_ANY;
    serv_address.sin_port = htons(16001);
    printf("The address before bind %s  ...\n",inet_ntoa(serv_address.sin_addr) );
    if (bind(sockfd,(struct sockaddr *)&serv_address,sizeof(serv_address)) == 0)	//bind
      printf("Binding Socket\n");   
   str_echo(sockfd,(struct sockaddr *)&cli_address);
	  
    return 0 ;
}

