/*************************
* File: qestion3c.c
* Purpose: Use SIGHUP to reinitialize a program.  
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
 
  DIR * dirp;
  struct dirent *dirent;
  char str[100];
  char buffer[1000];
  char stream[100];
  char *rwa;
  char *dirLine;
  FILE *file1;
  FILE *file2;

  file1 = fopen("fileList.txt", "r");


  while((fgets(stream, 100, file1)) != NULL) {
    dirLine = strtok(stream, " ");
    rwa = strtok(NULL, " ");

    file2 = fopen(dirLine, rwa);
  }

  sprintf(str, "/proc/%i/fd", getpid());
  chdir(str);
  dirp = opendir(".");

  while(dirent = readdir(dirp)) {
  //Reading the contents of the link in the buffer
    readlink(dirent->d_name, buffer, sizeof(buffer));
    fprintf(stdout, "%s\n", buffer);
  }
}

//main program
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
