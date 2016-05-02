/*
   File: book_order.c
   Course: CENG251
   Author: Prof. Leon King,J230,x4200
   Date: Sunday Jan 18, 2015   21:58 PM
*/


#include <stdio.h>

#include "book_order.h"

int main(int argc, char * argv[],char * envp[])
{
  struct BOOK_ORDER order;
  struct BOOK_ORDER orders[]={
          {"007-6092024712",22,"Linux Programming", 143800000,"Robbins",43.34,0},
          {"978-1449397227",30,"JQuery Pocket Ref", 143900400,"Flanagan",14.50,'Y'},
          {"978-1430210436",40,"Portable Shell Scripts",14402900,"Seebach",39.95,'Y'}
         } ;

  //Show all the records
  displayOrder(0,orders[0]);
  displayOrder(1,orders[1]);
  displayOrder(2,orders[2]); 

  //Prompt for a replacement title and author
  fprintf(stdout,"\n\nEnter a new title for order #1: " );
  fflush(stdout);
  fgets(orders[1].title, sizeof(orders[1].title),stdin);

  fprintf(stdout,"\n\nEnter a new author for order #1: " );
  fflush(stdout);
  fgets(orders[1].author, sizeof(orders[1].author),stdin);


  fprintf(stdout,"\n\nModified order: ");
  displayOrder(1,orders[1]);
  
  FILE * dumpFile=fopen("orders.dump","wb");
  fwrite(orders,sizeof order,sizeof orders/sizeof order,dumpFile);
  fclose(dumpFile); 

  return 0;
  }

