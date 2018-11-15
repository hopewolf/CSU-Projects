#include <stdio.h>

// Parameter and result
int Needle = 4;
int *Result;

// Array definition
int Count = 7;
int Haystack[] = {14, 12, 10, 8, 6, 4, 2};

// Forward declaration
int *BinarySearch(int x, int *loAddress, int *hiAddress);

// Entry point
int main() {
  Result = BinarySearch(Needle, Haystack, Haystack + (Count - 1));
  
  // Print the result (you don't need to do this in assembly)
  if (Result)
    printf("Found at address %p (contains %d)\n", Result, *Result);
  else
    printf("Element not found!\n");
}

// Binary search recursive function
// Adapted from: http://www.cs.utsa.edu/~wagner/CS3343/recursion/binsearch.html
int *BinarySearch(int x, int *loAddress, int *hiAddress) {
  int midOffset = 0;
  int *midAddress = 0;
  
  // Base case (the element was not found)
  if (loAddress > hiAddress) return 0;
  
  // Calculate the address of the element in the middle
  midOffset = (hiAddress - loAddress) / 2;
  midAddress = loAddress + midOffset;
  
  // Have we found the element?
  if (x == *midAddress) {
    // We have found it!
    return midAddress;
  } else if (x > *midAddress) {
    // We haven't found it: continue on the lower half
    return BinarySearch(x, loAddress,hidAddress - 1);
  } else {
    // We haven't found it: continue on the upper half
    return BinarySearch(x, midAddress + 1, hiAddress);
  }
}
