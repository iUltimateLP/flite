/*
	This file contains headers of the cst_file_stdio methods,
	which can be hooked from outside the library, so the game can hook
	into them to provide it's own filesystem implementation.

	Author: Jonathan Verbeek
	  Date: 28/04/2021
*/

#pragma once
//#ifdef NEXUS

#ifdef __cplusplus
extern "C"
{
#endif

#include "cst_file.h"
#include "cst_string.h"
#include "cst_error.h"
#include "cst_alloc.h"

// Type definitions
typedef FILE* (fopen_t)(const char*, const char*); // path, mode
typedef size_t (fwrite_t)(const void*, size_t, size_t, FILE*); // fh, buf, size, count
typedef size_t (fread_t)(void*, size_t, size_t, FILE*); // fh, buf, size, count
typedef int (fgetc_t)(FILE*); // fh
typedef long (ftell_t)(FILE*); // fh
typedef long (fseek_t)(FILE*, long, int); // fh, pos, whence
typedef int (fprintf_t)(FILE*, const char* fmt, ...); // fh, fmt, ...
typedef int (fclose_t)(FILE*); // fh

// Pointers to the hooked functions that should be called
extern fopen_t* current_fopen;
extern fwrite_t* current_fwrite;
extern fread_t* current_fread;
extern fgetc_t* current_fgetc;
extern ftell_t* current_ftell;
extern fseek_t* current_fseek;
extern fprintf_t* current_fprintf;
extern fclose_t* current_fclose;

// Setter functions to set a new hook for the I/O functions
void nx_file_set_fopen(fopen_t* new_fopen);
void nx_file_set_fwrite(fwrite_t* new_fwrite);
void nx_file_set_fread(fread_t* new_fread);
void nx_file_set_fgetc(fgetc_t* new_fgetc);
void nx_file_set_ftell(ftell_t* new_ftell);
void nx_file_set_fseek(fseek_t* new_fseek);
void nx_file_set_fprintf(fprintf_t* new_fprintf);
void nx_file_set_fclose(fclose_t* new_fclose);

#ifdef __cplusplus
}
#endif

//#endif
