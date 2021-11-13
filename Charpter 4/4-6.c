#include<time.h>
#include<stdio.h>
int main()
{
  time_t timep;
  char *wday[]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
  struct tm *p;
  time(&timep);
  printf("%s",asctime(gmtime(&timep)));
  p=localtime(&timep);
  printf("%d-%d-%d ",(1900+p->tm_year),(1+p->tm_mon),(p->tm_mday));
  printf("%s %d:%d:%d\n",wday[p->tm_wday],p->tm_hour,p->tm_min,p->tm_sec);
  return 0;
}
