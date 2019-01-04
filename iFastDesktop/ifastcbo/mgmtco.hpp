#pragma once
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
//    Copyright 2005 by International Financial Data Services
//
//
//******************************************************************************
// ^FILE   : MgmtCo.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : MgmtCo
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
#include <bfutil\bfcritsec.hpp>

class FundMasterList;
class TranslationList;
class FundDetailList;
class MgmtCoOptions;
class MgmtCoOptions2;
class GroupList;
class CurrencyList;
class GroupFundList;
class TaxTypeRuleList;
class FundToList;
class MasterContractList;
class IntermediaryList;
class ErrMsgRulesList;
class FundSponsorsList;
class RecipientTypeList;
class SavingPlanMasterList;
class CommitmentProductList;
class DynamicSubListHolder;
class DocumentTypeList;
class TranslationTable;
class FundCommGroupList;
class FundGroupTypeList;
class FeeParamConfigList;
class DocumentTypeOverrideList;
class FeeParamSysList;
class SupportedProductsList;
class LSIFCodesList;
class LSIFRolloverRulesList;
class FundGroupSubList;
class FeeSetupTradeRulesList;
class FeeModelSetupList;
//class ExtTransferTypeList;
class ProvinceList;
class DefaultMailOptionList;
class FrequencyList;
class SystemVerificationDetailsList;
class NEQDetailsList;
class DefaultSysConfigList;
class DefaultSysConfigDetailList;
class NetworkConfigDetailList; 
class FinInstRegDetlList;
class TradeTransTypeSetFromMiscInfoList;
class MiscInfoExternalInstitutionList;
class FundRuleList;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif


class IFASTCBO_LINKAGE MgmtCo : public MFCanBFCbo, private boost::noncopyable
{
public:   
   static void buildKey (const DString &strMgmtCo, DString &strKey);
public:
   MgmtCo (BFAbstractCBO &parent);
   virtual ~MgmtCo();
   SEVERITY init (const DString &companyId);

//methods that use the template private getter   
   SEVERITY getFundMasterList (FundMasterList *&pFundMasterList);
   SEVERITY getFundDetailList (FundDetailList *&pFundDetailList);
   SEVERITY getMgmtCoOptions (MgmtCoOptions *&pMgmtCoOptions);
   SEVERITY getMgmtCoOptions2 (MgmtCoOptions2 *&pMgmtCoOptions2);
   SEVERITY getTranslationList (TranslationList *&pTranslationList);
   SEVERITY getSupportedProductsList (SupportedProductsList *&pFundDetailList);
   SEVERITY getLSIFCodesList (LSIFCodesList *&pLSIFCodesList);
   SEVERITY getTaxTypeRuleList (TaxTypeRuleList *&pTaxTypeRuleList); // Celia
   SEVERITY getGroupList (GroupList *&pGroupList);    // Celia
   SEVERITY getGroupFundList (GroupFundList *&pGroupFundList);
   SEVERITY getFeeSetupTradeRulesList (FeeSetupTradeRulesList *&pGroupFundList);
   SEVERITY getCurrencyList (CurrencyList *&pCurrencyList);
   SEVERITY getFeeModelSetupList(FeeModelSetupList *&pFeeModelSetupList);
   SEVERITY getErrMsgRulesList (ErrMsgRulesList *&pErrMsgRulesList); // Celia
   SEVERITY getFundSponsorsList (FundSponsorsList *&pFundSponsorsList);
   SEVERITY getIntermediaryList (IntermediaryList *&pIntermediaryList); // Winnie
   SEVERITY getMasterContractList (MasterContractList *&pMasterContractList); // Celia
   SEVERITY getSavingPlanMasterList( SavingPlanMasterList *&pSavingPlanMasterList );
   SEVERITY getCommitmentProductList( CommitmentProductList *&pCommitmentProductList );
   SEVERITY getRecipientTypeList (RecipientTypeList *&pRecipientTypeList); // Celia
   SEVERITY getDocumentTypeList (DocumentTypeList *&pDocumentTypeList);
   SEVERITY getFeeParamConfigList (FeeParamConfigList *&pFeeParamConfigList);
//others
   SEVERITY getLSIFRolloverRulesList ( const DString &fromFund, 
                                       const DString &fromClass, 
                                       LSIFRolloverRulesList *&pLSIFRolloverRulesList
                                     );

