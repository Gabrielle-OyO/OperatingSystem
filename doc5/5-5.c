#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

pthread_t ntid;
void printids(const char *s)
{
  pid_t pid;
  pthread_t tid;
  pid=getpid();
  tid=pthread_self();
  printf("%s pid= %u tid= %u (0x%x)\n",s,(unsigned int)pid,(unsigned int)tid,(unsigned int)tid);
}

void *thread_fun(void *arg)
{
  pid_t pid;
  pthread_t tid;
  pid=getpid();
  tid=pthread_self();
  int k;
  for(k=0;k<5;k++)
  {
    printf(" pid= %u tid= %u (0x%x)\n",(unsigned int)pid,(unsigned int)tid,(unsigned int)tid);
  }
  
  printids(arg);
  return NULL;
}

int main(void)
{
  int err;
  err=pthread_create(&ntid,NULL,thread_fun,"I'm the new thread:\n");
  if(err!=0)
  {
    fprintf(stderr,"Failed to create thread:%s\n",strerror(err));
    exit(1);
  }
  printids("I'm the parent process:\n");
  
  pid_t pid;
  pthread_t tid;
  pid=getpid();
  tid=pthread_self();
  int k;
  for(k=0;k<10;k++)
  {
    printf(" pid= %u tid= %u (0x%x)\n",(unsigned int)pid,(unsigned int)tid,(unsigned int)tid);
  }
  sleep(1);
  return 0;
}
  

