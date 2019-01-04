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
//    Copyright 2001 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : DSTCBankInstructionsTrxnBuilder.cpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : March 2001
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCBankInstructionsTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include <ifastdataimpl\dse_dstc0097_req.hpp>
#include <ifastdataimpl\dse_dstc0097_vw.hpp>
#include "dstcbankinstructionstrxnbuilder.hpp"
#include "ifasthosttransactioncontainer.hpp"
#include "clientbankinstructionslist.hpp"
#include "distributorbankinstructionslist.hpp"
#include "distributorrepository.hpp"
#include "fundbankinstructionslist.hpp"
#include "fundgroupbankinstructionslist.hpp"
#include "fundsponsorbankinstructionslist.hpp"
#include "fundbankinstructionslistrepository.hpp"
#include "directtradingbankinstructionslist.hpp"
#include "shareholderbankinstructionslist.hpp"
#include "shareholder.hpp"
#include "mgmtco.hpp"
#include "regagentbankInstructionslist.hpp"
#include "agentbankinstructionslistrepository.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest BANKING_UPDATE;
}
namespace
{
   const I_CHAR* CLASSNAME                    = I_ ("DSTCBankInstructionsTrxnBuilder");
   const I_CHAR* BUILDTRANSACTIONS            = I_ ("buildTransactions");
   const I_CHAR* BUILDSHAREHOLDERTRANSACTIONS = I_ ("buildShareholderTransactions");
   const I_CHAR* BUILDDISTRIBUTORTRANSACTIONS = I_ ("buildDistributorTransactions");
   const I_CHAR* BUILDCLIENTTRANSACTIONS      = I_ ("buildClientTransactions");
   const I_CHAR* BUILDFUNDTRANSACTIONS        = I_ ("buildFundTransactions");
   const I_CHAR* BUILDFUNDGROUPTRANSACTIONS   = I_ ("buildFundGroupTransactions");
   const I_CHAR* BUILDFUNDSPONSORTRANSACTIONS = I_ ("buildFundSponsorTransactions");
   const I_CHAR* BUILDREGAGENTTRANSACTIONS    = I_ ("buildRegAgentTransactions");
}

namespace CND
{
   extern const I_CHAR* IFASTCBO_CONDITION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;
   extern CLASS_IMPORT const BFNumericFieldId RepeatCount;
   extern CLASS_IMPORT const BFTextFieldId FundCode;
   extern CLASS_IMPORT const BFTextFieldId ClassCode;
   extern CLASS_IMPORT const BFTextFieldId FundSponsor;
   extern CLASS_IMPORT const BFTextFieldId BankInstrType;
   extern CLASS_IMPORT const BFTextFieldId RegAgent;
   extern CLASS_IMPORT const BFTextFieldId rxBankingEntity;
   extern CLASS_IMPORT const BFNumericFieldId rxAcctNum;
}

namespace KEYTYPES
{
   extern CLASS_IMPORT I_CHAR * const SHRNUM;
   extern CLASS_IMPORT I_CHAR * const ACCOUNTNUM;
}

namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR * const CLIENT;
   extern CLASS_IMPORT I_CHAR * const FUND;
} 

namespace BANKENTITY
{
   extern CLASS_IMPORT I_CHAR * const CLIENT;
   extern CLASS_IMPORT I_CHAR * const BROKER;
   extern CLASS_IMPORT I_CHAR * const BRANCH;
   extern CLASS_IMPORT I_CHAR * const SALESREP;
   extern CLASS_IMPORT I_CHAR * const SHAREHOLDER;
   extern CLASS_IMPORT I_CHAR * const FUND;
   extern CLASS_IMPORT I_CHAR * const FUND_CLASS;
   extern CLASS_IMPORT I_CHAR * const FUND_GROUP;
   extern CLASS_IMPORT I_CHAR * const FUND_SPONSOR;
   extern CLASS_IMPORT I_CHAR * const REG_AGENT;
   extern CLASS_IMPORT I_CHAR * const ACCOUNT;
}

namespace BANKINGLEVEL
{
   extern CLASS_IMPORT I_CHAR *  const SHAREHOLDER_LEVEL ;
   extern CLASS_IMPORT I_CHAR *  const ACCOUNT_LEVEL ;
   extern CLASS_IMPORT I_CHAR *  const SHAREHOLDER_AND_ACCOUNT_LEVEL ;
}

extern BF_OBJ_TYPE OBJ_TYPE_DISTRIBUTOR_BANK_INSTR;

//******************************************************************************
void DSTCBankInstructionsTrxnBuilder::buildTrxnKey (DString &strKey, 
   Shareholder* pShareholder)
{
   DString dstShrNum;

   pShareholder->getField (ifds::ShrNum, dstShrNum, BF::HOST, true);
   dstShrNum.stripLeading ('0').strip ();
   addIDITagValue (strKey, TRXNTAG::SHRBANKTAG, dstShrNum);
}

//******************************************************************************
void DSTCBankInstructionsTrxnBuilder::buildTrxnKey (DString& strKey, 
   ClientBankInstructionsList* pClientBankInstructionsList)
{
   addIDITagValue (strKey, TRXNTAG::CLIENTBANK, I_ ("0"));
}

//******************************************************************************
void DSTCBankInstructionsTrxnBuilder::buildTrxnKey (DString &strKey, 
   FundBankInstructionsList *pFundBankInstructionsList)
{
   DString dstrFundCode;
   
   pFundBankInstructionsList->getField (ifds::FundCode, dstrFundCode, BF::HOST, false);
   dstrFundCode.stripLeading ('0').strip ();
   addIDITagValue (strKey, TRXNTAG::FUNDBANK, dstrFundCode);
}

//******************************************************************************
const void DSTCBankInstructionsTrxnBuilder::buildTrxnKeyForBankingInstr (DString &strKey, const DString& dstrBankEntityType,
   const Shareholder* pShareholder) 
{
   if(BANKENTITY::SHAREHOLDER ==  dstrBankEntityType)
   {
    DString dstShrNum;
    pShareholder->getField (ifds::ShrNum, dstShrNum, BF::HOST, true);
    dstShrNum.stripLeading ('0').strip ();
    addIDITagValue (strKey, TRXNTAG::SHRBANKTAG, dstShrNum);
   }
   if(BANKENTITY::ACCOUNT==  dstrBankEntityType)
   {
    DString dstAcctNum;
    pShareholder->getField(ifds::AccountNum, dstAcctNum, BF::HOST, true); 
    dstAcctNum.stripLeading ('0').strip ();
    addIDITagValue (strKey, TRXNTAG::SHRBANKTAG, dstAcctNum);
   }
}

