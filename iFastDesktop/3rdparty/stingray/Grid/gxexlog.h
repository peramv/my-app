// This is a part of the Objective Grid Pro C++ Library.
// Copyright © 1999-2004 Quovadx, Inc.  All Rights Reserved.
// 
// 
// This computer software is owned by Quovadx, Inc. and is protected by 
// U.S. copyright laws and other laws and by international treaties. This 
// computer software is furnished by Quovadx, Inc. pursuant to a written 
// license agreement and may be used, copied, transmitted, and stored 
// only in accordance with the terms of such license agreement and with 
// the inclusion of the above copyright notice.  This computer software or 
// any other copies thereof may not be provided or otherwise made available 
// to any other person.
// 
// U.S. Government Restricted Rights.  This computer software: 
//      (a) was developed at private expense and is in all respects the 
//          proprietary information of Quovadx, Inc.; 
//      (b) was not developed with government funds; 
//      (c) is a trade secret of Quovadx, Inc. for all purposes of the 
//          Freedom of Information Act; and 
//      (d) is a commercial item and thus, pursuant to Section 12.212 
//          of the Federal Acquisition Regulations (FAR) and DFAR 
//          Supplement Section 227.7202, Government’s use, duplication or 
//          disclosure of the computer software is subject to the restrictions 
//          set forth by Quovadx, Inc.
//
//
// This source code is only intended as a supplement to
// the Objective Grid Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding
// the Objective Grid product.
//
// Author: Daniel Jebaraj
//

#ifndef _GX_EX_LOG_H__
#define _GX_EX_LOG_H__

//
// GridMFC Extension DLL
// initialize declaration context
//

#if	defined(_GXDLL) && !defined(_GXNOEXTSTATE) 
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    GX_DATAEXT
#endif

#ifndef _GX_EX_HLP_H__
#include "grid\gxexhlp.h"
#endif //_GX_EX_HLP_H__

///////////////////////////////////////////
// CGXExcelLogger /////////////////////////
// Logging support for Excel Read/Write ///

class CGXExcelLogger
{
public:
	// construction
	CGXExcelLogger();
	
	CGXExcelLogger(const TCHAR* pszFileName);

	virtual ~CGXExcelLogger();

	// operations
	void InitLogFile(const TCHAR* pszFileName);
	void CloseLogFile();
	
	// log text
	void LogText(const TCHAR* pszText);
	void LogNumber(int nNum, BOOL bNewLine = FALSE);
	void LogXNumber(int nNum, BOOL bNewLine = FALSE);

	// access
	void SetNoLogging(BOOL b);
	BOOL GetNoLogging() const;

protected:
	// data
	CStdioFile fileLog;
	BOOL m_bIsLogFileOpen;
	BOOL m_bNoLogging;
};

typedef CGXCaptiveManagerNoRef<CGXExcelLogger> CGXLoggerManager;

struct CGXExcelLoggerFactory
{
	static CGXExcelLogger* CreateInstance()
	{
		CGXExcelLogger* pLogger = s_loggerMan.CreateObject();
		return pLogger;
	};

	static CGXLoggerManager* GetLoggerManager()
	{return &s_loggerMan;};

	static CGXLoggerManager s_loggerMan;
};

//
// GridMFC extension DLL
// reset declaration context
//

#if !defined(_GXNOEXTSTATE) 
#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR
#endif


#endif //_GX_EX_LOG_H__
