#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>

struct arraylist {
    // update if necessary
    int *buffer;     // pointer to allocated memory
    int buffer_size; // the max number of integers the buffer can hold
    int length;      // the number of integers stored in the list
    int sum;        // the sum of the elements in the buffer
};

void arraylist_add(struct arraylist *a, int x) {
    // check inputs
    if(a==NULL) {abort();}
    if(a->buffer_size <= a->length) {
        // initial size is 2 otherwise double the size
        a->buffer_size=(a->buffer_size < 1 ? 2 : a->buffer_size*2);
        // keep a pointer to the old block￼
        int *p = a->buffer;
        // allocate or reallocate memory block
        a->buffer=(int *)realloc(a->buffer,a->buffer_size*sizeof(int));
        // check for failed allocation
        if(a->buffer==NULL) {
            // free old block if necessary
            if(p) free(p);
            // exit abnormally
            printf("ERROR: memory allocation failed.\n");
            abort(); }
    }
    // append element
    a->buffer[a->length]=x;
    // increment array length
    a->length=a->length+1;
    a->sum=a->sum+x;
}

void arraylist_remove(struct arraylist *a, int index) {
    if(a==NULL) {abort();}
    int i;
    
    a->sum = a->sum-a->buffer[index];
    
    for(i=index;i<a->length-1;i++) a->buffer[i]=a->buffer[i+1];
    a->length=a->length-1;
}

int arraylist_get(struct arraylist *a, int index) {
    if(a==NULL) {abort();}
    return(a->buffer[index%a->length]);
}

void arraylist_insert(struct arraylist *a, int index, int x) {
    if(a==NULL) {abort();}
    if(a->buffer_size <= a->length) {
        a->buffer_size=(a->buffer_size < 1 ? 2 : a->buffer_size*2);
        int *p = a->buffer;
        a->buffer=(int *)realloc(a->buffer,a->buffer_size*sizeof(int));
        if(a->buffer==NULL) {
            if(p) free(p);
            printf("ERROR: memory allocation failed.\n");
            abort(); }
    }
    
    for (int i=a->length; i>index%a->buffer_size; i--) {
        a->buffer[i]=a->buffer[i-1];
    }
    a->buffer[index%a->buffer_size]=x;
    a->length = a->length+1;
    a->sum = a->sum + x;
}

struct arraylist arraylist_new() {
    struct arraylist a;
    a.buffer = NULL;
    a.buffer_size = 0;
    a.length = 0;
    a.sum = 0;
    
    return a;
}

struct arraylist arraylist_copy(struct arraylist *a) {
    if(a==NULL) {abort();}
    struct arraylist copy;
    copy.buffer_size = a->buffer_size;
    copy.length = a->length;
    copy.sum = a->sum;
    copy.buffer=(int *)malloc(a->buffer_size*sizeof(int));
    memcpy(copy.buffer, a->buffer, a->buffer_size*sizeof(int));

    return copy;
}

void arraylist_free(struct arraylist *a) {
    if(a==NULL) {abort();}
    a->sum=0;
    a->length=0;
    a->buffer_size=0;
    if(a->buffer) free(a->buffer);
}

double arraylist_mean(struct arraylist *a) {
    if(a==NULL) {abort();}
    
    return((double)a->sum/a->length);
}

void arraylist_print(struct arraylist *a) {
    printf("[");
    if (a->length > 0) {
        for(int i = 0; i < a->length-1; i++)
            printf("%d, ",arraylist_get(a,i));
        printf("%d", arraylist_get(a,a->length-1));
    }
    
    printf("]\n");
    //printf("] %f\n", arraylist_mean(a));
}



int main(int argc, char *argv[]) {
    // START OF TEST
    struct arraylist a = arraylist_new();
    
    arraylist_add(&a, 0);
    arraylist_add(&a, 1);
    arraylist_add(&a, 2);
    arraylist_print(&a);
    
    struct arraylist b = arraylist_copy(&a);
    arraylist_print(&b);
    
    arraylist_add(&a, 3);
    arraylist_add(&b, 300);
    arraylist_print(&a);
    arraylist_print(&b);
    
    printf("Clean: ");
    arraylist_print(&a);
    for (int i = 0; i < a.length + 1; i++) {
        arraylist_insert(&a, i, 100);
        printf("Insert position %d: ", i);
        arraylist_print(&a);
        arraylist_remove(&a, i);
    }
    printf("Clean: ");
    arraylist_print(&a);
    
    printf("Mean is: %f\n", arraylist_mean(&a));
    
    arraylist_free(&a);
    arraylist_free(&b);
    // END OF TEST
    
    return 0;
}
