#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<string.h>
void f1();
void f2(char c);
FILE *fp;
char buf_s[1000];
int i=0;
int main()
{
  pid_t pid;
  int pipe_fd[2];
  char buf_r[1000],c,d;
  memset(buf_r,0,sizeof(buf_r));
  if(pipe(pipe_fd)<0)
  {
    printf("create pipe fail!\n");
    return -1;
  }
  pid=fork();
  if(pid<0)
  {
    perror("create pid failed!");
    exit;
  }
  else if(pid==0)
  {
    close(pipe_fd[1]);
    read(pipe_fd[0],buf_r,1000);
    printf("child pipe read :\n%s",buf_r);
    close(pipe_fd[0]);
    exit(0);
  }
  else
  {
    if((fp=fopen("ceshi.c","r"))==NULL)
      exit(0);
    while((c=fgetc(fp))!=EOF)
    {
      if(c=='/')
        if((d=fgetc(fp))=='*')
          f1();
        else
        {
          buf_s[i]=c;
          buf_s[i+1]=d;
          i+=2;
        }
      else if(c=='\''||c=='\"')
        f2(c);
      else
      {
        buf_s[i]=c;
        i++;
      }
    }
    buf_s[i]=0;
    fclose(fp);
    close(pipe_fd[0]);
    write(pipe_fd[1],buf_s,1000);
    printf("parent pipe write succeed!\n");
    close(pipe_fd[1]);
    waitpid(pid,NULL,0);
    exit(0);
  }
}

void f1()
{
  char c,d;
  c=fgetc(fp);
  d=fgetc(fp);
  while(c!='*'||d!='/')
  {
    c=d;
    d=fgetc(fp);
  }
}

void f2(char c)
{
  char d;
  buf_s[i]=c;
  i++;
  while((d=fgetc(fp))!=c)
  {
    buf_s[i]=d;
    i++;
    if(d=='\\')
    {
      buf_s[i]=fgetc(fp);
      i++;
    }
  }
  buf_s[i]=d;
  i++;
}
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
