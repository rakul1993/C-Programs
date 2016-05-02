/*
   File: octalDump.c
   Course: CENG251
   Author: Rakul Mahenthiran
   Date: Tuesday Feb 10, 2015  
*/



#include <errno.h>
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>


struct GetOptFlags  //structure is defined globally
    {
      bool asciiFormat;
      bool decimalFormat;
      bool octalFormat;
      bool hexFormat;
      int  addressRadix;
      int  skipBytes;  
      char * fileName;
      FILE * outputDevice;
     };

void do_Od(FILE *fp,struct GetOptFlags flags)
{

   char buffer[512]="";
   int lineCount=0;
   int counter2=0;

   (fseek(fp,flags.skipBytes,SEEK_SET));//skips specified number of bytes
 

   //Flags work together.  Process all the flags in the same loop
   while(fgets(buffer,sizeof(buffer),fp))
   {	

	 fprintf(flags.outputDevice,"%s\n",buffer);
                
      }
   
   fprintf(flags.outputDevice,"\n\n\n");  //Add spacing after the end of the file   
 }

int main(int argc,char * argv[])
{
    //A bundle of variables to remember the flags on the
    //command line
    struct GetOptFlags  getOptFlags = 
            {true,false,false,false, 8, 0,NULL,stdout};
    
    unsigned int flag,indexVal;

    char * shortOptions="cdoxA:j:"; //Note - none of these has parameters
  
        //process options
    while( (flag=getopt(argc,argv,shortOptions))!=-1)
	{
	    switch(flag)
	    {
		case 'c':  getOptFlags.asciiFormat=true;
			   break;

		case 'd':  getOptFlags.decimalFormat=true;
			   break;

		case 'o':  getOptFlags.octalFormat=true;
                           break;
  
                case 'x':  getOptFlags.hexFormat=true;
                           break;

                case 'A':  getOptFlags.addressRadix=atoi(optarg);
                           break;

                case 'j':  getOptFlags.skipBytes=atoi(optarg);
                           break;
                  }
         }

       //Verify the options
      fprintf(stdout, "-c set to:\t %s\n", getOptFlags.asciiFormat ? "on" : "off");
      fprintf(stdout, "-d set to:\t %s\n", getOptFlags.decimalFormat ? "on" : "off");
      fprintf(stdout, "-o set to:\t %s\n", getOptFlags.octalFormat? "on" : "off");
      fprintf(stdout, "-x set to:\t %s\n",  getOptFlags.hexFormat ? "on" : "off");
      fprintf(stdout, "-A set to:\t %d\n", getOptFlags.addressRadix);
      fprintf(stdout, "-j set to:\t %d\n", getOptFlags.skipBytes);

                 
  if(optind==argc) {
             fprintf(getOptFlags.outputDevice,"Processing stdin\n");
             do_Od(stdin,getOptFlags);  //No args - read from terminal
            }
  else while(argv[optind]) //Process each of the files
      {
        FILE *infile;
        fprintf(getOptFlags.outputDevice,"Processing file: %s\n\n",argv[optind]);
        infile=fopen(argv[optind],"r");
        if(infile) {
             do_Od(infile,getOptFlags);
             fclose(infile);
              }
          else {
                fprintf(stderr,"Error code: %d ",errno);
                perror("Oops ");
                }
        optind++;
       }

  return 0;
  }

