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
//
// ^FILE   : MgmtCo.cpp
// ^AUTHOR : Mike Metzger
// ^DATE   : 3/28/99
//
//******************************************************************************

#include "stdafx.h"
#include "mgmtco.hpp"

#include <bfutil\bfguard.hpp>
#include "currencylist.hpp"
#include "documenttypelist.hpp"
#include "documenttypeoverridelist.hpp"
#include "dynamicsublistholder.hpp"
#include "errmsgruleslist.hpp"
#include "feeparamconfiglist.hpp"
#include "feeparamsyslist.hpp"
#include "feesetuptraderuleslist.hpp"
#include "fundcommgrouplist.hpp"
#include "funddetaillist.hpp"
#include "fundgrouptypelist.hpp"
#include "fundgroupsublist.hpp"
#include "fundmasterlist.hpp"
#include "fundsponsorslist.hpp"
#include "fundtolist.hpp"
#include "groupfundlist.hpp"
#include "grouplist.hpp"
#include "intermediarylist.hpp"
#include "lsifcodeslist.hpp"
#include "lsifrolloverruleslist.hpp"
#include "mastercontractlist.hpp"
#include "mgmtcooptions.hpp"
#include "mgmtcooptions2.hpp"
#include "recipienttypelist.hpp"
#include "savingplanmasterlist.hpp"
#include "commitmentproductlist.hpp"
#include "supportedproductslist.hpp"
#include "taxtyperulelist.hpp"
#include "translationlist.hpp"
#include "translationtable.hpp"
#include "provincelist.hpp"
#include "DefaultMailOPtionList.hpp"
#include "frequencylist.hpp"
#include "SystemVerificationDetailsList.hpp"
#include "NEQDetailsList.hpp"
#include "feemodelsetuplist.hpp"
#include "DefaultSysConfigDetailList.hpp"
#include "DefaultSysConfigList.hpp"
#include "NetworkConfigDetailList.hpp"
#include "TradeTransTypeSetFromMiscInfoList.hpp" 
#include "FinInstRegDetlList.hpp"
#include "translationtablebyasyncreading.hpp"
#include "FundRuleList.hpp"

namespace CND
{
   extern const long ERR_EMPTY_CLIENT_ID;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId CompanyId;
   extern CLASS_IMPORT const BFTextFieldId ClientID;
   extern CLASS_IMPORT const BFTextFieldId CompanyName;
   extern CLASS_IMPORT const BFTextFieldId CompanyUrl;
   extern CLASS_IMPORT const BFTextFieldId CompanyCode;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME      = I_("MgmtCo");
   const I_CHAR * const MGMT_CO_FIELD  = I_("CompanyId");
   const I_CHAR * const FATCA          = I_("FA");
   const I_CHAR * const FATCA_CRSRP	   = I_("FA,CRSRP");
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
//  Field DD Id,            State Flags,             Group Flags 
   {ifds::CompanyId,    BFCBO::READ_ONLY,    0}, 
   {ifds::CompanyName,  BFCBO::READ_ONLY,    0}, 
   {ifds::ClientID,     BFCBO::READ_ONLY,    0}, 
   {ifds::CompanyUrl,   BFCBO::READ_ONLY,    0}, 
};

namespace FUND_RULE_TYPE
{
    extern CLASS_IMPORT I_CHAR * const SOFT_CAPPED;
}

static const int NUM_FIELDS = sizeof (classFieldInfo) / sizeof (BFCBO::CLASS_FIELD_INFO);


//******************************************************************************
MgmtCo::MgmtCo (BFAbstractCBO &parent) 
: MFCanBFCbo (parent)
, pFundMasterList_(NULL)
, pFundDetailList_(NULL)
, pMgmtCoOptions_(NULL)
, pMgmtCoOptions2_(NULL)
, pTranslationList_(NULL)
, pSupportedProductsList_(NULL)
, pLSIFCodesList_(NULL)
, pTaxTypeRuleList_(NULL)
, pGroupList_(NULL)
, pGroupFundList_(NULL)
, pFeeSetupTradeRulesList_(NULL)
, pCurrencyList_(NULL)
, pErrMsgRulesList_(NULL)
, pFundSponsorsList_(NULL)
, pIntermediaryList_(NULL)
, pMasterContractList_(NULL)
, pSavingPlanMasterList_(NULL)
, pCommitmentProductList_(NULL)
, pRecipientTypeList_(NULL)
, pDocumentTypeList_ (NULL)
, pFeeParamConfigList_(NULL)
, pDynamicSubListHolder_(NULL)
, pFeeParamSysList_(NULL)
, pDefaultMailOptionList_(NULL)
, pFrequencyList_(NULL)
, pSystemVerificationDetailsList_(NULL)
, pNEQDetailsList_(NULL)
, pFeeModelSetupList_(NULL)
, pDefaultSysConfigList_(NULL)
, pDefaultSysConfigDetailList_(NULL)
, pNetworkConfigDetailList_(NULL)
, pTradeTransTypeSetFromMiscInfoList_(NULL)
, pMiscInfoExternalInstitutionList_(nullptr)
//, pFinInstRegDetlList_(NULL)
, referenceCount (0)
{
   TRACE_CONSTRUCTOR (CLASSNAME, I_("MgmtCo::MgmtCo () "));

   registerMemberData ( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                        0,
                        NULL
                      );
}

