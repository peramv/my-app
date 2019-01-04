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
// ^FILE   : AmsLmtOverride.cpp
// ^AUTHOR : May Lin
// ^DATE   : July 03,2003
//
// ^CLASS    : AmsLmtOverride
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************
#include "stdafx.h"
#include "AmsLmtOverride.hpp"
#include "AmsLmtOverrideList.hpp"
#include <ifastdataimpl\dse_dstc0262_req.hpp>
#include <ifastdataimpl\dse_dstc0262_vw.hpp>

namespace
{
   const I_CHAR * const CLASSNAME		  = I_( "AmsLmtOverride" );
   const I_CHAR * const ALL				  = I_( "*" );
   const I_CHAR * const ERROR_MESSAGE	  = I_( "E" );
   const I_CHAR * const WARNING_MESSAGE  = I_( "W" );
   const I_CHAR * const IGNORE_MESSAGE	  = I_( "I" );
   const I_CHAR * const YES				  = I_( "Y" );
   const I_CHAR * const NO					  = I_( "N" );


   const I_CHAR * const MIN_INIT_PUR_AMT     = I_("01");  
   const I_CHAR * const MIN_SUB_SEQ_PUR      = I_("02");  
   const I_CHAR * const STOP_PUR             = I_("03");  
   const I_CHAR * const STOP_RED             = I_("04");  
   const I_CHAR * const STOP_TRFER_IN        = I_("05");  
   const I_CHAR * const STOP_TRFER_OUT       = I_("06");  
   const I_CHAR * const PAC_MIN_AMT          = I_("07");  
   const I_CHAR * const STOP_PAC             = I_("08");  
   const I_CHAR * const STOP_SWP             = I_("09");  
   const I_CHAR * const STOP_ATI             = I_("10");  
   const I_CHAR * const STOP_ATO             = I_("11");  
   const I_CHAR * const MIN_BAL              = I_("12");  
   const I_CHAR * const MAX_RED_PERCENT      = I_("13");  
	const I_CHAR * const MKT_VALUE_REBAL_MIN  = I_("14");  

   const I_CHAR * const RRSP_TAX_TYPE    = I_( "1" );
   const I_CHAR * const RRIF_TAX_TYPE    = I_( "2" );
   const I_CHAR * const RRSP_PLAN_TYPE   = I_( "RSP" );
   const I_CHAR * const RRIF_PLAN_TYPE   = I_( "RIF" );

   const I_CHAR * const ALL_CODE         = I_( "*" );   

   int INCLUDE = 1;
   int EXCLUDE = 0;
   int NOT_FOUND = -1;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FundAlloc;

}

namespace CND
{
   extern const long ERR_INVALID_ACCOUNT_TYPE;
   extern const long ERR_INVALID_TAX_TYPE;
   extern const long ERR_VALUE_BETWEEN_0_AND_100;
}


const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,             Group Flags 
   { ifds::RuleType,				BFCBO::REQUIRED,             0 }, 
   { ifds::OverrideDecimal,		BFCBO::NONE,                 0 }, 
   { ifds::OverrideLogical,        BFCBO::NONE,				 0 }, 
   { ifds::OverrideFundLevel,      BFCBO::NONE,				 0 }, 
   { ifds::AMSTaxType,				BFCBO::NONE,				 0 }, 
   { ifds::AMSAcctType,			BFCBO::NONE,				 0 }, 
   { ifds::AMSAcctDesignation,     BFCBO::NONE,				 0 }, 
   { ifds::AMSTaxJurisCode,        BFCBO::NONE,				 0 }, 
   { ifds::OnLineEWI,				BFCBO::NONE,				 0 }, 
   { ifds::CycleEWI,		        BFCBO::NONE,				 0 }, 
   { ifds::ESGEWI,			        BFCBO::NONE,				 0 }, 
   { ifds::AMSResProvCode,         BFCBO::NONE,				 0 }, 

};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//***************************************************************************************
AmsLmtOverride::AmsLmtOverride( BFAbstractCBO &parent ) :
MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo,0,NULL);

}

