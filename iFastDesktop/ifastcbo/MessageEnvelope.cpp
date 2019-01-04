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
// ^FILE   :MessageEnvelope.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    :MessageEnvelope
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "MessageEnvelope.hpp"
#include "MsgEventList.hpp"
#include <ifastdataimpl\dse_dstc0332_vw.hpp>

namespace
{
   const I_CHAR * const CLASSNAME = I_( "MessageEnvelope" );  
	const I_CHAR * const MSGEVENTLIST = I_( "MsgEventList" );
}

namespace ifds
{
	 extern CLASS_IMPORT const BFNumericFieldId  EnvelopeID;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,     Group Flags 
   { ifds::EnvelopeID,         BFCBO::NONE,     0 },
 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );
//****************************************************************************
// Constructor
//****************************************************************************
MessageEnvelope::MessageEnvelope( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL );
}

//****************************************************************************
// Destructor
//****************************************************************************
MessageEnvelope::~MessageEnvelope()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}     

//****************************************************************************
//Initializes the CBO
//@param const BFData& InstData - Data object to attach toMessageEnvelopeList.
//@returns SEVERITY
//****************************************************************************
SEVERITY MessageEnvelope::init( const BFData& Data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init( const BFData& Data )" ) );
   attachDataObject( const_cast<BFData&>(Data), false, true );

	return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************
SEVERITY MessageEnvelope::getMsgEventList( MsgEventList *&pMsgEventList, const BFDataGroupId& idDataGroup, bool bCreate )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getMsgEventList") );
   pMsgEventList = NULL;

   pMsgEventList = dynamic_cast<MsgEventList*>(getObject( MSGEVENTLIST, idDataGroup ) );
   if( pMsgEventList || !bCreate )
   {
      return(GETCURRENTHIGHESTSEVERITY());
   }
  
   pMsgEventList = new MsgEventList( *this );
   if( isNew() )
   {
//      pMsgEventList->initNew( idDataGroup );  // Use initExisting w/ActivityID
      setObject( pMsgEventList, MSGEVENTLIST, OBJ_ACTIVITY_NONE, idDataGroup );
   }
   else
   {
      DString dstrEnvelopeID;
      getField(ifds::EnvelopeID, dstrEnvelopeID, idDataGroup, false);

      if( pMsgEventList->initExisting( I_("N"), NULL_STRING, NULL_STRING, dstrEnvelopeID ) <= WARNING )
      {
         setObject( pMsgEventList, MSGEVENTLIST, OBJ_ACTIVITY_NONE, BF::HOST );
      }
      else
      {
         delete pMsgEventList;
         pMsgEventList = NULL;
      }
   }

	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/MessageEnvelope.cpp-arc  $
// 
//    Rev 1.0   Feb 24 2005 17:43:10   ZHANGCEL
// Initial revision.
*/
