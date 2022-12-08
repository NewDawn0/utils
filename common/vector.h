///////////////////////////////////////////////////
// vector - A C library adding c++ sting vectors //
// Written/Copyright by NewDawn0 (Tom) 7.12.2022 //
// Code is licensed under the MIT license        //
///////////////////////////////////////////////////

// Ispired by "https://markkevinbaltazar.medium.com/lets-make-a-dynamic-array-vector-in-c-16dbe6d72a79

// include guard
#ifndef VECTOR_H
#define VECTOR_H

// definitions
#define VECTOR_INIT_LIM 5

// Vector typedef
typedef struct Vector {
    void **data;
    int limit;
    int count;
    void (*push)(struct Vector*, void*);
    void (*remove)(struct Vector*, int);
    void (*free)(struct Vector*);
} vector;

// Vector Init method
void VectorInit(vector* vector);

// include guard
#endif
