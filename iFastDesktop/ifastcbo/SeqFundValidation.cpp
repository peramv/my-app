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
// ^FILE   : SeqFundValidation.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 08/08/2000
//
// ^CLASS    : SeqFundValidation
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"

#include "errmsgruleslist.hpp"
#include "mastercontractlist.hpp"
#include "mfaccount.hpp"
#include "mgmtco.hpp"
#include "seqfundvalidation.hpp"

#include <ifastdataimpl\dse_dstc0140_req.hpp>
#include <ifastdataimpl\dse_dstc0140_vw.hpp>
#include <ifastdataimpl\dse_dstc0193_req.hpp>
#include <ifastdataimpl\dse_dstc0193_vw.hpp>
#include <ifastdataimpl\dse_dstc0354_req.hpp>
#include <ifastdataimpl\dse_dstc0354_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest SEQ_FUND_VALIDATION;
   extern CLASS_IMPORT const DSTCRequest SEQ_FUND_VALIDATION_NUSU;
   extern CLASS_IMPORT const DSTCRequest SEQ_FUND_VALIDATION_354;
}

namespace  
{
   const I_CHAR * const CLASSNAME         = I_( "SeqFundValidation" );
   const I_CHAR * const YES               = I_( "Y" );
   const I_CHAR * const NO                = I_( "N" );
   const I_CHAR * const CONTRACTEFFECT    = I_( "ContractEffect" );
   const I_CHAR * const EFFECTIVEDATE     = I_( "EffectiveDate" );
   const I_CHAR * const TRADEDATE         = I_( "TRADE_DATE" );
   const I_CHAR * const CONTRACTAGE       = I_( "CONTRACTAGE" );
   const I_CHAR * const PARAM             = I_( "PARAM" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId SegClient;
   extern CLASS_IMPORT const BFTextFieldId CotClient;
   extern CLASS_IMPORT const BFTextFieldId FundCode;
   extern CLASS_IMPORT const BFTextFieldId ClassCode;
   extern CLASS_IMPORT const BFTextFieldId GroupCode;
   extern CLASS_IMPORT const BFTextFieldId DepAllowed;
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFTextFieldId PorfolioIsRequried;
   extern CLASS_IMPORT const BFTextFieldId GuaranteeCalcByRules;
   extern CLASS_IMPORT const BFTextFieldId TradesTransType;
   extern CLASS_IMPORT const BFTextFieldId GuaranteesOverride;
}

namespace  CND
{
   extern const long ERR_CONTRACT_TYPE_NOT_FOUND;
   extern const long ERR_CONTRACT_NOT_EFFECTIVE;
   extern const long ERR_CONTRACT_MUST_BE_CREATED;
   extern const long ERR_DEPOSITS_NOT_ALLOWED;
   extern const long ERR_RESET_DONE;
   extern const long ERR_NO_CONTRACT_AVAILABLE_TO_SHAAREHOLDER_GROUP;
   extern const long ERR_CONTR_MAT_DATE_MISSING;
   extern const long ERR_SEG_VALIDATION_BACKDATED_NOT_ALLOWED;

   extern const long WARN_TRADE_UNIT_ADJ_REQ_FOR_ACCOUNT_FROM;
   extern const long WARN_TRADE_UNIT_ADJ_REQ_FOR_ACCOUNT_TO;   
   extern const long WARN_TRADE_GUAR_ADJ_EXISTS_AFTER_TRADE_DATE_ACCT_FROM;
   extern const long WARN_TRADE_GUAR_ADJ_EXISTS_AFTER_TRADE_DATE_ACCT_TO;
   extern const long WARN_TRADE_GUAR_ADJ;
   extern const long WARN_CONTRACT_CLOSED_FOR_NEW_BUSINESS;
   extern const long WARN_FUND_CLASS_NOT_AVAILABLE_FOR_PURCHASE;
   extern const long WARN_PURCHASE_ANNUITANT_OLDER_THAN_LATEST_AGE;
   extern const long WARN_TRANS_NOT_ALLOWED_DURING_SETTLMENTPHASE;
   extern const long ERR_GUARANTEE_ADJUSTMENT_EXISTS_AFTER_TRADE_DATE_INA;
   extern const long WARN_GUARANTEE_ADJUSTMENT_EXISTS_AFTER_TRADE_DATE_INA;
   extern const long WARN_TRADE_DOES_NOT_BELONG_TO_EXISTING_FUND;
   extern const long WARN_ANNUITANT_AGE_BELOW_MINIMUM_REQUIREMENT_PER_CONTRACT;

