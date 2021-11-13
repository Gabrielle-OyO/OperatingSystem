#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
int main()
{
  pid_t result;
  result=fork();
  int ret;
  int newret;
  if(result<0)
  {
    perror("ERROR EXIT!\n");
    exit(1);
  }
  else if(result==0)
  {
    raise(SIGSTOP);
    exit(0);
  }
  else
  {
    printf("PID is :%d\n",result);
    if((waitpid(result,NULL,WNOHANG))==0)
    {
      if(ret=kill(result,SIGKILL)==0)
      {
        printf("fun kill's return is %d,pid is %d\n",ret,result);
      }
      else
      {
        perror("kill failed!");
      }
    }
  }
}
