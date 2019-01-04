//********************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2005 By International Financial Data Services.
//
//
//********************************************************************************
//
// ^FILE   : MsgProcessCBO.cpp
//
//********************************************************************************
#include "stdafx.h"
#include "MsgProcessCBO.hpp"
#include "MsgProcessCBOList.hpp"
#include "MsgActivityList.hpp"

#include <ifastdataimpl\dse_dstc0333_vw.hpp>
#include <ifastdataimpl\dse_dstc0333_req.hpp>

namespace
{
   const I_CHAR * const CLASSNAME = I_( "MsgProcessCBO" );
   const I_CHAR * const MSGACTIVITYLIST = I_( "MsgActivityList" );
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
//  Field DD Id,					State Flags,			Group Flags 
   { ifds::ProcessID,           BFCBO::NONE,                     0 }, 
   { ifds::MsgProcessType,      BFCBO::NONE,                     0 },
   { ifds::MsgProcessStatus,    BFCBO::NONE,                     0 }, 
   { ifds::ProcessDate,         BFCBO::NONE,                     0 }, 
   { ifds::ProcessTime,         BFCBO::NONE,                     0 }, 
   { ifds::MsgProcessCategory,  BFCBO::NONE,                     0 }, 
   { ifds::FileName,            BFCBO::NONE,                     0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = 
{
   // Object Label,                 State Flags,      Group Flags 
   { I_( "MsgActivityList" ),    BFCBO::NONE,     0},
};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );

//******************************************************************************

MsgProcessCBO::MsgProcessCBO( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, NUM_OBJECTS, (const CLASS_OBJECT_INFO *)&classObjectInfo );
}

//******************************************************************************

MsgProcessCBO::~MsgProcessCBO()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}  

//******************************************************************************

SEVERITY MsgProcessCBO::init(const BFData& data)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   attachDataObject(const_cast<BFData&>(data), false);  
//   clearUpdatedFlags( BF::HOST );  // Here in case we setFields before this.

	return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************************

SEVERITY MsgProcessCBO::getMsgActivityList( MsgActivityList *&pMsgActivityList, const BFDataGroupId& idDataGroup, bool bCreate )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getMsgActivityList") );
   pMsgActivityList = NULL;

   pMsgActivityList = dynamic_cast<MsgActivityList*>(getObject( MSGACTIVITYLIST, idDataGroup ) );
   if( pMsgActivityList || !bCreate )
   {
      return(GETCURRENTHIGHESTSEVERITY());
   }
  
   pMsgActivityList = new MsgActivityList( *this );
   if( isNew() )
   {
//      pMsgActivityList->initNew( idDataGroup );  // Use initExisting w/ProcessId
      setObject( pMsgActivityList, MSGACTIVITYLIST, OBJ_ACTIVITY_NONE, idDataGroup );
   }
   else
   {
      DString dstrProcessId;
      getField(ifds::ProcessID, dstrProcessId, idDataGroup, false);

      if( pMsgActivityList->initExisting( I_("N"), NULL_STRING, dstrProcessId ) <= WARNING )
      {
         setObject( pMsgActivityList, MSGACTIVITYLIST, OBJ_ACTIVITY_NONE, BF::HOST );
      }
      else
      {
         delete pMsgActivityList;
         pMsgActivityList = NULL;
      }
   }

	return(GETCURRENTHIGHESTSEVERITY());
}


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/MsgProcessCBO.cpp-arc  $
// 
//    Rev 1.0   Feb 21 2005 11:14:16   hernando
// Initial revision.