//******************************************************************************
MgmtCo::~MgmtCo ()
{
   TRACE_DESTRUCTOR (CLASSNAME);
   delObject_X( pFundMasterList_, _csFundMasterList );
   delObject_X( pFundDetailList_, _csFundDetailList );
   delObject_X( pMgmtCoOptions_, _csMgmtCoOptions );
   delObject_X( pMgmtCoOptions2_, _csMgmtCoOptions2 );
   delObject_X( pTranslationList_, _csTranslationList );
   delObject_X( pSupportedProductsList_, _csSupportedProductsList );
   delObject_X( pLSIFCodesList_, _csLSIFCodesList );
   delObject_X( pTaxTypeRuleList_, _csTaxTypeRuleList );
   delObject_X( pGroupList_, _csGroupList );
   delObject_X( pGroupFundList_, _csGroupFundList );
   delObject_X( pFeeSetupTradeRulesList_, _csFeeSetupTradeRulesList );
   delObject_X( pCurrencyList_, _csCurrencyList );
   delObject_X( pErrMsgRulesList_, _csErrMsgRulesList );
   delObject_X( pFundSponsorsList_, _csFundSponsorsList );
   delObject_X( pIntermediaryList_, _csIntermediaryList );
   delObject_X( pMasterContractList_, _csMasterContractList );
   delObject_X( pSavingPlanMasterList_, _csSavingPlanMasterList );
   delObject_X( pCommitmentProductList_, _csCommitmentProductList );
   delObject_X( pRecipientTypeList_, _csRecipientTypeList );
   delObject_X( pDocumentTypeList_, _csDocumentTypeList );
   delObject_X( pFeeParamConfigList_, _csFeeParamConfigList );
   delObject_X( pDynamicSubListHolder_, _csDynamicSubListHolder );
   delObject_X( pFeeParamSysList_, _csFeeParamSysList );
   delObject_X( pDefaultMailOptionList_, _csDefaultMailOption );
   delObject_X( pFrequencyList_, _csFrequencyList ); 
   delObject_X( pSystemVerificationDetailsList_, _csSystemVerificationDetailsList ); 
   delObject_X( pNEQDetailsList_, _csNEQDetailsList ); 
   delObject_X( pFeeModelSetupList_, _csFeeModelSetupList); 
   delObject_X( pDefaultSysConfigList_,		_csDefaultSysConfigList);
   delObject_X( pDefaultSysConfigDetailList_,	_csDefaultSysConfigDetailList);
   delObject_X( pNetworkConfigDetailList_, _csNetworkConfigDetailList);
   delObject_X( pTradeTransTypeSetFromMiscInfoList_, _csTradeTransTypeSetFromMiscInfoList);
   delObject_X( pMiscInfoExternalInstitutionList_, _csMiscInfoExternalInstitutionList);
   //delObject_X( pFinInstRegDetlList_, _csFinInstRegDetlList);
}     

//******************************************************************************
SEVERITY MgmtCo::init (const DString &companyId)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   setFieldNoValidate (ifds::CompanyId, companyId, BF::HOST);

   DString clientId, companyName, companyUrl;

   getSecurity ()->getClientId (companyId, clientId, companyName, companyUrl);

   setFieldNoValidate (ifds::CompanyName, companyName, BF::HOST);
   setFieldNoValidate (ifds::CompanyUrl, companyUrl, BF::HOST);

   MgmtCoOptions *pMgmtCoOptions = NULL;
   getMgmtCoOptions (pMgmtCoOptions);

   if(pMgmtCoOptions == NULL)
      return GETCURRENTHIGHESTSEVERITY();

   FundMasterList *pFundMasterList;
   getFundMasterList (pFundMasterList);

   FundDetailList *pFundDetailList;
   getFundDetailList (pFundDetailList);

   // with ACS, ClientID of a company should be get from CompanyCode of view 149
   if(pMgmtCoOptions != NULL)
   {
      pMgmtCoOptions->getField (ifds::CompanyCode, clientId, BF::HOST);
      if (clientId.empty ())
      {
         THROWFROMFILE2 (CND::IFASTCBO_CONDITION, 
                      CLASSNAME, 
                      I_("init"), 
                      CND::ERR_EMPTY_CLIENT_ID);
      }

      setFieldNoValidate (ifds::ClientID, clientId, BF::HOST);
   }

   MgmtCoOptions2 *pMgmtCoOptions2;
   getMgmtCoOptions2 (pMgmtCoOptions2);

   TranslationList *pTranslationList;
   getTranslationList (pTranslationList);

   SupportedProductsList *pSupportedProductsList;
   getSupportedProductsList (pSupportedProductsList);
 
   LSIFCodesList *pLSIFCodesList;
   getLSIFCodesList (pLSIFCodesList);

   TaxTypeRuleList *pTaxTypeRuleList;
   getTaxTypeRuleList (pTaxTypeRuleList);

   FeeSetupTradeRulesList *pFeeSetupTradeRulesList;
   getFeeSetupTradeRulesList (pFeeSetupTradeRulesList);

   CurrencyList *pCurrencyList;
   getCurrencyList (pCurrencyList);

   ErrMsgRulesList *pErrMsgRulesList;
   getErrMsgRulesList (pErrMsgRulesList);

   FeeParamConfigList *pFeeParamConfigList;
   getFeeParamConfigList (pFeeParamConfigList);

   SystemVerificationDetailsList *pSystemVerificationDetailsList;
   getSystemVerificationDetailsList(pSystemVerificationDetailsList);

   NEQDetailsList *pNEQDetailsList;
   getNEQDetailsList(pNEQDetailsList);

   FinInstRegDetlList *pFATCAFinInstRegDetlList;
   getFinInstRegDetlList(FATCA_CRSRP,pFATCAFinInstRegDetlList);

   MiscInfoExternalInstitutionList *pMiscInfoExternalInstitutionList;
   getMiscInfoExternalInstitutionList(pMiscInfoExternalInstitutionList);

   FundRuleList *pSoftCapRuleList;
   getFundRuleList(FUND_RULE_TYPE::SOFT_CAPPED, pSoftCapRuleList);

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY MgmtCo::getFundMasterList (FundMasterList *&pFundMasterList)
{
   return getObject_X ( I_("getFundMasterList"), 
                        pFundMasterList_, 
                        _csFundMasterList, 
                        pFundMasterList);
}

//******************************************************************************
SEVERITY MgmtCo::getFundDetailList (FundDetailList *&pFundDetailList)
{
   return getObject_X ( I_("getFundDetailList"), 
                        pFundDetailList_, 
                        _csFundDetailList, 
                        pFundDetailList);
}


