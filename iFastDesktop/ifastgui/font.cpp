// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


#include "stdafx.h"
#include "font.h"


/////////////////////////////////////////////////////////////////////////////
// COleFont properties

CString COleFont::GetName()
{
   CString result;
   GetProperty(0x0, VT_BSTR, (void*)&result);
   return(result);
}

void COleFont::SetName(LPCTSTR propVal)
{
   SetProperty(0x0, VT_BSTR, propVal);
}

CY COleFont::GetSize()
{
   CY result;
   GetProperty(0x2, VT_CY, (void*)&result);
   return(result);
}

void COleFont::SetSize(const CY& propVal)
{
   SetProperty(0x2, VT_CY, &propVal);
}

BOOL COleFont::GetBold()
{
   BOOL result;
   GetProperty(0x3, VT_BOOL, (void*)&result);
   return(result);
}

void COleFont::SetBold(BOOL propVal)
{
   SetProperty(0x3, VT_BOOL, propVal);
}

BOOL COleFont::GetItalic()
{
   BOOL result;
   GetProperty(0x4, VT_BOOL, (void*)&result);
   return(result);
}

void COleFont::SetItalic(BOOL propVal)
{
   SetProperty(0x4, VT_BOOL, propVal);
}

BOOL COleFont::GetUnderline()
{
   BOOL result;
   GetProperty(0x5, VT_BOOL, (void*)&result);
   return(result);
}

void COleFont::SetUnderline(BOOL propVal)
{
   SetProperty(0x5, VT_BOOL, propVal);
}

BOOL COleFont::GetStrikethrough()
{
   BOOL result;
   GetProperty(0x6, VT_BOOL, (void*)&result);
   return(result);
}

void COleFont::SetStrikethrough(BOOL propVal)
{
   SetProperty(0x6, VT_BOOL, propVal);
}

short COleFont::GetWeight()
{
   short result;
   GetProperty(0x7, VT_I2, (void*)&result);
   return(result);
}

void COleFont::SetWeight(short propVal)
{
   SetProperty(0x7, VT_I2, propVal);
}

short COleFont::GetCharset()
{
   short result;
   GetProperty(0x8, VT_I2, (void*)&result);
   return(result);
}

void COleFont::SetCharset(short propVal)
{
   SetProperty(0x8, VT_I2, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// COleFont operations

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   D:/scc/ifds/ifast/archives/ifastgui/font.cpp-arc  $
 * 
 *    Rev 1.1   Oct 09 2002 23:55:40   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.0   Feb 15 2000 11:01:14   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.1   Jul 08 1999 10:05:10   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
