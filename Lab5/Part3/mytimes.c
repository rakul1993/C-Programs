#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <inttypes.h>
#include <sys/wait.h>
#include <sys/times.h>
#include <sys/types.h>

int main(int argc,char *argv[],char *envp[]) {
  int status, childPID;
  char *arglist[argc];
  int count;
  long clockTicksPerSecond=sysconf(_SC_CLK_TCK);
  struct timeval  wallClockTime1,wallClockTime2;
  struct tms startTime, endTime;


  for(count=1; count < argc; count++)  {
    arglist[count-1] = argv[count];
  } 
  
  arglist[argc-1] = NULL;  

  fprintf(stdout,"Ticks per second: %ld\n\n",clockTicksPerSecond);
  times(&startTime);
  gettimeofday(&wallClockTime1,NULL);

  switch(fork())  {

    //child process
    case 0:
      execv(argv[1],arglist);
      break;

    //forking error
    case -1:
      perror("Error in Fork");
      break;

    //parent process
    default:
      childPID=wait(&status);

      times(&endTime);
      gettimeofday(&wallClockTime2,NULL);

      fprintf(stdout,"\nThis is the parent %d speaking, child %d has finshed.\n\n", getpid(), childPID);

      //Present the timing info
      time_t secs=wallClockTime2.tv_sec-wallClockTime1.tv_sec;
      time_t usecs=wallClockTime2.tv_usec-wallClockTime1.tv_usec;
      if(usecs<0) //Adjust the time
      {
        usecs+=1000000;  //add a second
        secs--;          //subtract a second
      }
      fprintf(stdout,"Elapsed (real) time: %ld.%06ld seconds. \n",secs, usecs);
      fprintf(stdout,"Elapsed user process time: %8.4lf seconds. \n",(endTime.tms_utime-startTime.tms_utime)/(double) clockTicksPerSecond);
      fprintf(stdout,"Elapsed system process time: %8.4lf seconds. \n",(endTime.tms_stime-startTime.tms_stime)/(double) clockTicksPerSecond);
  }

  return 0;  
}
