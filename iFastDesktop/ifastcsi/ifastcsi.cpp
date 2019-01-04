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
//    Copyright 2000 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : ifastcsi.cpp
// ^AUTHOR : 
// ^DATE   : 
// ^CLASS    : ifastcsi
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : implementation of the DstcCsi class.
//
//******************************************************************************

//#define DTEST
#define STANDARD_TIMEOUT 30000

#include "ifastcsi.h"
#include "CsiSession.h"
#include <tesession\TESession.h>

#include "DcMenu.h"
#include "DcMenuItem.h"
#include "DcInputScreen.h"
#include "DcInputField.h"
#include "DcListScreen.h"
#include "DcListColumn.h"
#include "CsiIdentifier.h"

using namespace DcCsiProcesses;
using namespace DcCsiParameters;

//******************************************************************************
void DstcCsi::RegisterProcesses()
{
   try
   {
      CsiSession &session = CsiSession::getInstance();

      session.registerPresetProcess(preset);
      session.registerResetProcess(reset);

      session.registerProcess( MASTER_MENU,                  MasterMenu );
      session.registerProcess( ACCOUNT_INFORMATION,          AccountInformation );
      session.registerProcess( AUTOMATIC_TRANSFER_INFO,      AutomaticTransferInfo );
      session.registerProcess( BASIC_SHARE_HOLDER,           BasicShareholder );
      session.registerProcess( HISTORICAL_ACCOUNT_INFO,      HistoricalAccountInfo );
      session.registerProcess( BANK_INFORMATION_MENU,        BankInformationMenu );
      session.registerProcess( BANK_INFORMATION,             BankInformation );
      session.registerProcess( PAC_INFORMATION,              PACInformation );
      session.registerProcess( SWP_INFORMATION,              SWPInformation );
      session.registerProcess( PAC_ALLOCATION,               PACAllocation );
      session.registerProcess( SWP_ALLOCATION,               SWPAllocation );
      session.registerProcess( ALLOCATIONS,                  Allocations );
      session.registerProcess( TRANSACTION,                  Transaction );
      session.registerProcess( SHAREHOLDER_REMARKS,          ShareholderRemarks );
      session.registerProcess( DEMOGRAPHIC_INFO,             DemographicInfo );
      session.registerProcess( TRANSACTION_PROCESSING_MENU,  TransactionProcessingMenu );
      session.registerProcess( SETTLEMENTS,                  Settlements );
      session.registerProcess( ORDERS_PROCESSED,             OrdersProcessed );
      session.registerProcess( ADDRESS_INFORMATION,          AddressInformation );
      session.registerProcess( ADDRESS_ASSIGNMENTS,          AddressAssignments );
      session.registerProcess( ACCOUNT_ENTITY_RELATIONSHIP,  AccountEntityRelationship );
      session.registerProcess( BRANCH_INFORMATION,           BranchInformation );
      session.registerProcess( BROKER_INFORMATION,           BrokerInformation );
      session.registerProcess( SALES_REP_INFORMATION,        SalesRepInformation );
      session.registerProcess( WHERE_USED,                   WhereUsed );
      session.registerProcess( ENTITY_MAINTAINANCE,          EntityMaintainance );
      session.registerProcess( NEW_SHAREHOLDER,              NewShareholder );
      session.registerProcess( FUNDVALUE_TRADE_OR_FUND,      FundValueByTradeOrByFund );

      session.registerProcess( ADD_DISTRIBUTION_INFO,        AddDistributionInfo );
      session.registerProcess( DISTRIBUTION_INFO,            DistributionInfo );
      session.registerProcess( CERTIFICATE_INFO,             CertificateInfo );
      session.registerProcess( DISTRIBUTION_ADD,             DistributionAdd );
      session.registerProcess( CHOOSE_MANAGE_COMP,           ChooseManageComp );

      session.registerProcess( LOCKED_IN_INFORMATION,        LockedInformation );
      session.registerProcess( RESP_INFORMATION,             RespInformation );
      session.registerProcess( RESP_TRANS_INFORMATION,       RespTransInformation );

      session.registerProcess( GUARANTEE_TRANSACTION,        GuaranteeTransaction );
      session.registerProcess( CONTRACT_INFORMATION,         ContractInformation );

      session.registerProcess( LIF_INFO_PROCESS,             LIFInformation );
      session.registerProcess( RRIF_INFO_PROCESS,            RRIFInformation );
      session.registerProcess( LRIF_INFO_PROCESS,            LRIFInformation );

      session.registerProcess(LIF_ALLOCATION_PROCESS,       LIFAllocation );
      session.registerProcess(RRIF_ALLOCATION_PROCESS,      RRIFAllocation );
      session.registerProcess(LRIF_ALLOCATION_PROCESS,      LRIFAllocation );

      session.registerProcess(HYPO_REDEMPTION_PROCESS,      HypoRedemptionInfo );

      session.registerProcess(TAX_RATE_INFORMATION,         TaxRateInformation );
      session.registerProcess(PATCH_ORDER_ENTRY_INFO,       PatchOrderEntryInformation ); 
      session.registerProcess(AMS_GLOBAL_ALLOCATION,        AmsGlobalAllocation);
      session.registerProcess(REDEMPTION_DETAIL,            RedemptionDetail );
		session.registerProcess(YTD_CONTRIBUTION,             YTDContribution );
   }
   catch( CsiException &e )
   {
      DSystem::userMessage(e.getMessage(), "International Financial Data Service Csi");
   }
}

