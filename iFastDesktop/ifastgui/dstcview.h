
#ifndef DSTCVIEW_H
#define DSTCVIEW_H

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

#include <bfproc\GenericInterface.hpp>
#include "mfdstcddeserver.h"
#include <uibase/IFDSStatusBar.h>
#include <boost\scoped_ptr.hpp>
#include <boost\shared_ptr.hpp>
#include <json\json.h>

// Forward declares
class BFAwdData;
class BFAwdKey;
class DSTCDoc;
class GenericInterface;
class LEdit;
class WorkEventAgent;
class WorkEvent;

/*
class CIFDSStatusBar : public CStatusBar
{
public:
   CIFDSStatusBar();
};
*/

class CDSTCView : public CFormView , public GenericInterface::ProcessObserver
{
friend class MFDSTCDDETopic;
public:
   CDSTCView();
   virtual ~CDSTCView();
   DSTCDoc *GetDocument();
   void UpdateLabels();
   void setCallerName( const I_CHAR* name );
   void setCallerRelationship( const I_CHAR* relationship );
   void setCallerPhoneNum( const I_CHAR* phoneNum );
   void setCallerExt( const I_CHAR* ext );
   void setCallerTimeOfCall( const I_CHAR* timeOfCall );
   void enableDetailsButton( bool enable );
   void enableRemarksButton( bool enable );
   void fillAllCheckingSecurity();
   void enableTradeButton( bool enable );
   bool clearWorksession(bool bDiscard = true, bool bSkipAWD = true, bool SearchBTN = false );
   void setCurrWorkSessionPGI (GenericInterface *_pGIWorkSession)
   {
      m_currpGIWorkSession = _pGIWorkSession;
   };
   bool isWorkSessionValid (GenericInterface* pWS);
   bool displayActiveBatches();
   void NotifyStatusBarOnRegistryChange(void);

#ifdef _DEBUG
   virtual void AssertValid() const;
   virtual void Dump(CDumpContext& dc) const;
#endif

   static CDSTCView* GetView();
   const GenericInterface* getUserSession() const { return m_rpGIUserSession; }

   void PostWorkEventMessage(boost::shared_ptr<WorkEvent> const & event);
   void UpdateWorkEvent(void);
   void SetWorkComment(const DString& dstrComment);
   void SetWorkData(const DString& cmdName, const BFData& data);
   DString getWorkEventField(DString fieldId);

   bool HasWorkEvent(void) {
      return (m_workEvent);
   }

   bool isWorkAgentRunning(void) {
      return (m_workEventAgent);
   }

   virtual void notifyOk(const GenericInterface *rpGICaller,
                         AbstractProcess *process);

   void createWork(const DString& dstrEventName);

   Json::Value lookupWork(const DString& accountNum, const DString& awdContentId);
   Json::Value lookupWork(const DString& accountNum);

   Json::Value lookupWork(const Json::Value& params);

   //{{AFX_DATA(CDSTCView)
   enum
   {
      IDD = IDD_SEARCH_FORM
   };
   CStatic  m_lblAreaCode;
   CEdit m_edtAreaCode;
   CButton  m_btnRemarks;
   CButton  m_btnHarness;
   CButton  m_btnDetails;
   CButton  m_btnFinancial;
   CButton  m_btnFund;
   CButton  m_btnFYI;
   CButton  m_btnEnd;
   CButton  m_btnGetWork;
   CButton  m_btnIdCaller;
   CButton  m_btnSearch;
   CStatic  m_txtName;
   CStatic  m_txtRelation;
   CStatic  m_txtPhone;
   CStatic  m_txtPhone2;
   CStatic  m_txtTime;
   CComboBox   m_cmbUsing;
   CComboBox   m_cmbSearch;
   CEdit m_edtSearch3;
   CEdit m_edtSearch2;
   CEdit m_edtSearch1;
   CStatic  m_lblSearch3;
   CStatic  m_lblSearch2;
   CStatic  m_lblSearch1;
   CButton  m_btnNew;
   CStatic  m_txtExt;
   CButton  m_btnAccount;
   CButton  m_btnSettlement;
   CButton  m_btnGlobalSearch;
   //}}AFX_DATA

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CDSTCView)
public:
   virtual void OnInitialUpdate();
   virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

protected: // create from serialization only
   DECLARE_DYNCREATE(CDSTCView)

private:
   bool CanPerformSearch();
   void destroyBusInfo();
   bool OKToSetCallerInfo();
   DString GetAWDPortalTopic();
   DString GetCallCentreTopic();


   GenericInterfaceContainer *m_pGIC;
   GenericInterface *m_rpGIUserSession;
   GenericInterface *m_rpGIWorkSession;
   GenericInterface *m_rpGIFiller; //Pointer to the Business Process that fills the search criterias
   GenericInterface *m_currpGIWorkSession;

   int                 m_iUsingSel;        // Which Using item they last selected
   bool                m_bFormsContinue;
   bool                m_bFundOk;          // Is it ok to call Fund Info screen?
   bool                m_bClose;           // Are we closing?
   bool                m_bNotReady;        // Are we through initializing yet?
   bool                m_bGetWork;         // GetWork button enabled or disabled
   bool                m_bAWD;             // TRUE - using AWD
   bool                m_bIdCaller;        // Have we called the IDCaller yet?
   bool                m_bIdCallerEnd;     // Pop up ID caller on the End if we have not yet called it
   bool                m_bIdCallerSearch;  // Pop up ID caller when they hit search
   bool                m_bDiscard;
   bool                m_bCallStart;
   DString             m_strFileDir;       // Location of the files
   DString             m_strSysloadDir;    // Location of the Sysload files
   CString             m_csSearchValue;    // Search value
   CString             m_csUsingValue;     // Using value
   CString             m_csLink;           // Link by criteria
   CString             m_csSystem;         // Chosen System
   CString             m_csMgmt;           // Chosen Management Co
   DString             m_strOPID;          // Operator ID
