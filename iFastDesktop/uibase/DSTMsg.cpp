// DSTMsg.cpp : implementation file
//

#define WIN32UIBASE_DLL

#include "stdafx.h"
#include "DSTMsg.h"
#ifndef CONFIGMANAGER_HPP
   #include <configManager.hpp>
#endif

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const int DISTANCE = 4; // gap between control and msg box
   const int EDGE = 5;      // edge around text in msg box
   const int MIN_WIDTH = 150; // min width of the msg box
}

namespace CND
{
}
/////////////////////////////////////////////////////////////////////////////
// DSTMsg

DSTMsg::DSTMsg(CWnd *pCtrl, COLORREF BkGroundClr, COLORREF TextClr) :
_bShow( false ),
_bMsgTurnOnByMouseOver( false ),
DelayTime(500),
FontHeight(10)
{
   _pCtrl = pCtrl;
   BkClr = BkGroundClr;
   TxtClr = TextClr;

   CRect r(0,0,1,1);
   Create( NULL, WS_CHILD | WS_BORDER | SS_WHITERECT, r, _pCtrl->GetParent() );
}

DSTMsg::~DSTMsg()
{
}

BEGIN_MESSAGE_MAP(DSTMsg, CStatic)
//{{AFX_MSG_MAP(DSTMsg)
ON_WM_PAINT()
ON_WM_TIMER()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DSTMsg message handlers
void DSTMsg::ShowMsg( bool bShow, bool bMouseOver )
{
   _bMsgTurnOnByMouseOver = bMouseOver;
   if( !( _bShow = bShow) )
   {
      MsgRect.InflateRect(EDGE+1, EDGE+1);

      if( _pCtrl->GetSafeHwnd() && _pCtrl->GetParent()->GetSafeHwnd() )
      {
         _pCtrl->GetParent()->InvalidateRect(MsgRect);
         _pCtrl->GetParent()->UpdateWindow();
      }
   }
   else
   {
      Draw();
   }
}

void DSTMsg::Draw( )
{
   if( _bShow && !_Msg.IsEmpty() )
   {
      ShowWindow(SW_SHOW);

      // get rect
      WINDOWPLACEMENT wp;                

      _pCtrl->GetWindowPlacement( &wp );

      int MsgBoxWidth = wp.rcNormalPosition.right - wp.rcNormalPosition.left ;

      MsgBoxWidth = ( MsgBoxWidth > MIN_WIDTH )? MsgBoxWidth : MIN_WIDTH;

      MsgRect = CRect(wp.rcNormalPosition.left,wp.rcNormalPosition.top-100,
                      wp.rcNormalPosition.left + MsgBoxWidth,wp.rcNormalPosition.top-4);

      CDC *pDC=GetDC();

      // change font
      LOGFONT logFont;
      CFont* pFont = _pCtrl->GetFont();
      pFont->GetLogFont(&logFont);

      CFont hFont,*holdFont;
/**
    LOGFONT Font;
    memset(&Font,0,sizeof(LOGFONT));
    lstrcpy(Font.lfFaceName,_T("MS Sans Serif"));
    Font.lfHeight=FontHeight;
    hFont.CreateFontIndirect(&Font);
    holdFont=pDC->SelectObject(&hFont);
*/
      holdFont = pDC->SelectObject(pFont);

      pDC->DrawText( _Msg,  MsgRect, DT_CALCRECT | DT_LEFT | DT_NOCLIP | DT_WORDBREAK);

      MsgRect.InflateRect(EDGE, EDGE);
      int tmp=MsgRect.bottom-MsgRect.top;

      //Decide the tooptip's position based on the Registry Setting
      DString dstrPosition = GetConfigValueAsString(I_("LocaleFormats"), 
                                                    I_("Tooltips"), I_("Position"));
      dstrPosition.strip().upperCase();
      if( dstrPosition == NULL_STRING )
      {
         WriteConfigValue(I_("LocaleFormats"),I_("Tooltips"), I_("Position"), I_("Below"));  //Below or Above
         dstrPosition = I_("Below");
      }
      dstrPosition.strip().upperCase();
      if( dstrPosition == I_("ABOVE") )
      {
         MsgRect.top = wp.rcNormalPosition.top - (DISTANCE + tmp);
         MsgRect.bottom = MsgRect.top + tmp;
      }
      else
      {
         // tool tip at bottom
         MsgRect.top = wp.rcNormalPosition.bottom+DISTANCE;
         MsgRect.bottom = MsgRect.top+tmp;
      }
      /*
      MsgRect.bottom = wp.rcNormalPosition.top-DISTANCE;
      MsgRect.top = MsgRect.bottom-tmp;
  
      if(MsgRect.top < 0)
      {
        MsgRect.top = wp.rcNormalPosition.bottom+DISTANCE;
        MsgRect.bottom = MsgRect.top+tmp;
      }
      */

      tmp=wp.rcNormalPosition.right;
      _pCtrl->GetParent()->GetWindowPlacement( &wp );
      if( MsgRect.right + wp.rcNormalPosition.left > wp.rcNormalPosition.right )
      {
         int width=MsgRect.right-MsgRect.left;
         MsgRect.right = tmp;
         MsgRect.left = MsgRect.right-width;
      }

      // set bk clr
      CBrush hBrush,*holdBrush;
      hBrush.CreateSolidBrush(BkClr);
      holdBrush=pDC->SelectObject(&hBrush);
      pDC->Rectangle(MsgRect.left,MsgRect.top,MsgRect.right,MsgRect.bottom);
      pDC->SelectObject(holdBrush);

      pDC->SetBkMode(TRANSPARENT);
      pDC->SetTextColor(TxtClr);

      // write text
      MsgRect.InflateRect(-EDGE, -EDGE);
      pDC->DrawText(_Msg, MsgRect, DT_LEFT | DT_NOCLIP | DT_WORDBREAK);

      // set Z order of tooltip window to top most
      SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0,SWP_NOMOVE|SWP_NOSIZE);

      pDC->SelectObject(holdFont);
   }
}

