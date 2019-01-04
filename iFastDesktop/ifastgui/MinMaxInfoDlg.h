#ifndef MINMAXINFODLG_H
#define MINMAXINFODLG_H
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
// ^FILE   : MinMaxInfoDlg.h
// ^AUTHOR : Celia Zhang
// ^DATE   : 02/15/2000
//
// ^CLASS    : MinMaxInfoDlg
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

#ifndef DSTDATETIMECTRL_H
   #include <uibase\DSTDateTimeCtrl.h>
#endif

#ifndef INCLUDED_VECTOR
   #define INCLUDED_VECTOR
   #include <vector>
#endif

#ifndef __AFXDTCTL_H__
   #include <afxdtctl.h>
#endif
#if _MSC_VER > 1000
   #pragma once
#endif // _MSC_VER > 1000
// MinMaxInfoDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MinMaxInfoDlg dialog

class MinMaxInfoDlg : public BaseMainDlg
{
// Construction
public:
   MinMaxInfoDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);

// Dialog Data
   //{{AFX_DATA(MinMaxInfoDlg)
   enum
   {
      IDD = IDD_MINMAX_INFO
   };
   DSTDateTimeCtrl m_DtpAsofDate;
   //}}AFX_DATA

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(MinMaxInfoDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation

protected:

   // Generated message map functions
   //{{AFX_MSG(MinMaxInfoDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnSearch();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()

//   DSTDateTimeCtrl	m_DtpAsofDate;
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
   virtual bool doRefresh(
                         GenericInterface * /*rpGICaller*/, 
                         const I_CHAR * /*szOriginalCommand*/
                         );
   virtual void GetCellProperties(
                                 UINT ctrlId,
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

private:
   // private member functions
   bool search();

   // private member data
   DString m_dstrAccountNumber;
   DString m_dstrTaxType;
   bool m_bClear;
};

//{{AFX_INSERT_LOCATION
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
//}}AFX_INSERT_LOCATION

#endif // !defined(AFX_MINMAXINFODLG_H__B6BEE7A1_E311_11D3_9AA8_00C04F33D7DE__INCLUDED_)

/******************************************************************************
 *              Revision Control Entries
 ******************************************************************************
 *
 * $Log:   Y:/VCS/BF iFAST/ifastgui/MinMaxInfoDlg.h-arc  $
 * 
 *    Rev 1.8   Jul 24 2009 01:37:56   dchatcha
 * PET 157825 - FN 13 - Dilution Allocation Enhancements, Sorting combo in grid.
 * 
 *    Rev 1.7   Mar 21 2003 18:39:12   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.6   Oct 09 2002 23:55:48   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.5   Aug 29 2002 20:09:26   SMITHDAV
 * CellProperties fixes
 * 
 *    Rev 1.4   Aug 29 2002 18:14:32   SMITHDAV
 * Additional FieldId fixes.
 * 
 *    Rev 1.3   19 Mar 2002 13:44:50   PURDYECH
 * Added #pragma once include guard
 * Removed compile time "including..." message.
 * 
 *    Rev 1.2   Oct 18 2000 17:46:36   ZHANGCEL
 * Code clean up
 * 
 *    Rev 1.1   May 29 2000 09:21:50   BUZILA
 * maskeEdit controls
 * 
 *    Rev 1.0   Mar 22 2000 12:52:18   BUZILA
 * Initial revision.
 * 
 */
