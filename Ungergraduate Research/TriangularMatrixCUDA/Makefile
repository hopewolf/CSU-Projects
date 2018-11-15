CC=g++
NVCC=nvcc
CXXFLAGS= -fopenmp -O3 -Wextra -std=c++11
CUDAFLAGS= -std=c++11 -c -arch=sm_20
LIBS= -lopenblas -lpthread -lcudart -lcublas
LIBDIRS=-L/usr/local/cuda-7.5/lib64
INCDIRS=-I/usr/local/cuda-7.5/include
GPUMatrixMult.o: GPUMatrixMult.cu
	$(NVCC) $(CUDAFLAGS)  GPUMatrixMult.cu
all: GPUMatrixMult.o
	$(CC) -o test matrix_blas.cpp alg.cpp test.cpp GPUMatrixMult.o $(LIBDIRS) $(INCDIRS) $(LIBS) $(CXXFLAGS)
clean:
	rm -rf test *.o
