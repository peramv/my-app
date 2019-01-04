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
// ^FILE   : GIInvestmentDetailsList.cpp
// ^AUTHOR : 
// ^DATE   : 
//
//********************************************************************************
#include "stdafx.h"
#include "giinvestmentdetails.hpp"
#include "giinvestmentdetailslist.hpp"
#include "fundmasterlist.hpp"
#include "mgmtco.hpp"

#include <ifastdataimpl\dse_dstc0421_vw.hpp>
#include <ifastdataimpl\dse_dstc0421_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0421_req.hpp>


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest INVESTMENT_HISTORY_INQUIRY;
}

namespace
{
   const I_CHAR * const CLASSNAME	= I_( "GIInvestmentDetailsList" );
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
   extern CLASS_IMPORT const BFTextFieldId AmtType;
}

namespace CND
{  
   extern const long ERR_INVALID_FUND_CLASS_CODES;
   extern const long ERR_GI_NET_REDEMPTION_CAN_USE_ONLY_ONE_INVESTMENT;
   extern const long ERR_GI_SELECTED_AMOUNT_NOT_TRADE_AMOUNT;
   extern const long ERR_GI_SELECTED_TOTAL_NOT_100;
   extern const long ERR_AMOUNT_EXCEEDS_PRINCIPAL;  
   extern const long ERR_NO_INVESTMENT_SETUP;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
   // Field DD Id,                     State Flags,      Group Flags 
   { ifds::InvestmentHistoryFund,      BFCBO::NONE,         0},
   { ifds::InvestmentHistoryClass,     BFCBO::NONE,         0},
   { ifds::InvestmentHistoryNumber,    BFCBO::NONE,         0},
   { ifds::InvestmentHistorySearch,    BFCBO::REQUIRED,     0},
   { ifds::InvestmentHistoryStatus,    BFCBO::NONE,         0},
   { ifds::GIRedemInvSelectAmountType, BFCBO::NONE,         0},
   { ifds::ReadOnly,                   BFCBO::NONE,         0},


   {ifds::AccountNum,     BFCBO::NONE,         0},
   {ifds::EffectiveDate,  BFCBO::NONE,         0},
   {ifds::GrossOrNet,     BFCBO::NONE,         0},
   {ifds::RedemOrder,     BFCBO::NONE,         0},
   {ifds::SuppressMVA,    BFCBO::NONE,         0},
   {ifds::SuppressAdmin,  BFCBO::NONE,         0},
   {ifds::TransType,      BFCBO::NONE,         0},
   {ifds::TradeAmount,    BFCBO::NONE,         0},
 


};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
GIInvestmentDetailsList::GIInvestmentDetailsList( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
, m_requestData (ifds::DSTC0421_REQ)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   m_isTotalsCBO = false;
   setObjectAsList ();
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}

