// This file is generated from test alphabets program by code generator in alphaz
// To compile this code, use -lm option for math library.

// Includes
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <limits.h>
#include <float.h>
#include <time.h>
#include <sys/time.h>
#include <sys/errno.h>


// Common Macros
#define max(x, y)   ((x)>(y) ? (x) : (y))
#define MAX(x, y)	((x)>(y) ? (x) : (y))
#define min(x, y)   ((x)>(y) ? (y) : (x))
#define MIN(x, y)	((x)>(y) ? (y) : (x))
#define CEILD(n,d)  (int)ceil(((double)(n))/((double)(d)))
#define ceild(n,d)  (int)ceil(((double)(n))/((double)(d)))
#define FLOORD(n,d) (int)floor(((double)(n))/((double)(d)))
#define floord(n,d) (int)floor(((double)(n))/((double)(d)))
#define CDIV(x,y)    CEILD((x),(y))
#define div(x,y)    CDIV((x),(y))
#define FDIV(x,y)    FLOORD((x),(y))
#define LB_SHIFT(b,s)  ((int)ceild(b,s) * s)
#define MOD(i,j)   ((i)%(j))
#define mallocCheck(v,s,d) if ((v) == NULL) { printf("Failed to allocate memory for %s : size=%lu\n", "sizeof(d)*(s)", sizeof(d)*(s)); exit(-1); }
#define EPSILON 1.0E-9






//Memory Macros
#define A(i,j,k,l) A[i][j][k][l]
#define B(i,j,k,l) B[i][j][k][l]
#define C(i,j,k,l) C[i][j][k][l]

#define C_verify(i,j,k,l) C_verify[i][j][k][l]
#define var_C(i,j,k,l) C(i,j,k,l)
#define var_C_verify(i,j,k,l) C_verify(i,j,k,l)

//function prototypes
void BlockedTTMM(long, long, float****, float****, float****);
void BlockedTTMM_verify(long, long, float****, float****, float****);