//******************************************************************************
SEVERITY MgmtCo::getMgmtCoOptions (MgmtCoOptions *&pMgmtCoOptions)
{
   return getObject_X ( I_("getMgmtCoOptions"), 
                        pMgmtCoOptions_, 
                        _csMgmtCoOptions, 
                        pMgmtCoOptions);
}

//******************************************************************************
SEVERITY MgmtCo::getMgmtCoOptions2 (MgmtCoOptions2 *&pMgmtCoOptions2)
{
   return getObject_X ( I_("getMgmtCoOptions2"), 
                        pMgmtCoOptions2_, 
                        _csMgmtCoOptions2, 
                        pMgmtCoOptions2);
}

//******************************************************************************
SEVERITY MgmtCo::getTranslationList (TranslationList *&pTranslationList)
{
 /* PTS 10038677 : Remove this logic since the data from this view is not used for any purpose
                   all the Jprocess that refer to this list are obsolete code and translation is not
						 needed for update via API nor Desktop display
						 There is client with over 5000 funds with over 30000 records in this table
						 loading all this translation up front will eat up resource and slow down the fund master list
						 and fund detail list initialization. System hang when user enter trade
 return getObject_X ( I_("getTranslationList"), 
                        pTranslationList_, 
                        _csTranslationList, 
                        pTranslationList
                      );*/
	return NO_CONDITION;
}

//******************************************************************************
SEVERITY MgmtCo::getSupportedProductsList (SupportedProductsList *&pSupportedProductsList)
{
   return getObject_X ( I_("getSupportedProductsList"), 
                        pSupportedProductsList_, 
                        _csSupportedProductsList, 
                        pSupportedProductsList);
}

//******************************************************************************
SEVERITY MgmtCo::getLSIFCodesList (LSIFCodesList *&pLSIFCodesList)
{
   return getObject_X ( I_("getLSIFCodesList"), 
                        pLSIFCodesList_, 
                        _csLSIFCodesList, 
                        pLSIFCodesList);
}

//******************************************************************************
SEVERITY MgmtCo::getTaxTypeRuleList (TaxTypeRuleList *&pTaxTypeRuleList)
{
   return getObject_X ( I_("getTaxTypeRuleList"), 
                        pTaxTypeRuleList_, 
                        _csTaxTypeRuleList, 
                        pTaxTypeRuleList);
}

//******************************************************************************
SEVERITY MgmtCo::getGroupList (GroupList *&pGroupList)
{
   return getObject_X ( I_("getGroupList"), 
                        pGroupList_, 
                        _csGroupList, 
                        pGroupList);
}

//******************************************************************************
SEVERITY MgmtCo::getGroupFundList (GroupFundList *&pGroupFundList)
{
   return getObject_X ( I_("getGroupFundList"), 
                        pGroupFundList_, 
                        _csGroupFundList, 
                        pGroupFundList);
}


//******************************************************************************
SEVERITY MgmtCo::getFeeSetupTradeRulesList (FeeSetupTradeRulesList *&pFeeSetupTradeRulesList)
{
   return getObject_X ( I_("getFeeSetupTradeRulesList"), 
                        pFeeSetupTradeRulesList_, 
                        _csFeeSetupTradeRulesList, 
                        pFeeSetupTradeRulesList);
}

//******************************************************************************
SEVERITY MgmtCo::getCurrencyList (CurrencyList *&pCurrencyList)
{
   return getObject_X ( I_("getCurrencyList"), 
                        pCurrencyList_, 
                        _csCurrencyList, 
                        pCurrencyList);
}

//******************************************************************************
SEVERITY MgmtCo::getFeeModelSetupList(FeeModelSetupList *&pFeeModelSetupList)
{
   return getObject_X ( I_("getFeeModelSetupList"), 
                        pFeeModelSetupList_, 
                        _csFeeModelSetupList, 
                        pFeeModelSetupList);
}

//****************************************************************************************
SEVERITY MgmtCo::getErrMsgRulesList (ErrMsgRulesList *&pErrMsgRulesList)
{
   return getObject_X ( I_("getErrMsgRulesList"), 
                        pErrMsgRulesList_, 
                        _csErrMsgRulesList, 
                        pErrMsgRulesList);
}

//******************************************************************************
SEVERITY MgmtCo::getFundSponsorsList (FundSponsorsList *&pFundSponsorsList)
{
   return getObject_X ( I_("getFundSponsorsList"), 
                        pFundSponsorsList_, 
                        _csFundSponsorsList, 
                        pFundSponsorsList);
}

//******************************************************************************
SEVERITY MgmtCo::getIntermediaryList (IntermediaryList *&pIntermediaryList)
{
   return getObject_X ( I_("getIntermediaryList"), 
                        pIntermediaryList_, 
                        _csIntermediaryList, 
                        pIntermediaryList);
}

//****************************************************************************************
SEVERITY MgmtCo::getMasterContractList (MasterContractList *&pMasterContractList)
{
   return getObject_X ( I_("getMasterContractList"), 
                        pMasterContractList_, 
                        _csMasterContractList, 
                        pMasterContractList);
};

//**********************************************************************************************
SEVERITY MgmtCo::getSavingPlanMasterList (SavingPlanMasterList *&pSavingPlanMasterList)
{
   return getObject_X ( I_("getSavingPlanMasterList"), 
                        pSavingPlanMasterList_, 
                        _csSavingPlanMasterList, 
                        pSavingPlanMasterList);

}
//**********************************************************************************************
SEVERITY MgmtCo::getCommitmentProductList (CommitmentProductList *&pCommitmentProductList)
{
   return getObject_X ( I_("getCommitmentProductList"), 
                        pCommitmentProductList_, 
                        _csCommitmentProductList, 
                        pCommitmentProductList);

}
//******************************************************************************
SEVERITY MgmtCo::getRecipientTypeList (RecipientTypeList *&pRecipientTypeList)
{
   return getObject_X ( I_("getRecipientTypeList"), 
                        pRecipientTypeList_, 
                        _csRecipientTypeList, 
                        pRecipientTypeList);
}

