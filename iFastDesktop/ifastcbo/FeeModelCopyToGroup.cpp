//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial 
//    Data Services, Ltd., are proprietary in nature and as such
//    are confidential. Any unauthorized use or disclosure of such
//    information may result in civil liabilities.
//
//    Copyright 2015 by International Financial Data Services, Ltd.
//
//
//******************************************************************************
//
// ^FILE   : FeeModelCopyToGroup.cpp
// ^AUTHOR : 
// ^DATE   : 9 July 2015
//
// ^CLASS    : FeeModelCopyToGroup
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "FeeModelCopyToGroup.hpp"

#include "acctgrpconfiglist.hpp"
#include "dstcommonfunction.hpp"
#include "feemodelcopytogrouplist.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"

namespace
{
   const I_CHAR * const CLASSNAME   = I_("FeeModelCopyToGroup");
   const I_CHAR * const YES         = I_("Y"); 
   const I_CHAR * const NO          = I_("N");
}

namespace ifds
{
   //	extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFTextFieldId FeeModelSrc;
   extern CLASS_IMPORT const BFTextFieldId GroupDest;
   extern CLASS_IMPORT const BFTextFieldId FeeModelCode;
   extern CLASS_IMPORT const BFTextFieldId FeeModelDesc;
   extern CLASS_IMPORT const BFNumericFieldId FeeModelRecid;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
   //  Field DD Id,               State Flags,    Group Flags 
   { ifds::FeeModelSrc,           BFCBO::NONE,        0 }, 
   { ifds::GroupDest,             BFCBO::REQUIRED,    0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//****************************************************************************
FeeModelCopyToGroup::FeeModelCopyToGroup (BFAbstractCBO &parent) :
   MFCanBFCbo (parent)
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );

   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );

}

//****************************************************************************
FeeModelCopyToGroup::~FeeModelCopyToGroup()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//****************************************************************************
SEVERITY FeeModelCopyToGroup::init (const BFData &data)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   attachDataObject( const_cast<BFData&>(data), false, true );

   return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************
SEVERITY FeeModelCopyToGroup::initNew (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("initNew"));

   setObjectNew();
   initFieldSubstitutionList(idDataGroup);

   DString _feeModelRecId;
   getParent()->getField(ifds::FeeModelRecid,_feeModelRecId,idDataGroup,false);
   setFieldNoValidate(ifds::FeeModelSrc,_feeModelRecId,idDataGroup,false,true,true);

   return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************
void FeeModelCopyToGroup::initFieldSubstitutionList(const BFDataGroupId& idDataGroup)
{
   DString _feeModelCode, _feeModelRecId, _feeModelDesc;
   getParent()->getField(ifds::FeeModelCode,_feeModelCode,idDataGroup,false);
   getParent()->getField(ifds::FeeModelRecid,_feeModelRecId,idDataGroup,false);
   getParent()->getField(ifds::FeeModelDesc,_feeModelDesc,idDataGroup,false);

   _feeModelCode += I_(" " );
   _feeModelCode += _feeModelRecId;

   DString substitution = _feeModelRecId, blanksubstitution = I_(" = ;");
   substitution += I_("=");
   substitution += _feeModelDesc;
   substitution += I_(";");
   setFieldAllSubstituteValues (ifds::FeeModelSrc, idDataGroup, substitution);
   substitution = NULL_STRING;

   AcctGrpConfigList *pAcctGrpConfigList = nullptr;
   if (getWorkSession().getAcctGrpConfigList(pAcctGrpConfigList,idDataGroup) <= WARNING &&
      pAcctGrpConfigList){
      // it would be built from result of view 468
      pAcctGrpConfigList->buildListOfCopyableGroup(substitution,idDataGroup);
      blanksubstitution += substitution;
      substitution = blanksubstitution;
   }

   setFieldAllSubstituteValues (ifds::GroupDest, idDataGroup, substitution);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/FeeModelCopyToGroup.cpp-arc  $
// 