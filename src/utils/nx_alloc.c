/*
	This file contains implementations of Flite's memory allocator.
	Similar to the stdio proxy hooks, this can be used to swap out the
	memory allocator in NEXUS.

	Author: Jonathan Verbeek
	  Date: 13/10/2021
*/

//#ifdef NEXUS
#include "nx_alloc.h"
#include <stdio.h>
#include <conio.h>

// Needed to have some default declarations of these
free_t* current_free = NULL;
alloc_t* current_alloc = NULL;
calloc_t* current_calloc = NULL;
realloc_t* current_realloc = NULL;

void* cst_safe_alloc(int size)
{
	if (current_alloc)
	{
		return current_alloc(size);
	}
	else
	{
		return cst_safe_alloc_internal(size);
	}
}

void* cst_safe_calloc(int size)
{
	if (current_calloc)
	{
		return current_calloc(size);
	}
	else
	{
		return cst_safe_calloc_internal(size);
	}
}

void* cst_safe_realloc(void* p, int size)
{
	if (current_realloc)
	{
		return current_realloc(p, size);
	}
	else
	{
		return cst_safe_realloc_internal(p, size);
	}
}

void cst_free(void* p)
{
	if (current_free)
	{
		current_free(p);
	}
	else
	{
		cst_free_internal(p);
	}
}

void nx_alloc_set_free(free_t* new_free)
{
	current_free = new_free;
}

void nx_alloc_set_alloc(alloc_t* new_alloc)
{
	current_alloc = new_alloc;
}

void nx_alloc_set_calloc(calloc_t* new_calloc)
{
	current_calloc = new_calloc;
}

void nx_alloc_set_realloc(realloc_t* new_realloc)
{
	current_realloc = new_realloc;
}

//#endif
