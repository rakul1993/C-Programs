/*
   File:
   Purpose:    
   Course: CENG251
   Author: 
   Date: 
    
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>
#include <locale.h>
#include <langinfo.h>
#include <stdint.h>
#include <string.h>
#include <memory.h>

int main(int argc, char * argv[],char * envp[])
{

  struct passwd *pwdRec;
  FILE * password;
  char line[1024];
  char uidBuffer[50];
  char * passwdBuffer;
  char * fieldSplitter = ":";
  //int count =0;
  setpwent(); 

  while(pwdRec=getpwent())  {
    //count++;
    password = fopen("passwdFile","r");

    passwdBuffer = pwdRec->pw_passwd; //obtain record passwn and store in passwdBuffer
    sprintf(uidBuffer, "%d", pwdRec->pw_uid); //obtain uid and store in uidBuffer as a string

    //use string concatenate to join the password and uid seprated by colons
    char * str3 = (char *) malloc(1 + strlen(passwdBuffer) + strlen(fieldSplitter) + strlen(uidBuffer) + strlen(fieldSplitter));
    strcpy(str3,passwdBuffer);
    strcat(str3,fieldSplitter);
    strcat(str3,uidBuffer);
    strcat(str3,fieldSplitter);
    //fprintf(stdout,"%s",str3);
    
    //search through my passwd file and look for matches from /etc/passwd
    while(fgets(line, sizeof(line),password )) {
      if (strstr(line, str3) != NULL) {
        fprintf(stdout,"Found %s in your password file.\n", pwdRec->pw_gecos);   // if line contains the text, print it
      }
    }

    fclose(password);
    }

  endpwent(); 

  //fprintf(stdout,"\n\nSearched for %d records", count);
  return 0;

}

