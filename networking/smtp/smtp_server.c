//SMTP server
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
  printf("Server selected");
  char to[100],from[100],sub[100],msg[100];
  char to_ext[20],from_ext[20];
  int i,j,k=0,len,f;
  int sockid,new_sockid;
  FILE *ptr;

  struct sockaddr_in addr1,addr2;

  addr1.sin_family=AF_INET;
  addr1.sin_addr.s_addr=INADDR_ANY;
  addr1.sin_port=3008;

  sockid = socket(AF_INET,SOCK_STREAM,0);
  f=bind(sockid,(struct sockaddr*)&addr1,sizeof(struct sockaddr));
  
  if(f == -1)
  {
    printf("Binding error");
    exit(1);
  }
    f=listen(sockid,3);
    if(f == -1)
  {
    printf("Listen failed");
    exit(1);
  }
    
  len = sizeof(struct sockaddr_in);
  new_sockid = accept(sockid,(struct sockaddr*)&addr2,&len);

  printf("\nReceived mail! from client");
  printf("\n__________________MAIL__________________");
  recv(new_sockid,to,sizeof(to),0);
  recv(new_sockid,from,sizeof(from),0);
  recv(new_sockid,sub,sizeof(sub),0);
  recv(new_sockid,msg,sizeof(msg),0);
  printf("\nTo : %s",to);
  printf("\nFrom : %s",from);
  printf("\nSub : %s",sub);
  printf("\nMsg : %s",msg);

  for(i=0;i<strlen(to);i++)
   {
     if(to[i]=='@')
     {
       for(j=i+1;j<strlen(to);j++)
       {
         if(to[j]=='.')
           break;
         to_ext[k]=to[j];
         k++;
       }
     }
   }
   printf("\nTo Domain name : %s",to_ext);
   k=0;
  for(i=0;i<strlen(from);i++)
  {
    if(from[i]=='@')
    {
      for(j=i+1;j<strlen(from);j++)
      {
        if(from[j]=='.')
         break;
        from_ext[k]=from[j];
        k++;
      }
    }
  }
  printf("\nFrom Domain name : %s\n",from_ext);

  close(sockid);
  close(new_sockid);
}
