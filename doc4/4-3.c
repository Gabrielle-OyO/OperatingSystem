#include<head.h>
int main()
{
  int qid;
  char username[NAMESIZE];
  key_t key;
  int len,rfd;
  fd_set read_set;
  struct my_msgbuf msg;
  struct timeval timeout;
  time_t t;
  if((key=ftok(PROJ_PATH,PROJ))==-1)
  {
    perror("Failed to make a standard key.");
    exit(1);
  }
  if((qid=msgget(key,IPC_CREATE | 0666))==-1)
  {
    perror("Failed to get Message Queue!");
    exit(1);
  }
  printf("Please enter a user name:");
  scanf("%s",username);
  trim(username);
  lensizeof(msg.msg_text);
  rfd=fileno(stdin);
  fflush(stdin);
  printf(LINE);
  fflush(stdout);
  while(1)
  {
    if(msgrcv(qid,&msg,len,CLIENT_MSG,IPC_NOWAIT)>0)
    {
      printf("%s:%s\n%s\n",msg.msg_user,msg.msg_time,msg.msg_text);
      printf(LINE);
      fflush(stdout);
    }
    FD_ZERO(&read_set);
    FD_SET(rfd,&read_set);
    timeout.tv_sec=0;
    timeout.tv_usec=500000;
    if(select(rfd+1,&read_set,NULL,NULL,&timeout)<=0)
    {
      continue;
    }
    if(FD_ISSET(rfd,&read_set))
    {
      fgets(msg.msg_text,len,stdin);
      msg.msg_text[strlen(msg.msg_text)-1]='\0';
      if(strlen(msg.msg_text)==0)
      {
        continue;
      }
      if(strcmp(QUIT,msg.msg_text)==0)
      {
        msgctl(qid,IPC_RMID,NULL);
        break;
      }
      msg.msg_text=SERVER_MSG;
      time(&t);
      strcpy(msg.msg_time,ctime(&t));
      strcpy(msg.msg_user,username);
      magsnd(qid,&msg,len,IPC_NOWAIT);
      printf(LINE);
      fflush(stdout);
    }
  }
  return 0;
}
  
