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
//    Copyright 2004 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : BrokerRemark.cpp
// ^AUTHOR : 
// ^DATE   : 10/10/2004
//
// ^CLASS    : BrokerRemark
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "BrokerRemark.hpp"
#include "mgmtco.hpp"
#include "mgmtcoOptions.hpp"
#include "BrokerRemarkList.hpp"

#include <ifastdataimpl\dse_dstc0315_req.hpp>
#include <ifastdataimpl\dse_dstc0315_vw.hpp>


namespace
{
   const I_CHAR * const CLASSNAME = I_( "BrokerRemark" );
   const I_CHAR * const YES = I_( "Y" );
   const I_CHAR * const NO = I_( "N" );
}

namespace CND
{
   extern const long ERR_BROKER_INTERMEDIARY_ADDRESS_NOT_FOUND;
   extern const long ERR_BROKER_INVALID_AS_OF_DATE;
   extern const long ERR_BROKER_NOT_EFFECTIVE;
   extern const long ERR_EFFECTIVE_DATE_MUST_BE_ENTERED;
}
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId Default;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
}


const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//   Field DD Id,        State Flags,       Group Flags 
   { ifds::BrokerCode,				BFCBO::NONE, 0 }, 
   { ifds::EffectiveDate,			BFCBO::NONE, 0 }, 
   { ifds::BranchCode,				BFCBO::NONE, 0 }, 
   { ifds::AgentCode,				BFCBO::NONE, 0 }, 
   { ifds::Remark1,					BFCBO::NONE, 0 }, 
   { ifds::Remark2,					BFCBO::NONE, 0 }, 
   { ifds::Remark3,					BFCBO::NONE, 0 }, 
   { ifds::Remark4,					BFCBO::NONE, 0 }, 
   { ifds::Remark5,					BFCBO::NONE, 0 }, 
   { ifds::Remark6,					BFCBO::NONE, 0 }, 
   { ifds::Remark7,					BFCBO::NONE, 0 }, 
   { ifds::Remark8,					BFCBO::NONE, 0 }, 
   { ifds::Remark9,					BFCBO::NONE, 0 }, 
   { ifds::Remark10,				BFCBO::NONE, 0 }, 
};
static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );


//****************************************************************************
BrokerRemark::BrokerRemark( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
 

   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL );
}

//****************************************************************************
BrokerRemark::~BrokerRemark()
{
   TRACE_DESTRUCTOR( CLASSNAME );


}     

//****************************************************************************
SEVERITY BrokerRemark::init( const BFData& InstData )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   attachDataObject( const_cast<BFData&>(InstData), false, true );
   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************
SEVERITY BrokerRemark::initNew( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initNew" ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void BrokerRemark::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{
   DString dstrCurDate;
   getWorkSession().getMgmtCoOptions()->getField( ifds::CurrBusDate, dstrCurDate, BF::HOST,false );
	dstrCurDate.strip();
   setFieldNoValidate( ifds::EffectiveDate, dstrCurDate, idDataGroup,false );
	BrokerRemarkList* pList = dynamic_cast<BrokerRemarkList* >( getParent()  );  
	if( pList )
	{	
		DString brokerCode,branchCode,agentCode;
		pList->getBrokerBranchAgentCode( brokerCode,branchCode,agentCode );
		setFieldNoValidate( ifds::BrokerCode, brokerCode, idDataGroup,false );
		setFieldNoValidate( ifds::BranchCode, branchCode, idDataGroup,false );
		setFieldNoValidate( ifds::AgentCode, agentCode, idDataGroup,false );
	}
}

//*******************************************************************************

SEVERITY BrokerRemark::doValidateField( const BFFieldId& idField,
                                   const DString& strValue,
                                   const BFDataGroupId& idDataGroup )

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );
	if( idField == ifds::EffectiveDate )
	{
		DString dstr( strValue );
		dstr.strip();
		if( dstr==NULL_STRING )
		{
		    ADDCONDITIONFROMFILE( CND::ERR_EFFECTIVE_DATE_MUST_BE_ENTERED );
		}	
	}
   return(GETCURRENTHIGHESTSEVERITY());

}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/BrokerRemark.cpp-arc  $
// 
//    Rev 1.2   Nov 14 2004 14:29:28   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.1   Sep 24 2004 13:58:22   YINGBAOL
// PET 1145 FN01 save BrokerCode BranchCode and SalesRep at cbo
// 
//    Rev 1.0   Sep 15 2004 10:57:08   YINGBAOL
// Initial revision.
 



 */