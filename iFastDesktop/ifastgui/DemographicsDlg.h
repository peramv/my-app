#ifndef DEMOGRAPHICSDLG_H
#define DEMOGRAPHICSDLG_H
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
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : DemographicsDlg.h
// ^AUTHOR : Yakov Prager
// ^DATE   : 3/99
//
// ^CLASS    : DemographicsDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Handles the code for the Demographics dialog
//
//
//
// ^METHOD : process()
//
// ^DESCRIPTION : Get the intial stuff. Gets parms from call global.
//                
//
// ^PARAMETERS  :
//    ^^STRINGVECTOR *display - Values to add to list, comes from
//                                CallDataPtr()->_psvParm1
//    ^^string title            - Title of dialog, comes from
//                                CallDataPtr()->_sParm1
//
// ^RETURNS     :
//    ^^ int - Index into string vector of item selected or -1
//             CallDataPtr->iParm1
//
// ^THROWS      :
//
// ^EXAMPLE     :
//
// -----------------------------------------------------------------------------
//
//******************************************************************************

#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif


#ifndef __AFXDTCTL_H__
   #include <afxdtctl.h>
#endif

#ifndef DSTOLEDATETIME_H
   #include <uibase\DSTOleDateTime.h>
#endif

#ifndef DSTDATETIMECTRL_H
   #include <uibase\DSTDateTimeCtrl.h>
#endif

#if _MSC_VER > 1000
   #pragma once
#endif // _MSC_VER > 1000
// DemographicsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DemographicsDlg dialog

/**
 * Class that displays the Demograhics dialog.
 *
 * @author Yakov Prager
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 03/10/1999</dd></dl>
 * @version 0.1
 */
#include <uibase\ComboBase.h>
class DemographicsDlg : public BaseMainDlg
{
// Construction
public:
   DemographicsDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);

// Dialog Data
   //{{AFX_DATA(DemographicsDlg)
   enum
   {
      IDD = IDD_DEMOGRAPHICS
   };
   //}}AFX_DATA
   BOOL PreTranslateMessage( MSG* pMsg );

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(DemographicsDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(DemographicsDlg)
   virtual BOOL OnInitDialog();
// afx_msg void OnBtnChange();
   afx_msg void OnBtnReset();
   afx_msg void OnBtnAdmin();
   afx_msg void OnBtnHistorical();
   afx_msg void OnBtnDocList();
   afx_msg void OnBtnBroker();
   afx_msg void OnKillfocusEdtProfileNumber();
   afx_msg void OnKillfocusEdtRefNumber();
   afx_msg void OnKillfocusEdtProfileValue();
   afx_msg void OnCheckBoxClickByRange(UINT ctrlID);

   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()

   /**
     * Loading entity list and first selection
     * This method is invoked by the base architecture after OnInitDialog has 
     * completed.  This should be implemented for time intensive setup so that
     * the screen can display quickly and then do this processing.
     */
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
     * This is the implementation for OnOk processing to be done.  BaseMainDlg
     * enforces its actions by making OnOk private.
     * @returns a bool with true = perform Ok, false = stop process
     */
   virtual bool Ok()
   {
      // just return true for now

      return(true);
   }
   virtual void ControlUpdated(
                              UINT controlID,
                              const DString &strValue
                              );
   virtual void PostOk (bool okStatus);

   void tabSelectionChanged( UINT tabControlID, const DString& strPageName );

private:
   void setEmptyForNotAvailable( DString &str );
   bool GetDataForControl(UINT controlID,DString &strValueOut,bool bFormatted, int index) const;
   bool SetDataFromControl(UINT controlID, const DString &strValue, bool bFormatted,
                           SEVERITY &sevRtn, int index);
   void showHouseControls( bool bShow );
   void MarkReadOnly();
   void registerTabControls (bool bShow);
   void addStaticControls (bool bShow);

   void hideControls( void );

   void hideInvProfile( bool bShow );
   void hideEmploymentInfo( bool bShow );
   void hideAML( bool bShow );
   void hideInvObjective( bool bShow );
   void hideWitness( bool bShow );
   void hideMemorable( bool bShow );
   void hideAssociateComp( bool bShow );
   void hideKYCMisc( bool bShow );
   void hideHouseBroker( bool bShow );
   void hideSourceOfPayment( bool bShow );

   void DisplayCaption( void );


   LRESULT OpenBranchListDlg( WPARAM, LPARAM );
   DString GetMarket();

   DString m_strDemoTitle;
   DString m_dstrKYCAccountLevel;
   DString m_dstrEntityID;

   bool    m_bShowTabs;
};

