#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<time.h>
typedef struct
{
  char str1[50];
  char str2[50];
  int no1,no2;
}str;

int main(int argc,char** argv)
{
  int shm_id,i;
  key_t key;
  str *p_map;
  time_t timep;
  struct tm *p;
  char* name="/dev/shm/myshm2";
  key=ftok(name,0);
  shm_id=shmget(key,4096,IPC_CREAT);
  if(shm_id==-1)
  {
    perror("Error getting the ID of the memory share\n");
    return 0;
  }
  p_map=(str*)shmat(shm_id,NULL,0);
  (*p_map).no1=0;(*p_map).no2=0;
  printf("This is A.\n");
  fgets((*p_map).str2,sizeof((*p_map).str2),stdin);
  (*p_map).no1=1;
  while(1)
  {
    if((*p_map).no2==1)
    {
      time(&timep);
      gmtime(&timep);
      p=localtime(&timep);
      printf("B:%s%d:%d:%d\n",(*p_map).str1,p->tm_hour,p->tm_min,p->tm_sec);
      (*p_map).str1[0]='\0';
      (*p_map).no2=0;
    }
    else continue;
    if((*p_map).no1==0)
    {
      fgets((*p_map).str2,sizeof((*p_map).str2),stdin);
      (*p_map).no1=1;
    }
  }
  if(shmdt(p_map)==-1)
    perror("Unmap error!\n");
}

