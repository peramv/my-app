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
// ^FILE   : PaymentInstructionsList.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : June 2003
//
// ^CLASS    : PaymentInstructionsList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "paymentinstructions.hpp"
#include "paymentinstructionslist.hpp"
#include "distributorrepository.hpp"
#include "paytoentity.hpp"
#include "paytoentitylist.hpp"

#include <ifastdataimpl\dse_dstc0256_req.hpp>
#include <ifastdataimpl\dse_dstc0256_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest PAYMENT_INSTRUCTIONS_LIST;
}

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME  = I_("PaymentInstructionsList");
}

namespace CND
{  // Conditions used
   extern const long ERR_DUPLICATE_RECORD;
	extern const long ERR_EFF_STOP_DATE_RANGE_OVERLAP;
}

namespace ifds
{
   //field ids used
   extern CLASS_IMPORT const BFTextFieldId PayToEntity;
}

namespace PAYMENT_FOR
{
    extern CLASS_EXPORT const I_CHAR * TRAILER_FEE = I_("TF");
    extern CLASS_EXPORT const I_CHAR * COMMISSION  = I_("CO");
	extern CLASS_EXPORT const I_CHAR * REDEMPTION  = I_("PW");
	extern CLASS_EXPORT const I_CHAR * DISTRIBUTION = I_("ID");
    extern CLASS_EXPORT const I_CHAR * NSCCCOMMISSION = I_("NC");
}


namespace CONSOL_TYPE
{
   extern CLASS_EXPORT const I_CHAR * INDIVIDUAL_PAYMENT = I_("0");
   extern CLASS_EXPORT const I_CHAR * BULKING            = I_("1");
	extern CLASS_EXPORT const I_CHAR * BULKING_NETTING    = I_("2");
	extern CLASS_EXPORT const I_CHAR * NOT_AVAILABLE      = I_("");
}

namespace CURRENCY_OPTION
{
   extern const I_CHAR * PAY_CURRENCY = I_("02");
   extern const I_CHAR * PAY_FUND_CURRENCY = I_("01");
	extern const I_CHAR * PAY_SETTLEMENT_CURRENCY = I_("03");
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
                             //  Field DD Id,      State Flags,      Group Flags 
   {ifds::BrokerCode,     BFCBO::NONE,      0}, 
   {ifds::BranchCode,     BFCBO::NONE,      0}, 
   {ifds::SalesRepCode,   BFCBO::NONE,      0}, 
   {ifds::PaymentFor,     BFCBO::NONE,      0}, 
   {ifds::DuplicateCheck, BFCBO::NONE,      0}, 
   //helper fields
   {ifds::PayToEntity,    BFCBO::NONE,      0},
	{ifds::CompanyCode,    BFCBO::NONE,      0},

};

static const int NUM_FIELDS = sizeof(classFieldInfo) / sizeof(BFCBO::CLASS_FIELD_INFO);

//******************************************************************************
PaymentInstructionsList::PaymentInstructionsList(BFAbstractCBO &parent)
: MFCanBFCbo(parent),
_searchTypeMgmt(NULL_STRING),
_pRequestData(NULL)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   setObjectAsList();
   registerMemberData(NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL);
}

//******************************************************************************
PaymentInstructionsList::~PaymentInstructionsList()
{
   TRACE_DESTRUCTOR(CLASSNAME);
   if (_pRequestData != NULL)
   {
      delete _pRequestData;
   }
}

