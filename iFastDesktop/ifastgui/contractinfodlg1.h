#ifndef CONTRACTINFODLG1_H
#define CONTRACTINFODLG1_H
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
// ^FILE   : ContractInfoDlg.h
// ^AUTHOR : Celia Zhang
// ^DATE   : 01/31/2000
//
// ^CLASS    : ContractInfoDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Handles the code for the Remarks dialog
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

#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif

#ifndef DSTCOMMONFUNCTION_HPP
   #include <ifastcbo\DSTCommonFunction.hpp>
#endif

#ifndef DSTOLEDATETIME_H
   #include <uibase\DSTOleDateTime.h>
#endif

#if _MSC_VER > 1000
   #pragma once
#endif // _MSC_VER > 1000

//*******************************************************************************************
// ContractInfoDlg dialog
// The class EffectiveDateSort is definde for the sorting of CONTRACT_LIST by effective date

class EffectiveDateSort1 
{
public:
   DString key;
   DString StartDate;

   // construction

   EffectiveDateSort1 ( DString dstrKey, DString dstrStartDate )
   {
      key = dstrKey;
      StartDate = dstrStartDate;
   }

   // operator <= overload
   bool operator <= ( const EffectiveDateSort1 & CtrEffDate) const
   {
      DSTCommonFunctions::DATE_ORDER ret;
      ret = DSTCommonFunctions::CompareDates( StartDate, CtrEffDate.StartDate );

      return( ( ret == DSTCommonFunctions::FIRST_EARLIER ) ||
              ( ret == DSTCommonFunctions::EQUAL) );
   }

};

class ContractInfoDlg1 : public BaseMainDlg
{
// Construction
public:
   ContractInfoDlg1(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );

// Dialog Data
   //{{AFX_DATA(ContractInfoDlg)
   enum
   {
      IDD = IDD_CONTRACT_INFO_1
   };
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(ContractInfoDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(ContractInfoDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnAdmDates();
   afx_msg void OnBtnEntity();
   afx_msg void OnBtnGuarantee();
   afx_msg void OnBtnUserDefMat();
   afx_msg void OnKillfocusDtpEffDate(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnAdd();
   afx_msg void OnDel();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()

   /**
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
   virtual bool doRefresh( GenericInterface * /*rpGICaller*/, 
                           const I_CHAR * /*szOriginalCommand*/ );

   virtual bool GetOverrideItemString( long lSubstituteId, 
                                       const DString& ColumnKey, 
                                       DString& strOut );

   virtual bool GetDataForControl( UINT controlID,
                                   DString &strValueOut,
                                   bool bFormatted,
                                   int index ) const;

   bool SetDataFromControl( UINT controlID,
                            const DString &strValue,
                            bool bFormatted,
                            SEVERITY &sevRtn,
                            int index );

   void DoListItemChanged( UINT listControlID, 
                           const DString &strKey, 
                           bool bIsNewItem, 
                           bool bIsDummyItem );

   virtual void ControlUpdated( UINT controlID, const DString &strValue );

private:
   // private member functions
   void LoadContractInfo();

   void setTitleBar ( );

   void UpdateLatestItemStopDate();

   bool GetEffDateMinusOne( DString& dstrEffDate, 
                            DString& dstrEffDateMinusOne );

   // private member data
   DString m_dstrAccountNumber;
   DString m_dstrShareHoldNum;
   DString m_dstrKey;
   DString m_dstrTransIdEmpty;
   DString m_dstrOwnerName;
   DString m_dstrSpouseName;
   DString m_dstrAskDofBirthSp;
   DString m_dstrAskDofBirthEntity;
   bool    bEffDateChanged;
   bool    m_bNewCopyAdded;
   bool    isSelItemNew;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
/******************************************************************************
 *              Revision Control Entries
 ******************************************************************************
 *
 * $Log:   Y:/VCS/BF iFAST/ifastgui/contractinfodlg1.h-arc  $
//
//   Rev 1.11   Apr 18 2005 13:55:30   hernando
//PET1024 FN02 - Added controlUpdated.
//
//   Rev 1.10   Mar 16 2005 14:33:06   hernando
//PET1024 FN02 - Added OnBtnUserDefMat.
//
//   Rev 1.9   Mar 21 2003 18:34:52   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.8   Oct 09 2002 23:55:36   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.7   22 May 2002 19:15:56   PURDYECH
//BFData Implementation
//
//   Rev 1.6   Nov 07 2001 15:32:44   ZHANGCEL
//Remove some memeber datas those are no longer be   ing used
//
//   Rev 1.5   18 Oct 2001 13:56:54   HSUCHIN
//code cleanup and bug fix for YEARS (changed to use string table and yrs )
//
//   Rev 1.4   Sep 06 2001 14:08:10   ZHANGCEL
//Added second parameter in ListViewControlFilter()
//
//   Rev 1.3   Aug 21 2001 11:40:26   OLTEANCR
//Removed AddCopy button
//
//   Rev 1.2   Aug 10 2001 11:44:36   OLTEANCR
//disabled AddCopy button
//
//   Rev 1.1   Jul 30 2001 09:31:42   OLTEANCR
//added ListViewControlFilter()
//
//   Rev 1.0   Jul 17 2001 09:58:42   OLTEANCR
//Initial revision.
 * 
 *    Rev 1.11   01 Mar 2001 16:41:26   KOVACSRO
 * Modifications for permission check.
 * 
 *    Rev 1.10   Dec 13 2000 14:41:56   KOVACSRO
 * Modified DoListItemChanged.
 * 
 *    Rev 1.9   Nov 30 2000 10:18:32   ZHANGCEL
 * Added a method for the title bar setting
 * 
 *    Rev 1.8   Sep 21 2000 14:43:46   ZHANGCEL
 * Bug fixed
 * 
 *    Rev 1.7   Jul 28 2000 16:46:00   ZHANGCEL
 * StopDate and EffectiveDate stuffs
 * 
 *    Rev 1.6   Jul 26 2000 11:14:26   ZHANGCEL
 * Added a new class to deal with the EffectiveDate and StopDate problem
 * 
 *    Rev 1.5   May 12 2000 17:53:58   ZHANGCEL
 * Deal with DofBirth checking problems
 * 
 *    Rev 1.4   Apr 20 2000 16:37:02   ZHANGCEL
 * Milestone check in
 * 
 *    Rev 1.3   Apr 14 2000 09:51:30   ZHANGCEL
 * modify
 * 
 *    Rev 1.2   Mar 17 2000 16:51:02   ZHANGCEL
 * Checked in for release
 */

#endif // !defined(AFX_ONTRACTINFODLG_H__02C9A811_D7F3_11D3_9AA5_00C04F33D7DE__INCLUDED_)
