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
//    Copyright 2003 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : TradingFeeRules.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : March, 2003
//
// ^CLASS    : TradingFeeRules
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "TradingFeeRules.hpp"
#include "fundfeelist.hpp"

namespace
{
   const I_CHAR * const CLASSNAME = I_( "TradingFeeRules" );
   const I_CHAR * const NO = I_( "N" );
   const I_CHAR * const YES = I_( "Y" );
}

namespace CND
{  // Conditions used
   extern const long ERR_FEE_MUST_BE_NUMERIC;
   extern const long ERR_NEGATIVE_FEE_NOT_ALLOW;
   extern const long ERR_FEE_LESS_OR_EQUAL_100;
   extern const long ERR_EXCHANGE_OUT_FEE_UNDER_MINIMUM;
   extern const long ERR_EXCHANGE_OUT_FEE_OVER_MAXIMUM;
   extern const long ERR_NEGATIVE_FEE_NOT_ALLOW;
   extern CLASS_IMPORT const long ERR_FEE_PARAMS_NOT_AVAILABLE;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FundCode;
   extern CLASS_IMPORT const BFTextFieldId ClassCode;
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFTextFieldId TradeType;
   extern CLASS_IMPORT const BFTextFieldId FeeCode;
   extern CLASS_IMPORT const BFDecimalFieldId MinFee;
   extern CLASS_IMPORT const BFDecimalFieldId MaxFee;
   extern CLASS_IMPORT const BFDecimalFieldId Rate;
   extern CLASS_IMPORT const BFTextFieldId FeeType;
   extern CLASS_IMPORT const BFTextFieldId FeeExists;
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const EXCHANGE_OUT;
   extern CLASS_IMPORT I_CHAR * const REDEMPTION;
   extern CLASS_IMPORT I_CHAR * const TRANSFER_OUT;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
//   Field DD Id,        State Flags,       Group Flags 
   { ifds::TradeType, BFCBO::NONE, 0 }, 
   { ifds::FeeCode, BFCBO::NONE, 0 }, 
   { ifds::MinFee, BFCBO::NONE, 0 }, 
   { ifds::MaxFee, BFCBO::NONE, 0 }, 
   { ifds::Rate, BFCBO::NONE, 0 }, 
   { ifds::FeeType, BFCBO::NONE, 0 }, 
   { ifds::FeeExists, BFCBO::NONE, 0 }, 
};


