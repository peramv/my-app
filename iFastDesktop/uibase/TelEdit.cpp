//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : CTelEdit.cpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 06/24/1999
//
// ----------------------------------------------------------
//
// ^CLASS    : CTelEdit
//
// ^MEMBER VARIABLES :
//
// this edit only allow char set by using SetAllowedChars. 
// the default allowed chars are _T("0123456789()-")
// when allowed chars is _T(""), this edit behaves exactly like normal cedit
//
//******************************************************************************
#define WIN32UIBASE_DLL

#include "stdafx.h"

//removed for new arch
//#include "mfdstc.h"

#include "TelEdit.h"

namespace CND
{
}
#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTelEdit

CTelEdit::CTelEdit() : _AllowedChars(_T("0123456789()-")), MaxCharNum (60)
{
}

CTelEdit::~CTelEdit()
{
}


BEGIN_MESSAGE_MAP(CTelEdit, CEdit)
//{{AFX_MSG_MAP(CTelEdit)
ON_WM_CHAR()
ON_CONTROL_REFLECT(EN_SETFOCUS, OnSetfocus)
ON_CONTROL_REFLECT(EN_KILLFOCUS, OnKillfocus)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTelEdit message handlers

void CTelEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
   CString tmp;
   GetWindowText(tmp);

   if( tmp.GetLength()<MaxCharNum && (_AllowedChars.IsEmpty() || _AllowedChars.Find(nChar)!=-1 || nChar==VK_BACK ) )
      CEdit::OnChar(nChar, nRepCnt, nFlags);
   else
      MessageBeep(0);
}

void CTelEdit::SetAllowedChars(LPCTSTR AllowedChars)
{
   _AllowedChars=AllowedChars;
}

void CTelEdit::OnSetfocus() 
{
   current=ImmGetContext(this->m_hWnd);
   OpenStatus=ImmGetOpenStatus(  current );
   ImmSetOpenStatus(  current,    FALSE  ); 
}

void CTelEdit::OnKillfocus() 
{
   ImmSetOpenStatus(  current,    OpenStatus  ); 
   ImmReleaseContext(  this->m_hWnd,     current  );
}

void CTelEdit::SetMaxCharNum(long n)
{
   MaxCharNum=n;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/uibase/TelEdit.cpp-arc  $
 * 
 *    Rev 1.2   Oct 09 2002 17:42:56   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.1   Sep 10 2002 14:34:44   PURDYECH
 * Base condition split out
 * 
 *    Rev 1.0   Feb 15 2000 11:01:42   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.8   Jul 28 1999 10:41:12   YINGZ
 * add max char feature
 * 
 *    Rev 1.7   Jul 21 1999 09:28:42   YINGZ
 * ?
 * 
 *    Rev 1.6   Jul 20 1999 14:52:10   YINGZ
 * ?
 * 
 *    Rev 1.5   Jul 20 1999 13:53:22   YINGZ
 * new ime support
 * 
 *    Rev 1.4   Jul 15 1999 11:41:08   YINGZ
 * add more
 * 
 *    Rev 1.3   Jul 15 1999 09:07:06   YINGZ
 * take off space at the request of qa
 * 
 *    Rev 1.2   Jul 12 1999 09:14:48   YINGZ
 * add the ability to clear allowed char
 * 
 *    Rev 1.1   Jul 08 1999 10:05:58   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
