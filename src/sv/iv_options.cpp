/* -*- C++ -*-
   Delphi Delco Electronics Proprietary

   $Id: iv_options.cpp,v 1.1 2015/06/16 14:38:32 cvsroot Exp $

   Copyright 2003 by Delphi Corporation. All Rights Reserved.
   This file contains Delphi Delco Electonics Proprietary information.
   It may not be reproduced or distributed without permission.
   Contact:   
*/
//#include "globals.h"	// Defines and Constants of LDW

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>   // for toupper
#include <assert.h>

#include "iv_options.h"
#ifndef _MAX_PATH
# include <stdlib.h>
#endif

// implementation details removed from the header file
#define RC_CFG_OK	0
#define RC_CFG_ITEM_NOT_FOUND	-1
#define RC_CFG_STRING_QUOTES_MISSING	-13
#define RC_CFG_OPEN_NOT_POSSIBLE		-14
#define RC_CFG_SYNTAX_ERROR				-15
#define RC_CFG_SYNTAX_ERROR_MISSING_DBLPOINT -16


#define FIELD_SEPARATOR			':'
#define FIELD_SEPARATOR_STRING	":"
#define COMMENT_CHAR			'#'
#define QUOTES					"'\""


////////////////////////// implementation //////////////////////////

#ifdef linux
static char* _itoa(int value, char *string, int radix)
{
	assert(radix==10);
	sprintf(string, "%d", value);
	return string;
}
//#define stricmp strcasecmp
#endif


#define MAX_LINE_LEN   250

#define MAX_OPTLIST_SIZE 1024

static Options iv_optlist[MAX_OPTLIST_SIZE] = {
   {NULL}
};

Options *get_options_list() { return iv_optlist; }
// add Options at runtime
int addOptions(Options const* list)
{
	unsigned used_elements=0;
	for (;iv_optlist[used_elements].name;++used_elements);
	unsigned listlen=0;
	for (;list[listlen].name;++listlen);
	assert(used_elements+listlen<MAX_OPTLIST_SIZE);
	if ( used_elements+listlen<MAX_OPTLIST_SIZE )
	{
		memcpy(iv_optlist+used_elements, list, (listlen+1)*sizeof(list[0]));
		return listlen;
	}
	else
	{
		return -1;
	}
}

void initOptions()
{
	iv_optlist[0].name = NULL;
}

#undef LACKSISSPACE
#ifdef _MSC_VER
# define LACKSSTRCASE
#endif
//#define CASESENSITIVE 
#ifdef CASESENSITIVE
#define STRCMP strcmp
#define STRNCMP strncmp
#else
#define STRCMP strcasecmp
#define STRNCMP strncasecmp
#endif


#ifdef LACKSISSPACE
static int isspace(char c)  {return ((c ==' ')|| (c =='\t'));  }
#endif

#ifdef LACKSSTRCASE
int
strcasecmp(const char *s1, const char *s2)
{
  while(*s1 && *s2 && toupper(*s1) == toupper(*s2))
    { s1++; s2++; }

  return (int)*s1 - (int)*s2;
}

int
strncasecmp(const char *s1, const char *s2,int n)
{
  if(n==0) return 0;
  
  while(--n && *s1 && *s2 && toupper(*s1) == toupper(*s2))
    { s1++; s2++; }

  return (int)toupper(*s1) - (int)toupper(*s2);
}
#endif

//static char const*sep;

/* Remove the trailing spaces and trailing comment. Yes, i didn't want to
   come up with a name for this, nor did i want to splice it in the middle
   of the main parser function.
*/
static char *
clearDaDamnTrailingSpaces(char *p)
{
  char *v;

  /* Poke out the string at a a comment char if there is one. */
  if((v = strchr(p, COMMENT_CHAR))!=NULL)
    *v = '\0';

  for(v = p+strlen(p)-1; v>p && isspace(*v) ; --v)
    *v = '\0';

  return p;
}


static char *
skipspaces(char *s)
{
  while(*s && isspace(*s))++s;

  return s;
}


