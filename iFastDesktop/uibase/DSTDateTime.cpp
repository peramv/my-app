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
// ^FILE   : DSTDateTime.cpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 07/14/1999
//
// ----------------------------------------------------------
//
// ^CLASS    : DSTDateTime
//
// ^MEMBER VARIABLES :
//
//
//******************************************************************************

#define WIN32UIBASE_DLL

#include "stdafx.h"
#include "DSTDateTime.h"
#include <ClientLocale.hpp>
#include <bfutil\ClientLocaleContext.hpp>
#include <ConfigManager.hpp>
#include "DstcFuncs.h"
#include "DSTOleDateTime.h"

namespace CND
{
}

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//******************************************************************************

DSTDateTime::DSTDateTime(
                        BaseDlg *rpParent,
                        UINT controlID,
                        DString Type
                        ) :
BaseControl( rpParent, controlID ),
OriginalStr(NULL_STRING),
IsDropdown(FALSE)
{
   m_Type = Type;

   SubclassDlgItem( controlID, reinterpret_cast<CWnd *>( rpParent ) );

   COleDateTime maxDate( 9999, 12, 31, 0, 0, 0 );

   SetRange( NULL, &maxDate );
}

//******************************************************************************

DSTDateTime::~DSTDateTime()
{
}

//******************************************************************************

BEGIN_MESSAGE_MAP(DSTDateTime, CDateTimeCtrl)
//{{AFX_MSG_MAP(DSTDateTime)
ON_WM_KILLFOCUS()
ON_WM_SETFOCUS()
ON_WM_MOUSEMOVE()
ON_NOTIFY_REFLECT(DTN_DROPDOWN, OnDropdown)
ON_NOTIFY_REFLECT(DTN_CLOSEUP, OnCloseUp)
ON_WM_LBUTTONDOWN()
//}}AFX_MSG_MAP
ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DSTDateTime message handlers

// return 0 when ok, otherwise, Out will be the same as it is input
void DSTDateTime::GetDateInHostFormat( CString &strOut ) const
{
   strOut.Empty();

   DSTOleDateTime date;
   GetTime( date ) ;
   date.DSTHostFormat( strOut );
}

//******************************************************************************

void DSTDateTime::PreSubclassWindow() 
{
   DString mask;
   // get the language, country, variant string from the current locale
   const DString &lcv = ClientLocaleContext::get().getLocale();

   //  look in the registry for the date format mask
   DString dstrConfiguration( I_( "DisplayMasks" ) );
   DString dstrType( I_( "-" ) );
   dstrType.append( m_Type );
   DString dstrKey( lcv );
   dstrKey.append( dstrType );

   mask = GetConfigValueAsString( I_( "LocaleFormats" ), 
                                  dstrConfiguration,
                                  dstrKey );
   m_strFormat = _T("");

   // Defaults
   if( mask.length() == 0 )
   {
      if( m_Type == I_("T") )
      {
         mask = I_("HH:mm");
      }
   }

   // Change
   if( mask.length() )
   {
      CString strMask( mask.c_str() );
      
      // Date Mask changes
      strMask.Replace( _T( "/" ), _T( "\'/\'" ) );
      strMask.Replace( _T( "yyyy" ), _T( "yyy" ) );

      SetFormat( strMask );
      m_strFormat = mask.c_str();
   }

   CDateTimeCtrl::PreSubclassWindow();
}

//******************************************************************************

BOOL DSTDateTime::PreTranslateMessage(MSG* pMsg) 
{  
   if( pMsg->message == WM_KEYDOWN && !IsUpdateable() )
      if( !( pMsg->wParam == VK_TAB || pMsg->wParam == VK_LEFT || pMsg->wParam == VK_RIGHT || pMsg->wParam == VK_ESCAPE ) )
         return(TRUE);

   if( pMsg->message==WM_KEYDOWN )
   {
      switch( (pMsg->wParam) )
      {
         case VK_RETURN:
            SendMessage(WM_KILLFOCUS);
            SendMessage(WM_SETFOCUS);
            break;

         case VK_F11:
            ToggleToolTip();
            break;
      }
   }

   return(CDateTimeCtrl::PreTranslateMessage(pMsg));
}

//******************************************************************************

void DSTDateTime::OnKillFocus(CWnd* pNewWnd) 
{
   CDateTimeCtrl::OnKillFocus(pNewWnd);

   //ValidateAndSetDate();	

   // drop down cause kill focus so that old date is read
   if( IsDropdown )
   {
      IsDropdown = FALSE;
   }
   else
   {
      DoKillFocus();
   }
}

