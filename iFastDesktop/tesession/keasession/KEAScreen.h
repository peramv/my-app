// KEAScreen.h: interface for the CKEAScreen class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_KEASCREEN_H__INCLUDED_)
#define _KEASCREEN_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <keasession\keavt.h>

class KEAScreen : public KEADispatch::Screen  
{
public:
   KEAScreen(LPDISPATCH pDispatch);
   virtual ~KEAScreen();

   bool WaitForString(LPCSTR text, long wait, short row=0, short col=0);
   bool WaitForStream(LPCSTR text, long wait);
   bool WaitForCursor(long wait, short row, short col);
   CString WaitForKeyStroke();

};

#endif // !defined(_KEASCREEN_H__INCLUDED_)
