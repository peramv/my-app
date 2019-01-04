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
// ^FILE   : EntityAddressSearchCriteria.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 02/24/2003
//
// ^CLASS    : EntityAddressSearchCriteria
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"

#include "EntityAddressSearchCriteria.hpp"
#include "addressentitylist.hpp"
#include "entityaddress.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include <ifastdataimpl\dse_dstc0071_vw.hpp>
#include <ifastdataimpl\dse_dstc0071_req.hpp>

namespace  
{
   const I_CHAR * const CLASSNAME					= I_( "EntityAddressSearchCriteria" );
   const I_CHAR * const YES							= I_( "Y" );
   const I_CHAR * const NO								= I_( "N" );
   const I_CHAR * const ADDRESS_ENTITY_LIST     = I_( "AddressEntityList" );
   const I_CHAR * const NAMES							= I_( "Names" );
	const I_CHAR * const LASTNAME						= I_( "LastName" );
	const I_CHAR * const ADDRESSID					= I_( "AddrId" );
	const I_CHAR * const POSTCODE						= I_( "PSTL" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId SearchType;
   extern CLASS_IMPORT const BFTextFieldId SearchFirstName;
   extern CLASS_IMPORT const BFTextFieldId SearchLastName;
   //extern CLASS_IMPORT const BFDecimalField AddrId;
   extern CLASS_IMPORT const BFTextFieldId SearchPSTL;
   extern CLASS_IMPORT const BFTextFieldId SearchCountry;
	extern CLASS_IMPORT const BFTextFieldId SearchFieldCriteria1;
	extern CLASS_IMPORT const BFTextFieldId SearchFieldCriteria2;
	extern CLASS_IMPORT const BFTextFieldId EntityAddressSearchUsing;

}

namespace  CND
{
   extern CLASS_IMPORT const I_CHAR *BFBASE_CONDITION;
	extern CLASS_IMPORT const long ERR_FIELD_VALUE_NOT_VALID;

}

const BFFieldId criteriaFields[]=
{
   ifds::SearchFirstName,
   ifds::SearchLastName,
   ifds::AddrId,
   ifds::SearchPSTL,
   ifds::SearchCountry,
};

static const int numCriteriaFields = sizeof( criteriaFields ) / sizeof( BFFieldId );

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//   Field DD Id,								State Flags,       Group Flags 
   { ifds::SearchType,						BFCBO::NONE,               0 }, 
   { ifds::SearchFirstName,				BFCBO::NONE,               0 }, 
   { ifds::SearchLastName,					BFCBO::NONE,               0 }, 
   { ifds::AddrId,							BFCBO::NONE,               0 }, 
   { ifds::SearchPSTL,						BFCBO::NONE,               0 }, 
   { ifds::SearchCountry,					BFCBO::NONE,               0 }, 
   { ifds::SearchFieldCriteria1,       BFCBO::NONE,					0 }, 
	{ ifds::SearchFieldCriteria2,       BFCBO::NONE,					0 },

};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = {
   //  Object Label,                  State Flags,      Group Flags 
   { I_( "AddressEntityList" ),             BFCBO::NONE,      0},
   
};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );

//****************************************************************************
EntityAddressSearchCriteria::EntityAddressSearchCriteria( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       NUM_OBJECTS, 
							  (const CLASS_OBJECT_INFO *)&classObjectInfo );
 
}

//****************************************************************************
EntityAddressSearchCriteria::~EntityAddressSearchCriteria()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}   

//****************************************************************************

