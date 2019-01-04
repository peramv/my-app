
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
//    Copyright 2003 by International Financial Data Service
//
//******************************************************************************
//
// ^FILE   : MktIndexMasterMaintDlg.h
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : MktIndexMasterMaintDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
// -----------------------------------------------------------------------------
//
//******************************************************************************


#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif
class MktIndexMasterMaintDlg : public BaseMainDlg
{
public:
   /**
    * Standard dialog constructor for DSTC
    */
   MktIndexMasterMaintDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);

   //{{AFX_DATA(MktIndexMasterMaintDlg)
   enum
   {
      IDD = IDD_MKT_INDEX_MASTER
   };
   //}}AFX_DATA

   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(MktIndexMasterMaintDlg)
   protected:
   virtual BOOL PreTranslateMessage(MSG* pMsg);
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

protected:

   virtual bool doRefresh( GenericInterface * /*rpGICaller*/, 
                           const I_CHAR * /*szOriginalCommand*/ );

   // Generated message map functions
   //{{AFX_MSG(MktIndexMasterMaintDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnReset();
   afx_msg void OnBtnAddIndex();
   afx_msg void OnBtnDelIndex();
   afx_msg void OnBtnAddFund();
   afx_msg void OnBtnDelFund();
   afx_msg void OnBtnAdmDates();
   //}}AFX_MSG

   virtual bool GetOverrideItemString(long lSubstituteId, const DString& ColumnKey, DString& strOut );
   virtual void OnPostInitDialog();
	virtual bool doDisablePermCheckButton(UINT nID);
   void DoListItemChanged(UINT listControlID, const DString &strKey, bool bIsNewItem, bool bIsDummyItem);
   virtual void ControlUpdated( UINT controlID, const DString &strValue );

   DECLARE_MESSAGE_MAP()

public:

		virtual bool filterListColumn(const BFFieldId &idSubstitute, const DString& dstrTag);

private:

   LRESULT OpenFundClassListDlg( WPARAM, LPARAM );
   void EnableControls( );
   void ClearEnableChildControls( );
   void checkPermissionForInqUpdate();

   bool m_bFundNumberSupported;
   bool m_bIsIndexNewItem;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/MktIndexMasterMaintDlg.h-arc  $
//
//   Rev 1.3   Mar 21 2003 18:39:16   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.2   Feb 07 2003 16:09:48   HERNANDO
//Added ControlUpdated.
//
//   Rev 1.1   Feb 03 2003 15:26:36   HERNANDO
//Added DoListItemChanged and a new flag.
//
//   Rev 1.0   Jan 23 2003 10:33:00   HERNANDO
//Initial Revision
*/