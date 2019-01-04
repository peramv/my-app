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

#include <uibase\BaseControl.hpp>

#undef WIN32UIBASE_LINKAGE
#ifdef WIN32UIBASE_DLL
   #define WIN32UIBASE_LINKAGE CLASS_EXPORT
#else
   #define WIN32UIBASE_LINKAGE CLASS_IMPORT
#endif

#pragma warning( disable: 4275 )
class WIN32UIBASE_LINKAGE DSTEdit : public CEdit, public BaseControl
{
// Construction
public:
   enum INPUT_ALLOWED
   {
      GENERAL, UNSIGNED, INTEGER, UNSIGNED_DECIMAL, DECIMAL
   };
   DSTEdit(
          BaseDlg *rpParent,
          UINT controlID
          );
   virtual ~DSTEdit();
   void SetMaxCharNum( long lMaxCharNum );
   void SetAllowedChars( LPCTSTR strAllowedChars );
   void SetAllDigits(bool bAllDigits);
   void AllowNonnegativeDecimalNumbers( int iMaxNumDigitsBeforeDecimalPoint,
                                        int iMaxNumDigitsAfterDecimalPoint );    

   void setMaxNumDigitsBeforeDecimalPoint( int iMaxNumDigitsBeforeDecimalPoint ) 
			{ _iMaxNumDigitsBeforeDecimalPoint = iMaxNumDigitsBeforeDecimalPoint; }

   void setMaxNumDigitsAfterDecimalPoint( int iMaxNumDigitsAfterDecimalPoint ) 
			{ _iMaxNumDigitsAfterDecimalPoint = iMaxNumDigitsAfterDecimalPoint; } 
   void setInputAllowedUnsignedDecimal()
			{ _enInputAllowed = UNSIGNED_DECIMAL; }

   void setInputAllowedDecimal();

   /**
    * Currently the converting routine only vavid for unicode mode
    * The related functions needs to be changed for the non-unicode mode
    */
   void SetKanaEdit(DSTEdit* pKanaEdit);
   void SetKanjiStatus(BOOL bKanjiStatus) {_bKanjiStatus = bKanjiStatus;}
   HWND getToFocusHwnd() {return(_hwndGetFocus);}             // handle of the window be focused

   /**
     Resize the edit control's client area based on the selected fixed font and 
     the maximum allowed number of characters
     */
   void ResizeEditArea();
   void SetFixedWrappingFlag(bool bFixWrappingFlag = true) { _bFixWrappingFlag = bFixWrappingFlag;}
   /**
     set the window font as the fixed font
     */
   void SelectFixedFont();          
   static void SetFixedFont(CFont* pFixedFont) {_pFixedFont = pFixedFont;}
   bool IsSetAsReadOnly() {return(m_bSetAsReadOnly);}
   BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);

	void setNumLine( int iNumLine = -1 );
	bool isWordWrappingInProcess(){return m_bWordWrapInProcess;};

    void SetRemoveUnwantedCharsAfterPaste(bool bRemove);

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(DSTEdit)
public:
   virtual BOOL PreTranslateMessage(MSG* pMsg);
   //}}AFX_VIRTUAL

   // Generated message map functions
protected:
   //{{AFX_MSG(DSTEdit)
   afx_msg void OnKillFocus(CWnd* pNewWnd);
   afx_msg void OnSetFocus(CWnd* pOldWnd);
   afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
   afx_msg void OnMouseMove(UINT nFlags, CPoint point);
   afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
   afx_msg void OnUpdate();
   //}}AFX_MSG
   LRESULT OnMouseLeave(WPARAM a=0, LPARAM b=0L);

   DECLARE_MESSAGE_MAP()
   /**
    * This method is called from BaseControl::GetText and is expected to return
    * the value of the control in the string provided.
    * 
    * @param strValueOut
    *               reference of string where value is returned.
    * @param index  this value is not used by this override of the method.
    */
   virtual void DoGetText( DString &strValueOut, int index=0 ) const;
   /**
    * This method is called from BaseControl::Init to allow us to get new
    * properties.
    * This may be called more than once (to allow the same control to be tied
    * to different fields, depending on context).
    */
   virtual void DoInit();
   /**
    * This method is called from BaseControl::SetText and is expected to sets
    * the value of the control to the specified value.
    * 
    * @returns flag with true = success, false = failure, check conditions
    * @param strValueIn value to set.
    * @param index      not used by this class
    * 
    * @return 
    */
   virtual bool DoSetText( const DString &strValueIn, int index=0 );
   virtual void DoClear();
   bool doSetCtrlReadOnly(bool bReadOnly);
   void SetFlags( UINT flags );	

