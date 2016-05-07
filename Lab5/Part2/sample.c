/*
   File: zombie.c
   Course: CENG411
   Author: Prof. Leon King,007,007
   Date: Tuesday Apr 22, 2014   09:14 AM
   
   Based on forkDemo3.  The state of the child should be Z.
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
   int childPID;	
   childPID = fork();
   if(childPID==0)
          fprintf(stdout,"This is the child %d speaking\n",
                           getpid());
   else if(childPID==-1)
          exit(1);  //return right away - the child becomes a zombie 
   else 
      {   //This is the parent     
          sleep(1); //give the child enough time to die
          fprintf(stdout,"The is parent %d.  Checking the status of child %d\n", getpid(),childPID);
          system("ps -O ppid");  //examine the child status
          wait(NULL); //reap the child
       }
   fprintf(stdout,"Process %d is now done\n",getpid());
 }
 
