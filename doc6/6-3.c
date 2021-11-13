#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

pthread_mutex_t count_lock;
pthread_cond_t count_nonzero;
unsigned count=0;

void *decrement_count(void *arg)
{
  pthread_mutex_lock(&count_lock);
  printf("decrement_count get count_lock\n");
  while(count==0)
  {
    printf("decrement_count count==0\n");
    printf("decrement_count before cond_wait\n");
    pthread_cond_wait(&count_nonzero,&count_lock);
    printf("decrement_count after cond_wait\n");
  }
  printf("tid1:count--\n");
  count=count-1;
  printf("tid1:count%d\n",count);
  pthread_mutex_unlock(&count_lock);
}
  
void *increment_count(void *arg)
{
 pthread_mutex_lock(&count_lock);
 printf("increment_count before cond_signal\n");
 if(count==0)
 {
   printf("increment_count before cond_signal\n");
   pthread_cond_signal(&count_nonzero);
   printf("increment_count after cond_signal\n");
 }
 printf("tid2:count++\n");
 count=count+1;
 printf("tid2:count=%d\n",count);
 pthread_mutex_unlock(&count_lock);
}

int main(void)
{
  pthread_t tid1,tid2;
  pthread_mutex_init(&count_lock,NULL);
  pthread_cond_init(&count_nonzero,NULL);
  
  pthread_create(&tid1,NULL,decrement_count,NULL);
  printf("tid1 decrement is created,begin sleep 2s\n");
  sleep(2);
  printf("after sleep 2s,start creat tid2 increment\n");
  
  pthread_create(&tid2,NULL,decrement_count,NULL);
  printf("after tid2 increment is created,begin sleep 10s\n");
  sleep(5);
  
  printf("after sleep 5s,begin exit!\n");
  pthread_exit(0);
  
  return 0;
}
  
