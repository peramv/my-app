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
// ^FILE   : DSTEdit.cpp
// ^AUTHOR : 
// ^DATE   : 10/11
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : DSTEdit
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  : 
//
//******************************************************************************

#define WIN32UIBASE_DLL
#include "stdafx.h"
#include <imm.h>

#include "DSTEdit.h"
#include "BaseDlg.h"
#include <bfcbo\BFProperties.hpp>
#include <limits>
#include <configmanager.hpp>
#include <bfutil/localetraits.hpp>

namespace CND
{
}

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CFont* DSTEdit::_pFixedFont = NULL;
//******************************************************************************
//              Public Methods
//******************************************************************************

DSTEdit::DSTEdit(
                BaseDlg *rpParent,
                UINT controlID
                ) :
BaseControl( rpParent, controlID ),
_strAllowedChars( _T( "" ) ), // allow all char
_iNumLine( 1 ),
_lMaxCharNum( 60 ),
_enInputAllowed( GENERAL ),
_iMaxNumDigitsBeforeDecimalPoint( std::numeric_limits< int >::max() ),
_iMaxNumDigitsAfterDecimalPoint( std::numeric_limits< int >::max() ),
_pKanaDSTEdit(NULL),
_bStartComp(false),
_pWorkingBuf(NULL),
_strKanjiBuf(_T("")),
_strKanaBuf(_T("")),
_strCharBuf(_T("")),
_strAccumKanaBuf(_T("")),
_bIMMStatus(false),
_hwndGetFocus(NULL),
_dstMask( NULL_STRING ),
_bKanjiStatus(false),
_bFixWrappingFlag(false),
m_bWordWrapInProcess(false)
{
   SubclassDlgItem( controlID, reinterpret_cast< CWnd * >( rpParent ) );
   m_bSetAsReadOnly = (GetStyle() & ES_READONLY ) == ES_READONLY;
   m_bRemoveUnwantedCharsAfterPaste = false;
}

//******************************************************************************

DSTEdit::~DSTEdit()
{
   if( _pWorkingBuf )
   {
      delete []_pWorkingBuf;
      _pWorkingBuf = NULL;
   }
}

//******************************************************************************
//              Message Handlers
//******************************************************************************

BEGIN_MESSAGE_MAP(DSTEdit, CEdit)
//{{AFX_MSG_MAP(DSTEdit)
ON_WM_KILLFOCUS()
ON_WM_SETFOCUS()
ON_WM_KEYDOWN()
ON_WM_MOUSEMOVE()
ON_WM_CHAR()
ON_CONTROL_REFLECT(EN_UPDATE, OnUpdate)
//}}AFX_MSG_MAP
ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave)

END_MESSAGE_MAP()


//******************************************************************************

void DSTEdit::SelectFixedFont()
{
   if( DSTEdit::_pFixedFont )
      SetFont(DSTEdit::_pFixedFont);
}
//******************************************************************************

void DSTEdit::ResizeEditArea()
{
   if( _iNumLine <= 1 || !_bFixWrappingFlag )
      return;

   SelectFixedFont();

   CDC* pDC = GetWindowDC();

   CFont* pOrgFont = pDC->SelectObject(DSTEdit::_pFixedFont);
   TEXTMETRIC tm;
   pDC->GetTextMetrics( &tm );

   pDC->SelectObject(pOrgFont);
   int iCharWidth = tm.tmAveCharWidth;

   RECT orgRC;
   GetRect( &orgRC );

   RECT wndRECT;
   GetClientRect( &wndRECT );
   pDC->DPtoLP( &wndRECT );

   int iLineWidth = iCharWidth * _lMaxCharNum;
   if( iLineWidth <= wndRECT.right - wndRECT.left )
   {
      orgRC.right = orgRC.left + iLineWidth;
      orgRC.bottom = wndRECT.bottom - wndRECT.top - orgRC.top;
      SetRect(&orgRC);
   }
   ReleaseDC( pDC );
}

//******************************************************************************

void DSTEdit::SetAllowedChars(LPCTSTR strAllowedChars)
{
   DString strText = strAllowedChars;
   if ( strText.isDecimal() )
   {
      const bfutil::LocaleTraits& localeTraitsE = bfutil::LocaleTraits::get( ClientLocaleContext::get() );
      I_CHAR RadixSeparatorE = localeTraitsE.getRadixSeparator();
      const bfutil::LocaleTraits& localeTraitsDisp = bfutil::LocaleTraits::get( ClientLocaleContext::get(), true );
      CString RadixSeparatorDisp = localeTraitsDisp.getRadixSeparator();
	   DString dstLocaleStr = ClientLocaleContext::get().getLocale();
	   if( dstLocaleStr == I_("deDE")   )
	   {
         while( true )
         {
	         int iPos = strText.find( RadixSeparatorE );
	         if( iPos == DString::npos ) break;
	         strText.replace( iPos, 1, RadixSeparatorDisp );
         }
         _strAllowedChars = strText.c_str();
	   }
      else
      {
         _strAllowedChars = strText.c_str();
      }
   }
	else
	{
		   _strAllowedChars = strAllowedChars;
	}
}

