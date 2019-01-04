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
// ^FILE   : FeeModelCopyToGroupList.cpp
// ^AUTHOR :
// ^DATE   : 9 July 2015
//
// ^CLASS    : FeeModelCopyToGroupList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "FeeModelCopyToGroupList.hpp"
#include "FeeModelCopyToGroup.hpp"

namespace
{
   const I_CHAR * const CLASSNAME = I_("FeeModelCopyToGroupList");
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FeeModelCopyToGroupHeading;
   extern CLASS_IMPORT const BFTextFieldId FeeModelCode;
   extern CLASS_IMPORT const BFTextFieldId FeeModelDesc;
   extern CLASS_IMPORT const BFNumericFieldId FeeModelRecid;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
   //  Field DD Id,                       State Flags,               Group Flags 
   {ifds::FeeModelCopyToGroupHeading,     BFCBO::CALCULATED_FIELD,      0 }, 
   {ifds::FeeModelCode,                   BFCBO::CALCULATED_FIELD,      0 }, 
   {ifds::FeeModelRecid,                  BFCBO::CALCULATED_FIELD,      0 }, 
   {ifds::FeeModelDesc,                   BFCBO::CALCULATED_FIELD,      0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
FeeModelCopyToGroupList::FeeModelCopyToGroupList(BFAbstractCBO &parent)
   : MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );

   setObjectAsList( );
}

//******************************************************************************
FeeModelCopyToGroupList::~FeeModelCopyToGroupList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY FeeModelCopyToGroupList::init(const DString &dstrTrack, 
                                       const DString &dstrPageName)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   setObjectNew();

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY FeeModelCopyToGroupList::addChildRecord(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("addNewAllocation"));

   FeeModelCopyToGroup *pFeeModelCopyToGroup = NULL;
   DString strKeyNew;
   getStrKeyForNewItem( strKeyNew );
   BFObjectKey objKey (strKeyNew, idDataGroup);
   pFeeModelCopyToGroup = dynamic_cast <FeeModelCopyToGroup*> (getNewListItem (objKey));

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY FeeModelCopyToGroupList::doCreateNewObject(BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

   FeeModelCopyToGroup *pFeeModelCopyToGroup = new FeeModelCopyToGroup(*this);

   pFeeModelCopyToGroup->initNew(idDataGroup);
   pBase = pFeeModelCopyToGroup;

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/FeeModelCopyToGroupList.cpp-arc  $
// 