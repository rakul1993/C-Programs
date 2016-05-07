/*
   File: timeDemo2.c
   Course: CENG411
   Author: Leon King,J230,x4200
   Date: Friday Mar 14, 2012   01:44 PM 
   Purpose:  Convert strings to time_t values

             struct tm is known as "broken down time" - it has separate fields
                    for year, month, day, hours, minutes, seconds
             strptime converts a string to to a struct tm
             mktime converts a struct tm to time_t

             There is no built in function to do it directly.

*/


#include <stdio.h>
#define _XOPEN_SOURCE
#include <time.h>
#include <stdlib.h>
int main(int argc, char * argv[],char * envp[])
{
  //When was Unix born:  Jan 1, 1970
  time_t  when;
  struct  tm  brokenDownTime; 

  char dateFormat[] = "%b %d, %Y  %H:%M:%S";
  //char eventString[]="March 12, 2002 14:22:17";
  char eventString[]="January 1, 1970 00:00:07";
  //In the assignment assume that all times are in a fixed format
  strptime(eventString,dateFormat,&brokenDownTime); 

  when=mktime(&brokenDownTime);
  fprintf(stdout,"The time in seconds since Jan 1, 1970: %ld\n",when);
  fprintf(stdout,"Converted back to a string: %s",ctime(&when));
  return 0;
  }