//**********************************************************************************************
SEVERITY MgmtCo::getDocumentTypeList (DocumentTypeList *&pDocumentTypeList)
{
   return getObject_X ( I_("getDocumentTypeList"), 
                        pDocumentTypeList_, 
                        _csDocumentTypeList, 
                        pDocumentTypeList);
}

//******************************************************************************
SEVERITY MgmtCo::getFeeParamConfigList (FeeParamConfigList *&pFeeParamConfigList)
{
   return getObject_X ( I_("getFeeParamConfigList"), 
                        pFeeParamConfigList_, 
                        _csFeeParamConfigList, 
                        pFeeParamConfigList);
}

//**********************************************************************************************
DynamicSubListHolder* MgmtCo::getDynamicSubListHolder ()
{
   if (NULL == pDynamicSubListHolder_)
   {
      BFGuard cs (_csDynamicSubListHolder);
      if (NULL == pDynamicSubListHolder_)
      {
         pDynamicSubListHolder_ = new DynamicSubListHolder (*this);
      }
   }

   return (pDynamicSubListHolder_);
}


//******************************************************************************
SEVERITY MgmtCo::getLSIFRolloverRulesList ( const DString &fromFund,
                                            const DString &fromClass,
                                            LSIFRolloverRulesList *&pLSIFRolloverRulesList
                                          )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getLSIFRolloverRulesList"));

   BFGuard cs (_csLSIFRolloverRulesList);
   DString strFromFund (fromFund),
      strFromClass (fromClass);

   strFromFund.strip().upperCase();
   strFromClass.strip().upperCase();
   pLSIFRolloverRulesList = 
         dynamic_cast<LSIFRolloverRulesList *> (getObject (strFromFund + I_("_") + strFromClass, BF::HOST));
   if (!pLSIFRolloverRulesList)
   {
      pLSIFRolloverRulesList = new LSIFRolloverRulesList (*this);
      if (pLSIFRolloverRulesList->init (fromFund, fromClass) <= WARNING)
      {
			setObject ( pLSIFRolloverRulesList, 
                     strFromFund + I_("_") + strFromClass, 
                     OBJ_ACTIVITY_NONE, 
                     BF::HOST
                   );
      }
      else
      {
         delete pLSIFRolloverRulesList;
         pLSIFRolloverRulesList = NULL;
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY MgmtCo::getFundGroupSubList ( FundGroupSubList *&pFundGroupSubList, 
                                       const DString &dstrType)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION,
                           CLASSNAME,
                           I_("getFundGroupSubList"));

   DString dstrGroupType (dstrType);

   BFGuard cs (_csFundGroupSubList);
	
   dstrGroupType.upperCase();
   pFundGroupSubList = dynamic_cast<FundGroupSubList *> (getObject (dstrGroupType, BF::HOST));
   if (!pFundGroupSubList)
   {
// if does not exist, create a new one
      pFundGroupSubList = new FundGroupSubList( *this );
      if (pFundGroupSubList && pFundGroupSubList->init( dstrGroupType ) <= WARNING)
      {
         setObject (pFundGroupSubList, dstrGroupType, OBJ_ACTIVITY_NONE, BF::HOST);
      }
      else
      {
         delete pFundGroupSubList;
         pFundGroupSubList = NULL;
      }
	}
   return GETCURRENTHIGHESTSEVERITY ();
}


//******************************************************************************
SEVERITY MgmtCo::getFundCommGroupList ( const DString &dstrFundGroupType,  
                                        FundCommGroupList *&pFundCommGroupList)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION,
                           CLASSNAME,
                           I_("getFundCommGroupList (FundCommGroupList *&)"));

   BFGuard cs (_csFundCommGroupList);
   DString dstrGroupType (dstrFundGroupType);
   
   dstrGroupType.strip ().upperCase ();
	pFundCommGroupList = dynamic_cast<FundCommGroupList*> (getObject (dstrGroupType, BF::HOST));
   if (!pFundCommGroupList)
   {
// if does not exist, create a new one
      pFundCommGroupList = new FundCommGroupList (*this);
      if (pFundCommGroupList->init (dstrFundGroupType) <= WARNING)
      {
			setObject (pFundCommGroupList, dstrGroupType, OBJ_ACTIVITY_NONE, BF::HOST);
      }
      else
      {
         delete pFundCommGroupList;
         pFundCommGroupList = NULL;
      }
	}
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY MgmtCo::getFundGroupTypeList ( FundGroupTypeList *&pFundGroupTypeList, 
                                        const DString &fundGroupType)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getFundGroupTypeList"));

   BFGuard cs (_csFundGroupTypeList);

   pFundGroupTypeList = dynamic_cast<FundGroupTypeList *> (getObject (fundGroupType, BF::HOST));
   if (!pFundGroupTypeList)
   {
      pFundGroupTypeList = new FundGroupTypeList (*this);
      if (pFundGroupTypeList->init (fundGroupType) <= WARNING)
	   {
         setObject (pFundGroupTypeList, fundGroupType, OBJ_ACTIVITY_NONE, BF::HOST);
      }
      else
		{
         delete pFundGroupTypeList;
			pFundGroupTypeList = NULL;
	   }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//************************************************************************************
SEVERITY MgmtCo::getDocumentTypeOverrideList ( const DString &dstrGroupCode,
                                               DocumentTypeOverrideList *&pDocumentTypeOverrideList)
{

   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION,
                          CLASSNAME,
                          I_("getDocumentTypeOverrideList"));

   BFGuard cs (_csDocumentTypeOverrideList);
	
	DString mdstrGroupCode (dstrGroupCode); 

   mdstrGroupCode.strip ().upperCase ();
	pDocumentTypeOverrideList = dynamic_cast<DocumentTypeOverrideList *> (getObject (mdstrGroupCode, BF::HOST));
	if (!pDocumentTypeOverrideList)
	{
      // if it is not existed, create a new one
      pDocumentTypeOverrideList = new DocumentTypeOverrideList (*this);
      if (pDocumentTypeOverrideList->init (mdstrGroupCode) <= WARNING)
      {
         setObject (pDocumentTypeOverrideList, mdstrGroupCode, OBJ_ACTIVITY_NONE, BF::HOST);
      }
      else
      {
			delete pDocumentTypeOverrideList;
			pDocumentTypeOverrideList = NULL;
      }
	}
   return GETCURRENTHIGHESTSEVERITY ();
}

