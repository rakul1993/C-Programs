/*
   File: ansi.h
   Course: CTEC102
   Author: Leon King
   Date: Tuesday January 17, 2006
   Description:  Macros for ansi terminal codes
   */

#define ESCAPE '\033'
#define UP             "\033[1A"
#define DOWN           "\033[1B"
#define RIGHT          "\033[1C"
#define LEFT           "\033[1D"
#define SAVECURSOR     "\033[s"
#define RESTORECURSOR  "\033[u"

#define CLEARSCREEN    "\033[2J"
#define NORMAL         "\033[0m"
#define BOLD           "\033[1m"
#define UNDERLINE      "\033[4m"
#define BLINKING       "\033[5m"
#define REVERSE        "\033[7m"
#define INVISIBLE      "\033[8m"

//Foreground colours
#define BLACK    "\033[30m" 
#define RED      "\033[31m"         
#define GREEN    "\033[32m" 
#define YELLOW   "\033[33m" 
#define BLUE     "\033[34m" 
#define MAGENTAl "\033[35m" 
#define CYAN     "\033[36m" 
#define WHITE    "\033[37m" 
//Background colours
#define BBLACK    "\033[40m" 
#define BRED      "\033[41m"         
#define BGREEN    "\033[42m" 
#define BYELLOW   "\033[43m" 
#define BBLUE     "\033[44m" 
#define BMAGENTA "\033[45m" 
#define BCYAN     "\033[46m" 
#define BWHITE    "\033[47m" 

//Navigation
#define goto(x,y)   fprintf(stdout,"\033[%d;%df",y,x);
//More to come
