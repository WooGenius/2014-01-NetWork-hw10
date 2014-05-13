/* Sample UDP server */

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char**argv)
{
  int sockfd,n;
  struct sockaddr_in servaddr,cliaddr;
  socklen_t len;
  char buf[100];
  int addNum, addNum2, result;
  int boo = 1;

  sockfd=socket(AF_INET,SOCK_DGRAM,0);

  memset(&servaddr,0,sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
  servaddr.sin_port=htons(32000);
  bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

  for (;;)
    {
      len = sizeof(cliaddr);
	  if (boo) {
      	  recvfrom(sockfd,&addNum,sizeof(int),0,(struct sockaddr *)&cliaddr,&len);
		  sendto(sockfd,&addNum,sizeof(int),0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
	  } else {
      	  recvfrom(sockfd,&addNum2,sizeof(int),0,(struct sockaddr *)&cliaddr,&len);
		  result = addNum + addNum2;
		  sendto(sockfd,&result,sizeof(int),0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
    	  printf("-------------------------------------------------------\n");
     	  printf("Send Result :  %d + %d = %d\n",addNum, addNum2, result);
     	  printf("-------------------------------------------------------\n");
		  break;
	  }
	  boo = !boo;
    }
  close(sockfd);
}
