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
// ^FILE   : CMEdit.cpp
// ^AUTHOR : Chin Hsu   
// ^DATE   : 10/18/1999
//
// ----------------------------------------------------------
//
// ^CLASS    : CMEdit
//
// ^MEMBER VARIABLES :
//
//
//******************************************************************************

#include "stdafx.h"
#include "mfdstc.h"
#include "CMEdit.h"

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTelEdit

CMEdit::CMEdit()
{
}

CMEdit::~CMEdit()
{
}


BEGIN_MESSAGE_MAP(CMEdit, CEdit)
//{{AFX_MSG_MAP(CMEdit)
ON_WM_CHAR()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTelEdit message handlers

void CMEdit::SetMaxCharPerLine(long n)
{
   MaxCharPerLine=n;
}

void CMEdit::SetMaxLine(long n)
{
   MaxLine=n;
}

void CMEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
   LPTSTR s_lineTmp = new wchar_t[80];
   //Count the number of lines in the edit control
   int i_curLine = LineFromChar();
   int i_lineLen;
   //If the keystroke is return, increment the number of lines entered in the text
   //control by 1.
   if( nChar == VK_RETURN )
      i_curLine++;
   //Get the line of text enter
   i_lineLen = GetLine(LineFromChar(),s_lineTmp,80);
   s_lineTmp[i_lineLen] = NULL;
   i_lineLen++;
   //Get the selection position if there is any.
   int i_startSel,i_endSel;
   GetSel(i_startSel,i_endSel);
   //If the number of bytes on the current edit line is less than the Maximum
   //bytes of characters allowed for a line and we have not reached the maximum
   //lines allowed.. let the keystroke throu.  If it is a backspace key, let it throu
   //always.
   if( ( (i_lineLen <= (MaxCharPerLine)) && (i_curLine < MaxLine) ) || nChar==VK_BACK )
   {
      CEdit::OnChar(nChar, nRepCnt, nFlags);
      //If there is selected text, we will let the keystroke pass throu except for the 
      //return key.
   }
   else if( (nChar != VK_RETURN) && ( i_startSel != i_endSel ) )
   {
      CEdit::OnChar(nChar, nRepCnt, nFlags);
      //If the maximum bytes of character for a line has been reached but the maximum
      //number of line hasn't been reached, we will let the return key be passed throu.
   }
   else if( (i_lineLen == (MaxCharPerLine+1)) && (nChar==VK_RETURN) && (GetLineCount() != MaxLine) )
   {
      CEdit::OnChar(nChar, nRepCnt, nFlags);
   }
}
