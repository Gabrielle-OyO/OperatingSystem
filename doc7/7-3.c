#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#define MAX_SEQUENCE 100

struct Data
{
  int num;
  int Fibo[MAX_SEQUENCE];
};

void *Fibonacci(void *data)
{
  struct Data *tmp=(struct Data*)data;
  int i;
  if(tmp->num=0) return;
  if(tmp->num==1)
  {
    tmp->Fibo[0]=0;
    return;
  }
  tmp->Fibo[0]=0;
  tmp->Fibo[1]=1;
  
  for(i=2;i<tmp->num;i++)
  {
    tmp->Fibo[i]=tmp->Fibo[i-1]+tmp->Fibo[i-2];
  }
}

int main()
{
  struct Data data;
  pthread_t th;
  int ret;
  int n;
  int i;
  
  printf("The fibonacci program!\n Plead input an number within 1~200:");
  scanf("%d",&n);
  if(n<0||n>200)
  {
    printf("Your input is error.");
    return -1;
  }
  data.num=n;
  
  ret=pthread_create(&th,NULL,Fibonacci,(void *)&data);
  if(ret!=0)
  {
    printf("create thread error!\n");
    return -1;
  }
  
  pthread_join(th,NULL);
  
  if(data.num==0)
  {
    printf("Nothing output.");
  }
  else
  {
    printf("The Fibonacci %d items are:\n",data.Fibo[i]);
  }
  printf("\n");
}

