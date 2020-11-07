#include<unistd.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<netinet/in.h>
#include<string.h>

void str_cli(FILE *fp, int sockfd,struct sockaddr* serv_addr)
{
   int bufsize = 2048;
   int n;
   char* recv_buffer = malloc(bufsize);
   char* send_buffer = malloc(bufsize);
	 int servaddr_len = sizeof(struct sockaddr_in);
	while(fgets(send_buffer,bufsize,fp)!=NULL)
  {
	   sendto(sockfd, send_buffer, bufsize ,0,serv_addr,servaddr_len);  

  	 if((n=recvfrom(sockfd, recv_buffer, bufsize, 0,NULL,NULL)>0)) 
    	 fputs(recv_buffer,stdout);
  }
	printf("\nEOF\n");
}

int main(int argc,char *argv[])
{
  int sockfd;
  struct sockaddr_in serv_addr;
  if ((sockfd = socket(AF_INET,SOCK_DGRAM,0)) > 0)
    printf("The Socket was created\n");
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(16001);

  inet_pton(AF_INET,argv[1],&serv_addr.sin_addr);
 
  
  str_cli(stdin,sockfd,(struct sockaddr *)&serv_addr);
  exit(0);
}
