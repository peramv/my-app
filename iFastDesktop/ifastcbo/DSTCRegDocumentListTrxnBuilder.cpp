//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use orsuch information
//    may result in civil liabilities. disclosure of 
//
//    Copyright 1999 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : DSTCRegDocumentListTrxnBuilder.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCRegDocumentListTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"

#include <ifastdataimpl\dse_dstc0390_req.hpp>
#include <ifastdataimpl\dse_dstc0390_reqrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0390_vw.hpp>

#include "ifasthosttransactioncontainer.hpp"
#include "accountentityxref.hpp"
#include "demographics.hpp"
#include "dstcregdocumentlisttrxnbuilder.hpp"
#include "entity.hpp"
#include "mfaccount.hpp"
#include "mgmtco.hpp"
#include "regdocumentlist.hpp"
#include "regdocument.hpp"
#include "worksessionentitylist.hpp"
#include "dstclisttrxnbuilder.hpp"


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest REG_DOCLIST_MAINTENANCE ;
}
namespace
{
   const I_CHAR* CLASSNAME          = I_( "DSTCRegDocumentListTrxnBuilder" );
}

namespace CND
{
   extern const I_CHAR* IFASTCBO_CONDITION;
}

namespace KEYTYPES
{
   extern CLASS_IMPORT I_CHAR * const ACCOUNTNUM;
   extern CLASS_IMPORT I_CHAR * const ENTITYID;
}

namespace ifds // remove later
{
   extern CLASS_IMPORT const BFTextFieldId RegulatoryStandard;
}

namespace COMPLY_RULE
{
   extern CLASS_IMPORT const DString TaxCompliant;
   extern CLASS_IMPORT const DString AcctRegistration;
   extern CLASS_IMPORT const DString DeathClaim;
   extern CLASS_IMPORT const DString AccountholderRisk;
}

