/*/////////////////////////////////////////////////////////////////////////////
//
// File name : sieve1.c
// Author    : Luke Burford
// Date      : 2018/15/09
// Desc      : Finds the primes up to N, with sequential optimization
//
/////////////////////////////////////////////////////////////////////////////*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "timer.h"
#define indexIn(i) (i-1)/2  

int main(int argc, char **argv) {

   long N  = 100;

   char *mark;

   long   size;
   long   curr;
   long   i, j,n;
   long   count;

   /* Time */

   double time;

   if ( argc > 1 ) N  = atoi(argv[1]);

   /* Start Timer */

   initialize_timer ();
   start_timer();

   size = (N+1)*sizeof(char);
   mark = (char *)malloc(size/2);
   
   #pragma omp parallel for
   for (i=1; i<=N/2-1; i=i+1){
     mark[i]=0;
   }

   curr=3;       /*first prime*/
   while (curr*curr<=N) { /*outer loop iterates only until sqrt(curr) */
   #pragma omp parallel for
   for (i=curr*curr; i<=N; i+=curr*2)
       if(i % 2 != 0) mark[(i-1)/2]=1;
    else continue;
   while (mark[(curr += 1)/2]) ; /* do nothing */
   /* now index has the first unmarked number, so ... */
   }

   /* stop timer */
   stop_timer();
   time=elapsed_time ();

   /*number of primes*/
   count = 1;
   for(i = 1; i <=indexIn(N); i++){
        if(mark[i] == 0) {
//         	 printf("\t prime %ld  \n",i );
        	++count;
        }

   }
//   printf("There are %ld primes less than or equal to %ld\n", count, N);
   /* print results */
//   printf("First three primes:");
   j = 1;
//   printf("%d ", 2);
   for ( i=1 ; i <= indexIn(N) && j < 3; i+=1 ) {
      if (mark[i]==0){
//            printf("%ld ", 2*i+1);
            ++j;
      }
   }
//   printf("\n");

//   printf("Last three primes:");
   j = 0;
   n=(N%2?N:N-1);
   for (i = n/2; i > 1 && j < 3; i-=1){
     if (mark[i]==0){
//        printf("%ld ", 2*i+1);
        j++;
     }
   }
//   printf("\n");


   printf("%lf\n", time);

   free(mark);
   return 0;
}