//***************************************************************************************
AmsLmtOverride::~AmsLmtOverride()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//***************************************************************************************
SEVERITY AmsLmtOverride::init( const BFData& data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   attachDataObject( const_cast<BFData&>(data), false, true );

   DString dstrRuleType = data.getElementValue(ifds::RuleType);
   dstrRuleType.strip();
   if ( dstrRuleType == STOP_PUR       ||
		  dstrRuleType == STOP_RED       ||            
		  dstrRuleType == STOP_TRFER_IN  ||
		  dstrRuleType == STOP_TRFER_OUT ||        
		  dstrRuleType == STOP_PAC       ||
		  dstrRuleType == STOP_SWP       ||
		  dstrRuleType == STOP_ATI       || 
		  dstrRuleType == STOP_ATO       || 
		  dstrRuleType == MIN_BAL        ||
		  dstrRuleType == MAX_RED_PERCENT )
	{
	   setFieldReadOnly(ifds::OverrideFundLevel, BF::HOST, true );
	}
	else if ( dstrRuleType == MKT_VALUE_REBAL_MIN )
	{
		setFieldReadOnly(ifds::OverrideFundLevel, BF::HOST, true);
		setFieldReadOnly(ifds::OverrideLogical,   BF::HOST, true);		
	}
	else
		setFieldReadOnly(ifds::OverrideFundLevel, BF::HOST, false );
	

   return(GETCURRENTHIGHESTSEVERITY());
}

//***************************************************************************************
void AmsLmtOverride::initNew(const BFDataGroupId& idDataGroup )
{

}
  
//***************************************************************************************
void AmsLmtOverride::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{
   setFieldNoValidate( ifds::OverrideDecimal, I_("0.00"), idDataGroup, false );
   setFieldNoValidate( ifds::OverrideLogical, NO, idDataGroup, false );
   setFieldNoValidate( ifds::OverrideFundLevel, NO, idDataGroup, false );
   setFieldNoValidate( ifds::AMSResProvCode, ALL, idDataGroup, false );
   setFieldNoValidate( ifds::AMSAcctType, ALL, idDataGroup, false );
   setFieldNoValidate( ifds::AMSTaxType, ALL, idDataGroup, false );
   setFieldNoValidate( ifds::AMSAcctDesignation, ALL, idDataGroup, false );
   setFieldNoValidate( ifds::AMSTaxJurisCode, ALL, idDataGroup, false );
   setFieldNoValidate( ifds::OnLineEWI, ERROR_MESSAGE, idDataGroup, false );
   setFieldNoValidate( ifds::CycleEWI, ERROR_MESSAGE, idDataGroup, false );
   setFieldNoValidate( ifds::ESGEWI, ERROR_MESSAGE, idDataGroup, false );

}
  
//***************************************************************************************
SEVERITY AmsLmtOverride::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

   if (idField == ifds::RuleType)
		doRuleTypeRelatedChanges(idDataGroup);
   
   return(GETCURRENTHIGHESTSEVERITY());

}
   
//***************************************************************************************
void AmsLmtOverride::doRuleTypeRelatedChanges(const BFDataGroupId& idDataGroup)
{
	DString dstrRuleType;
	getField(ifds::RuleType,dstrRuleType,idDataGroup,false);

	//if RuleType is Min. Subsequent Purchase, set default value for EWI to I
    if ( dstrRuleType == MIN_SUB_SEQ_PUR  || dstrRuleType == MIN_INIT_PUR_AMT )
	{
		setFieldReadOnly(ifds::OverrideFundLevel, idDataGroup, false );
		
		setFieldNoValidate( ifds::OnLineEWI, IGNORE_MESSAGE, idDataGroup, false, true, true );
		setFieldNoValidate( ifds::CycleEWI, IGNORE_MESSAGE, idDataGroup, false, true, true );
		setFieldNoValidate( ifds::ESGEWI, IGNORE_MESSAGE, idDataGroup, false, true, true );

	}
/*	
	else if ( dstrRuleType == MAX_RED_PERCENT )
	{
		setFieldNoValidate( ifds::OverrideDecimal, I_("100.00"), idDataGroup, false,false);

	}
*/
	else if ( dstrRuleType == STOP_PUR       || 
		       dstrRuleType == STOP_RED       || 
				 dstrRuleType == STOP_TRFER_IN  || 
				 dstrRuleType == STOP_TRFER_OUT || 
				 dstrRuleType == STOP_PAC       || 
				 dstrRuleType == STOP_SWP    	  || 
				 dstrRuleType == STOP_ATI    	  || 
				 dstrRuleType == STOP_ATO    	  || 
				 dstrRuleType == MIN_BAL 		  || 
				 dstrRuleType == MAX_RED_PERCENT )
	{
		setFieldReadOnly(ifds::OverrideFundLevel, idDataGroup, true);
		setFieldNoValidate( ifds::OverrideFundLevel, NO, idDataGroup, false );
	}
	else if ( dstrRuleType == MKT_VALUE_REBAL_MIN )
	{
		setFieldReadOnly(ifds::OverrideFundLevel, idDataGroup, true);
		setFieldReadOnly(ifds::OverrideLogical,   idDataGroup, true);

		setFieldNoValidate( ifds::OverrideFundLevel, NO, idDataGroup, false );
		setFieldNoValidate( ifds::OverrideLogical,   NO, idDataGroup, false );
	}
	else
	{
		setFieldReadOnly(ifds::OverrideFundLevel, idDataGroup, false );
	}
}