//******************************************************************************
void DstcCsi::RegisterScreens()
{

   try
   {
      CsiSession &session = CsiSession::getInstance();
      CsiScreen *screen;

      screen = new DcMenu("RTE Menu", 37);
//      screen->addComponent(new DcMenuItem("Execute Application"));
      screen->addComponent(new CsiIdentifier("Menu Header", "RTE MENU", tes::POSITION_ANY, 37));
      screen->addComponent(new CsiIdentifier("Menu Trailer", "\x0e\x12\x12\x12\x12\x12\x12", tes::POSITION_ANY, 31));
//      screen->addComponent(new CsiIdentifier("Name", 23, 32));
//      screen->addComponent(new CsiIdentifier("eXit", 23, 2));
      session.registerScreen(screen);

      screen = new DcMenu("Master Menu", 29);
//      screen->addComponent(new DcMenuItem("Accountholder Information"));
//      screen->addComponent(new DcMenuItem("Transaction Processing"));
      screen->addComponent(new CsiIdentifier("Menu Header", "Master Menu", tes::POSITION_ANY, 35));
      screen->addComponent(new CsiIdentifier("Menu Trailer", "\x0e\x12\x12\x12\x12\x12\x12", tes::POSITION_ANY, 23));
      screen->addComponent(new CsiIdentifier("Select Menu Choice", 24, 1));
      session.registerScreen(screen);


      screen = new DcInputScreen("Logon Screen");
      screen->addComponent(new DcInputField(USER_ID, 20, 42, 1));
      screen->addComponent(new DcInputField(PASSWORD, 21 ,42, 2));
      screen->addComponent(new DcInputField(CHANGE_PASSWORD, 23, 42, 3));
      screen->addComponent(new CsiIdentifier("Logon", 19, 35));
      session.registerScreen(screen);

      screen = new DcInputScreen("Account Lookup");
      screen->addComponent(new DcInputField(ACCOUNT_NUMBER, 4, 45, 1));
      screen->addComponent(new DcInputField(ENTITY_NAME, 5, 30, 2));
      screen->addComponent(new DcInputField(BIRTH_NAME, 6, 30, 3));
      screen->addComponent(new DcInputField(SIN_NUMBER, 8, 30, 5));
      screen->addComponent(new CsiIdentifier("Select A Shareholder", 2, 10));
      session.registerScreen(screen);

      screen = new CsiScreen("Account Information");
      screen->addComponent(new CsiIdentifier("Shareholder:", 2, 3));
      session.registerScreen(screen);

      screen = new DcMenu("Activity Menu", 20,40); 
      screen->addComponent(new CsiIdentifier("Menu Header", "Activity Menu", 1,10,2,50 ));
      screen->addComponent(new CsiIdentifier("Menu Trailer", "\x0e\x12\x12\x12\x12\x12\x12", 15,10,25,50));
      {
         CsiScreen *moreScreen = new DcMenu("More Menu", 20,40); //25);
         moreScreen->addComponent(new CsiIdentifier("Menu Header", "Activity Menu (continued)", 1,10,5,50) );  //tes::POSITION_ANY, 25));
         moreScreen->addComponent(new CsiIdentifier("Menu Trailer", "\x0e\x12\x12\x12\x12\x12\x12", 6,10,24,50) ); //tes::POSITION_ANY, 19));
         screen->addComponent(moreScreen);
      }
      screen->addComponent(new CsiIdentifier("Select Menu Choice", 24, 1));
      session.registerScreen(screen);

      screen = new DcMenu("Account Options Menu", 20,40); //25 change to rec yingbao
//      screen->addComponent(new DcMenuItem("Banking Information"));
//      screen->addComponent(new DcMenuItem("Shareholder Remarks"));
//      screen->addComponent(new DcMenuItem("Demographic Data"));
      screen->addComponent(new CsiIdentifier("Menu Header", "Account Options Menu", 1,10,5,50) ) ;//tes::POSITION_ANY, 31));
      screen->addComponent(new CsiIdentifier("Menu Trailer", "\x0e\x12\x12\x12\x12\x12\x12", 15,10,25,50) );//tes::POSITION_ANY, 19));
      {
         CsiScreen *moreScreen = new DcMenu("More Menu", 20,40); //25);
         moreScreen->addComponent(new CsiIdentifier("Menu Header", "Account Options Menu (continued)", 8,10,20,50) );  //tes::POSITION_ANY, 25));
         moreScreen->addComponent(new CsiIdentifier("Menu Trailer", "\x0e\x12\x12\x12\x12\x12\x12", 19,10,24,50) ); //tes::POSITION_ANY, 19));
         screen->addComponent(moreScreen);
      }
      session.registerScreen(screen);

      screen = new DcMenu("Banking Information Menu", 32);
//      screen->addComponent(new DcMenuItem("P.A.C. Information"));
//      screen->addComponent(new DcMenuItem("S.W.P. Information"));
//      screen->addComponent(new DcMenuItem("Bank Accounts"));
      screen->addComponent(new CsiIdentifier("Menu Header", "Banking Information", tes::POSITION_ANY, 31));
      screen->addComponent(new CsiIdentifier("Menu Trailer", "\x0e\x12\x12\x12\x12\x12\x12", tes::POSITION_ANY, 26));
      session.registerScreen(screen);

      screen = new DcListScreen("Banking Information List", 6, 20);
      screen->addComponent(new DcListColumn(BANK_ACCOUNT_NUMBER, 3));
      screen->addComponent(new CsiIdentifier("Banking Information", 3, tes::POSITION_ANY));
      session.registerScreen(screen);

      screen = new CsiScreen("PAC Information");
      screen->addComponent(new CsiIdentifier("P.A.C. (Debit) Information", 2, 28));
      session.registerScreen(screen);

      screen = new CsiScreen("SWP Information");
      screen->addComponent(new CsiIdentifier("S.W.P. (Credit) Information", 2, 27));
      session.registerScreen(screen);

      screen = new CsiScreen("Allocations");
      screen->addComponent(new CsiIdentifier("Allocations for Shareholder:", 3, tes::POSITION_ANY));
      session.registerScreen(screen);

      screen = new CsiScreen("Remarks");
      screen->addComponent(new CsiIdentifier("Remarks", 5, 37));
      session.registerScreen(screen);

      screen = new CsiScreen("Demographic Information");
      screen->addComponent(new CsiIdentifier("Current Demographic Information", 2, 25));
      session.registerScreen(screen);

/*
      screen = new DcListScreen("Funds Available", 6, 20);
      screen->addComponent(new DcListColumn(FUND, 9));
      screen->addComponent(new DcListColumn(CLASS, 14));
      screen->addComponent(new CsiIdentifier("Menu Header", "Funds Available", tes::POSITION_ANY, 35));
      screen->addComponent(new CsiIdentifier("Menu Trailer", "\x0e\x12\x12\x12\x12\x12\x12", tes::POSITION_ANY, 8));
      session.registerScreen(screen);
*/

      screen = new DcMenu("Transaction Processing Menu",25);
//      screen->addComponent(new DcMenuItem("Orders Processed"));
//      screen->addComponent(new DcMenuItem("Settlements"));
      screen->addComponent(new CsiIdentifier("Menu Header", "Transaction Processing",tes::POSITION_ANY, 30));
      screen->addComponent(new CsiIdentifier("Menu Trailer", "\x0e\x12\x12\x12\x12\x12\x12",tes::POSITION_ANY, 19));
      screen->addComponent(new CsiIdentifier("Select Menu Choice", 24, 1));
      session.registerScreen(screen);		

      screen = new DcMenu("Settlements Menu", 20,30); //26);
      screen->addComponent(new CsiIdentifier("Menu Header", "Settlements", 1,20,4,50) );//tes::POSITION_ANY, 35));
      screen->addComponent(new CsiIdentifier("Menu Trailer", "\x0e\x12\x12\x12\x12\x12\x12",4,10,35,50) ); //tes::POSITION_ANY, 20));
      screen->addComponent(new CsiIdentifier("Select Menu Choice", 24, 1));
      session.registerScreen(screen);

      screen = new CsiScreen("Orders Processed");
      screen->addComponent(new CsiIdentifier("Orders Processed", 2, 33));
      session.registerScreen(screen);

      screen = new CsiScreen("Address Information");
      screen->addComponent(new CsiIdentifier("Address Information", tes::POSITION_ANY, 31));
      session.registerScreen(screen);

      screen = new CsiScreen("Address Assignments");
      screen->addComponent(new CsiIdentifier("Account:", 4, tes::POSITION_ANY));
      screen->addComponent(new CsiIdentifier("Address Assignments", 4, tes::POSITION_ANY));
      session.registerScreen(screen);

      screen = new CsiScreen("Account / Entity Relationship Information");
      screen->addComponent(new CsiIdentifier("Account / Entity Relationship Information", 2, 20));
      session.registerScreen(screen);

      screen = new DcMenu("Fund Information Menu", 20,35);  //new added on Nov. 29,99
      screen->addComponent(new CsiIdentifier("Menu Header", "Fund Information ", 1,15,2,50) );   
      screen->addComponent(new CsiIdentifier("Menu Trailer", "\x0e\x12\x12\x12\x12\x12\x12", 3, 15,23,50) );   
      screen->addComponent(new CsiIdentifier("Select Menu Choice", tes::POSITION_ANY, 1) );  
      session.registerScreen(screen);

      screen = new CsiScreen("Unit Values"); // new added on Nov. 29, 99      
      session.registerScreen(screen);

      screen = new DcMenu("Fund and Broker Information Menu", 20,30);  //26);
      screen->addComponent(new CsiIdentifier("Menu Header", "Fund and Broker Information", 1,15,3,50) );   //tes::POSITION_ANY, 27));
      screen->addComponent(new CsiIdentifier("Menu Trailer", "\x0e\x12\x12\x12\x12\x12\x12", 3, 15,23,50) );   //tes::POSITION_ANY, 20));
      screen->addComponent(new CsiIdentifier("Select Menu Choice", tes::POSITION_ANY, 1) );  //24,1
      session.registerScreen(screen);

      screen = new DcMenu("Broker Information Menu", 26);
      screen->addComponent(new CsiIdentifier("Menu Header", "Broker Information", tes::POSITION_ANY, 31));
      screen->addComponent(new CsiIdentifier("Menu Trailer", "\x0e\x12\x12\x12\x12\x12\x12", tes::POSITION_ANY, 20));
      screen->addComponent(new CsiIdentifier("Select Menu Choice", 24, 1));
      session.registerScreen(screen);

      screen = new DcListScreen("Broker Information List", 5, 20);
      screen->addComponent(new DcListColumn(BROKER_NUMBER, 28));
      screen->addComponent(new CsiIdentifier("Broker Information", 2, 31));
      session.registerScreen(screen);

      screen = new DcListScreen("Choose Broker List", 5, 20);
      screen->addComponent(new DcListColumn(BROKER_NUMBER, 28));
      screen->addComponent(new CsiIdentifier("Choose Broker", 2, 34));
      session.registerScreen(screen);

      screen = new DcMenu("Broker Select By Menu", 32);
      screen->addComponent(new CsiIdentifier("Menu Header", "Select BY", tes::POSITION_ANY, 36));
      screen->addComponent(new CsiIdentifier("Menu Trailer", "\x0e\x12\x12\x12\x12\x12\x12", tes::POSITION_ANY, 27));
      session.registerScreen(screen);

      screen = new DcInputScreen("Broker Lookup By Broker Code");
      screen->addComponent(new DcInputField(BROKER_NUMBER, 8, 43, 1));
      screen->addComponent(new CsiIdentifier("Broker   :", 8, 32));
//      screen->addComponent(new CsiIdentifier("Enter data or press F4 to end.", 24, 1));
      session.registerScreen(screen);

      screen = new DcListScreen("Branch Information List", 6, 19);
      screen->addComponent(new DcListColumn(BRANCH_NUMBER, 24));
      screen->addComponent(new CsiIdentifier("Branch Information", 2, 32));
      session.registerScreen(screen);

      screen = new DcMenu("Branch Select By Menu", 33);
      screen->addComponent(new CsiIdentifier("Menu Header", "Select BY", tes::POSITION_ANY, 36));
      screen->addComponent(new CsiIdentifier("Menu Trailer", "\x0e\x12\x12\x12\x12\x12\x12", tes::POSITION_ANY, 27));
      session.registerScreen(screen);

      screen = new DcInputScreen("Branch Lookup By Branch Code");
      screen->addComponent(new DcInputField(BRANCH_NUMBER, 8, 42, 1));
      screen->addComponent(new CsiIdentifier("Branch:", 8, 34));
//      screen->addComponent(new CsiIdentifier("Enter data or press F4 to end.", 24, 1));
      session.registerScreen(screen);

      screen = new DcListScreen("Salesman Information List", 5, 19);
      screen->addComponent(new DcListColumn(BROKER_NUMBER, 31));
      screen->addComponent(new DcListColumn(BRANCH_NUMBER, 38));
      screen->addComponent(new DcListColumn(SALES_REP_NUMBER, 45));
      screen->addComponent(new CsiIdentifier("Salesman Information", 2, 31));
      session.registerScreen(screen);

      screen = new DcMenu("Salesman Select By Menu", 33);
      screen->addComponent(new CsiIdentifier("Menu Header", "Select BY", tes::POSITION_ANY, 36));
      screen->addComponent(new CsiIdentifier("Menu Trailer", "\x0e\x12\x12\x12\x12\x12\x12", tes::POSITION_ANY, 27));
      session.registerScreen(screen);

      screen = new DcInputScreen("Salesman Lookup By Salesman Code");
      screen->addComponent(new DcInputField(BROKER_NUMBER, 8, 43, 1));
      screen->addComponent(new DcInputField(BRANCH_NUMBER, 10, 43, 2));
      screen->addComponent(new DcInputField(SALES_REP_NUMBER, 12, 43, 3));
      screen->addComponent(new CsiIdentifier("Broker:", 8, 35));
      screen->addComponent(new CsiIdentifier("Branch:", 10, 35));
      screen->addComponent(new CsiIdentifier("Sales Rep:", 12, 32));
//      screen->addComponent(new CsiIdentifier("Enter data or press F4 to end.", 24, 1));
      session.registerScreen(screen);

      screen = new CsiScreen("Entity List Screen");
      screen->addComponent(new CsiIdentifier("LastName", 3, 2));
      screen->addComponent(new CsiIdentifier("FirstName", 3, 27));
      session.registerScreen(screen);

      screen = new CsiScreen("Automatic Transfers Information");
      screen->addComponent(new CsiIdentifier("Automatic Transfers Information", 4, 25));
      session.registerScreen(screen);

      screen = new CsiScreen("Certificate screen");
      screen->addComponent(new CsiIdentifier("Certificate - Choose Fun", 4, 28));
      session.registerScreen(screen);

      screen = new CsiScreen("EntityMaintenance screen");
      screen->addComponent(new CsiIdentifier("Entities", 2, 37));
      screen->addComponent(new CsiIdentifier("Switch", 24, 1));
      session.registerScreen(screen);

      screen = new CsiScreen("DistributionOperate Screen"); //What Type of Distribution Do You Want to Add? screen");
      screen->addComponent(new CsiIdentifier("What", 9, 21));
      screen->addComponent(new CsiIdentifier("Distribution", 9, 34));
      session.registerScreen(screen);

      screen = new CsiScreen("Account / Escrow Representative Relationship Information");
      screen->addComponent(new CsiIdentifier("Account / Escrow Representative Relationship Information", 2, 13));
      screen->addComponent(new CsiIdentifier("Entity Relationship", 3, 4));
      session.registerScreen(screen);

      screen = new CsiScreen("RESP Information");
      screen->addComponent(new CsiIdentifier("RESP Account Information", 3, 29));
      screen->addComponent(new CsiIdentifier("Beneficiary Information", 9, 29));
      session.registerScreen(screen);

      screen = new CsiScreen("RESP Transaction");
      screen->addComponent(new CsiIdentifier("RESP Transaction History Inquiry / Maintenance", 3, 18));
      screen->addComponent(new CsiIdentifier("Old Contract ID:", 19, 2));
      session.registerScreen(screen);

      screen = new CsiScreen("Contract Information");
      screen->addComponent(new CsiIdentifier("Contract Information", 4, 31));
      screen->addComponent(new CsiIdentifier("Bail-Out Maturity Date", 18, 3));
      session.registerScreen(screen);

      screen = new CsiScreen("Guarantee Transaction");      
      session.registerScreen(screen);

      screen = new CsiScreen("AccountLRif screen");
      screen->addComponent(new CsiIdentifier("Account L.R.I.F. Information", 4, 27));
      screen->addComponent(new CsiIdentifier("Effective", 6, 4));
      session.registerScreen(screen);

      screen = new CsiScreen("AccountLif screen");
      screen->addComponent(new CsiIdentifier("Account L.I.F. Information", 4, 28));
      screen->addComponent(new CsiIdentifier("Effective", 6, 4));
      session.registerScreen(screen);


      screen = new CsiScreen("AccountRRif screen");
      screen->addComponent(new CsiIdentifier("Account R.R.I.F. Information", 4, 27));
      screen->addComponent(new CsiIdentifier("Effective", 6, 4));
      session.registerScreen(screen);

      screen = new CsiScreen("TaxRate screen");
      screen->addComponent(new CsiIdentifier("Withholding Tax", 2, 33));
      screen->addComponent(new CsiIdentifier("Tax", 3, 10));
      screen->addComponent(new CsiIdentifier("Go", 24, 5));

      session.registerScreen(screen);

      screen = new CsiScreen("Hypothetical Redemptions screen");
      screen->addComponent(new CsiIdentifier("Hypothetical Redemptions Criteria", 4, 24));
      screen->addComponent(new CsiIdentifier("Redemption Code", 9, 18));
      session.registerScreen(screen);

      screen = new CsiScreen("Batch Order Entry screen");
      screen->addComponent(new CsiIdentifier("Batch Order Entry", 2, 32));
      screen->addComponent(new CsiIdentifier("USER ID:", 3, 10));
      screen->addComponent(new CsiIdentifier("User         Batch      Effective   Trace DOCUMENTS Status", 4, 10));
      session.registerScreen(screen);

      screen = new CsiScreen("AMS Global Allocation screen");
      screen->addComponent(new CsiIdentifier("AMS Global Allocation", 3, 30));
      screen->addComponent(new CsiIdentifier("AMSCode", 6, 14));
      session.registerScreen(screen);

      screen = new DcMenu("Client Information screen", 20,35);  
      screen->addComponent(new CsiIdentifier("Menu Header", "Client Information", 1,15,2,50) );   
      screen->addComponent(new CsiIdentifier("Menu Trailer", "\x0e\x12\x12\x12\x12\x12\x12", 3, 15,23,50) );   
      screen->addComponent(new CsiIdentifier("Select Menu Choice", tes::POSITION_ANY, 1) );  
      session.registerScreen(screen);

      screen = new DcListScreen("Funds Available", 5, 7);
      screen->addComponent(new DcListColumn(FUND, 17));
      screen->addComponent(new DcListColumn(CLASS, 22));
      screen->addComponent(new CsiIdentifier("Menu Header", "Funds Available", tes::POSITION_ANY, 39));
      screen->addComponent(new CsiIdentifier("Menu Trailer", "\x0e\x12\x12\x12\x12\x12\x12", tes::POSITION_ANY, 16));
      session.registerScreen(screen);

      screen = new CsiScreen("Account Holdings screen");
      screen->addComponent(new CsiIdentifier("Find", 21, 7));
      screen->addComponent(new CsiIdentifier("Trade", 21, 12));
      screen->addComponent(new CsiIdentifier("actiVity", 21, 18));
      session.registerScreen(screen);

      screen = new CsiScreen("Trade Inquiry screen");
      screen->addComponent(new CsiIdentifier("Cheque", 21, 5));
      screen->addComponent(new CsiIdentifier("casHdivs", 21, 12));
      screen->addComponent(new CsiIdentifier("ACB", 21, 21));
      session.registerScreen(screen);

      screen = new CsiScreen("Trade More screen");
      screen->addComponent(new CsiIdentifier("FIFO", 21, 3));
      screen->addComponent(new CsiIdentifier("LifeGross", 21, 8));
      screen->addComponent(new CsiIdentifier("RedemDetl", 21, 60));
      session.registerScreen(screen);

      screen = new CsiScreen("Redemption Detail screen");
      screen->addComponent(new CsiIdentifier("Redemption Details", "Redemption Details for", 1,5,8,90));
      screen->addComponent(new CsiIdentifier("Orig", 5, 5));
      screen->addComponent(new CsiIdentifier("Pship", 6, 25));
      session.registerScreen(screen);

		screen = new CsiScreen("YTD Contribution");  
		screen->addComponent(new DcInputField(ACCOUNT_NUMBER, 8, 43, 1));
		session.registerScreen(screen);
		
		screen = new DcMenu("Reports Menu", 20,30);  //26);
      screen->addComponent(new CsiIdentifier("Menu Header", "Reports", 1,15,3,50) );   //tes::POSITION_ANY, 27));
      screen->addComponent(new CsiIdentifier("Menu Trailer", "\x0e\x12\x12\x12\x12\x12\x12", 3, 15,23,50) );   //tes::POSITION_ANY, 20));
      screen->addComponent(new CsiIdentifier("Select Menu Choice", tes::POSITION_ANY, 1) );  //24,1
		session.registerScreen(screen);

		screen = new DcMenu("Government Reports Menu", 29 );
		screen->addComponent(new CsiIdentifier("Menu Header", "Government Reports", 1,15,3,50) );   //tes::POSITION_ANY, 27));
      screen->addComponent(new CsiIdentifier("Menu Trailer", "\x0e\x12\x12\x12\x12\x12\x12", 3, 15,23,50) );   //tes::POSITION_ANY, 20));
      screen->addComponent(new CsiIdentifier("Select Menu Choice", tes::POSITION_ANY, 1) );  //24,1
      session.registerScreen(screen);
   }
   catch( CsiException &e )
   {
      DSystem::userMessage(e.getMessage(), "International Financial Data Service Csi");
   }
}