//main
int main(int argc, char** argv) {
	//Check number of args
	if (argc <= 2) {
		printf("Number of argument is smaller than expected.\n");
		printf("Expecting n,b\n");
		exit(0);
	}
	
	char *end = 0;
	char *val = 0;
	//Read Parameters
	//Initialisation of n
	errno = 0;
	end = 0;
	val = argv[1];
	long n = strtol(val,&end,10);
	if ((errno == ERANGE && (n == LONG_MAX || n == LONG_MIN)) || (errno != 0 && n == 0)) {
		perror("strtol");
		exit(EXIT_FAILURE);
	}
	if (end == val) {
		fprintf(stderr, "No digits were found for n\n");
		exit(EXIT_FAILURE);
	}
	if (*end != '\0'){
		printf("For parameter n: Converted part: %ld, non-convertible part: %s\n", n, end);
		exit(EXIT_FAILURE);
	}
	
	//Initialisation of b
	errno = 0;
	end = 0;
	val = argv[2];
	long b = strtol(val,&end,10);
	if ((errno == ERANGE && (b == LONG_MAX || b == LONG_MIN)) || (errno != 0 && b == 0)) {
		perror("strtol");
		exit(EXIT_FAILURE);
	}
	if (end == val) {
		fprintf(stderr, "No digits were found for b\n");
		exit(EXIT_FAILURE);
	}
	if (*end != '\0'){
		printf("For parameter b: Converted part: %ld, non-convertible part: %s\n", b, end);
		exit(EXIT_FAILURE);
	}
	
	
	///Parameter checking
	if (!((n >= 1 && b >= 1))) {
		printf("The value of parameters are not valid.\n");
		exit(-1);
	}
	
	
	//Memory Allocation
	int mz1, mz2, mz3, mz4;
	float* _lin_A = (float*)malloc(sizeof(float)*((n) * (n) * (b) * (b)));
	mallocCheck(_lin_A, ((n) * (n) * (b) * (b)), float);
	float**** A = (float****)malloc(sizeof(float***)*(n));
	mallocCheck(A, (n), float***);
	for (mz1=0;mz1 < n; mz1++) {
		A[mz1] = (float***)malloc(sizeof(float**)*(n));
		mallocCheck(A[mz1], (n), float**);
		for (mz2=0;mz2 < n; mz2++) {
			A[mz1][mz2] = (float**)malloc(sizeof(float*)*(b));
			mallocCheck(A[mz1][mz2], (b), float*);
			for (mz3=0;mz3 < b; mz3++) {
				A[mz1][mz2][mz3] = &_lin_A[(mz1*((n) * (b) * (b))) + (mz2*((b) * (b))) + (mz3*(b))];
			}
		}
	}
	float* _lin_B = (float*)malloc(sizeof(float)*((n) * (n) * (b) * (b)));
	mallocCheck(_lin_B, ((n) * (n) * (b) * (b)), float);
	float**** B = (float****)malloc(sizeof(float***)*(n));
	mallocCheck(B, (n), float***);
	for (mz1=0;mz1 < n; mz1++) {
		B[mz1] = (float***)malloc(sizeof(float**)*(n));
		mallocCheck(B[mz1], (n), float**);
		for (mz2=0;mz2 < n; mz2++) {
			B[mz1][mz2] = (float**)malloc(sizeof(float*)*(b));
			mallocCheck(B[mz1][mz2], (b), float*);
			for (mz3=0;mz3 < b; mz3++) {
				B[mz1][mz2][mz3] = &_lin_B[(mz1*((n) * (b) * (b))) + (mz2*((b) * (b))) + (mz3*(b))];
			}
		}
	}
	float* _lin_C = (float*)malloc(sizeof(float)*((n) * (n) * (b) * (b)));
	mallocCheck(_lin_C, ((n) * (n) * (b) * (b)), float);
	float**** C = (float****)malloc(sizeof(float***)*(n));
	mallocCheck(C, (n), float***);
	for (mz1=0;mz1 < n; mz1++) {
		C[mz1] = (float***)malloc(sizeof(float**)*(n));
		mallocCheck(C[mz1], (n), float**);
		for (mz2=0;mz2 < n; mz2++) {
			C[mz1][mz2] = (float**)malloc(sizeof(float*)*(b));
			mallocCheck(C[mz1][mz2], (b), float*);
			for (mz3=0;mz3 < b; mz3++) {
				C[mz1][mz2][mz3] = &_lin_C[(mz1*((n) * (b) * (b))) + (mz2*((b) * (b))) + (mz3*(b))];
			}
		}
	}
	#ifdef VERIFY
		float* _lin_C_verify = (float*)malloc(sizeof(float)*((n) * (n) * (b) * (b)));
		mallocCheck(_lin_C_verify, ((n) * (n) * (b) * (b)), float);
		float**** C_verify = (float****)malloc(sizeof(float***)*(n));
		mallocCheck(C_verify, (n), float***);
		for (mz1=0;mz1 < n; mz1++) {
			C_verify[mz1] = (float***)malloc(sizeof(float**)*(n));
			mallocCheck(C_verify[mz1], (n), float**);
			for (mz2=0;mz2 < n; mz2++) {
				C_verify[mz1][mz2] = (float**)malloc(sizeof(float*)*(b));
				mallocCheck(C_verify[mz1][mz2], (b), float*);
				for (mz3=0;mz3 < b; mz3++) {
					C_verify[mz1][mz2][mz3] = &_lin_C_verify[(mz1*((n) * (b) * (b))) + (mz2*((b) * (b))) + (mz3*(b))];
				}
			}
		}
	#endif

	//Initialization of rand
	srand((unsigned)time(NULL));
	 
	//Input Initialization
	{
		#if defined (RANDOM)
			#define S0(i,j,k,l) (A(i,j,k,l) = rand()) 
		#elif defined (CHECKING) || defined (VERIFY)
			#ifdef NO_PROMPT
				#define S0(i,j,k,l) scanf("%f", &A(i,j,k,l))
			#else
				#define S0(i,j,k,l) printf("A(%ld,%ld,%ld,%ld)=",(long) i,(long) j,(long) k,(long) l); scanf("%f", &A(i,j,k,l))
			#endif
		#else
			#define S0(i,j,k,l) (A(i,j,k,l) = 1)   //Default value
		#endif
		
		
		int c1,c2,c3,c4;
		for(c1=0;c1 <= n-1;c1+=1)
		 {
		 	for(c2=c1;c2 <= n-1;c2+=1)
		 	 {
		 	 	for(c3=0;c3 <= b-1;c3+=1)
		 	 	 {
		 	 	 	for(c4=0;c4 <= b-1;c4+=1)
		 	 	 	 {
		 	 	 	 	S0((c1),(c2),(c3),(c4));
		 	 	 	 }
		 	 	 }
		 	 }
		 }
		#undef S0
	}
	{
		#if defined (RANDOM)
			#define S0(i,j,k,l) (B(i,j,k,l) = rand()) 
		#elif defined (CHECKING) || defined (VERIFY)
			#ifdef NO_PROMPT
				#define S0(i,j,k,l) scanf("%f", &B(i,j,k,l))
			#else
				#define S0(i,j,k,l) printf("B(%ld,%ld,%ld,%ld)=",(long) i,(long) j,(long) k,(long) l); scanf("%f", &B(i,j,k,l))
			#endif
		#else
			#define S0(i,j,k,l) (B(i,j,k,l) = 1)   //Default value
		#endif
		
		
		int c1,c2,c3,c4;
		for(c1=0;c1 <= n-1;c1+=1)
		 {
		 	for(c2=c1;c2 <= n-1;c2+=1)
		 	 {
		 	 	for(c3=0;c3 <= b-1;c3+=1)
		 	 	 {
		 	 	 	for(c4=0;c4 <= b-1;c4+=1)
		 	 	 	 {
		 	 	 	 	S0((c1),(c2),(c3),(c4));
		 	 	 	 }
		 	 	 }
		 	 }
		 }
		#undef S0
	}
	
	//Timing
	struct timeval time;
	double elapsed_time;
	
	//Call the main computation
	gettimeofday(&time, NULL);
	elapsed_time = (((double) time.tv_sec) + ((double) time.tv_usec)/1000000);
	
	BlockedTTMM(n, b, A, B, C);

	gettimeofday(&time, NULL);
	elapsed_time = (((double) time.tv_sec) + ((double) time.tv_usec)/1000000) - elapsed_time;

	// timing information
	printf("Execution time : %lf sec.\n", elapsed_time);
	
	#ifdef TIMING
		FILE * fp = fopen( "trace.dat","a+");
		if (fp == NULL) {
				printf("I couldn't open trace.dat for writing.\n");
				exit(EXIT_FAILURE);
		}
		fprintf(fp, "%ld\t%ld\t%lf\n",n,b,elapsed_time);
		fclose(fp);
	#endif
	
	//Verification Run
	#ifdef VERIFY
		#ifdef TIMING
			gettimeofday(&time, NULL);
			elapsed_time = (((double) time.tv_sec) + ((double) time.tv_usec)/1000000);
		#endif
    	BlockedTTMM_verify(n, b, A, B, C_verify);
    	#ifdef TIMING
    		gettimeofday(&time, NULL);
			elapsed_time = (((double) time.tv_sec) + ((double) time.tv_usec)/1000000) - elapsed_time;
			
			FILE * fp_verify = fopen( "trace_verify.dat","a+");
			if (fp == NULL) {
					printf("I couldn't open trace_verify.dat for writing.\n");
					exit(EXIT_FAILURE);
			}
			fprintf(fp, "%ld\t%ld\t%lf\n",n,b,elapsed_time);
			fclose(fp_verify);
		#endif
	#endif
    	
	#ifdef CHECKING
    	//Print Outputs
		{
			#ifdef NO_PROMPT
				#define S0(i,j,k,l) printf("%0.2f\n",var_C(i,j,k,l))
			#else
				#define S0(i,j,k,l) printf("C(%ld,%ld,%ld,%ld)=",(long) i,(long) j,(long) k,(long) l);printf("%0.2f\n",var_C(i,j,k,l))
			#endif
			int c1,c2,c3,c4;
			for(c1=0;c1 <= n-1;c1+=1)
			 {
			 	for(c2=c1;c2 <= n-1;c2+=1)
			 	 {
			 	 	for(c3=0;c3 <= b-1;c3+=1)
			 	 	 {
			 	 	 	for(c4=0;c4 <= b-1;c4+=1)
			 	 	 	 {
			 	 	 	 	S0((c1),(c2),(c3),(c4));
			 	 	 	 }
			 	 	 }
			 	 }
			 }
			#undef S0
		}
	#elif VERIFY
		//Compare outputs for verification
		{
			//Error Counter
			int _errors_ = 0;
			#define S0(i,j,k,l) if (fabsf(1.0f - var_C_verify(i,j,k,l)/var_C(i,j,k,l)) > EPSILON) _errors_++;
			int c1,c2,c3,c4;
			for(c1=0;c1 <= n-1;c1+=1)
			 {
			 	for(c2=c1;c2 <= n-1;c2+=1)
			 	 {
			 	 	for(c3=0;c3 <= b-1;c3+=1)
			 	 	 {
			 	 	 	for(c4=0;c4 <= b-1;c4+=1)
			 	 	 	 {
			 	 	 	 	S0((c1),(c2),(c3),(c4));
			 	 	 	 }
			 	 	 }
			 	 }
			 }
			#undef S0
			if(_errors_ == 0){
				printf("TEST PASSED\n");
			}else{
				printf("TEST FAILED\n");
			}
		}
    #endif
    
	//Memory Free
	free(_lin_A);
	for (mz1=0;mz1 < n; mz1++) {
		for (mz2=0;mz2 < n; mz2++) {
			free(A[mz1][mz2]);
		}
		free(A[mz1]);
	}
	free(A);
	free(_lin_B);
	for (mz1=0;mz1 < n; mz1++) {
		for (mz2=0;mz2 < n; mz2++) {
			free(B[mz1][mz2]);
		}
		free(B[mz1]);
	}
	free(B);
	free(_lin_C);
	for (mz1=0;mz1 < n; mz1++) {
		for (mz2=0;mz2 < n; mz2++) {
			free(C[mz1][mz2]);
		}
		free(C[mz1]);
	}
	free(C);
	#ifdef VERIFY
		free(_lin_C_verify);
		for (mz1=0;mz1 < n; mz1++) {
			for (mz2=0;mz2 < n; mz2++) {
				free(C[mz1][mz2]_verify);
			}
			free(C[mz1]_verify);
		}
		free(C_verify);
	#endif
	
	return EXIT_SUCCESS;
}

//Memory Macros
#undef A
#undef B
#undef C


//Common Macro undefs
#undef max
#undef MAX
#undef min
#undef MIN
#undef CEILD
#undef ceild
#undef FLOORD
#undef floord
#undef CDIV
#undef FDIV
#undef LB_SHIFT
#undef MOD
#undef EPSILON
