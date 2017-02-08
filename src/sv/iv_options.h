/* -*- C++ -*-
   Delphi Delco Electronics Proprietary

   $Id: iv_options.h,v 1.1 2015/06/16 14:38:32 cvsroot Exp $

   Copyright 2003-2012 by Delphi Corporation. All Rights Reserved.
   This file contains Delphi Delco Electonics Proprietary information.
   It may not be reproduced or distributed without permission.
   Contact:  Christof Petig <christof.petig@delphi.com>
*/


#ifndef _IV_OPTIONS_H
#define _IV_OPTIONS_H


#define IV4OPT_API

#ifdef _MSC_VER
# if _MSC_VER>=1400 && _MSC_VER<=1600
#  define snprintf _snprintf_s
# else
#  define snprintf _snprintf
# endif
# if _MSC_VER>=1400
#  define strnicmp _strnicmp
#  define vsnprintf _vsnprintf
//#  define strncpy strncpy_s
# else
#  define vsnprintf _vsnprintf
# endif
# define access _access
# if _MSC_VER<=1600
# define lroundf(X) (((long int)((X) + (X > 0 ? 0.5f : -0.5f )))) 
#endif
#endif



typedef enum {MoosOptShort, MoosOptInt, MoosOptFloat,
              MoosOptChar, MoosOptStr, MoosOptBool, MoosOptEnd } MoosTypes;

# ifndef EMBEDDED_ONLY // PC based options (read from file)

// added short int options 19May99 (LRH)
typedef struct Options {
	char const* name;
	MoosTypes type;
	void *ptr;
	int optional;
	int specified;
} Options;

// returns iRC
//  CPE: This functions has a clear bug: a # inside a string terminates the string, contact me if you want this bug fixed
int  MOptionsRead(char const*fname, int* list_count, bool fQuiet);

// add options to global list
int addOptions(Options const* list);

void initOptions();

/// get explanation for error code
void Opt_GetErrorMsg(char * pErrorMsg, unsigned bufsize, int iRC);

# endif
#endif
