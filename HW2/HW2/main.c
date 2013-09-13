//
//  main.c
//  HW2
//
//  Created by Laura Herrle on 2/19/13.
//  Copyright (c) 2013 Laura Herrle. All rights reserved.
//

#include<stdio.h>
#include<stdlib.h>

struct arraylist {
    int *buffer;     // pointer to allocated memory
    int buffer_size; // the max number of integers the buffer can hold
    int length;      // the number of integers stored in the list
};

void arraylist_add(struct arraylist *a, int x) {
    if(a->length==a->buffer_size) {
        int *temp;
        temp = realloc(a->buffer, (a->buffer_size+1)*2);
        
        a->buffer = temp;
        a->buffer_size=(a->buffer_size+1)*2;
    }
    
    a->buffer[a->length] = x;
    a->length++;
}

void arraylist_remove(struct arraylist *a, int index) {
    int i;
    
    for(i=index;i<a->length-1;i++) a->buffer[i]=a->buffer[i+1];
    a->length=a->length-1;
}

int arraylist_get(struct arraylist *a, int index) {
    return(a->buffer[index]);
}

int main(int argc, char *argv[]) {
    struct arraylist a;
    int i,j;
    
    a.buffer=NULL;
    a.buffer_size=0;
    a.length=0;
    for(i=1;i<argc;i++) {
        j=atoi(argv[i]);
        if(j<0) arraylist_remove(&a,-j-1);
        else arraylist_add(&a,j);
    }
    
    for(i=0;i<a.length;i++) printf("%d, ",arraylist_get(&a,i));
    printf("\n");

    if(a.buffer!=NULL) free(a.buffer);
    return(0);
}