/*/////////////////////////////////////////////////////////////////////////////
//
// File name : sieve2.c
// Author    : Luke Burford
// Date      : 2018/15/09
// Desc      : Finds the primes up to N, with sequential optimization, and basic paralization
//
/////////////////////////////////////////////////////////////////////////////*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "timer.h"
#define MIN(a,b) ((a<b)  ? a : b)
#define MAX(a,b) ((a>b) ? a : b)
#define indexIn(i) (i-1)/2  
#define indexOut(i) (2*i)+1 

int FMIB(int ii, int j) {
    int a = ii/ j;
    int firstMult = a *j;
    if(firstMult <= ii)
        firstMult += j;
    if(firstMult%2==0)
        firstMult += j;
    return firstMult;
}

int main(int argc, char **argv) {

   long N  = 100;
   long BLKSize = 400000;
   char *mark;

   long   size;
   long   curr;
   long   i, j,n, ii;
   long   count;

   /* Time */

   double time;

   if ( argc > 1 )
       N  = atoi(argv[1]);
   if (argc > 2)
       BLKSize = atoi(argv[2]); 

       
   /* Start Timer */

   initialize_timer ();
   start_timer();

   size = (N+1)*sizeof(char);
   mark = (char *)malloc(size/2);
   for (i=1; i<=N/2-1; i=i+1){
     mark[i]=0;
   }

   curr=3;       /*first prime*/
   while (curr*curr<=sqrt(N)) { /*outer loop iterates only until sqrt(curr) */
   for (i=curr*curr; i<=sqrt(N); i+=curr*2)
       if(i % 2 != 0) mark[(i-1)/2]=1;
    else continue;
   while (mark[(curr += 2 -1)/2]) ; /* do nothing */
   /* now index has the first unmarked number, so ... */
   }
   
   long numP = 0;
   long pSize = (sqrt(N)+1)*sizeof(int); 
   long* primes = (long *)malloc(pSize);
   long current = 0;
   for(i = 1; i <= indexIn(sqrt(N)); ++i){
       if(mark[i] == 0){
           numP++;
           primes[current] = indexOut(i);
           current++;
       }
   }
   long start = sqrt(N);
   
   for(ii = start; ii < N; ii += BLKSize){
       for(j = 0; j < numP; j++){     
           for(i = FMIB(ii, primes[j]); i <= MIN((ii+BLKSize), N); i+=(primes[j]*2)){
               mark[indexIn(i)] = 1;
           }
       }
       start += BLKSize;
   }

   /* stop timer */
   stop_timer();
   time=elapsed_time ();

   /*number of primes*/
   count = 1;
   for(i = 1; i <=N/2-1; i+=1){
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
   for ( i=1 ; i <= N/2 && j < 3; i+=1 ) {
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


