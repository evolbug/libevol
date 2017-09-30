/*
   evolbug - 2017, MIT license
   vector/dynamic array implementation
*/



#ifndef EVOLBUG_VECTOR
#define EVOLBUG_VECTOR



#include "strace/strace.h"
#include "except/except.h"
#include "garbage/gm.h"



const Exception
(
   VECTOR_UNINITIALIZED,
   "vector [\033[1;32m%s\033[0m] not initialized with [\033[1;34mv_new()\033[0m]"
);

const Exception
(
   VECTOR_EMPTY,
   "vector [\033[1;32m%s\033[0m] is empty"
);

const Exception
(
   VECTOR_INDEX_OUT_OF_RANGE,
   "index [\033[1;32m%s\033[0m[\033[1;34ms\033[0m]\033[0m] is out of range"
);



struct Vector
{
   unsigned length;
   void* data;
};


#define V_DATAP(struct) ((void*)((unsigned*)struct + 1))
#define V_REALP(data) ((struct Vector*)((unsigned*)data - 1))

#define V_CHK_PTR(v)    ({if (!v) throw(VECTOR_UNINITIALIZED, #v)})
#define V_CHL_LEN(v)    ({if (!v->length) throw(VECTOR_EMPTY, #v)})
#define V_CHK_IDX(v, i) ({if (i >= v->length) throw(VECTOR_INDEX_OUT_OF_RANGE, #v, #i)})



#define v_length(v) (V_CHK_PTR(v), st_call(V_REALP(vector)->length))


void* v_new ()
#define v_new () st_call(v_new())
{
   struct Vector *vector = alloc(sizeof(struct Vector));
   *vector = (struct Vector){0};
   return V_DATAP(vector);
}

#define v_insert(index, vector, ...) ({ \
   st_push(v_insert(index, vector, ##__VA_ARGS__));\
\
   V_CHK_PTR(vector);\
   struct Vector *v = V_REALP(vector);\
   V_CHK_LEN(v);\
   V_CHK_IDC(v, count);\
\
   __typeof__(vector[0]) temp[] = {__VA_ARGS__};\
   unsigned count = sizeof(temp)/sizeof(vector[0]);\
\
   vector = V_DATAP((v = grealloc(V_REALP(vector),\
      sizeof(struct Vector) + sizeof(vector[0]) * v->length + count + 1)));\
\
   for (unsigned i = index; i < v->length; i++) vector[i + count] = vector[i];\
   v->length += count;\
   for (unsigned i = 0; i < count; i++) vector[i + index] = temp[i];\
\
   st_pop(); })

#define v_push(vector, ...) v_insert(V_REALP(vector)->length, vector, __VA_ARGS__)


#define v_remove(vector, index) ({\
   st_push(v_pop(vector));\
\
   V_CHK_PTR(vector);\
   struct Vector *v = V_REALP(vector);\
   V_CHK_LEN(v);\
   V_CHK_IDX(v, index);\
\
   __typeof__(vector[0]) r = vector[index];\
   v->length--;\
   for (unsigned i = index; i <= v->length; i++) vector[i] = vector[i+1];\
\
   vector = V_DATAP(grealloc(V_REALP(vector),\
      sizeof(struct Vector) + sizeof(vector[0]) * v->length));\
\
   st_pop();\
   r; })

#define v_pop(vector) v_remove(vector, V_REALP(vector)->length-1)


#undef V_DATAP
#undef V_REALP
#undef V_CHK_PTR
#undef V_CHL_LEN
#undef V_CHK_IDX



#endif
