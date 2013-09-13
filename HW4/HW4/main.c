//
//  main.c
//  HW4
//
//  Created by Laura Herrle on 4/17/13.
//  Copyright (c) 2013 Laura Herrle. All rights reserved.
//

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

struct hashtable {
    int *buffer;     // pointer to allocated memory
    int buffer_size; // the max number of integers the buffer can hold
    int length;      // the number of integers stored in the table
    int puts;        // the number of puts
    int init;      // whether it is initialized
};

/* taken from http://www.cse.yorku.ca/~oz/hash.html, djb2 hash function */
unsigned long hash(int *str) {
    unsigned long hash = 5381;
    int c;
    
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    
    return hash;
}

void hashtable_create(struct hashtable *self) {
    if(self->init==1)
        exit(1);
    
    self->buffer = (int *)malloc(2*sizeof(int)*2);
    self->buffer_size = 2;
    self->length = 0;
    self->puts = 0;
    self->init = 1;
}

void hashtable_put(struct hashtable *self, int key, int value) {
    unsigned long hash_val = hash(&key);
    
    //resize if necessary (i.e. load factor >= .5 before adding new value)
    if(((double)self->length/(double)self->buffer_size)>=0.5) {
        int old = self->buffer_size;
        self->buffer_size=old*2;
        int *p=self->buffer;
        
        self->buffer=(int *)malloc(self->buffer_size*sizeof(int)*2*2);
        // check for failed allocation
        if(self->buffer==NULL) {
            if(p) free(p);
            // exit abnormally
            printf("ERROR: memory allocation failed.\n");
            abort();
        }
        
        int v, k;
        unsigned long h;
        for(int i=0; i<old*2; i+=2) {
            v = p[i];
            k = p[i+1];
            
            h = hash(&k)%self->buffer_size;
            if(v!=0) {
                while (self->buffer[2*h] != 0 && self->buffer[2*h+1] != k) {
                    h = (h+1) % (self->buffer_size);
                }
            
                self->buffer[2*h] = v;
                self->buffer[2*h+1] = k;
                self->puts=self->puts+1;
            }
        }
    }
    
    //linear probe to determine index
    hash_val = hash_val%self->buffer_size;
    while (self->buffer[2*hash_val] != 0 && self->buffer[2*hash_val+1] != key) {
        hash_val = (hash_val+1) % (self->buffer_size);
    }
    
    self->buffer[2*hash_val] = value;
    self->buffer[2*hash_val+1] = key;
    self->puts=self->puts+1;
}

int hashtable_get(struct hashtable *self, int key) {
    unsigned long hash_val = hash(&key);
    
    for(int i=0; i<self->buffer_size; i++) {
        if (self->buffer[2*(hash_val+i)%self->buffer_size+1] == key)
            return self->buffer[2*(hash_val+i)%self->buffer_size];
    }
    
    exit(1);
}

void hashtable_remove(struct hashtable *self, int key) {
    unsigned long hash_val = hash(&key);
    unsigned long start_val = self->buffer_size +1;
    
    for(int i=0; i<self->buffer_size; i++) {
        if (self->buffer[2*(hash_val+i)%self->buffer_size + 1] == key) {
            self->buffer[2*(hash_val+i)%self->buffer_size] = 0;
            self->buffer[2*(hash_val+i)%self->buffer_size + 1] = 0;
            start_val = hash_val+i+1;
        }
    }
    
    if(start_val==(self->buffer_size+1))
        exit(1);
    
    int k, v;
    
    for(int i=0; i<self->buffer_size; i++) {
        if(self->buffer[2*(hash_val+i)%self->buffer_size] == 0)
            return;
        v = self->buffer[2*(hash_val+i)%self->buffer_size];
        k = self->buffer[2*(hash_val+i)%self->buffer_size + 1];
        self->buffer[2*(hash_val+i)%self->buffer_size] = 0;
        self->buffer[2*(hash_val+i)%self->buffer_size + 1] = 0;
        hashtable_put(self, k, v);
    }
}

void hashtable_stats(struct hashtable *self) {
    printf("length = %d, N = %d, puts = %d\n", self->length, self->buffer_size, self->puts);
    printf("in stats \n");
}

int main(int argc, char *argv[]) {
    printf("seriously why isn't this working\n");
    struct hashtable a;
    
    hashtable_create(&a);
    printf("print here?\n");
    hashtable_put(&a,0,99);
    printf("before stats, after put \n");
    hashtable_stats(&a); /* prints: "length = 1, N = 2, puts = 1\n" */
    printf("after stats\n");
    hashtable_put(&a,1,42);
    hashtable_stats(&a);
    assert(hashtable_get(&a,0)==99);
    hashtable_remove(&a,0);
    hashtable_get(&a,0); /* causes program to exit with exit code 1 */
    hashtable_remove(&a,0); /* would also cause program to exit with exit code 1 */
    printf("is this working?");
    return(0);
}