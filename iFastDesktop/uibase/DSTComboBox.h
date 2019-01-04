#pragma once


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

#include <uibase\BaseControl.hpp>
#include <bfdata\bfdatafield.hpp>

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId Substitute_Description;
}

class GenericInterface;


#undef WIN32UIBASE_LINKAGE
#ifdef WIN32UIBASE_DLL
   #define WIN32UIBASE_LINKAGE CLASS_EXPORT
#else
   #define WIN32UIBASE_LINKAGE CLASS_IMPORT
#endif

#pragma warning( disable: 4275 )
class WIN32UIBASE_LINKAGE DSTComboBox : public CComboBox, public BaseControl
{
// Construction
public:
   DSTComboBox(
              BaseDlg *rpParent,
              UINT controlID
              );
   virtual ~DSTComboBox();

   void FillInListValues( const BFContainerId& idContainer, const BFFieldId &idField);
   void FillInSubstituteValues();
   void FillInSubstituteValues( const BFContainerId& idSubstitute, 
                                const BFFieldId &idSubstituteItem = ifds::Substitute_Description );
   void FillInTwoListValues( const BFContainerId& idContainer, const BFFieldId &idField1, const BFFieldId &idField2, 
                             const DString& Separator=I_(" "), const DString& ExtraLine=NULL_STRING);
   // The following method should be used to set the selection when the
   //  parent should be notified of the change
   int SetCurSelWithNotify(
                          int idx
                          );
   void SetSavedSelection();

   void SetSelectionByData( const DString &dstrData );

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(DSTComboBox)
public:
   virtual BOOL PreTranslateMessage(MSG* pMsg);
   //}}AFX_VIRTUAL

   // Generated message map functions
protected:
   DString m_autoExpand;
   //{{AFX_MSG(DSTComboBox)
   afx_msg void OnMouseMove(UINT nFlags, CPoint point);
   afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
   afx_msg BOOL OnKillfocus();
   afx_msg BOOL OnSetfocus();
   afx_msg void OnSelendok();
   //}}AFX_MSG
   LRESULT OnMouseLeave(WPARAM a=0L, LPARAM b=0L);

   DECLARE_MESSAGE_MAP()
   /**
     * This method is called from BaseControl::GetText and is expected to return
     * the value of the control in the string provided.
     * @param strValueOut - reference of string where value is returned.
     */

   virtual bool AllowExtension( const DString& strValueOut )
   {  // Override if you want to allow for autoexpand to have unused characters
      //  at the end
      return(false);
   }
   virtual bool AutoExpand(
                          const DString &result
                          );
   virtual void DoClear();
   virtual void DoGetText(
                         DString &strValueOut,
                         int index=0
                         ) const;
   /**
     * This method is called from BaseControl::Init to allow us to get new 
     * properties.
     * This may be called more than once (to allow the same control to be tied
     * to different fields, depending on context).
     */
   virtual void DoInit();
   /**
    * This method is called from BaseControl::SetText and is expected to sets
    * the value of the control to the specified value.
    * 
    * @returns flag with true = success, false = failure, check conditions
    * @param strValueIn value to set.
     * @param index - not used for this class
    * 
    * @return 
    */
   virtual bool DoSetText(
                         const DString &strValueIn,
                         int index=0
                         );

   virtual bool doSetCtrlReadOnly(bool bReadOnly);
private:
   int m_iSaveSelection;
   BFContainerId idSubstitute_;
   std::vector< DString * > m_tagVector;

   void ClearSelections();
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/uibase/DSTComboBox.h-arc  $
 * 
 *    Rev 1.11   23 Jun 2009 00:29:24   popescu
 * Fixed read only issues for the new style of combo box - when applying permission
 * 
 *    Rev 1.10   Jan 06 2003 16:46:40   PURDYECH
 * BFDataGroupId and BFContainerId changeover
 * 
 *    Rev 1.9   Nov 27 2002 15:06:08   PURDYECH
 * Documentation Changes
 * 
 *    Rev 1.8   Nov 13 2002 11:43:16   PURDYECH
 * Fixed up C4275 warning error.
 * 
 *    Rev 1.7   Nov 08 2002 10:00:32   PURDYECH
 * Use #pragma warning(...) to remove warning C4275 (non-Dll interface class used as base for interface class).
 * 
 *    Rev 1.6   Oct 09 2002 17:42:42   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.5   Aug 29 2002 12:57:06   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.4   22 May 2002 19:14:56   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.3   19 Mar 2002 13:36:14   PURDYECH
 * Added #pragma once include guard
 * Removed compile time "including..." message.
 * 
 *    Rev 1.2   Nov 06 2000 16:29:46   HERNANDO
 * Publicized SetSelectionByData
 * 
 *    Rev 1.1   Feb 15 2000 18:58:54   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 11:00:58   SMITHDAV
 * Initial revision.
// 
//    Rev 1.14   Jan 22 2000 14:53:16   YINGZ
// pass OnSetfocus to dlg
// 
//    Rev 1.13   Dec 29 1999 12:22:38   DT24433
// get values from bfproperties
// 
//    Rev 1.12   Dec 21 1999 14:38:04   YINGZ
// change OnKillfocus, give dlg a chance to get the notification
// 
//    Rev 1.11   Nov 15 1999 14:08:26   DT24433
// removed flag parm in constructor
// 
//    Rev 1.10   Nov 12 1999 17:11:58   YINGZ
// add onselchangeok
// 
//    Rev 1.9   Nov 12 1999 14:39:58   YINGZ
// add new functions
// 
//    Rev 1.8   Nov 05 1999 11:24:28   YINGZ
// just check in so it can be used
// 
//    Rev 1.7   Nov 02 1999 17:26:26   YINGZ
// add index
// 
//    Rev 1.6   Oct 22 1999 16:50:56   YINGZ
// other guy want to use it now
// 
//    Rev 1.5   Oct 19 1999 09:29:10   YINGZ
// set/kill focus
// 
//    Rev 1.4   Oct 14 1999 15:55:04   DT24433
// use interface methods for working with tooltip display
// 
//    Rev 1.3   Oct 14 1999 15:37:28   YINGZ
// add tooltip support and move combobase function here
// 
//    Rev 1.2   Oct 14 1999 10:03:12   DT24433
// added new methods
// 
//    Rev 1.1   Oct 11 1999 17:51:58   DT24433
// added header/trailer junk
 * 
 */
