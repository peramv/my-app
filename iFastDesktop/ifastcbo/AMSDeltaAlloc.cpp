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
// ^FILE   : AMSDeltaAlloc.cpp
// ^AUTHOR : Thanisorn Sangkrajang
// ^DATE   : Jan. 10, 2018
//
// ^CLASS    : AMSDeltaAlloc
// ^SUBCLASS :
//
//******************************************************************************
#include "stdafx.h"

#include "AMSDeltaAlloc.hpp"
#include "amsmstrinfo.hpp"
#include "amsmstrlist.hpp"
#include "AMSDeltaAlloc.hpp"
#include "AMSDeltaAllocList.hpp"
#include "mfaccount.hpp"
#include "MgmtCoOptions.hpp"
#include "mgmtco.hpp"

namespace
{
   const I_CHAR * const CLASSNAME = I_("AMSDeltaAlloc");
}

namespace CND
{  // Conditions used
   extern const long ERR_DELTA_MUST_WITHIN_100;
}

namespace ifds
{  
   extern CLASS_IMPORT const BFTextFieldId FundCode;
   extern CLASS_IMPORT const BFTextFieldId ClassCode;
   extern CLASS_IMPORT const BFTextFieldId ToFundNumber;
   extern CLASS_IMPORT const BFDecimalFieldId AllocPercentage;
   extern CLASS_IMPORT const BFDecimalFieldId AMSAllocDelta;
   extern CLASS_IMPORT const BFTextFieldId AMSDeltaDetlUUID;
   extern CLASS_IMPORT const BFDecimalFieldId Version;
   extern CLASS_IMPORT const BFDateFieldId ProcessDate;
   extern CLASS_IMPORT const BFTextFieldId Username;
   extern CLASS_IMPORT const BFDateFieldId ModDate;
   extern CLASS_IMPORT const BFTextFieldId ModUser;
   extern CLASS_IMPORT const BFTextFieldId Status;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,State Flags,Group Flags
   {ifds::FundCode,BFCBO::NONE,0},
   {ifds::ClassCode,BFCBO::NONE,0},
   {ifds::ToFundNumber,BFCBO::NONE,0},
   {ifds::AllocPercentage,BFCBO::NONE,0},
   {ifds::AMSAllocDelta,BFCBO::NONE,0},
   {ifds::AMSDeltaDetlUUID,BFCBO::NONE,0},
   {ifds::Version,BFCBO::NONE,0},
   {ifds::ProcessDate,BFCBO::NONE,0},
   {ifds::Username,BFCBO::NONE,0},
   {ifds::ModDate,BFCBO::NONE,0},
   {ifds::ModUser,BFCBO::NONE,0},
   {ifds::Status,BFCBO::NONE,0},
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
AMSDeltaAlloc::AMSDeltaAlloc( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   registerMemberData(NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL);
}

//******************************************************************************
AMSDeltaAlloc::~AMSDeltaAlloc( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}
//******************************************************************************

SEVERITY AMSDeltaAlloc::initNew( const BFDataGroupId& idDataGroup,
                                 const DString& dstrTrack ,
                                 const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initNew" ) );
   setObjectNew();
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY AMSDeltaAlloc::initExisting(const BFData &data)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("initExisting"));
   attachDataObject(const_cast<BFData&>(data), false, true);
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY AMSDeltaAlloc::doApplyRelatedChanges(const BFFieldId& idField, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

   return(GETCURRENTHIGHESTSEVERITY());

}
//******************************************************************************

SEVERITY AMSDeltaAlloc::doValidateField(const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ));

   //Currently, this screen only have AMSAllocDelta field that can be changed.
   if( idField == ifds::AMSAllocDelta)
   {
	  BigDecimal delta = DSTCommonFunctions::convertToBigDecimal(strValue);
      BigDecimal maxDelta = DSTCommonFunctions::convertToBigDecimal(I_("100"));
      BigDecimal minDelta = DSTCommonFunctions::convertToBigDecimal(I_("-100"));

      if(delta > maxDelta || delta < minDelta)
      {
         ADDCONDITIONFROMFILE(CND::ERR_DELTA_MUST_WITHIN_100);
      }
      else
      {
         DString oldStrValue,newStrValue;
         getField(ifds::AMSAllocDelta,oldStrValue,BF::HOST);
         getField(ifds::AMSAllocDelta,newStrValue,idDataGroup);

         BigDecimal oldValue = DSTCommonFunctions::convertToBigDecimal(oldStrValue);
         BigDecimal newValue = DSTCommonFunctions::convertToBigDecimal(newStrValue);

         if(oldValue != newValue)
            setFieldNoValidate(ifds::Status,I_("M"),idDataGroup);
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}