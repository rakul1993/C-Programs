/*
*     File: reapingProcess.c
*     Course: CENG251
*     Author: Rakul Mahenthiran
*     Date: Apr 05, 15
*     Description: This short program creates a single child.   
*                  The child will output its process id and 
*                  the name and exit  with a status code. The 
*                  parent will wait for child to die and 
*                  display status.
*/

#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

main() {

  int originalProcess;	
  int childProcess;
  int status;

  originalProcess=getpid();

  if(fork()==-1) 
    fprintf(stderr,"Error in fork\n");
  
  //Parent process
  else if(originalProcess==getpid()) {
    childProcess = waitpid(-1, &status, WNOHANG);
    fprintf(stdout,"This is Parent: %d.\nMy dead child is: %d.\nMy child exit status code: %d.\n", getpid(), childProcess, WEXITSTATUS(status));
  }

  //Child Process
  else  { 
    fprintf(stdout,"This Child: %d has exited.\n\n", getpid());
    exit(17);
  }
}
  
