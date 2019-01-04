// AboutPropMgmtOptionsPage.cpp : implementation file
//

#include "stdafx.h"
#include "ifsupp.h"
#include "ifsuppext.hpp"

#include "AboutPropMgmtOptionsPage.h"
#include <ConfigManager.hpp>
////#include <ifastgui/dstcview.h>

#include <bfdata\bfdataid.hpp>

#include <ifastcbo/dstcusersession.hpp>
#include <ifastcbo/dstcglobalsession.hpp>
#include <ifastcbo/MgmtCo.hpp>
#include <ifastcbo/MgmtCoOptions.hpp>
////#include <ifastbp/UserSessionProcessIncludes.h>
#include <ifastdataimpl\dse_dstc0083_vw.hpp>
#include <ifastdataimpl\dse_dstc0149_vw.hpp>
#include <ifastdataimpl\dse_dstc0263_vw.hpp>
#include <ifastdataimpl\dse_dstc0344_vw.hpp>


namespace {
   const unsigned long MAXBUFSIZE = 256;

   //Used in list control
   const I_CHAR *COL_HEADER1 = I_( "Option" );
   const I_CHAR *COL_HEADER2 = I_( "Value" );
}



//Macro used in ShowImports() function
#define MakePtr( cast, ptr, addValue ) (cast)( (DWORD)(ptr) + (addValue) )


// AboutPropMgmtOptionsPage dialog

IMPLEMENT_DYNAMIC(AboutPropMgmtOptionsPage, CPropertyPage)
AboutPropMgmtOptionsPage::AboutPropMgmtOptionsPage()
: CPropertyPage(AboutPropMgmtOptionsPage::IDD)
, m_optionCount(0)
, pMgmtCo_(NULL)
{
   ifsupp::PFNMGMTCOINFO pfnMgmtCoInfo;
   ifsupp::GetMgmtCoInfoCallback(pfnMgmtCoInfo);
   if( NULL != pfnMgmtCoInfo ) {
      DSTCUserSession* p;
      CString str1,str2,str3,str4;  // just placeholders...
      (*pfnMgmtCoInfo)(p, pMgmtCo_, str1,str2,str3,str4);
   }
}

AboutPropMgmtOptionsPage::~AboutPropMgmtOptionsPage()
{
}

void AboutPropMgmtOptionsPage::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(AboutDetailsDlg)
   DDX_Control(pDX, IDC_LB_MGMT_OPTIONS, m_optionList);
   //}}AFX_DATA_MAP
}


bool AboutPropMgmtOptionsPage::hasOptions() const {
   return( pMgmtCo_ != NULL );
}


#ifndef STRINGIFY
   #define STRINGIFY(str) STRINGIFY_W( #str )
   #define STRINGIFY_W( str ) L ## str
