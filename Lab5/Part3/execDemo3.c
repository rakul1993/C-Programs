/*
  Program: execleDemo.c
  Author: Rakul Mahenthiran
  Date: Apr 11, 15
  Purpose: This program demonstrates the use of execle.The 
           execle function allows the caller to specify the
           environment of the executed program via the argument envp.
*/

#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc,char *argv[],char *envp[])
{
  char *newEnv[] = {"name=rakul","shell=game","user=c00li0",NULL};
  pid_t childpid;
  int status, options=0;

  childpid=0;

    //Demostrating execle
  childpid=fork();
  if(childpid==0)  {  
    execle("./exeMyDemo","hello","this","is","unix",NULL,newEnv);
    perror("Failed to run execle");
    exit(1);
  }

  return 0;
  }

