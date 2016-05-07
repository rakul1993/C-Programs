/*
  Program: dAte.c
  Name: Rakul Mahenthiran
  Date: Apr 22, 2015
  Pupose: This program replicates some of the functions
          of the unix command date 
*/
#include <string.h>   
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>  
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <utmp.h>

int main(int argc,char * argv[])  {

  struct GetOptFlags  {
    char * dateString;
    char * dateFile;
    char * dateUsr;
    char * dateFormat;    
  }

  getoptFlags = {0,0,0,0};

  //flags and long options
  char * shortOptions="d:f:m:u:"; 
  struct option  options[]=  {  
    {"date", 1, NULL, 'd'}, 
    {"file", 1, NULL, 'f'}, 
    {"fmt", 1, NULL, 'm'},
    {"username", 1, NULL, 'u'},
    {NULL,0,NULL,'\0'}};

  //Use these variables to record the command line options
  int flag;
  int indexVal;
  int i,last=1;

  //Time variables
  time_t now;
  struct tm ts;
  char buf[80];

  //EPOCH current time
  time(&now);
  ts = *localtime(&now);  

  while( (flag=getopt_long(argc,argv,shortOptions,options,&indexVal))!=-1)  {
    last=optind;
    switch(flag)  {
      case 'd':
        getoptFlags.dateString = optarg;  
	break;

      case 'f':  
	getoptFlags.dateFile = optarg;
	break;

      case 'm':  
	getoptFlags.dateFormat = optarg;
	break;

      case 'u': 
	getoptFlags.dateUsr=optarg;
	break;
    }
  }


  //Default Behaviour
  if(argc == 1) {
    strftime(buf, sizeof(buf), "%a %b %d %H:%M:%S %Z %Y", &ts);
    printf("%s\n", buf); 
  }

  //Specify date format
  if(getoptFlags.dateFormat)  {
    strftime(buf, sizeof(buf), getoptFlags.dateFormat, &ts);
    printf("%s\n", buf);
  }

  //Convert string to date  
  if(getoptFlags.dateString)  {

    struct tm broken;
    time_t t;
    strptime(getoptFlags.dateString,"%b %d, %Y  %H:%M:%S", &broken);
    t = mktime(&broken);  
    fprintf(stdout,"Epoch time: %ld \n", t);
    fprintf(stdout,"Back to a string: %s \n", ctime(&t));
  }

  //File dates
  if(getoptFlags.dateFile)  {

    FILE *f1 = fopen(getoptFlags.dateFile, "r");
    char str[128];
    struct tm broken2;
    time_t t2;
    while(fgets(str,sizeof(str), f1)) {
      fprintf(stdout,"%s",str);
      strptime(str,"%b %d, %Y  %H:%M:%S", &broken2);
      t2 = mktime(&broken2);   
      fprintf(stdout,"Epoch time: %ld \n", t2);
      fprintf(stdout,"Back to a string: %s \n\n", ctime(&t2));
    }     
  }

  //User login dates
  if(getoptFlags.dateUsr)  {

    struct utmp * current_record;
    int utmpfd;  /* File Descriptor */
    int	reclen = sizeof current_record;
    int recordCount=0;
 
    utmpname(WTMP_FILE); /* UTMP_FILE is default valuei */
    setutent(); /*Opens the utmp file */
    
    /* loop thru the utmp file and read each record */
    while(current_record=getutent())  {
      recordCount++;
      if(strcmp(current_record->ut_name,getoptFlags.dateUsr) == 0)  {
        char *timeValue;
        if(current_record->ut_type==USER_PROCESS)  {
          fprintf(stdout,"%-10.10s ",current_record->ut_name); /* User Name */
          timeValue=ctime(&current_record->ut_time);
          timeValue[strlen(timeValue)-1]='\0'; //remove the newline
          fprintf(stdout,"%s  ",timeValue); /* login time */
          fprintf(stdout,"\n");
        }
      }
    }
    endutent();
  }

   
  return 0;
}


