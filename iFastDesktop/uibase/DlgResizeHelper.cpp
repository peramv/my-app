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
// ^FILE   : DlgResizeHelper.cpp
// ^AUTHOR : 
// ^DATE   : 09/2005
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : DlgResizeHelper
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  : This is the resize help class.
//
//******************************************************************************

#include "stdafx.h"
#include "DlgResizeHelper.h"
#include "BaseDlg.h"

#include <afxwin.h>

void DlgResizeHelper::Init(HWND a_hParent, BaseDlg* a_attachWnd)  
{ 
  m_hParent = a_hParent; 
  m_attachWnd = a_attachWnd; 
  m_ctrls.clear(); 
  if (::IsWindow(m_hParent))  
  { 
    // keep original parent size 
    ::GetWindowRect(m_hParent, m_origParentSize); 
 
    // get all child windows and store their original sizes and positions 
    HWND hCtrl = ::GetTopWindow(m_hParent); 
    while (hCtrl)  
	{ 
      CtrlSize cs; 
      cs.m_hCtrl = hCtrl; 
      ::GetWindowRect(hCtrl, cs.m_origSize); 
      ::ScreenToClient(m_hParent, &cs.m_origSize.TopLeft()); 
      ::ScreenToClient(m_hParent, &cs.m_origSize.BottomRight()); 
      m_ctrls.push_back(cs); 
 
      hCtrl = ::GetNextWindow(hCtrl, GW_HWNDNEXT); 
    } 
  } 
} 
 
void DlgResizeHelper::Add(HWND a_hWnd)  
{ 
  if (m_hParent && a_hWnd)  
  { 
    CtrlSize cs; 
    cs.m_hCtrl = a_hWnd; 
    ::GetWindowRect(a_hWnd, cs.m_origSize); 
    ::ScreenToClient(m_hParent, &cs.m_origSize.TopLeft()); 
    ::ScreenToClient(m_hParent, &cs.m_origSize.BottomRight()); 
    m_ctrls.push_back(cs); 
  } 
} 
 
void DlgResizeHelper::OnSize(int width /*= -1*/, int height /*= -1*/ )  
{ 
   bool isBrowser = false;  
   BaseDlg* pBaseDlg = dynamic_cast< BaseDlg* > ( m_attachWnd);
   if(pBaseDlg && pBaseDlg->IsBrowserBasedDialog())
      isBrowser = true;
   
   if (::IsWindow(m_hParent))  
   { 
      CRect currParentSize;  
      int width_ (width), 
         height_ (height); 

      if (width_ == -1 || height_ == -1) 
      {		 
         ::GetWindowRect (m_hParent, currParentSize); 
         width_ = currParentSize.Width(); 
         height_ = currParentSize.Height(); 
      } 

      double xRatio = 1; 
      double yRatio = 1; 

      if( width_ != 0 && height_ != 0 ) 
      { 
         xRatio = ((double) width_) / m_origParentSize.Width(); 
         yRatio = ((double) height_) / m_origParentSize.Height(); 

      }	 
      if( yRatio > 1 && !isBrowser) yRatio = 1;	 

      //double dblSmallestYRatio = 1; 
      //dblSmallestYRatio = GetSmallestYRatio(); 
      //yRatio = (yRatio < dblSmallestYRatio) ? dblSmallestYRatio : yRatio; 

      CRect wndRect; 
      ::GetWindowRect(m_hParent, &wndRect); 
      MoveWindow(m_hParent, wndRect.left, wndRect.top, INT(xRatio * m_origParentSize.Width()), INT(yRatio* m_origParentSize.Height()), TRUE); 
      
      ::GetWindowRect(m_hParent, &wndRect); 
      
      CRect clientRect; 
      ::GetClientRect(m_hParent, &clientRect); 

      height_ = INT(yRatio* m_origParentSize.Height()); 

      CFont* m_pFont = NULL; 
      BaseDlg * pBaseDlg = dynamic_cast< BaseDlg * > ( m_attachWnd ); 
      if( pBaseDlg ) 
      { 
         int fontsize = (yRatio == 1 && xRatio < 1) ? INT((xRatio) * 10 ) * 10 : INT((yRatio) * 10 ) * 10; 
         m_pFont = new CFont; 
         if (m_pFont) 
         { 
            CString strFaceName ("MS Sans Serif"); 
            m_pFont->CreatePointFont (fontsize, strFaceName); 
            pBaseDlg->SetDlgFont (m_pFont); 
         } 
      } 
      // resize child windows according to their fix attributes 
      CtrlCont_t::const_iterator it; 
      for (it = m_ctrls.begin(); it != m_ctrls.end(); ++it)  
      { 
         CRect currCtrlSize; 
         EHFix hFix = it->m_hFix; 
         EVFix vFix = it->m_vFix; 

         CWnd * pwnd = CWnd::FromHandle( it->m_hCtrl ); 
         CStatusBar * pStatusBar = dynamic_cast< CStatusBar * > ( pwnd );	 

         // might go easier ;-) 
         if(!isBrowser)
         {
            if (hFix & kLeft) 
            { 
               currCtrlSize.left = it->m_origSize.left; 
            } 
            else 
            { 
               currCtrlSize.left = ((hFix & kWidth) && (hFix & kRight)) ? (it->m_origSize.left + currParentSize.Width() - m_origParentSize.Width()) : (long)(it->m_origSize.left * xRatio); 
            } 

            if (hFix & kRight) 
            { 
               currCtrlSize.right = it->m_origSize.right + currParentSize.Width() - m_origParentSize.Width(); 
            } 
            else 
            { 
               currCtrlSize.right = (hFix & kWidth) ? (currCtrlSize.left + it->m_origSize.Width()) : (long)(it->m_origSize.right * xRatio); 
            } 
         }
         else
         {
            currCtrlSize.left = 0;
            currCtrlSize.right = clientRect.Width();
         }

         if (pStatusBar != NULL )  
         { 
            if(!isBrowser)
            {
               currCtrlSize.bottom = (yRatio == 1) ? it->m_origSize.bottom : height_ - (m_origParentSize.Height() - it->m_origSize.bottom);	   

               if (( it->m_origSize.bottom - it->m_origSize.top) * yRatio < INT_MINHEIGHT_STATUSBAR) 
               { 
                  currCtrlSize.top = currCtrlSize.bottom - INT_MINHEIGHT_STATUSBAR; 
               } 
               else 
               { 
                  currCtrlSize.top = INT(currCtrlSize.bottom - (it->m_origSize.bottom - it->m_origSize.top) * yRatio); 
               } 
            }
            else
            {
               currCtrlSize.top    = clientRect.Height()- 18;	   
               currCtrlSize.bottom = clientRect.Height();	   
            }
            MoveWindow(it->m_hCtrl, currCtrlSize.left, currCtrlSize.top, currCtrlSize.Width(), currCtrlSize.Height(), TRUE);	  	   

         } 
         else 
         { 
            if(!isBrowser)
            {
               if (vFix & kTop) 
               { 
                  currCtrlSize.top = it->m_origSize.top; 
               } 
               else 
               { 
					currCtrlSize.top = ((vFix & kHeight) && (vFix & kBottom)) ? (it->m_origSize.top + height_ - m_origParentSize.Height()) : (long)(it->m_origSize.top * yRatio); 
               } 
               if (vFix & kBottom) 
               { 
                  currCtrlSize.bottom = it->m_origSize.bottom + height_ - m_origParentSize.Height(); 
               } 
               else 
               { 
					currCtrlSize.bottom = (vFix & kHeight) ? (currCtrlSize.top + it->m_origSize.Height()) : (long)(it->m_origSize.bottom * yRatio);		  		   
               } 
            }
            else
            {
               currCtrlSize.top = 0;
               currCtrlSize.bottom = clientRect.Height() - 18;
            }

            CComboBox * pComboBox = dynamic_cast< CComboBox * > ( pwnd ); 
            if( pComboBox == NULL)  
            { 
               // resize child window 
               MoveWindow(it->m_hCtrl, currCtrlSize.left, currCtrlSize.top, currCtrlSize.Width(), currCtrlSize.Height(), TRUE);	  	   
            } 
            else 
            { 
               MoveWindow(it->m_hCtrl, currCtrlSize.left, currCtrlSize.top, currCtrlSize.Width(), INT(currCtrlSize.Height()*0.8), TRUE);	  	  		 
            } 
         }      

         if( !isBrowser && m_pFont )  
         {		 
            pwnd->SetFont (m_pFont); 
         }			 
      }	 

      if( pBaseDlg ) 
      { 
         pBaseDlg->ShowWindow(SW_SHOWNA); 
         //pBaseDlg->SetFocus(); 
      } 
   } 
} 
 