//************************************************************************************
SEVERITY MgmtCo::getTranslationTable ( const DString &dstrGrpCode, 
                                       TranslationTable *&pTranslationTable)
{

   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION,
                           CLASSNAME,
                           I_("getTranslationTable"));

   BFGuard cs (_csTranslationTable) ;	
   DString dstrGroupCode (dstrGrpCode); 
   
   dstrGroupCode.strip ().upperCase ();
	pTranslationTable = dynamic_cast<TranslationTable *> (getObject (dstrGroupCode, BF::HOST));
   if (!pTranslationTable)
   {
// if does not exist, create a new one
      pTranslationTable = new TranslationTable (*this);
      if (pTranslationTable->init (dstrGroupCode) <= WARNING)
      {
         setObject (pTranslationTable, dstrGroupCode, OBJ_ACTIVITY_NONE, BF::HOST);
      }
      else
      {
         delete pTranslationTable;
         pTranslationTable = NULL;
      }
	}
   return GETCURRENTHIGHESTSEVERITY ();
}
//**********************************************************************************************
SEVERITY MgmtCo::getDefaultFeeParamSysList (FeeParamSysList *&pFeeParamSysList)
{
   if (NULL != pFeeParamSysList_)
   {
      pFeeParamSysList = pFeeParamSysList_;
      return (NO_CONDITION);
   }

   BFGuard cs (_csFeeParamSysList);
 
   if (NULL != pFeeParamSysList_)
   {
      pFeeParamSysList = pFeeParamSysList_;
      return (NO_CONDITION);
   }

   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION,
                          CLASSNAME,
                          I_("getFeeParamSysList (pFeeParamSysList *&)"));

   pFeeParamSysList = new FeeParamSysList (*this);
   if (pFeeParamSysList->initForDefault (BF::HOST ) >= SEVERE_ERROR)
   {
		delete pFeeParamSysList;
		pFeeParamSysList=NULL;
   }
   pFeeParamSysList_ = pFeeParamSysList;

   return GETCURRENTHIGHESTSEVERITY ();

}

//******************************************************************************
SEVERITY MgmtCo::getDefaultSysConfigList (DefaultSysConfigList *&pDefaultSysConfigList)
{
   if (NULL != pDefaultSysConfigList_)
   {
      pDefaultSysConfigList = pDefaultSysConfigList_;
      return (NO_CONDITION);
   }

   BFGuard cs (_csDefaultSysConfigList);
 
   if (NULL != pDefaultSysConfigList_)
   {
      pDefaultSysConfigList = pDefaultSysConfigList_;
      return (NO_CONDITION);
   }

   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION,
                          CLASSNAME,
                          I_("getDefaultSysConfigList (pDefaultSysConfigList *&)"));

   pDefaultSysConfigList = new DefaultSysConfigList (*this);
   if (pDefaultSysConfigList->init () >= SEVERE_ERROR)
   {
      delete pDefaultSysConfigList;
      pDefaultSysConfigList=NULL;
   }
   pDefaultSysConfigList_ = pDefaultSysConfigList;

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY MgmtCo::getDefaultSysConfigDetailList (DefaultSysConfigDetailList *&pDefaultSysConfigDetailList)
{
   if (NULL != pDefaultSysConfigDetailList_)
   {
      pDefaultSysConfigDetailList = pDefaultSysConfigDetailList_;
      return (NO_CONDITION);
   }

   BFGuard cs (_csDefaultSysConfigDetailList);
 
   if (NULL != pDefaultSysConfigDetailList_)
   {
      pDefaultSysConfigDetailList = pDefaultSysConfigDetailList_;
      return (NO_CONDITION);
   }

   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION,
                          CLASSNAME,
                          I_("getDefaultSysConfigList (pDefaultSysConfigList *&)"));

   pDefaultSysConfigDetailList = new DefaultSysConfigDetailList (*this);
   if (pDefaultSysConfigDetailList->init() >= SEVERE_ERROR)
   {
      delete pDefaultSysConfigDetailList;
      pDefaultSysConfigDetailList=NULL;
   }
   pDefaultSysConfigDetailList_ = pDefaultSysConfigDetailList;

   return GETCURRENTHIGHESTSEVERITY ();
}
//******************************************************************************
SEVERITY MgmtCo::getNetworkConfigDetailList (NetworkConfigDetailList *&pNetworkConfigDetailList)
{
   BFGuard cs (_csNetworkConfigDetailList);
 
   if (pNetworkConfigDetailList_ != NULL)
   {
      pNetworkConfigDetailList = pNetworkConfigDetailList_;
      return (NO_CONDITION);
   }

   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION,
                          CLASSNAME,
                          I_("getNetworkConfigDetailList (pNetworkConfigDetailList *&)"));

   pNetworkConfigDetailList = new NetworkConfigDetailList (*this);
   if (pNetworkConfigDetailList->init() >= SEVERE_ERROR)
   {
		delete pNetworkConfigDetailList;
		pNetworkConfigDetailList=NULL;
   }
   pNetworkConfigDetailList_ = pNetworkConfigDetailList;

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY MgmtCo::getFinInstRegDetlList(const DString &dstrComplyRule,
                                       FinInstRegDetlList *&pFinInstRegDetlList)
{
   //return getObject_X ( I_("getFinInstRegDetlList"), 
   //                     pFinInstRegDetlList_, 
   //                     _csFinInstRegDetlList, 
   //                     pFinInstRegDetlList);

   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION,
                          CLASSNAME,
                          I_("getFinInstRegDetlList"));

   BFGuard cs (_csFinInstRegDetlList);

   DString strComplyRule (I_("FinInstRegDetlList")); 

   strComplyRule += I_("_");
   strComplyRule += dstrComplyRule;
   pFinInstRegDetlList = dynamic_cast<FinInstRegDetlList*> (getObject (strComplyRule, BF::HOST));
   if (!pFinInstRegDetlList)
   {
      // if it is not existed, create a new one
      pFinInstRegDetlList = new FinInstRegDetlList (*this);
      if (pFinInstRegDetlList->init (dstrComplyRule) <= WARNING)
      {
         setObject (pFinInstRegDetlList, strComplyRule, OBJ_ACTIVITY_NONE, BF::HOST);
      }
      else
      {
         delete pFinInstRegDetlList;
         pFinInstRegDetlList = NULL;
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY MgmtCo::getFundRuleList(const DString &dstrRuleType, FundRuleList *&pFundRuleList)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION,
                          CLASSNAME,
                          I_("getFundRuleList"));

//###BFGuard cs (_csFinInstRegDetlList);
    DString dstrKey (I_("RuleType=") + dstrRuleType);

    pFundRuleList = dynamic_cast<FundRuleList*>(getObject(dstrKey, BF::HOST));

    if (!pFundRuleList)
    {
        pFundRuleList = new FundRuleList(*this);

        if (pFundRuleList->init(dstrRuleType) <= WARNING)
        {
            setObject(pFundRuleList, dstrKey, OBJ_ACTIVITY_NONE, BF::HOST);
        }
        else
        {
            delete pFundRuleList;
            pFundRuleList = NULL;
        }
    }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
void MgmtCo::buildKey (const DString& strMgmtCo, DString &strKey)
{
   //because we want to keep the mgmtco as long as the user doesn't change it,
   //we will not build the key based on the worksession id
   strKey += MGMT_CO_FIELD;
   strKey += I_("=");
   DString strTemp = strMgmtCo;
   strTemp.strip ();
   strTemp.stripLeading ( (I_CHAR)'0');
   strKey += strTemp;
}

//******************************************************************************
template <class _X>
   SEVERITY MgmtCo::getObject_X ( const I_CHAR* i_methodName, 
                                  _X *&pXMember, 
                                  BFCritSec &bfCS,
                                  _X *&pXOut)
{
   if (NULL != pXMember)
   {
      pXOut = pXMember;
      return NO_CONDITION;
   }
   
   BFGuard cs (bfCS);

   if (NULL != pXMember)
   {
      pXOut = pXMember;
      return NO_CONDITION;
   }

   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           i_methodName
                         );

   pXOut = new _X (*this);
   if (pXOut->init () >= SEVERE_ERROR)
   {
      delete pXOut;
      pXOut = NULL;
   }
   pXMember = pXOut;
   return GETCURRENTHIGHESTSEVERITY ();
}