//******************************************************************************
GIInvestmentDetailsList::~GIInvestmentDetailsList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY GIInvestmentDetailsList::init (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   setFieldNoValidate(ifds::GIRedemInvSelectAmountType, I_("D"), idDataGroup);
   setFieldNoValidate (ifds::InvestmentHistorySearch, I_("ALL"), idDataGroup, false, true, true);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY GIInvestmentDetailsList::init(const DString& dstrAccountNum, 
                                       const DString& dstrTransId, 
                                       const DString& dstrFund,
                                       const DString& dstrClass,
                                       const DString& dstrInvNum, 
                                       const DString& dstrInvStatus,
                                       const DString& dstrSearchBy,
                                       const DString& dstrTradeDate,
                                       const DString& dstrAmountType,
                                       bool isNew,
                                       const BFDataGroupId& idDataGroup,
                                       const DString& dstrSuppressMVA,
                                       const DString& dstrSuppressAdmin,
                                       const DString& dstrTradeAmt,
                                       const DString& dstrGrossNet)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   DString mgmtCoIdOut;


   if( !dstrFund.empty() && !dstrClass.empty() )
   {
		m_requestData.setElementValue( ifds::InputAcctNum, dstrAccountNum);
		m_requestData.setElementValue( ifds::TransId, dstrTransId);
		m_requestData.setElementValue( ifds::InvestmentHistoryFund, dstrFund);
		m_requestData.setElementValue( ifds::InvestmentHistoryClass, dstrClass );
		m_requestData.setElementValue( ifds::InvestmentHistoryNumber, dstrInvNum);
		m_requestData.setElementValue( ifds::InvestmentHistoryStatus, dstrInvStatus);
		if(isNew)
         m_requestData.setElementValue(ifds::InvestmentHistorySearch, I_("SelInv"));
      else
      {
         m_requestData.setElementValue(ifds::InvestmentHistorySearch, I_("SelInvPend"));
         m_requestData.setElementValue(ifds::TransId, dstrTransId);
      }

      m_requestData.setElementValue(ifds::EffectiveDate, dstrTradeDate);
		m_requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
		m_requestData.setElementValue( ifds::RedemOrder, I_("SI"));
		m_requestData.setElementValue( ifds::GrossNet, I_("Y"));
		m_requestData.setElementValue( ifds::Track, I_("N") );

      m_requestData.setElementValue( ifds::SuppressMVA, dstrSuppressMVA);
		m_requestData.setElementValue( ifds::SuppressAdmin, dstrSuppressAdmin);
      
      m_requestData.setElementValue( ifds::TradeAmount, dstrTradeAmt);
      m_requestData.setElementValue( ifds::GrossNet,    dstrGrossNet);



		ReceiveData (DSTC_REQUEST::INVESTMENT_HISTORY_INQUIRY, m_requestData, 
			ifds::DSTC0421_VW, DSTCRequestor(getSecurity(), false), false);
    
      setFieldNoValidate( ifds::SuppressMVA,     dstrSuppressMVA,     idDataGroup, false);
		setFieldNoValidate( ifds::SuppressAdmin,   dstrSuppressAdmin,   idDataGroup, false);
		setFieldNoValidate( ifds::AccountNum,      dstrAccountNum,      idDataGroup, false);
		
      setFieldNoValidate( ifds::EffectiveDate,   dstrTradeDate,       idDataGroup, false);
		setFieldNoValidate( ifds::GrossOrNet,      dstrGrossNet,        idDataGroup, false);
		setFieldNoValidate( ifds::TradeAmount,     dstrTradeAmt,        idDataGroup, false);
      setFieldNoValidate( ifds::RedemOrder,      I_("SI"),        idDataGroup, false);

      bool foundPercent = false;
      bool foundAlloc   = false; 
      BFObjIter iterGIInvestmentDetails (*this, idDataGroup, false);
      while (!iterGIInvestmentDetails.end())
      {
         DString dstrAmtType;
         GIInvestmentDetails *pGIInvestmentDetails = dynamic_cast<GIInvestmentDetails*> (iterGIInvestmentDetails.getObject()); 
         pGIInvestmentDetails->getField(ifds::SelInvAmtType, dstrAmtType, idDataGroup, false);
         if(dstrAmtType == I_("P"))
            foundPercent = true;
         else if(dstrAmtType == I_("A"))
            foundAlloc = true;
         ++iterGIInvestmentDetails;
      }

      if(foundPercent)
         changeAmtType( I_("P"), idDataGroup);
      else if(foundAlloc)
         changeAmtType( I_("A"), idDataGroup);
      else
         changeAmtType( I_("D"), idDataGroup);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY GIInvestmentDetailsList::initCalc(
                     const DString dstrAccountNum, 
                     const DString& dstrTransId,       
                     const DString& dstrFundFrom,      
                     const DString& dstrClassFrom,     
                     const DString& dstrEffDate,     
                     const DString& dstrGrossNet,    
                     const DString& dstrRedemOrder,  
                     const DString& dstrSelInvAmtType, 
                     const DString& dstrSelInvAmount,  
                     const DString& dstrSuppressMVA, 
                     const DString& dstrSuppressAdmin,
                     const DString& dstrInvHisInvestId,
                     const DString& dstrInvSummId,
                     const DString& dstrTradeAmount)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initCalc" ) );

   DString mgmtCoIdOut;
   m_requestData.setElementValue( ifds::InputAcctNum,             dstrAccountNum);
   m_requestData.setElementValue( ifds::InvestmentHistoryFund,    dstrFundFrom);
   m_requestData.setElementValue( ifds::InvestmentHistoryClass,   dstrClassFrom);
   m_requestData.setElementValue( ifds::TransId,                  dstrTransId);
   m_requestData.setElementValue( ifds::EffectiveDate,            dstrEffDate);
   m_requestData.setElementValue( ifds::GrossNet,                 dstrGrossNet);
   m_requestData.setElementValue( ifds::RedemOrder,               dstrRedemOrder);
   m_requestData.setElementValue( ifds::SelInvAmtType,            dstrSelInvAmtType);
   m_requestData.setElementValue( ifds::SelInvAmount,             dstrSelInvAmount);
   m_requestData.setElementValue( ifds::SuppressMVA,              dstrSuppressMVA);
   m_requestData.setElementValue( ifds::SuppressAdmin,            dstrSuppressAdmin);
   m_requestData.setElementValue( ifds::InvHisInvestId,           dstrInvHisInvestId);
   m_requestData.setElementValue( ifds::InvSummId,                dstrInvSummId);
   if(dstrSelInvAmtType == I_("A"))
      m_requestData.setElementValue( ifds::TradeAmount,           dstrTradeAmount);

   m_requestData.setElementValue(ifds::InvestmentHistorySearch, I_("SelInvCal"));

	m_requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
	m_requestData.setElementValue( ifds::Track, I_("N") );

	ReceiveData (DSTC_REQUEST::INVESTMENT_HISTORY_INQUIRY, m_requestData, 
		ifds::DSTC0421_VW, DSTCRequestor(getSecurity(), false), false);
   

   return GETCURRENTHIGHESTSEVERITY();
}

SEVERITY GIInvestmentDetailsList::recalculateAll(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "recalculateAll" ) );

   BFObjIter iterGIInvestmentDetails (*this, idDataGroup, false);
   while (!iterGIInvestmentDetails.end())
   {
      GIInvestmentDetails *pGIInvestmentDetails = dynamic_cast<GIInvestmentDetails*> (iterGIInvestmentDetails.getObject()); 
      DString dstrIsInvSelected;
      pGIInvestmentDetails->getField(ifds::IsInvSelected, dstrIsInvSelected, idDataGroup, false);
      if(dstrIsInvSelected == I_("Y"))
      {
         pGIInvestmentDetails->calculateFees(idDataGroup);
      }
      ++iterGIInvestmentDetails;
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//*************************************************************************************
SEVERITY GIInvestmentDetailsList::doCreateObject (const BFData& data, BFCBO*& pObjOut)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   GIInvestmentDetails* pGIInvestmentDetails = new GIInvestmentDetails(*this);
   pGIInvestmentDetails->init(const_cast<BFData&>(data));
   
   pObjOut = pGIInvestmentDetails;

   return( GETCURRENTHIGHESTSEVERITY() );
}

