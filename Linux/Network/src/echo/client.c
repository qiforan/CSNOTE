#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>

#define ERR_EXIT(m) \
  do { \
    perror(m); \
    exit(EXIT_FAILURE); \
  } while (0)

int main()
{
  int sockfd;
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    ERR_EXIT("socket");

  struct sockaddr_in servaddr;
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(5188);
  servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  int rt = connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
  if(rt < 0)
    ERR_EXIT("connect");
  char sendbuf[1024] = {0};
  while(fgets(sendbuf, sizeof(sendbuf), stdin) != NULL)
  {
    write(sockfd, sendbuf, strlen(sendbuf));
    bzero(sendbuf,  sizeof(sendbuf));
    read(sockfd, sendbuf, sizeof(sendbuf));
    printf("%s", sendbuf);
  }
  close(sockfd);
}
