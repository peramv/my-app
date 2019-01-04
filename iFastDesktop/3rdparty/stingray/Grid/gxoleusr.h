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
// Author: Stefan Hoenig, Daniel Jebaraj
//

#ifndef _GX_OLEVARIANT_USER_H__
#define _GX_OLEVARIANT_USER_H__

#if _MFC_VER >= 0x0400


#include "grid\gxman.h"

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


class CGXOleVarUserAttribute: public CGXAbstractUserAttribute
{
	DECLARE_SERIAL(CGXOleVarUserAttribute);

public:
	CGXOleVarUserAttribute();
	CGXOleVarUserAttribute(const COleVariant& var);

	virtual ~CGXOleVarUserAttribute();

	// Change value, update the grid, generate undo info
	virtual CGXAbstractUserAttribute& SetValue(const CString& strValue);
	virtual CGXAbstractUserAttribute& SetValue(LPCTSTR pszValue);

	virtual const CString& GetValue() const;

	CGXOleVarUserAttribute& SetOleVarValue(const COleVariant& var);

	const COleVariant* GetOleVarValue() const;

	// Copying attribute (e.g. from one style object to another)
	virtual CGXAbstractUserAttribute* Clone() const;

	virtual void Serialize(CArchive& ar);

	// Comparision
	virtual BOOL IsEqual(const CGXOleVarUserAttribute& p) const; // (TRUE if equal)

	operator LPCTSTR() const;
	
	virtual BOOL IsEmpty() const;

public:
	static CGXCaptiveManager<COleVariant> g_VarCreator;
	COleVariant* m_pOleVar;
	// special flag that is useful when updating the browser grid
	BOOL m_bModifyState;
};

//
// GridMFC extension DLL
// reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR


#endif //#if _MFC_VER >= 0x0400

#endif //_GX_OLEVARIANT_USER_H__
