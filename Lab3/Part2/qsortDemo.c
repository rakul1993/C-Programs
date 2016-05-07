/*
File: qsortDemo.c Course: CENG251
Author: Rakul Mahenthiran
Date: Feb 26, 2015

Based on the employee sorting demo in Robbins, Example 6.2.1.1 
with a few extra tricks
This example uses the PERSON data structure used in createPerson.c and findPerson.c
 */
#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

#include "person.h"
#include "ansi.h"

#define prompt(string)  fprintf(stdout,string),fflush(stdout) 

struct  {   
    char * rank;
    int  level; 
} rankTable[]={{"Captain",1},{"Science Officer",2},
               {"Engineer",3}, 
               {"Medical Officer",3},{"Navigator",4},
               {"Transporter Chief",5},{"Morale Officer",6},
               {"Crew",7},{"Ensign",8}, {"Red Shirt",9}};

int lookupRank(char *rank)
{
  int i;
  for(i=0;i<(sizeof rankTable)/(sizeof rankTable[0]);i++)
     if(strcmp(rank,rankTable[i].rank)==0)
             return rankTable[i].level;

  return i;
  }
   
//Compare 2 people by rank
int sortByRank(const void * record1, const void * record2)
{
    //Cast record 1 and record2 to PERSON to unclutter later code
        goto(0,0);
    struct PERSON *person1=(struct PERSON *) record1,
		  *person2=(struct PERSON *) record2;

    return lookupRank(person1->position)-lookupRank(person2->position);
  }

//Compare 2 people by name
int sortByName(const void * record1, const void * record2)
{
    //Cast record 1 and record2 to PERSON to unclutter later code
    struct PERSON *person1=(struct PERSON *) record1,
		  *person2=(struct PERSON *) record2;
    int result;

    return (result=strcmp(person1->lastName,person2->lastName)) 
	? result : strcmp(person1->firstName,person2->firstName);
}

//Compare 2 people by age
int sortByAge(const void * record1, const void * record2)
{
    struct PERSON *person1=(struct PERSON *) record1,
		  *person2=(struct PERSON *) record2;
    return person1->age-person2->age;
}

int main(int argc, char * argv[],char * envp[])
{
    int personDB=open("myDB",O_CREAT | O_RDONLY,0600);
    struct stat fileInfo;
    bool   dirtyFlag=false;
    char   response[10];
    int    nRecs,i;
    struct PERSON *baseAddress;
    if(!personDB) {  perror("missing myDB database file"); exit(1); }
    //Determine the number of records in the file - version 1
    fprintf(stdout,"There are %d records in myDB\n",lseek(personDB,0,SEEK_END)/(sizeof(struct PERSON))); 
    lseek(personDB,0,SEEK_SET);  //reset the file pointer to the beginning of the file

    //2nd method of determining # of records
    fstat("myDB",&fileInfo); 
    fprintf(stdout,"There are %d records in myDB\n",nRecs=(fileInfo.st_size/(sizeof (struct PERSON)))); 

    struct PERSON fileInMemory[nRecs];
    read(fileInMemory,sizeof(struct PERSON),personDB);  //Load the personDB into memory
    close(personDB);

    while(true)
    {
	prompt(CLEARSCREEN); goto(0,0);
	fprintf(stdout,"1. Sort by name\n");
	fprintf(stdout,"2. Sort by age\n");
	fprintf(stdout,"3. Sort by rank\n");
	fprintf(stdout,"4. Display records\n");
	fprintf(stdout,"5. Save to file\n");
	fprintf(stdout,"6. Quit\n\n\n");
	prompt("Select an action: ");

	fgets(response,sizeof response,stdin);
	__fpurge(stdin);  //Use this for clearing an input buffer 


	switch(atoi(response))
	{
	    case 1: qsort(fileInMemory,nRecs,sizeof (struct PERSON),sortByName);
	            dirtyFlag=true;
		break;

	    case 2: qsort(fileInMemory,nRecs,sizeof (struct PERSON),sortByAge);
                    dirtyFlag=true;
		    break;

	    case 3:  qsort(fileInMemory,nRecs,sizeof (struct PERSON),sortByRank);
		    break;

	    case 4: //Display the records in memory
		    for(i=0; i<nRecs;i++)
			displayPerson(fileInMemory[i]);
                    prompt("Press return to continue");
                    fgets(response,sizeof response,stdin);
                    __fpurge(stdin);
		    break;
	    case 5:
		    if(dirtyFlag) {
			personDB=open("myDB",O_CREAT | O_WRONLY,0600);
			write(fileInMemory,sizeof fileInMemory,personDB);
		        dirtyFlag=false;
		    } 

		    break;
	    case 6:  if(dirtyFlag)  //exiting the program
		     { 
			 prompt("File has changed - proceed or cancel (P/C)");
			 fgets(response,sizeof response,stdin);
			 __fpurge(stdin);
                         if(toupper(response[0])=='P') exit(0);
		     }
	} //end of switch

     }  //end of while
    return 0;
}