//******************************************************************************
SEVERITY DSTCBankInstructionsTrxnBuilder::buildTransactions (DSTCWorkSession &workSession, 
   BFAbstractCBO* pObj, HostTransactionContainer* pTrCont, 
   BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTTIVITY_NONE*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS);

   if (dynamic_cast<Shareholder*> (pObj))
   {
      buildDefaultShareholderTransactions (workSession, 
         dynamic_cast<Shareholder*> (pObj), pTrCont);
      buildDirectTradingTransactions (workSession, 
         dynamic_cast<Shareholder*> (pObj), pTrCont);
   } 
   else if (dynamic_cast<DistributorRepository*> (pObj))
   {
      buildDistributorTransactions (workSession, 
         dynamic_cast<DistributorRepository*> (pObj), pTrCont);
   } 
   else if (dynamic_cast<FundBankInstructionsListRepository*> (pObj))
   {
      buildFundTransactions (workSession, 
         dynamic_cast<FundBankInstructionsListRepository*> (pObj), pTrCont);
      buildFundGroupTransactions (workSession, 
         dynamic_cast<FundBankInstructionsListRepository*> (pObj), pTrCont);
      buildFundSponsorTransactions (workSession, 
         dynamic_cast<FundBankInstructionsListRepository*> (pObj), pTrCont);
   } 
   else if (dynamic_cast<ClientBankInstructionsList*> (pObj))
   {
      buildClientTransactions (workSession, 
         dynamic_cast<ClientBankInstructionsList*> (pObj), pTrCont);
   }
   else if (dynamic_cast<AgentBankInstructionsListRepository*> (pObj))  
   {
	   buildRegAgentTransactions(workSession, 
		   dynamic_cast<AgentBankInstructionsListRepository*> (pObj), pTrCont);
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY DSTCBankInstructionsTrxnBuilder::buildDefaultShareholderTransactions (
   DSTCWorkSession &workSession, 
   Shareholder *pShareholder, 
   HostTransactionContainer *pTrCont)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, BUILDSHAREHOLDERTRANSACTIONS);
   ShareholderBankInstructionsList* pShareholderBankInstructionsList = NULL;

   if (pShareholder->getShareholderBankInstructionsList (
      pShareholderBankInstructionsList, BF::HOST, false))
   {
      buildShareholderTransactions (
         workSession, 
         pShareholder,
         pShareholderBankInstructionsList,
         pTrCont);
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY DSTCBankInstructionsTrxnBuilder::buildDirectTradingTransactions (
   DSTCWorkSession &workSession, 
   Shareholder *pShareholder, 
   HostTransactionContainer *pTrCont)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, BUILDDISTRIBUTORTRANSACTIONS);
   DirectTradingBankInstructionsList* pDirectTradingBankInstructionsList = NULL;

   if (pShareholder->getDirectTradingBankInstructionsList (
      pDirectTradingBankInstructionsList, BF::HOST, false))
   {
      buildDirectTradingTransactions (
         workSession, 
         pShareholder,
         dynamic_cast<DirectTradingBankInstructionsList *>(pDirectTradingBankInstructionsList),
         pTrCont);
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY DSTCBankInstructionsTrxnBuilder::buildDirectTradingTransactions (
   DSTCWorkSession &workSession, 
   Shareholder *pShareholder, 
   DirectTradingBankInstructionsList *pDirectTradingBankInstructionsList, 
   HostTransactionContainer *pTrCont)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, BUILDSHAREHOLDERTRANSACTIONS);

   int count = 0;
   if (pDirectTradingBankInstructionsList != NULL)
   {
      DString strKey;
      DSTCBankInstructionsTrxnBuilder::buildTrxnKey (strKey, pShareholder);

      //define an iterator on the account distributions list
      BFObjIter iterBankInstructionsList (*pDirectTradingBankInstructionsList, BF::HOST);

		if ( iterBankInstructionsList.isDummy () ) 
		{
			return NO_CONDITION;
		}
      //define an iterator on the HostTransactionContainer
      HostTransactionContainerIterator iterTrxnContList (pTrCont);
      //set filter to look for Entity fixed area
      iterTrxnContList.walkStrKey (strKey);
      iterTrxnContList.walkTrxnGroup (NO_GROUP);
      iterTrxnContList.walkTrxnSubType (0);

      BFData* pDataReq = NULL;
      BFData* pDataRes = NULL;

      while (!iterBankInstructionsList.end () && !iterBankInstructionsList.hasTransactionUpdates ())
         ++iterBankInstructionsList;

      iterTrxnContList.begin ();

      if (!iterBankInstructionsList.end ())
      {
         if (iterTrxnContList.end ())
         {
            pDataReq = new BFData (ifds::DSTC0097_REQ);
            pDataRes = new BFData (ifds::DSTC0097_VW);

            DString dstTrack, dstActivity;
            pDirectTradingBankInstructionsList->getTrackActivity (dstTrack, dstActivity);
            pDataReq->setElementValue (ifds::Track,    dstTrack,    false, false);
            pDataReq->setElementValue (ifds::Activity, dstActivity, false, false);

            DString mgmtCoId;
            workSession.getMgmtCo ().getField (ifds::CompanyId, mgmtCoId, BF::HOST);
            pDataReq->setElementValue (ifds::CompanyId, mgmtCoId);

            DString dstShrNum;
            pShareholder->getField (ifds::ShrNum, dstShrNum, BF::HOST);
            pDataReq->setElementValue (ifds::ShrNum, dstShrNum, false, false);

            pDataReq->setElementValue (ifds::BankingEntity, BANKENTITY::SHAREHOLDER, false, false);

            DString keyTypes;
            addIDITagValue (keyTypes, KEYTYPES::SHRNUM, dstShrNum.stripLeading ('0').strip ());

            JData *jdata = new JData (DSTC_REQUEST::BANKING_UPDATE, pDataReq, pDataRes);
            pTrCont->addTransaction (strKey, jdata, OBJ_ACTIVITY_NONE, NOT_PERSISTENT, keyTypes);
         }
         else
         {
            pDataReq = (*iterTrxnContList)->getRequestDataObject ();
         }
      }

      while (!iterBankInstructionsList.end ())
      {
         if (iterBankInstructionsList.hasTransactionUpdates () && 
               iterBankInstructionsList.getKey ().getDataGroupId () == BF::HOST)
         {
            //create a repeat for the pDataReq and fill it in
            BFData repeat (ifds::DSTC0097_REQRepeat_Record);

            pDataReq->setElementValue (ifds::RepeatCount, DString::asString (++count), false, false);

            //fill in the pDataReq update, only the part for which this banking is responsible
            BFCBO* pBFBase = dynamic_cast< BFCBO* > (iterBankInstructionsList.getObject ());
            pBFBase->getData (repeat, BF::HOST);
            //set the RunMode field to the banking trxn
            BF_OBJ_ACTIVITY listObjActivity = iterBankInstructionsList.getKey ().getActivity ();
            DSTCWorkSession::setRunMode (&repeat, listObjActivity);     

            //add the repeat to the retrieved pDataReq
            pDataReq->addRepeat (repeat);
         }  // banking instruction available
         ++iterBankInstructionsList;
      }  // while loop
   } // banking instruction list not null

   return GETCURRENTHIGHESTSEVERITY ();
}
//******************************************************************************
SEVERITY DSTCBankInstructionsTrxnBuilder::buildShareholderTransactions (
   DSTCWorkSession &workSession, 
   Shareholder *pShareholder, 
   ShareholderBankInstructionsList *pShareholderBankInstructionsList, 
   HostTransactionContainer *pTrCont)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, BUILDSHAREHOLDERTRANSACTIONS);

   int count = 0;
   if (pShareholderBankInstructionsList != NULL)
   {
     DString dstrBankingLevel;
     pShareholderBankInstructionsList->getBankingConfiguration(dstrBankingLevel, BF::HOST);
     if(BANKINGLEVEL::SHAREHOLDER_LEVEL == dstrBankingLevel)
         buildShareholderBankTransactions (workSession, pShareholder, pShareholderBankInstructionsList,  pTrCont);
     else if(BANKINGLEVEL::ACCOUNT_LEVEL == dstrBankingLevel)
         buildAccountBankTransactions (workSession, pShareholder, pShareholderBankInstructionsList,  pTrCont);
     else if(BANKINGLEVEL::SHAREHOLDER_AND_ACCOUNT_LEVEL == dstrBankingLevel) 
     {     
         //doing this dirty hack as the view needs diffrent update calls using VIEW 97 for shareholder and entity 
         buildShareholderBankTransactions (workSession, pShareholder, pShareholderBankInstructionsList,  pTrCont);
         buildAccountBankTransactions (workSession, pShareholder, pShareholderBankInstructionsList,  pTrCont);
     }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}
