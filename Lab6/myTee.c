/*
   File: myTee.c
   Course: CENG251
   Author: Rakul Mahentiran
   Date: Apr 22, 2015
   Description: redirects the output from a program to the 
                specified files "myProg | TEE f1 f2 ...."
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>

 
int main(int argc, char * argv[],char * envp[])
{
  int i;
  char buffer[100];

  //create an array of file pointers
  int nFiles=argc-optind+1;
  int *fdArray;
  fdArray=(int *)calloc(nFiles,sizeof( int));
  fdArray[0]=fileno(stdout);  //always output to stdout
  for(i=1;optind<argc;i++,optind++)
     fdArray[i]=open(argv[optind], O_APPEND | O_CREAT | O_WRONLY ); 

  //move input from stdin to all open files
  while(fgets(buffer,sizeof buffer, stdin))  {
     for(i=0;i<nFiles;i++) 
         write(fdArray[i],buffer,strlen(buffer));
  }

  //close all the files
  for(i=1;i<nFiles;i++) close(fdArray[i]);
  return 0;
}
