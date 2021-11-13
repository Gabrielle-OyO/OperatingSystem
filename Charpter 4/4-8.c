#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include<unistd.h>
int main()
{
  long int begin,sec,stop;
  struct timeval tv1,tv2;
  struct timezone tz;
  char tmp;
  begin=0;
  stop=0;
  sec=0;
  system("clear");
  printf("Timer program(unit s)\n");
  printf("Input b(begin) :The timer starts to count\n");
  printf("Input w(watch) :View the accumulated time\n");
  printf("Input r(rest)  :Restart timing\n");
  printf("Input s(stop)  :Pause timing\n");
  printf("Input e(end)   :End time\n");
  while(1)
  {
    scanf("%c",&tmp);
      if(tmp=='b')
      {
        if(begin==1&&stop==0)
          printf("Timer has started\n");
        if(begin==0&&stop==0)
        {
          printf("Timer start\n");
          gettimeofday(&tv1,&tz);
          sec=0;
          begin=1;
        }
        if(stop==1)
        {
          gettimeofday(&tv1,&tz);
          stop=0;
          printf("End\n");
        }
      }
    if(tmp=='w')
    {
      gettimeofday(&tv2,&tz);
      printf("Already timed %lds \n",sec+tv2.tv_sec-tv1.tv_sec);
    }
    if(stop==1)
    {
      printf("Already timed %lds\n",sec);
    }
    if(tmp=='s')
    {
      if(stop==1)
      {
        printf("Time has been paused!\n");
      }
      if(stop==0)
      {
        gettimeofday(&tv2,&tz);
        sec=sec+tv2.tv_sec-tv1.tv_sec;
        printf("Timeout,already timed %lds\n",sec);
        stop=1;
      }
    }
    if(tmp=='r')
    {
      gettimeofday(&tv2,&tz);
      printf("Alread timed %lds\n",sec+tv2.tv_sec-tv1.tv_sec);
      printf("The timer is reset after 5 secondes!\n");
      sleep(5);
      begin=0;
      sec=0;
      stop=0;
      system("clear");
      printf("Timer program(unit s)\n");
      printf("Input b(begin) :The timer starts to count\n");
      printf("Input w(watch) :View the accumulated time\n");
      printf("Input r(rest)  :Restart timing\n");
      printf("Input s(stop)  :Pause timing\n");
      printf("Input e(end)   :End time\n");
    }
    if(tmp=='e') break;
  }
  return 0;
}
