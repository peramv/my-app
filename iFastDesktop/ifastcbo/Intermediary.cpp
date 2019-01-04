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
// ^FILE   : Intermediary.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 29/08/2000
//
// ^CLASS    : Intermediary
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "intermediary.hpp"
#include "nomineeinteraddr.hpp"
#include "nomineeinteraddrlist.hpp"

namespace
{
   const I_CHAR * const CLASSNAME = I_( "Intermediary" );
   const I_CHAR * const YES = I_( "Y" );

}

namespace CND
{
   extern const long ERR_BROKER_INTERMEDIARY_ADDRESS_NOT_FOUND;

}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId Default;
   extern CLASS_IMPORT const BFTextFieldId IntermCode;

}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//   Field DD Id,        State Flags,       Group Flags 
   { ifds::IntermCode, BFCBO::NONE, 0 }, 
};
static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = {
//  Object Label,                          State Flags,         Group Flags 
   { I_( "NomineeInterAddressList" ),      BFCBO::NONE,        0},

};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );

//****************************************************************************
Intermediary::Intermediary( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       NUM_OBJECTS,
                       (const CLASS_OBJECT_INFO *)&classObjectInfo );
}

//****************************************************************************
Intermediary::~Intermediary()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}     

//****************************************************************************
SEVERITY Intermediary::init( const BFData& InstData )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   attachDataObject( const_cast<BFData&>(InstData), false, true );

   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************

SEVERITY Intermediary::getNomineeInterAddressList( const BFDataGroupId& idDataGroup, NomineeInterAddrList *&pNomInterAddrList)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getDefaultAddress") );
   pNomInterAddrList = NULL;
   DString strInterCode;
   getField(ifds::IntermCode , strInterCode, idDataGroup);

   //check cbobase to see if we've already built it
   //if not built, create and store with base
   DString strTag = I_("NomineeInterAddressList");
   pNomInterAddrList = dynamic_cast<NomineeInterAddrList *>( BFCBO::getObject( strTag, idDataGroup ) );
   if( ! pNomInterAddrList )
   {
      pNomInterAddrList = new NomineeInterAddrList( *this );
      if( pNomInterAddrList->init( strInterCode ) <= WARNING )
      {
         setObject( pNomInterAddrList, strTag, OBJ_ACTIVITY_NONE, idDataGroup ); 
      }
      else
      {
         delete pNomInterAddrList;
         pNomInterAddrList = NULL;
      }
   }
   if( !pNomInterAddrList )
      ADDCONDITIONFROMFILE( CND::ERR_BROKER_INTERMEDIARY_ADDRESS_NOT_FOUND);
   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/Intermediary.cpp-arc  $
 // 
 //    Rev 1.8   Nov 14 2004 14:48:32   purdyech
 // PET910 - .NET Conversion
 // 
 //    Rev 1.7   Mar 21 2003 18:16:12   PURDYECH
 // BFDataGroupId/BFContainerId changeover
 // 
 //    Rev 1.6   Oct 09 2002 23:54:40   PURDYECH
 // PVCS Database Conversion
 // 
 //    Rev 1.5   Aug 29 2002 12:56:04   SMITHDAV
 // ClientLocale and typed field changes.
 // 
 //    Rev 1.4   22 May 2002 18:28:54   PURDYECH
 // BFData Implementation
 // 
 //    Rev 1.3   03 May 2001 14:06:42   SMITHDAV
 // Session management restructuring.
 // 
 //    Rev 1.2   Feb 19 2001 11:05:24   DINACORN
 // Add Revision Control Entries
 *
 */