//******************************************************************************

void DSTEdit::SetMaxCharNum( long lMaxCharNum )
{
   _lMaxCharNum = lMaxCharNum;

   if( _iNumLine > 1 )
      ResizeEditArea();

   if( _pKanaDSTEdit )
   {
      if( _pWorkingBuf )
      {
         delete []_pWorkingBuf;
         _pWorkingBuf = NULL;
      }
      _pWorkingBuf = new wchar_t[_lMaxCharNum * 2];
      _wcsnset(_pWorkingBuf, 0, _lMaxCharNum * 2);
      _strKanjiBuf = _T("");
   }
}

//******************************************************************************

void DSTEdit::OnKillFocus(CWnd* pNewWnd) 
{
   HIMC hIMC = ImmGetContext(m_hWnd);
   _bIMMStatus = ImmGetOpenStatus(hIMC);

   DoKillFocus();

   CEdit::OnKillFocus(pNewWnd);
}

//******************************************************************************

void DSTEdit::OnSetFocus( CWnd* pOldWnd ) 
{
   HIMC hIMC = ImmGetContext(m_hWnd);

   if( _pKanaDSTEdit || _bKanjiStatus )
   {
      _bIMMStatus = true;
   }
   else
   {
      int i = 0;
      for( i = 0; i < _strAllowedChars.GetLength(); i++ )
      {
         if( !(_istdigit(_strAllowedChars.GetAt(i)) || 
               _strAllowedChars.GetAt(i) == _T(',')   || 
               _strAllowedChars.GetAt(i) == _T('.')) )
         {
            break;
         }
      }
      if( i >= _strAllowedChars.GetLength() )
         _bIMMStatus = false;
   }
   ImmSetOpenStatus(hIMC, _bIMMStatus);
   DoSetFocus();

   // If the current text selection for the control is at the beginning of the control 
   // (i.e. at 0,0) then swipe the entire text.  This helps data-entry by making sure
   // that typing anything in the field will overwrite the contents of the field.
   int iStart = -1;
   int iEnd = -1;
   GetSel( iStart, iEnd );
   if( 0 == iStart &&
       0 == iEnd )
   {
      SetSel( 0, -1 );
   }


   CEdit::OnSetFocus(pOldWnd);  
}

//******************************************************************************

void DSTEdit::OnChar( UINT nChar, UINT nRepCnt, UINT nFlags ) 
{
   if( nChar == VK_RETURN )
   {
      if( _iNumLine <= GetLineCount() )
      {
         SendMessage(WM_KEYDOWN, VK_DOWN);
         return;
      }
   }
   else if( nChar == VK_BACK )
   {
      if( !RemovingCharsAllowed( nChar ) )
         return;
   }
   else
   {
      //if the character is not allowed, return
      if( !_strAllowedChars.IsEmpty() && _strAllowedChars.Find( nChar ) == -1 )
         return;
      //if already the max. number of chars, for single line return, for multiline insert a new line
      int iStartSel, iEndSel;
      GetSel( iStartSel, iEndSel ) ;
      DWORD dwStyle = GetStyle();
      if( iStartSel == iEndSel && LineLength() >= _lMaxCharNum )
      {
         //even if it is multiline, but already have the max. number of line, return
         if( GetFlags() & CTRLFLAG_WORD_WRAP && dwStyle & ES_MULTILINE && GetLineCount() < _iNumLine )
            multilineWordWrap(nChar);
         else
            return; 
      }
      if( _enInputAllowed == UNSIGNED_DECIMAL || _enInputAllowed == DECIMAL)
      {
		  if(  nChar == I_('-') && _enInputAllowed == DECIMAL)
		  {
			  int selectStart, selectEnd;
			  GetSel(selectStart, selectEnd);

			  //not the first character in the line
			  if(selectStart != 0) 
				  return;
			
			  CString str;
			  GetWindowText( str );
			  //minus sign already exists
			  if(str.Find(I_('-')) != -1 && selectStart == selectEnd) 
				  return;

		  }
         CString str;
         GetWindowText( str );

		 DString dstr = str;		 
		 BaseDlg::DisplayUnFormat( dstr, (BFFieldId)GetFieldID(0) );
		 str = dstr.c_str();

         str.Delete( iStartSel, iEndSel - iStartSel );
         int iDecimalPointPos = str.Find( I_CHAR( '.' ) );
         if( iDecimalPointPos == -1 )//no decimal point in the string
         {
            if( nChar != I_CHAR( '.' ) )
            {
               if( str.GetLength() >= _iMaxNumDigitsBeforeDecimalPoint )
                  return;//max num of digits before decimal point has been reached
            }
            else//a decimal point is going to be inserted
            {
               if( iStartSel > _iMaxNumDigitsBeforeDecimalPoint
                   || str.GetLength() - iStartSel 
                   > _iMaxNumDigitsAfterDecimalPoint )
                  return;
            }
         }
         else
         {
            if( nChar == I_CHAR( '.' ) )
               return;
            if( iStartSel <= iDecimalPointPos ) //char is going to be inserted
            {
               //before the decimal point
               if( iDecimalPointPos >= _iMaxNumDigitsBeforeDecimalPoint )
                  return; //max num of digits before decimal 
            }         //point has been reached
            else  //char is going to be inserted
            {
               //after the decimal point
               if( str.GetLength() - iDecimalPointPos - 1
                   >= _iMaxNumDigitsAfterDecimalPoint )
                  return; //max num of digits after decimal
               //point has been reached
            }
         }
      }
   }

   CEdit::OnChar( nChar, nRepCnt, nFlags );
}

