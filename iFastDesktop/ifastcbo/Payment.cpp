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
//    Copyright 2004 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : Payment.cpp
// ^AUTHOR : 
// ^DATE   : 17 Nov 2011
//
// ^CLASS    : Payment
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "Payment.hpp"

#include <ifastdataimpl\dse_dstc0393_req.hpp>


namespace  
{
   const I_CHAR * const CLASSNAME		= I_( "Payment" );   
}

namespace ifds
{   
	
	extern CLASS_IMPORT const BFNumericFieldId TransId;
	extern CLASS_IMPORT const BFNumericFieldId TransNum;
	extern CLASS_IMPORT const BFTextFieldId PendProcRecordType;
}

namespace CND
{  // Conditions used
	
}


//-------------------------------------------------------------------
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
   // Field DD Id,                  State Flags,      Group Flags 
   { ifds::PaymentInfo,          BFCBO::NONE,         0 },
   { ifds::TransId,                 BFCBO::NONE,         0 },
   { ifds::TransNum,                BFCBO::NONE,         0 },
   { ifds::PendProcRecordType,      BFCBO::NONE,         0 },
  
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//**********************************************************************************
Payment::Payment( BFAbstractCBO &parent )
: MFCanBFCbo (parent)
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL );	

}
//***********************************************************************************
Payment::~Payment()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}     

//******************************************************************************************
SEVERITY Payment::init(const DString &recordType,
                                  const DString &transNum,
                                  const DString &transId,
                                  const DString &Payment,
                                  const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   setFieldNoValidate (ifds::PendProcRecordType, recordType, idDataGroup); 
   setFieldNoValidate (ifds::TransNum, transNum, idDataGroup); 
   setFieldNoValidate (ifds::TransId, transId, idDataGroup); 
   setFieldNoValidate (ifds::PaymentInfo, Payment, idDataGroup); 

   return GETCURRENTHIGHESTSEVERITY();
}

SEVERITY Payment::init( const BFData& data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );	
   
   attachDataObject(const_cast<BFData&>(data), false); 	

   return(GETCURRENTHIGHESTSEVERITY());
}

//*************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/Payment.cpp-arc  $
// 
//    Rev 1.0   Dec 08 2011 00:35:18   wp040032
// Initial revision.
//