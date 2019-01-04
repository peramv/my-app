#pragma once

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

#define IVORY  RGB(255, 255, 220)
#define BLACK	RGB(0, 0, 0)

#undef WIN32UIBASE_LINKAGE
#ifdef WIN32UIBASE_DLL
   #define WIN32UIBASE_LINKAGE CLASS_EXPORT
#else
   #define WIN32UIBASE_LINKAGE CLASS_IMPORT
#endif

#pragma warning( disable: 4275 )
class WIN32UIBASE_LINKAGE DSTMsg : public CStatic
{
// Construction
public:
   DSTMsg(CWnd *pCtrl, COLORREF BkGroundClr = IVORY, COLORREF TextClr = BLACK);
   virtual ~DSTMsg();

   void DelayedDisplay();
   void GetMsg( long MsgId = -1 );
   bool IsMsgAlreadyShown();
   void MouseLeave();
   void SetBackgroundClr(COLORREF _BkClr);
   void SetMessageFromConditions( CONDITIONVECTOR &conditions );
   void SetDelayTime(int ms);
   void SetFontHeight(int h);
   void SetTextClr(COLORREF _TxtClr);
   void ShowMsg( bool bShow, bool bMouseOver = false); 
   void ToggleMsgBox();

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(DSTMsg)
   //}}AFX_VIRTUAL

   // Generated message map functions
protected:
   //{{AFX_MSG(DSTMsg)
   afx_msg void OnPaint();
   afx_msg void OnTimer(UINT nIDEvent);
   //}}AFX_MSG

   DECLARE_MESSAGE_MAP()
   private:
   int FontHeight;
   int DelayTime;
   void Draw( );
   bool _bMsgTurnOnByMouseOver;
   bool _bShow;
   CString _Msg;
   CWnd * _pCtrl;
   COLORREF BkClr, TxtClr;
   CRect MsgRect;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/uibase/DSTMsg.h-arc  $
 * 
 *    Rev 1.4   Nov 13 2002 11:43:22   PURDYECH
 * Fixed up C4275 warning error.
 * 
 *    Rev 1.3   Oct 09 2002 17:42:46   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.2   19 Mar 2002 13:36:16   PURDYECH
 * Added #pragma once include guard
 * Removed compile time "including..." message.
 * 
 *    Rev 1.1   Feb 15 2000 18:58:54   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 11:00:58   SMITHDAV
 * Initial revision.
// 
//    Rev 1.5   Nov 22 1999 11:34:08   YINGZ
// tooltip is now below the control
// 
//    Rev 1.4   Nov 05 1999 15:33:46   DT24433
// added initial condition handling
// 
//    Rev 1.3   Nov 04 1999 07:52:30   DT24433
// change BOOL to bool, misc
 * 
 */