//******************************************************************************

void DSTEdit::AllowNonnegativeDecimalNumbers(
                                            int iMaxNumDigitsBeforeDecimalPoint, 
                                            int iMaxNumDigitsAfterDecimalPoint ) 
{ 
   _enInputAllowed = UNSIGNED_DECIMAL;
   SetAllowedChars( _T( "0123456789." ) );
   _iMaxNumDigitsBeforeDecimalPoint = iMaxNumDigitsBeforeDecimalPoint;
   _iMaxNumDigitsAfterDecimalPoint = iMaxNumDigitsAfterDecimalPoint;
}

//******************************************************************************
//              Protected methods
//******************************************************************************

void DSTEdit::DoGetText(
                       DString &strValueOut,
                       int index
                       ) const
{
   CString cstr;

   WCHAR *p;
   // The old logic returned text based on the the max char value set by SetMaxCharNum
   // This will truncated text which has been formatted by the base cbo resulting in
   // incorrect display hence override the old correct value.  Rather than using the
   // max char value to determine the amount of text returned, we will simply returned 
   // what was entered
   int iLength = LineLength ( LineIndex ( index ) );
   p = cstr.GetBuffer( iLength + 1 ); 
   int CharReturned = GetLine( index, p, iLength ) ;
   p[ CharReturned ] = _T( '\0' );
   cstr.ReleaseBuffer();

   DString tmp = cstr;
   BaseDlg::DisplayUnFormat( tmp, (BFFieldId)GetFieldID(0) );
   strValueOut = LPCTSTR( tmp.c_str() );

    if (m_bRemoveUnwantedCharsAfterPaste)
    {
        CString strTemp = strValueOut.c_str();

        strTemp.Replace(_T("\r"), _T(" ")); // replace all <cr> with space
        strTemp.Replace(_T("\n"), _T(" ")); // replace all <lf> with space
        strTemp.Replace(_T("\f"), _T(" ")); // replace all <ff> with space
        strTemp.Replace(_T("\t"), _T(" ")); // replace all <tab> with space
        strTemp.Replace(_T("\""), _T(" ")); // replace all <double quote/inverted commas> with space

        strValueOut = strTemp;
    }
}

//******************************************************************************

void DSTEdit::DoInit()
{
   _iNumLine = GetFieldCount();

   if( _iNumLine > 1 )
      ResizeEditArea();

   SetEditReadOnly( !IsUpdateable() );
   if( IsMaskedField() )
   {
      if( GetParentProcess() )
      {
         const BFProperties * pPropr = GetParentProcess()->getFieldAttributes( GetParentDlg(), GetContainerID(), GetFieldID(0) );
         if( pPropr )
            pPropr->getMask( _dstMask );
      };

   };
}

//******************************************************************************
void DSTEdit::setNumLine( int iNumLine )
{
	if( iNumLine == -1 )
	{
		_iNumLine = GetFieldCount();
	}
	else
	{
		_iNumLine = iNumLine;
	}
}

//******************************************************************************

