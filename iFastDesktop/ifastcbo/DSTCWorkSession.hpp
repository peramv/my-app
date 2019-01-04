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
//    Copyright 2000 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : DSTCWorkSession.hpp
// ^AUTHOR : Bunch of cool dudes
// ^DATE   : Jan, 2001
//
// ^CLASS    : DSTCWorkSession
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <bfcbo\BFWorkSession.hpp>
#include <boost\utility.hpp>

#include <map>
#include <set>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class DSTCUserSession;
class DSTCGlobalSession;
class HostSubstitutionValuesList;

class MFAccount;
class AccountEntityXref;
class Entity;
class Shareholder;
class WorksessionTradesList;
class WorkSessionEntityList;
class MgmtCo;
class MgmtCoOptions;
class MgmtCoOptions2;
class BrokerList;
class AdvisorList;
class Settlement;
class AMSMstrList;
class ifastCommonReportCriteria;
class FeeParamSysSearchCriteria;
class ProtectedFundList;
class FundDetail;
class ResetInstrList;
class MktIndexMasterList;
class MktIndexValuesList;
class TradeSearchCriteria;
class CancelInstrSearchCriteria;
class BrokerAMSsearch;
class ManualDividendList;
class ClientBankInstructionsList;
class DistributorRepository;
class FundBankInstructionsListRepository;
class AgentBankInstructionsListRepository;
class FinancialInstitutionListRepository;
class SysLvlSettlementInstrList;
class DailyTransactionsFeesRepository;
class HoldingCompList;

class FeeModelList;
class FundSponsorFeeModelList;
class RemarkContainer;
class FundBrokerList;
class AggregatedOrderList;
class WhereUsedList;
class MsgProcessCBOList;
class MsgDetailList;
class MessageEnvelopeList;
class FileSearchCriteria;
class TransCancellist;
class OPCConfirmReprint;
class BulkCancellist;
class SavingsDirective;
class DilutionAllocList;
class CloneAccount;
class Confirmation;
class ChequeList;
class Residency;
class BatchInfoList;
class AcctGuaranteeGuardOptList;
class FamilyCodeList;
class InvestmentHistoryList;
class ProgressiveIntRateList;
class InterestSegmentList;
class FinInstRegDetlList;
class AcctRegDetailsList;
class EntityRegDetailsList;
class FATCAMasterList;
class TransactionList;
class TradeVerificationSearch;
class TradeVerificationList;
class TradeOverideRuleWarningsList;
class AcctGrpConfigList;
class RESPRegMstrList;
class ExternalInstitutionList;
class AcctCutOffTimesList;
class RESPRegRuleList;

namespace TRXNTAG
{
    extern IFASTCBO_LINKAGE const I_CHAR* ACCTTAG;
    extern IFASTCBO_LINKAGE const I_CHAR* SHRTAG;
    extern IFASTCBO_LINKAGE const I_CHAR* ADDRESSTAG;
    extern IFASTCBO_LINKAGE const I_CHAR* ENTITYIDTAG;
    extern IFASTCBO_LINKAGE const I_CHAR* ENTITYIDSTAG;
    extern IFASTCBO_LINKAGE const I_CHAR* ACCTENTITYTAG;
    extern IFASTCBO_LINKAGE const I_CHAR* DEMOGRAPHICSTAG;
    extern IFASTCBO_LINKAGE const I_CHAR* DISTRIBUTIONTAG;
    extern IFASTCBO_LINKAGE const I_CHAR* SHRBANKTAG;
    extern IFASTCBO_LINKAGE const I_CHAR* SYSACCTNUMTAG;
    extern IFASTCBO_LINKAGE const I_CHAR* TRADEACCTNUMTAG;
    extern IFASTCBO_LINKAGE const I_CHAR* TRANSTYPETAG;
    extern IFASTCBO_LINKAGE const I_CHAR* FUNDTAG;
    extern IFASTCBO_LINKAGE const I_CHAR* CLASSTAG;
    extern IFASTCBO_LINKAGE const I_CHAR* EFFDATETAG;
    extern IFASTCBO_LINKAGE const I_CHAR* STATUSTAG;
    extern IFASTCBO_LINKAGE const I_CHAR* ACCTMAILINGTAG;
    extern IFASTCBO_LINKAGE const I_CHAR* REMARKSTAG;
    extern IFASTCBO_LINKAGE const I_CHAR* ENTADDRTAG;
    extern IFASTCBO_LINKAGE const I_CHAR* ALLOCTAG;
    extern IFASTCBO_LINKAGE const I_CHAR* TRANSNUMTAG;
    extern IFASTCBO_LINKAGE const I_CHAR* RRIFINFOTAG;
    extern IFASTCBO_LINKAGE const I_CHAR* RIFIDTAG;
    extern IFASTCBO_LINKAGE const I_CHAR* CONTRACTTAG;
    extern IFASTCBO_LINKAGE const I_CHAR* CONTRACTTYPETAG;
    extern IFASTCBO_LINKAGE const I_CHAR* ISSUEDATETAG;
    extern IFASTCBO_LINKAGE const I_CHAR* ASPENSIONTAG;
    extern IFASTCBO_LINKAGE const I_CHAR* ACCTSPLITCOMMTAG; 
    extern IFASTCBO_LINKAGE const I_CHAR* ESOPTAG;
    extern IFASTCBO_LINKAGE const I_CHAR* FEEPARAMTAG;
    extern IFASTCBO_LINKAGE const I_CHAR* FEEPARAMSYSTAG;
    extern IFASTCBO_LINKAGE const I_CHAR* FEETAG;
    extern IFASTCBO_LINKAGE const I_CHAR* FEEMODELTAG;
    extern IFASTCBO_LINKAGE const I_CHAR* FUNDSPONSORTAG;
    extern IFASTCBO_LINKAGE const I_CHAR* COMMGROUPTAG;
    extern IFASTCBO_LINKAGE const I_CHAR* PENSIONINFOPARAMTAG;
    extern IFASTCBO_LINKAGE const I_CHAR* SETTLEMENTTAG;
    extern IFASTCBO_LINKAGE const I_CHAR* ACCTENTITYADDRMAILTAG;
    extern IFASTCBO_LINKAGE const I_CHAR* AMSMSTRINFOTAG;
    extern IFASTCBO_LINKAGE const I_CHAR* AMSCODETAG;
    extern IFASTCBO_LINKAGE const I_CHAR* REPORTIDTAG;
    extern IFASTCBO_LINKAGE const I_CHAR* SHRFAMILYTAG;
    extern IFASTCBO_LINKAGE const I_CHAR* ACCTCATEGORYTAG;
    extern IFASTCBO_LINKAGE const I_CHAR* RESETINSTRTAG;
    extern IFASTCBO_LINKAGE const I_CHAR* AMSBROKERTAG;
    extern IFASTCBO_LINKAGE const I_CHAR* ACCTMAILINGOVERRIDETAG;
    extern IFASTCBO_LINKAGE const I_CHAR* CLIENTBANK;
    extern IFASTCBO_LINKAGE const I_CHAR* FUNDBANK;
    extern IFASTCBO_LINKAGE const I_CHAR* RULETYPETAG;
    extern IFASTCBO_LINKAGE const I_CHAR* AMSLMTTAG;
    extern IFASTCBO_LINKAGE const I_CHAR* DIRECTTRADINGTAG;
    extern IFASTCBO_LINKAGE const I_CHAR* FUNDBROKERTAG;
    extern IFASTCBO_LINKAGE const I_CHAR* FUNDBROKERCODETAG;
    extern IFASTCBO_LINKAGE const I_CHAR* WHEREUSEDTAG;
    extern IFASTCBO_LINKAGE const I_CHAR* EXEMPTTAG;
    extern IFASTCBO_LINKAGE const I_CHAR* BULKCANCELTAG;
    extern IFASTCBO_LINKAGE const I_CHAR* SAVDIRECTIVETAG;
    extern IFASTCBO_LINKAGE const I_CHAR* AMSACCTLVLTAG;
    extern IFASTCBO_LINKAGE const I_CHAR* ACCTSETTLEMENTRULETAG;
    extern IFASTCBO_LINKAGE const I_CHAR* TRADEAUTHORIZATIONTAG;
    extern IFASTCBO_LINKAGE const I_CHAR* ACCTGUARNTGUARDOPTNTAG;
    extern IFASTCBO_LINKAGE const I_CHAR* ACCTCOMMTAG;
    extern IFASTCBO_LINKAGE const I_CHAR* ACCTREGDETAILS;
    extern IFASTCBO_LINKAGE const I_CHAR* ENTITYREGDETAILS;
    extern IFASTCBO_LINKAGE const I_CHAR* ENTITYREGJURISDETAILS;
    extern IFASTCBO_LINKAGE const I_CHAR* TRADEVERIFICATION;
    extern IFASTCBO_LINKAGE const I_CHAR* DEMOGRAPHICS_CHILD_TAG;
	extern IFASTCBO_LINKAGE const I_CHAR* PENDINGTRADEERRORTAG;
    extern IFASTCBO_LINKAGE const I_CHAR* ENTITYRISKTAG;
	extern IFASTCBO_LINKAGE const I_CHAR* ACCTROUNDINGRULETAG;
}

