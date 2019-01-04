//********************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2010 By International Financial Data Services.
//
//
//********************************************************************************
//
// ^FILE   : GIInvestmentDetails.cpp
// ^AUTHOR : 
// ^DATE   : 
//
//********************************************************************************
#include "stdafx.h"
#include "GIInvestmentDetails.hpp"
#include "GIInvestmentDetailsList.hpp"

#include <ifastdataimpl\dse_dstc0421_vw.hpp>

namespace
{
   const I_CHAR * const CLASSNAME				= I_( "GIInvestmentDetails" );

   const I_CHAR * const SEARCHALL				= I_( "ALL" );	   //I_( "AL" ); //All
   const I_CHAR * const SEARCH_INV_NUM			= I_( "INVNUM" );  //I_( "IN" ); //Investment Number
   const I_CHAR * const SEARCH_INV_STATUS		= I_( "INVSTAT" ); //I_( "IS" ); //Investment Status

   const I_CHAR * const STATUS_ACTIVE			= I_( "ACTIVE" );
   const I_CHAR * const STATUS_MATURED			= I_( "MATURED" );
   const I_CHAR * const STATUS_CANCELLED		= I_( "CANCELLED" );
}
  
namespace CND
{  
   extern const long ERR_AMOUNT_EXCEEDS_PRINCIPAL;
   extern const long ERR_VALUE_BETWEEN_0_AND_100;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId Selected;
   extern CLASS_IMPORT const BFDecimalFieldId Amount;
   extern CLASS_IMPORT const BFTextFieldId RecordType;
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFTextFieldId GrossOrNet;
   extern CLASS_IMPORT const BFTextFieldId RedemOrder;
   extern CLASS_IMPORT const BFTextFieldId SuppressMVA;
   extern CLASS_IMPORT const BFTextFieldId SuppressAdmin;
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFDecimalFieldId TradeAmount;
}

namespace TRADETYPE
{
   extern CLASS_EXPORT I_CHAR * const EXCHANGE;
   extern CLASS_IMPORT I_CHAR * const REDEMPTION;
   extern CLASS_IMPORT I_CHAR * const TRANSFER;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
	// Field DD Id,                          State Flags, Group Flags 
   { ifds::RecordType,                      BFCBO::NONE,		0},
   { ifds::IntInvestUUID,                   BFCBO::NONE,		0},
	{ ifds::Fund,                            BFCBO::NONE,		0},
	{ ifds::Class,                           BFCBO::NONE,		0},
	{ ifds::TransNum,                        BFCBO::NONE,		0},
	{ ifds::TransId,                         BFCBO::NONE,		0},
	{ ifds::InvHisNumber,                    BFCBO::NONE,		0},
	{ ifds::InvHisStatus,                    BFCBO::NONE,		0},
	{ ifds::InvHisIntCalcMthd,               BFCBO::NONE,		0},
	{ ifds::InvHisIntRateType,               BFCBO::NONE,		0}, 
	{ ifds::InvHisTerm,                      BFCBO::NONE,		0},
	{ ifds::InvHisIntRate,                   BFCBO::NONE,		0},
	{ ifds::InvHisDepDate,                   BFCBO::NONE,		0},
	{ ifds::InvHisMatDate,                   BFCBO::NONE,		0},
	{ ifds::InvHisPrincipal,                 BFCBO::NONE,		0},
	{ ifds::InvHisIntFreq,                   BFCBO::NONE,		0},
	{ ifds::InvHisCurMktVal,                 BFCBO::NONE,		0},
	{ ifds::InvHisLastIntCrdDate,            BFCBO::NONE,		0},
	{ ifds::InvHisAcurdToDate,               BFCBO::NONE,		0},
	{ ifds::ModDate,                         BFCBO::NONE,		0},
	{ ifds::ModUser,                         BFCBO::NONE,		0},
	{ ifds::Username,                        BFCBO::NONE,		0},
	{ ifds::Version,                         BFCBO::NONE,		0},
   { ifds::InvHisLotId,                     BFCBO::NONE,		0},
   { ifds::InvHisInvestId,                  BFCBO::NONE,		0},
	{ ifds::Principal,                       BFCBO::NONE,		0}, 
	{ ifds::MarketValue,                     BFCBO::NONE,		0},
	{ ifds::ValueAtMaturity,                 BFCBO::NONE,		0},
	{ ifds::SelInvAmtType,                   BFCBO::NONE,		0},
	{ ifds::SelInvAmount,                    BFCBO::NONE,		0},
	{ ifds::PrincRedeemed,                   BFCBO::NONE,		0},
	{ ifds::AccruedInterest,                 BFCBO::NONE,		0},
	{ ifds::AdminFee,                        BFCBO::NONE,		0},
	{ ifds::MVA,                             BFCBO::NONE,		0},  
	{ ifds::AmountNet,                       BFCBO::NONE,		0},
	{ ifds::InvSummId,                       BFCBO::NONE,		0},
	{ ifds::IsInvSelected,                   BFCBO::NONE,		0},
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
GIInvestmentDetails::GIInvestmentDetails( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}

//******************************************************************************
GIInvestmentDetails::~GIInvestmentDetails()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}  

