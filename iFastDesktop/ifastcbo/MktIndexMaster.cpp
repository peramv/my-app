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
// ^FILE   : MktIndexMaster.cpp
// ^AUTHOR : 
// ^DATE   : 
//
//********************************************************************************
#include "stdafx.h"
#include "MktIndexMaster.hpp"
#include "MktIndexMasterList.hpp"
#include "MktIndexFundsList.hpp"
#include "MgmtCoOptions.hpp"
#include "mgmtco.hpp"

#include <ifastdataimpl\dse_dstc0240_vw.hpp>
#include <ifastdataimpl\dse_dstc0240_req.hpp>

namespace
{
   const I_CHAR * const CLASSNAME               = I_( "MktIndexMaster" );
   const I_CHAR * const INDEXFUNDSLIST          = I_( "MktIndexFundsList" );
}

namespace CND
{
   extern const long ERR_DUPLICATE_MKT_INDEX_CODE;
   extern const long ERR_DAYS_BASIS_EMPTY;
   extern const long WARN_DAYS_BASIS_EMPTY;
   extern const long ERR_INPUTDATATYPE_EMPTY;
   extern const long WARN_INPUTDATATYPE_EMPTY;
}
namespace IFASTERR 
{
   extern CLASS_IMPORT I_CHAR * const DAYS_BASIS_EMPTY;
   extern CLASS_IMPORT I_CHAR * const INPUTDATATYPE_EMPTY;
}
namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const MKT_INDEX;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
//  Field DD Id,					State Flags,			Group Flags 
   { ifds::IndexCode,     BFCBO::REQUIRED,                 0 }, 
   { ifds::IndexName,     BFCBO::REQUIRED,                 0 },
   { ifds::ProcessDate,   BFCBO::NONE,                     0 }, 
   { ifds::Username,      BFCBO::NONE,                     0 }, 
   { ifds::ModDate,       BFCBO::NONE,                     0 }, 
   { ifds::ModUser,       BFCBO::NONE,                     0 }, 
   { ifds::DaysBasis,     BFCBO::NONE,                     0 }, 
   { ifds::InputDataType, BFCBO::NONE,                     0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = 
{
   // Object Label,                 State Flags,      Group Flags 
   { I_( "MktIndexFundsList" ),    BFCBO::NONE,     0},
};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );

//******************************************************************************

MktIndexMaster::MktIndexMaster( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, NUM_OBJECTS, (const CLASS_OBJECT_INFO *)&classObjectInfo );
}

//******************************************************************************

MktIndexMaster::~MktIndexMaster()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}  

//******************************************************************************

SEVERITY MktIndexMaster::init(const BFData& data)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   attachDataObject(const_cast<BFData&>(data), false);  
   // setFieldStates
//	bool bPermit = getWorkSession().hasUpdatePermission(UAF::MKT_INDEX );
   setFieldReadOnly( ifds::IndexCode, BF::HOST, true );  // Cannot rename existing Index codes.

   DString dstrInputDataType = data.getElementValue( ifds::InputDataType );
   dstrInputDataType.strip();
   setFieldReadOnly (ifds::DaysBasis, BF::HOST, (dstrInputDataType == I_("01")));

   clearUpdatedFlags( BF::HOST );

	return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************

void MktIndexMaster::initNew(const BFDataGroupId& idDataGroup )
{
//	setFieldStates( idDataGroup );
//	bool bPermit = getWorkSession().hasUpdatePermission( UAF::MKT_INDEX );
	setFieldNoValidate(ifds::IndexCode, NULL_STRING, idDataGroup, false);
	setFieldNoValidate(ifds::IndexName, NULL_STRING, idDataGroup, false);
	setFieldNoValidate(ifds::DaysBasis, NULL_STRING, idDataGroup, false);
	setFieldReadOnly (ifds::DaysBasis, idDataGroup, true);
	setFieldNoValidate(ifds::InputDataType, NULL_STRING, idDataGroup, false,true,false,false);
}

//*********************************************************************************

