
#ifndef ENTITYMAINTENANCEDLG_H
#define ENTITYMAINTENANCEDLG_H
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
//
// ^FILE   : EntityMaintenanceDlg.h
// ^AUTHOR : Yingbao  Li
// ^DATE   : 23/04/1999
//
// ^CLASS    : EntityMaintenanceDlg
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
 * Class that display the Entity Maintenance screen.
 *
 * @author 
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 03/04/1999</dd></dl>
 * @version 0.1
 */
class EntityMaintenanceDlg : public BaseMainDlg
{
// Construction
public:
   EntityMaintenanceDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);

// Dialog Data
   //{{AFX_DATA(EntityMaintenanceDlg)
   enum
   {
      IDD = IDD_ENTITY_MAINT
   };
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(EntityMaintenanceDlg)
public:
   virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL
   void DoKillfocus();

// Implementation
protected:
   // Generated message map functions
   //{{AFX_MSG(EntityMaintenanceDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnAdminDates();
   afx_msg void OnBtnWhereUsed();
   afx_msg void OnBtnDelete();
   afx_msg void OnBtnAdd();
   afx_msg void OnBtnReset();
   afx_msg void OnBtnSearch();
   afx_msg void OnBtnAddId();
   afx_msg void OnBtnDeleteId();
   afx_msg void OnKillfocusEdtIdValue();
   afx_msg void OnKillfocusCmbIdType();
   afx_msg void OnKillfocusCmbEntityType();
   afx_msg void OnKillfocusCmbIdValue ();
   afx_msg void OnKillfocusCmbRiskCntryOfExpr();
   afx_msg void OnKillfocusCmbRiskType();
   afx_msg void OnAccelEntity();
   afx_msg void OnBtnEntityDetails();
   afx_msg void OnBtnBenRelation();
   afx_msg void OnBtnEntityHistory();
   afx_msg void OnBtnCopyentity();
   afx_msg void OnBtnHistorical();
   afx_msg void OnBtnEntityAddress();  
   afx_msg void OnChkUpdateShareholder();
   afx_msg void OnBtnDeathClaim (); 
   afx_msg void OnBtnKYC();
   afx_msg void OnBtnGrant();
   afx_msg void OnBtnTaxJurisHistory();
   afx_msg void OnBtnEntRegDetail();
   afx_msg void OnBtnAddRisk();
   afx_msg void OnBtnDelRisk();
   afx_msg void OnBtnSetRiskLevel();
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
   LRESULT OpenFundClassListDlg( WPARAM, LPARAM );
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

   virtual bool doDisableControl (UINT nID, bool bIsNew);

private:
   void FillBeneficiarySection();
   bool GetOverrideItemString( long lSubstituteId, const DString &ColumnKey, DString &strOut );
   bool CalculateAvailablePercentForBeneficiary( const DString& benef, DString& result );
   void DoPreListItemChanged( UINT listControlID, const DString &strKey, bool bIsNewItem, bool bIsDummyItem );
   void fillEntityValues();
   void LoadListWithSelection( UINT listControlID, const DString &strKey );   
   void EnableEntityControls( bool bFlag );
   void DisplayJoinInfoControls( bool visible );
   bool GetDataForControl( UINT controlID, DString &strValueOut, bool bFormatted, int index ) const;
   void DisplayRespBeneficiaryControls();
   void DisplayEscrowControls();
   void DisplayBeneficiaryControls();
   void DisplayJointInfomationControls();
   void ShowOverLappedPart();
   void DisplayRegistrationAgentControls();
   void EnableEntityPhoneControls( bool bFlag = true );
   void EnableEntityIdsControls( const I_CHAR * functionCode, bool isNewItem);
   bool GetEntityEnable();
   void addTabPage( UINT iPageName );
   void removeTabPage( UINT iPageName );
   void hideAllExistingRESPControls();
   void updateEmployeeClass(const DString &dstrValue);
   void updateRT511RelatedControls();
   bool doesSupportMstrActAMSC();
   bool multipleRiskEnv();
   bool riskTabSelected();
   void DisplayRDSPControls();

