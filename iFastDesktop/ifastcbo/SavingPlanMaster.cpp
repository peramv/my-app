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
//    Copyright 1999 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : SavingPlanMaster.cpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 05/23/2001
//
// ^CLASS    : SavingPlanMaster
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "savingplanmaster.hpp"

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME = I_( "SavingPlanMaster" );
}

//******************************************************************************
SavingPlanMaster::SavingPlanMaster( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //setVersionable( false );

}


//******************************************************************************
SavingPlanMaster::~SavingPlanMaster()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY SavingPlanMaster::init( const BFData &data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );

   attachDataObject( const_cast<BFData&>( data ), false, true );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/SavingPlanMaster.cpp-arc  $
// 
//    Rev 1.6   Nov 24 2004 10:18:46   yingbaol
// PET1117:temperary take out version features
// 
//    Rev 1.5   Nov 18 2004 13:28:24   YINGBAOL
// PET1117: Perfermance Tunning
// 
//    Rev 1.4   Nov 14 2004 14:53:40   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.3   Oct 09 2002 23:54:56   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.2   Aug 29 2002 12:56:36   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.1   22 May 2002 18:29:50   PURDYECH
// BFData Implementation
// 
//    Rev 1.0   25 May 2001 15:05:20   YINGZ
// Initial revision.
*/