
#ifndef BASEADDRESSBOOKDLG_H
#define BASEADDRESSBOOKDLG_H
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
// ^FILE   : BaseAddressBookDlg.h
// ^AUTHOR : Yingbao  Li
// ^DATE   : September 3,2002
//
// ^CLASS    : BaseAddressBookDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************
 
#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif
#include <ifastgui\ifasthistoricalinfo.hpp>

#ifndef COMBOBASE_H
   #include <uibase\combobase.h>
#endif

#ifndef _GXALL_H_
   #include <gxall.h>
#endif

class BaseAddressBookDlg : public BaseMainDlg
{
public:
   BaseAddressBookDlg(UINT nID, CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
   ~BaseAddressBookDlg(){
      clearMailmap();
   }
   /**
   implement here any bussiness rules related to the buttons that were added for permission check (add or delete buttons)
   return true if it should be disabled and false if it should be enabled
   DO NOT call EnableWindow() here
   * @param nID - the control's ID
   */
   virtual bool doDisablePermCheckButton(UINT nID);
   virtual bool HideGridRowColumn(DString& dstrTag);

// Dialog Data
   //{{AFX_DATA(AddressBookDlg)
// enum { IDD = IDD_ADDRESSBOOK };
   //}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
protected:
   //{{AFX_VIRTUAL(AddressBookDlg)
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

   //}}AFX_VIRTUAL
// Implementation
protected:
   // Generated message map functions
   //{{AFX_MSG(AddressBookDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnAdmDates();
   afx_msg void OnRbShareHolder();
   afx_msg void OnRbEntity();
   afx_msg void OnRbDefault();
   afx_msg void OnRbOverride();
   afx_msg void OnSelchangeCmbDispCode();
   afx_msg void OnSelchangeCmbEntity();
   afx_msg void OnSelEntityOutput();
   afx_msg void OnSelAddressCode();
   afx_msg void OnSetfocusLvAddresses(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnSetfocusLvMailAssign(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnBtnReset();
   afx_msg void OnBtnDelete();
   afx_msg void OnBtnAdd();	
   afx_msg void OnBtnHistoricalAddress();
   afx_msg void OnBtnHistoricalMailing();
   afx_msg void OnKillfocusEdtPostCode();
   afx_msg void OnBtnEntityMailAdd();
   afx_msg void OnBtnEntityMailDel();
   afx_msg void OnBtnLookup();
   afx_msg void OnChkSkipVal();
   afx_msg void OnSelDefaultEntityAddress();
   virtual BOOL PreTranslateMessage(MSG* pMsg);
   virtual void OnSelRetMail(){};//Implemented in children class, cannot be pure virtual.
   afx_msg void OnBtnEntityLookup();
   afx_msg void OnListItemChanged(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnListItemChanging(NMHDR* pNMHDR, LRESULT* pResult);
   //}}AFX_MSG

   DECLARE_MESSAGE_MAP()

   void OnPostInitDialog();
   virtual SEVERITY doInit();
   //**
    // * Required implementation for the refresh method.  No refresh activity is
    // * performed for this class.
   //  * @param rpGICaller - A reference pointer to the calling object.
    // * @param szOriginalCommand - A string literal representing the original
    // * command issuing the refresh (which may provide a hint on whether this
   //  * object needs to check for refresh).
   //  * @returns true if successful, call getErrors for errors if false
   virtual bool doRefresh(
      GenericInterface * /*rpGICaller*/, 
      const I_CHAR * //*szOriginalCommand
      );

   virtual void InitControl(UINT controlID );
   virtual bool PreOk();
   virtual void PostOk( bool  bOkStatus  );
   virtual void DoListItemChanged( UINT listControlID,
                                   const DString &strKey, 
                                   bool bIsNewItem ,
                                   bool bIsDummyItem
                                   );

   virtual void GetCellProperties( UINT ctrlId, 
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
	  DString& dstrAllowedChar);

   virtual bool GetOverrideItemString(long lSubstituteId, 
                                      const DString &ColumnKey, 
                                      DString &strOut);

   virtual bool GetDataForControl( UINT controlID,
                                   DString &strValueOut, 
                                   bool bFormatted, 
                                   int index ) const;

   virtual bool GetCellValue( UINT ctrlId,
                              const DString &rowKey,
                              const DString &colKey,
                              DString &strOut,
                              bool bFormatted );

   virtual bool SetDataFromControl( UINT controlID,
                                    const DString &strValue,
                                    bool bFormatted,
                                    SEVERITY &sevRtn,
                                    int index=0
                                    );

   virtual void GridControlUpdated( UINT ctrlId,
                                    const DString &rowKey,
                                    const DString &colKey,
                                    const DString &strNewValue,
                                    bool bFormatted,
                                    SEVERITY nSeverity);

   virtual void ControlUpdated( UINT controlID, const DString &strValue );

   void doDisableNonPermButtons();

   /**
   implement here any bussiness rules related to any buttons that were NOT added for permission check
   example: GetDlgItem( IDC_BTN_RESET )->EnableWindow( FALSE );
   Do not enable/disable here buttons that were added for permission check
   this method is called just before CheckPermission returns
   
   void doDisableNonPermButtons();
   */
   virtual bool doDisableControl(UINT nID, bool bIsNew);
   virtual bool GridControlFilter( UINT ctrlId, const DString &rowKey );
   virtual bool SetCellValue( UINT ctrlId,
                              const DString &rowKey,
                              const DString &colKey,
                              const DString &strIn,
                              bool bFormatted,
                              SEVERITY &sevRtn );





protected: // will be override in derived class
   virtual void addControls();
   virtual void LoadShareHolderAddress();
   virtual void LoadEntityAddress();
   virtual void ShowShareHolder(bool bFreshList); 
   virtual void ShowAcctMailingOverride(bool bFreshList); 
   virtual void ShowEntity(); 
   virtual void SetAddressControlsReadOnly(bool bReadOnly);
   bool         disableControlForAddress01();
   virtual const BFFieldId getAddressSubId();

   virtual void tabSelectionChanged ( UINT tabControlID, 
                                       const DString &pageName);

   // only Domestic client would be able to execute 
   virtual void DoRefreshUncliamedRelatedFieldsForAddrCode01( void ) {}
   virtual void DoRefreshRegAddrCode( void );

   DSTTabCtrl *m_pMailInfoTabCtrl;
   DString     m_strCurrentMailingPageName;
   CString     m_cstrAlert;

private:
  
   DString              m_dstrSel_ShareholderList;
   DString              m_dstrSel_EntityList;
   DString              m_dstrAccountNum;
   DString              m_dstrAddrCodeList;
   DString              m_dstrEntityAddrCodeList;
   DString              m_dstrOverrideAddrCodeList;
   CComboBox            m_EntityName;

   CComboBase           m_DisplayCode;
   bool                 m_bShareEntity;  
   DString              m_dstrShrNum;
   DString              m_strNASUFlag;
   DString              m_dstrEntityId;
   DString              m_dstrFromEntity;
   DString              m_dstrEntityType;
   DString              m_dstrSeqNum;
   DString              m_dstrAddrCode;
   DString              m_strSearShareholder;
   DString              strAddtlRegInit;
   bool                 m_bCurrAddressNew;
   bool                 m_bLoadMailing;
   bool                 m_bSalutationFreeFormat;
   bool                 m_bPCLookupEnabled;
   int                  m_iCurOutput;
   DString              _InquiryOnly;
   bool                 m_bOverride; 
   DString              m_dstrFromEntityAlone;
   LRESULT OnListViewItemChanged(WPARAM PreviousSelection, LPARAM ListIdentifier);

   class Mailing
   {
   public:
		Mailing(BFFieldId& lAddrCode,BFFieldId& lHold,BFFieldId& lSerAgent,BFFieldId& lCopies,BFFieldId& lSuppress,
			BFFieldId& lWaive,BFFieldId& lMail,BFFieldId& lFax,BFFieldId& lCD,BFFieldId& lEmail,BFFieldId& lEpost,BFFieldId& lAuth,BFFieldId& lFreq)
		{
			this->lAddrCode = lAddrCode;
			this->lHold = lHold;
			this->lSerAgent = lSerAgent;
			this->lCopies = lCopies;	
			this->lSuppress = lSuppress;
			this->lWaive = lWaive;
			this->lMail = lMail;
			this->lFax = lFax;
			this->lCD = lCD;
			this->lEmail = lEmail;
         this->lEpost = lEpost;
         this->lAuthorize = lAuth;
		 this->lFreq = lFreq;   
		}
		BFFieldId getAddrCode(){ return lAddrCode;}
		BFFieldId getHold(){return lHold;}
		BFFieldId getAgent(){return lSerAgent;}
		BFFieldId getCopies(){return lCopies;}
		BFFieldId getSuppress(){return lSuppress;}
		BFFieldId getMail(){return lMail;}
		BFFieldId getWaive(){return lWaive;}
		BFFieldId getFax(){return lFax;}
		BFFieldId getCD(){return lCD;}
		BFFieldId getEmail(){return lEmail;}
		BFFieldId getEpost(){return lEpost;}
		BFFieldId getAuthorization(){return lAuthorize;}
		BFFieldId getInvstFrequency() {return lFreq;} 

   private:
		BFFieldId lAddrCode;
		BFFieldId lHold;
		BFFieldId lSerAgent;
		BFFieldId lCopies;
		BFFieldId lSuppress;
		BFFieldId lWaive;
		BFFieldId lMail;
		BFFieldId lFax;
		BFFieldId lCD;
		BFFieldId lEmail;
		BFFieldId lEpost;
		BFFieldId lAuthorize;
		BFFieldId lFreq;
      

	};

   typedef std::map< DString, Mailing* > MAIL_MAP;
   typedef MAIL_MAP::iterator           MAIL_MAP_ITER;
   typedef MAIL_MAP::value_type         MAIL_MAP_VALUE_TYPE;
   MAIL_MAP                             _mailmap;

private:
   DString getMailOption(BFFieldId& lFieldId, int iPos,bool bFormated);
   void  setMailOption(BFFieldId& lFieldId,int iPos,const DString& inValue,bool bFormated);
   void  clearMailmap();
   void  setupShareholderMailing();
   void  getComboStringForAddressCode(DString& dstrList);
   void  setLoadMailing(bool bFlag){ m_bLoadMailing  = bFlag; }	
protected:
   bool  IsShareholder() const;	
   void  doSwitchProvinceControl();
   LRESULT OnOpenAlertMessageBox(WPARAM wWordParam, LPARAM lLongParam );
   void postOpenAlertBox();

private:
   void  setShareholoderFlag( bool _bFlag );
   bool  IsOverride() const;	
   void  setOverrideFlag( bool _bFlag );
   void  DisplayAddressLvList();
   void  SetMailingLabel();
   void  setDlgTitle(bool bNameFlag = false,bool bEntityFlag =  false );
   void  FillMailAddressList();
   void  FillAcctMailOverrideList();
   void  FillEntityCombo(); 
   void  FillDisplayCodeComboBox();
   void  findAddrCode();
   bool  MailingPositionByAccount(const DString& AccountNumber);
   void  ClearMailingList();
   void  InitCombo(UINT controlID,const BFContainerId& idContainer,const BFFieldId& fieldid,bool bCode = true);
   //bool	isDemoMode();
   bool  HideMailOption(DString& dstrTag );
   LRESULT OpenBrokerAddressDlg( WPARAM, LPARAM );
   bool  isAccountOwner();

   LRESULT OpenAddressSearchDlg( WPARAM, LPARAM );
   void HideReturnMail();
   void SelAddrOfRetMailForNomineeIntermAcct( void );

};

#endif


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/BaseAddressBookDlg.h-arc  $
//
//   Rev 1.30   Jan 19 2012 12:14:04   wp040132
//Minerva ISF Code changes..
//
//   Rev 1.29   Jan 25 2010 22:55:42   dchatcha
//IN# 1983880 - Rel 97 Static Data - Status of Nom (01 Reg address) is set to Unverified.
//
//   Rev 1.28   Jul 24 2009 12:50:58   dchatcha
//PET 157825 - FN 13 - Dilution Allocation Enhancements, Sorting combo in grid.
//
//   Rev 1.27   17 Jul 2009 14:08:06   walkerro
//PET156681 FN03 - Postal Code Lookup on address screen
//
//   Rev 1.26   Jan 06 2009 05:34:40   daechach
//IN 1461977 - Return mail on caution box does not link to the return mail screen for nominee.
//
//   Rev 1.25   Nov 19 2008 17:24:30   wongsakw
//IN1483714 - REL 89 - Unclaimed Property Retun Mail Flag issues and Stage -- Sync Up
//
//   Rev 1.24   Nov 06 2008 02:46:54   daechach
//PET5517 FN71 Unclaimed Property Phase 2
//
//   Rev 1.23   Sep 29 2008 07:57:42   wongsakw
//PET5517 FN71 Unclaimed Property - Return Mail
//
//   Rev 1.22   Sep 22 2008 08:46:54   wongsakw
//PET5517 FN71 Unclaimed Property
//
//   Rev 1.21   Sep 21 2005 16:51:46   yingbaol
//PET1277,FN09 Investment Fund Continious Disclosure
//
//   Rev 1.20   Mar 11 2005 14:59:22   porteanm
//PET 1171 FN01 - EUSD Entity Address Update - work in progress.
//
//   Rev 1.19   Mar 04 2005 16:16:04   porteanm
//PET 1171 FN01 - EUSD Entity Address Update support - work in progress.
//
//   Rev 1.18   Mar 03 2005 12:48:12   porteanm
//PET 1171 FN01 - EUSD Entity Address Update support - work in progress.
//
//   Rev 1.17   Feb 25 2005 13:17:48   porteanm
//PET 1171 FN01 - EUSD Entity Address Search.
//
//   Rev 1.16   Dec 02 2004 11:38:56   yingbaol
//PET1137,FN01: add Epost functionalities
//
//   Rev 1.15   Mar 28 2004 16:27:48   HERNANDO
//PTS10028484 - Renamed existing OnBtnHistorical fn., and added additional historical function.
//
//   Rev 1.14   Mar 02 2004 16:22:10   HERNANDO
//PET965 FN11 - Added Historical functionality.
//
//   Rev 1.13   Oct 14 2003 13:19:30   HERNANDO
//PET893 FN08 - Salutation enhancement.
//
//   Rev 1.12   Jun 06 2003 14:52:28   popescu
//Fixed PTS 10018010
//
//   Rev 1.11   May 16 2003 18:18:16   YINGBAOL
//add method isAccountOwner and corresponding logic for EntityAddressMainling
//
//   Rev 1.10   Apr 03 2003 09:40:02   YINGBAOL
//Broker Address Enhancement
//
//   Rev 1.9   Apr 01 2003 16:54:50   FENGYONG
//Add AcctMailingOverride panel
//
//   Rev 1.8   Mar 21 2003 18:33:28   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.7   Mar 03 2003 12:01:16   KOVACSRO
//Added _InquiryOnly.
//
//   Rev 1.6   Feb 06 2003 10:20:52   linmay
//added getAddressSubId() 
//
//   Rev 1.5   Nov 06 2002 10:32:54   YINGBAOL
//sync. up release 49
//
//   Rev 1.4   Oct 10 2002 15:05:50   YINGBAOL
//add OnSelDefaultEntityAddress
//
//   Rev 1.3   Oct 08 2002 11:52:36   YINGBAOL
//add out put control for entity mailing
//
//   Rev 1.2   Sep 23 2002 15:25:30   YINGBAOL
//dynamic show mailing according to view 149
//
//   Rev 1.1   Sep 19 2002 14:05:40   YINGBAOL
//add grid control filter
 * 



*/