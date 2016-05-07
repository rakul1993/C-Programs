/******************
 * File: qestion3c.c
 * Purpose: Use SIGHUP to reinitialize a program
 * Course: CENG 251
 * Author: Rakul Mahenthiran
 * Date: March 26, 2015
********************/

#include <stdio.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>


void signalHandler(int signum)
{
  char *f, *m;
  char buffer[100];
  FILE * listFile = fopen("files.list","r");

  while (fgets(buffer,100,listFile) != NULL)
  {
    fprintf(stdout,"File String: %s",buffer);

    f = strtok(buffer,":");
    m = strtok(NULL,":");
  }
}


int main(int argc, char * argv[],char * envp[])
{
  void signalHandler(int);
  int count;  

  fprintf(stdout, "Current Process id: %d\n", getpid());
  fprintf(stdout, "Parent Process id: %d\n", getppid());

  signal(SIGHUP,signalHandler);

  for(count=0; count<5; count++) 
  {
    fprintf(stdout, "ID: %d\n", count);
    sleep(6);
  }
}
