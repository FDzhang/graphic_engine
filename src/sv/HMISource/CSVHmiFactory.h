/*===========================================================================*\
 * FILE: CSVHmiFactory.h
 *===========================================================================
 * Copyright 2003 O-Film Technologies, Inc., All Rights Reserved.
 * O-Film Confidential
 *
 * DESCRIPTION:
 *
 * ABBREVIATIONS:
 *   TODO: List of abbreviations used, or reference(s) to external document(s)
 *
 * TRACEABILITY INFO:
 *   Design Document(s):
 *     TODO: Update list of design document(s)
 *
 *   Requirements Document(s):
 *     TODO: Update list of requirements document(s)
 *
 *   Applicable Standards (in order of precedence: highest first):
 *
 * DEVIATIONS FROM STANDARDS:
 *   TODO: List of deviations from standards in this file, or
 *   None.
 *
\*===========================================================================*/

/*===========================================================================*\
 * Standard Header Files
\*===========================================================================*/


#ifndef _CSV_HMI_FACTORY_H_
#define _CSV_HMI_FACTORY_H_

#include "../../XrCore/XrSrc/External/XrHeaders.h"

#include <map>

typedef void* (* HmiConstructor)();

/*static std::map<char* , HmiConstructor> test_instance;
//static std::map<char* , HmiConstructor>& m_instance = test_instance;
static std::map<char* , HmiConstructor>& m_instance()
	{
		static std::map<char* , HmiConstructor> instance;
		return instance;
	}*/
		

class CSVHmiFactory
{
public:
	
	static void RegisterClass(char* pClassName, HmiConstructor pHmiConstructor)
	{
		HmiConstructors()[pClassName] = pHmiConstructor;
	}

	static void* CreateHmi(char** pClassName)
	{
		HmiConstructor hmiConstructor = NULL;
		if(HmiConstructors().find(*pClassName) != HmiConstructors().end())
		{
			hmiConstructor = HmiConstructors().find(*pClassName)->second;
		}
		if(hmiConstructor == NULL)
		{
			return NULL;
		}

		return (*hmiConstructor)();
	}


/*	static void RegisterClass(char* pClassName, HmiConstructor pHmiConstructor)
	{
		m_instance()[pClassName] = pHmiConstructor;
	}

	static void* CreateHmi(char** pClassName)
	{
		HmiConstructor hmiConstructor = NULL;
		if(m_instance().find(*pClassName) != m_instance().end())
		{
			hmiConstructor = m_instance().find(*pClassName)->second;
		}
		if(hmiConstructor == NULL)
		{
			return NULL;
		}

		return (*hmiConstructor)();
	}
*/
private:

	inline static std::map<char* , HmiConstructor>& HmiConstructors()
	{
		static std::map<char* , HmiConstructor> instance;
		return instance;
	}

private:


};

#define REGISTER_HMI_CLASS(className) \
class className##Helper {\
public: \
	className##Helper() \
	{\
		CSVHmiFactory::RegisterClass(#className, className##Helper::createHmiFunc);\
	}\
	static void* createHmiFunc()\
	{\
		return new className;\
	}\
};\
className##Helper className##helper;

#endif //_CSV_HMI_FACTORY_H_


/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  12/16/17   Jensen Wang   Create the CSVHmiFactory class.
\*===========================================================================*/