#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
// 同下，输出在指针指向的地址


#define ERR_EXIT(m) \
  do { \
    perror(m); \
    exit(EXIT_FAILURE); \
  } while (0)

int main()
{
  int listenfd;
  // PF_INET equals AF_INET
  listenfd = socket(PF_INET, SOCK_STREAM, 0);
  /* listenfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); */
  if (listenfd < 0) {
    ERR_EXIT("socket");
  }
  struct sockaddr_in servaddr;
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(5188);
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

  if(bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
    ERR_EXIT("bind");
  }
  if(listen(listenfd, SOMAXCONN) < 0) {
    ERR_EXIT("listen");
  }
  if(listenfd < 0) {
    ERR_EXIT("socket");
  }
  struct sockaddr_in peeraddr;
  socklen_t peerlen = sizeof(peeraddr);
  int connfd = accept(listenfd, (struct sockaddr*)&peeraddr, &peerlen);
  if(connfd < 0) {
    ERR_EXIT("accept");
  }
  char buf[1024];
  while(1) {
    bzero(buf,  sizeof(buf));
    ssize_t readsize = read(connfd, buf, sizeof(buf));
    if(readsize < 0) {
      ERR_EXIT("read");
    }
    printf("%s",  buf);
    write(connfd, buf, readsize);
  }
  return 0;
}
