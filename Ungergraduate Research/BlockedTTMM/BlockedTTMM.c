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

// Common functions for min and max
//functions for integer max
inline int __max_int(int x, int y){
	return ((x)>(y) ? (x) : (y));
}

inline short __max_short(short x, short y){
	return ((x)>(y) ? (x) : (y));
}

inline long __max_long(long x, long y){
	return ((x)>(y) ? (x) : (y));
}

inline unsigned int __max_unsigned_int(unsigned int x, unsigned int y){
	return ((x)>(y) ? (x) : (y));
}

inline unsigned short __max_unsigned_short(unsigned short x, unsigned short y){
	return ((x)>(y) ? (x) : (y));
}

//function for float max
inline float __max_float(float x, float y){
	return ((x)>(y) ? (x) : (y));
}

//function for double max
inline double __max_double(double x, double y){
	return ((x)>(y) ? (x) : (y));
}

//function for integer min
inline int __min_int(int x, int y){
	return ((x)>(y) ? (y) : (x));
}

inline short __min_short(short x, short y){
	return ((x)>(y) ? (y) : (x));
}

inline long __min_long(long x, long y){
	return ((x)>(y) ? (y) : (x));
}

inline unsigned int __min_unsigned_int(unsigned int x, unsigned int y){
	return ((x)>(y) ? (y) : (x));
}

inline unsigned short __min_unsigned_short(unsigned short x, unsigned short y){
	return ((x)>(y) ? (y) : (x));
}

inline unsigned long __min_unsigned_long(unsigned long x, unsigned long y){
	return ((x)>(y) ? (y) : (x));
}

inline float __min_float(float x, float y){
	return ((x)>(y) ? (y) : (x));
}

inline double __min_double(double x, double y){
	return ((x)>(y) ? (y) : (x));
}


///Global Variables
static float**** A;
static float**** B;
static float**** C;
static char**** _flag_C;


//Local Function Declarations
float reduce_BlockedTTMM_C_1(long, long, int, int, int, int);
float eval_C(long, long, int, int, int, int);

//Memory Macros
#define A(i,j,k,l) A[i][j][k][l]
#define B(i,j,k,l) B[i][j][k][l]
#define C(i,j,k,l) C[i][j][k][l]
#define _flag_C(i,j,k,l) _flag_C[i][j][k][l]

void BlockedTTMM(long n, long b, float**** _local_A, float**** _local_B, float**** _local_C){
	///Parameter checking
	if (!((n >= 1 && b >= 1))) {
		printf("The value of parameters are not valid.\n");
		exit(-1);
	}
	//Copy to global
	A = _local_A;
	B = _local_B;
	C = _local_C;
	
	//Memory Allocation
	int mz1, mz2, mz3, mz4;
	
	char* _lin__flag_C = (char*)malloc(sizeof(char)*((n) * (n) * (b) * (b)));
	mallocCheck(_lin__flag_C, ((n) * (n) * (b) * (b)), char);
	_flag_C = (char****)malloc(sizeof(char***)*(n));
	mallocCheck(_flag_C, (n), char***);
	for (mz1=0;mz1 < n; mz1++) {
		_flag_C[mz1] = (char***)malloc(sizeof(char**)*(n));
		mallocCheck(_flag_C[mz1], (n), char**);
		for (mz2=0;mz2 < n; mz2++) {
			_flag_C[mz1][mz2] = (char**)malloc(sizeof(char*)*(b));
			mallocCheck(_flag_C[mz1][mz2], (b), char*);
			for (mz3=0;mz3 < b; mz3++) {
				_flag_C[mz1][mz2][mz3] = &_lin__flag_C[(mz1*((n) * (b) * (b))) + (mz2*((b) * (b))) + (mz3*(b))];
			}
		}
	}
	memset(_lin__flag_C, 'N', ((n) * (n) * (b) * (b)));
	#define S0(i,j,k,l) eval_C(n,b,i,j,k,l)
	{
		//Domain
		//{i,j,k,l|i>=0 && j>=i && n>=j+1 && k>=0 && b>=k+1 && l>=0 && b>=l+1 && n>=1 && b>=1}
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
	}
	#undef S0
	
	//Memory Free
	free(_lin__flag_C);
	for (mz1=0;mz1 < n; mz1++) {
		for (mz2=0;mz2 < n; mz2++) {
			free(_flag_C[mz1][mz2]);
		}
		free(_flag_C[mz1]);
	}
	free(_flag_C);
}
float reduce_BlockedTTMM_C_1(long n, long b, int ip, int jp, int kp, int lp){
	float reduceVar = 0;
	#define S0(i,j,k,l,d,e) reduceVar = (reduceVar)+((A(i,d,k,e))*(B(d,j,e,l)))
	{
		//Domain
		//{i,j,k,l,d,e|ip>=0 && jp>=ip && b>=lp+1 && kp>=0 && b>=kp+1 && lp>=0 && n>=jp+1 && b>=1 && n>=1 && i>=0 && d>=i && n>=d+1 && k>=0 && b>=k+1 && e>=0 && b>=e+1 && j>=i && l>=0 && d>=0 && j>=d && n>=j+1 && b>=l+1 && ip==i && jp==j && kp==k && lp==l}
		int c5,c6;
		for(c5=ip;c5 <= jp;c5+=1)
		 {
		 	for(c6=0;c6 <= b-1;c6+=1)
		 	 {
		 	 	S0((ip),(jp),(kp),(lp),(c5),(c6));
		 	 }
		 }
	}
	#undef S0
	return reduceVar;
}
float eval_C(long n, long b, int i, int j, int k, int l){
	if ( _flag_C(i,j,k,l) == 'N' ) {
		_flag_C(i,j,k,l) = 'I';
	//Body for C
		C(i,j,k,l) = reduce_BlockedTTMM_C_1(n,b,i,j,k,l);
		_flag_C(i,j,k,l) = 'F';
	} else if ( _flag_C(i,j,k,l) == 'I' ) {
		printf("There is a self dependence on C at (%d,%d,%d,%d) \n",i,j,k,l);
		exit(-1);
	}
	return C(i,j,k,l);
}

//Memory Macros
#undef A
#undef B
#undef C
#undef _flag_C


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
