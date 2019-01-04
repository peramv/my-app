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

#ifndef _GX_XRDRIM_H__
#define _GX_XRDRIM_H__

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

#ifdef _UNICODE
#pragma message( "Unsupported configuration. UNICODE is not supported with Excel read/write")
Fatal error!
#endif

// forward declaration
class CGXExcelDocAdapter;

// def read modes
enum gxExReadMode
{
	gxExReadAll = 0x01,
	gxExReadNum = 0x02,
	gxExReadIndex = 0x04,
};

// process state for writing
enum gxProcessState
{
	gxPreProcess,
	gxPostProcess,
};

// pass data for writing Excel file
enum gxPassData
{
	gxPassOne,
	gxPassTwo,
	gxPassThree,
	gxPassFour,
	gxPassFive,
	gxBoundSheetSpecialPass,
};

// type of handler
// table: Global data
// handler: field data
enum gxTableHandler
{
	gxTable,
	gxHandler,
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// base class for Excel Read /////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

class CGXExcelReader
{	
public:
// construction
	CGXExcelReader();
	virtual ~CGXExcelReader();

	virtual void ExcelReadImpl(CArchive& ar, CGXExcelDocAdapter* pDocAdapter) = 0;
	virtual void ExcelReadImpl(const CString& strFilePath, CGXExcelDocAdapter* pDocAdapter) = 0;

	virtual void ExcelWriteImpl(CArchive& ar, CGXExcelDocAdapter* pDocAdapter) = 0;
	virtual void ExcelWriteImpl(const CString& strFilePath, CGXExcelDocAdapter* pDocAdapter) = 0;

// access
	virtual int SetReadMode(int eMode) = 0;
	virtual int GetReadMode() const = 0;

	virtual UINT GetTabCount() const = 0;
	virtual void SetTabCount(UINT nTabs) = 0; 

	virtual void SetReadIndex(UINT index);
	virtual UINT GetReadIndex() const;

protected:
	UINT m_nReadIndex;
};


struct CGXWriteEntry
{
	CGXWriteEntry(const int t, gxTableHandler hType, gxPassData d = gxPassOne);
	~CGXWriteEntry();

// data
	int type;
	gxTableHandler handlerType;
	gxPassData data;
};


template<class T>
void gxTableProcessor(T* pTable, gxProcessState state, gxPassData data, DWORD dwLength, UINT nCTab = 0)
{
	// the default is to do nothing
}

// forward declarations
class CGXExcelTable;
class CGXExcelHandler;

class CGXExcelReaderImpl : public CGXExcelReader
{	
	friend class CGXExcelClipHandler;
public:
// construction
	CGXExcelReaderImpl();
	virtual ~CGXExcelReaderImpl();

// operations
	virtual void ReadCompoundExcelFile(LPCTSTR pszFileName, CGXExcelDocAdapter* pDocAdapter);
	
	virtual void ExcelWriteImpl(CArchive& ar, CGXExcelDocAdapter* pDocAdapter);
	virtual void ExcelWriteImpl(const CString& strFilePath, CGXExcelDocAdapter* pDocAdapter);

	virtual void ExcelReadImpl(CArchive& ar, CGXExcelDocAdapter* pDocAdapter);
	virtual void ExcelReadImpl(const CString& strFilePath, CGXExcelDocAdapter* pDocAdapter);

	// logging support
	virtual void CloseLogFiles();
	virtual void InitLogFiles();

// overrideables
	virtual BOOL OnWriteHandlerNotFound(int type, LPSTREAM pstm, DWORD& dwLength);

// access
	virtual UINT GetTabCount() const;
	virtual void SetTabCount(UINT nTabs);

	// override if you want to have different names for log files
	virtual CString GetHandlerLogName();
	virtual CString GetTableLogName();
	
	virtual int SetReadMode(int eMode);
	virtual int GetReadMode() const;

	// writing support
	virtual CGXWriteEntry* GetWriteHandlerMap();
	virtual CGXWriteEntry* GetWriteTableMap();

protected:
// overrideables
	virtual DWORD GetDocFileCreateMode() const;
	virtual DWORD GetStreamCreateMode() const;

	virtual DWORD GetDocFileReadMode() const;
	virtual DWORD GetStreamReadMode() const;
	
	virtual void gxTableProcessor(int type, CGXExcelTable* pTable, gxProcessState state, gxPassData data, DWORD dwLength, UINT nCTab = 0);
	virtual void gxTableProcessor(int type, CGXExcelHandler* pHandler, gxProcessState state, gxPassData data, DWORD dwLength, UINT nCTab = 0);

//implementation
	void ReadStream(IStream* pStream, CGXExcelDocAdapter* pDocAdapter);
	void ReadStorage(IStorage* pStorage, CGXExcelDocAdapter* pDocAdapter);

	virtual void WriteBIFFHelper(LPSTREAM pStream, CGXExcelDocAdapter* pDocAdapter, UINT nTabs = GX_INVALID);
	virtual BOOL ProcessStorageFile(const TCHAR* psz, IStorage*& pStorage, IStream*& pStream);
	
// data
	// the read mode
	int m_eReadMode;
	UINT m_nCTabs;
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

#endif //_GX_XRDRIM_H__
