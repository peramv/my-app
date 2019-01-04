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
//    ^FILE   : ProtectedFund.cpp
//    ^AUTHOR : Serban Popescu
//    ^DATE   : 01/08/2003
//    Copyright 2000 by DST Canada, Inc.
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : ProtectedFund
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include "ProtectedFund.hpp"
#include "FundClassRules.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include <ifastdataimpl\dse_dstc0237_vwrepeat_record.hpp>

namespace 
{
   const I_CHAR *  CLASSNAME = I_( "ProtectedFund" );
}

namespace CND
{  // Conditions used
   extern const long ERR_EFFECTIVE_DATE_LATE_THAN_STOP_DATE;
   extern const long ERR_MATURITY_YEAR_GREATER_ZERO;
}

namespace ifds
{
   //field ids used
   extern CLASS_IMPORT const BFTextFieldId FundNumber;
   extern CLASS_IMPORT const BFTextFieldId FundClass;
   extern CLASS_IMPORT const BFTextFieldId CompoundDate;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
   //  Field DD Id,        State Flags,       Group Flags 
   { ifds::ProtectedFundRId,  BFCBO::NONE, 0 }, 
   { ifds::FundCode, BFCBO::REQUIRED, 0 }, 
   { ifds::ClassCode, BFCBO::REQUIRED, 0 }, 
   { ifds::EffectiveDate, BFCBO::REQUIRED, 0 }, 
   { ifds::StopDate, BFCBO::REQUIRED, 0 }, 
   { ifds::InsurCode, BFCBO::REQUIRED, 0 }, 
   { ifds::InsurCost, BFCBO::NONE, 0 }, 
   { ifds::ContractGapType, BFCBO::REQUIRED, 0 }, 
   { ifds::ResetsAllowed, BFCBO::REQUIRED, 0 }, 
   { ifds::MaturityYears, BFCBO::REQUIRED, 0 }, 
   { ifds::ModDate, BFCBO::NONE, 0 }, 
   { ifds::ModUser, BFCBO::NONE, 0 }, 
   { ifds::Username, BFCBO::NONE, 0 }, 
   { ifds::ProcessDate, BFCBO::NONE, 0 }, 
   { ifds::FundNumber, BFCBO::NONE, 0 }, 
   //cross edits
   { ifds::FundClass, BFCBO::IMMEDIATE_VALIDATION, 0 }, 
   { ifds::CompoundDate,BFCBO::IMMEDIATE_VALIDATION,0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );
//******************************************************************************
ProtectedFund::ProtectedFund( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent ),
m_bSettingFundClass(false),
m_bSettingFundNumber(false),
m_pFundClassRules(NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL );
   //fund class
   addCrossEdit(ifds::FundClass, ifds::FundCode);
   addCrossEdit(ifds::FundClass, ifds::ClassCode);
   //compund date
   addCrossEdit(ifds::CompoundDate, ifds::EffectiveDate);
   addCrossEdit(ifds::CompoundDate, ifds::StopDate);
   m_pFundClassRules = new FundClassRules(*this);
}

//******************************************************************************
ProtectedFund::~ProtectedFund()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   if (m_pFundClassRules != NULL) 
   {
      delete m_pFundClassRules;
   }
}

