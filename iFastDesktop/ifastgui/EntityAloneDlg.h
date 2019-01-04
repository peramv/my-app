
#ifndef ENTITYALONEDLG_H
#define ENTITYALONEDLG_H
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
//    Copyright 2005 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : EntityAloneDlg.h
// ^AUTHOR : Yingbao  Li
// ^DATE   : 23/02/2005
//
// ^CLASS    : EntityAloneDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif
#include <ifastgui\ifasthistoricalinfo.hpp>

/**
 * Class that display the Entity Alone screen.
 *
 * @author 
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 02/23/2005</dd></dl>
 * @version 0.1
 */
class EntityAloneDlg : public BaseMainDlg
{
// Construction
public:
   EntityAloneDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);

// Dialog Data
   //{{AFX_DATA(EntityAloneDlg)
   enum
   {
      IDD = IDD_ENTITY_ALONE
   };
   //}}AFX_DATA

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(EntityAloneDlg)
public:
   virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL
  // void DoKillfocus();

// Implementation
protected:
   // Generated message map functions
   //{{AFX_MSG(EntityAloneDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnAdminDates();
   afx_msg void OnBtnDelete();
   afx_msg void OnBtnAdd();
   afx_msg void OnBtnReset();
   afx_msg void OnBtnMore();
   afx_msg void OnBtnAddId();
   afx_msg void OnBtnDeleteId();
   afx_msg void OnBtnEntityHistory();
   afx_msg void OnBtnHistorical();
   afx_msg void OnBtnAddWhereUsed();
   afx_msg void OnBtnDelWhereUsed();
   afx_msg void OnBtnSearch();
   afx_msg void OnChkUpdateShareholder();
   afx_msg void OnBtnMoreWhereUsed();
   afx_msg void OnBtnAddress();
   afx_msg void OnBtnCutOffTime();
   afx_msg void OnBtnManagementFee();
   afx_msg void OnBtnKYC();
   afx_msg void OnBtnEntRegDetail();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()

   void OnPostInitDialog();
   /**
     * Get parameters from InterProcessData.
     * @returns SEVERITY, check conditions if > NO_SEVERITY
     */
   virtual SEVERITY doInit();
   /**
     * Required implementation for the refresh method.  No refresh activity is
     * performed for this class.
     * @param rpGICaller - A reference pointer to the calling object.
     * @param szOriginalCommand - A string literal representing the original
     * command issuing the refresh (which may provide a hint on whether this
     * object needs to check for refresh).
     * @returns true if successful, call getErrors for errors if false
     */
   virtual bool doRefresh(
                         GenericInterface * /*rpGICaller*/, 
                         const I_CHAR * /*szOriginalCommand*/
                         );
   /**
     * This method should be overridden in the derived dialog if there is
     * OnOk processing to be done after the base processing.  Note that the OnOk
     * processing can no longer be "cancelled" at this point.  BaseMainDlg 
     * enforces its actions by making OnOk private.
     * @param bCancelStatus - true = Ok successful, false = Ok failed
     */
   virtual void PostOk(
                      bool /* bOkStatus */
                      );
   virtual bool PreOk();

   virtual void ControlUpdated(UINT controlID, const DString &dstrValue);
   virtual void DoListItemChanged(
                                 UINT listControlID,
                                 const DString &strKey, 
                                 bool bIsNewItem,
                                 bool bIsDummyItem
                                 );


   bool doSend(
              GenericInterface *rpGICaller,
              const I_CHAR * szMessage
              );
   /**
    implement here any bussiness rules related to the buttons that were added for permission check (add or delete buttons)
    return true if it should be disabled and false if it should be enabled
    DO NOT call EnableWindow() here
    * @param nID - the control's ID
    */
   bool doDisablePermCheckButton(UINT nID);

   void tabSelectionChanged( UINT tabControlID, const DString& strPageName );

private:
   bool GetOverrideItemString( long lSubstituteId, const DString &ColumnKey, DString &strOut );
   void fillEntityValues();
   void EnableEntityControls( bool bFlag );
   void EnableEntityIdsControls( const I_CHAR * functionCode, bool isNewItem );
   bool GetDataForControl( UINT controlID, DString &strValueOut, bool bFormatted, int index ) const;
   void EnableEntityPhoneControls();
   bool disableEntityDeleteButton ();
   bool disableWhereUseDeleteButton ();
   bool disableCutOffTimeButton ();
   LRESULT OpenFundClassListDlg( WPARAM, LPARAM );
   LRESULT OpenFundGroupDlg( WPARAM, LPARAM );

   DString m_dstrKeySel;
   DString _entityId;
   bool m_bNewEntity;
   bool m_bSalutationFreeFormat;
   BOOL m_bUpdateShareholder;
};

/******************************************************************************
 *              Revision Control Entries
 ******************************************************************************
 *
 * $Log:   Y:/VCS/BF iFAST/ifastgui/EntityAloneDlg.h-arc  $
//
//   Rev 1.7   Sep 12 2008 06:59:56   daechach
//PET0128026 - KYC Phase 2
//
//   Rev 1.6   Aug 10 2007 18:34:46   ivespaul
//PET2360 - Web Integration - moved button from Entity Maint Dlg to All Entity aka ENTITY_ALONE Dlg.
//
//   Rev 1.5   Nov 20 2006 13:49:16   jankovii
//PET 2287 FN01 - Grupo Mundial Trade Aggregation.
//
//   Rev 1.4   Jul 21 2006 16:38:48   jankovii
//PET 2192 FN02 - Dealings - Sender Cut Off Time.
//
//   Rev 1.3   Jan 10 2006 11:16:36   jankovii
//Incident #511921 - Wrong error message when delete the only whereuse type in an entity.
//
//   Rev 1.2   Oct 27 2005 10:35:18   jankovii
//PET1228_FN01-EU Savings Directive Phase
//
//   Rev 1.1   Mar 09 2005 16:08:58   yingbaol
//PET1171,FN01: EU saving, entity update
//
//   Rev 1.0   Mar 01 2005 09:59:00   yingbaol
//Initial revision.
 * 

 */
#endif // ENTITYALONEDLG_H

