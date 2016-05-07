/*
*     File: zombieProcess.c
*     Course: CENG251
*     Author: Rakul Mahenthiran
*     Date: Apr 05, 15
*     Description: This program creates a single child. The 
*                  child process dies right away but leaves 
*                  the parent running in a loop or an extended 
*                  sleep. 
*/


#include <stdio.h>

main()
{
  int childPID;	
  childPID = fork();

  //Child process
  if(childPID==0)
    fprintf(stdout,"\nThis is child %d.\n", getpid());    
           
  else if(childPID==-1)
    fprintf(stderr,"Error in fork\n");
 
  //Parent process
  else   {      
    sleep(5); 
    fprintf(stdout,"This is parent %d. Checking child %d status.\n", getpid(),childPID);
    system("ps -O ppid");  
    wait(NULL); 
  }
   fprintf(stdout,"Process %d is now done\n\n",getpid());
}
 
