/*===========================================================================*\
 * FILE: CSVHmiIntend.cpp
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
#include "CSVHmiIntent.h"
#include "ISVHmi.h"
#include "CSVHmiFactory.h"

CSVHmiIntent::CSVHmiIntent():m_fromHmi(0), m_toHmi(0)
{

}
CSVHmiIntent::~CSVHmiIntent()
{

}

CSVHmiIntent* CSVHmiIntent::GetInstance()
{
	static CSVHmiIntent* intend = NULL;
	if(intend == NULL)
	{
		intend = new CSVHmiIntent;
	}
	return intend;
}

int CSVHmiIntent::Intent(ISVHmi* pFromHmi, char* pToHmi)
{
	if(pToHmi == NULL)
	{
		return -1;
	}

	m_fromHmi = pFromHmi;

	if(m_toHmi)
	{
		delete m_toHmi;
		m_toHmi = NULL;	
	}

	m_toHmi = static_cast<ISVHmi*>(CSVHmiFactory::CreateHmi(&pToHmi));
	m_toHmi->Init(XrGetScreenWidth(), XrGetScreenHeight());

	//m_toHmi->SetIntent(this);

	return 0;
}

int CSVHmiIntent::Intent(char* pToHmi)
{
	if(pToHmi == NULL)
	{
		return -1;
	}

	m_fromHmi = GetCurrentHmi();
	
	m_toHmi = static_cast<ISVHmi*>(CSVHmiFactory::CreateHmi(&pToHmi));
	if(m_toHmi)
	{
		m_toHmi->Init(XrGetScreenWidth(), XrGetScreenHeight());
	}
	//m_toHmi->SetIntent(this);
}
int CSVHmiIntent::StartHmi(void* hmiMsg)
{
	if(m_fromHmi)
	{
		delete m_fromHmi;
		m_fromHmi = NULL;
	}

	if(m_toHmi)
	{	
		m_toHmi->Update(*((Hmi_Message_T*)hmiMsg));
	}
	return 0;
}

ISVHmi* CSVHmiIntent::GetCurrentHmi()
{
	return m_toHmi;
}
/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  12/16/17   Jensen Wang   Create the CSVHmiIntend class.
\*===========================================================================*/