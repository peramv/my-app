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
// ^FILE   : MktIndexValues.cpp
// ^AUTHOR : 
// ^DATE   : 
//
//********************************************************************************
#include "stdafx.h"
#include "MktIndexValues.hpp"
#include "MktIndexValuesList.hpp"
#include "MktIndexFundsList.hpp"
#include "MktIndexMaster.hpp"
#include "MktIndexMasterList.hpp"
#include "MgmtCoOptions.hpp"
#include "mgmtco.hpp"
#include "DSTCommonFunction.hpp"

#include <ifastdataimpl\dse_dstc0247_vw.hpp>
#include <ifastdataimpl\dse_dstc0247_req.hpp>

namespace
{
   const I_CHAR * const CLASSNAME               = I_( "MktIndexValues" );
   const I_CHAR * const INDEXFUNDSLIST          = I_( "MktIndexFundsList" );
}

namespace CND
{
   extern const long ERR_DUPLICATE_MKT_INDEX_ENTRY;
   extern const long ERR_CLOSING_VALUE_ZERO;
   extern const long WARN_VALUE_BETWEEN_TWO_REOCRDS; 
   extern const long ERR_VALUE_BETWEEN_TWO_REOCRDS;
   extern const long WARN_HURDLE_CALCULATED;
   extern const long ERR_HURDLE_CALCULATED;
   extern const long WARN_HURDLE_BETWEEN_TWO_REOCRDS;
   extern const long ERR_HURDLE_BETWEEN_TWO_REOCRDS;
   extern const long ERR_HURDLE_RATE_ZERO;
   extern const long WARN_HURDLE_RATE_ZERO;
   extern const long ERR_VALUE_ZERO; 
   extern const long WARN_VALUE_ZERO;
   extern const long ERR_DUPLICATE_HURDLE_ENTRY;
   extern const long WARN_DUPLICATE_HURDLE_ENTRY; 
}
namespace IFASTERR 
{
   extern CLASS_IMPORT I_CHAR * const VALUE_BETWEEN_TWO_REOCRDS;
   extern CLASS_IMPORT I_CHAR * const HURDLE_CALCULATED;
   extern CLASS_IMPORT I_CHAR * const HURDLE_BETWEEN_TWO_REOCRDS;
   extern CLASS_IMPORT I_CHAR * const HURDLE_RATE_ZERO;
   extern CLASS_IMPORT I_CHAR * const VALUE_ZERO;    
   extern CLASS_IMPORT I_CHAR * const DUPLICATE_HURDLE_ENTRY;
}
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId IndexName;
   extern CLASS_IMPORT const BFTextFieldId DUPLICATE_CHK;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const MKT_INDEX;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
//  Field DD Id,					State Flags,			Group Flags 
   { ifds::IndexCode,     BFCBO::REQUIRED,                 0 }, 
   { ifds::EffectiveDate, BFCBO::REQUIRED,                 0 },
   { ifds::ClosingValue,  BFCBO::REQUIRED,                 0 },
   { ifds::GoodBad,       BFCBO::NONE,                     0 },
   { ifds::PercentageChanged, BFCBO::NONE,                 0 },
   { ifds::HurdleRate,    BFCBO::REQUIRED,                 0 },

   // Admin/Date fields
   { ifds::ProcessDate,   BFCBO::NONE,                     0 }, 
   { ifds::Username,      BFCBO::NONE,                     0 }, 
   { ifds::ModDate,       BFCBO::NONE,                     0 }, 
   { ifds::ModUser,       BFCBO::NONE,                     0 }, 

   // Cross Edit
   { ifds::DUPLICATE_CHK, BFCBO::NONE,                     0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = 
{
   // Object Label,                 State Flags,      Group Flags 
   { I_( "MktIndexFundsList" ),    BFCBO::NONE,     0},
};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );

//******************************************************************************

MktIndexValues::MktIndexValues( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, NUM_OBJECTS, (const CLASS_OBJECT_INFO *)&classObjectInfo );

   addCrossEdit ( ifds::DUPLICATE_CHK, ifds::IndexCode ); 
   addCrossEdit ( ifds::DUPLICATE_CHK, ifds::EffectiveDate );
   //addCrossEdit ( ifds::DUPLICATE_CHK, ifds::ClosingValue );
}

//******************************************************************************

MktIndexValues::~MktIndexValues()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}  

//******************************************************************************

SEVERITY MktIndexValues::init(const BFData& data, const DString& dstrSubstitution )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   attachDataObject(const_cast<BFData&>(data), false);  
   // setFieldStates
