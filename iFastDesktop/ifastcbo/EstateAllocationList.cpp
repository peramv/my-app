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
//    Copyright 2011 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : EstateAllocationList.cpp
// ^AUTHOR : 
// ^DATE   : 
//
//********************************************************************************
#include "stdafx.h"
#include "estateallocation.hpp"
#include "estateallocationlist.hpp"
#include "fundmasterlist.hpp"
#include "mgmtco.hpp"

#include <ifastdataimpl\dse_dstc0441_vw.hpp>
#include <ifastdataimpl\dse_dstc0441_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0441_req.hpp>


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ESTATE_ALLOCATION;
}

namespace
{
   const I_CHAR * const CLASSNAME	= I_( "EstateAllocationList" );

   const I_CHAR * const AMOUNT_TYPE_AMOUNT   = I_( "D" );
   const I_CHAR * const AMOUNT_TYPE_PERCENT  = I_( "P" );
   const I_CHAR * const AMOUNT_TYPE_UNITS    = I_( "U" );

}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId Selected;
   extern CLASS_IMPORT const BFTextFieldId GIRedemInvSelectAmountType;
   extern CLASS_IMPORT const BFTextFieldId ReadOnly;
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFTextFieldId GrossOrNet;
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFDecimalFieldId TradeAmount;
	extern CLASS_IMPORT const BFTextFieldId IsInvSelected;
   extern CLASS_IMPORT const BFDecimalFieldId FundTotalAmt;
}

namespace CND
{  
   extern const long ERR_INVALID_FUND_CLASS_CODES;
   extern const long ERR_GI_NET_REDEMPTION_CAN_USE_ONLY_ONE_INVESTMENT;
   extern const long ERR_GI_SELECTED_AMOUNT_NOT_TRADE_AMOUNT;
   extern const long ERR_GI_SELECTED_TOTAL_NOT_100;
   extern const long ERR_AMOUNT_EXCEEDS_PRINCIPAL;  
   extern const long ERR_SUM_OF_PERCENTAGES_NOT_100;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
   // Field DD Id,                     State Flags,      Group Flags 

 
   { ifds::FundClassAmtFullPW,     BFCBO::NONE,         0},
   { ifds::FundNAV,                BFCBO::NONE,         0},
   { ifds::Amount,                 BFCBO::NONE,         0},
   { ifds::AmountType,             BFCBO::NONE,         0},
   { ifds::FundTotalAmt,           BFCBO::NONE,         0},
 
   { ifds::AccountNum,        BFCBO::NONE,         0},
   { ifds::BenefEntityID,     BFCBO::NONE,         0},
   { ifds::BenefAddrCode,     BFCBO::NONE,         0},
   { ifds::BenefAddrLevel,    BFCBO::NONE,         0},
   { ifds::BenefPrcnt,        BFCBO::NONE,         0},
   { ifds::BenefAmount,       BFCBO::NONE,         0},
   { ifds::BenefUnits,        BFCBO::NONE,         0},
   { ifds::BenefName,         BFCBO::NONE,         0}

};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
EstateAllocationList::EstateAllocationList( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
, m_requestData (ifds::DSTC0441_REQ)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   setObjectAsList ();
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}
 
