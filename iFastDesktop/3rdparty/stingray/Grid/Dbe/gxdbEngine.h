// This is a part of the Objective Grid C++ Library.
// Copyright � 1999-2004 Quovadx, Inc.  All Rights Reserved.
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
//          Supplement Section 227.7202, Government�s use, duplication or 
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

// gxdbengine.h : header file

// An abstract base class that exposes the standard interface used by the grid
// to communicate with any database...

#ifndef _GXDBENGINE
#define _GXDBENGINE

//
// GridMFC Extension DLL
// initialize declaration context
//

#if defined( _GXDLL) && !defined _GXNOEXTSTATE
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    GX_DATAEXT
#endif



// Abstrace interface through which the grid communicates with any
// concrete implementation.
class CGXDBEngine
{
public:
	CGXDBEngine();
	virtual ~CGXDBEngine();

	enum EditMode { noMode, edit, addNew };
	// Type of result set stored in the engine:
	// table: table without any selection criteria
	// join: A join of multiple tables (usually results in read-only)
	// tableSubset: table with a selection criteria
	enum ResultType { noType, table, join, tableSubset };

	short m_nEditMode;	// Edit Mode is addNew or edit
	BOOL m_bDirty;		
	BOOL m_bEOF;	
	long m_nEditRecord;	// Currently edited record, 0 based...

protected:
	long m_nIncrement;	// Default increment when fetching rows...
	int m_nTransPending;	// Pending transactions.

public:
	virtual void FetchRecords(long nRecords) = 0;	// Enables incremental fetching...
	virtual BOOL GetValue(long nRecord, long nField, CString& strValue) = 0;	// nRecord and nField are 0 based...
	virtual BOOL SetValue(long nRecord, long nField, CString* strValue) = 0;
	virtual long GetRecordCount() = 0;	// 1 based...
	virtual long GetFieldCount() = 0;	// 1 based...
	virtual BOOL Edit(long nRecord) = 0;	// Call Edit before editing a record via SetValue...
	virtual BOOL Update(CString* strError = NULL) = 0;	// Complete the editing on a record by calling Update...
	virtual long AddRow() = 0;	// The returned value is the new record no. that should be used in SetValue...
	virtual BOOL DeleteRows(long nFrom, long nTo) = 0;	//
	virtual void CleanUp();	// Called by the destructor...
	virtual BOOL CanUpdate() = 0;
	virtual BOOL CanAppend() = 0;
	virtual BOOL IsEOFSeen() ;
	virtual BOOL IsInit() = 0;
	virtual void CancelRecord() = 0;
	virtual void Requery() = 0;
	virtual void OnDeletedRecords();

	// Support for transactions.
	virtual void BeginTrans(LPCTSTR pszDescription);
	virtual void CommitTrans();
	virtual void Rollback();

	// Support for hierarchical resultsets
	virtual CGXDBEngine* GetChildAt(long nRecord);
	virtual BOOL AreChildrenAvailable();
protected:
	// nRecord and nField are 0 based; Returns the field value in the underlying database
	// irrespective of its presence in the dirty-cache.
	virtual BOOL GetOrigFieldValue(long nRecord, long nField, CString& strValue) = 0;	
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

//

#endif //_GXDBENGINE