//******************************************************************************
void DSTDateTime::OnCloseUp(NMHDR* pNMHDR, LRESULT* pResult) 
{	
	DoKillFocus();
}

//******************************************************************************
// Set the date back if the Date is over 9999
// This is due to the bug of MS - DataTimeCtrl 
//
void DSTDateTime::ValidateAndSetDate() 
{
   if( m_strFormat == _T("") )
      return;

   CString strTime, strYear, strMon, strDay;
   GetWindowText(strTime);
   strYear = _T("");
   strMon  = _T("");
   strDay  = _T("");
   m_strFormat.MakeUpper();
   int iYPos = m_strFormat.Find('Y');
   int iMPos = m_strFormat.Find('M');
   int iDPos = m_strFormat.Find('D');
   if( iYPos >= 0 )
   {
      bool bFoundSep = false;
      for( int i = iYPos; i < strTime.GetLength(); i++ )
      {
         if( !_istdigit(strTime.GetAt(i)) )
         {
            bFoundSep = true;
            strYear = strTime.Mid(iYPos, i - iYPos);
            if( strYear.GetLength() > 4 )
            {
               strTime.Replace( strYear, _T("9999"));
               strMon = strTime.Mid(iMPos, 2);
               strDay = strTime.Mid(iDPos, 2);
            }
            break;
         }
      }
      if( !bFoundSep )
      {
         strYear = strTime.Mid(iYPos);
         if( strYear.GetLength() > 4 )
         {
            strTime.Replace( strYear, _T("9999"));
            strMon = strTime.Mid(iMPos, 2);
            strDay = strTime.Mid(iDPos, 2);
         }
      }
   }
   if( strMon != _T("") )
   {
      COleDateTime dtDateTime(9999, _ttoi(strMon), _ttoi(strDay), 0, 0, 0);
      SetTime( dtDateTime );
   }
}

//******************************************************************************

void DSTDateTime::OnSetFocus(CWnd* pOldWnd) 
{
   CDateTimeCtrl::OnSetFocus(pOldWnd);
   DoSetFocus();
}

//******************************************************************************

LRESULT DSTDateTime::OnMouseLeave(WPARAM , LPARAM )
{
   MouseLeave();

   return(0);
}

//******************************************************************************

void DSTDateTime::OnMouseMove(UINT nFlags, CPoint point) 
{
   if( IsError() /*&& !IsToolTipVisible()*/ )
   {
      TriggerToolTip(); 
   }

   CDateTimeCtrl::OnMouseMove(nFlags, point);
}

//******************************************************************************
// get text in display format instead of host format
void DSTDateTime::DoGetText(
                           DString &strValueOut,
                           int index
                           ) const
{
   DSTOleDateTime date;
   GetTime(date);

   if( date.GetDay() == 31 && date.GetMonth() == 12 && date.GetYear() == 9999 && m_Type == I_("D") )
   {
      strValueOut = OriginalStr;
   }
   else if( date.GetHour() == 0 && date.GetMinute() == 0 && m_Type == I_("T") )
   {
      strValueOut = OriginalStr;
   }
   else
   {
      CString tmp;
      date.DSTHostFormat( tmp, m_Type );
      strValueOut = tmp.GetBuffer(0);
      tmp.ReleaseBuffer(-1);
   }
}

//******************************************************************************

void DSTDateTime::DoInit()
{
   SetLoadDisplayFormat( false );
}

//******************************************************************************
// strValueIn must be in host format
bool DSTDateTime::DoSetText(
                           const DString &strValueIn,
                           int index
                           )
{
   DString tmp=strValueIn;

   if(( tmp.strip() == NULL_STRING || tmp.find( I_("9999") ) != DString::npos ) && m_Type == I_("D") )
   {
      OriginalStr = strValueIn;
      SetTo9999();
   }
   else if( (tmp.strip() == NULL_STRING || tmp.find( I_("00:00") ) != DString::npos ) && m_Type == I_("T") )
   {
      OriginalStr = strValueIn;
      SetTimeTo0000();
   }
   else
   {
      COleDateTime date;
      setOleDateFromHost(date, const_cast<DString&>(strValueIn), m_Type );
      SetTime( date );
   }

   return(true);
}

//******************************************************************************

void DSTDateTime::SetToToday()
{
   COleDateTime date;
   date=COleDateTime::GetCurrentTime();
   SetTime( date );
}