//   bool                m_bOneSearchUsing;   // True if only one edit field is used in the search criteria
   int                 m_iNumFieldsUsedOnSearch; //we use 1,2 or 3 fields for search
   bool                m_bAreaCodeRequired;
   bool                m_bForceAwdUpdate;
   bool                m_bSkipAWD;
   unsigned char       m_ucSession;
   DWORD               m_dwHtmlHelpCookie;
   IFDSStatusBar       m_statusBar;

   //typedef std::vector<LEdit *>                          m_LEdit;
   LEdit*          m_LEdit;


   void clearScreen();                             // Clear the call
   bool SetUsingList( const I_CHAR * searchCriteria, const I_CHAR * selection);     // Sets the Using Combo box
   virtual E_COMMANDRETURN DoProcess()
   {  // Don't use it yet
      return(CMD_OK);
   }
   BOOL CDSTCView::OnCmdMsg( UINT nID, int nCode, void* pExtra,
                             AFX_CMDHANDLERINFO* pHandlerInfo );
   LRESULT displayIdData( WPARAM, LPARAM );        // Display ID Caller data
   bool enableFYI( void );                         // Enable or Disable the FYI screen
   LRESULT expandCase( WPARAM, LPARAM );           // Tell the AwdSession to expand the case
   LRESULT functionKeyPressed( WPARAM, LPARAM );   // Another dialog pressed a Function Key
   LRESULT launchAccountDetails( WPARAM, LPARAM ); // Launches account details after a new shareholder setup
   LRESULT launchHoldingComp( WPARAM, LPARAM );    // re launches GHolding company
   LRESULT OnEndSession( WPARAM, LPARAM );
   LRESULT launchTrading(WPARAM,LPARAM);
   LRESULT newSearch( WPARAM, LPARAM );
   LRESULT OnEndCurrSession( WPARAM, LPARAM );     // Confirm one worksession

   bool   OnBtnEndCall();

   //NET... added
   bool   OnBtnEndCall1();

   void ReloadResource(const DString &dstrCompId);

   void getRegistry( void );                       // Gets the Registry Key
   bool getSignOn(void );                          // Sign on
   BOOL getStateZip( void );                       // Query the State or Zip
   void getWorkDataForAccountSearch( const BFAwdData * );  // Get work from AWD do Account Search
   void moveDialog( void );                        // Put us where we need to be
   void profileInitialization( void );             // Initialization based on profile
   LRESULT ready( WPARAM, LPARAM );                // we're through initializing
   void resetRoadData( void );                     // Reset the whiteboard
   void startCall( bool createCase = true );       // Action taken, start the call
   bool Search( void );
   void storeAcct( void );                         // Store the ACCT or SSN
   void stripLeadingChar( CString &, char * );     // Removes the leading characters from the CString
   void validateTime();                            // Validate the time
   void sendExitMsg();                      // DAWC -- notify user application is exiting
   void showSearchEditFields(int numFields);
   void hide2EditFields();                         // hides edit 1 & edit 2 if only one search criteria
   void hide1EditField();                          // hides edit 3 if 2 search criteria
   bool DiffMgmCo ( DString );          // Checks to see if the new management company matches current
   bool SetMgmCo ( DString );            // Sets to new management company.
   const BFAwdKey   *pAwdKey;
   HACCEL m_hAccel;
   void checkForTelefonNo(const DString &searchCriteriaKey);
   void doNASU();
   void LaunchHelp(const DString &);
   void F4pressed();   
   void OpenKYC (const DString &accountNum, const DString &dstrBusArea, const DString &dstrSmartForm);

   //{{AFX_MSG(CDSTCView)
   afx_msg void OnBtnFinancial();
   afx_msg void OnBtnRemarks();
   afx_msg void OnBtnDetails();
   afx_msg void OnBtnFund();
   afx_msg void OnBtnFYI();
   afx_msg void OnBtnGetwork();
   afx_msg void OnBtnIdcaller();
   afx_msg void OnBtnSearch();
   afx_msg void OnBtnGlobalSearch ();
   afx_msg void OnBtnClose();
   afx_msg void OnSetfocusLstSearch();
   afx_msg void OnBtnEndCallV();
   afx_msg void OnDestroy();
   afx_msg void OnSelchangeCmbSearch();
   afx_msg void OnChange();
   afx_msg void OnSelchangeCmbUsing();
   afx_msg void OnSelChangeSearch1();
   afx_msg void OnBtnNew();
   afx_msg void OnDSTC();
   afx_msg void OnBtnHarness();
   afx_msg void OnAWDComment();
   afx_msg void OnUpdateAWDComment( CCmdUI* pCmdUI );
   afx_msg void OnForms();
   afx_msg void OnEncorr();
   afx_msg void OnDefaultSetting();
   afx_msg void OnAwdHistory();
   afx_msg void OnTaxrates();
   afx_msg void OnUpdateFinancial(CCmdUI* pCmdUI);
   afx_msg void OnUpdateSettlement(CCmdUI* pCmdUI);
   afx_msg void OnChangeEdtAreaCode();
   afx_msg void OnHelp1();
   afx_msg void OnHelp2();
   afx_msg void OnHelp3();
   afx_msg void OnAMSReports();
   afx_msg void OnUpdateAmsReports(CCmdUI* pCmdUI);
   afx_msg void OnHistoricalInfoSrch();
   afx_msg void OnUpdateHistoricalInfoSrch(CCmdUI* pCmdUI);
   afx_msg void OnProtectedfundsetup();
   afx_msg void OnUpdateProtectedfundsetup(CCmdUI* pCmdUI);
   afx_msg void OnMktIndexMaster();
   afx_msg void OnUpdateMktIndexMaster(CCmdUI* pCmdUI);
   afx_msg void OnMktIndexValues();
   afx_msg void OnUpdateMktIndexValues(CCmdUI* pCmdUI);
   afx_msg void OnMsgInquirySearch();
   afx_msg void OnUpdateMsgInquirySearch(CCmdUI* pCmdUI);
   afx_msg void OnFileInquirySearch();
   afx_msg void OnUpdateFileInquirySearch(CCmdUI* pCmdUI);
   afx_msg void OnCancellationInstr();
   afx_msg void OnUpdateCancellationInstr(CCmdUI* pCmdUI);
   afx_msg void OnReportStatus();
   afx_msg void OnSystemLevelFee();
   afx_msg void OnUpdateSystemLevelFee(CCmdUI* pCmdUI);
   afx_msg void OnTrailerFeeSetup();
   afx_msg void OnUpdateTrailerFeeSetup(CCmdUI* pCmdUI);
   afx_msg void OnSmartForms();
   afx_msg void OnUpdateSmartForms(CCmdUI* pCmdUI);
   afx_msg void OnTradeSearch();
   afx_msg void OnUpdateTradeSearch(CCmdUI* pCmdUI);
   afx_msg void OnBtnSettlement();
   afx_msg void OnBrokerAMS();
   afx_msg void OnUpdateBrokerAMS(CCmdUI* pCmdUI);
   afx_msg void OnGlobalAMS();
   afx_msg void OnUpdateGlobalAMS(CCmdUI* pCmdUI);
   afx_msg void OnManualDividend();
   afx_msg void OnUpdateManualDividend(CCmdUI* pCmdUI);
   afx_msg void OnSettlementLocation();
   afx_msg void OnUpdateSettlementLocation(CCmdUI* pCmdUI);
   afx_msg void OnPaymentInstructions();
   afx_msg void OnUpdatePaymentInstructions(CCmdUI* pCmdUI);
   afx_msg void OnManagementFee();                               // PMI
   afx_msg void OnUpdateManagementFee(CCmdUI* pCmdUI);           // PMI
   afx_msg void OnAccountBalanceOverride();                      // PMI
   afx_msg void OnUpdateAccountBalanceOverride(CCmdUI* pCmdUI);  // PMI
   afx_msg void OnDilutionCalculator();                          // PMI
   afx_msg void OnUpdateDilutionCalculator(CCmdUI* pCmdUI);      // PMI
   afx_msg void OnPayToEntity();
   afx_msg void OnUpdatePayToEntity(CCmdUI* pCmdUI);
   afx_msg void OnBrokerBanking();
   afx_msg void OnUpdateBrokerBanking(CCmdUI* pCmdUI);
   afx_msg void OnFinancialInstitutions();
   afx_msg void OnUpdateFinancialInstitutions(CCmdUI* pCmdUI);
   afx_msg void OnDailyTransactionsFees();
   afx_msg void OnUpdateDailyTransactionsFees(CCmdUI* pCmdUI);
   afx_msg void OnFeeModel();
   afx_msg void OnUpdateFeeModel(CCmdUI* pCmdUI);
   afx_msg void OnFundSponsorFeeModel();
   afx_msg void OnUpdateFundSponsorFeeModel(CCmdUI* pCmdUI);
   afx_msg void OnFundBroker();
   afx_msg void OnAggregateOrder();
   afx_msg void OnUpdateFundBroker(CCmdUI* pCmdUI);
   afx_msg void OnUpdateAggregateOrder(CCmdUI* pCmdUI);
   afx_msg void OnMgmtCoPaymentInstr();
   afx_msg void OnUpdateMgmtCoPaymentInstr(CCmdUI* pCmdUI);
   afx_msg void OnMgmtCoPayToEntity();
   afx_msg void OnUpdateMgmtCoPayToEntity(CCmdUI* pCmdUI);
   afx_msg void OnPaymentSearch();
   afx_msg void OnUpdatePaymentSearch(CCmdUI* pCmdUI);
   afx_msg void OnPaymentBatch();
   afx_msg void OnUpdatePaymentBatch(CCmdUI* pCmdUI);
   afx_msg void OnFundLimitation();
   afx_msg void OnUpdateFundLimitation(CCmdUI* pCmdUI);
   afx_msg void OnRegulatoryStandards();
   afx_msg void OnUpdateRegulatoryStandards(CCmdUI* pCmdUI);
   afx_msg void OnUpdateRegulatoryDocuments(CCmdUI* pCmdUI);
   afx_msg void OnRegulatoryDocuments ();
   afx_msg void OnUpdateFundMaster(CCmdUI* pCmdUI);
   afx_msg void OnFundMaster ();
   afx_msg void OnReleaseFrozenAccount();
   afx_msg void OnUpdateReleaseFrozenAccount(CCmdUI* pCmdUI);
   afx_msg void OnUpdateFundClassCopy(CCmdUI* pCmdUI);
   afx_msg void OnFundClassCopy ();
   afx_msg void OnUpdateFundClassMaintenance(CCmdUI* pCmdUI);
   afx_msg void OnFundClassMaintenance ();
   afx_msg void OnUpdateInterfaceFile(CCmdUI* pCmdUI);
   afx_msg void OnInterfaceFile ();
   afx_msg void OnPortfolioSetup ();
   afx_msg void OnUpdatePortfolioSetup(CCmdUI* pCmdUI);
   afx_msg void OnCommisionReduction();
   afx_msg void OnUpdateCommisionReduction(CCmdUI* pCmdUI);
   afx_msg void OnInterestRateConfiguration();
   afx_msg void OnUpdateInterestRateConfiguration(CCmdUI* pCmdUI);
   afx_msg void OnInterestRateMaintenance();
   afx_msg void OnUpdateInterestRateMaintenance(CCmdUI* pCmdUI);
   afx_msg void OnLanguageEnglish();
   afx_msg void OnLanguageFrench();
   afx_msg void OnUpdateLanguageEnglish(CCmdUI *pCmdUI);
   afx_msg void OnUpdateLanguageFrench(CCmdUI *pCmdUI);
   afx_msg void OnSegMaintenanceSegAttributes ();
   afx_msg void OnUpdateSegMaintenanceSegAttributes(CCmdUI* pCmdUI);
   afx_msg void OnSegMaintenanceGuaranteeRules ();
   afx_msg void OnUpdateMaintenanceGuaranteeRules (CCmdUI* pCmdUI);
   afx_msg void OnRESPDiplomaMenuItem();
   afx_msg void OnUpdateRESPDiplomaMenuItem(CCmdUI* pCmdUI);
   afx_msg void OnEventDateGen(); 
   afx_msg void OnUpdateEventDateGen(CCmdUI* pCmdUI);  
   afx_msg void OnEventSchduleMain();
   afx_msg void OnUpdateEventSchduleMain(CCmdUI* pCmdUI);
   afx_msg void OnTradeSchduleMain();
   afx_msg void OnUpdateTradeSchduleMain(CCmdUI* pCmdUI);
   afx_msg void OnAccountForeignTaxReview();
   afx_msg void OnUpdateAccountForeignTaxReview(CCmdUI* pCmdUI);
   afx_msg void OnRemitUnclmAcct(); 
   afx_msg void OnUpdateRemitUnclmAcct(CCmdUI* pCmdUI);
   afx_msg void OnAccountFeeModelAssociation();
   afx_msg void OnUpdateAccountFeeModelAssociation(CCmdUI* pCmdUI);     
   afx_msg void OnHoldingCompany();
   afx_msg void OnUpdateHoldingCompany(CCmdUI* pCmdUI);

   afx_msg void OnMFAndMFRInvoiceInstruction();
   afx_msg void OnUpdateMFAndMFRInvoiceInstruction(CCmdUI* pCmdUI);
   afx_msg void OnMFAndMFRReportGroup();
   afx_msg void OnUpdateMFAndMFRReportGroup(CCmdUI* pCmdUI);
   afx_msg void OnMFAndMFRAdditionalAssets();
   afx_msg void OnUpdateMFAndMFRAdditionalAssets(CCmdUI* pCmdUI);
   afx_msg void OnForeignFinancialInstitutionMaintenance();
   afx_msg void OnUpdateForeignFinancialInstitutionMaintenance(CCmdUI* pCmdUI);
   afx_msg void OnSystemIdentificationMaintenance();
   afx_msg void OnUpdateSystemIdentificationMaintenance(CCmdUI* pCmdUI);
   afx_msg void OnFundGroupRegulatory();
   afx_msg void OnUpdateFundGroupRegulatory(CCmdUI* pCmdUI);
   afx_msg void OnBrokerRegulatory();
   afx_msg void OnUpdateBrokerRegulatory(CCmdUI* pCmdUI);
   afx_msg void OnIntermediaryRegulatory();
   afx_msg void OnUpdateIntermediaryRegulatory(CCmdUI* pCmdUI);
   afx_msg void OnTrailerFeesInquiry();
   afx_msg void OnUpdateTrailerFeesInquiry(CCmdUI* pCmdUI);
   afx_msg void OnAccountGroup();
   afx_msg void OnUpdateAccountGroup(CCmdUI* pCmdUI);
   afx_msg void OnPrivateWealthInformation();
   afx_msg void OnUpdatePrivateWealthInformation(CCmdUI* pCmdUI);
   afx_msg void OnTradeVerification();
   afx_msg void OnUpdateTradeVerification(CCmdUI* pCmdUI);
   afx_msg void OnFATCAFilingDetail();
   afx_msg void OnUpdateFATCAFilingDetail(CCmdUI* pCmdUI);
   afx_msg void OnAccountHouseholdInfo();
   afx_msg void OnUpdateAccountHouseholdInfo(CCmdUI* pCmdUI);
   afx_msg void OnFundRulesMaintenance();
   afx_msg void OnUpdateFundRulesMaintenance(CCmdUI* pCmdUI);
   afx_msg void OnTransferAccounts();
   afx_msg void OnUpdateTransferAccounts(CCmdUI* pCmdUI);
   afx_msg void OnFundGroup();
   afx_msg void OnUpdateFundGroup(CCmdUI* pCmdUI);
   afx_msg void OnFundBrokerLinkage();
   afx_msg void OnUpdateFundBrokerLinkage(CCmdUI* pCmdUI);
   afx_msg void OnRegPlanTransfer();
   afx_msg void OnUpdateRegPlanTransfer(CCmdUI* pCmdUI);
   afx_msg void OnRegulatoryAgreement();
   afx_msg void OnUpdateRegulatoryAgreement(CCmdUI* pCmdUI);
   afx_msg void OnBrokerCutOff();
   afx_msg void OnUpdateBrokerCutOff(CCmdUI* pCmdUI);
   afx_msg void OnExternalTAFundLinkage();
   afx_msg void OnUpdateExternalTAFundLinkage(CCmdUI* pCmdUI);
   afx_msg void OnRegAcctExtr();
   afx_msg void OnUpdateRegAcctExtr(CCmdUI* pCmdUI);
   afx_msg void OnRegAcctInfoRev();
   afx_msg void OnUpdateRegAcctInfoRev(CCmdUI* pCmdUI);
   afx_msg void OnWithholdingTaxRatesMaintenance();
   afx_msg void OnUpdateWithholdingTaxRatesMaintenance(CCmdUI* pCmdUI);
   afx_msg void OnFundDistributionSplitMaintenance();
   afx_msg void OnUpdateFundDistributionSplitMaintenance(CCmdUI* pCmdUI);
   afx_msg void OnRDSPInterfaceTransactions();
   afx_msg void OnUpdateRDSPInterfaceTransactions(CCmdUI* pCmdUI);
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()

