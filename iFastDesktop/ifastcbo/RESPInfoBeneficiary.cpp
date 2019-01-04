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
// ^FILE   : RESPInfoBeneficiary.cpp
// ^AUTHOR : Dan Petolescu
// ^DATE   : 11/01/2000
//
// ^CLASS    : RESPInfoBeneficiary
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "respinfobeneficiary.hpp"
#include "respinfo.hpp"
#include <ifastdataimpl\dse_dstc0066_req.hpp>
#include <ifastdataimpl\dse_dstc0066_vw.hpp>

namespace  
{
   const I_CHAR * const CLASSNAME = I_( "RESPInfoBeneficiary" );
}

const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = {
//  Object Label,    State Flags,         Group Flags 
   {  I_(""),        BFCBO::REQUIRED,         0}
};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );

//****************************************************************************
RESPInfoBeneficiary::RESPInfoBeneficiary( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   registerMemberData( 0,
                       NULL,
                       NUM_OBJECTS,
                       (const CLASS_OBJECT_INFO *)&classObjectInfo );
}

//****************************************************************************
RESPInfoBeneficiary::~RESPInfoBeneficiary()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}     

//****************************************************************************
SEVERITY RESPInfoBeneficiary::init( const BFData& InstData )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   attachDataObject( const_cast<BFData&>(InstData), false, true );

   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************
SEVERITY RESPInfoBeneficiary::doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

   if( idField == ifds::TerminateDate )
   {

   }
   else if( idField == ifds::MaturityDate )
   {


   }
   else if( idField == ifds::ToDateContr )
   {


   }
   else if( idField == ifds::PlanNum )
   {

   }
   else if( idField == ifds::GrantRepayable )
   {

   }
   else if( idField == ifds::CESGEligible )
   {

   }
   else if( idField == ifds::TDRedEarning )
   {

   }
   else if( idField == ifds::GFathered )
   {

   }
   else if( idField == ifds::CurrEarning )
   {

   }
   else if( idField == ifds::RESPStatus )
   {

   }
   else if( idField == ifds::RESPStatDesc )
   {

   }
   else if( idField == ifds::RedLifeContr )
   {

   }
   else if( idField == ifds::RedUCAmt )
   {

   }
   else if( idField == ifds::RedACAmt )
   {

   }
   else if( idField == ifds::RedNetGrant )
   {

   }
   else if( idField == ifds::AcctLifeContr )
   {

   }
   else if( idField == ifds::AcctUCAmt )
   {

   }
   else if( idField == ifds::AcctACAmt )
   {

   }
   else if( idField == ifds::AcctNetGrant )
   {

   }
   else if( idField == ifds::AcctEAP )
   {

   }
   else if( idField == ifds::BeneName )
   {

   }
   else if( idField == ifds::YTDContr )
   {

   }
   else if( idField == ifds::LifeContr )
   {

   }
   else if( idField == ifds::UnAssisted )
   {

   }
   else if( idField == ifds::Assisted )
   {

   }
   else if( idField == ifds::NetGrant )
   {

   }
   else if( idField == ifds::EAPayment )
   {

   }
   else
   {

   }
   return(GETCURRENTHIGHESTSEVERITY());
}

/******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RESPInfoBeneficiary.cpp-arc  $
 * 
 *    Rev 1.7   Nov 14 2004 14:52:22   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.6   Mar 21 2003 18:22:06   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.5   Oct 09 2002 23:54:52   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.4   Aug 29 2002 12:56:28   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.3   22 May 2002 18:29:42   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.2   03 May 2001 14:07:00   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.1   Dec 17 2000 20:24:18   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.0   Mar 22 2000 09:05:40   PETOLESC
 * Initial revision.
// 
//    Rev 1.0   Feb 16 2000 10:10:34   PETOLESC
// Initial revision.
 *
 * 
 *
 */