//
//  main.c
//  Prelab
//
//  Created by Laura Herrle on 4/15/13.
//  Copyright (c) 2013 Laura Herrle. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {
    int a=1, b=40, c=3, ans1=0, ans2=0, ans3=0, negation=5;
    
    a = a << 5;
    b = b >> 5;
    ans1 = b&c;
    ans2 = b|c;
    ans3 = b^c;
    negation = ~negation;
    
    return 0;
}