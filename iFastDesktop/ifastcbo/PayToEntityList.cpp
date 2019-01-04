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
//    Copyright 1999 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : PayToEntityList.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : June 2003
//
// ^CLASS    : PayToEntityList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "paytoentity.hpp"
#include "paytoentitylist.hpp"
#include <ifastdataimpl\dse_dstc0258_req.hpp>
#include <ifastdataimpl\dse_dstc0258_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest PAY_TO_ENTITY_LIST;
}

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME  = I_("PayToEntityList");
}

namespace CND
{  // Conditions used
   extern const long ERR_EFF_STOP_DATE_RANGE_OVERLAP;
   extern const long ERR_DUPLICATE_RECORD;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
                              //  Field DD Id, State Flags,   Group Flags 
   {ifds::BrokerCode, BFCBO::NONE,   0}, 
};

static const int NUM_FIELDS = sizeof(classFieldInfo) / sizeof(BFCBO::CLASS_FIELD_INFO);

namespace PAY_TO
{
   extern CLASS_EXPORT I_CHAR * const BROKER  = I_("BROKER");
   extern CLASS_EXPORT I_CHAR * const BRANCH = I_("BRANCH");
   extern CLASS_EXPORT I_CHAR * const SALESREP = I_("REP");
   extern CLASS_EXPORT I_CHAR * const CLIENT = I_("CLIENT");
}

//******************************************************************************
PayToEntityList::PayToEntityList (BFAbstractCBO &parent)
: MFCanBFCbo(parent),
_searchType(NULL_STRING),
_pRequestData(NULL)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   setObjectAsList();
   registerMemberData (NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL);
}

//******************************************************************************
PayToEntityList::~PayToEntityList()
{
   TRACE_DESTRUCTOR(CLASSNAME);
   if (_pRequestData != NULL)
   {
      delete _pRequestData;
      _pRequestData = NULL;
   }
}

