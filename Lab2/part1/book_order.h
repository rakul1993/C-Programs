/*
   File: book_order.h
   Course: CENG251
   Author: Rakul Mahenthiran
   Date: Feb 1, 2015
   Purpose:  Data Structure to describe a book order from a book store
*/


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <stddef.h>

struct BOOK_ORDER
{
    char    isbn[15];
    int     copiesOnOrder;
    char    title[23]; 
    time_t  dateExpected;
    char    author[11];
    double  price;   
    bool    prepaid;
   
};

void displayOrder(int recordNo,struct BOOK_ORDER order)
{
  //sample array of BOOK_ORDER size of 10
  struct BOOK_ORDER testBook[10]= {"123-1234567890", 43, "Lab2", 121200000, "King", 99.99, 'Y'};  

  fprintf(stdout,"recordNo: %d isbn: %s copies: %d  author: %s  "
                 "title: %s price: %lf  prepaid: %c   dateExpected: %s \n",
                   recordNo,order.isbn, order.copiesOnOrder,order.author,
                            order.title, order.price, order.prepaid ? 'Y' : 'N',
                            ctime(&order.dateExpected) 
                   );
                  // , order.prepaid ? 'Y' : 'N'
 

  // display the size of each individual field in BOOK_ORDER
  fprintf(stdout, "The size of isbn is:          %d \n", sizeof(order.isbn));
  fprintf(stdout, "The size of copiesOnOrder is: %d \n", sizeof(order.copiesOnOrder));
  fprintf(stdout, "The size of title is:         %d \n", sizeof(order.title));
  fprintf(stdout, "The size of dateExpected is:  %d \n", sizeof(order.dateExpected));
  fprintf(stdout, "The size of author is:        %d \n", sizeof(order.author));
  fprintf(stdout, "The size of price is:         %d \n", sizeof(order.price));
  fprintf(stdout, "The size of prepaid is:       %d \n\n\n", sizeof(order.prepaid));

  // display the offset of each individual field in BOOK_ORDER
  fprintf(stdout, "The offset of isbn is:          %u \n", offsetof(struct BOOK_ORDER, isbn));
  fprintf(stdout, "The offset of copiesOnOrder is: %u \n", offsetof(struct BOOK_ORDER, copiesOnOrder));
  fprintf(stdout, "The offset of title is:         %u \n", offsetof(struct BOOK_ORDER, title));
  fprintf(stdout, "The offset of dateExpected is:  %u \n", offsetof(struct BOOK_ORDER, dateExpected));
  fprintf(stdout, "The offset of author is:        %u \n", offsetof(struct BOOK_ORDER, author));
  fprintf(stdout, "The offset of price is:         %u \n", offsetof(struct BOOK_ORDER, price));
  fprintf(stdout, "The offset of prepaid is:       %u \n\n\n", offsetof(struct BOOK_ORDER, prepaid));

  // display size of testBook array
  fprintf(stdout, "The size of STRUCT testBook is: %d \n\n\n", sizeof(testBook));

  // display size of elements in STRUCT testBook array
  fprintf(stdout, "The size of isbn for array is:          %d \n", sizeof(testBook[0].isbn));
  fprintf(stdout, "The size of copiesOnOrder for array is: %d \n", sizeof(testBook[0].copiesOnOrder));
  fprintf(stdout, "The size of title for array is:         %d \n", sizeof(testBook[0].title));
  fprintf(stdout, "The size of dateExpected for array is:  %d \n", sizeof(testBook[0].dateExpected));
  fprintf(stdout, "The size of author for array is:        %d \n", sizeof(testBook[0].author));
  fprintf(stdout, "The size of price for array is:         %d \n", sizeof(testBook[0].price));
  fprintf(stdout, "The size of prepaid for array is:       %d \n\n\n", sizeof(testBook[0].prepaid));

  // display base address of STRUCT testBook array(in HEX)
  fprintf(stdout, "The starting memory location of STRUCT testBook array is: %p \n\n\n", &testBook);
  
  // display addresses of the next 3 records in STRUCT testBook array
  fprintf(stdout, "The starting memory location of second record in STRUCT testBook array is: %p \n", &testBook[1]);
  fprintf(stdout, "The starting memory location of third record in STRUCT testBook array is:  %p \n", &testBook[2]);
  fprintf(stdout, "The starting memory location of fourth record in STRUCT testBook array is: %p \n\n\n", &testBook[3]);

}  