//  CGXGridWnd m_gridWindow;

   DString m_dstrAccountNum;
   DString m_dstrKeySel;
   DString m_existAccount;
   DString m_availPercent;
   DString m_dstrCreatingAccount;
   DString m_dstrCreatingShareholder;
   DString m_dstrModelAccountNum;
   bool flg_add_new_item_mode;
   DString _entityId;
   bool flg_click_outside_ids_frame;
   bool flg_tab_pressed;
   bool flg_ready_for_background_search;
   bool flg_shift_pressed;
   bool flg_joint_controls;
   bool flg_not_opended_yet;
   bool m_bNewEntity;
   bool m_bSalutationFreeFormat;
   HACCEL m_hAccel;
   BOOL m_bUpdateShareholder;
   bool m_bPaternalMaternal;
};

// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

/******************************************************************************
 *              Revision Control Entries
 ******************************************************************************
 *
 * $Log:   Y:/VCS/BF iFAST/ifastgui/EntityMaintenanceDlg.h-arc  $
 * 
 *    Rev 1.33   Apr 16 2012 17:29:04   if991250
 * CPF Account Setup
 * 
 *    Rev 1.32   Mar 12 2010 14:50:04   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.31   Jan 26 2010 13:43:04   jankovii
 * PET165541 FN01 - QESI - RESP Gap
 * 
 *    Rev 1.30   16 Jan 2009 17:23:32   popescu
 * Incident 1544134 - various fixes
 * 
 *    Rev 1.29   Sep 12 2008 06:58:52   daechach
 * PET0128026 - KYC Phase 2
 * 
 *    Rev 1.28   Jul 25 2008 16:06:00   jankovii
 * PET 59888 AML Enhancement.
 * 
 *    Rev 1.27   Aug 10 2007 17:59:10   ivespaul
 * PET2360 - Web Integration - removed mgmt fee button.
 * 
 *    Rev 1.25   27 Jun 2007 16:48:00   popescu
 * Incident# 929895 - enable search button and create a new entity if this is used.
 * 
 *    Rev 1.24   Jun 01 2007 14:14:34   porteanm
 * PET2271 FN06 - Enable/Disable entity selelction based on gc.
 * 
 *    Rev 1.23   Nov 28 2005 10:01:18   zhengcon
 * Incident #457932 -- Disable control when the Entity is disabled
 * 
 *    Rev 1.22   Mar 09 2005 16:01:52   yingbaol
 * PET1171,FN01:EU saving  fix  check box issue
 * 
 *    Rev 1.21   Mar 04 2005 17:16:42   yingbaol
 * PET1171,FN01:EUSD add Tax jurisdiction
 * 
 *    Rev 1.20   Feb 25 2005 13:15:30   porteanm
 * PET 1171 FN01 - EUSD Entity Address Search.
 * 
 *    Rev 1.19   Feb 10 2005 08:15:40   porteanm
 * PTS 10038225 - Enable/Disable Entity controls for Escrow based on escrow band.
 * 
 *    Rev 1.18   Apr 23 2004 17:38:04   HERNANDO
 * PET1027 FN02 - Added tabSelectionChanged.
 * 
 *    Rev 1.17   Mar 01 2004 14:28:30   HERNANDO
 * PET965 FN11 - Added OnBtnHistorical.
 * 
 *    Rev 1.16   Oct 14 2003 11:30:44   HERNANDO
 * PET893 FN08 - Salutation Enhancement.
 * 
 *    Rev 1.15   Aug 22 2003 14:54:52   FENGYONG
 * remove delete relate rules to cbo
 * 
 *    Rev 1.14   Aug 21 2003 19:53:16   FENGYONG
 * KYC Joint info enhancement
 * 
 *    Rev 1.13   Mar 21 2003 18:36:04   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.12   Oct 09 2002 23:55:38   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.11   Jul 18 2002 11:39:48   KOVACSRO
 * Added doDisablePermCheckButton
 * 
 *    Rev 1.10   19 Mar 2002 13:44:38   PURDYECH
 * Added #pragma once include guard
 * Removed compile time "including..." message.
 * 
 *    Rev 1.9   06 Dec 2001 16:19:52   KOVACSRO
 * Added doSend.
 * 
 *    Rev 1.8   22 May 2001 16:42:02   KOVACSRO
 * Removed OnKillfocusBirthdate().
 * 
 *    Rev 1.7   Dec 20 2000 10:43:52   ZHANGCEL
 * Added a new function OnBtnCopyentity for CopyEntity requirement
 * 
 *    Rev 1.6   Dec 15 2000 12:03:46   KOVACSRO
 * Added isDummy to DoListItemChanged, DoPreListItemChanged.
 * 
 *    Rev 1.5   Oct 27 2000 10:59:24   DINACORN
 * Add OnKillfocusBirthDate() method
 * 
 *    Rev 1.4   Sep 25 2000 15:45:40   YINGBAOL
 * add HLLAPI entry for EntityHistory
 * 
 *    Rev 1.3   Aug 11 2000 15:59:46   YINGBAOL
 * fix change item bug
 * 
 *    Rev 1.2   Aug 01 2000 09:36:34   YINGBAOL
 * add delete logic
 * 
 *    Rev 1.1   Jul 26 2000 11:11:22   YINGBAOL
 * first version for C2
 * 
 *    Rev 1.0   Feb 15 2000 11:01:14   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.33   Feb 08 2000 13:10:24   VASILEAD
 * Added HLLAPI for EntityDetails
 * 
 *    Rev 1.32   Jan 25 2000 19:20:46   VASILEAD
 * Refresh stuff
 * 
 *    Rev 1.31   Jan 13 2000 17:39:42   VASILEAD
 * Added support for catching errors
 * 
 *    Rev 1.30   Jan 11 2000 14:35:46   VASILEAD
 * Fixed entity background search
 * 
 *    Rev 1.29   Jan 10 2000 16:15:04   VASILEAD
 * Added Joint information in Entity screen
 * 
 *    Rev 1.28   Jan 03 2000 12:10:02   DT24433
 * removed unused headers, misc.
 * 
 *    Rev 1.27   Dec 23 1999 15:48:12   VASILEAD
 * Added ids validation
 * 
 *    Rev 1.26   Dec 23 1999 14:18:06   VASILEAD
 * Added validation for ids
 * 
 *    Rev 1.25   Dec 21 1999 10:42:16   VASILEAD
 * Added Entity list iteration based on the string keys and not on the ObjectKey, added background search support
 * 
 *    Rev 1.24   Dec 15 1999 10:44:18   VASILEAD
 * Implemented background search for Entity screen
 * 
 *    Rev 1.23   Dec 07 1999 12:22:10   VASILEAD
 * Fixes in Entity
 * 
 *    Rev 1.22   Dec 06 1999 18:14:02   VASILEAD
 * Took out dynamic_cast
 * 
 *    Rev 1.21   Dec 01 1999 19:54:34   VASILEAD
 * Stuff
 * 
 *    Rev 1.20   Dec 01 1999 14:55:34   VASILEAD
 * Fixed bug on deleting entities
 * 
 *    Rev 1.19   Dec 01 1999 09:24:12   VASILEAD
 * NASU fixes
 * 
 *    Rev 1.18   Nov 30 1999 18:25:04   POPESCUS
 * changes related to the NASU flow
 * 
 *    Rev 1.17   Nov 29 1999 09:54:00   VASILEAD
 * Added business/edits for Entity screen
 * 
 *    Rev 1.16   Nov 25 1999 09:28:02   VASILEAD
 * Entity business/screen edits
 * 
 *    Rev 1.15   Nov 22 1999 15:21:46   BUZILA
 * changed IDs list to be ListControl not Grid
 * 
 *    Rev 1.14   Nov 20 1999 13:12:52   VASILEAD
 * Worked on entity - account relationship
 * 
 *    Rev 1.13   Nov 13 1999 16:35:00   BUZILA
 * fix
 * 
 *    Rev 1.12   Nov 07 1999 14:57:02   BUZILA
 * Changes
 * 
 *    Rev 1.11   27 Oct 1999 13:20:30   ZARKHINE
 * Functionality for Add
 * 
 *    Rev 1.10   Sep 01 1999 12:39:48   YINGBAOL
 * 
 *    Rev 1.9   Jul 28 1999 12:03:38   BUZILA
 * moved gxall.h include at dialog level
 * 
 *    Rev 1.8   Jul 27 1999 15:02:44   BUZILA
 * First M2 revision
 * 
 *    Rev 1.7   Jul 16 1999 09:34:18   YINGBAOL
 * 
 * 
 * 
 *    Rev 1.2   Jul 09 1999 16:54:56   YINGBAOL
*/

#endif // ENTITYMAINTENANCEDLG_H
