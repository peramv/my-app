///////////////////////////////////////////////////////////////////////////////
// gxexlog.cpp
//
// Copyright (c) 1997-2012 Rogue Wave Software, Inc.  All Rights Reserved.
//
// This computer software is owned by Rogue Wave Software, Inc. and is protected by
// U.S. copyright laws and other laws and by international treaties. This
// computer software is furnished by Rogue Wave Software, Inc. pursuant to a written
// license agreement and may be used, copied, transmitted, and stored
// only in accordance with the terms of such license agreement and with
// the inclusion of the above copyright notice.  This computer software or
// any other copies thereof may not be provided or otherwise made available
// to any other person.
//
// U.S. Government Restricted Rights.  This computer software:
//      (a) was developed at private expense and is in all respects the
//          proprietary information of Rogue Wave Software, Inc.;
//      (b) was not developed with government funds;
//      (c) is a trade secret of Rogue Wave Software, Inc. for all purposes of the
//          Freedom of Information Act; and
//      (d) is a commercial item and thus, pursuant to Section 12.212
//          of the Federal Acquisition Regulations (FAR) and DFAR
//          Supplement Section 227.7202, Government’s use, duplication or
//          disclosure of the computer software is subject to the restrictions
//          set forth by Rogue Wave Software, Inc.
//
///////////////////////////////////////////////////////////////////////////////
//
// Author: Daniel Jebaraj
//

#define _OG_EXPORT_IMPL

#include "stdafx.h"

#include "grid\gxexman.h"

#include "grid\gxexlog.h"


CGXCaptiveManagerNoRef<CGXExcelLogger> CGXExcelLoggerFactory::s_loggerMan;


CGXExcelLogger::CGXExcelLogger()
{
	// file open is FALSE
	m_bIsLogFileOpen = FALSE;

	// default is that we log for debug build and not for release
#ifdef _DEBUG
	m_bNoLogging = FALSE;
#else
	m_bNoLogging = TRUE;
#endif
};

CGXExcelLogger::~CGXExcelLogger()
{
	CloseLogFile();
}

CGXExcelLogger::CGXExcelLogger(const TCHAR* pszFileName)
{
	InitLogFile(pszFileName);
}
	
void CGXExcelLogger::SetNoLogging(BOOL b)
{
	m_bNoLogging = b;
}	

BOOL CGXExcelLogger::GetNoLogging() const
{
	return m_bNoLogging;
}

void CGXExcelLogger::LogText(const TCHAR* pszText)
{
	try
	{
		if(m_bIsLogFileOpen) 
			fileLog.WriteString(pszText);
	}
	catch(...)
	{
		// this should never crash the program
		GX_THROW_LAST
	}
}

void CGXExcelLogger::InitLogFile(const TCHAR* pszFileName)
{
	if(m_bIsLogFileOpen == TRUE || m_bNoLogging == TRUE) 
		return;

	// intialize the error log handler
	try
	{
		BOOL b = fileLog.Open(pszFileName, CFile::modeCreate|CFile::modeReadWrite);
		
		if(b)
			m_bIsLogFileOpen = TRUE;
		else
		{
			TRACE0("CGXExcelLogger::InitLogFile: Unable to create log file\n");
			m_bIsLogFileOpen = FALSE;
			return;
		}

		COleDateTime dt(COleDateTime::GetCurrentTime());
		CString str = dt.Format();
		
		LogText(_T("Stingray Software. Objective Grid Excel Reader Log File\nCreated:"));
		LogText(str+_T("\n\n"));
		
	}
	catch(CFileException * fe)
	{	
		fe->ReportError();
		TRACE0("OG: File exception thrown when opening log file\n");
		GX_THROW_LAST;
		fe->Delete();
	}
	catch(...)
	{
		TRACE0("OG: Unknown exception thrown when opening log file\n");
		TRACE0("OG: Read/Write errors will not be logged\n");
		GX_THROW_LAST
	}
}

void CGXExcelLogger::CloseLogFile()
{
	if(m_bIsLogFileOpen != TRUE)
		return;
	
	try
	{
		fileLog.Close();
	}
	catch(CFileException * fe)
	{	
		fe->ReportError();
		TRACE0("OG: File exception thrown when closing log file\n");
		GX_THROW_LAST;
		fe->Delete();
	}
	catch(...)
	{
		TRACE0("OG: Unknown exception thrown when closing log file\n");
		GX_THROW_LAST
	}

	m_bIsLogFileOpen = FALSE;

	CGXExcelLoggerFactory::GetLoggerManager()->RecycleObject(this);
}

void CGXExcelLogger::LogNumber(int nNum, BOOL bNewLine)
{
	if(m_bNoLogging == TRUE)
		return;
	
	static TCHAR szNum[255];
	memset(&szNum, _T('\0'), sizeof(TCHAR)*255);
#ifdef _WIN64 //RW64
	//_stprintf_s(szNum, sizeof(szNum), "%d", nNum);
	_stprintf(szNum, "%d", nNum);
#else
	_stprintf(szNum, "%d", nNum);
#endif //_WIN64
	LogText(szNum);
	
	if(bNewLine)
		LogText(_T("\n"));
}


void CGXExcelLogger::LogXNumber(int nNum, BOOL bNewLine)
{
	if(m_bNoLogging == TRUE)
		return;
	
	static TCHAR szNum[255];
	memset(szNum, _T('\0'), sizeof(TCHAR)*255);
#ifdef _WIN64 //RW64
	//_stprintf_s(szNum, sizeof(szNum), "%x", nNum);
	_stprintf(szNum, "%x", nNum);
#else
	_stprintf(szNum, "%x", nNum);
#endif //_WIN64
	LogText(szNum);
	
	if(bNewLine)
		LogText(_T("\n"));
}		
