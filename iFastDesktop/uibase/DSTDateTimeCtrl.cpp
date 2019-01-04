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
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : DSTDateTimeCtrl.cpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 07/14/1999
//
// ----------------------------------------------------------
//
// ^CLASS    : DSTDateTimeCtrl
//
// ^MEMBER VARIABLES :
//
//
//******************************************************************************

#define WIN32UIBASE_DLL

#include "stdafx.h"
#include "DSTDateTimeCtrl.h"
#include <ClientLocale.hpp>
#include <bfutil\ClientLocaleContext.hpp>
#include <ConfigManager.hpp>
#include "DSTOleDateTime.h"

namespace CND
{
}
#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DSTDateTimeCtrl

DSTDateTimeCtrl::DSTDateTimeCtrl()
{
}

DSTDateTimeCtrl::~DSTDateTimeCtrl()
{
}


BEGIN_MESSAGE_MAP(DSTDateTimeCtrl, CDateTimeCtrl)
//{{AFX_MSG_MAP(DSTDateTimeCtrl)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DSTDateTimeCtrl message handlers

// return 0 when ok, otherwise, Out will be the same as it is input
void DSTDateTimeCtrl::GetDateInHostFormat( CString &strOut )
{
   /*DString mask;

   //  look in the registry for the date format mask
   DString dstrConfiguration( I_( "HostMasks" ) );
   DString dstrKey( I_("D") );

   mask = GetConfigValueAsString( I_( "LocaleFormats" ), 
                                  dstrConfiguration,
                                  dstrKey );

   if ( mask.length() )
   {
    COleDateTime Date;
    GetTime( Date ) ;
    CString tmp;
    tmp=mask.c_str();
    tmp.Replace(_T("dd"),_T("%d"));
    tmp.Replace(_T("MM"),_T("%m"));
    tmp.Replace(_T("yyyy"),_T("%Y"));

    Out=Date.Format(tmp);

    return 0;
   }
  else
    return 1;*/

   strOut.Empty();

   DSTOleDateTime date;
   GetTime( date ) ;
   date.DSTHostFormat( strOut );
}

void DSTDateTimeCtrl::PreSubclassWindow() 
{
   DString mask;
   // get the language, country, variant string from the current locale
   const DString &lcv = ClientLocaleContext::get().getLocale();

   //  look in the registry for the date format mask
   DString dstrConfiguration( I_( "DisplayMasks" ) );
   DString dstrType( I_( "-D" ) );
   DString dstrKey( lcv );
   dstrKey.append( dstrType );

   mask = GetConfigValueAsString( I_( "LocaleFormats" ), 
                                  dstrConfiguration,
                                  dstrKey );
   if( mask.length() )
   {
      CString strMask( mask.c_str() );
      strMask.Replace( _T( "/" ), _T( "\'/\'" ) );
      strMask.Replace( _T( "yyyy" ), _T( "yyy" ) );
      //SetFormat(mask.c_str());
      SetFormat( strMask );
   }

   CDateTimeCtrl::PreSubclassWindow();
}

BOOL DSTDateTimeCtrl::PreTranslateMessage(MSG* pMsg) 
{
   if( pMsg->message==WM_KEYDOWN && (int)(pMsg->wParam)==VK_RETURN )
   {
      SendMessage(WM_KILLFOCUS);
      SendMessage(WM_SETFOCUS);
   }

   return(CDateTimeCtrl::PreTranslateMessage(pMsg));
}
