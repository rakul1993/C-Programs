/*
   File: findPerson.c
   Course: CENG411
   Author: Leon King,J230,x4200
   Date: Wednesday Feb 03, 2010   21:32 PM
 
   Program will prompt you for a record number
   Using random access it will retrieve the specified record
*/


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include "person.h"

int main(int argc, char * argv[],char * envp[])
{
  struct PERSON person;
  char response[512];

  FILE *myDB=fopen("myDB","r");
  fprintf(stdout,"The size of an PERSON is: %d\n\n",sizeof person);
  while(true)
  {
    fprintf(stdout,"Enter a record number. (-1 exits): ");
    fflush(stdout);
    fgets(response,10,stdin);
    if(atoi(response)<0) break;
    fseek(myDB, atoi(response)*sizeof person, SEEK_SET);
    fprintf(stdout,"\nPosition in file before reading it: %ld\n", ftell(myDB));
    fread(&person,sizeof person,1,myDB);
    displayPerson(person);
    fprintf(stdout,"Position in file after reading it: %ld\n\n", ftell(myDB));
    
   }
  fclose(myDB);  
  return 0;
  }

