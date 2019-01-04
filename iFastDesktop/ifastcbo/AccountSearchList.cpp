//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1999 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : AccountSearchList.cpp
// ^AUTHOR : 
// ^DATE   : 03/11/99
//
// ^CLASS    : AccountSearchList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : This list handles the server response after a search. Keeps a list of 
//                      entities.
//
//******************************************************************************

#include "stdafx.h"
#include "accountsearchlist.hpp"
#include <ifastdataimpl\dse_dstc0198_req.hpp>
#include <ifastdataimpl\dse_dstc0198_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ACCOUNT_SEARCH;
}

namespace CND
{  // Conditions used
   extern const long ERR_ENTRY_EMPTY_OR_CONTAINS_ONLY_SPACE;
   extern const long ERR_INVALID_CHAR;
   extern const long ERR_ENTRY_BOTH_FIELDS;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "AccountSearchList" );

   const I_CHAR * const MORERECORDSEXIST = I_( "moreRecordsExist" );
   const I_CHAR * const DOVALIDATEFIELD = I_( "doValidateField" );
   const I_CHAR * const INIT = I_( "init" );
}

//******************************************************************************
AccountSearchList::AccountSearchList( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent ), 
_requestData( NULL ) 
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   setObjectAsList();
}

//******************************************************************************
AccountSearchList::~AccountSearchList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
   delete _requestData;
   _requestData = NULL;
}

//******************************************************************************
SEVERITY AccountSearchList::init( DString& _srchAltAcct,
                                  DString& _SrchBrokerCode,
                                  DString& _OneAcctOnly,
                                  const DString& dstrTrack,
                                  const DString& dstrPageName,
                                  const DString& dstrOverrideRepeats,
                                  const DString& dstrNextOrPrevious )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, INIT );

   if( _requestData == NULL )
   {
      _requestData =  new BFData(ifds::DSTC0198_REQ);
   }
   if( _requestData != NULL )
   {
      DString mgmtCoIdOut;
      _requestData->setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
      _requestData->setElementValue( ifds::Track, dstrTrack );
      _requestData->setElementValue( ifds::Activity, dstrPageName );
      _requestData->setElementValue( ifds::OverrideRepeats, dstrOverrideRepeats );
      _requestData->setElementValue( ifds::NextOrPrevious, dstrNextOrPrevious );
      _requestData->setElementValue( ifds::SrchAltAcct, _srchAltAcct );
      _requestData->setElementValue( ifds::SrchBroker, _SrchBrokerCode );
      _requestData->setElementValue( ifds::OneAcctOnly, _OneAcctOnly );
   }
   try
   {
      // BUZILAMI for Ident Account we want to have DATA_NOT_FOUND as an error (4th param of DSTCRequestor::DSTCRequestor(...) made true
      ReceiveData(DSTC_REQUEST::ACCOUNT_SEARCH,*_requestData, ifds::DSTC0198_VW, DSTCRequestor( getSecurity(), true) );      
   }
   catch( ConditionException &ce )
   {
      throw ce;
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************

SEVERITY AccountSearchList::doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, DOVALIDATEFIELD );

/*   DString tmp( strValue );
   if ( idField == ifds::SrchAccountNum )
   {
      if ( isStringEmptyOrJustContainSpace( strValue ) )
      {
         throw EXCEPTIONFROMFILE( CND::ERR_ENTRY_EMPTY_OR_CONTAINS_ONLY_SPACE );
      }
   }*/
   return(GETCURRENTHIGHESTSEVERITY()); 
}

//******************************************************************************
bool AccountSearchList::isStringEmptyOrJustContainSpace( const DString& str )
{
   DString tmp( str );
   return(tmp == NULL_STRING || tmp.strip() == NULL_STRING);
}

//******************************************************************************
bool AccountSearchList::containOnlyAllowedChars( const DString& AllowedChars, const DString& str )
{
   bool rte = true;

   for( DString::size_type i = 0; i < str.length(); ++i )
      if( AllowedChars.find( str[ i ] ) == -1 )
      {
         rte = false;
         break;
      }
   return(rte);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AccountSearchList.cpp-arc  $
// 
//    Rev 1.6   Nov 17 2004 15:02:02   PURDYECH
// PET910 - .NET Conversion:  Fixed compiler warning messages
// 
//    Rev 1.5   Mar 21 2003 17:55:14   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.4   Oct 09 2002 23:53:54   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.3   Aug 29 2002 12:54:54   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.2   22 May 2002 18:26:14   PURDYECH
// BFData Implementation
// 
//    Rev 1.1   Feb 07 2002 16:53:18   FENGYONG
// change receive flag
 * 
*/