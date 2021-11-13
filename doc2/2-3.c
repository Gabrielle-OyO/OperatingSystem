#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
void sig_handler(int num)
{
  printf("receive the signal %d.\n",num);
  alarm(3);
}
void fun_ctrl_c();
void fun_ctrl_c()
{
  printf("push Ctrl+C  but nothing happen !\n");
  (void) signal(SIGINT,SIG_DFL);
}

int main()
{
  (void) signal(SIGINT,fun_ctrl_c);
  signal(SIGALRM,sig_handler);
  alarm(3);
  while(1){pause();}
  exit(0);
}
