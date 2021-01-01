//implement DNS_Server using udp
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
  int sockid,dlen,i,c=0;
  char dname[50],data[100],ip[100];
  FILE *ptr;
  struct sockaddr_in addr1,addr2;

  sockid = socket(AF_INET,SOCK_DGRAM,0);
  memset(&addr1,0,sizeof(addr1));
  memset(&addr2,0,sizeof(addr2));

  addr1.sin_family = AF_INET;
  addr1.sin_addr.s_addr = INADDR_ANY;
  addr1.sin_port = htons(8080);

  bind(sockid,(struct sockaddr*)&addr1,sizeof(addr1));

  int len = sizeof(addr2);
  printf("\nReceiving domain name from client!");
  int n = recvfrom(sockid,dname,50,0,(struct sockaddr*)&addr2,&len);
  dname[n]='\0';
  printf("\nDomain Name : %s ",dname);

  dlen = strlen(dname);
  printf("\nLength of domain %d ",dlen);
  ptr = fopen("DOMIP.txt","r");

  while(fgets(data,100,ptr))
  {
    if(strstr(data,dname)!=NULL)
    {
      for(i=1;i<strlen(data)-dlen;i++)
      {
        ip[i-1] = data[dlen+i];
      }
      c++;
    }
  }
  if(c!=1)
  printf("\nError");

  printf("\nIp : %s ",ip);
  sendto(sockid,ip,strlen(ip),0,(struct sockaddr*)&addr2,sizeof(addr2));
  close(sockid);
}
