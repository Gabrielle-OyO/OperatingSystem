#include<pthread.h>
#include<stdio.h>
#include<sys/time.h>
#include<string.h>
#define MAX 10
pthread_t thread[2];
pthread_mutex_t mut;
int number=0,i;

void *thread1()
{
  int i;				//
  printf("thread1:I'm thread 1\n");
  for(i=0;i<MAX;i++)
  {
    printf("thread1:number= %d\n",number);
    pthread_mutex_lock(&mut);
      number++;
    pthread_mutex_unlock(&mut);
    sleep(2);
  }
  printf("thread1:Is the main function waiting for me to complete the task?\n");
  pthread_exit(NULL);
}

void *thread2()
{
  int i;				//
  printf("thread2:I'm thread 2\n");
  for(i=0;i<MAX;i++)
  {
    printf("thread2:number= %d\n",number);
    pthread_mutex_lock(&mut);
      number++;
    pthread_mutex_unlock(&mut);
    sleep(3);
  }
  printf("thread2:Is the main function waiting for me to complete the task?\n");
  pthread_exit(NULL);
}

void thread_create(void)
{
  int temp;
  memset(&thread,0,sizeof(thread));
  if((temp=pthread_create(&thread[0],NULL,thread1,NULL))!=0)
    printf("Thread 1 creation failed!\n");
  else
    printf("Thread 1 is created!\n");
  if((temp=pthread_create(&thread[1],NULL,thread2,NULL))!=0)
    printf("Thread 2 creation failed!\n");
  else
    printf("Thread 2 is created!\n");
}

void thread_wait(void)
{
  if(thread[0]!=0)
  {
    pthread_join(thread[0],NULL);
    printf("Thread 1 has ended!\n");
  }
  if(thread[1]!=0)
  {
    pthread_join(thread[1],NULL);
    printf("Thread 2 has ended!\n");
  }
}

int main()
{
  pthread_mutex_init(&mut,NULL);
  printf("I am the main function is creating a thread\n");
  thread_create();
  printf("I am the main function, waiting for the thread to complete the task!\n");
  thread_wait();
  return 0;
}


