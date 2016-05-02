/*
   File: octalDump.c
   Course: CENG251
   Author: Rakul Mahenthiran
   Date: Tuesday Feb 10, 2015  
   
*/


#include <stdio.h>
#include <getopt.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

struct FLAGS
   {
      bool asciiFormat;
      bool decimalFormat;
      bool octalFormat;
      bool hexFormat;
      int addressRadix;
      int skipBytes;	 
   };


int main(int argc, char * argv[],char * envp[])
{
  struct FLAGS flags={true, false, false, false, 8, 0};//set defaults

  int flag;
  long double result;

  while((flag=getopt(argc,argv,"cdoxA:j:"))!=-1)
  {
     fprintf(stdout,"Processing cmd line arg #%d with flag %c.\n",
                    optind-1,flag); 
     switch(flag)
     {
       case 'c':
            flags.asciiFormat=true;
            break;
       case 'd':
            flags.decimalFormat=true;
            break;
       case 'o':
            flags.octalFormat=true;
            break;
       case 'x':
            flags.hexFormat=true;
            break;
       case 'A':
	    flags.addressRadix=atoi(optarg);
	    break;
       case 'j':
            flags.skipBytes=atoi(optarg);
            break;
       default:
            perror("Ooops! Bad flag or missing argument");
            fprintf(stderr,"flag: %c  opterr: %d optopt %c\n",
                         flag, opterr, optopt);
       }
  }

    //Verification - necessary for testing the getopt loop
     fprintf(stdout,"The flag -c is set to: %s\n", flags.asciiFormat ? "true" : "false");     
     fprintf(stdout,"The flag -d is set to: %s\n", flags.decimalFormat ? "true" : "false");
     fprintf(stdout,"The flag -o is set to: %s\n", flags.octalFormat ? "true" : "false");
     fprintf(stdout,"The flag -x is set to: %s\n", flags.hexFormat ? "true" : "false");
     fprintf(stdout,"The flag -A is set to: %d\n", flags.addressRadix);
     fprintf(stdout,"The flag -j is set to: %d\n", flags.skipBytes);

  //Print out the remaining values
  int i;
  for(i=optind; i<argc; i++)
    fprintf(stdout,"%d. %s\n", i, argv[i]); 

  return 0;
}

