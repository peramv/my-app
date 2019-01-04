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
//    Copyright 2002 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : AbstractFundAlloc.cpp
// ^AUTHOR : Yingbao   Li
// ^DATE   : Nov. 13, 2002
//
// ^CLASS    : AbstractFundAlloc
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : Abstract Fund Allocation
//
//******************************************************************************
#include "stdafx.h"
#include "AbstractFundAlloc.hpp"
#include "AbstractFundAlloclist.hpp"
#include "FundMasterList.hpp"
#include "mgmtco.hpp"
#include "FundDetailList.hpp"

namespace
{
   const I_CHAR * const CLASSNAME              = I_( "AbstractFundAlloc" );
   const I_CHAR * const NO                     = I_( "N" );
   const I_CHAR * const YES                    = I_( "Y" );
   const double dSmallValue                    = .0000000001;
}

namespace CND
{  // Conditions used
   extern const long ERR_BLANK_FUND;    
   extern const long ERR_INVALID_FUND_CLASS_CODES;    
   extern const long ERR_INVALID_FUND_NUMBER;    
   extern const long ERR_BLANK_CLASS;    
   extern const long ERR_INVALID_FUND_CLASS_CODES;    
   extern const long ERR_ENTRY_EMPTY_OR_CONTAINS_ONLY_SPACE;    
   extern const long ERR_VALUE_BETWEEN_0_AND_100;    
   extern const long ERR_INVALID_FUND_NUMBER;    
}

namespace ifds
{  
   extern CLASS_IMPORT const BFTextFieldId		FundCode;
   extern CLASS_IMPORT const BFTextFieldId		ClassCode;
   extern CLASS_IMPORT const BFTextFieldId		FundClass;
   extern CLASS_IMPORT const BFTextFieldId		ToFundNumber;
   extern CLASS_IMPORT const BFDecimalFieldId	AllocPercentage;

}
//******************************************************************************
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//		Field DD Id,				State Flags,					      Group Flags
   { ifds::FundClass,			  BFCBO::IMMEDIATE_VALIDATION, 0 },
   { ifds::FundCode,           BFCBO::REQUIRED,             0 }, 
   { ifds::ClassCode,          BFCBO::REQUIRED,             0 }, 
   { ifds::ToFundNumber,			  BFCBO::NONE,                 0 }, 
   { ifds::AllocPercentage,	  BFCBO::NONE,                 0 }, 
};


static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
AbstractFundAlloc::AbstractFundAlloc( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS,  (const CLASS_FIELD_INFO *)&classFieldInfo,
                       NULL, NULL);

   addCrossEdit(ifds::FundClass, ifds::FundCode);
   addCrossEdit(ifds::FundClass, ifds::ClassCode);
}

//******************************************************************************
AbstractFundAlloc::~AbstractFundAlloc( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}


//******************************************************************************

SEVERITY AbstractFundAlloc::initExisting(const BFData &data)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initExisting" ) );

   attachDataObject( const_cast< BFData & >( data ), false, true ); 
   setFundNumber(BF::HOST);

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY AbstractFundAlloc::doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );
 
	if( idField == ifds::ToFundNumber )
		validateFundNumber(strValue,idDataGroup );
   if( idField == ifds::FundCode )
      validateFundCode( strValue, idDataGroup );
   else if( idField == ifds::ClassCode )
      validateClassCode( strValue, idDataGroup );
   else if( idField == ifds::FundClass )
      validateFundClass ( idDataGroup );
   else if( idField == ifds::AllocPercentage )
      validatePercentage(strValue, idDataGroup);
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY AbstractFundAlloc::validateFundCode( const DString& strValue, const BFDataGroupId& idDataGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFundCode" ) );
   DString dstrFundCode( strValue );

   if( dstrFundCode.strip().upperCase().empty() )
   {
      ADDCONDITIONFROMFILE( CND::ERR_BLANK_FUND );
      return(GETCURRENTHIGHESTSEVERITY());  
   }

   FundMasterList *pFundMasterList = NULL;
   if( getMgmtCo().getFundMasterList(pFundMasterList)<=WARNING && pFundMasterList )
      if( !(pFundMasterList->IsFundExist( dstrFundCode, idDataGroup ) ) )
         ADDCONDITIONFROMFILE( CND::ERR_INVALID_FUND_CLASS_CODES );


   return(GETCURRENTHIGHESTSEVERITY());
}
//*****************************************************************************

SEVERITY AbstractFundAlloc::validateFundNumber( const DString& strValue, const BFDataGroupId& idDataGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFundNumber" ) );
   DString dstrFundCode,dstrClassCode;
   if( !getWorkSession().GetFundClassCode( strValue,dstrFundCode,dstrClassCode ) )
      ADDCONDITIONFROMFILE( CND::ERR_INVALID_FUND_NUMBER );

   return(GETCURRENTHIGHESTSEVERITY());
}