bool DSTEdit::DoSetText(
                       const DString &strValueIn,
                       int index
                       )
{
   if( index == 0 )
   {
      _dstrText = strValueIn;
   }
   else if( index <= GetNumOfFields() - 1 )
   {
      if( GetFlags()& CTRLFLAG_LINE_PACK )
      {
           if (strValueIn != NULL_STRING)
            {
               _dstrText += I_( "\r\n" ) + strValueIn;
            }
      }
      else
      {
         _dstrText += I_( "\r\n" ) + strValueIn;
      }
   }
   if( index == GetNumOfFields() - 1 )
   {
      if( _iNumLine > 1 )
      {
         CString strTemp;
         strTemp = _dstrText.c_str();
         strTemp.TrimRight(_T("\r\n"));
         if( strTemp != _dstrText.c_str() && strTemp != NULL_STRING )
            strTemp += _T("\r\n");
         _dstrText = (LPCTSTR)strTemp;
      }

	  BaseDlg::DisplayFormat( _dstrText, (BFFieldId)GetFieldID(0) );
      SetWindowText( _dstrText.c_str() );
   }

   return(true);
}

//******************************************************************************

void DSTEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
   switch( nChar )
   {
      case VK_F11:
         ToggleToolTip();
         break;
      case VK_DELETE:
         if( !RemovingCharsAllowed( nChar ) )
            return;
         break;
      default:
         break;
   }

   CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

//******************************************************************************

bool DSTEdit::RemovingCharsAllowed( UINT nChar )
{
   assert( nChar == VK_DELETE || nChar == VK_BACK );
   if( _enInputAllowed == UNSIGNED_DECIMAL || _enInputAllowed == DECIMAL)
   {
      int iStartSel, iEndSel;
      GetSel( iStartSel, iEndSel );
      CString str;
      GetWindowText( str );

	  DString dstr = str;
	  BaseDlg::DisplayUnFormat( dstr, (BFFieldId)GetFieldID(0) );
	  str = dstr.c_str();

      int iSelLength = iEndSel - iStartSel;
      if( iSelLength )
         str.Delete( iStartSel, iSelLength );
      else if( nChar == VK_DELETE )
         str.Delete( iStartSel, 1 );
      else//nChar == VK_BACK
      {
         if( iStartSel )
            str.Delete( iStartSel - 1, 1 );
      }
      int iDecimalPointPos = str.Find( I_CHAR( '.' ) );
      if( iDecimalPointPos == -1 )//no decimal point in the string
      {
         if( str.GetLength() > _iMaxNumDigitsBeforeDecimalPoint )
            return(false); //after BACK or DELETE, there would be too many 
      }             //digits before decimal point
   }

   return(true);
}

//******************************************************************************

LRESULT DSTEdit::OnMouseLeave(WPARAM , LPARAM )
{
   MouseLeave();

   return(0);
}

//******************************************************************************

void DSTEdit::OnMouseMove(UINT nFlags, CPoint point) 
{
   if( IsError() /*&& !IsToolTipVisible()*/ )
   {
      TriggerToolTip(); 
   }

   CEdit::OnMouseMove(nFlags, point);
}
//******************************************************************************
void DSTEdit::SetRemoveUnwantedCharsAfterPaste(bool bRemove)
{
    m_bRemoveUnwantedCharsAfterPaste = bRemove;
}

//******************************************************************************

void DSTEdit::DoClear()
{
   SetSel(0, -1);
   CEdit::Clear( );
}

//******************************************************************************

