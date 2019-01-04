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
// ^FILE   : COANavig.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : COANavig
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "coanavig.hpp"
#include <ifastdataimpl\dse_dstc0049_req.hpp>
#include <ifastdataimpl\dse_dstc0049_vw.hpp>
#include <bfutil\bfdate.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest COA_NAVIG;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
   { ifds::PendingTrade, BFCBO::NONE, 0 }, 
   { ifds::Remarks,      BFCBO::NONE, 0 }, 
   { ifds::Certificates, BFCBO::NONE, 0 }, 
   { ifds::StopPurchase, BFCBO::NONE, 0 }, 
   { ifds::StopRed,      BFCBO::NONE, 0 }, 
   { ifds::StopXferOut,  BFCBO::NONE, 0 }, 
   { ifds::StopXferIn,   BFCBO::NONE, 0 }, 
   { ifds::BankingInstr, BFCBO::NONE, 0 }, 
   { ifds::SystemTrsfr,  BFCBO::NONE, 0 }, 
   { ifds::PAC,          BFCBO::NONE, 0 }, 
   { ifds::SWP,          BFCBO::NONE, 0 }, 
   { ifds::AcctAlloc,    BFCBO::NONE, 0 }, 
   { ifds::ClanPlan,     BFCBO::NONE, 0 }, 
   { ifds::UnsettledTrn, BFCBO::NONE, 0 }, 
   { ifds::CurrBusDate,  BFCBO::NONE, 0 } 
};

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "COANavig" );
   const I_CHAR * const DATE_FORMAT = I_( "MMddyyyy" );      
}

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
COANavig::COANavig( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );

   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}

//******************************************************************************
COANavig::~COANavig()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY COANavig::init()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY COANavig::init( const DString& AccountNum,
                         const DString& dstrTrack,
                         const DString& dstrPageName)                            
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   SEVERITY sevRtn = SEVERE_ERROR;

   BFData requestData(ifds::DSTC0049_REQ);

   DString mgmtCoIdOut;
   requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   requestData.setElementValue(ifds::AccountNum, AccountNum );

   //date stuff
   DString dstrConfiguration( I_( "HostMasks" ) );
   DString dstrKey( I_( "D" ) );
   DString mask = GetConfigValueAsString( I_( "LocaleFormats" ), dstrConfiguration, dstrKey );
   //BFDate currentDate( BFDate::today() );
   DString AsOfDate;
   getWorkSession().getOption( ifds::CurrBusDate, AsOfDate, BF::HOST, false );
   //if( !mask.length() )
   //{
   //   AsOfDate = AsOfDate.get( BFDate::DF_US );     // US Date format is default
   //}
   //else
   //{
   //   AsOfDate = currentDate.get( mask );
   //}

   requestData.setElementValue( ifds::AsofDate, AsOfDate, false, false );
   requestData.setElementValue( ifds::Track, dstrTrack );
   requestData.setElementValue( ifds::Activity, dstrPageName );

   ReceiveData(DSTC_REQUEST::COA_NAVIG, requestData, ifds::DSTC0049_VW, DSTCRequestor( getSecurity(), true) );



   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/COANavig.cpp-arc  $
 * 
 *    Rev 1.13   Nov 14 2004 14:29:42   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.12   Mar 21 2003 18:01:38   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.11   Oct 09 2002 23:54:08   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.10   Aug 29 2002 12:55:10   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.9   Jul 05 2002 11:49:38   PURDYECH
 * Infrastructure Fixup ... no more ICU!
 * 
 *    Rev 1.8   May 28 2002 12:18:38   PURDYECH
 * BFData Implementation - Phase II
 * 
 *    Rev 1.7   22 May 2002 18:26:34   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.6   03 May 2001 14:06:04   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.5   Jan 18 2001 16:04:12   YINGBAOL
 * add eTracker
 * 
 *    Rev 1.4   Dec 17 2000 20:22:46   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.3   Dec 06 2000 10:49:06   OLTEANCR
 * changed ReceiveData
 * 
 *    Rev 1.2   Nov 02 2000 13:23:20   YINGBAOL
 * use new databroker
 * 
 *    Rev 1.1   Feb 28 2000 15:31:08   PRAGERYA
 * Check-in For Mihai
 * 
 *    Rev 1.0   Feb 15 2000 10:59:50   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.12   Feb 03 2000 10:51:06   BUZILA
 * INIT_TO_DEFAULT flag took out
 * 
 *    Rev 1.11   Dec 12 1999 16:25:14   POPESCUS
 * Xchgdata issue; create and delete the object in the CBO
// 
*/