//******************************************************************************
SEVERITY DSTCBankInstructionsTrxnBuilder::buildShareholderBankTransactions (
   DSTCWorkSession &workSession, 
   Shareholder *pShareholder, 
   ShareholderBankInstructionsList *pShareholderBankInstructionsList, 
   HostTransactionContainer *pTrCont )
{
    MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("buildShareholderBankTransactions"));
   
    DString dstrBankingEntity, dstrKeyForShrBankingUpdate;
    DSTCBankInstructionsTrxnBuilder::buildTrxnKeyForBankingInstr(dstrKeyForShrBankingUpdate, BANKENTITY::SHAREHOLDER, pShareholder);

    //Build the updates for the shareholder first if applicable
    HostTransactionContainerIterator iterTrxnContList (pTrCont);
    //set filter to look for Entity fixed area
    iterTrxnContList.walkStrKey (dstrKeyForShrBankingUpdate);
    iterTrxnContList.walkTrxnGroup (NO_GROUP);
    iterTrxnContList.walkTrxnSubType (0);
    BFObjIter iterBankInstructionsList (*pShareholderBankInstructionsList, BF::HOST);
   
    //dont update dummy
	if ( iterBankInstructionsList.isDummy () ) 
			return NO_CONDITION;

    BFData* pDataReq = NULL;
    BFData* pDataRes = NULL;
    int count = 0;
    //iterBankInstructionsList.begin();
    while (!iterBankInstructionsList.end ())
    {
      //doing this dirty hack as the view needs diffrent update calls using VIEW 97 for shareholder and entity 
      (iterBankInstructionsList.getObject())->getField(ifds::rxBankingEntity, dstrBankingEntity,BF::HOST);
      
      if( BANKENTITY::SHAREHOLDER == dstrBankingEntity && iterBankInstructionsList.hasTransactionUpdates())
      {
       
       // robs ..just putting down my thoughths as will save somebody's time...
       //DSTCListTrxnBuilder cannot be used as the list will have always entity type as 10- shareholder in an environment that supports account
       //and shareholder banking 
       // to over come this you need to first filter the data group and hard set the Banking entity to be 10 or 14 based 
       //unfortunately we dont have a key on the banking instrcution to filter either....
       //iterBankInstructionsList.setKeyFilter(BANKENTITY::SHAREHOLDER , true);
 
        iterTrxnContList.begin ();
        if (iterTrxnContList.end ())
        {
            pDataReq = new BFData (ifds::DSTC0097_REQ);
            pDataRes = new BFData (ifds::DSTC0097_VW);

            DString dstTrack, dstActivity;
            pShareholderBankInstructionsList->getTrackActivity (dstTrack, dstActivity);
            pDataReq->setElementValue (ifds::Track,    dstTrack,    false, false);
            pDataReq->setElementValue (ifds::Activity, dstActivity, false, false);

            DString mgmtCoId;
            workSession.getMgmtCo ().getField (ifds::CompanyId, mgmtCoId, BF::HOST);
            pDataReq->setElementValue (ifds::CompanyId, mgmtCoId);

            DString dstShrNum;
            pShareholder->getField (ifds::ShrNum, dstShrNum, BF::HOST);
            pDataReq->setElementValue (ifds::ShrNum, dstShrNum, false, false);

            pDataReq->setElementValue (ifds::BankingEntity, BANKENTITY::SHAREHOLDER, false, false);

            DString keyTypes;
            addIDITagValue (keyTypes, KEYTYPES::SHRNUM, dstShrNum.stripLeading ('0').strip ());

            JData *jdata = new JData (DSTC_REQUEST::BANKING_UPDATE, pDataReq, pDataRes);
            pTrCont->addTransaction (dstrKeyForShrBankingUpdate, jdata, OBJ_ACTIVITY_NONE, NOT_PERSISTENT, keyTypes);
        }
        else
        {
            pDataReq = (*iterTrxnContList)->getRequestDataObject ();
        }
        if(iterBankInstructionsList.getKey ().getDataGroupId () == BF::HOST)
        {
           //create a repeat for the pDataReq and fill it in
           BFData repeat (ifds::DSTC0097_REQRepeat_Record);
           pDataReq->setElementValue (ifds::RepeatCount, DString::asString (++count), false, false);
           //fill in the pDataReq update, only the part for which this banking is responsible
           BFCBO* pBFBase = dynamic_cast< BFCBO* > (iterBankInstructionsList.getObject ());
           pBFBase->getData (repeat, BF::HOST);           
           //set the RunMode field to the banking trxn
           BF_OBJ_ACTIVITY listObjActivity = iterBankInstructionsList.getKey ().getActivity ();
           DSTCWorkSession::setRunMode (&repeat, listObjActivity);     
           pDataReq->addRepeat(repeat);
        }
      }
      ++iterBankInstructionsList;
    }//while
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY DSTCBankInstructionsTrxnBuilder::buildAccountBankTransactions (
   DSTCWorkSession &workSession, 
   Shareholder *pShareholder, 
   ShareholderBankInstructionsList *pShareholderBankInstructionsList, 
   HostTransactionContainer *pTrCont )
{
    MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("buildShareholderBankTransactions"));
   
    DString dstrBankingEntity, dstrKeyForShrBankingUpdate;
    DSTCBankInstructionsTrxnBuilder::buildTrxnKeyForBankingInstr(dstrKeyForShrBankingUpdate, BANKENTITY::ACCOUNT, pShareholder);

    //Build the updates for the shareholder first if applicable
    HostTransactionContainerIterator iterTrxnContList (pTrCont);
    //set filter to look for Entity fixed area
    iterTrxnContList.walkStrKey (dstrKeyForShrBankingUpdate);
    iterTrxnContList.walkTrxnGroup (NO_GROUP);
    iterTrxnContList.walkTrxnSubType (0);
    BFObjIter iterBankInstructionsList (*pShareholderBankInstructionsList, BF::HOST);

    //dont update dummy
	if ( iterBankInstructionsList.isDummy () ) 
			return NO_CONDITION;

    BFData* pDataReq = NULL;
    BFData* pDataRes = NULL;
    int count = 0;
    //iterBankInstructionsList.begin();

    while (!iterBankInstructionsList.end ())
    {
      //doing this dirty hack as the view needs diffrent update calls using VIEW 97 for shareholder and entity 
      (iterBankInstructionsList.getObject())->getField(ifds::rxBankingEntity, dstrBankingEntity,BF::HOST);
       DString dstrAcctNum;
      (iterBankInstructionsList.getObject())->getField(ifds::rxAcctNum, dstrAcctNum,BF::HOST);
      if( BANKENTITY::ACCOUNT == dstrBankingEntity  && iterBankInstructionsList.hasTransactionUpdates())
      {
       
       // robs ..just putting down my thoughths as will same somebody's time...
       //DSTCListTrxnBuilder cannot be used as the list will have always entity type as 10- shareholder in an environment that supports account
       //and shareholder banking 
       // to over come this you need to first filter the data group and hard set the Banking entity to be 10 or 14 based 
       //unfortunately we dont have a key on the banking instrcution to filter either....
       //iterBankInstructionsList.setKeyFilter(BANKENTITY::SHAREHOLDER , true);
 
        iterTrxnContList.begin ();
        if (iterTrxnContList.end ())
        {
            pDataReq = new BFData (ifds::DSTC0097_REQ);
            pDataRes = new BFData (ifds::DSTC0097_VW);

            DString dstTrack, dstActivity;
            pShareholderBankInstructionsList->getTrackActivity (dstTrack, dstActivity);
            pDataReq->setElementValue (ifds::Track,    dstTrack,    false, false);
            pDataReq->setElementValue (ifds::Activity, dstActivity, false, false);

            DString mgmtCoId;
            workSession.getMgmtCo ().getField (ifds::CompanyId, mgmtCoId, BF::HOST);
            pDataReq->setElementValue (ifds::CompanyId, mgmtCoId);           
            pDataReq->setElementValue (ifds::AccountNum, dstrAcctNum, false, false);

            DString dstrShrNum;
            pShareholder->getField (ifds::ShrNum, dstrShrNum, BF::HOST);
            pDataReq->setElementValue (ifds::ShrNum, dstrShrNum, false, false);

            pDataReq->setElementValue (ifds::BankingEntity, BANKENTITY::ACCOUNT, false, false);
            DString keyTypes;
            addIDITagValue (keyTypes, KEYTYPES::ACCOUNTNUM, dstrAcctNum.stripLeading ('0').strip ());

            JData *jdata = new JData (DSTC_REQUEST::BANKING_UPDATE, pDataReq, pDataRes);
            pTrCont->addTransaction (dstrKeyForShrBankingUpdate, jdata, OBJ_ACTIVITY_NONE, NOT_PERSISTENT, keyTypes);
        }
        else
        {
            pDataReq = (*iterTrxnContList)->getRequestDataObject ();
        }
        if(iterBankInstructionsList.getKey ().getDataGroupId () == BF::HOST)
        {
           //create a repeat for the pDataReq and fill it in
           BFData repeat (ifds::DSTC0097_REQRepeat_Record);
           pDataReq->setElementValue (ifds::RepeatCount, DString::asString (++count), false, false);
           //fill in the pDataReq update, only the part for which this banking is responsible
           BFCBO* pBFBase = dynamic_cast< BFCBO* > (iterBankInstructionsList.getObject ());
           pBFBase->getData (repeat, BF::HOST);
           //set the RunMode field to the banking trxn
           BF_OBJ_ACTIVITY listObjActivity = iterBankInstructionsList.getKey ().getActivity ();
           DSTCWorkSession::setRunMode (&repeat, listObjActivity);   
           pDataReq->addRepeat(repeat);  
        }
      }
      ++iterBankInstructionsList;
    }//while
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY DSTCBankInstructionsTrxnBuilder::buildDistributorTransactions (
   DSTCWorkSession &workSession, 
   DistributorRepository* pDistributorRepository, 
   HostTransactionContainer* pTrCont)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, BUILDDISTRIBUTORTRANSACTIONS);

   DistributorBankInstructionsList* pDistributorBankInstructionsList = NULL;
   BFObjIter iterRep (*pDistributorRepository, BF::HOST);

   iterRep.begin (OBJ_TYPE_DISTRIBUTOR_BANK_INSTR, OBJ_ACTIVITY_NONE);
   while (!iterRep.end ())
   {
      if (iterRep.hasTransactionUpdates ())
      {
         int count = 0;
         DString dstTranKey;

         dstTranKey = I_ ("DistributorBank;");
         dstTranKey += iterRep.getStringKey ();
         pDistributorBankInstructionsList = dynamic_cast<DistributorBankInstructionsList*> (iterRep.getObject ());

         BFObjIter iterDistributorBankInstructionsList (*pDistributorBankInstructionsList, BF::HOST);
         HostTransactionContainerIterator iterTrxnContList (pTrCont);

         iterTrxnContList.walkStrKey (dstTranKey);
         iterTrxnContList.walkTrxnGroup (NO_GROUP);
         iterTrxnContList.walkTrxnSubType (0);

         BFData* pDataReq = NULL;
         BFData* pDataRes = NULL;

         while (!iterDistributorBankInstructionsList.end () && 
               !iterDistributorBankInstructionsList.hasTransactionUpdates ())
         {
            ++iterDistributorBankInstructionsList;
         }

         iterTrxnContList.begin ();

         if (!iterDistributorBankInstructionsList.end ())
         {
            if (iterTrxnContList.end ())
            {
               pDataReq = new BFData (ifds::DSTC0097_REQ);
               pDataRes = new BFData (ifds::DSTC0097_VW );

               DString dstTrack, dstActivity;

               pDistributorBankInstructionsList->getTrackActivity (dstTrack,dstActivity);
               pDataReq->setElementValue (ifds::Track,    dstTrack,    false, false);
               pDataReq->setElementValue (ifds::Activity, dstActivity, false, false);

               DString mgmtCoId;
               workSession.getMgmtCo ().getField (ifds::CompanyId, mgmtCoId, BF::HOST);
               pDataReq->setElementValue (ifds::CompanyId, mgmtCoId);

               DString dstBroker, dstBranch, dstSlsRep;

               pDistributorBankInstructionsList->getField (ifds::BrokerCode, dstBroker, BF::HOST, false);
               pDistributorBankInstructionsList->getField (ifds::BranchCode, dstBranch, BF::HOST, false);
               pDistributorBankInstructionsList->getField (ifds::SlsrepCode, dstSlsRep, BF::HOST, false);
               pDataReq->setElementValue (ifds::BrokerCode, dstBroker, false, false);
               pDataReq->setElementValue (ifds::BranchCode, dstBranch, false, false);
               pDataReq->setElementValue (ifds::SlsrepCode, dstSlsRep, false, false);
               DString dstBankingEntity;
               if (dstSlsRep != NULL_STRING)
               {
                  dstBankingEntity = BANKENTITY::SALESREP;
               }
               else if (dstBranch != NULL_STRING)
               {
                  dstBankingEntity = BANKENTITY::BRANCH;
               }
               else if (dstBroker != NULL_STRING)
               {
                  dstBankingEntity = BANKENTITY::BROKER;
               }
               else 
               {
                  assert (0);
               }

               pDataReq->setElementValue (ifds::BankingEntity, dstBankingEntity, false, false);

               JData *jdata = new JData (DSTC_REQUEST::BANKING_UPDATE, pDataReq, pDataRes);
               pTrCont->addTransaction (dstTranKey, jdata, OBJ_ACTIVITY_NONE, NOT_PERSISTENT, NULL_STRING);
            }
            else
            {
               pDataReq = (*iterTrxnContList)->getRequestDataObject ();
            }
         }

         while (!iterDistributorBankInstructionsList.end ())
         {
            if (iterDistributorBankInstructionsList.hasTransactionUpdates ())
            {
               //create a repeat for the pDataReq and fill it in
               BFData repeat (ifds::DSTC0097_REQRepeat_Record);

               pDataReq->setElementValue (ifds::RepeatCount, DString::asString (++count), false, false);

               //fill in the pDataReq update, only the part for which this banking is responsible
               BFCBO* pBFBase = dynamic_cast< BFCBO* > (iterDistributorBankInstructionsList.getObject ());
               pBFBase->getData (repeat, BF::HOST);
               //set the RunMode field to the banking trxn
               BF_OBJ_ACTIVITY listObjActivity = iterDistributorBankInstructionsList.getKey ().getActivity ();
               DSTCWorkSession::setRunMode (&repeat, listObjActivity);     

               //add the repeat to the retrieved pDataReq
               pDataReq->addRepeat (repeat);
            }  // banking instruction available
            ++iterDistributorBankInstructionsList;
         }  // while loop
      }
      ++iterRep;
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY DSTCBankInstructionsTrxnBuilder::buildClientTransactions (DSTCWorkSession &workSession, 
   ClientBankInstructionsList *pClientBankInstructionsList, HostTransactionContainer *pTrCont)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, BUILDCLIENTTRANSACTIONS);

   int count = 0;

   if (pClientBankInstructionsList && 
      pClientBankInstructionsList->hasTransactionUpdates ())
   {
      BFObjIter iter (*pClientBankInstructionsList, BF::HOST);

      while (!iter.end ())
      {
         BFCBO *pBase = dynamic_cast< BFCBO* > (iter.getObject ());
         BF_OBJ_ACTIVITY objActivity = iter.getKey ().getActivity ();

         if (pBase && (objActivity == OBJ_ACTIVITY_ADDED || 
               objActivity == OBJ_ACTIVITY_DELETED || 
               pBase->hasTransactionUpdates ()) )
         {
            DString strKey;

            buildTrxnKey (strKey, pClientBankInstructionsList);

            //define an iterator on the HostTransactionContainer
            HostTransactionContainerIterator iterTrxnContList (pTrCont);
            //set filter to look for Entity fixed area
            iterTrxnContList.walkStrKey (strKey);
            iterTrxnContList.walkTrxnGroup (NO_GROUP);
            iterTrxnContList.walkTrxnSubType (0);

            BFData* pDataReq = NULL;
            BFData* pDataRes = NULL;

            iterTrxnContList.begin ();
            if (iterTrxnContList.end ())
            {
               pDataReq = new BFData (ifds::DSTC0097_REQ);
               pDataRes = new BFData (ifds::DSTC0097_VW );

               DString dstTrack, dstActivity;
               
               pClientBankInstructionsList->getTrackActivity (dstTrack,dstActivity);
               pDataReq->setElementValue (ifds::Track,    dstTrack,    false, false);
               pDataReq->setElementValue (ifds::Activity, dstActivity, false, false);

               DString mgmtCoId;

               workSession.getMgmtCo ().getField (ifds::CompanyId, mgmtCoId, BF::HOST);
               pDataReq->setElementValue (ifds::CompanyId, mgmtCoId);
               pDataReq->setElementValue (ifds::BankingEntity, BANKENTITY::CLIENT, false, false);

               JData *jdata = new JData (DSTC_REQUEST::BANKING_UPDATE, pDataReq, pDataRes);
               pTrCont->addTransaction (strKey, jdata, OBJ_ACTIVITY_NONE, NOT_PERSISTENT, NULL_STRING);
            }
            else
            {
               pDataReq = (*iterTrxnContList)->getRequestDataObject ();
            }

            //create a repeat for the pDataReq and fill it in
            BFData repeat (ifds::DSTC0097_REQRepeat_Record);

            pDataReq->setElementValue (ifds::RepeatCount, DString::asString (++count), false, false);

            //fill in the pDataReq update, only the part for which this banking is responsible
            pBase->getData (repeat, BF::HOST);
            //set the RunMode field to the banking trxn
            DSTCWorkSession::setRunMode (&repeat, objActivity);     

            //add the repeat to the retrieved pDataReq
            pDataReq->addRepeat (repeat);
         }
         ++iter;
      }// while loop
   }
   return (GETCURRENTHIGHESTSEVERITY ());
}

