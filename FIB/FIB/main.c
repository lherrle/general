//
//  fibonacci.c
//  HW3
//
//  Created by Laura Herrle on 3/13/13.
//  Copyright (c) 2013 Laura Herrle. All rights reserved.
//

#include <stdio.h>

int theArray[40];

int main() {
    int n = 2;
    theArray[0] = 1;
    theArray[1] = 1;
    
    do {
        theArray[n] = theArray[n-1] + theArray[n-2];
        n++;
    } while (n < 40);  // compute the first 40 terms
    
    return 0;
}
