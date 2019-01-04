//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1999 by International Financial Data Servicesaguila
//
//******************************************************************************
//
// ^FILE   : FeaturesSearchDlg.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : June, 2003
//
// ----------------------------------------------------------
//
// ^CLASS    : FeaturesSearchDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  

//******************************************************************************
#include "stdafx.h"
#include "MFDSTC.h"
#include "featuressearchdlg.h"
#include <ifastbp\featuressearchprocessincludes.h>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastcbo\dstcworksession.hpp>
#include <bfproc\genericinterfacecontainer.hpp>
#include "discardmsgdlg.h"

extern CLASS_IMPORT const I_CHAR* CMD_GUI_FEATURES_SEARCH;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_BROKER;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_BRANCH;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_SLSREP;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FUNDCLASS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FEE_MODEL;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FUND_BROKER;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< FeaturesSearchDlg > dlgCreator(CMD_GUI_FEATURES_SEARCH);

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_("FeaturesSearchDlg");
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace BF_SEARCH_CRITERIA
{
   //payment instructions
   extern CLASS_IMPORT I_CHAR * const PAY_TO_ENTITY;
   extern CLASS_IMPORT I_CHAR * const PAYMENT_INSTRUCTIONS;
}

namespace FEATURES_SEARCH_CONTROLS
{   
   const UINT EDIT_CNTRL   = 1;
   const UINT COMBO_CNTRL  = 2;
}

//*****************************************************************************
// Public methods
//*****************************************************************************
FeaturesSearchDlg::FeaturesSearchDlg(CWnd* pParent, 
   GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, 
   const Command& rCommand)
: BaseMainDlg(FeaturesSearchDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME), 
m_pWndItemInFocus(NULL),
m_dstrBackgroundSearch(NULL_STRING)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   //{{AFX_DATA_INIT(FeaturesSearchDlg)
   //}}AFX_DATA_INIT
}

//*****************************************************************************
void FeaturesSearchDlg::DoDataExchange(CDataExchange* pDX)

{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(FeaturesSearchDlg)
   //}}AFX_DATA_MAP
}

//*****************************************************************************
SEVERITY FeaturesSearchDlg::doInit()
{
   TRACE_METHOD(CLASSNAME, DOINIT);

   getParameter(MFCAN_IP_PARAM::BACKGROUND_SEARCH, 
      m_dstrBackgroundSearch);  
   return(NO_CONDITION);
}

//*****************************************************************************
BEGIN_MESSAGE_MAP(FeaturesSearchDlg, BaseMainDlg)
//{{AFX_MSG_MAP(FeaturesSearchDlg)
ON_MESSAGE(UM_OPENFUNDLISTDLG, OpenFundListDlg)
ON_MESSAGE(UM_OPENBROKERLISTDLG, OpenBrokerListDlg)
ON_MESSAGE(UM_OPENBRANCHLISTDLG, OpenBranchListDlg)
ON_MESSAGE(UM_OPENSLSREPLISTDLG, OpenSlsRepListDlg)
ON_MESSAGE(UM_OPENFEEMODELDLG, OpenFeeModelDlg)
ON_MESSAGE(UM_OPENFNDBRKRLISTDLG, OpenFndBrkrListDlg)
ON_BN_CLICKED(IDC_BTN_SEARCH, OnBtnSearch)
ON_BN_CLICKED(IDC_ADD_FUND_BROKER2, OnBtnAdd)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
// Message handlers
//*****************************************************************************
BOOL FeaturesSearchDlg::OnInitDialog() 
{
   TRACE_METHOD(CLASSNAME, ONINITDIALOG);

   BaseMainDlg::OnInitDialog();

   return TRUE;
}

//*****************************************************************************
void FeaturesSearchDlg::OnPostInitDialog()
{
   TRACE_METHOD(CLASSNAME, ONPOSTINITDIALOG);

   AddControl(CTRL_COMBO, IDC_CMB_SEARCH, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      ifds::SearchCriteria, CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST);
   AddControl(CTRL_COMBO, IDC_CMB_USING, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      ifds::SearchUsing, CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST);
   AddControl(CTRL_STATIC, IDC_STC_SEARCH11, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      ifds::SearchLabel1, CTRLFLAG_DEFAULT);
   AddControl(CTRL_EDIT, IDC_EDT_SEARCH11, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      ifds::SearchFieldCriteria1, CTRLFLAG_DEFAULT);
   AddControl(CTRL_STATIC, IDC_STC_SEARCH21, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      ifds::SearchLabel1, CTRLFLAG_DEFAULT);
   AddControl(CTRL_EDIT, IDC_EDT_SEARCH21, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      ifds::SearchFieldCriteria1, CTRLFLAG_DEFAULT);   	
   AddControl(CTRL_COMBO, IDC_CMB_SEARCH21, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      ifds::SearchFieldCriteria1, CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST);			
	AddControl(CTRL_STATIC, IDC_STC_SEARCH22, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      ifds::SearchLabel2, CTRLFLAG_DEFAULT);
   AddControl(CTRL_EDIT, IDC_EDT_SEARCH22, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      ifds::SearchFieldCriteria2, CTRLFLAG_DEFAULT);
	AddControl(CTRL_DATE, IDC_DTP_SEARCH22, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      ifds::SearchFieldCriteria2, CTRLFLAG_DEFAULT); 
   AddControl(CTRL_STATIC, IDC_STC_SEARCH31, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      ifds::SearchLabel1, CTRLFLAG_DEFAULT);
   AddControl(CTRL_EDIT, IDC_EDT_SEARCH31, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      ifds::SearchFieldCriteria1, CTRLFLAG_DEFAULT);
   AddControl(CTRL_COMBO, IDC_CMB_SEARCH31, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      ifds::SearchFieldCriteria1, CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST);

	// For Aggregation "FromDate"
	AddControl(CTRL_DATE, IDC_DTP_SEARCH31, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      ifds::SearchFieldCriteria1, CTRLFLAG_DEFAULT);

   AddControl(CTRL_STATIC, IDC_STC_SEARCH32, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      ifds::SearchLabel2, CTRLFLAG_DEFAULT);
	//AddControl(CTRL_STATIC, IDC_STC_SEARCH32, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      //ifds::SearchLabel1, CTRLFLAG_DEFAULT);
   AddControl(CTRL_EDIT, IDC_EDT_SEARCH32, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      ifds::SearchFieldCriteria2, CTRLFLAG_DEFAULT);
   AddControl(CTRL_COMBO, IDC_CMB_SEARCH32, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      ifds::SearchFieldCriteria2, CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST);
	
	// For Aggregation "ToDate"
	AddControl(CTRL_DATE, IDC_DTP_SEARCH32, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      ifds::SearchFieldCriteria2, CTRLFLAG_DEFAULT);

   AddControl(CTRL_STATIC, IDC_STC_SEARCH33, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      ifds::SearchLabel3, CTRLFLAG_DEFAULT);
   AddControl(CTRL_EDIT, IDC_EDT_SEARCH33, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      ifds::SearchFieldCriteria3, CTRLFLAG_DEFAULT); 
	
	// For Aggregation "Status"
	AddControl(CTRL_COMBO, IDC_CMB_SEARCH33, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      ifds::SearchFieldCriteria3, CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST);
   
	// For Aggregation "Fund Broker"
	AddControl(CTRL_STATIC, IDC_STC_SEARCH41, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      ifds::SearchLabel4, CTRLFLAG_DEFAULT);
      // Map controls to same field but add them to different group
   AddControl(CTRL_COMBO, IDC_CMB_SEARCH41, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      ifds::SearchFieldCriteria4, CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, FEATURES_SEARCH_CONTROLS::COMBO_CNTRL);
   AddControl(CTRL_EDIT, IDC_EDT_SEARCH41, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      ifds::SearchFieldCriteria4, CTRLFLAG_DEFAULT, FEATURES_SEARCH_CONTROLS::EDIT_CNTRL);

	// For Aggrgation "Fund"
	AddControl(CTRL_STATIC, IDC_STC_SEARCH42, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      ifds::SearchLabel5, CTRLFLAG_DEFAULT);
   AddControl(CTRL_EDIT, IDC_EDT_SEARCH42, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      ifds::SearchFieldCriteria5, CTRLFLAG_DEFAULT); 

	// For Aggrgation "WKN"
	AddControl(CTRL_STATIC, IDC_STC_SEARCH43, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      ifds::SearchLabel6, CTRLFLAG_DEFAULT);
   AddControl(CTRL_EDIT, IDC_EDT_SEARCH43, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      ifds::SearchFieldCriteria6, CTRLFLAG_DEFAULT); 

	// For Aggrgation "ISIN"
	AddControl(CTRL_STATIC, IDC_STC_SEARCH44, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      ifds::SearchLabel7, CTRLFLAG_DEFAULT);
   AddControl(CTRL_EDIT, IDC_EDT_SEARCH44, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      ifds::SearchFieldCriteria7, CTRLFLAG_DEFAULT); 
   
   // For new FundBroker "Add New" 
   AddControl( CTRL_STATIC, IDC_ADD_FUND_BROKER2, CTRLFLAG_GUI_FIELD);
   DString searchType;
   getParent()->getField(this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      ifds::FillSearchType, searchType);

   if(searchType == SEARCH_TYPE::FUNDBROKER)
	   ShowControl(IDC_ADD_FUND_BROKER2, true);
   else
	   ShowControl(IDC_ADD_FUND_BROKER2, false);
		

//for dtf search criteria, there are new controls
   doRefresh (this, NULL_STRING);
}

