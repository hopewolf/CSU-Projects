// nvcc 036 sgemm .c -lcublas
# include <stdio.h>
# include <stdlib.h>
# include <cuda_runtime.h>
# include "cublas_v2.h"
#include <sys/time.h>     //measuring performance data
# define IDX2C(i ,j , ld ) ((( j )*( ld ))+( i ))
# define m 32000 // a - mxk matrix
# define n 32000 // b - kxn matrix
# define k 32000 // c - mxn matrix

/**********************************************************************
 * function name: cublasGetErrorString
 * description: gets the cublas string error codes for printing
 * parameters: 
 * error a cublas error status enum
 * return: char pointer (string)
 **********************************************************************/
const char* cublasGetErrorString(cublasStatus_t status)
{
    switch(status)
    {
        case CUBLAS_STATUS_SUCCESS: return "CUBLAS_STATUS_SUCCESS";
        case CUBLAS_STATUS_NOT_INITIALIZED: return "CUBLAS_STATUS_NOT_INITIALIZED";
        case CUBLAS_STATUS_ALLOC_FAILED: return "CUBLAS_STATUS_ALLOC_FAILED";
        case CUBLAS_STATUS_INVALID_VALUE: return "CUBLAS_STATUS_INVALID_VALUE"; 
        case CUBLAS_STATUS_ARCH_MISMATCH: return "CUBLAS_STATUS_ARCH_MISMATCH"; 
        case CUBLAS_STATUS_MAPPING_ERROR: return "CUBLAS_STATUS_MAPPING_ERROR";
        case CUBLAS_STATUS_EXECUTION_FAILED: return "CUBLAS_STATUS_EXECUTION_FAILED"; 
        case CUBLAS_STATUS_INTERNAL_ERROR: return "CUBLAS_STATUS_INTERNAL_ERROR"; 
    }
    return "unknown error";
}

int main ( void ){
    struct timeval time;
    double elapsed_time;
    cudaError_t cudaStat ; // cudaMalloc status
    cublasStatus_t stat ; // CUBLAS functions statusx
    cublasHandle_t handle ; // CUBLAS context
    int i,j; // i-row index ,j- column index
    float *a; // mxk matrix a on the host
    float *b; // kxn matrix b on the host
    float *c; // mxn matrix c on the host
    gettimeofday(&time, NULL);
    elapsed_time = (((double) time.tv_sec) + ((double) time.tv_usec)/1000000);
    a=(float*)malloc(m*k*sizeof(float)); // host memory for a
    b=(float*)malloc(k*n*sizeof(float)); // host memory for b
    c=(float*)malloc(m*n*sizeof(float)); // host memory for c
    // define an mxk matrix a column by column
    int ind =11; // a:
    // print a row by row
//     printf ("a:\n");
    int val = 1;
    // random initialize matrix A [mxk]
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            a[i * n + j] =val++;
//             printf("%5.0f", a[i * n + j]);
        }
//         printf("\n");
    }
    // define a kxn matrix b column by column
    

    // print b row by row
    val = 1;
//     printf ("b:\n");
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < n; ++j) {
            b[i * n + j] =val++;
//             printf("%5.0f", b[i * n + j]);
        }
//         printf("\n");
    }
    // define an mxn matrix c column by column
    // print c row by row
//     printf ("c:\n");
    val = 1;
//     for (int i = 0; i < m; ++i) {
//         for (int j = 0; j < n; ++j) {
//             c[i * n + j] =val++;
//             printf("%5.0f", c[i * n + j]);
//         }
//         printf("\n");
//     }
    // on the device
    float *d_a; // d_a - a on the device
    float *d_b; // d_b - b on the device
    float *d_c; // d_c - c on the device
    cudaStat = cudaMalloc((void**)&d_a,m*k*sizeof(*a)); // device memory alloc for a
    cudaStat = cudaMalloc((void**)&d_b,k*n*sizeof(*b)); // device memory alloc for b
    cudaStat = cudaMalloc((void**)&d_c,m*n*sizeof(*c)); // device memory alloc for c
    stat = cublasCreate(&handle); // initialize CUBLAS context
//     printf("Cublas Create Error: %s\n", cublasGetErrorString(stat));
    // copy matrices from the host to the device
    //cudaGetErrorString((cudaError_t) cudaStat);
    stat = cublasSetMatrix(m,k,sizeof(*a),a,m,d_a,m); //a -> d_a
    stat = cublasSetMatrix(k,n,sizeof(*b),b,k,d_b,k); //b -> d_b
    stat = cublasSetMatrix(m,n,sizeof(*c),c,m,d_c,m); //c -> d_c
    float al =1.0f; // al =1
    float bet =0.0f; // bet =0
    // matrix - matrix multiplication : d_c = al*d_a *d_b + bet *d_c
    // d_a -mxk matrix , d_b -kxn matrix , d_c -mxn matrix ;
    // al ,bet -scalars
    stat=cublasSgemm(handle,CUBLAS_OP_N,CUBLAS_OP_N,m,n,k,&al,d_a,m,d_b,k,&bet,d_c,m);
    stat = cublasGetMatrix (m,n, sizeof (*c) ,d_c ,m,c,m); // cp d_c - >c
//     printf ("c after Sgemm :\n");
//     for (i = 0; i < m; i++) {
//         for (j = 0; j < n; j++) {
//             //printf("[%d][%d]:%d, ", i, j, c[i*k + j]);
//             printf(" %7.0f ", c[i*n + j]);
//         }
//         printf("\n");
//     }
    cudaFree(d_a); // free device memory
    cudaFree(d_b); // free device memory
    cudaFree(d_c); // free device memory
    cublasDestroy(handle); // destroy CUBLAS context
    gettimeofday(&time, NULL);
    elapsed_time = (((double) time.tv_sec) + ((double) time.tv_usec)/1000000) - elapsed_time;
    printf("Execution time : %lf sec.\n", elapsed_time);
    free(a); // free host memory
    free(b); // free host memory
    free(c); // free host memory
    return EXIT_SUCCESS;
}
// a:
// 11 17 23 29 35
// 12 18 24 30 36
// 13 19 25 31 37
// 14 20 26 32 38
// 15 21 27 33 39
// 16 22 28 34 40
// b:
// 11 16 21 26
// 12 17 22 27
// 13 18 23 28
// 14 19 24 29
// 15 20 25 30
// c:
// 11 17 23 29
// 12 18 24 30
// 13 19 25 31
// 14 20 26 32
// 15 21 27 33
// 16 22 28 34
// c after Sgemm :
// 1566 2147 2728 3309
// 1632 2238 2844 3450
// 1698 2329 2960 3591 // c=al*a*b+bet *c
// 1764 2420 3076 3732
// 1830 2511 3192 3873
// 1896 2602 3308 4014
