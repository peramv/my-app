//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1999 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : HostSubstitutionValuesList.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : 03/11/99
//
// ^CLASS    : HostSubstitutionValuesList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : This list handles the server response after a persistent transaction ends. 
//                      Keeps a list of substitutions values for temporary ids.
//
//******************************************************************************

#include "stdafx.h"
#include "hostsubstitutionvalueslist.hpp"
#include <ifastdataimpl\dse_dstc0074_req.hpp>
#include <ifastdataimpl\dse_dstc0074_vw.hpp>

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "HostSubstitutionValuesList" );

   const I_CHAR * const STOPPERSISTENTTRXN = I_( "stoppersistenttrxn" );
   const I_CHAR * const INIT = I_( "init" );
   const I_CHAR * const YES = I_( "Y" );
   const I_CHAR * const NO = I_( "N" );
}

namespace STOPPERSTAGS
{
   const I_CHAR * const KEYTYPE = I_( "KeyType" );
   const I_CHAR * const TEMPVALUE = I_( "TempValue" );
}

namespace KEYTYPES
{
   extern CLASS_IMPORT I_CHAR * const ENTITYID;
   extern CLASS_IMPORT I_CHAR * const SHRNUM;
   extern CLASS_IMPORT I_CHAR * const ACCOUNTNUM;
   extern CLASS_IMPORT I_CHAR * const SPONSORMODELID;
}

//******************************************************************************
HostSubstitutionValuesList::HostSubstitutionValuesList( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList();
}

//******************************************************************************
HostSubstitutionValuesList::~HostSubstitutionValuesList()
{
   TRACE_DESTRUCTOR( CLASSNAME );

}

//******************************************************************************
void HostSubstitutionValuesList::addSubstitutionData( BFData *substitutionData )
{
   attachDataObject( *substitutionData, true, true );
   createObjectForEachRepeat( *substitutionData );

}

//******************************************************************************
void HostSubstitutionValuesList::buildHostSubstValueKeyForTempAccount( DString &strKey, const DString& accountNum )
{
   //reset the key
   strKey = NULL_STRING;
   addIDITagValue( strKey, STOPPERSTAGS::KEYTYPE, KEYTYPES::ACCOUNTNUM );

   DString tempAccountNum( accountNum );

   tempAccountNum.stripLeading( '0' );
   tempAccountNum.strip();
   addIDITagValue( strKey, STOPPERSTAGS::TEMPVALUE, tempAccountNum );
}

//******************************************************************************
void HostSubstitutionValuesList::buildHostSubstValueKeyForTempEntity( DString &strKey, 
                                                                      const DString& entityId )
{
   //reset the key
   strKey = NULL_STRING;
   addIDITagValue( strKey, STOPPERSTAGS::KEYTYPE, KEYTYPES::ENTITYID );

   DString tempEntityId( entityId );

   tempEntityId.stripLeading( '0' );
   tempEntityId.strip();
   addIDITagValue( strKey, STOPPERSTAGS::TEMPVALUE, tempEntityId );
}

//******************************************************************************
void HostSubstitutionValuesList::buildHostSubstValueKeyForTempShareholder( DString &strKey, 
                                                                           const DString& shareholder )
{
   //reset the key
   strKey = NULL_STRING;
   addIDITagValue( strKey, STOPPERSTAGS::KEYTYPE, KEYTYPES::SHRNUM );

   DString tempShareholder( shareholder );

   tempShareholder.stripLeading( '0' );
   tempShareholder.strip();
   addIDITagValue( strKey, STOPPERSTAGS::TEMPVALUE, tempShareholder );
}

//******************************************************************************
void buildHostSubstValueKeyForTempFundSponsorModelId( DString &strKey, const DString& dstrSponsorModelID )
{
   //reset the key
   strKey = NULL_STRING;
   addIDITagValue( strKey, STOPPERSTAGS::KEYTYPE, KEYTYPES::SPONSORMODELID );

   DString tempSponsorModelID( dstrSponsorModelID );

   tempSponsorModelID.stripLeading( '0' );
   tempSponsorModelID.strip();
   addIDITagValue( strKey, STOPPERSTAGS::TEMPVALUE, tempSponsorModelID );
}
//******************************************************************************
void HostSubstitutionValuesList::buildHostSubstValueKey( DString& strKey, 
                                                         const DString& keyType, 
                                                         const DString& tempValue )
{
   //reset the key
   strKey = NULL_STRING;

   DString tempKeyType( keyType );
   DString tempTempValue( tempValue );

   tempKeyType.strip().stripLeading( '0' );
   addIDITagValue( strKey, STOPPERSTAGS::KEYTYPE, tempKeyType );
   tempTempValue.strip().stripLeading( '0' );
   addIDITagValue( strKey, STOPPERSTAGS::TEMPVALUE, tempTempValue );
}

//******************************************************************************
SEVERITY HostSubstitutionValuesList::init()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, INIT );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//the repeatable section of view #74
//the key will look like: KeyType=xxxx;TempValue=xxxx
void HostSubstitutionValuesList::getStrKey( DString &strKey, const BFData *data )
{
   if( data != NULL )
   {
      DString keyType, tempValue;

      data->getElementValue( ifds::KeyType, keyType );
      data->getElementValue( ifds::TempValue, tempValue );
      buildHostSubstValueKey( strKey, keyType, tempValue );
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/hostsubstitutionvalueslist.cpp-arc  $
 * 
 *    Rev 1.11   Nov 14 2004 14:44:20   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.10   Aug 10 2004 11:24:44   FENGYONG
 * PET 1117 FN 5 - Client condition Fee
 * 
 *    Rev 1.9   Mar 21 2003 18:13:46   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.8   Oct 09 2002 23:54:38   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.7   Aug 29 2002 12:56:02   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.6   22 May 2002 18:28:52   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.5   03 May 2001 14:06:40   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.4   16 Feb 2001 14:55:42   SMITHDAV
 * Fixed Substitution values. ??Some testing required??
 * 
 *    Rev 1.3   06 Feb 2001 11:48:26   SMITHDAV
 * Removed unused code and depenencies
 * 
 *    Rev 1.2   Jan 18 2001 16:05:14   YINGBAOL
 * add eTracker
 * 
 *    Rev 1.1   Dec 17 2000 20:23:48   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.0   Feb 15 2000 11:00:00   SMITHDAV
 * Initial revision.
// 
//    Rev 1.6   Jan 18 2000 11:29:50   POPESCUS
// fixed some of the settings of the global values (account & shareholder)
// 
//    Rev 1.5   Jan 16 2000 16:57:36   POPESCUS
// new methods to retrieve host subst values needed in refresh
// 
//    Rev 1.4   Jan 05 2000 20:10:52   BUZILA
// adding list flag
// 
//    Rev 1.3   Dec 17 1999 18:49:16   POPESCUS
// fixes related to the commit logic
// 
//    Rev 1.2   Dec 12 1999 16:25:38   POPESCUS
// Xchgdata issue; create and delete the object in the CBO
// 
*/