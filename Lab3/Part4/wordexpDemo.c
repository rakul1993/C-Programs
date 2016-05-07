/*
   File: fileNameDemo3.c
   Course: CTEC102
   Author: Leon King,J230,x4200
   Date: Tuesday February 13, 2007
   Description: Using wordexp to match file names
                Enter any shell expression to expand a name, ie:
                        [a-m]*.txt   ~/???.c   $TZ/*    $(whoami)/abc
   */
 
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <wordexp.h>

#define FILEMODE 0600
int main()
{
  char fileName[60];
  int i;
  char *pos;
  wordexp_t  expansionList;
  int result;

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
  for(i=0;i<expansionList.we_wordc;i++)
      fprintf(stdout,"  %d. %s\n",i+1,expansionList.we_wordv[i]);
  
  wordfree(&expansionList);
  return 0;
  }