//******************************************************************************
bool FeaturesSearchDlg::doRefresh(GenericInterface *rpGICaller, 
   const I_CHAR *szOriginalCommand)
{ 
   TRACE_METHOD(CLASSNAME, DOREFRESH);

   ConnectControlsToData();
   LoadControls(IFASTBP_PROC::SEARCH_CRITERIA_FILLER);
   if (m_dstrBackgroundSearch == I_("Y"))
   {
      MoveDialog(GUIPOS_TOP, 0);
      OnBtnSearch();
      //this is a one time call, 
      //so reset the background search option
      m_dstrBackgroundSearch = I_("N");
   }
   SetDlgCaption();
   return true;
}

//*************************************************************************
void FeaturesSearchDlg::SetDlgCaption()
{
   DString searchType,
      caption;
   CString cs;

   getParent()->getField(this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      ifds::FillSearchType, searchType);

   if (searchType == SEARCH_TYPE::BROKER_FEATURES)
   {
      cs.LoadString (TXT_FEATURES_SEARCH_BROKERS);
   }
   else if (searchType == SEARCH_TYPE::FI_FEATURES)
   {
      cs.LoadString (TXT_FEATURES_SEARCH_FI);
   }
   else if (searchType == SEARCH_TYPE::DAILY_TRANSACTIONS_FEES)
   {
      cs.LoadString (TXT_FEATURES_SEARCH_DTF);
   }
   else if (searchType == SEARCH_TYPE::FUNSSPONSORFEEMODEL)
   {
      cs.LoadString (TXT_FEATURES_SEARCH_FM);
   }
   else if (searchType == SEARCH_TYPE::FUNDBROKER)
   {
      cs.LoadString (TXT_FEATURES_SEARCH_FB);
   }
	else if (searchType == SEARCH_TYPE::AGGREGATEDORDER)
   {
      cs.LoadString (TXT_FEATURES_SEARCH_AGGREGATE);
   }
	
   caption = cs.GetBuffer (0);
   caption = I_(": ") + caption;
   SetCaption (caption);
}

//*************************************************************************
bool FeaturesSearchDlg::PreCancel()
{
   return discardUpdates();
}