//******************************************************************************
SEVERITY DSTCBankInstructionsTrxnBuilder::buildFundTransactions (DSTCWorkSession &workSession, 
   FundBankInstructionsListRepository *pFundBankInstructionsListRepository, 
   HostTransactionContainer *pTrCont)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, BUILDFUNDTRANSACTIONS);

   FundBankInstructionsList* pFundBankInstructionsList = NULL;
   BFObjIter iterRep (*pFundBankInstructionsListRepository, BF::HOST);

   while (!iterRep.end ())
   {
      if (iterRep.hasTransactionUpdates ())
      {
         int count = 0;
         DString dstTranKey;

         dstTranKey = I_ ("FundBank;");
         dstTranKey += iterRep.getStringKey ();
         pFundBankInstructionsList = dynamic_cast<FundBankInstructionsList*> (iterRep.getObject ());
         if( !pFundBankInstructionsList )
         {
            break;
         }
         BFObjIter iterFundBankInstructionsList (*pFundBankInstructionsList, BF::HOST);
         HostTransactionContainerIterator iterTrxnContList (pTrCont);

         iterTrxnContList.walkStrKey (dstTranKey);
         iterTrxnContList.walkTrxnGroup (NO_GROUP);
         iterTrxnContList.walkTrxnSubType (0);

         BFData* pDataReq = NULL;
         BFData* pDataRes = NULL;

         while (!iterFundBankInstructionsList.end () && 
               !iterFundBankInstructionsList.hasTransactionUpdates ())
         {
            ++iterFundBankInstructionsList;
         }
         iterTrxnContList.begin ();
         if (!iterFundBankInstructionsList.end ())
         {
            if (iterTrxnContList.end ())
            {
               pDataReq = new BFData (ifds::DSTC0097_REQ);
               pDataRes = new BFData (ifds::DSTC0097_VW );

               DString dstTrack, dstActivity;

               pFundBankInstructionsList->getTrackActivity (dstTrack, dstActivity);
               pDataReq->setElementValue (ifds::Track,    dstTrack,    false, false);
               pDataReq->setElementValue (ifds::Activity, dstActivity, false, false);

               DString mgmtCoId;
               workSession.getMgmtCo ().getField (ifds::CompanyId, mgmtCoId, BF::HOST);
               pDataReq->setElementValue (ifds::CompanyId, mgmtCoId);

               DString dstrFundCode, 
                  dstrClassCode;

               pFundBankInstructionsList->getField (ifds::FundCode, dstrFundCode, 
                  BF::HOST, false);
               pFundBankInstructionsList->getField (ifds::ClassCode, dstrClassCode, 
                  BF::HOST, false);
               pDataReq->setElementValue (ifds::FundCode, dstrFundCode, false, false);
               pDataReq->setElementValue (ifds::ClassCode, dstrClassCode, false, false);
               if (dstrClassCode.strip().empty())
               {
                  pDataReq->setElementValue (ifds::BankingEntity, BANKENTITY::FUND, false, false);
               }
               else
               {
                  pDataReq->setElementValue (ifds::BankingEntity, BANKENTITY::FUND_CLASS, false, false);
               }

               JData *jdata = new JData (DSTC_REQUEST::BANKING_UPDATE, pDataReq, pDataRes);

               pTrCont->addTransaction (dstTranKey, jdata, OBJ_ACTIVITY_NONE, NOT_PERSISTENT, NULL_STRING);
            }
            else
            {
               pDataReq = (*iterTrxnContList)->getRequestDataObject ();
            }
         }
         while (!iterFundBankInstructionsList.end ())
         {
            if (iterFundBankInstructionsList.hasTransactionUpdates ())
            {
               //create a repeat for the pDataReq and fill it in
               BFData repeat (ifds::DSTC0097_REQRepeat_Record);

               pDataReq->setElementValue (ifds::RepeatCount, DString::asString (++count), false, false);

               //fill in the pDataReq update, only the part for which this banking is responsible
               BFCBO* pBFBase = dynamic_cast< BFCBO* > (iterFundBankInstructionsList.getObject ());
               pBFBase->getData (repeat, BF::HOST);
               //set the RunMode field to the banking trxn
               BF_OBJ_ACTIVITY listObjActivity = iterFundBankInstructionsList.getKey ().getActivity ();
               DSTCWorkSession::setRunMode (&repeat, listObjActivity);     

               //add the repeat to the retrieved pDataReq
               pDataReq->addRepeat (repeat);
            }  // banking instruction available
            ++iterFundBankInstructionsList;
         }  // while loop
      }
      ++iterRep;
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY DSTCBankInstructionsTrxnBuilder::buildFundGroupTransactions (
   DSTCWorkSession &workSession, 
   FundBankInstructionsListRepository *pFundBankInstructionsListRepository, 
   HostTransactionContainer *pTrCont)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, BUILDFUNDGROUPTRANSACTIONS);

   FundGroupBankInstructionsList* pFundGroupBankInstructionsList = NULL;
   BFObjIter iterRep (*pFundBankInstructionsListRepository, BF::HOST);

   while (!iterRep.end ())
   {
      if (iterRep.hasTransactionUpdates ())
      {
         int count = 0;
         DString dstTranKey;

         dstTranKey = I_ ("FundGroup;");
         dstTranKey += iterRep.getStringKey ();
         pFundGroupBankInstructionsList = dynamic_cast<FundGroupBankInstructionsList*> (iterRep.getObject ());
         if( !pFundGroupBankInstructionsList )
         {
            break;
         }
         BFObjIter iterFundGroupBankInstructionsList (*pFundGroupBankInstructionsList, BF::HOST);
         HostTransactionContainerIterator iterTrxnContList (pTrCont);

         iterTrxnContList.walkStrKey (dstTranKey);
         iterTrxnContList.walkTrxnGroup (NO_GROUP);
         iterTrxnContList.walkTrxnSubType (0);

         BFData* pDataReq = NULL;
         BFData* pDataRes = NULL;

         while (!iterFundGroupBankInstructionsList.end () && 
                !iterFundGroupBankInstructionsList.hasTransactionUpdates ())
         {
            ++iterFundGroupBankInstructionsList;
         }
         iterTrxnContList.begin ();
         if (!iterFundGroupBankInstructionsList.end ())
         {
            if (iterTrxnContList.end ())
            {
               pDataReq = new BFData (ifds::DSTC0097_REQ);
               pDataRes = new BFData (ifds::DSTC0097_VW );

               DString dstTrack, dstActivity;

               pFundGroupBankInstructionsList->getTrackActivity (dstTrack, dstActivity);
               pDataReq->setElementValue (ifds::Track,    dstTrack,    false, false);
               pDataReq->setElementValue (ifds::Activity, dstActivity, false, false);

               DString mgmtCoId;
               workSession.getMgmtCo ().getField (ifds::CompanyId, mgmtCoId, BF::HOST);
               pDataReq->setElementValue (ifds::CompanyId, mgmtCoId);

               DString dstrFundGroup;

               pFundGroupBankInstructionsList->getField (ifds::FundGroup, dstrFundGroup, BF::HOST, false);
               pDataReq->setElementValue (ifds::FundGroup, dstrFundGroup, false, false);
               pDataReq->setElementValue (ifds::BankingEntity, BANKENTITY::FUND_GROUP, false, false);

               JData *jdata = new JData (DSTC_REQUEST::BANKING_UPDATE, pDataReq, pDataRes);

               pTrCont->addTransaction (dstTranKey, jdata, OBJ_ACTIVITY_NONE, NOT_PERSISTENT, NULL_STRING);
            }
            else
            {
               pDataReq = (*iterTrxnContList)->getRequestDataObject ();
            }
         }
         while (!iterFundGroupBankInstructionsList.end ())
         {
            if (iterFundGroupBankInstructionsList.hasTransactionUpdates ())
            {
               //create a repeat for the pDataReq and fill it in
               BFData repeat (ifds::DSTC0097_REQRepeat_Record);

               pDataReq->setElementValue (ifds::RepeatCount, DString::asString (++count), false, false);

               //fill in the pDataReq update, only the part for which this banking is responsible
               BFCBO* pBFBase = dynamic_cast< BFCBO* > (iterFundGroupBankInstructionsList.getObject ());
               pBFBase->getData (repeat, BF::HOST);
               //set the RunMode field to the banking trxn
               BF_OBJ_ACTIVITY listObjActivity = iterFundGroupBankInstructionsList.getKey ().getActivity ();
               DSTCWorkSession::setRunMode (&repeat, listObjActivity);     

               //add the repeat to the retrieved pDataReq
               pDataReq->addRepeat (repeat);
            }  // banking instruction available
            ++iterFundGroupBankInstructionsList;
         }  // while loop
      }
      ++iterRep;
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY DSTCBankInstructionsTrxnBuilder::buildFundSponsorTransactions (
   DSTCWorkSession &workSession, 
   FundBankInstructionsListRepository *pFundBankInstructionsListRepository, 
   HostTransactionContainer *pTrCont)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, BUILDFUNDSPONSORTRANSACTIONS);

   FundSponsorBankInstructionsList* pFundSponsorBankInstructionsList = NULL;
   BFObjIter iterRep (*pFundBankInstructionsListRepository, BF::HOST);

   while (!iterRep.end ())
   {
      if (iterRep.hasTransactionUpdates ())
      {
         int count = 0;
         DString dstTranKey;

         dstTranKey = I_ ("FundSponsor;");
         dstTranKey += iterRep.getStringKey ();
         pFundSponsorBankInstructionsList = dynamic_cast<FundSponsorBankInstructionsList*> (iterRep.getObject ());
         if( !pFundSponsorBankInstructionsList )
         {
            break;
         }
         BFObjIter iterFundSponsorBankInstructionsList (*pFundSponsorBankInstructionsList, BF::HOST);
         HostTransactionContainerIterator iterTrxnContList (pTrCont);

         iterTrxnContList.walkStrKey (dstTranKey);
         iterTrxnContList.walkTrxnGroup (NO_GROUP);
         iterTrxnContList.walkTrxnSubType (0);

         BFData* pDataReq = NULL;
         BFData* pDataRes = NULL;

         while (!iterFundSponsorBankInstructionsList.end () && 
               !iterFundSponsorBankInstructionsList.hasTransactionUpdates ())
         {
            ++iterFundSponsorBankInstructionsList;
         }
         iterTrxnContList.begin ();
         if (!iterFundSponsorBankInstructionsList.end ())
         {
            if (iterTrxnContList.end ())
            {
               pDataReq = new BFData (ifds::DSTC0097_REQ);
               pDataRes = new BFData (ifds::DSTC0097_VW );

               DString dstTrack, dstActivity;

               pFundSponsorBankInstructionsList->getTrackActivity (dstTrack, dstActivity);
               pDataReq->setElementValue (ifds::Track,    dstTrack,    false, false);
               pDataReq->setElementValue (ifds::Activity, dstActivity, false, false);

               DString mgmtCoId;
               workSession.getMgmtCo ().getField (ifds::CompanyId, mgmtCoId, BF::HOST);
               pDataReq->setElementValue (ifds::CompanyId, mgmtCoId);

               DString dstrFundSponsor;

               pFundSponsorBankInstructionsList->getField (ifds::FundSponsor, dstrFundSponsor, BF::HOST, false);
               pDataReq->setElementValue (ifds::FundSponsor, dstrFundSponsor, false, false);
               pDataReq->setElementValue (ifds::BankingEntity, BANKENTITY::FUND_SPONSOR, false, false);

               JData *jdata = new JData (DSTC_REQUEST::BANKING_UPDATE, pDataReq, pDataRes);

               pTrCont->addTransaction (dstTranKey, jdata, OBJ_ACTIVITY_NONE, NOT_PERSISTENT, NULL_STRING);
            }
            else
            {
               pDataReq = (*iterTrxnContList)->getRequestDataObject ();
            }
         }
         while (!iterFundSponsorBankInstructionsList.end ())
         {
            if (iterFundSponsorBankInstructionsList.hasTransactionUpdates ())
            {
               //create a repeat for the pDataReq and fill it in
               BFData repeat (ifds::DSTC0097_REQRepeat_Record);

               pDataReq->setElementValue (ifds::RepeatCount, DString::asString (++count), false, false);

               //fill in the pDataReq update, only the part for which this banking is responsible
               BFCBO* pBFBase = dynamic_cast< BFCBO* > (iterFundSponsorBankInstructionsList.getObject ());
               pBFBase->getData (repeat, BF::HOST);
               //set the RunMode field to the banking trxn
               BF_OBJ_ACTIVITY listObjActivity = iterFundSponsorBankInstructionsList.getKey ().getActivity ();
               DSTCWorkSession::setRunMode (&repeat, listObjActivity);     

               //add the repeat to the retrieved pDataReq
               pDataReq->addRepeat (repeat);
            }  // banking instruction available
            ++iterFundSponsorBankInstructionsList;
         }  // while loop
      }
      ++iterRep;
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//*******************************************************************************
SEVERITY DSTCBankInstructionsTrxnBuilder::buildRegAgentTransactions (
	DSTCWorkSession &workSession, 
	AgentBankInstructionsListRepository *pAgentBankInstructionsListRepository, 
	HostTransactionContainer *pTrCont)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, BUILDREGAGENTTRANSACTIONS);

	RegAgentBankInstructionsList* pRegAgentInstructionsList = NULL;
	BFObjIter iterRep (*pAgentBankInstructionsListRepository, BF::HOST);

	while (!iterRep.end ())
	{
		if (iterRep.hasTransactionUpdates ())
		{
			int count = 0;
			DString dstTranKey;

			dstTranKey = I_ ("RegAgent;");
			dstTranKey += iterRep.getStringKey ();
			pRegAgentInstructionsList = dynamic_cast<RegAgentBankInstructionsList*> (iterRep.getObject ());
			if( !pRegAgentInstructionsList )
			{
				break;
			}
			BFObjIter iterRegAgentBankInstructionsList (*pRegAgentInstructionsList, BF::HOST);
			HostTransactionContainerIterator iterTrxnContList (pTrCont);

			iterTrxnContList.walkStrKey (dstTranKey);
			iterTrxnContList.walkTrxnGroup (NO_GROUP);
			iterTrxnContList.walkTrxnSubType (0);

			BFData* pDataReq = NULL;
			BFData* pDataRes = NULL;

			while (!iterRegAgentBankInstructionsList.end () && 
				!iterRegAgentBankInstructionsList.hasTransactionUpdates ())
			{
				++iterRegAgentBankInstructionsList;
			}
			iterTrxnContList.begin ();
			if (!iterRegAgentBankInstructionsList.end ())
			{
				if (iterTrxnContList.end ())
				{
					pDataReq = new BFData (ifds::DSTC0097_REQ);
					pDataRes = new BFData (ifds::DSTC0097_VW );

					DString dstTrack, dstActivity;

					pRegAgentInstructionsList->getTrackActivity (dstTrack, dstActivity);
					pDataReq->setElementValue (ifds::Track,    dstTrack,    false, false);
					pDataReq->setElementValue (ifds::Activity, dstActivity, false, false);

					DString mgmtCoId;
					workSession.getMgmtCo ().getField (ifds::CompanyId, mgmtCoId, BF::HOST);
					pDataReq->setElementValue (ifds::CompanyId, mgmtCoId);

					DString dstrRegAgent;

					pRegAgentInstructionsList->getField (ifds::RegAgent, dstrRegAgent, BF::HOST, false);
					pDataReq->setElementValue (ifds::RegAgent, dstrRegAgent, false, false);
					pDataReq->setElementValue (ifds::BankingEntity, BANKENTITY::REG_AGENT, false, false);

					JData *jdata = new JData (DSTC_REQUEST::BANKING_UPDATE, pDataReq, pDataRes);

					pTrCont->addTransaction (dstTranKey, jdata, OBJ_ACTIVITY_NONE, NOT_PERSISTENT, NULL_STRING);
				}
				else
				{
					pDataReq = (*iterTrxnContList)->getRequestDataObject ();
				}
			}
			while (!iterRegAgentBankInstructionsList.end ())
			{
				if (iterRegAgentBankInstructionsList.hasTransactionUpdates ())
				{
					//create a repeat for the pDataReq and fill it in
					BFData repeat (ifds::DSTC0097_REQRepeat_Record);

					pDataReq->setElementValue (ifds::RepeatCount, DString::asString (++count), false, false);

					//fill in the pDataReq update, only the part for which this banking is responsible
					BFCBO* pBFBase = dynamic_cast< BFCBO* > (iterRegAgentBankInstructionsList.getObject ());
					pBFBase->getData (repeat, BF::HOST);
					//set the RunMode field to the banking trxn
					BF_OBJ_ACTIVITY listObjActivity = iterRegAgentBankInstructionsList.getKey ().getActivity ();
					DSTCWorkSession::setRunMode (&repeat, listObjActivity);     

					//add the repeat to the retrieved pDataReq
					pDataReq->addRepeat (repeat);
				}  // banking instruction available
				++iterRegAgentBankInstructionsList;
			}  // while loop
		}
		++iterRep;
	}
	return GETCURRENTHIGHESTSEVERITY ();
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCBankInstructionsTrxnBuilder.cpp-arc  $
 * 
 *    Rev 1.28   Apr 09 2012 13:23:52   wp040133
 * P0187485
 * Reg Agent banking setup ESS
 * Adding the Include file names correctly to rectify the build errors
 * 
 *    Rev 1.27   Apr 03 2012 21:36:20   wp040039
 * PETP0187485-Registartion Agent  Banking
 * 
 *    Rev 1.26   Oct 18 2006 15:53:32   popescu
 * PET 2217/26 STP Multiple Debit Accounts - fund sponsor banking
 * 
 *    Rev 1.25   Sep 10 2006 18:08:24   popescu
 * STP 2192/11
 * 
 *    Rev 1.24   Jul 31 2006 15:35:54   ZHANGCEL
 * PET2192 FN11 -- MgmtCo Banking related changes
 * 
 *    Rev 1.23   Nov 14 2004 14:31:42   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.22   Sep 24 2004 13:26:18   popescu
 * PET1094 FN06 - Absatzmeldung Files enhancement. sent the correct update transaction for fund and class banking
 * 
 *    Rev 1.21   Sep 21 2004 16:22:56   HERNANDO
 * PET1094 FN06 - Absatzmeldung Files enhancement.
 * 
 *    Rev 1.20   Oct 24 2003 13:16:24   FENGYONG
 * Add buildDirectTradingTransactions
 * 
 *    Rev 1.19   Oct 06 2003 12:43:06   popescu
 * Added banking support for DirectTrading enhancement
 * 
 *    Rev 1.18   Jul 25 2003 15:33:16   YINGBAOL
 * do not build transaction if it is dummy.
 * 
 *    Rev 1.17   May 31 2003 11:55:00   popescu
 * RRIF bank work
 * 
 *    Rev 1.16   May 23 2003 10:04:20   popescu
 * Part of bank instructions cleaning up process, moved the bank types into the ifastids project
 * 
 *    Rev 1.15   May 22 2003 15:00:38   popescu
 * name change 'left overs'
 * 
 *    Rev 1.14   May 22 2003 14:12:30   popescu
 * Replaced name 'BankInstr' with 'BankInstructions'; 
 * simplified child lists getters for the Shareholder object