BOOL DSTEdit::PreTranslateMessage(MSG* pMsg) 
{
   // TODO: Add your specialized code here and/or call the base class
   if( pMsg->message == WM_KILLFOCUS )
      _hwndGetFocus = (HWND)pMsg->wParam; // handle to window receiving focus 
   else if( pMsg->message == WM_KEYDOWN )
      HideToolTip();

   if( !_pKanaDSTEdit )
      return(CEdit::PreTranslateMessage(pMsg));

   HIMC hIMC = ImmGetContext(pMsg->hwnd);
   long lBufLen;

   // Allocating the working buffer for the converting string
   if( !_pWorkingBuf )
   {
      _pWorkingBuf = new wchar_t[_lMaxCharNum * 2];
      _wcsnset(_pWorkingBuf, 0, _lMaxCharNum * 2);
      _strKanjiBuf = _T("");
   }

   if( pMsg->message == WM_CHAR )
   {
      wchar_t wch = pMsg->wParam;
      if( _strKanjiBuf.GetLength() != 0 )
      {
         _strCharBuf += wch;
         if( _strCharBuf == _strKanjiBuf )
         {
            _strCharBuf    = _T("");
            _strKanjiBuf   = _T("");
            if( _strKanaBuf.GetLength() )
            {
               _strAccumKanaBuf += _strKanaBuf;
               _strKanaBuf = _T("");
            }
         }
      }
      else if( (wch >= 0x0020 && wch <= 0x007E) || (wch >= 0xFF61 && wch <= 0xFF9F) )
      {
         _strAccumKanaBuf += wch;
      }
      else if( wch == 0x000D )
      {
         _strAccumKanaBuf += _T("\r\n");
      }
   }
   else if( (int)(pMsg->message) == WM_IME_STARTCOMPOSITION )
   {
      _bStartComp = true;
      _strKanaBuf = _T("");
      _strKanjiBuf= _T("");
   }
   else if( (int)(pMsg->message) == WM_IME_ENDCOMPOSITION )
   {
      if( _bStartComp && _strKanaBuf != _T("") )
      {
         _strAccumKanaBuf += _strKanaBuf;
         _strKanaBuf = _T("");
      }
      _bStartComp = false;
   }
   else if( (int)(pMsg->message) == WM_IME_COMPOSITION && _bStartComp )
   {
      wchar_t wch = pMsg->wParam;
      lBufLen = ImmGetCompositionString(hIMC, GCS_RESULTSTR, _pWorkingBuf, _lMaxCharNum * 2);
      if( lBufLen )
      {
         lBufLen /= 2;
         _pWorkingBuf[lBufLen] = 0;
         _strKanjiBuf = _pWorkingBuf;
      }
      lBufLen = ImmGetCompositionString(hIMC, GCS_RESULTREADSTR, _pWorkingBuf, _lMaxCharNum * 2);
      if( lBufLen )
      {
         lBufLen /= 2;
         _pWorkingBuf[lBufLen] = 0;
         _strKanaBuf = _pWorkingBuf;
      }
   }
   return(CEdit::PreTranslateMessage(pMsg));
}

//******************************************************************************

void DSTEdit::OnUpdate() 
{
   // TODO: If this is a RICHEDIT control, the control will not
   // send this notification unless you override the CEdit::OnInitDialog()
   // function to send the EM_SETEVENTMASK message to the control
   // with the ENM_UPDATE flag ORed into the lParam mask.

   // TODO: Add your control notification handler code here
   if( !_pKanaDSTEdit )
      return;

   CString strText;
   GetWindowText(strText);

	DString dstr = strText;	
	BaseDlg::DisplayUnFormat( dstr, (BFFieldId)GetFieldID(0) );
	strText = dstr.c_str();

   strText.TrimRight();
   if( strText != _T("") )
   {
      _pKanaDSTEdit->GetWindowText(strText);

		dstr = strText;
		BaseDlg::DisplayUnFormat( dstr, (BFFieldId)GetFieldID(0) );
		strText = dstr.c_str();

      DString dstrJapConvertMode = GetConfigValueAsString(I_("LocaleFormats"), 
                                                          I_("JapaneseConvert"), I_("Mode"));
      dstrJapConvertMode.strip().upperCase();
      if( dstrJapConvertMode == NULL_STRING )
      {
         WriteConfigValue(I_("LocaleFormats"),I_("JapaneseConvert"), I_("Mode"), I_("Single-byte"));
         dstrJapConvertMode = I_("Single-byte");
      }
      int iRes = 0;
      if( dstrJapConvertMode.substr(0, 1) == I_("D") )
      {
         iRes = LCMapString(LOCALE_USER_DEFAULT, LCMAP_FULLWIDTH,
                            (LPCTSTR)_strAccumKanaBuf, _strAccumKanaBuf.GetLength(),
                            _pWorkingBuf, _lMaxCharNum);
         if( iRes != 0 )
         {
            _pWorkingBuf[iRes] = 0;
            strText += _pWorkingBuf;
         }
      }
      if( iRes == 0 )
         strText += _strAccumKanaBuf;

      _strAccumKanaBuf = _T("");
   }
   DString tmpstr = strText;   
   BaseDlg::DisplayFormat( tmpstr, (BFFieldId)GetFieldID(0) );
   _pKanaDSTEdit->SetWindowText(LPCTSTR(tmpstr.c_str()));
}

//******************************************************************************

