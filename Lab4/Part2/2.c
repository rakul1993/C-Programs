/*
   File: 2.c
   Purpose: This program enables users to enter a group name and a string to use as salt. 
            Then the program extract all the password records for the memebers of that 
            group; encryps the GECOS field and stores the rcords in a file.   
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
#include <grp.h>
#include <locale.h>
#include <langinfo.h>
#include <stdint.h>


int main(int argc, char * argv[],char * envp[])
{

  struct passwd *pwdRec;
  struct group *grp;
  char * groupName = argv[1];
  FILE * password=fopen("passwdFile","a");

  grp = getgrnam(groupName); 	//gets command line group name

  setpwent(); 	//begining of passsword database
   while(pwdRec=getpwent())	//loop through every record in passwd
      {
        if(pwdRec->pw_gid == grp->gr_gid){ 	//check if record groupID and entered groupID match
         pwdRec->pw_gecos = crypt(pwdRec->pw_gecos,argv[2]); 	//crypt GECOS field
         putpwent(pwdRec,password); 	//write in file
        }
      }
  endpwent();	//close password database

  fclose(password); 

return 0;

}
