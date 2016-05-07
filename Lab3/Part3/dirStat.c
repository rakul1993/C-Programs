/*
   File: dirStat.c
   Course: CENG251
   Author: Rakul Mahenthiran
   Date: Feb 26, 2015
*/
 
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <locale.h>
#include <langinfo.h>
#include <stdint.h>


int main(int argc, char * argv[])
{
  DIR * dirp;
  struct dirent *dirent;
  struct stat info;
  struct passwd  *pwd;
  struct group   *grp;

  chdir(argv[1]);
  dirp=opendir("."); 
  while(dirent=readdir(dirp))
  {
    fprintf(stdout,"File Name: %s   \t",dirent->d_name);
    stat(dirent->d_name,&info);

    if ((grp = getgrgid(info.st_gid)) != NULL)
      fprintf(stdout,"Group: %s   \t", grp->gr_name);
    
    if ((pwd = getpwuid(info.st_uid)) != NULL)
      fprintf(stdout,"Owner: %s\t   \n", pwd->pw_name);
    

   }
  closedir(dirp);
  return 0;
  }

