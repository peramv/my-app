#ifndef BANKINSTRDLG_H
#define BANKINSTRDLG_H
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Canada, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2001 by DST Canada, Inc.
//
//******************************************************************************
//
// ^FILE   : BankInstructionsDlg.h
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : 02/09/01
//
// ^CLASS    : BankInstructionsDlg
// ^SUBCLASS : BankInstructionsDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#include <ifastgui\ifasthistoricalinfo.hpp>

#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif
#ifndef INCLUDED_VECTOR
   #define INCLUDED_VECTOR
   #include <vector>
#endif
#ifndef __AFXDTCTL_H__
   #include <afxdtctl.h>
#endif
#ifndef DSTDATETIMECTRL_H
   #include <uibase\DSTDateTimeCtrl.h>
#endif
#ifndef COMBOBASE_H
   #include <uibase\combobase.h>
#endif

#ifndef _GXALL_H_
   #include <gxall.h>
#endif


#if _MSC_VER > 1000
   #pragma once
#endif // _MSC_VER > 1000
// BankInstructionsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// BankInstructionsDlg dialog


class BankInstructionsDlg : public BaseMainDlg
{
// Construction
public:
   BankInstructionsDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, 
      GenericInterface* pGIParent, const Command& rCommand);
   ~BankInstructionsDlg();
// Dialog Data
   //{{AFX_DATA(BankInstructionsDlg)
//	enum { IDD = IDD_BANKINS };
   enum
   {
      IDD = IDD_BANK_INSTRUCTIONS
   };
   //}}AFX_DATA

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(BankInstructionsDlg)
public:
   virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   void GetCellProperties( UINT ctrlId, 
                           const DString &rowKey, 
                           const DString &colKey, 
                           BFContainerId& idContainer,
                           BFFieldId &idField,
                           DString& listItemKey,
                           int& nCellState,
                           UINT& cellCtrlType, 
                           int& nCtrlInitMode,
                           BFFieldId &idSubstitution,
                           DString& comboList, 
                           DString& mask,
                           int& nComboSortingMode ,
                           DString& dstrAllowedChar );	 

   void GridControlUpdated( UINT ctrlId,
                            const DString &rowKey,
                            const DString &colKey,
                            const DString &strNewValue,
                            bool bFormatted,
                            SEVERITY nSeverity);
// Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(BankInstructionsDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnTo();
   afx_msg void OnBtnAdd();
   afx_msg void OnBtnDel();
   afx_msg void OnBtnAdmDates();
   afx_msg void OnBtnReset();
   afx_msg void OnSelchangeCmbCbIdType();
   afx_msg void OnSelchangeCmbIdType();
   afx_msg void OnBtnHistorical();
   afx_msg void OnChkAcctBanking();
   afx_msg void OnChkShrBanking();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()

   void SetDlgCaption();
   void SetToBtnCaption(const DString& dstrBankType);
   bool doDisablePermCheckButton(UINT nID);
   void doDisableNonPermButtons();
   virtual bool doDisableControl(UINT nID, bool bIsNew);
   virtual void DoPreListItemChanged(UINT listControlID,
      const DString &strKey, bool bIsNewItem, bool bIsDummyItem);
   virtual void DoListItemChanged(UINT listControlID, const DString &strKey,
      bool bIsNewItem,  bool bIsDummyItem);
   virtual bool GetOverrideItemString(long lSubstituteId, 
      const DString &ColumnKey, DString &strOut);

   void OnPostInitDialog();

   virtual SEVERITY doInit();
   virtual bool doRefresh(GenericInterface *rpGICaller, 
      const I_CHAR *szOriginalCommand);
   void showFields();
   void showCBFields();
   void showControl(int ctrlId, bool show);
   virtual bool SetDataFromControl(UINT controlID,
      const DString &strValue, bool bFormatted,
      SEVERITY &sevRtn, int index = 0);
   virtual bool GetDataForControl(UINT controlID,
      DString &strValueOut, bool bFormatted, int index = 0) const;
   void ControlUpdated(UINT ControlID, const DString &strValue);
   void SetUserAccesFuncCode();
   bool ListViewControlFilter(long lSubstituteId, 
      const DString *strKey);

//###temporary fix for demo mode
   bool isDemoMode();
   void setDefaultFilterForBankingInstrLevel(bool bSetDummyBankInstrTypeField = true );
private:
   void modifyControlStyle (const DString& dstBankIDType, UINT nID);
   LRESULT OpenBankListDlg (WPARAM, LPARAM);
   DString m_strUserAccessCode,
           m_fundSponsorDesc,
           m_dstrBankInstructionsListSelectionKey;
   CFont *m_pFont;
   bool m_bEnableHistory;
   int  m_bShrBank;
   bool bIsRedRegAgentInst();
   bool m_bShrDummyList_Added;
   bool m_bAcctDummyList_Added;
   bool m_bFromPostinitDlg;
};