void DSTMsg::GetMsg(long MsgId)
{
   switch( MsgId )
   {
      case SEVERE_ERROR:
      case CRITICAL_ERROR:
         _Msg=_T("error\r\nNot good");
         break;
      case WARNING:
         _Msg=_T("warning\r\nGetting Better");
         break;
      case INFORMATIONAL:
         _Msg=_T("Info\r\nDont' be scared");
         break;
   }
}

void DSTMsg::OnPaint() 
{
   CPaintDC dc(this); 
   Draw(  );
}

bool DSTMsg::IsMsgAlreadyShown()
{
   return(_bShow);
}

void DSTMsg::DelayedDisplay()
{
   SetTimer(1,DelayTime,NULL);
}

void DSTMsg::OnTimer(UINT nIDEvent) 
{
   KillTimer(1);
   if( !_bShow )
   {
      POINT p;
      GetCursorPos(&p);
      _pCtrl->ScreenToClient(&p);
      if( _pCtrl->ChildWindowFromPoint(p) )
      {
         ShowMsg( true, true );
      }
   }
   else 
   {
      POINT p;
      GetCursorPos(&p);
      _pCtrl->ScreenToClient(&p);
      if( _pCtrl->ChildWindowFromPoint(p) )
      {
         ShowMsg( true, _bMsgTurnOnByMouseOver );
      }

   }

   CStatic::OnTimer(nIDEvent);
}

// TODO - This method may not be needed if we take out keyboard toggling
void DSTMsg::ToggleMsgBox()
{
   if( !_bMsgTurnOnByMouseOver )
   {
      ShowMsg( !_bShow );
   }
}

void DSTMsg::MouseLeave()
{
   if( _bMsgTurnOnByMouseOver )
   {
      ShowMsg( false );
   }
}

void DSTMsg::SetTextClr(COLORREF _TxtClr)
{
   TxtClr = _TxtClr;
}

void DSTMsg::SetBackgroundClr(COLORREF _BkClr)
{
   BkClr = _BkClr;
}

void DSTMsg::SetMessageFromConditions( CONDITIONVECTOR &conditions )
{  // Set up message from conditions
//TODO may want to save pointer to condition vector so can support CTRL+ALT+F1
   _Msg = NULL_STRING;
   //if the same condition appears more than once in the conditions vector, only display it once
   CONDITIONVECTOR conditions1;
   bool bAddCondition ;
   CONDITIONVECTOR::iterator iter = conditions.begin( );
   while( iter != conditions.end( ) )
   {
      bAddCondition = true;
      int condCode = ( *iter )->getCode();
      CONDITIONVECTOR::iterator iter1 = conditions1.begin( );
      while( iter1 != conditions1.end( ) )
      {
         int existentCondCode = ( *iter1 )->getCode();
         if( existentCondCode == condCode )
         {
            bAddCondition = false;
            break;
         }
         ++iter1;
      }
      if( bAddCondition )
         conditions1.push_back( *iter  );
      ++iter;
   }
   for( int i = 0; i < conditions1.size(); i++ )
   {
      _Msg += conditions1[i]->getMessage();
      if( i < conditions1.size()-1 )_Msg += I_( "\r\n" );
   }
}

void DSTMsg::SetDelayTime(int ms)
{
   DelayTime = ms;
}

void DSTMsg::SetFontHeight(int h)
{
   FontHeight = h;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/uibase/DSTMsg.cpp-arc  $
//
//   Rev 1.8   Nov 06 2009 04:10:52   dchatcha
//IN# 1882468 - Overlapping error message display.
//
//   Rev 1.7   Sep 27 2004 09:32:32   FENGYONG
//PTS10024458 - do not check visible before show error message
 * 
 *    Rev 1.6   Oct 09 2002 17:42:46   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.5   Sep 10 2002 14:34:36   PURDYECH
 * Base condition split out
 * 
 *    Rev 1.4   Jun 25 2001 16:08:28   HUANGSHA
 * fix the crash problem when the window is destroyed
 * 
 *    Rev 1.3   Dec 12 2000 16:45:54   HUANGSHA
 * added registry setting to decide the tooptip's display setting
 * 
 *    Rev 1.2   Nov 13 2000 15:34:12   KOVACSRO
 * Modified setMessageFromConditions() not to show the same error more than once.
 * 
 *    Rev 1.1   May 31 2000 16:40:00   HUANGSHA
 * calculate the tooltip size based on the Dialog font
 * 
 *    Rev 1.0   Feb 15 2000 11:01:40   SMITHDAV
 * Initial revision.
// 
//    Rev 1.9   Jan 12 2000 11:52:58   YINGZ
// set min msg box width
// 
//    Rev 1.8   Nov 22 1999 12:00:24   YINGZ
// clear empty line after msg
// 
//    Rev 1.7   Nov 22 1999 11:34:08   YINGZ
// tooltip is now below the control
// 
//    Rev 1.6   Nov 17 1999 10:17:10   YINGZ
// delete anuseless line
// 
//    Rev 1.5   Nov 05 1999 15:32:06   DT24433
// added initial condition handling
// 
//    Rev 1.4   Nov 04 1999 07:51:16   DT24433
// change BOOL to bool, misc
 * 
 */
