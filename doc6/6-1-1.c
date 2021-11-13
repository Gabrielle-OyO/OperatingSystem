#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define nLOOP 10
int counter=0;

pthread_mutex_t cat;				//

void *pthread(void *vptr)
{
  int i,val;
  for(i=0;i<nLOOP;i++)
  {
    pthread_mutex_lock(&cat);			//
    val=counter;
    sleep(vptr);
    printf("%x: %d\n",(unsigned int)pthread_self(),counter);
    counter=val+1;
    pthread_mutex_unlock(&cat);			//
    sleep(1);
  }
  return NULL;
}

int main(int argc,char **argv)
{
  pthread_t tid1,tid2;
  pthread_mutex_init(&cat,NULL);		//
  pthread_create(&tid1,NULL,pthread,(void*)1);
  pthread_create(&tid2,NULL,pthread,(void*)2);
  pthread_join(tid1,NULL);
  pthread_join(tid2,NULL);
  pthread_mutex_destroy(&cat);			//
  return 0;
}
