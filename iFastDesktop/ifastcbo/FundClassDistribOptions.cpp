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
//    Copyright 2007 by IFDS Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : FundClassDistribOptions.cpp
// ^AUTHOR : Chatchai Daecha
// ^DATE   : 06/04/07
//
// ^CLASS    : FundClassDistribOptions
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "FundClassDistribOptions.hpp"
#include <ifastdataimpl\dse_dstc0379_vwrepeat_record.hpp>

namespace CND
{  // Conditions used
   
};


namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME = I_( "FundClassDistribOptions" );  
   const I_CHAR * const CASH      = I_( "CASH" );
   const I_CHAR * const CS        = I_( "CS" );  
   const I_CHAR * const RI        = I_( "RI" );  
   const I_CHAR * const RD        = I_( "RD" );  
};

////////////////////////////////////////////////////////////////////////////////////////////

FundClassDistribOptions::FundClassDistribOptions(BFAbstractCBO &parent)
: MFCanBFCbo( parent )
{
	TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
}

FundClassDistribOptions::~FundClassDistribOptions(void)
{
	TRACE_DESTRUCTOR( CLASSNAME );
}

SEVERITY FundClassDistribOptions::init(const BFData& data)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

	attachDataObject( const_cast<BFData&>(data), false );

	return(GETCURRENTHIGHESTSEVERITY());
}

bool FundClassDistribOptions::isCashAllowed(const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "isCashAllowed" ) );

	DString strOverrideOpt,strDefInvestOpt;
	getField(ifds::OverrideOpt,strOverrideOpt,idDataGroup);
	getField(ifds::DefInvestOpt,strDefInvestOpt,idDataGroup);
   strOverrideOpt.strip().upperCase();
   strDefInvestOpt.strip().upperCase();

	return isCodeInList (CS, strOverrideOpt) || 
          isCodeInList (CS, strDefInvestOpt);
}

bool FundClassDistribOptions::isReinvestmentAllowed ( const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "isReinvestmetnAllowed" ) );

	DString strOverrideOpt,strDefInvOpt;

	getField(ifds::OverrideOpt,strOverrideOpt,idDataGroup);
	getField(ifds::DefInvestOpt,strDefInvOpt,idDataGroup);
   strOverrideOpt.strip().upperCase();
   strDefInvOpt.strip().upperCase();

	return isCodeInList (RI, strOverrideOpt) ||
          isCodeInList (RI, strDefInvOpt);
}

bool FundClassDistribOptions::isRedistributionAllowed(const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "isRedistributionAllowed" ) );

	DString strOverrideOpt,strDefInvOpt;

	getField(ifds::OverrideOpt,strOverrideOpt,idDataGroup);
	getField(ifds::DefInvestOpt,strDefInvOpt,idDataGroup);
   strOverrideOpt.strip().upperCase();
   strDefInvOpt.strip().upperCase();

   return isCodeInList (RD, strOverrideOpt) ||
          isCodeInList (RD, strDefInvOpt);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FundClassDistribOptions.cpp-arc  $
// 
//    Rev 1.1   24 Jul 2007 20:12:52   popescu
// GAP 20 -22 AIM
 * 
 */