void DSTEdit::SetKanaEdit(DSTEdit* pKanaEdit)
{
   TCHAR tcLang[100];
   GetLocaleInfo(LOCALE_SYSTEM_DEFAULT, LOCALE_SENGCOUNTRY, tcLang, 40);
   CString strSysLang(tcLang);

   if( strSysLang == _T("Japan") || strSysLang == _T("JAN") )
   {
      DString dstrJapConvert = GetConfigValueAsString(I_("LocaleFormats"), 
                                                      I_("JapaneseConvert"), I_("Activate"));
      dstrJapConvert.strip().upperCase();
      if( dstrJapConvert == NULL_STRING )
      {
         WriteConfigValue(I_("LocaleFormats"),I_("JapaneseConvert"), I_("Activate"), I_("Yes"));
         dstrJapConvert = I_("Yes");
      }
      if( dstrJapConvert.substr(0, 1) == I_("Y") )
         _pKanaDSTEdit = pKanaEdit;
   }
}
//******************************************************************************

bool DSTEdit::doSetCtrlReadOnly(bool bReadOnly)
{
   SetEditReadOnly(bReadOnly);
   return(true);
}

//******************************************************************************

BOOL DSTEdit::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
   if( (message == EM_SETREADONLY) && (lParam == 0) )
   {
      m_bSetAsReadOnly = wParam != 0;
   }

   BOOL retVal = CWnd::OnWndMsg(message, wParam, lParam, pResult);

   if( message == WM_PASTE )
   {
      GetParentDlg()->doPaste( GetControlID() );
   }
   
   return ( retVal );   
}

//******************************************************************************

void DSTEdit::SetFlags( UINT flags )
{  // Note: if a version of this is made public, need to do a CheckFlags
   //   - don't want a checkFlags for this version (or have internal
   //   methods set _flags directly instead of use this).
   if( flags & CTRLFLAG_NOT_UPDATABLE )
      m_bSetAsReadOnly = true;
   //else do not reset m_bSetAsReadOnly (set in constructor)

   BaseControl::SetFlags( flags );
}
//******************************************************************************

BOOL DSTEdit::SetEditReadOnly(bool bReadOnly /*= true*/)
{
   ASSERT(::IsWindow(m_hWnd)); 
   return(BOOL)::SendMessage(m_hWnd, EM_SETREADONLY, bReadOnly, 1L);
}
//******************************************************************************

void DSTEdit::SetAllDigits(bool bAllDigits)
{
   DWORD dwStyle = ES_NUMBER;
   if( bAllDigits )
      ModifyStyle( NULL, dwStyle);
   else
      ModifyStyle( dwStyle, NULL);
}
//******************************************************************************

void DSTEdit::multilineWordWrap(UINT nChar)
{
   if( m_bWordWrapInProcess )
      return;

   CString strBeforeLastSpace, strAfterLastSpace, strCurrLine;
   int iLineIndex = LineIndex();
   int iLineNum =0;
   while( LineIndex(iLineNum) < iLineIndex && iLineNum < _iNumLine )
   {
	   iLineNum++;
   }
   int iLineLength = LineLength();
   GetLine(iLineNum, strCurrLine.GetBuffer(iLineLength), iLineLength);
   strCurrLine.ReleaseBuffer(iLineLength);

   DString dstr = strCurrLine;	
   BaseDlg::DisplayUnFormat( dstr, (BFFieldId)GetFieldID(0) );
   strCurrLine = dstr.c_str();

   int iLength = strCurrLine.GetLength();
   int iSpacePos = strCurrLine.ReverseFind(' ');//ReverseFind is 0 based

   int iStart, iEnd;
   bool bNeedRepositioning = false;
   bool bAddSpace = false;
   GetSel(iStart, iEnd);

   if( iLength == _lMaxCharNum && nChar == VK_SPACE && iStart == iLineIndex+_lMaxCharNum )
   {
      // the user enters a space at the end of the line: no wrapping necessary, just add a new line
	  SendMessage(WM_CHAR, VK_RETURN);//insert a new line here
   }
   else if( iSpacePos > 0 && iLength - iSpacePos < _lMaxCharNum )//a space was found and it is on the current line
   {
      //if space is the last character on the line, also move down the word before the space
      if( strCurrLine.GetAt( strCurrLine.GetLength() - 1 ) == VK_SPACE )
	  {
         strCurrLine = strCurrLine.Left(strCurrLine.GetLength() - 1);
		 iSpacePos = strCurrLine.ReverseFind(' ');
		 bAddSpace = true;
		 iLength--;
	  }
      strBeforeLastSpace = strCurrLine.Left(iSpacePos);//Left is 1 based! don't include the space itself
      strAfterLastSpace = strCurrLine.Right(iLength - iSpacePos);//Right is 1 based! include the space, too, because we want to move it on the next line	  
	  if( bAddSpace )
         strAfterLastSpace += " ";
	  m_bWordWrapInProcess = true;
      //position carret at the end of the line	  
      if( iStart < iLineIndex+_lMaxCharNum )
      {
         //carret not at the EOL; position to EOL
         SetSel(iLineIndex+_lMaxCharNum, iLineIndex+_lMaxCharNum);
         bNeedRepositioning = true;
      }
      for( int i=0; i<strAfterLastSpace.GetLength();i++ )
         SendMessage(WM_CHAR, VK_BACK);
      SendMessage(WM_CHAR, VK_RETURN);//insert a new line here
      for( int i=0; i<strAfterLastSpace.GetLength();i++ )
         SendMessage(WM_CHAR, strAfterLastSpace.GetAt(i));   
      if( bNeedRepositioning )
      {
         SetSel(iStart, iEnd);
      }
	  m_bWordWrapInProcess = false;
   }
   else//no wrapping, just add a new line
      SendMessage(WM_CHAR, VK_RETURN);//insert a new line here
}