//******************************************************************************
SEVERITY ProtectedFund::init(const BFData &viewData)
{
   MAKEFRAME2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );

   m_pFundClassRules->init();
   attachDataObject( const_cast<BFData&>( viewData ), false, true );
   setFieldReadOnly(ifds::FundCode, BF::HOST, true);
   setFieldReadOnly(ifds::ClassCode, BF::HOST, true);
   setFieldReadOnly(ifds::FundNumber, BF::HOST, true);
   clearUpdatedFlags(BF::HOST, true);
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY ProtectedFund::init(const BFDataGroupId& idDataGroup)
{
   MAKEFRAME2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));
   DString dstrCurrBusDate;
   MgmtCoOptions *pMgmtCoOptions = NULL;

   m_pFundClassRules->init();
   getMgmtCo().getMgmtCoOptions( pMgmtCoOptions );
   if( pMgmtCoOptions )
   {
      pMgmtCoOptions->getField(ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false);
      setFieldNoValidate(ifds::EffectiveDate, dstrCurrBusDate, idDataGroup);

   }
   setFieldNoValidate(ifds::StopDate, I_("12319999"), idDataGroup);
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY ProtectedFund::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

   if( idField == ifds::FundClass )
      setFundNumber(idDataGroup);
   else if( idField == ifds::FundNumber )
      setFundClassCode(idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY ProtectedFund::doValidateField( const BFFieldId& idField, 
   const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );
   
   if( idField == ifds::FundCode )
      m_pFundClassRules->validateFundCode(idDataGroup );
   else if( idField == ifds::ClassCode )
      m_pFundClassRules->validateClassCode( idDataGroup );
   else if( idField == ifds::FundNumber )
      m_pFundClassRules->validateFundNumber(idDataGroup);
   else if( idField == ifds::FundClass )
      m_pFundClassRules->validateFundClass( idDataGroup );
   else if( idField == ifds::CompoundDate )
      validateDate(idDataGroup );
   else if( idField == ifds::MaturityYears ) {
      double dYears = DSTCommonFunctions::convertToDouble ( strValue );
      if ( dYears < 1 ) {
         ADDCONDITIONFROMFILE( CND::ERR_MATURITY_YEAR_GREATER_ZERO );
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY ProtectedFund::setFundClassCode(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setFundClassCode" ) );

   DString dstrFundNumber,dstrFundCode,dstrClassCode;

   getField(ifds::FundNumber, dstrFundNumber, idDataGroup, false);

   if(!dstrFundNumber.strip().empty())
   {
      if( !m_bSettingFundNumber && 
         getWorkSession().GetFundClassCode(dstrFundNumber, dstrFundCode, dstrClassCode))
      {
         m_bSettingFundClass = true;
         setField(ifds::FundCode, dstrFundCode, idDataGroup, false, true);
         setField( ifds::ClassCode, dstrClassCode, idDataGroup, false,true); 
         m_bSettingFundClass = false;
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY ProtectedFund::setFundNumber(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setFundNumber" ) );

   DString dstrFundNumber, dstrFundCode, dstrClassCode;

   getField(ifds::FundCode,dstrFundCode,idDataGroup,false);
   getField(ifds::ClassCode,dstrClassCode,idDataGroup,false);
   getWorkSession().GetFundNumber(dstrFundCode.strip().upperCase(), 
      dstrClassCode.strip().upperCase(), dstrFundNumber);

   if(!m_bSettingFundClass)
   {
      m_bSettingFundNumber = true;
      setField( ifds::FundNumber, dstrFundNumber, idDataGroup, false, true);
      m_bSettingFundNumber = false;
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//*************************************************************
SEVERITY ProtectedFund::validateDate(const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateDate" ) );
   DString dstrEffectiveDate, dstrStopDate;

   getField(ifds::EffectiveDate, dstrEffectiveDate, idDataGroup);
   getField(ifds::StopDate, dstrStopDate, idDataGroup);
   if( DSTCommonFunctions::CompareDates( dstrStopDate, dstrEffectiveDate ) 
       != DSTCommonFunctions::SECOND_EARLIER )
   {
      ADDCONDITIONFROMFILE( CND::ERR_EFFECTIVE_DATE_LATE_THAN_STOP_DATE );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ProtectedFund.cpp-arc  $
// 
//    Rev 1.10   Nov 14 2004 14:51:12   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.9   Mar 21 2003 18:20:20   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.8   Mar 06 2003 10:25:36   HSUCHIN
// PTS 10014501 - Maturity years field requirement
// 
//    Rev 1.7   Feb 27 2003 14:12:48   HSUCHIN
// PTS - 10014239 make effective date, maturity years and resets allowed required.
// 
//    Rev 1.6   Feb 26 2003 15:09:20   popescu
// do not look for FundNumber anymore, since the view is sending it back
// 
//    Rev 1.5   Feb 14 2003 11:18:34   popescu
// grayed out the fund elements if the protected fund record exists
// 
//    Rev 1.4   Jan 26 2003 15:50:54   popescu
// Added the Revsion Control entry section
// 
//    Rev 1.3   Jan 20 2003 15:43:52   popescu
// Checked in for unit testing the ProtectedFundSetup feature
// 
 */