static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//****************************************************************************
SEVERITY TradingFeeRules::getExchangeOutFeeRules(BFAbstractCBO &cboParent, 
   TradingFeeRules*& rpTradingFeeRules,
   const BFFieldId& tradeFeeFieldId, const BFFieldId& tradeFeeTypeFieldId,
   const BFFieldId& fundCodeFieldId, const BFFieldId& classCodeFieldId,
   const BFFieldId& effectiveDateFieldId, const BFFieldId& accountNumFieldId,
   const BFFieldId& brokerFieldId, const BFFieldId& branchFieldId,
   const BFFieldId& slsrepFieldId,
   const BFDataGroupId& idDataGroup,
   bool ignoreFeeNotExists /*=true*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getExchangeOutFeeRules"));
   rpTradingFeeRules = new TradingFeeRules(cboParent);
   //Fee code in case of the exchange out fee is 44
   rpTradingFeeRules->init(TRADETYPE::EXCHANGE_OUT, I_("44"),
      tradeFeeFieldId, tradeFeeTypeFieldId,
      fundCodeFieldId, classCodeFieldId,
      effectiveDateFieldId, accountNumFieldId,
      brokerFieldId, branchFieldId, slsrepFieldId,
      idDataGroup, ignoreFeeNotExists);
   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************
SEVERITY TradingFeeRules::getERFeeRules(BFAbstractCBO &cboParent, 
      TradingFeeRules*& rpTradingFeeRules,
      const BFFieldId& tradeFeeFieldId, const BFFieldId& tradeFeeTypeFieldId,
      const BFFieldId& fundCodeFieldId, const BFFieldId& classCodeFieldId,
      const BFFieldId& effectiveDateFieldId, const BFFieldId& accountNumFieldId,
      const BFFieldId& brokerFieldId, const BFFieldId& branchFieldId,
      const BFFieldId& slsrepFieldId, 
      const BFDataGroupId& idDataGroup,
      bool ignoreFeeNotExists /*=true*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getERFeeRules"));
   rpTradingFeeRules = new TradingFeeRules(cboParent);
   //Fee code in case of the early redemption fee is 340
   rpTradingFeeRules->init(TRADETYPE::REDEMPTION, I_("340"),
      tradeFeeFieldId, tradeFeeTypeFieldId,
      fundCodeFieldId, classCodeFieldId,
      effectiveDateFieldId, accountNumFieldId,
      brokerFieldId, branchFieldId, slsrepFieldId,
      idDataGroup, ignoreFeeNotExists);
   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************
SEVERITY TradingFeeRules::getSTTRFeeRules(BFAbstractCBO &cboParent, 
      TradingFeeRules*& rpTradingFeeRules,
      const BFFieldId& tradeFeeFieldId, const BFFieldId& tradeFeeTypeFieldId,
      const BFFieldId& fundCodeFieldId, const BFFieldId& classCodeFieldId,
      const BFFieldId& effectiveDateFieldId, const BFFieldId& accountNumFieldId,
      const BFFieldId& brokerFieldId, const BFFieldId& branchFieldId,
      const BFFieldId& slsrepFieldId, 
      const BFDataGroupId& idDataGroup,
      bool ignoreFeeNotExists /*=true*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getSTTRFeeRules"));
   rpTradingFeeRules = new TradingFeeRules(cboParent);
   //Fee code in case of the short term transfer fee is 350
   rpTradingFeeRules->init(TRADETYPE::TRANSFER_OUT, I_("350"),
      tradeFeeFieldId, tradeFeeTypeFieldId,
      fundCodeFieldId, classCodeFieldId,
      effectiveDateFieldId, accountNumFieldId,
      brokerFieldId, branchFieldId, slsrepFieldId,
      idDataGroup, ignoreFeeNotExists);
   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************
SEVERITY TradingFeeRules::getWithdrawalFeeRules( const DString &dstrTransType,
		                                           const DString &dstrFeeCode,			 			  				  	                                               											          
											                TradingFeeRules*& rpTradingFeeRules,
												             const DString &dstrTradeFee, 
												             const DString &dstrTradeFeeType,
												             const DString &dstrFundCode, 
												             const DString &dstrClassCode,
												             const DString &dstrEffectiveDate, 
												             const DString &dstrAccountNum,
												             const DString &dstrBroker, 
												             const DString &dstrBranch,
												             const DString &dstrSlsrep, 
												             const BFDataGroupId& idDataGroup,
												             bool ignoreFeeNotExists )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getWithdrawalFeeRules("));   	
   			
   if ( !_pFundFeeList )
   {      
      DString dstrStopDate;
		DSTCommonFunctions::getFormat12319999Date( dstrStopDate );
      _pFundFeeList = new FundFeeList( *this );

      if ( _pFundFeeList->init( dstrFeeCode, 
			                       dstrFundCode, 
										  dstrClassCode, 
										  NULL_STRING,
                                dstrEffectiveDate, 
										  dstrAccountNum, 
										  I_("FindRecord"), 
										  NULL_STRING, 
										  NULL_STRING, 
										  NULL_STRING,
                                NULL_STRING, 
										  dstrStopDate, 
										  dstrBroker, 
										  NULL_STRING, 
										  dstrBranch, 
										  dstrSlsrep) <= WARNING)
      {
			_tradeType = dstrTransType;
         DString strMaxFee, strMinFee, strFeeRate, strFeeType;

         setField(ifds::FeeExists, I_("Y"), idDataGroup);
			
         _pFundFeeList->getField(ifds::MinFee, strMinFee, idDataGroup);
         setField(ifds::MinFee, strMinFee, idDataGroup);
         _pFundFeeList->getField(ifds::MaxFee, strMaxFee, idDataGroup);
         setField(ifds::MaxFee, strMaxFee, idDataGroup);
         _pFundFeeList->getField(ifds::Rate, strFeeRate, idDataGroup);
         setField(ifds::Rate, strFeeRate, idDataGroup);
         _pFundFeeList->getField(ifds::FeeType, strFeeType, idDataGroup);
         setField(ifds::FeeType, strFeeType, idDataGroup);         
			
      }
      else
      {
         int count = CONDITIONCOUNT();
         Condition   *c = NULL;
         for( int i = 0; i < count; i++ )
         {
            c = GETCONDITION( i );
            int condCode = c->getCode();
            if( condCode == CND::ERR_FEE_PARAMS_NOT_AVAILABLE )
            {
               CLEARCONDITION( i );
               setField( ifds::FeeExists, I_("N"), idDataGroup );
               break;
            }
         }         
      }
   }
   
   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************
TradingFeeRules::TradingFeeRules(BFAbstractCBO &parent)
: MFCanBFCbo(parent),
_tradeType(NULL_STRING),
_feeCode(NULL_STRING),
_tradeFeeFieldId(ifds::NullFieldId),
_tradeFeeTypeFieldId(ifds::NullFieldId),
_fundCodeFieldId(ifds::NullFieldId),
_classCodeFieldId(ifds::NullFieldId),
_effectiveDateFieldId(ifds::NullFieldId),
_accountNumFieldId(ifds::NullFieldId),
_brokerFieldId(ifds::NullFieldId),
_branchFieldId(ifds::NullFieldId),
_slsrepFieldId(ifds::NullFieldId),
_pFundFeeList(NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0, NULL );
}

//****************************************************************************
TradingFeeRules::~TradingFeeRules()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   if (_pFundFeeList)
   {
      delete _pFundFeeList;
   }
}     

//****************************************************************************
SEVERITY TradingFeeRules::init(const DString& strTradeType, const DString& strFeeCode,
   const BFFieldId& tradeFeeFieldId, const BFFieldId& tradeFeeTypeFieldId,
   const BFFieldId& fundCodeFieldId, const BFFieldId& classCodeFieldId,
   const BFFieldId& effectiveDateFieldId, const BFFieldId& accountNumFieldId,
   const BFFieldId& brokerFieldId, const BFFieldId& branchFieldId,
   const BFFieldId& slsrepFieldId, const BFDataGroupId& idDataGroup,
   bool ignoreFeeNotExists /*= true*/)