//******************************************************************************
void D_CALLBACK DstcCsi::MasterMenu()
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();
}

//******************************************************************************
void D_CALLBACK DstcCsi::AccountInformation()
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();

   session.getScreen("Master Menu")->select("Accountholder Information") ;

   const CsiScreen *screen = session.getScreen("Account Lookup");
   screen->wait(STANDARD_TIMEOUT);
   screen->init();
   terminal->sendKeyboardSpecial(TESession::F1_Key);

   session.getScreen("Account Information")->wait(STANDARD_TIMEOUT) ;
}

//******************************************************************************
void D_CALLBACK DstcCsi::AutomaticTransferInfo()
{

   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();

   AccountInformation();

   terminal->sendKeyboardString("o");

   const CsiScreen *screen = session.getScreen("Account Options Menu");
   screen->wait(STANDARD_TIMEOUT);
   screen->select("Automatic Transfers");
   session.getScreen("Automatic Transfers Information")->wait(STANDARD_TIMEOUT);

}

//******************************************************************************
void D_CALLBACK DstcCsi::EntityRelationship()
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();

   AccountInformation();

   terminal->sendKeyboardString("o");

   const CsiScreen *screen = session.getScreen("Account Options Menu");
   screen->wait(STANDARD_TIMEOUT);
   screen->select("Entity Maintenance");
   session.getScreen("EntityMaintenance screen")->wait(STANDARD_TIMEOUT);

}

