//implement DNS_client using udp
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

void main()
{
  int sockid;
  char dname[50],ip[50];
  struct sockaddr_in addr1;

  sockid = socket(AF_INET,SOCK_DGRAM,0);
  memset(&addr1,0,sizeof(addr1));

  addr1.sin_family = AF_INET;
  addr1.sin_addr.s_addr = INADDR_ANY;
  addr1.sin_port = htons(8080);

  printf("\nSending Domain name to server!");
  scanf("%s",dname);
  sendto(sockid,dname,strlen(dname),0,(struct sockaddr*)&addr1,sizeof(addr1));
  printf("\nReceiving Corresponding Ip from server!");
  recvfrom(sockid,ip,50,0,(struct sockaddr*)&addr1,sizeof(addr1));
  printf("\nIp Address : %s",ip);
  close(sockid);
}
