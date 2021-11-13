#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>
int main()
{
  const char fname[]="main.c";
  struct stat stat_info;
  if(0!=stat(fname,&stat_info))
  {
    perror("Failed to obtain file information!");
    exit(1);
  }
  printf("File device number:%ld\r\n",stat_info.st_dev);
  printf("File system index:%ld\r\n",stat_info.st_ino);
  printf("File type and access permissions:%d\r\n",stat_info.st_mode);
  printf("The number of hard links to the file:%ld\r\n",stat_info.st_nlink);
  printf("User ID of the owner of the file:%d\r\n",stat_info.st_uid);
  printf("Organization ID of the file owner:%d\r\n",stat_info.st_gid);
  printf("Device file:%ld\r\n",stat_info.st_rdev);
  printf("File size:%ld\r\n",stat_info.st_size);
  printf("I/O buffer size of the file system:%ld\r\n",stat_info.st_blksize);
  printf("The number of occupied file blocks (each block size is 512 bytes):%ld\r\n",stat_info.st_blocks);
  printf("The time when the file was last accessed or executed:%ld\r\n",stat_info.st_atime);
  printf("The time when the file was last modified:%ld\r\n",stat_info.st_mtime);
  printf("The last time the file was updated:%ld\r\n",stat_info.st_ctime);
  printf("文件设备编号:%ld\r\n",stat_info.st_dev);
  printf("文件系统索引:%ld\r\n",stat_info.st_ino);
  printf("文件的类型和存取权限:%d\r\n",stat_info.st_mode);
  printf("文件的硬连接数目:%ld\r\n",stat_info.st_nlink);
  printf("文件所有者的用户识别码:%d\r\n",stat_info.st_uid);
  printf("文件所有者的组织识别码:%d\r\n",stat_info.st_gid);
  printf("装置设备文件:%ld\r\n",stat_info.st_rdev);
  printf("文件大小:%ld\r\n",stat_info.st_size);
  printf("文件系统的I/O缓冲区大小:%ld\r\n",stat_info.st_blksize);
  printf("占用文件区块的个数（每一区块大小为512个字节）:%ld\r\n",stat_info.st_blocks);
  printf("文件最后一次被存取或被执行的时间:%ld\r\n",stat_info.st_atime);
  printf("文件最后一次被修改的时间:%ld\r\n",stat_info.st_mtime);
  printf("文件最近一次被更的时间:%ld\r\n",stat_info.st_ctime);
  return 0;
}
