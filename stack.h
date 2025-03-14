#ifndef __STACK_H__
#define __STACK_H__

#include <stddef.h> /* For size_t */

typedef struct stack stack_t;


/* Creates and returns ptr to stack_t */
stack_t* Create(size_t capacity, size_t element_size);

/* Destroys the given stack by freeing its memory */
void Destroy(stack_t* stack);

/* Pushes the given value to the top of the given stack */
void Push(stack_t* stack, const void* value);

/* Removes the top value from the given stack */
void Pop(stack_t* stack);

/* Returns the top value from the given stack */
void* Peek(const stack_t* stack);

/* Returns 1 if the stack is empty, else returns 0 */
int IsEmpty(const stack_t* stack);

/* Returns the current occupied size of the stack */
size_t Size(const stack_t* stack);

/* Returns the capacity of the stack */
size_t Capacity(const stack_t* stack);



#endif
