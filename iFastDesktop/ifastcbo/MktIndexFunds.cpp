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
//    Copyright 2003 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : MktIndexFunds.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : MktIndexFunds
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : MktIndexFunds
//
//******************************************************************************
#include "stdafx.h"
#include "MktIndexFunds.hpp"
#include "fundmasterlist.hpp"
#include "funddetail.hpp"
#include "funddetaillist.hpp"
#include "MgmtCoOptions.hpp"
#include "mgmtco.hpp"

#include <ifastdataimpl\dse_dstc0241_vw.hpp>

namespace
{
   const I_CHAR * const CLASSNAME              = I_( "MktIndexFunds" );
   const I_CHAR * const NO                     = I_( "N" );
   const I_CHAR * const YES                    = I_( "Y" );
}

namespace CND
{  // Conditions used
///   extern const long 	ERR_FUND_STOP_TRANSFER;
   extern const long ERR_BLANK_FUND;
   extern const long ERR_INVALID_FUND_CLASS_CODES;
   extern const long ERR_BLANK_CLASS;
}

namespace UAF
{
///   extern CLASS_IMPORT I_CHAR * const MKT_INDEX_MASTER;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FundClass;
}
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,             Group Flags 
   { ifds::FundCode,   BFCBO::REQUIRED,                        0 }, 
   { ifds::ClassCode,  BFCBO::REQUIRED,                        0 }, 
   //cross edits
   { ifds::FundClass,  BFCBO::IMMEDIATE_VALIDATION, 0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************

MktIndexFunds::MktIndexFunds( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
   addCrossEdit(ifds::FundClass, ifds::FundCode);
   addCrossEdit(ifds::FundClass, ifds::ClassCode);
}

//******************************************************************************

MktIndexFunds::~MktIndexFunds( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************

SEVERITY MktIndexFunds::initNew( const BFDataGroupId& idDataGroup,
                              const DString& dstrTrack ,
                              const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initNew" ) );
   setObjectNew();
	checkUpdatePermission( BF::HOST );
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY MktIndexFunds::initExisting(const BFData &data)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initExisting" ) );
   attachDataObject( const_cast< BFData & >( data ), false, true ); 
	checkUpdatePermission( BF::HOST );
   clearUpdatedFlags( BF::HOST );
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY MktIndexFunds::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY MktIndexFunds::doValidateField( const BFFieldId& idField, const DString& dstrValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

   if( idField == ifds::FundCode )
   {
      validateFundCode( dstrValue, idDataGroup );
   }
   else if( idField == ifds::ClassCode )
   {
      validateClassCode( dstrValue, idDataGroup );
   }
   else if( idField == ifds::FundClass )
   {
      validateFundClass( idDataGroup );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY MktIndexFunds::validateFundCode( const DString& strValue, const BFDataGroupId& idDataGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFundCode" ) );

   DString dstrFundCode( strValue );

   if( dstrFundCode.strip().upperCase().empty() )
   {
      ADDCONDITIONFROMFILE( CND::ERR_BLANK_FUND );
      return(GETCURRENTHIGHESTSEVERITY());  
   }

   FundMasterList *pFundMasterList = NULL;
   if( getMgmtCo().getFundMasterList(pFundMasterList)<=WARNING && pFundMasterList )
   {
      if( !(pFundMasterList->IsFundExist( dstrFundCode, idDataGroup ) ) )
      {
         ADDCONDITIONFROMFILE( CND::ERR_INVALID_FUND_CLASS_CODES );
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY MktIndexFunds::validateClassCode( const DString& strValue, const BFDataGroupId& idDataGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateClassCode" ) );

   DString dstrClassCode( strValue );
   if( dstrClassCode.strip().empty() )
   {
      ADDCONDITIONFROMFILE( CND::ERR_BLANK_CLASS );
      return(GETCURRENTHIGHESTSEVERITY());
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************

SEVERITY MktIndexFunds::validateFundClass( const BFDataGroupId& idDataGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFundClass" ) );
   FundDetail *pFundDetail = NULL;
   DString dstrClassCode, dstrFundCode;
   getField(ifds::FundCode, dstrFundCode, idDataGroup, false);
   getField(ifds::ClassCode, dstrClassCode, idDataGroup, false);

   pFundDetail = NULL;
   FundDetailList * pFundDetailList = NULL;
   getMgmtCo().getFundDetailList(  pFundDetailList );
   if( pFundDetailList )
   {
      pFundDetailList->getFundDetail( dstrFundCode.strip().upperCase(), dstrClassCode.strip().upperCase(), BF::HOST, pFundDetail);
   }

   if( !pFundDetail )
   {
      ADDCONDITIONFROMFILE( CND::ERR_INVALID_FUND_CLASS_CODES );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************

void MktIndexFunds::checkUpdatePermission(const BFDataGroupId& idDataGroup)
{
/*
//	bool bPermit = getWorkSession().hasUpdatePermission(UAF::MKT_INDEX_MASTER );
	setFieldReadOnly( ifds::FundCode, idDataGroup, !bPermit );
	setFieldReadOnly( ifds::ClassCode, idDataGroup, !bPermit );
	setFieldReadOnly( ifds::FundNumber, idDataGroup, !bPermit );
*/
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/MktIndexFunds.cpp-arc  $
// 
//    Rev 1.2   Nov 14 2004 14:50:28   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.1   Mar 21 2003 18:19:10   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.0   Jan 23 2003 10:30:42   HERNANDO
// Initial Revision
 */