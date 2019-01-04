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
//    Copyright 1999 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : NoFee.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : November 2004
//
// ^CLASS    : NoFee
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "nofee.hpp"

#include "trade.hpp"

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME  = I_("NoFee");
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFIntegerFieldId TransFeeCode;
   extern CLASS_IMPORT const BFTextFieldId FeeCharge;
}

namespace CND
{  // Conditions used
}

namespace FEES
{
   extern const I_CHAR * NO_FEE;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
                             //  Field DD Id,      State Flags,      Group Flags 
   { ifds::FeeRate,          BFCBO::NONE,      0}, 
   { ifds::FeeCharge,        BFCBO::NONE,      0}, 
   { ifds::OrigFeeRate,      BFCBO::NONE,      0}, 
};

static const int NUM_FIELDS = sizeof(classFieldInfo) / sizeof(BFCBO::CLASS_FIELD_INFO);

//******************************************************************************
NoFee::NoFee (BFAbstractCBO &parent) : TransFee (parent, FEES::NO_FEE)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
   registerMemberData (NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL);
}

//******************************************************************************
NoFee::~NoFee()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}


//******************************************************************************
bool NoFee::isSystemApplicable (const BFDataGroupId &idDataGroup)
{
//does not apply, allways
   return false;
}

//******************************************************************************
bool NoFee::isContextApplicable (const BFDataGroupId &idDataGroup)
{
//does not apply, allways
   return false;
}

//******************************************************************************
bool NoFee::hasContextChanged (const BFDataGroupId &idDataGroup)
{
   return false;
}

//******************************************************************************
bool NoFee::isChargeFee (const BFDataGroupId &idDataGroup)
{
   return false;
}

//******************************************************************************
SEVERITY NoFee::setFeeDefault (const BFDataGroupId &idDataGroup)
{
   return NO_CONDITION;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/NoFee.cpp-arc  $
// 
//    Rev 1.3   Nov 17 2004 16:15:18   popescu
// PET 1117/06, Trade processing fees
// 
//    Rev 1.2   Nov 15 2004 16:23:16   popescu
// PET 1117/06, more synch to .NET changes
// 
//    Rev 1.0   Nov 10 2004 09:31:04   popescu
// Initial revision.
// 
//    Rev 1.0   Nov 06 2004 00:35:04   popescu
// Initial revision.
// 
//    Rev 1.0   Nov 04 2004 11:03:16   popescu
// Initial revision.
// 
 */