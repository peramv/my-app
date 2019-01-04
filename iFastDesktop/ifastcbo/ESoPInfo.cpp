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
//    Copyright 2000 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : ESoPInfo.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 07/29/2000
//
// ^CLASS    : ESoPInfo
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "dstcommonfunction.hpp"
#include "esophistoricallist.hpp"
#include "esopinfo.hpp"
#include "mfaccount.hpp"
#include "fundmaster.hpp"
#include "fundmasterlist.hpp"
#include "funddetaillist.hpp"
#include "groupfundlist.hpp"
#include "groupfund.hpp"
#include "mgmtco.hpp"
#include <ifastdataimpl\dse_dstc0169_req.hpp>
#include <ifastdataimpl\dse_dstc0169_vw.hpp>
#include <ifastdataimpl\dse_dstc0168_req.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ESOP_INFO;
}

namespace  
{
   const I_CHAR * const CLASSNAME            = I_( "ESoPInfo" );
   const I_CHAR * const YES                  = I_( "Y" );
   const I_CHAR * const NO                   = I_( "N" );
   const I_CHAR * const ESOP_INVESTMENT      = I_( "D" );
   const I_CHAR * const ESOP_PARTICIPATION   = I_( "E" );
   const I_CHAR * const ACTIVE               = I_( "0" );
   const I_CHAR * const NON_ESOP             = I_( "9" );

}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FromFundNumber;
   extern CLASS_IMPORT const BFTextFieldId AcctStatus;
   extern CLASS_IMPORT const BFTextFieldId FundClass;
   extern CLASS_IMPORT const BFTextFieldId FundName;
   extern CLASS_IMPORT const BFTextFieldId ElongName1;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFTextFieldId TaxType;
   extern CLASS_IMPORT const BFTextFieldId AcctGroup;
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFTextFieldId StopPurchase;

}

namespace  CND
{
   extern CLASS_IMPORT const long ERR_DATA_NOT_FOUND;
   extern const long ERR_INVALID_NEGATIVE_AMOUNT;
   extern const long ERR_AMOUNT_EXCEED_MAX_LIMIT;

   extern const long ERR_INVALID_FUND_CLASS_CODES;
   extern const long ERR_INVALID_FUND_NUMBER;
   extern const long ERR_ESOP_INTERRUPT_DATE_BLANK;
   extern const long ERR_ESOP_INTERRUPT_DATE_INVALID;

}


const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//   Field DD Id,             State Flags,       Group Flags 
   { ifds::IFASNumber,        BFCBO::NONE,                 0 }, 
   { ifds::InitPurchDate,     BFCBO::NONE,                 0 }, 
   { ifds::BankEffectiveDate, BFCBO::NONE,                 0 }, 
   { ifds::AutoCreate,        BFCBO::NONE,                 0 }, 
   { ifds::FromFundNumber,    BFCBO::NONE,                 0 }, 
   { ifds::FundCode,          BFCBO::REQUIRED,             0 }, 
   { ifds::FundName,          BFCBO::NONE,                 0 }, 
   { ifds::ClassCode,         BFCBO::REQUIRED,             0 }, 
   { ifds::Amount,            BFCBO::REQUIRED,             0 }, 
   { ifds::Currency,          BFCBO::REQUIRED,             0 }, 
   { ifds::InterruptDate,     BFCBO::NONE,                 0 }, 
   { ifds::InterruptCode,     BFCBO::NONE,                 0 }, 
   { ifds::FundClass,         BFCBO::IMMEDIATE_VALIDATION, 0 }, 
   { ifds::ESoPStatus,        BFCBO::READ_ONLY,            0 }, 
   { ifds::InitInvestDate,    BFCBO::READ_ONLY,            0 }, 
   { ifds::ContStartDate,     BFCBO::READ_ONLY,            0 }, 
   { ifds::ContEndDate,       BFCBO::READ_ONLY,            0 }, 
   { ifds::BlockStartDate,    BFCBO::READ_ONLY,            0 }, 
   { ifds::BlockEndDate,      BFCBO::READ_ONLY,            0 }, 
   { ifds::InactiveDate,      BFCBO::READ_ONLY,            0 }, 
   { ifds::ContExpireDate,    BFCBO::READ_ONLY,            0 }, 

   //fields required for update
   { ifds::ShrNum,            BFCBO::NONE,                 0 }, 
   { ifds::BrokerCode,        BFCBO::NONE,                 0 }, 
   { ifds::BranchCode,        BFCBO::NONE,                 0 }, 
   { ifds::SalesRepCode,      BFCBO::NONE,                 0 }, 
   { ifds::LastName,          BFCBO::NONE,                 0 }, 
   { ifds::FirstName,         BFCBO::NONE,                 0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//****************************************************************************
ESoPInfo::ESoPInfo( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL );
   addCrossEdit(ifds::FundClass, ifds::FundCode);
   addCrossEdit(ifds::FundClass, ifds::ClassCode); 
}