//	bool bPermit = getWorkSession().hasUpdatePermission(UAF::MKT_INDEX );
   setFieldAllSubstituteValues( ifds::IndexCode, BF::HOST, dstrSubstitution );

   DString dstrStatus = data.getElementValue( ifds::GoodBad );
   if( dstrStatus == I_("N") )   // N - BAD Record.
   {
      setFieldReadOnly( ifds::EffectiveDate, BF::HOST, true );
      setFieldReadOnly( ifds::IndexCode, BF::HOST, true );
      setFieldReadOnly( ifds::ClosingValue, BF::HOST, true );
	  setFieldReadOnly( ifds::HurdleRate, BF::HOST, true );
   }
   clearUpdatedFlags( BF::HOST, false );
	return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************

void MktIndexValues::initNew(const BFDataGroupId& idDataGroup, const DString& dstrSubstitution, const DString& dstrIndexCode )
{
//	setFieldStates( idDataGroup );
//	bool bPermit = getWorkSession().hasUpdatePermission( UAF::MKT_INDEX );
/*
	setFieldNoValidate(ifds::IndexCode, NULL_STRING, idDataGroup, false);
	setFieldNoValidate(ifds::IndexName, NULL_STRING, idDataGroup, false);
*/
   setFieldAllSubstituteValues( ifds::IndexCode, idDataGroup, dstrSubstitution );
   setFieldNoValidate(ifds::IndexCode, dstrIndexCode, idDataGroup, false );
   clearUpdatedFlags( idDataGroup, false );
}

//*********************************************************************************

SEVERITY MktIndexValues::doValidateField( const BFFieldId& idField, const DString& dstrValue, 
												      const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField" ));   

   if (idField == ifds::ClosingValue )
   {
	   validateClosingValue(idDataGroup,dstrValue);
   }
   else if (idField == ifds::DUPLICATE_CHK )
   {
      duplicateCheck( idDataGroup );
   }
   else if (idField == ifds::HurdleRate )
   {
	    validateHurdleRate(idDataGroup,dstrValue);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//***************************************************************************************

SEVERITY MktIndexValues::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges") );
   
   if( (idField == ifds::IndexCode ) ||
	   (idField == ifds::HurdleRate ) ||
	   (idField == ifds::ClosingValue ))
   {
      clearRequiredFlags(idDataGroup);	
   } 
   return GETCURRENTHIGHESTSEVERITY();
}

//************************************************************************************

SEVERITY MktIndexValues::getMktIndexFundsList( MktIndexFundsList *&pMktIndexFundsList, const BFDataGroupId& idDataGroup, bool bCreate )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getMktIndexFundsList") );
   pMktIndexFundsList = NULL;
   DString dstrIndexCode;
   getField( ifds::IndexCode, dstrIndexCode, idDataGroup );
   dstrIndexCode.upperCase();

   MktIndexMasterList *pMktIndexMasterList = NULL;
   MktIndexMaster *pMktIndexMaster = NULL;
   getWorkSession().getMktIndexMasterList(pMktIndexMasterList, idDataGroup, bCreate);
   if( pMktIndexMasterList ) {
      BFObjIter iter( *pMktIndexMasterList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
      if( iter.positionByKey( dstrIndexCode ) )
      {
         pMktIndexMaster = static_cast<MktIndexMaster *>( iter.getObject());
         pMktIndexMaster->getMktIndexFundsList( pMktIndexFundsList, idDataGroup );
      }
   }

	return(GETCURRENTHIGHESTSEVERITY());
}

//*******************************************************************************

SEVERITY MktIndexValues::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{ 
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );
	MktIndexFundsList* pMktIndexFundsList = NULL;
	getMktIndexFundsList( pMktIndexFundsList, idDataGroup, false );

   if( pMktIndexFundsList )
	{
      pMktIndexFundsList->validateAll( idDataGroup, lValidateGroup );
	}

   return(GETCURRENTHIGHESTSEVERITY());
}

//*******************************************************************************

