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


#ifndef _GX_EX_TAB_WND_MGR__
#define _GX_EX_TAB_WND_MGR__

#include "grid\gxtbmgr.h"

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


class CGXExTabWndMgr : public CGXTabWndMgr
{
	DECLARE_SERIAL(CGXExTabWndMgr)
public:
	
// constructors / destructors
	CGXExTabWndMgr();
	
	CGXExTabWndMgr(CWnd* pTabParent);
	
	virtual ~CGXExTabWndMgr();

// access
	void SetLDocument(CGXDocument* pDocument);
	
//overrides
	virtual BOOL ReadDocumentsFromArchive(CArchive& ar, CGXDocument* pDocThis, int nIndex = 0);
	virtual BOOL ExIterateAndLoadDocuments(CArchive& ar, CGXDocument* pDocThis, int nIndex);
	
	virtual BOOL StoreDocumentsInArchive(CArchive& ar);
	virtual BOOL ExIterateAndSaveDocuments(CArchive& ar) const;

protected:
	CGXDocument* m_pLoneDocument;

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

#endif //_GX_EX_TAB_WND_MGR__