//****************************************************************************
ESoPInfo::~ESoPInfo()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}   

//****************************************************************************

SEVERITY ESoPInfo::init( const BFDataGroupId& idDataGroup, const DString& dstrTrack /*= I_("N")*/,
                         const DString& dstrPageName /*= NULL_STRING*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );



   BFData queryData(ifds::DSTC0169_REQ);
   DString strAccountNum, mgmtCoIdOut;
   getParent()->getField(ifds::AccountNum, strAccountNum, BF::HOST, false);
   queryData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   queryData.setElementValue( ifds::AccountNum, strAccountNum );
   queryData.setElementValue( ifds::Track, dstrTrack );
   queryData.setElementValue( ifds::Activity, dstrPageName );

   if( ReceiveData( DSTC_REQUEST::ESOP_INFO, queryData, ifds::DSTC0169_VW, DSTCRequestor( getSecurity(), true, true ) ) > WARNING )
   {
      int count = CONDITIONCOUNT();
      Condition   *c = NULL;
      for( int i = 0; i < count; i++ )
      {
         c = GETCONDITION( i );
         int condCode = c->getCode();
         if( condCode == CND::ERR_DATA_NOT_FOUND )
         {
            CLEARCONDITION( i )
            break;
         }
      }
      if( GETCURRENTHIGHESTSEVERITY() <= WARNING )//Data not found and no other severe errors : create a new ESoPInfo
         initNew(BF::HOST);
      else
         return(GETCURRENTHIGHESTSEVERITY());//something is really wrong here
   }

   DString strStatus;
   getField(ifds::ESoPStatus, strStatus, BF::HOST, false);
   if( strStatus.strip() == NON_ESOP )
      setAllFieldsReadOnly(BF::HOST);
   //the following two lines shouldn't be here, but BFProperties doesn't work well, yet
   else
      setFieldsReadOnly(BF::HOST);

   //fund number and name don't come from backend
   setFundNumber(BF::HOST);
   setFundName(BF::HOST);

   clearUpdatedFlags( BF::HOST, false );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY ESoPInfo::initNew(const BFDataGroupId& idDataGroup, const DString& dstrTrack /*= I_("N")*/,
                           const DString& dstrPageName /*= NULL_STRING*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   setObjectNew();
   doInitWithDefaultValues( idDataGroup );
   clearUpdatedFlags( idDataGroup, false );

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

void ESoPInfo::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{
   DString strAcctCurrency, strEffectiveDate, strTaxType, strCurrBussDate;
   getParent()->getField(ifds::Currency, strAcctCurrency, idDataGroup, false);
   getWorkSession().getOption( ifds::CurrBusDate, strCurrBussDate, idDataGroup, false);
   setFieldNoValidate(ifds::ESoPStatus, ACTIVE, idDataGroup, false, true, true);
   setFieldNoValidate(ifds::AutoCreate, NO, idDataGroup, false, true, true);
   setFieldNoValidate(ifds::Currency, strAcctCurrency, idDataGroup, false, true, true);
   //setFieldNoValidate(DBR::HistoricalInfoExist, NO, idDataGroup, false);


   getParent()->getField(ifds::TaxType, strTaxType, idDataGroup, false);

   int nMonth = DSTCommonFunctions::getMonthFromUnFormattedDate(strCurrBussDate);
   int nYear = DSTCommonFunctions::getYearFromUnFormattedDate(strCurrBussDate);

   if( strTaxType.strip().upperCase() == ESOP_PARTICIPATION )
   {
      //BlockStartDate
      DString strBeginOfYear;
      DSTCommonFunctions::getBeginOfMonthUnFormattedDate(1, nYear, strBeginOfYear);
      setFieldNoValidate(ifds::BlockStartDate, strBeginOfYear, idDataGroup, false, true, true);

      //BlockEndDate
      DString strEndOfMonthFiveYearsAfter;
      DSTCommonFunctions::getEndOfMonthUnFormattedDate(nMonth, nYear+5, strEndOfMonthFiveYearsAfter);
      setFieldNoValidate(ifds::BlockEndDate, strEndOfMonthFiveYearsAfter, idDataGroup, false, true, true);
   }


   //BankEffectiveDate
   getParent()->getField(ifds::EffectiveDate, strEffectiveDate, idDataGroup, false);
   nMonth = DSTCommonFunctions::getMonthFromUnFormattedDate(strEffectiveDate);
   nYear = DSTCommonFunctions::getYearFromUnFormattedDate(strEffectiveDate);

   DString strBeginOfNextMonth;
   if( nMonth == 12 )
      DSTCommonFunctions::getBeginOfMonthUnFormattedDate(1, nYear+1, strBeginOfNextMonth);
   else
      DSTCommonFunctions::getBeginOfMonthUnFormattedDate(nMonth+1, nYear, strBeginOfNextMonth);
   setFieldNoValidate(ifds::BankEffectiveDate, strBeginOfNextMonth, idDataGroup, false, true, true);

   setFieldsReadOnly(idDataGroup);

}
//****************************************************************************

SEVERITY ESoPInfo::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAME2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );
   if( idField == ifds::FundClass )
      setFundNumber(idDataGroup);
   else if( idField == ifds::FromFundNumber )
      setFundClassCode(idDataGroup);
   else if( idField == ifds::FundCode )
      setFundName(idDataGroup);
   else if( idField == ifds::InitPurchDate )
      InitPurchDateRelChanges(idDataGroup);
   else if( idField == ifds::ContStartDate )
      ContStartDateRelChanges(idDataGroup);
   else if( idField == ifds::InterruptCode )
      InterruptCodeRelChanges(idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());

}

//****************************************************************************
void ESoPInfo::setFundClassCode(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setFundClassCode" ) )
   DString dstrFundNumber,dstrFundCode,dstrClassCode;


   getField(ifds::FromFundNumber,dstrFundNumber,idDataGroup,false);

   if( dstrFundNumber.strip() != NULL_STRING )
   {
      if( getWorkSession().GetFundClassCode(dstrFundNumber,dstrFundCode,
                                            dstrClassCode) )
      {
         setField(ifds::FundCode, dstrFundCode, idDataGroup, false, true);
         setField( ifds::ClassCode, dstrClassCode, idDataGroup, false,true); 
      }
   }
}
//******************************************************************************

void ESoPInfo::setFundNumber(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setFundNumber" ) )
   DString dstrFundNumber,dstrFundCode,dstrCalssCode;


   getField(ifds::FundCode,dstrFundCode,idDataGroup,false);
   getField(ifds::ClassCode,dstrCalssCode,idDataGroup,false);
   dstrFundCode.strip().upperCase();
   dstrCalssCode.strip().upperCase();
   getWorkSession().GetFundNumber( dstrFundCode, 
                                   dstrCalssCode, dstrFundNumber );

   setField( ifds::FromFundNumber, dstrFundNumber, idDataGroup, false,true );
}
//******************************************************************************

SEVERITY ESoPInfo::doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

   if( idField == ifds::FundClass )
      validateFundClass(idDataGroup);
   else if( idField == ifds::FromFundNumber )
      validateFromFundNumber(idDataGroup);
   else if( idField == ifds::InterruptDate )
      validateInterruptDate(idDataGroup);
   else if( idField == ifds::Amount )
      validateAmount(idDataGroup);
   else if( idField == ifds::FundCode )
      validateFundCode(idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
SEVERITY ESoPInfo::validateFundCode(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFundCode" ) );
   DString strFundCode;
   getField(ifds::FundCode, strFundCode, idDataGroup, false);

   FundMasterList *pFundMasterList = NULL;
   getWorkSession().getMgmtCo().getFundMasterList(pFundMasterList);
   if( !pFundMasterList )
      return(GETCURRENTHIGHESTSEVERITY());

   if( !pFundMasterList->IsFundExist( strFundCode, idDataGroup ) )
   {
      ADDCONDITIONFROMFILE( CND::ERR_INVALID_FUND_CLASS_CODES );
   }

   return(GETCURRENTHIGHESTSEVERITY());  
}
//******************************************************************************

SEVERITY ESoPInfo::validateFundClass (const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFundClass" ) );
   DString strFundCode, strClassCode;
   getField(ifds::FundCode, strFundCode, idDataGroup, false);
   getField(ifds::ClassCode, strClassCode, idDataGroup, false);
   if( strFundCode.strip().empty() || strClassCode.strip().empty() )
      return(GETCURRENTHIGHESTSEVERITY());

   FundDetailList * pFundDetailList = NULL;
   if( getWorkSession().getMgmtCo().getFundDetailList(pFundDetailList) > WARNING )
      return(GETCURRENTHIGHESTSEVERITY());

   if( !pFundDetailList->IsFundClassExist(strFundCode, strClassCode, idDataGroup) ||
       !isESopEligible(strFundCode, strClassCode, idDataGroup) )
   {
      ADDCONDITIONFROMFILE( CND::ERR_INVALID_FUND_CLASS_CODES );
   }

   return(GETCURRENTHIGHESTSEVERITY());  

}
//******************************************************************************

SEVERITY ESoPInfo::validateFromFundNumber(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFromFundNumber" ) );

   DString strFundNumber, strFundCode, strClassCode;
   getField(ifds::FromFundNumber, strFundNumber, idDataGroup, false);
   if( strFundNumber.strip().empty() )
      return(GETCURRENTHIGHESTSEVERITY());

   if( !getWorkSession().GetFundClassCode(strFundNumber, strFundCode, strClassCode) )
   {
      ADDCONDITIONFROMFILE( CND::ERR_INVALID_FUND_NUMBER );
      return(GETCURRENTHIGHESTSEVERITY());  
   }

   if( !isESopEligible(strFundCode, strClassCode, idDataGroup) )
   {
      ADDCONDITIONFROMFILE( CND::ERR_INVALID_FUND_NUMBER );
   }

   return(GETCURRENTHIGHESTSEVERITY());  

}

//******************************************************************************
void ESoPInfo::setFundName(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setFundName" ) )

   FundMasterList *pFundMasterList = NULL;
   DString fundName;

   getWorkSession().getMgmtCo().getFundMasterList(pFundMasterList);
   if (pFundMasterList)
   {
      DString fundCode;

      getField (ifds::FundCode, fundCode, idDataGroup, false);
      if (!fundCode.strip().empty())
      {
	      FundMaster *pFundMaster = NULL;

	      if (pFundMasterList->getFundMaster (fundCode, idDataGroup, pFundMaster) &&
		        NULL != pFundMaster)
         {
            pFundMaster->getField (ifds::ElongName1, fundName, idDataGroup, true);
         }
      }
   }
   setFieldNoValidate (ifds::FundName, fundName, idDataGroup, true, true, true);
}
//******************************************************************************

void ESoPInfo::setFieldsReadOnly(const BFDataGroupId& idDataGroup)
{
   setFieldReadOnly(ifds::ESoPStatus ,    idDataGroup, true);
   setFieldReadOnly(ifds::InitInvestDate ,idDataGroup, true);
   setFieldReadOnly(ifds::ContStartDate , idDataGroup, true);
   setFieldReadOnly(ifds::ContEndDate ,   idDataGroup, true);
   setFieldReadOnly(ifds::BlockStartDate ,idDataGroup, true);
   setFieldReadOnly(ifds::BlockEndDate ,  idDataGroup, true);
   setFieldReadOnly(ifds::InactiveDate ,  idDataGroup, true);
   setFieldReadOnly(ifds::ContExpireDate ,idDataGroup, true);
}
//******************************************************************************

SEVERITY ESoPInfo::validateInterruptDate(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateInterruptDate" ) );
   DString strInterruptCode, strInterruptDate, strCurrBussDate, strFirstOfPreviousMonth;
   getField(ifds::InterruptCode, strInterruptCode, idDataGroup, false);
   getField(ifds::InterruptDate, strInterruptDate, idDataGroup, false);

   if( !strInterruptCode.strip().empty() && (strInterruptDate.strip().empty() || 
                                             strInterruptDate == I_("12319999") ) )
   {
      ADDCONDITIONFROMFILE( CND::ERR_ESOP_INTERRUPT_DATE_BLANK );
   }

   if( strInterruptDate.empty() || strInterruptDate == I_("12319999") )
      return(GETCURRENTHIGHESTSEVERITY());

   getWorkSession().getOption( ifds::CurrBusDate, strCurrBussDate, idDataGroup, false);
   int nMonth = DSTCommonFunctions::getMonthFromUnFormattedDate(strCurrBussDate);
   int nYear = DSTCommonFunctions::getYearFromUnFormattedDate(strCurrBussDate);
   if( nMonth == 1 )
      DSTCommonFunctions::getBeginOfMonthUnFormattedDate(12, nYear-1, strFirstOfPreviousMonth);
   else
      DSTCommonFunctions::getBeginOfMonthUnFormattedDate(nMonth-1, nYear, strFirstOfPreviousMonth);

   if( (DSTCommonFunctions::CompareDates(strCurrBussDate, strInterruptDate ) == 
        DSTCommonFunctions::FIRST_EARLIER) ||
       (DSTCommonFunctions::CompareDates(strInterruptDate, strFirstOfPreviousMonth ) == 
        DSTCommonFunctions::FIRST_EARLIER) )
   {
      ADDCONDITIONFROMFILE( CND::ERR_ESOP_INTERRUPT_DATE_INVALID );
   }

   return(GETCURRENTHIGHESTSEVERITY());  
}
//******************************************************************************

SEVERITY ESoPInfo::validateAmount(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAmount" ) );
   DString strAmount;
   getField(ifds::Amount, strAmount, idDataGroup, false);
   double dAmount = DSTCommonFunctions::convertToDouble( strAmount.strip() );
   if( dAmount < 0 )
   {
      ADDCONDITIONFROMFILE( CND::ERR_INVALID_NEGATIVE_AMOUNT );
   }
   else if( dAmount > 999999999999.00 )
   {
      DString strMaxAmount = I_("999999999999.00");
	  DSTCommonFunctions::DisplayFormat( strMaxAmount, ifds::Amount );
      ADDCONDITIONFROMFILEIDI( CND::ERR_AMOUNT_EXCEED_MAX_LIMIT, (I_("Amount=")+strMaxAmount).c_str() );
   }

   return(GETCURRENTHIGHESTSEVERITY());  
}
//******************************************************************************

void ESoPInfo::setAllFieldsReadOnly(const BFDataGroupId& idDataGroup, bool bReadOnly /*= true*/)
{
   setFieldsReadOnly(idDataGroup);

   setFieldReadOnly(ifds::IFASNumber ,    idDataGroup, bReadOnly);
   setFieldReadOnly(ifds::InitPurchDate ,idDataGroup, bReadOnly);
   setFieldReadOnly(ifds::BankEffectiveDate , idDataGroup, bReadOnly);
   setFieldReadOnly(ifds::AutoCreate ,   idDataGroup, bReadOnly);
   setFieldReadOnly(ifds::FromFundNumber ,idDataGroup, bReadOnly);
   setFieldReadOnly(ifds::FundCode ,    idDataGroup, bReadOnly);
   setFieldReadOnly(ifds::FundName ,idDataGroup, bReadOnly);
   setFieldReadOnly(ifds::ClassCode , idDataGroup, bReadOnly);
   setFieldReadOnly(ifds::Amount ,   idDataGroup, bReadOnly);
   setFieldReadOnly(ifds::Currency ,idDataGroup, bReadOnly);
   setFieldReadOnly(ifds::InterruptDate ,    idDataGroup, bReadOnly);
   setFieldReadOnly(ifds::InterruptCode ,idDataGroup, bReadOnly);

}
//******************************************************************************