//******************************************************************************
EstateAllocationList::~EstateAllocationList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY EstateAllocationList::init (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY EstateAllocationList::init(const DString& dstrAccountNum, 
					   const DString& dstrTransId, 
                  const DString& dstrAmount,
                  const DString& dstrAmountType,
                  const DString& dstrFund,
					   const DString& dstrClass,
                  const DString& dstrTradeDate,
					   const BFDataGroupId& idDataGroup,
                  bool  bReadOnly)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   DString mgmtCoIdOut;

   setField(ifds::AccountNum, dstrAccountNum, BF::HOST, false);

   m_requestData.setElementValue( ifds::AccountNum,     dstrAccountNum);
   m_requestData.setElementValue( ifds::TransId,        dstrTransId);
   m_requestData.setElementValue( ifds::Amount,         dstrAmount);
   m_requestData.setElementValue( ifds::AmountType,     dstrAmountType);
   m_requestData.setElementValue( ifds::Fund,           dstrFund);
   m_requestData.setElementValue( ifds::Class,          dstrClass);
   m_requestData.setElementValue( ifds::EffectiveDate,  dstrTradeDate);
	m_requestData.setElementValue( ifds::CompanyId,      getMgmtCoId( mgmtCoIdOut ) );

   ReceiveData (DSTC_REQUEST::ESTATE_ALLOCATION, m_requestData, 
	ifds::DSTC0441_VW, DSTCRequestor(getSecurity(), false), false);

   BigDecimal bdTotalAmount = BIGDEC_ZERO;
   BFObjIter iter (*this, idDataGroup);
   while(!iter.end())
   {
      EstateAllocation* pEstateAllocation = dynamic_cast <EstateAllocation*>(iter.getObject());
      
      DString dstrBenefAmount;
      pEstateAllocation->getField(ifds::BenefAmount, dstrBenefAmount, idDataGroup, false);
      BigDecimal bdBenefAmount(dstrBenefAmount);
      bdTotalAmount += bdBenefAmount;
      if(bReadOnly)
      {
         pEstateAllocation->setFieldReadOnly(ifds::BenefAddrCode, idDataGroup, true);
         pEstateAllocation->setFieldReadOnly(ifds::BenefAddrLevel, idDataGroup, true);
         pEstateAllocation->setFieldReadOnly(ifds::BenefPrcnt, idDataGroup, true);    
         pEstateAllocation->setFieldReadOnly(ifds::BenefAmount, idDataGroup, true);   
         pEstateAllocation->setFieldReadOnly(ifds::BenefUnits, idDataGroup, true);    
      }
      ++iter;
   }
   setFieldNoValidate(ifds::Amount, bdTotalAmount.asDString(), BF::HOST, false, true, false, false);
   setFieldNoValidate(ifds::AmountType, dstrAmountType, BF::HOST, false, true, false, false);

   if(dstrAmountType == AMOUNT_TYPE_PERCENT)
   {
      BigDecimal bdPercent (dstrAmount);
      BigDecimal bd100(100);
      BigDecimal bdFundTotalAmt = bdTotalAmount * bd100 / bdPercent;
      setField(ifds::FundTotalAmt, bdFundTotalAmt.asDString(), idDataGroup, false);
   }
   return GETCURRENTHIGHESTSEVERITY();
}


//*************************************************************************************
SEVERITY EstateAllocationList::doCreateObject (const BFData& data, BFCBO*& pObjOut)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   EstateAllocation* pEstateAllocation = new EstateAllocation(*this);
   pEstateAllocation->init(const_cast<BFData&>(data));
   
   pObjOut = pEstateAllocation;

   return( GETCURRENTHIGHESTSEVERITY() );
}