//**************************************************************************************
SEVERITY GIInvestmentDetailsList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

   if (doMoreRecordsExist())
   {
      ReceiveData ( DSTC_REQUEST::INVESTMENT_HISTORY_INQUIRY, 
                    m_requestData, 
                    ifds::DSTC0421_VW, 
                    DSTCRequestor(getSecurity(), false), 
                    false);
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//*******************************************************************************
void GIInvestmentDetailsList::changeAmtType( const DString& dstrAmtType, const BFDataGroupId &idDataGroup)
{
   setFieldNoValidate(ifds::GIRedemInvSelectAmountType, dstrAmtType, idDataGroup, false, true, true, false);
   BFObjIter iterGIInvestmentDetails (*this, idDataGroup, false);
   while (!iterGIInvestmentDetails.end())
   {
      GIInvestmentDetails *pGIInvestmentDetails = dynamic_cast<GIInvestmentDetails*> (iterGIInvestmentDetails.getObject()); 
      pGIInvestmentDetails->setField(ifds::SelInvAmtType, dstrAmtType, idDataGroup, false);
      ++iterGIInvestmentDetails;
   }

}
//*******************************************************************************
SEVERITY GIInvestmentDetailsList::doApplyRelatedChanges ( const BFFieldId &idField, 
                                                        const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ));
   setFieldUpdated (idField, idDataGroup, false);
   if(idField == ifds::GIRedemInvSelectAmountType)
   {
      DString dstGIRedemInvSelectAmountType;
      getField(ifds::GIRedemInvSelectAmountType, dstGIRedemInvSelectAmountType, idDataGroup);

      BFObjIter iterGIInvestmentDetails (*this, idDataGroup, false);
      while (!iterGIInvestmentDetails.end())
      {
         GIInvestmentDetails *pGIInvestmentDetails = dynamic_cast<GIInvestmentDetails*> (iterGIInvestmentDetails.getObject()); 
         pGIInvestmentDetails->setField(ifds::SelInvAmtType, dstGIRedemInvSelectAmountType, idDataGroup, false);
         pGIInvestmentDetails->setField(ifds::IsInvSelected, I_("N"), idDataGroup, false);
         ++iterGIInvestmentDetails;
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
SEVERITY GIInvestmentDetailsList::doValidateAll (const BFDataGroupId& idDataGroup, 
                                               long lValidateGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );
   if(m_isTotalsCBO)
      return NO_SEVERITY;
				
   DString dstrGrossOrNet;
   DString dstrGIRedemInvSelectAmountType;
   DString dstrRedemOrder;
//   DString readOnly;
   DString dstrTradeAmountType;

   getField(ifds::GrossOrNet,                 dstrGrossOrNet,                 idDataGroup, false);
   getField(ifds::GIRedemInvSelectAmountType, dstrGIRedemInvSelectAmountType, idDataGroup, false);
   getParent()->getField(ifds::RedemOrder,    dstrRedemOrder,                 idDataGroup, false);
   getParent()->getField(ifds::AmtType,       dstrTradeAmountType,            idDataGroup, false);
//   getField(ifds::ReadOnly,                   readOnly,                       idDataGroup, false);

   if(I_("FM") == dstrRedemOrder || I_("P") == dstrTradeAmountType)// == readOnly == I_("Y"))
   {
      return GETCURRENTHIGHESTSEVERITY();
   }


   if(dstrGrossOrNet == I_("N") &&
      dstrGIRedemInvSelectAmountType  == I_("D") &&
      dstrRedemOrder != I_("") &&
      dstrRedemOrder != I_("FM"))
   {
      int numSelected = 0;
	  bool bIsInvSelected = false;
      
      BFObjIter iterGIInvestmentDetails (*this, idDataGroup, false);
      while (!iterGIInvestmentDetails.end())
      {
         GIInvestmentDetails *pGIInvestmentDetails = dynamic_cast<GIInvestmentDetails*> (iterGIInvestmentDetails.getObject()); 
         if(pGIInvestmentDetails)
         {
            DString dstrIsInvSelected;
            pGIInvestmentDetails->getField(ifds::IsInvSelected, dstrIsInvSelected, idDataGroup, false);
            if(dstrIsInvSelected == I_("Y"))
			{
               numSelected++;
			   bIsInvSelected = true;
			}
         }
         ++iterGIInvestmentDetails;
      }
      if(numSelected != 1)
      {
         ADDCONDITIONFROMFILE( CND::ERR_GI_NET_REDEMPTION_CAN_USE_ONLY_ONE_INVESTMENT);
      }
	  if( !bIsInvSelected )
      {
         ADDCONDITIONFROMFILE( CND::ERR_NO_INVESTMENT_SETUP);
      }
   }



   if(//(dstrGrossOrNet == I_("Y") || dstrGrossOrNet == I_("N")) &&
      I_("P") != dstrTradeAmountType &&
//      readOnly != I_("Y") &&
//      dstrGIRedemInvSelectAmountType  == I_("D") &&
      dstrRedemOrder != I_("") && dstrRedemOrder != I_("FM"))
   {
      DString dstrTradeAmount;
	  bool bIsInvSelected = false;
      
      getField(ifds::TradeAmount, dstrTradeAmount, idDataGroup, false);
      BigDecimal tradeAmount(dstrTradeAmount);
      BigDecimal totalAmount(0);

  //    if(tradeAmount != BIGDEC_ZERO) // check trade amount not to be 0
  //    {

         BFObjIter iterGIInvestmentDetails (*this, idDataGroup, false);

         while (!iterGIInvestmentDetails.end())
         {
            GIInvestmentDetails *pGIInvestmentDetails = dynamic_cast<GIInvestmentDetails*> (iterGIInvestmentDetails.getObject()); 
            if(pGIInvestmentDetails)
            {
               DString dstrIsInvSelected;
               DString dstrSelInvAmount;
               pGIInvestmentDetails->getField(ifds::IsInvSelected, dstrIsInvSelected, idDataGroup, false);
  
               if(dstrGIRedemInvSelectAmountType == I_("D"))
                  pGIInvestmentDetails->getField(ifds::SelInvAmount, dstrSelInvAmount, idDataGroup, false);
               else
                  pGIInvestmentDetails->getField(ifds::PrincRedeemed, dstrSelInvAmount, idDataGroup, false);
//               pGIInvestmentDetails->getField(ifds::SelInvAmount, dstrSelInvAmount, idDataGroup, false);

               if(dstrIsInvSelected == I_("Y"))
               {
                  BigDecimal currAmount(dstrSelInvAmount);
                  totalAmount += currAmount;
				  bIsInvSelected = true;
               }
            }
            ++iterGIInvestmentDetails;
         }
         if(totalAmount != tradeAmount)
         {
            ADDCONDITIONFROMFILE( CND::ERR_GI_SELECTED_AMOUNT_NOT_TRADE_AMOUNT);
         }
		 if( !bIsInvSelected || ((totalAmount == 0 ) && (tradeAmount == 0)))
		 {
             ADDCONDITIONFROMFILE( CND::ERR_NO_INVESTMENT_SETUP);
		 }
 //     }
   }

   if(dstrGrossOrNet == I_("Y") &&
      dstrGIRedemInvSelectAmountType  == I_("A") &&
      dstrRedemOrder != I_("") &&
      dstrRedemOrder != I_("FM"))
   {
      DString dstrTradeAmount;
	  bool bIsInvSelected = false;
      
      getField(ifds::TradeAmount, dstrTradeAmount, idDataGroup, false);
      BigDecimal tradeAmount(100);
      BigDecimal totalAmount(0);

      BFObjIter iterGIInvestmentDetails (*this, idDataGroup, false);

      while (!iterGIInvestmentDetails.end())
      {
         GIInvestmentDetails *pGIInvestmentDetails = dynamic_cast<GIInvestmentDetails*> (iterGIInvestmentDetails.getObject()); 
         if(pGIInvestmentDetails)
         {
            DString dstrIsInvSelected;
            DString dstrSelInvAmount;
            pGIInvestmentDetails->getField(ifds::IsInvSelected, dstrIsInvSelected, idDataGroup, false);
            pGIInvestmentDetails->getField(ifds::SelInvAmount, dstrSelInvAmount, idDataGroup, false);

            if(dstrIsInvSelected == I_("Y"))
            {
			   bIsInvSelected = true;
               BigDecimal currAmount(dstrSelInvAmount);
               totalAmount += currAmount;
               DString dstrPrincRedeemed;
               DString dstrPrincipal;
               pGIInvestmentDetails->getField(ifds::PrincRedeemed, dstrPrincRedeemed, idDataGroup, false);
               pGIInvestmentDetails->getField(ifds::Principal, dstrPrincipal, idDataGroup, false);
               BigDecimal bdPrincRedeemed(dstrPrincRedeemed);
               BigDecimal bdPrincipal(dstrPrincipal);
               if(bdPrincRedeemed > bdPrincipal)
               {
                  ADDCONDITIONFROMFILE(CND::ERR_AMOUNT_EXCEEDS_PRINCIPAL);    
               }
            }
         }
         ++iterGIInvestmentDetails;
      }
      if(totalAmount != tradeAmount)
      {
         ADDCONDITIONFROMFILE( CND::ERR_GI_SELECTED_TOTAL_NOT_100);
      }
      if( !bIsInvSelected || ((totalAmount == 0 ) && (tradeAmount == 0)))
	  {
		ADDCONDITIONFROMFILE( CND::ERR_NO_INVESTMENT_SETUP);
	  }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY GIInvestmentDetailsList::doValidateField ( const BFFieldId &idField, 
                                                  const DString &strValue, 
                                                  const BFDataGroupId &idDataGroup) 
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
	                       I_("doValidateField"));

   if (idField == ifds::InvestmentHistoryFund)
   {
      FundMasterList *pFundMasterList (NULL);
      if (!strValue.empty())
      {
         if ( getMgmtCo().getFundMasterList (pFundMasterList) <= WARNING && 
              pFundMasterList)
         {
            if (!pFundMasterList->IsFundExist (strValue, idDataGroup))
            {
               ADDCONDITIONFROMFILE (CND::ERR_INVALID_FUND_CLASS_CODES);
            }
         }
      }
   }
   else if(idField == ifds::InvestmentHistoryClass)
   {
      DString dstrFund;
      getField(ifds::InvestmentHistoryFund, dstrFund, idDataGroup, false);

      FundDetail *pFundDetail = NULL;
	  if(!strValue.empty())
	  {
		if (!dstrFund.empty() && !getWorkSession().getFundDetail (  dstrFund,
																	strValue,
																	idDataGroup,
																	pFundDetail) ||
			!pFundDetail)
		{
			ADDCONDITIONFROMFILE (CND::ERR_INVALID_FUND_CLASS_CODES);
		}
	  }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY GIInvestmentDetailsList::calculateTotals( GIInvestmentDetailsList& totalsList, const BFDataGroupId &idDataGroup) 
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("calculateTotals"));

   GIInvestmentDetails* totalsCBO = NULL;
   BFObjIter totalsIter (totalsList, idDataGroup, true);
   while (!totalsIter.end())
   {
      totalsCBO = dynamic_cast <GIInvestmentDetails*> (totalsIter.getObject());
      break;
   }
   
   if(totalsCBO != NULL)
   {
      BigDecimal bdPrincRedeemed(0);
      BigDecimal bdAccruedInterest(0);
      BigDecimal bdAdminFee(0);
      BigDecimal bdMVA(0);
      BigDecimal bdAmountNet(0);
      BigDecimal bdSelInvAmount(0);
      
      BFObjIter iter (*this, idDataGroup, true);
      while (!iter.end())
      {
         GIInvestmentDetails* pGIInvestmentDetails = dynamic_cast <GIInvestmentDetails*> (iter.getObject());
         DString dstrPrincRedeemed;
         DString dstrAccruedInterest;
         DString dstrAdminFee;
         DString dstrMVA;
         DString dstrAmountNet;
         DString dstrSelInvAmount;
         
         if(pGIInvestmentDetails != NULL)
         {
            pGIInvestmentDetails->getField(ifds::PrincRedeemed,     dstrPrincRedeemed,    idDataGroup, false);
            pGIInvestmentDetails->getField(ifds::AccruedInterest,   dstrAccruedInterest,  idDataGroup, false);
            pGIInvestmentDetails->getField(ifds::AdminFee,          dstrAdminFee,         idDataGroup, false);
            pGIInvestmentDetails->getField(ifds::MVA,               dstrMVA,              idDataGroup, false);
            pGIInvestmentDetails->getField(ifds::AmountNet,         dstrAmountNet,        idDataGroup, false);
            pGIInvestmentDetails->getField(ifds::SelInvAmount,      dstrSelInvAmount,     idDataGroup, false);

            BigDecimal bdCurrPrincRedeemed   = DSTCommonFunctions::convertToBigDecimal (dstrPrincRedeemed);
            BigDecimal bdCurrAccruedInterest = DSTCommonFunctions::convertToBigDecimal (dstrAccruedInterest);
            BigDecimal bdCurrAdminFee        = DSTCommonFunctions::convertToBigDecimal (dstrAdminFee);
            BigDecimal bdCurrMVA             = DSTCommonFunctions::convertToBigDecimal (dstrMVA);
            BigDecimal bdCurrAmountNet       = DSTCommonFunctions::convertToBigDecimal (dstrAmountNet);
            BigDecimal bdCurrSelInvAmount    = DSTCommonFunctions::convertToBigDecimal (dstrSelInvAmount);



            bdPrincRedeemed      += bdCurrPrincRedeemed;
            bdAccruedInterest    += bdCurrAccruedInterest;
            bdAdminFee           += bdCurrAdminFee;
            bdMVA                += bdCurrMVA;
            bdAmountNet          += bdCurrAmountNet;
            bdSelInvAmount       += bdCurrSelInvAmount;
         }
         ++iter;
      }
      totalsCBO->setField(ifds::PrincRedeemed,    bdPrincRedeemed.asDString(),     idDataGroup, false);
      totalsCBO->setField(ifds::AccruedInterest,  bdAccruedInterest.asDString(),   idDataGroup, false);
      totalsCBO->setField(ifds::AdminFee,         bdAdminFee.asDString(),          idDataGroup, false);
      totalsCBO->setField(ifds::MVA,              bdMVA.asDString(),               idDataGroup, false);
      totalsCBO->setField(ifds::AmountNet,        bdAmountNet.asDString(),         idDataGroup, false);
      totalsCBO->setField(ifds::SelInvAmount,     bdSelInvAmount.asDString(),      idDataGroup, false);

   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/GIInvestmentDetailsList.cpp-arc  $
// 
//    Rev 1.19   01 Aug 2012 17:06:14   if991250
// IN3045636: SEnding Trade Date in view 421
// 
//    Rev 1.18   Jun 22 2012 06:04:24   kitticha
// IN 2957854 - P0186477_FN05_03.
// 
//    Rev 1.17   Jun 08 2012 14:08:02   jankovii
// IN 2957854 - P0186477_FN05_03_Same transno. in distrib-delt to be used & changes to misc-info
// 
//    Rev 1.16   May 16 2012 11:19:34   if991250
// IN2951488 - GI Money out
// 
//    Rev 1.15   May 01 2012 09:23:46   if991250
// GI Money Out - clearing the calculated amounts when the Investment row is unselected.
// 
//    Rev 1.14   Apr 26 2012 15:48:36   if991250
// Money out refresh fees on supress changes
// 
//    Rev 1.13   Apr 26 2012 11:06:38   if991250
// Sending GrossNet and TradeAmount to vw 421 in inquiry modes
// 
//    Rev 1.12   Apr 25 2012 18:15:44   if991250
// Money Out - sending SuppressMVA and Suppress Admin fee for investment inquiry and pending trade
// 
//    Rev 1.11   Apr 23 2012 13:24:42   if991250
// GI Money Out - Populating the correct amtType for Percent/Allocation pending trades
// 
//    Rev 1.10   Mar 21 2012 16:12:28   if991250
// IN 2885623 - GI Money Out - Error handling
// 
//    Rev 1.9   Mar 20 2012 16:41:48   if991250
// IN 2885623 - GI Money Oout
// 
//    Rev 1.8   Mar 15 2012 17:59:06   if991250
// IN 2879297: Money Out
// 
//    Rev 1.7   Mar 12 2012 18:11:14   if991250
// GI Money Out
// 
//    Rev 1.6   Mar 09 2012 17:45:50   if991250
// GIInvestmentDetails
// 
//    Rev 1.5   Mar 08 2012 17:47:02   if991250
// GI Money Out
// 
//    Rev 1.3   Mar 08 2012 09:58:02   if991250
// GI Money Out
// 
//    Rev 1.2   Feb 22 2012 17:03:56   if991250
// updated InvestmentHistorySearch
// 
//    Rev 1.1   Jan 26 2012 14:48:36   if991250
// Added GIInvestmentDetails (cpp and hpp)
// 
//    Rev 1.0   Jan 16 2012 15:26:26   if991250
// Initial revision.
// 
// 
*/