//if broker code, branch code and sales rep code are NULL_STRING 
//all records are returned
//******************************************************************************
SEVERITY PaymentInstructionsList::init( const DString &dstrBrokerCode /*=NULL_STRING*/,
                                        const DString &dstrBranchCode /*=NULL_STRING*/,
                                        const DString &dstrSalesRepCode /*=NULL_STRING*/,
                                        const DString &dstrPaymentFor /*=NULL_STRING*/,
	                                     const DString &dstrSearchTypeMgmt /* =NULL_STRING*/,
                                        const DString &dstrDuplicateCheck /*=I_("N")*/,
	                                     const DString &dstrEffectiveDate  /*=NULL_STRING*/,
	                                     const DString &dstrPayInstructionsId /*=NULL_STRING*/,
                                        const DString &dstrStopDate /*=NULL_STRING*/,
                                        const BFDataGroupId &idDataGroup /*=BF::HOST*/, 
                                        const DString& dstrTrack /*= I_("N")*/, 
                                        const DString& dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   DString brokerCode (dstrBrokerCode),
      branchCode (dstrBranchCode),
      salesRepCode (dstrSalesRepCode),
      paymentFor (dstrPaymentFor);
   
   brokerCode.stripAll().upperCase();
   branchCode.stripAll().upperCase();
   salesRepCode.stripAll().upperCase();
   paymentFor.stripAll().upperCase();
	
	_searchTypeMgmt = dstrSearchTypeMgmt;
	_searchTypeMgmt.stripAll().upperCase();

   setFieldNoValidate (ifds::BrokerCode, brokerCode, idDataGroup, false);
   setFieldNoValidate (ifds::BranchCode, branchCode, idDataGroup, false);
   setFieldNoValidate (ifds::SalesRepCode, salesRepCode, idDataGroup, false);
	setFieldNoValidate (ifds::PaymentFor, paymentFor, idDataGroup, false);
   setFieldNoValidate (ifds::DuplicateCheck, dstrDuplicateCheck, idDataGroup, false);
   
   _pRequestData = new BFData(ifds::DSTC0256_REQ);

   DString mgmtCoIdOut;

   _pRequestData->setElementValue (ifds::BrokerCode, brokerCode);
   _pRequestData->setElementValue (ifds::BranchCode, branchCode);
   _pRequestData->setElementValue (ifds::SalesRepCode, salesRepCode);
	_pRequestData->setElementValue (ifds::SearchTypeMgmt, _searchTypeMgmt);
   _pRequestData->setElementValue (ifds::PaymentFor, paymentFor);
   _pRequestData->setElementValue (ifds::DuplicateCheck, dstrDuplicateCheck);
	_pRequestData->setElementValue (ifds::EffectiveDate, dstrEffectiveDate);
   _pRequestData->setElementValue (ifds::StopDate, dstrStopDate);
   _pRequestData->setElementValue (ifds::PayInstructRID, dstrPayInstructionsId);
   _pRequestData->setElementValue (ifds::CompanyId, getMgmtCoId(mgmtCoIdOut));
   _pRequestData->setElementValue (ifds::Track, dstrTrack);
   _pRequestData->setElementValue (ifds::Activity, dstrPageName);

   ReceiveData ( DSTC_REQUEST::PAYMENT_INSTRUCTIONS_LIST, 
                 *_pRequestData, 
                 ifds::DSTC0256_VW, 
                 DSTCRequestor(getSecurity(), false));
   return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
SEVERITY PaymentInstructionsList::doCreateNewObject( BFCBO *&pBase, 
                                                     DString &strKey, 
                                                     const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateNewObject"));

   DString brokerCode,
      branchCode,
      salesRepCode,
      paymentFor;

   getField (ifds::BrokerCode, brokerCode, idDataGroup);
   getField (ifds::BranchCode, branchCode, idDataGroup);
   getField (ifds::SalesRepCode, salesRepCode, idDataGroup);
   getField (ifds::PaymentFor, paymentFor, idDataGroup);

   PaymentInstructions *pPaymentInstructions = new PaymentInstructions((BFAbstractCBO&)(*this));

   if (pPaymentInstructions->init ( brokerCode, 
                                    branchCode, 
                                    salesRepCode, 
                                    paymentFor, 
                                    idDataGroup, 
                                    _searchTypeMgmt) > WARNING)
   {
      //delete pPaymentInstructions;
      //pPaymentInstructions = NULL;
   }
   pBase = pPaymentInstructions;
   return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
SEVERITY PaymentInstructionsList::doCreateObject(const BFData &data, BFCBO *&pObjOut)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateObject"));

   PaymentInstructions *pPaymentInstructions = 
      new PaymentInstructions((BFAbstractCBO&)(*this));
	
   if (pPaymentInstructions->init(data, _searchTypeMgmt) > WARNING)
   {
      //delete pPaymentInstructions;
      //pPaymentInstructions = NULL;
   }
   pObjOut = pPaymentInstructions;
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY PaymentInstructionsList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getMore"));

   if (doMoreRecordsExist())
   {
      ReceiveData ( DSTC_REQUEST::PAYMENT_INSTRUCTIONS_LIST, 
                    *_pRequestData, 
                    ifds::DSTC0256_VW, 
                    DSTCRequestor(getSecurity(), false));
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY PaymentInstructionsList::doApplyRelatedChanges ( const BFFieldId& idField, 
                                                          const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));

   if (idField == ifds::PayToEntity)
   {
      setFieldUpdated (ifds::PayToEntity, idDataGroup, false);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void PaymentInstructionsList::getStrKey(DString &strKey, const BFData *data)
{
   if (data) 
   {
      DString dstrBrokerCode = data->getElementValue (ifds::BrokerCode);
      DString dstrBranchCode = data->getElementValue (ifds::BranchCode);
      DString dstrSalesRepCode = data->getElementValue (ifds::SalesRepCode);
      DString dstrPaymentFor = data->getElementValue (ifds::PaymentFor);
	  DString dstrCompanyCode = data->getElementValue (ifds::CompanyCode);
	  DString dstrEffectiveDate = data->getElementValue (ifds::EffectiveDate);
	  DString dstrStopDate = data->getElementValue (ifds::StopDate);

      buildKey (strKey, dstrBrokerCode, dstrBranchCode, dstrSalesRepCode, dstrPaymentFor, 
		        dstrCompanyCode, dstrEffectiveDate, dstrStopDate);
   }
   else
   {
      BFCBO::getStrKey(strKey, NULL);
   }
}

//******************************************************************************
void PaymentInstructionsList::buildKey ( DString &dstrKey, 
                                         const DString &dstrBrokerCode, 
                                         const DString &dstrBranchCode,
                                         const DString &dstrSalesRepCode, 
                                         const DString &dstrPaymentFor,
	                                     const DString& dstrCompanyCode,
										 const DString& dstrEffectiveDate,
										 const DString& dstrStopDate)
{
   DString brokerCode (dstrBrokerCode);
   DString branchCode (dstrBranchCode);
   DString salesRepCode (dstrSalesRepCode);
   DString paymentFor (dstrPaymentFor);
   DString companyCode (dstrCompanyCode);
   DString effectiveDate (dstrEffectiveDate);
   DString stopDate (dstrStopDate);

   dstrKey = I_("Broker=") + brokerCode.stripAll().upperCase() + 
      I_(";Branch=") + branchCode.stripAll().upperCase() + 
      I_(";SlsRep=") + salesRepCode.stripAll().upperCase() + 
	  I_(";Company=") + companyCode.stripAll().upperCase() + 
      I_(";PayFor=") + paymentFor.stripAll().upperCase() +
	  I_(";EffectiveDate=") + effectiveDate.stripAll().upperCase() +
	  I_(";StopDate=") + stopDate.stripAll().upperCase();
}

//********************************************************************
SEVERITY PaymentInstructionsList::checkDuplicate ( const PaymentInstructions *pPaymentInstructionsToCheck, 
                                                   const BFDataGroupId &idDataGroup,
                                                   bool bDuplicateError /*= true*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("checkDuplicate"));
   DString brokerCode, 
      branchCode,
      salesRepCode, 
      paymentFor,
		companyCode,
		effectiveDate,
		stopDate,
		payInstructionsId;

   //get the values for broker/branch/sales rep and payment for, to check against
   pPaymentInstructionsToCheck->getField (ifds::BrokerCode, brokerCode, idDataGroup);
   pPaymentInstructionsToCheck->getField (ifds::BranchCode, branchCode, idDataGroup);
   pPaymentInstructionsToCheck->getField (ifds::SalesRepCode, salesRepCode, idDataGroup);
   pPaymentInstructionsToCheck->getField (ifds::PaymentFor, paymentFor, idDataGroup);
	pPaymentInstructionsToCheck->getField (ifds::CompanyCode, companyCode, idDataGroup);
	pPaymentInstructionsToCheck->getField (ifds::EffectiveDate, effectiveDate, idDataGroup);
	pPaymentInstructionsToCheck->getField (ifds::StopDate, stopDate, idDataGroup);
	pPaymentInstructionsToCheck->getField (ifds::PayInstructRID, payInstructionsId, idDataGroup);

   brokerCode.stripAll().upperCase();
   branchCode.stripAll().upperCase();
   salesRepCode.stripAll().upperCase();
   paymentFor.stripAll().upperCase();
	companyCode.stripAll().upperCase();
   
   bool hasDuplicate = false;

   //check first whether in the list (in memory) we have a duplicate
   //this catches the newly added items, as well 
   BFObjIter iter(*this, idDataGroup, 0,BFObjIter::ITERTYPE::NON_DELETED);

   while (!iter.end())
   {
      PaymentInstructions *pPaymentInstructions = 
            dynamic_cast<PaymentInstructions*>(iter.getObject());

      if (pPaymentInstructions != pPaymentInstructionsToCheck)
      {
         DString brokerCode_, 
                 branchCode_, 
                 salesRepCode_, 
                 paymentFor_, 
                 companyCode_,
					  effectiveDate_, 
                 stopDate_;

         pPaymentInstructions->getField (ifds::BrokerCode, brokerCode_, idDataGroup);
         pPaymentInstructions->getField (ifds::BranchCode, branchCode_, idDataGroup);
         pPaymentInstructions->getField (ifds::SalesRepCode, salesRepCode_, idDataGroup);
         pPaymentInstructions->getField (ifds::PaymentFor, paymentFor_, idDataGroup);
			pPaymentInstructions->getField (ifds::CompanyCode, companyCode_, idDataGroup);
			pPaymentInstructions->getField (ifds::EffectiveDate, effectiveDate_, idDataGroup);
			pPaymentInstructions->getField (ifds::StopDate, stopDate_, idDataGroup);
         brokerCode_.stripAll().upperCase();
         branchCode_.stripAll().upperCase();
         salesRepCode_.stripAll().upperCase();
         paymentFor_.stripAll().upperCase();
			companyCode_.stripAll().upperCase();
         if ( brokerCode == brokerCode_   && 
              branchCode == branchCode_ &&
              salesRepCode == salesRepCode_ && 
              paymentFor == paymentFor_ &&
				  companyCode == companyCode_ &&
              !(DSTCommonFunctions::CompareDates (stopDate, effectiveDate_) == DSTCommonFunctions::FIRST_EARLIER ||
                DSTCommonFunctions::CompareDates (stopDate_, effectiveDate) == DSTCommonFunctions::FIRST_EARLIER))
         {
			hasDuplicate = true;
            break;
         }
      }
      ++iter;
   }
   //finally, if no duplicates in memory, check the back-end
   if (!hasDuplicate)
   {
      PaymentInstructionsList paymentInstructionsList ((BFAbstractCBO&)(*this));

      //check duplicate, 
      if (paymentInstructionsList.init ( brokerCode, 
                                         branchCode, 
                                         salesRepCode, 
                                         paymentFor, 
                                         _searchTypeMgmt, I_("Y"), 
			                                effectiveDate, 
                                         payInstructionsId, 
                                         stopDate,
                                         idDataGroup) <= WARNING)
      {
         //we should get an exact match, so the DuplicateExist flag
         //of the single section is set to Y or N
         DString duplicateExist;

         paymentInstructionsList.getField (ifds::DuplicateExist, duplicateExist, idDataGroup, false);
         hasDuplicate = duplicateExist == I_("Y");
//but if we found a duplicate, this might have been already deleted 
//in the memory
         if (hasDuplicate)
         { //check the memory again for possible deleted duplicates
            BFObjIter iterInMemory (*this, idDataGroup);

            while (!iterInMemory.end())
            {
               if (iterInMemory.getKey().getActivity() == OBJ_ACTIVITY_DELETED)
               {
                  PaymentInstructions *pDeletedPaymentInstructions = 
                     dynamic_cast<PaymentInstructions*>(iterInMemory.getObject());
                  DString deletedBrokerCode, 
                     deletedBranchCode,
                     deletedSalesRepCode,
                     deletedPaymentFor,
							deletedCompanyCode,
							deletedEffectiveDate, 
							deletedStopDate;

                  pDeletedPaymentInstructions->getField (ifds::BrokerCode, deletedBrokerCode, idDataGroup);
                  pDeletedPaymentInstructions->getField (ifds::BranchCode, deletedBranchCode, idDataGroup);
                  pDeletedPaymentInstructions->getField (ifds::SalesRepCode, deletedSalesRepCode, idDataGroup);
                  pDeletedPaymentInstructions->getField (ifds::PaymentFor, deletedPaymentFor, idDataGroup);
						pDeletedPaymentInstructions->getField (ifds::CompanyCode, deletedCompanyCode, idDataGroup);
						pDeletedPaymentInstructions->getField (ifds::EffectiveDate, deletedEffectiveDate, idDataGroup);
						pDeletedPaymentInstructions->getField (ifds::StopDate, deletedStopDate, idDataGroup);

                  deletedBrokerCode.stripAll().upperCase();
                  deletedBranchCode.stripAll().upperCase();
                  deletedSalesRepCode.stripAll().upperCase();
                  deletedPaymentFor.stripAll().upperCase();
						deletedCompanyCode.stripAll().upperCase();

                  if (  brokerCode    == deletedBrokerCode   && 
                        branchCode    == deletedBranchCode   &&
                        salesRepCode  == deletedSalesRepCode &&
                        paymentFor    == deletedPaymentFor   &&
								companyCode   == deletedCompanyCode  &&
                        stopDate      == deletedStopDate &&
                        effectiveDate == deletedEffectiveDate)
                  {
                     hasDuplicate = false;
                     break;
                  }
               }
               ++iterInMemory;
            }
         }
      }
   }
   if (hasDuplicate)
   {
      ADDCONDITIONFROMFILE (CND::ERR_DUPLICATE_RECORD);
   }
   return GETCURRENTHIGHESTSEVERITY();
}
//********************************************************************
SEVERITY PaymentInstructionsList::doValidateAll ( const BFDataGroupId& idDataGroup, 
                                                  long lValidateGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateAll"));
   return GETCURRENTHIGHESTSEVERITY ();
}

//********************************************************************
bool PaymentInstructionsList::isNotDeleted( const BFDataGroupId &idDataGroup, 
														  const DString &pairPayInstructRID )
{
 	bool bNotDelete = true;
	//check the memory for possible deleted pair
	DString payInstructionsId;
	BFObjIter iterInMemory (*this, idDataGroup);

	while (!iterInMemory.end())
	{
		if (iterInMemory.getKey().getActivity() == OBJ_ACTIVITY_DELETED)
		{
			PaymentInstructions *pDeletedPaymentInstructions = 
				dynamic_cast<PaymentInstructions*>(iterInMemory.getObject());
			DString deletedPayInstructRID;

			pDeletedPaymentInstructions->getField (ifds::PayInstructRID, deletedPayInstructRID, idDataGroup);
     
			if ( pairPayInstructRID == deletedPayInstructRID )
         {
            bNotDelete = false;
            break;
         }
      }
      ++iterInMemory;
   }
	return bNotDelete;
}

//********************************************************************
bool PaymentInstructionsList::isNotAdded(   const BFDataGroupId &idDataGroup,
														  const DString &dstrBrokerCode,
														  const DString &dstrBranchCode,
														  const DString &dstrSalesRepCode,
														  const DString &lookingForPaymentFor,
														  const DString &dstrEffectiveDate,
														  const DString &dstrStopDate)
{
   
 
	bool bNotAdded = true;
	//check the memory for possible added pair
	BFObjIter iter(*this, idDataGroup, 0,BFObjIter::ITERTYPE::NON_DELETED);

	while (!iter.end())
	{
		PaymentInstructions *pPaymentInstructions = 	dynamic_cast<PaymentInstructions*>(iter.getObject());
		if ( pPaymentInstructions ) 
      {
			DString addedBrokerCode, addedBranchCode,	addedSalesRepCode, addedPaymentFor;
			DString addedConsolType, addedEffectiveDate, addedStopDate;
         pPaymentInstructions->getField (ifds::BrokerCode, addedBrokerCode, idDataGroup);
         pPaymentInstructions->getField (ifds::BranchCode, addedBranchCode, idDataGroup);
         pPaymentInstructions->getField (ifds::SalesRepCode, addedSalesRepCode, idDataGroup);
         pPaymentInstructions->getField (ifds::PaymentFor, addedPaymentFor, idDataGroup);
			pPaymentInstructions->getField (ifds::ConsolType, addedConsolType, idDataGroup);
			pPaymentInstructions->getField (ifds::EffectiveDate, addedEffectiveDate, idDataGroup);
			pPaymentInstructions->getField (ifds::StopDate, addedStopDate, idDataGroup);

         addedBrokerCode.stripAll().upperCase();
         addedBranchCode.stripAll().upperCase();
         addedSalesRepCode.stripAll().upperCase();
         addedPaymentFor.stripAll().upperCase();
			addedConsolType.stripAll().upperCase();

         if (  dstrBrokerCode			== addedBrokerCode   && 
               dstrBranchCode			== addedBranchCode   &&
               dstrSalesRepCode		== addedSalesRepCode &&
               lookingForPaymentFor == addedPaymentFor   &&
					!(DSTCommonFunctions::CompareDates ( dstrEffectiveDate, addedEffectiveDate ) == DSTCommonFunctions::FIRST_EARLIER ||
					  DSTCommonFunctions::CompareDates ( addedStopDate, dstrStopDate ) == DSTCommonFunctions::FIRST_EARLIER )
					
               )
         {
            bNotAdded = false;
            break;
         }
      }
      ++iter;
   }
	return bNotAdded;
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/PaymentInstructionsList.cpp-arc  $
// 
//    Rev 1.18   May 01 2007 10:25:14   jankovii
// IN 862766 - Payment instr.
// 
//    Rev 1.17   Nov 03 2006 16:18:32   ZHANGCEL
// Incident 731541 -- Add logice to check Pair
// 
//    Rev 1.16   Oct 20 2006 18:14:52   popescu
// Incident# 731541 reviewed the way related changes for  fields is working in paym instruct
// 
//    Rev 1.15   Oct 16 2006 10:16:20   popescu
// Incident# 731541 - set PayinstructRID as req param to vew 256
// 
//    Rev 1.14   Sep 12 2006 10:52:58   popescu
// STP - PET 2192/11
// 
//    Rev 1.13   Sep 10 2006 17:59:10   popescu
// STP 2192/12
// 
//    Rev 1.12   Aug 28 2006 15:39:48   ZHANGCEL
// PET2212 FN10 -- Added new logic for Netting Bulking Redemption and Distribution Payment
// 
//    Rev 1.11   Jul 27 2006 18:00:46   ZHANGCEL
// PET2192 FN11 - Commission Payments to MgmtCo related changes
// 
//    Rev 1.10   Nov 14 2004 14:50:52   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.9   Sep 02 2003 17:41:52   popescu
// do not delete the objects if there is failure in the commonInit mehtod. The getNewListItem method in bfcbo expects a valid object from doCreatenewObject
// 
//    Rev 1.8   Sep 02 2003 17:03:32   popescu
// Fixes related to the duplicate check; when reading the current values of the broker, branch and salesrep, the values should be converted to upper case
// 
//    Rev 1.7   Aug 20 2003 12:59:54   popescu
// switch the codes for the currency option set
// 
//    Rev 1.6   Aug 07 2003 18:39:12   popescu
// make the account usage codes and payment for, visible to the GUI layer
// 
//    Rev 1.5   Jul 26 2003 19:37:50   popescu
// fixes related with the duplicate checks
// 
//    Rev 1.4   Jul 11 2003 20:07:36   popescu
// strip all and uppercase the br,bra, slsrep codes
// 
//    Rev 1.3   Jul 11 2003 13:46:58   popescu
// fixes related to the confirmation screen showing up even if there are no changes for the payment instructions screen, added validation for the Currency if BAAF is selected as the file processor
// 
//    Rev 1.2   Jul 10 2003 22:21:04   popescu
// check in for payment instruct, used mfcan_ip_param for some interporcess param passing
// 
//    Rev 1.1   Jul 09 2003 21:56:58   popescu
// Payment Instructiuons work, business rules implementation SSB_PET_821_FN17
// 
//    Rev 1.0   Jul 01 2003 18:17:16   popescu
// Initial revision.
// 
 */