   // import from the definition at databroker level
   extern CLASS_IMPORT const long ERR_ANNUITANT_AGE_BELOW_MINIMUM_REQUIREMENT_PER_CONTRACT;
}

namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const GUARANTEE_ADJUSTMENT_EXISTS_AFTER_TRADE_DATE;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//   Field DD Id,        State Flags,       Group Flags 
   { ifds::ContractType,   BFCBO::NONE, 0 }, 
   { ifds::FutureContract, BFCBO::NONE, 0 }, 
   { ifds::EffectiveDate,  BFCBO::NONE, 0 }, 
   { ifds::CreateContract, BFCBO::NONE, 0 }, 
   { ifds::DepAllowed,     BFCBO::NONE, 0 }, 
   { ifds::ResetExist,     BFCBO::NONE, 0 }, 
   { ifds::ContractExist,  BFCBO::NONE, 0 }, 
   { ifds::GuaranteesOverride,   BFCBO::NONE, 0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = {
//  Object Label,    State Flags,         Group Flags 
   {  I_(""),        BFCBO::REQUIRED,         0}
};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );

//****************************************************************************
SeqFundValidation::SeqFundValidation( BFAbstractCBO &parent )
: MFCanBFCbo( parent ),
_pV140ReceivedData( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       NUM_OBJECTS,
                       (const CLASS_OBJECT_INFO *)&classObjectInfo );
}

//****************************************************************************
SeqFundValidation::~SeqFundValidation()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}   

//****************************************************************************
SEVERITY SeqFundValidation::init( const BFData& InstData, 
                                  const DString& strFundCode, 
                                  const DString& strClassCode,
                                  const DString& strAccountNum, 
                                  const DString& strEffectiveDate,
                                  const DString& strEventTransType )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   attachDataObject( const_cast<BFData&>(InstData), false, true );

   bChecked = false;
   bValid = true;
   saveInitValues(strFundCode, 
                  strClassCode, 
                  strAccountNum, 
                  strEffectiveDate, 
                  strEventTransType);

   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************

