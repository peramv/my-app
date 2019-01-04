// DSTCDoc.cpp : implementation of the DSTCDoc class
//

#define WIN32UIBASE_DLL

#include "stdafx.h"

//removed for new arch
//#ifndef MFDSTC_H
//#include "MFDSTC.h"
//#endif

#include "DSTCDoc.h"

namespace CND
{
}
#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DSTCDoc

IMPLEMENT_DYNCREATE(DSTCDoc, CDocument)

BEGIN_MESSAGE_MAP(DSTCDoc, CDocument)
//{{AFX_MSG_MAP(DSTCDoc)
// NOTE - the ClassWizard will add and remove mapping macros here.
//    DO NOT EDIT what you see in these blocks of generated code!
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DSTCDoc construction/destruction

DSTCDoc::DSTCDoc()
{
   // TODO: add one-time construction code here

}

DSTCDoc::~DSTCDoc()
{
}

BOOL DSTCDoc::OnNewDocument()
{
   if( !CDocument::OnNewDocument() )
      return(FALSE);

   // TODO: add reinitialization code here
   // (SDI documents will reuse this document)

   return(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// DSTCDoc serialization

void DSTCDoc::Serialize(CArchive& ar)
{
   if( ar.IsStoring() )
   {
      // TODO: add storing code here
   }
   else
   {
      // TODO: add loading code here
   }
}

/////////////////////////////////////////////////////////////////////////////
// DSTCDoc diagnostics

#ifdef _DEBUG
void DSTCDoc::AssertValid() const
{
   CDocument::AssertValid();
}

void DSTCDoc::Dump(CDumpContext& dc) const
{
   CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// DSTCDoc commands

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/uibase/DSTCDoc.cpp-arc  $
 * 
 *    Rev 1.2   Oct 09 2002 17:42:40   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.1   Sep 10 2002 14:34:32   PURDYECH
 * Base condition split out
 * 
 *    Rev 1.0   Feb 15 2000 11:01:38   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.1   Jul 08 1999 10:04:58   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
