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
//    Copyright 2005 by International Financial Data Services
//
//*****************************************************************************
//
//    ^FILE   : Province.cpp
//    ^AUTHOR : Monica Porteanu
//    ^DATE   : February 2005
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : Province
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"


#include "Province.hpp"
#include "Provincelist.hpp"

#include <ifastdataimpl\dse_dstc0252_req.hpp>               // Province Inquiry
#include <ifastdataimpl\dse_dstc0252_vwrepeat_record.hpp>   // Province Inquiry

// Constants
namespace 
{
   const I_CHAR * CLASSNAME = I_("Province");
}

//******************************************************************************
Province::Province(BFAbstractCBO &parent) 
: MFCanBFCbo(parent)
{
   TRACE_CONSTRUCTOR(CLASSNAME , NULL_STRING);   
}

//******************************************************************************
Province::~Province()
{
   TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************
SEVERITY Province::init( const BFData &viewData )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   attachDataObject (const_cast<BFData&>(viewData), false, true);
   		
   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/Province.cpp-arc  $
// 
//    Rev 1.1   Mar 02 2005 16:39:54   porteanm
// PET 1171 FN01 - EUSD Entity Address Update support.
// 
//    Rev 1.0   Feb 22 2005 14:29:40   porteanm
// Initial revision.
// 

