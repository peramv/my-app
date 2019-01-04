// This is a part of the Objective Grid C++ Library.
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
// Author: Praveen Ramesh
//

// gxScrCurEng.h : header file
//

#ifndef _GX_SCRCUR_ENG
#define _GX_SCRCUR_ENG

#ifndef _GXDBENGINE
#include "grid\gxdbengine.h"
#endif

#ifndef _GXDBEGRID
#include "grid\gxdbegrid.h"
#endif

//
// GridMFC Extension DLL
// initialize declaration context
//
#if defined (_GXDLL) && !defined (_GXNOEXTSTATE)
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    GX_DATAEXT
#endif

/////////////////////////////////////////////////////////////////////////////
// CGXDBDirtyFieldStruct
//
// holds edited field values for the current record

struct CGXDBDirtyFieldStruct
{
	CGXDBDirtyFieldStruct();
	// edited fields
	BOOL bDirty;
	CString sValue;
};

// Base class for any engine that binds to a scrollable cursor.
// Impliments some common base functionality for such engines.
class CGXScrollableCurEngine : public CGXDBEngine
{
protected:
	CGXScrollableCurEngine();

protected:

	long m_nCols;		// No. of columns in the result set

	// Current record - internal buffer with edited field values
	CGXDBDirtyFieldStruct* m_paDirtyFieldStruct;
	long m_nLastRecordSeen;	// Records fetched so far. 0 based.
	long m_nCurrentCursorPos;	// Record where the cursor is positioned at. 0 based.

public:

	virtual BOOL Edit(long nRecord);	// Call Edit before editing a record via SetValue...
	virtual BOOL GetValue(long nRecord, long nField, CString& strValue);	// nRecord and nField are 1 based...
	virtual BOOL SetValue(long nRecord, long nField, CString* strValue);
	virtual BOOL Update(CString* strError = NULL); // Complete the editing on a record by calling Update...
	virtual long AddRow();	// The returned value is the new record no. that should be used in SetValue...
	virtual void CancelRecord();
	virtual long GetRecordCount();	// 1 based...
	virtual long GetFieldCount();	// 1 based...
	virtual BOOL MoveToPosition(long nRecord, BOOL bSync = TRUE, BOOL bThrowExceptionOnError = FALSE) = 0;
	virtual void OnDeletedRecords();
	long GetCurrentCursorPos(){return m_nCurrentCursorPos;}

protected:
	void OnAddedNewRecord();
	virtual BOOL OnFlushRecord(long nEditRecord, CString* ps);
	virtual void OnFlushCellValue(long nEditRow, long nField, CString& strValue)=0;
};


//
// GridMFC extension DLL
// reset declaration context
//
#if !defined _GXNOEXTSTATE
#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR
#endif

#endif //_GX_SCRCUR_ENG