//specifies the grouping of a shareholder/account trxn
//values for the trxn sub type
namespace SHRACCGROUPING
{
   extern const long SHR;
   extern const long ACCT;
   extern const long ADDRESS;
   extern const long MAILING;
   extern const long ENTITY;
   extern const long ACCTENTITY;
   extern const long ENTITYIDS;
   extern const long OTHER;
}

namespace FEEMODELGROUPING
{
   extern const long FUND_SPONDSOR_FEE_MODEL ;
   extern const long FUND_SPONDSOR_FEE ;
}

namespace RUNMODE 
{
   extern IFASTCBO_LINKAGE const I_CHAR* ADDED;
   extern IFASTCBO_LINKAGE const I_CHAR* MODIFIED;
   extern IFASTCBO_LINKAGE const I_CHAR* DELETED;
   extern IFASTCBO_LINKAGE const I_CHAR* UNCHANGED;
}

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE DSTCWorkSession : public BFWorkSession, private boost::noncopyable
{
public:
   ~DSTCWorkSession ();

   enum DATE_TYPE
   {
      CURRENT_BUSINESS_DAY, CURRENT_SYSTEM_DAY, DAY12319999
   };

   // convenience methods  (taken from DSTCommonFunctions)
   const MgmtCo &getMgmtCo () const;
   MgmtCo &getMgmtCo ();
   void setMgmtCo (const DString &mgmtCoId);
   MgmtCoOptions *getMgmtCoOptions () const;
   MgmtCoOptions2 *getMgmtCoOptions2 () const;

   SEVERITY getOption (const BFFieldId &idField, 
                       DString &strValueOut, 
                       const BFDataGroupId &idDataGroup, 
                       bool formatted= true) const;
   SEVERITY getOption2 (const BFFieldId &idField, 
                        DString &strValueOut, 
                        const BFDataGroupId &idDataGroup, 
                        bool formatted= true) const;
   void getDateInHostFormat (DString &Date, 
                             int DateRequired = DAY12319999, 
                             const BFDataGroupId &idDataGroup = BF::NullDataGroupId) const;
   double getExchRate ( const DString &dstrToCurrency, 
                        DString &AsofDate, 
                        const BFDataGroupId &idDataGroup);

   //fund related methods
   bool getFundDetail ( const DString &fundCode, 
                        const DString &classCode, 
                        const BFDataGroupId &idDataGroup, 
                        FundDetail *&pFundDetail);
   void GetFundNumber ( const DString &fundCode, 
                        const DString &classCode, 
                        DString &fundNumber);
   void GetISINNumber ( const DString &fundCode, 
                        const DString &classCode, 
                        DString &isin);
   void GetWKNNumber ( const DString &fundCode, 
                       const DString &classCode, 
                       DString &wkn);
   void GetLFCNumber ( const DString &fundCode, 
                       const DString &classCode, 
                       DString &lfc);
   void GetCUSIPNumber ( const DString &fundCode, 
                         const DString &classCode, 
                         DString &cusip);
   bool GetFundClassCode ( const DString &fundNumber, 
                           DString &fundCode, 
                           DString &classCode);
   bool GetFundClassCodeByISIN ( const DString &isinNumber, 
                                 DString &fundCode, 
                                 DString &classCode);
   bool GetFundClassCodeByWKN ( const DString &wknNumber, 
                                DString &fundCode, 
                                DString &classCode);
   bool GetFundClassCodeByLFC ( const DString &lfcCode, 
                                DString &fundCode, 
                                DString &classCode);
   bool GetFundClassCodeByCUSIP ( const DString &cusipCode, 
                                DString &fundCode, 
                                DString &classCode);
   void getFundName ( const DString &fundCode, 
                      DString &fundName);

   // MFAccount maints
   SEVERITY getNewMFAccount ( const BFDataGroupId &idDataGroup, 
                              const DString &shrNum, 
                              MFAccount *&pAcctOut, 
                              const DString &strAccNum = NULL_STRING);
   SEVERITY getMFAccount ( const BFDataGroupId &idDataGroup, 
                           const DString &strAcctNum, 
                           MFAccount *&pAcctOut, 
                           const DString &dstrTrack = I_ ("N"), 
                           const DString &dstrPageName = NULL_STRING, 
                           bool bCreate = true, 
                           bool bValidateAccNum = false);
   SEVERITY PopulateMFAccount (const BFDataGroupId &idDataGroup, 
                               const BFData &accountData, 
                               MFAccount *&pAcctOut);

   // AccountEntityXref maints
   SEVERITY getAccountEntityXref ( const BFDataGroupId &idDataGroup, 
                                   AccountEntityXref *&pAccountEntityXrefOut);

   // Entity maints
   SEVERITY getNewEntity ( const BFDataGroupId &idDataGroup, 
                           Entity *&pEntityOut);
   SEVERITY getEntity ( const BFDataGroupId &idDataGroup, 
                        const DString &strEntityNum, 
                        Entity *&pEntityOut);
   SEVERITY PopulateEntity ( const BFDataGroupId &idDataGroup, 
                             const BFData &entityData, 
                             Entity *&pEntityOut);
   void getFirstSequenced01AccountholderEntityName ( const BFDataGroupId &idDataGroup, 
                                                     DString &AcctNum, 
                                                     DString &EntityName, 
                                                     bool kanji = true);
   //This function only need to get the name of the first entity of the account
   //should not add anything to the acct and entity map of the existing account detail screen.
   void getAccountholder01EntityName ( const BFDataGroupId &idDataGroup, 
                                       DString &AcctNum, 
                                       DString &EntityName, 
                                       bool kanji = true);

   // Shareholder maints
   SEVERITY getNewShareholder ( const BFDataGroupId &idDataGroup, 
                                Shareholder *&pShrhldrOut, 
                                DString  &dstrNewShrNum = DString (NULL_STRING));
   SEVERITY getShareholder ( const BFDataGroupId &idDataGroup, 
                             const DString &shrNum, 
                             Shareholder *&pShrhldrOut, 
                             bool bValidateShrNum = false);

   SEVERITY getBatchList (BatchInfoList* &pBatchInfoList, const BFDataGroupId &idDataGroup);

   SEVERITY getHoldingCompList(HoldingCompList* &pHoldingCompList, const BFDataGroupId &idDataGroup, 
                               const DString& dstrHoldingCompCode, const DString& dstrHoldingCompName, 
                               const DString& dstrAll, const DString& dstrEffDate, bool doViewCall, bool isProcSupport = false);

   SEVERITY getNEQList (DString &dstrNEQList,  const DString dstrWhereUse,  const BFDataGroupId &idDataGroup);
   SEVERITY getNEQId (DString &dstrNEQId,  const DString dstrWhereUse,  const BFDataGroupId &idDataGroup);

   //START: <Methods that use the template function getObject_X>
   SEVERITY getBrokerCutOff(const DString& dstrBrokerCode, AcctCutOffTimesList*& pBrokerCutOff, const BFDataGroupId& idDataGroup );
   //BrokerList: starts empty and grows with each getBroker () call on it
   SEVERITY getWorkSessionEntityList ( WorkSessionEntityList *&pWorkSessionEntityList,
                                       const BFDataGroupId &idDataGroup = BF::HOST, 
                                       bool bCreate = true);
   SEVERITY getBrokerList ( BrokerList* &pBrokerList, 
                            const BFDataGroupId &idDataGroup = BF::HOST, 
                            bool bCreate = true);
   // Trade maints
   SEVERITY getTradesList ( WorksessionTradesList *&pTradesListOut, 
                            const BFDataGroupId &idDataGroup = BF::HOST, 
                            bool bCreate = true, 
                            const DString &dstrTrack = I_ ("N"),
                            const DString &dstrPageName = NULL_STRING);
   //the protected fund list
   SEVERITY getProtectedFundList ( ProtectedFundList *&pListOut, 
                                   const BFDataGroupId &idDataGroup = BF::HOST, 
                                   bool bCreate = true);
   //Mkt index list
   SEVERITY getMktIndexMasterList ( MktIndexMasterList *&pMktIndexMasterList, 
                                    const BFDataGroupId &idDataGroup = BF::HOST, 
                                    bool bCreate = true);
   SEVERITY getMktIndexValuesList ( MktIndexValuesList *&pMktIndexValuesList, 
                                    const BFDataGroupId &idDataGroup = BF::HOST, 
                                    bool bCreate = true);
   SEVERITY setMktIndexValuesList ( MktIndexValuesList *&pMktIndexValuesList);

   SEVERITY getMktIndexValuesList(MktIndexValuesList *&pMktIndexValuesList,
                                  const BFDataGroupId& idDataGroup,
                                  const DString& dstrIndexCode,
                                  const DString& dstrFromDate,
                                  const DString& dstrSearchType,
                                  const DString& dstrToDate);
   SEVERITY getSettlementLocationSysLvlList ( SysLvlSettlementInstrList *&pSysLvlSettlementInstrList, 
                                              const BFDataGroupId &idDataGroup = BF::HOST, 
                                              bool bCreate = true);

   SEVERITY canVerify (const BFDataGroupId& idDataGroup,
                       const DString& functionCode,
                       const DString &dstrVerifyCategory, 
                       const DString &dstrVerifyLevel,
                       const DString &dstrLastUser,
                       bool &bCanVerify);

   //trade search criteria
   SEVERITY getTradeSearchCriteria ( TradeSearchCriteria *&pTradeSearchCriteria, 
                                     const BFDataGroupId &idDataGroup = BF::HOST, 
                                     bool bCreate = true);

   SEVERITY getTradeVerificationSearchCriteria( TradeVerificationSearch *&pTradeVerifcationSearchCriteria, 
                                                const BFDataGroupId &idDataGroup = BF::HOST, 
                                                bool bCreate = true); 
   SEVERITY getTradeOverideRuleWarningsList( TradeOverideRuleWarningsList *&pTradeOverideRuleWarningsList, 
                                             const BFDataGroupId& idDataGroup = BF::HOST, bool bCreate = true);
   // CancelInstr Search Criteria

   SEVERITY getCancelInstrSearchCriteria ( CancelInstrSearchCriteria *&pCancelInstrSearchCriteria, 
                                           const BFDataGroupId& idDataGroup = BF::HOST, 
                                           bool bCreate = true );
   //Settlement
   SEVERITY getSettlement ( Settlement *&pSettlement, 
                            const BFDataGroupId &idDataGroup = BF::HOST, 
                            bool bCreate = true);
   //Broker AMS Search
   SEVERITY getBrokerAMSsearch ( BrokerAMSsearch *&pBrokerAMSsearch, 
                                 const BFDataGroupId &idDataGroup = BF::HOST, 
                                 bool bCreate = true);
   //System Level Fee
   SEVERITY getFeeParamSysSearchCriteria ( FeeParamSysSearchCriteria *&pFeeParamSysSearchCriteria,
                                           const BFDataGroupId &idDataGroup = BF::HOST, 
                                           bool bCreate = true);
   //Manual dividend list
   SEVERITY getManualDividendList ( ManualDividendList *&pManualDividendList, 
                                    const BFDataGroupId &idDataGroup = BF::HOST, 
                                    bool bCreate = true);
   //the fund bank instructions repositroy
   SEVERITY getFundBankInstructionsListRepository ( FundBankInstructionsListRepository *&rpFundBankInstructionsListRepository, 
                                                    const BFDataGroupId &idDataGroup = BF::HOST, 
                                                    bool bCreate = true);

   SEVERITY getAgentBankInstructionsListRepository( AgentBankInstructionsListRepository *&pAgentBankInstructionsListRepository, 
                                                     const BFDataGroupId &idDataGroup = BF::HOST, 
                                                     bool bCreate = true);

   //the distributor bank instructions repository
   SEVERITY getDistributorRepository ( DistributorRepository *&pDistributorRepository,
                                       const BFDataGroupId &idDataGroup = BF::HOST, 
                                       bool bCreate = true);
   //the client bank instructions repository
   SEVERITY getClientBankInstructionsList ( ClientBankInstructionsList *&pClientBankInstructionsList, 
                                            const BFDataGroupId &idDataGroup = BF::HOST, 
                                            bool bCreate = true);
   SEVERITY getFinancialInstitutionListRepository (FinancialInstitutionListRepository *&pFinancialInstitutionListRepository,
                                                   const BFDataGroupId &idDataGroup = BF::HOST, 
                                                   bool bCreate = true);
   SEVERITY getDailyTransactionsFeesRepository (DailyTransactionsFeesRepository *&pDailyTransactionsFeesRepository,
                                                const BFDataGroupId &idDataGroup = BF::HOST, 
                                                bool bCreate = true);
   /*SEVERITY getReports  (ifastCommonReportCriteria* &pifastCommonReportCriteria, 
      const BFDataGroupId &idDataGroup = BF::HOST, bool bCreate = true);
   SEVERITY getResetInstrList (ResetInstrList* &pResetInstrList, 
      const BFDataGroupId &idDataGroup = BF::HOST, bool bCreate = true);*/

   //END: <Methods that use the template function getObject_X>

   SEVERITY getResetInstrList  ( ResetInstrList* &pResetInstrList, 
                                 const BFDataGroupId &idDataGroup, 
                                 bool bCreate = true);
   SEVERITY createResetInstrList  (ResetInstrList* &pResetInstrList, 
                                   const BFDataGroupId &idDataGroup);   
   SEVERITY getReports  ( ifastCommonReportCriteria* &pifastCommonReportCriteria, 
                          const BFDataGroupId &idDataGroup = BF::HOST, 
                          bool bCreate = true);
   SEVERITY createReports  ( ifastCommonReportCriteria* &pifastCommonReportCriteria, 
                             const BFDataGroupId &idDataGroup, 
                             bool bCreate = true);
   SEVERITY createReports  ( ifastCommonReportCriteria* &pifastCommonReportCriteria,
							 DString dstrRptName,
                             const BFDataGroupId &idDataGroup, 
                             bool bCreate = true);
   // SlsRep maints
   SEVERITY getAdvisorList ( const BFDataGroupId &idDataGroup, 
                             AdvisorList *&pAdvisorListOut, 
                             const DString &strBrokerCode,
                             const DString &strBranchCode, 
                             const DString &strSlsRep,
                             DString AllResult = I_ ("false"), 
                             const DString &dstrTrack = I_ ("N"),
                             const DString &dstrPageName = NULL_STRING, 
                             bool bCreate = true);
   SEVERITY getFeeModelList  ( FeeModelList* &pFeeModelList, 
                  const BFDataGroupId& idDataGroup , 
                  const DString& dstrHoldingCompCode = I_(""),
                  const DString& dstrHoldingCompName = I_(""),
                  const DString& dstrFeeModelCode = I_(""),
                  const DString& dstrFeeModelDesc = I_(""),
                  const DString& dstrSearchAll = I_("Y"),
                  const DString& dstrAsofDate = I_("12319999"),
                  bool bCreate = true,
                  bool bRetrieveAll = true);
   SEVERITY getFundSponsorFeeModelList ( FundSponsorFeeModelList *&pFundSponsorFeeModelList, 
                                         const BFDataGroupId &idDataGroup, 
                                         bool bCreate = true,
                                         const DString &feeModelCode = NULL_STRING,
                                         const DString &fundSponsorCode = NULL_STRING,
                                         bool allResults = false);
   SEVERITY getFundBrokerList ( FundBrokerList *&pFundBrokerList, 
                                const BFDataGroupId &idDataGroup, 
                                bool bCreate = true, 
                                const DString &dstrFBCode = NULL_STRING, 
                                const DString &dstrFBname = NULL_STRING,
								const bool noDataIsErrorCondition = false );
   SEVERITY getWhereUsedList( WhereUsedList *&pWhereUsedList, 
                              const BFDataGroupId& idDataGroup, 
                              bool bCreate, 
                              const DString& dstrEntityId );
   SEVERITY getTransCancellist( TransCancellist *&pTransCancellist,
                                const DString& _TransNum,
                                const DString& cashDivPaidAfer, 
                                const BFDataGroupId& idDataGroup,
                                const DString &dstrTradeDate = NULL_STRING,
                                const DString &dstrFundCode = NULL_STRING,
                                const DString &dstrClassCode = NULL_STRING,
                                const DString &dstrSearchType = NULL_STRING,
                                const DString &dstrTranStatus = NULL_STRING,
                                const DString &dstrAdjustType = NULL_STRING,
                                const DString &dstrTradeAdjustId = NULL_STRING,
                                const DString &dstrSettleDate = NULL_STRING,
                                const DString &dstrTransType = NULL_STRING);

      SEVERITY getBulkCancellist( BulkCancellist *&pBulkCancellist,
                                  const BFDataGroupId& idDataGroup, 
                                  const DString &dstrTradeDate,
                                  const DString &dstrFundCode,
                                  const DString &dstrClassCode,
                                  const DString &dstrTransNum = NULL_STRING,
                                  const DString &dstrTradeAdjustId = NULL_STRING );
   //AMS Global
   SEVERITY getAMSMstrList ( AMSMstrList *&pAmsMstrList , 
                             const DString &dstrAmsType, 
                             const DString &dstrAmsCode, 
                             const DString &dstrEffectiveDate, 
                             const BFDataGroupId &idDataGroup = BF::HOST, 
                             bool bCreate = true, 
                             bool bDel = false, 
                             bool ignoreDataNotFound = true, 
                             bool bDupCheck = false);
   SEVERITY getAggregatedOrderList( const DString& dstrFromDate,
                                    const DString& dstrToDate,
                                    const DString& dstrStatus,
                                    const DString& dstrBrokerCode,
                                    const DString& dstrFundCode,
                                    const DString& dstrAggrOrderNum,
                                    const DString& dstrRoutingRefNum,
                                    const DString& dstrSearchType,
                                    AggregatedOrderList *&pAggregatedOrderListOut,
                                    const BFDataGroupId& idDataGroup = BF::HOST,
                                    const DString& dstrTrack = I_("N"),
                                    const DString& dstrPageName = NULL_STRING,
                                    bool bCreate = true, 
                                    const DString& dstrFundKvBrkKvNum = NULL_STRING,
                                    const DString& dstrFundIDType = NULL_STRING,
                                    const DString& dstrFundIDValue = NULL_STRING,
                                    const DString& dstrAmountType = NULL_STRING,
                                    const DString& dstrAmount = NULL_STRING,
                                    const DString& dstrTransType  = NULL_STRING);
   SEVERITY getFileSearchCriteria( FileSearchCriteria *&pFileSearchCriteria, 
                                   const BFDataGroupId& idDataGroup,
                                   bool bCreate = true,
                                   const DString& dstrTrack = I_("N"),
                                   const DString& dstrPageName = NULL_STRING);
   SEVERITY getRemarkContainer ( RemarkContainer*&  pRemarkContainer,
                                 const DString& dstrBrokerCode, 
                                 const DString& dstrBranchCode,
                                 const DString& dstrAgentCode, 
                                 const DString& date,
                                 const BFDataGroupId& idDataGroup = BF::HOST, 
                                 bool bCreate =true,
                                 const DString& dstrTrack = I_("N"),
                                 const DString& dstrPageName  = NULL_STRING);

   SEVERITY getMsgProcessList( MsgProcessCBOList *&pMsgProcessList, 
                               const BFDataGroupId& idDataGroup, 
                               bool bCreate, 
                               const DString& EnvelopeID,
                               const DString& TransNum, 
                               const DString& AggrOrderNum, 
                               const DString& ActivityID,
                               const DString& SenderRefNum, 
                               const DString& NetworkID, 
                               const DString& StartDate,
                               const DString& EndDate, 
                               const DString ProcessType, 
                               const DString& ProcessCategory,
                               const DString& ProcessStatus, 
                               const DString& MsgSearchType);

   SEVERITY getChequeList(ChequeList *&pChequeList, 
                          const BFDataGroupId& idDataGroup, 
                          bool bCreate, 
                          DString& TransId, 
                          DString& AccountNum, 
                          DString& InCheqNum, 
                          DString& Broker, 
                          DString& Status, 
                          bool bIgnoreDataNotFound,
                          bool bIgnoreUnknAcct);

   SEVERITY getInvestmentHistoryList(	InvestmentHistoryList *&pInvestmentHistoryList,
										const DString& dstrAccountNum,
										const DString& dstrTranId,
										const DString& dstrFund,
										const DString& dstrClass,
										const DString& dstrInvestmentNo,
										const DString& dstrStatus,
										const DString& dstrSearchBy,
										const BFDataGroupId& idDataGroup);

   SEVERITY getProgressiveIntRateList(	ProgressiveIntRateList *&pProgressiveIntRateList,
										const DString& dstrAccountNum,
										const DString& dstrIntInvestID,
										const BFDataGroupId& idDataGroup);

   SEVERITY getInterestSegmentList(	InterestSegmentList *&pInterestSegmentList,
										const DString& dstrAccountNum,
										const DString& dstrIntInvestID,
										const BFDataGroupId& idDataGroup);

   SEVERITY getMsgDetailList( MsgDetailList *&pMsgDetailList, 
                              const BFDataGroupId& idDataGroup, 
                              bool bCreate, 
                              const DString& ActivityID);
   SEVERITY getMessageEnvelopeList( const DString& NetworkID,
                                    const DString& FileName,
                                    const DString& StartDate,
                                    const DString& EndDate,
                                    MessageEnvelopeList *&pMessageEnvelopeList, 
                                    const BFDataGroupId& idDataGroup, 
                                    bool bCreate = true,
                                    const DString& dstrTrack = I_("N"),
                                    const DString& dstrPageName  = NULL_STRING);

   SEVERITY getAcctGrpConfigList(AcctGrpConfigList *&pAcctGrpConfigList,
                                 const BFDataGroupId& idDataGroup);

   // general maints
   virtual SEVERITY buildTransactions ();
   virtual SEVERITY commit ();
   virtual SEVERITY refreshData ();
   void popCommitConditions (Frame* pFrame);
   void pushCommitConditions (Frame* pFrame);
   virtual bool hasCreatePermission (const DString &functionCode) const;
   virtual bool hasReadPermission (const DString &functionCode) const;
   virtual bool hasUpdatePermission (const DString &functionCode) const;
   virtual bool hasDeletePermission (const DString &functionCode) const;
   SEVERITY getHostAccountNum (const DString &tempAccountNum, 
                               DString &hostAccountNum);
   SEVERITY getHostShareholderNum (const DString &tempShrNum, 
                                   DString &hostShrNum);
   SEVERITY getHostEntityId (const DString &tempEntityId, 
                             DString &hostEntityId);
   void filterHostCondition(long condition);
   void clearHostConditionFilter();
   bool haveAccount(const DString &dstrAccountNumber);
   void setCommitParams (BFData &commitParams);

   //public static convenient methods
   static const DString getRunMode (BF_OBJ_ACTIVITY Activity, bool objUpdated);
   static void setRunMode (BFData* request, BF_OBJ_ACTIVITY objActivity);

   SEVERITY getOPCConfirmReprint( const DString &dstrTransId,
                                  const DString &dstrAccountNum,
                                  OPCConfirmReprint *&pOPCConfirmReprint, 
                                  const BFDataGroupId& idDataGroup,
                                  const DString& dstrTrack = I_("N"),
                                  const DString& dstrPageName = NULL_STRING );
   SEVERITY deleteOPCConfirmReprint();
   SEVERITY getTransHistDilutionAllocList ( const DString &dstrTransId,
                                            DilutionAllocList *&pDilutionAllocList, 
                                            const BFDataGroupId& idDataGroup,
                                            const DString &dstrTradeDate = NULL_STRING,
                                            const DString &dstrSettleDate = NULL_STRING,
                                            const DString &dstrTransNum = NULL_STRING,
                                            const DString &dstrTrack = I_("N"),
                                            const DString &dstrPageName = NULL_STRING);
   SEVERITY getSavingsDirective( const DString &dstrTransId,
                                 const DString &dstrAccountNum,
                                 const DString &dstrFund,
                                 const DString &dstrClass,
                                 const DString &dstrTradeDate,
                                 const DString &dstrTISType,
                                 const DString &dstrTIS,
                                 const DString &dstrCostType,
                                 const DString &dstrCost,
                                 const DString &dstrVersion,
                                 SavingsDirective *&pSavingsDirective,
                                 const BFDataGroupId& idDataGroup,
                                 const DString& dstrTrack ,
                                 const DString& dstrPageName );
   SEVERITY getCloneAccount ( const DString &accountNum,
                              CloneAccount *&pCloneAccount, 
                              const BFDataGroupId& idDataGroup,
                              bool bCreate = true);
   SEVERITY getResidency( Residency*& pResidency, const DString& dstrTaxType, 
                          const DString& dstrJurisd, const BFDataGroupId& idDataGroup );
   SEVERITY getResidency( Residency*& pResidency, const DString& dstrAccountNum, 
                          const DString& dstrAsOfDate, const DString& dstrDepositType, 
                          const BFDataGroupId& idDataGroup );
   SEVERITY getResidencyForShareholder( Residency*& pResidency, const DString& dstrShrNum, 
                                        const DString& dstrJurisd, const BFDataGroupId& idDataGroup );

   bool isNonRegLike( const DString& dstrTaxType );
   bool isLIFLike( const DString& dstrTaxType );
   bool isLIRALike( const DString& dstrTaxType );
   bool isIntRIFPlan( const DString& dstrTaxType );
   bool isPerfFeeFund(const DString &fundCode, const DString &classCode,const BFDataGroupId& idDataGroup);

   void getVerificationCategoryList(DString& dstrVerificationCategoryList);

   SEVERITY isVerificationEnabled (const BFDataGroupId& idDataGroup, 
                                   const DString &dstrVerifyCategory, 
                                   const DString &dstrVerifyLevel,
                                   bool &bEnabled,
								   DString &dstrVerifyFilter = (DString) NULL_STRING);

   bool isQESIClient( const BFDataGroupId& idDataGroup = BF::HOST );
   bool isRES2Client( const BFDataGroupId& idDataGroup = BF::HOST );

   bool isGuarGuardAllowed (const DString& dstrAccountNum,
                            const BFDataGroupId &idDataGroup);

   bool isHistTxfr( const BFDataGroupId& idDataGroup = BF::HOST  ); 
   bool isFunctionActivated( const DString& functionCode ) const;
   bool isIWTClient( const BFDataGroupId& idDataGroup );

   SEVERITY getFamilyCodeList( FamilyCodeList*& pFamilyCodeList,
                               const BFDataGroupId &idDataGroup );
   //P0186486_FN15_The Source of Funds                            
   bool isSrcOfFundRequired(const DString &srcOfFund,const BFDataGroupId& idDataGroup);
   bool isTaxAnniversaryClient( const BFDataGroupId& idDataGroup );
   SEVERITY getFATCAMasterList(FATCAMasterList *&pFATCAMasterList,   
							   const BFDataGroupId &idDataGroup = BF::HOST);
   bool isSAGESClient( const BFDataGroupId& idDataGroup = BF::HOST );

   SEVERITY getTransactionList(TransactionList *&pTransactionList,
						       const DString& transNum,
							   const BFDataGroupId &IdDataGroup = BF::HOST);

   bool isRESPTransformationClient( const BFDataGroupId& idDataGroup = BF::HOST );
   bool isBCTESGClient( const BFDataGroupId& idDataGroup = BF::HOST );
   bool isACESClient( const DString &dstrTradeDate, const BFDataGroupId& idDataGroup = BF::HOST );
   SEVERITY getRESPRegMstrList(RESPRegMstrList *&pRESPRegMstrList, const BFDataGroupId &idDataGroup);
   bool isMasterActWithOneChild(const BFDataGroupId& idDataGroup );
   bool isAMSFundClass(const DString& dstrFundCode, const DString& dstrClassCode, const BFDataGroupId& idDataGroup);
   SEVERITY fundClassSoftCappedCheck(const DString &dstrAccountNum, 
                                     const DString &dstrFundCode, 
                                     const DString &dstrClassCode, 
                                     const DString &dstrTransType,
                                     const DString &dstrEffectiveDate,
                                     const BFDataGroupId &idDataGroup);
   SEVERITY getExternalInstitutionList(ExternalInstitutionList*& pExternalInstitutionList, const BFDataGroupId& idDataGroup);
   bool multipleRiskEnv();
   SEVERITY getRESPRegRuleList(RESPRegRuleList *&pRESPRegRuleList, const BFDataGroupId &idDataGroup = BF::HOST);
   bool isNetBalTransfer( const DString& respNotlType, const BFDataGroupId& idDataGroup = BF::HOST );

private:

   // Construct only through DSTCUserSession::createWorkSession method  (friend)
   DSTCWorkSession ( const DString &mgmtCoId, 
                     DSTCUserSession &userSession);

   void getNewKey (DString &newKey);
   long _lKey;

   void orderTrxn ();
   void clearCommitConditions ();
   bool getValueForTag (DString &strBuffer, const I_CHAR* szTag, DString &strValue);
   bool addTag (DString &strBuffer, const I_CHAR* szTag, const I_CHAR* szValue);
   void checkSubstitutionsValues (const DString &keyType, const DString &tempValue, BFData &request);
   template <class _X> 
      SEVERITY getObject_X (const I_CHAR* i_charname, _X* &pListOut, 
         const BFDataGroupId &idDataGroup, BF_OBJ_TYPE bfObjType, bool bCreate,
         const DString &dstrTrack = I_ ("N"), const DString &dstrPageName = NULL_STRING);

   //for the current persistent trxn group we need 
   //to know if it has been filled; if yes what will be 
   //the next group to be used
   struct TrxnGroupInfo //used in orderTrxn method
   {
      //the next trxn grp id if this is filled
      long _nxtTrxnGrpId;
      //whether this grp id is filled 
      long _trxns;
      TrxnGroupInfo () : 
      _nxtTrxnGrpId (0), _trxns (0x0000)
      {
      };
   };

   //this is used to keep track of the persistence 
   //groups that failed
   //the structure is used inside the commit method,
   //in a map which keyed by the group id
   struct PersitentGroupCommitInfo
   {
      //the values of the new shareholder number,
      //new account number and new entity number
      DString _keyType;
      //whether it failed or not
      bool _failed;
      PersitentGroupCommitInfo () :
      _failed (false)
      {
      };
   };

   HostSubstitutionValuesList *_hostSubstitutionList;
   //keeps a vector of coditions resulted after building transaction and commiting them
   CONDITIONVECTOR* _commitConditions;
   MgmtCo *_currentMgmtCo;
   static long _maxTrxnGroup;
   static MutexSemaphore _trxnGroupSemaphore;   

   friend DSTCUserSession;


   // HostConditionFilter nested class contains DSTC conditions which will be filtered.
   class HostConditionFilter : public std::set< long, std::less<long> >
   {
      public:
         bool contains (long condition);
   } _hostConditionFilter;

   // HostConditionMap nested class maps all host error codes to DSTC conditions.
   class HostConditionMap : protected std::map< long, long, std::less<long> >
   {
   public:
      HostConditionMap(const long hostConditionArray[][2]);

      long getCondition(long hostErrorCode) const;
   private:
      HostConditionMap(); // not implemented
      void addCondition(long hostErrorCode, long condition);
   };

   static const HostConditionMap _hostConditions;

   SEVERITY addWarningForUpdateView (const DString &dstrWarnCode, const DString &dstrWarnParam);
   SEVERITY checkPersistentViewWarnings(BFData *persistStopResponse);
   SEVERITY saveCommitParams (BFData &request, const BFFieldId &idField);
   BFData *m_commitParams;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCWorkSession.hpp-arc  $
//
//   Rev 1.134   May 14 2012 10:14:04   kitticha
//P0186477 FN06 - T5 Processing.
//
//   Rev 1.133   Apr 20 2012 03:30:58   panatcha
//P0186486_FN15_The Source of Funds
//
//   Rev 1.132   Apr 03 2012 21:41:10   wp040039
//PETP0187485-Registartion Agent  Banking
//
//   Rev 1.131   Feb 22 2012 17:01:32   if991250
//Account Commitment
//
//   Rev 1.130   Jan 26 2012 10:54:28   wp040027
//P0188394_Performance Fees - Benchmark Upload (Modifying Search Functionality)
//
//   Rev 1.129   Jan 16 2012 13:55:28   wp040027
//P0188394_Performance Fees - Benchmark Upload
//
//   Rev 1.128   Dec 12 2011 11:58:02   wp040100
//P0186477/FN03 - GIA - Investment History Changes
//
//   Rev 1.127   Dec 01 2011 19:10:32   wp040100
//P0186477/FN03 - GIA - Investment History Changes
//
//   Rev 1.126   Nov 27 2011 21:35:14   wp040100
//P0186477/FN03 - GIA - Investment History Changes
//
//   Rev 1.125   Nov 25 2011 17:40:34   wp040100
//P0186477/FN03 - GIA - Investment History Changes
//
//   Rev 1.124   Nov 17 2011 15:51:26   wp040100
//P0186477/FN03 - GIA - Investment History Changes
//
//   Rev 1.123   Nov 11 2011 10:14:56   wp040100
//P0186477/FN03 - GIA - Added getInvestmentHistoryList method
//
//   Rev 1.122   Nov 08 2011 12:01:04   dchatcha
//P0188902 FN02 - DYN Household Project
//
//   Rev 1.121   Oct 21 2011 09:28:38   kitticha
//PETP0188150 FN01 - Irish Withholding Tax Functionality.
//
//   Rev 1.120   Oct 04 2011 18:16:22   dchatcha
//P0186477 FN01 - GIA Enhancements, display validate portfolio fields based on environment functionality(UAF).
//
//   Rev 1.119   Jun 28 2011 10:29:30   panatcha
//P0184541_FN01_InvescoQESItrans
//
//   Rev 1.118   Jan 20 2011 07:05:22   wichian
//IN#2319580 - Update according to code review 579300 w/o
//
//   Rev 1.116   Sep 17 2010 07:49:50   kitticha
//PETP0173756 FN02 Don't Bust the Rules.
//
//   Rev 1.115   Jul 05 2010 15:34:46   popescu
//Noticed that isQESI method is empty and redundant - took it out
//
//   Rev 1.114   Apr 27 2010 16:22:44   jankovii
//PET165541_FN01_QESI - RESP Gap_Dsk_Trading
//
//   Rev 1.113   Apr 20 2010 16:13:06   jankovii
//PET165541_FN01_QESI - RESP Gap_Dsk_Trading
//
//   Rev 1.112   Mar 12 2010 14:54:42   dchatcha
//PET165541_FN01_QESI - RESP Gap_Dsk_NASU
//
//   Rev 1.111   Jan 28 2010 17:04:36   jankovii
//PET165541 FN01 - QESI - RESP Gap.
//
//   Rev 1.110   Nov 17 2009 15:19:12   jankovii
//PET0166583 FN01 Static Data Changes Banking 
//
//   Rev 1.109   Nov 16 2009 06:42:42   dchatcha
//P0166583 - Static Data Change Phase 2 - FN02-03-04
//
//   Rev 1.108   May 12 2009 13:49:58   jankovii
//PET 159770 FN05 Auto Batching.
//
//   Rev 1.107   04 Mar 2009 15:53:40   kovacsro
//IN#1608629 - Aimprod RTS error 9
//
//   Rev 1.106   Mar 02 2009 09:58:54   jankovii
//PET0159508 FN03 ESG In Cash Transfer 
//
//   Rev 1.105   Nov 25 2008 11:17:20   jankovii
//PET 142196 FN01 Federal Restricted LIF and LIRA.
//
//   Rev 1.104   06 Oct 2008 13:16:52   kovacsro
//PET142007  FN01 TFSA
//
//   Rev 1.103   Sep 08 2008 16:10:06   jankovii
//PET 5517 FN71 - Stale Cheque.
//
//   Rev 1.102   Mar 11 2008 20:09:20   daechach
//PET2385FN02&07 - Account Level Settlement Periods and Currency Holiday - Check in for Build.
//
//   Rev 1.101   12 Nov 2007 23:44:16   popescu
//PET 5653/01 - Internal Audit project
//
//   Rev 1.100   17 Jul 2007 15:19:02   popescu
//GAP 6 CIF - AIM
//
//   Rev 1.99   Jul 11 2007 16:21:46   smithdav
//PET 2360 FN02 - AMS - Interim changes
//
//   Rev 1.98   Nov 14 2006 16:46:28   porteanm
//Incident 676881 - Pass TransType to 338 (TransCancel).
//
//   Rev 1.97   Nov 08 2006 17:29:08   popescu
//PET 2281/FN 01- copy account for TA 
//
//   Rev 1.96   Sep 11 2006 13:54:22   porteanm
//Incident 693185 - Warn support for view 161.
//
//   Rev 1.95   Mar 10 2006 13:55:08   porteanm
//Incident 563764 - TradeDate/SettleDate validation support for a cancelled transaction.
//
//   Rev 1.94   Dec 29 2005 13:09:00   porteanm
//Incident 501804 - Allow multiple Bulk Cancellation Instructions for the same Trade Date/Fund/Class.
//
//   Rev 1.93   Dec 16 2005 20:45:10   porteanm
//Incident 421704 - gap - TranshistDilutionAlloc update support.
//
//   Rev 1.92   Dec 13 2005 19:30:22   porteanm
//Incident 421704 - gap - TranshistDilutionAlloc update support.
//
//   Rev 1.91   Nov 29 2005 17:28:48   AGUILAAM
//PET1228_FN02_EUSD Phase 2
//
//   Rev 1.90   Nov 06 2005 15:06:28   porteanm
//PET 1286 FN01 - Bulk Cancellation.
//
//   Rev 1.89   Nov 04 2005 10:47:08   ZHANGCEL
//PET 1286  FN01 -- Add Cancellation Instruction related issue
//
//   Rev 1.88   Aug 09 2005 10:21:28   porteanm
//Incident 361254 - syncup from 1.85.2.1 - Added checkPersistentViewWarnings() and call each time when the persistant view is closed in commit().
//
//   Rev 1.87   Jul 13 2005 17:53:16   popescu
//Incident 352435 - improved performance on the fund sponsor fee model screen - synch-up from release 63.0.0
//
//   Rev 1.86   Jul 08 2005 09:30:56   Yingbaol
//PET1235,FN01:transaction cancellation rebook
//
//   Rev 1.85   Jun 16 2005 15:38:26   porteanm
//PET1024 FN40 - Guarantee Adjustments.
//
//   Rev 1.84   May 25 2005 15:03:14   porteanm
//PET OPC Confirm Reprint - Commit and Reset.
//
//   Rev 1.83   Apr 21 2005 10:24:32   ZHANGCEL
//Incident #292340 -- Added EXEMPTTAG in namespace TRXNTAG
//
//   Rev 1.82   Mar 16 2005 15:35:30   Fengyong
//PET1190 FN05 - change view 337 to repeatable
//
//   Rev 1.81   Mar 06 2005 15:40:50   yingbaol
//PET1171,FN01: EU Saving add where use transaction builder
//
//   Rev 1.80   Mar 03 2005 18:53:18   Fengyong
//PET1190 FN05 - Transaction cancellation and dilution
//
//   Rev 1.79   Feb 24 2005 17:28:20   ZHANGCEL
//PET1117- FN66-68 - Added getMsgEnvelopeList function
//
//   Rev 1.78   Feb 17 2005 16:00:12   hernando
//PET1117 FN66-68 - Added getMsgProcessList and getMsgDetailList.
//
//   Rev 1.77   Jan 26 2005 11:01:10   yingbaol
//PET1117 FN67 enhance Aggregate order for API
//
//   Rev 1.76   Dec 02 2004 15:06:08   Fengyong
//PET1117 FN54 - Fund Broker static
//
//   Rev 1.75   Nov 23 2004 17:24:42   Fengyong
//PET1117FN54 - adjustment after first day intergretion test
//
//   Rev 1.74   Nov 19 2004 10:08:38   zhangcel
//PET1117 FN8 -- Added getAggregatedOrderList function 
//
//   Rev 1.73   Nov 14 2004 14:36:22   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.72   Nov 07 2004 16:11:46   popescu
//PET 1117/56, getters for wkn/isin numbers fund/class by isin and wkn
//
//   Rev 1.71   Nov 04 2004 11:01:08   FENGYONG
//PET1117 FN54 - Fund broker static temp check in for 59 build
//
//   Rev 1.70   Oct 19 2004 14:54:38   FENGYONG
//PET1117 FN54 - Fund Broker Static
//
//   Rev 1.69   Oct 13 2004 13:50:32   VADEANUM
//PET 1117 FN21 - Replaced SysLvlSettleLoc with SettlementInstr...
//
//   Rev 1.68   Oct 07 2004 15:38:26   YINGBAOL
//PET1145 sync up version 1.
//
//   Rev 1.67   Sep 07 2004 14:11:04   YINGBAOL
//PET1117: add Fee model transaction builder 
//
//   Rev 1.66   Aug 10 2004 11:23:30   FENGYONG
//PET 1117 FN 5 - Client condition Fee
//
//   Rev 1.65   May 11 2004 14:27:44   FENGYONG
//PET1046 FN1 - transfer-switch -Rel57
//
//   Rev 1.64   Jan 28 2004 14:05:26   popescu
//PET 859, FN23, Added DailyTransactionsFees corresponding files and ids:
//DailyTransactionsFeeList.cpp +hpp
//DailyTransactionsFee.cpp +hpp
//DailyTransactionsFeesRepository.cpp +hpp
//DSTCDailyTransactionsFeesTrxnBuilder.cpp +hpp
//
//   Rev 1.63   Jan 02 2004 15:11:58   popescu
//PTS 10025696, NASU flow crash 
//
//   Rev 1.62   Nov 24 2003 18:10:32   HERNANDO
//PET859 FN1 - Added getSettlementLocationSysLvlList.
//
//   Rev 1.61   Oct 16 2003 12:20:10   FENGYONG
//PET809 FN08 Direct Trading enhancement
//
//   Rev 1.60   Oct 04 2003 17:17:12   popescu
//CIBC PET809, Fn13, added the financialinstitutionlistrepository getter
//
//   Rev 1.59   Jul 23 2003 11:04:18   linmay
//modified getamsmstrlist
//
//   Rev 1.58   Jul 18 2003 11:33:48   linmay
//modified for CIBC AMS
//
//   Rev 1.57   Jun 12 2003 16:48:28   YINGBAOL
//default to ingore data not found error message
//
//   Rev 1.56   May 31 2003 11:55:06   popescu
//RRIF bank work
//
//   Rev 1.55   May 28 2003 10:52:14   popescu
//Part of the cleaning of DSTCWorksession, not finalized yet, more to come....
//
//   Rev 1.54   May 27 2003 18:29:36   popescu
//due to several memory leaks found in some list getters at the DSTCWorkSession level caused by copy/paste, I've created a common template function to retrieve the dependent objects
//
//   Rev 1.53   May 27 2003 16:37:56   popescu
//NASU flow AMS :data not found issue fix and removed some memory leaks 
//
//   Rev 1.52   May 23 2003 14:44:08   HERNANDO
//Added getManualDividendList.
//
//   Rev 1.51   May 22 2003 14:12:34   popescu
//Replaced name 'BankInstr' with 'BankInstructions'; 
//simplified child lists getters for the Shareholder object
//
//   Rev 1.50   May 02 2003 14:43:58   linmay
//added FeeTag
//
//   Rev 1.49   Apr 29 2003 17:09:18   popescu
//added new convenience method getFundDetail (),
//
//   Rev 1.48   Apr 02 2003 11:32:42   FENGYONG
//Add keytag for mailing override
//
//   Rev 1.47   Mar 21 2003 18:07:36   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.46   Mar 03 2003 17:24:00   FENGYONG
//Add brokerlevel AMS
//
//   Rev 1.45   Mar 03 2003 09:42:36   KOVACSRO
//Added getTradeSearchCriteria.
//
//   Rev 1.44   Feb 11 2003 14:41:44   popescu
//changes related to the Historical information for Broker and Sales rep, as well as displaying the names for them in the Historical Info Search dialog
//
//   Rev 1.43   Jan 29 2003 12:16:12   HERNANDO
//Added getMktIndexValuesList.
//
//   Rev 1.42   Jan 27 2003 07:40:26   HSUCHIN
//removed resetinstrcriteria and added resetinstrlist
//
//   Rev 1.41   Jan 26 2003 15:53:38   HSUCHIN
//added reset instruction
//
//   Rev 1.40   Jan 25 2003 18:35:40   HERNANDO
//Added getMktIndexMasterList.
//
//   Rev 1.39   Jan 25 2003 16:31:56   HSUCHIN
//added methods get get reset instruction criteria
//
//   Rev 1.38   Jan 21 2003 12:52:38   KOVACSRO
//Added ACCTCATEGORYTAG
//
//   Rev 1.37   Jan 20 2003 14:51:24   YINGBAOL
//add CommGroup tag
//
//   Rev 1.36   Jan 18 2003 17:22:42   YINGBAOL
//add FeeParamSysTag
//
//   Rev 1.35   Jan 13 2003 18:00:54   sanchez
//Changes for Shareholer
//
//   Rev 1.34   Jan 10 2003 10:23:26   popescu
//No change.
//
//   Rev 1.33   Jan 09 2003 14:38:28   popescu
//Second revision, make things compilable
//
//   Rev 1.32   Jan 09 2003 10:09:52   YINGBAOL
//add GetFeeParamSystemSearchCriteria
//
//   Rev 1.31   Dec 27 2002 11:27:02   linmay
//modified getAMSMstrList signature, added AMSType as input parameter
//
//   Rev 1.30   Dec 08 2002 22:04:02   HSUCHIN
//removed reportstatuscriteria cbo
//
//   Rev 1.29   Nov 29 2002 13:13:58   HSUCHIN
//added report status 
//
//   Rev 1.28   Nov 27 2002 11:43:36   HSUCHIN
//added reports
//
//   Rev 1.27   Nov 20 2002 11:03:18   HSUCHIN
//added REPORTIDTAG again
//
//   Rev 1.26   Nov 19 2002 16:56:34   HSUCHIN
//sync up with 1.24.1.1
//
//   Rev 1.25   Nov 19 2002 16:19:36   YINGBAOL
//add getAMS....
//
//   Rev 1.24   Oct 09 2002 23:54:24   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.23   Sep 17 2002 10:09:10   HSUCHIN
//added account entity mailing tag
//
//   Rev 1.22   Aug 29 2002 12:52:14   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.21   Jun 13 2002 09:46:58   VASILEAD
//Added SETTLEMENTTAG
//
//   Rev 1.20   Jun 02 2002 17:51:54   HSUCHIN
//added pension info
//
//   Rev 1.19   May 30 2002 11:09:20   YINGBAOL
//add Settlement
//
//   Rev 1.18   24 May 2002 15:15:56   KOVACSRO
//Fund and Client bank.
//
//   Rev 1.17   22 May 2002 18:21:12   PURDYECH
//BFData Implementation
//
//   Rev 1.16   19 Mar 2002 13:16:52   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.15   08 Feb 2002 17:26:28   KOVACSRO
//Added a param. in getMFAccount and getShareholder
//
//   Rev 1.14   Jan 31 2002 14:49:24   YINGBAOL
//add FEEPARAMTAG
//
//   Rev 1.13   Jan 04 2002 12:15:08   FENGYONG
//Add getadvisorlist
//
//   Rev 1.12   25 Oct 2001 14:02:44   SMITHDAV
//hasPermission changes...
//
//   Rev 1.11   15 Oct 2001 12:05:20   KOVACSRO
//Added getBrokerList ()
//
//   Rev 1.10   Oct 03 2001 13:51:20   YINGBAOL
//add WorkSessionEntityList
//
//   Rev 1.9   19 Sep 2001 14:54:02   KOVACSRO
//Added ESOP.
//
//   Rev 1.8   30 Aug 2001 16:34:22   HSUCHIN
//added acct splitcomm flag
//
//   Rev 1.7   Aug 23 2001 12:23:36   JANKAREN
//Added ASPENSIONTAG
//
//   Rev 1.6   17 Jul 2001 15:13:08   HSUCHIN
//parameter bug fix for getTradeList
//
//   Rev 1.5   Jul 16 2001 18:59:42   OLTEANCR
//added CONTRACTTYPETAG,  ISSUEDATETAG;
//
//   Rev 1.4   09 Jul 2001 15:25:04   SMITHDAV
//Mgmt company refresh related changes.
//
//   Rev 1.3   14 Jun 2001 11:56:30   SMITHDAV
//Re-worked user access list and permission checking code.
//
//   Rev 1.2   Jun 12 2001 11:22:10   OLTEANCR
//sync up - getNewMfAccount (...)
//
//   Rev 1.1   Jun 11 2001 14:35:08   HERNANDO
//Added setMgmtCo (MgmtCo *).
//
//   Rev 1.0   03 May 2001 14:50:30   SMITHDAV
//Initial revision.
 *
 */
