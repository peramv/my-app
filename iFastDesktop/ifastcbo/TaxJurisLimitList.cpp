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
// ^FILE   : TaxJurisLimitList.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : TaxJurisLimitList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "TaxJurisLimitList.hpp"
#include <ifastdataimpl\dse_dstc0211_vw.hpp>
#include <ifastdataimpl\dse_dstc0211_req.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest TAXJURISDICTIONLIMIT_LIST;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "TaxJurisLimitList" );
}

namespace CND
{
   extern CLASS_IMPORT const long ERR_DATA_NOT_FOUND;
}
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,							State Flags,				Group Flags
   { ifds::rxTaxType,    BFCBO::NONE, 0 }, 
   { ifds::PensionJuris, BFCBO::NONE, 0 }, 
   { ifds::MinAge,       BFCBO::NONE, 0 }, 
   { ifds::MaxAge,       BFCBO::NONE, 0 }, 
   { ifds::MinWithAge,   BFCBO::NONE, 0 }, 
   { ifds::Unisex,       BFCBO::NONE, 0 }, 
   { ifds::SexDistinct,  BFCBO::NONE, 0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************

TaxJurisLimitList::TaxJurisLimitList( BFAbstractCBO &parent )
: MFCanBFCbo( parent ),
_strTaxTypeSchedule( NULL_STRING )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL);
   setObjectAsList( );
}


//******************************************************************************

TaxJurisLimitList::~TaxJurisLimitList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************

