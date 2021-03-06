#include<stdlib.h>
#include<pthread.h>
#include<stdio.h>
struct msg
{
  struct msg *next;
  int num;
};
struct msg *head;
pthread_cond_t has_product=PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER;

void *producer(void *p)
{
  struct msg *mp;
  int i;
  for(i=0;i<20;++i)
  {
    mp=malloc(sizeof(struct msg));
    mp->num=rand()%1000+1;
    printf("Produce %d\n",mp->num);
    pthread_mutex_lock(&lock);
    mp->next=head;
    head=mp;
    pthread_mutex_unlock(&lock);
    pthread_cond_signal(&has_product);
    sleep(rand()%5);
  }
}

void *consumer(void *p)
{
  struct msg *mp;
  int i;
  for(i-0;i<20;i++)
  {
    pthread_mutex_lock(&lock);
    while(head==NULL)
      pthread_cond_wait(&has_product,&lock);
    mp=head;
    head=mp->next;
    pthread_mutex_unlock(&lock);
    printf("consume %d\n",mp->num);
    free(mp);
    sleep(rand()%5);
  }
}
  int main(int argc,char *argv[])
  {
    pthread_t pt,ct;
    srand(time(NULL));
    pthread_create(&pt,NULL,producer,NULL);
    pthread_create(&ct,NULL,consumer,NULL);
    pthread_join(pt,NULL);
    pthread_join(ct,NULL);
    return 0;
  }
  
