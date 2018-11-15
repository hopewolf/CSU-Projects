/*
 *  file name: BlockingMat.cu
 *  NOTE: 
 *       squareMatrixMult is much more efficent than the regular multiplier
 *       currently compiling with: nvcc TilingMatrix.cu -o tileTest
 *       Device Standards for: GeForce GTX 1060 6GB
 *          total global mem size: 6078 MBytes (6373572608 bytes)
 *          total shared mem per block: 49.152 KBytes (49152 bytes)
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <sys/time.h>
#include <stdlib.h>

#include <sys/time.h>     //measuring performance data

#define BLOCK_SIZE 32


/**********************************************************************
function name: main
description: test and compare
parameters: 
            none
return: none
**********************************************************************/
int main(int argc, char** argv) {
    int m=4;
    int n=4;
    int k=4;

    // Allocate memory in host RAM
    float *copyA, *copyB, *copyC;
    cudaMallocHost((void**) &copyA, sizeof(float)*m*n); // copied matrix is m x n
    cudaMallocHost((void**) &copyB, sizeof(float)*n*k); // copied matrix is n x k
    cudaMallocHost((void**) &copyC, sizeof(float)*m*k); // copied matrix is m x k
    
    // float x = (float)rand()/(float)(RAND_MAX/a);
    // random initialize matrix A
    float val = 1;
    for (int i = 0; i < m; ++i) {
        for (int j = i; j < n; ++j) {
//             copyA[i * n + j] =((float)rand()/(float)(RAND_MAX)) * 1024;
            copyA[i * n + j] = val;
            ++val;
        }
    }
    val = 1;
    // random initialize matrix B
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < k; ++j) {
            copyB[i * k + j] = val;
            ++val;
        }
    }
    
    // Allocate memory space on the device 
    float *matA, *matB, *matC;
    cudaMalloc((void**) &matA, sizeof(float)*m*n); // matrix is m x n
    cudaMalloc((void**) &matB, sizeof(float)*n*k); // matrix is n x k
    cudaMalloc((void**) &matC, sizeof(float)*m*k); // matrix is m x k
    
    // copy matrix A and B from host to device memory
    cudaMemcpy(matA, copyA, sizeof(float)*m*n, cudaMemcpyHostToDevice);
    cudaMemcpy(matB, copyB, sizeof(float)*n*k, cudaMemcpyHostToDevice);
    
    printf("size of matA %dX%d: %zu bytes\n", m,n,(sizeof(float)*m*n));
    printf("size of matB %dX%d: %zu bytes\n", n,k,(sizeof(float)*n*k));
    printf("size of matC %dX%d: %zu bytes\n", m,k,(sizeof(float)*m*k));
    printf("total bytes allocated to mem: %zu bytes ", ((sizeof(float)*m*n)+(sizeof(float)*n*k)+ (sizeof(float)*m*k)));
    printf("(~%zu MBytes)\n\n", (((sizeof(float)*m*n)+(sizeof(float)*n*k)+(sizeof(float)*m*k)) / 1000000)); // get megabytes of the allocated arrays

    
    //prints the matricies
    // printf("[%d][%d]:%d, ", i, j, copyC[i*k + j]); //Another possible way to print the matrix
    //if the debug flag is on it will print the first two product arrays as well
    int i,j;
    // print matrix A
    printf("matA matrix: \n");
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            //printf("[%d][%d]:%d, ", i, j, copyA[i*k + j]);
            printf(" %f ", copyA[i*k + j]);
        }
        printf("\n");
    }
    // print matrix B
    printf("\nmatB matrix: \n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < k; j++) {
            //printf("[%d][%d]:%d, ", i, j, copyB[i*k + j]);
            printf(" %f ", copyB[i*k + j]);
        }
        printf("\n");
    }
    
    // print result matrix
    printf("\nResult matrix: \n");
    for (i = 0; i < m; i++) {
        for (j = 0; j < k; j++) {
            //printf("[%d][%d]:%d, ", i, j, copyC[i*k + j]);
            printf(" %f ", copyC[i*k + j]);
        }
        printf("\n");
    }
    
    // free memory
    cudaFree(matA);
    cudaFree(matB);
    cudaFree(matC);
    cudaFreeHost(copyA);
    cudaFreeHost(copyB);
    cudaFreeHost(copyC);
    return 0;
}
