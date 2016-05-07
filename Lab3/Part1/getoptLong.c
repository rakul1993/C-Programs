
//Author: Rakul Mahenthiran
//Date: Feb 21, 2015
/* Description:

  
*/

#include <string.h>   
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>  //Added in C99


//These are declared for us in getopt.h - we don't have to declare them
extern char * optarg;   //string.  Argument of the flag
extern int optind;      //index in argv[] of the next entry to parse
extern int optopt;      //If getopt returns '?' (invalid option) or ':'
extern int opterr;
//(missing argument) then optopt is the flag


int main(int argc,char * argv[])
{
    //A bundle of variables to remember the flags on the
    //command line
    struct GetOptFlags
    {
	int afterContext;
	int beforeContext;
	bool count;
	bool ignoreCase;
	bool invertMatch;
    }
   
    getoptFlags = {0,0,false,false,false};

    char * shortOptions="A:B:civ"; 
    struct option  options[]= { //{flag,has_arg,ignore,returnCode} 
	{"after-context", 1, NULL, 'A'}, 
	{"before-context", 1, NULL, 'B'}, 
	{"count",0,NULL,'c'},
	{"ignore-case",0,NULL,'i'},
	{"invert-match",0,NULL,'v'},
	{NULL,0,NULL,'\0' }};

    //Use these variables to record the command line options
    int flag;
    int indexVal;
    int i,last=1;




    while( (flag=getopt_long(argc,argv,shortOptions,options,&indexVal))!=-1)
    {
	last=optind;
	switch(flag)
	{
	    case 'A':  
		getoptFlags.afterContext=atoi(optarg);
		break;

	    case 'B':  
		getoptFlags.beforeContext=atoi(optarg);
		break;

	    case 'c':  
		getoptFlags.count=true;
		break;

	    case 'i': 
		getoptFlags.ignoreCase=true;
		break;

            case 'v': 
		getoptFlags.invertMatch=true;
		break;


	    case '?':  fprintf(stderr,"CENG251: Invalid Flag: %c\n", optopt);
		       break;

	    case ':':   fprintf(stderr,"CENG251: Missing command line argument for flag %c\n",optopt);
			break;

	}
    }

     //Verification - necessary for testing the getopt loop
     fprintf(stdout,"The flag -A is set to: %d\n", getoptFlags.afterContext);     
     fprintf(stdout,"The flag -B is set to: %d\n", getoptFlags.beforeContext);

     fprintf(stdout,"The flag -c is set to: %s\n", getoptFlags.count ? "true" : "false");
     fprintf(stdout,"The flag -i is set to: %s\n", getoptFlags.ignoreCase ? "true" : "false");
     fprintf(stdout,"The flag -v is set to: %s\n", getoptFlags.invertMatch ? "true" : "false");


    //Display the remaining command line arguments
    //Always start at position optind.  getopt and getopt_long
    //  rearrange the order of the command line so that the flags
    //  and their arguments are moved to the beginning, and the remaining
    //  arguments are moved to the end.
    fprintf(stdout,"\n\nThe remaining command line args are: \n");
    for(i=optind;i<argc;i++)
	fprintf(stdout,"argv[%d] is %s\n",i,argv[i]);

   
    return 0;
}