private:
   bool RemovingCharsAllowed( UINT nChar );
   BOOL SetEditReadOnly(bool bReadOnly = true);
   void multilineWordWrap(UINT nChar);

   DString  _dstrText;
   DString  _dstMask;
   int      _iNumLine;
   CString  _strAllowedChars;
   long     _lMaxCharNum;
   INPUT_ALLOWED _enInputAllowed;
   int      _iMaxNumDigitsBeforeDecimalPoint;
   int      _iMaxNumDigitsAfterDecimalPoint;

   BOOL     _bKanjiStatus;
   BOOL     _bIMMStatus;
   BOOL     _bStartComp;
   DSTEdit* _pKanaDSTEdit;
   CString  _strAccumKanaBuf;
   CString  _strKanaBuf;
   CString  _strKanjiBuf;
   CString  _strCharBuf;
   wchar_t* _pWorkingBuf;
   HWND     _hwndGetFocus;             // handle to window receiving focus 
   bool     _bFixWrappingFlag;
   static CFont*   _pFixedFont;        // fixed pitch used for mutline edit wrapping
   bool m_bSetAsReadOnly;//want to keep track if developer called SetReadOnly() on DSTEdit, or this edit control has readonly attrib. in resource file
   bool m_bWordWrapInProcess;
   bool m_bRemoveUnwantedCharsAfterPaste;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/uibase/DSTEdit.h-arc  $
 * 
 *    Rev 1.20   Jun 17 2011 16:32:12   wutipong
 * IN2504087 - QESI Transfer Tab - Allow Negative Values
 * 
 *    Rev 1.19   24 Oct 2008 10:23:08   kovacsro
 * 1399970 - GL-1254 Desktop Screen (Remarks - odd character )
 * 
 *    Rev 1.18   16 Jan 2008 09:27:40   kovacsro
 * IN#1103220 - added a parameter to setNumLines
 * 
 *    Rev 1.17   Aug 01 2006 17:41:54   porteanm
 * Incident 666232 - Setters.
 * 
 *    Rev 1.16   May 06 2004 16:13:24   VADEANUM
 * PET 1017 - AWD Comments - added setNumLine().
 * 
 *    Rev 1.15   Nov 27 2002 15:06:20   PURDYECH
 * Documentation Changes
 * 
 *    Rev 1.14   Nov 13 2002 11:43:18   PURDYECH
 * Fixed up C4275 warning error.
 * 
 *    Rev 1.13   Nov 08 2002 10:00:34   PURDYECH
 * Use #pragma warning(...) to remove warning C4275 (non-Dll interface class used as base for interface class).
 * 
 *    Rev 1.12   Oct 09 2002 17:42:44   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.11   18 Apr 2002 10:03:00   KOVACSRO
 * Added word wrapping for multiline edits.
 * 
 *    Rev 1.10   19 Mar 2002 13:36:12   PURDYECH
 * Added #pragma once include guard
 * Removed compile time "including..." message.
 * 
 *    Rev 1.9   09 May 2001 12:05:30   KOVACSRO
 * Added SetAllDigits().
 * 
 *    Rev 1.8   26 Apr 2001 16:51:20   KOVACSRO
 * Added support for read only edit boxes.
 * 
 *    Rev 1.7   03 Apr 2001 11:46:04   KOVACSRO
 * Permission check stuff.
 * 
 *    Rev 1.6   29 Mar 2001 14:07:58   KOVACSRO
 * Added SetCtrlReadOnly();
 * 
 *    Rev 1.5   Jan 29 2001 16:29:24   HUANGSHA
 * added fixed length wrapping
 * 
 *    Rev 1.4   Jul 04 2000 16:44:44   HUANGSHA
 * Added the KanjiOpenStatus
 * 
 *    Rev 1.3   May 31 2000 16:43:30   BUZILA
 * masking support
 * 
 *    Rev 1.2   Apr 05 2000 14:17:14   HSUCHIN
 * more M2 sync up
 * 
 *    Rev 1.1   Feb 15 2000 18:58:54   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 11:00:58   SMITHDAV
 * Initial revision.
// 
//    Rev 1.15   Feb 08 2000 18:04:38   PRAGERYA
// Mask handling modified in a way forbidding illegal inputs
// 
//    Rev 1.14   Feb 07 2000 14:33:08   HUANGSHA
// Keep the IME status
// 
//    Rev 1.13   Jan 12 2000 17:39:06   HUANGSHA
// kanji-kana converting only effective for Japanese PC
// 
//    Rev 1.12   Jan 11 2000 18:06:16   HUANGSHA
// changed kanji-kana converting routine, removed the newline-carriage return for newly created multi-lines edit
// 
//    Rev 1.11   Dec 31 1999 14:46:38   HUANGSHA
// added Japanese Kanji-Kana routines
// 
//    Rev 1.10   Nov 17 1999 10:41:54   PRAGERYA
// Decimal numbers support added
// 
//    Rev 1.9   Nov 15 1999 14:04:12   DT24433
// removed flag parm in constructor
// 
//    Rev 1.8   Nov 05 1999 11:24:32   YINGZ
// just check in so it can be used
// 
//    Rev 1.7   Nov 02 1999 17:26:28   YINGZ
// add index
// 
//    Rev 1.6   Oct 26 1999 14:59:42   YINGZ
// add max num, char support
// 
//    Rev 1.5   Oct 26 1999 13:31:10   YINGZ
// add max num, char support
// 
//    Rev 1.4   Oct 14 1999 15:49:30   DT24433
// use interface methods for working with tooltip display
// 
//    Rev 1.3   Oct 14 1999 13:52:02   YINGZ
// add tooltip support
// 
//    Rev 1.2   Oct 14 1999 10:00:14   DT24433
// added new methods
// 
//    Rev 1.1   Oct 11 1999 17:48:18   DT24433
// added header/trailer junk
 * 
 */
