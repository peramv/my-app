#pragma once


//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1998 by DST Systems, Inc.
//
//*****************************************************************************
//
// ^FILE   : ComboBase.h
// ^AUTHOR : Jerry Leenerts
// ^DATE   : 10/07/98
//
// ^CLASS  : CComboBase
// ^PARENT : CComboBox
//
// ^CLASS DESCRIPTION :
//    This class wraps CComboBox providing selection as the user incrementally
//    types in additional characters.
//*****************************************************************************

#include <bfdata\bffieldid.hpp>
#include <bfproc\bfcontainerid.hpp>
class GenericInterface;

#undef WIN32UIBASE_LINKAGE
#ifdef WIN32UIBASE_DLL
   #define WIN32UIBASE_LINKAGE CLASS_EXPORT
#else
   #define WIN32UIBASE_LINKAGE CLASS_IMPORT
#endif

#pragma warning( disable: 4275 )
class WIN32UIBASE_LINKAGE CComboBase : public CComboBox
{
public:
   CComboBase();
   virtual ~CComboBase()
   {}

   // The following method should be used to set the selection when the
   //  parent should be notified of the change
   int SetCurSelWithNotify(
                          int idx
                          );
   void SetSavedSelection();
   void SetSelectionByData( const DString &dstrData );
   void FillInSubstituteValues( GenericInterface *pGICaller, const BFContainerId& idSubstitute );
protected:
   DString m_autoExpand;
   // Generated message map functions
   //{{AFX_MSG(CComboBase)
   afx_msg void OnSetFocus(CWnd* pOldWnd);
   afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()

   virtual bool AllowExtension( const DString & )
   {  // Override if you want to allow for autoexpand to have unused characters
      //  at the end
      return(false);
   }
   virtual bool AutoExpand(
                          const DString &result
                          );

private:
   int m_iSaveSelection;
   BFFieldId _idSubstituteDescription;

   BFContainerId idSubstitute_;
   GenericInterface* _pGI;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/uibase/combobase.h-arc  $
 * 
 *    Rev 1.8   Jan 06 2003 16:46:26   PURDYECH
 * BFDataGroupId and BFContainerId changeover
 * 
 *    Rev 1.7   Nov 13 2002 11:43:12   PURDYECH
 * Fixed up C4275 warning error.
 * 
 *    Rev 1.6   Nov 08 2002 10:00:28   PURDYECH
 * Use #pragma warning(...) to remove warning C4275 (non-Dll interface class used as base for interface class).
 * 
 *    Rev 1.5   Oct 09 2002 17:42:36   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.4   Aug 29 2002 12:57:06   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.3   19 Mar 2002 13:36:16   PURDYECH
 * Added #pragma once include guard
 * Removed compile time "including..." message.
 * 
 *    Rev 1.2   Mar 08 2000 13:39:14   DT24433
 * removed dependency on DBR namespace
 * 
 *    Rev 1.1   Feb 15 2000 18:58:50   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 11:00:56   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.6   Sep 16 1999 15:32:00   YINGZ
 * change SetSelectionByData so that in c1, only one line in comobo!
 * 
 *    Rev 1.5   Aug 18 1999 13:53:12   PRAGERYA
 * FillInSubstituteValues modified
 * 
 *    Rev 1.4   Aug 18 1999 13:36:22   YINGBAOL
 * 
 *    Rev 1.3   Aug 13 1999 10:24:54   PRAGERYA
 * Adding Increment 2 functionality
 * 
 *    Rev 1.2   Aug 10 1999 17:33:20   PRAGERYA
 * New method added
 * 
 *    Rev 1.1   Jul 08 1999 10:04:50   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
