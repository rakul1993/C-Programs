/*
   File: displayDirDemo.c
   Course: CTEC102
   Date: Sunday March 18, 2007
   */
 
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>


int main(int argc, char * argv[])
{
  DIR * dirp;
  struct dirent *dirent;
  struct stat info;
  chdir(argv[1]);
  dirp=opendir("."); 
  while(dirent=readdir(dirp))
  {
    fprintf(stdout,"fileName:  %s  inode#: %u\n",
             dirent->d_name,(unsigned int)dirent->d_ino);
    stat(dirent->d_name,&info);
   }
  closedir(dirp);
  return 0;
  }

