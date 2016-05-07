/*
   File: simpleGetOpt.c
   Course: CENG251
   Author: Rakul Mahenthiran
   Date: Tuesday Jan 13, 2015  
   
   A program that takes a series of numbers and flags.
   
   The purpose of the after-context flag is to print NUM lines of 
   trailing context after matching lines.
   
   The purpose of the before-context flag is to print NUM lines of
   leading context before matching lines.
   
   The purpose of the count flag is to print a count of matching lines 
   for each input file.
   
   The purpose of the ignore-case flag is to Ignore case distinctions
   in both the PATTERN and the input files.
   
   The purpose of the invert-match flag is toInvert the sense of 
   matching, to select non-matching lines.
 
   All the options have a default.  The entire command line has to
   be processed first and the options collected before they can be 
   acted on.
*/


#include <stdio.h>
#include <getopt.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

struct FLAGS
   {
      int afterContext;
      int beforeContext;
      bool count;
      bool ignoreCase;
      bool invertMatch;		 
   };


int main(int argc, char * argv[],char * envp[])
{
  struct FLAGS flags={0,0,false,false,false};//set defaults

  int flag;
  long double result;

  while((flag=getopt(argc,argv,"A:B:civ"))!=-1)
  {
     fprintf(stdout,"Processing cmd line arg #%d with flag %c.\n",
                    optind-1,flag); 
     switch(flag)
     {
       case 'A':
            flags.afterContext=atoi(optarg);
            break;
       case 'B':
            flags.beforeContext=atoi(optarg);
            break;
       case 'c':
            flags.count=true;
            break;
       case 'i':
            flags.ignoreCase=true;
            break;
       case 'v':
	    flags.invertMatch=true;
	    break;
       default:
            perror("Ooops! Bad flag or missing argument");
            fprintf(stderr,"flag: %c  opterr: %d optopt %c\n",
                         flag, opterr, optopt);
       }
  }

    //Verification - necessary for testing the getopt loop
     fprintf(stdout,"The flag -A is set to: %d\n", flags.afterContext);     
     fprintf(stdout,"The flag -B is set to: %d\n", flags.beforeContext);

     fprintf(stdout,"The flag -c is set to: %s\n", flags.count ? "true" : "false");
     fprintf(stdout,"The flag -i is set to: %s\n", flags.ignoreCase ? "true" : "false");
     fprintf(stdout,"The flag -v is set to: %s\n", flags.invertMatch ? "true" : "false");

  //Print out the remaining values
  int i;
  for(i=optind; i<argc; i++)
    fprintf(stdout,"%d. %s\n", i, argv[i]); 

  return 0;
}


