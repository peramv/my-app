#if !defined(AFX_PICTURE1_H__BF1FD622_FD53_11D2_B8E9_00C04F572654__INCLUDED_)
   #define AFX_PICTURE1_H__BF1FD622_FD53_11D2_B8E9_00C04F572654__INCLUDED_

   #if _MSC_VER > 1000
      #pragma once
   #endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CPicture wrapper class

class CPicture : public COleDispatchDriver
{
public:
   CPicture() {}   // Calls COleDispatchDriver default constructor
   CPicture(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
   CPicture(const CPicture& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
   long GetHandle();
   long GetHPal();
   void SetHPal(long);
   short GetType();
   long GetWidth();
   long GetHeight();

// Operations
public:
   // method 'Render' not emitted because of invalid return type or parameter type
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PICTURE1_H__BF1FD622_FD53_11D2_B8E9_00C04F572654__INCLUDED_)

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   D:/scc/ifds/ifast/archives/ifastgui/picture1.h-arc  $
 * 
 *    Rev 1.2   Oct 09 2002 23:55:50   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.1   Feb 15 2000 18:59:38   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 11:01:22   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.1   Jul 08 1999 10:05:44   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