//******************************************************************************
void D_CALLBACK DstcCsi::LIFInformation()
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();

   BankInformationMenu();

   const CsiScreen *screen = session.getScreen("Banking Information Menu");
   screen->select("L.I.F. Information");

   session.getScreen("AccountLif screen")->wait(STANDARD_TIMEOUT);
}

//******************************************************************************
void D_CALLBACK DstcCsi::RRIFInformation()
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();

   BankInformationMenu();

   const CsiScreen *screen = session.getScreen("Banking Information Menu");

   screen->select("R.R.I.F. Information");
   session.getScreen("AccountRRif screen")->wait(STANDARD_TIMEOUT);
}

//******************************************************************************
void D_CALLBACK DstcCsi::LRIFInformation()
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();

   BankInformationMenu();

   const CsiScreen *screen = session.getScreen("Banking Information Menu");

   screen->select("L.R.I.F. Information");
   session.getScreen("AccountLRif screen")->wait(STANDARD_TIMEOUT);
}

//******************************************************************************
void D_CALLBACK DstcCsi:: LIFAllocation()
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();
   LIFInformation();
}

//******************************************************************************
void D_CALLBACK DstcCsi:: RRIFAllocation()
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();
   RRIFInformation();
}

//******************************************************************************
void D_CALLBACK DstcCsi::LRIFAllocation()
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();
   LRIFInformation();
}

