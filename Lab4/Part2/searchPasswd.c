/*
   Name: searchPasswd.c
   Purpose: search and identify a user and thier password, and reject bad combinations   
   Course: CENG251
   Author: Rakul Mahenthiran
   Date: Mar 23, 2015
    
*/


#include <stdio.h>
#include <crypt.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>
#include <grp.h>
#include <locale.h>
#include <langinfo.h>
#include <stdint.h>
#include <string.h>


int main(int argc, char * argv[],char * envp[])
{

  struct passwd *pwdRec;
  char userPasswd[100];
  uid_t userid;

  fprintf(stdout,"\nEnter user id: ");
  scanf(" %d", &userid);
  fprintf(stdout,"Enter Full Name: ");  
  scanf(" %[^\n]%*c", userPasswd);

  pwdRec=getpwuid(userid); 
  if(strcmp(pwdRec->pw_gecos,userPasswd) == 0)
    fprintf(stdout,"\n\tSuccessfully identified: \n\t\t UserID \t%d\n\t\t Password: \t%s\n", userid, userPasswd);

  else
    fprintf(stdout,"\n\tInvalid user ID/password.\n");

  return 0;

}