//***************************************************************************************
SEVERITY AmsLmtOverride::doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField") );
   
   DString dstrRuleType;
   getField(ifds::RuleType, dstrRuleType, idDataGroup, false);

   if (idField == ifds::OverrideDecimal &&  dstrRuleType == MAX_RED_PERCENT )
   {
		   validateMaxRedPercent(strValue, idDataGroup);
   }
   	return(GETCURRENTHIGHESTSEVERITY());
			
}


//***************************************************************************************
SEVERITY AmsLmtOverride::validateMaxRedPercent (const DString& strValue,const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateRate" ) )
   DString dstrPercent(strValue);
   dstrPercent.strip();
   double dPercent =  DSTCommonFunctions::convertToDouble( dstrPercent );
   if( dPercent > 100.0 || dPercent < 0.0 )
   {
      ADDCONDITIONFROMFILE( CND::ERR_VALUE_BETWEEN_0_AND_100 );
   }
   

   return(GETCURRENTHIGHESTSEVERITY());
}


//***************************************************************************************
// we are in the target item
void AmsLmtOverride::ModelAMS(AmsLmtOverride *Model, const BFDataGroupId& idDataGroup)
{
   BFData *tmp = new BFData(ifds::DSTC0262_VWRepeat_Record);


   BFDataFieldIter dIter(*tmp);
   DString str;

   for(;dIter; ++dIter)
   {
      const BFFieldId& idField = dIter().getId();
	  if ( idField != ifds::AMSRuleId ) //don't copy AMSRuleId, it should be unique
	  {
			Model->getField(idField, str, idDataGroup, false);
			setField(idField, str, idDataGroup, false);
	  }
   }

   delete tmp;
}

//***************************************************************************************
// return -1 if not found.
// return 1 if include.
// return 0 if exclude.
//***************************************************************************************
int AmsLmtOverride::isCodeAllowed ( const DString& dstrCode, const DString& dstrCodeList ) 
{
   DString dstrCopyCodeList = dstrCodeList;
   int iPos = dstrCopyCodeList.find(',');     
   int iFound = -1;
   DString dstrCurrentCode;
   if ( iPos < 0 ) {
      //Final state, only one element in list.
      dstrCurrentCode = dstrCopyCodeList;
   } else {
      // If an exclude code is found, we will simply return exclude.
      iFound = isCodeAllowed ( dstrCode, dstrCopyCodeList.right ( dstrCopyCodeList.length() - iPos - 1 ) );
      if ( iFound == 0 )
         return 0;
      dstrCurrentCode = dstrCopyCodeList.left ( iPos );
   }   
   int iExcludePos = dstrCurrentCode.find('!');

   dstrCurrentCode.strip();
   if ( iExcludePos >= 0 ) {
      dstrCurrentCode.strip ('!');
      if ( dstrCurrentCode == dstrCode )
         return 0;
      else {
         return iFound;
      }
   } else if ( dstrCurrentCode == ALL_CODE ) {
      return ( iFound < 0 )?1:iFound;
   } else if ( dstrCode == dstrCurrentCode ) {
      return 1;
   } else {
      return iFound;
   }
}

//***************************************************************************************
//***************************************************************************************

bool AmsLmtOverride::isTaxJurisInList( const DString& dstrTaxJuris, const BFDataGroupId& idDataGroup ) 
{
   DString dstrTaxJurisList;
   getField ( ifds::AMSTaxJurisCode, dstrTaxJurisList, idDataGroup );      
   int iResult = isCodeAllowed ( dstrTaxJuris, dstrTaxJurisList );
   // If the Tax Juris code is found on the list
   if ( iResult > 0 )
      return true;
   else
      return false;
}

//***************************************************************************************
//***************************************************************************************

bool AmsLmtOverride::isProvResInList( const DString& dstrProvResid, const BFDataGroupId& idDataGroup ) 
{
   DString dstrProvResidList;
   getField ( ifds::AMSResProvCode, dstrProvResidList, idDataGroup );
   int iResult = isCodeAllowed ( dstrProvResid, dstrProvResidList );
   // If the Tax Juris code is found on the list
   if ( iResult > 0 )
      return true;
   else
      return false;
}

//***************************************************************************************
//***************************************************************************************

