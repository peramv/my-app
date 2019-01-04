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
// ^FILE   : TransFeeContext.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : November 2004
//
// ^CLASS    : TransFeeContext
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "transfeecontext.hpp"

#include "pendingtradedetails.hpp"
#include "trade.hpp"

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME  = I_("TransFeeContext");
}

namespace CND
{  // Conditions used
}

namespace ifds
{
//field ids used
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFTextFieldId AllAmtTypes;
   extern CLASS_IMPORT const BFTextFieldId AmountType;
   extern CLASS_IMPORT const BFTextFieldId PayType2;
   extern CLASS_IMPORT const BFTextFieldId rxFundCode;
   extern CLASS_IMPORT const BFTextFieldId rxClassCode;
   extern CLASS_IMPORT const BFTextFieldId FundTo;
   extern CLASS_IMPORT const BFTextFieldId ClassToCode;
   extern CLASS_IMPORT const BFTextFieldId PayType2;
   extern CLASS_IMPORT const BFNumericFieldId rxAcctNum;
   extern CLASS_IMPORT const BFDateFieldId TradeDate;
   extern CLASS_IMPORT const BFDecimalFieldId ExchRate;

}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
   //  Field DD Id,       State Flags,      Group Flags 
   { ifds::TransType,     BFCBO::NONE,      BFCBO::CALCULATED_FIELD }, 
   { ifds::TransNum,      BFCBO::NONE,      BFCBO::CALCULATED_FIELD }, 
   { ifds::AccountNum,    BFCBO::NONE,      BFCBO::CALCULATED_FIELD }, 
   { ifds::AccountTo,     BFCBO::NONE,      BFCBO::CALCULATED_FIELD }, 
   { ifds::EffectiveDate, BFCBO::NONE,      BFCBO::CALCULATED_FIELD }, 
   { ifds::RedCode,       BFCBO::NONE,      BFCBO::CALCULATED_FIELD }, 
   { ifds::DepositType,   BFCBO::NONE,      BFCBO::CALCULATED_FIELD }, 
   { ifds::Broker,        BFCBO::NONE,      BFCBO::CALCULATED_FIELD }, 
   { ifds::Branch,        BFCBO::NONE,      BFCBO::CALCULATED_FIELD }, 
   { ifds::SlsrepCode,    BFCBO::NONE,      BFCBO::CALCULATED_FIELD }, 
   { ifds::FromFund,      BFCBO::NONE,      BFCBO::CALCULATED_FIELD }, 
   { ifds::FromClass,     BFCBO::NONE,      BFCBO::CALCULATED_FIELD }, 
   { ifds::ToFund,        BFCBO::NONE,      BFCBO::CALCULATED_FIELD }, 
   { ifds::ToClass,       BFCBO::NONE,      BFCBO::CALCULATED_FIELD }, 
   { ifds::SettleCurrency,BFCBO::NONE,      BFCBO::CALCULATED_FIELD }, 
   { ifds::Amount,        BFCBO::NONE,      BFCBO::CALCULATED_FIELD }, 
   { ifds::AmtType,       BFCBO::NONE,      BFCBO::CALCULATED_FIELD }, 
   { ifds::LSIFCode,      BFCBO::NONE,      BFCBO::CALCULATED_FIELD }, 
   { ifds::TradesPayType, BFCBO::NONE,      BFCBO::CALCULATED_FIELD }, 
   { ifds::GrossOrNet,    BFCBO::NONE,      BFCBO::CALCULATED_FIELD }, 
   { ifds::AcqFeeOption,  BFCBO::NONE,      BFCBO::CALCULATED_FIELD }, 
   { ifds::ROAAmount,      BFCBO::NONE,      BFCBO::CALCULATED_FIELD }, 
   { ifds::ExchRate,       BFCBO::NONE,      BFCBO::CALCULATED_FIELD }, 
   { ifds::TradeInDate,   BFCBO::NONE,      BFCBO::CALCULATED_FIELD },

};

static const int NUM_FIELDS = sizeof(classFieldInfo) / sizeof(BFCBO::CLASS_FIELD_INFO);


//******************************************************************************
TransFeeContext::TransFeeContext (BFAbstractCBO &parent) : MFCanBFCbo (parent)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
   registerMemberData ( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo,
                        0, NULL);
   setFieldAllSubstituteValues ( ifds::AmtType, 
                                 BF::HOST, 
                                 ifds::AllAmtTypes);
}

//******************************************************************************
TransFeeContext::~TransFeeContext ()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
TransFeeContext& TransFeeContext::operator= (const TransFeeContext &copy)
{
   for (int i = 0; i < NUM_FIELDS; i++)
   {
      BFCBO::CLASS_FIELD_INFO fieldInfo = classFieldInfo [i];
   
      DString value;
      const BFFieldId &fieldId = fieldInfo.getFieldId();

      copy.getField (fieldId, value, BF::HOST);
      setFieldNoValidate (fieldId, value, BF::HOST, false);
   }
   return *this;
}