//******************************************************************************
void DSTEdit::setInputAllowedDecimal()
{
	_enInputAllowed = DECIMAL; 
	DSTEdit::SetAllowedChars(I_("0123456789.-"));
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/uibase/DSTEdit.cpp-arc  $
//
//   Rev 1.34   Jun 17 2011 16:32:38   wutipong
//IN2504087 - QESI Transfer Tab - Allow Negative Values
//
//   Rev 1.33   24 Dec 2008 10:49:54   kovacsro
//IN#1399970 - one more code change for remarks formatting
//
//   Rev 1.32   24 Oct 2008 10:23:06   kovacsro
//1399970 - GL-1254 Desktop Screen (Remarks - odd character )
//
//   Rev 1.31   16 May 2008 13:30:30   kovacsro
//IN#1223298 - calling doPaste for WM_PASTE messages
//
//   Rev 1.30   16 Jan 2008 09:29:42   kovacsro
//IN#1103220 - added a new parameter to setNumLine
//
//   Rev 1.29   Jul 22 2005 15:12:58   Fengyong
//PET1250FN02 - European format - syncup
//
//   Rev 1.28   Jul 21 2005 15:24:02   Yingbaol
//PET1250,FN02:1 line has not been check in.
//
//   Rev 1.27   Jul 21 2005 15:17:56   Yingbaol
//PET1250,FN02:fix SetAllowedChars
//
//   Rev 1.26   Jun 30 2005 16:59:32   Fengyong
//PET1250FN02 - eropean numeric EH - Please apply Localetraits.cpp/hpp code 
//
//   Rev 1.25   Jun 24 2005 17:01:26   Fengyong
//PET1250 FN02 - EuroPean numeric enhancement
//
//   Rev 1.24   Apr 14 2005 11:49:38   yingbaol
//Incident 283230: pack multi line edit based on the set up.
//
//   Rev 1.23   Mar 30 2005 15:38:08   yingbaol
//Incident 273898, reverse changes in version 1.22
//
//   Rev 1.22   Sep 27 2004 09:57:20   popescu
//PET 1117/06, add a line to a multi-line control only if the value of it is not null string
//
//   Rev 1.21   Sep 27 2004 09:32:06   FENGYONG
//PTS10024458 - do not check visible before show error message
//
//   Rev 1.20   May 06 2004 16:13:54   VADEANUM
//PET 1017 - AWD Comments - added setNumLine().
 * 
 *    Rev 1.19   Apr 02 2003 13:33:36   PURDYECH
 * Force selection of text on gain of focus if the selection is currently an insertion point at the beginning of the text.  
 * 
 *    Rev 1.18   Oct 09 2002 17:42:44   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.17   Sep 27 2002 16:36:36   HSUCHIN
 * bug fix fo DoGetText.  Wrong use of LineLength
 * 
 *    Rev 1.16   Sep 13 2002 09:34:20   HSUCHIN
 * added comment to last fix.
 * 
 *    Rev 1.15   Sep 13 2002 09:17:20   HSUCHIN
 * bug fix to formatted values which exceed maxchar set to edit control which resulted in truncated values.
 * 
 *    Rev 1.14   Sep 10 2002 14:34:34   PURDYECH
 * Base condition split out
 * 
 *    Rev 1.13   Jul 05 2002 10:46:30   PURDYECH
 * Include file cleanup.
 * 
 *    Rev 1.12   26 Apr 2002 10:38:54   KOVACSRO
 * Only if CTRLFLAG_WORD_WRAP flag is on, perform the word wrapping.
 * 
 *    Rev 1.11   18 Apr 2002 10:02:16   KOVACSRO
 * For multine edits automatically add a new line when the max. number of characters is riched.
 * 
 *    Rev 1.10   Feb 25 2002 18:58:06   PURDYECH
 * Removed annoying compiler warnings.
 * 
 *    Rev 1.9   09 May 2001 12:06:02   KOVACSRO
 * Added SetAllDigits().
 * 
 *    Rev 1.8   26 Apr 2001 16:53:18   KOVACSRO
 * Added support for read only edit boxes.
 * 
 *    Rev 1.7   03 Apr 2001 11:56:28   KOVACSRO
 * Permission check stuff.
 * 
 *    Rev 1.6   29 Mar 2001 14:08:50   KOVACSRO
 * Implemented SetCtrlReadOnly();
 * 
 *    Rev 1.5   Jan 29 2001 16:27:56   HUANGSHA
 * added fixed length wrapping
 * 
 *    Rev 1.4   Dec 07 2000 17:03:08   HUANGSHA
 * added switch for single/double bytes kana
 * 
 *    Rev 1.3   Jul 04 2000 16:43:08   HUANGSHA
 * Added the KanjiOpenStatus
 * 
 *    Rev 1.2   May 31 2000 16:44:30   BUZILA
 * masking support
 * 
 *    Rev 1.1   Apr 05 2000 14:17:16   HSUCHIN
 * more M2 sync up
 * 
 *    Rev 1.0   Feb 15 2000 11:01:40   SMITHDAV
 * Initial revision.
// 
//    Rev 1.28   Feb 08 2000 18:04:40   PRAGERYA
// Mask handling modified in a way forbidding illegal inputs
// 
//    Rev 1.27   Feb 07 2000 14:33:06   HUANGSHA
// Keep the IME status
// 
//    Rev 1.26   Jan 28 2000 16:55:30   YINGZ
// return back to orignal version
// 
//    Rev 1.25   Jan 28 2000 16:12:40   YINGZ
// get max char from data dictionary
// 
//    Rev 1.24   Jan 12 2000 17:39:10   HUANGSHA
// kanji-kana converting only effective for Japanese PC
// 
//    Rev 1.23   Jan 11 2000 18:06:14   HUANGSHA
// changed kanji-kana converting routine, removed the newline-carriage return for newly created multi-lines edit
// 
//    Rev 1.22   Jan 05 2000 11:45:58   YINGZ
// allow overwrite selected char
// 
//    Rev 1.21   Jan 04 2000 12:42:48   DT24433
// set readonly based on IsUpdateable call
// 
//    Rev 1.20   Dec 31 1999 14:46:36   HUANGSHA
// added Japanese Kanji-Kana routines
// 
//    Rev 1.19   Dec 24 1999 09:33:10   YINGZ
// change behaviour of return key
// 
//    Rev 1.18   Dec 08 1999 13:14:38   YINGZ
// set readonly in doinit
// 
//    Rev 1.17   Nov 23 1999 16:21:12   YINGZ
// fix doclear
// 
//    Rev 1.16   Nov 17 1999 14:16:04   PRAGERYA
// Bug fixed
// 
//    Rev 1.15   Nov 17 1999 11:11:00   YINGZ
// doclear do not clear cbo value now
// 
//    Rev 1.14   Nov 17 1999 10:41:36   PRAGERYA
// Decimal numbers support added
// 
//    Rev 1.13   Nov 15 1999 14:02:52   DT24433
// removed flag parm in constructor
// 
//    Rev 1.12   Nov 13 1999 12:33:48   YINGZ
// implment DoGetText
// 
//    Rev 1.11   Nov 05 1999 11:24:30   YINGZ
// just check in so it can be used
// 
//    Rev 1.10   Nov 02 1999 17:26:28   YINGZ
// add index
// 
//    Rev 1.9   Oct 28 1999 09:35:24   YINGZ
// for a clean Get from PVCS!
// 
//    Rev 1.8   Oct 26 1999 13:35:40   YINGZ
// change default char
// 
//    Rev 1.7   Oct 26 1999 13:31:10   YINGZ
// add max num, char support
// 
//    Rev 1.6   Oct 21 1999 15:54:20   YINGZ
// add doinit
// 
//    Rev 1.5   Oct 18 1999 15:51:04   YINGZ
// modify onmousemove
// 
//    Rev 1.4   Oct 14 1999 15:47:38   DT24433
// use interface methods for working with tooltip display
// 
//    Rev 1.3   Oct 14 1999 13:52:02   YINGZ
// add tooltip support
// 
//    Rev 1.2   Oct 14 1999 09:58:50   DT24433
// added new methods
// 
//    Rev 1.1   Oct 11 1999 17:49:32   DT24433
// added header/trailer junk
 * 
*/ 

