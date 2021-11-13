#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/types.h>
void fun_ctrl_c();
void fun_ctrl_z();
void fun_ctrl_d();
int main()
{
  int i;
  sigset_t set,pendest;
  struct sigaction action;
  (void) signal(SIGINT,fun_ctrl_c);
  (void) signal(SIGTSTP,fun_ctrl_z);
  (void) signal(SIGQUIT,fun_ctrl_d);
  if(sigemptyset(&set)<0)
    perror("initail error!");
  if(sigaddset(&set,SIGINT)<0)
    perror("<Ctrl>+C  error!");
  if(sigaddset(&set,SIGTSTP)<0)
    perror("<Ctrl>+Z  error!");
  if(sigprocmask(SIG_BLOCK,&set,NULL)<0)
    perror("put an error signal");
  else
  {
    for(i=0;i<10;i++)
    {
      printf("<Ctrl>+C  <Ctrl>+Z  is  blocked!  need to  procced '<Ctrl>+\' signal\n");
      sleep(3);
    }
  }
  if(sigprocmask(SIG_UNBLOCK,&set,NULL)<0)
    perror("delete an error\n");
}

void fun_ctrl_c()
{
  int n;
  printf("\t push <Ctrl>+C  system ignores you?\n");
  for(n=0;n<4;n++)
    printf("\t dealing <Ctrl>+C signal\n");
}

void fun_ctrl_z()
{
  int n;
  printf("\t push <Ctrl>+Z  system ignores you?\n");
  for(n=0;n<6;n++)
    printf("\t dealing <Ctrl>+Z signal\n");
}

void fun_ctrl_d()
{
  int n;
  printf("\t push '<Ctrl>+\'  system answer you?\n");
  for(n=0;n<2;n++)
    printf("\t dealing <Ctrl>+Z signal\n");
}






    