SEVERITY SeqFundValidation::init(const DString& strFundCode, 
                                 const DString& strClassCode,
                                 const DString& strAccountNum, 
                                 const DString& strEffectiveDate,
                                 const DString& strEventTransType,
                                 const DString& strFundCodeTo,
                                 const DString& strClassCodeTo,
                                 const DString& strAccountNumTo,
                                 const DString& strTransType,
                                 bool  bViewCall,
                                 const DString& dstrTrack,
                                 const DString& dstrPageName ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   bIsNewAccount = false;
   DString strSegClient, strCotClient;

   getWorkSession().getOption( ifds::SegClient, strSegClient, BF::HOST );
   getWorkSession().getOption( ifds::CotClient, strCotClient, BF::HOST );

   if( (strSegClient == YES) && (strCotClient == YES) && (bViewCall) )
   {

      BFData queryData(ifds::DSTC0140_REQ);      
      _pV140ReceivedData = new BFData(ifds::DSTC0140_VW);

      DString mgmtCoIdOut;
      queryData.setElementValue( ifds::CompanyId,      getMgmtCoId( mgmtCoIdOut ) );
      queryData.setElementValue( ifds::FundCode,       strFundCode ); 
      queryData.setElementValue( ifds::ClassCode,      strClassCode );
      queryData.setElementValue( ifds::AccountNum,     strAccountNum );
      queryData.setElementValue( ifds::EffectiveDate,  strEffectiveDate, false, false );     
      queryData.setElementValue( ifds::FundTo,         strFundCodeTo ); 
      queryData.setElementValue( ifds::ClassTo,        strClassCodeTo );
      queryData.setElementValue( ifds::AccountTo,      strAccountNumTo );
      queryData.setElementValue( ifds::EventTransType, strEventTransType );
      queryData.setElementValue( ifds::TransType,      strTransType );
      queryData.setElementValue( ifds::Track,          dstrTrack );
      queryData.setElementValue( ifds::Activity,       dstrPageName );

      DString strGuaranteesOverride;
      getField( ifds::GuaranteesOverride,strGuaranteesOverride,BF::HOST,false);

      DSTCRequestor requestor (getSecurity());

      if(strGuaranteesOverride.strip().upperCase() == I_("Y"))
      {
         requestor.filterHostCondition (CND::ERR_ANNUITANT_AGE_BELOW_MINIMUM_REQUIREMENT_PER_CONTRACT);
      }

      ReceiveData( DSTC_REQUEST::SEQ_FUND_VALIDATION, 
                   queryData, 
                   *_pV140ReceivedData, 
                    requestor );

   }

   saveInitValues( strFundCode, 
                   strClassCode, 
                   strAccountNum, 
                   strEffectiveDate, 
                   strEventTransType,
                   strTransType,
                   strFundCodeTo,
                   strClassCodeTo,
                   strAccountNumTo);

   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************
SEVERITY SeqFundValidation::init( const DString& strFundCode, 
                                  const DString& strClassCode,
                                  const DString& strEffectiveDate,
                                  const DString& strAcctDesignation,
                                  const DString& strTaxType,
                                  const DString& strPensionJuris,
                                  const DString& strDofBirth,
                                  const DString& strContractType,
                                  const DString& strMaturityType,
                                  const DString& strUserMaturityDate,
                                  const DString& strAgeBasedOn,
                                  bool  bViewCall,
                                  const DString& dstrTrack,
                                  const DString& dstrPageName ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   bIsNewAccount = true;
   DString strSegClient, strCotClient;
   getWorkSession().getOption( ifds::SegClient, strSegClient, BF::HOST );
   getWorkSession().getOption( ifds::CotClient, strCotClient, BF::HOST );

   if( (strSegClient == YES) && (strCotClient == YES) && (bViewCall) )
   {

      BFData queryData(ifds::DSTC0193_REQ);
      BFData *receivedData = new BFData(ifds::DSTC0193_VW);

      DString mgmtCoIdOut;
      queryData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
      queryData.setElementValue( ifds::FundCode, strFundCode ); 
      queryData.setElementValue( ifds::ClassCode, strClassCode );
      queryData.setElementValue( ifds::EffectiveDate, strEffectiveDate, false, false );
      queryData.setElementValue( ifds::AcctDesignation, strAcctDesignation ); 
      queryData.setElementValue( ifds::TaxType, strTaxType );
      queryData.setElementValue( ifds::PensionJuris, strPensionJuris );
      queryData.setElementValue( ifds::DofBirth, strDofBirth, false, false ); 
      queryData.setElementValue( ifds::ContractType, strContractType );
      queryData.setElementValue( ifds::MaturityType, strMaturityType );
      queryData.setElementValue( ifds::UserMaturityDate, strUserMaturityDate, false, false  ); 
      queryData.setElementValue( ifds::AgeBasedOn, strAgeBasedOn );
      queryData.setElementValue( ifds::Track, dstrTrack );
      queryData.setElementValue( ifds::Activity, dstrPageName );

      ReceiveData( DSTC_REQUEST::SEQ_FUND_VALIDATION_NUSU, queryData, *receivedData, DSTCRequestor( getSecurity() ) );

   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************
SEVERITY SeqFundValidation::canTradeFundClass ( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "canTradeFundClass" ) );
   //if already chequed and valid, just return
   //if chequed and not valid, still want to add the condition ...
   //if parameters change, bChequed will be set to false
   if( ( (!bChecked) || ( bChecked && !bValid ) ) && !bIsNewAccount )
   {
      DString strSegClient, strCotClient;
      getWorkSession().getOption( ifds::SegClient, strSegClient, idDataGroup );//formated?
      getWorkSession().getOption( ifds::CotClient, strCotClient, idDataGroup );//formated?

      if( (strSegClient == YES) && (strCotClient == YES) )
      {
         bChecked = true;
         DString strContractType;
         getField(ifds::ContractType, strContractType, idDataGroup);
         if( strContractType == NULL_STRING )
         {
			 // NOTE: This need to be enabled once cleanup is done.
            ADDCONDITIONFROMFILE( CND::ERR_CONTRACT_TYPE_NOT_FOUND );
            bValid = false;
         }
         DString strFutureContract;
         getField(ifds::FutureContract, strFutureContract, idDataGroup);
         if( strFutureContract == YES )
         {
            DString strEffDate, idiStr;
            getField(ifds::EffectiveDate, strEffDate, idDataGroup, true);
            //format the date into mm/dd/yyyy or whatever the host is setup to be.
            //DSTCommonFunctions::formatToolTipDate( ifds::EffectiveDate, strEffDate );
            addIDITagValue( idiStr, CONTRACTEFFECT, strEffDate );
            ADDCONDITIONFROMFILEIDI( CND::ERR_CONTRACT_NOT_EFFECTIVE, idiStr.c_str() );
            bValid = false;
         }
         DString strCreateContract;
         getField(ifds::CreateContract, strCreateContract, idDataGroup);
         if( strCreateContract == YES )
         {
            ADDCONDITIONFROMFILE( CND::ERR_CONTRACT_MUST_BE_CREATED );
            bValid = false;
         }
         DString strDepAllowed;
         getField(ifds::DepAllowed, strDepAllowed, idDataGroup);
         if( strDepAllowed == NO )
         {
            ADDCONDITIONFROMFILE( CND::ERR_DEPOSITS_NOT_ALLOWED );
            bValid = false;
         }
         DString strResetExists;
         getField(ifds::ResetExist, strResetExists, idDataGroup);
         if( strResetExists == YES )
         {
            DString idiStr;
            addIDITagValue( idiStr, EFFECTIVEDATE, m_strEffectiveDate );
            ADDCONDITIONFROMFILEIDI( CND::ERR_RESET_DONE, idiStr.c_str() );
            bValid = false;
         }

         // Check to see whether the trade is allowed based on whether Maturity Dates exist.
         // TradeAllow returns Y or N.  PET1024 FN02
         DString TradeAllow;
         getField( ifds::TradeAllow, TradeAllow, idDataGroup, false );
         if( TradeAllow == NO )
         {
            ADDCONDITIONFROMFILE( CND::ERR_CONTR_MAT_DATE_MISSING );
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************
bool SeqFundValidation::isChanged( const DString& strFundCode, 
                                   const DString& strClassCode,
                                   const DString& strAccountNum, 
                                   const DString& strEffectiveDate,
                                   const DString& strEventTransType,
                                   const DString& strFundCodeTo,
                                   const DString& strClassCodeTo,
                                   const DString& strAccountNumTo )
{
   TRACE_METHOD( CLASSNAME, I_("isChanged") );
   if( strFundCode != m_strFundCode )
      return(true);
   if( strClassCode != m_strClassCode )
      return(true);
   if( strAccountNum != m_strAccountNum )
      return(true);
   if( strEffectiveDate != m_strEffectiveDate )
      return(true);   
   if ( strFundCodeTo!= m_strFundCodeTo )
      return true;  
   if ( strClassCodeTo!= m_strClassCodeTo )
      return true;
   if ( strAccountNumTo!= m_strAccountNumTo )
      return true; 
   if ( strEventTransType!= m_strEventTransType )
      return true; 

   return(false);
}

//****************************************************************************
void SeqFundValidation::saveInitValues(const DString& strFundCode, 
                                       const DString& strClassCode,
                                       const DString& strAccountNum, 
                                       const DString& strEffectiveDate,
                                       const DString& strEventTransType,
                                       const DString& strTransType,
                                       const DString& strFundCodeTo,
                                       const DString& strClassCodeTo,
                                       const DString& strAccountNumTo )
{
   TRACE_METHOD( CLASSNAME, I_("saveInitValues") );

   m_strFundCode       = strFundCode;
   m_strClassCode      = strClassCode;
   m_strAccountNum     = strAccountNum;
   m_strEffectiveDate  = strEffectiveDate;
   m_strFundCodeTo     = strFundCodeTo;
   m_strClassCodeTo    = strClassCodeTo;
   m_strAccountNumTo   = strAccountNumTo;
   m_strEventTransType = strEventTransType;
   m_strTransType      = strTransType;

   bChecked = false;
   bValid = true;

}

//****************************************************************************
SEVERITY SeqFundValidation::reInit( const DString& strFundCode, 
                                   const DString& strClassCode, 
                                   const DString& strAccountNum, 
                                   const DString& strEffectiveDate,
                                   const DString& strEventTransType,
                                   const DString& strFundCodeTo,
                                   const DString& strClassCodeTo,
                                   const DString& strAccountNumTo,
                                   const DString& strTransType )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "reInit" ) );

   if( !isNew() )
   {
      init( strFundCode, 
            strClassCode, 
            strAccountNum, 
            strEffectiveDate, 
            strEventTransType,
            strFundCodeTo,
            strClassCodeTo, 
            strAccountNumTo,
            strTransType );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************
void SeqFundValidation::getInitValues(DString &strFundCode, DString &strClassCode, 
                                      DString &strAccountNum, DString &strEffectiveDate,
                                      DString &strEventTransType)
{
   strFundCode = m_strFundCode;
   strClassCode = m_strClassCode;
   strAccountNum = m_strAccountNum;
   strEffectiveDate = m_strEffectiveDate;
   strEventTransType = m_strEventTransType;
}

//****************************************************************************
SEVERITY SeqFundValidation::validateSegFund( DString dstrAcctGroup, 
                                             DString dstrEffectiveDate, 
                                             DString dstrEffectDateCnt, 
                                             DString dstrContractType, 
                                             const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateSegFund" ) );

   DString strSegClient, strCotClient;

   getWorkSession().getOption( ifds::SegClient, strSegClient, BF::HOST );
   getWorkSession().getOption( ifds::CotClient, strCotClient, BF::HOST );

   if( (strSegClient == YES) && (strCotClient == YES) )
   {
      DString dstrContractExist, idiStr;
      getField( ifds::ContractExist, dstrContractExist, idDataGroup );
      if( dstrContractExist == NO )
	  {
		  // NOTE: This need to be enabled once cleanup is done.
         ADDCONDITIONFROMFILE( CND::ERR_CONTRACT_TYPE_NOT_FOUND );
	  }

      if( DSTCommonFunctions::CompareDates( dstrEffectiveDate, dstrEffectDateCnt) == DSTCommonFunctions::FIRST_EARLIER )
      {
         addIDITagValue( idiStr, CONTRACTEFFECT, dstrEffectDateCnt );
         ADDCONDITIONFROMFILEIDI( CND::ERR_CONTRACT_NOT_EFFECTIVE, idiStr.c_str() );
      }

      MasterContractList *pMasterContractList = NULL;
      getMasterContractList(pMasterContractList,idDataGroup);
      //getMgmtCo().getMasterContractList( pMasterContractList );
      if( pMasterContractList )
      {
         BFData data;
         data.setElementValue( ifds::GroupCode, dstrAcctGroup, true, false );
         data.setElementValue( ifds::ContractType, dstrContractType, true, false );
         DString dstrKey;
         pMasterContractList->getStrKey( dstrKey, &data );
         BFObjIter iterList( *pMasterContractList, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
         if( !iterList.positionByKey( dstrKey ) )
         {
            addIDITagValue( idiStr, I_("SHAREHOLDERGROUP"), dstrAcctGroup );
            ADDCONDITIONFROMFILEIDI( CND::ERR_NO_CONTRACT_AVAILABLE_TO_SHAAREHOLDER_GROUP, idiStr.c_str() );  
         }
      }

      DString dstrDepAllowed;
      getField( ifds::DepAllowed, dstrDepAllowed, idDataGroup );
      if( dstrDepAllowed == NO )
         ADDCONDITIONFROMFILE( CND::ERR_DEPOSITS_NOT_ALLOWED );

   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************
SEVERITY SeqFundValidation::addSegFundValidationWarnings( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "addSegFundValidationWarnings" ) );

   if ( NULL != _pV140ReceivedData )
   {	
      int cRepeats = _pV140ReceivedData->getRepeatCount( );

      if( cRepeats != 0 )
      {
         // for each repeat
         for( int i = 0; i < cRepeats; i++ )
         {
            BFCBO *pObj = NULL;
            doCreateObject( _pV140ReceivedData->getRepeat( i ), pObj );

            if( pObj != NULL )
            {
               DString dstrWarnCode;
               pObj->getField( ifds::WarnCode, dstrWarnCode, idDataGroup );
               dstrWarnCode.strip().upperCase();
               if ( !dstrWarnCode.empty() && dstrWarnCode != I_("0"))
               {
                  DString dstrWarnSide, dstrWarnParam;
                  pObj->getField( ifds::WarnSide, dstrWarnSide, idDataGroup );
                  pObj->getField( ifds::WarnParam, dstrWarnParam, idDataGroup );
                  dstrWarnSide.strip().upperCase();
                  bool bWarnCodeExists = true;	
                  int iWarnCode = dstrWarnCode.asInteger ();
                  switch( iWarnCode )
                  {
                  case 463:	
                     {
                        if ( I_( "FROM" ) == dstrWarnSide )
                        {
                           // Unit Adjustment required for Account From.
                           ADDCONDITIONFROMFILE( CND::WARN_TRADE_UNIT_ADJ_REQ_FOR_ACCOUNT_FROM );
                        }
                        else if ( I_( "TO" ) == dstrWarnSide )
                        {
                           // Unit Adjustment required for Account To.
                           ADDCONDITIONFROMFILE( CND::WARN_TRADE_UNIT_ADJ_REQ_FOR_ACCOUNT_TO );								
                        }
                        else
                           bWarnCodeExists = false;
                     }
                     break;
                  case 462:
                     {
                        DString dstrErrValue;
                        getErrMsgValue( IFASTERR::GUARANTEE_ADJUSTMENT_EXISTS_AFTER_TRADE_DATE,
                                        idDataGroup, 
                                        dstrErrValue);
                        dstrErrValue.strip().upperCase();

                        if(dstrErrValue == I_("E")) // INA would always error
                        {
                           DString idiStr, dstrTranstype(m_strTransType);
                           dstrTranstype.strip().upperCase();
                           BFDataField::formatValue( ifds::TradesTransType, dstrTranstype );
                           dstrTranstype.strip().lowerCase();
                           addIDITagValue( idiStr, I_("TRANSTYPE"), dstrTranstype );
                           ADDCONDITIONFROMFILEIDI( CND::ERR_GUARANTEE_ADJUSTMENT_EXISTS_AFTER_TRADE_DATE_INA, idiStr );
                           bWarnCodeExists = true;
                        }
                        else // the rest would rely on old logic
                        {
                           if ( I_( "FROM" ) == dstrWarnSide )
                           {
                              // Guarantee Adjustment exists after trade date for Account From 
                              ADDCONDITIONFROMFILE( CND::WARN_TRADE_GUAR_ADJ_EXISTS_AFTER_TRADE_DATE_ACCT_FROM );
                           }
                           else if ( I_( "TO" ) == dstrWarnSide )
                           {
                              // Guarantee Adjustment exists after trade date for Account To
                              ADDCONDITIONFROMFILE( CND::WARN_TRADE_GUAR_ADJ_EXISTS_AFTER_TRADE_DATE_ACCT_TO );
                           }
                           else
                           {
                              bWarnCodeExists = false;
                           }
                        }
                     }
                     break;
                  case 468:
                     {
                        DString idiStr;
                        addIDITagValue (idiStr, CONTRACTAGE, dstrWarnParam );
                        ADDCONDITIONFROMFILEIDI( CND::WARN_PURCHASE_ANNUITANT_OLDER_THAN_LATEST_AGE, idiStr );										
                     }
                     break;
                  case 469:
                     {
                        DString idiStr, warnParam;
                        addIDITagValue (idiStr, PARAM, dstrWarnParam );
                        ADDCONDITIONFROMFILEIDI (CND::WARN_FUND_CLASS_NOT_AVAILABLE_FOR_PURCHASE, idiStr)
                     }
                     break;
                  case 483:
                     {
                        ADDCONDITIONFROMFILE (CND::WARN_TRANS_NOT_ALLOWED_DURING_SETTLMENTPHASE);
                     }
                     break;
                  case 1396:
                      {
                          ADDCONDITIONFROMFILE(CND::WARN_TRADE_DOES_NOT_BELONG_TO_EXISTING_FUND);
                      }
                      break;
                  case 1397:
                      {
                          ADDCONDITIONFROMFILE(CND::WARN_ANNUITANT_AGE_BELOW_MINIMUM_REQUIREMENT_PER_CONTRACT);
                      }
                      break;
                  default:    // Just in case they have added another error that we haven't been told about...
                     {
                        bWarnCodeExists = false;
                     }
                     break;
                  } // switch

                  if ( ! bWarnCodeExists )
                  {
                     DString dstrWarnMessage;
                     pObj->getField( ifds::WarnDesc, dstrWarnMessage, idDataGroup );

                     if ( I_( "FROM" ) == dstrWarnSide.strip().upperCase() )
                        dstrWarnMessage = I_( "Account From:" ) + dstrWarnMessage;
                     else if ( I_( "TO" ) == dstrWarnSide.strip().upperCase() )
                        dstrWarnMessage = I_( "Account To:" ) + dstrWarnMessage;

                     DString dstrIDI;
                     addIDITagValue (dstrIDI, I_("WarningTradeGuarAdj"), dstrWarnMessage);
                     ADDCONDITIONFROMFILEIDI (CND::WARN_TRADE_GUAR_ADJ , dstrIDI);   
                  }					
               }	// if ( !dstrWarnCode.empty() )		   
            } // if( pObj != NULL )
         } // for( int i = 0; i < cRepeats; i++ )
      } // if( cRepeats != 0 )
   } // if ( NULL != _pV140ReceivedData )

   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************
SEVERITY SeqFundValidation::init354( const DString& strAcctNum, 
                                     const DString& strContractType,
                                     const DString& strEffectiveDate,
                                     const DString& dstrContractTypeId,
                                     bool  bViewCall,
                                     const DString& dstrTrack,
                                     const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   // bIsNewAccount = false;
   DString strSegClient, strCotClient;

   getWorkSession().getOption( ifds::SegClient, strSegClient, BF::HOST );
   getWorkSession().getOption( ifds::CotClient, strCotClient, BF::HOST );

   if( (strSegClient == YES) && (strCotClient == YES) && (bViewCall) )
   {
      BFData queryData(ifds::DSTC0354_REQ);      
      _pV354ReceivedData = new BFData(ifds::DSTC0354_VW);

      DString mgmtCoIdOut;
      queryData.setElementValue( ifds::CompanyId,      getMgmtCoId( mgmtCoIdOut ) );
      queryData.setElementValue( ifds::AccountNum,     strAcctNum );
      queryData.setElementValue( ifds::ContractType,   strContractType );
      queryData.setElementValue( ifds::EffectiveDate,  strEffectiveDate, false, false  );     
      queryData.setElementValue( ifds::Track,          dstrTrack );
      queryData.setElementValue( ifds::Activity,       dstrPageName );
      queryData.setElementValue( ifds::ContractTypeId, dstrContractTypeId );

      ReceiveData( DSTC_REQUEST::SEQ_FUND_VALIDATION_354, 
                   queryData, 
                   *_pV354ReceivedData, 
                   DSTCRequestor( getSecurity() ) );

   }

   return(GETCURRENTHIGHESTSEVERITY());
}


//****************************************************************************
SEVERITY SeqFundValidation::SegFundValidationWarnings( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "SegFundValidationWarnings" ) );

   if ( NULL != _pV354ReceivedData )
   {	
      int cRepeats = _pV354ReceivedData->getRepeatCount( );

      if( cRepeats != 0 )
      {
         // for each repeat
         for( int i = 0; i < cRepeats; i++ )
         {
            BFCBO *pObj = NULL;
            doCreateObject( _pV354ReceivedData->getRepeat( i ), pObj );

            if( pObj != NULL )
            {
               DString dstrWarnCode, dstrWarnParam;
               pObj->getField( ifds::WarnCode, dstrWarnCode, idDataGroup );
               pObj->getField( ifds::WarnParam, dstrWarnParam, idDataGroup );

               dstrWarnCode.strip().upperCase();
               if ( !dstrWarnCode.empty() && dstrWarnCode != I_("0"))
               {
                  bool bWarnCodeExists = true;	

                  int iWarnCode = dstrWarnCode.asInteger ();
                  switch( iWarnCode )
                  {

                  case 468:
                     {
                        DString idiStr;
                        addIDITagValue (idiStr, CONTRACTAGE, dstrWarnParam );
                        ADDCONDITIONFROMFILEIDI( CND::WARN_PURCHASE_ANNUITANT_OLDER_THAN_LATEST_AGE, idiStr );		
                     }
                     break;
                  case 469:
                     {
                        DString idiStr;
                        addIDITagValue (idiStr, PARAM, dstrWarnParam );
                        ADDCONDITIONFROMFILEIDI (CND::WARN_FUND_CLASS_NOT_AVAILABLE_FOR_PURCHASE, idiStr)
                     }
                     break;
                  case 483:
                     {
                        ADDCONDITIONFROMFILE (CND::WARN_TRANS_NOT_ALLOWED_DURING_SETTLMENTPHASE);
                     }
                     break;
                  default:    // Just in case they have added another error that we haven't been told about...
                     {
                        bWarnCodeExists = false;
                     }
                     break;
                  }

                  if ( ! bWarnCodeExists )
                  {
                     DString dstrWarnMessage;
                     pObj->getField( ifds::WarnDesc, dstrWarnMessage, idDataGroup );

                     DString dstrIDI;
                     addIDITagValue (dstrIDI, I_("WarningTradeGuarAdj"), dstrWarnMessage);
                     ADDCONDITIONFROMFILEIDI (CND::WARN_TRADE_GUAR_ADJ , dstrIDI);   
                  }
               } // if ( !dstrWarnCode.empty() )
            } // if( pObj != NULL )
         } // for( int i = 0; i < cRepeats; i++ ) 
      } // if( cRepeats != 0 )
   } // if ( NULL != _pV354ReceivedData )

   return(GETCURRENTHIGHESTSEVERITY());
}


//****************************************************************************
SEVERITY SeqFundValidation::checkBackdatedAllowed (const DString &strTradeDate, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "checkBackdatedAllowed" ) );
   if( ( (!bChecked) || ( bChecked && !bValid ) ) && !bIsNewAccount )
   {
      DString strSegClient, strCotClient, strGuaranteeCalcByRules;
      getWorkSession().getOption( ifds::SegClient, strSegClient, idDataGroup );
      getWorkSession().getOption( ifds::CotClient, strCotClient, idDataGroup );
      getWorkSession().getOption(ifds::GuaranteeCalcByRules, strGuaranteeCalcByRules, idDataGroup, false);
      strGuaranteeCalcByRules.strip().upperCase();

      if ((strSegClient == YES) && (strCotClient == YES))
      {
         DString strBackdatedAllowed;
         getField(ifds::BackdatedAllowed, strBackdatedAllowed, idDataGroup);

         if (strBackdatedAllowed == NO && strGuaranteeCalcByRules != I_("Y"))
         {
            DString idiStr, formatedTradeDate;
            formatedTradeDate = strTradeDate;

            DSTCommonFunctions::FormatDate (formatedTradeDate);
            addIDITagValue (idiStr, TRADEDATE, formatedTradeDate);
            ADDCONDITIONFROMFILEIDI (CND::ERR_SEG_VALIDATION_BACKDATED_NOT_ALLOWED, idiStr.c_str());
         }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY SeqFundValidation::getMasterContractList(MasterContractList*& _pMasterContractList, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMasterContractList" ) );
   
   DString dstrPorfolioIsRequried;
   getWorkSession().getOption( ifds::PorfolioIsRequried, dstrPorfolioIsRequried, idDataGroup, false );
   dstrPorfolioIsRequried.strip().upperCase();

   if( dstrPorfolioIsRequried == I_("Y") )
   {
      MFAccount *pMFAccount = NULL;
      DString dstrAcctNum = m_strAccountNum;

      if(!dstrAcctNum.strip().empty())
      {
         getWorkSession().getMFAccount( idDataGroup, dstrAcctNum, pMFAccount );
         if ( NULL != pMFAccount )
         {
            pMFAccount->getMasterContractListByPortfolio(_pMasterContractList,idDataGroup);
         }
      }
   }
   else
   {
      getMgmtCo().getMasterContractList( _pMasterContractList );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void SeqFundValidation::getErrMsgValue( DString dstrErrNum,
                                        const BFDataGroupId& idDataGroup, 
                                        DString& dstrErrValue)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getErrMsgValue" ) );

   ErrMsgRulesList *pErrMsgRulesList = NULL;

   if( getMgmtCo().getErrMsgRulesList( pErrMsgRulesList ) <= WARNING &&
      pErrMsgRulesList )
   {
      pErrMsgRulesList->getEWIValue (dstrErrNum, idDataGroup, dstrErrValue);
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/SeqFundValidation.cpp-arc  $
 // 
 //    Rev 1.30   Jun 01 2012 15:46:00   dchatcha
 // IN#2952786 - Err Msg when keying Purchase Before Guarantee Adjustment- Trade Entry Screen
 // 
 //    Rev 1.29   Mar 16 2012 13:38:26   dchatcha
 // P0186484 FN05 - SEG Trade Processing, new validations.
 // 
 //    Rev 1.28   Feb 16 2012 13:53:16   dchatcha
 // IN# 2848252 - P0186484 FN02 Seg Desktop - Contract Info Screen issues for non-IA
 // 
 //    Rev 1.27   Jan 30 2012 14:59:20   dchatcha
 // IN# 2799812 - Contract Screen Issues.
 // 
 //    Rev 1.26   Jan 26 2012 14:33:46   if991250
 // P0186477- GIA trading Screen Issue - Seg fund validation needs to be executed only if the fund category is segregated ('S').
 // 
 //    Rev 1.25   Dec 29 2011 13:39:18   jankovii
 // Commented seg fund validation to enable trading on gia funds.Need to be done properly.
 // 
 //    Rev 1.24   Sep 19 2006 15:17:08   porteanm
 // Incident 714923 - Invalid warning message description.
 // 
 //    Rev 1.23   Jul 25 2006 19:31:20   porteanm
 // Incident 642056 - UDM validation. Layout change for 354 request and fixed response.
 // 
 //    Rev 1.22   May 25 2006 09:41:52   jankovii
 // PET 2102 FN02 - Manulife Flex Trade/Systematic Entry.
 // 
 //    Rev 1.21   Sep 28 2005 16:21:22   ZHANGCEL
 // PET1244 - FN01 - Seg Fund Evolution enhancement
 // 
 //    Rev 1.20   Sep 23 2005 18:24:40   ZHANGCEL
 // PET1244 FN01 -- Seg Func Evolution enhancement
 // 
 //    Rev 1.19   Jun 15 2005 15:45:04   porteanm
 // PET1024 FN40 - Guarantee Adjustments.
 // 
 //    Rev 1.18   Mar 20 2005 14:57:50   hernando
 // PET1024 FN02 - Added a validation to canTradeFundClass; checks logical TradeAllow.
 // 
 //    Rev 1.17   Nov 14 2004 14:53:44   purdyech
 // PET910 - .NET Conversion
 // 
 //    Rev 1.16   Mar 21 2003 18:23:40   PURDYECH
 // BFDataGroupId/BFContainerId changeover
 // 
 //    Rev 1.15   Oct 09 2002 23:54:58   PURDYECH
 // PVCS Database Conversion
 // 
 //    Rev 1.14   Aug 29 2002 12:56:36   SMITHDAV
 // ClientLocale and typed field changes.
 // 
 //    Rev 1.13   Jul 17 2002 10:49:54   KOVACSRO
 // Fixed crash.
 // 
 //    Rev 1.12   22 May 2002 18:29:50   PURDYECH
 // BFData Implementation
 // 
 //    Rev 1.11   Dec 21 2001 17:38:58   ZHANGCEL
 // Added new functions and code for seg fund validation during the NASU flow
 // 
 //    Rev 1.10   21 Oct 2001 16:09:38   HSUCHIN
 // bug fix, formatted date in tool tip
 // 
 //    Rev 1.9   03 May 2001 14:07:06   SMITHDAV
 // Session management restructuring.
 // 
 //    Rev 1.8   Apr 02 2001 15:14:44   OLTEANCR
 // fix: setElementValue(DBR::EffectiveDate,..  )
 // 
 //    Rev 1.7   Jan 18 2001 16:09:44   YINGBAOL
 // add eTracker
 // 
 //    Rev 1.6   Dec 17 2000 20:24:26   OLTEANCR
 // changed to use a precompiled header
 // 
 //    Rev 1.5   Dec 08 2000 17:19:52   DINACORN
 // Synchronization to C2/C3: Checked for segFund before making the view call;
 // Add "Revision Control Entries" at the end of file.
 // 
 //    Rev 1.4   Dec 07 2000 18:01:24   DINACORN
 // Temporary CheckIn
*/