BOOL DlgResizeHelper::Fix(HWND a_hCtrl, EHFix a_hFix, EVFix a_vFix) 
{
  CtrlCont_t::iterator it;
  for(it = m_ctrls.begin(); it!=m_ctrls.end(); ++it) 
  {
    if (it->m_hCtrl == a_hCtrl) 
	{
      it->m_hFix = a_hFix;
      it->m_vFix = a_vFix;
      return TRUE;
    }
  }
  return FALSE;
}

BOOL DlgResizeHelper::Fix(int a_itemId, EHFix a_hFix, EVFix a_vFix) 
{
  return Fix(::GetDlgItem(m_hParent, a_itemId), a_hFix, a_vFix);
}

BOOL DlgResizeHelper::Fix(EHFix a_hFix, EVFix a_vFix) 
{
  CtrlCont_t::iterator it;
  for(it = m_ctrls.begin(); it!=m_ctrls.end(); ++it) 
  {
    it->m_hFix = a_hFix;
    it->m_vFix = a_vFix;
  }
  return TRUE;
}

UINT DlgResizeHelper::Fix(LPCTSTR a_pszClassName, EHFix a_hFix, EVFix a_vFix) 
{
  UINT cnt = 0;
/*
  CtrlCont_t::iterator it;
  char pszCN[200];
  for(it = m_ctrls.begin(); it!=m_ctrls.end(); ++it) 
  {
    ::GetClassName(it->m_hCtrl, pszCN, sizeof(pszCN));	
    if (strcmp(pszCN, &tmp) == 0) {
      cnt++;
      it->m_hFix = a_hFix;
      it->m_vFix = a_vFix;
    }
  }
*/
  return cnt;
}

double DlgResizeHelper::GetSmallestYRatio()
{
	 CtrlCont_t::const_iterator it;

	 int intLagestButtom = 0;
	 int intStatusTop = 0;
	 double dblPercentage = 0;

    for (it=m_ctrls.begin(); it!=m_ctrls.end(); ++it) 
		{
    	CWnd * pwnd = CWnd::FromHandle( it->m_hCtrl );
			CStatusBar * pStatusBar = dynamic_cast< CStatusBar * > ( pwnd );	
		
			if (pStatusBar != NULL)
			{
				intStatusTop = it->m_origSize.top;
			}
			else
			{
				intLagestButtom = (intLagestButtom < it->m_origSize.bottom)? it->m_origSize.bottom : intLagestButtom;
			}
		}
		dblPercentage = (intLagestButtom > intStatusTop || DBL_SMALLEST_GAP > (intStatusTop -intLagestButtom))? 1 : DBL_SMALLEST_GAP/(intStatusTop -intLagestButtom);

		return (dblPercentage);
}
