//*****************************************************************************
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
//*****************************************************************************
//
//    ^FILE   : PayToEntity.cpp
//    ^AUTHOR : Serban Popescu
//    ^DATE   : June 2003
//    Copyright 2000 by DST Canada, Inc.
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : PayToEntity
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include "paytoentity.hpp"

#include "broker.hpp"
#include "brokerlist.hpp"
#include "distributorrepository.hpp"
#include "paytoentitylist.hpp"
#include "paymentinstructionslist.hpp"

namespace 
{
   const I_CHAR * CLASSNAME = I_("PayToEntity");
   const I_CHAR * YES = I_("Y");
}

namespace ifds
{
   //field ids used
   extern CLASS_IMPORT const BFTextFieldId BrokerName;
   extern CLASS_IMPORT const BFIntegerFieldId CommissionType;
   extern CLASS_IMPORT const BFTextFieldId PayToEntityNoAll;
   extern CLASS_IMPORT const BFTextFieldId BrokerPaymentFor;
   extern CLASS_IMPORT const BFTextFieldId CompanyCodePaymentFor;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFTextFieldId BranchCode;
   extern CLASS_IMPORT const BFTextFieldId SalesRepCode;
   extern CLASS_IMPORT const BFTextFieldId NSCCCompliant;
   extern CLASS_IMPORT const BFTextFieldId PaymentInstructionsPaymentFor;
   extern CLASS_IMPORT const BFTextFieldId NSCCPaymentFor;
   extern CLASS_IMPORT const BFTextFieldId FileTypeJ;
   extern CLASS_IMPORT const BFTextFieldId FileTypeD; 
   extern CLASS_IMPORT const BFTextFieldId ClientName; 
   extern CLASS_IMPORT const BFTextFieldId PayToEntityMgmt;
   extern CLASS_IMPORT const BFTextFieldId SearchTypeMgmt;
   extern CLASS_IMPORT const BFTextFieldId EffectiveStopDate;
}


const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
   //  Field DD Id,               State Flags,               Group Flags 
   {ifds::BrokerCode,             BFCBO::REQUIRED,                 0},
   {ifds::BrokerName,             BFCBO::NONE,                     0},
   {ifds::PaymentFor,             BFCBO::REQUIRED,                 0},
   {ifds::PayToEntity,            BFCBO::REQUIRED,                 0},
   {ifds::CompanyCode,            BFCBO::NONE,                     0},
   //cross edits
   {ifds::BrokerPaymentFor,       BFCBO::NONE,                     0},
   {ifds::CompanyCodePaymentFor,  BFCBO::NONE,                     0},
   {ifds::EffectiveDate,          BFCBO::REQUIRED,                 0},
   {ifds::StopDate,               BFCBO::NONE,                     0},
   {ifds::EffectiveStopDate,      BFCBO::IMMEDIATE_VALIDATION,     0},

};

namespace CND
{  // Conditions used
   extern const long ERR_NO_PAYMENT_INSTRUCTIONS_RECORD;
   extern CLASS_IMPORT const long ERR_BROKER_NOT_FOUND;
   extern const long ERR_STOP_DATE_LESS_THAN_DEFF;
}

namespace PAY_TO
{
   extern I_CHAR * const ALL;
   extern I_CHAR * const BROKER;
   extern I_CHAR * const BRANCH;
   extern I_CHAR * const SALESREP;
   extern I_CHAR * const CLIENT;
}

namespace PAYMENT_FOR
{
   extern const I_CHAR * COMMISSION;
   extern const I_CHAR * REDEMPTION;
   extern const I_CHAR * DISTRIBUTION;
   extern const I_CHAR * NSCCCOMMISSION;
}


