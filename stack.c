/*
Omri Naor
Created: 27/01/2025
Last Update: 27/01/2025

Albert Molcho
Review Date: 27/01/2025
*/

#include <stdlib.h> /* For malloc */
#include <assert.h> /* For assert */
#include <stdio.h> /* For perror */
#include <string.h> /* For memcpy */
#include "stack.h"

#define ARRAY_START ((char *)(stack + 1)) 

struct stack
{
	size_t capacity;
	size_t element_size;
	size_t index;
};

stack_t* Create(size_t capacity, size_t element_size)
{
	stack_t* stack = (stack_t*) malloc (sizeof(stack_t) + element_size * capacity); /* Memory for both the strack and the 'hidden' array */
	
	assert(0 != capacity && 0 != element_size);
	
	if (NULL == stack)
	{
		perror("Failed to allocate memory\n");
		return (NULL);
	}
	stack->capacity = capacity;
	stack->index = 0;
	stack->element_size = element_size;
	
	return stack;
}


void Destroy(stack_t* stack)
{
	assert(NULL != stack);
	
	free (stack);
	stack = NULL;
}

void Push(stack_t* stack, const void* value)
{
	void* tmp = NULL;
	assert(NULL != stack && stack->index != stack->capacity);
	
	tmp = ARRAY_START + (stack->index * stack->element_size); /* Gets to next free index of the 'hidden' array */
	memcpy(tmp, value, stack->element_size);
	++stack->index;
}

void Pop(stack_t* stack)
{
	assert(NULL != stack && 0 != stack->index);
	--stack->index;
}

void* Peek(const stack_t* stack)
{
	void* tmp = ARRAY_START + (stack->index - 1) * stack->element_size;
	assert(NULL != stack && 0 != stack->index);
	return 0 == stack->index ? (NULL) : (tmp);	
}

int IsEmpty(const stack_t* stack)
{
	assert(NULL != stack);
	return (0 == stack->index);
}

size_t Size(const stack_t* stack)
{
	assert(NULL != stack);
	return (stack->index);
}

size_t Capacity(const stack_t* stack)
{
	assert(NULL != stack);
	return (stack->capacity);
}
