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
//    Copyright 2008 by IFDS Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : AcctSettlementRuleList.cpp
// ^AUTHOR : Chatchai Daecha
// ^DATE   : Febuary 2008
//
// ^CLASS    : AcctLvlSttlmntRuleList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "AcctSettlementRuleList.hpp"
#include "AcctSettlementRule.hpp"

#include <ifastdataimpl\dse_dstc0386_vw.hpp>
#include <ifastdataimpl\dse_dstc0386_req.hpp>
#include <ifastdataimpl\dse_dstc0386_vwrepeat_record.hpp>


namespace DSTC_REQUEST
{
    extern CLASS_IMPORT const DSTCRequest ACCT_CONTROL_INQUIRY;
}

namespace
{
    const I_CHAR * const CLASSNAME = I_( "AcctLvlSttlmntRuleList" );
}

namespace ifds
{
}

namespace CND
{
    extern const long ERR_ACCT_CONTROL_EXISTS;
}

//******************************************************************************
AcctLvlSttlmntRuleList::AcctLvlSttlmntRuleList( BFAbstractCBO &parent )
: MFCanBFCbo(parent)
, m_requestData( ifds::DSTC0386_REQ )
{
    TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

    setObjectAsList( );
}

//******************************************************************************
AcctLvlSttlmntRuleList::~AcctLvlSttlmntRuleList(void)
{
    TRACE_DESTRUCTOR( CLASSNAME );   
}

//******************************************************************************
void AcctLvlSttlmntRuleList::getStrKey( DString &dstrKey, const BFData *data)
{
   if ( data )
   {
      DString dstrRuleType        = data->getElementValue (ifds::RuleType );
      DString dstrEffectiveDate   = data->getElementValue (ifds::EffectiveDate );
      DString dstrStopDate        = data->getElementValue (ifds::StopDate );
      DString dstrFundCode        = data->getElementValue (ifds::FundCode );
      DString dstrClassCode       = data->getElementValue (ifds::ClassCode );
	  DString dstrFundGroup       = data->getElementValue (ifds::FundGroup );

      buildKey( dstrKey,
                _accountNum,
                dstrRuleType,
                dstrFundCode,
                dstrClassCode,
                dstrEffectiveDate,
				dstrStopDate,
				dstrFundGroup);
   }
   else
   {
      BFCBO::getStrKey (dstrKey, NULL);
   }
}

//******************************************************************************
SEVERITY AcctLvlSttlmntRuleList::initNew( const DString &strAccountNumber,
                                          const BFDataGroupId& idDataGroup,
                                          const DString &strTrack,
                                          const DString &strPageName
                                     )
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initNew" ) );

    //setFieldNoValidate(ifds::AccountNum, strAccountNumber, idDataGroup, false ); 
    _accountNum = strAccountNumber;

    return( GETCURRENTHIGHESTSEVERITY() );
}

//******************************************************************************
SEVERITY AcctLvlSttlmntRuleList::init( const DString &strAccountNumber,
                                       const BFDataGroupId& idDataGroup,
                                       const DString &strRuleType,
                                       const DString &strFundCode,
                                       const DString &strClassCode,
                                       const DString &strTrack,
                                       const DString &strPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   _accountNum = strAccountNumber;

   BFData responseData(ifds::DSTC0386_VW);

   // Set request fields
   //m_requestData.setElementValue( ifds::NextKey, NULL_STRING );
   m_requestData.setElementValue( ifds::Track, strTrack );
   m_requestData.setElementValue( ifds::Activity, strPageName );
   m_requestData.setElementValue( ifds::AccountNum, strAccountNumber );
   m_requestData.setElementValue( ifds::RuleType, strRuleType );
   m_requestData.setElementValue( ifds::InquiryType, I_("SETMNTRULE") );

   DString mgmtCoIdOut;
   m_requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );

   ReceiveData( DSTC_REQUEST::ACCT_CONTROL_INQUIRY, m_requestData, ifds::DSTC0386_VW, DSTCRequestor(getSecurity()) );

   return( GETCURRENTHIGHESTSEVERITY() );
}

//******************************************************************************
SEVERITY AcctLvlSttlmntRuleList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   pObjOut =  new AcctLvlSttlmntRule( *this );
   ((AcctLvlSttlmntRule*) pObjOut )->init( data );

   return( GETCURRENTHIGHESTSEVERITY() );
}