//******************************************************************************

void DSTDateTime::DoClear()
{
   //SetToToday();
   if( m_Type == I_("D") )
   {
      SetTo9999();
   }
   else
   {
      SetTimeTo0000();
   }
}

//******************************************************************************

void DSTDateTime::SetTo9999()
{
   COleDateTime date( 9999, 12, 31, 0, 0, 0 );
   SetTime( date );
}

//******************************************************************************

void DSTDateTime::SetTimeTo0000()
{
   COleDateTime date( 1899, 12, 30, 0, 0, 0 );  // Dec. 30, 1899
   SetTime( date );
}

//******************************************************************************

void DSTDateTime::OnDropdown(NMHDR* pNMHDR, LRESULT* pResult) 
{
   // TODO: Add your control notification handler code here
   IsDropdown = TRUE;

   *pResult = 0;
}

//******************************************************************************

bool DSTDateTime::doSetCtrlReadOnly(bool bReadOnly)
{
   return(true);
}
//******************************************************************************

void DSTDateTime::OnLButtonDown(UINT nFlags, CPoint point) 
{
   // TODO: Add your message handler code here and/or call default
   if( IsUpdateable() )
      CDateTimeCtrl::OnLButtonDown(nFlags, point);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/uibase/DSTDateTime.cpp-arc  $
//
//   Rev 1.14   Jul 11 2005 13:46:40   hernando
//PET1250 FN01 - Added default Time mask.
//
//   Rev 1.13   Jul 06 2005 14:01:44   hernando
//PET1250 FN01 - Added support for time.
//
//   Rev 1.12   Nov 12 2004 14:04:42   YINGBAOL
//reverse version 1.11, put the logic in dialog class
//
//   Rev 1.11   Sep 29 2004 09:56:00   YINGBAOL
//PTS10034116:when user change date to 12/31/9999, desktop save null string to database
//
//   Rev 1.10   Sep 27 2004 09:32:06   FENGYONG
//PTS10024458 - do not check visible before show error message
 * 
 *    Rev 1.9   Oct 09 2002 17:42:42   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.8   Sep 10 2002 14:34:34   PURDYECH
 * Base condition split out
 * 
 *    Rev 1.7   Aug 29 2002 12:57:34   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.6   Jul 05 2002 10:45:44   PURDYECH
 * Include file cleanup.
 * 
 *    Rev 1.5   21 Sep 2001 15:43:20   HSUCHIN
 * bug fix for readonly control where tab sequence was lost
 * 
 *    Rev 1.4   06 Apr 2001 11:12:22   KOVACSRO
 * Made control act as non updateable if it is readonly.
 * 
 *    Rev 1.3   03 Apr 2001 11:55:38   KOVACSRO
 * Permission check stuff.
 * 
 *    Rev 1.2   30 Mar 2001 12:11:06   KOVACSRO
 * Added SetCtrlReadOnly()
 * 
 *    Rev 1.1   Jun 13 2000 17:51:38   DT24433
 * new Infra interfaces use ClientLocale
 * 
 *    Rev 1.0   Feb 15 2000 11:01:40   SMITHDAV
 * Initial revision.
// 
//    Rev 1.13   Feb 08 2000 13:43:24   YINGZ
// comment ValidateAndSetDate
// 
//    Rev 1.12   Feb 08 2000 13:34:16   YINGZ
// set max date to be 12/31/9999
// 
//    Rev 1.11   Feb 07 2000 14:34:02   HUANGSHA
// Put the Year back if it is over 9999
// 
//    Rev 1.10   Jan 20 2000 14:50:48   DT24433
// changed to return data in host format
// 
//    Rev 1.9   Dec 12 1999 11:40:30   YINGZ
// fix drop down cause old date to be read problem
// 
//    Rev 1.8   Dec 09 1999 13:40:14   YINGZ
// base already got 12/31/9999! got it
// 
//    Rev 1.7   Dec 09 1999 11:34:16   YINGZ
// set default date to 12/31/9999
// 
//    Rev 1.6   Nov 23 1999 15:39:44   YINGZ
// change DoGetText to get display format
// 
//    Rev 1.5   Nov 15 1999 14:08:28   DT24433
// removed flag parm in constructor
// 
//    Rev 1.4   Nov 05 1999 11:24:28   YINGZ
// just check in so it can be used
// 
//    Rev 1.3   Nov 03 1999 15:14:40   DT24433
// change DoInit
 * 
 */


