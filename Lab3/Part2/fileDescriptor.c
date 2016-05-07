#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int main(int argc, char * argv[],char * envp[])
{
  int fdArray[argc];
  char * msg="Hello World!!!!!\n";
  char buffer[512]="";
 
  //open the files 
  //Ignore argv[0] - we don't want the program to overwrite itself
  
  int i;
  for(i=1;i<argc;i++)
     fdArray[i]=open(argv[i],O_CREAT | O_WRONLY,0600);

  //write to the files
  for(i=1;i<argc;i++)
    write(fdArray[i],"Greetings world!!!!\n", sizeof(buffer));

  //close the files
  for(i=1;i<argc;i++)
    close(fdArray[i]);
  
  return 0;
  }