bool AmsLmtOverride::isTaxTypeInList( const DString& dstrTaxType, const BFDataGroupId& idDataGroup ) 
{
   DString dstrTaxTypeList;
   getField ( ifds::AMSTaxType, dstrTaxTypeList, idDataGroup );
   int iResult = isCodeAllowed ( dstrTaxType, dstrTaxTypeList );
   // If the Tax Juris code is found on the list
   if ( iResult > 0 )
      return true;
   else
      return false;
}

//***************************************************************************************
//***************************************************************************************

bool AmsLmtOverride::isAcctTypeInList( const DString& dstrAcctType, const BFDataGroupId& idDataGroup ) 
{
   DString dstrAcctTypeList;
   getField ( ifds::AMSAcctType, dstrAcctTypeList, idDataGroup );
   int iResult = isCodeAllowed ( dstrAcctType, dstrAcctTypeList );
   // If the Tax Juris code is found on the list
   if ( iResult > 0 )
      return true;
   else
      return false;
}

//***************************************************************************************
//***************************************************************************************

bool AmsLmtOverride::isAcctDesignationInList( const DString& dstrAcctDesignation, const BFDataGroupId& idDataGroup ) 
{
   DString dstrAcctDesignationList;
   getField ( ifds::AMSAcctDesignation, dstrAcctDesignationList, idDataGroup );
   int iResult = isCodeAllowed ( dstrAcctDesignation, dstrAcctDesignationList );
   // If the Tax Juris code is found on the list
   if ( iResult > 0 )
      return true;
   else
      return false;
}
//***************************************************************************************
//***************************************************************************************

bool AmsLmtOverride::isError( const BFDataGroupId& idDataGroup ) 
{
   DString dstrEWI;
   getField ( ifds::OnLineEWI, dstrEWI, idDataGroup );
   return ( dstrEWI == ERROR_MESSAGE );
}
//***************************************************************************************
//***************************************************************************************
bool AmsLmtOverride::isWarning( const BFDataGroupId& idDataGroup ) 
{
   DString dstrEWI;
   getField ( ifds::OnLineEWI, dstrEWI, idDataGroup );
   return ( dstrEWI == WARNING_MESSAGE );
}

//***************************************************************************************
//***************************************************************************************
void AmsLmtOverride::getFundOverride ( bool& bFundOverride, const BFDataGroupId& idDataGroup )
{
   DString dstrFundOverride;
   getField ( ifds::OverrideFundLevel, dstrFundOverride, idDataGroup );
   bFundOverride = dstrFundOverride == YES;
}

//***************************************************************************************
//***************************************************************************************
void AmsLmtOverride::getDecimalField  ( DString& dstrDecimal, const BFDataGroupId& idDataGroup )
{   
   getField ( ifds::OverrideDecimal, dstrDecimal, idDataGroup );    
}

//***************************************************************************************
//***************************************************************************************
void AmsLmtOverride::getLogicalField (  DString& dstrLogical, const BFDataGroupId& idDataGroup )
{
   getField ( ifds::OverrideLogical, dstrLogical, idDataGroup ); 
}

//***************************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AmsLmtOverride.cpp-arc  $
// 
//    Rev 1.14   Nov 14 2004 14:25:56   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.13   Apr 09 2004 09:53:38   VADEANUM
// PET1005 FN11 - AMS Gaps.
// 
//    Rev 1.12   Mar 09 2004 10:14:44   VADEANUM
// PTS 10026510 - AMS Limitation, Override Fund Limitation, added limitation for Rules 12 and 13 as per Winnie's request.
// 
//    Rev 1.11   Feb 18 2004 09:35:22   VADEANUM
// PTS 10026510 - AMS Limitation, Override Fund Level
// 
//    Rev 1.10   Aug 22 2003 14:51:48   linmay
// modified init()
// 
//    Rev 1.9   Aug 14 2003 13:03:08   HSUCHIN
// Change the fund override from pass by copy to pass by reference.
// 
//    Rev 1.8   Aug 13 2003 10:56:16   linmay
// modified isTaxTypeInList,..
// 
//    Rev 1.7   Aug 13 2003 10:22:32   linmay
// added TaxType .. fields
// 
//    Rev 1.6   Aug 12 2003 10:12:52   HSUCHIN
// bug fix to isCodeAllowed and getDecimalField
// 
//    Rev 1.4   Aug 05 2003 11:27:20   linmay
// fix bug
// 
//    Rev 1.3   Jul 30 2003 14:15:10   linmay
// change view to 261..
// 
//    Rev 1.2   Jul 25 2003 17:05:18   HSUCHIN
// added support for limit override checks such as stop purchase, stop PAC etc. etc.
// 
//    Rev 1.1   Jul 23 2003 10:56:20   linmay
// change to amsruleid
// 
//    Rev 1.0   Jul 23 2003 09:23:10   linmay
// Initial Revision
// 
*/