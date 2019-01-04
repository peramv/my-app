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


#ifndef _GX_DCADPT_H__
#define _GX_DCADPT_H__

#ifndef _GX_EX_OLE_H__
#include "grid\gxexole.h"
#endif

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


// forward decl
class CGXExcelReader;

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// class CGXNodeManagerAr
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Simple creation and garbage collection support
// uses CRuntimeClass

template <class T>
class CGXNodeManagerAr
{
	
	class __t : public T
	{
		friend class CGXNodeManagerAr;
	 public:
		 __t(DWORD index)
		 {m_dwIndexUsed = index; };
		 
		 virtual ~__t()
		 {};

	 protected:
		 DWORD m_dwIndexUsed;
	};


public:
	CGXNodeManagerAr(CRuntimeClass* pRuntimeClass);
	virtual ~CGXNodeManagerAr();

	virtual T* CreateObject(int dw);
	virtual T* CreateAndInsertObject(int dw);

	void RemoveObject(int dw);
	
	CArray<T*, T*&>& GetMap()
	{return m_pMpT;};

//implementation
protected:
	CArray<T*, T*&> m_pMpT;
	
// clean up
	void CleanObjects();
	CRuntimeClass* m_pRuntimeClass;
};


template <class T>
CGXNodeManagerAr<T>::CGXNodeManagerAr(CRuntimeClass* pRuntimeClass)
{
	m_pRuntimeClass = pRuntimeClass;
}

template <class T>
CGXNodeManagerAr<T>::~CGXNodeManagerAr()
{
	CleanObjects();
}

template <class T>
T* CGXNodeManagerAr<T>::CreateObject(int dw)
{
	T* pObject = NULL;
	if(GetMap().GetUpperBound() < dw || GetMap()[dw] == NULL)
	{
		T* p = (T*) m_pRuntimeClass->CreateObject();

		ASSERT(p != NULL);
		
		GetMap().SetAtGrow(dw, p);
		return p;
	}
	else
	{
		return (GetMap())[dw];
	}	
}
	
template <class T>
T* CGXNodeManagerAr<T>::CreateAndInsertObject(int dw)
{
	if(GetMap()[dw] == NULL)
		return CreateObject(dw);
	
	T* p = NULL;
	GetMap().InsertAt(dw, p);
		
	return CreateObject(dw);
}

// This will remove the object from the internal map and delete it
template <class T>
void CGXNodeManagerAr<T>::RemoveObject(int dw)
{
	DWORD dwKey = dw;
	T* pObject = NULL;
	
	ASSERT( dw <= GetMap().GetUpperBound());
	
	pObject = GetMap()[dw];

	GetMap().RemoveAt(dw);

	if (pObject != NULL)
		delete pObject;
}

// clean up
template <class T>
void CGXNodeManagerAr<T>::CleanObjects()
{
	// iterate through the list and call delete
	CArray<T*, T*&>& arr = GetMap();

	TRACE1("The number of objects in CGXNodeManagerAr is: %i\n", arr.GetSize());

	int nBound = (int)arr.GetUpperBound();
	
	T* pObject = NULL;

	for (int index(0); index <= nBound; index++)
	{	
		pObject = arr[index];
	
		if(pObject != NULL)
			delete pObject;
	}	

	arr.RemoveAll();
}

typedef CGXNodeManagerAr<CGXGridParam> CGXParamManager;

/////////////////////////////////////////////////////////
// CGXExcelDocAdapter ///////////////////////////////////
/////////////////////////////////////////////////////////
class CGXExcelDocAdapter
{
public:
	// construction
	CGXExcelDocAdapter();
	virtual ~CGXExcelDocAdapter();

	// Operations
	void ImplementExcelReadWrite();
	
	virtual void InitializeParam(UINT index, UINT nIndexPrim);
	
	virtual void ReadExcelData();

	virtual void UpdateTabCount();

	//serialization helpers
	virtual void ExcelSerializeImpl(CArchive& ar, BOOL bReadAll = FALSE);
	virtual void ExcelWorkBookSerializeImpl(CArchive& ar);

	//access
	// will return a CGXGridParam based on the index value passed in
	virtual CGXGridParam* GetParam(UINT index);
	// will return a CGXGridCore pointer based on the index passed in
	virtual CGXGridCore* GetGrid(UINT index);
	// Will return the index based on the CObject pointer that is passed in
	virtual int GetIndex(const CObject* pObject);
	