static const int NUM_FIELDS = sizeof(classFieldInfo) / sizeof(BFCBO::CLASS_FIELD_INFO);
//******************************************************************************
PayToEntity::PayToEntity(BFAbstractCBO &parent) 
: MFCanBFCbo(parent),
_searchType (NULL_STRING),
_isNoSplitCommissionEnvironment (false)
{
   TRACE_CONSTRUCTOR (CLASSNAME , NULL_STRING);
   registerMemberData (NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL);

   DString commissionType;

   getWorkSession().getOption (ifds::CommissionType, commissionType, BF::HOST, false);
   _isNoSplitCommissionEnvironment = commissionType == I_("0");
   addCrossEdit(ifds::BrokerPaymentFor, ifds::BrokerCode);
   addCrossEdit(ifds::BrokerPaymentFor, ifds::PaymentFor);

   addCrossEdit(ifds::CompanyCodePaymentFor, ifds::CompanyCode);
   addCrossEdit(ifds::CompanyCodePaymentFor, ifds::PaymentFor);

   addCrossEdit(ifds::EffectiveStopDate, ifds::EffectiveDate);
   addCrossEdit(ifds::EffectiveStopDate, ifds::StopDate);
}

//******************************************************************************
PayToEntity::~PayToEntity()
{
   TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************
SEVERITY PayToEntity::init ( const BFData &viewData,  
                             const DString &searchTypeMgmt)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));
   attachDataObject(const_cast<BFData&>(viewData), false, true);
   
   DString brokerCode (viewData.getElementValue (ifds::BrokerCode));
   _searchType = searchTypeMgmt;
   _searchType.stripAll().upperCase();

   commonInit (brokerCode, BF::HOST);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY PayToEntity::init ( const DString &brokerCode, 
                             const BFDataGroupId &idDataGroup, 
                             const DString &dstrSearchTypeMgmt)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   _searchType = dstrSearchTypeMgmt;
   _searchType.stripAll().upperCase();

   commonInit (brokerCode, idDataGroup);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY PayToEntity::commonInit ( const DString &dstrBrokerCode, 
                                   const BFDataGroupId &idDataGroup)

{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("commonInit"));

   DString dstrPaymentFor;
   bool bPaymentForReadOnly = false;
   getField( ifds::PaymentFor, dstrPaymentFor, idDataGroup );

   if (isMgtCoPayToEntity ())
   {
      setFieldReadOnly (ifds::CompanyCode, idDataGroup, true);
      setFieldReadOnly (ifds::PayToEntity, idDataGroup, true);
   }
   else
   {
      DString brokerCode (dstrBrokerCode);
      
      brokerCode.stripAll().upperCase();
      setFieldNoValidate (ifds::BrokerCode, brokerCode, idDataGroup, false, false, true, true);
      if (!brokerCode.empty())
      {
         //here we do not care if broker does not exist
         if (setBrokerName (brokerCode, idDataGroup) > WARNING) 
         {
            int count = CONDITIONCOUNT();
            Condition   *c = NULL;
            for (int i = 0; i < count; i++)
            {
               c = GETCONDITION( i );
               int condCode = c->getCode();
               if(condCode == CND::ERR_BROKER_NOT_FOUND)
               {
                  CLEARCONDITION( i );
                  break;
               }
            }
         }
      
         //the key values should be made read only, if not a new object
         setFieldReadOnly ( ifds::BrokerCode, 
                            idDataGroup, 
                            idDataGroup == BF::HOST || brokerCode != NULL_STRING);
         setFieldReadOnly (ifds::PaymentFor, idDataGroup, idDataGroup == BF::HOST);
         if (_isNoSplitCommissionEnvironment)
         {
            setFieldAllSubstituteValues (ifds::PayToEntity, idDataGroup, ifds::PayToEntityNoAll);
         }   
         else if (!dstrPaymentFor.empty () && 
			       dstrPaymentFor != PAYMENT_FOR::COMMISSION && 
			       PAYMENT_FOR::NSCCCOMMISSION != dstrPaymentFor )
         {
            setFieldAllSubstituteValues (ifds::PayToEntity, idDataGroup, ifds::PayToEntityNoAll);
         }   
      }

      if ( dstrPaymentFor == PAYMENT_FOR::REDEMPTION || 
             dstrPaymentFor == PAYMENT_FOR::DISTRIBUTION) 
      {
         bPaymentForReadOnly = true;
      }         
      
      setFieldReadOnly (ifds::PayToEntity, idDataGroup, bPaymentForReadOnly);
   }
   setPaymentForSubSet (idDataGroup);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void PayToEntity::doInitWithDefaultValues (const BFDataGroupId& idDataGroup)
{
   setFieldNoValidate (ifds::PaymentFor, PAYMENT_FOR::COMMISSION, idDataGroup, false, true, true, false);
   if (isMgtCoPayToEntity ())
   {
      DString companyCode;

      getWorkSession().getOption (ifds::CompanyCode, companyCode, BF::HOST, false);
      setFieldNoValidate (ifds::CompanyCode, companyCode, idDataGroup, false, true, true, true);
      setFieldNoValidate (ifds::PayToEntity, PAY_TO::CLIENT, idDataGroup, false, false, true, false);
      setNonDummyFlag();
   }

   DString date,
      stopDate;

   getWorkSession().getOption (ifds::CurrBusDate, date, idDataGroup, false);
   getWorkSession().getDateInHostFormat (stopDate, DSTCWorkSession::DATE_TYPE::DAY12319999, idDataGroup);
   setFieldNoValidate (ifds::EffectiveDate, date, idDataGroup, false, true, true);
   setFieldNoValidate (ifds::StopDate, stopDate, idDataGroup, false, true, true);
}

