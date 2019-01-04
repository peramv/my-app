#error "This file is obsolete"
//Use FinancialInstitutionList.cpp instead

/*
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
// ^FILE   : BankList.cpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 03/22/99
//
// ^CLASS    : BankList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "banklist.hpp"
#include <dataimpl\dse_dstc0100_req.hpp>
#include <dataimpl\dse_dstc0100_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest BANKLIST;
}

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME = I_( "BankList" );
}

//******************************************************************************
BankList::BankList( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
}

//******************************************************************************
BankList::~BankList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY BankList::init( const DString& dstrTrack,const DString& dstrPageName)                

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   BFData requestData( ifds::DSTC0100_REQ);

   DString mgmtCoIdOut;
   requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   requestData.setElementValue( ifds::Track, dstrTrack );
   requestData.setElementValue( ifds::Activity, dstrPageName );

   ReceiveData(DSTC_REQUEST::BANKLIST, requestData, ifds::DSTC0100_VW, DSTCRequestor( getSecurity(), true) );

   return(GETCURRENTHIGHESTSEVERITY());
}
//*****************************************************************************
bool BankList::IsValueExistInBankList(const BFFieldId& fieldID, const DString& Value)
{
   DString str;

   BFObjIter iter( *this, BF::HOST );

   while( !iter.end() )
   {
      iter.getObject( )->getField( fieldID, str, BF::HOST, true );

      if( str.asInteger() == Value.asInteger() )
         return(true);
      else
         ++iter;
   }

   return(false);
}

/******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/BankList.cpp-arc  $
 * 
 *    Rev 1.15   Nov 14 2004 14:29:02   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.14   Oct 04 2003 15:57:36   popescu
 * CIBC PET 809, FN 13;
 * also cleaned-up BankSearch and BankList objects,
 * replaced with FinancialInstitutionList
 * 
 *    Rev 1.13   Mar 21 2003 18:00:32   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.12   Oct 09 2002 23:54:04   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.11   Aug 29 2002 12:55:08   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.10   22 May 2002 18:26:30   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.9   03 May 2001 14:06:00   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.8   Jan 18 2001 16:04:10   YINGBAOL
 * add eTracker
 * 
 *    Rev 1.7   Dec 17 2000 20:22:40   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.6   Dec 06 2000 10:13:30   OLTEANCR
 * change in ReceiveData
 * 
 *    Rev 1.5   Nov 07 2000 16:40:26   VASILEAD
 * Set the locale in the init
 * 
 *    Rev 1.4   Nov 03 2000 14:59:06   YINGBAOL
 * get security from userdession instead of work session
 * 
 *    Rev 1.3   Nov 02 2000 13:35:30   YINGBAOL
 * use new databroker
 * 
 *    Rev 1.2   Aug 04 2000 13:58:14   YINGBAOL
 * change enquiry bank 
 * 
 *    Rev 1.1   Aug 01 2000 09:48:56   YINGBAOL
 * add business rules
 *
 
*/
