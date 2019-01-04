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
// "gxwchr.h" : interface of the CGXWChar class
//
/////////////////////////////////////////////////////////////////////////////
#ifndef _GX_W_CHR_H__
#define _GX_W_CHR_H__

// simple helper class for wide characters
class CGXWChar
{
public:
// construction
	CGXWChar();
	
	CGXWChar(char* psz, UINT uiPage = CP_ACP, DWORD dwFlags = 0);
	
	CGXWChar(WCHAR* pszW, UINT uiPage = CP_ACP, DWORD dwFlags = 0);
	
	virtual ~CGXWChar();
	
// access interface
	const WCHAR* GetWChar();
	
	// you must take care to realloc and then call SetWChar when you call this
	// call Detach if you do not want to do this
	WCHAR* GetWCharRef();
	
	void Attach(WCHAR* pszW);
	WCHAR* Detach();
	
	// access
	void SetWChar(const WCHAR* pszW);
	void SetChar(const char* psz);

	UINT GetCodePage() const;
	void SetCodePage(UINT uiPage);

	DWORD GetFlags() const;
	void SetFlags(DWORD dwFlags);
	
// static helpers
	// They use defaults for member data
	static WCHAR* ConvertDef(const char* psz);
	static void FreeAllocData(WCHAR*& pszW);
	
protected:
// helpers
	static void ReportError();

	WCHAR* Convert(const char* psz);
	WCHAR* Clone(const WCHAR* pszW);
	
	void Free();

// data
	WCHAR* m_pszWChar;
	
	// code page
	UINT m_uiPage;
	
	// flags
	DWORD m_dwFlags;
};

#endif //_GX_W_CHR_H__
