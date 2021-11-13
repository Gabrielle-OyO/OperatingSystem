#include<sys/types.h>
#include<unistd.h>
#include<sys/mman.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
typedef struct
{
  char name[4];
  int age;
}people;
int main(int argc,char** argv)
{
  pid_t result;
  int i;
  people *p_map;
  char temp;
  p_map=(people*)mmap(NULL,sizeof(people)*10,PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);
  result=fork();
  if(result<0)
  {
    perror("Failed to create child process\n");
    exit(0);
  }
  else if(result==0)
  {
    sleep(2);
    for(i=0;i<5;i++)
      printf("child process reading.....: the %d people age is :%d\n",i+1,(*(p_map+i)).age);
    (*p_map).age=110;
    munmap(p_map,sizeof(people)*10);
    exit(0);
  }
  else
  {
    temp='a';
    for(i=0;i<5;i++)
    {
      temp+=1;
      memcpy((*(p_map+i)).name,&temp,2);
      (*(p_map+i)).age=20+i;
    }
    sleep(5);
    printf("parent process reading......: five people age sum is :%d\n",(*p_map).age);
    printf("Unmap memory......\n");
    munmap(p_map,sizeof(people)*10);
    printf("Successfully unmap memory!\n");
  }
  return 0;
}