{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));
   _tradeType = strTradeType;
   _feeCode = strFeeCode;
   _tradeFeeFieldId = tradeFeeFieldId;
   _tradeFeeTypeFieldId = tradeFeeTypeFieldId;
   _fundCodeFieldId = fundCodeFieldId;
   _classCodeFieldId = classCodeFieldId;
   _effectiveDateFieldId = effectiveDateFieldId;
   _accountNumFieldId = accountNumFieldId;
   _brokerFieldId = brokerFieldId;
   _branchFieldId = branchFieldId;
   _slsrepFieldId = slsrepFieldId;
   initFeeDefaults(idDataGroup, ignoreFeeNotExists);
   return(GETCURRENTHIGHESTSEVERITY());
}


//****************************************************************************
SEVERITY TradingFeeRules::initFeeDefaults(const BFDataGroupId& idDataGroup, 
   bool ignoreFeeNotExists)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("initFeeDefaults"));
   if (!_pFundFeeList)
   {
      DString strFeeCode, strFundCode, strFundClass, strEffectiveDate, strAccountNum,
         strBroker, strBranch, strSlsRep, stopDate;

      getParent()->getField(_fundCodeFieldId , strFundCode, idDataGroup);
      getParent()->getField(_classCodeFieldId, strFundClass, idDataGroup);
      getParent()->getField(_effectiveDateFieldId, strEffectiveDate, idDataGroup);
      getParent()->getField(_accountNumFieldId, strAccountNum, idDataGroup);
      getParent()->getField(_brokerFieldId, strBroker, idDataGroup);
      getParent()->getField(_branchFieldId, strBranch, idDataGroup);
      getParent()->getField(_slsrepFieldId, strSlsRep, idDataGroup);
      DSTCommonFunctions::getFormat12319999Date(stopDate);
      _pFundFeeList = new FundFeeList(*this);

      if (_pFundFeeList->init(_feeCode, strFundCode, strFundClass, NULL_STRING,
         strEffectiveDate, strAccountNum, I_("FindRecord"), NULL_STRING, NULL_STRING, NULL_STRING,
         NULL_STRING, stopDate, strBroker, NULL_STRING, strBranch, strSlsRep) <= WARNING)
      {
         DString strMaxFee, strMinFee, strFeeRate, strFeeType;

         setField(ifds::FeeExists, I_("Y"), idDataGroup);
         _pFundFeeList->getField(ifds::MinFee, strMinFee, idDataGroup);
         setField(ifds::MinFee, strMinFee, idDataGroup);
         _pFundFeeList->getField(ifds::MaxFee, strMaxFee, idDataGroup);
         setField(ifds::MaxFee, strMaxFee, idDataGroup);
         _pFundFeeList->getField(ifds::Rate, strFeeRate, idDataGroup);
         setField(ifds::Rate, strFeeRate, idDataGroup);
         _pFundFeeList->getField(ifds::FeeType, strFeeType, idDataGroup);
         setField(ifds::FeeType, strFeeType, idDataGroup);         
      }
      else
      {
         int count = CONDITIONCOUNT();
         Condition   *c = NULL;
         for( int i = 0; i < count; i++ )
         {
            c = GETCONDITION( i );
            int condCode = c->getCode();
            if(condCode == CND::ERR_FEE_PARAMS_NOT_AVAILABLE)
            {
               CLEARCONDITION( i );
               setField(ifds::FeeExists, I_("N"), idDataGroup);
               break;
            }
         }         
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************
SEVERITY TradingFeeRules::validateTradingFee(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   if (feeExists(idDataGroup))
   {
      DString dstrTradeFee;
      //get the trading fee from the parent
      getParent()->getField(_tradeFeeFieldId, dstrTradeFee, idDataGroup);

      if(isDecimal(dstrTradeFee))
      {
         double dblTradeFee = DSTCommonFunctions::convertToDouble(dstrTradeFee);

         if(dblTradeFee >= 0)
         {
            DString strMaxFee, strMinFee;

            getField(ifds::MaxFee, strMaxFee, idDataGroup);
            getField(ifds::MinFee, strMinFee, idDataGroup);
            double dblMaxFee = DSTCommonFunctions::convertToDouble(strMaxFee);
            double dblMinFee = DSTCommonFunctions::convertToDouble(strMinFee);

            if(dblTradeFee <= dblMaxFee)
            {
               if(dblTradeFee >= dblMinFee)
               {
                  DString dstrFeeType;
                  getParent()->getField(_tradeFeeTypeFieldId, dstrFeeType, idDataGroup); 

                  if(dstrFeeType.strip() == NO && dblTradeFee > 100)
                  {
                     ADDCONDITIONFROMFILE(CND::ERR_FEE_LESS_OR_EQUAL_100);
                  }
               }
               else
               {
                  ADDCONDITIONFROMFILE(CND::ERR_EXCHANGE_OUT_FEE_UNDER_MINIMUM);
               }
            }
            else
            {
               ADDCONDITIONFROMFILE(CND::ERR_EXCHANGE_OUT_FEE_OVER_MAXIMUM);
            }
         }
         else
         {
            ADDCONDITIONFROMFILE(CND::ERR_NEGATIVE_FEE_NOT_ALLOW);
         }
      }
      else
      {
         ADDCONDITIONFROMFILE(CND::ERR_FEE_MUST_BE_NUMERIC);
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool TradingFeeRules::feeExists(const BFDataGroupId& idDataGroup)
{
   DString dstrFeeExists;

   getField(ifds::FeeExists, dstrFeeExists, idDataGroup);
   return dstrFeeExists == I_("Y");
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TradingFeeRules.cpp-arc  $
// 
//    Rev 1.12   Nov 14 2004 14:58:06   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.11   Dec 17 2003 09:38:58   VADEANUM
// PTS 10025195 - syncup from 54.1P - rewrote getWithdrawalFeeRules() to support Allocation Funds Fees validation.
// 
//    Rev 1.10   Dec 08 2003 15:28:52   popescu
// PTS 10023645, split commission re-work
// 
//    Rev 1.9   Jul 29 2003 11:09:20   VADEANUM
// PET 809 F05 - Withdrawal Fee support.
// 
//    Rev 1.8   Apr 08 2003 17:38:56   popescu
// Fixed PTS call 10015818
// 
//    Rev 1.7   Apr 04 2003 10:19:00   popescu
// split commsion work
// 
//    Rev 1.6   Mar 21 2003 21:07:10   PURDYECH
// Sync 1.1.1.0 back to trunk
// 
//    Rev 1.5   Mar 21 2003 15:47:10   popescu
// cahnged the way we get the defaults for stopdate
// 
//    Rev 1.4   Mar 21 2003 14:57:18   popescu
// read only fields bug fix
// 
//    Rev 1.3   Mar 20 2003 11:26:00   popescu
// Early redemption fee and short term transfer fee work
// 
//    Rev 1.2   Mar 19 2003 14:44:54   popescu
// Exchange Out fee automatic transfer, and Trad
// 
//    Rev 1.1   Mar 18 2003 21:10:44   popescu
// Exchange out fee work
// 
//    Rev 1.0   Mar 13 2003 15:24:04   popescu
// Initial revision.
 */