/* Advances the pointer to the end of the net token.
   For now, a token is delimited by white spaces or by the field
   separator..
*/
static char*
skipToken(char *s)
{
  s = skipspaces(s);
  while(*s && *s!=FIELD_SEPARATOR && !isspace(*s))++s;

  return s;
}

static int
isin(char c,char const* lst)
{
  while(*lst &&  c!=*lst)lst++;

  return *lst;
}


/* Sets the option name optname to value val. Converts
   val to the proper type.
*/
//RJ: use global iv_optlist, so optlist is not required as a parameter
static int
SetValue(
	// Options *optlist,
	 char const	*optname,
	 char	*val,
	 int	line_num,
	 char const	*fname,
	 bool	fQuiet
)
{
  int iOK = RC_CFG_OK;    // 1 == ok
  Options *op;

  // options might appear multiple times, so we have to scan the whole list
  bool found=false;
  for(op = iv_optlist; op->name && iOK == RC_CFG_OK; ++op)
  {
	if (!STRCMP(op->name, optname))
	{
		// op now is the correct option
		switch(op->type)
		{
			case MoosOptShort:
				*((short int *)op->ptr) = (short int) atoi(val);
				break;
			case MoosOptInt:
				*((int *)op->ptr) = atoi(val);
				break;
			case MoosOptFloat:
				*((float *)op->ptr) = (float) atof(val);
				break;
			case MoosOptChar:
			case MoosOptStr:
			{
				int vlen = (int)(strlen(val)-1);
				if(!isin(val[0], QUOTES) || !isin(val[vlen], QUOTES))
				{
					if (!fQuiet)
					{
						char str[1024];
						snprintf(str, sizeof(str), "String value for \"%s\", on line %d of file \"%s\" must be enclosed within quotes.\n",
								op->name, line_num, fname); // , val);
//						infr_ptr->DisplayError(str, false);
					}
					iOK = RC_CFG_STRING_QUOTES_MISSING;
				}
				char *val2 = val, oldend=val[vlen];
				val2[vlen] = '\0';
				++val2;
				if(op->type==MoosOptChar)
					*((char *)op->ptr) = *val2;
				else
				{
					if (op->optional)
					{
						strncpy((char *)op->ptr, val2, op->optional);
						if (vlen >= op->optional)
							((char *)op->ptr)[op->optional] = '\0';  // truncate the string
					}
					else
					{
						if (!fQuiet)
						{
							char str[1024];
							snprintf(str, sizeof(str), "\noptlist.optional not initialized for option %s ... skipping\n", op->name);
//							infr_ptr->DisplayError(str, false);
						}
					}
				}
				// restore old value with quotes
				val[vlen]= oldend;
			}
				break;
			case MoosOptBool:
			{
				bool v = false;
				if(*val=='1' || toupper(*val)=='T')
					v = true;
				else if(*val=='0' || toupper(*val)=='F')
					v = false;
				else
					if (!fQuiet)
					{
						char str[1024];
						snprintf(str, sizeof(str), "Bad value for option \"%s\", on line %d of file \"%s\": \"%s\"\n", op->name, line_num, fname, val);
//						infr_ptr->DisplayError(str, false);
					}
					*((bool *)op->ptr) = v;
				}
				break;
			case MoosOptEnd: break;
		} // endswitch
		op->specified = 1;
		found=true;
	}
  }
  if (!found)
  {
	  return RC_CFG_ITEM_NOT_FOUND;
  }
  return (iOK);
}


/* Reads in options. See library documentation for the exact format
   of the options file.
   New requirement: VERSION must be the first identifier in the configuration file!
*/

