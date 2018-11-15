#include <stdio.h> 

///
/// MM2chainkernel01.cu
/// By Luke Burford 
/// Created: 1 Nov 2018

#define B 32 // threads per block 
#define C 60 // matracies proccessed per block 

__global__ void multiply(const float* A, float* tempoMult){ 
    int i; 
    
    
    float MxM00 = 0; 
    float MxM01 = 0; 
    float MxM10 = 0; 
    float MxM11 = 0; 
    
    float TH00 = 0; 
    float TH01 = 0; 
    float TH10 = 0; 
    float TH11 = 0; 
    
    __shared__ float SharedAMat[(B * C * 4)]; 

    #pragma unroll 
    for( i = 0 ; i < 4 * C ; ++i){ 
        SharedAMat[i*B + threadIdx.x] = A[(blockIdx.x * B *  4 * C )+  i*B + threadIdx.x]; 
    } 
    
    __syncthreads(); 
    
    
    TH00 = SharedAMat[threadIdx.x * 4 * C  + 0]; 
    TH01 = SharedAMat[threadIdx.x * 4 * C  + 1]; 
    TH10 = SharedAMat[threadIdx.x * 4 * C  + 2]; 
    TH11 = SharedAMat[threadIdx.x * 4 * C  + 3]; 
    
    #pragma unroll 
    for (i = 4 + (threadIdx.x * 4 * C) ; i < C * 4 +  (threadIdx.x * 4 * C); i+=4){ 
        MxM00 = (TH00 * SharedAMat[i])   + (TH01 * SharedAMat[i+2]); 
        MxM01 = (TH00 * SharedAMat[i+1]) + (TH01 * SharedAMat[i+3]); 
        MxM10 = (TH10 * SharedAMat[i])   + (TH11 * SharedAMat[i+2]); 
        MxM11 = (TH10 * SharedAMat[i+1]) + (TH11 * SharedAMat[i+3]); 
        TH00 = MxM00; 
        TH01 = MxM01; 
        TH10 = MxM10; 
        TH11 = MxM11; 
    } 
    
    SharedAMat[threadIdx.x * 4 * C  + 0] = TH00; 
    SharedAMat[threadIdx.x * 4 * C  + 1] = TH01; 
    SharedAMat[threadIdx.x * 4 * C  + 2] = TH10; 
    SharedAMat[threadIdx.x * 4 * C  + 3] = TH11; 

    __syncthreads(); 
    
    if (threadIdx.x == 0){ 
        #pragma unroll 
        for (i = C *  4; i < B * 4 * C; i+=C * 4){ 
            MxM00 = (TH00 * SharedAMat[i])   + (TH01 * SharedAMat[i+2]); 
            MxM01 = (TH00 * SharedAMat[i+1]) + (TH01 * SharedAMat[i+3]); 
            MxM10 = (TH10 * SharedAMat[i])   + (TH11 * SharedAMat[i+2]); 
            MxM11 = (TH10 * SharedAMat[i+1]) + (TH11 * SharedAMat[i+3]); 
            TH00 = MxM00; 
            TH01 = MxM01; 
            TH10 = MxM10; 
            TH11 = MxM11; 
        } 
        tempoMult[0 + blockIdx.x * 4] = TH00; 
        tempoMult[1 + blockIdx.x * 4] = TH01; 
        tempoMult[2 + blockIdx.x * 4] = TH10; 
        tempoMult[3 + blockIdx.x * 4] = TH11; 
    }   
}
