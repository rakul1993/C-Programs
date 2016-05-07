/*
   File: wordExp.c
   Course: CENG251
   Author: Rakul Mahenthiran
   Date: Feb 28, 2015
   Description: Using wordexp to and stat to match file names
                Enter any shell expression to expand a name, ie:
                        [a-m]*.txt   ~/???.c   $TZ/*    $(whoami)/abc
*/
 
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <wordexp.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <locale.h>
#include <langinfo.h>
#include <stdint.h>


#define FILEMODE 0600
int main()
{
  char fileName[60];
  int i;
  char *pos;
  wordexp_t  expansionList;
  int result;

  int userExeCount=0;
  int groupExeCount=0;
  int otherExeCount=0;
  int directoryCount=0;
  int hiddenFileCount=0;
  int sameModAccCount=0;	

  struct stat st_buf;
  int status;

  char buffer[1000]="The name of your file is: ";

  fprintf(stdout,"Enter file name: ");
  fgets(fileName,sizeof(fileName),stdin);

  //Remove the trailing newline using rindex
  if((pos=rindex(fileName,'\n'))==(fileName+strlen(fileName)-1)) 
          *pos='\0'; 

  fprintf(stdout,"Your file name is: x%sx\n",fileName);

  result=wordexp(fileName,&expansionList, WRDE_SHOWERR);
  fprintf(stdout,"Result: %d\n",result);
  fprintf(stdout,"Your fileName matched the following %d files: \n",
                    expansionList.we_wordc);

  //Print out all matching file names
  for(i=0;i<expansionList.we_wordc;i++) {
      fprintf(stdout,"  %d. %s\n",i+1,expansionList.we_wordv[i]);

      status = stat (expansionList.we_wordv[i], &st_buf);

      if(((st_buf.st_mode & S_IXUSR) ? "true" : "false")=="true"){
        printf ("\t\tUser Executable.\n");
        userExeCount++;
      }

      if(((st_buf.st_mode & S_IXGRP) ? "true" : "false")=="true"){
        printf ("\t\tGroup Executable.\n");
        groupExeCount++;
      }

      if(((st_buf.st_mode & S_IXOTH) ? "true" : "false")=="true"){
        printf ("\t\tOther Executable.\n");
        otherExeCount++;
      }
     
      if(expansionList.we_wordv[i][0] == '.'){
        printf ("\t\tHidden file.\n");
        hiddenFileCount++;
      } 

      if(S_ISDIR (st_buf.st_mode)) {
        printf ("\t\tDirectory.\n");
        directoryCount++;
      }

      if(ctime(&st_buf.st_atime) == ctime(&st_buf.st_mtime)){
        printf ("\t\tSame last modified and last accessed time.\n");
        sameModAccCount++;
      }
  }

  fprintf(stdout,"\n\n%d files are user executable.\n",userExeCount);
  fprintf(stdout,"%d files are group executable.\n",groupExeCount);
  fprintf(stdout,"%d files are others executable.\n",otherExeCount);
  fprintf(stdout,"%d files are hidden.\n",hiddenFileCount);
  fprintf(stdout,"%d expansions are directories.\n",directoryCount);
  fprintf(stdout,"%d files have the same last modified and accessed time.\n",sameModAccCount);
  
  wordfree(&expansionList);
  return 0;
  }

