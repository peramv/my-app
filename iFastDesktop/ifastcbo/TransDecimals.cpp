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
//    ^FILE   : TransDecimals.cpp
//    ^AUTHOR : Amelia Aguila
//    ^DATE   : February 2005
//    Copyright 2004 by International Financial Data Services
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : TransDecimals
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"


#include "TransDecimals.hpp"
#include "TransDecimalslist.hpp"

#include <ifastdataimpl\dse_dstc0330_req.hpp>               // TransDecimals Inquiry
#include <ifastdataimpl\dse_dstc0330_vwrepeat_record.hpp>   // Deduction Inventory Inquiry


// Constants
namespace 
{
   const I_CHAR * CLASSNAME = I_("TransDecimals");
}

//******************************************************************************
TransDecimals::TransDecimals(BFAbstractCBO &parent) 
: MFCanBFCbo(parent)
{
   TRACE_CONSTRUCTOR(CLASSNAME , NULL_STRING);   
}

//******************************************************************************
TransDecimals::~TransDecimals()
{
   TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************
SEVERITY TransDecimals::init( const BFData &viewData )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   attachDataObject (const_cast<BFData&>(viewData), false, true);
   		
   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/TransDecimals.cpp-arc  $
// 
//    Rev 1.0   Mar 03 2005 14:42:24   aguilaam
// Initial revision.
// 
// 
