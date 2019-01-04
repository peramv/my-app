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
//    Copyright 2003 By International Financial Data Services.
//
//
//********************************************************************************
//
// ^FILE   : SettleLocationAcctLvl.cpp
// ^AUTHOR : 
// ^DATE   : 
//
//********************************************************************************
#include "stdafx.h"
#include "SettleLocationAcctLvl.hpp"
#include "SettleLocationAcctLvlList.hpp"
#include "SettleLocationSysLvl.hpp"
#include "SettleLocationSysLvlList.hpp"
#include "MgmtCoOptions.hpp"
#include "mgmtco.hpp"
#include "DSTCommonFunction.hpp"

#include <dataimpl\dse_dstc0269_vw.hpp>
#include <dataimpl\dse_dstc0269_req.hpp>

namespace
{
   const I_CHAR * const CLASSNAME = I_( "SettleLocationAcctLvl" );
}

namespace CND
{
   extern const long ERR_DUPLICATE_SETTLE_LOCATION;
   extern const long ERR_MULTIPLE_DEFAULT;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const SETTLE_LOCATION_ACCT_LVL;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
   // Field DD Id,				State Flags,			     Group Flags 
   { BFCBO::CLASS_FIELD_INFO( ifds::SettleLocationCode, BFCBO::REQUIRED, 0 )}, 
   { BFCBO::CLASS_FIELD_INFO( ifds::Default,            BFCBO::NONE,     0 )},

   // Admin/Date fields
   { BFCBO::CLASS_FIELD_INFO( ifds::ProcessDate,        BFCBO::NONE,     0 )}, 
   { BFCBO::CLASS_FIELD_INFO( ifds::Username,           BFCBO::NONE,     0 )}, 
   { BFCBO::CLASS_FIELD_INFO( ifds::ModDate,            BFCBO::NONE,     0 )}, 
   { BFCBO::CLASS_FIELD_INFO( ifds::ModUser,            BFCBO::NONE,     0 )}, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************

SettleLocationAcctLvl::SettleLocationAcctLvl( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}

//******************************************************************************

SettleLocationAcctLvl::~SettleLocationAcctLvl()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}  

//******************************************************************************

SEVERITY SettleLocationAcctLvl::init(const BFData& data, const DString& dstrSubstitution )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   attachDataObject(const_cast<BFData&>(data), false);  
   setFieldAllSubstituteValues( ifds::SettleLocationCode, BF::HOST, dstrSubstitution );
   clearUpdatedFlags( BF::HOST, false );
	return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************

void SettleLocationAcctLvl::initNew(const BFDataGroupId& idDataGroup, const DString& dstrSubstitution, const DString& dstrSettleLocationCode )
{
   setFieldAllSubstituteValues( ifds::SettleLocationCode, idDataGroup, dstrSubstitution );
   setField(ifds::Default, I_("N"), idDataGroup, false );
   clearUpdatedFlags( idDataGroup, false );
}

//*********************************************************************************

SEVERITY SettleLocationAcctLvl::doValidateField( const BFFieldId& idField, const DString& dstrValue, 
												      const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField" ));   

   if (idField == ifds::SettleLocationCode )
	{
      validateSettlementLocation( dstrValue, idDataGroup );
   }
   else if( idField == ifds::Default )
   {
      validateDefault( dstrValue, idDataGroup );
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//***************************************************************************************

SEVERITY SettleLocationAcctLvl::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges") );
   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************

SEVERITY SettleLocationAcctLvl::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{ 
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );
   return(GETCURRENTHIGHESTSEVERITY());
}

//*******************************************************************************

SEVERITY SettleLocationAcctLvl::validateSettlementLocation( const DString& dstrSettlementLocationCode, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateSettlementLocation") );

   DString dstrSettleLocationCode( dstrSettlementLocationCode );
   dstrSettleLocationCode.strip().upperCase();

   if( dstrSettleLocationCode.empty() )
   {
      return( NO_CONDITION );
   }

	bool bExist = (dynamic_cast<SettleLocationAcctLvlList*>(getParent()) )->isDuplicateSettlementLocation( dstrSettleLocationCode, idDataGroup );
   if( bExist )
	{
      ADDCONDITIONFROMFILE( CND::ERR_DUPLICATE_SETTLE_LOCATION );
		return  GETCURRENTHIGHESTSEVERITY();
	}

   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************

SEVERITY SettleLocationAcctLvl::validateDefault( const DString& dstrDefaultCode, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateDefault") );

   DString dstrDefault( dstrDefaultCode );
   dstrDefault.strip().upperCase();

   if( dstrDefault.empty() )
   {
      return( NO_CONDITION );
   }

	bool bExist = (dynamic_cast<SettleLocationAcctLvlList*>(getParent()) )->isDuplicateDefault( dstrDefault, idDataGroup );
   if( bExist )
	{
      ADDCONDITIONFROMFILE( CND::ERR_MULTIPLE_DEFAULT );
		return  GETCURRENTHIGHESTSEVERITY();
	}

   return GETCURRENTHIGHESTSEVERITY();
}

//***********************************************
//R E V I S I O N   C O N T R O L   E N T R I E S
//***********************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/SettleLocationAcctLvl.cpp-arc  $
// 
//    Rev 1.2   Nov 14 2004 14:53:48   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.1   Nov 24 2003 18:11:04   HERNANDO
// Next revision.
// 
//    Rev 1.0   Nov 20 2003 11:08:40   HERNANDO
// Initial revision.
