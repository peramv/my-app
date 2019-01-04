//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2004 by International Financial Data Services
//
//*****************************************************************************
//
//    ^FILE   : InvDetlDeduction.cpp
//    ^AUTHOR : Amelia Aguila
//    ^DATE   : January 2005
//    Copyright 2004 by International Financial Data Services
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : InvDetlDeduction
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"


#include "InvDetlDeduction.hpp"
#include "InvDetlDeductionlist.hpp"

#include <ifastdataimpl\dse_dstc0329_req.hpp>               // Deduction Inventory Inquiry
#include <ifastdataimpl\dse_dstc0329_vwrepeat_record.hpp>   // Deduction Inventory Inquiry


// Constants
namespace 
{
   const I_CHAR * CLASSNAME = I_("InvDetlDeduction");
}

//******************************************************************************
InvDetlDeduction::InvDetlDeduction(BFAbstractCBO &parent) 
: MFCanBFCbo(parent)
{
   TRACE_CONSTRUCTOR(CLASSNAME , NULL_STRING);   
}

//******************************************************************************
InvDetlDeduction::~InvDetlDeduction()
{
   TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************
SEVERITY InvDetlDeduction::init( const BFData &viewData )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   attachDataObject (const_cast<BFData&>(viewData), false, true);
   		
   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/InvDetlDeduction.cpp-arc  $
// 
//    Rev 1.1   Feb 17 2005 13:15:22   aguilaam
// PET1198_FN01: LSIF Reason Code enhancement. 
// 
//    Rev 1.0   Jan 28 2005 13:52:24   aguilaam
// Initial revision.
// 