//******************************************************************************
SEVERITY GIInvestmentDetails::init (const BFData &data)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );	

   attachDataObject (const_cast<BFData&>(data), false); 

   DString isSelected;
   getField(ifds::IsInvSelected, isSelected, BF::HOST);
   
   if(I_("N") == isSelected)
   {
      setFieldReadOnly (ifds::SelInvAmount, BF::HOST, true);
   }
   else if(I_("Y") == isSelected)
   {
      DString transType;
      if(getParent())
         getParent()->getField(ifds::TransType, transType, BF::HOST, false);
      
      if(transType != TRADETYPE::TRANSFER)
         setFieldReadOnly (ifds::SelInvAmount, BF::HOST, false);
   } 

   return(GETCURRENTHIGHESTSEVERITY());
}

SEVERITY GIInvestmentDetails::calculateFees(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("calculateFees"));

   GIInvestmentDetailsList* pGIInvestmentDetailsList = (GIInvestmentDetailsList*)getParent();
   
   DString dstrAccountNum;
   DString dstrEffDate;
   DString dstrGrossNet; 
   DString dstrRedemOrder; 
   DString dstrSuppressMVA; 
   DString dstrSuppressAdmin;
   DString dstrTradeAmount;

   pGIInvestmentDetailsList->getField(ifds::AccountNum,     dstrAccountNum,      idDataGroup);
   pGIInvestmentDetailsList->getField(ifds::EffectiveDate,  dstrEffDate,         idDataGroup);
   pGIInvestmentDetailsList->getField(ifds::GrossOrNet,     dstrGrossNet,        idDataGroup); 
   pGIInvestmentDetailsList->getField(ifds::RedemOrder,     dstrRedemOrder,      idDataGroup); 
   pGIInvestmentDetailsList->getField(ifds::SuppressMVA,    dstrSuppressMVA,     idDataGroup); 
   pGIInvestmentDetailsList->getField(ifds::SuppressAdmin,  dstrSuppressAdmin,   idDataGroup);
   pGIInvestmentDetailsList->getField(ifds::TradeAmount,    dstrTradeAmount,     idDataGroup);
   
   if(dstrAccountNum != I_(""))
   {
      calculate(dstrAccountNum, dstrEffDate, dstrGrossNet, dstrRedemOrder, dstrSuppressMVA, 
                     dstrSuppressAdmin, dstrTradeAmount, idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY GIInvestmentDetails::doApplyRelatedChanges ( const BFFieldId &idField, 
                                          const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doApplyRelatedChanges"));
   if (idField == ifds::IsInvSelected)
   {
      DString isSelected;
      getField(ifds::IsInvSelected, isSelected, idDataGroup);
      if(I_("N") == isSelected)
      {
         setFieldReadOnly (ifds::SelInvAmount, idDataGroup, true);
         setField (ifds::SelInvAmount, I_("0"), idDataGroup, true);

         setField (ifds::PrincRedeemed,   I_("0"), idDataGroup, true);
         setField (ifds::AccruedInterest, I_("0"), idDataGroup, true);
         setField (ifds::AdminFee,        I_("0"), idDataGroup, true);
         setField (ifds::MVA,             I_("0"), idDataGroup, true);
         setField (ifds::AmountNet,       I_("0"), idDataGroup, true);

      }
      else if(I_("Y") == isSelected)
      {
         DString transType;
         if(getParent())
            getParent()->getField(ifds::TransType, transType, idDataGroup, false);
         
         if(transType != TRADETYPE::TRANSFER)
         {
            setFieldReadOnly (ifds::SelInvAmount, idDataGroup, false);

            DString dstSelInvAmount;
            getField(ifds::SelInvAmount, dstSelInvAmount, idDataGroup);
            if(dstSelInvAmount != I_("0"))
            {
               calculateFees(idDataGroup);
            }
         }
         else
         {
            DString principal;
            getField(ifds::InvHisPrincipal, principal, idDataGroup, false);
            setField(ifds::SelInvAmount, principal, idDataGroup, false);
         }
//         setFieldReadOnly (ifds::SelInvAmount, idDataGroup, false);
  
      } 
   }
   else if (idField == ifds::SelInvAmount)
   {
      calculateFees(idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

SEVERITY GIInvestmentDetails::calculate(const DString& dstrAccountNum, 
                                        const DString& dstrEffDate, 
                                        const DString& dstrGrossNet, 
                                        const DString& dstrRedemOrder, 
                                        const DString& dstrSuppressMVA, 
                                        const DString& dstrSuppressAdmin,
                                        const DString& dstrTradeAmount,
                                        const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("calculate"));


//InvestmentHistorySearch = “SelInvCal”, 
//Account, 
//Fund, 
//Class, 
//EffectiveDate, 
//GrossNet (From trade), 
//RedemOrder (From trade), 
//SelInvAmtType, 
//SelInvAmount, 
//SuppressMVA, 
//SuppressAdmin, 
//IntHisInvestId (From selected record) 
//InvSummId (From selected record).



	DString dstrTransId;
	DString dstrFundFrom;
	DString dstrClassFrom;
	DString dstrInvNum;
	DString dstrInvStatus;
	DString dstrSelInvAmtType;
   DString dstrSelInvAmount;
   DString dstrInvHisInvestId; 
   DString dstrInvSummId;

   getField(ifds::TransId,          dstrTransId,         idDataGroup);
   getField(ifds::Fund,             dstrFundFrom,        idDataGroup);
   getField(ifds::Class,            dstrClassFrom,       idDataGroup);
   getField(ifds::SelInvAmtType,    dstrSelInvAmtType,   idDataGroup);
   getField(ifds::SelInvAmount,     dstrSelInvAmount,    idDataGroup);
   getField(ifds::InvHisInvestId,   dstrInvHisInvestId,  idDataGroup); 
   getField(ifds::InvSummId,        dstrInvSummId,       idDataGroup);

   DString dstIsInvSelected;
   getField(ifds::IsInvSelected,    dstIsInvSelected,       idDataGroup);

   if(dstIsInvSelected == I_("Y"))
   {
      GIInvestmentDetailsList lGIInvestmentDetailsList(*this);
      SEVERITY severity = lGIInvestmentDetailsList.initCalc (dstrAccountNum, dstrTransId, dstrFundFrom, 
         dstrClassFrom, dstrEffDate, dstrGrossNet, dstrRedemOrder, dstrSelInvAmtType, dstrSelInvAmount, 
         dstrSuppressMVA, dstrSuppressAdmin, dstrInvHisInvestId, dstrInvSummId, dstrTradeAmount);

      BFObjIter iterGIInvestmentDetails (lGIInvestmentDetailsList, idDataGroup, false);
      while (!iterGIInvestmentDetails.end())
      {
         GIInvestmentDetails *pGIInvestmentDetails = dynamic_cast<GIInvestmentDetails*> (iterGIInvestmentDetails.getObject()); 
         if(pGIInvestmentDetails != NULL)
         {
            DString dstrPrincRedeemed;
            DString dstrAccruedInterest;
            DString dstrAdminFee;
            DString dstrMVA;
            DString dstrAmountNet;
            
            pGIInvestmentDetails->getField(ifds::PrincRedeemed,     dstrPrincRedeemed,    idDataGroup, false);
            pGIInvestmentDetails->getField(ifds::AccruedInterest,   dstrAccruedInterest,  idDataGroup, false);
            pGIInvestmentDetails->getField(ifds::AdminFee,          dstrAdminFee,         idDataGroup, false);
            pGIInvestmentDetails->getField(ifds::MVA,               dstrMVA,              idDataGroup, false);
            pGIInvestmentDetails->getField(ifds::AmountNet,         dstrAmountNet,        idDataGroup, false);

            setField(ifds::PrincRedeemed,     dstrPrincRedeemed,    idDataGroup, false);
            setField(ifds::AccruedInterest,   dstrAccruedInterest,  idDataGroup, false);
            setField(ifds::AdminFee,          dstrAdminFee,         idDataGroup, false);
            setField(ifds::MVA,               dstrMVA,              idDataGroup, false);
            setField(ifds::AmountNet,         dstrAmountNet,        idDataGroup, false);
         }      
         
         break;
      }

   }
   return GETCURRENTHIGHESTSEVERITY();

}

SEVERITY GIInvestmentDetails::doValidateField( const BFFieldId &fieldId,
                                    const DString& strValue,
                                    const BFDataGroupId& idDataGroup )
{ 
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

   if( fieldId == ifds::SelInvAmount)
   {
      DString dstrSelInvAmtType;
      getField(ifds::SelInvAmtType, dstrSelInvAmtType, idDataGroup, false);
      if(dstrSelInvAmtType == I_("D"))
      {
         BigDecimal bdAmount (strValue);

         DString dstrPrincipal;
         getField(ifds::Principal, dstrPrincipal, idDataGroup, false);
         BigDecimal bdPrincipal (dstrPrincipal);
         if(bdPrincipal < bdAmount)
         {
            ADDCONDITIONFROMFILE(CND::ERR_AMOUNT_EXCEEDS_PRINCIPAL);    
         }
      }
      
      if(dstrSelInvAmtType == I_("P") || dstrSelInvAmtType == I_("A"))
      {
         BigDecimal bd100Percent (I_("100"));
         BigDecimal bdAmount (strValue);
         if(bdAmount < BIGDEC_ZERO || bdAmount > bd100Percent)
         {
            ADDCONDITIONFROMFILE(CND::ERR_VALUE_BETWEEN_0_AND_100);
         }

      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/GIInvestmentDetails.cpp-arc  $
// 
//    Rev 1.9   May 16 2012 11:19:20   if991250
// IN2951488 - GI Money out
// 
//    Rev 1.8   May 01 2012 09:23:36   if991250
// GI Money Out - clearing the calculated amounts when the Investment row is unselected.
// 
//    Rev 1.7   Apr 25 2012 18:14:40   if991250
// Money Out - sending SuppressMVA and Suppress Admin fee for investment inquiry and pending trade
// 
//    Rev 1.6   Mar 20 2012 16:41:22   if991250
// IN 2885623 - GI Money Oout
// 
//    Rev 1.5   Mar 15 2012 17:58:22   if991250
// IN 2879297: Money Out
// 
//    Rev 1.4   Mar 12 2012 18:10:54   if991250
// GI Money Out
// 
//    Rev 1.3   Mar 09 2012 17:45:16   if991250
// GIInvestmentDetails
// 
//    Rev 1.2   Mar 08 2012 17:46:22   if991250
// GI Money Out
// 
//    Rev 1.1   Mar 08 2012 09:57:40   if991250
// GI Money Out
// 
//    Rev 1.0   Jan 26 2012 14:46:26   if991250
// Initial revision.
// 
*/