SEVERITY ESoPInfo::InitPurchDateRelChanges(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "InitPurchDateRelChanges" ) );
   DString strInitPurchDate, strTaxType;
   getField(ifds::InitPurchDate, strInitPurchDate, idDataGroup, false);
   setFieldNoValidate(ifds::InitInvestDate, strInitPurchDate, idDataGroup, false, true, true);

   getParent()->getField(ifds::TaxType, strTaxType, idDataGroup, false);
   if( strTaxType.strip().upperCase() == ESOP_INVESTMENT )
   {
      //ContStartDate
      setFieldNoValidate(ifds::ContStartDate, strInitPurchDate, idDataGroup, false, true, true);
      //ContEndDate
      DString strEndOfMonthSixYearsAfter;
      int nMonth = DSTCommonFunctions::getMonthFromUnFormattedDate(strInitPurchDate);
      int nYear = DSTCommonFunctions::getYearFromUnFormattedDate(strInitPurchDate);
      DSTCommonFunctions::getEndOfMonthUnFormattedDate(nMonth, nYear+6, strEndOfMonthSixYearsAfter);
      setFieldNoValidate(ifds::ContEndDate, strEndOfMonthSixYearsAfter, idDataGroup, false, true, true);
   }
   return(GETCURRENTHIGHESTSEVERITY());  
}
//******************************************************************************

