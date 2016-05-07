#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int main(int argc, char * argv[],char * envp[])
{
  FILE * fileArray[argc];
  char * msg="Hello World!!!!!\n";
 
  //open the files 
  //ignore argv[0] - its the name of the  program itself.
  int i;    
  for(i=1;i<argc;i++)
     fileArray[i]=fopen(argv[i],"w");

  //write to the files
  for(i=1;i<argc;i++)
    fwrite(msg,strlen(msg),1,fileArray[i]);

  //close the files
  for(i=1;i<argc;i++)
    fclose(fileArray[i]);
  
  return 0;
  }

