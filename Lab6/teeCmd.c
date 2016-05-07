/*
   File: teeCmd.c
   Course: CENG251
   Author: Rakul Mahentiran
   Date: Apr 22, 2015
   Description: Redirects the output of a program to the given 
                commands. " myProg | TEE2 cmd1 cmd2 ..." 
*/
#include <stdio.h>
#include <getopt.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <fcntl.h>
#include <errno.h>
 
int main(int argc, char * argv[],char * envp[])
{
  char str[100];
  char buffer[100];
  int numOfFiles = argc-optind+1;
  int count;
  int fdRead=open("progOutput.txt",O_CREAT | O_WRONLY); //this file will hold the prog output
  int *fdArray;

  fdArray=(int *)calloc(numOfFiles,sizeof( int));
  fdArray[0]=fileno(stdout);  //always output to stdout
  
  //write prgrams output to file
  while(fgets(buffer,sizeof buffer, stdin))  {
    write(fdRead,buffer,strlen(buffer));
  }

  //redirect prog output to specidied commands and write into file
  for(count=1;optind<argc;count++,optind++)  { 
    sprintf(str,"%s progOutput.txt > %s.out",argv[count],argv[count]); 
    fdArray[count]=popen(str,"w");
  }
  
  //close all the files
  for(count=1;count<numOfFiles;count++) close(fdArray[count]);

  close(fdRead);
  return 0;
}