SEVERITY ESoPInfo::ContStartDateRelChanges(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ContStartDateRelChanges" ) );
   DString strContStartDate, strTaxType;
   getField(ifds::ContStartDate, strContStartDate, idDataGroup, false);

   getParent()->getField(ifds::TaxType, strTaxType, idDataGroup, false);
   if( strTaxType.strip().upperCase() == ESOP_INVESTMENT )
   {
      //BlockStartDate
      DString strBeginOfYear;
      int nMonth = DSTCommonFunctions::getMonthFromUnFormattedDate(strContStartDate);
      int nYear = DSTCommonFunctions::getYearFromUnFormattedDate(strContStartDate);
      DSTCommonFunctions::getBeginOfMonthUnFormattedDate(1, nYear, strBeginOfYear);
      setFieldNoValidate(ifds::BlockStartDate, strBeginOfYear, idDataGroup, false, true, true);
      //BlockEndDate
      DString strEndOfYearSixYearsAfter;
      DSTCommonFunctions::getEndOfMonthUnFormattedDate(12, nYear+6, strEndOfYearSixYearsAfter);
      setFieldNoValidate(ifds::BlockEndDate, strEndOfYearSixYearsAfter, idDataGroup, false, true, true);
   }
   return(GETCURRENTHIGHESTSEVERITY());  
}
//******************************************************************************