//******************************************************************************
void D_CALLBACK DstcCsi::FundValueByTradeOrByFund()
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();
   
   session.getScreen("Master Menu")->select("Unit Values") ;	
	   
   const CsiScreen *screen = screen = session.getScreen("Unit Values");
   screen->wait(STANDARD_TIMEOUT);   
}

//******************************************************************************
void D_CALLBACK DstcCsi::ChooseManageComp()
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();

   //terminal->setVisible(true);
}

//******************************************************************************
//What Type of Distribution
void D_CALLBACK DstcCsi::DistributionAdd()
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();

   AccountInformation();

   terminal->sendKeyboardString("o");

   const CsiScreen *screen = session.getScreen("Account Options Menu");
   screen->wait(STANDARD_TIMEOUT);

   if( !screen->trySelect("Distribution Info") )
      screen->select("Add Distribution Info");

   terminal->sendKeyboardString("A");
   session.getScreen("DistributionOperate Screen");
}

//******************************************************************************
void D_CALLBACK DstcCsi::CertificateInfo()
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();

   AccountInformation();

   terminal->sendKeyboardString("o");

   const CsiScreen *screen = session.getScreen("Account Options Menu");
   screen->wait(STANDARD_TIMEOUT);
   screen->select("Certificates");
   session.getScreen("Certificate screen")->wait(STANDARD_TIMEOUT);
}

//******************************************************************************
void D_CALLBACK DstcCsi::BasicShareholder()
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();

   AccountInformation();

   terminal->sendKeyboardString("o");

   const CsiScreen *screen = session.getScreen("Account Options Menu");
   screen->wait(STANDARD_TIMEOUT);
   screen->select("Basic Shareholder Data");
}

//******************************************************************************
void D_CALLBACK DstcCsi::HistoricalAccountInfo()
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();

   AccountInformation();

   terminal->sendKeyboardString("h");

//   const CsiScreen *screen = session.getScreen("Account Options Menu"); 
//   screen->wait(STANDARD_TIMEOUT);
//   screen->select("Historical Values");
}

//******************************************************************************
void D_CALLBACK DstcCsi::BankInformationMenu()
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();

   AccountInformation();

   terminal->sendKeyboardString("o");

   const CsiScreen *screen = session.getScreen("Account Options Menu");
   screen->wait(STANDARD_TIMEOUT);
   screen->select("Banking Information");

   session.getScreen("Banking Information Menu")->wait(STANDARD_TIMEOUT);
}

//******************************************************************************
void D_CALLBACK DstcCsi::HypoRedemptionInfo()
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();

   AccountInformation();

   terminal->sendKeyboardString("o");

   const CsiScreen *screen = session.getScreen("Account Options Menu");
   screen->wait(STANDARD_TIMEOUT);
   screen->select("Hypothetical Redemptions");

   session.getScreen("Hypothetical Redemptions screen")->wait(STANDARD_TIMEOUT);
}

//******************************************************************************
void D_CALLBACK DstcCsi::BankInformation()
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();

   BankInformationMenu();

   session.getScreen("Banking Information Menu")->select("Bank Accounts");

   const CsiScreen *screen = session.getScreen("Banking Information List");
   screen->wait(STANDARD_TIMEOUT);
   screen->init();
//   terminal->sendKeyboardSpecial(TESession::Return_Key);
}

//******************************************************************************
void D_CALLBACK DstcCsi::PACInformation()
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();

   BankInformationMenu();

   session.getScreen("Banking Information Menu")->select("P.A.C. Information");

   session.getScreen("PAC Information")->wait(STANDARD_TIMEOUT);
}

