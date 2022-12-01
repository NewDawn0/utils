#define VECTOR_INIT_LIM 5
typedef struct Vector {
    void **data;
    int limit;
    int count;
    void (*push)(struct Vector*, void*);
    void (*remove)(struct Vector*, int);
    void (*free)(struct Vector*);
} Vector;
void VectorInit(Vector* vector);
// source "https://markkevinbaltazar.medium.com/lets-make-a-dynamic-array-vector-in-c-16dbe6d72a79"