SEVERITY TaxJurisLimitList::init( DString& TaxType, 
								  const DString &strTaxTypeSchedule,
                                  bool bIgnoreDataNotFound,
                                  bool bIgnoreUnknAcct, 
                                  const DString& dstrTrack,
                                  const DString& dstrPageName)                             
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   _strTaxTypeSchedule = strTaxTypeSchedule;
   if( _strTaxTypeSchedule.strip().empty() )
   {
      _strTaxTypeSchedule = I_("00");
   }

   BFData requestData(ifds::DSTC0211_REQ);

   DString mgmtCoIdOut;
   requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   requestData.setElementValue( ifds::TaxType, TaxType ); 
   requestData.setElementValue( ifds::TaxTypeSchedule, _strTaxTypeSchedule ); 

   requestData.setElementValue( ifds::Track, dstrTrack );
   requestData.setElementValue( ifds::Activity, dstrPageName );

   SEVERITY sevRtn = ReceiveData( DSTC_REQUEST::TAXJURISDICTIONLIMIT_LIST, requestData, ifds::DSTC0211_VW, DSTCRequestor( getSecurity() ,true ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY TaxJurisLimitList::init( const BFData& data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init( data )" ) );

   attachDataObject( const_cast<BFData&>(data), false, true );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY TaxJurisLimitList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   DString dstTaxTypeSchedule = data.getElementValue( I_( "TaxTypeSchedule" ));
   if( dstTaxTypeSchedule.strip().empty() )
   {
      dstTaxTypeSchedule = I_("00");
   }

   if( _strTaxTypeSchedule == dstTaxTypeSchedule )
   {
      pObjOut = new TaxJurisLimitList((BFAbstractCBO&)(*this));
	  (( TaxJurisLimitList* ) ( pObjOut ) )->init( const_cast<BFData&>(data) );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

bool TaxJurisLimitList::isValidAge( const DString& dstrAge, const DString& dstrJurisdiction, const BFDataGroupId& idDataGroup )
{
   DString dstrJurisdictionValue;
   BFObjIter iter( *this, BF::HOST );
   while( !iter.end() )
   {
      iter.getObject()->getField( ifds::PensionJuris, dstrJurisdictionValue, idDataGroup );
      if( dstrJurisdictionValue.compare(dstrJurisdiction) == 0 )
      {
         DString dstrMinAge, dstrMaxAge;
         iter.getObject()->getField( ifds::MinAge, dstrMinAge, idDataGroup );
         iter.getObject()->getField( ifds::MaxAge, dstrMaxAge, idDataGroup );
         // Check age inclusively Age >= Min && Age <= Max;
         return( (dstrAge.asInteger() >= dstrMinAge.asInteger()) && (dstrAge.asInteger() <= dstrMaxAge.asInteger()) );
      }
      ++iter;
   };

   return(false);  // Could not find Jurisdiction
}

//******************************************************************************

bool TaxJurisLimitList::isValidMinimumAge( const DString& dstrAge, const DString& dstrJurisdiction, const BFDataGroupId& idDataGroup )
{
   DString dstrJurisdictionValue;
   BFObjIter iter( *this, BF::HOST );
   while( !iter.end() )
   {
      iter.getObject()->getField( ifds::PensionJuris, dstrJurisdictionValue, idDataGroup );
      if( dstrJurisdictionValue.compare(dstrJurisdiction) == 0 )
      {
         DString dstrMinAge;
         iter.getObject()->getField( ifds::MinAge, dstrMinAge, idDataGroup );
         return(dstrAge.asInteger() >= dstrMinAge.asInteger());
      }
      ++iter;
   };

   return(false);  // Could not find Jurisdiction
}

//******************************************************************************

bool TaxJurisLimitList::isValidMaximumAge( const DString& dstrAge, const DString& dstrJurisdiction, const BFDataGroupId& idDataGroup )
{
   DString dstrJurisdictionValue;
   BFObjIter iter( *this, BF::HOST );
   while( !iter.end() )
   {
      iter.getObject()->getField( ifds::PensionJuris, dstrJurisdictionValue, idDataGroup );
      if( dstrJurisdictionValue.compare(dstrJurisdiction) == 0 )
      {
         DString dstrMaxAge;
         iter.getObject()->getField( ifds::MaxAge, dstrMaxAge, idDataGroup );
         return(dstrAge.asInteger() <= dstrMaxAge.asInteger());
      }
      ++iter;
   };

   return(false);  // Could not find Jurisdiction
}

//******************************************************************************

bool TaxJurisLimitList::getAgeCalcBasedOn(int& ageCalcBasedOn, const DString& dstrJurisdiction, const BFDataGroupId& idDataGroup )
{
   DString dstrJurisdictionValue;
   BFObjIter iter( *this, BF::HOST );
   while( !iter.end() )
   {
      iter.getObject()->getField( ifds::PensionJuris, dstrJurisdictionValue, idDataGroup );
      if( dstrJurisdictionValue.compare(dstrJurisdiction) == 0 )
      {
		 DString dstrAgeCalcBasedOn;
         iter.getObject()->getField( ifds::AgeCalcBasedOn, dstrAgeCalcBasedOn, idDataGroup );
		 ageCalcBasedOn = dstrAgeCalcBasedOn.asInteger();
         return true;;
      }
      ++iter;
   };

   return(false);  // Could not find Jurisdiction
}
//******************************************************************************

bool TaxJurisLimitList::isValidMinimumAgeForWithdrawl( const DString& dstrAge, const DString& dstrJurisdiction, const BFDataGroupId& idDataGroup )
{
   DString dstrJurisdictionValue;
   BFObjIter iter( *this, BF::HOST );
   while( !iter.end() )
   {
      iter.getObject()->getField( ifds::PensionJuris, dstrJurisdictionValue, idDataGroup );
      if( dstrJurisdictionValue.compare(dstrJurisdiction) == 0 )
      {
         DString dstrMinWithAge;
         iter.getObject()->getField( ifds::MinWithAge, dstrMinWithAge, idDataGroup );
         return( dstrAge.asInteger() >= dstrMinWithAge.asInteger());
      }
      ++iter;
   };

   return(false);  // Could not find Jurisdiction
}

//******************************************************************************

bool TaxJurisLimitList::isValidPensionJurisdiction( const DString& dstrJurisdiction, const BFDataGroupId& idDataGroup )
{
   DString dstrJurisdictionValue;
   BFObjIter iter( *this, BF::HOST );
   while( !iter.end() )
   {
      iter.getObject()->getField( ifds::PensionJuris, dstrJurisdictionValue, idDataGroup );
      if( dstrJurisdictionValue.compare(dstrJurisdiction) == 0 )
      {
         return(true);
      }
      ++iter;
   };

   return(false);  // Could not find Jurisdiction
}

//******************************************************************************
// This method returns the value based on the field id and jurisdiction passed in.
// @param - const BFFieldId& idField - Field Id to returned
//          DString &dstrJurisdiction - Jurisdiction to look for.
//          const BFDataGroupId& idDataGroup - datagroup id.
//******************************************************************************
DString TaxJurisLimitList::getJurisLimitField( const BFFieldId& idField, const DString& dstrJurisdiction, const BFDataGroupId& idDataGroup, bool blFormatted )
{
   DString dstrJurisdictionValue;
   BFObjIter iter( *this, BF::HOST );
   while( !iter.end() )
   {
      iter.getObject()->getField( ifds::PensionJuris, dstrJurisdictionValue, idDataGroup );
      if( dstrJurisdictionValue.compare(dstrJurisdiction) == 0 )
      {
         DString dstrValue;
         iter.getObject()->getField ( idField, dstrValue, idDataGroup, blFormatted );
         return(dstrValue);
      }
      ++iter;
   };
   return(NULL_STRING);
}

//******************************************************************************
bool TaxJurisLimitList::isCarryForwardUnusedMaxApplic( const DString& dstrJurisdiction, 
												      const BFDataGroupId& idDataGroup )
{
   bool bIsCarryForwardUnusedMaxApplic = false;
   DString dstrJurisdictionValue;
   BFObjIter iter( *this, BF::HOST );
   while( !iter.end() )
   {
      iter.getObject()->getField( ifds::PensionJuris, dstrJurisdictionValue, idDataGroup );
      if( dstrJurisdictionValue.compare(dstrJurisdiction) == 0 )
      {
		 DString dstrCarryForUnusedMax;
		 iter.getObject()->getField( ifds::CarryForUnusedMax, dstrCarryForUnusedMax, idDataGroup );
         bIsCarryForwardUnusedMaxApplic = I_( "Y" ) == dstrCarryForUnusedMax;
		 break;
      }
      ++iter;
   };

   return bIsCarryForwardUnusedMaxApplic;  
}

//******************************************************************************
bool TaxJurisLimitList::canUseSpousesAge( const DString& dstrJurisdiction, 
												      const BFDataGroupId& idDataGroup )
{
   bool bUseSpousesAge = true;
   DString dstrJurisdictionValue;
   BFObjIter iter( *this, BF::HOST );
   while( !iter.end() )
   {
      iter.getObject()->getField( ifds::PensionJuris, dstrJurisdictionValue, idDataGroup );
      if( dstrJurisdictionValue.compare(dstrJurisdiction) == 0 )
      {
         DString dstrUseSpousesAge ;
         iter.getObject()->getField( ifds::UseSpAge, dstrUseSpousesAge, idDataGroup );
         bUseSpousesAge = I_( "Y" ) == dstrUseSpousesAge;
         break;
      }
      ++iter;
   };

   return bUseSpousesAge ;  
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TaxJurisLimitList.cpp-arc  $
// 
//    Rev 1.13   Feb 20 2009 14:35:58   jankovii
// IN  1557042 - Accountholder less than 55 but no warning on Desktop and a/c created
// 
//    Rev 1.12   Nov 28 2008 13:47:40   jankovii
// PET 142196 FN01 Federal Restricted LIF and LIRA.
// 
//    Rev 1.11   01 May 2008 13:57:48   kovacsro
// PET2255 FN47 - New Ontario LIF - finalized
// 
//    Rev 1.10   24 Apr 2008 13:29:40   kovacsro
// PET2255 FN47 - New Ontario LIF - added TaxTypeSchedule to the request
// 
//    Rev 1.9   15 Apr 2008 12:10:08   kovacsro
// PET2255 FN47 - New Ontario LIF
// 
//    Rev 1.8   Jan 23 2008 11:54:20   hsuchin
// Incident# 1105490 - default to allow data entry for spousal date of birth for RRIFs
// 
//    Rev 1.7   Aug 10 2007 17:07:08   smithdav
// PET2360 FN76,91
// 
//    Rev 1.6   Sep 07 2006 16:53:00   porteanm
// PET2216 FN35 - RRIF Locked-In products - RRIF Unused Amt. 
// 
//    Rev 1.5   Nov 14 2004 14:56:56   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.4   Mar 21 2003 18:25:58   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.3   Oct 09 2002 23:55:06   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.2   Aug 29 2002 12:56:48   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.1   Jul 09 2002 10:21:36   HSUCHIN
// added method getJurisLimitField to return values of field id passed in based on the jurisdiction.
// 
//    Rev 1.0   08 Jun 2002 18:19:20   HERNANDO
// Initial revision.
 * 
// 
*/