//******************************************************************************
void PayToEntity::doReset (const BFDataGroupId &idDataGroup)
{
   if (isNew())
   {
      init(NULL_STRING, idDataGroup, _searchType);
   }
}

//******************************************************************************
SEVERITY PayToEntity::doApplyRelatedChanges( const BFFieldId &idField, 
                                             const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));
   
   if (idField == ifds::BrokerCode)
   {
      DString dstrPayToEntity;
      
      getField (ifds::PayToEntity, dstrPayToEntity, idDataGroup);
      dstrPayToEntity.strip().upperCase();      
      if (dstrPayToEntity != PAY_TO::CLIENT)
      {
         setPaymentForSubSet (idDataGroup);
      }
   }
   else if (idField == ifds::PaymentFor)
   {
      DString dstrPaymentFor;

      getField(ifds::PaymentFor,  dstrPaymentFor, idDataGroup );
      dstrPaymentFor.strip().upperCase();
      if (!isMgtCoPayToEntity ())
      {
         if ( dstrPaymentFor == PAYMENT_FOR::REDEMPTION || 
              dstrPaymentFor == PAYMENT_FOR::DISTRIBUTION) 
         {
            setFieldNoValidate (ifds::PayToEntity, PAY_TO::BROKER, idDataGroup, false, true, true, false);
            setFieldReadOnly (ifds::PayToEntity, idDataGroup, true);
         }
         else
         {
         if (_isNoSplitCommissionEnvironment)
         {
            setFieldAllSubstituteValues (ifds::PayToEntity, idDataGroup, ifds::PayToEntityNoAll);
         }   
         else if (!dstrPaymentFor.empty () &&  
			       dstrPaymentFor != PAYMENT_FOR::COMMISSION && 
				   PAYMENT_FOR::NSCCCOMMISSION !=  dstrPaymentFor)
         {
            setFieldAllSubstituteValues (ifds::PayToEntity, idDataGroup, ifds::PayToEntityNoAll);
         }   
         else if (dstrPaymentFor == PAYMENT_FOR::COMMISSION)
         {
            
/*            DString payToEntitySubList = addItemToSubtList (ifds::PayToEntity, I_("ALL"), idDataGroup);
         
            setFieldAllSubstituteValues (ifds::PayToEntity, idDataGroup, payToEntitySubList);
            */
         }

          if (!isMgtCoPayToEntity ())
         {
            DString payToEntitySubList = removeItemFromSubtList (ifds::PayToEntity, PAY_TO::CLIENT, idDataGroup);
         
            setFieldAllSubstituteValues (ifds::PayToEntity, idDataGroup, payToEntitySubList);
         }
         
         setFieldReadOnly (ifds::PayToEntity, idDataGroup, false);
         }
      }
   }
   else if (idField == ifds::PayToEntity)
   {
      setFieldValid (ifds::EffectiveStopDate, idDataGroup, false);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY PayToEntity::doValidateField ( const BFFieldId &idField, 
                                        const DString &strValue, 
                                        const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField"));

   if (idField == ifds::BrokerPaymentFor)
   {
      DString brokerCode;

      getField (ifds::BrokerCode, brokerCode, idDataGroup);
      if (!brokerCode.empty())
      {
//check duplicate
         PayToEntityList *pPayToEntityList = dynamic_cast <PayToEntityList*> (getParent());

         pPayToEntityList->checkDuplicate (this, idDataGroup);
      }
   }
   else if (idField == ifds::PaymentFor)
   {
      duplicateCheck (idDataGroup);
   }
   else if (idField == ifds::CompanyCodePaymentFor)
   {
      DString companyCode;

      getField (ifds::CompanyCode, companyCode, idDataGroup);
      if (!companyCode.empty())
      {
//check duplicate
         PayToEntityList *pPayToEntityList = dynamic_cast <PayToEntityList*> (getParent());

         pPayToEntityList->checkDuplicate (this, idDataGroup);
      }
   }
   else if (idField == ifds::BrokerCode)
   {
      if (!strValue.empty())
      {
//validates the broker code, as well
         setBrokerName (strValue, idDataGroup, true);
      }
      else
      {
         //reset the broker name
         setFieldNoValidate (ifds::BrokerName, NULL_STRING, idDataGroup, false, true, true, false);
      }
   }
   else if (idField == ifds::PayToEntity)
   {
      if (strValue != PAY_TO::CLIENT)
      {
         validatePayToEntity (idDataGroup);
      }

      DString brokerCode;

      getField (ifds::BrokerCode, brokerCode, idDataGroup);

      if (!brokerCode.empty())
      {
         duplicateCheck (idDataGroup);
      }
   }
   else if (idField == ifds::EffectiveStopDate)  //cross edit
   {
      DString effectiveDate, 
         stopDate;

      getField (ifds::StopDate, stopDate, idDataGroup, false);
      getField (ifds::EffectiveDate, effectiveDate, idDataGroup, false);

      if (DSTCommonFunctions::CompareDates (stopDate, effectiveDate) == DSTCommonFunctions::FIRST_EARLIER)
      {
         ADDCONDITIONFROMFILE (CND::ERR_STOP_DATE_LESS_THAN_DEFF);
      }
      duplicateCheck (idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY PayToEntity::duplicateCheck(const BFDataGroupId &idDataGroup) 
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("duplicateCheck"));

   PayToEntityList *pPayToEntityList = dynamic_cast <PayToEntityList*>(getParent());
         
   if (pPayToEntityList)
    {
      pPayToEntityList->checkDuplicate (this, idDataGroup, false); //raise the date range error
    }

   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY PayToEntity::setBrokerName( const DString &brokerCode,
                                     const BFDataGroupId &idDataGroup,
                                     bool checkEffective /*=false*/) 
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("setBrokerName"));
   
   //reset the broker name
   setFieldNoValidate ( ifds::BrokerName, NULL_STRING, idDataGroup, 
                        false, true, true, false);
   Broker *pBroker (NULL);

   if ( getBroker ( pBroker, idDataGroup) <= WARNING &&
         pBroker)
   {
      DString brokerName;

      pBroker->getField (ifds::BrokerName, brokerName, idDataGroup);
      setFieldNoValidate (ifds::BrokerName, brokerName, idDataGroup, false, true, true, false);
      if (checkEffective)
      {
         DString dstrCurrBusDate;

//chech the effectiveness of the broker
         getWorkSession().getOption(ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false); 
         pBroker->checkEffective (dstrCurrBusDate, idDataGroup);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY PayToEntity::validatePayToEntity (const BFDataGroupId &idDataGroup)
{
   //there must be at least on payment instructions record
   //set for the broker, payment for, at the given payToEntity level

   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validatePayToEntity"));

   DString payToEntity;
   getField(ifds::PayToEntity, payToEntity, idDataGroup, false);
   /*~~disable the validation until somebody decides to put it in~~*/
   if (false && payToEntity != NULL_STRING) 
   {
      DString paymentFor, brokerCode;
      PaymentInstructionsList *paymentInstructionsList = NULL;
      DistributorRepository *pDistributorRepository = NULL;

      getField(ifds::PaymentFor, paymentFor, idDataGroup, false);
      getField(ifds::BrokerCode, brokerCode, idDataGroup, false);

      //do not get the payment instructions list, 
      //when the broker is empty the view call is retrievieng all data
      if (brokerCode != NULL_STRING) 
      {
         if (getWorkSession().getDistributorRepository
            (pDistributorRepository) <= WARNING && pDistributorRepository)
         {
            if (pDistributorRepository->getPaymentInstructionsList(
                  brokerCode, NULL_STRING, NULL_STRING, paymentFor, I_("BROKER"), 
                  paymentInstructionsList, idDataGroup) <= WARNING &&
                  paymentInstructionsList)
            {
               bool bFoundPaymentInstructions = false;
               BFObjIter bfIter(*paymentInstructionsList, idDataGroup, 0, 
                     BFObjIter::ITERTYPE::NON_DELETED);

               while (!bfIter.end())
               {
                  DString  _brokerCode, _branchCode, _salesRepCode,
                     _paymentFor;

                  bfIter.getObject()->getField(ifds::BrokerCode, _brokerCode, 
                     idDataGroup, false);
                  bfIter.getObject()->getField(ifds::BranchCode, _branchCode, 
                     idDataGroup, false);
                  bfIter.getObject()->getField(ifds::SalesRepCode, _salesRepCode, 
                     idDataGroup, false);
                  bfIter.getObject()->getField(ifds::PaymentFor, _paymentFor, 
                     idDataGroup, false);
                  //the following 'if' seems redundant, but it is good 
                  //if bad data comes from the back-end
                  if (brokerCode == _brokerCode && paymentFor == _paymentFor) 
                  {
                     if (payToEntity == PAY_TO::BROKER)
                     {
                        bFoundPaymentInstructions = _branchCode == NULL_STRING && 
                           _salesRepCode == NULL_STRING;
                     }
                     else if (payToEntity == PAY_TO::BRANCH)
                     {
                        bFoundPaymentInstructions = _branchCode != NULL_STRING && 
                           _salesRepCode == NULL_STRING;
                     }
                     else if (payToEntity == PAY_TO::SALESREP)
                     {
                        bFoundPaymentInstructions = _branchCode != NULL_STRING && 
                           _salesRepCode != NULL_STRING;
                     }
                  }
                  if (bFoundPaymentInstructions)
                  {
                     break;
                  }
                  ++bfIter;
               }
               if (!bFoundPaymentInstructions)
               {
                  DString strIDI, 
                     brokerName, 
                     paymentForDescr,
                     payToEntityDescr;
               
                  getField(ifds::BrokerName, brokerName, idDataGroup, false);
                  getField(ifds::PaymentFor, paymentForDescr, idDataGroup, true);
                  getField(ifds::PayToEntity, payToEntityDescr, idDataGroup, true);
                  addIDITagValue(strIDI, I_("brokername"), brokerName);
                  addIDITagValue(strIDI, I_("paymentfordescr"), paymentForDescr);
                  addIDITagValue(strIDI, I_("paytoentitydescr"), payToEntityDescr);
                  ADDCONDITIONFROMFILEIDI(CND::ERR_NO_PAYMENT_INSTRUCTIONS_RECORD, strIDI);
               }
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY PayToEntity::setPaymentForSubSet (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("setPayTypeSubstSet"));

   DString nsccCompliant, 
      brokerCode;
   bool NSCCapply = false;
   
   if (getWorkSession().getOption (ifds::NSCCCompliant, nsccCompliant, idDataGroup, false) <= WARNING)
   {
      if (nsccCompliant == YES)
      {
         Broker *pBroker (NULL);

         if ( getBroker ( pBroker, idDataGroup) <= WARNING &&
              pBroker)
         {
             DString dstrBrokerNSCCCompliant, 
                dstrFileTypeJ;

             pBroker->getField (ifds::NSCCCompliant, dstrBrokerNSCCCompliant, idDataGroup, false);
             pBroker->getField (ifds::FileTypeJ, dstrFileTypeJ, idDataGroup);
             if (dstrBrokerNSCCCompliant == YES && dstrFileTypeJ == YES)
             {
                NSCCapply = true;
             }
         }
      }
   }
   if (NSCCapply)
   {
      setFieldSubstituteValues (ifds::PaymentFor, idDataGroup, ifds::NSCCPaymentFor);
   }
   else
   {
      setFieldSubstituteValues (ifds::PaymentFor, idDataGroup, ifds::PaymentInstructionsPaymentFor);
      if (!isMgtCoPayToEntity ())
      {
         DString payToEntitySubList = removeItemFromSubtList (ifds::PayToEntity, PAY_TO::CLIENT, idDataGroup);
         
         setFieldAllSubstituteValues (ifds::PayToEntity, idDataGroup, payToEntitySubList);
      }
   }   
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY PayToEntity::getBroker ( Broker *&pBroker,
                                  const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getBroker"));
   pBroker = NULL;

   DString brokerCode;

   getField (ifds::BrokerCode, brokerCode, idDataGroup, false);
   if (!brokerCode.empty())
   {
      DString strKey (I_("Broker=") + brokerCode);
//look for the list
      BrokerList *pBrokerList = 
            dynamic_cast <BrokerList*> (getObject ( strKey, 
                                                    idDataGroup));
      if (!pBrokerList) //make view call
      {
         pBrokerList = new BrokerList ((BFAbstractCBO&)(*this));
         if (pBrokerList->init2 ( brokerCode, 
                                  NULL_STRING, 
                                  I_("L"),  //exact match
                                  NULL_STRING, 
                                  NULL_STRING) <= WARNING)
         {
            setObject ( pBrokerList,
                        strKey,
                        OBJ_ACTIVITY_NONE,
                        idDataGroup);
         }            
         else 
         {
            delete pBrokerList;
            pBrokerList = NULL;
         }
      }
//get the broker
      if (pBrokerList)
      {
         BFObjIter bfIter (*pBrokerList, idDataGroup);

         if (!bfIter.end())
         {
            pBroker = dynamic_cast <Broker*> (bfIter.getObject());
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool PayToEntity::isMgtCoPayToEntity ()
{
   return _searchType == I_("MGMTCO");
}

//******************************************************************************
SEVERITY PayToEntity::setField( const BFFieldId& idField, 
                                const DString& dstrValue,
                                const BFDataGroupId& idDataGroup, 
                                bool bFormatted, 
                                bool bSideEffect,
                                bool bCheckCurrentValue)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("setField"));

   DString str12319999;
   getWorkSession().getDateInHostFormat (str12319999, DSTCWorkSession::DATE_TYPE::DAY12319999, idDataGroup);

   if ( idField == ifds::StopDate && ( dstrValue == str12319999 || dstrValue == NULL_STRING ) )
   {
      BFCBO::setFieldNoValidate( idField, str12319999, idDataGroup, false, true, true );
      BFCBO::setFieldNoValidate( idField, str12319999, BF::HOST, false, true, true );

      setFieldUpdated( idField, idDataGroup, true );
      setFieldUpdated( idField, BF::HOST, true );
   }
   else
   {
      BFCBO::setField( idField, dstrValue, idDataGroup, bFormatted, bSideEffect );
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/PayToEntity.cpp-arc  $
// 
//    Rev 1.22   Jun 11 2008 06:43:14   daechach
// in#1222106 - Stop Dates not picking up properly in Pay Entities and Pay Instructions
// 
//    Rev 1.21   May 01 2007 10:29:04   jankovii
// IN 862766 - Payment instr.
// 
//    Rev 1.20   Sep 14 2006 12:47:36   porteanm
// STP 2192/FN 13
// 
//    Rev 1.19   Sep 13 2006 19:11:14   popescu
// STP 2192/FN 13
// 
//    Rev 1.18   Sep 10 2006 17:59:14   popescu
// STP 2192/12
// 
//    Rev 1.17   Sep 07 2006 21:37:54   popescu
// STP 2192/02
// 
//    Rev 1.16   Aug 28 2006 15:40:24   ZHANGCEL
// PET2212 FN10 -- Added new logic for Netting Bulking Redemption and Distribution Payment
// 
//    Rev 1.15   Aug 01 2006 14:14:48   ZHANGCEL
// PET2192 FN11 -- Fix problem with dummy record
// 
//    Rev 1.14   Jul 27 2006 18:01:16   ZHANGCEL
// PET2192 FN11 - Commission Payments to MgmtCo related changes
// 
//    Rev 1.13   Nov 30 2004 14:13:12   hernando
// PTS 10036108 - Fixed the broker/branch/salesrep not found issue; there is a case when pay entity/instruct records are in the database but the correspondent brokers/branches/sales reps are not.  SYNCHRONIZED WITH 1.10.1.1
// 
//    Rev 1.12   Nov 26 2004 13:28:26   Fengyong
// 10034745
// 
//    Rev 1.11   Nov 14 2004 14:50:56   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.10   Apr 07 2004 18:38:34   FENGYONG
// PET944FN01 rel56.1 NSCC Broker
// 
//    Rev 1.9   Apr 05 2004 17:29:48   FENGYONG
// PET944 FN01, release 56.1 NSCC Broker Matrix
// 
//    Rev 1.8   Mar 04 2004 17:49:00   popescu
// PTS 10027865, fixed crash in Pay to entity search for inactive brokers. Disabled 'Instructions' button in pay to entity dialog if broker is inactive/not effective
// 
//    Rev 1.7   Aug 07 2003 17:07:12   popescu
// disabled the pay to entity validation
// 
//    Rev 1.6   Aug 07 2003 14:59:10   popescu
// PTS 10020472 and added validation for pay to entity. User cannot set-up a pay to entity record if there are no payment instructions records at the pay to entity level
// 
//    Rev 1.5   Jul 11 2003 20:07:42   popescu
// strip all and uppercase the br,bra, slsrep codes
// 
//    Rev 1.4   Jul 10 2003 22:21:06   popescu
// check in for payment instruct, used mfcan_ip_param for some interporcess param passing
// 
//    Rev 1.3   Jul 09 2003 21:57:00   popescu
// Payment Instructiuons work, business rules implementation SSB_PET_821_FN17
// 
//    Rev 1.2   Jul 02 2003 17:49:48   popescu
// work for payment instructions feature 
// 
//    Rev 1.1   Jul 01 2003 18:08:00   popescu
// Clean-up the code, new business rules, set the broker name to the dialog caption, etc...
// 
//    Rev 1.0   Jun 27 2003 18:16:48   popescu
// Initial revision.
// 
 */