SEVERITY EntityAddressSearchCriteria::init(const DString & dstrSearchType, const BFDataGroupId& idDataGroup /*=BF::HOST*/,
   const DString& dstrTrack /*= I_("N")*/, const DString& dstrPageName /*= NULL_STRING*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   doInitWithDefaultValues(idDataGroup);
	setFieldAllSubstituteValues(ifds::SearchType, idDataGroup, ifds::EntityAddressSearchUsing );
	
	if( dstrSearchType != NULL_STRING )
		setFieldNoValidate(ifds::SearchType,     dstrSearchType,    idDataGroup, false);
	else
		setFieldNoValidate(ifds::SearchType,     I_("Names"),    idDataGroup, false);

	setObjectNew();

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

void EntityAddressSearchCriteria::doInitWithDefaultValues(const BFDataGroupId& idDataGroup)
{

   setFieldNoValidate(ifds::AddrId,				I_("0"),     idDataGroup, false ); //, false, true, true,  false);
   setFieldNoValidate(ifds::SearchFirstName, NULL_STRING, idDataGroup, false ); //, false, true, true,  false);
   setFieldNoValidate(ifds::SearchLastName,  NULL_STRING, idDataGroup, false ); //, false, true, true,  false);
   setFieldNoValidate(ifds::SearchPSTL,		NULL_STRING, idDataGroup, false ); //, false, true, true,  false);
   setFieldNoValidate(ifds::SearchCountry,   NULL_STRING, idDataGroup, false ); //, false, true, true,  false);
  
   //setFieldNoValidate(ifds::SearchType,     I_("Names"),    idDataGroup, false);

}
//****************************************************************************

SEVERITY EntityAddressSearchCriteria::getAddressEntityList( AddressEntityList *&pAddressEntityList, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getAddressEntityList" ) );
  
   pAddressEntityList = dynamic_cast<AddressEntityList*>(BFCBO::getObject( ADDRESS_ENTITY_LIST, idDataGroup ) );

   if( !pAddressEntityList )
   {
      pAddressEntityList = new AddressEntityList( *this );
      DString strSearchType, strSearchFirstName, strSearchLastName, 
			     strAddrId, strSearchPSTL, strSearchCountry; 

      getField(ifds::SearchType,			strSearchType,				idDataGroup, false );
		getField(ifds::SearchFirstName,  strSearchFirstName,     idDataGroup, false );
      getField(ifds::SearchLastName,   strSearchLastName,      idDataGroup, false );
      getField(ifds::AddrId,				strAddrId,					idDataGroup, false );
      getField(ifds::SearchPSTL,			strSearchPSTL,				idDataGroup, false );
      getField(ifds::SearchCountry,    strSearchCountry,			idDataGroup, false );
      
		strSearchType.strip();
		strSearchFirstName.strip();
		strSearchLastName.strip();
		strAddrId.strip();
		strSearchPSTL.strip();
		strSearchCountry.strip();
		if( pAddressEntityList->initSearch( strSearchType, 
			                           strSearchFirstName, 
												strSearchLastName, 
												strAddrId, 
                                    strSearchPSTL, 
												strSearchCountry) <= WARNING )
         setObject( pAddressEntityList, ADDRESS_ENTITY_LIST, OBJ_ACTIVITY_NONE, idDataGroup );
      else
      {
         delete pAddressEntityList;
         pAddressEntityList = NULL;
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}
	
////////////////////////////////VALIDATIONS////////////////////////////////////

//******************************************************************************

SEVERITY EntityAddressSearchCriteria::doValidateField(const BFFieldId& idField, 
   const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

	DString dstrSearchType;
	getField(ifds::SearchType,	dstrSearchType, idDataGroup, false );
	dstrSearchType.strip();
	
   if( idField == ifds::SearchFirstName )
	{
		if ( dstrSearchType == NAMES && strValue == NULL_STRING )
			ADDCONDITIONFROMFILE(CND::ERR_FIELD_VALUE_NOT_VALID);
	}
 
   else if ( idField == ifds::SearchLastName )
	{
      if (  ( dstrSearchType == NAMES || dstrSearchType == LASTNAME )&& strValue == NULL_STRING )
			ADDCONDITIONFROMFILE(CND::ERR_FIELD_VALUE_NOT_VALID);
	}
   else if( idField == ifds::AddrId )
	{
     if ( dstrSearchType == ADDRESSID && strValue == NULL_STRING )
		  ADDCONDITIONFROMFILE(CND::ERR_FIELD_VALUE_NOT_VALID);
	}
	else if( idField == ifds::SearchPSTL )
	{
      if ( dstrSearchType == POSTCODE && strValue == NULL_STRING )
			ADDCONDITIONFROMFILE(CND::ERR_FIELD_VALUE_NOT_VALID);
	}
	else if( idField == ifds::SearchCountry )
	{
      if (  dstrSearchType == POSTCODE && strValue == NULL_STRING )
			ADDCONDITIONFROMFILE(CND::ERR_FIELD_VALUE_NOT_VALID);
	}

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY EntityAddressSearchCriteria::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAME2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

	if( idField == ifds::SearchType )
   {
      //setUpdatedFlag(idField, idDataGroup, false);
      DString strSearchType;
      getField(ifds::SearchType, strSearchType, idDataGroup, false);
      clearSearchFields(idDataGroup);
      if (strSearchType.strip() == NAMES )
		{
			clearRequiredFlags(idDataGroup);
			setFieldRequired(ifds::SearchFirstName, idDataGroup, true);
			setFieldValid(ifds::SearchFirstName, idDataGroup, false);
			setFieldRequired(ifds::SearchLastName, idDataGroup, true);
			setFieldValid(ifds::SearchLastName, idDataGroup, false);
		}
		else if (strSearchType.strip() == LASTNAME )
		{
			clearRequiredFlags(idDataGroup);
			setFieldRequired(ifds::SearchLastName, idDataGroup, true);
			setFieldValid(ifds::SearchLastName, idDataGroup, false);
		}
		else if (strSearchType.strip() == ADDRESSID )
		{
			clearRequiredFlags(idDataGroup);
			setFieldRequired(ifds::AddrId, idDataGroup, true);
			setFieldValid(ifds::AddrId, idDataGroup, false);
		}
		else if (strSearchType.strip() == POSTCODE )
		{
			clearRequiredFlags(idDataGroup);
			setFieldRequired(ifds::SearchPSTL, idDataGroup, true);
			setFieldValid(ifds::SearchPSTL, idDataGroup, false);
			setFieldRequired(ifds::SearchCountry, idDataGroup, true);
			setFieldValid(ifds::SearchCountry, idDataGroup, false);
		}

      notifyObservers( idField, idDataGroup, FIELD_NOTIFICATIONS, E_EVENT_VALUE_CHANGE, I_( "" ));
   }

   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
////////////////////////////////END RELATED CHANGES////////////////////////////////
//******************************************************************************

void EntityAddressSearchCriteria::clearRequiredFlags(const BFDataGroupId& idDataGroup)
{
   for( int i=0; i<numCriteriaFields; ++i )
      setFieldRequired(criteriaFields[i], idDataGroup, false);
}

//******************************************************************************

void EntityAddressSearchCriteria::clearSearchFields(const BFDataGroupId& idDataGroup)
{
   for( int i=1; i<numCriteriaFields; ++i )
      setFieldNoValidate(criteriaFields[i], NULL_STRING, idDataGroup, false);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/EntityAddressSearchCriteria.cpp-arc  $
// 
//    Rev 1.0   Mar 10 2005 16:25:04   ZHANGCEL
// Initial revision.

*/