//*************************************************************************
void FeaturesSearchDlg::ControlUpdated (
   UINT controlID, 
   const DString &strValue)
{
   switch (controlID)
   {
      case IDC_CMB_USING:
      {
         DString howManySearchCriterias,
            searchType, searchUsing;

         getParent()->getField(this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
            ifds::HowManySearchCriterias, howManySearchCriterias);
         getParent()->getField(this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
            ifds::FillSearchType, searchType);
         getParent()->getField(this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
            ifds::SearchUsing, searchUsing, false);

         if (howManySearchCriterias == I_("0"))
         {
			ShowControl (IDC_STC_SEARCH11, false);
			ShowControl (IDC_EDT_SEARCH11, false);
			ShowControl (IDC_STC_SEARCH21, false);
			ShowControl (IDC_EDT_SEARCH21, false);
			ShowControl (IDC_CMB_SEARCH21, false);
			ShowControl (IDC_STC_SEARCH22, false);
			ShowControl (IDC_EDT_SEARCH22, false);
			ShowControl (IDC_DTP_SEARCH22, false);
         ConnectControl( IDC_DTP_SEARCH22, false );
			ShowControl (IDC_STC_SEARCH31, false);
			ShowControl (IDC_EDT_SEARCH31, false);
			ShowControl (IDC_CMB_SEARCH31, false);
			ShowControl (IDC_STC_SEARCH32, false);
			ShowControl (IDC_EDT_SEARCH32, false);
			ShowControl (IDC_CMB_SEARCH32, false);
			ShowControl (IDC_STC_SEARCH33, false);
			ShowControl (IDC_EDT_SEARCH33, false); 
			ShowControl (IDC_STC_SEARCH41, false);
			ShowControl (IDC_CMB_SEARCH41, false);
			ShowControl (IDC_EDT_SEARCH41, false);
			ShowControl (IDC_STC_SEARCH42, false);
			ShowControl (IDC_EDT_SEARCH42, false);
			ShowControl (IDC_STC_SEARCH43, false);
			ShowControl (IDC_EDT_SEARCH43, false);
			ShowControl (IDC_STC_SEARCH44, false);
			ShowControl (IDC_EDT_SEARCH44, false);
			ShowControl (IDC_DTP_SEARCH31, false);
         ConnectControl( IDC_DTP_SEARCH31, false );
			ShowControl (IDC_DTP_SEARCH32, false);
         ConnectControl( IDC_DTP_SEARCH32, false );
			ShowControl (IDC_CMB_SEARCH33, false);
         }
         else if (howManySearchCriterias == I_("1"))
         {
            if( (searchType == SEARCH_TYPE::FUNSSPONSORFEEMODEL && searchUsing == FEEMODEL_USING::FUNDSPONSORCODE ) 
               /*|| (searchType == SEARCH_TYPE::FUNDBROKER && searchUsing == FUNDBROKER_USING::FUNDBROKERCODE)*/
				)
            {
				ShowControl (IDC_STC_SEARCH11, false);
				ShowControl (IDC_EDT_SEARCH11, false);
				ShowControl (IDC_STC_SEARCH21, true);
				ShowControl (IDC_EDT_SEARCH21, false);
				ShowControl (IDC_CMB_SEARCH21, true);
				ShowControl (IDC_STC_SEARCH22, false);
				ShowControl (IDC_EDT_SEARCH22, false);
				ShowControl (IDC_DTP_SEARCH22, false);
            ConnectControl( IDC_DTP_SEARCH22, false );
				ShowControl (IDC_STC_SEARCH31, false);
				ShowControl (IDC_EDT_SEARCH31, false);
				ShowControl (IDC_CMB_SEARCH31, false);
				ShowControl (IDC_STC_SEARCH32, false);
				ShowControl (IDC_EDT_SEARCH32, false);
				ShowControl (IDC_CMB_SEARCH32, false);
				ShowControl (IDC_STC_SEARCH33, false);
				ShowControl (IDC_EDT_SEARCH33, false); 
				ShowControl (IDC_STC_SEARCH41, false);
				ShowControl (IDC_CMB_SEARCH41, false);
				ShowControl (IDC_EDT_SEARCH41, false);
				ShowControl (IDC_STC_SEARCH42, false);
				ShowControl (IDC_EDT_SEARCH42, false);
				ShowControl (IDC_STC_SEARCH43, false);
				ShowControl (IDC_EDT_SEARCH43, false);
				ShowControl (IDC_STC_SEARCH44, false);
				ShowControl (IDC_EDT_SEARCH44, false);
				ShowControl (IDC_DTP_SEARCH31, false);
            ConnectControl( IDC_DTP_SEARCH31, false );
				ShowControl (IDC_DTP_SEARCH32, false);
            ConnectControl( IDC_DTP_SEARCH32, false );
				ShowControl (IDC_CMB_SEARCH33, false);
            }
            else
            {
				ShowControl (IDC_STC_SEARCH11, true);
				ShowControl (IDC_EDT_SEARCH11, false);
				ShowControl (IDC_STC_SEARCH21, false);
				ShowControl (IDC_EDT_SEARCH21, false);
				ShowControl (IDC_CMB_SEARCH21, false);
				ShowControl (IDC_STC_SEARCH22, false);
				ShowControl (IDC_EDT_SEARCH22, false);
				ShowControl (IDC_DTP_SEARCH22, false);
            ConnectControl( IDC_DTP_SEARCH22, false );
				ShowControl (IDC_STC_SEARCH31, false);
				ShowControl (IDC_EDT_SEARCH31, false );
				ShowControl (IDC_CMB_SEARCH31, false );
				ShowControl (IDC_STC_SEARCH32, false);
				ShowControl (IDC_EDT_SEARCH32, true );
				ShowControl (IDC_CMB_SEARCH32, false);
				ShowControl (IDC_STC_SEARCH33, false);
				ShowControl (IDC_EDT_SEARCH33, false); 
				ShowControl (IDC_STC_SEARCH41, false);
				ShowControl (IDC_CMB_SEARCH41, false);
				ShowControl (IDC_EDT_SEARCH41, false);
				ShowControl (IDC_STC_SEARCH42, false);
				ShowControl (IDC_EDT_SEARCH42, false);
				ShowControl (IDC_STC_SEARCH43, false);
				ShowControl (IDC_EDT_SEARCH43, false);
				ShowControl (IDC_STC_SEARCH44, false);
				ShowControl (IDC_EDT_SEARCH44, false);
				ShowControl (IDC_DTP_SEARCH31, false);
            ConnectControl( IDC_DTP_SEARCH31, false );
				ShowControl (IDC_DTP_SEARCH32, false);
            ConnectControl( IDC_DTP_SEARCH32, false );
				ShowControl (IDC_CMB_SEARCH33, false);
            }
         }
         else if (howManySearchCriterias == I_("2"))
         {
			if (searchType == SEARCH_TYPE::DAILY_TRANSACTIONS_FEES)
            {															
				ShowControl (IDC_STC_SEARCH11, false );
				ShowControl (IDC_EDT_SEARCH11, false );
				ShowControl (IDC_STC_SEARCH21, true );
				ShowControl (IDC_EDT_SEARCH21, false );
				ShowControl (IDC_CMB_SEARCH21, true );
				ShowControl (IDC_STC_SEARCH22, true );
				ShowControl (IDC_EDT_SEARCH22, false );					
				ShowControl (IDC_DTP_SEARCH22, true );
				GetControl (IDC_DTP_SEARCH22)->ConnectToData (true);
				LoadControl (IDC_DTP_SEARCH22);
				ShowControl (IDC_STC_SEARCH31, false );
				ShowControl (IDC_EDT_SEARCH31, false );
				ShowControl (IDC_CMB_SEARCH31, false );
				ShowControl (IDC_STC_SEARCH32, false );
				ShowControl (IDC_EDT_SEARCH32, false );
				ShowControl (IDC_CMB_SEARCH32, false );               
				ShowControl (IDC_STC_SEARCH33, false );               
				ShowControl (IDC_EDT_SEARCH33, false);
				ShowControl (IDC_STC_SEARCH41, false);
				ShowControl (IDC_CMB_SEARCH41, false);
				ShowControl (IDC_EDT_SEARCH41, false);
				ShowControl (IDC_STC_SEARCH42, false);
				ShowControl (IDC_EDT_SEARCH42, false);
				ShowControl (IDC_STC_SEARCH43, false);
				ShowControl (IDC_EDT_SEARCH43, false);
				ShowControl (IDC_STC_SEARCH44, false);
				ShowControl (IDC_EDT_SEARCH44, false);
				ShowControl (IDC_DTP_SEARCH31, false);
            ConnectControl( IDC_DTP_SEARCH31, false );
				ShowControl (IDC_DTP_SEARCH32, false);
            ConnectControl( IDC_DTP_SEARCH32, false );
				ShowControl (IDC_CMB_SEARCH33, false);
            }
			else if (searchType == SEARCH_TYPE::AGGREGATEDORDER)
            {															
				ShowControl (IDC_STC_SEARCH11, false );
				ShowControl (IDC_EDT_SEARCH11, false );
				ShowControl (IDC_STC_SEARCH21, false );
				ShowControl (IDC_EDT_SEARCH21, false );
				ShowControl (IDC_CMB_SEARCH21, false );
				ShowControl (IDC_STC_SEARCH22, false );
				ShowControl (IDC_EDT_SEARCH22, false );					
				ShowControl (IDC_DTP_SEARCH22, false );
            ConnectControl( IDC_DTP_SEARCH22, false );
				ShowControl (IDC_STC_SEARCH31, true );
				ShowControl (IDC_EDT_SEARCH31, false );
				ShowControl (IDC_CMB_SEARCH31, true );
				ShowControl (IDC_STC_SEARCH32, false );
				ShowControl (IDC_EDT_SEARCH32, false );
				ShowControl (IDC_CMB_SEARCH32, false );               
				ShowControl (IDC_STC_SEARCH33, true );               
				ShowControl (IDC_EDT_SEARCH33, true ); 
				ShowControl (IDC_STC_SEARCH41, false);
				ShowControl (IDC_CMB_SEARCH41, false);
				ShowControl (IDC_EDT_SEARCH41, false);
				ShowControl (IDC_STC_SEARCH42, false);
				ShowControl (IDC_EDT_SEARCH42, false);
				ShowControl (IDC_STC_SEARCH43, false);
				ShowControl (IDC_EDT_SEARCH43, false);
				ShowControl (IDC_STC_SEARCH44, false);
				ShowControl (IDC_EDT_SEARCH44, false);
				ShowControl (IDC_DTP_SEARCH31, false);
            ConnectControl( IDC_DTP_SEARCH31, false );
				ShowControl (IDC_DTP_SEARCH32, false);
            ConnectControl( IDC_DTP_SEARCH32, false );
				ShowControl (IDC_CMB_SEARCH33, false);
         } 
			else
			{
				ShowControl (IDC_STC_SEARCH11, false);
				ShowControl (IDC_EDT_SEARCH11, false);
				ShowControl (IDC_STC_SEARCH21, true);
				ShowControl (IDC_EDT_SEARCH21, true);
				ShowControl (IDC_CMB_SEARCH21, false);
				ShowControl (IDC_STC_SEARCH22, true);
				ShowControl (IDC_EDT_SEARCH22, true);
				ShowControl (IDC_DTP_SEARCH22, false);
            ConnectControl( IDC_DTP_SEARCH22, false );
				ShowControl (IDC_STC_SEARCH31, false);
				ShowControl (IDC_EDT_SEARCH31, false);
				ShowControl (IDC_CMB_SEARCH31, false);
				ShowControl (IDC_STC_SEARCH32, false);
				ShowControl (IDC_EDT_SEARCH32, false);
				ShowControl (IDC_CMB_SEARCH32, false);
				ShowControl (IDC_STC_SEARCH33, false);
				ShowControl (IDC_EDT_SEARCH33, false);
				ShowControl (IDC_STC_SEARCH41, false);
				ShowControl (IDC_CMB_SEARCH41, false);
				ShowControl (IDC_EDT_SEARCH41, false);
				ShowControl (IDC_STC_SEARCH42, false);
				ShowControl (IDC_EDT_SEARCH42, false);
				ShowControl (IDC_STC_SEARCH43, false);
				ShowControl (IDC_EDT_SEARCH43, false);
				ShowControl (IDC_STC_SEARCH44, false);
				ShowControl (IDC_EDT_SEARCH44, false);
				ShowControl (IDC_DTP_SEARCH31, false);
            ConnectControl( IDC_DTP_SEARCH31, false );
				ShowControl (IDC_DTP_SEARCH32, false);
            ConnectControl( IDC_DTP_SEARCH32, false );
				ShowControl (IDC_CMB_SEARCH33, false);
			}
         }
         else if (howManySearchCriterias == I_("3"))
         {            
            if (searchType == SEARCH_TYPE::BROKER_FEATURES)
            {
				ShowControl (IDC_STC_SEARCH11, false);
				ShowControl (IDC_EDT_SEARCH11, false);
				ShowControl (IDC_STC_SEARCH21, false);
				ShowControl (IDC_EDT_SEARCH21, false);
				ShowControl (IDC_CMB_SEARCH21, false);
				ShowControl (IDC_STC_SEARCH22, false);
				ShowControl (IDC_EDT_SEARCH22, false);
				ShowControl (IDC_DTP_SEARCH22, false);
            ConnectControl( IDC_DTP_SEARCH22, false );
				ShowControl (IDC_STC_SEARCH31, true);
				ShowControl (IDC_EDT_SEARCH31, true);
				ShowControl (IDC_CMB_SEARCH31, false);
				ShowControl (IDC_STC_SEARCH32, true);
				ShowControl (IDC_EDT_SEARCH32, true);
				ShowControl (IDC_CMB_SEARCH32, false);
				ShowControl (IDC_STC_SEARCH33, true);
				ShowControl (IDC_EDT_SEARCH33, true);
				ShowControl (IDC_STC_SEARCH41, false);
				ShowControl (IDC_CMB_SEARCH41, false);
				ShowControl (IDC_EDT_SEARCH41, false);
				ShowControl (IDC_STC_SEARCH42, false);
				ShowControl (IDC_EDT_SEARCH42, false);
				ShowControl (IDC_STC_SEARCH43, false);
				ShowControl (IDC_EDT_SEARCH43, false);
				ShowControl (IDC_STC_SEARCH44, false);
				ShowControl (IDC_EDT_SEARCH44, false);
				ShowControl (IDC_DTP_SEARCH31, false);
            ConnectControl( IDC_DTP_SEARCH31, false );
				ShowControl (IDC_DTP_SEARCH32, false);
            ConnectControl( IDC_DTP_SEARCH32, false );
				ShowControl (IDC_CMB_SEARCH33, false);
            }
            else if (searchType == SEARCH_TYPE::FI_FEATURES)
            {
				ShowControl (IDC_STC_SEARCH11, false);
				ShowControl (IDC_EDT_SEARCH11, false);
				ShowControl (IDC_STC_SEARCH21, false);
				ShowControl (IDC_EDT_SEARCH21, false);
				ShowControl (IDC_CMB_SEARCH21, false);
				ShowControl (IDC_STC_SEARCH22, false);
				ShowControl (IDC_EDT_SEARCH22, false);
				ShowControl (IDC_DTP_SEARCH22, false);
            ConnectControl( IDC_DTP_SEARCH22, false );
				ShowControl (IDC_STC_SEARCH31, true);
				ShowControl (IDC_EDT_SEARCH31, false);
				ShowControl (IDC_CMB_SEARCH31, true);
				ShowControl (IDC_STC_SEARCH32, true);
				ShowControl (IDC_EDT_SEARCH32, false);
				ShowControl (IDC_CMB_SEARCH32, true);
				ShowControl (IDC_STC_SEARCH33, true);
				ShowControl (IDC_EDT_SEARCH33, true);
				ShowControl (IDC_STC_SEARCH41, false);
				ShowControl (IDC_CMB_SEARCH41, false);
				ShowControl (IDC_EDT_SEARCH41, false);
				ShowControl (IDC_STC_SEARCH42, false);
				ShowControl (IDC_EDT_SEARCH42, false);
				ShowControl (IDC_STC_SEARCH43, false);
				ShowControl (IDC_EDT_SEARCH43, false);
				ShowControl (IDC_STC_SEARCH44, false);
				ShowControl (IDC_EDT_SEARCH44, false);
				ShowControl (IDC_DTP_SEARCH31, false);
            ConnectControl( IDC_DTP_SEARCH31, false );
				ShowControl (IDC_DTP_SEARCH32, false);
            ConnectControl( IDC_DTP_SEARCH32, false );
				ShowControl (IDC_CMB_SEARCH33, false);
            }            
			if (searchType == SEARCH_TYPE::DAILY_TRANSACTIONS_FEES)
            {
				ShowControl (IDC_STC_SEARCH11, false);
				ShowControl (IDC_EDT_SEARCH11, false);
				ShowControl (IDC_STC_SEARCH21, false);
				ShowControl (IDC_EDT_SEARCH21, false);
				ShowControl (IDC_CMB_SEARCH21, false);
				ShowControl (IDC_STC_SEARCH22, false);
				ShowControl (IDC_EDT_SEARCH22, false);
				ShowControl (IDC_DTP_SEARCH22, false);
				GetControl (IDC_DTP_SEARCH22)->ConnectToData (false);
				// 3 search params, first one: Fee Type label
				ShowControl (IDC_STC_SEARCH31, true);
				// 3 search params, first one: disabled as Fee Type is combo
				ShowControl (IDC_EDT_SEARCH31, false);
				// 3 search params, first one: Fee Type combo enabled
				ShowControl (IDC_CMB_SEARCH31, true);               
				// 3 search params, second one: Fund label
				ShowControl (IDC_STC_SEARCH32, true);
				// 3 search params, second one: Fund edit enabled
				ShowControl (IDC_EDT_SEARCH32, true);            
				// 3 search params, second one: disabled as Fund is edit
				ShowControl (IDC_CMB_SEARCH32, false);
				// 3 search params, third one: Class label
				ShowControl (IDC_STC_SEARCH33, true);
				// 3 search params, third one: Class edit 
				ShowControl (IDC_EDT_SEARCH33, true);
				ShowControl (IDC_STC_SEARCH41, false);
				ShowControl (IDC_CMB_SEARCH41, false);
				ShowControl (IDC_EDT_SEARCH41, false);
				ShowControl (IDC_STC_SEARCH42, false);
				ShowControl (IDC_EDT_SEARCH42, false);
				ShowControl (IDC_STC_SEARCH43, false);
				ShowControl (IDC_EDT_SEARCH43, false);
				ShowControl (IDC_STC_SEARCH44, false);
				ShowControl (IDC_EDT_SEARCH44, false);
				ShowControl (IDC_DTP_SEARCH31, false);
            ConnectControl( IDC_DTP_SEARCH31, false );
				ShowControl (IDC_DTP_SEARCH32, false);
            ConnectControl( IDC_DTP_SEARCH32, false );
				ShowControl (IDC_CMB_SEARCH33, false);
            }
		 }
		 else if (howManySearchCriterias == I_("7"))
         {
			if (searchType == SEARCH_TYPE::AGGREGATEDORDER)
            {
				ShowControl (IDC_STC_SEARCH11, false);
				ShowControl (IDC_EDT_SEARCH11, false);
				ShowControl (IDC_STC_SEARCH21, false);
				ShowControl (IDC_EDT_SEARCH21, false);
				ShowControl (IDC_CMB_SEARCH21, false);
				ShowControl (IDC_STC_SEARCH22, false);
				ShowControl (IDC_EDT_SEARCH22, false);
				ShowControl (IDC_DTP_SEARCH22, false);
            ConnectControl( IDC_DTP_SEARCH22, false );
				ShowControl (IDC_EDT_SEARCH31, false);
				ShowControl (IDC_CMB_SEARCH31, false);
				ShowControl (IDC_STC_SEARCH31, true);  // "From Date"
				ShowControl (IDC_DTP_SEARCH31, true);  // From Date
				GetControl(IDC_DTP_SEARCH31)->SetConnected(true);
				GetControl(IDC_DTP_SEARCH31)->ConnectToData(true);
				LoadControl(IDC_DTP_SEARCH31);
 				ShowControl (IDC_EDT_SEARCH32, false);
				ShowControl (IDC_CMB_SEARCH32, false);
				ShowControl (IDC_STC_SEARCH32, true);  // "To Date"
				ShowControl (IDC_DTP_SEARCH32, true); // To Date
				GetControl(IDC_DTP_SEARCH32)->SetConnected(true);
				GetControl(IDC_DTP_SEARCH32)->ConnectToData(true);
				LoadControl(IDC_DTP_SEARCH32);
				ShowControl (IDC_STC_SEARCH33, true);  // "Status"
				ShowControl (IDC_EDT_SEARCH33, false);
				ShowControl (IDC_CMB_SEARCH33, true);  // Status
				ShowControl (IDC_STC_SEARCH41, true);  // "Fund Broker"
				ShowControl (IDC_CMB_SEARCH41, false);  // In this case, combobox need to be disable
				ShowControl (IDC_EDT_SEARCH41, true);  // fund broker
			   ConnectControlsToData( FEATURES_SEARCH_CONTROLS::COMBO_CNTRL, false );
			   ConnectControlsToData( FEATURES_SEARCH_CONTROLS::EDIT_CNTRL, true );
				ShowControl (IDC_STC_SEARCH42, true);  // "Fund"
				ShowControl (IDC_EDT_SEARCH42, true);  // fund
				ShowControl (IDC_STC_SEARCH43, true);  // "WKN:"
				ShowControl (IDC_EDT_SEARCH43, true);  // wkn
				ShowControl (IDC_STC_SEARCH44, true);  // "ISIN:"
				ShowControl (IDC_EDT_SEARCH44, true);  // ISIN
			}
		}  
		break;
	   }
	  case IDC_CMB_SEARCH:
	{
		DString searchType;
		getParent()->getField(this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
								ifds::FillSearchType, searchType);

		if(searchType == SEARCH_TYPE::FUNDBROKER)
			ShowControl(IDC_ADD_FUND_BROKER2, true);
		else
			ShowControl(IDC_ADD_FUND_BROKER2, false);
	}
       default:
			break;
   
   }
	//this dialog should not care for the updated flag
	setUpdateFlag (false);
}

