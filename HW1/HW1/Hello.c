//
//  Hello.c
//  HW1
//
//  Created by Laura Herrle on 2/4/13.
//  Copyright (c) 2013 Laura Herrle. All rights reserved.
//

#include <stdio.h>
#include <string.h>

int main(void) {
	char buf[128];
    puts("What is your name?");
	fgets(buf, 128, stdin);
    
    long l = strlen(buf);
    if (l > 0 && buf[l-1] == '\n')
        buf[l-1] = '\0';
    
	printf("Hello, %s.", buf);
	return 0;
}