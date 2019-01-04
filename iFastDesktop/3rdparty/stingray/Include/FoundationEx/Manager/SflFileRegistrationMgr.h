#if !defined __SFLFILEREGISTRATIONMGR__H__
#define __SFLFILEREGISTRATIONMGR__H__

//////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 1997-2012 Rogue Wave Software, Inc.  All Rights Reserved.
//
// This computer software is owned by Rogue Wave Software, Inc. and is protected by
// U.S. copyright laws and other laws and by international treaties. This
// computer software is furnished by Rogue Wave Software, Inc. pursuant to a written
// license agreement and may be used, copied, transmitted, and stored
// only in accordance with the terms of such license agreement and with
// the inclusion of the above copyright notice.  This computer software or
// any other copies thereof may not be provided or otherwise made available
// to any other person.
//
// U.S. Government Restricted Rights.  This computer software:
//      (a) was developed at private expense and is in all respects the
//          proprietary information of Rogue Wave Software, Inc.;
//      (b) was not developed with government funds;
//      (c) is a trade secret of Rogue Wave Software, Inc. for all purposes of the
//          Freedom of Information Act; and
//      (d) is a commercial item and thus, pursuant to Section 12.212
//          of the Federal Acquisition Regulations (FAR) and DFAR
//          Supplement Section 227.7202, Government’s use, duplication or
//          disclosure of the computer software is subject to the restrictions
//          set forth by Rogue Wave Software, Inc.
//
//////////////////////////////////////////////////////////////////////////////

#include "StingrayExportDefs.h"
#include <vector>
#include <strsafe.h>

using namespace std;

namespace sflex
{
#if (WINVER >= 0x0600) && (_MSC_VER >= 1600) // Windows Vista or Higher and VS2010 or Higher.
// SFLFileRegistrationMgr

class SFLFileRegistrationMgr
{
public:
	FOUNDATIONEX_API SFLFileRegistrationMgr();
    FOUNDATIONEX_API SFLFileRegistrationMgr(LPCTSTR progID, LPCTSTR path, LPCTSTR friendlyName, LPCTSTR appUserModelID, int numExtensions, LPCTSTR * extensions);
    FOUNDATIONEX_API virtual ~SFLFileRegistrationMgr(void);

	// Register File Types.
    FOUNDATIONEX_API HRESULT RegisterFileTypeHandlers();
	// Are the File Types Registered?
    FOUNDATIONEX_API BOOL 	 AreFileTypesRegistered();
	// Un-Register File Types. 
    FOUNDATIONEX_API HRESULT UnRegisterFileTypeHandlers();

	// Get/Set ProgID.
	inline virtual CString GetProgID() { return m_strProgID; }
	inline virtual void SetProgID(CString strProgID) { m_strProgID = strProgID; }
	// Get/Set Application Path.
	inline virtual CString GetAppPath() { return m_strAppPath; }
	inline virtual void SetAppPath(CString strAppPath) { m_strAppPath = strAppPath; }
	// Get/Set Friendly Name.
	inline virtual CString GetFriendlyName() { return m_strFriendlyName; }
	inline virtual void SetFriendlyName(CString strFriendlyName) { m_strFriendlyName = strFriendlyName; }
	// Get/Set Application User Mode ID.
	inline virtual CString GetAppUserModeID() { return m_strAppUserModeID; }
	inline virtual void SetAppUserModeID(CString strAppUserModelID) { m_strAppUserModeID = strAppUserModelID; }
	// Get by Reference the Exts to Register.
	inline virtual vector<CString> & GetExtsToRegister() { return m_rgstrExtsToRegister; }

private:
	// Register ProgID
    FOUNDATIONEX_API HRESULT RegisterProgID(BOOL fRegister);
	// Register Extensions
	FOUNDATIONEX_API HRESULT RegisterToHandleExt(LPCTSTR pszExt, BOOL fRegister);
	// Register String.
	FOUNDATIONEX_API HRESULT RegSetString(HKEY hkey, LPCTSTR pszSubKey, LPCTSTR pszValue, LPCTSTR pszData);

private:
    CString m_strProgID;
    CString m_strAppPath;
    CString m_strFriendlyName;
   	CString m_strAppUserModeID;
    vector<CString> m_rgstrExtsToRegister;
};

#endif // Vista & VS2010 

} // namespace sflex

#endif // __SFLFILEREGISTRATIONMGR__H__
