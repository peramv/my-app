// KEAScreen.cpp: implementation of the CKEAScreen class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "KEAScreen.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

KEAScreen::KEAScreen(LPDISPATCH pDispatch)
: Screen(pDispatch)
{
}

KEAScreen::~KEAScreen()
{
}

bool
KEAScreen::WaitForString(LPCSTR text, long wait, short row, short col)
{

   KEADispatch::MatchWait matchWait( Screen::WaitForString(text, COleVariant(row), COleVariant(col), COleVariant((short)0), COleVariant((long)0), COleVariant(wait), COleVariant((short)0)) ); 

   CString retstr = matchWait.GetString();

   if( 0 == retstr.Compare(text) )
      return true;

   return false;
}

bool
KEAScreen::WaitForStream(LPCSTR text, long wait)
{

   KEADispatch::MatchWait matchWait( Screen::WaitForStream(text, COleVariant((long)0), COleVariant(wait), COleVariant((short)0)) ); 

   CString retstr = matchWait.GetString();

   if( 0 == retstr.Compare(text) )
      return true;

   return false;
}

bool
KEAScreen::WaitForCursor(long wait, short row, short col)
{

   KEADispatch::CursorWait cursorWait( Screen::WaitForCursor(COleVariant(row), COleVariant(col), COleVariant((short)0)) ); 

   return( TRUE==cursorWait.Wait(COleVariant(wait)) );

}

CString
KEAScreen::WaitForKeyStroke()
{

   KEADispatch::KeyWait keyWait( Screen::WaitForKeys(COleVariant((short)true)) ); 

   return( keyWait.GetName() );

}
