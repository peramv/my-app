// DSTButton.cpp : implementation file
//

#define WIN32UIBASE_DLL

#include "stdafx.h"

//removed for new arch
//#include "mfdstc.h"
#include "DSTButton.h"

namespace CND
{
}
#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DSTButton

DSTButton::DSTButton(
                    BaseDlg *rpParent,
                    UINT controlID
                    ) :
BaseControl( rpParent, controlID )
{
   SubclassDlgItem( controlID, reinterpret_cast<CWnd *>( rpParent ) );
}

DSTButton::~DSTButton()
{
}


BEGIN_MESSAGE_MAP(DSTButton, CButton)
//{{AFX_MSG_MAP(DSTButton)
// NOTE - the ClassWizard will add and remove mapping macros here.
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DSTButton message handlers

void DSTButton::DoGetText(
                         DString &strValueOut,
                         int index
                         ) const
{
}

//******************************************************************************

void DSTButton::DoInit()
{
   int i=0;
}

//******************************************************************************

bool DSTButton::DoSetText(
                         const DString &strValueIn,
                         int index
                         )
{
   return(true);
}

//******************************************************************************

bool DSTButton::doSetCtrlReadOnly(bool bReadOnly)
{
   EnableWindow(!bReadOnly);
   return(true);
}
