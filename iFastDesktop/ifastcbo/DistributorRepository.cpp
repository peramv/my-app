//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Canada, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2001 by DST Canada, Inc.
//
//*****************************************************************************
//
// ^FILE   : DistributorRepository.cpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : 3/6/01
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : DistributorRepository
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include "distributorrepository.hpp"
#include "distributorbankinstructionslist.hpp"
#include "paytoentitylist.hpp"
#include "paymentinstructions.hpp"
#include "paymentinstructionslist.hpp"

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "DistributorRepository");
}

namespace ifds
{
   //field ids used
   extern CLASS_IMPORT const BFTextFieldId BrokerCode;
}

extern BF_OBJ_TYPE OBJ_TYPE_DISTRIBUTOR_BANK_INSTR;
extern BF_OBJ_TYPE OBJ_TYPE_PAY_TO_ENTITY_LIST;
extern BF_OBJ_TYPE OBJ_TYPE_PAYMENT_INSTRUCTIONS_LIST;

//******************************************************************************
DistributorRepository::DistributorRepository( 
   BFAbstractCBO &parent)
: MFCanBFCbo( parent)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING);
   setObjectAsList();
}

//******************************************************************************
DistributorRepository::~DistributorRepository()
{
   TRACE_DESTRUCTOR( CLASSNAME);
}


