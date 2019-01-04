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
// Author: Daniel Jebaraj
//

// gxtbmgr.h : header file
//

#ifndef _GX_TB_MGR_H__
#define _GX_TB_MGR_H__

#include "grid\gxdoc.h"

#include <afxtempl.h>

#include "grid\gxman.h"

#include "grid\gxtbadpt.h"

//
// GridMFC Extension DLL
// initialize declaration context
//

#ifdef _GXDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    GX_DATAEXT
#endif

// CRuntimeClass::Load slightly modified
class CGXRuntimeClassOp
{
public:
	static CRuntimeClass* PASCAL Load(CArchive& ar);
	static void Store(CRuntimeClass* pRClass, CArchive& ar);
};



enum gxContextGen
{
	gxGenFromDefault,
	gxGenFromIndex,
	gxGenUseIntact,
};

// this will be passed in to create the actual views as tab children
class CGXTabCreateInfo : public CObject
{
	DECLARE_SERIAL(CGXTabCreateInfo)

public:
// constructors / destructors
	CGXTabCreateInfo();
	
	CGXTabCreateInfo(CCreateContext* pContext, gxContextGen gen = gxGenFromDefault,
		CDocTemplate* pDocTemplate = NULL, const TCHAR* pszLabel = NULL, BOOL bUseContextIntact = FALSE);
	
	CGXTabCreateInfo(CGXTabCreateInfo& info);
	
	virtual ~CGXTabCreateInfo();
	
// operations
	void Initialize(CCreateContext* pContext, gxContextGen gen = gxGenFromDefault,
		CDocTemplate* pDocTemplate = NULL, const TCHAR* pszLabel = NULL, BOOL bUseContextIntact = FALSE);

// overrides 
	virtual void Serialize(CArchive& ar);
	
// access
	CRuntimeClass* GetViewRuntimeClass() const;
	void SetViewRuntimeClass(CRuntimeClass* pRuntimeClass);

	CRuntimeClass* GetDocRuntimeClass() const;
	void SetDocRuntimeClass(CRuntimeClass* pRuntimeClass);

	CCreateContext* GetCreateContext();
	void SetCreateContext(const CCreateContext* pContext);

	BOOL GetUseContextIntact() const;
	void SetUseContextIntact(BOOL bContext);

	CString GetLabel() const;
	void SetLabel(CString strLabel);

	CDocTemplate* GetDocTemplate() const;
	void SetDocTemplate(CDocTemplate* pDocTemplate);

	CGXDocument* GetDocument() const;
	void SetDocument(CGXDocument* pDocument);

	gxContextGen GetContextGenMode() const;
	void SetContextGenMode(gxContextGen gen);

	int GetIndex();
	void SetIndex(int index);
	
	void SetInit(BOOL b);
	BOOL IsInit();

//operators
	virtual void operator=(CGXTabCreateInfo& pInfo);

// Diagnostic Support
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
//data
	// the view runtime class
	CRuntimeClass* m_pViewRuntimeClass; 
	// the document runtime class
	CRuntimeClass* m_pDocRuntimeClass; 
	// the current creation context
	CCreateContext* m_pContext;
	
	// Whether the create context should be used intact.
	// a new document will not be created in this case.
	BOOL m_bUseContextIntact;
	// the label for the tab. Only minimum information for the tab appearance is
	// persisted in this variant
	CString m_strLabel;
	// the doc template to be used for document creation
	CDocTemplate* m_pDocTemplate;
	// pointer to the document used (set or created)
	CGXDocument* m_pDocument;

	// CCreateContext generation mode
	gxContextGen m_gxCGgen;

	// Init 
	BOOL m_bIsInit;
	
	int m_nIndex;
};

// two responsibilities
// 1) Create 
// 2) Serialize tabs and recreate
class CGXTabWndAdapter;

typedef CArray<CGXTabCreateInfo*, CGXTabCreateInfo*> CGXTabCreateArray;

class CGXTabWndMgr : public CObject
{
	DECLARE_SERIAL(CGXTabWndMgr)
public:
	
// constructors / destructors
	CGXTabWndMgr();
	
