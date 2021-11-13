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
    int sumAge=0;   //add
    for(i=0;i<5;i++)
    {
      printf("child process reading.....: the %d people %s's age is :%d\n",i+1,(*(p_map+i)).name,(*(p_map+i)).age);//change
      sumAge+=(*(p_map+i)).age;	  //add
    }
    (*p_map).age=110;
    (*p_map).age=sumAge;	//add
    munmap(p_map,sizeof(people)*10);
    exit(0);
  }
  else
  {
    int sumAge=0;
    temp='a';
    char name[30];
    int age;
    for(i=0;i<5;i++)
    {
      temp+=1;
      printf("Please enter name and age:\n");
      scanf(" %d",&((*(p_map+i)).age));
      sumAge+=(*(p_map+i)).age;	
      memcpy((*(p_map+i)).name,&temp,2);
      (*p_map).age=sumAge;
      //(*(p_map+i)).age=20+i;
    }
    sleep(5);
    printf("parent process reading......: five people age sum is :%d\n",(*p_map).age);
    printf("Unmap memory......\n");
    munmap(p_map,sizeof(people)*10);
    printf("Successfully unmap memory!\n");
  }
  return 0;
}
