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
//    Copyright 2000 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : MgmtFeeRebate.cpp
// ^AUTHOR : Serban Popescu   
// ^DATE   : November, 2006
//
// ^CLASS    : MgmtFeeRebate - 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "mgmtfeerebate.hpp"

namespace ifds
{
//attributes grid
   extern CLASS_IMPORT const BFTextFieldId TradeAttributesFields;
   extern CLASS_IMPORT const BFTextFieldId PurchaseAttributes;
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const MGMT_FEE_REBATE;
}


namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME = I_ ("MgmtFeeRebate");
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
    //  Field DD Id,              State Flags,      Group Flags 
    { ifds::PurchaseAttributes,      BFCBO::NONE,             0}, 
};
static const int NUM_FIELDS = sizeof (classFieldInfo) / sizeof (BFCBO::CLASS_FIELD_INFO);
//******************************************************************************
MgmtFeeRebate::MgmtFeeRebate (BFAbstractCBO &parent) : Purchase (parent), Trade (parent)
{
   TRACE_CONSTRUCTOR ( CLASSNAME, 
                       NULL_STRING);
   registerMemberData ( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo,
                        0, NULL);
}


//******************************************************************************
MgmtFeeRebate::~MgmtFeeRebate ()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}     

//******************************************************************************
bool MgmtFeeRebate::supportsAllocations (const BFDataGroupId &idDataGroup)
{
   return false;
}

//******************************************************************************
bool MgmtFeeRebate::supportsFromAllocations (const BFDataGroupId &idDataGroup)
{
   return false;
}

//******************************************************************************
bool MgmtFeeRebate::isSplitCommissionAllowed (const BFDataGroupId &idDataGroup)
{
   return false; 
}

//******************************************************************************
inline bool MgmtFeeRebate::areTaxRatesAllowed (const BFDataGroupId &idDataGroup)
{
   return false;
}

//******************************************************************************
inline bool MgmtFeeRebate::isSettleLocAllowed (const BFDataGroupId &idDataGroup)
{
   return false;
}

//******************************************************************************
inline bool MgmtFeeRebate::isWireSupported (const BFDataGroupId &idDataGroup)
{
	return false;
}

//******************************************************************************
SEVERITY MgmtFeeRebate::doInit (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doInit"));
   setFieldNoValidate ( ifds::TradesTransType, 
                        TRADETYPE::MGMT_FEE_REBATE, 
                        idDataGroup, 
                        false);
//attributes grid,set this as default, just to show something on the screen
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY MgmtFeeRebate::preInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("preInitWithDefaultValues"));
//base class call   
   Purchase::preInitWithDefaultValues (idDataGroup);

   setFieldReadOnly (ifds::OrderType, idDataGroup, true);
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
void MgmtFeeRebate::doInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
   Purchase::doInitWithDefaultValues (idDataGroup);
   setFieldNoValidate ( ifds::OrderType, I_("N"), idDataGroup, false, //direct
                        false, //valid
                        true);  //notify
   setFieldNoValidate ( ifds::WireOrdNum, NULL_STRING, idDataGroup, false,
                        true, //valid
                        true);  //notify observers
}

//******************************************************************************
SEVERITY MgmtFeeRebate::transTypeRelatedChanges (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("transTypeRelatedChanges"));

   DString purchaseAttributeSubstList;
   BFProperties *pBFProperties = getFieldProperties (ifds::PurchaseAttributes, idDataGroup);
   if(pBFProperties)
    {
     pBFProperties->getAllSubstituteValues (purchaseAttributeSubstList);
     purchaseAttributeSubstList = removeItemFromSubtList ( purchaseAttributeSubstList,  
                                                            I_("SourceofFundsChecked"));   
     //attributes grid
     setFieldAllSubstituteValues ( ifds::PurchaseAttributes, 
                                 idDataGroup, 
                                 purchaseAttributeSubstList);
    }
   setFieldAllSubstituteValues ( ifds::TradeAttributesFields, 
                                 idDataGroup, 
                                 ifds::PurchaseAttributes);
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY MgmtFeeRebate::doApplyRelatedChanges ( const BFFieldId &idField, 
                                                const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doApplyRelatedChanges"));
   Purchase::doApplyRelatedChanges (idField, idDataGroup);
   return GETCURRENTHIGHESTSEVERITY ();

}
//******************************************************************************
SEVERITY MgmtFeeRebate::RDRAdviceRelatedChanges (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("RDRAdviceRelatedChanges"));
   
   DString fromAccount, fromFund, fromClass,tradeDate;
   getField (ifds::AccountNum, fromAccount, idDataGroup, false);
   getField (ifds::FromFund, fromFund, idDataGroup, false);
   getField (ifds::FromClass, fromClass, idDataGroup, false);
   getField (ifds::EffectiveDate, tradeDate, idDataGroup, false);
   setRDRAdviceFlag( TRADETYPE::MGMT_FEE_REBATE,
					 fromAccount,
					 fromFund,
					 fromClass,
					 tradeDate,
					 idDataGroup);
   setFieldReadOnly (ifds::RDRAdvice, idDataGroup,true);
   
   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/MgmtFeeRebate.cpp-arc  $
// 
//    Rev 1.2   01 Aug 2007 15:59:04   popescu
// Incident # 956780 - mgfeerebate should always be direct
// 
//    Rev 1.1   Nov 16 2006 11:11:46   popescu
// PET 2252. FN01 - mgmt fee rebate
// 
//    Rev 1.0   Nov 16 2006 10:44:46   popescu
// Initial revision.
// 
*/
