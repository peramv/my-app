//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2004 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : CancelInstrSearchCriteria.cpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 10/31/2005
//
// ^CLASS    : CancelInstrSearchCriteria
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "CancelInstrSearchCriteria.hpp"

#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"

namespace  
{
   const I_CHAR * const CLASSNAME					= I_( "CancelInstrSearchCriteria" );
   const I_CHAR * const YES							= I_( "Y" );
   const I_CHAR * const NO								= I_( "N" );
   const I_CHAR * const FILENAME						= I_( "FileName" );
	const I_CHAR * const NETWORKID					= I_( "NetworkID" );
	const I_CHAR * const STARTDATE					= I_( "StartDate" );
	const I_CHAR * const ENDDATE						= I_( "EndDate" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId  CancSearchType;
	extern CLASS_IMPORT const BFTextFieldId  SearchUsing;
	extern CLASS_IMPORT const BFTextFieldId  TranStatus;
	extern CLASS_IMPORT const BFTextFieldId  CancellationType;
}

namespace  CND
{
	
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//   Field DD Id,								State Flags,       Group Flags 
   { ifds::CancSearchType,					BFCBO::REQUIRED,               0 }, 
   { ifds::SearchUsing,					BFCBO::REQUIRED,               0 }, 
   
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = {
   //  Object Label,									State Flags,      Group Flags 
   { I_( "CancelInstrSearchCriteria" ),             BFCBO::NONE,      0},
   
};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );

//****************************************************************************
CancelInstrSearchCriteria::CancelInstrSearchCriteria( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       NUM_OBJECTS, 
							  (const CLASS_OBJECT_INFO *)&classObjectInfo );
 
}

//****************************************************************************
CancelInstrSearchCriteria::~CancelInstrSearchCriteria()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}   

//****************************************************************************

SEVERITY CancelInstrSearchCriteria::init(const BFDataGroupId& idDataGroup /*=BF::HOST*/,
   const DString& dstrTrack /*= I_("N")*/, const DString& dstrPageName /*= NULL_STRING*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   doInitWithDefaultValues(idDataGroup);
	setObjectNew();

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

void CancelInstrSearchCriteria::doInitWithDefaultValues(const BFDataGroupId& idDataGroup)
{

	setFieldNoValidate( ifds::CancSearchType, I_("AdjustType"), idDataGroup, false, true, true, true );
	
	setFieldAllSubstituteValues (ifds::SearchUsing, idDataGroup, ifds::CancellationType);

	setFieldNoValidate( ifds::SearchUsing, I_("BULKCAN"), idDataGroup, false, true, true, true );

	clearUpdatedFlags( BF::HOST );

}

//******************************************************************************
SEVERITY CancelInstrSearchCriteria::doApplyRelatedChanges (
   const BFFieldId &idField, 
   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));

   if (idField == ifds::CancSearchType)
   { 
		DString dstrSearchType;
		getField( ifds::CancSearchType, dstrSearchType, idDataGroup, false );
		if ( dstrSearchType == I_("TransStat") )
		{
			setFieldAllSubstituteValues (ifds::SearchUsing, idDataGroup, ifds::TranStatus);
			setFieldNoValidate( ifds::SearchUsing, I_("All"), idDataGroup, false, true, true, true );
		}
		else if (  dstrSearchType == I_("AdjustType") )
		{
			setFieldAllSubstituteValues (ifds::SearchUsing, idDataGroup, ifds::CancellationType);
			setFieldNoValidate( ifds::SearchUsing, I_("BULKCAN"), idDataGroup, false, true, true, true );
		}

		clearUpdatedFlags( BF::HOST );
	}
	return GETCURRENTHIGHESTSEVERITY ();
}


    
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/CancelInstrSearchCriteria.cpp-arc  $
// 
//    Rev 1.3   Nov 30 2005 13:16:30   porteanm
// PET1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.2   Nov 14 2005 18:02:28   ZHANGCEL
// PET1286 FN01 -- Change default value for the SearchUsing
// 
//    Rev 1.1   Nov 11 2005 17:01:00   ZHANGCEL
// PET 1286 FN01 -- Make it works properly for the Cancellation Instruction search screen
// 
//    Rev 1.0   Nov 04 2005 11:48:32   ZHANGCEL
// Initial revision.
// 
*/


