//SMTP client
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
void main()
{
  printf("Client Selected!");
  char to[100],from[100],sub[100],msg[100];
  char toip[100],fromip[100];
  int sockid;

  struct sockaddr_in addr2;

  addr2.sin_family=AF_INET;
  addr2.sin_addr.s_addr=INADDR_ANY;
  addr2.sin_port=3008;

  sockid = socket(AF_INET,SOCK_STREAM,0);

  connect(sockid,(struct sockaddr*)&addr2,sizeof(struct sockaddr));

  printf("\nSend message to server");
  printf("\nTo : ");
  scanf("%s",to);
  printf("\nFrom : ");
  scanf("%s",from);
  printf("\nSub : ");
  scanf("%s",sub);
  printf("\nMsg : ");
  scanf("%s",msg);
  send(sockid,to,sizeof(to),0);
  send(sockid,from,sizeof(from),0);
  send(sockid,sub,sizeof(sub),0);
  send(sockid,msg,sizeof(msg),0);

  close(sockid);

}
