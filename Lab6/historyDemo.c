#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wordexp.h>
#include <pwd.h>

int main(int argc, char *argv[]){

 char subCmd[30];
 wordexp_t expansionList;
         strcpy(subCmd,"cat -n .bash_history | tail"); //default for tail is 10 lines
 system(subCmd);
 return 0;
}
