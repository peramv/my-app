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
//    Copyright 2005 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : MsgActivity.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : MsgActivity
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : MsgActivity
//
//******************************************************************************
#include "stdafx.h"
#include "MsgActivity.hpp"
#include "MsgEvent.hpp"
#include "MsgEventList.hpp"

#include <ifastdataimpl\dse_dstc0336_vw.hpp>

namespace
{
   const I_CHAR * const CLASSNAME = I_( "MsgActivity" );
   const I_CHAR * const MSGEVENTLIST = I_( "MsgEventList" );
}

namespace ifds
{
//   extern CLASS_IMPORT const BFTextFieldId FundClass;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,             Group Flags 
   { ifds::ProcessID,            BFCBO::NONE,             0 }, 
   { ifds::ActivityID,           BFCBO::NONE,             0 }, 
   { ifds::ActivityType,         BFCBO::NONE,             0 }, 
   { ifds::SendRefNum,           BFCBO::NONE,             0 }, 
   { ifds::MsgDate,              BFCBO::NONE,             0 }, 
   { ifds::MsgTime,              BFCBO::NONE,             0 }, 
   { ifds::ProcessDate,          BFCBO::NONE,             0 }, 
   { ifds::ProcessTime,          BFCBO::NONE,             0 }, 
   { ifds::FundBrokerCode,       BFCBO::NONE,             0 }, 
   { ifds::OmnibusID,            BFCBO::NONE,             0 }, 
   { ifds::AccountNum,           BFCBO::NONE,             0 }, 
   { ifds::TransNum,             BFCBO::NONE,             0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************

MsgActivity::MsgActivity( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}

//******************************************************************************

MsgActivity::~MsgActivity( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************

SEVERITY MsgActivity::initExisting(const BFData &data)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initExisting" ) );
   attachDataObject( const_cast< BFData & >( data ), false, true ); 
//   clearUpdatedFlags( BF::HOST );
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY MsgActivity::getMsgEventList( MsgEventList *&pMsgEventList, const BFDataGroupId& idDataGroup, bool bCreate )
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
      DString dstrActivityID;
      getField(ifds::ActivityID, dstrActivityID, idDataGroup, false);

      if( pMsgEventList->initExisting( I_("N"), NULL_STRING, dstrActivityID ) <= WARNING )
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
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/MsgActivity.cpp-arc  $
// 
//    Rev 1.0   Feb 21 2005 11:12:50   hernando
// Initial revision.
