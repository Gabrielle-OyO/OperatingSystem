#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
struct co
{
  int index;
  char name[8];
  char MTel[12];
  char Tel[12];
};
int x;
int main()
{
  struct co *p;
  char ch;
  printf("do you want to add a user? Y/N\n");
  ch=getchar();
  if(ch=='y'||ch=='Y')
  {
    p=(struct co *)malloc(sizeof(struct co));
    p->index=++x;
    printf("User name:");
    scanf("%s",p->name);
    printf("MoveTel:");
    scanf("%s",p->MTel);
    printf("Tel:");
    scanf("%s",p->Tel);
    printf(" intex:%d\n name:%s\n MoveTel:%s\n HomeTel:%s\n",p->index,p->name,p->MTel,p->Tel);
  }
  printf("page size = %d\n",getpagesize());
}
