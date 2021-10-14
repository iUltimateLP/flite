/*
	This file contains implementations of Flite's memory allocator.
	Similar to the stdio proxy hooks, this can be used to swap out the
	memory allocator in NEXUS.

	Author: Jonathan Verbeek
	  Date: 13/10/2021
*/

#pragma once
//#ifdef NEXUS

#ifdef __cplusplus
extern "C"
{
#endif

#include "cst_string.h"
#include "cst_alloc.h"

// Type definitions
typedef void (free_t)(void*); // void cst_free(void *p);
typedef void* (alloc_t)(int); // void *cst_safe_alloc(int size);
typedef void* (calloc_t)(int); // void *cst_safe_calloc(int size);
typedef void* (realloc_t)(void*, int); // void *cst_safe_realloc(void *p,int size);

// Pointers to the hooked functions that should be called
extern free_t* current_free;
extern alloc_t* current_alloc;
extern calloc_t* current_calloc;
extern realloc_t* current_realloc;

// Setter functions to set a new hook
void nx_alloc_set_free(free_t* new_free);
void nx_alloc_set_alloc(alloc_t* new_alloc);
void nx_alloc_set_calloc(calloc_t* new_calloc);
void nx_alloc_set_realloc(realloc_t* new_realloc);

#ifdef __cplusplus
}
#endif

//#endif