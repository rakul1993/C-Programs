/*
  Name: Rakul Mahenthiran
  Ptogram: modForkingShell.c
  Date: Apr 22, 2015
  Description: This program runs shell built in commands specified.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <wordexp.h>
#include <sys/wait.h>

int main()  {
  int status;
  char cmd[1000];
  wordexp_t expansionList;
  int result;
  char * compile;
  FILE *history = fopen(".shellHistory","a+");
  char temp[100] = "tail .shellHistory -n";
  char gcc[20] = "gcc ";
  
  while(1)  {
    fprintf(stdout,"Prompt> ");
    fgets(cmd,sizeof(cmd),stdin);
    cmd[strlen(cmd)-1]='\0';
    if(feof(stdin)) break;

    result=wordexp(cmd,&expansionList, WRDE_SHOWERR);

    //Check if the line is a comment
    if(cmd[0]=='#') continue;

    fprintf(history,"%s\n",cmd);  

    //Check for builtin commands
    //export
    if(strcmp(expansionList.we_wordv[0],"export")==0)  {
      setenv(expansionList.we_wordv[1],expansionList.we_wordv[3],0);
      continue;
    }

    //unset
    if(strcmp(expansionList.we_wordv[0],"unset")==0)  {
      unsetenv(expansionList.we_wordv[1]);
      continue;
    }

    //history
    if(strcmp(expansionList.we_wordv[0],"history" ) == 0)  { 
      if(! expansionList.we_wordv[1])//= null, defualt = 10
        system("tail .shellHistory");
      else
        system(strcat(temp, expansionList.we_wordv[1]));
    }
    

    //compile
    compile = expansionList.we_wordv[0];
    if((compile = strrchr(expansionList.we_wordv[0],'.')) != NULL )
      if(strcmp(compile,".c") == 0)  { 
        strcat(gcc,expansionList.we_wordv[0]); // "gcc test.c"
        strcat(gcc," -o ");  // "gcc test.c -o "
        strcat(gcc,strtok(expansionList.we_wordv[0],"."));
       				
        system(gcc);
    }     

     if(strcmp(cmd,"exit")==0) exit(0);

     switch(fork())
     {
       case 0:  //We are in the child
            execvp(expansionList.we_wordv[0],expansionList.we_wordv);
            return -1; //Failed to exec
       case -1:  perror("Failed to fork");
             break;
       default: 
               wait(&status); 
               wordfree(&expansionList);

      }
     fprintf(stdout,"Status of command is: %d\n",status>>8);    
   }
  return 0;
  }