   DynamicSubListHolder* getDynamicSubListHolder();
   SEVERITY getFundCommGroupList ( const DString& dstrFundGroupType, 
                                   FundCommGroupList *&pFundCommGroupList
                                 );
   SEVERITY getFundGroupTypeList ( FundGroupTypeList *&pFundGroupTypeList, 
                                   const DString &fundGroupType
                                 );

   SEVERITY getDocumentTypeOverrideList( const DString& dstrGroupCode, 
                                         DocumentTypeOverrideList *&pDocumentTypeOverrideList 
                                       );
   SEVERITY getTranslationTable ( const DString& dstrGroupCode, 
                                  TranslationTable *&pTranslationTable
                                );
   SEVERITY getFundGroupSubList ( FundGroupSubList *&pFundGroupSubList, 
                                  const DString &dstrType
                                );
   SEVERITY getDefaultFeeParamSysList (FeeParamSysList *&pFeeParamSysList);
// SEVERITY getExtTransferTypeList( ExtTransferTypeList *&pExtTransferTypeList );

   SEVERITY getProvinceList( const DString& dstrCountryCode, 
                              ProvinceList *&pProvinceList );

   SEVERITY getFrequencyList( FrequencyList *&pProvinceList );

   SEVERITY getDefaultMailOptionList( DefaultMailOptionList *&pDefaultMailOptionList );
   SEVERITY getSystemVerificationDetailsList(SystemVerificationDetailsList *&pSystemVerificationDetailsList);
   SEVERITY getNEQDetailsList(NEQDetailsList *&pNEQDetailsList);
   SEVERITY getDefaultSysConfigList (DefaultSysConfigList *&pDefaultSysConfigList);
   SEVERITY getDefaultSysConfigDetailList (DefaultSysConfigDetailList *&pDefaultSysConfigDetailList);
   SEVERITY getNetworkConfigDetailList (NetworkConfigDetailList *&pNetworkConfigDetailList);
   SEVERITY getTradeTransTypeSetFromMiscInfoList (TradeTransTypeSetFromMiscInfoList *&pTradeTransTypeSetFromMiscInfoList);
   SEVERITY getFinInstRegDetlList(const DString &dstrComplyRule, FinInstRegDetlList *&pFinInstRegDetlList);
   SEVERITY getFundRuleList(const DString &dstrRuleType, FundRuleList *&pFundRuleList);

   SEVERITY getMiscInfoExternalInstitutionList(MiscInfoExternalInstitutionList *&pMiscInfoExternalInstitutionList);


private:
   template <class _X> 
   SEVERITY getObject_X ( const I_CHAR* i_methodName, 
                          _X *&pXMember, 
                          BFCritSec &bfCS,
                          _X *&pXOut);

   // Because MgmtCo is used as a global object in BPServer, the lazy
   //  initialization used in the above methods require synchronization so we
   //  don't run into any race conditions.
   // An alternative would be to force all to be initialized up front (on the
   //  server) so we wouldn't always pay the penalty for synchronization for the
   //  majority of times these methods are used.

//lists that use templates   

template <class _X>
   void delObject_X( _X*& pList, BFCritSec &bfCS );



   BFCritSec _csFundMasterList;
   FundMasterList* pFundMasterList_;

   BFCritSec _csFundDetailList;
   FundDetailList* pFundDetailList_;

   BFCritSec _csMgmtCoOptions;
   MgmtCoOptions* pMgmtCoOptions_;

   BFCritSec _csMgmtCoOptions2;
   MgmtCoOptions2* pMgmtCoOptions2_;

   BFCritSec _csTranslationList;
   TranslationList* pTranslationList_;

   BFCritSec _csSupportedProductsList;
   SupportedProductsList *pSupportedProductsList_;

   BFCritSec _csLSIFCodesList;
   LSIFCodesList *pLSIFCodesList_;

