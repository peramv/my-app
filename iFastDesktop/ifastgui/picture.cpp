// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


#include "stdafx.h"
#include "picture1.h"


/////////////////////////////////////////////////////////////////////////////
// CPicture properties

long CPicture::GetHandle()
{
   long result;
   GetProperty(0x0, VT_I4, (void*)&result);
   return(result);
}

long CPicture::GetHPal()
{
   long result;
   GetProperty(0x2, VT_I4, (void*)&result);
   return(result);
}

void CPicture::SetHPal(long propVal)
{
   SetProperty(0x2, VT_I4, propVal);
}

short CPicture::GetType()
{
   short result;
   GetProperty(0x3, VT_I2, (void*)&result);
   return(result);
}

long CPicture::GetWidth()
{
   long result;
   GetProperty(0x4, VT_I4, (void*)&result);
   return(result);
}

long CPicture::GetHeight()
{
   long result;
   GetProperty(0x5, VT_I4, (void*)&result);
   return(result);
}

/////////////////////////////////////////////////////////////////////////////
// CPicture operations

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   D:/scc/ifds/ifast/archives/ifastgui/picture.cpp-arc  $
 * 
 *    Rev 1.1   Oct 09 2002 23:55:50   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.0   Feb 15 2000 11:01:22   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.1   Jul 08 1999 10:05:44   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