//******************************************************************************
bool TransFeeContext::operator== (const TransFeeContext &o)
{
   for (int i = 0; i < NUM_FIELDS; i++)
   {
      BFCBO::CLASS_FIELD_INFO fieldInfo = classFieldInfo [i];
   
      DString val, 
         _val;
      const BFFieldId &fieldId = fieldInfo.getFieldId();

      getField (fieldId, val, BF::HOST);
      o.getField (fieldId, _val, BF::HOST);
      if (val != _val)
      {
         return false;
      }
   }
   return true;
}

//******************************************************************************
SEVERITY TransFeeContext::initTradeContext ( Trade *pTrade,
                                             const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("initTradeContext"));

   assert (pTrade);
   for (int i = 0; i < NUM_FIELDS; i++)
   {
      BFCBO::CLASS_FIELD_INFO fieldInfo = classFieldInfo [i];
   
      DString value;
      BFFieldId fieldId = fieldInfo.getFieldId();

      if (fieldId == ifds::TransType)
      {
         fieldId = ifds::TradesTransType;
      }
      //set the field onto the new context only if is valid
//      if (pTrade->getErrorState (fieldId, idDataGroup) <= WARNING)
      {
         pTrade->getField (fieldId, value, idDataGroup);
         if (fieldId == ifds::TradesTransType)
         {
            fieldId = ifds::TransType;
         }
         setFieldNoValidate(fieldId, value, BF::HOST, false);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TransFeeContext::initPendingTradeContext ( PendingTradeDetails *pPendingTradeDetails,
                                                    const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("initPendingTradeContext"));

   assert (pPendingTradeDetails);
//copy fields that do not match
   struct pending2context_mapping
   {
      BFFieldId _pending;
      BFFieldId _context;
   } 

   a_pending2context_mapping [] = 
   {
      {ifds::rxAcctNum,     ifds::AccountNum},
      {ifds::TradeDate,     ifds::EffectiveDate},
      {ifds::PayType2,      ifds::TradesPayType},
      {ifds::rxFundCode,    ifds::FromFund},
      {ifds::rxClassCode,   ifds::FromClass},
      {ifds::FundTo,        ifds::ToFund},
      {ifds::ClassToCode,   ifds::ToClass},
      {ifds::AmountType,    ifds::AmtType},
      {ifds::ROAAmount,     ifds::ROAAmount},
      {ifds::TradeInDate,    ifds::TradeInDate},

   };         

   int _num_fields = sizeof (a_pending2context_mapping) / sizeof (pending2context_mapping);

   for (int i = 0; i < NUM_FIELDS; i++)
   {
      BFCBO::CLASS_FIELD_INFO fieldInfo = classFieldInfo [i];      
      DString value;      
      BFFieldId fieldId = fieldInfo.getFieldId();
      int matchingNdx = -1;

      for (int i = 0; i < _num_fields; i++)
      {
         if (fieldId == a_pending2context_mapping [i]._context)
         {
            fieldId = a_pending2context_mapping [i]._pending;
            matchingNdx = i;
            break;
         }
      }
//set the field onto the new context only if is valid
//      if (pPendingTradeDetails->getErrorState (fieldId, idDataGroup) <= WARNING)
      {
         pPendingTradeDetails->getField (fieldId, value, idDataGroup);
         if (matchingNdx >= 0)
         {
            fieldId = a_pending2context_mapping [matchingNdx]._context;
         }
         setFieldNoValidate (fieldId, value, BF::HOST, false);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TransFeeContext.cpp-arc  $
// 
//    Rev 1.12   Jun 02 2005 10:16:00   yingbaol
// PEt1203,FN01,Add ExchRate to FieldInfo
// 
//    Rev 1.11   May 18 2005 09:03:42   yingbaol
// PET1203,FN01 Commission-Class A enhancement
// 
//    Rev 1.10   Feb 25 2005 18:16:44   popescu
// Incident# 251618, restored the 'regular' subst value for acq fee option, and raised error if user chooses regular for a shareholder that has fee model and fund is FEL
// 
//    Rev 1.9   Jan 21 2005 19:02:46   popescu
// PET 1117/06, fixed admin fee amount type issue.
// 
//    Rev 1.8   Jan 20 2005 11:03:42   popescu
// PTS 10038127, fixed internal error when user clicks on the 'Fees' button in trans  history screen
// 
//    Rev 1.7   Jan 09 2005 17:42:42   popescu
// PTS 10037339, set all amt types subst set to amt type
// 
//    Rev 1.6   Dec 02 2004 18:23:30   popescu
// PET 1117/06/56, trades processing/fees processing
// 
//    Rev 1.5   Nov 24 2004 21:36:32   popescu
// PET 1117/06/56. trade processing, settle location
// 
//    Rev 1.4   Nov 17 2004 16:15:56   popescu
// PET 1117/06, Trade processing fees
// 
//    Rev 1.3   Nov 15 2004 16:23:40   popescu
// PET 1117/06, more synch to .NET changes
// 
//    Rev 1.1   Nov 09 2004 16:51:10   popescu
// PET 1117/06, Trade processing
// 
//    Rev 1.0   Nov 05 2004 21:30:24   popescu
// Initial revision.
// 
 */