//*******************************************************************************
template <class _X>
void MgmtCo::delObject_X( _X*& pList, BFCritSec &bfCS )
{
   if( pList != NULL )
   {
      BFGuard cs (bfCS);
      delete pList;
      pList = NULL;
   }
}

//**********************************************************************************************
SEVERITY MgmtCo::getProvinceList( const DString& dstrCountryCode, 
                                  ProvinceList *&pProvinceList )
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION,
                          CLASSNAME,
                          I_( "getProvinceList" ));

   BFGuard cs (_csProvinceList) ;	
   DString dstrLocalCountryCode(dstrCountryCode); 

   dstrLocalCountryCode.strip ().upperCase ();
   pProvinceList = dynamic_cast<ProvinceList*>(getObject( dstrLocalCountryCode, BF::HOST ) );
    
	if (!pProvinceList )
    {
      // if does not exist, create a new one
      pProvinceList = new ProvinceList (*this);
      if ( pProvinceList->init (dstrLocalCountryCode) <= WARNING )
      {
         setObject (pProvinceList, dstrLocalCountryCode, OBJ_ACTIVITY_NONE, BF::HOST );
      }
      else
      {
         delete pProvinceList;
         pProvinceList = NULL;
      }
	}

	return GETCURRENTHIGHESTSEVERITY ();
}

//**********************************************************************************************
SEVERITY MgmtCo::getFrequencyList (FrequencyList *&pFrequencyList)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION,
                          CLASSNAME,
                          I_( "getFrequencyList" ) );
	 
   return getObject_X ( I_("getFrequencyList"), 
                        pFrequencyList_, 
                        _csFrequencyList, 
                        pFrequencyList);

	return GETCURRENTHIGHESTSEVERITY ();
}

//**********************************************************************************************
SEVERITY MgmtCo::getDefaultMailOptionList (DefaultMailOptionList *&pDefaultMailOptionList )
{
   if( pDefaultMailOptionList_ != NULL )
   {
      pDefaultMailOptionList = pDefaultMailOptionList_;
      return NO_CONDITION;
   }
	BFGuard cs (_csDefaultMailOption) ;	
   if( pDefaultMailOptionList_ != NULL )
   {
      pDefaultMailOptionList = pDefaultMailOptionList_;
      return NO_CONDITION;
   }

	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION,
                          CLASSNAME,
                          I_( "getDefaultMailOptionList" ) );

   pDefaultMailOptionList = new DefaultMailOptionList(*this);
   pDefaultMailOptionList_ = pDefaultMailOptionList;
   
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY MgmtCo::getSystemVerificationDetailsList(SystemVerificationDetailsList *&pSystemVerificationDetailsList)
{

   return getObject_X ( I_("getSystemVerificationDetailsList"), 
                        pSystemVerificationDetailsList_, 
                        _csSystemVerificationDetailsList, 
                        pSystemVerificationDetailsList);
}

//******************************************************************************
SEVERITY MgmtCo::getNEQDetailsList(NEQDetailsList *&pNEQDetailsList)
{

   return getObject_X ( I_("getpNEQDetailsList"), 
                        pNEQDetailsList_, 
                        _csNEQDetailsList, 
                        pNEQDetailsList);
}

