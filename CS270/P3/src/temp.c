#include "Debug.h"
#include "iFloat.h"

/** @file iFloat.c
 *  @brief You will modify this file and implement nine functions
 *  @details Your implementation of the functions defined in iFloat.h.
 *  You may add other function if you find it helpful. Added function
 *  should be declared <b>static</b> to indicate they are only used
 *  within this file.
 *  <p>
 *  @author <b>Luke Burford </b> goes here
 */

/* declaration for useful function contained in testFloat.c */
const char* getBinary (iFloat_t value);

iFloat_t floatGetSign (iFloat_t x) {
    /* shifts 1 to most significant bit (sign bit) gets sign bit of x, shifts back to least significant bit, and returns */
    return ((x & (1 << 15)) >> 15); 
}

iFloat_t floatGetExp (iFloat_t x) {
    /* get the exponent bits (hi=14 lo=10) shift it back to least significant bit */
    // exponent mask is 0x7C00
    return ((x & 0x7C00) >> 10);
}

iFloat_t floatGetVal (iFloat_t x) {
    /* gets the bits of the mantissa, sets the implicit 1, then checks if floating number x is negative, if so take the 2's compliment of it (-someInt) gives you the 2's compliment or (~someInt + 1) does too */
    //mantissa mask is 0x3FF
    iFloat_t mantissa = ((x & 0x3FF) | 0x400);
    if(floatGetSign(x) > 0)
        mantissa = ~mantissa + 1;
    return mantissa;
}

void floatGetAll(iFloat_t x, iFloat_t* sign, iFloat_t*exp, iFloat_t* val) {
    /* gets the sign, exponent, and value of the float and assigns them all to pointer parameters */
    *sign = floatGetSign(x);
    *exp = floatGetExp(x);
    *val = floatGetVal(x);
}


iFloat_t floatLeftMost1 (iFloat_t bits) {
//    debug("%s: bits of the int (IEE 754)", getBinary(bits));
    if(bits != 0) {
        for(int i=15; i>=0; i--) {
            if(((bits & (1 << i)) >> i) == 1) {
//                debug("Sucsess! 1 found at bit %d", i);
                return i;
            }
//            debug("No 1 in bit %d", i);
        }
    }
    return -1;
}

iFloat_t floatAbs (iFloat_t x) {
    /* uses binary & operator to clear most significant bit */
    return (x & 0x7FFF);
}

iFloat_t floatNegate (iFloat_t x) {
    /* sets the sign bit to 1, setting the float as a negative */
//    debug("%s: bits of x before negate (IEEE 754)", getBinary(x));
//    debug("%s: bits of x after negate (IEEE 754)", getBinary(x | (1 << 15)));
    if(x != 0)
        return (x | (1 << 15));
    return x;
}


iFloat_t floatAdd (iFloat_t x, iFloat_t y) {
    if((x == 0) && ( == 0)) {
        debug("Both x and y are zero, return 0");
        return 0;
    }
    /* declaration for the components of the floats */
    iFloat_t signX; iFloat_t expX; iFloat_t valX; // float x components
    iFloat_t signY; iFloat_t expY; iFloat_t valY; // float y components
    /* --STEP 1: Extract-- */
    /* initalize the variables for both floats */
    floatGetAll(x, &signX, &expX, &valX);
    floatGetAll(y, &signY, &expY, &valY);
    debug("STEP 1");
    /* --STEP 2: Equalize the exponents-- */
    iFloat_t expR = expX;
    if(expX > expY) {
        valY = valY >> (expX - expY);
        expR = expX;
    }
    else if(expX < expY) {
        expR = expY;
        valX = valX >> (expY - expX);
    }
    debug("STEP 2");
    /* --STEP 3: Integer addition-- */
    iFloat_t valR = valX + valY;
    debug("STEP 3");
    if(valR == 0){
        return 0;
    }
    /* --STEP 4: Convert the two's compliment bact to sign magnitude-- */
    debug("STEP 4");
    int signR = 0;
    if(floatGetSign(valR) > 0) {
        signR = 1;
        valR = ~valR + 1;
    }
    /* --STEP 5: Normalize result-- */
    debug("STEP 5");
    if(floatLeftMost1(valR) < 10) {
        expR = expR - (10 - floatLeftMost1(valR));
        valR = valR << (10 - floatLeftMost1(valR));
    }
    else if(floatLeftMost1(valR) > 10) {
        expR = expR + (floatLeftMost1(valR) - 10);
        valR = valR >> (floatLeftMost1(valR) - 10);
    }
    /* --STEP 6: Re-assemble all the componets of the result into a 16-bit value-- */
    debug("STEP 6");
    iFloat_t normR;
    valR = valR ^ 0x400;
    expR = expR << 10;
    signR = signR << 15;
    normR = signR | expR | valR;
    return normR;
}

iFloat_t floatSub (iFloat_t x, iFloat_t y) {
    return floatAdd(x, floatNegate(y));
}

