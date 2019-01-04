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
//    Copyright 2009 By International Financial Data Services.
//
//
//********************************************************************************
//
// ^FILE   : ChequeDetails.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 01/07/09
//
//********************************************************************************
#include "stdafx.h"
#include "ChequeDetails.hpp"

#include <ifastdataimpl\dse_dstc0021_vwrepeat_record.hpp>

namespace
{
	const I_CHAR * const CLASSNAME			= I_( "ChequeDetails" );
	const I_CHAR * const ASSIGNED_BY_USER	= I_( "User" );
	const I_CHAR * const OUTSTANDING	    = I_( "Out" );
	const I_CHAR * const RECONCILED    	    = I_( "Rec" );
	const I_CHAR * const REPLACED			= I_( "Rep" );
	const I_CHAR * const STALED 			= I_( "STLD" );
	const I_CHAR * const STOPPED			= I_( "Stop" );
	const I_CHAR * const UNMATCHED			= I_( "Unm" );
	const I_CHAR * const VOIDED				= I_( "Void" );
	const I_CHAR * const REMITTED           = I_( "RMTD" );

}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
	// Field DD Id,				State Flags,			     Group Flags 
	{ ifds::PrintDate,		BFCBO::NONE,		0 },
	{ ifds::StageStampDate,	BFCBO::NONE,		0 },
	{ ifds::RemittanceDate,	BFCBO::NONE,        0 },
	{ ifds::ChqStage,		BFCBO::NONE,		0 },
	{ ifds::ChqStatus,		BFCBO::NONE,		0 },
	{ ifds::ChqComments,	BFCBO::NONE,		0 },
	{ ifds::StageAssignBy,	BFCBO::NONE,		0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
ChequeDetails::ChequeDetails( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );	
}

//******************************************************************************
ChequeDetails::~ChequeDetails()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}  

//*******************************************************************************
SEVERITY ChequeDetails::init(const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
	

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ChequeDetails::init( const BFData& data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );	

   attachDataObject(const_cast<BFData&>(data), false); 


   DString chequeSubstList = removeItemFromSubtList (ifds::ChqStatus, I_("ALL"), BF::HOST);
		   
   setFieldAllSubstituteValues (ifds::ChqStatus, BF::HOST, chequeSubstList);

   setFieldReadOnly ( ifds::PrintDate, BF::HOST, true );
   setFieldReadOnly ( ifds::StageStampDate, BF::HOST, true );
   //setFieldReadOnly ( ifds::RemittanceDate, BF::HOST, true );
   setFieldReadOnly ( ifds::StageAssignBy, BF::HOST, true );

   getField (ifds::ChqStatus, m_dstrCheque, BF::HOST);
   
   bool bReadOnly = m_dstrCheque == OUTSTANDING || m_dstrCheque == UNMATCHED || m_dstrCheque == STALED || m_dstrCheque == NULL_STRING ? false : true;
   
   setChequeSubstitionList (m_dstrCheque, BF::HOST);

   setFieldReadOnly ( ifds::ChqStatus, BF::HOST, bReadOnly );

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY ChequeDetails::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
	MAKEFRAME2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

	if (idField == ifds::ChqStage)
	{
	   setFieldNoValidate (ifds::StageAssignBy, ASSIGNED_BY_USER, idDataGroup, false);
    }
	
	return(GETCURRENTHIGHESTSEVERITY());
};

//*********************************************************************************
SEVERITY ChequeDetails::setChequeSubstitionList (const DString &dstrCheque, const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("setChequeSubstitionList" ));   

	if (dstrCheque == OUTSTANDING || dstrCheque == UNMATCHED || dstrCheque == STALED || dstrCheque == NULL_STRING)
	{

		DString chequeSubList = NULL_STRING;
		
		BFProperties *pBFProperties = getFieldProperties (ifds::ChqStatus, idDataGroup);
   
		pBFProperties->getAllSubstituteValues (chequeSubList);

		if (dstrCheque == OUTSTANDING || dstrCheque == NULL_STRING) 
		{
			chequeSubList = removeItemFromSubtList (chequeSubList, STALED);
			chequeSubList = removeItemFromSubtList (chequeSubList, REPLACED); 
			chequeSubList = removeItemFromSubtList (chequeSubList, REMITTED);
			
			if( dstrCheque == NULL_STRING )
			{
				chequeSubList = removeItemFromSubtList (chequeSubList, OUTSTANDING); 
				chequeSubList = I_(" = ;") + chequeSubList;
			}
		}
		else if (dstrCheque == UNMATCHED)
		{
			chequeSubList = removeItemFromSubtList (chequeSubList, OUTSTANDING);
			chequeSubList = removeItemFromSubtList (chequeSubList, STALED);
			chequeSubList = removeItemFromSubtList (chequeSubList, REPLACED);
			chequeSubList = removeItemFromSubtList (chequeSubList, REMITTED);
		}
		else if (dstrCheque == STALED)
		{
			chequeSubList = removeItemFromSubtList (chequeSubList, RECONCILED);
			chequeSubList = removeItemFromSubtList (chequeSubList, REPLACED);
			chequeSubList = removeItemFromSubtList (chequeSubList, UNMATCHED);
			chequeSubList = removeItemFromSubtList (chequeSubList, REMITTED);
		}
		   
		setFieldAllSubstituteValues (ifds::ChqStatus, idDataGroup, chequeSubList);
	}

   	return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ChequeDetails.cpp-arc  $
// 
//    Rev 1.1   Oct 14 2009 10:32:08   yingz
// change for incident 1641175. the remittance date is now not mandatory
// 
//    Rev 1.0   08 Jan 2009 14:33:36   kovacsro
// Initial revision.
 * 
// 
*/