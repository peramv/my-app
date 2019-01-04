
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
//    Copyright 2003 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : FundClassRules.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : January 8, 2003
//
// ^CLASS    : FundClassRules
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "FundClassRules.hpp"
#include "fundmasterlist.hpp"
#include "funddetaillist.hpp"
#include "mgmtco.hpp"

namespace
{
   const I_CHAR * const CLASSNAME = I_( "FundClassRules" );
}

namespace CND
{  // Conditions used
   extern const long ERR_INVALID_FUND_CLASS_CODES;
   extern const long ERR_FUND_CLASS_NOT_EFFECTIVE;
   extern const long ERR_INVALID_FUND_NUMBER;
   extern const long ERR_FUND_NOT_EFFECTIVE;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FundNumber;
   extern CLASS_IMPORT const BFTextFieldId FundCode;
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFTextFieldId ClassCode;
}

//****************************************************************************
FundClassRules::FundClassRules( BFAbstractCBO &parent )
: MFCanBFCbo(parent)
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
}

//****************************************************************************
FundClassRules::~FundClassRules()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}     

//****************************************************************************
SEVERITY FundClassRules::init( 
   const BFFieldId& fundNumberId /*= ifds::NullFieldId*/ ,
   const BFFieldId& fundCodeId /*= ifds::NullFieldId*/, 
   const BFFieldId& classCodeId /*= ifds::NullFieldId*/,
   const BFFieldId& effectiveDateId /*= ifds::NullFieldId*/)
{
   MAKEFRAME2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );
   if (fundNumberId == ifds::NullFieldId)
   {
      FundNumber = ifds::FundNumber;
   }
   else 
   {
      FundNumber = fundNumberId;
   }
   if (fundCodeId == ifds::NullFieldId)
   {
      FundCode = ifds::FundCode;
   }
   else 
   {
      FundCode = fundCodeId;
   }
   if (classCodeId == ifds::NullFieldId)
   {
      ClassCode = ifds::ClassCode;
   }
   else 
   {
      ClassCode = classCodeId;
   }
   if (effectiveDateId == ifds::NullFieldId)
   {
      EffectiveDate = ifds::EffectiveDate;
   }
   else 
   {
      EffectiveDate = effectiveDateId;
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************
SEVERITY FundClassRules::validateFundCode(const BFDataGroupId& idDataGroup )
{
 	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateFundCode") );
	DString dstrFundCode,dstrClassCode,dstrEffectiveDate;
   FundMasterList* pFundMasterList;

   getParent()->getField(FundCode, dstrFundCode, idDataGroup, false);
	dstrFundCode.strip().upperCase();
   getParent()->getField(ClassCode,dstrClassCode,idDataGroup,false);
	dstrClassCode.strip().upperCase();
   getParent()->getField(EffectiveDate, dstrEffectiveDate, idDataGroup, false);
	dstrEffectiveDate.strip().upperCase();
   getMgmtCo().getFundMasterList( pFundMasterList );
   if( dstrFundCode == I_( "CASH" ) )
   {
      ADDCONDITIONFROMFILE( CND::ERR_INVALID_FUND_CLASS_CODES );
      return(GETCURRENTHIGHESTSEVERITY());  
   }
   if( pFundMasterList != NULL && dstrFundCode != NULL_STRING )
   {
      if( pFundMasterList->IsFundExist( dstrFundCode, idDataGroup ) == false )
      {
         ADDCONDITIONFROMFILE( CND::ERR_INVALID_FUND_CLASS_CODES );
      }
      else
      {
         if( pFundMasterList->IsFundValidAtDate ( dstrFundCode, dstrEffectiveDate, 
				idDataGroup) == false )
         {
            DString idiStr;
            addIDITagValue( idiStr, I_( "FUNDNAME" ),  dstrFundCode );
            ADDCONDITIONFROMFILEIDI( CND::ERR_FUND_NOT_EFFECTIVE, idiStr );
         }
      }
	}	
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY FundClassRules::validateClassCode(const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateClassCode") );
	DString dstrFundCode,dstrClassCode,dstrEffectiveDate;
   FundDetail *pFundDetail = NULL;
   FundDetailList * pFundDetailList = NULL;

   getParent()->getField(FundCode, dstrFundCode, idDataGroup,false);
	dstrFundCode.strip().upperCase();
	getParent()->getField(ClassCode,dstrClassCode, idDataGroup,false);
	dstrClassCode.strip().upperCase();
	getParent()->getField(EffectiveDate, dstrEffectiveDate, idDataGroup,false);
	dstrEffectiveDate.strip().upperCase();
   SEVERITY sev = getMgmtCo().getFundDetailList(pFundDetailList); // Not using sev at the moment
   if ( pFundDetailList && !dstrFundCode.empty() && !dstrClassCode.empty() ) 
   {
      if( !pFundDetailList->IsFundClassExist( dstrFundCode, dstrClassCode, BF::HOST ) )
      {
         ADDCONDITIONFROMFILE( CND::ERR_INVALID_FUND_CLASS_CODES );
      }
      else
      {
         //if fundcode is not effective then do not need to validate classCode
		 SEVERITY sev = NO_CONDITION;
		 sev = validateFundCode( idDataGroup );
		 if(sev <= WARNING)
		 {
			 if( pFundDetailList->IsFundValidAtDate( dstrFundCode, dstrClassCode, 
				dstrEffectiveDate, idDataGroup) == false )
			 {
				DString idiStr;
				addIDITagValue( idiStr, I_( "FUNDNAME" ),  dstrFundCode );
				addIDITagValue( idiStr, I_( "CLASSNAME" ), dstrClassCode );
				ADDCONDITIONFROMFILEIDI( CND::ERR_FUND_CLASS_NOT_EFFECTIVE, idiStr );
			 }
		 }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

/**
 * FundClass field should be set as a cross edit field, in order to call this method
 **/
//**********************************************************************************
SEVERITY FundClassRules::validateFundClass( const BFDataGroupId& idDataGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFundClass" ) );
   FundDetail *pFundDetail = NULL;
   DString dstrClassCode, dstrFundCode;

   getParent()->getField(FundCode, dstrFundCode, idDataGroup, false);
   getParent()->getField(ClassCode, dstrClassCode, idDataGroup, false);
   getFundDetail(dstrFundCode.strip().upperCase(), dstrClassCode.strip().upperCase(), pFundDetail);
   if(!pFundDetail)
      ADDCONDITIONFROMFILE( CND::ERR_INVALID_FUND_CLASS_CODES );

   return(GETCURRENTHIGHESTSEVERITY());
}

//**********************************************************************************
SEVERITY FundClassRules::validateFundNumber(const BFDataGroupId& idDataGroup)
{
	MAKEFRAME2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateFundNumber") );
   DString dstrFundNumber;

   getParent()->getField(FundNumber,dstrFundNumber,idDataGroup,false);
	dstrFundNumber.strip().upperCase();
   if(dstrFundNumber.strip() != NULL_STRING)
   {
      DString dstrFundCode, dstrClassCode;

      if(!getWorkSession().GetFundClassCode(dstrFundNumber, dstrFundCode, dstrClassCode))
         ADDCONDITIONFROMFILE( CND::ERR_INVALID_FUND_NUMBER);
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//************************************************************************************
SEVERITY FundClassRules::getFundDetail(const DString& strFundCode, 
   const DString& strClassCode, FundDetail *&pFundDetail)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getFundDetail" ) );

   pFundDetail = NULL;
   FundDetailList * pFundDetailList = NULL;

   getMgmtCo().getFundDetailList(pFundDetailList);

   if(pFundDetailList)
      pFundDetailList->getFundDetail(strFundCode, strClassCode, BF::HOST, pFundDetail);

   return(GETCURRENTHIGHESTSEVERITY());
}

//************************************************************************************
void FundClassRules::setFundClassCode(const BFDataGroupId& idDataGroup)
{
}

//**************************************************************************************
void FundClassRules::setFundNumber(const BFDataGroupId& idDataGroup)
{
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FundClassRules.cpp-arc  $
// 
//    Rev 1.8   Nov 29 2004 13:21:42   hernando
// PET1117 - Tuning Project - Revised use of FundDetailList.
// 
//    Rev 1.7   Nov 14 2004 14:41:46   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.6   Apr 12 2003 15:14:32   FENGYONG
// When fund is not effective then don't need to check if class is effective
// 
//    Rev 1.5   Mar 21 2003 18:10:46   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.4   Jan 27 2003 10:52:38   popescu
// Fixed an initialization issue
// 
//    Rev 1.3   Jan 21 2003 10:18:06   popescu
// Fixed some compiling issues related to FeePram Base class
// 
//    Rev 1.2   Jan 20 2003 15:43:50   popescu
// Checked in for unit testing the ProtectedFundSetup feature
// 
//    Rev 1.1   Jan 16 2003 15:33:56   YINGBAOL
// change init
// 
//    Rev 1.0   Jan 09 2003 10:05:18   YINGBAOL
// Initial Revision
//
 */