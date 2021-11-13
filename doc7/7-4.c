#include<pthread.h>
#include<stdio.h>
#include<semaphore.h>
#include<stdlib.h>
#include<unistd.h>
sem_t full,empty;
pthread_mutex_t mutex;
int num;
void *R(void *arg)
{
  sem_wait(&empty);
  pthread_mutex_lock(&mutex);
  printf("R input number :-------");
  scanf("%d",&num);
  pthread_mutex_unlock(&mutex);
  sem_post(&full);
}
void *W(void *arg)
{
  sem_wait(&full);
  pthread_mutex_lock(&mutex);
  printf("W output number :--------%d\n",num);
  pthread_mutex_unlock(&mutex);
  sem_post(&empty);
}
int main(int argc,char *argv[])
{
  pthread_t R1,R2;
  pthread_t W1,W2;
  sem_init(&full,0,0);
  sem_init(&empty,0,1);
  pthread_mutex_init(&mutex,NULL);
  int a=1,b=1;
  pthread_create(&R1,NULL,R,&a);
  pthread_create(&R2,NULL,R,&b);
  pthread_create(&W1,NULL,W,&a);
  pthread_create(&W2,NULL,W,&b);
  pthread_join(R1,NULL);
  pthread_join(R2,NULL);
  pthread_join(W1,NULL);
  pthread_join(W2,NULL);
  pthread_mutex_destroy(&mutex);
  sem_destroy(&full);
  sem_destroy(&empty);
  return 0;
}
