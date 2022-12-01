#include <stdlib.h>
#include "vector.h"

// source "https://markkevinbaltazar.medium.com/lets-make-a-dynamic-array-vector-in-c-16dbe6d72a79"

// Push
void vectorPush(Vector* self, void* data) {
    // resize if full
    if (self->count == self->limit) {
        self->limit = self->limit+1;
        self->data = realloc(self->data, sizeof(void*) *self->limit);
    }
    // add data
    self->data[self->count] = data;
    self->count ++;
}
// remove
void vectorRemove(Vector* self, int index) {
    if (index > -1 && index < self->count) {
        // swap the last item to the index to be removed
        // then remove the last item
        self->data[index] = self->data[self->count-1];
        self->data[self->count-1] = NULL;
        self->count --;
    }
}
// delete
void vectorFree(Vector* self) {
    if (self->data) {
        free(self->data);
        self->data = NULL;
    }
}
// init
void vectorInit(Vector* vector) {
    vector->limit = VECTOR_INIT_LIM;
    vector->count = 0;
    vector->push = vectorPush;
    vector->remove = vectorRemove;
    vector->free = vectorFree;
    vector->data = malloc(sizeof(void*) * vector->limit);
}