int  MOptionsRead(char const*fname, int* list_count, bool fQuiet)
{

  *list_count = 0;

  FILE *db = fopen(fname, "r");	// if failed, try again in iv_system root-folder itself

  if(db == NULL)
  {
     if (!fQuiet)
     {
    	 char str[1024];
    	 printf( "Error openning config file \"%s\"\n",  fname);
//    	 infr_ptr->DisplayError(str, false);
     }
     return RC_CFG_OPEN_NOT_POSSIBLE;      
  } 

  
  char *p, ln[MAX_LINE_LEN];
  int line_number = 0;
  char *optname,*sep;

  int  iOK = RC_CFG_OK;
  
  while((iOK == RC_CFG_OK) && ((p = fgets(ln, MAX_LINE_LEN - 5, db))!=NULL))
  {
      line_number++;      
      p = skipspaces(p);			/* Skip beginning blanks. */
      
      if(*p == COMMENT_CHAR)		/* Handle comments. */
        continue;
      
      p[strlen(p)-1] = '\0';		/* Remove the trailing \n. */

      clearDaDamnTrailingSpaces(p); /* Remove the trailing spaces. */
      
      
      if(!*p)						/* Skip empty lines. */
        continue;

      /* Find the field separator on the line. */
      sep = skipToken(p);
      if(!*sep)
      {
    	     if (!fQuiet)
    	     {
    	    	 char str[1024];
    	    	 printf( "Syntax error at line %d of %s. Missing ':'.\n",
 				        line_number, fname);
//    	    	 infr_ptr->DisplayError(str, false);
    	     }
    	     iOK = RC_CFG_SYNTAX_ERROR_MISSING_DBLPOINT;
			 continue;
      }
      
      /* Terminate the line here. p is now the null terminated option
         string. Way may have either clobbered a space or the field
         separator by doing this. */
      *sep = '\0';

      optname = p;
      
      /* Skip to the separator or to the beginning of the value if we've
	 killed the separator. */
      sep = skipspaces(sep+1);
      
      /* If we're at the separator, then skip it and the spaces afterwards. */
      if(*sep==FIELD_SEPARATOR) sep = skipspaces(sep+1);
      if(!*sep)
        {
 	     if (!fQuiet)
 	     {
 	    	 char str[1024];
 	    	 printf( "Warning: No value specified for option \"%s\" on line %d of %s.\n", p, line_number, fname);
// 	    	 infr_ptr->DisplayError(str, false);
 	     }
          continue;
        }

	  {
		/* Set the value of the option to that specified on this line. */
		iOK = SetValue(/*optlist*/ optname, sep, line_number, fname, fQuiet);
		if ( RC_CFG_OK == iOK )
		{
			( *list_count) ++;
		}
	  }	  
  }

  if (db) fclose(db);

   return (iOK);
}

/****************************************************/
/****************************************************/
/*! \brief	get error msg from RC returned from module
 * \param[in]	ptr buffer for error msg
 * \param[in]	iRC returned from module
 * \return	 void
  * */
/****************************************************/
/****************************************************/
void Opt_GetErrorMsg(char * pErrorMsg, unsigned bufsize, int iRC)
{
	switch (iRC)
	{
//	case RC_CFG_OLD_CONFIG:
//		strncpy(pErrorMsg, "Old config file. \n Please check that the config file has a version specified. \n Detailed info in stderr.txt.", bufsize);
//		break;
//	case RC_CFG_VERSION_INVALID:
//		strncpy(pErrorMsg, "Version in config file is invalid. \nPlease check for a config file with another version.\n Detailed info in stderr.txt.", bufsize);
//		break;
	case RC_CFG_ITEM_NOT_FOUND:
		strncpy(pErrorMsg, "Invalid item in config file: can not found in dictionary.", bufsize);
		break;
	case RC_CFG_STRING_QUOTES_MISSING:
		strncpy(pErrorMsg, "Invalid config file: a string without quotes has been specified in the config file.", bufsize);
		break;
	case RC_CFG_OPEN_NOT_POSSIBLE:
		strncpy(pErrorMsg, "Cannot open config file.", bufsize);
		break;
	case RC_CFG_SYNTAX_ERROR:
		strncpy(pErrorMsg, "Config file has a syntax error.", bufsize);
		break;
	case RC_CFG_SYNTAX_ERROR_MISSING_DBLPOINT:
		strncpy(pErrorMsg, "Config file has syntax error.", bufsize);
		break;
	}
	return;
}

