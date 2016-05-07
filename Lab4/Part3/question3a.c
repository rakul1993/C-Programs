/******************
 * File: qestion3a.c
 * Purpose: a signal handler for SIGUSR1 what uses popen to run a
 *          shell command that determines the number of processes  
 *          on the system.  Print that value out to the terminal.  
 * Course: CENG 251
 * Author: Rakul Mahenthiran
 * Date: March 22, 2015
********************/
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>

 void signalHandler (int sigNUM) {
   char * prompt = "ps | wc - l";
   char processBuffer[100];
   FILE *proc;
   time_t time=0L;


   if((proc = popen(prompt, "r")) != NULL) {

     while(fgets(processBuffer, 100, proc) != NULL)
       fprintf(stdout, "Number of Processes is: %s", processBuffer);
     pclose(proc);
   }

   // write date and number of proccess to log file.
   FILE *myLogs = fopen("myLog.log", "a");
   fprintf(myLlogs, "Time: %sProcess Id: %s\n\n", ctime(&time), processBuffer);
   fclose(myLogs);
}

 // main program
 int main(int argc, char * argv[], char envp[]) {
   void signalHandler(int); 
   int count;

   fprintf(stdout, "Current Process id: %d\n", getpid());
   fprintf(stdout, "Parent Process id: %d\n", getppid());


   signal(SIGUSR1, signalHandler);

   //Handler Loop for interrupts
   for (count = 0; count < 5; count++) {
     fprintf(stdout, "ID: %d\n", count);
     sleep(6);
   }
 }