#endif
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/BankInstructionsDlg.h-arc  $
 * 
 *    Rev 1.19   Apr 24 2012 21:34:42   wp040039
 * PETP0187485 - Trade Entry And Processing
 * 
 *    Rev 1.18   Jul 24 2009 01:18:58   dchatcha
 * PET 157825 - FN 13 - Dilution Allocation Enhancements, Sorting combo in grid.
 * 
 *    Rev 1.17   Nov 02 2006 11:46:10   ZHANGCEL
 * PET2217 FN26 - Add a new parameter for Bank Instruction title display
 * 
 *    Rev 1.16   Feb 28 2004 16:58:58   HERNANDO
 * PET965 FN11 - Additional historical enhancement.
 * 
 *    Rev 1.15   Oct 06 2003 12:44:36   popescu
 * Added banking support for DirectTrading enhancement
 * 
 *    Rev 1.14   Oct 04 2003 16:02:02   popescu
 * CIBC PET 809, FN 13;
 * also cleaned-up BankSearch and BankList objects,
 * replaced with FinancialInstitutionList
 * 
 *    Rev 1.13   Aug 07 2003 18:35:48   popescu
 * added new param that will help set the UI selection on the desired bank
 * 
 *    Rev 1.12   Jun 18 2003 17:45:20   popescu
 * RRIF Banking Enhancement , business rules, bug fixes 
 * 
 *    Rev 1.11   Jun 01 2003 17:08:20   popescu
 * Systematic & Distribution banking work
 * 
 *    Rev 1.10   May 31 2003 11:55:42   popescu
 * RRIF bank work
 * 
 *    Rev 1.9   May 27 2003 13:14:10   popescu
 * RRIF Banking work
 * 
 *    Rev 1.8   May 22 2003 14:13:46   popescu
 * Replaced name 'BankInstr' with 'BankInstructions'; 
 * simplified child lists getters for the Shareholder object
//
//   Rev 1.24   Mar 21 2003 18:33:06   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.23   Feb 04 2003 17:21:10   KOVACSRO
//Added GridControlUpdated.
//
//   Rev 1.22   Oct 09 2002 23:55:30   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.21   Sep 11 2002 09:53:14   KOVACSRO
//Added m_strUserAccessCode
//
//   Rev 1.20   Aug 29 2002 20:09:24   SMITHDAV
//CellProperties fixes
//
//   Rev 1.19   Aug 29 2002 18:14:28   SMITHDAV
//Additional FieldId fixes.
//
//   Rev 1.18   Aug 29 2002 12:57:14   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.17   Jul 24 2002 13:25:40   KOVACSRO
//Added doDisableControl().
//
//   Rev 1.16   Jun 07 2002 17:54:26   KOVACSRO
//removed bank info
//
//   Rev 1.15   Apr 08 2002 17:02:34   HERNANDO
//Added getBankIdNumInfo, getBankTransitNumInfo, and getBankAccNumInfo from DSTCommonFunctions.  Made getBankAccNumInfo Market dependent.
//
//   Rev 1.14   23 Nov 2001 14:22:02   KOVACSRO
//perm check changes.
//
//   Rev 1.13   Jun 06 2001 11:58:50   DINACORN
//temporary fix for demo mode - added isDemoMode()
//
//   Rev 1.12   14 May 2001 14:41:44   KOVACSRO
//Added param. to ModifyControlStyle()
//
//   Rev 1.11   14 May 2001 11:16:34   KOVACSRO
//Added ModifyControlStyle().
//
//   Rev 1.10   19 Apr 2001 17:13:40   KOVACSRO
//perm. check stuff.
//
//   Rev 1.9   10 Apr 2001 14:14:08   KOVACSRO
//added OnSelCmbUseChanged()
//
//   Rev 1.8   Apr 09 2001 15:50:36   YINGBAOL
//implement acctUse etc. for TransactionBank
//
//   Rev 1.7   Apr 06 2001 12:57:48   YINGBAOL
//lauch bank search dialog
//
//   Rev 1.6   Apr 05 2001 16:02:14   YINGBAOL
//fix bugs
//
//   Rev 1.5   Apr 03 2001 15:25:06   YINGBAOL
//add SetControlReadOnly Method
//
//   Rev 1.4   27 Mar 2001 16:46:44   KOVACSRO
//perm. check stuff
//
//   Rev 1.3   27 Mar 2001 11:47:00   BUZILAMI
//BankSearch launch preparation
//
//   Rev 1.2   16 Mar 2001 16:26:54   BUZILAMI
//Added SetDlgCaption
//
//   Rev 1.1   07 Mar 2001 15:44:40   BUZILAMI
//Broker, Branch, SlsRep Bank Instructions changes
//
//   Rev 1.0   Feb 21 2001 15:58:42   BUZILAMI
//Initial revision.
 * 
 */
