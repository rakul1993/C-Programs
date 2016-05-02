#include <stdio.h>
int main(int argc, char * argv[],char * envp[])
{
  FILE * fp=fopen("freadDemo.c","r");
  char  buffer[100];
  int  n;

  fprintf(stdout,"First test of fread:\n");
  n=fread(buffer,sizeof buffer,1,fp);
  fprintf(stdout,"%d items read in\n",n);

  fprintf(stdout,"2nd test of fread:\n");
  fseek(fp,0,SEEK_SET); //reset the file pointer to the beginning  
  n=fread(buffer,1,sizeof buffer,fp);  //middle args are reversed
  fprintf(stdout,"%d items read in\n",n);

  fseek(fp,0,SEEK_SET);
  
  fprintf(stdout,"\n\n\nThird test: Reading in the file:\n"); 
  while((n=fread(buffer,1,sizeof buffer,fp))>0)
  {
     fprintf(stdout,"%d bytes read\n",n);
   }

  fprintf(stdout,"Final value of n:  %d\n",n);
  
  
 
  return 0;
  }

