/*
  Program: scriptReader.c
  Author: Rakul Mahenthiran
  Date: Apr 11, 15
  Purpose: This program reads the myScript.sh and executes
           all four lines of command on the script
*/

#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <wordexp.h>

int main(int argc, char * argv[], char * envp[])  {

  FILE *fp = fopen("myScript.sh","r");
  wordexp_t expansion[4]; 
  char **expansionList;
  int i,count;
  pid_t childPID;
  int status;

  //script contains 4 commands, use word expansion on each line containing a command.
  wordexp("`sed -n '3p' myScript.sh`", &expansion[0], 0);
  wordexp("`sed -n '4p' myScript.sh`", &expansion[1], 0);
  wordexp("`sed -n '5p' myScript.sh`", &expansion[2], 0);
  wordexp("`sed -n '6p' myScript.sh`", &expansion[3], 0);

  //loop runs until all 4 commands are executed
  for(count=0; count<4; count++){
    expansionList = expansion[count].we_wordv;  
    switch(fork())  {
      //child process
      case 0:
        fprintf(stdout,"Child PID: %d\n", getpid());
        fprintf(stdout,"Executing script command......\n");
        execlp(expansionList[0],expansionList[0],expansionList[1],NULL);
        break;

      //forking error
      case -1:
        perror("Error in Fork");
        break;

      //parent process
      default:
        childPID=wait(&status);
        fprintf(stdout,"This is the parent %d speaking, child %d has finshed.\n\n", getpid(), childPID); 
    } 
  }  
 
  wordfree(&expansion[0]);
  wordfree(&expansion[1]);
  wordfree(&expansion[2]);
  wordfree(&expansion[3]);
  return 0;
}  
  

