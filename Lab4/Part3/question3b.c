/************************
* File: equestion3b.c
* Purpose: Open two files at the beginning of the program.
*          When you send the program SIGINT (<ctrl>c)  have
*          it display the real names of all the open files 
*          in the directory /proc/pid/fd using readdir.   
* Course: CENG251
* Author: Rakul Mahenthiran
* Date: March 26, 2015
*************************/
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>


void signalHandler(int signum) {
   char *file1;
   char *file2;
   DIR * curdir;
   struct dirent *dirent;

   char str[100];
   sprintf(str, "/proc/%i/fd", getpid());
   chdir(str);
   curdir = opendir("."); 
   char buffer[1000];

   while(dirent = readdir(curdir)) {
     readlink(dirent->d_name, buffer, sizeof(buffer));
     fprintf(stdout, "%s\n", buffer);
   }
}

int main (int argc, char * argv[], char envp[]) {
  void signalHandler(int);
  int count;

  //Declaring Files being used
  FILE *file1 = fopen("firstFile.txt", "w");
  FILE *file2 = fopen("secondFile.txt", "w");

  fprintf(stdout, "Current Process id: %d\n", getpid());
  fprintf(stdout, "Parent Process id: %d\n", getppid());

  signal(SIGINT, signalHandler);

  //Handler Loop for interrupts
  for (count = 0; count < 5; count++) {
    fprintf(stdout, "ID: %d\n", count);
    sleep(6);
  }

  fclose(file1);
  fclose(file2);
  return 0;
}


