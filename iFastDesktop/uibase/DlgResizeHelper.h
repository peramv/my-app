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

#ifndef DLGRESIZEHELPER_H_
#define DLGRESIZEHELPER_H_

#pragma warning (disable: 4786)
#include <list>

class BaseDlg;
class DlgResizeHelper
{
public:

  // fix horizontal dimension/position
  enum EHFix {
    kNoHFix     = 0,
    kWidth      = 1,
    kLeft       = 2,
    kRight      = 4,
    kWidthLeft  = 3,
    kWidthRight = 5,
    kLeftRight  = 6
  };

  // fix vertical dimension/position
  enum EVFix {
    kNoVFix       = 0,
    kHeight       = 1,
    kTop          = 2,
    kBottom       = 4,
    kHeightTop    = 3,
    kHeightBottom = 5,
    kTopBottom    = 6
  };

  // initialize with parent window, all child windows must already have
  // their original position/size
  void Init(HWND a_hParent, BaseDlg* a_attachWnd);

  // explicitly add a window to the list of child windows (e.g. a sibling window)
  // Note: you've got to call Init() before you can add a window
  void Add(HWND a_hWnd);

  // fix position/dimension for a child window, determine child by...
  // ...HWND...
  BOOL Fix(HWND a_hCtrl, EHFix a_hFix, EVFix a_vFix);
  // ...item ID (if it's a dialog item)...
  BOOL Fix(int a_itemId, EHFix a_hFix, EVFix a_vFix);
  // ...all child windows with a common class name (e.g. "Edit")
  UINT Fix(LPCTSTR a_pszClassName, EHFix a_hFix, EVFix a_vFix);
  // ...or all registered windows
  BOOL Fix(EHFix a_hFix, EVFix a_vFix);

  // resize child windows according to changes of parent window and fix attributes
  void OnSize (int width = -1, int height = -1);
private:

	//Get the smallest percentage that the form can be shrinked
	 double GetSmallestYRatio();

  struct CtrlSize {
    CRect m_origSize;
    HWND  m_hCtrl;
    EHFix  m_hFix;
    EVFix  m_vFix;
    CtrlSize() : m_hFix(kNoHFix), m_vFix(kNoVFix) {
    }
  };
  typedef std::list<CtrlSize> CtrlCont_t;
  CtrlCont_t m_ctrls;
  HWND       m_hParent;
  CRect      m_origParentSize;
  CWnd *  m_attachWnd;
};

	//Status Bar Min Height
  const int INT_MINHEIGHT_STATUSBAR = 12;
	const double DBL_SMALLEST_GAP = 8.0;

#endif // DLGRESIZEHELPER_H_