//if broker code is NULL_STRING all records are returned
//******************************************************************************
SEVERITY PayToEntityList::init( const DString &dstrBrokerCode /*=NULL_STRING*/, 
										  const DString &searchTypeMgmt /*=NULL_STRING*/,
										  const BFDataGroupId &idDataGroup /*=BF::HOST*/, 
										  const DString &dstrTrack /*= I_("N")*/, 
										  const DString &dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   DString brokerCode (dstrBrokerCode);

   _searchType = searchTypeMgmt;
	_searchType.stripAll().upperCase();

   brokerCode.stripAll().upperCase();
   setFieldNoValidate (ifds::BrokerCode, brokerCode, idDataGroup, false);

   _pRequestData = new BFData (ifds::DSTC0258_REQ);

   DString mgmtCoIdOut;

	_pRequestData->setElementValue (ifds::BrokerCode, brokerCode);
   _pRequestData->setElementValue (ifds::SearchTypeMgmt, _searchType);
   _pRequestData->setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   _pRequestData->setElementValue (ifds::Track, dstrTrack);
   _pRequestData->setElementValue (ifds::Activity, dstrPageName);

   ReceiveData ( DSTC_REQUEST::PAY_TO_ENTITY_LIST, 
                 *_pRequestData, 
                 ifds::DSTC0258_VW, 
                 DSTCRequestor(getSecurity(), false));
   return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
SEVERITY PayToEntityList::doCreateNewObject ( BFCBO *&pBase, 
                                              DString &strKey, 
                                              const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateNewObject"));

   DString brokerCode, 
      searchType;
   
   getField (ifds::BrokerCode, brokerCode, idDataGroup);

   PayToEntity *pPayToEntity = new PayToEntity (*this);
   
   if (pPayToEntity->init (brokerCode, idDataGroup, _searchType ) > WARNING)
   {
//      delete pPayToEntity;
//      pPayToEntity = NULL;
   }
   pBase = pPayToEntity;
   return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
SEVERITY PayToEntityList::doCreateObject(const BFData &data, BFCBO *&pObjOut)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateObject"));

   PayToEntity *pPayToEntity = new PayToEntity(*this);

   if (pPayToEntity->init (data, _searchType) > WARNING)
   {
      //delete pPayToEntity;
      //pPayToEntity = NULL;
   }
   pObjOut = pPayToEntity;
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY PayToEntityList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getMore"));

   if (doMoreRecordsExist())
   {
      ReceiveData ( DSTC_REQUEST::PAY_TO_ENTITY_LIST, 
                    *_pRequestData, 
                    ifds::DSTC0258_VW, 
                    DSTCRequestor(getSecurity(), false));
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
/*void PayToEntityList::getStrKey(DString &strKey, const BFData *data)
{
   if (data) 
   {
      DString dstrBrokerCode = data->getElementValue(ifds::BrokerCode);
      DString dstrPaymentForCode = data->getElementValue(ifds::PaymentFor);
		DString dstrPayToEntity = data->getElementValue(ifds::PayToEntity);
      DString dstrPayToRid = data->getElementValue(ifds::PayEntityId);

      buildKey (strKey, dstrBrokerCode, dstrPaymentForCode, dstrPayToEntity, dstrPayToRid);
   }
   else
   {
      BFCBO::getStrKey(strKey, NULL);
   }
}

//******************************************************************************
void PayToEntityList::buildKey ( DString &dstrKey, 
                                 const DString &dstrBrokerCode, 
                                 const DString &dstrPaymentForCode, 
                                 const DString &dstrPayToEntity,
                                 const DString &dstrPayEntityRid)
{
   DString brokerCode (dstrBrokerCode);
   DString paymentForCode (dstrPaymentForCode);
	DString payToEntity (dstrPayToEntity);
   DString payEntityRid (dstrPayEntityRid);

   dstrKey = I_("Broker=") + brokerCode.strip().upperCase() + 
             I_(";PayFor=") + paymentForCode.strip().upperCase() +
		       I_(";PayToEntity=") + payToEntity.strip().upperCase() +
             I_(";PayEntityId=") + payEntityRid.strip();
}
*/

//********************************************************************
SEVERITY PayToEntityList::doValidateAll( const BFDataGroupId& idDataGroup, 
                                         long lValidateGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateAll"));
   BFObjIter iter(*this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);

   while (!iter.end())
   {
      PayToEntity *pPayToEntity = dynamic_cast<PayToEntity*>(iter.getObject());

      pPayToEntity->validatePayToEntity(idDataGroup);
      ++iter;
   }	
   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************
SEVERITY PayToEntityList::checkDuplicate ( const PayToEntity *pPayToEntityToCheck,
                                           const BFDataGroupId &idDataGroup,
                                           bool bDuplicateError /*= true*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("checkDuplicate"));

   std::set< DString > pIds;

   DString brokerCode, brokerCode_,
      paymentFor, paymentFor_,
		payToEntity, payToEntity_,
		effectiveDate, effectiveDate_,
		stopDate, stopDate_,
      payEntityId, payEntityId_,
      companyCode, companyCode_;

   //get the values for to check against
   pPayToEntityToCheck->getField (ifds::BrokerCode, brokerCode, idDataGroup);
   pPayToEntityToCheck->getField (ifds::PaymentFor, paymentFor, idDataGroup);
	pPayToEntityToCheck->getField (ifds::PayToEntity, payToEntity, idDataGroup);
	pPayToEntityToCheck->getField (ifds::EffectiveDate, effectiveDate, idDataGroup);
	pPayToEntityToCheck->getField (ifds::StopDate, stopDate, idDataGroup);
   pPayToEntityToCheck->getField (ifds::PayEntityId, payEntityId, idDataGroup);
   pPayToEntityToCheck->getField (ifds::CompanyCode, companyCode, idDataGroup);

    //getWorkSession().getOption (ifds::CompanyCode, companyCode, idDataGroup, false);

   //make it upper case
   brokerCode.stripAll().upperCase();
   paymentFor.stripAll().upperCase();
	payToEntity.stripAll().upperCase();
   companyCode.stripAll().upperCase();
   
   bool hasDuplicate = false;

   //check first whether in the list (in memory) we have a duplicate
   //this catches the newly added items, as well 
   BFObjIter iter (*this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);

   pIds.insert (payEntityId);
   while (!iter.end())
   {
      PayToEntity *pPayToEntity = dynamic_cast<PayToEntity*>(iter.getObject());

      if (pPayToEntity != pPayToEntityToCheck)
      {
         pPayToEntity->getField (ifds::BrokerCode, brokerCode_, idDataGroup);
         pPayToEntity->getField (ifds::PaymentFor, paymentFor_, idDataGroup);
			pPayToEntity->getField (ifds::PayToEntity, payToEntity_, idDataGroup);
			pPayToEntity->getField (ifds::EffectiveDate, effectiveDate_, idDataGroup);
			pPayToEntity->getField (ifds::StopDate, stopDate_, idDataGroup);
         pPayToEntity->getField (ifds::PayEntityId, payEntityId_, idDataGroup);
         pPayToEntity->getField (ifds::CompanyCode, companyCode_, idDataGroup);
         //make it upper case
         brokerCode_.stripAll().upperCase();
         paymentFor_.stripAll().upperCase();
			payToEntity_.stripAll().upperCase();
         companyCode_.stripAll().upperCase();
         if ( brokerCode  == brokerCode_ && 
				  paymentFor  == paymentFor_ && 
				  payToEntity == payToEntity_ &&
              /* companyCode == companyCode_ &&*/
              !(DSTCommonFunctions::CompareDates (stopDate, effectiveDate_) == DSTCommonFunctions::FIRST_EARLIER ||
                DSTCommonFunctions::CompareDates (stopDate_, effectiveDate) == DSTCommonFunctions::FIRST_EARLIER))
         {
			 if (_searchType == I_("MGMTCO"))
			 {
				 if (companyCode == companyCode_ )
					hasDuplicate = true;
			 }
			 else
				hasDuplicate = true;
            break;
         }
      }
      pIds.insert (payEntityId_);
      ++iter;
   }

//if no duplicates in memory, check the back-end
   if (!hasDuplicate)
   {
      PayToEntityList payToEntityList ((BFAbstractCBO&)(*this));

      if (payToEntityList.init (brokerCode, _searchType, idDataGroup) <= WARNING)
      {
         //since, for now there are max two records in this list,
         //we can afford to loop
         BFObjIter iter (payToEntityList, idDataGroup);

         while (!iter.end())
         {
            PayToEntity *pPayToEntity = dynamic_cast <PayToEntity*>(iter.getObject());

            pPayToEntity->getField (ifds::BrokerCode, brokerCode_, idDataGroup);
            pPayToEntity->getField (ifds::PaymentFor, paymentFor_, idDataGroup);
				pPayToEntity->getField (ifds::PayToEntity, payToEntity_, idDataGroup);
				pPayToEntity->getField (ifds::EffectiveDate, effectiveDate_, idDataGroup);
				pPayToEntity->getField (ifds::StopDate, stopDate_, idDataGroup);
            pPayToEntity->getField (ifds::PayEntityId, payEntityId_, idDataGroup);
            pPayToEntity->getField (ifds::CompanyCode, companyCode_, idDataGroup);
            //upper case
            brokerCode_.stripAll().upperCase();
            paymentFor_.stripAll().upperCase();
				payToEntity_.stripAll().upperCase();
            if ( pIds.find (payEntityId_) == pIds.end () && //not already checked in memory
                 payEntityId != payEntityId_ &&
                 brokerCode  == brokerCode_ && 
					  paymentFor  == paymentFor_ && 
                 payToEntity == payToEntity_ &&
                 companyCode == companyCode_ &&
                 !(DSTCommonFunctions::CompareDates (stopDate, effectiveDate_) == DSTCommonFunctions::FIRST_EARLIER ||
                   DSTCommonFunctions::CompareDates (stopDate_, effectiveDate) == DSTCommonFunctions::FIRST_EARLIER))
            {
               hasDuplicate = true;
//should check whether this is deleted in the memory
               BFObjIter iterInMemory (*this, idDataGroup);

               while (!iterInMemory.end())
               {
                  if (iterInMemory.getKey().getActivity() == OBJ_ACTIVITY_DELETED)
                  {
                     PayToEntity *pDeletedPayToEntity = dynamic_cast<PayToEntity*>(iterInMemory.getObject());
                     DString deletedBrokerCode, 
                           deletedPaymentFor, 
                           deletedPayToEntity,
								   deletedEffectiveDate, 
                           deletedStopDate,
                           deletedCompanyCode;

                     pDeletedPayToEntity->getField (ifds::BrokerCode, deletedBrokerCode, idDataGroup);
                     pDeletedPayToEntity->getField (ifds::PaymentFor, deletedPaymentFor, idDataGroup);
							pDeletedPayToEntity->getField (ifds::PayToEntity, deletedPayToEntity, idDataGroup);
							pDeletedPayToEntity->getField (ifds::EffectiveDate, deletedEffectiveDate, idDataGroup);
							pDeletedPayToEntity->getField (ifds::StopDate, deletedStopDate, idDataGroup);
                     pDeletedPayToEntity->getField (ifds::CompanyCode, deletedCompanyCode, idDataGroup);
                     //make it upper case
                     deletedBrokerCode.stripAll().upperCase();
                     deletedPaymentFor.stripAll().upperCase();
							deletedPayToEntity.stripAll().upperCase();
                     deletedCompanyCode.stripAll().upperCase();
                     if (brokerCode == deletedBrokerCode && 
                         paymentFor == deletedPaymentFor &&
								 payToEntity == deletedPayToEntity &&
                         stopDate == deletedStopDate &&
                         effectiveDate == deletedEffectiveDate &&
                         companyCode == deletedCompanyCode)
                     {
                        hasDuplicate = false;
                        break;
                     }
                  }
                  ++iterInMemory;
               }
               break;
            }
            ++iter;
         }
      }
   }
   if (hasDuplicate)
   {
        ADDCONDITIONFROMFILE (CND::ERR_DUPLICATE_RECORD);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/PayToEntityList.cpp-arc  $
// 
//    Rev 1.15   May 01 2007 10:48:02   jankovii
// IN#862766 - Payment Instr.
// 
//    Rev 1.14   Sep 13 2006 19:11:20   popescu
// STP 2192/FN 13
// 
//    Rev 1.13   Sep 07 2006 21:37:58   popescu
// STP 2192/02
// 
//    Rev 1.12   Aug 28 2006 15:40:54   ZHANGCEL
// PET2212 FN10 -- Added new logic for Netting Bulking Redemption and Distribution Payment
// 
//    Rev 1.11   Jul 27 2006 18:02:08   ZHANGCEL
// PET2192 FN11 - Commission Payments to MgmtCo related changes
// 
//    Rev 1.10   Nov 14 2004 14:50:58   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.9   Mar 04 2004 17:49:02   popescu
// PTS 10027865, fixed crash in Pay to entity search for inactive brokers. Disabled 'Instructions' button in pay to entity dialog if broker is inactive/not effective
// 
//    Rev 1.8   Sep 02 2003 17:03:46   popescu
// Fixes related to the duplicate check; when reading the current values of the broker, branch and salesrep, the values should be converted to upper case
// 
//    Rev 1.7   Aug 07 2003 14:57:48   popescu
// doValidateAll, checks whther there are payment instrucitons records set-up for a pay to entity record
// 
//    Rev 1.6   Jul 26 2003 19:38:00   popescu
// fixes related with the duplicate checks
// 
//    Rev 1.5   Jul 11 2003 20:07:46   popescu
// strip all and uppercase the br,bra, slsrep codes
// 
//    Rev 1.4   Jul 10 2003 22:21:16   popescu
// check in for payment instruct, used mfcan_ip_param for some interporcess param passing
// 
//    Rev 1.3   Jul 09 2003 21:57:14   popescu
// Payment Instructiuons work, business rules implementation SSB_PET_821_FN17
// 
//    Rev 1.2   Jul 02 2003 17:49:52   popescu
// work for payment instructions feature 
// 
//    Rev 1.1   Jul 01 2003 18:08:02   popescu
// Clean-up the code, new business rules, set the broker name to the dialog caption, etc...
// 
//    Rev 1.0   Jun 27 2003 18:16:50   popescu
// Initial revision.
 */