//******************************************************************************
SEVERITY MgmtCo::getTradeTransTypeSetFromMiscInfoList(TradeTransTypeSetFromMiscInfoList *&pTradeTransTypeSetFromMiscInfoList)
{

   return getObject_X ( I_("getTradeTransTypeSetFromMiscInfoList"), 
                        pTradeTransTypeSetFromMiscInfoList_, 
                        _csTradeTransTypeSetFromMiscInfoList, 
                        pTradeTransTypeSetFromMiscInfoList);
}

//******************************************************************************
SEVERITY MgmtCo::getMiscInfoExternalInstitutionList(MiscInfoExternalInstitutionList *&pMiscInfoExternalInstitutionList)
{
   if (nullptr != pMiscInfoExternalInstitutionList_)
   {
      pMiscInfoExternalInstitutionList = pMiscInfoExternalInstitutionList_;
      return NO_CONDITION;
   }
   
   BFGuard cs (_csMiscInfoExternalInstitutionList);

   if (nullptr != pMiscInfoExternalInstitutionList_)
   {
      pMiscInfoExternalInstitutionList = pMiscInfoExternalInstitutionList_;
      return NO_CONDITION;
   }

   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getMiscInfoExternalInstitutionList")
                         );

   MiscInfoExternalInstitutionList *pObj = new MiscInfoExternalInstitutionList (*this);
   if (pObj && pObj->init () >= SEVERE_ERROR)
   {
      delete pObj;
      pObj = nullptr;
   }
   pMiscInfoExternalInstitutionList = pMiscInfoExternalInstitutionList_ = pObj;

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/mgmtco.cpp-arc  $
 * 
 *    Rev 1.81   Jun 08 2012 09:41:36   yingz
 * fixing IN2821255 by set client id from companycode returned by view 149
 * 
 *    Rev 1.80   Feb 24 2012 18:44:30   if991250
 * Account Commitment
 * 
 *    Rev 1.79   Apr 20 2010 16:13:50   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.78   Nov 16 2009 06:40:58   dchatcha
 * P0166583 - Static Data Change Phase 2 - FN02-03-04
 * 
 *    Rev 1.77   20 Aug 2009 15:25:36   popescu
 * 95  - ACL replacement project - 
 * 
 *    Rev 1.76   31 Jul 2009 13:39:40   popescu
 * 95  - ACL replacement project - 
 * 
 *    Rev 1.75   24 Jul 2008 12:01:00   popescu
 * Incident - 1190617 - set all the data init calls to be asynch
 * 
 *    Rev 1.74   06 Dec 2007 15:20:02   popescu
 * Incident 1088629 - read the ACL set-up for the web pages URL instead of the using the xml configuration file.
 * 
 *    Rev 1.73   Jun 22 2007 14:22:34   porteanm
 * PET 2360 FN02 - AMS - work in progress.
 * 
 *    Rev 1.72   Sep 21 2005 16:47:26   yingbaol
 * PET1277,FN09 Investment Fund Continious Disclosure
 * 
 *    Rev 1.71   Sep 02 2005 09:17:32   popescu
 * BPS performance issues - cached call to view 253 - fee param config list
 * 
 *    Rev 1.70   Mar 21 2005 10:16:40   yingbaol
 * Incident 240192: speed up getDefault fee parameters
 * 
 *    Rev 1.69   Feb 25 2005 10:18:40   popescu
 * Incident#  243353, pre-loaded the err msg rules list, view 142, to enhance performance, synch-up from release 60.0.0.0
 * 
 *    Rev 1.68   Feb 22 2005 15:05:14   porteanm
 * PET1171 FN01 - Added getProvinceList().
 * 
 *    Rev 1.67   Feb 21 2005 15:26:08   Fengyong
 * 21193 BPServer error : "User needs to log on first"
 * 
 *    Rev 1.65   Feb 11 2005 17:44:28   winnie
 * PTS 10038677 : Remove calling of translation-info view 136 since nothing in Desktop nor BPServer require this information. Client has over 30000 records in this table that cause major delay in initialization.
 * 
 *    Rev 1.64   Nov 25 2004 10:31:46   popescu
 * Removed fee param config list from pre-loading since the view is very slow
 * 
 *    Rev 1.63   Nov 16 2004 13:55:42   YINGBAOL
 * PTS10034074: Fix memory leak for multi management company environment.
 * 
 *    Rev 1.62   Nov 14 2004 14:50:12   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.61   Nov 04 2004 17:38:08   popescu
 * PET 1117/06, Trade processing
 * 
 *    Rev 1.60   Sep 21 2004 13:28:46   HERNANDO
 * PET1094 FN06 - Absatzmeldung Files enhancement.  Added getFundGroupSublist.
 * 
 *    Rev 1.59   May 09 2004 20:10:22   popescu
 * PET 985, FN 01, LSIF Trade Entry
 * 
 *    Rev 1.58   May 06 2004 18:38:14   popescu
 * PET 985, fn01, Trade Entry LSIF
 * 
 *    Rev 1.57   Feb 26 2004 13:43:56   popescu
 * PTS 10026434, changed name of parameters for method init to signal a broader use; changed the ASync call to a normal Receive call
 * 
 *    Rev 1.56   Oct 22 2003 17:04:58   HSUCHIN
 * PET809FN12 - Added code to retrieve transfer types from base.  Currently disabled.
 * 
 *    Rev 1.55   Oct 03 2003 19:22:10   popescu
 * CIBC PET 809, FN13, removed references to BankList 
 * 
 *    Rev 1.54   Oct 02 2003 14:19:14   HERNANDO
 * Added getTranslationTable.
 * 
 *    Rev 1.53   Jun 20 2003 16:30:26   linmay
 * PTS#10014935
 * 
 *    Rev 1.52   Apr 21 2003 09:49:42   YINGBAOL
 * add getDocumentTypeOverrideList
 * 
 *    Rev 1.51   Apr 15 2003 10:53:52   linmay
 * Sync up with 1.46.1.1
 * 
 *    Rev 1.50   Mar 25 2003 14:47:24   linmay
 * sync up
 * 
 *    Rev 1.49   Mar 21 2003 18:18:42   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.48   Mar 18 2003 16:13:18   linmay
 * modified getFundCommGroupList
 * 
 *    Rev 1.47   Mar 10 2003 14:52:22   linmay
 * added getFeeParamConfigList
 * 
 *    Rev 1.46   Feb 17 2003 10:24:54   YINGBAOL
 * take out FundFeeList
 * 
 *    Rev 1.45   Jan 13 2003 11:22:26   KOVACSRO
 * name change : fundtype into fundgrouptype
 * 
 *    Rev 1.44   Jan 12 2003 18:55:34   KOVACSRO
 * Added FundTypeList
 * 
 *    Rev 1.43   Jan 03 2003 19:41:10   YINGBAOL
 * make fundCommGroupList work
 * 
 *    Rev 1.42   Jan 02 2003 15:26:28   linmay
 * added GetFundCommGroupList
 * 
 *    Rev 1.41   Oct 09 2002 23:54:46   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.40   Sep 23 2002 15:20:04   YINGBAOL
 * small fix
 * 
 *    Rev 1.39   Sep 13 2002 15:56:06   YINGBAOL
 * add getDocumentTypeList
 * 
 *    Rev 1.38   Aug 29 2002 12:56:20   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.37   Jun 04 2002 11:26:56   YINGZ
 * getDynamicSubListHolder
 * 
 *    Rev 1.36   May 31 2002 17:06:12   YINGZ
 * for Robert
 * 
 *    Rev 1.35   May 31 2002 16:02:34   YINGZ
 * add getDynamicSubListHolder
 * 
 *    Rev 1.33   24 May 2002 15:47:16   KOVACSRO
 * getGroupFundList is back
 * 
 *    Rev 1.32   22 May 2002 18:29:34   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.31   Feb 25 2002 18:55:48   PURDYECH
 * Phase 1 of BFData Rollout - Base Component Compatibility
 * 
 *    Rev 1.30   Feb 18 2002 10:14:56   YINGBAOL
 * add getFundFeeList
 * 
 *    Rev 1.29   Nov 29 2001 16:31:04   ZHANGCEL
 * Comment getGroupFundList () since it has been move to Group CBO
 * 
 *    Rev 1.28   Oct 12 2001 13:13:48   HERNANDO
 * Added condition, ERR_EMPTY_CLIENT_ID.
 * 
 *    Rev 1.27   14 Aug 2001 11:19:10   SMITHDAV
 * Added ClientID field.
 * 
 *    Rev 1.26   09 Jul 2001 15:25:12   SMITHDAV
 * Mgmt company refresh related changes.
 * 
 *    Rev 1.25   25 May 2001 15:06:08   YINGZ
 * add getSavingPlanMasterList
 * 
 *    Rev 1.24   03 May 2001 14:06:52   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.23   Mar 21 2001 13:17:22   FENGYONG
 * add get Option2
 * 
 *    Rev 1.22   Feb 27 2001 14:39:10   FENGYONG
 * Add delete fundrelatelist
 * 
 *    Rev 1.21   Feb 14 2001 10:33:16   HSUCHIN
 * reorder init for better async.
 * 
 *    Rev 1.20   Jan 17 2001 12:08:26   VASILEAD
 * Added workSessionId param for MgmtCo::getMgmtCoOptions ()
 * 
 *    Rev 1.19   Dec 17 2000 20:24:06   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.18   Dec 17 2000 15:50:22   OLTEANCR
 * no change
 * 
 *    Rev 1.17   Dec 05 2000 13:54:30   VASILEAD
 * Added worksessionid for FundToList
 * 
 *    Rev 1.16   Nov 27 2000 11:37:16   VASILEAD
 * Added AllFundInfo support to provide with fund information for the global object in ECOMM
 * 
 *    Rev 1.15   Nov 22 2000 11:40:28   ZHANGCEL
 * Added function getRecipientType ()
 * 
 *    Rev 1.14   Nov 21 2000 10:50:00   VASILEAD
 * Added getFundSponsorsList
 * 
 *    Rev 1.13   Nov 20 2000 10:21:36   ZHANGCEL
 * Added function getErrMsgRulesList ()
 * 
 *    Rev 1.12   Nov 02 2000 14:11:36   VASILEAD
 * Added workSeesionId parameter for Mgmtco based CBOs
 * 
 *    Rev 1.11   Oct 24 2000 15:18:34   VASILEAD
 * Initialized TaxTypeRulesList in constructor
 * 
 *    Rev 1.10   Sep 04 2000 16:29:40   YINGZ
 * fix getTranslationList
 * 
 *    Rev 1.9   Aug 04 2000 13:58:42   YINGBAOL
 * change enquiry bank 
 * 
 *    Rev 1.8   Aug 02 2000 15:33:14   BUZILA
 * "locale"changes
 * 
 *    Rev 1.7   Jul 21 2000 15:12:12   VASILEAD
 * Initialize FundMaster, FundDetails and MgmtOptions
 * 
 *    Rev 1.6   Jul 14 2000 16:55:38   WINNIE
 * Add intermediary list to respository
 * 
 *    Rev 1.5   May 09 2000 17:51:58   DT24433
 * synchronized lazy initialization
 * 
 *    Rev 1.4   Apr 20 2000 16:38:46   BUZILA
 * changed to MgmtCoId
 * 
 *    Rev 1.3   Apr 14 2000 09:48:52   ZHANGCEL
 * Add GetMasterContract
 * 
 *    Rev 1.2   Apr 03 2000 08:55:28   BUZILA
 * Added FundToList to repository
 * 
 *    Rev 1.1   Mar 30 2000 18:02:16   BUZILA
 * moved BankList from BFSessionManager to MgmtCo
 * 
 *    Rev 1.0   Feb 15 2000 11:00:04   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.9   Dec 21 1999 13:37:16   POPESCUS
 * validations and misc
 * 
 *    Rev 1.8   Dec 20 1999 10:15:44   ZHANGCEL
 * add GetTaxTypeRule ()
 * 
 *    Rev 1.7   Dec 12 1999 16:25:50   POPESCUS
 * Xchgdata issue; create and delete the object in the CBO
*/