SEVERITY ESoPInfo::InterruptCodeRelChanges(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "InterruptCodeRelChanges" ) );
   DString strInterruptCode;
   getField(ifds::InterruptCode, strInterruptCode, idDataGroup, false);
   if( !strInterruptCode.strip().empty() )
      getParent()->setField(ifds::StopPurchase, YES, idDataGroup, false);

   return(GETCURRENTHIGHESTSEVERITY());  
}
//******************************************************************************

SEVERITY ESoPInfo::getESoPHistoricalList( ESoPHistoricalList *&pESoPHistoricalList, const BFDataGroupId& idDataGroup, bool bCreate /*= true*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getESoPHistoricalList" ) );
   //check cbobase to see if we've already built it
   //otherwise, create and store with base
   pESoPHistoricalList = dynamic_cast<ESoPHistoricalList*>(BFCBO::getObject( I_( "ESoPHistoricalList" ), idDataGroup ) );

   if( !pESoPHistoricalList )
   {
      if( !isNew() && bCreate )
      {
         pESoPHistoricalList = new ESoPHistoricalList( *this );
         pESoPHistoricalList->init();
      }
      if( pESoPHistoricalList )
      {
         if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
            setObject( pESoPHistoricalList, I_( "ESoPHistoricalList" ), OBJ_ACTIVITY_NONE, BF::HOST );
         else
         {
            delete pESoPHistoricalList;
            pESoPHistoricalList = NULL;
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

bool ESoPInfo::isESopEligible(const DString& strFundCode, const DString& strClassCode, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "isESopEligible" ) );
   DString strGroupCode;
   getParent()->getField(ifds::AcctGroup, strGroupCode, idDataGroup, false);
   strGroupCode.strip();

   DString strAccountNum;
   getParent()->getField(ifds::AccountNum, strAccountNum, idDataGroup, false);

   MFAccount * pMFAccount = NULL;
   if( strAccountNum != NULL_STRING && 
       getWorkSession().getMFAccount( idDataGroup, strAccountNum, pMFAccount ) <=WARNING )
   {
      GroupFundList *pGroupFundList = NULL;
      if( pMFAccount->getGroupFundListFromGroup( strGroupCode, strFundCode, idDataGroup, pGroupFundList) > WARNING )
	  {
	     /*if ( pGroupFundList )
			 delete pGroupFundList;*/
         return(false);
	  }

	  bool bisESoEligibe = pGroupFundList->isESoPEligibleFundClass(strGroupCode, strFundCode, strClassCode);

	  /*if ( pGroupFundList )
		  delete pGroupFundList;*/

      return(bisESoEligibe);
   }

   return(false);
}
//******************************************************************************

