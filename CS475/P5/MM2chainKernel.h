#ifndef _2BY2MULTKERNEL_H_
#define _2BY2MULTKERNEL_H_

#define B 32 //number of threads per thread block
#define C 60 //number of matrices processed per thread

__global__ void multiply(const float* A, float* partial_mult );
#endif //_2BY2MULTKERNEL_H_