#endif // !defined(AFX_DEMOGRAPHICSDLG_H__35654AD0_E3BA_11D2_A30A_005004146900__INCLUDED_)

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/DemographicsDlg.h-arc  $
 * 
 *    Rev 1.17   Sep 16 2011 06:07:34   kitticha
 * PETP0186486 - KYC Risk Tolerance.
 * 
 *    Rev 1.16   Oct 09 2008 11:54:00   jankovii
 * IN 1437673 KYC Broker info.
 * 
 *    Rev 1.15   Sep 12 2008 07:01:58   daechach
 * PET0128026 - KYC Phase 2
 * 
 *    Rev 1.14   Aug 28 2008 14:23:04   jankovii
 * IN 1388930 - NASU flow does not update document list unless at least one document.
 * 
 *    Rev 1.13   Jul 23 2008 16:28:42   jankovii
 * PET 59888 - AML Enhancement.
 * 
 *    Rev 1.12   Jul 06 2007 14:22:52   jankovii
 * PET 2360 FN96 - added support for AIM KYC screen.
 * 
 *    Rev 1.11   Feb 28 2004 16:16:10   HERNANDO
 * PET965 FN11 - Additional historical enhancement.
 * 
 *    Rev 1.10   Nov 20 2003 10:05:10   HSUCHIN
 * PTS 10024105 - Enable branch search for house brokers.
 * 
 *    Rev 1.9   Aug 19 2003 15:55:54   HSUCHIN
 * added support for branch / agent code input
 * 
 *    Rev 1.8   Jul 31 2003 13:24:34   FENGYONG
 * Add Historical logic
 * 
 *    Rev 1.7   Jul 11 2003 16:00:36   FENGYONG
 * PET 809, FN07 Show KYC screen FOR CIBC broker
 * 
 *    Rev 1.6   Mar 21 2003 18:34:58   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.5   Oct 09 2002 23:55:36   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.4   Sep 22 2000 17:30:34   HERNANDO
 * Added OnBtnReset()
 * 
 *    Rev 1.3   Aug 09 2000 11:49:28   ZHANGCEL
 * Bug fixed and code clean up
 * 
 *    Rev 1.2   Aug 08 2000 14:21:10   ZHANGCEL
 * Removed OnBtnChanged()
 * 
 *    Rev 1.1   Feb 15 2000 18:59:20   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 11:01:12   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.7   Nov 15 1999 12:19:16   ZHANGCEL
 * modify
 * 
 *    Rev 1.6   Nov 11 1999 09:55:10   ZHANGCEL
 * Using DST new controls to implement functions
 * 
 *    Rev 1.5   Sep 20 1999 13:13:40   HSUCHIN
 * Minor bug fixes, added missing control
 * 
 *    Rev 1.4   Sep 17 1999 14:12:16   HSUCHIN
 * Demographic change for C1 and M2
 * 
 *    Rev 1.3   25 Aug 1999 16:00:08   HUANGSHA
 * Check in temperorily
 * 
 *    Rev 1.2   Aug 11 1999 17:48:48   BUZILA
 * fix dtp control
 * 
 *    Rev 1.1   Jul 08 1999 10:04:58   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
