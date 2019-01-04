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
//    Copyright 2007 by International Financial Data Services
//
//*****************************************************************************
//
//    ^FILE   : Frequency.cpp
//    ^AUTHOR : Monica Porteanu
//    ^DATE   : June 2007
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : Frequency
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"


#include "Frequency.hpp"
#include "Frequencylist.hpp"

#include <ifastdataimpl\dse_dstc0382_req.hpp>               // Frequency Inquiry
#include <ifastdataimpl\dse_dstc0382_vwrepeat_record.hpp>   // Frequency Inquiry

// Constants
namespace 
{
   const I_CHAR * CLASSNAME = I_("Frequency");
}

//******************************************************************************
Frequency::Frequency(BFAbstractCBO &parent) 
: MFCanBFCbo(parent)
{
   TRACE_CONSTRUCTOR(CLASSNAME , NULL_STRING);   
}

//******************************************************************************
Frequency::~Frequency()
{
   TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************
SEVERITY Frequency::init( const BFData &viewData )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   attachDataObject (const_cast<BFData&>(viewData), false, true);
   		
   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/Frequency.cpp-arc  $
// 
//    Rev 1.1   Jun 22 2007 14:20:38   porteanm
// PET 2360 FN02 - AMS - work in progress.
// 
//    Rev 1.0   Jun 20 2007 11:39:54   porteanm
// Initial revision.
// 
// 

