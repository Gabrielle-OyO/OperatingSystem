#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<unistd.h>
#include<string.h>
#include<time.h>

#define MSGLEN 650
#define LINE "-------------------------------\n"
#define NAMESIZE 50
#define PROJ_PATH "/tmp"
#define CLIENT_MSG 0x55
#define SERVER_MSG 0xAA
#define QUIT "86"
#define PROJ 0x26

struct my_msgbuf
{
  long msg_type;
  char msg_user[NAMESIZE];
  char msg_time[100];
  char msg_text[500];

};