//******************************************************************************
void D_CALLBACK DstcCsi::SWPInformation()
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();

   BankInformationMenu();

   session.getScreen("Banking Information Menu")->select("S.W.P. Information");

   session.getScreen("SWP Information")->wait(STANDARD_TIMEOUT);
}

//******************************************************************************
void D_CALLBACK DstcCsi::PACAllocation()
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();

   PACInformation();
}

//******************************************************************************
void D_CALLBACK DstcCsi::SWPAllocation()
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();

   SWPInformation();
}

//******************************************************************************
void D_CALLBACK DstcCsi::Allocations()
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();

   AccountInformation();

   terminal->sendKeyboardString("o");

   const CsiScreen *screen = session.getScreen("Account Options Menu");
   screen->wait(STANDARD_TIMEOUT);
   screen->select("Allocation Info");

   session.getScreen("Allocations")->wait(STANDARD_TIMEOUT);
}

//******************************************************************************
void D_CALLBACK DstcCsi::Transaction()
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();

   AccountInformation();

   terminal->sendKeyboardString("r");

//   session.getScreen("Funds Available")->wait(STANDARD_TIMEOUT);
}

//******************************************************************************
void D_CALLBACK DstcCsi::ShareholderRemarks()
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();

   AccountInformation();

   terminal->sendKeyboardString("o");

   const CsiScreen *screen = session.getScreen("Account Options Menu");
   screen->wait(STANDARD_TIMEOUT);
   screen->select("Shareholder Remarks");

   session.getScreen("Remarks")->wait(STANDARD_TIMEOUT);
}

//******************************************************************************
void D_CALLBACK DstcCsi::DemographicInfo()
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();

   AccountInformation();

   terminal->sendKeyboardString("o");

   const CsiScreen *screen = session.getScreen("Account Options Menu");
   screen->wait(STANDARD_TIMEOUT);
   screen->select("Demographic Data");

   session.getScreen("Demographic Information")->wait(STANDARD_TIMEOUT);
}

//******************************************************************************
void D_CALLBACK DstcCsi::TransactionProcessingMenu()
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();

   session.getScreen("Master Menu")->select("Transaction Processing") ;
   session.getScreen("Transaction Processing Menu")->wait(STANDARD_TIMEOUT);
}

//******************************************************************************
void D_CALLBACK DstcCsi::OrdersProcessed()
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();

   TransactionProcessingMenu();
   session.getScreen("Transaction Processing Menu")->select("Orders Processed");
   session.getScreen("Orders Processed")->wait(STANDARD_TIMEOUT);
}

//******************************************************************************
void D_CALLBACK DstcCsi::Settlements()
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();

   TransactionProcessingMenu();
   session.getScreen("Transaction Processing Menu")->select("Settlements");
   session.getScreen("Settlements Menu")->wait(STANDARD_TIMEOUT);
}

//******************************************************************************
void D_CALLBACK DstcCsi::AddressInformation()
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();

   AccountInformation();

   terminal->sendKeyboardString("o");

   const CsiScreen *screen = session.getScreen("Account Options Menu");
   screen->wait(STANDARD_TIMEOUT);
   screen->select("Shareholder Address");

   session.getScreen("Address Information")->wait(STANDARD_TIMEOUT);
}

//******************************************************************************
void D_CALLBACK DstcCsi::AddressAssignments()
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();

   AccountInformation();

   terminal->sendKeyboardString("o");

   const CsiScreen *screen = session.getScreen("Account Options Menu");
   screen->wait(STANDARD_TIMEOUT);
   screen->select("Mailing Information");

   session.getScreen("Address Assignments")->wait(STANDARD_TIMEOUT);
}

//******************************************************************************
void D_CALLBACK DstcCsi::AccountEntityRelationship()
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();

   AccountInformation();

   terminal->sendKeyboardString("o");

   const CsiScreen *screen = session.getScreen("Account Options Menu");
   screen->wait(STANDARD_TIMEOUT);
   screen->select("Account/Entity Relationships");

   session.getScreen("Account / Entity Relationship Information")->wait(STANDARD_TIMEOUT);
}

//******************************************************************************
void D_CALLBACK DstcCsi::NewShareholder()
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();

   session.getScreen("Master Menu")->select("Accountholder Information") ;

   const CsiScreen *screen = session.getScreen("Account Lookup");
   screen->wait(STANDARD_TIMEOUT);

   terminal->sendKeyboardSpecial(TESession::F3_Key);
}

//******************************************************************************
void D_CALLBACK DstcCsi::BrokerInformationMenu()
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();
   session.getScreen("Master Menu")->select("Fund and Broker Information") ;
   const CsiScreen *screen = session.getScreen("Fund and Broker Information Menu");
   screen->wait(STANDARD_TIMEOUT);
   screen->select("Broker Information");
   session.getScreen("Broker Information Menu")->wait(STANDARD_TIMEOUT);
}

//******************************************************************************
void D_CALLBACK DstcCsi::TaxRateInformation()
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();
   session.getScreen("Master Menu")->select("Transaction Processing") ;

   const CsiScreen *screen = session.getScreen("Activity Menu");
   screen->wait(STANDARD_TIMEOUT);
   screen->select("Tax Rates");
   session.getScreen("TaxRate screen")->wait(STANDARD_TIMEOUT);
}

//******************************************************************************
void D_CALLBACK DstcCsi::PatchOrderEntryInformation()
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();
   TransactionProcessingMenu();
   const CsiScreen *screen = session.getScreen("Transaction Processing Menu");
	screen->wait(STANDARD_TIMEOUT);
   screen->select("Batch Order Entry");
   session.getScreen("Batch Order Entry screen")->wait(60000);
}

//******************************************************************************
void D_CALLBACK DstcCsi::ContractInformation()
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();

   AccountInformation();

   terminal->sendKeyboardString("o");

   const CsiScreen *screen = session.getScreen("Account Options Menu");
   screen->wait(STANDARD_TIMEOUT);
   screen->select("Contract Information");
   session.getScreen("Contract Information")->wait(STANDARD_TIMEOUT);
}

//******************************************************************************
void D_CALLBACK DstcCsi::GuaranteeTransaction()
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();

   AccountInformation();

   terminal->sendKeyboardString("o");

   const CsiScreen *screen = session.getScreen("Account Options Menu");
   screen->wait(STANDARD_TIMEOUT);   
}

//******************************************************************************
void D_CALLBACK DstcCsi::RespInformation()
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();

   AccountInformation();

   terminal->sendKeyboardString("o");

   const CsiScreen *screen = session.getScreen("Account Options Menu");
   screen->wait(STANDARD_TIMEOUT);
   screen->select("RESP Information");
   session.getScreen("RESP Information")->wait(STANDARD_TIMEOUT);
}

