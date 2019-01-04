#pragma once
#include <bfutil\RTRevisionReport.hpp>

#undef WIN32UIBASE_LINKAGE
#ifdef WIN32UIBASE_DLL
   #define WIN32UIBASE_LINKAGE CLASS_EXPORT
#else
   #define WIN32UIBASE_LINKAGE CLASS_IMPORT
#endif

class WIN32UIBASE_LINKAGE RevisionListControl : public CListCtrl, public virtual RTRevisionReport
{
public:
   RevisionListControl();
   ~RevisionListControl();

   void Init();

protected:

   virtual void reportSourceRevision( const RTRevision * const revsion );
   virtual void reportHeaderRevision( const RTRevision * const revsion );

   void DrawItem(LPDRAWITEMSTRUCT);

private:
   int _itemCount;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/uibase/RevisionListControl.hpp-arc  $
//
//   Rev 1.2   Oct 09 2002 17:42:54   PURDYECH
//New PVCS Database
//
//   Rev 1.1   19 Mar 2002 13:36:10   PURDYECH
//Added #pragma once include guard
//Removed compile time "including..." message.
//
//   Rev 1.0   03 Jul 2001 15:52:28   SMITHDAV
//Initial revision.
 */