//******************************************************************************
void FeaturesSearchDlg::OnBtnSearch()
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnSearch"));
   CWaitCursor wait;

   GetDlgItem(IDC_BTN_SEARCH)->SetFocus();
   if (discardUpdates())
   {
      if (getParent()->performSearch(this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
         SEARCH_START) > WARNING)
      {
         // Display error
         ConditionMessageBox(FRAMEBELOW(), GETHIGHESTSEVERITY());
      }
   }
}

//******************************************************************************
void FeaturesSearchDlg::OnBtnAdd()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_(" OnBtnAdminDates() " ) );
   CWaitCursor wait;

   if (discardUpdates())
   {
	   try
	   {
			E_COMMANDRETURN eRtn;

			//2319580 - This logic is to force fundbroker name criteria to be the fundbroker name 
			//that couldn't be found anywhere so that It can bring up the Fund Broker screen 
			//with empty fund broker row just like the existing function when do a search 
			//for a non-existing fund broker by name.
			//We should replace the existing fuction when do a seach for a non-existing 
			//fund broker by name to return "data not found instead of bring up fund broker screen 
			//with empty fund broker row.
			setParameter(I_( "SearchType" ),I_("FundBrokerName"));
			setParameter(I_( "FundBrokerName" ),I_("-fromnewfb-"));
			setParameter(I_( "FundBrokerCode" ),I_(""));
			
			eRtn = invokeCommand (getParent(), CMD_BPROC_FUND_BROKER, 
				PROC_NO_TYPE, false, NULL);
			SetMessageStatusBar( NULL_STRING );
			switch( eRtn )
			{
				case CMD_OK:
				case CMD_CANCEL:
				case CMD_MODELESS_INPROCESS:
					break;
				default:
					// Display error
					ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
					break;
			}
		}
		catch( ConditionException &ce )
		{
			ConditionMessageBox( ce );
		}
		catch( ... )
		{
			DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
		}
   }
}
//******************************************************************
BOOL FeaturesSearchDlg::PreTranslateMessage(MSG* pMsg) 
{
   //do not allow F4 on the edit controls that are not updateable
   if (pMsg->message == WM_KEYDOWN && (int)(pMsg->wParam) == VK_F4 && 
      !IsSelectedCtrlUpdateable())
   {
      return TRUE;
   }
   if (pMsg->message == WM_KEYDOWN && (int)(pMsg->wParam) == VK_F4)
   {
      if (isBrokerSearchField())
      {
         PostMessage (UM_OPENBROKERLISTDLG);
      } 
      else if (isBranchSearchField())
      {
         PostMessage (UM_OPENBRANCHLISTDLG);
      }
      else if (isSlsRepSearchField())
      {
         PostMessage (UM_OPENSLSREPLISTDLG);
      }
      else if (isFundCodeSearchField() || isClassCodeSearchField())
      {
         PostMessage (UM_OPENFUNDLISTDLG);
      }
      else if (isSponsorSearchField() )
      {
         //PostMessage (UM_OpenFundSponsorDlg);
      }
      else if (isFeeModelSearchField() )
      {
         PostMessage (UM_OPENFEEMODELDLG);
      }
      else if (isFndBrkrForAggregatedOrderSearchField())
      {
         PostMessage (UM_OPENFNDBRKRLISTDLG);
      }
   }
   return BaseMainDlg::PreTranslateMessage(pMsg);
}

