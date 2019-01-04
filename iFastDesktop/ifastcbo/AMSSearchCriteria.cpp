

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
//    Copyright 2003 by International Financial.
//
//
//******************************************************************************
//
// ^FILE   : AMSSearchCriteria.cpp
// ^AUTHOR : May Lin
// ^DATE   : Aug. 20,  2003
//
// ^CLASS    : AMSSearchCriteria
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "AMSSearchCriteria.hpp"
#include "MgmtCoOptions.hpp"
namespace
{
   const I_CHAR * const CLASSNAME						= I_( "AMSSearchCriteria" );
   const I_CHAR * const YES								= I_( "Y" );
   const I_CHAR * const SEARCH_TYPE_AMSCODE					= I_( "AMSCode" );
   const I_CHAR * const SEARCH_TYPE_EFFECTIVE_DATE		= I_( "EffectiveDate" );

}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId AMSSearchType;
   extern CLASS_IMPORT const BFTextFieldId AMSCode;
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFTextFieldId AMSType;
   extern CLASS_IMPORT const BFTextFieldId ClientAMSType;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
}

namespace AMS_VALIDATION_GROUP
{

   const long AMS_MST_SEARCH = 0x0001;

}
//-------------------------------------------------------------------
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,             Group Flags 
	{ ifds::AMSSearchType,		BFCBO::NONE, AMS_VALIDATION_GROUP::AMS_MST_SEARCH }, 
   { ifds::AMSCode,			BFCBO::NONE, AMS_VALIDATION_GROUP::AMS_MST_SEARCH}, 
   { ifds::AMSType,			BFCBO::NONE, AMS_VALIDATION_GROUP::AMS_MST_SEARCH }, 
   { ifds::EffectiveDate,		BFCBO::NONE, AMS_VALIDATION_GROUP::AMS_MST_SEARCH }, 

};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );


const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = {
//  Object Label,            State Flags,           Group Flags 
   {  I_(""),        BFCBO::REQUIRED,         0}
};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );



//****************************************************************************
AMSSearchCriteria::AMSSearchCriteria( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
    registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
							  NULL );
}

//****************************************************************************
AMSSearchCriteria::~AMSSearchCriteria()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}     

//****************************************************************************
SEVERITY AMSSearchCriteria::init( const BFDataGroupId& idDataGroup,
   const DString& dstrTrack /*= I_("N")*/, 
   const DString& dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAME2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );
   
   setFieldNoValidate(ifds::AMSSearchType,SEARCH_TYPE_EFFECTIVE_DATE,idDataGroup,false,true,true );
   
   DString dstrAMSTypeList;
   getAMSTypeList(dstrAMSTypeList);
   setFieldAllSubstituteValues(ifds::AMSType, idDataGroup, dstrAMSTypeList);
   setFieldNoValidate( ifds::AMSType, _dstrAmsType, idDataGroup, false,true, false, false  ); 

   getWorkSession().getMgmtCoOptions()->getField( ifds::CurrBusDate, _dstrCurDate, BF::HOST ,false );
   setFieldNoValidate( ifds::EffectiveDate, _dstrCurDate, idDataGroup, false,true, false, false  ); 

	return(GETCURRENTHIGHESTSEVERITY());
}

//**********************************************************************************
SEVERITY AMSSearchCriteria::doApplyRelatedChanges( const BFFieldId& idField, 
																			 const BFDataGroupId& idDataGroup )
{
   MAKEFRAME2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges") );
	if( idField == ifds::AMSSearchType )
	{
	
		SearchTypeRelatedChanges( idDataGroup );
	
	}

	return(GETCURRENTHIGHESTSEVERITY());
}


//****************************************************************************************
void AMSSearchCriteria::SearchTypeRelatedChanges(const BFDataGroupId& idDataGroup )
{

   BFFieldId lFieldIds1[3] = { ifds::NullFieldId, ifds::NullFieldId, ifds::NullFieldId};

   BFFieldId lFieldIds2[3] = { ifds::NullFieldId, ifds::NullFieldId, ifds::NullFieldId};
	DString dstrSearchType;
	getField(ifds::AMSSearchType,dstrSearchType,idDataGroup,false);
	if( dstrSearchType == SEARCH_TYPE_AMSCODE )
	{
		lFieldIds1[0] = ifds::AMSType;
		lFieldIds1[1] = ifds::AMSCode;	
		lFieldIds2[0] = ifds::EffectiveDate;
		clearFieldsValue( lFieldIds2, idDataGroup);	

	}
	else if(	dstrSearchType == SEARCH_TYPE_EFFECTIVE_DATE	)
	{
		lFieldIds1[0] = ifds::AMSType;	
		lFieldIds1[1] = ifds::EffectiveDate;

		lFieldIds2[0] = ifds::AMSCode;

		setFieldNoValidate( ifds::EffectiveDate, _dstrCurDate, idDataGroup, false,true, false, false  ); 


	}
	setFieldsAsRequired( lFieldIds1,idDataGroup,true );
	setFieldsAsRequired( lFieldIds2,idDataGroup,false );

}
//*********************************************************************************
void AMSSearchCriteria::setFieldsAsRequired( const BFFieldId idField[], const BFDataGroupId& idDataGroup,bool bReqired )
{
   int i = 0;  
   while( idField[i] != ifds::NullFieldId )
   {
      setFieldRequired( idField[i],idDataGroup,bReqired );
      setValidFlag(  idField[i], idDataGroup, false);
      i++;
   }
}
//***********************************************************************************
void AMSSearchCriteria::clearFieldsValue( const BFFieldId idField[], const BFDataGroupId& idDataGroup)
{
   int i = 0;  
   while( idField[i] != ifds::NullFieldId )
   {
      setFieldNoValidate( idField[i],NULL_STRING,idDataGroup,false,true,true );
      i++;
   }
}

//***********************************************************************************
void AMSSearchCriteria::getAMSTypeList(DString &dstrAMSTypeList)
{
	DString dstrCode,dstrDes, dstrCodeList ;
	dstrCodeList = NULL_STRING;
	dstrAMSTypeList = NULL_STRING;

	getWorkSession().getMgmtCoOptions()->getField(ifds::ClientAMSType, dstrCodeList, BF::HOST, false);
	dstrCodeList.strip().upperCase();

	BFProperties * pBFP = getFieldProperties(ifds::AMSType, BF::HOST);

    if( dstrCodeList != NULL_STRING )
      dstrCodeList += I_(",");

    int iPos =  dstrCodeList.find_first_of(I_(",") );
    while( iPos != DString::npos )
    {
		iPos =  dstrCodeList.find_first_of(I_(",") );
		if( iPos == DString::npos ) break;
		dstrCode = dstrCodeList.left(iPos);
		dstrCodeList = dstrCodeList.right(dstrCodeList.length() - iPos  - 1);
		dstrDes = dstrCode;
		_dstrAmsType = dstrCode;
		pBFP->formatValue(ifds::AMSType,dstrDes,true);
		dstrAMSTypeList += dstrCode+I_("=") + dstrDes + I_(";");
	}	

}

//*****************************************************************************************
void AMSSearchCriteria::clearUpdateFlags(const BFDataGroupId& idDataGroup)
{

   clearUpdatedFlags( idDataGroup );
   setAllFieldsValid( idDataGroup );


}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AMSSearchCriteria.cpp-arc  $
// 
//    Rev 1.1   Nov 14 2004 14:26:04   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.0   Aug 22 2003 11:23:30   linmay
// Initial Revision
// 
 * 
 */