	// will return the parent document that is derived from this document adapter
	virtual CGXDocument* GetParentDoc();
	// will retun the associated CGXTabWnd
	virtual CGXTabWnd* GetTabWnd();
	// will return the document adapter that corresponds to the primary 
	virtual CGXExcelDocAdapter* GetParentDocAdapter();

	// whether the write mode is set to Excel output
	BOOL GetWriteAsExcel() const;
	// set the write mode
	void SetWriteAsExcel(BOOL b);

	// when reading the file this checks to see if this is an Excel file
	// This uses a rather simplistic check. You can override and handle for other checks
	// You have to override and handle if you use a different extension than xls
	virtual BOOL IsExcelFile(const TCHAR* lpszFileName) const;

	// returns a pointer to the Excel Reader
	virtual CGXExcelReader* GetExcelReader() const;
	virtual CGXExcelReader* GetExcelReaderA();
	
	// return the param manager. This object manages parameter objects based on the index
	// of the tab
	virtual CGXParamManager* GetParamManager();
	
	// return the number of tabs hosted
	UINT GetTabCount() const;
	
	// will be called from OnInitialUpdate to check whether it is possible to perform
	// initialization or wait.
	void SetWaitMode(BOOL bWaitMode);
	BOOL GetWaitMode();

	// the path of the underlying file
	void SetFilePath(LPCTSTR pszFilePath);
	const CString& GetFilePath() const;

protected:
	// data
	// actual reader
	CGXExcelReader* m_pExcelReader;	
	
	// Write as Excel or as grid data?
	BOOL m_bWriteAsExcel;

	// wait mode is used for proper initialization
	BOOL m_bWaitMode;
	
	// the number of tabs
	UINT m_nTabCount;

	// file path
	CString m_strFilePath;

	// document read mode
	BOOL m_bDocReadMode;

	// shared data
	CGXProperties* m_pProperties;
	CGXStylesMap* m_pStylesMap;
	CGXPrintDevice* m_pPrintDevice;

	// non shared data
	// some node manager for CGXGridParam data. This will depend on the number of worksheets
	CGXParamManager*  m_pParamManager;
	
	// impl
	virtual void AllocSharedComponents();
	virtual void SetSharedComponents(UINT index, UINT nIndexPrim);
};

/////////////////////////////////////////////////////////////////////////
// class CGXExcelWndDocAdapter //////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// Used for single tab read/write

class CGXExcelWndDocAdapter : public CGXExcelDocAdapter
{
public:
	// construction
	CGXExcelWndDocAdapter();
	virtual ~CGXExcelWndDocAdapter();

	// Operations
	virtual void InitializeParam(UINT index);
	
	void ReadExcelFile(const CString& strFileName, UINT index = 0);
	void SaveExcelFile(const CString& strFileName);

	//serialization helpers
	virtual void ExcelSerializeImpl(CArchive& ar, BOOL bReadAll = FALSE);
	virtual void ExcelWorkBookSerializeImpl(CArchive& ar);

	//access
	// will return a CGXGridParam based on the index value passed in
	virtual CGXGridParam* GetParam(UINT index);
	virtual CGXGridCore* GetGrid(UINT index);
	virtual int GetIndex(const CObject* pObject);

	virtual CGXDocument* GetParentDoc();
	virtual CGXTabWnd* GetTabWnd();
	virtual CGXExcelDocAdapter* GetParentDocAdapter();

	void SetGrid(CGXGridCore* pCore);
	
protected:
	// data
	CGXGridCore* m_pCore;
};

////////////////////////////////////////////////////////////////////
// class CGXExcelClipHandler ///////////////////////////////////////
////////////////////////////////////////////////////////////////////
// Used for BIFF clipboard handling
class CGXExcelClipHandler
{
public:
	CGXExcelClipHandler(BOOL bFormula = FALSE);
	~CGXExcelClipHandler();

	virtual BOOL Copy(CGXGridCore* pCore, const CGXRange& rg);
	virtual BOOL Paste(CGXGridCore* pCore, const CGXRange& rg);
	
	virtual BOOL CanCopy(CGXGridCore* pCore);
	virtual BOOL CanPaste(CGXGridCore* pCore);
	
	virtual CGXGridWnd* GetGridWnd();
	void DestroyGridWnd();
	void ResetGridWnd();
	
protected:
	UINT m_uiData;
	// used internally for easier clipboard access
	CGXGridWnd  m_gridWnd;
	
	// When used with formula grids
	BOOL m_bFormula;
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

#endif //_GX_DCADPT_H__