//******************************************************************
LRESULT FeaturesSearchDlg::OpenBrokerListDlg(WPARAM, LPARAM)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OpenBrokerListDlg"));
   E_COMMANDRETURN eRtn = CMD_CANCEL;
   CWaitCursor wait;

   try
   {
      DString brokerCode;
   
      getParent()->getField(this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
         ifds::SearchFieldCriteria1, brokerCode);
      if (shouldSetTheCaller())
      {
         setParameter(MFCAN_IP_PARAM::CALLER, I_("PaymentInstructions"));
      }
      setParameter(MFCAN_IP_PARAM::BROKER_CODE, brokerCode);
      eRtn = invokeCommand(getParent(), CMD_BPROC_BROKER, 
            PROC_SUPPORT, true, NULL);
      switch(eRtn)
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               getParameter(MFCAN_IP_PARAM::BROKER_CODE, brokerCode);
               if(brokerCode != NULL_STRING)
               {
                  getParent()->setField(this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
                     ifds::SearchFieldCriteria1, brokerCode);
               }
               LoadControl(getBrokerEditControlId());
               break;
            }
         case CMD_CANCEL:
            break;
         default:
            // Display error
            ConditionMessageBox(FRAMEBELOW(), GETHIGHESTSEVERITY());
            break;
      }
   }
   catch(ConditionException &ce)
   {
      ConditionMessageBox(ce);
   }
   catch(...)
   {
      DISPLAYCONDITIONFROMFILE(CND::GUI_ERR_UNKNOWN_EXCEPTION);
   }
   return eRtn;
}

