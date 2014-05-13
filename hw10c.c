/* Sample UDP client */

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char**argv)
{
  int sockfd,n;
  struct sockaddr_in servaddr,cliaddr;
  int addNum, result;
  char buf[BUFSIZ];

  if (argc != 2)
    {
      printf("usage: ex04c <IP address>\n");
      exit(1);
    }

  sockfd=socket(AF_INET,SOCK_DGRAM,0);

  memset(&servaddr,0,sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr=inet_addr(argv[1]);
  servaddr.sin_port=htons(32000);

  while (fgets(buf, BUFSIZ,stdin) != NULL)
    {
      addNum = atoi(buf);
      sendto(sockfd,(void *)&addNum,sizeof(int),0,
             (struct sockaddr *)&servaddr,sizeof(servaddr));
	  printf("-------------------------------------------------------\n");
	  printf("Send Integer : %d\n", addNum);
	  printf("-------------------------------------------------------\n");

      recvfrom(sockfd,(void *)&result,sizeof(int),0,NULL,NULL);

	  if (result != addNum) {
		  printf("-------------------------------------------------------\n");
	  	  printf("Result : %d\n", result);
		  printf("-------------------------------------------------------\n");
		  break;
	  }
    }
  close(sockfd);
}
