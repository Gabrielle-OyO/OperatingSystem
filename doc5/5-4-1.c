#include<stdio.h>
#include<pthread.h>
void *print_thread_id(void *arg)
{
  printf("Current thread id is %u\n",(unsigned)pthread_self());
}

int main(int argc,char *argv[])
{
  pthread_t thread;
  pthread_create(&thread,NULL,print_thread_id,NULL);
  sleep(10);
  printf("Main thread id is %u\n",(unsigned)pthread_self());
  return 0;
}