//******************************************************************
LRESULT FeaturesSearchDlg::OpenBranchListDlg(WPARAM, LPARAM)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OpenBranchListDlg"));
   E_COMMANDRETURN eRtn = CMD_CANCEL;
   CWaitCursor wait;

   try
   {
      DString brokerCode, branchCode;
   
      getParent()->getField(this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
         ifds::SearchFieldCriteria1, brokerCode);
      if (shouldSetTheCaller())
      {
         setParameter(MFCAN_IP_PARAM::CALLER, I_("PaymentInstructions"));
      }
      setParameter(MFCAN_IP_PARAM::BROKER_CODE, brokerCode);
      eRtn = invokeCommand(getParent(), 
         CMD_BPROC_BRANCH, PROC_SUPPORT, true, NULL);
      switch(eRtn)
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               getParameter(MFCAN_IP_PARAM::BRANCH_CODE, branchCode);
               if(branchCode != NULL_STRING)
               {
                  getParent()->setField(this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
                     ifds::SearchFieldCriteria2, branchCode);
               }
               LoadControl(getBranchEditControlId());
               break;
            }
         case CMD_CANCEL:
            break;
         default:
            // Display error
            ConditionMessageBox(FRAMEBELOW(), GETHIGHESTSEVERITY());
            break;
      }
   }
   catch(ConditionException &ce)
   {
      ConditionMessageBox(ce);
   }
   catch(...)
   {
      DISPLAYCONDITIONFROMFILE(CND::GUI_ERR_UNKNOWN_EXCEPTION);
   }
   return eRtn;
}

//******************************************************************
LRESULT FeaturesSearchDlg::OpenSlsRepListDlg(WPARAM, LPARAM) 
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OpenSlsRepListDlg"));
   E_COMMANDRETURN eRtn = CMD_CANCEL;
   CWaitCursor wait;

   try
   {
      DString brokerCode, branchCode;
   
      getParent()->getField(this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
         ifds::SearchFieldCriteria1, brokerCode);
      getParent()->getField(this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
         ifds::SearchFieldCriteria2, branchCode);
      if (shouldSetTheCaller())
      {
         setParameter(MFCAN_IP_PARAM::CALLER, I_("PaymentInstructions"));
      }
      setParameter(MFCAN_IP_PARAM::BROKER_CODE, brokerCode);
      setParameter(MFCAN_IP_PARAM::BRANCH_CODE, branchCode);
      eRtn = invokeCommand(getParent(), 
            CMD_BPROC_SLSREP, PROC_SUPPORT, true, NULL);
      switch (eRtn)
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               DString slsrepCode;

               getParameter(MFCAN_IP_PARAM::SALES_REP_CODE, slsrepCode);
               if(slsrepCode != NULL_STRING)
               {
                  getParent()->setField(this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
                     ifds::SearchFieldCriteria3, slsrepCode);
               }
               LoadControl(getSlsRepEditControlId());
               break;
            }
         case CMD_CANCEL:
            break;
         default:
            // Display error
            ConditionMessageBox(FRAMEBELOW(), GETHIGHESTSEVERITY());
            break;
      }
   }
   catch(ConditionException &ce)
   {
      ConditionMessageBox(ce);
   }
   catch(...)
   {
      DISPLAYCONDITIONFROMFILE(CND::GUI_ERR_UNKNOWN_EXCEPTION);
   }
   return(eRtn);
}

//******************************************************************
LRESULT FeaturesSearchDlg::OpenFeeModelDlg(WPARAM, LPARAM) 
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OpenSlsRepListDlg"));
   E_COMMANDRETURN eRtn = CMD_CANCEL;
   CWaitCursor wait;

   try
   {
      DString dstrParamsIDI;
      addIDITagValue (dstrParamsIDI, MFCAN_IP_PARAM::SEARCH_TYPE, 
      SEARCH_TYPE::SYSTEM );

      eRtn = invokeCommand(getParent(), 
            CMD_BPROC_FEE_MODEL, PROC_SUPPORT, true, NULL);
      switch (eRtn)
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               DString feeModeCode;

               getParameter(MFCAN_IP_PARAM::FEE_MODEL_CODE, feeModeCode);
               if(feeModeCode != NULL_STRING)
               {
                  getParent()->setField(this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
                     ifds::SearchFieldCriteria1, feeModeCode);
               }
               LoadControl(getFeeModelEditControlId());
               break;
            }
         case CMD_CANCEL:
            break;
         default:
            // Display error
            ConditionMessageBox(FRAMEBELOW(), GETHIGHESTSEVERITY());
            break;
      }
   }
   catch(ConditionException &ce)
   {
      ConditionMessageBox(ce);
   }
   catch(...)
   {
      DISPLAYCONDITIONFROMFILE(CND::GUI_ERR_UNKNOWN_EXCEPTION);
   }
   return(eRtn);
}

//******************************************************************
LRESULT FeaturesSearchDlg::OpenFundListDlg(WPARAM, LPARAM)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenFundListDlg" ) );

   E_COMMANDRETURN eRtn = CMD_CANCEL;
   CWaitCursor wait;

   try
   {
      if (m_pWndItemInFocus == GetDlgItem (IDC_EDT_SEARCH32)) 
      {
         DString fundCode;

         GetControlText (IDC_EDT_SEARCH32, fundCode);
         setParameter (I_("FundCode"), fundCode);
      } 
      else if (m_pWndItemInFocus == GetDlgItem (IDC_EDT_SEARCH33))
      {
         DString classCode;

         GetControlText (IDC_EDT_SEARCH33, classCode);
         setParameter (I_("ClassCode"), classCode);
      }
      //invoke the fund class dialog and process
      SetMessageStatusBar (TXT_LOAD_FUND_INFO);
      eRtn = invokeCommand( getParent(), 
								    CMD_BPROC_FUNDCLASS, 
								    PROC_SUPPORT, 
									 true, 
									 NULL );
      switch (eRtn)
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               DString dstrFundCode, 
                       dstrClassCode;

               getParameter (I_("FundCode"), dstrFundCode);
               getParent()->setField ( this, 
                                       IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
                                       ifds::SearchFieldCriteria2, 
                                       dstrFundCode);
               getParameter (I_("ClassCode"), dstrClassCode);
               getParent()->setField ( this, 
                                       IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
                                       ifds::SearchFieldCriteria3, 
                                       dstrClassCode);
               LoadControl (IDC_EDT_SEARCH32);
               LoadControl (IDC_EDT_SEARCH33);
               break;
            }
         case CMD_CANCEL:
            break;
         default:
            // Display error
            ConditionMessageBox (FRAMEBELOW(), GETHIGHESTSEVERITY());
            SetMessageStatusBar (NULL_STRING);
            break;
      }
      SetMessageStatusBar (NULL_STRING);
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch (...)
   {
      DISPLAYCONDITIONFROMFILE (CND::GUI_ERR_UNKNOWN_EXCEPTION);
   }
   return eRtn;
}

LRESULT FeaturesSearchDlg::OpenFndBrkrListDlg(WPARAM, LPARAM)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenFndBrkrListDlg" ) );
   E_COMMANDRETURN eRtn = CMD_CANCEL;
   CWaitCursor wait;
   
   try
   {
      setParameter(MFCAN_IP_PARAM::CALLER, I_("AggregatedOrders"));
      eRtn = invokeCommand( getParent(), CMD_BPROC_BROKER, PROC_SUPPORT, true, NULL);
      
      switch (eRtn)
      {
      
         case CMD_OK:
         {
            DString dstrFundBrokerCode;
            
            m_pWndItemInFocus = GetFocus();
            getParameter(MFCAN_IP_PARAM::BROKER_CODE, dstrFundBrokerCode); 
            
            if ( m_pWndItemInFocus == GetDlgItem(IDC_EDT_SEARCH33))
            {
               getParent()->setField(this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
                        ifds::SearchFieldCriteria3, dstrFundBrokerCode);
               LoadControl( IDC_EDT_SEARCH33 );
            }
            else if ( m_pWndItemInFocus == GetDlgItem(IDC_EDT_SEARCH41))
            {
               getParent()->setField(this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
                        ifds::SearchFieldCriteria4, dstrFundBrokerCode);
               LoadControl( IDC_EDT_SEARCH41 );
            }
     
            break;
         }
          
         case CMD_MODELESS_INPROCESS:
            break;
         case CMD_CANCEL:
            break;
         default:
            
            break;
      }
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch (...)
   {
      DISPLAYCONDITIONFROMFILE (CND::GUI_ERR_UNKNOWN_EXCEPTION);
   }
   return eRtn;
}

