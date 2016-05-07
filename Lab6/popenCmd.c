#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wordexp.h>
#include <sys/types.h>
#include <string.h>

int myPipe(char * argv[]) {
  
  int pipes[2];
  pid_t PID;
  wordexp_t wordExpanssion;
  char **word;
  int count;
  char mode;
  int whichUsed;
  pipe(pipes); 

  wordexp(argv[1],&wordExpanssion,0);
  word= wordExpanssion.we_wordv;
  for(count = 0; count < wordExpanssion.we_wordc; count++)
    fprintf(stdout,"w[%d] %s\n", count, word[count]); 
  wordfree(&wordExpanssion);
    
  if(*word[1] == 'r')
    mode = 'r';
  else if(*word[1] == 'w')
    mode = 'w';
  fprintf(stdout,"mode: %c \n", mode);
 
  PID = fork(); 
  if(PID == 0)  { // child
    if(whichUsed == 0)  { //write 
      close(pipes[0]);
      dup2(0, pipes[1]);// old, new
    }
    else if(whichUsed == 1)  {  //read
      close(pipes[1]);
      dup2(1, pipes[0]);
    }
  }
 
  else  { //parent
    if(mode == 'r')  {
      whichUsed = 1;
      return pipes[0];
    }
    else  {
      whichUsed = 0;
      return pipes[1];
    }
  }
}//end of function
 
int main(int argc, char * argv[],char * envp[])  {
  fprintf(stdout,"Hello World %d \n",myPipe(argv));
  return 0;
}

