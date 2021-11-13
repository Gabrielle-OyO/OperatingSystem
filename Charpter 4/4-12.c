#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/mman.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
int main()
{
  int fd;
  void *start;
  struct stat sb;
  fd=open("/etc/passwd",O_RDONLY);
  fstat(fd,&sb);
  start=mmap(NULL,sb.st_size,PROT_READ,MAP_SHARED,fd,0);
  if(start==MAP_FAILED)
  return 0;
  printf(" %s\n",(char *)start);
  munmap(start,sb.st_size);
  close(fd);
}