//******************************************************************************
SEVERITY DistributorRepository::init( const BFDataGroupId &idDataGroup /*= BF::HOST*/,
                                      const DString& dstrTrack /*= I_("N")*/, 
                                      const DString& dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));
  
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DistributorRepository::
   getDistributorBankInstructionsList( const DString &dstrBroker, 
                                       const DString &dstrBranch, 
                                       const DString &dstrSlsRep,
                                       DistributorBankInstructionsList *&pDistributorBankInstructionsList, 
                                       const BFDataGroupId &idDataGroup, 
	                                    BFAbstractCBO *parent_ /*=NULL*/, 
                                       const DString &dstrTrack /*= I_("N")*/, 
                                       const DString &dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getDistributorBankInstructionsList"));
   DString dstrKey;

   buildKey (dstrBroker, dstrBranch, dstrSlsRep, dstrKey);
   
   BFObjectKey objKey ( dstrKey, 
                        idDataGroup, 
                        OBJ_ACTIVITY_NONE, 
                        OBJ_TYPE_DISTRIBUTOR_BANK_INSTR);

   pDistributorBankInstructionsList = 
      dynamic_cast<DistributorBankInstructionsList*>(getObject( dstrKey, 
                                                                idDataGroup, 
                                                                OBJ_TYPE_DISTRIBUTOR_BANK_INSTR, 
                                                                OBJ_ACTIVITY_NONE));
   if (!pDistributorBankInstructionsList)
   {
      pDistributorBankInstructionsList = new DistributorBankInstructionsList (*this);
      if (pDistributorBankInstructionsList->init ( dstrBroker, 
                                                   dstrBranch, 
                                                   dstrSlsRep, 
                                                   idDataGroup) <= WARNING)
      {
         setObject (objKey, pDistributorBankInstructionsList);
      }
      else
      {
         delete pDistributorBankInstructionsList;
         pDistributorBankInstructionsList = NULL;
      }
   }
   if ( pDistributorBankInstructionsList && 
        dynamic_cast <PaymentInstructions*> (parent_))
   {
      pDistributorBankInstructionsList->setPayInstructionsAsParentCBO (parent_);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DistributorRepository::getPayToEntityList( const DString &dstrBroker, 
	                                                 const DString &dstrSearchTypeMgmt,
                                                    PayToEntityList *&pPayToEntityList, 
                                                    const BFDataGroupId &idDataGroup, 
                                                    const DString& dstrTrack /*= I_("N")*/, 
                                                    const DString& dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getPayToEntityList"));
   DString dstrKey = I_("PayToEntityList");
   BFObjectKey objKey(dstrKey, idDataGroup, OBJ_ACTIVITY_NONE, 
      OBJ_TYPE_PAY_TO_ENTITY_LIST);

   pPayToEntityList = dynamic_cast<PayToEntityList*>(getObject(dstrKey, 
      idDataGroup, OBJ_TYPE_PAY_TO_ENTITY_LIST, OBJ_ACTIVITY_NONE));
   if (!pPayToEntityList)
   {
      pPayToEntityList = new PayToEntityList(*this);
      if (pPayToEntityList->init(
         dstrBroker,
			dstrSearchTypeMgmt,
         idDataGroup, 
         dstrTrack, 
         dstrPageName) <= WARNING)
      {
         //set it only once
         setObject(objKey, pPayToEntityList);
      }
      else
      {
         delete pPayToEntityList;
         pPayToEntityList = NULL;
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DistributorRepository::getPaymentInstructionsList( const DString &dstrBroker, 
                                                            const DString &dstrBranch, 
                                                            const DString &dstrSlsRep, 
                                                            const DString &dstrPaymentFor,
	                                                         const DString &dstrSearchTypeMgmt,
	                                                         PaymentInstructionsList *&pPaymentInstructionsList, 
                                                            const BFDataGroupId &idDataGroup, 
                                                            const DString& dstrTrack /*= I_("N")*/, 
                                                            const DString& dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getPayToEntityList"));
   DString dstrKey = I_("PaymentInstructionsList");
   BFObjectKey objKey(dstrKey, idDataGroup, OBJ_ACTIVITY_NONE, 
      OBJ_TYPE_PAYMENT_INSTRUCTIONS_LIST);

   pPaymentInstructionsList = dynamic_cast<PaymentInstructionsList*>(getObject(dstrKey, 
      idDataGroup, OBJ_TYPE_PAYMENT_INSTRUCTIONS_LIST, OBJ_ACTIVITY_NONE));
   if (!pPaymentInstructionsList)
   {
      pPaymentInstructionsList = new PaymentInstructionsList(*this);
      if (pPaymentInstructionsList->init (
         dstrBroker, 
         dstrBranch, 
         dstrSlsRep,
		   dstrPaymentFor, 
			dstrSearchTypeMgmt,      
			I_("N")/*not exact match*/,
			NULL_STRING, //EffectiveDate
			NULL_STRING, //PayInstructionsId
         NULL_STRING, //stop date
			idDataGroup, 
         dstrTrack, 
         dstrPageName) <= WARNING)
      {
         setObject (objKey, pPaymentInstructionsList);
      }
      else
      {
         delete pPaymentInstructionsList;
         pPaymentInstructionsList = NULL;
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void DistributorRepository::buildKey( const DString &dstrBroker, 
                                      const DString &dstrBranch, 
                                      const DString &dstrSlsRep,
                                      DString &key)
{
   DString broker (dstrBroker),
      branch (dstrBranch), 
      slsRep (dstrSlsRep);

   key = I_("Broker=") + broker.stripAll().upperCase();
   key += I_(";Branch=") + branch.stripAll().upperCase();
   key += I_(";SlsRep=") + slsRep.stripAll().upperCase();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DistributorRepository.cpp-arc  $
// 
//    Rev 1.12   Oct 20 2006 18:14:34   popescu
// Incident# 731541 reviewed the way related changes for  fields is working in paym instruct
// 
//    Rev 1.11   Sep 10 2006 17:59:02   popescu
// STP 2192/12
// 
//    Rev 1.10   Aug 28 2006 15:43:46   ZHANGCEL
// PET2212 FN10 -- Added new fields in PaymentInstruction::Init()
// 
//    Rev 1.9   Jul 31 2006 15:34:56   ZHANGCEL
// PET2192 FN11 -- MgmtCo Banking related changes
// 
//    Rev 1.8   Jul 27 2006 17:59:28   ZHANGCEL
// PET2192 FN11 - Commission Payments to MgmtCo related changes
// 
//    Rev 1.7   Nov 14 2004 14:31:00   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.6   Feb 18 2004 18:01:12   popescu
// PTS 10027184; - moved the ownership of the payment instructions banking list at the payment instructions CBO level.
// - clean-up the work session every time user hits 'Search' on the Features Search Dialog
// - do not add payment instructions/ pay to entity records, when refreshing the respective CBO lists in DistributorRepository, always read them from back-end. Now, this is possible since the work session is cleaned-up all the time.
// - fixed crash that happens when a new record is added to the payment instructions bank list. The scenario to get this crash is: go to pay to entity screen, then click the 'instructions' button, modify an existing payment instructions record with bank information. Hit okay, commit the changes in the parent. Go back to the payment instructions (you will notice that the previous changes are not saved -  another issue that has been fixed with this ticket), and then click the Bank button. Add a new bank record. Desktop reports an internal error.
// - use new IFDSListCtrl, for the PayToEntity list and PaymentInstructions list.
// 
//    Rev 1.5   Aug 17 2003 16:14:30   popescu
// When asking for DistributorBanks, payment instructions sends itself as the parent CBO
// 
//    Rev 1.4   Jul 23 2003 18:20:40   popescu
// Capitalized the parameters
// 
//    Rev 1.3   Jul 09 2003 21:56:50   popescu
// Payment Instructiuons work, business rules implementation SSB_PET_821_FN17
// 
//    Rev 1.2   Jul 01 2003 18:09:26   popescu
// Added the payment instruction dialog, process and CBO's, as well as the DistributorRepository builder
// 
//    Rev 1.1   Jun 27 2003 18:13:24   popescu
// Pay To Entity feature, dialog, process and CBO
// 
//    Rev 1.0   May 31 2003 12:00:46   popescu
// Initial revision.
// 
*/

