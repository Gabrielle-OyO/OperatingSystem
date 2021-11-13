#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<unistd.h>
struct msgmbuf
{
  long msg_type;
  char msg_text[512];
};
int main()
{
  int qid;
  key_t key;
  int len;
  struct msgmbuf msg;
  if((key=ftok(".",'a'))==-1)
  {
    perror("Error generating standard key");
    exit(1);
  }
  if((qid=msgget(key,IPC_CREAT|0666))==-1)
  {
  perror("Error create queue");
  exit(1);
  }
  printf("create/opened queue number is:%d\n",qid);
  puts("Please enter the message to be added to the queue:");
  if((fgets((&msg)->msg_text,512,stdin))==NULL)
  {
    puts("no message");
    exit(1);
  }
  msg.msg_type=getpid();
  len=strlen(msg.msg_text);
  if((msgsnd(qid,&msg,len,0))<0)
  {
    perror("Error adding information");
    exit(1);
  }
  if((msgrcv(qid,&msg,512,0,0))<0)
  {
  perror("Error reading message");
  exit(1);
  }
  printf("Read message:%s\n",(&msg)->msg_text);
  if((msgctl(qid,IPC_RMID,NULL))<0)
  {
  perror("Error deleting message queue");
  exit(1);
  }
  exit(0);
}
