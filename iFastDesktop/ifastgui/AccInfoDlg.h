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
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : AccInfoDlg.h
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : 06/04/99
//
// ^CLASS    : AccInfoDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Handles the code for the Fund Info screen
//
// -----------------------------------------------------------------------------
//
//******************************************************************************

#define LAST_NAME_COLUMN         0
#define FIRST_NAME_COLUMN        1
#define TELEPHONE_NUM_COLUMN     2
#define ADDRESS_COLUMN           3

#include <ifastgui\basemaindlg.h>

#include <bfutil\bfdate.hpp>
#include <uibase\listctrl.h>
#include <uibase\combobase.h>
#include <uibase\dstdatetimectrl.h>

class AccInfoDlg : public BaseMainDlg
{
public:
   // standard constructor
   AccInfoDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
// Dialog Data
   //{{AFX_DATA(AccInfoDlg)
   enum
   {
      IDD = IDD_ACCINFO
   };
   //}}AFX_DATA

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(AccInfoDlg)
public:
   virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:
   virtual bool doRefresh( GenericInterface * /*rpGICaller*/, 
                           const I_CHAR * /*szOriginalCommand*/ );
   virtual SEVERITY doInit();
   virtual void PostOk( bool );
   virtual bool PreOk(); 
   virtual void ControlUpdated( UINT controlID, const DString &strValue );
   virtual bool GetDataForControl( UINT controlID, DString &strValueOut, 
                                   bool bFormatted, int index ) const;

   /*
   virtual void InitControl( UINT controlID );
   virtual bool GetDataForControl( UINT controlID, DString &strValueOut, 
      bool bFormatted, int index ) const;
   virtual bool SetDataFromControl( UINT controlID, const DString &strValue, 
      bool bFormatted, SEVERITY &sevRtn, int index );
   */
   virtual void OnPostInitDialog();
   // Generated message map functions
   //{{AFX_MSG(AccInfoDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnAdmDates();
   afx_msg void OnBtnHistorical();
   afx_msg void OnBtnEntity();
   afx_msg void OnBtnEntity2();
   afx_msg void OnBtnReset();
   afx_msg void OnKillFocusSalesRep();
   afx_msg void OnBtnCOA();


   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()


private:
   //methods
   void adjustToProcessType();
   void setTitle();
   void updateTaxTypeSchedule();

   LRESULT OpenBrokerListDlg( WPARAM, LPARAM );
   LRESULT OpenBranchListDlg( WPARAM, LPARAM );
   LRESULT OpenSlsRepListDlg( WPARAM, LPARAM );
   void CanadaPensionLegCodeChk( bool initial = false );
   BFDate::DATE_FORMAT getDateFormatFromClientLocale(const ClientLocale& rLocale) const;
   BFDate::DATE_FORMAT inferMaskFormat( const DString& dstrMask ) const;

//properties
   DString m_dstrMarket;
   DString _strAccNo;
   bool _bManualAccNum;
   bool _bAccCreated;
   DString dstrOldTaxType;
   DString m_strPreviousTaxType;
   DString dstrOldPensionJuris;
   void enableControls();
   bool _bAskCreateSalesRep;
   DString _shareholderNum,
      _fromScreen;

};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/AccInfoDlg.h-arc  $
 * 
 *    Rev 1.24   Jul 12 2012 11:10:48   dchatcha
 * P0191601 FN03 - Manual T3/RL 16/NR4 Slip for Taxable Trusts.
 * 
 *    Rev 1.23   Feb 17 2012 10:05:22   popescu
 * refresh portfolio - temporary backed the code out.
 * 
 *    Rev 1.22   Feb 08 2012 20:48:50   dchatcha
 * IN# 2837678 - REL12.2-PET0186484- New INA Contract Information screen issues as on 6 Feb 2012
 * 
 *    Rev 1.21   Feb 07 2012 18:11:28   dchatcha
 * IN# 2837678 - REL12.2-PET0186484- New INA Contract Information screen issues as on 6 Feb 2012
 * 
 *    Rev 1.20   15 Apr 2008 12:13:40   kovacsro
 * PET2255 FN47 - New Ontario LIF
 * 
 *    Rev 1.19   Jan 26 2006 12:04:40   popescu
 * Disable the COA button on the AccInfo screen if this is invoked from the  COA dialog
 * 
 *    Rev 1.18   Jul 06 2005 11:01:24   ZHANGCEL
 * PET1141 - FN05 -- NSCC Broker enhancement
 * 
 *    Rev 1.17   Oct 27 2003 16:33:10   ZHANGCEL
 * PTS ticket 10023250: added a member data :_shareholderNum which is used to display the ShareHolder Number on the title bar
 * 
 *    Rev 1.16   Jul 30 2003 11:27:20   FENGYONG
 * CIBC enhancement PET809_FN46
 * 
 *    Rev 1.15   Apr 15 2003 12:09:24   sanchez
 * Ticket 10015035 sync up with version 1.13.10
 * 
 *    Rev 1.14   Mar 21 2003 18:30:28   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.13   Nov 05 2002 10:41:30   HERNANDO
 * Removed AMS Controls and function.
 * 
 *    Rev 1.12   Oct 09 2002 23:55:26   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.11   Aug 09 2002 16:14:28   HSUCHIN
 * added private variable to store old jurisdiction info
 * 
 *    Rev 1.10   May 23 2002 10:39:34   PURDYECH
 * BFData Implementation Verification Corrections
 * 
 *    Rev 1.9   22 May 2002 19:15:32   PURDYECH
 * BFData Implementation
 */
