//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by Internation Financial Data Services
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2003 by Internation Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : AMSHypoAllocList.cpp
// ^AUTHOR : Thanisorn Sangkrajang
// ^DATE   : July 24, 2017
//
// ^CLASS    : AMSHypoAllocList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : AMS Hypothetical Rebalancing report (Allocation).
//
//******************************************************************************
#include "stdafx.h"
#include "AMSHypoAlloc.hpp"
#include "AMSHypoAllocList.hpp"
#include "FundAllocList.hpp"
#include <ifastdataimpl\dse_dstc0218_req.hpp>
#include <ifastdataimpl\dse_dstc0218_vw.hpp>

namespace
{
   const I_CHAR * const CLASSNAME = I_( "AMSHypoAllocList" );
   const I_CHAR * const NO = I_( "N" );
   const I_CHAR * const YES = I_( "Y" );
   const double dSmallValue       = .0000000001;
}

namespace CND
{
   extern const long	ERR_WARNING_AMS_ALLOCATION_CHANGE;
}

namespace ifds
{  
   extern CLASS_IMPORT const BFTextFieldId    FundAlloc;
   extern CLASS_IMPORT const BFTextFieldId    ForeignRelFundClass;
   extern CLASS_IMPORT const BFTextFieldId	  TransType;
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest AMS_FUND_ALLOC_LIST;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//		Field DD Id,				State Flags,					Group Flags
   { ifds::AMSCode, BFCBO::NONE, 0 }, 
   { ifds::AMSType, BFCBO::NONE, 0 }, 
   { ifds::EffectiveDate, BFCBO::NONE, 0 }, 

};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = 
{
   // Object Label,                 State Flags,      Group Flags 
   { I_( "AMSHypoAlloc" ),    BFCBO::REQUIRED,     0},

};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );
//******************************************************************************
AMSHypoAllocList::AMSHypoAllocList( BFAbstractCBO &parent ) 
: FundAllocList( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList();
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}

//******************************************************************************
AMSHypoAllocList::~AMSHypoAllocList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY AMSHypoAllocList::initExisting(const DString& dstrTrack,
                                          const DString& dstrPageName)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initExisting" ) );   

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AMSHypoAllocList::initNew(  const BFDataGroupId& idDataGroup,
												 bool bGetDefault,
                                     const DString& dstrTrack,
                                     const DString& dstrPageName)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initNew" ) );

   FundAllocList::initNew(idDataGroup, bGetDefault, dstrTrack, dstrPageName);

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AMSHypoAllocList::doCreateNewObject( BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

   AMSHypoAlloc *pAllocation = new AMSHypoAlloc( *this );
   pAllocation->initNew( idDataGroup );
   pBase = pAllocation;
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AMSHypoAllocList::doCreateObject( const BFData &data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   pObjOut = new AMSHypoAlloc ( *this );
   dynamic_cast< AMSHypoAlloc * >( pObjOut )->initExisting( data );
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AMSHypoAllocList::doCopyCurrAlloc( DString dstrToFundNumber, DString dstrFundCode, DString dstrClassCode, DString dstrAllocPrcnt,const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCopyCurrAlloc" ) );
	DString dstrKey;
	getStrKey ( dstrKey );  
	AMSHypoAlloc *pAllocation = new AMSHypoAlloc( *this );
	pAllocation->initNew( idDataGroup );
	pAllocation->setField(ifds::ToFundNumber, dstrToFundNumber, idDataGroup);
	pAllocation->setField(ifds::FundCode, dstrFundCode, idDataGroup);
	pAllocation->setField(ifds::ClassCode, dstrClassCode, idDataGroup);
	pAllocation->setField(ifds::AllocPercentage, dstrAllocPrcnt, idDataGroup);
	setObject(pAllocation, dstrKey,OBJ_ACTIVITY_ADDED, idDataGroup);
	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AMSHypoAllocList::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

	SEVERITY sev = FundAllocList::doValidateAll(idDataGroup,lValidateGroup );
	if(sev > WARNING ) return sev;

	// Allocation of different fund currency is not allowed in the AMS fund mix if the system feature Multi-currency = No. 
    if( !isMultiCurrency() )
      validateMulticurrency(idDataGroup);


	return (GETCURRENTHIGHESTSEVERITY());
	
}

//******************************************************************************
SEVERITY AMSHypoAllocList::doDeleteObject (const DString &strKey, 
   const BFDataGroupId& idDataGroup, bool bIsObjectDestroyed) 
{ 
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("doDeleteObject"));

   return GETCURRENTHIGHESTSEVERITY ();
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AMSHypoAllocList.cpp-arc  $
// 
//    Rev 1.0   Jul 23 2003 09:22:22   Thanisorn S.
// Initial Revision
// 
*/