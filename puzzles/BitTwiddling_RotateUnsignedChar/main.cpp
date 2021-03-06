#include <iostream>
#include <stdio.h>
using namespace std;

/**
 
 eg:
 0x13 ==> 0001 0011
 temp ==> 0110 0000 -\ ORR
 x    ==> 0000 0010 -/
 o/p  ==> 0110 0010
 */

unsigned char rotateRight(unsigned char x, int n){
    
    unsigned char temp = x;
    temp = temp << (8-n);   // left-shift the bits that would otherwise be lost
    x = x >> n;             // right-shift by n
    return (x | temp);      // or the two
}

unsigned char rotateLeft(unsigned char x, int n){
    
    unsigned char temp = x;
    temp = temp >>(8-n);   // right-shift the bits that would otherwise be lost
    x = x << n;             // left-shift by n
    return (x | temp);      // or the two
}



// driver program to test above function
int main()
{
    int x = 0x13;
    printf("%x\n", x);
    printf("%x\n", rotateRight(x, 3));
    x = 0x4;
    printf("%x\n", x);
    printf("%x\n", rotateLeft(x, 6));

    
    return 0;
}