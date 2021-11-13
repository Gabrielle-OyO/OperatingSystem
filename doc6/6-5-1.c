#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

void *thread_fun1(void *arg)
{
  printf("thread 1 returning\n");
  for(int i=0;i<10;i++) printf("fun1---%d\n",i);
  return ((void *)1);
  sleep(100);
}

void *thread_fun2(void *arg)
{
  printf("thread 2 exiting\n");
  for(int i=0;i<10;i++) printf("fun2---%d\n",i);
  pthread_exit((void *)2);
}

int main(void)
{
  int err;
  pthread_t tid1,tid2;
  void *tret;
  
  err=pthread_create(&tid1,NULL,thread_fun1,NULL);
  if(err!=0)
    fprintf(stderr,"can't create thread 1:%s\n",strerror(err));
    
  err=pthread_create(&tid2,NULL,thread_fun2,NULL);
  if(err!=0)
    fprintf(stderr,"can't create thread 2:%s\n",strerror(err));
    
  err=pthread_join(tid1,&tret);
  if(err!=0)
    fprintf(stderr,"can't join with thread 1:%s\n",strerror(err));
  printf("thread 1 exit code %ld\n", (long)tret);
  
  err=pthread_join(tid2,&tret);
  if(err!=0)
    fprintf(stderr,"can't join with thread 2:%s\n",strerror(err));
  printf("thread 2 exit code %ld\n", (long)tret);
  exit(0); 
}
  
  