SEVERITY MktIndexValues::duplicateCheck( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("duplicateCheck") );

   DString dstrIndexCode, dstrEffectiveDate, dstrClosingValue, dstrStatus,dstrHurdleRate;
   getField( ifds::IndexCode, dstrIndexCode, idDataGroup );
   getField( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup );
   getField( ifds::ClosingValue, dstrClosingValue, idDataGroup );
   getField( ifds::GoodBad, dstrStatus, idDataGroup );
   getField( ifds::HurdleRate, dstrHurdleRate, idDataGroup );

   dstrIndexCode.strip().upperCase();
   dstrEffectiveDate.strip().upperCase();
   dstrClosingValue.strip().upperCase();
   dstrStatus.strip().upperCase();

   DString dstrInputDataType = getInputDataType(idDataGroup); 
   
   if( dstrInputDataType == I_("03") ) 
   {
	   DString dstrZeroCheck( dstrHurdleRate );
	   dstrZeroCheck.stripAll( I_CHAR('0') ).stripAll( I_CHAR('.') );

	   if( dstrIndexCode.empty() || 
		   dstrEffectiveDate.empty() || 
		   dstrHurdleRate.empty() ||
		   dstrStatus == I_("N") ||
		   dstrZeroCheck.empty()
		   )
	   {
		   return( NO_CONDITION );
	   }
   }
   else 
   {
	   DString dstrZeroCheck( dstrClosingValue );
	   dstrZeroCheck.stripAll( I_CHAR('0') ).stripAll( I_CHAR('.') );

	   if( dstrIndexCode.empty() || 
		   dstrEffectiveDate.empty() || 
		   dstrClosingValue.empty() || 
		   dstrStatus == I_("N") ||
		   dstrZeroCheck.empty()
		   )
	   {
		   return( NO_CONDITION );
	   }
   }

	bool bExist = (dynamic_cast<MktIndexValuesList*>(getParent()) )->isDuplicate( dstrIndexCode, dstrEffectiveDate, idDataGroup );
   if( bExist )
	{
		DString dstrTag;
		getField( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, true );
		addIDITagValue( dstrTag, I_("CODE"), dstrIndexCode );
		addIDITagValue( dstrTag, I_("DATE"), dstrEffectiveDate );
		if( dstrInputDataType == I_("03") )
		{
			getErrMsg ( IFASTERR::HURDLE_CALCULATED,
				CND::ERR_DUPLICATE_HURDLE_ENTRY,
				CND::WARN_DUPLICATE_HURDLE_ENTRY,
				idDataGroup,
				dstrTag);
		}
		else
		{			
			ADDCONDITIONFROMFILEIDI( CND::ERR_DUPLICATE_MKT_INDEX_ENTRY, dstrTag );
		}
		return  GETCURRENTHIGHESTSEVERITY();
	}

   return GETCURRENTHIGHESTSEVERITY();
}
//********************************************************************************************
DString MktIndexValues::getInputDataType(const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("isHurdleOption" )); 
	
	DString dstrIndexCode;
	getField( ifds::IndexCode, dstrIndexCode, idDataGroup );  

	DString dstrInputDataType = (dynamic_cast<MktIndexValuesList*>(getParent()) )->getInputDataType( dstrIndexCode, idDataGroup );

	return dstrInputDataType;
}
//************************************************************************************************************
SEVERITY MktIndexValues::validateClosingValue( const BFDataGroupId& idDataGroup,const DString& dstrValue )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("ValidateClosingValue" )); 
   DString dstrInputDataType = getInputDataType(idDataGroup); 
   
   if( dstrInputDataType == I_("01") )// For 'Index' 
   { 
	   DString dstrZeroCheck( dstrValue );
	   dstrZeroCheck.stripAll().stripAll( I_CHAR('0') ).stripAll( I_CHAR('.') );
	   if( dstrZeroCheck.empty() )
	   {
		   ADDCONDITIONFROMFILE( CND::ERR_CLOSING_VALUE_ZERO );
	   }
   }
   else if( dstrInputDataType == I_("02"))//Index with Hurdle calculation
   {
	   DString dstrZeroCheck( dstrValue );
	   dstrZeroCheck.stripAll().stripAll( I_CHAR('0') ).stripAll( I_CHAR('.') );
	   if( dstrZeroCheck.empty() )
	   {
		   getErrMsg ( IFASTERR::VALUE_ZERO,
                              CND::ERR_VALUE_ZERO,
                              CND::WARN_VALUE_ZERO,
                              idDataGroup );
	   }
	   if(GETCURRENTHIGHESTSEVERITY() <= WARNING)
	   {
		   DString dstrEffectiveDate,dstrIndexCode;
		   getField( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup );
		   getField( ifds::IndexCode, dstrIndexCode, idDataGroup );

		   DString dstrDate1=I_(""),dstrDate2=I_("");

		  
		   MktIndexValuesList* pMktIndexValuesListToCheck = NULL;
		   if ( getWorkSession ().getMktIndexValuesList (pMktIndexValuesListToCheck,
														 idDataGroup,															
														 dstrIndexCode,															
														 dstrEffectiveDate,
														 I_("EDITCHECK"),
														 NULL_STRING) <= WARNING && pMktIndexValuesListToCheck ) 
		   {
			   isBetweenTwoIndex( pMktIndexValuesListToCheck,idDataGroup,dstrDate1,dstrDate2);
			   if( dstrDate1 != I_("") && dstrDate2 != I_("") )
			   {
				   //WARNMSG:: Hurdle is calculated between dstrDate1 to dstrEffectiveDate and dstrEffectiveDate to dstrDate2.
				   
				   DSTCommonFunctions::FormatDate(dstrDate1);
				   DSTCommonFunctions::FormatDate(dstrEffectiveDate);
				   DSTCommonFunctions::FormatDate(dstrDate2);
				  

				   DString dstrTag;
				   addIDITagValue( dstrTag, I_("DATE1"), dstrDate1);
				   addIDITagValue( dstrTag, I_("DATE2"), dstrEffectiveDate);
				   addIDITagValue( dstrTag, I_("DATE3"), dstrEffectiveDate);
				   addIDITagValue( dstrTag, I_("DATE4"), dstrDate2);
				
				   getErrMsg ( IFASTERR::VALUE_BETWEEN_TWO_REOCRDS,
					   CND::ERR_VALUE_BETWEEN_TWO_REOCRDS,
					   CND::WARN_VALUE_BETWEEN_TWO_REOCRDS,
					   idDataGroup,
					   dstrTag);
			   }
			   else if( dstrDate1 != I_("") && dstrDate2 == I_("") )
			   {
				   if( DSTCommonFunctions::CompareDates (dstrDate1, dstrEffectiveDate) == DSTCommonFunctions::FIRST_EARLIER )
				   {
					   //WARNMSG::Hurdle is calculated between dstrDate1 to dstrEffectiveDate
					   DSTCommonFunctions::FormatDate(dstrDate1);
					   DSTCommonFunctions::FormatDate(dstrEffectiveDate);
				       
				  
					   DString dstrTag;
					   addIDITagValue( dstrTag, I_("DATE1"), dstrDate1);
					   addIDITagValue( dstrTag, I_("DATE2"), dstrEffectiveDate);

					   getErrMsg ( IFASTERR::HURDLE_CALCULATED,
						   CND::ERR_HURDLE_CALCULATED,
						   CND::WARN_HURDLE_CALCULATED,
						   idDataGroup,
						   dstrTag);
				   }
				   else
				   {
					   //WARNMSG:: Hurdle is calculated between dstrEffectiveDate to dstrDate1
					   DSTCommonFunctions::FormatDate(dstrDate1);
				       DSTCommonFunctions::FormatDate(dstrEffectiveDate);
				   				  
					   DString dstrTag;			  
					   addIDITagValue( dstrTag, I_("DATE1"), dstrEffectiveDate);
					   addIDITagValue( dstrTag, I_("DATE2"), dstrDate1);

					   getErrMsg ( IFASTERR::HURDLE_CALCULATED,
						   CND::ERR_HURDLE_CALCULATED,
						   CND::WARN_HURDLE_CALCULATED,
						   idDataGroup,
						   dstrTag);
				   }
			   }
		   }
	   }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//**********************************************************************************************
bool MktIndexValues::isBetweenTwoIndex( MktIndexValuesList* pMktIndexValuesListToCheck,
									    const BFDataGroupId& idDataGroup,
										DString &dstrDate1,
										DString &dstrDate2)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("isDuplicate") );

	bool bExist = false;
	BFObjIter iter( *pMktIndexValuesListToCheck, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
	iter.begin();

	short nFound = 0;
	while( !iter.end() && nFound < 2)
	{
		if( nFound == 0)
		{
			iter.getObject()->getField( ifds::EffectiveDate, dstrDate1, idDataGroup, false );
			dstrDate1.upperCase();
		}
		if( nFound == 1)
		{
			iter.getObject()->getField( ifds::EffectiveDate, dstrDate2, idDataGroup, false );
			dstrDate2.upperCase();
		}
		++nFound;
		++iter;
	}
	if (nFound > 1)
		bExist = true;

	CLEARCONDITIONS();

	return bExist;
}
//************************************************************************************************************
SEVERITY MktIndexValues::validateHurdleRate( const BFDataGroupId& idDataGroup,const DString& dstrValue )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("ValidateClosingValue" )); 
   DString dstrInputDataType = getInputDataType(idDataGroup); 
   
   if( dstrInputDataType == I_("03") )//Hurdle
   { 
	   DString dstrZeroCheck( dstrValue );
	   dstrZeroCheck.stripAll().stripAll( I_CHAR('0') ).stripAll( I_CHAR('.') );
	   if( dstrZeroCheck.empty() )
	   {
		   getErrMsg ( IFASTERR::HURDLE_RATE_ZERO,
                              CND::ERR_HURDLE_RATE_ZERO,
                              CND::WARN_HURDLE_RATE_ZERO,
                              idDataGroup );
	   }
	   if(GETCURRENTHIGHESTSEVERITY() <= WARNING)
	   {
		   DString dstrEffectiveDate,dstrIndexCode;
		   getField( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup );
		   getField( ifds::IndexCode, dstrIndexCode, idDataGroup );

		   DString dstrDate1=I_(""),dstrDate2=I_("");
		   MktIndexValuesList* pMktIndexValuesListToCheck = NULL;
		   if ( getWorkSession ().getMktIndexValuesList (pMktIndexValuesListToCheck,
														 idDataGroup,															
														 dstrIndexCode,															
														 dstrEffectiveDate,
														 I_("EDITCHECK"),
														 NULL_STRING) <= WARNING && pMktIndexValuesListToCheck ) 
		   {
			   bool bBetween2Records = isBetweenTwoIndex( pMktIndexValuesListToCheck,idDataGroup,dstrDate1,dstrDate2);
			   if( bBetween2Records )
			   {
				   //WARNMSG:: Records modified between two existing dates
				   getErrMsg ( IFASTERR::HURDLE_BETWEEN_TWO_REOCRDS,
					   CND::ERR_HURDLE_BETWEEN_TWO_REOCRDS,
					   CND::WARN_HURDLE_BETWEEN_TWO_REOCRDS,
					   idDataGroup );
			   }
		   }
	   }
   }
   return GETCURRENTHIGHESTSEVERITY();
}
//*******************************************************************************
void MktIndexValues::clearRequiredFlags( const BFDataGroupId& idDataGroup )
{
	DString dstrIndexCode;
	getField( ifds::IndexCode, dstrIndexCode, idDataGroup );  

	DString dstrInputDataType = (dynamic_cast<MktIndexValuesList*>(getParent()) )->getInputDataType( dstrIndexCode, idDataGroup );

	if(dstrInputDataType == I_("03"))//Hurdle
	{
		setFieldRequired(ifds::HurdleRate, idDataGroup, true);
		setValidFlag(ifds::HurdleRate, idDataGroup, false);

		setFieldRequired(ifds::ClosingValue, idDataGroup, false);
		setValidFlag(ifds::ClosingValue, idDataGroup, true);

		clearFieldErrors( ifds::ClosingValue, idDataGroup );
	}
	else //Index and Index with Hurdle calculation
	{
		setFieldRequired(ifds::HurdleRate, idDataGroup, false);
		setValidFlag(ifds::HurdleRate, idDataGroup, true);

		setFieldRequired(ifds::ClosingValue, idDataGroup, true);
		setValidFlag(ifds::ClosingValue, idDataGroup, false);
		
		clearFieldErrors( ifds::HurdleRate, idDataGroup );
	}	
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/MktIndexValues.cpp-arc  $
// 
//    Rev 1.12   Jan 16 2012 14:33:42   wp040027
// P0188394_Performance Fees - Benchmark Upload
// 
//    Rev 1.11   Nov 14 2004 14:50:38   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.10   May 16 2003 17:32:42   HERNANDO
// Initialize IndexCode.
// 
//    Rev 1.9   Mar 21 2003 18:19:32   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.8   Feb 27 2003 11:36:04   HERNANDO
// Uppercase the IndexCode in getMktIndexFundsList.
// 
//    Rev 1.7   Feb 06 2003 15:18:00   HERNANDO
// Revised zero-check.
// 
//    Rev 1.6   Feb 06 2003 13:39:04   HERNANDO
// Clean-up.
// 
//    Rev 1.5   Feb 06 2003 11:34:22   HERNANDO
// Quick fix before a clean up.
// 
//    Rev 1.4   Feb 06 2003 10:40:08   HERNANDO
// Added duplicate check.
// 
//    Rev 1.3   Feb 03 2003 15:54:50   HERNANDO
// Revised.
// 
//    Rev 1.2   Jan 29 2003 18:33:56   HERNANDO
// Revised.
// 
//    Rev 1.1   Jan 29 2003 12:14:06   HERNANDO
// Revised.
//