//*************************************************************************
bool FeaturesSearchDlg::isBrokerSearchField()
{
   DString isSearchCriteria1Broker;

   getParent()->getField(this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
         IsBFSearchCriteria1Broker, isSearchCriteria1Broker);
   m_pWndItemInFocus = GetFocus();
   return isSearchCriteria1Broker == I_("Y") &&
      (m_pWndItemInFocus == GetDlgItem(IDC_EDT_SEARCH11) ||
         m_pWndItemInFocus == GetDlgItem(IDC_EDT_SEARCH21) ||
         m_pWndItemInFocus == GetDlgItem(IDC_EDT_SEARCH31));
}

//*************************************************************************
bool FeaturesSearchDlg::isBranchSearchField()
{
   DString isSearchCriteria2Branch;

   getParent()->getField(this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
         IsBFSearchCriteria2Branch, isSearchCriteria2Branch);
   m_pWndItemInFocus = GetFocus();
   return isSearchCriteria2Branch == I_("Y") && 
      (m_pWndItemInFocus == GetDlgItem(IDC_EDT_SEARCH22) ||
         m_pWndItemInFocus == GetDlgItem(IDC_EDT_SEARCH32));
}

//*************************************************************************
bool FeaturesSearchDlg::isSlsRepSearchField()
{
   DString isSearchCriteria3SlsRep;

   getParent()->getField(this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
         IsBFSearchCriteria3SlsRep, isSearchCriteria3SlsRep);
   m_pWndItemInFocus = GetFocus();
   return isSearchCriteria3SlsRep == I_("Y") && 
      m_pWndItemInFocus == GetDlgItem(IDC_EDT_SEARCH33);
}

//*************************************************************************
bool FeaturesSearchDlg::isFundCodeSearchField()
{
   DString isSearchCriteria2Fund;

   getParent()->getField(this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
         IsDTFSearchCriteria2Fund, isSearchCriteria2Fund);
   m_pWndItemInFocus = GetFocus();
   return isSearchCriteria2Fund == I_("Y") &&
      (m_pWndItemInFocus == GetDlgItem(IDC_EDT_SEARCH32));
}

//*************************************************************************
bool FeaturesSearchDlg::isClassCodeSearchField()
{
   DString isSearchCriteria3Class;

   getParent()->getField(this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
         IsDTFSearchCriteria3Class, isSearchCriteria3Class);
   m_pWndItemInFocus = GetFocus();
   return isSearchCriteria3Class == I_("Y") &&
      (m_pWndItemInFocus == GetDlgItem (IDC_EDT_SEARCH33));
}

//*************************************************************************
bool FeaturesSearchDlg::isFeeModelSearchField()
{
   DString isSearchCriteria1FeeModel;

   getParent()->getField(this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
         IsFMSearchCriteriaFeeModel, isSearchCriteria1FeeModel);
   m_pWndItemInFocus = GetFocus();
   return isSearchCriteria1FeeModel == I_("Y") && ( m_pWndItemInFocus == GetDlgItem(IDC_EDT_SEARCH11) );
}

//*************************************************************************
bool FeaturesSearchDlg::isSponsorSearchField()
{
   DString isSearchCriteria1Sponsor;

   getParent()->getField(this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
         IsFMSearchCriteriaSponsor, isSearchCriteria1Sponsor);
   m_pWndItemInFocus = GetFocus();
   return isSearchCriteria1Sponsor == I_("Y") &&
      (  m_pWndItemInFocus == GetDlgItem(IDC_EDT_SEARCH21) ||
         m_pWndItemInFocus == GetDlgItem(IDC_EDT_SEARCH31));
}

//*************************************************************************
bool FeaturesSearchDlg::isFndBrkrForAggregatedOrderSearchField()
{
   m_pWndItemInFocus = GetFocus();
   if ( m_pWndItemInFocus == GetDlgItem(IDC_EDT_SEARCH33))
   {
      DString isSearchCriteriaAggregationStatus;
      
      getParent()->getField(this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
         isFMSearchCriteriaAggregationStatus, isSearchCriteriaAggregationStatus);
         
      return isSearchCriteriaAggregationStatus == I_("Y") && 
             m_pWndItemInFocus == GetDlgItem(IDC_EDT_SEARCH33); 
   }
   else if( m_pWndItemInFocus == GetDlgItem(IDC_EDT_SEARCH41))
   {
      DString isSearchCriteriaAggregationTradeDate;
      
      getParent()->getField(this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
         isFMSearchCriteriaAggregationTradeDate, isSearchCriteriaAggregationTradeDate);
         
      return isSearchCriteriaAggregationTradeDate == I_("Y") && 
             m_pWndItemInFocus == GetDlgItem(IDC_EDT_SEARCH41); 
   }
   return false;     
}

//*************************************************************************
/*
bool FeaturesSearchDlg::isAggregatedOrderSearchField()
{
   DString isSearchCriteria1AggregationAggrOrdNo;

   getParent()->getField(this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
         isFMSearchCriteriaAggregationAggrOrdNo, isSearchCriteria1AggregationAggrOrdNo);
   m_pWndItemInFocus = GetFocus();
   return isSearchCriteria1AggregationAggrOrdNo == I_("Y") &&
      (  m_pWndItemInFocus == GetDlgItem(IDC_EDT_SEARCH21) ||
         m_pWndItemInFocus == GetDlgItem(IDC_EDT_SEARCH31));
}
*/
//******************************************************************
void FeaturesSearchDlg::getBrokerFieldId(BFFieldId &brokerId)
{
   brokerId = ifds::SearchFieldCriteria1;
}

//*************************************************************************
UINT FeaturesSearchDlg::getBrokerEditControlId()
{
   UINT brokerEditId = (UINT)0;
   DString isSearchCriteria1Broker;

   getParent()->getField(this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
         IsBFSearchCriteria1Broker, isSearchCriteria1Broker);
   if (isSearchCriteria1Broker == I_("Y"))
   {
      DString howManySearchCriterias;

      getParent()->getField(this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
         ifds::HowManySearchCriterias, howManySearchCriterias);
      if (howManySearchCriterias == I_("1"))
      {
         brokerEditId = IDC_EDT_SEARCH11;
      }
      else if (howManySearchCriterias == I_("2"))
      {
         brokerEditId = IDC_EDT_SEARCH21;
      }
      else if (howManySearchCriterias == I_("3"))
      {
         brokerEditId = IDC_EDT_SEARCH31;
      }
   }
   return brokerEditId;
}

//*************************************************************************
UINT FeaturesSearchDlg::getBranchEditControlId()
{
   UINT branchEditId = (UINT)0;
   DString isSearchCriteria2Branch;

   getParent()->getField(this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
         IsBFSearchCriteria2Branch, isSearchCriteria2Branch);
   if (isSearchCriteria2Branch == I_("Y"))
   {
      DString howManySearchCriterias;

      getParent()->getField(this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
         ifds::HowManySearchCriterias, howManySearchCriterias);
      if (howManySearchCriterias == I_("2"))
      {
         branchEditId = IDC_EDT_SEARCH22;
      }
      else if (howManySearchCriterias == I_("3"))
      {
         branchEditId = IDC_EDT_SEARCH32;
      }
   }
   return branchEditId;
}