//******************************************************************************
SEVERITY DSTCRegDocumentListTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                            BFAbstractCBO* pObj,
                                                            HostTransactionContainer* pTrCont, 
                                                            BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("buildTransactions"));
   MFAccount* pMFAccount = dynamic_cast<MFAccount*>(pObj);

   if (pMFAccount)
   {
      DString accountNum;

      pMFAccount->getField (ifds::AccountNum, accountNum, BF::HOST);
      AccountEntityXref *pAccountEntityXref (NULL);
      WorkSessionEntityList *pWorkEntityList = NULL;
      workSession.getWorkSessionEntityList (pWorkEntityList);

      Demographics *pDemographics (NULL);
      DString regStandard;

//find the regulatory standard, get this from the demographics object
      if ( pMFAccount->getDemographicsList (pDemographics, BF::HOST) <= WARNING && 
            pDemographics)
      {
         pDemographics->getField (ifds::RegulatoryStandard, regStandard, BF::HOST);
      }

      if (workSession.getAccountEntityXref (BF::HOST, pAccountEntityXref) <= WARNING &&
          pAccountEntityXref)
      {
         BFObjIter iterAccountEntityXrefOut (*pAccountEntityXref, 
                                             BF::HOST, 
                                             true, 
                                             BFObjIter::ITERTYPE::NON_DELETED);
         DString searchKey;
      //read all the entities - not only the account owners
         AccountEntityXref::buildPartialKeyForAccount (searchKey, accountNum);
         iterAccountEntityXrefOut.begin (OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey);
         
		   std::set<DString> setEntityId;
         while (!iterAccountEntityXrefOut.end())
         {
            DString entityId;
            DString key = iterAccountEntityXrefOut.getStringKey ();
            AccountEntityXref::getValueForTag (key, I_("EntityId"), entityId);         
			
			   if(setEntityId.find(entityId) != setEntityId.end())
			   {
				   ++iterAccountEntityXrefOut;
				   continue;
			   }

			   setEntityId.insert(entityId);

		      if ( pWorkEntityList)
            {
               Entity *pEntity (NULL);

				   pWorkEntityList->getEntity (BF::HOST, entityId, pEntity);
				   if (pEntity)
				   {
                  if(regStandard.empty()) regStandard = I_("0");

					   buildEachTransaction(workSession, pTrCont, objActivity, 
                     pMFAccount, pEntity, regStandard, COMPLY_RULE::AcctRegistration);

					   buildEachTransaction(workSession, pTrCont, objActivity, 
                     pMFAccount, pEntity, I_("0"), COMPLY_RULE::DeathClaim);

					   buildEachTransaction(workSession, pTrCont, objActivity, 
						   pMFAccount, pEntity, I_(""), COMPLY_RULE::TaxCompliant);

                       //Build trasaction update for COMPLY_RULE::AccountholderRisk
                       buildEachTransaction(workSession, pTrCont, objActivity, 
						   pMFAccount, pEntity, I_(""), COMPLY_RULE::AccountholderRisk);
               }
            }
            ++iterAccountEntityXrefOut;
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

SEVERITY DSTCRegDocumentListTrxnBuilder::buildEachTransaction(
   DSTCWorkSession &workSession,
   HostTransactionContainer* pTrCont,
   BF_OBJ_ACTIVITY objActivity,
   MFAccount* pMFAccount,
   Entity *pEntity,
   const DString& regStandard,
   const DString& complyRule)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("buildEachTransaction"));
   //build the key for the reg doc list
   DString listKey;
   WorkSessionEntityList *pWorkEntityList = NULL;
   workSession.getWorkSessionEntityList (pWorkEntityList);

   DString entityId, accountNum;
   pEntity->getField(ifds::EntityId, entityId, BF::HOST);
   pMFAccount->getField (ifds::AccountNum, accountNum, BF::HOST);

   listKey =  I_("EntityID=") + entityId + I_(";");
   listKey += I_("RegulatoryStd=") + regStandard + I_(";");
   listKey += I_("ComplyRule=") + complyRule;

   RegDocumentList  *pRegDocumentList(NULL);

   pRegDocumentList = dynamic_cast <RegDocumentList *>(pMFAccount->getObject (listKey, BF::HOST));
         
   if (pRegDocumentList)
   {
	   DString keyTypes;   

      if(complyRule != COMPLY_RULE::DeathClaim)
      {
         addIDITagValue (keyTypes, KEYTYPES::ACCOUNTNUM, accountNum);
      }
	   addIDITagValue (keyTypes, KEYTYPES::ENTITYID, entityId);

	   DSTCListTrxnBuilder<RegDocument*> RegDocumentListTrxnBuilder;
	   DString key =  I_("EntityID=") + entityId + I_(";");
	   
	   key += I_("RegulatoryStd=") + regStandard + I_(";");
	   key += I_("ComplyRule=") + complyRule;
      std::vector <BFFieldId> fieldsRegDocumentList;

      if(complyRule != COMPLY_RULE::DeathClaim)
      {
         fieldsRegDocumentList.push_back (ifds::AccountNum);
      }
      fieldsRegDocumentList.push_back (ifds::EntityId);
      fieldsRegDocumentList.push_back (ifds::ComplyRule);
	   TRXNINFO regDocumentTrxnInfo( key, 
                                    DSTC_REQUEST::REG_DOCLIST_MAINTENANCE,
									         ifds::DSTC0390_REQ,
										      ifds::DSTC0390_REQRepeat_Record,
										      ifds::DSTC0390_VW,
                                    fieldsRegDocumentList);
	   RegDocumentListTrxnBuilder.buildTransactions( workSession, 
		 												         pTrCont, 
														         pRegDocumentList, 
  														         regDocumentTrxnInfo,
														         objActivity,
														         keyTypes); 
   }

   return GETHIGHESTSEVERITY();
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCRegDocumentListTrxnBuilder.cpp-arc  $
// 
//    Rev 1.8   Aug 13 2012 10:45:28   wutipong
// IN3055286 P0179630FN01 FATCA - Cannot modify document on Acct Doc List screen
// 
//    Rev 1.7   Jul 23 2012 12:26:00   wutipong
// PETP0179630_FN01 FATCA Account Entity Document Tracking
// 
//    Rev 1.6   06 Nov 2008 11:11:48   popescu
// KYC-AML fixes after system integrated testing
// 
//    Rev 1.5   04 Nov 2008 13:11:44   popescu
// KYC-AML fixes after system integrated testing
// 
//    Rev 1.4   03 Nov 2008 17:32:34   popescu
// KYC/AML - Joint accounts feature - after System Integrated Testing
// 
//    Rev 1.3   31 Oct 2008 16:18:22   popescu
// KYC/AML - joint accounts feature
*/