#error "This file is obsolete"
//Please use FinancialInstitutioList.cpp instead
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
// ^FILE   : BankSearch.cpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 03/08/01
//
// ^CLASS    : BankSearch
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "banksearch.hpp"
#include <dataimpl\dse_dstc0100_req.hpp>
#include <dataimpl\dse_dstc0100_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest BANKLIST;
}


namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME = I_( "BankSearch" );
}

//******************************************************************************
BankSearch::BankSearch( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
}

//******************************************************************************
BankSearch::~BankSearch( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY BankSearch::init( const DString&  dstrTrack, const DString&  dstrPageName )

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   BFData requestData( ifds::DSTC0100_REQ);

   DString mgmtCoIdOut;
   requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   requestData.setElementValue( ifds::SearchType, I_("A") );
   requestData.setElementValue( ifds::BankType, NULL_STRING );
   requestData.setElementValue( ifds::BankIdNum, NULL_STRING );
   requestData.setElementValue( ifds::TransitNo, NULL_STRING );
   requestData.setElementValue( ifds::Track, dstrTrack );
   requestData.setElementValue( ifds::Activity, dstrPageName );

   ReceiveData(DSTC_REQUEST::BANKLIST, requestData, ifds::DSTC0100_VW, DSTCRequestor( getSecurity(), true ) );


   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
// this init is used to search bank
// we can use name or code to search bank

SEVERITY BankSearch::init( const DString&  dstrBankType,
                           const DString&  dstrBankIdNum, //code
                           const DString&  dstrInstName, //Name
                           const DString&  dstrTrack,
                           const DString&  dstrPageName)                

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   BFData requestData( ifds::DSTC0100_REQ);

   DString mgmtCoIdOut;
   requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   requestData.setElementValue( ifds::SearchType, I_("S") );
   requestData.setElementValue( ifds::BankIdNum, dstrBankIdNum );  //BankId
   requestData.setElementValue( ifds::BankType, dstrBankType );  
   requestData.setElementValue( ifds::InstName, dstrInstName );   
   requestData.setElementValue( ifds::Track, dstrTrack );
   requestData.setElementValue( ifds::Activity, dstrPageName );
   requestData.setElementValue( ifds::TransitNo, NULL_STRING );

   ReceiveData(DSTC_REQUEST::BANKLIST, requestData, ifds::DSTC0100_VW, DSTCRequestor( getSecurity(), true, true ) );

   return(GETCURRENTHIGHESTSEVERITY());
}
//****************************************************************************
// this init is used to search bank 
// we can use bankType, BankIdNum or TransitNo to search bank
// test for qaslot22: I_("03"),I_("00001234"),I_("000123") 
// this is for the validation purpose
SEVERITY BankSearch::init2( const DString&  dstrBankType, //BankType
                            const DString&  dstrBankIdNum, //BankId
                            const DString&  dstrTransitNo, // TransitNo
                            const DString&  dstrTrack,
                            const DString&  dstrPageName)                

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   BFData requestData( ifds::DSTC0100_REQ);

   DString mgmtCoIdOut;
   requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   requestData.setElementValue( ifds::SearchType, I_("S") );
   requestData.setElementValue( ifds::BankIdNum, dstrBankIdNum );
   requestData.setElementValue( ifds::TransitNo, dstrTransitNo );   
   requestData.setElementValue( ifds::BankType, dstrBankType );   
   requestData.setElementValue( ifds::Track, dstrTrack );
   requestData.setElementValue( ifds::Activity, dstrPageName );

   ReceiveData(DSTC_REQUEST::BANKLIST, requestData, ifds::DSTC0100_VW, DSTCRequestor( getSecurity() ,true ) );

   return(GETCURRENTHIGHESTSEVERITY());
}


//*****************************************************************************
bool BankSearch::IsValueExistInBankSearch(const BFFieldId& fieldID, const DString& Value)
{
   DString str;

   BFObjIter iter( *this, BF::HOST );

   while( !iter.end() )
   {
      iter.getObject( )->getField(fieldID, str, BF::HOST, true );

      if( str.asInteger() == Value.asInteger() )
         return(true);
      else
         ++iter;
   }

   return(false);
}
//****************************************************************************
bool BankSearch::validateInstCodeTransitNo( const DString& InstCode, const DString& TransitNo )
{
   DString BankType = I_("03"); // Canadian Bank
   init2( BankType, InstCode, TransitNo );
   BFObjIter iter( *this, BF::HOST );
   if( iter.end() ) return(false);  // no record found
   return(true);

}
/******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/BankSearch.cpp-arc  $
// 
//    Rev 1.11   Nov 14 2004 14:29:04   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.10   Oct 04 2003 15:57:40   popescu
// CIBC PET 809, FN 13;
// also cleaned-up BankSearch and BankList objects,
// replaced with FinancialInstitutionList
// 
//    Rev 1.9   Mar 21 2003 18:00:36   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.8   Oct 09 2002 23:54:06   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.7   Aug 29 2002 12:55:08   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.6   22 May 2002 18:26:30   PURDYECH
// BFData Implementation
// 
//    Rev 1.5   Aug 16 2001 10:59:36   YINGBAOL
// using bankIdNum instead of BankId to do searching
// 
//    Rev 1.4   09 May 2001 14:42:36   HSUCHIN
// Sync up with SSB
// 
//    Rev 1.3   03 May 2001 14:06:02   SMITHDAV
// Session management restructuring.
// 
//    Rev 1.2   Apr 03 2001 15:19:36   YINGBAOL
// add method "validateInstCodeTransitNo()"
// 
//    Rev 1.1   Mar 23 2001 03:36:58   YINGBAOL
// make it work
// 
//    Rev 1.0   Mar 08 2001 15:20:32   ZHANGCEL
// Initial revision.
 * 
 */






