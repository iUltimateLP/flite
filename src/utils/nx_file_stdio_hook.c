/*
	This file contains implementations of the cst_file_stdio methods,
	which can be hooked from outside the library, so the game can hook
	into them to provide it's own filesystem implementation.

	Author: Jonathan Verbeek
	  Date: 28/04/2021
*/

//#ifdef NEXUS
#include "nx_file_stdio_hook.h"

// Needed to have some default declarations of these
fopen_t* current_fopen = NULL;
fwrite_t* current_fwrite = NULL;
fread_t* current_fread = NULL;
fgetc_t* current_fgetc = NULL;
ftell_t* current_ftell = NULL;
fseek_t* current_fseek = NULL;
fprintf_t* current_fprintf = NULL;
fclose_t* current_fclose = NULL;

FILE* cst_fopen(const char* path, int mode)
{
	char cmode[4];

	if (cst_urlp(path))
		return cst_url_open(path);
	else if ((mode & CST_OPEN_WRITE) && (mode & CST_OPEN_READ))
		strcpy(cmode, "r+");
	else if ((mode & CST_OPEN_APPEND) && (mode & CST_OPEN_READ))
		strcpy(cmode, "a+");
	else if (mode & CST_OPEN_WRITE)
		strcpy(cmode, "w");
	else if (mode & CST_OPEN_APPEND)
		strcpy(cmode, "a");
	else if (mode & CST_OPEN_READ)
		strcpy(cmode, "r");

	/* Windows likes to make a distinction between binary and not */
	/* While other operating systems do not -- we're going to always */
	/* treat files as binary, because the non-binary Windows case is */
	/* never what we want */
	strcat(cmode, "b");

	if (current_fopen)
	{
		return current_fopen(path, cmode);
	}
	else
	{
		return fopen(path, cmode);
	}
}

long cst_fwrite(FILE* fh, const void* buf, long size, long count)
{
	if (current_fwrite)
	{
		return (long)current_fwrite(buf, size, count, fh);
	}
	else
	{
		return fwrite(buf, size, count, fh);
	}
}

long cst_fread(FILE* fh, void* buf, long size, long count)
{
	if (current_fread)
	{
		return (long)current_fread(buf, size, count, fh);
	}
	else
	{
		return fread(buf, size, count, fh);
	}
}

long cst_filesize(FILE* fh)
{
	/* FIXME: guaranteed to break on text files on Win32 */
	long pos, epos;

	if (current_fseek && current_ftell)
	{
		pos = current_ftell(fh);
		current_fseek(fh, 0, SEEK_END);
		epos = current_ftell(fh);
		current_fseek(fh, pos, SEEK_SET);
	}
	else
	{
		pos = ftell(fh);
		fseek(fh, 0, SEEK_END);
		epos = ftell(fh);
		fseek(fh, pos, SEEK_SET);
	}

	return epos;
}

int cst_fgetc(FILE* fh)
{
	if (current_fgetc)
	{
		return current_fgetc(fh);
	}
	else
	{
		return fgetc(fh);
	}
}

long cst_ftell(FILE* fh)
{
	if (current_ftell)
	{
		return current_ftell(fh);
	}
	else
	{
		return ftell(fh);
	}
}

long cst_fseek(FILE* fh, long pos, int whence)
{
	int w = 0;

	if (whence == CST_SEEK_ABSOLUTE)
		w = SEEK_SET;
	else if (whence == CST_SEEK_RELATIVE)
		w = SEEK_CUR;
	else if (whence == CST_SEEK_ENDREL)
		w = SEEK_END;

	if (current_fseek)
	{
		current_fseek(fh, pos, w);
	}
	else
	{
		fseek(fh, pos, w);
	}

	if (current_ftell)
	{
		return current_ftell(fh);
	}
	else
	{
		return ftell(fh);
	}
}

int cst_fprintf(FILE* fh, const char* fmt, ...)
{
	if (current_fprintf)
	{
		va_list args;
		int rv;

		va_start(args, fmt);
		rv = current_fprintf(fh, fmt, args);
		va_end(args);

		return rv;
	}
	else
	{
		va_list args;
		int rv;

		va_start(args, fmt);
		rv = vfprintf(fh, fmt, args);
		va_end(args);

		return rv;
	}
}

int cst_sprintf(char* s, const char* fmt, ...)
{
	// Don't need any special handling here, so this is copied from cst_file_stdio.c

	va_list args;
	int rv;

	va_start(args, fmt);
	rv = vsprintf(s, fmt, args);
	va_end(args);

	return rv;
}

int cst_fclose(FILE* fh)
{
	if (current_fclose)
	{
		return current_fclose(fh);
	}
	else
	{
		return fclose(fh);
	}
}

void nx_file_set_fopen(fopen_t* new_fopen)
{
	current_fopen = new_fopen;
}

void nx_file_set_fwrite(fwrite_t* new_fwrite)
{
	current_fwrite = new_fwrite;
}

void nx_file_set_fread(fread_t* new_fread)
{
	current_fread = new_fread;
}

void nx_file_set_fgetc(fgetc_t* new_fgetc)
{
	current_fgetc = new_fgetc;
}

void nx_file_set_ftell(ftell_t* new_ftell)
{
	current_ftell = new_ftell;
}

void nx_file_set_fseek(fseek_t* new_fseek)
{
	current_fseek = new_fseek;
}

void nx_file_set_fprintf(fprintf_t* new_fprintf)
{
	current_fprintf = new_fprintf;
}

void nx_file_set_fclose(fclose_t* new_fclose)
{
	current_fclose = new_fclose;
}

//#endif
