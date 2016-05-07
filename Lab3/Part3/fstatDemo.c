#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
//#include <unistd.h>

int main(int argc, char * argv[],char * envp[])
{
  struct stat fileInfo; 
  if(stat(argv[1],&fileInfo)==-1) 
         {
           perror(argv[1]);
           exit(1);
          }

  fprintf(stdout,"Hello World %d\n",sizeof(struct stat)); 
  fprintf(stdout,"Inode: %d\n",(int) fileInfo.st_ino);
  fprintf(stdout,"Permisions: %04o\n",fileInfo.st_mode &0377);
 
  //Check man 2 stat for mask values of other permissions
  fprintf(stdout,"Readable by owner: %c\n",
                      S_IRUSR & fileInfo.st_mode ? 'r' : '-');
  if(S_ISREG(fileInfo.st_mode)) fprintf(stdout,"- Regular File\n");
  if(S_ISDIR(fileInfo.st_mode)) fprintf(stdout,"d Directory\n");
  if(S_ISCHR(fileInfo.st_mode)) fprintf(stdout,"c Character (console) device\n");
  if(S_ISBLK(fileInfo.st_mode)) fprintf(stdout,"b Block device\n");
  if(S_ISFIFO(fileInfo.st_mode)) fprintf(stdout,"p FIFO (pipe) device\n");
  if(S_ISLNK(fileInfo.st_mode)) fprintf(stdout,"l Symbolic Link\n");
  if(S_ISSOCK(fileInfo.st_mode)) fprintf(stdout,"s Socket \n");
  
  fprintf(stdout,"# of hard links: %d\n",fileInfo.st_nlink);

  fprintf(stdout,"Last access time (secs since the EPOCH): %ld\n", 
                            fileInfo.st_atime);
  fprintf(stdout,"Last access time: %s", ctime(&fileInfo.st_atime));
  
  fprintf(stdout,"Last modified time (secs since the EPOCH): %ld\n", 
                            fileInfo.st_mtime);
  fprintf(stdout,"Last modifiedaccess time: %s", ctime(&fileInfo.st_mtime));
 
  fprintf(stdout,"Last change time (secs since the EPOCH): %ld\n", 
                            fileInfo.st_mtime);
  fprintf(stdout,"Last change time: %s", ctime(&fileInfo.st_mtime));
  return 0;
 }
