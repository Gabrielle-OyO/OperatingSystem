#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>
void fun_ctrl_c();
int main()
{
  (void) signal(SIGINT,fun_ctrl_c);
  printf("endless while !\n");
  while(1)
  {
    printf("press  ctrl+c\n");
    sleep(3);
  }
  exit(0);
}

void fun_ctrl_c()
{
  printf("\t you pressed ctrl+c\n");
  (void) signal(SIGINT,SIG_DFL);
}