//******************************************************************************
void D_CALLBACK DstcCsi::RespTransInformation()
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();

   AccountInformation();   

   terminal->sendKeyboardString("r");   
}

//******************************************************************************
void D_CALLBACK DstcCsi::BranchInformation()
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();

   BrokerInformationMenu();

   session.getScreen("Broker Information Menu")->select("Branch Information");
   session.getScreen("Choose Broker List")->wait(STANDARD_TIMEOUT);

   terminal->sendKeyboardSpecial(TESession::F6_Key);

   const CsiScreen *screen = session.getScreen("Broker Select By Menu");
   screen->wait(STANDARD_TIMEOUT);
   screen->select("Broker Code");

   screen = session.getScreen("Broker Lookup By Broker Code");
   screen->wait(STANDARD_TIMEOUT);
   screen->init();

   terminal->sendKeyboardSpecial(TESession::Return_Key);

   terminal->silenceWait(STANDARD_TIMEOUT, 1000); 
   terminal->sendKeyboardSpecial(TESession::Return_Key);

   session.getScreen("Branch Information List")->wait(STANDARD_TIMEOUT);

   terminal->sendKeyboardSpecial(TESession::F6_Key);

   screen = session.getScreen("Branch Select By Menu");
   screen->wait(STANDARD_TIMEOUT);
   screen->select("Branch Code");

   screen = session.getScreen("Branch Lookup By Branch Code");
   screen->wait(STANDARD_TIMEOUT);
   screen->init();

   terminal->sendKeyboardSpecial(TESession::Return_Key);
}

//******************************************************************************
void D_CALLBACK DstcCsi::BrokerInformation()
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();

   BrokerInformationMenu();

   session.getScreen("Broker Information Menu")->select("Broker Information");
   session.getScreen("Broker Information List")->wait(STANDARD_TIMEOUT);

   terminal->sendKeyboardSpecial(TESession::F6_Key);

   const CsiScreen *screen = session.getScreen("Broker Select By Menu");
   screen->wait(STANDARD_TIMEOUT);
   screen->select("Broker Code");

   screen = session.getScreen("Broker Lookup By Broker Code");
   screen->wait(STANDARD_TIMEOUT);
   screen->init();

   terminal->sendKeyboardSpecial(TESession::Return_Key);
}

//******************************************************************************
void D_CALLBACK DstcCsi::SalesRepInformation()
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();

   BrokerInformationMenu();

   session.getScreen("Broker Information Menu")->select("Salesman Information");
   session.getScreen("Salesman Information List")->wait(STANDARD_TIMEOUT);

   terminal->sendKeyboardSpecial(TESession::F6_Key);

   const CsiScreen *screen = session.getScreen("Salesman Select By Menu");
   screen->wait(STANDARD_TIMEOUT);
   screen->select("Salesman Code");

   screen = session.getScreen("Salesman Lookup By Salesman Code");
   screen->wait(STANDARD_TIMEOUT);
   screen->init();

   terminal->sendKeyboardSpecial(TESession::Return_Key);
}

//******************************************************************************
void D_CALLBACK DstcCsi::WhereUsed()
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();

   session.getScreen("Master Menu")->select("Accountholder Information") ;

   const CsiScreen *screen = session.getScreen("Account Lookup");
   screen->wait(STANDARD_TIMEOUT);
   terminal->sendKeyboardSpecial(TESession::F8_Key);  // clear the screen...
   screen->init();
   terminal->sendKeyboardSpecial(TESession::F1_Key);

   session.getScreen("Entity List Screen")->wait(STANDARD_TIMEOUT) ;
}

//******************************************************************************
void D_CALLBACK DstcCsi::EntityMaintainance()
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();

   AccountInformation();

   terminal->sendKeyboardString("o");

   const CsiScreen *screen = session.getScreen("Account Options Menu");
   screen->wait(STANDARD_TIMEOUT);

   screen->select("Entity Maintenance");
   session.getScreen("EntityMaintenance screen")->wait(STANDARD_TIMEOUT);
//   screen->select("Account/Entity Relationships");

//   session.getScreen("Account / Entity Relationship Information")->wait(STANDARD_TIMEOUT);
}

//******************************************************************************
void D_CALLBACK DstcCsi::AddDistributionInfo()
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();

   AccountInformation();

   terminal->sendKeyboardString("o");

   const CsiScreen *screen = session.getScreen("Account Options Menu");
   screen->wait(STANDARD_TIMEOUT);

   if( !screen->trySelect("Distribution Info") )
      screen->select("Add Distribution Info");
}

//******************************************************************************
void D_CALLBACK DstcCsi::LockedInformation()
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();

   AccountInformation();

   terminal->sendKeyboardString("o");

   const CsiScreen *screen = session.getScreen("Account Options Menu");
   screen->wait(STANDARD_TIMEOUT);

   screen->select("Locked-In Information");
   screen =  session.getScreen("Account / Escrow Representative Relationship Information");
   screen->wait(STANDARD_TIMEOUT);
}

//******************************************************************************
void D_CALLBACK DstcCsi::DistributionInfo()
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();

   AccountInformation();

   terminal->sendKeyboardString("o");

   const CsiScreen *screen = session.getScreen("Account Options Menu");
   screen->wait(STANDARD_TIMEOUT);

   //if (!screen->trySelect("Distribution Info"))
   screen->select("Distribution Info");
}

//******************************************************************************
void D_CALLBACK DstcCsi::AmsGlobalAllocation()
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();
   session.getScreen("Master Menu")->select("Fund and Broker Information") ;
   const CsiScreen *screen = session.getScreen("Fund and Broker Information Menu");
   screen->wait(STANDARD_TIMEOUT);
   screen->select("Client Information");
   screen = session.getScreen("Client Information screen");
   screen->wait(STANDARD_TIMEOUT);
   screen->select("Client Global AMS Allocations");
}

//******************************************************************************
void D_CALLBACK DstcCsi::RedemptionDetail()
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();
   
	AccountInformation();

	terminal->sendKeyboardString("r");

   const CsiScreen *screen = session.getScreen("Funds Available");
   screen->wait(STANDARD_TIMEOUT);
   screen->init();   	
}

//******************************************************************************
void D_CALLBACK DstcCsi::YTDContribution()
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();

	session.getScreen("Master Menu")->select("Reports");
	const CsiScreen *screen = session.getScreen("Reports Menu");
   screen->wait(STANDARD_TIMEOUT);
   screen->select("Government Reports");
	session.getScreen("Government Reports Menu")->wait(STANDARD_TIMEOUT);
	screen->select("Tax and RRSP Contribution Receipt Processing");	
}

//******************************************************************************
void DstcCsi::logon()
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();

   if( !terminal->getConnected() )
      terminal->setConnected();