   BFCritSec _csTaxTypeRuleList;
   TaxTypeRuleList* pTaxTypeRuleList_;

   BFCritSec _csGroupList;
   GroupList* pGroupList_;

   BFCritSec _csGroupFundList;
   GroupFundList* pGroupFundList_;

   BFCritSec _csFeeSetupTradeRulesList;
   FeeSetupTradeRulesList* pFeeSetupTradeRulesList_;
     
   BFCritSec _csCurrencyList;
   CurrencyList*  pCurrencyList_;
   
   BFCritSec _csErrMsgRulesList;
   ErrMsgRulesList* pErrMsgRulesList_;

   BFCritSec _csFundSponsorsList;
   FundSponsorsList* pFundSponsorsList_;

   BFCritSec _csIntermediaryList;
   IntermediaryList* pIntermediaryList_;

   BFCritSec _csMasterContractList;
   MasterContractList* pMasterContractList_;

   BFCritSec _csSavingPlanMasterList;
   SavingPlanMasterList* pSavingPlanMasterList_;

   BFCritSec _csCommitmentProductList;
   CommitmentProductList* pCommitmentProductList_;

   BFCritSec _csRecipientTypeList;
   RecipientTypeList* pRecipientTypeList_;

   BFCritSec _csDocumentTypeList;
   DocumentTypeList* pDocumentTypeList_;

   BFCritSec _csFeeParamConfigList;
   FeeParamConfigList* pFeeParamConfigList_;
   
   BFCritSec _csDynamicSubListHolder;
   DynamicSubListHolder* pDynamicSubListHolder_;

   BFCritSec _csFundCommGroupList;
   BFCritSec _csFundGroupTypeList;

   BFCritSec _csFeeParamSysList;
   FeeParamSysList* pFeeParamSysList_;

   BFCritSec _csFeeModelSetupList;
   FeeModelSetupList* pFeeModelSetupList_;


   BFCritSec _csDocumentTypeOverrideList,
      _csTranslationTable, 
      _csFundGroupSubList,
      _csLSIFRolloverRulesList;

   BFCritSec _csProvinceList;

   BFCritSec _csFrequencyList;
   FrequencyList* pFrequencyList_; 

   BFCritSec _csDefaultMailOption;
   DefaultMailOptionList* pDefaultMailOptionList_;

   BFCritSec _csSystemVerificationDetailsList;
   SystemVerificationDetailsList* pSystemVerificationDetailsList_;

   BFCritSec _csNEQDetailsList;
   NEQDetailsList* pNEQDetailsList_;

   BFCritSec _csDefaultSysConfigList;
   DefaultSysConfigList* pDefaultSysConfigList_;

   BFCritSec _csDefaultSysConfigDetailList;
   DefaultSysConfigDetailList* pDefaultSysConfigDetailList_;
   
   BFCritSec _csNetworkConfigDetailList;
   NetworkConfigDetailList* pNetworkConfigDetailList_;

   BFCritSec _csTradeTransTypeSetFromMiscInfoList;
   TradeTransTypeSetFromMiscInfoList* pTradeTransTypeSetFromMiscInfoList_;

   BFCritSec _csMiscInfoExternalInstitutionList;
   MiscInfoExternalInstitutionList* pMiscInfoExternalInstitutionList_;

   BFCritSec _csFinInstRegDetlList;
   //FinInstRegDetlList *pFinInstRegDetlList_;

   int referenceCount;

   friend DSTCGlobalSession;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/mgmtco.hpp-arc  $
 * 
 *    Rev 1.58   Feb 24 2012 18:44:44   if991250
 * Account Commitment
 * 
 *    Rev 1.57   Apr 20 2010 16:14:16   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.56   Nov 18 2009 10:08:24   dchatcha
 * P0166583 - Static Data Change Phase 2 - FN02-03-04, fix compile issue caused by revision control entry.
 * 
 *    Rev 1.55   Nov 16 2009 06:38:36   dchatcha
 * P0166583 - Static Data Change Phase 2 - FN02-03-04
 */ 