//*************************************************************************
UINT FeaturesSearchDlg::getSlsRepEditControlId()
{
   UINT slsRepEditId = (UINT)0;
   DString isSearchCriteria3SlsRep;

   getParent()->getField(this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
         IsBFSearchCriteria3SlsRep, isSearchCriteria3SlsRep);
   if (isSearchCriteria3SlsRep == I_("Y"))
   {
      DString howManySearchCriterias;

      getParent()->getField(this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
         ifds::HowManySearchCriterias, howManySearchCriterias);
      if (howManySearchCriterias == I_("3"))
      {
         slsRepEditId = IDC_EDT_SEARCH33;
      }
   }
   return slsRepEditId;
}

//*************************************************************************
UINT FeaturesSearchDlg::getFeeModelEditControlId()
{
   UINT feeModelEditId = (UINT)0;
   DString isSearchCriteriaFeeModel;

   getParent()->getField(this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
         IsFMSearchCriteriaFeeModel, isSearchCriteriaFeeModel);
   if (isSearchCriteriaFeeModel == I_("Y"))
   {
      DString howManySearchCriterias;

      getParent()->getField(this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
         ifds::HowManySearchCriterias, howManySearchCriterias);
      if (howManySearchCriterias == I_("1"))
      {
         feeModelEditId = IDC_EDT_SEARCH11;
      }
   }
   return feeModelEditId;
}

//*************************************************************************
UINT FeaturesSearchDlg::getAggFndBrkrEditControlId()
{
   UINT AggFndBrkrModelEditId = (UINT)0;
   
   DString isSearchCriteriaAggregationTradeDate;
   
   getParent()->getField(this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      isFMSearchCriteriaAggregationTradeDate, isSearchCriteriaAggregationTradeDate);
   
   if ( isSearchCriteriaAggregationTradeDate == I_("Y") )
   {
      DString howManySearchCriterias;

      getParent()->getField(this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
         ifds::HowManySearchCriterias, howManySearchCriterias);
         
      if (howManySearchCriterias == I_("2"))
      {
         AggFndBrkrModelEditId = IDC_EDT_SEARCH33;
      }   
      else if (howManySearchCriterias == I_("7"))
      {
         AggFndBrkrModelEditId = IDC_EDT_SEARCH41;
      }   
       
   }

   return AggFndBrkrModelEditId;
}
//*************************************************************************
bool FeaturesSearchDlg::discardUpdates()
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("discardUpdates"));
   bool bCanSearch = true;
   
   BFWorkSession *bfWorkSession = getBFWorkSession();

   if (bfWorkSession && bfWorkSession->hasNonHostUpdates())
   {
      DiscardMsgDlg discardDlg(NULL, TXT_DISCARD_MSGA, 
         TXT_DISCARD_MSGB, TXT_DISCARD);
      
      if (discardDlg.DoModal() == IDCANCEL)
      {
         bCanSearch = false;
      }
      else 
      {
         //discard everything and close the dialogs
         getGIContainer()->destroyGUIChildren(this);
      }
   }
//clean-up the work session before each search, even if there are no updates
   if (bCanSearch && bfWorkSession)
   {
      bfWorkSession->cleanupWorkSession();
   }
   return bCanSearch;
}

//*************************************************************************
bool FeaturesSearchDlg::shouldSetTheCaller()
{
   DString searchCriteria;

   getParent()->getField(this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      ifds::SearchCriteria, searchCriteria, false);

   return searchCriteria == BF_SEARCH_CRITERIA::PAY_TO_ENTITY ||
      searchCriteria == BF_SEARCH_CRITERIA::PAYMENT_INSTRUCTIONS;
}

//*************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/FeaturesSearchDlg.cpp-arc  $
// 
//    Rev 1.20   Jan 20 2011 07:17:50   wichian
// IN#2319580 - Updated code according to code review 579300 w/o
// 
//    Rev 1.18   Mar 26 2009 01:49:14   kitticha
// IN#1588682 - Small Enhancement - Feature search screen for Fund Broker Search. Code review.
// 
//    Rev 1.17   Mar 25 2009 07:22:08   kitticha
// IN#1588682 - Small Enhancement - Feature search screen for Fund Broker Search.
// 
//    Rev 1.16   Sep 15 2005 15:12:02   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.15   Jan 14 2005 14:08:04   zhangcel
// PTS Ticket 10037813 -- Reload FromDate and ToDate to solve display issue.
// 
//    Rev 1.14   Dec 15 2004 19:01:40   zhangcel
// PET1117 - FN 08 -- Bug fix for FromDate and ToDate control grey out
// 
//    Rev 1.13   Dec 09 2004 14:53:42   hernando
// PET910 - Changed location of setUpdateFlag to prevent discard message from popping-up.
// 
//    Rev 1.12   Dec 08 2004 19:37:22   hernando
// PET910 - Disconnected Date Control from common used field (appropriately) to prevent crashing.
// 
//    Rev 1.11   Dec 06 2004 11:17:50   Fengyong
// do not show IDC_CMB_SEARCH33 for first search option,
// Celia need change specific for her case by add options.
// 
//    Rev 1.10   Nov 26 2004 19:08:14   Fengyong
// change fund broker code select from combo to edit box
// 
//    Rev 1.9   Nov 26 2004 14:49:10   zhangcel
// PET1117/FN8 -- Aggregated Order related changes
// 
//    Rev 1.8   Nov 05 2004 15:42:50   ZHANGCEL
// PET1117/08 Add sreaching logic for AggregatedOrder
// 
//    Rev 1.7   Oct 19 2004 14:40:30   FENGYONG
// PET1117 FN54 - Fund Broker Static
// 
//    Rev 1.6   Oct 15 2004 16:06:26   FENGYONG
// PTS10034766 - disable add and delete when access FeeModel from fundsponsor fee model screen.
// 
//    Rev 1.5   Aug 10 2004 11:28:12   FENGYONG
// PET 1117 FN5 - Client Condition Fee
// 
//    Rev 1.4   Feb 27 2004 11:50:36   popescu
// PET859 FN23 - ADL - fixed crash when refresh after a Fund/Class search for ADL fee.
// 
//    Rev 1.3   Feb 18 2004 18:14:04   popescu
// PTS 10027184, synch-up release 55.0.2, version 1.0.1.0
// 
//    Rev 1.2   Feb 03 2004 16:36:08   VADEANUM
// PET 859 FN23 - ADL - removed Fee search param
// 
//    Rev 1.1   Jan 28 2004 21:35:30   popescu
// PET 859, FN 23, modified resources (dialogs and menu item) and coded for the features search dialog
// 
//    Rev 1.0   Oct 04 2003 16:10:34   popescu
// Initial revision.
// 
//    Rev 1.8   Aug 20 2003 19:50:56   popescu
// PTS 10020922,
// the payment instructions screen is launched as modal and as support from pay to entity. This will ensure that all transactions in payment instructions will be commited to the parent group id and will be sent after the pay to entity transactions are sent
// 
//    Rev 1.7   Jul 29 2003 15:25:30   popescu
// Check if there are updates before cancelling the dialog/diasbled the update flag at the dialog level
// 
//    Rev 1.6   Jul 29 2003 14:19:36   popescu
// Fixes regarding the Discard/Cancel dialog
// 
//    Rev 1.5   Jul 11 2003 18:35:36   popescu
// no need to check for end confirmation, any more
// 
//    Rev 1.4   Jul 10 2003 22:21:32   popescu
// check in for payment instruct, used mfcan_ip_param for some interporcess param passing
// 
//    Rev 1.3   Jul 09 2003 21:57:30   popescu
// Payment Instructiuons work, business rules implementation SSB_PET_821_FN17
// 
//    Rev 1.2   Jul 02 2003 17:49:52   popescu
// work for payment instructions feature 
// 
//    Rev 1.1   Jul 01 2003 18:05:00   popescu
// Added the discard/cancel dialog if user clicks search again; changed the children processes to modeless, instead of modal
// 
//    Rev 1.0   Jun 27 2003 18:18:08   popescu
// Initial revision.
 * 
*/