void ESoPInfo::getField( const BFFieldId& idField,
                         DString& strFieldValue,
                         const BFDataGroupId& idDataGroup,
                         bool formattedReturn ) const
{
   BFCBO::getField( idField, strFieldValue, idDataGroup, formattedReturn );
   if( idField == ifds::Amount && formattedReturn )
   {
      DString currency;
      getField( ifds::Currency, currency, idDataGroup, false );
      currency.strip();

      BFCBO::getField( idField, strFieldValue, idDataGroup, false );
      CurrencyClass::FormatValue( currency, strFieldValue, strFieldValue );
   }
}
//******************************************************************************
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ESoPInfo.cpp-arc  $
// 
//    Rev 1.23   Oct 25 2005 12:50:52   popescu
// Incident# 434042 - removed the deletes of the group fund list. since now is cached at the mgmt co leve.
// 
//    Rev 1.22   Jul 11 2005 17:22:44   Fengyong
// PET1250FN02 - European numeric enahncement - conditions
// decimal format 
// 
//    Rev 1.21   Mar 13 2005 17:12:00   winnie
// Restore the previous version. Remove the pointer variable _groupFundListbyFund in Group object since it will cause problem in multi-threading process (affect API processing). GroupFundList should be delete the object by the object which creates it.
// 
//    Rev 1.20   Mar 11 2005 14:08:24   smithdav
// Fixed bug in Group::getGroupFundListByFund function where BPS threads clashed the function call concurrently.
// 
//    Rev 1.19   Feb 15 2005 20:17:46   winnie
// PTS 237768 : Get Group Fund by Fund Code to speed up the performance.
// 
//    Rev 1.18   Nov 14 2004 14:36:54   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.17   May 11 2004 15:49:16   popescu
// PET 985, FN 01, LSIF Trade Entry, added handy methods to fund master list, to check whether a fund is LSIF/Money Market, GIC
// 
//    Rev 1.16   Mar 21 2003 18:08:42   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.15   Oct 09 2002 23:54:28   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.14   Aug 29 2002 12:55:46   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.13   22 May 2002 18:28:34   PURDYECH
// BFData Implementation
// 
//    Rev 1.12   05 Feb 2002 10:08:02   KOVACSRO
// Added getField
// 
//    Rev 1.11   21 Dec 2001 16:24:44   KOVACSRO
// Added isESoPEligible() to make code clearer.
// 
//    Rev 1.10   14 Dec 2001 10:41:38   KOVACSRO
// code cleanup.
// 
//    Rev 1.9   07 Dec 2001 17:28:30   KOVACSRO
// more implementation.
// 
//    Rev 1.8   Dec 03 2001 15:38:46   ZHANGCEL
// Change logic in order to get GroupFundList from Group CBO instead of from mgmc
// 
//    Rev 1.7   Nov 29 2001 16:13:30   ZHANGCEL
// Check in for Release 45
// 
//    Rev 1.6   02 Oct 2001 11:45:42   KOVACSRO
// Modifies inits and added getEsopHistoricalList.
// 
//    Rev 1.5   24 Sep 2001 12:26:54   KOVACSRO
// minor change.
// 
//    Rev 1.4   19 Sep 2001 15:16:40   KOVACSRO
// Added some more bussines rules.
// 
//    Rev 1.3   14 Sep 2001 17:00:46   KOVACSRO
// Added validation and implemented doInitWithDefaultValues.
// 
//    Rev 1.2   16 Aug 2001 14:26:50   KOVACSRO
// Added some methods.
// 
//    Rev 1.1   16 Aug 2001 10:52:42   KOVACSRO
// milestone check in.
// 
//    Rev 1.0   29 Jul 2001 19:11:40   KOVACSRO
// Initial revision.
 // 
 
*/