// 
//    Rev 1.13   Mar 21 2003 18:04:26   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.12   Oct 09 2002 23:54:16   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.11   Aug 29 2002 12:55:24   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.10   Jul 31 2002 09:57:24   KOVACSRO
// more fixes for multiple banks.
// 
//    Rev 1.9   Jul 30 2002 11:10:22   HSUCHIN
// bug fix for multiple bank default entries from search screen.
// 
//    Rev 1.8   Jul 05 2002 11:56:46   KOVACSRO
// Introduced BankTypes
// 
//    Rev 1.7   Jun 28 2002 11:51:56   KOVACSRO
// reset international wire stuff when adding/modifying a Fund bank.
// 
//    Rev 1.6   Jun 07 2002 17:44:50   KOVACSRO
// Finally ! The view is here.
// 
//    Rev 1.5   24 May 2002 15:43:26   KOVACSRO
// Fund and Client bank.
// 
//    Rev 1.4   22 May 2002 18:27:08   PURDYECH
// BFData Implementation
// 
//    Rev 1.3   Feb 25 2002 18:55:22   PURDYECH
// Phase 1 of BFData Rollout - Base Component Compatibility
// 
//    Rev 1.2   23 May 2001 14:39:54   SMITHDAV
// Fill CompanyId to all request Data objects that are posted to the HTC.
// 
//    Rev 1.1   03 May 2001 14:06:12   SMITHDAV
// Session management restructuring.
// 
//    Rev 1.0   09 Mar 2001 18:07:04   BUZILAMI
// Initial revision.
 * 
*/