#ifndef DTEST
   terminal->setVisible(true);

   while( tes::EVENT_TIMEOUT == terminal->doneWait(1000) )
   {
      if( session.getScreen("Master Menu")->tryWait(0) )
      {
         terminal->setVisible(VISIBLE_NAV);
         return;
      }
   }

   terminal->setVisible(VISIBLE_NAV);

   if( terminal->getConnected() )
      terminal->setConnected(false);

   throw DstcCsiLogonCancelled();

#else
   terminal->sendKeyboardSpecial(TESession::Return_Key);

   if( tes::EVENT_SUCCESS != terminal->streamTextWait(5, "ogin:") )
   {
      terminal->sendKeyboardSpecial(TESession::Return_Key);
      if( tes::EVENT_SUCCESS != terminal->streamTextWait(5, "ogin:") )
         throw DstcCsiTimeout("\"ogin:\"");
   }

   terminal->sendKeyboardString("smithd");
   terminal->sendKeyboardSpecial(TESession::Return_Key);

   if( tes::EVENT_SUCCESS != terminal->streamTextWait(STANDARD_TIMEOUT, "assword:") )
      throw DstcCsiTimeout("\"assword:\"");

   terminal->sendKeyboardString("regular02");
   terminal->sendKeyboardSpecial(TESession::Return_Key);

   if( tes::EVENT_SUCCESS != terminal->streamTextWait(STANDARD_TIMEOUT, "TERM") )
      throw DstcCsiTimeout("\"TERM\"");

   terminal->sendKeyboardString("vt220");
   terminal->sendKeyboardSpecial(TESession::Return_Key);

   if( tes::EVENT_SUCCESS != terminal->streamTextWait(STANDARD_TIMEOUT, "smithd") )
      throw DstcCsiTimeout("\"OS Pprompt\"");

   terminal->sendKeyboardString("Kill.rmenu");
   terminal->sendKeyboardSpecial(TESession::Return_Key);

   if( tes::EVENT_SUCCESS != terminal->streamTextWait(STANDARD_TIMEOUT, "smithd") )
      throw DstcCsiTimeout("\"OS Pprompt\"");

   terminal->sendKeyboardString("envrte");
   terminal->sendKeyboardSpecial(TESession::Return_Key);

   if( tes::EVENT_SUCCESS != terminal->streamTextWait(STANDARD_TIMEOUT, "smithd") )
      throw DstcCsiTimeout("\"OS Pprompt\"");

   terminal->sendKeyboardString("rtemenu");
   terminal->sendKeyboardSpecial(TESession::Return_Key);

   if( tes::EVENT_SUCCESS != terminal->displayTextWait(STANDARD_TIMEOUT, "RTE MENU", TEPosition(tes::POSITION_ANY, 37)) )
      throw DstcCsiTimeout("\"RTE Menu\"");

   terminal->sendKeyboardString("7");
   terminal->sendKeyboardSpecial(TESession::Return_Key);

   if( tes::EVENT_SUCCESS != terminal->displayTextWait(STANDARD_TIMEOUT, "rdslot1", TEPosition(6, 25)) )
      throw DstcCsiTimeout("\"rdslot1\"");

   terminal->sendKeyboardSpecial(TESession::DOWN_Key);
   terminal->sendKeyboardSpecial(TESession::Return_Key);

   if( tes::EVENT_SUCCESS != terminal->displayTextWait(STANDARD_TIMEOUT, "Userid:", TEPosition(17, 30)) )
      throw DstcCsiTimeout("\"UserId\"");

   terminal->sendKeyboardString("corfax");
   terminal->sendKeyboardSpecial(TESession::Return_Key);
   terminal->sendKeyboardSpecial(TESession::Return_Key);
   terminal->sendKeyboardSpecial(TESession::Return_Key);

   session.getScreen("Master Menu")->wait(STANDARD_TIMEOUT);

#endif
}

//******************************************************************************
void D_CALLBACK DstcCsi::reset()
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();

   if( !terminal->getConnected() )
      return;

   const CsiScreen *masterMenu =  session.getScreen("Master Menu");

   for( int i=0; i<5; i++ )
   {
      terminal->sendKeyboardSpecial(TESession::F4_Key);
      terminal->sendKeyboardSpecial(TESession::F4_Key);
      terminal->sendKeyboardSpecial(TESession::F4_Key);
      terminal->sendKeyboardSpecial(TESession::F4_Key);

      terminal->silenceWait(STANDARD_TIMEOUT, 1000);
      if( masterMenu->tryWait(0) )
         return;
   }

   if( masterMenu->tryWait(STANDARD_TIMEOUT) )
      return;

   terminal->setConnected(false);
}

//******************************************************************************
void D_CALLBACK DstcCsi::preset()
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();

   terminal->setVisible(VISIBLE_NAV);
   if( !terminal->getConnected() )
      logon();

   terminal->sendKeyboardSpecial(TESession::F4_Key);
   terminal->silenceWait(STANDARD_TIMEOUT, 1000);
   if( !session.getScreen("Master Menu")->tryWait(2000) )
      logon();
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcsi/ifastcsi.cpp-arc  $
 * 
 *    Rev 1.14   May 31 2005 16:36:10   porteanm
 * Incident 300390 - Unit Values.
 * 
 *    Rev 1.13   May 03 2005 15:14:24   porteanm
 * Incident 300390 - Unit Values.
 * 
 *    Rev 1.12   May 28 2004 15:55:16   VADEANUM
 * PTS 10028913 - Removed F4 for Redemption Detail
 * 
 *    Rev 1.11   May 26 2004 15:21:48   VADEANUM
 * PTS 10028913 - YTD support and inserted back code for RESPInformation.
 * 
 *    Rev 1.10   May 26 2004 10:57:08   VADEANUM
 * PTS 10028913 - Corrected some time outs and redirections - work in progress.
 * 
 *    Rev 1.9   Oct 09 2002 23:55:20   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.8   Jan 29 2002 10:58:08   JANKAREN
 * Added Redemption Detail
 * 
 *    Rev 1.7   Nov 28 2001 09:59:54   YINGBAOL
 * add AMS Global Allocation
 * 
 *    Rev 1.6   May 05 2000 10:28:36   YINGBAOL
 * add patch order information
 * 
 *    Rev 1.5   Apr 17 2000 17:13:06   YINGBAOL
 * added redemption
 * 
 *    Rev 1.4   Apr 03 2000 16:02:56   YINGBAOL
 * fix
 * 
 *    Rev 1.3   Apr 03 2000 15:49:08   YINGBAOL
 * added RIF LIF Allocation
 * 
 *    Rev 1.2   Mar 21 2000 15:06:12   YINGBAOL
 * added LRIF screen
 * 
 *    Rev 1.1   Mar 07 2000 09:40:34   YINGBAOL
 * change synchronize
 * 
 *    Rev 1.22   Mar 07 2000 09:11:52   YINGBAOL
 * added Tax rate
 * 
 *    Rev 1.21   Feb 29 2000 17:08:46   YINGBAOL
 * adde new entry point
 * 
 *
 */
