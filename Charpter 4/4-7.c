#include<sys/time.h>
#include<unistd.h>
#include<stdio.h>
int main()
{
  struct timeval tv1,tv2;
  struct timezone tz;
  gettimeofday(&tv1,&tz);
  printf("tv_sec; %ld\n",tv1.tv_sec);
  printf("tv_usec; %ld\n",tv1.tv_usec);
  gettimeofday(&tv2,&tz);
  printf("tv2_usec-tv1_usec; %ld\n",tv2.tv_usec-tv1.tv_usec);
  return 0;
}
