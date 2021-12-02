#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<errno.h>
#include<sys/types.h>
#define _CRT_SECURE_NO_WARNINGS
int port=8888;
int main()
{
  int sockfd;
  int n=0,i=0;
  int z; 
  char buf[80],str1[80],str2[80],ch;
  struct sockaddr_in adr_server;
  FILE *fp;
  printf("Please enter content...\n");
  scanf("%s\n",str2);
  fp=fopen("zyy.txt","w");
  printf("Open file...\n");
  fp=fopen("zyy.txt","r");
  if(fp==NULL)
  {
    perror("Failed to open file!");
    exit(1);
  }
  while(str2[n]!='\0')
  {
    fputc(str2[n],fp);
    n++;
  }
  printf("Connect to the server.....\n");
  adr_server.sin_family=AF_INET;
  adr_server.sin_port=htons(port);
  adr_server.sin_addr.s_addr=htonl(INADDR_ANY);
  bzero(&(adr_server.sin_zero),8);
  sockfd=socket(AF_INET,SOCK_DGRAM,0);
  if(sockfd==-1)
  {
    perror("Error socket!\n");
    exit(1);
  }
  printf("Send file...\n");
  while(str1!=EOF)
  {
    fgets(str1,80,fp);
    printf("%d:%s",i,str1);
    sprintf(buf,"%d:%s",i,str1);
    z=sendto(sockfd,buf,sizeof(buf),0,(struct sockaddr *)&adr_server,sizeof(adr_server));
    if(z<0)
    {
      perror("Error recvfrom!\n");
      exit(1);
    }
  }
  printf("Sending...\n");
  sprintf(buf,"qiut\n");
  z=sendto(sockfd,buf,sizeof(buf),0,(struct sockaddr *)&adr_server,sizeof(adr_server));
  if(z<0)
  {
    perror("Error recvfrom\n");
    exit(1);
  }
  fclose(fp);
  close(sockfd);
  exit(0);
}