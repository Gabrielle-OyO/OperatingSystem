#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<string.h>
int main()
{
  pid_t result;
  int r_num;
  int i=0,y=1;
  int pipe_fd[2];
  char buf_r[100],buf_w[100];
  memset(buf_r,0,sizeof(buf_r));
  if(pipe(pipe_fd)<0)
  {
    printf("create pipe failed!");
    exit(1);
  }
  result=fork();
  if(result<0)
  {
    perror("create child pid failed!");
    exit(1);
  }
  else if(result==0)
  {
    close(pipe_fd[1]);
    while(y)
    {
      if((r_num=read(pipe_fd[0],buf_r,100))>0)
      {buf_r[r_num]='\0';}
      printf("child read string from pipe%d  ,string:%s\n",r_num,buf_r);
      if(strcmp(buf_r,"q")==0)
        y=0;
    }
    close(pipe_fd[0]);
    while(y)
    {
      i++;
      printf("input pipe string  the : %d\n  ",i);
      scanf("%s",buf_w);
      if(write(pipe_fd[1],buf_w,strlen(buf_w))!=-1)
        printf("parent pid write into pipe:%s\n",buf_w);
      printf("continue(1/0?):");
      scanf("%d",&y);
      if(y==0)
        write(pipe_fd[1],"q",2);
    }
    close(pipe_fd[1]);
    waitpid(result,NULL,0);
    exit(0);
  }
}
