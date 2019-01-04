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

// gxdoc.h : header file
//

#ifndef _GX_DOC_H__
#define _GX_DOC_H__

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


// All documents that are used by workbook classes should be derived from CGXDocument. The actual serialization code should be 
// copied over to WorkBookSerialize. Change the existing Serialize handler to simply call the base class (or remove the handler
// itself) 
class CGXTabWndMgr;
class CGXDocument :public CDocument
{
	DECLARE_SERIAL(CGXDocument)

// constructors / destructor
	CGXDocument();
	virtual ~CGXDocument();

//overrides
	virtual void WorkBookSerialize(CArchive& ar);
	
	virtual void Serialize(CArchive& ar);
	
	virtual BOOL DoSave(LPCTSTR lpszPathName, BOOL bReplace = TRUE);

	virtual BOOL SaveModified(); // return TRUE if ok to continue
	
//access
	void SetPrimaryDocument(CGXDocument* pDoc) ;
	CGXDocument* GetPrimaryDocument() const;
	CGXTabWndMgr* GetTabManager();

protected:

	//data
	CGXDocument* m_pDocument;
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
#endif //_GX_DOC_H__