private:
   void openFundClassListDlg (int control);
   void openFundGroupDlg (int control);
   void onWorkType (const DString &workType);
   void onSmartForms (const DString &dstrCRDA);
   bool enableSystemMenuItem(I_CHAR * const dstrUaf);
   void onSystemMenuItem ( UINT uiMsgId,
                           const I_CHAR* processId,
                           bool bModal = false,
                           const DString &dstrParamsIDI = NULL_STRING);

   afx_msg LRESULT onWorkEvent(WPARAM wParam, LPARAM lParam);
   DString GetMgmCoName(DString companyID);


   MFDSTCDDEServer* m_mfdstcDDEServer;

   boost::scoped_ptr<WorkEvent> m_workEvent;
   boost::scoped_ptr<WorkEventAgent> m_workEventAgent;

   std::pair<Json::Value, Json::Value> m_WorkOutData;

   NMHDR m_notifyHeader;

   bool m_bManualSmartForm;
   bool m_bDskNasu;
};


#ifndef _DEBUG  // debug version in DSTCView.cpp
inline DSTCDoc *CDSTCView::GetDocument()
{ return( DSTCDoc * )m_pDocument;}
#endif

#endif // DSTCVIEW_H

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/dstcview.h-arc  $
 * 
 *    Rev 1.106   Jul 16 2012 12:16:22   dchatcha
 * P0179630 FN01 FATCA Project - Foriegn Tax Review.
 * 
 *    Rev 1.105   Feb 15 2012 12:23:52   if991250
 * RESP Diploma Desktop Web
 * 
 *    Rev 1.104   Jan 24 2012 00:16:32   panatcha
 * P0188394 - iFast Performance Fee
 * 
 *    Rev 1.103   Oct 21 2011 13:28:28   popescu
 * SEG - Configuration  S1 (SEG and Desktop skeleton) - synch-up
 * 
 *    Rev 1.102   Oct 11 2011 11:45:10   dchatcha
 * P0186484 FN01 - INA - Desktop Seg and Desktop French Enhancements, add language DLL switching support for domestic client.
 * 
 *    Rev 1.101   Sep 19 2011 19:43:38   dchatcha
 * P0186477 FN01 - GIA Enhancements, remove GIA Attributes as this one will be part of fund setup.
 * 
 *    Rev 1.100   Aug 04 2011 18:26:08   dchatcha
 * P0186477 FN01 - GIA Enhancements
 * 
 *    Rev 1.99   Jul 28 2011 11:38:32   jankovii
 * PET186484 - Global Search
 * 
 *    Rev 1.98   May 20 2011 09:10:04   jankovii
 * IN 2532301 - NASU Issue in MFS and Domestic Clients
 * 
 *    Rev 1.97   May 05 2011 15:52:20   jankovii
 * IN 2511918 - Desktop refresh not working properly with SF
 * 
 *    Rev 1.96   Mar 17 2011 13:15:36   jankovii
 * PET 179563 FN01 - Smart Forms
 * 
 *    Rev 1.95   Nov 22 2010 13:43:18   jankovii
 * PET175778 FN01 - Upstreaming Phase 2
 * 
 *    Rev 1.94   Sep 30 2010 10:11:16   jankovii
 * PET168727 FN22 - Trailer Fee Setup
 * 
 *    Rev 1.93   Jul 05 2010 14:07:52   jankovii
 * PET165541_FN09_QESI Phase 2
 * 
 *    Rev 1.92   Jan 14 2010 04:48:06   dchatcha
 * P0160872 - Fund Setup Phase II - Removed Fund Detail from main menu as replaced by Fund Class Maintenance.
 * 
 *    Rev 1.91   Dec 22 2009 06:29:40   dchatcha
 * IN# 1952546 - Indicator to show that the database DSK is connected to is scrambled.
 * 
 *    Rev 1.90   Dec 02 2009 09:54:08   popescu
 * P0160872 - Fund Setup Phase II
 * 
 *    Rev 1.89   Sep 21 2009 15:57:30   popescu
 * Added support for launching the Trading screen if mapping for pruchase and redeem work types exists in the AWD Ini file
 * 
 *    Rev 1.88   May 14 2009 11:33:44   dchatcha
 * PET160872 FN01 Fund Setup-Class Level.
 * 
 *    Rev 1.87   Feb 20 2009 14:57:32   purdyech
 * ZTS Revision 6
 * 
 *    Rev 1.86   Feb 06 2009 14:55:00   purdyech
 * Interim CheckIn for ZTS Support (Chris is goin' on vacation!)
 * 
 *    Rev 1.85   Nov 03 2008 05:28:12   yaviratp
 * PET5517 FN71B2 Unclaimed Property - new browser screen (Release Frozen Account).
 * 
 *    Rev 1.84   Aug 11 2008 15:11:16   jankovii
 * PET0057430 FN01 - Performance Fee.
 * 
 *    Rev 1.83   18 Jul 2008 13:55:12   popescu
 * Incident 1190617 - pop a progress control dialog to monitor the static data loading when the management company is swithced
 * 
 *    Rev 1.82   Jul 11 2008 16:22:44   jankovii
 * PET59888 FN01 - AML Enhancement.
 * 
 *    Rev 1.81   26 Sep 2007 16:58:52   kovacsro
 * IN#1015356 - added displayActivBatches
 * 
 *    Rev 1.80   Aug 10 2007 11:47:04   ivespaul
 * PET2360 - Web Integration.
 *
 *    Rev 1.79   Feb 14 2007 15:11:38   jankovii
 * PET 2302 FN01 - Payment Release.
 *
 *    Rev 1.78   Dec 18 2006 17:51:26   popescu
 * Added support for dde server
 *
 *    Rev 1.77   Nov 21 2006 16:35:36   jankovii
 * PET 2287 FN01 - Grupo Mundial Trade Aggregation.
 *
 *    Rev 1.76   Oct 19 2006 09:37:42   fengyong
 * Temp check in for PET 2185 - Fund limitation
 *
 *    Rev 1.75   Aug 23 2006 14:53:30   fengyong
 * temp check in for PET 2192
 *
 *    Rev 1.74   Jul 27 2006 18:03:10   ZHANGCEL
 * PET2192 FN11 - Commission Payments to MgmtCo related changes
 *
 *    Rev 1.73   Nov 11 2005 18:33:14   porteanm
 * PET1228_FN01-EU Savings Directive Phase two.
 *
 *    Rev 1.72   Nov 04 2005 11:07:02   ZHANGCEL
 * PET 1286  FN01 -- Add Cancellation Instruction search related issue
 *
 *    Rev 1.71   Oct 27 2005 10:38:02   jankovii
 * PET1228_FN01-EU Savings Directive Phase
 *
 *    Rev 1.70   Sep 22 2005 18:55:08   fengyong
 * Incident 403519 - Add menu Default Setting
 *
 *    Rev 1.69   Feb 24 2005 19:21:30   popescu
 * Incident # 243353, added timer used to monitor if fund master/detail list are fully loade. Status bar message is displayed while data is loading, synch-up from release 59.04
 *
 *    Rev 1.68   Feb 08 2005 11:31:14   hernando
 * PET1117 FN66-68 - Added functions to support Message Inquiry and File Inquiry menu items.
 *
 *    Rev 1.67   Jan 17 2005 18:27:46   hernando
 * PTS10037736 - Removed reference to AWDEVENT.
 *
 *    Rev 1.66   Nov 26 2004 14:48:52   zhangcel
 * PET1117/FN8 -- Aggregated Order related changes
 *
 *    Rev 1.65   Nov 14 2004 15:00:40   purdyech
 * PET910 - .NET Conversion
 *
 *    Rev 1.64   Oct 01 2004 12:25:58   FENGYONG
 * Add FundBroker to Menu
 *
 *    Rev 1.63   Aug 10 2004 11:28:10   FENGYONG
 * PET 1117 FN5 - Client Condition Fee
 *
 *    Rev 1.62   Jun 17 2004 17:45:18   FENGYONG
 * PTS10031349, fix problems caused by  "onSystemMenuItem" function.
 *
 *    Rev 1.61   May 19 2004 13:16:06   YINGBAOL
 * PTS10029450: change logic of display discard error message when there is an AWD object has not been updated
 *
 *    Rev 1.60   May 11 2004 14:24:48   FENGYONG
 * PET1046 FN1 - transfer-switch -Rel57
 *
 *    Rev 1.59   May 05 2004 14:05:30   VADEANUM
 * PET 1017 - AWD Comments - work in progress.
 *
 *    Rev 1.58   Mar 26 2004 13:30:30   YINGBAOL
 * sync. Version 1.55.1.1
 *
 *    Rev 1.57   Feb 23 2004 14:25:50   YINGBAOL
 * PTS10027246:sync.to trunk.
 *
 *    Rev 1.56   Jan 28 2004 21:35:26   popescu
 * PET 859, FN 23, modified resources (dialogs and menu item) and coded for the features search dialog
 *
 *    Rev 1.55   Dec 31 2003 14:43:14   HERNANDO
 * PET910 - AWD Voice Integration enhancement.
 *
 *    Rev 1.54   Nov 20 2003 17:31:54   HERNANDO
 * PET859 FN1 - Added OnSettlementLocation and OnUpdateSettlementLocation.
 *
 *    Rev 1.53   Oct 04 2003 16:02:12   popescu
 * CIBC PET 809, FN 13;
 * also cleaned-up BankSearch and BankList objects,
 * replaced with FinancialInstitutionList
 *
 *    Rev 1.52   Sep 23 2003 18:44:38   popescu
 * Added the IDD_FINANCIAL_INSTITUTIONS dialog in the resources, as well as the new menu item for invoking it
 *
 *    Rev 1.51   Jul 09 2003 21:57:42   popescu
 * Payment Instructiuons work, business rules implementation SSB_PET_821_FN17
 *
 *    Rev 1.50   Jun 27 2003 18:11:30   popescu
 * Changed name for the BrokerFeaturesSearch handler
 *
 *    Rev 1.49   Jun 27 2003 17:53:44   popescu
 * Added menu handlers for the Payment Instructions feature
 *
 *    Rev 1.48   May 23 2003 14:38:04   HERNANDO
 * Added OnManualDividend and OnUpdateManualDividend.
 *
 *    Rev 1.47   Apr 16 2003 13:22:46   popescu
 * Enable the system level menu items when there is no worksession available (where there is no work)
 *
 *    Rev 1.46   Apr 16 2003 09:41:04   YINGBAOL
 * remove AMS global from search to system menu
 *
 *    Rev 1.45   Mar 31 2003 16:21:20   sanchez
 * Define function prototypes:   afx_msg void OnUpdateFinancial(CCmdUI* pCmdUI) and
 *    afx_msg void OnUpdateSettlement(CCmdUI* pCmdUI);
 *
 *    Rev 1.44   Mar 14 2003 17:27:50   FENGYONG
 * Add menu Broker level AMS
 *
 *    Rev 1.43   Mar 03 2003 09:46:52   KOVACSRO
 * Added TradeSearch
 *
 *    Rev 1.42   Feb 18 2003 11:46:16   popescu
 * Added security check for AMS report menu item
 *
 *    Rev 1.41   Feb 06 2003 10:24:48   popescu
 * added the handlers for Historical Info Searc
 *
 *    Rev 1.40   Feb 05 2003 13:34:24   HERNANDO
 * Revised OnUpdateMktIndex.
 *
 *    Rev 1.39   Jan 31 2003 13:09:40   HERNANDO
 * Added OnUpdateMktIndex.
 *
 *    Rev 1.38   Jan 29 2003 13:29:22   HERNANDO
 * Added OnMktIndexValues.
 *
 *    Rev 1.37   Jan 21 2003 15:12:02   YINGBAOL
 * added  OnSystemLevelFee()
 *
 *    Rev 1.36   Jan 21 2003 11:22:40   HERNANDO
 * Added OnMktIndexMaster.
 *
 *    Rev 1.35   Jan 20 2003 15:43:58   popescu
 * Checked in for unit testing the ProtectedFundSetup feature
 *
 *    Rev 1.34   Dec 08 2002 22:17:22   HSUCHIN
 * added report status option
 *
 *    Rev 1.33   Nov 27 2002 11:48:20   HSUCHIN
 * added reports launch point
 *
 *    Rev 1.32   Oct 09 2002 23:55:38   PURDYECH
 * PVCS Database Conversion
 *
 *    Rev 1.31   Jul 30 2002 12:04:44   YINGBAOL
 * added LEdit Type and force user to input numeric number for SIN Account Nbr. ShareholderNbr and Certificate Nbr.
 *
 *    Rev 1.30   Jun 08 2002 13:28:32   HSUCHIN
 * added settlement support
 *
 *    Rev 1.29   May 29 2002 15:18:30   KOVACSRO
 * BFData Implementation - Phase II - syncup
 *
 *    Rev 1.28   24 May 2002 17:14:14   KOVACSRO
 * Added F4pressed.
 *
 *    Rev 1.27.1.0   May 28 2002 12:19:50   PURDYECH
 * BFData Implementation - Phase II
 *
 *    Rev 1.27   15 Apr 2002 14:53:54   HERNANDO
 * PTS 10007576 - Add newSearch.
 *
 *    Rev 1.26   Apr 03 2002 18:34:58   HERNANDO
 * Flag added - Allow changing MgmtCo without losing AWD Work Object.
 *
 *    Rev 1.25   19 Mar 2002 13:44:36   PURDYECH
 * Added #pragma once include guard
 * Removed compile time "including..." message.
 *
 *    Rev 1.24   Feb 14 2002 11:09:56   HERNANDO
 * Added doNASU.
 *
 *    Rev 1.23   Dec 10 2001 17:27:16   HERNANDO
 * Data type change.
 *
 *    Rev 1.22   Dec 07 2001 17:57:48   HERNANDO
 * Removed m_pAwdInterface.
 *
 *    Rev 1.21   Nov 29 2001 14:30:40   HERNANDO
 * Added OnHelp1(), OnHelp2(), OnHelp3(), LaunchHelp(), dwHtmlHelpCookie; removed OnHelp()
 *
 *    Rev 1.20   Nov 28 2001 17:26:28   HERNANDO
 * Added OnHelp()
 *
 *    Rev 1.19   24 Sep 2001 11:00:18   HSUCHIN
 * added function to enable/disable trade button
 *
 *    Rev 1.18   30 Jul 2001 15:49:52   YINGZ
 * auto change of resources
 *
 *    Rev 1.17   May 17 2001 12:25:18   HERNANDO
 * Sync with 1.15.2.0 - Added Session Number.
 *
 *    Rev 1.16   03 May 2001 14:07:32   SMITHDAV
 * Session management restructuring.
 *
 *    Rev 1.15   07 Mar 2001 15:44:42   BUZILAMI
 * Broker, Branch, SlsRep Bank Instructions changes
 *
 *    Rev 1.14   Oct 18 2000 18:17:48   HERNANDO
 * Added flag - conditional Discard of AWD work object
 *
 *    Rev 1.13   Oct 13 2000 15:21:04   HERNANDO
 * Added getWorkDataForAccountSearch()
 *
 *    Rev 1.12   Oct 06 2000 17:10:08   HERNANDO
 * Added OnAwdHistory; cleaned up a little.
 *
 *    Rev 1.11   Sep 28 2000 15:19:14   HERNANDO
 * Cleaned up code.
 *
 *    Rev 1.10   Sep 22 2000 13:32:36   KOVACSRO
 * added OnChangeEdtAreaCode()
 *
 *    Rev 1.9   Sep 22 2000 09:00:10   KOVACSRO
 * Added checkForTelephoneNo, and a flag.
 *
 *    Rev 1.8   Aug 25 2000 10:43:24   YINGBAOL
 * add trade screen to NASU flow
 *
 *    Rev 1.7   Apr 05 2000 10:24:48   DT24433
 * added class DSTCDoc forward reference
 *
 *    Rev 1.6   Apr 03 2000 15:43:30   DT24433
 * removed businfo member variable
 *
 *    Rev 1.5   Apr 03 2000 10:35:38   YINGZ
 * code sync
 *
 *    Rev 1.4   Mar 30 2000 09:45:40   BUZILA
 * fix BusInfoDlg cleanup
 *
 *    Rev 1.3   Mar 22 2000 09:00:32   PETOLESC
 * Added Tax Rates, RESP dialogs.
 *
 *    Rev 1.2   Mar 02 2000 10:58:58   DT24433
 * changes for new dispatcher base classes
 *
 *    Rev 1.1   Feb 15 2000 18:59:20   MCNABBGL
 * changed comment format
 *
 *    Rev 1.0   Feb 15 2000 11:01:12   SMITHDAV
 * Initial revision.
 *
 *    Rev 1.19   Jan 28 2000 17:49:24   POPESCUS
 * JERRY!!!! :-)) FIXED THE BIG CRASH AT THE END;
 *
 *    Rev 1.18   Jan 18 2000 16:36:08   HSUCHIN
 * changed launchAccountDetails's parameters
 *
 *    Rev 1.17   Jan 16 2000 17:01:04   POPESCUS
 * changes for the refresh of account details after a new shareholder is created
 *
 *    Rev 1.16   Jan 14 2000 14:44:18   HSUCHIN
 * end call flow
 *
 *    Rev 1.15   23 Dec 1999 15:53:18   HSUCHIN
 * End call no longer calls confirmation
 *
 *    Rev 1.14   Nov 25 1999 10:37:42   HSUCHIN
 * No change.
 *
 *    Rev 1.13   Oct 24 1999 11:18:02   POPESCUS
 * Added the remarks button to the main control screen
 *
 *    Rev 1.12   Oct 18 1999 09:48:58   POPESCUS
 * New search criterias and UAF codes
 *
 *    Rev 1.11   Oct 14 1999 10:47:44   HSUCHIN
 * AWD now using Session Object.  There are still outstanding issues.
 *
 *    Rev 1.10   Aug 10 1999 13:16:40   YINGZ
 * caller infor should only be entered if nobody has enter it
 *
 *    Rev 1.9   Aug 04 1999 11:15:56   PRAGERYA
 * Fixing date
 *
 *    Rev 1.8   Aug 03 1999 17:08:38   BUZILA
 * added ..
 *
 *    Rev 1.7   Jul 29 1999 19:07:20   HSUCHIN
 * Fixed AWD to use Databroker for Search Options
 *
 *    Rev 1.6   Jul 23 1999 10:23:04   POPESCUS
 * Using substiutes list for the combos
 *
 *    Rev 1.5   Jul 19 1999 11:52:02   POPESCUS
 *
 *    Rev 1.4   Jul 16 1999 12:31:52   POPESCUS
 *
 *    Rev 1.3   Jul 15 1999 12:30:50   POPESCUS
 * No change.
 *
 *    Rev 1.2   Jul 13 1999 17:23:20   HSUCHIN
 * small bug fix
 *
 *    Rev 1.1   Jul 08 1999 10:05:02   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
