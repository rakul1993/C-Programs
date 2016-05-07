/*
   File:
   Purpose:    
   Course: CENG251
   Author: 
   Date: 
    
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
  FILE * password=fopen("anotherPasswordFile","a");


  grp = getgrnam(groupName);
  
  printf("%d\n", grp->gr_gid);

  setpwent(); 
   while(pwdRec=getpwent())
      {
        if(pwdRec->pw_gid == grp->gr_gid)
         putpwent(pwdRec,password);
      }
  endpwent(); 

return 0;

}

