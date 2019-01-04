//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2003 by International Financial.
//
//
//******************************************************************************
//
// ^FILE   : Branch.cpp
// ^AUTHOR : 
// ^DATE   : Mar 04, 2003
//
// ^CLASS    : Branch
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "branch.hpp"
#include <ifastdataimpl\dse_dstc0091_vw.hpp>

namespace
{
   const I_CHAR * const CLASSNAME = I_( "Branch" );   
}

namespace CND
{
	extern const long ERR_BRANCH_INVALID_AS_OF_DATE;
	extern const long ERR_BRANCH_NOT_EFFECTIVE;   
}

//****************************************************************************
// Constructor
//****************************************************************************
Branch::Branch( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
}

//****************************************************************************
// Destructor
//****************************************************************************
Branch::~Branch()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}     

//****************************************************************************
//Initializes the CBO
//@param const BFData& InstData - Data object to attach to BranchList.
//@returns SEVERITY
//****************************************************************************
SEVERITY Branch::init( const BFData& InstData )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   attachDataObject( const_cast<BFData&>(InstData), false, true );
   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************
//Compares the date passed in with the effective and stop date of the Branch.
//Returns NO_CONDITION when the date passed in is within the effective and stop
//date range.
//@param const DString& dstAsOfDate - Date to compare to.
//       const BFDataGroupId& idDataGroup - current data group id.
//@returns SEVERITY - ERR_BRANCH_INVALID_AS_OF_DATE - date is later than stop date
//                    ERR_BRANCH_NOT_EFFECTIVE - date is before effective date.
//****************************************************************************
SEVERITY Branch::checkEffective( const DString& dstrAsOfDate, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "checkEffective" ) );
   DString dstrEffectiveDate, dstrStopDate, idiStr;
   getField( ifds::StopDate, dstrStopDate, idDataGroup, false );
   getField( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false );   
   if ( (DSTCommonFunctions::CompareDates( dstrStopDate,dstrAsOfDate) != DSTCommonFunctions::SECOND_EARLIER) ) {            
      getField( ifds::StopDate, dstrStopDate, idDataGroup, true );
      addIDITagValue( idiStr, I_("DATE"), dstrStopDate);
      ADDCONDITIONFROMFILEIDI( CND::ERR_BRANCH_INVALID_AS_OF_DATE, idiStr );
   } else if ( (DSTCommonFunctions::CompareDates( dstrAsOfDate, dstrEffectiveDate ) == DSTCommonFunctions::FIRST_EARLIER) ) {
      getField( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, true );
      addIDITagValue( idiStr, I_("DATE"), dstrEffectiveDate);
      ADDCONDITIONFROMFILEIDI( CND::ERR_BRANCH_NOT_EFFECTIVE, idiStr );            
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/Branch.cpp-arc  $
// 
//    Rev 1.3   Jul 27 2005 18:43:10   AGUILAAM
// IN 353952 - refine validations of Systematic records against broker/branch/rep effective/stop dates.
// 
//    Rev 1.2   Nov 14 2004 14:29:12   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.1   Mar 21 2003 18:00:52   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.0   Mar 05 2003 12:04:44   HSUCHIN
// Initial revision.
 */