/*
*     File: orphanProcess.c
*     Course: CENG251
*     Author: Rakul Mahenthiran
*     Date: Apr 05, 15
*     Description: This short program that creates a single child.   
*                  Have the main process die right away but leave the
*                  child still executing in an infinite loop. 
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

main()
{
  int childPID=0;	
  childPID = fork();
  switch(childPID)
  {
    //Child process
    case 0:
      while(1)  {
        fprintf(stdout,"\nChild %d still running......\n", getpid());
        system("ps -o ppid");
        sleep(15);
      }
      break;
     
    case -1:
      perror("Error in fork");
      break;
   
    //Parent process
    default:    
      fprintf(stdout,"\nParent %d has finished.\n", getpid());
    }
    
    fprintf(stdout,"Process %d is now done\n\n",getpid()); 
 }
  
