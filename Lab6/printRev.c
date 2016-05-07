/*
  Name: Rakul Mahenthiran
  Program: printRev.c
  Date: Apr 22, 2015
  Description: This program uses va_args to take an unknown number of
               args, reverse the order and write to a file specifed by fd(arg). 
*/

#include <stdio.h>
#include <stdarg.h> //Note the new include
#include <string.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define ENDOFLIST -1024*1024*1024

void printRev(int myFd, ...)  {
  char *p;
  int numArgs=0;
  int count=0;
  va_list args;

  //This loop counts the number of args
  va_start(args,myFd);
  while(va_arg(args,char *))  {
    numArgs++;
  }
  va_end(args);

  //Create an array based on number of args
  char *argsList[numArgs+1];
  argsList[numArgs+1]=" ";  //extra index to store " "

  //This loop stores the args into an array
  va_start(args,myFd);
  while((p=va_arg(args,char *)))  {
    if(count<numArgs)  {
      argsList[count]=p;
      count++;
    }
  }
  va_end(args);

  //This loop writes args into file in reverse order
  myFd=open("reverseArgs.txt",O_CREAT | O_WRONLY,0600);
  for(count=numArgs;count>0;count--)  {
    write(myFd,argsList[count-1],strlen(argsList[count-1]));
    write(myFd,argsList[numArgs+1],strlen(argsList[numArgs+1]));//puts space after arg
  } 
}

int main()  {

  printRev(1,"This", "is", "a", "test","I", "Have","Many","Args",NULL);
  
  return 0;
}


