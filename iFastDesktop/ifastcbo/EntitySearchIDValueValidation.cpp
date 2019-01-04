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
//    Copyright 2018 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : EntitySearchIDValidation.cpp
// ^AUTHOR : 
// ^DATE   : 10 May, 2018
//
// ^CLASS    : 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "mgmtco.hpp"
#include "EntitySearchIDValueValidation.hpp"
#include <ifastdataimpl\dse_dstc0490_req.hpp>
#include <ifastdataimpl\dse_dstc0490_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ENTITYSEARCHID_VALIDATION;
}

namespace CND
{  
	
}

namespace IFASTERR
{
	
}

namespace
{
	const I_CHAR * const CLASSNAME           = I_ ("EntitySearchIDValueValidation");
}
EntitySearchIDValueValidation::EntitySearchIDValueValidation (BFAbstractCBO &parent)
: MFCanBFCbo (parent)
{
	TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
	
}

//******************************************************************************
EntitySearchIDValueValidation::~EntitySearchIDValueValidation ()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}


//******************************************************************************
SEVERITY EntitySearchIDValueValidation::init ( const DString &SrchEntType, 
										  const DString &SrchIdType,
										  const DString &SrchEntityIDs,
										  const DString &dstrTrack, 
										  const DString &dstrPageName)
{

	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("init"));
	BFData queryData  (ifds::DSTC0490_REQ);

	DString mgmtCoIdOut;

	queryData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
	queryData.setElementValue( ifds::Track, dstrTrack );
	queryData.setElementValue( ifds::Activity, dstrPageName );
	queryData.setElementValue (ifds::SrchIdType, SrchIdType);
	queryData.setElementValue (ifds::SrchEntType, SrchEntType);
	queryData.setElementValue (ifds::SrchEntityId, SrchEntityIDs);
	

	ReceiveData  (DSTC_REQUEST::ENTITYSEARCHID_VALIDATION, 
                 queryData, 
                 ifds::DSTC0490_VW,
                 DSTCRequestor  (getSecurity (), false));

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/*   $*/