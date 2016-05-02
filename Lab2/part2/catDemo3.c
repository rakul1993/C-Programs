/*
   File: catDemo3.c
   Course: CENG251
   Author: Prof. Leon King,J230,x4200
   Date: Tuesday Jan 27, 2015   12:48 PM
*/



#include <errno.h>
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#define MAXINT   200000


struct GetOptFlags  //Note that his structure is defined globally
    {
      bool version;
      bool help;
      bool numberLines;
      bool nonblankOnly;
      int  startLine;
      int  endLine;
      char * terminator;  
      char * fileName;
      FILE * outputDevice;
     };

void do_Cat(FILE *fp,struct GetOptFlags flags)
{
   char buffer[512]="";
   int lineCount=0;
   int counter2=0;

   //Flags work together.  Process all the flags in the same loop
   while(fgets(buffer,sizeof(buffer),fp))
   {
        counter2++;
        buffer[strlen(buffer)-1]='\0';
        strcat(buffer,flags.terminator); //terminator defaults to ""

        //Increment lineCount separate from the printout
        //Remember that -n and -b options were defined as mutually exclusive
        if(flags.numberLines)lineCount++;
        if(flags.nonblankOnly && buffer[0]!='\0') lineCount++;
        
       
        //skip over initial lines
        if(counter2<flags.startLine) continue;
        //Exit loop after last line
        if(counter2>flags.endLine) break;
       
        if(flags.numberLines) 
           fprintf(flags.outputDevice,"%6d  ",lineCount);
        if(flags.nonblankOnly && buffer[0]!='\0') 
           fprintf(flags.outputDevice,"%6d  ",lineCount);

        fprintf(flags.outputDevice,"%s\n",buffer);
        
       
      }

      fprintf(flags.outputDevice,"\n\n\n");  //Add spacing after the end of the file
   }





void printUsage(char * progName) //Sample "usage" message
{
    fprintf(stdout,"Correct usage of %s is: \n"
            " -v   version\n"
            " -h   help/print this message\n"
            " -n   number the output lines\n" 
	    " -s n  (start at line #n)\n"  
            " -e n  (finish at line number n)\n"
            " -b    (number nonblank lines only\n"
            " -E    (terminate each line with a $ symbol\n"
            "        or use the value of $TERMINATOR if set)\n" 
            " -d   devname  (send output to a terminal or file)\n",
	    progName);
    exit(7);  //Program exits immediately
}


int main(int argc,char * argv[])
{
    //A bundle of variables to remember the flags on the
    //command line
    struct GetOptFlags  getOptFlags = 
            {false,false,false,false, 0, MAXINT,"",NULL,stdout};
    unsigned int flag,indexVal;

    char * shortOptions="vhnEbs:e:d:"; //Note - none of these has parameters
  
        //process options
    while( (flag=getopt(argc,argv,shortOptions))!=-1)
	{
	    switch(flag)
	    {
		case 'v':  getOptFlags.version=true;
			   break;

		case 'h':  getOptFlags.help=true;
			   break;


		case 'E': if(getenv("TERMINATOR"))
                                getOptFlags.terminator=getenv("TERMINATOR");
                           else getOptFlags.terminator="$";
                           break;
  
                case 'n': getOptFlags.numberLines=true;
                          getOptFlags.nonblankOnly=false;
                          break;

                case 'b': getOptFlags.numberLines=false;
                          getOptFlags.nonblankOnly=true;
                          break;

                //start line
                case 's': getOptFlags.startLine=atoi(optarg);
                          break;

                //end line
		case 'e': getOptFlags.endLine=atoi(optarg); 
                          break;

                //device output - defaults to stdout
                case 'd': getOptFlags.outputDevice=fopen(optarg,"w");
                          getOptFlags.fileName=strdup(optarg);
                          
                          break;
                  }
         }

       //Verify the options
      fprintf(stdout, "version set to:\t %s\n", getOptFlags.version ? "on" : "off");
      fprintf(stdout, "help set to:\t %s\n", getOptFlags.help ? "on" : "off");
      fprintf(stdout, "-n set to:\t %s\n", getOptFlags.numberLines? "on" : "off");
      fprintf(stdout, "-b set to:\t %s\n",  getOptFlags.nonblankOnly ? "on" : "off");
      fprintf(stdout, "-s set to:\t %d\n", getOptFlags.startLine);
      fprintf(stdout, "-e set to:\t %d\n", getOptFlags.endLine);
      fprintf(stdout, "-E (terminator) set to: %s\n", strlen(getOptFlags.terminator) ? getOptFlags.terminator : "(none)");
      fprintf(stdout, "-d set to: %s\n", getOptFlags.outputDevice==stdout ?
                           "stdout"  : getOptFlags.fileName);;

               
  //The help and version options run once and then quit the program
  if(getOptFlags.help) {printUsage(argv[0]);exit(0);}
  if(getOptFlags.version) { fprintf(stdout,"This is version .9\n");exit(0);}


  

  if(optind==argc) {
             fprintf(getOptFlags.outputDevice,"Processing stdin\n");
             do_Cat(stdin,getOptFlags);  //No args - read from terminal
            }
  else while(argv[optind]) //Process each of the files
      {
        FILE *infile;
        fprintf(getOptFlags.outputDevice,"Processing file: %s\n\n",argv[optind]);
        infile=fopen(argv[optind],"r");
        if(infile) {
             do_Cat(infile,getOptFlags);
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
