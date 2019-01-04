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
//    Copyright 2010 by IFDS Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : AcctControlRecord.cpp
// ^AUTHOR : 
// ^DATE   : Dec 2010
//
// ^CLASS    : AcctControlRecord
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "acctcontrolrecord.hpp"
#include "mgmtco.hpp"

#include <ifastdataimpl\dse_dstc0386_vw.hpp>
#include <ifastdataimpl\dse_dstc0386_req.hpp>
#include <ifastdataimpl\dse_dstc0386_vwrepeat_record.hpp>

namespace DSTC_REQUEST
{
    extern CLASS_IMPORT const DSTCRequest ACCT_CONTROL_INQUIRY;
};

namespace 
{
    const I_CHAR * const CLASSNAME           = I_( "AcctControlRecord" );
};

// Reference to Fields
namespace ifds
{
};

// Conditions used
namespace CND
{
}

//******************************************************************************
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
    // Field DD Id,                          State Flags,               Group Flags
   { ifds::AccountNum,   BFCBO::NONE,      0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
AcctControlRecord::AcctControlRecord(BFAbstractCBO &parent)
: MFCanBFCbo( parent )
{
    TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );

    registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}

//******************************************************************************
AcctControlRecord::~AcctControlRecord(void)
{
    TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY AcctControlRecord::initNew( const DString& accountNum, 
                                     const BFDataGroupId& idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("initNew" )); 

    setFieldNoValidate( ifds::AccountNum, accountNum, idDataGroup );

    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AcctControlRecord::init( const BFData& data )
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init" ));

    attachDataObject(const_cast<BFData&>( data ), false); 

    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
// $Log:   Y:/VCS/BF iFAST/ifastcbo/AcctControlRecord.cpp-arc  $ 
// 
//    Rev 1.1   Feb 01 2011 10:07:58   dchatcha
// P0179308 FN01 - Multi Manager Subscription and Direct Debit Payment, take out getErrMsg, due to no need to override this method.
// 
//    Rev 1.0   Jan 31 2011 14:09:24   dchatcha
// Initial revision.
// 