//*******************************************************************************
SEVERITY EstateAllocationList::doApplyRelatedChanges ( const BFFieldId &idField, 
                                                        const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ));
   setFieldUpdated (idField, idDataGroup, false);
   if(idField == ifds::GIRedemInvSelectAmountType)
   {
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
SEVERITY EstateAllocationList::doValidateAll (const BFDataGroupId& idDataGroup, 
                                               long lValidateGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );
				

   BigDecimal bdTotalAmount = BIGDEC_ZERO;
   BigDecimal bdTotalPercent = BIGDEC_ZERO;
   BFObjIter iter (*this, idDataGroup);
   while(!iter.end())
   {
      EstateAllocation* pEstateAllocation = dynamic_cast <EstateAllocation*>(iter.getObject());
      
      DString dstrBenefAmount;
      pEstateAllocation->getField(ifds::BenefAmount, dstrBenefAmount, idDataGroup);
      BigDecimal bdBenefAmount(dstrBenefAmount);
      bdTotalAmount += bdBenefAmount;

      DString dstrBenefPrcnt;
      pEstateAllocation->getField(ifds::BenefPrcnt, dstrBenefPrcnt, idDataGroup);
      BigDecimal bdBenefPrcnt(dstrBenefPrcnt);
      bdTotalPercent += bdBenefPrcnt;
      ++iter;
   }
   
   BigDecimal bd100(100);
   if(bdTotalPercent > bd100 || bdTotalPercent < bd100)
   {
      ADDCONDITIONFROMFILE (CND::ERR_SUM_OF_PERCENTAGES_NOT_100);
   }

   DString dstrAmountType;
   getField(ifds::AmountType, dstrAmountType, idDataGroup);
   if(dstrAmountType == AMOUNT_TYPE_AMOUNT || dstrAmountType == AMOUNT_TYPE_UNITS)
   {
      DString dstrAmount;
      getField(ifds::Amount, dstrAmount, idDataGroup);
      BigDecimal bdAmount(dstrAmount);
      if(bdAmount != dstrAmount)
      {
         ADDCONDITIONFROMFILE( CND::ERR_GI_SELECTED_AMOUNT_NOT_TRADE_AMOUNT);
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY EstateAllocationList::doValidateField ( const BFFieldId &idField, 
                                                  const DString &strValue, 
                                                  const BFDataGroupId &idDataGroup) 
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
	                       I_("doValidateField"));

//   if (idField == ifds::InvestmentHistoryFund)
   {
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

SEVERITY EstateAllocationList::recalculateAmounts(const DString& dstrAmount, const DString& dstrAmountType, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("recalculateAmounts"));
   
   DString dstrFundNAV;
   getField(ifds::FundNAV, dstrFundNAV, idDataGroup, false);

   if(dstrAmountType == AMOUNT_TYPE_AMOUNT)
   {
      setField(ifds::Amount, dstrAmount, idDataGroup);
   }
   else if(dstrAmountType == AMOUNT_TYPE_UNITS)
   {
      BigDecimal bdAmount(dstrAmount);
      BigDecimal bdFundNAV(dstrFundNAV);
      bdAmount *= bdFundNAV;
      setField(ifds::Amount, bdAmount.asDString(), idDataGroup);
   }
   else if(dstrAmountType == AMOUNT_TYPE_PERCENT)
   {  
      DString dstrFundTotalAmt;
      getField(ifds::FundTotalAmt, dstrFundTotalAmt, idDataGroup, false);
      BigDecimal bdAmount(dstrAmount);
      BigDecimal bdFundTotalAmt(dstrFundTotalAmt);
      BigDecimal bd100(100);
      bdAmount = bdAmount * bdFundTotalAmt / bd100;
      setField(ifds::Amount, bdAmount.asDString(), idDataGroup);

   }

   BFObjIter iterEstateAllocation(*this, idDataGroup, false);
   while (!iterEstateAllocation.end())
   {
      DString dstrAmtType;
      EstateAllocation *pEstateAllocation = dynamic_cast<EstateAllocation*> (iterEstateAllocation.getObject()); 
      
      pEstateAllocation->recalculateAmount(dstrAmount, dstrAmountType, dstrFundNAV, idDataGroup);

      ++iterEstateAllocation;
   }


   return GETCURRENTHIGHESTSEVERITY ();
};

SEVERITY EstateAllocationList::getBenefAmount(const BFDataGroupId& idDataGroup, BigDecimal& bdTotalBenefAmount)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getBenefAmount"));
   
   bdTotalBenefAmount = BIGDEC_ZERO;

   BFObjIter iterEstateAllocation(*this, idDataGroup, false);
   while (!iterEstateAllocation.end())
   {
      EstateAllocation *pEstateAllocation = dynamic_cast<EstateAllocation*> (iterEstateAllocation.getObject()); 

      DString dstrBenefAmount;
      pEstateAllocation->getField(ifds::BenefAmount, dstrBenefAmount, idDataGroup, false);
      BigDecimal bdBenefAmount(dstrBenefAmount);
      bdTotalBenefAmount += bdBenefAmount;

      ++iterEstateAllocation;
   }

   return GETCURRENTHIGHESTSEVERITY ();
};

SEVERITY EstateAllocationList::getBenefAmount(const BFDataGroupId& idDataGroup, DString& dstrTotalBenefAmount)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getBenefAmount"));
   
   BigDecimal bdTotalBenefAmount;
   bdTotalBenefAmount = BIGDEC_ZERO;

   getBenefAmount(idDataGroup, bdTotalBenefAmount);

   dstrTotalBenefAmount = bdTotalBenefAmount.asDString();

   return GETCURRENTHIGHESTSEVERITY ();
};



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/EstateAllocationList.cpp-arc  $
// 
//    Rev 1.1   10 Aug 2012 13:07:06   if991250
// Estate Allocation
// 
//    Rev 1.0   25 Jul 2012 15:26:18   if991250
// Initial revision.
// 
// 
*/