//******************************************************************************
SEVERITY AcctLvlSttlmntRuleList::doCreateNewObject( BFCBO *&pObjOut, 
                                                    DString &strKey, 
                                                    const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

   pObjOut =  new AcctLvlSttlmntRule( *this );
   ((AcctLvlSttlmntRule*) pObjOut )->initNew( _accountNum, idDataGroup );

   return( GETCURRENTHIGHESTSEVERITY() );
}

//******************************************************************************
void AcctLvlSttlmntRuleList::buildKey( DString &dstrKey, 
                const DString &dstrAccountNum,
                const DString &dstrRuleType,
                const DString &dstrFundCode,
                const DString &dstrClassCode,
                const DString &dstrEffectiveDate,
                const DString &dstrStopDate,
				const DString &dstrFundGroup)
{
    DString dstrLocalAccountNum(dstrAccountNum),
            dstrLocalRuleType(dstrRuleType),
            dstrLocalFundCode(dstrFundCode),
            dstrLocalClassCode(dstrClassCode),
            dstrLocalEffectiveDate (dstrEffectiveDate),
			dstrLocalStopDate (dstrStopDate),
			dstrLocalFundGroup(dstrFundGroup);   

    dstrKey = I_("AccountNum=")     + dstrLocalAccountNum.stripAll().upperCase()    +
              I_(";RuleType=")      + dstrLocalRuleType.stripAll().upperCase()      +
              I_(";FundCode=")      + dstrLocalFundCode.stripAll().upperCase()      +
              I_(";ClassCode=")     + dstrLocalClassCode.stripAll().upperCase()     +
              I_(";EffectiveDate=") + dstrLocalEffectiveDate.stripAll().upperCase() +
              I_(";StopDate=")      + dstrLocalStopDate.stripAll().upperCase()      +
			  I_(";FundGroup=")     + dstrLocalFundGroup.stripAll().upperCase();
}

//******************************************************************************
SEVERITY AcctLvlSttlmntRuleList::getAcctLvlSttlmntRule( AcctLvlSttlmntRule *&pAcctLvlSttlmntRule, 
                                                        const BFDataGroupId &idDataGroup,
                                                        const DString &dstrRuleType,
                                                        const DString &dstrFundCode,
                                                        const DString &dstrClassCode,
                                                        const DString &dstrEffectiveDate,
                                                        const DString &dstrStopDate,
														const DString &dstrFundGroup) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getAcctLvlSttlmntRule" ) );

   pAcctLvlSttlmntRule = NULL;

   DString dstrKey, dstrAccountNum;

   MFCanBFCbo* pParentCBO = dynamic_cast<MFCanBFCbo *>( getParent() );

   pParentCBO->getField( ifds::AccountNum, dstrAccountNum, idDataGroup );
   buildKey( dstrKey, dstrAccountNum, dstrRuleType, dstrFundCode, dstrClassCode, dstrEffectiveDate, dstrStopDate,dstrFundGroup );

   pAcctLvlSttlmntRule = dynamic_cast<AcctLvlSttlmntRule*>( getObject( dstrKey, idDataGroup ) );

   return( GETCURRENTHIGHESTSEVERITY() );
}

//******************************************************************************
SEVERITY AcctLvlSttlmntRuleList::doValidateAll( const BFDataGroupId& idDataGroup, 
                                                long lValidateGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   // Check for duplicates of 
   std::set< DString > setAcctSettlementRules;
   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   while( !iter.end() )
   {
      ++iter; 
   }

   return( GETCURRENTHIGHESTSEVERITY() );
}

//******************************************************************************
SEVERITY AcctLvlSttlmntRuleList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

   if( doMoreRecordsExist() )
   {
      ReceiveData( DSTC_REQUEST::ACCT_CONTROL_INQUIRY, m_requestData, ifds::DSTC0386_VW, DSTCRequestor(getSecurity()) );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AcctSettlementRuleList.cpp-arc  $
// 
//    Rev 1.4   Jan 31 2011 18:04:12   dchatcha
// P0179308 FN01 - Multi Manager Subscription and Direct Debit Payment.
// 
//    Rev 1.3   Apr 16 2008 18:49:08   daechach
// PET2385 FN02&07 - Modified code regarding code review.
// 
//    Rev 1.2   28 Mar 2008 12:10:48   kovacsro
// PET2385FN02&07 - some more code cleanup
// 
//    Rev 1.1   26 Mar 2008 15:50:30   kovacsro
// PET2385 FN02&07 - code review
*
*/

