
/*
   File: octalDump.c
   Course: CENG411
   Date: Sunday Feb 22, 2015   10:25 AM
*/
 
#include <stdio.h>
#include <getopt.h>
#include <stdbool.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct FLAGS 
   {
      bool hex;
      bool octal;
      bool decimal;
      bool character;
      int  skipBytes;
      char *radixFormat;
     };


void do_Octal(FILE * fp,struct FLAGS myFlags)
{
  char buffer[16];
  int currentOffset=myFlags.skipBytes;
  int nChars;
  int i;

  //Skip bytes - the slow way
  int counter;
  for(counter=myFlags.skipBytes;counter;counter--)fgetc(fp);
  fprintf(stdout,"Verifying position in file: %ld\n",ftell(fp));

  //Skip bytes - the fast way
  fseek(fp,myFlags.skipBytes,SEEK_SET);

  fprintf(stdout,"Verifying position in file again: %ld\n",ftell(fp));

  while(nChars=fread(buffer,1,sizeof buffer,fp))
  {
    fprintf(stdout,myFlags.radixFormat,currentOffset);

    if(myFlags.hex){
       for(i=0;i<nChars; i++)
             fprintf(stdout," %02x ",buffer[i]);
       fprintf(stdout,"\n        ");  //newline + next indent
       }

    if(myFlags.octal) {
       for(i=0;i<nChars; i++) 
	   fprintf(stdout," %03o",buffer[i]);
       fprintf(stdout,"\n        ");  //newline + next indent
       }

    if(myFlags.decimal) {
       for(i=0;i<nChars; i++) 
	   fprintf(stdout," %03u",buffer[i]);
       fprintf(stdout,"\n        ");  //newline + next indent
    }

    //Print out as characters with substitutions for
    //unprintable characters.  Code taken from mallocDemo.c 
    if(myFlags.character){ 
	for(i=0;i<nChars;i++)
	{
	    if(isprint(buffer[i])) fprintf(stdout,"%4c",buffer[i]);
	    else if(buffer[i]=='\0')   fprintf(stdout,"  \\0");
	    else if(buffer[i]=='\n')   fprintf(stdout,"  \\n");
	    else fprintf(stdout," . ");
	}

	fprintf(stdout,"\n"); //Final newline
    }
    currentOffset+=sizeof buffer;
    fprintf(stdout,"\n");
  } //end of while loop
}
int main(int argc, char * argv[],char * envp[])
{
    char * shortOpts="ocdxj:A:";
    struct FLAGS myFlags = {false,false,false,false,0,"%06o   "} ;
    FILE * infile;
    int  index;
    int  flag;

    //Process the options
    while((flag=getopt(argc,argv,shortOpts))!=-1)
    {
	switch(flag)
	{
	    case 'o':
		myFlags.octal=true;
		break;
            case 'd':
                myFlags.decimal=true;
	    case 'x':
		myFlags.hex=true;
		break;
	    case 'c':
		myFlags.character=true;
		break;
	    case 'j':
		myFlags.skipBytes=atoi(optarg);
            case 'A':
                if(strcmp(optarg,"o")==0) myFlags.radixFormat="%06o   ";
                if(strcmp(optarg,"d")==0) myFlags.radixFormat="%06d   ";
                if(strcmp(optarg,"x")==0) myFlags.radixFormat="%06x   ";
		break;

	}
    }

    //Make sure that if no options are set, hex is the default
    if(!myFlags.octal && !myFlags.hex && !myFlags.character)
	myFlags.hex=true;

    //Verifiying the setting of the flags
    fprintf(stdout,"Hex flag setting: %c\n",
	    myFlags.hex ? 'T' : 'F');
    fprintf(stdout,"Character flag setting: %c\n",
	    myFlags.character ? 'T' : 'F');
    fprintf(stdout,"Octal flag setting: %c\n",
	    myFlags.octal ? 'T' : 'F') ;
    fprintf(stdout,"Decimal flag setting: %c\n",
	    myFlags.decimal ? 'T' : 'F') ;

    fprintf(stdout,"Skip bytes setting: %d\n",myFlags.skipBytes);
    fprintf(stdout,"Radix format: %s\n",myFlags.radixFormat);


    while(optind<argc)
    {
	infile=fopen(argv[optind],"r");
	if(infile) {
	    do_Octal(infile,myFlags);
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
