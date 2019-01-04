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
// ^FILE   : MktIndexValuesMaintDlg.h
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : MktIndexValuesMaintDlg
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
class MktIndexValuesMaintDlg : public BaseMainDlg
{
public:
   /**
    * Standard dialog constructor for DSTC
    */
   MktIndexValuesMaintDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);

   //{{AFX_DATA(MktIndexValuesMaintDlg)
   enum
   {
      IDD = IDD_MKT_INDEX_VALUES
   };
   //}}AFX_DATA

   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(MktIndexValuesMaintDlg)
   protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

protected:

   virtual bool doRefresh( GenericInterface *, const I_CHAR *);

   // Generated message map functions
   //{{AFX_MSG(MktIndexValuesMaintDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnReset();
   afx_msg void OnBtnAddIndex();
   afx_msg void OnBtnDelIndex();
   afx_msg void OnBtnAdmDates();
   afx_msg void OnBtnMore();
   afx_msg void OnBtnSearch();
   //}}AFX_MSG

   virtual bool GetOverrideItemString(long lSubstituteId, const DString& ColumnKey, DString& strOut );
   virtual void OnPostInitDialog();
	virtual bool doDisablePermCheckButton(UINT nID);
   virtual void ControlUpdated( UINT controlID, const DString &strValue );
   virtual bool GetDataForControl(UINT controlID, DString &strValueOut, bool bFormatted, int index ) const;

   DECLARE_MESSAGE_MAP()

   virtual void DoListItemChanged (UINT listControlID, const DString &strKey, bool bIsNewItem, bool bIsDummyItem);

public:

		virtual bool filterListColumn(const BFFieldId &idSubstitute, const DString& dstrTag);

private:

   void EnableControls( );
   void ClearEnableChildControls( );
   void checkPermissionForInqUpdate();

   bool m_bFundNumberSupported;

   void enableControls ( const DString &inputDataType );
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/MktIndexValuesMaintDlg.h-arc  $
//
//   Rev 1.3   Jan 16 2012 13:49:32   wp040027
//P0188394_Performance Fees - Benchmark Upload
//
//   Rev 1.2   Mar 21 2003 18:39:22   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.1   Feb 03 2003 15:47:22   HERNANDO
//Added GetDataForControl.
//
//   Rev 1.0   Jan 29 2003 13:00:50   HERNANDO
//Initial Revision
//
//   Rev 1.0   Jan 23 2003 10:33:00   HERNANDO
//Initial Revision
*/