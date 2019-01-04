#ifndef GUARANTEEINFODLG1_H
#define GUARANTEEINFODLG1_H
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
// ^FILE   : GuaranteeInfoDlg1.h
// ^AUTHOR :
// ^DATE   : 
//
// ^CLASS    : 
// ^SUBCLASS :
//******************************************************************************

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

#if _MSC_VER > 1000
   #pragma once
#endif // _MSC_VER > 1000
//
// GuaranteeInfoDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// GuaranteeInfoDlg dialog

class GuaranteeInfoDlg1 : public BaseMainDlg
{
// Construction
public:
   GuaranteeInfoDlg1(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
// Dialog Data
   //{{AFX_DATA(GuaranteeInfoDlg)
   enum
   {
      IDD = IDD_GUARANTEE_INFO_1
   };
   //}}AFX_DATA

   virtual bool GridControlFilter( UINT ctrlId, const DString &rowKey );


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(GuaranteeInfoDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(GuaranteeInfoDlg)
   afx_msg void OnBtnContract();
   afx_msg void OnBtnEntity();
   afx_msg void OnBtnMore();
   afx_msg void OnBtnSegOptions();
   virtual BOOL OnInitDialog();
   afx_msg void OnRbContract();
   afx_msg void OnRbYearTerm();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()


   void OnPostInitDialog();

   virtual SEVERITY doInit();
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
                                 DString& mask);

   virtual void DoListItemChanged(
                                 UINT listControlID, 
                                 const DString &strKey, 
                                 bool bIsNewItem , 
                                 bool bIsDummyItem);

   virtual bool GetDataForControl(
                                 UINT controlID,
                                 DString &strValueOut,
                                 bool bFormatted,
                                 int index
                                 ) const;

   // bool ListViewControlFilter( long lSubstituteId );

   bool GetOverrideItemString( long lSubstituteId,
                               const DString& ColumnKey, DString& strOut );


private:
   // private member functions
   void AdjustControl();
   void setTitleBar ( );

   // private member data  
   DString m_dstrAccountNumber;
   DString m_dstrShareHoldNum;
   DString m_dstrKey;
   DString m_dstrGuarAcctTotal;
   DString _strTotal;
   bool m_bFirst;
   virtual bool ListViewControlFilter( long lSubstituteId, const DString *strKey = NULL  );
   bool m_rbContract;
   bool m_rbPolicyYearTerm;
   int _count1;
   int _count2;
   double _dTotal;

};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

/******************************************************************************
 *              Revision Control Entries
 ******************************************************************************
 *
 * $Log:   Y:/VCS/BF iFAST/ifastgui/GuaranteeInfoDlg1.h-arc  $
//
//   Rev 1.7   Mar 21 2003 18:37:16   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.6   Oct 09 2002 23:55:42   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.5   Aug 29 2002 20:09:26   SMITHDAV
//CellProperties fixes
//
//   Rev 1.4   Aug 29 2002 18:14:32   SMITHDAV
//Additional FieldId fixes.
//
//   Rev 1.3   Sep 06 2001 14:09:42   ZHANGCEL
//Added second parameter in ListViewControlFilter()
//
//   Rev 1.2   Aug 21 2001 17:06:48   OLTEANCR
//added _count1, _count2, _dTotal, m_dstrGuarAcctTotal
//
//   Rev 1.1   Jul 30 2001 09:32:56   OLTEANCR
//added radio buttons
//
//   Rev 1.0   Jul 17 2001 10:00:36   OLTEANCR
//Initial revision.
 * 
 *    Rev 1.7   Dec 13 2000 14:43:32   KOVACSRO
 * Modified DoListItemChanged.
 * 
 *    Rev 1.6   Nov 30 2000 10:20:02   ZHANGCEL
 * Added a method for the title bar setting
 * 
 *    Rev 1.5   Jul 28 2000 16:48:38   ZHANGCEL
 * Fund Number problem
 * 
 *    Rev 1.4   Mar 30 2000 15:18:38   ZHANGCEL
 * Change logic for getting detail records
 * 
 *    Rev 1.3   Mar 17 2000 16:54:14   ZHANGCEL
 * Checked in for release
 * 
 *    Rev 1.2   Mar 10 2000 12:53:08   ZHANGCEL
 * Changed some controls
 * 
 *    Rev 1.1   Mar 08 2000 17:13:42   ZHANGCEL
 * Improve revision
// 
//    Rev 1.3   Mar 03 2000 15:54:32   ZHANGCEL
// Bug fixed
// 
//    Rev 1.2   Feb 22 2000 17:43:10   ZHANGCEL
// Changed fields type
 */

#endif // !defined(AFX_GUARANTEEINFODLG_H__CB77A5C1_C9D0_11D3_9A9B_00C04F33D7DE__INCLUDED_)

