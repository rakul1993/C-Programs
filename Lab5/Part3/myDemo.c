/*
  Program: myDemo.c
  Name: Rakul Mahenthiran
  Date: Apr 11, 15
  Purpose: This program print out the arguments used to run 
           the program and the enviroment variables.
*/
 
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char * argv[],char * envp[])
{
  int count;

  fprintf(stdout,"\n\n\Running program myDemo.c: \n");
  
  fprintf(stdout,"\tProgram Arguments: ");
  for(count = 0; count < argc; count++) {
    fprintf(stdout,"%s", argv[count]);
    if(count < (argc-1))
      fprintf(stdout,", ");
  }
 
  fprintf(stdout,"\n\n\tProgram Enviroment variables: \n");
  for(count = 0; envp[count]; count++) {
    fprintf(stdout,"\t\t%d. %s\n",count,envp[count]);
  }

  return 0;
}
