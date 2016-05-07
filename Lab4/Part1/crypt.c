/*
   File: crypt.c
   Purpose: Demo of simple cryptology.   
   Course: CENG411
   Author: Leon King,J230,x4200
   Date: Monday Mar 14, 2011   08:29 AM
   Note:  Must be compiled with -lcrypt to bring in the cryptology library
*/


#include <stdio.h>
#include <crypt.h>
#include <unistd.h>
int main(int argc, char * argv[],char * envp[])
{
  char password[]="swordfish";
  char * result=crypt(password,"cinnamon");

  fprintf(stderr,"encrypted result: %s\n", result); //getpass also output 

  char *pass;
  pass=getpass("Enter your password: ");
  fprintf(stdout,"Your password was: %s\n",pass);
  result=crypt(pass,"pepper");
  fprintf(stderr,"encrypted result: %s\n", result); //getpass also output 
  return 0;
  }
