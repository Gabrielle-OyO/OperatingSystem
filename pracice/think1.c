#include<stdio.h>
#include<signal.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/types.h>
void sig_callback1(){printf("signal:SIGUSER1\n");}
void sig_callback2(){printf("signal:SIGUSER2\n");}
void sig_haha(){printf("heng,i do not terminate the process,so what?\n");}
int main()
{
  if(SIG_ERR==signal(SIGUSR1,sig_callback1))
  {
    printf("error1\n");
    return 1;
  }
  if(SIG_ERR==signal(SIGUSR2,sig_callback2))
  {
    printf("error2\n");
    return 1;
  }
  if(SIG_ERR==signal(SIGTERM,sig_haha))
  {
    printf("error3\n");
    return 1;
  }
  while(1)
  {
    getchar();
    kill(getpid(),SIGUSR1);
    getchar();
    raise(SIGUSR2);
  }
  return 0;
}