#endif
#define REPORTTEXTFIELD( ss, p, fld ) \
   ReportTextField( ss, STRINGIFY(fld), p, ifds:: ## fld )
#define ADDTEXTFIELD( p, fld ) \
   AddTextField( STRINGIFY(fld), p, ifds:: ## fld )


void AboutPropMgmtOptionsPage::ReportTextField( std::wstringstream& ss,
                                              const DString& dstrName,
                                              BFCBO* pCBO,
                                              const BFFieldId& idField ) {
   DString dstrValue;
   pCBO->getField(idField, dstrValue, BF::HOST );

   ss.width(40);
   ss.setf( std::ios::left );
   ss << dstrName.c_str();
   ss << I_(": ") << dstrValue.c_str();
   ss << std::endl;
}

void AboutPropMgmtOptionsPage::ReportTextFields( std::wstringstream& ss,
                                              const BFDataId& dataID,
                                              BFCBO* pCBO) {
   DString dstrValue;
   BFData queryData(dataID);

   unsigned int iNumField = queryData.getFieldCount();

   for(unsigned int i=0;i<iNumField;i++)
   {
      const BFDataField& dataField = queryData.getElementByIndex( i );
      pCBO->getField(dataField.getId(), dstrValue, BF::HOST );

      ss.width(40);
      ss.setf( std::ios::left );
      ss << BFFieldId(dataField.getId()).getName().c_str();
      ss << I_(": ") << dstrValue.c_str();
      ss << std::endl;
   }
}

void AboutPropMgmtOptionsPage::generateReport( std::wstringstream& ss )
{
   DString tempString = ConfigManager::getApplication();
   ss << I_("=====================================================") << std::endl;
   ss << I_("=== Management Company Options ======================") << std::endl;

   MgmtCoOptions* pOptions = NULL;
   pMgmtCo_->getMgmtCoOptions( pOptions );

   if( NULL != pOptions ) {
      // View 83
      REPORTTEXTFIELD( ss, pOptions,SysCurrency);
      REPORTTEXTFIELD( ss, pOptions,ShrNumCtrl);
      REPORTTEXTFIELD( ss, pOptions,ShrNumVal);
      REPORTTEXTFIELD( ss, pOptions,AcctNumCtrl);
      REPORTTEXTFIELD( ss, pOptions,AcctNumVal);
      REPORTTEXTFIELD( ss, pOptions,DefaultGrp);
      REPORTTEXTFIELD( ss, pOptions,GrpCodeLevel);
      REPORTTEXTFIELD( ss, pOptions,TaxTypeUpd);
      REPORTTEXTFIELD( ss, pOptions,MktMailDef);
      REPORTTEXTFIELD( ss, pOptions,RepByBranch);
      REPORTTEXTFIELD( ss, pOptions,BrokerBranch);
      REPORTTEXTFIELD( ss, pOptions,CapAddress);
      REPORTTEXTFIELD( ss, pOptions,CountryVal);
      REPORTTEXTFIELD( ss, pOptions,MandatoryId);
      REPORTTEXTFIELD( ss, pOptions,BirthNameMand);
      REPORTTEXTFIELD( ss, pOptions,SinException);
      REPORTTEXTFIELD( ss, pOptions,ShadowNominee);
      REPORTTEXTFIELD( ss, pOptions,BankValid1);
      REPORTTEXTFIELD( ss, pOptions,BankValid2);
      REPORTTEXTFIELD( ss, pOptions,BankLayout);
      REPORTTEXTFIELD( ss, pOptions,SYMBrkUpd);
      REPORTTEXTFIELD( ss, pOptions,BrokerFund);
      REPORTTEXTFIELD( ss, pOptions,PACMinAmt);
      REPORTTEXTFIELD( ss, pOptions,PACAmtEdit);
      REPORTTEXTFIELD( ss, pOptions,GICAllocOnly);
      REPORTTEXTFIELD( ss, pOptions,DisableFee4Alloc);
      REPORTTEXTFIELD( ss, pOptions,BusRounding);
      REPORTTEXTFIELD( ss, pOptions,MultiCurrency);
      REPORTTEXTFIELD( ss, pOptions,SplitComm);
      REPORTTEXTFIELD( ss, pOptions,AcctFeeParm);
      REPORTTEXTFIELD( ss, pOptions,CappedFund);
      REPORTTEXTFIELD( ss, pOptions,BankingFormat);
      REPORTTEXTFIELD( ss, pOptions,InstCodeMax);
      REPORTTEXTFIELD( ss, pOptions,TransitNoMax);
      REPORTTEXTFIELD( ss, pOptions,BankAcctNumMax);
      REPORTTEXTFIELD( ss, pOptions,CurrBusDate);
      REPORTTEXTFIELD( ss, pOptions,MandAddLines);
      REPORTTEXTFIELD( ss, pOptions,CurrSysDate);
      REPORTTEXTFIELD( ss, pOptions,CurrSysTime);
      REPORTTEXTFIELD( ss, pOptions,ChkDuplicationTrade);
      REPORTTEXTFIELD( ss, pOptions,InvAdvice);
      REPORTTEXTFIELD( ss, pOptions,AcqFeeDefault);
      REPORTTEXTFIELD( ss, pOptions,LastCycleDate);
      REPORTTEXTFIELD( ss, pOptions,AccountableMandatory);
      REPORTTEXTFIELD( ss, pOptions,SplitAcCode);
      REPORTTEXTFIELD( ss, pOptions,TRExclRedCodes);
      REPORTTEXTFIELD( ss, pOptions,TIKRedCodes);
      REPORTTEXTFIELD( ss, pOptions,DealDateTime);
      REPORTTEXTFIELD( ss, pOptions,EFTPurchase);
      REPORTTEXTFIELD( ss, pOptions,EFTPurchFuture);
      REPORTTEXTFIELD( ss, pOptions,GrpContribution);
      REPORTTEXTFIELD( ss, pOptions,AllowFractions);
      REPORTTEXTFIELD( ss, pOptions,SplitCommTransTypes);
      REPORTTEXTFIELD( ss, pOptions,CashReceiptTrack);
      REPORTTEXTFIELD( ss, pOptions,DepositId2);
      REPORTTEXTFIELD( ss, pOptions,DepositIdMandatory);
      REPORTTEXTFIELD( ss, pOptions,DefaultPurchPayType);
      REPORTTEXTFIELD( ss, pOptions,EFTPurchaseLeadDays);
      REPORTTEXTFIELD( ss, pOptions,CharWireNum);
      REPORTTEXTFIELD( ss, pOptions,WireNumMandatory);
      REPORTTEXTFIELD( ss, pOptions,WireNumDefault);
      REPORTTEXTFIELD( ss, pOptions,SrcOfFundMandatory);
      REPORTTEXTFIELD( ss, pOptions,RRIFPrevYear);
      REPORTTEXTFIELD( ss, pOptions,RRIFOrPayment);
      REPORTTEXTFIELD( ss, pOptions,RRIFValidation);
      REPORTTEXTFIELD( ss, pOptions,FundAllocLimit);
      REPORTTEXTFIELD( ss, pOptions,AMSOrder);
      REPORTTEXTFIELD( ss, pOptions,DefSetlCurrency);
      REPORTTEXTFIELD( ss, pOptions,PrevBusDate);
      REPORTTEXTFIELD( ss, pOptions,CurrChkByTaxType);
      REPORTTEXTFIELD( ss, pOptions,EuroAddrFormat);
      REPORTTEXTFIELD( ss, pOptions,InvalidCurr);
      REPORTTEXTFIELD( ss, pOptions,TaxTypeByCurrChk);
      REPORTTEXTFIELD( ss, pOptions,SegClient);
      REPORTTEXTFIELD( ss, pOptions,CotClient);
      REPORTTEXTFIELD( ss, pOptions,ResClient);
      REPORTTEXTFIELD( ss, pOptions,LipClient);
      REPORTTEXTFIELD( ss, pOptions,T550ReportMethod);
      REPORTTEXTFIELD( ss, pOptions,ShrEFTConsol);
      REPORTTEXTFIELD( ss, pOptions,PACSWPEFTConsol);
      REPORTTEXTFIELD( ss, pOptions,Unseizable);
      REPORTTEXTFIELD( ss, pOptions,RdLckdE);
      REPORTTEXTFIELD( ss, pOptions,RdLckdW);
      REPORTTEXTFIELD( ss, pOptions,TitleRestrict);
      REPORTTEXTFIELD( ss, pOptions,EditDeffs);
      REPORTTEXTFIELD( ss, pOptions,RoundFlag);
      REPORTTEXTFIELD( ss, pOptions,RedAccruedInt);
      REPORTTEXTFIELD( ss, pOptions,PQLIFLIRARedCodes);
      REPORTTEXTFIELD( ss, pOptions,PQLIFLIRAJuris);
      REPORTTEXTFIELD( ss, pOptions,PQLIFLIRAAage);
      REPORTTEXTFIELD( ss, pOptions,PQLIFLIRAMaxPrct);
      REPORTTEXTFIELD( ss, pOptions,PQLIFLIRATaxType);
      REPORTTEXTFIELD( ss, pOptions,AutoBanking);
      REPORTTEXTFIELD( ss, pOptions,RdAcctCurrency);
      REPORTTEXTFIELD( ss, pOptions,BankSrcAcct);
      REPORTTEXTFIELD( ss, pOptions,SourceOffFund);
      REPORTTEXTFIELD( ss, pOptions,ModRecipType);
      REPORTTEXTFIELD( ss, pOptions,SpecAcctNum);
      REPORTTEXTFIELD( ss, pOptions,TradeCutOff);
      REPORTTEXTFIELD( ss, pOptions,PartTransAsFull);
      REPORTTEXTFIELD( ss, pOptions,CheqDeliveryDefault);
      REPORTTEXTFIELD( ss, pOptions,SplitComm100);
      REPORTTEXTFIELD( ss, pOptions,CashDistribRule);
      REPORTTEXTFIELD( ss, pOptions,ValidDistributionPayType);
      REPORTTEXTFIELD( ss, pOptions,AllFundsTransfers);
      REPORTTEXTFIELD( ss, pOptions,TfrToDiffSH);
      REPORTTEXTFIELD( ss, pOptions,DeathRedCode);
      REPORTTEXTFIELD( ss, pOptions,SpouseBenefReLn);
      REPORTTEXTFIELD( ss, pOptions,ChildBenefReLn);
      REPORTTEXTFIELD( ss, pOptions,MultiAcctEachShrNum);
      REPORTTEXTFIELD( ss, pOptions,UpdOrdType);
      REPORTTEXTFIELD( ss, pOptions,CommissionType);
      REPORTTEXTFIELD( ss, pOptions,Residency1);
      REPORTTEXTFIELD( ss, pOptions,Residency2);
      REPORTTEXTFIELD( ss, pOptions,Residency3);
      REPORTTEXTFIELD( ss, pOptions,DefltRedCodeFlag);
      REPORTTEXTFIELD( ss, pOptions,DefltRedCode);
      REPORTTEXTFIELD( ss, pOptions,FundEligSlsRepLvl);
      REPORTTEXTFIELD( ss, pOptions,WrapAccount);
      REPORTTEXTFIELD( ss, pOptions,DistribFundsValidate);
      REPORTTEXTFIELD( ss, pOptions,XSFundsValidate);
      REPORTTEXTFIELD( ss, pOptions,ClientAMSType);
      REPORTTEXTFIELD( ss, pOptions,ClassRule);
      REPORTTEXTFIELD( ss, pOptions,ProfileCodeDflt);
      REPORTTEXTFIELD( ss, pOptions,MgmtFeePayOptDflt);
      REPORTTEXTFIELD( ss, pOptions,MgmtCoPayReq);
      REPORTTEXTFIELD( ss, pOptions,SplitPreferenceOption);
      REPORTTEXTFIELD( ss, pOptions,RES2Client);
      REPORTTEXTFIELD( ss, pOptions,QESIClient);
      REPORTTEXTFIELD( ss, pOptions,PSE_EAPEditDate);
      REPORTTEXTFIELD( ss, pOptions,EligDateforCLB);
      REPORTTEXTFIELD( ss, pOptions,NonTrustStartDate);
      REPORTTEXTFIELD( ss, pOptions,NonTrustStopDate);
      REPORTTEXTFIELD( ss, pOptions,IsNonTrustee);
	  REPORTTEXTFIELD( ss, pOptions,AutoDocTracking);

      // View 149
      REPORTTEXTFIELD( ss, pOptions,AllowMultiplePacSwp);
      REPORTTEXTFIELD( ss, pOptions,SWPEditlevel);
      REPORTTEXTFIELD( ss, pOptions,SWPMin);
      REPORTTEXTFIELD( ss, pOptions,SWPHardEdit);
      REPORTTEXTFIELD( ss, pOptions,DSCOverride);
      REPORTTEXTFIELD( ss, pOptions,DabScreen);
      REPORTTEXTFIELD( ss, pOptions,DepositId2);
      REPORTTEXTFIELD( ss, pOptions,DispClientTradeID);
      REPORTTEXTFIELD( ss, pOptions,DefaultBankType);
      REPORTTEXTFIELD( ss, pOptions,DispManageStyle);
      REPORTTEXTFIELD( ss, pOptions,DefaultBankUpd);
      REPORTTEXTFIELD( ss, pOptions,SplitOnAddPur);
      REPORTTEXTFIELD( ss, pOptions,SplitOnModPur);
      REPORTTEXTFIELD( ss, pOptions,SplitOnReqOnly);
      REPORTTEXTFIELD( ss, pOptions,SplitComBankDeflt);
      REPORTTEXTFIELD( ss, pOptions,ValSplCom);
      REPORTTEXTFIELD( ss, pOptions,SavePlanClient);
      REPORTTEXTFIELD( ss, pOptions,PACLastRunDate);
      REPORTTEXTFIELD( ss, pOptions,SWPLastRunDate);
      REPORTTEXTFIELD( ss, pOptions,ManualSettleDates);
      REPORTTEXTFIELD( ss, pOptions,ACHSavingsPlan);
      REPORTTEXTFIELD( ss, pOptions,ACHPAC);
      REPORTTEXTFIELD( ss, pOptions,ForeignContent);
      REPORTTEXTFIELD( ss, pOptions,AllowUnitsPurchase);
      REPORTTEXTFIELD( ss, pOptions,MultiCurrEFTUnitPurch);
      REPORTTEXTFIELD( ss, pOptions,DisAllowPayTypeUnitPurch);
      REPORTTEXTFIELD( ss, pOptions,AllowCashDistrib);
      REPORTTEXTFIELD( ss, pOptions,PACCalendar);
      REPORTTEXTFIELD( ss, pOptions,ProductGroupCode);
      REPORTTEXTFIELD( ss, pOptions,TradeDateLag);
      REPORTTEXTFIELD( ss, pOptions,TradeDateLagExch);
      REPORTTEXTFIELD( ss, pOptions,FCRebalancing);
      REPORTTEXTFIELD( ss, pOptions,CommFeeCodes);
      REPORTTEXTFIELD( ss, pOptions,CalcSwitch);
      REPORTTEXTFIELD( ss, pOptions,MiscFeeDefn);
      REPORTTEXTFIELD( ss, pOptions,AcctLvlFIFO);
      REPORTTEXTFIELD( ss, pOptions,CompCodeFlag);
      REPORTTEXTFIELD( ss, pOptions,PriceProcAtFndGrp);
      REPORTTEXTFIELD( ss, pOptions,MgmtFeeType);
      REPORTTEXTFIELD( ss, pOptions,LLPWithdrawalRules);
      REPORTTEXTFIELD( ss, pOptions,RRIFFromAlloc);
      REPORTTEXTFIELD( ss, pOptions,IsoCompliant);
      REPORTTEXTFIELD( ss, pOptions,ReviewDateFlag);
      REPORTTEXTFIELD( ss, pOptions,OverrideReviewDate);
      REPORTTEXTFIELD( ss, pOptions,ReviewMnths);
      REPORTTEXTFIELD( ss, pOptions,BankChrgs);
      REPORTTEXTFIELD( ss, pOptions,ConsolidEFT);
      REPORTTEXTFIELD( ss, pOptions,ACHRedemption);
      REPORTTEXTFIELD( ss, pOptions,ValueDateApplic);
      REPORTTEXTFIELD( ss, pOptions,SettleAll);
      REPORTTEXTFIELD( ss, pOptions,DuplicateAltAcct);
      REPORTTEXTFIELD( ss, pOptions,BankDetlName);
      REPORTTEXTFIELD( ss, pOptions,OPDeliveryMethods);
      REPORTTEXTFIELD( ss, pOptions,OPDeliveryOption);
      REPORTTEXTFIELD( ss, pOptions,CnsntToWaive);
      REPORTTEXTFIELD( ss, pOptions,OverridePrcntFree);
      REPORTTEXTFIELD( ss, pOptions,OvrdRBLThrshld);
      REPORTTEXTFIELD( ss, pOptions,CommonCurrency);
      REPORTTEXTFIELD( ss, pOptions,RBLThrshldDflt);
      REPORTTEXTFIELD( ss, pOptions,DispRBLSysThrshld);
      REPORTTEXTFIELD( ss, pOptions,ShrAddressFormat);
      REPORTTEXTFIELD( ss, pOptions,FundLimitOverride);
      REPORTTEXTFIELD( ss, pOptions,RestrictAMSBroker);
      REPORTTEXTFIELD( ss, pOptions,NetworkOrder);
      REPORTTEXTFIELD( ss, pOptions,EarlyPWFeeElig);
      REPORTTEXTFIELD( ss, pOptions,ShortTermTRFeeElig);
      REPORTTEXTFIELD( ss, pOptions,MailingByFundGroup);
      REPORTTEXTFIELD( ss, pOptions,ATFeeApply);
      REPORTTEXTFIELD( ss, pOptions,FeeOverrideType);
      REPORTTEXTFIELD( ss, pOptions,SummitAccountsLowerBound);
      REPORTTEXTFIELD( ss, pOptions,SummitAccountsUpperBound);
      REPORTTEXTFIELD( ss, pOptions,RRIFToAlloc);
      REPORTTEXTFIELD( ss, pOptions,ACHTrailerFee);
      REPORTTEXTFIELD( ss, pOptions,ACHCommission);
      REPORTTEXTFIELD( ss, pOptions,ACHDividend);
      REPORTTEXTFIELD( ss, pOptions,KYCAccountLevel);
      REPORTTEXTFIELD( ss, pOptions,AllowRetMailAutomation);
      REPORTTEXTFIELD( ss, pOptions,NoWithTax);
      REPORTTEXTFIELD( ss, pOptions,TaxOnRRIFRed);
      REPORTTEXTFIELD( ss, pOptions,WithTaxOverride);
      REPORTTEXTFIELD( ss, pOptions,AutomaticAll);
      REPORTTEXTFIELD( ss, pOptions,RIFTTaxableRedCode);
      REPORTTEXTFIELD( ss, pOptions,FullRedCode);
      REPORTTEXTFIELD( ss, pOptions,AllowMultiFundTransfer);
      REPORTTEXTFIELD( ss, pOptions,SalutationFormat);
      REPORTTEXTFIELD( ss, pOptions,DefaultBankInstCode);
      REPORTTEXTFIELD( ss, pOptions,NASUPopupOptions);
      REPORTTEXTFIELD( ss, pOptions,AFBAgentCoCode);
      REPORTTEXTFIELD( ss, pOptions,DefaultSTTRFlag);
      REPORTTEXTFIELD( ss, pOptions,DefaultERFlag);
      REPORTTEXTFIELD( ss, pOptions,ADLevyFee);
      REPORTTEXTFIELD( ss, pOptions,ADLevyFeeTransType);
      REPORTTEXTFIELD( ss, pOptions,FndMrgRedCod);
      REPORTTEXTFIELD( ss, pOptions,NSCCCompliant);
      REPORTTEXTFIELD( ss, pOptions,NSCCCurrencyList);
      REPORTTEXTFIELD( ss, pOptions,STTRFeeExclRedCodeList);
      REPORTTEXTFIELD( ss, pOptions,EntityRiskLevel);
      REPORTTEXTFIELD( ss, pOptions,EqualizationActive);
      REPORTTEXTFIELD( ss, pOptions,RegisteredTaxTypes);
      REPORTTEXTFIELD( ss, pOptions,AntiDilutionCalc);
      REPORTTEXTFIELD( ss, pOptions,UFactorCodes);
      REPORTTEXTFIELD( ss, pOptions,ACHPurch);
      REPORTTEXTFIELD( ss, pOptions,ACHSWP);
      REPORTTEXTFIELD( ss, pOptions,ACHAdminFee);
      REPORTTEXTFIELD( ss, pOptions,ClearingIdDefault);
      REPORTTEXTFIELD( ss, pOptions,ErrorAcctNum);
      REPORTTEXTFIELD( ss, pOptions,FundBrokerApplicable);
      REPORTTEXTFIELD( ss, pOptions,ValidNetworkType);
      REPORTTEXTFIELD( ss, pOptions,NetworkTypeUpd);
      REPORTTEXTFIELD( ss, pOptions,EUSDParticip);
      REPORTTEXTFIELD( ss, pOptions,DefEUSDOption);
      REPORTTEXTFIELD( ss, pOptions,VerCancTrd);
      REPORTTEXTFIELD( ss, pOptions,ActCatNegBal);
      REPORTTEXTFIELD( ss, pOptions,ActCatWireSett);
      REPORTTEXTFIELD( ss, pOptions,BackDatedReason);
      REPORTTEXTFIELD( ss, pOptions,Accountable);
      REPORTTEXTFIELD( ss, pOptions,OPCConfirmsBrokerScreen);
      REPORTTEXTFIELD( ss, pOptions,JumboPriceApplicable);
      REPORTTEXTFIELD( ss, pOptions,ClawbackBasedOnDate);
      REPORTTEXTFIELD( ss, pOptions,EUSDOption);
      REPORTTEXTFIELD( ss, pOptions,SuppressInactiveFunds);
      REPORTTEXTFIELD( ss, pOptions,ExemptLevelList);
      REPORTTEXTFIELD( ss, pOptions,AccessLevelCat);
      REPORTTEXTFIELD( ss, pOptions,GWOSupported);
      REPORTTEXTFIELD( ss, pOptions,AssigneeScreen);
      REPORTTEXTFIELD( ss, pOptions,Address1);
      REPORTTEXTFIELD( ss, pOptions,Address2);
      REPORTTEXTFIELD( ss, pOptions,Address3);
      REPORTTEXTFIELD( ss, pOptions,Address4);
      REPORTTEXTFIELD( ss, pOptions,Address5);
      REPORTTEXTFIELD( ss, pOptions,PostalCode);
      REPORTTEXTFIELD( ss, pOptions,CountryCode);
      REPORTTEXTFIELD( ss, pOptions,ClientName);
      REPORTTEXTFIELD( ss, pOptions,RedPayEntExist);
      REPORTTEXTFIELD( ss, pOptions,IsRRIFUnusedMaxApp);
      REPORTTEXTFIELD( ss, pOptions,CompanyCode);
      REPORTTEXTFIELD( ss, pOptions,JointDefaultDisposition);
      REPORTTEXTFIELD( ss, pOptions,BackWithholdTax);
      REPORTTEXTFIELD( ss, pOptions,ConsolTransType);
      REPORTTEXTFIELD( ss, pOptions,Consolidation);
      REPORTTEXTFIELD( ss, pOptions,ConsolDefault);
      REPORTTEXTFIELD( ss, pOptions,PurchNetting);
      REPORTTEXTFIELD( ss, pOptions,DftOrdTypeTR);
      REPORTTEXTFIELD( ss, pOptions,DftOrdTypeEX);
      REPORTTEXTFIELD( ss, pOptions,DftOrdTypeDSK);
      REPORTTEXTFIELD( ss, pOptions,CSSStopSINMatch);
      REPORTTEXTFIELD( ss, pOptions,AMSFreqOvrd);
      REPORTTEXTFIELD( ss, pOptions,RebalanceDay);
      REPORTTEXTFIELD( ss, pOptions,DistribChkAllowTfr);
      REPORTTEXTFIELD( ss, pOptions,KYCLevel);
      REPORTTEXTFIELD( ss, pOptions,MFRCorporateFund);
      REPORTTEXTFIELD( ss, pOptions,NetOfFeesDate);
      REPORTTEXTFIELD( ss, pOptions,DispHistUnitACB);
      REPORTTEXTFIELD( ss, pOptions,DivDates);
      REPORTTEXTFIELD( ss, pOptions,SwitchBanks);
      REPORTTEXTFIELD( ss, pOptions,CheckCloseBatch);
      REPORTTEXTFIELD( ss, pOptions,DefltFeeOption);
      REPORTTEXTFIELD( ss, pOptions,OnLineEntExcept);
      REPORTTEXTFIELD( ss, pOptions,UnitRoundingApplicable);
      REPORTTEXTFIELD( ss, pOptions,UnitRoundMethod);
      REPORTTEXTFIELD( ss, pOptions,RegDocsExist);
      REPORTTEXTFIELD( ss, pOptions,DeathClaimDocExist);
      REPORTTEXTFIELD( ss, pOptions,UnregPlan);
      REPORTTEXTFIELD( ss, pOptions,NonregLike);
      REPORTTEXTFIELD( ss, pOptions,IntRIFPlan);
      REPORTTEXTFIELD( ss, pOptions,ExtRIFPlan);
      REPORTTEXTFIELD( ss, pOptions,AllRIFPlan);
      REPORTTEXTFIELD( ss, pOptions,IntLIRAPlan);
      REPORTTEXTFIELD( ss, pOptions,AllLIRAPlan);
      REPORTTEXTFIELD( ss, pOptions,IntRESP);
      REPORTTEXTFIELD( ss, pOptions,IntRSP);
      REPORTTEXTFIELD( ss, pOptions,TaxJurisUpdateOpt);
      REPORTTEXTFIELD( ss, pOptions,RetMailOrStlDtChqAlert);
      REPORTTEXTFIELD( ss, pOptions,DeathClaimRedCodes);
      REPORTTEXTFIELD( ss, pOptions,IntLockInPlan);
      REPORTTEXTFIELD( ss, pOptions,AlwdTaxType);
      REPORTTEXTFIELD( ss, pOptions,LIRALike);
      REPORTTEXTFIELD( ss, pOptions,LIFLike);
      REPORTTEXTFIELD( ss, pOptions,FELCommOnGrant);
      REPORTTEXTFIELD( ss, pOptions,AllocTypeForBrokerValidation);
      REPORTTEXTFIELD( ss, pOptions,TFSATaxList);
      REPORTTEXTFIELD( ss, pOptions,AutoBatch);
      REPORTTEXTFIELD( ss, pOptions,ClosedCountryApplicable);
      REPORTTEXTFIELD( ss, pOptions,DskPCLookEnb);
      REPORTTEXTFIELD( ss, pOptions,DirectDepositBankApplicable);
      REPORTTEXTFIELD( ss, pOptions,VersionLabel);
      REPORTTEXTFIELD( ss, pOptions,CompanyUrl);
      REPORTTEXTFIELD( ss, pOptions,SettleLocOpt);
      REPORTTEXTFIELD( ss, pOptions,TUPActive);
      REPORTTEXTFIELD( ss, pOptions,TerminationAgeBeforeDeff);
      REPORTTEXTFIELD( ss, pOptions,TerminationAgeAfterDeff);
      REPORTTEXTFIELD( ss, pOptions,RESPAgeLimitsDeff);
      REPORTTEXTFIELD( ss, pOptions,GuaranteeGuardOn);
      REPORTTEXTFIELD( ss, pOptions,TrailerFeeArch);
      REPORTTEXTFIELD( ss, pOptions,AllowChqChange);
      REPORTTEXTFIELD( ss, pOptions,TFSAAcctCatCodeList);
      REPORTTEXTFIELD( ss, pOptions,RRSPAcctCatCodeList);
      REPORTTEXTFIELD( ss, pOptions,NetworkRespReqApplicable);
      REPORTTEXTFIELD( ss, pOptions,NetworkIDForAmountTrade);
      REPORTTEXTFIELD( ss, pOptions,AllEFTConsolActive);
      REPORTTEXTFIELD( ss, pOptions,BulkBackDate);
      REPORTTEXTFIELD( ss, pOptions,AllEFTConsolShrLv);
      REPORTTEXTFIELD( ss, pOptions,ACBUnitOffset);
      REPORTTEXTFIELD( ss, pOptions,EAPEarningCodes);
      REPORTTEXTFIELD( ss, pOptions,IWTEnable);
      REPORTTEXTFIELD( ss, pOptions,IWTTaxJurisList);
      REPORTTEXTFIELD( ss, pOptions,NonReceiptApplicable);
      REPORTTEXTFIELD( ss, pOptions,GuaranteeCalcByRules);
      REPORTTEXTFIELD( ss, pOptions,PorfolioIsRequried);
      REPORTTEXTFIELD( ss, pOptions,SOFforSGMR);
      REPORTTEXTFIELD( ss, pOptions,SourceOfFund);
      REPORTTEXTFIELD( ss, pOptions,StmtFreqDefault);
      REPORTTEXTFIELD( ss, pOptions,StmtFreqList);
      REPORTTEXTFIELD( ss, pOptions,RedCodesGuaranteeOverride);
      REPORTTEXTFIELD( ss, pOptions,CPFActiveFlag);
      REPORTTEXTFIELD( ss, pOptions,PrintAcctConf);
      REPORTTEXTFIELD( ss, pOptions,LanguageDefault);
      REPORTTEXTFIELD( ss, pOptions,EmpAgentAppl);
      REPORTTEXTFIELD( ss, pOptions,FundEliPSG);
      REPORTTEXTFIELD( ss, pOptions,FundSERVValidation);
      REPORTTEXTFIELD( ss, pOptions,LTAIndicator);
      REPORTTEXTFIELD( ss, pOptions,ModifyCompAgent);
      REPORTTEXTFIELD( ss, pOptions,SourceOfFundApp);
      REPORTTEXTFIELD( ss, pOptions,RefundRVCD);
      REPORTTEXTFIELD( ss, pOptions,FundAlloc);
      REPORTTEXTFIELD( ss, pOptions,NFConfBnkDetl);
      REPORTTEXTFIELD( ss, pOptions,RefundCalc);
      REPORTTEXTFIELD( ss, pOptions,DilutionCalc);
      REPORTTEXTFIELD( ss, pOptions,SrcOfFunds_IA_Required);
      REPORTTEXTFIELD( ss, pOptions,SrcOfFunds_IA_ED);
      REPORTTEXTFIELD( ss, pOptions,SrcOfFunds_IA_PW);
      REPORTTEXTFIELD( ss, pOptions,SrcOfFunds_IA_GIC);
      REPORTTEXTFIELD( ss, pOptions,SrcOfFunds_IA_SWP);
      REPORTTEXTFIELD( ss, pOptions,SrcOfFunds_IA_RIF);
      REPORTTEXTFIELD( ss, pOptions,TaxAnniversary);
      REPORTTEXTFIELD( ss, pOptions,RightToCancelDefault);
      REPORTTEXTFIELD( ss, pOptions,FATCAApplicable);
      REPORTTEXTFIELD( ss, pOptions,RDREnv);
      REPORTTEXTFIELD( ss, pOptions,ApplFeeModelType);
      REPORTTEXTFIELD( ss, pOptions,AutoGenFeeModelCode);
      REPORTTEXTFIELD( ss, pOptions,AutoStopAssociation);
      REPORTTEXTFIELD( ss, pOptions,ListDocType);
      REPORTTEXTFIELD( ss, pOptions,InvApplicable);
      REPORTTEXTFIELD( ss, pOptions,RptGrpApplicable);
      REPORTTEXTFIELD( ss, pOptions,MstrActActive);
      REPORTTEXTFIELD( ss, pOptions,MstrActAttrbName);
      REPORTTEXTFIELD( ss, pOptions,MstrActAttrbValue);
	  REPORTTEXTFIELD( ss, pOptions,IsTrlFeeAcctLevelApp);
	  REPORTTEXTFIELD( ss, pOptions,ReportFFIType);
      REPORTTEXTFIELD( ss, pOptions,RetMailUpdt);
	  REPORTTEXTFIELD( ss, pOptions,AllowBankUpdOnProcessedPAC);

      // View 263
      REPORTTEXTFIELD( ss, pOptions,DefaultRebFreq);
      REPORTTEXTFIELD( ss, pOptions,DefaultRoundFund);
      REPORTTEXTFIELD( ss, pOptions,DefaultRoundClass);
      REPORTTEXTFIELD( ss, pOptions,UpdAMSOnNewAcct);
      REPORTTEXTFIELD( ss, pOptions,DefaultAllocOverride);
      REPORTTEXTFIELD( ss, pOptions,PACSWPOverride);
      REPORTTEXTFIELD( ss, pOptions,NextRebDateApplicable);

      // View 344
      REPORTTEXTFIELD( ss, pOptions,TransTypeDefault);
      REPORTTEXTFIELD( ss, pOptions,TradeAmtTypeDefault);
      REPORTTEXTFIELD( ss, pOptions,TradePayTypeDefault);
      REPORTTEXTFIELD( ss, pOptions,TradeClearMethodDefault);
      REPORTTEXTFIELD( ss, pOptions,TradeFileProcessorDefault);
      REPORTTEXTFIELD( ss, pOptions,TrxSettCurrRefresh);
      REPORTTEXTFIELD( ss, pOptions,CanSuppressConfirm);
      REPORTTEXTFIELD( ss, pOptions,ROATransType);
      REPORTTEXTFIELD( ss, pOptions,DefaultExchRate);
      REPORTTEXTFIELD( ss, pOptions,MCHSRActive);
      REPORTTEXTFIELD( ss, pOptions,MCHNewTrade);
      REPORTTEXTFIELD( ss, pOptions,MCHRbkTrade);
      REPORTTEXTFIELD( ss, pOptions,MCHIndCancel);
      REPORTTEXTFIELD( ss, pOptions,MCHBulkCancel);
      REPORTTEXTFIELD( ss, pOptions,MCHBulkRbk);
      REPORTTEXTFIELD( ss, pOptions,SRNewTrade);
      REPORTTEXTFIELD( ss, pOptions,SRRbkTrade);
      REPORTTEXTFIELD( ss, pOptions,SRIndCancel);
      REPORTTEXTFIELD( ss, pOptions,SRBulkCancel);
      REPORTTEXTFIELD( ss, pOptions,SRBulkRbk);
      REPORTTEXTFIELD( ss, pOptions,SWPSettleESGElig);
      REPORTTEXTFIELD( ss, pOptions,CashIDSettleESGElig);
      REPORTTEXTFIELD( ss, pOptions,SDRTReportFlag);
      REPORTTEXTFIELD( ss, pOptions,AWDFieldFlag);
      REPORTTEXTFIELD( ss, pOptions,PSDAdvice);
      REPORTTEXTFIELD( ss, pOptions,PymtRoutingMthd);
      REPORTTEXTFIELD( ss, pOptions,TradelevelOveride);
      REPORTTEXTFIELD( ss, pOptions,DefPymtRoutingMthd);
      REPORTTEXTFIELD( ss, pOptions,StopOverrideRule);
   }
   ss << std::endl;
}

BEGIN_MESSAGE_MAP(AboutPropMgmtOptionsPage, CPropertyPage)
END_MESSAGE_MAP()

void AboutPropMgmtOptionsPage::AddTextField( const DString& dstrName, BFCBO* pCBO, const BFFieldId& idField ) {
   DString dstrValue;
   pCBO->getField(idField, dstrValue, BF::HOST );

   int idx = m_optionList.InsertItem( m_optionCount++, I_( "" ) );

   m_optionList.SetItemText( idx, 0, dstrName.c_str() );
   m_optionList.SetItemText( idx, 1, dstrValue.c_str() );
}

void AboutPropMgmtOptionsPage::AddTextFields( const BFDataId& dataID, BFCBO* pCBO ) {
   DString dstrValue;
   BFData queryData(dataID);

   unsigned int iNumField = queryData.getFieldCount();

   for(unsigned int i=0;i<iNumField;i++)
   {
      const BFDataField& dataField = queryData.getElementByIndex( i );
      pCBO->getField(dataField.getId(), dstrValue, BF::HOST );

      int idx = m_optionList.InsertItem( m_optionCount++, I_( "" ) );

      m_optionList.SetItemText( idx, 0, BFFieldId(dataField.getId()).getName().c_str() );
      m_optionList.SetItemText( idx, 1, dstrValue.c_str() );
   }
}

void AboutPropMgmtOptionsPage::AddTextSeparator( const DString& dstrCol0, const DString& dstrCol1 ) {
   int idx = m_optionList.InsertItem( m_optionCount++, I_( "" ) );

   m_optionList.SetItemText( idx, 0, dstrCol0.c_str() );
   m_optionList.SetItemText( idx, 1, dstrCol1.c_str() );
}

void AboutPropMgmtOptionsPage::AddTextBlankLineSeparator( ) {
   int idx = m_optionList.InsertItem( m_optionCount++, I_( "" ) );

   DString dstrCol0(I_("")),dstrCol1(I_(""));
   m_optionList.SetItemText( idx, 0, dstrCol0.c_str() );
   m_optionList.SetItemText( idx, 1, dstrCol1.c_str() );
}

// AboutPropMgmtOptionsPage message handlers
BOOL AboutPropMgmtOptionsPage::OnInitDialog()
{
   CPropertyPage::OnInitDialog();

   CWaitCursor waiter;

   m_optionList.InsertColumn( 0, I_("Name"), LVCFMT_LEFT, 100 );
   m_optionList.InsertColumn( 1, I_("Value"), LVCFMT_LEFT, 300 );

   MgmtCoOptions* pOptions = NULL;
   pMgmtCo_->getMgmtCoOptions( pOptions );

   bool bShowMGMTOptionsSeparator = GetConfigValueAsBool( I_("MFDSTC"), I_("Debug"), I_("ShowMGMTOptionsSeparator") );

   if( NULL != pOptions ) {
      // View 83

      DString dstrCol0, dstrCol1;

      dstrCol0 = I_("View 83");
      if(bShowMGMTOptionsSeparator)
      {
         AddTextSeparator(dstrCol0,dstrCol1);
      }

      //ADDTEXTFIELD(pOptions,SysCurrency);
      //ADDTEXTFIELD(pOptions,ShrNumCtrl);
      //ADDTEXTFIELD(pOptions,ShrNumVal);
      //ADDTEXTFIELD(pOptions,AcctNumCtrl);
      //ADDTEXTFIELD(pOptions,AcctNumVal);
      //ADDTEXTFIELD(pOptions,DefaultGrp);
      //ADDTEXTFIELD(pOptions,GrpCodeLevel);
      //ADDTEXTFIELD(pOptions,TaxTypeUpd);
      //ADDTEXTFIELD(pOptions,MktMailDef);
      //ADDTEXTFIELD(pOptions,RepByBranch);
      //ADDTEXTFIELD(pOptions,BrokerBranch);
      //ADDTEXTFIELD(pOptions,CapAddress);
      //ADDTEXTFIELD(pOptions,CountryVal);
      //ADDTEXTFIELD(pOptions,MandatoryId);
      //ADDTEXTFIELD(pOptions,BirthNameMand);
      //ADDTEXTFIELD(pOptions,SinException);
      //ADDTEXTFIELD(pOptions,ShadowNominee);
      //ADDTEXTFIELD(pOptions,BankValid1);
      //ADDTEXTFIELD(pOptions,BankValid2);
      //ADDTEXTFIELD(pOptions,BankLayout);
      //ADDTEXTFIELD(pOptions,SYMBrkUpd);
      //ADDTEXTFIELD(pOptions,BrokerFund);
      //ADDTEXTFIELD(pOptions,PACMinAmt);
      //ADDTEXTFIELD(pOptions,PACAmtEdit);
      //ADDTEXTFIELD(pOptions,GICAllocOnly);
      //ADDTEXTFIELD(pOptions,DisableFee4Alloc);
      //ADDTEXTFIELD(pOptions,BusRounding);
      //ADDTEXTFIELD(pOptions,MultiCurrency);
      //ADDTEXTFIELD(pOptions,SplitComm);
      //ADDTEXTFIELD(pOptions,AcctFeeParm);
      //ADDTEXTFIELD(pOptions,CappedFund);
      //ADDTEXTFIELD(pOptions,BankingFormat);
      //ADDTEXTFIELD(pOptions,InstCodeMax);
      //ADDTEXTFIELD(pOptions,TransitNoMax);
      //ADDTEXTFIELD(pOptions,BankAcctNumMax);
      //ADDTEXTFIELD(pOptions,CurrBusDate);
      //ADDTEXTFIELD(pOptions,MandAddLines);
      //ADDTEXTFIELD(pOptions,CurrSysDate);
      //ADDTEXTFIELD(pOptions,CurrSysTime);
      //ADDTEXTFIELD(pOptions,ChkDuplicationTrade);
      //ADDTEXTFIELD(pOptions,InvAdvice);
      //ADDTEXTFIELD(pOptions,AcqFeeDefault);
      //ADDTEXTFIELD(pOptions,LastCycleDate);
      //ADDTEXTFIELD(pOptions,AccountableMandatory);
      //ADDTEXTFIELD(pOptions,SplitAcCode);
      //ADDTEXTFIELD(pOptions,TRExclRedCodes);
      //ADDTEXTFIELD(pOptions,TIKRedCodes);
      //ADDTEXTFIELD(pOptions,DealDateTime);
      //ADDTEXTFIELD(pOptions,EFTPurchase);
      //ADDTEXTFIELD(pOptions,EFTPurchFuture);
      //ADDTEXTFIELD(pOptions,GrpContribution);
      //ADDTEXTFIELD(pOptions,AllowFractions);
      //ADDTEXTFIELD(pOptions,SplitCommTransTypes);
      //ADDTEXTFIELD(pOptions,CashReceiptTrack);
      //ADDTEXTFIELD(pOptions,DepositId2);
      //ADDTEXTFIELD(pOptions,DepositIdMandatory);
      //ADDTEXTFIELD(pOptions,DefaultPurchPayType);
      //ADDTEXTFIELD(pOptions,EFTPurchaseLeadDays);
      //ADDTEXTFIELD(pOptions,CharWireNum);
      //ADDTEXTFIELD(pOptions,WireNumMandatory);
      //ADDTEXTFIELD(pOptions,WireNumDefault);
      //ADDTEXTFIELD(pOptions,SrcOfFundMandatory);
      //ADDTEXTFIELD(pOptions,RRIFPrevYear);
      //ADDTEXTFIELD(pOptions,RRIFOrPayment);
      //ADDTEXTFIELD(pOptions,RRIFValidation);
      //ADDTEXTFIELD(pOptions,FundAllocLimit);
      //ADDTEXTFIELD(pOptions,AMSOrder);
      //ADDTEXTFIELD(pOptions,DefSetlCurrency);
      //ADDTEXTFIELD(pOptions,PrevBusDate);
      //ADDTEXTFIELD(pOptions,CurrChkByTaxType);
      //ADDTEXTFIELD(pOptions,EuroAddrFormat);
      //ADDTEXTFIELD(pOptions,InvalidCurr);
      //ADDTEXTFIELD(pOptions,TaxTypeByCurrChk);
      //ADDTEXTFIELD(pOptions,SegClient);
      //ADDTEXTFIELD(pOptions,CotClient);
      //ADDTEXTFIELD(pOptions,ResClient);
      //ADDTEXTFIELD(pOptions,LipClient);
      //ADDTEXTFIELD(pOptions,T550ReportMethod);
      //ADDTEXTFIELD(pOptions,ShrEFTConsol);
      //ADDTEXTFIELD(pOptions,PACSWPEFTConsol);
      //ADDTEXTFIELD(pOptions,Unseizable);
      //ADDTEXTFIELD(pOptions,RdLckdE);
      //ADDTEXTFIELD(pOptions,RdLckdW);
      //ADDTEXTFIELD(pOptions,TitleRestrict);
      //ADDTEXTFIELD(pOptions,EditDeffs);
      //ADDTEXTFIELD(pOptions,RoundFlag);
      //ADDTEXTFIELD(pOptions,RedAccruedInt);
      //ADDTEXTFIELD(pOptions,PQLIFLIRARedCodes);
      //ADDTEXTFIELD(pOptions,PQLIFLIRAJuris);
      //ADDTEXTFIELD(pOptions,PQLIFLIRAAage);
      //ADDTEXTFIELD(pOptions,PQLIFLIRAMaxPrct);
      //ADDTEXTFIELD(pOptions,PQLIFLIRATaxType);
      //ADDTEXTFIELD(pOptions,AutoBanking);
      //ADDTEXTFIELD(pOptions,RdAcctCurrency);
      //ADDTEXTFIELD(pOptions,BankSrcAcct);
      //ADDTEXTFIELD(pOptions,SourceOffFund);
      //ADDTEXTFIELD(pOptions,ModRecipType);
      //ADDTEXTFIELD(pOptions,SpecAcctNum);
      //ADDTEXTFIELD(pOptions,TradeCutOff);
      //ADDTEXTFIELD(pOptions,PartTransAsFull);
      //ADDTEXTFIELD(pOptions,CheqDeliveryDefault);
      //ADDTEXTFIELD(pOptions,SplitComm100);
      //ADDTEXTFIELD(pOptions,CashDistribRule);
      //ADDTEXTFIELD(pOptions,ValidDistributionPayType);
      //ADDTEXTFIELD(pOptions,AllFundsTransfers);
      //ADDTEXTFIELD(pOptions,TfrToDiffSH);
      //ADDTEXTFIELD(pOptions,DeathRedCode);
      //ADDTEXTFIELD(pOptions,SpouseBenefReLn);
      //ADDTEXTFIELD(pOptions,ChildBenefReLn);
      //ADDTEXTFIELD(pOptions,MultiAcctEachShrNum);
      //ADDTEXTFIELD(pOptions,UpdOrdType);
      //ADDTEXTFIELD(pOptions,CommissionType);
      //ADDTEXTFIELD(pOptions,Residency1);
      //ADDTEXTFIELD(pOptions,Residency2);
      //ADDTEXTFIELD(pOptions,Residency3);
      //ADDTEXTFIELD(pOptions,DefltRedCodeFlag);
      //ADDTEXTFIELD(pOptions,DefltRedCode);
      //ADDTEXTFIELD(pOptions,FundEligSlsRepLvl);
      //ADDTEXTFIELD(pOptions,WrapAccount);
      //ADDTEXTFIELD(pOptions,DistribFundsValidate);
      //ADDTEXTFIELD(pOptions,XSFundsValidate);
      //ADDTEXTFIELD(pOptions,ClientAMSType);
      //ADDTEXTFIELD(pOptions,ClassRule);
      //ADDTEXTFIELD(pOptions,ProfileCodeDflt);
      //ADDTEXTFIELD(pOptions,MgmtFeePayOptDflt);
      //ADDTEXTFIELD(pOptions,MgmtCoPayReq);
      //ADDTEXTFIELD(pOptions,SplitPreferenceOption);
      //ADDTEXTFIELD(pOptions,RES2Client);
      //ADDTEXTFIELD(pOptions,QESIClient);
      //ADDTEXTFIELD(pOptions,PSE_EAPEditDate);
      //ADDTEXTFIELD(pOptions,EligDateforCLB);
      //ADDTEXTFIELD(pOptions,NonTrustStartDate);
      //ADDTEXTFIELD(pOptions,NonTrustStopDate);
      //ADDTEXTFIELD(pOptions,IsNonTrustee);
      //ADDTEXTFIELD(pOptions,AutoDocTracking);

      AddTextFields(ifds::DSTC0083_VW,pOptions);

      // View 149

      dstrCol0 = I_("View 149");
      if(bShowMGMTOptionsSeparator)
      {
         AddTextBlankLineSeparator();
         AddTextSeparator(dstrCol0,dstrCol1);
      }

      //ADDTEXTFIELD(pOptions,AllowMultiplePacSwp);
      //ADDTEXTFIELD(pOptions,SWPEditlevel);
      //ADDTEXTFIELD(pOptions,SWPMin);
      //ADDTEXTFIELD(pOptions,SWPHardEdit);
      //ADDTEXTFIELD(pOptions,DSCOverride);
      //ADDTEXTFIELD(pOptions,DabScreen);
      //ADDTEXTFIELD(pOptions,DepositId2);
      //ADDTEXTFIELD(pOptions,DispClientTradeID);
      //ADDTEXTFIELD(pOptions,DefaultBankType);
      //ADDTEXTFIELD(pOptions,DispManageStyle);
      //ADDTEXTFIELD(pOptions,DefaultBankUpd);
      //ADDTEXTFIELD(pOptions,SplitOnAddPur);
      //ADDTEXTFIELD(pOptions,SplitOnModPur);
      //ADDTEXTFIELD(pOptions,SplitOnReqOnly);
      //ADDTEXTFIELD(pOptions,SplitComBankDeflt);
      //ADDTEXTFIELD(pOptions,ValSplCom);
      //ADDTEXTFIELD(pOptions,SavePlanClient);
      //ADDTEXTFIELD(pOptions,PACLastRunDate);
      //ADDTEXTFIELD(pOptions,SWPLastRunDate);
      //ADDTEXTFIELD(pOptions,ManualSettleDates);
      //ADDTEXTFIELD(pOptions,ACHSavingsPlan);
      //ADDTEXTFIELD(pOptions,ACHPAC);
      //ADDTEXTFIELD(pOptions,ForeignContent);
      //ADDTEXTFIELD(pOptions,AllowUnitsPurchase);
      //ADDTEXTFIELD(pOptions,MultiCurrEFTUnitPurch);
      //ADDTEXTFIELD(pOptions,DisAllowPayTypeUnitPurch);
      //ADDTEXTFIELD(pOptions,AllowCashDistrib);
      //ADDTEXTFIELD(pOptions,PACCalendar);
      //ADDTEXTFIELD(pOptions,ProductGroupCode);
      //ADDTEXTFIELD(pOptions,TradeDateLag);
      //ADDTEXTFIELD(pOptions,TradeDateLagExch);
      //ADDTEXTFIELD(pOptions,FCRebalancing);
      //ADDTEXTFIELD(pOptions,CommFeeCodes);
      //ADDTEXTFIELD(pOptions,CalcSwitch);
      //ADDTEXTFIELD(pOptions,MiscFeeDefn);
      //ADDTEXTFIELD(pOptions,AcctLvlFIFO);
      //ADDTEXTFIELD(pOptions,CompCodeFlag);
      //ADDTEXTFIELD(pOptions,PriceProcAtFndGrp);
      //ADDTEXTFIELD(pOptions,MgmtFeeType);
      //ADDTEXTFIELD(pOptions,LLPWithdrawalRules);
      //ADDTEXTFIELD(pOptions,RRIFFromAlloc);
      //ADDTEXTFIELD(pOptions,IsoCompliant);
      //ADDTEXTFIELD(pOptions,ReviewDateFlag);
      //ADDTEXTFIELD(pOptions,OverrideReviewDate);
      //ADDTEXTFIELD(pOptions,ReviewMnths);
      //ADDTEXTFIELD(pOptions,BankChrgs);
      //ADDTEXTFIELD(pOptions,ConsolidEFT);
      //ADDTEXTFIELD(pOptions,ACHRedemption);
      //ADDTEXTFIELD(pOptions,ValueDateApplic);
      //ADDTEXTFIELD(pOptions,SettleAll);
      //ADDTEXTFIELD(pOptions,DuplicateAltAcct);
      //ADDTEXTFIELD(pOptions,BankDetlName);
      //ADDTEXTFIELD(pOptions,OPDeliveryMethods);
      //ADDTEXTFIELD(pOptions,OPDeliveryOption);
      //ADDTEXTFIELD(pOptions,CnsntToWaive);
      //ADDTEXTFIELD(pOptions,OverridePrcntFree);
      //ADDTEXTFIELD(pOptions,OvrdRBLThrshld);
      //ADDTEXTFIELD(pOptions,CommonCurrency);
      //ADDTEXTFIELD(pOptions,RBLThrshldDflt);
      //ADDTEXTFIELD(pOptions,DispRBLSysThrshld);
      //ADDTEXTFIELD(pOptions,ShrAddressFormat);
      //ADDTEXTFIELD(pOptions,FundLimitOverride);
      //ADDTEXTFIELD(pOptions,RestrictAMSBroker);
      //ADDTEXTFIELD(pOptions,NetworkOrder);
      //ADDTEXTFIELD(pOptions,EarlyPWFeeElig);
      //ADDTEXTFIELD(pOptions,ShortTermTRFeeElig);
      //ADDTEXTFIELD(pOptions,MailingByFundGroup);
      //ADDTEXTFIELD(pOptions,ATFeeApply);
      //ADDTEXTFIELD(pOptions,FeeOverrideType);
      //ADDTEXTFIELD(pOptions,SummitAccountsLowerBound);
      //ADDTEXTFIELD(pOptions,SummitAccountsUpperBound);
      //ADDTEXTFIELD(pOptions,RRIFToAlloc);
      //ADDTEXTFIELD(pOptions,ACHTrailerFee);
      //ADDTEXTFIELD(pOptions,ACHCommission);
      //ADDTEXTFIELD(pOptions,ACHDividend);
      //ADDTEXTFIELD(pOptions,KYCAccountLevel);
      //ADDTEXTFIELD(pOptions,AllowRetMailAutomation);
      //ADDTEXTFIELD(pOptions,NoWithTax);
      //ADDTEXTFIELD(pOptions,TaxOnRRIFRed);
      //ADDTEXTFIELD(pOptions,WithTaxOverride);
      //ADDTEXTFIELD(pOptions,AutomaticAll);
      //ADDTEXTFIELD(pOptions,RIFTTaxableRedCode);
      //ADDTEXTFIELD(pOptions,FullRedCode);
      //ADDTEXTFIELD(pOptions,AllowMultiFundTransfer);
      //ADDTEXTFIELD(pOptions,SalutationFormat);
      //ADDTEXTFIELD(pOptions,DefaultBankInstCode);
      //ADDTEXTFIELD(pOptions,NASUPopupOptions);
      //ADDTEXTFIELD(pOptions,AFBAgentCoCode);
      //ADDTEXTFIELD(pOptions,DefaultSTTRFlag);
      //ADDTEXTFIELD(pOptions,DefaultERFlag);
      //ADDTEXTFIELD(pOptions,ADLevyFee);
      //ADDTEXTFIELD(pOptions,ADLevyFeeTransType);
      //ADDTEXTFIELD(pOptions,FndMrgRedCod);
      //ADDTEXTFIELD(pOptions,NSCCCompliant);
      //ADDTEXTFIELD(pOptions,NSCCCurrencyList);
      //ADDTEXTFIELD(pOptions,STTRFeeExclRedCodeList);
      //ADDTEXTFIELD(pOptions,EntityRiskLevel);
      //ADDTEXTFIELD(pOptions,EqualizationActive);
      //ADDTEXTFIELD(pOptions,RegisteredTaxTypes);
      //ADDTEXTFIELD(pOptions,AntiDilutionCalc);
      //ADDTEXTFIELD(pOptions,UFactorCodes);
      //ADDTEXTFIELD(pOptions,ACHPurch);
      //ADDTEXTFIELD(pOptions,ACHSWP);
      //ADDTEXTFIELD(pOptions,ACHAdminFee);
      //ADDTEXTFIELD(pOptions,ClearingIdDefault);
      //ADDTEXTFIELD(pOptions,ErrorAcctNum);
      //ADDTEXTFIELD(pOptions,FundBrokerApplicable);
      //ADDTEXTFIELD(pOptions,ValidNetworkType);
      //ADDTEXTFIELD(pOptions,NetworkTypeUpd);
      //ADDTEXTFIELD(pOptions,EUSDParticip);
      //ADDTEXTFIELD(pOptions,DefEUSDOption);
      //ADDTEXTFIELD(pOptions,VerCancTrd);
      //ADDTEXTFIELD(pOptions,ActCatNegBal);
      //ADDTEXTFIELD(pOptions,ActCatWireSett);
      //ADDTEXTFIELD(pOptions,BackDatedReason);
      //ADDTEXTFIELD(pOptions,Accountable);
      //ADDTEXTFIELD(pOptions,OPCConfirmsBrokerScreen);
      //ADDTEXTFIELD(pOptions,JumboPriceApplicable);
      //ADDTEXTFIELD(pOptions,ClawbackBasedOnDate);
      //ADDTEXTFIELD(pOptions,EUSDOption);
      //ADDTEXTFIELD(pOptions,SuppressInactiveFunds);
      //ADDTEXTFIELD(pOptions,ExemptLevelList);
      //ADDTEXTFIELD(pOptions,AccessLevelCat);
      //ADDTEXTFIELD(pOptions,GWOSupported);
      //ADDTEXTFIELD(pOptions,AssigneeScreen);
      //ADDTEXTFIELD(pOptions,Address1);
      //ADDTEXTFIELD(pOptions,Address2);
      //ADDTEXTFIELD(pOptions,Address3);
      //ADDTEXTFIELD(pOptions,Address4);
      //ADDTEXTFIELD(pOptions,Address5);
      //ADDTEXTFIELD(pOptions,PostalCode);
      //ADDTEXTFIELD(pOptions,CountryCode);
      //ADDTEXTFIELD(pOptions,ClientName);
      //ADDTEXTFIELD(pOptions,RedPayEntExist);
      //ADDTEXTFIELD(pOptions,IsRRIFUnusedMaxApp);
      //ADDTEXTFIELD(pOptions,CompanyCode);
      //ADDTEXTFIELD(pOptions,JointDefaultDisposition);
      //ADDTEXTFIELD(pOptions,BackWithholdTax);
      //ADDTEXTFIELD(pOptions,ConsolTransType);
      //ADDTEXTFIELD(pOptions,Consolidation);
      //ADDTEXTFIELD(pOptions,ConsolDefault);
      //ADDTEXTFIELD(pOptions,PurchNetting);
      //ADDTEXTFIELD(pOptions,DftOrdTypeTR);
      //ADDTEXTFIELD(pOptions,DftOrdTypeEX);
      //ADDTEXTFIELD(pOptions,DftOrdTypeDSK);
      //ADDTEXTFIELD(pOptions,CSSStopSINMatch);
      //ADDTEXTFIELD(pOptions,AMSFreqOvrd);
      //ADDTEXTFIELD(pOptions,RebalanceDay);
      //ADDTEXTFIELD(pOptions,DistribChkAllowTfr);
      //ADDTEXTFIELD(pOptions,KYCLevel);
      //ADDTEXTFIELD(pOptions,MFRCorporateFund);
      //ADDTEXTFIELD(pOptions,NetOfFeesDate);
      //ADDTEXTFIELD(pOptions,DispHistUnitACB);
      //ADDTEXTFIELD(pOptions,DivDates);
      //ADDTEXTFIELD(pOptions,SwitchBanks);
      //ADDTEXTFIELD(pOptions,CheckCloseBatch);
      //ADDTEXTFIELD(pOptions,DefltFeeOption);
      //ADDTEXTFIELD(pOptions,OnLineEntExcept);
      //ADDTEXTFIELD(pOptions,UnitRoundingApplicable);
      //ADDTEXTFIELD(pOptions,UnitRoundMethod);
      //ADDTEXTFIELD(pOptions,RegDocsExist);
      //ADDTEXTFIELD(pOptions,DeathClaimDocExist);
      //ADDTEXTFIELD(pOptions,UnregPlan);
      //ADDTEXTFIELD(pOptions,NonregLike);
      //ADDTEXTFIELD(pOptions,IntRIFPlan);
      //ADDTEXTFIELD(pOptions,ExtRIFPlan);
      //ADDTEXTFIELD(pOptions,AllRIFPlan);
      //ADDTEXTFIELD(pOptions,IntLIRAPlan);
      //ADDTEXTFIELD(pOptions,AllLIRAPlan);
      //ADDTEXTFIELD(pOptions,IntRESP);
      //ADDTEXTFIELD(pOptions,IntRSP);
      //ADDTEXTFIELD(pOptions,TaxJurisUpdateOpt);
      //ADDTEXTFIELD(pOptions,RetMailOrStlDtChqAlert);
      //ADDTEXTFIELD(pOptions,DeathClaimRedCodes);
      //ADDTEXTFIELD(pOptions,IntLockInPlan);
      //ADDTEXTFIELD(pOptions,AlwdTaxType);
      //ADDTEXTFIELD(pOptions,LIRALike);
      //ADDTEXTFIELD(pOptions,LIFLike);
      //ADDTEXTFIELD(pOptions,FELCommOnGrant);
      //ADDTEXTFIELD(pOptions,AllocTypeForBrokerValidation);
      //ADDTEXTFIELD(pOptions,TFSATaxList);
      //ADDTEXTFIELD(pOptions,AutoBatch);
      //ADDTEXTFIELD(pOptions,ClosedCountryApplicable);
      //ADDTEXTFIELD(pOptions,DskPCLookEnb);
      //ADDTEXTFIELD(pOptions,DirectDepositBankApplicable);
      //ADDTEXTFIELD(pOptions,VersionLabel);
      //ADDTEXTFIELD(pOptions,CompanyUrl);
      //ADDTEXTFIELD(pOptions,SettleLocOpt);
      //ADDTEXTFIELD(pOptions,TUPActive);
      //ADDTEXTFIELD(pOptions,TerminationAgeBeforeDeff);
      //ADDTEXTFIELD(pOptions,TerminationAgeAfterDeff);
      //ADDTEXTFIELD(pOptions,RESPAgeLimitsDeff);
      //ADDTEXTFIELD(pOptions,GuaranteeGuardOn);
      //ADDTEXTFIELD(pOptions,TrailerFeeArch);
      //ADDTEXTFIELD(pOptions,AllowChqChange);
      //ADDTEXTFIELD(pOptions,TFSAAcctCatCodeList);
      //ADDTEXTFIELD(pOptions,RRSPAcctCatCodeList);
      //ADDTEXTFIELD(pOptions,NetworkRespReqApplicable);
      //ADDTEXTFIELD(pOptions,NetworkIDForAmountTrade);
      //ADDTEXTFIELD(pOptions,AllEFTConsolActive);
      //ADDTEXTFIELD(pOptions,BulkBackDate);
      //ADDTEXTFIELD(pOptions,AllEFTConsolShrLv);
      //ADDTEXTFIELD(pOptions,ACBUnitOffset);
      //ADDTEXTFIELD(pOptions,EAPEarningCodes);
      //ADDTEXTFIELD(pOptions,IWTEnable);
      //ADDTEXTFIELD(pOptions,IWTTaxJurisList);
      //ADDTEXTFIELD(pOptions,NonReceiptApplicable);
      //ADDTEXTFIELD(pOptions,GuaranteeCalcByRules);
      //ADDTEXTFIELD(pOptions,PorfolioIsRequried);
      //ADDTEXTFIELD(pOptions,SOFforSGMR);
      //ADDTEXTFIELD(pOptions,SourceOfFund);
      //ADDTEXTFIELD(pOptions,StmtFreqDefault);
      //ADDTEXTFIELD(pOptions,StmtFreqList);
      //ADDTEXTFIELD(pOptions,RedCodesGuaranteeOverride);
      //ADDTEXTFIELD(pOptions,CPFActiveFlag);
      //ADDTEXTFIELD(pOptions,PrintAcctConf);
      //ADDTEXTFIELD(pOptions,LanguageDefault);
      //ADDTEXTFIELD(pOptions,EmpAgentAppl);
      //ADDTEXTFIELD(pOptions,FundEliPSG);
      //ADDTEXTFIELD(pOptions,FundSERVValidation);
      //ADDTEXTFIELD(pOptions,LTAIndicator);
      //ADDTEXTFIELD(pOptions,ModifyCompAgent);
      //ADDTEXTFIELD(pOptions,SourceOfFundApp);
      //ADDTEXTFIELD(pOptions,RefundRVCD);
      //ADDTEXTFIELD(pOptions,FundAlloc);
      //ADDTEXTFIELD(pOptions,NFConfBnkDetl);
      //ADDTEXTFIELD(pOptions,RefundCalc);
      //ADDTEXTFIELD(pOptions,DilutionCalc);
      //ADDTEXTFIELD(pOptions,SrcOfFunds_IA_Required);
      //ADDTEXTFIELD(pOptions,SrcOfFunds_IA_ED);
      //ADDTEXTFIELD(pOptions,SrcOfFunds_IA_PW);
      //ADDTEXTFIELD(pOptions,SrcOfFunds_IA_GIC);
      //ADDTEXTFIELD(pOptions,SrcOfFunds_IA_SWP);
      //ADDTEXTFIELD(pOptions,SrcOfFunds_IA_RIF);
      //ADDTEXTFIELD(pOptions,TaxAnniversary);
      //ADDTEXTFIELD(pOptions,RightToCancelDefault);
      //ADDTEXTFIELD(pOptions,FATCAApplicable);
      //ADDTEXTFIELD(pOptions,RDREnv);
      //ADDTEXTFIELD(pOptions,ApplFeeModelType);
      //ADDTEXTFIELD(pOptions,AutoGenFeeModelCode);
      //ADDTEXTFIELD(pOptions,AutoStopAssociation);
      //ADDTEXTFIELD(pOptions,ListDocType);
      //ADDTEXTFIELD(pOptions,InvApplicable);
      //ADDTEXTFIELD(pOptions,RptGrpApplicable);
      //ADDTEXTFIELD(pOptions,MstrActActive);
      //ADDTEXTFIELD(pOptions,MstrActAttrbName);
      //ADDTEXTFIELD(pOptions,MstrActAttrbValue);
      //ADDTEXTFIELD(pOptions,IsTrlFeeAcctLevelApp);
      //ADDTEXTFIELD(pOptions,ReportFFIType);
      //ADDTEXTFIELD(pOptions,RetMailUpdt);
      //ADDTEXTFIELD(pOptions,AllowBankUpdOnProcessedPAC);

      AddTextFields(ifds::DSTC0149_VW,pOptions);

      // View 263

      dstrCol0 = I_("View 263");
      if(bShowMGMTOptionsSeparator)
      {
         AddTextBlankLineSeparator();
         AddTextSeparator(dstrCol0,dstrCol1);
      }

      //ADDTEXTFIELD(pOptions,DefaultRebFreq);
      //ADDTEXTFIELD(pOptions,DefaultRoundFund);
      //ADDTEXTFIELD(pOptions,DefaultRoundClass);
      //ADDTEXTFIELD(pOptions,UpdAMSOnNewAcct);
      //ADDTEXTFIELD(pOptions,DefaultAllocOverride);
      //ADDTEXTFIELD(pOptions,PACSWPOverride);
      //ADDTEXTFIELD(pOptions,NextRebDateApplicable);

      AddTextFields(ifds::DSTC0263_VW,pOptions);

      // View 344

      dstrCol0 = I_("View 344");
      if(bShowMGMTOptionsSeparator)
      {
         AddTextBlankLineSeparator();
         AddTextSeparator(dstrCol0,dstrCol1);
      }

      //ADDTEXTFIELD(pOptions,TransTypeDefault);
      //ADDTEXTFIELD(pOptions,TradeAmtTypeDefault);
      //ADDTEXTFIELD(pOptions,TradePayTypeDefault);
      //ADDTEXTFIELD(pOptions,TradeClearMethodDefault);
      //ADDTEXTFIELD(pOptions,TradeFileProcessorDefault);
      //ADDTEXTFIELD(pOptions,TrxSettCurrRefresh);
      //ADDTEXTFIELD(pOptions,CanSuppressConfirm);
      //ADDTEXTFIELD(pOptions,ROATransType);
      //ADDTEXTFIELD(pOptions,DefaultExchRate);
      //ADDTEXTFIELD(pOptions,MCHSRActive);
      //ADDTEXTFIELD(pOptions,MCHNewTrade);
      //ADDTEXTFIELD(pOptions,MCHRbkTrade);
      //ADDTEXTFIELD(pOptions,MCHIndCancel);
      //ADDTEXTFIELD(pOptions,MCHBulkCancel);
      //ADDTEXTFIELD(pOptions,MCHBulkRbk);
      //ADDTEXTFIELD(pOptions,SRNewTrade);
      //ADDTEXTFIELD(pOptions,SRRbkTrade);
      //ADDTEXTFIELD(pOptions,SRIndCancel);
      //ADDTEXTFIELD(pOptions,SRBulkCancel);
      //ADDTEXTFIELD(pOptions,SRBulkRbk);
      //ADDTEXTFIELD(pOptions,SWPSettleESGElig);
      //ADDTEXTFIELD(pOptions,CashIDSettleESGElig);
      //ADDTEXTFIELD(pOptions,SDRTReportFlag);
      //ADDTEXTFIELD(pOptions,AWDFieldFlag);
      //ADDTEXTFIELD(pOptions,PSDAdvice);
      //ADDTEXTFIELD(pOptions,PymtRoutingMthd);
      //ADDTEXTFIELD(pOptions,TradelevelOveride);
      //ADDTEXTFIELD(pOptions,DefPymtRoutingMthd);
      //ADDTEXTFIELD(pOptions,UCITFlag);

      AddTextFields(ifds::DSTC0344_VW,pOptions);
   }

   return( TRUE );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
// $Log:   Y:/VCS/BF iFAST/ifsupp/AboutPropMgmtOptionsPage.cpp-arc  $
// 
//    Rev 1.17   Aug 02 2012 09:09:08   dchatcha
// P0198518-RDR FUNCTIONALITY
// 
//    Rev 1.16   Jul 24 2012 17:40:46   dchatcha
// P0198518-RDR FUNCTIONALITY
// 
//    Rev 1.15   Jul 12 2012 12:21:30   dchatcha
// P0179630 FN01 FATCA Project - Entity level.
// 
//    Rev 1.14   May 18 2012 18:44:46   wp040132
// Removed KIID Function from View 149
// 
//    Rev 1.13   May 11 2012 19:26:44   dchatcha
// P0186479 FN10 - Gap 14G - Block Service Unit Transfers.
// 
//    Rev 1.12   May 11 2012 18:48:06   dchatcha
// P0186486_FN15_The Source of Funds
// 
//    Rev 1.11   May 11 2012 18:37:36   dchatcha
// P0195754_FN01_ KIID_UCITs - KIID Validation
// 
//    Rev 1.10   May 04 2012 16:20:28   dchatcha
// P0187485 FN01 : CPF enhancements
// 
//    Rev 1.9   May 04 2012 16:13:20   dchatcha
// P0187485 FN01 : CPF enhancements
//
//    Rev 1.8   May 04 2012 16:08:38   dchatcha
// P0186486_FN15_The Source of Funds
// 
//    Rev 1.7   Apr 12 2012 15:24:10   dchatcha
// P0186486 FN10 -Gap 14G - Block Service Unit Transfers, removed 'transferoption' from 149 response.
// 
//    Rev 1.6   Apr 10 2012 18:32:56   dchatcha
// P0186486 FN10 -Gap 14G - Block Service Unit Transfers
// 
//    Rev 1.5   Mar 05 2012 12:36:14   dchatcha
// P0186484 FN05 - SEG Trade Processing.
// 
//    Rev 1.4   Jan 20 2012 17:54:12   dchatcha
// P0188394 Performance Fees
// 
//    Rev 1.3   Jan 20 2012 17:48:42   dchatcha
// P0186484 Contract Maturity Instructions 
// 
//    Rev 1.2   Dec 13 2011 12:44:06   dchatcha
// P0186477 FN03 - GIA Purchase, also include sync recently changes
// 
//    Rev 1.1   Dec 05 2011 09:20:06   purdyech
// Forgot a merge from ifastgui
//
//    Rev 1.0   Dec 05 2011 09:03:46   purdyech
// Initial revision.
//
//    Rev 1.9   Aug 24 2011 12:08:26   dchatcha
// IN#2579232 - EZN bulking Repayment.
//
//    Rev 1.8   Aug 04 2011 17:56:02   dchatcha
// P0186774 - Mutual Fund Order Processing
//
//    Rev 1.7   Dec 28 2010 05:38:14   dchatcha
// IN# 2370625 - Can not add Account Category 'EAP App' to TFSA and RRSP account.
//
//    Rev 1.6   Dec 02 2010 23:57:30   dchatcha
// P0175716 FN02 - Client Name Redemption - EPA Auto Settlement.
//
//    Rev 1.5   Sep 29 2010 05:18:24   dchatcha
// P0168727 FN22 - Trailer Fee Setup.
//
//    Rev 1.4   Sep 29 2010 05:08:32   dchatcha
// PET0173756 Don't Bust the Rules.
//
//    Rev 1.3   Apr 21 2010 10:27:46   dchatcha
// PET165541_FN01_QESI - RESP Gap_Dsk_Trading
//
//    Rev 1.2   Mar 23 2010 13:30:06   dchatcha
// PET165541_FN01_QESI - RESP Gap_Dsk_NASU
//
//    Rev 1.1   Jan 08 2010 05:59:12   dchatcha
// P0166095 FN01 - iFAST Validation on Redemptions - Update field report due to layout change on view#149 resp.
//

