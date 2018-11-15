This is our test program. 

You have to source the Intel C++ compiler variables prior to compiling the test suite :

source /s/parsons/l/sys/intel/bin/iccvars.sh

Then, add your source code to the source directory, and modify main.c so that it calls your TMM function. The source code is documented, but don't hesitqte to ask if it is unclear.
Timing code (generated by AlphaZ) is provided for your convenience, but this test is mainly for correctness, not for performance.

Again: This test suite is there to assess the **correctness** of your TMM, not its performance. I advise you to choose a value of N (size of the matrices) small enough to be able to run the tests in a reasonable amount of time.

In order to compile and run the test program, just type:
make
then:
make run (which will set the correct path to libtmm.so that contains the test cases).