	CGXTabWndMgr(CWnd* pTabParent);
	
	virtual ~CGXTabWndMgr();

// operations
	
	// create tabs initially
	virtual BOOL CreateTabs(CGXTabCreateInfo* pTabCreateInfo, int nTabs = 0, TCHAR* pszFileName = NULL, CGXTabWndAdapter* pTabAdapter = NULL);
	
	//use to Create supplementary tabs
	virtual BOOL CreateSupTabs(CGXTabCreateInfo* pTabCreateInfo, CMDIChildWnd* pChildWnd, int nTabs = 0, TCHAR* pszFileName = NULL );
	
	//use to remove supplementary tabs
	virtual void RemoveSupTab(CMDIChildWnd* pChildWnd);

	virtual CGXNodeManagerNor<CGXTabWndAdapter>* CreateSupTabHolder();

	virtual BOOL InsertWorkSheet(int nInsertBefore, CGXTabCreateInfo* pTabCreateInfo, UINT nID = 0);

	virtual BOOL DeleteWorkSheet(int nDeleteIndex);

	virtual BOOL CanInsertWorkSheet() const;
	
	virtual BOOL CanDeleteWorkSheet() const;

	virtual BOOL GenerateCreateContext(CGXTabCreateInfo* pTabCreateInfo);

	void UpdateTabCount();

	//access
	
	// sets the primary CCreateContext for all view creation
	void SetPrimaryContext(CCreateContext* pContext);
	
	// intialize with a parent window
	void SetParent(CWnd* pParentWnd);

	void SetPrimaryTabCreateInfo(CGXTabCreateInfo* pTabCreateInfo, BOOL bDeleteTabInfo = FALSE);
	
	CGXTabCreateInfo* GetPrimaryTabCreateInfo();

	int GetPrimaryIndex();
	
	CArray<CGXTabCreateInfo*, CGXTabCreateInfo*>* GetTabCreateInfoArray();

	int GetTabCount();

	int GetCursel() const;

	CGXNodeManagerNor<CGXTabWndAdapter>& GetSupTabWndHolder();

// overrides / overrideables
	
	//serialization code
	virtual void Serialize(CArchive& ar);
	
	virtual void Cleanup();
	
	virtual void OnInitialize();

	virtual CGXTabWndAdapter* GetTabWndAdapter() const;
	
	virtual void SetTabWndAdapter(CGXTabWndAdapter* pAdapter, BOOL bOwn = FALSE);

	virtual BOOL IsModified();
	
	virtual void SetModify(BOOL bModify);

	virtual void SetPrimaryModified(BOOL b);

	// serialization helpers
	virtual BOOL ReadDocumentsFromArchive(CArchive& ar, CGXDocument* pDocThis, int nIndex = 0);
	
	virtual BOOL StoreDocumentsInArchive(CArchive& ar);

// implementation
protected:
	
	BOOL IterateAndSaveDocuments(CArchive& ar) const;
	
	BOOL IterateAndLoadDocuments(CArchive& ar, CGXDocument* pDocThis, int nIndex = 0);
	
protected:
	// whether we own the tab window adapter. Owned adapters will be deleted by us.
	BOOL m_bOwn;
	// array of CGXTabCreateInfo structures
	CArray<CGXTabCreateInfo*, CGXTabCreateInfo*> m_ArrTabCreateInfo;
	// tab count
	int m_nTabCount;
	// Tab Window adapter
	CGXTabWndAdapter* m_pTabWndAdapter;
	// map to hold the supplementary tabs
	CGXNodeManagerNor<CGXTabWndAdapter>* m_pSupTabHolder;
	// pointer to the primary document
	CGXTabCreateInfo* m_pPrimaryTabCreateInfo;
	// Whether we should delete the stored tab info
	BOOL m_bDeleteTabInfo;

private:
	// the index of the primary tab
	int m_nPrimaryIndex;
	
	// Never call this unless you know exactly what changes will be needed
	void SetPrimaryIndex(int nIndex);
};


//
// GridMFC extension DLL
// reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

//

#endif //_GX_TB_MGR_H__
