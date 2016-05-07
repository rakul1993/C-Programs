/*
   File:fGetPWnam.c
   Purpose: Read the password record froma specified file.    
   Course: CENG251
   Author: Rakul Mahenthiran
   Date: Mar 24, 2015
    
*/


#include <stdio.h>
#include <crypt.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <locale.h>
#include <langinfo.h>
#include <stdint.h>

int main(int argc, char * argv[],char * envp[])
{
  FILE *fileSel = fopen(argv[1], "r");	//take command line argument and open the file with that name
  char c;
  char line[1024];

  while(fgets(line, sizeof(line), fileSel)) {	//read and store to file loop
    if (strstr(line, argv[2]) != NULL) {
      fprintf(stdout,"%s",line);   // if line contains the text, print it
    }
  }
 
  return 0;
}

