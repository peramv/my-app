// DSTStatic.cpp : implementation file
//

#define WIN32UIBASE_DLL

#include "stdafx.h"
#include "BaseDlg.h"
//removed for new arch
//#include "mfdstc.h"
#include "DSTStatic.h"

namespace CND
{
}
#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DSTStatic

DSTStatic::DSTStatic(
                    BaseDlg *rpParent,
                    UINT controlID
                    ) :
BaseControl( rpParent, controlID )
{
   SetControlNotUpdateable();
   SubclassDlgItem( controlID, reinterpret_cast<CWnd *>( rpParent ) );
}

DSTStatic::~DSTStatic()
{
}


BEGIN_MESSAGE_MAP(DSTStatic, CStatic)
//{{AFX_MSG_MAP(DSTStatic)
// NOTE - the ClassWizard will add and remove mapping macros here.
ON_WM_MOUSEMOVE()
//}}AFX_MSG_MAP
ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave)
END_MESSAGE_MAP()

//******************************************************************************

void DSTStatic::DoClear()
{
   for( int i=0; i<GetNumOfFields(); i++ )
   {
      DoSetText( NULL_STRING, i );
   }
}

//******************************************************************************

void DSTStatic::DoGetText(
                         DString &strValueOut,
                         int index
                         ) const
{
   CString cstr;

   GetWindowText( cstr );

	strValueOut = LPCTSTR( cstr );	
	BaseDlg::DisplayUnFormat( strValueOut, (BFFieldId)GetFieldID() );   
}

//******************************************************************************

void DSTStatic::DoInit()
{
}

//******************************************************************************

bool DSTStatic::DoSetText(
                         const DString &strValueIn,
                         int index
                         )
{
   DString tmpstr = strValueIn;

   BaseDlg::DisplayFormat( tmpstr, (BFFieldId)GetFieldID() );
   SetWindowText( tmpstr.c_str() );
   return(true);
}
//******************************************************************************

bool DSTStatic::doSetCtrlReadOnly(bool bReadOnly)
{
   //always readonly
   return(true);
}

//******************************************************************************
LRESULT DSTStatic::OnMouseLeave(WPARAM , LPARAM )
{
	HideToolTip ();
	MouseLeave();
	return(0);
}

//******************************************************************************

void DSTStatic::OnMouseMove(UINT nFlags, CPoint point) 
{
	if( IsError())
	{
		TriggerToolTip(); 
	}

	CStatic::OnMouseMove(nFlags, point);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/uibase/DSTStatic.cpp-arc  $
//
//   Rev 1.4   Jun 24 2005 17:02:32   Fengyong
//PET1250 FN02 - EuroPean numeric enhancement
 * 
 *    Rev 1.3   Oct 09 2002 17:42:48   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.2   Sep 10 2002 14:34:38   PURDYECH
 * Base condition split out
 * 
 *    Rev 1.1   03 Apr 2001 11:58:32   KOVACSRO
 * Permission check stuff.
 * 
 *    Rev 1.0   Feb 15 2000 11:01:40   SMITHDAV
 * Initial revision.
// 
//    Rev 1.8   Nov 19 1999 17:37:40   DT24433
// changed to set flag for control not updateable
// 
//    Rev 1.7   Nov 15 1999 14:13:54   DT24433
// removed flag parm in constructor
// 
//    Rev 1.6   Nov 09 1999 15:32:26   DT24433
// force CTRLFLAG_NOT_UPDATABLE on
 * 
 */
