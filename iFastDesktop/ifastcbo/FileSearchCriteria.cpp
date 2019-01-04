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
// ^FILE   : FileSearchCriteria.cpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 02/17/2005
//
// ^CLASS    : FileSearchCriteria
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "FileSearchCriteria.hpp"

#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"

namespace  
{
   const I_CHAR * const CLASSNAME					= I_( "FileSearchCriteria" );
   const I_CHAR * const YES							= I_( "Y" );
   const I_CHAR * const NO								= I_( "N" );
   const I_CHAR * const FILENAME						= I_( "FileName" );
	const I_CHAR * const NETWORKID					= I_( "NetworkID" );
	const I_CHAR * const STARTDATE					= I_( "StartDate" );
	const I_CHAR * const ENDDATE						= I_( "EndDate" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId  NetworkID;
	extern CLASS_IMPORT const BFTextFieldId  FileName;
	extern CLASS_IMPORT const BFDateFieldId  StartDate;
	extern CLASS_IMPORT const BFDateFieldId  EndDate;
	extern CLASS_IMPORT const BFDateFieldId  CurrBusDate;
	extern CLASS_IMPORT const BFTextFieldId  ValidNetworkType;
	extern CLASS_IMPORT const BFTextFieldId  NetworkTypeUpd;
}

namespace  CND
{
	extern const long ERR_START_DATE_LATE_THAN_STOP_DATE ; //Start date must precede End date.
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//   Field DD Id,								State Flags,       Group Flags 
   { ifds::NetworkID,					BFCBO::NONE,               0 }, 
   { ifds::FileName,						BFCBO::NONE,               0 }, 
   { ifds::StartDate,					BFCBO::REQUIRED,           0 }, 
   { ifds::EndDate,						BFCBO::REQUIRED,           0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = {
   //  Object Label,									State Flags,      Group Flags 
   { I_( "FileSearchCriteria" ),             BFCBO::NONE,      0},
   
};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );

//****************************************************************************
FileSearchCriteria::FileSearchCriteria( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       NUM_OBJECTS, 
							  (const CLASS_OBJECT_INFO *)&classObjectInfo );
 
}

//****************************************************************************
FileSearchCriteria::~FileSearchCriteria()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}   

//****************************************************************************

SEVERITY FileSearchCriteria::init(const BFDataGroupId& idDataGroup /*=BF::HOST*/,
   const DString& dstrTrack /*= I_("N")*/, const DString& dstrPageName /*= NULL_STRING*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   doInitWithDefaultValues(idDataGroup);
	setObjectNew();

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

void FileSearchCriteria::doInitWithDefaultValues(const BFDataGroupId& idDataGroup)
{

	//rules for default values:
	//1. StartDate is current business date
	//2. EndDate is current business date
	//3. All the other text fields are empty
	//4. Set NetWorkID substitution list
  
	DString dstrCurrBusDate = getCurrentBusDate();

   setFieldNoValidate(ifds::StartDate, dstrCurrBusDate, idDataGroup, false, true, true);
   setFieldNoValidate(ifds::EndDate,   dstrCurrBusDate, idDataGroup, false, true, true);
	setFieldNoValidate(ifds::FileName,  NULL_STRING, idDataGroup, false, true, true);
	loadNetworkIDValues(idDataGroup);
  

}
    
//******************************************************************************

SEVERITY FileSearchCriteria::doValidateField(const BFFieldId& idField, 
   const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

	if( idField == ifds::StartDate )
      validateDateRange( idDataGroup);
   else if ( idField == ifds::EndDate )
      validateDateRange( idDataGroup);
 
	return(GETCURRENTHIGHESTSEVERITY());
}
 
//******************************************************************************

DString FileSearchCriteria::getCurrentBusDate()
{
   MgmtCoOptions *pMgmtCoOptions = NULL;
	getMgmtCo().getMgmtCoOptions( pMgmtCoOptions );
   DString dstrCurrBusDate(NULL_STRING);
   if( pMgmtCoOptions )
      pMgmtCoOptions->getField( ifds::CurrBusDate, dstrCurrBusDate, BF::HOST, false );
   return dstrCurrBusDate.strip();
}

//*****************************************************************************
SEVERITY FileSearchCriteria::loadNetworkIDValues (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("loadNetworkIDValues"));

   DString validNetworkType;//comma separated list of valid network types for the environment

   getWorkSession().getOption ( ifds::ValidNetworkType,
                                validNetworkType,
                                BF::HOST,
                                false);
   
   if (!validNetworkType.empty())
   {
      loadSubstitutionList (ifds::NetworkID, idDataGroup, validNetworkType);
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//*****************************************************************************
SEVERITY FileSearchCriteria::validateDateRange( const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateDateRange" ) );

	DString dstrStartDate, dstrEndDate;
	getField(ifds::StartDate, dstrStartDate, idDataGroup, false);
	getField(ifds::EndDate, dstrEndDate, idDataGroup, false);
	if (!dstrStartDate.strip().empty() && !dstrEndDate.strip().empty() &&
      DSTCommonFunctions::CompareDates(dstrStartDate, dstrEndDate) == DSTCommonFunctions::SECOND_EARLIER)
   {
      ADDCONDITIONFROMFILE(CND::ERR_START_DATE_LATE_THAN_STOP_DATE);
   }
	return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FileSearchCriteria.cpp-arc  $
// 
//    Rev 1.2   Mar 18 2005 11:33:28   ZHANGCEL
// Magic #267177 -- Remove useless code
// 
//    Rev 1.1   Mar 17 2005 12:14:42   ZHANGCEL
// Magic #267177 -- Bug fix for the NetworkID comb box empty problem
// 
//    Rev 1.0   Feb 24 2005 17:42:20   ZHANGCEL
// Initial revision.

*/


