#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2003 by International Financial, Inc.
//
//******************************************************************************
//
// ^FILE   : AggregatedOrderDlg.h
// ^AUTHOR : Celia Zhang
// ^DATE   : Nev 18, 2004
//
// ^CLASS    : AggregatedOrderDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************


#include <ifastgui\basemaindlg.h>
#include <uibase\ifdslistctrl.h>
#include <ifastgui\ifasthistoricalinfo.hpp>

#if _MSC_VER > 1000
   #pragma once
#endif // _MSC_VER > 1000

class AggregatedOrderDlg : public BaseMainDlg
{

public:

//******************************************************************************
// Dialog Data 
//******************************************************************************

   //{{AFX_DATA(ReportDlg)
   enum
   {
      IDD =  IDD_AGGREGATE
   };
	  CString m_StrNumberOfTrade;

   //}}AFX_DATA

   //******************************************************************************
   // Constructor
   //******************************************************************************

   AggregatedOrderDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);

   //******************************************************************************
   // Destructor
   //******************************************************************************

   ~AggregatedOrderDlg(); 

// Implementation
protected:

   //******************************************************************************
   // Overrides
   // ClassWizard generated virtual function overrides
   //******************************************************************************
  
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   //******************************************************************************
   // Generated message map functions
   //******************************************************************************

   //{{AFX_MSG(AccountContractDlg)
   virtual BOOL OnInitDialog();    
   afx_msg void OnBtnMore();
   afx_msg void OnBtnReset();
   afx_msg void OnBtnRefresh( );
   afx_msg void OnBtnAdmDates();
   afx_msg void OnBtnTradeModify();
   afx_msg void OnBtnMessage();
   afx_msg void OnBtnHistorical();
   afx_msg void OnBtnMorePendingTrade();

   //}}AFX_MSG
   
   DECLARE_MESSAGE_MAP()

   virtual SEVERITY doInit();
	void OnPostInitDialog();

   //******************************************************************************
   // Method to refresh dialog controls
   // @param   GenericInterface *rpGICaller - pointer to the calling object
   // @param   const I_CHAR *szOriginalCommand - Not used in this case, but 
   //                      can be used to instruct special processing.
   // @returns bool - true.
   //******************************************************************************

   virtual bool doRefresh( GenericInterface * /*rpGICaller*/, 
                           const I_CHAR * /*szOriginalCommand*/ );      

   virtual void DoListItemChanged( UINT listControlID,
                           const DString &strKey,
                           bool bIsNewItem,
                           bool bIsDummyItem );
 
   virtual void ControlUpdated( UINT controlID,	 const DString &strValue );

	bool ListViewControlFilter( long lSubstituteId, const DString *strKey = NULL  );

   
private:
   
   //******************************************************************************
   // All the control hookups are done in this procedure.  This is called by the 
   // OnInitDialog function.
   // @returns void.
   //******************************************************************************
   void addControls();
   void StatusRelatedChanges( const DString str );
   void EnableUpdateingControls( bool bFlag );
   bool hasLossTrade();
   void InitialButtons();
   void registerTabControls ();
    
   DString DisableMsg;
	DString _dstrAggrOrderNum;
	bool isFromMessage;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/AggregatedOrderDlg.h-arc  $
//
//   Rev 1.8   Mar 05 2009 00:56:22   dchatcha
//IN 1395049 - Not returning all the pending trades, introduced 'More' button for pending trade part of Aggregated order screen.
//
//   Rev 1.7   Oct 05 2005 10:37:28   AGUILAAM
//PET1286_FN02_Verification of Aggregated Order Fund Price
//
//   Rev 1.6   Jun 16 2005 20:18:38   popescu
//Incident# 328435 - enable trade modify button in any circumstances for an aggregated order with status price loaded
//
//   Rev 1.5   May 30 2005 22:13:10   popescu
//Incident #301175 - subsequent fix - enable trade modify buttomn when an error on the underlying trades of an aggregated order occurs when user modifies the trade date
//
//   Rev 1.4   May 27 2005 15:48:36   ZHANGCEL
//Incident #297240 -- Added a filter funciton to fix the problem launching AggregatedOrderDlg from Message screen
//
//   Rev 1.3   May 04 2005 16:59:42   hernando
//Incident 303637 - Added parameter, DisableMsg.
//
//   Rev 1.2   Mar 09 2005 11:56:16   hernando
//PET1117 FN66-68 - Added MsgButton to Aggregate Order Dialog.
//
//   Rev 1.1   Dec 03 2004 17:10:22   zhangcel
//PET 1117 FN 08 -- More logic implemented
//
//   Rev 1.0   Nov 26 2004 14:53:16   zhangcel
//Initial revision.
 */
