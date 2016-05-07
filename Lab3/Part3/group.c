/* File:  group.c
   Descriptions:   Prints out a list of groups 
                   and their members */

#include <stdio.h>
#include <grp.h>
int main(int argc, char * argv[ ])
{  int i;
   struct group *groupRec;
   //See also:  getgrnam
   //           getgrid

   setgrent(); //Open the file /etc/group
   while(groupRec=(struct group *) getgrent())
      {
        fprintf(stdout,"Group Name: %s\t",groupRec->gr_name);
        fprintf(stdout,"GID: %d\n",groupRec->gr_gid);
	//List everyone in the group
	for(i=0; groupRec->gr_mem[i]; i++)
           fprintf(stdout,"   member: %s\n",groupRec->gr_mem[i]);
	fprintf(stdout,"\n\n"); 
        }
   endgrent();
  }