//******************************************************************************

SEVERITY AbstractFundAlloc::validateClassCode( const DString& strValue, const BFDataGroupId& idDataGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateClassCode" ) );
   DString dstrClassCode( strValue );
   if( dstrClassCode.strip().empty() )
   {
      ADDCONDITIONFROMFILE( CND::ERR_BLANK_CLASS );
      return(GETCURRENTHIGHESTSEVERITY());
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AbstractFundAlloc::validateFundClass( const BFDataGroupId& idDataGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFundClass" ) );
   FundDetail *pFundDetail = NULL;
   DString dstrClassCode, dstrFundCode;
   getField(ifds::FundCode, dstrFundCode, idDataGroup, false);
   getField(ifds::ClassCode, dstrClassCode, idDataGroup, false);
   getFundDetail( dstrFundCode.strip().upperCase(), dstrClassCode.strip().upperCase(), pFundDetail );
   if( !pFundDetail )
      ADDCONDITIONFROMFILE( CND::ERR_INVALID_FUND_CLASS_CODES );

   return(GETCURRENTHIGHESTSEVERITY());
}


//**********************************************************************************

SEVERITY AbstractFundAlloc::validatePercentage( const DString& strValue, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validatePercentage"));

   DString strPercentage( strValue );
   strPercentage.strip();
   if( strPercentage.empty() )
   {
      ADDCONDITIONFROMFILE( CND::ERR_ENTRY_EMPTY_OR_CONTAINS_ONLY_SPACE );
      return(GETCURRENTHIGHESTSEVERITY());
   }

   double dPercent = DSTCommonFunctions::convertToDouble(strPercentage);

   if( dPercent<0-dSmallValue || dPercent > 100+dSmallValue )
      ADDCONDITIONFROMFILE( CND::ERR_VALUE_BETWEEN_0_AND_100 );

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
SEVERITY AbstractFundAlloc::setFundNumber(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setFundNumber" ) );

   DString dstrFundNumber,dstrFundCode,dstrClassCode;

   getField(ifds::FundCode,dstrFundCode,idDataGroup,false);
   getField(ifds::ClassCode,dstrClassCode,idDataGroup,false);

   getWorkSession().GetFundNumber( dstrFundCode.strip().upperCase(), 
                                   dstrClassCode.strip().upperCase(), dstrFundNumber );

	setFieldNoValidate( ifds::ToFundNumber,dstrFundNumber,idDataGroup, false,true,true,false);

   return(GETCURRENTHIGHESTSEVERITY());
}
//**********************************************************************************

SEVERITY AbstractFundAlloc::setFundClassCode(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setFundClassCode" ) );

   DString dstrFundNumber,dstrFundCode,dstrClassCode;

   getField(ifds::ToFundNumber,dstrFundNumber,idDataGroup,false);

   if( !dstrFundNumber.strip().empty() )
   {
      if( getWorkSession().GetFundClassCode(
                                                                    dstrFundNumber,dstrFundCode, dstrClassCode) )
      {
			setFieldNoValidate( ifds::FundCode,dstrFundCode,idDataGroup, false,true,true,false);
			setFieldNoValidate( ifds::ClassCode,dstrClassCode,idDataGroup, false,true,true,false);
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}
//**********************************************************************************
SEVERITY AbstractFundAlloc::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );
	if(idField == ifds::ToFundNumber )setFundClassCode(idDataGroup);
	else if( idField == ifds::FundCode || idField == ifds::ClassCode )
	{
		setFundNumber(idDataGroup);
	}
   return(GETCURRENTHIGHESTSEVERITY());
}
//**********************************************************************************
SEVERITY AbstractFundAlloc::getFundDetail( const DString& strFundCode, 
                                           const DString& strClassCode, 
                                           FundDetail *&pFundDetail )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   pFundDetail = NULL;
   FundDetailList * pFundDetailList = NULL;

   getMgmtCo().getFundDetailList(  pFundDetailList );

   if( pFundDetailList )
      pFundDetailList->getFundDetail( strFundCode, strClassCode, BF::HOST, pFundDetail);

   return(GETCURRENTHIGHESTSEVERITY());
}







//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AbstractFundAlloc.cpp-arc  $
// 
//    Rev 1.3   Nov 14 2004 14:24:04   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.2   Mar 21 2003 17:53:36   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.1   Nov 22 2002 13:46:14   YINGBAOL
// change FundNumber to ToFundNumber
// 
//    Rev 1.0   Nov 13 2002 10:00:42   YINGBAOL
// Initial Revision
// 
 * 
 * 
 */