SEVERITY MktIndexMaster::doValidateField( const BFFieldId& idField, const DString& strValue, 
												  const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField" ));   
   if( idField == ifds::IndexCode )
	{
		validateMktIndexCode( strValue, idDataGroup );
	}
   else if( idField == ifds::DaysBasis )
   {
	    validateDaysBasis(idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//***************************************************************************************

SEVERITY MktIndexMaster::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges") );
   if (idField == ifds::InputDataType) 
   {
      DString dstrInputDataType;
	  getField(ifds::InputDataType, dstrInputDataType, idDataGroup, false);
	  
	  setFieldReadOnly (ifds::DaysBasis, idDataGroup, (dstrInputDataType == I_("01")));
	  setFieldNoValidate(ifds::DaysBasis, NULL_STRING, idDataGroup, false);	  
   }  
   return GETCURRENTHIGHESTSEVERITY();
}

//************************************************************************************

SEVERITY MktIndexMaster::validateMktIndexCode(const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateMktIndexCode") );
   DString dstrMktIndexCode(strValue);
	dstrMktIndexCode.strip().upperCase();

   if( !dstrMktIndexCode.empty() )
   {
	   bool bExist = (dynamic_cast<MktIndexMasterList*>(getParent()) )->isMktIndexCodeValid( dstrMktIndexCode, idDataGroup );
      if( bExist )
	   {
         DString dstrParameter = dstrMktIndexCode.strip().upperCase();
         DString dstrTag;
		   addIDITagValue( dstrTag, I_("CODE"), dstrParameter );
         ADDCONDITIONFROMFILEIDI( CND::ERR_DUPLICATE_MKT_INDEX_CODE, dstrTag );
		   return  GETCURRENTHIGHESTSEVERITY();
	   }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************************

SEVERITY MktIndexMaster::getMktIndexFundsList( MktIndexFundsList *&pMktIndexFundsList, const BFDataGroupId& idDataGroup, bool bCreate )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getMktIndexFundsList") );
   pMktIndexFundsList = NULL;

   pMktIndexFundsList = dynamic_cast<MktIndexFundsList*>(getObject( INDEXFUNDSLIST, idDataGroup ) );
   if( pMktIndexFundsList || !bCreate )
   {
      return(GETCURRENTHIGHESTSEVERITY());
   }
  
   pMktIndexFundsList = new MktIndexFundsList( *this );
   if( isNew() )
   {
      pMktIndexFundsList->initNew( idDataGroup);
      setObject( pMktIndexFundsList, INDEXFUNDSLIST, OBJ_ACTIVITY_NONE, idDataGroup );
   }
   else
   {
      DString dstrMktIndexCode;
      getField(ifds::IndexCode, dstrMktIndexCode, idDataGroup, false);
//      pMktIndexFundsList->setField(ifds::IndexCode, dstrMktIndexCode, BF::HOST, false);
//      if( pMktIndexFundsList->initExisting() <= WARNING )
      if( pMktIndexFundsList->initExisting( I_("N"), NULL_STRING, dstrMktIndexCode ) <= WARNING )
      {
         setObject( pMktIndexFundsList, INDEXFUNDSLIST, OBJ_ACTIVITY_NONE, BF::HOST );
      }
      else
      {
         delete pMktIndexFundsList;
         pMktIndexFundsList = NULL;
      }
   }

	return(GETCURRENTHIGHESTSEVERITY());
}

//*******************************************************************************

SEVERITY MktIndexMaster::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{ 
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );
	MktIndexFundsList* pMktIndexFundsList = NULL;
	getMktIndexFundsList( pMktIndexFundsList, idDataGroup, false );

   if( pMktIndexFundsList )
	{
      pMktIndexFundsList->validateAll( idDataGroup, lValidateGroup );
	}
	validateDaysBasis(idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());
}

//*******************************************************************************

SEVERITY MktIndexMaster::validateMktIndexFunds(const DString& strValue, const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateMktIndexFunds") );
	return GETCURRENTHIGHESTSEVERITY();
}
//*******************************************************************************
SEVERITY MktIndexMaster::validateDaysBasis(const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateDaysBasis") );
	
	DString dstrDaysBasis,dstrInputDataType;
	getField(ifds::DaysBasis, dstrDaysBasis, idDataGroup, false);
	getField(ifds::InputDataType, dstrInputDataType, idDataGroup, false);
	if( dstrInputDataType == I_("02") || dstrInputDataType == I_("03"))
	{
		if( dstrDaysBasis == NULL_STRING )
		{
			getErrMsg ( IFASTERR::DAYS_BASIS_EMPTY,
                              CND::ERR_DAYS_BASIS_EMPTY,
                              CND::WARN_DAYS_BASIS_EMPTY,
                              idDataGroup );
		}
	}
	return GETCURRENTHIGHESTSEVERITY();
}
//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/MktIndexMaster.cpp-arc  $
// 
//    Rev 1.4   Jan 16 2012 14:32:44   wp040027
// P0188394_Performance Fees - Benchmark Upload
// 
//    Rev 1.3   Nov 14 2004 14:50:32   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.2   Mar 21 2003 18:19:22   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.1   Feb 03 2003 16:47:36   HERNANDO
// Revised.
// 
//    Rev 1.0   Jan 23 2003 10:30:46   HERNANDO
// Initial Revision
//