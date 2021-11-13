#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
void sig_handler(int num)
{
  printf("receive the signal %d.\n",num);
  printf("user:zyy\n");
}

int main()
{
  signal(SIGALRM,sig_handler);
  alarm(2);
    pause();
  exit(0);
}
