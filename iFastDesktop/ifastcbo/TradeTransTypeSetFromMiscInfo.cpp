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
//******************************************************************************
//
// ^FILE   : TradeTransTypeSetFromMiscInfo
// ^AUTHOR : Robbins Kuriakose
// ^DATE   : Nov, 2014
//
// ^CLASS    :TradeTransTypeSetFromMiscInfo.cpp
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "TradeTransTypeSetFromMiscInfo.hpp"
#include "mgmtco.hpp"
#include <ifastdataimpl\dse_dstc0254_req.hpp>
#include <ifastdataimpl\dse_dstc0254_vw.hpp>
#include <ifastdataimpl\dse_dstc0254_vwrepeat_record.hpp>   

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest MISC_INFO_TRANSLATION_TABLE; 
}
namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME              = I_("TradeTransTypeSetFromMiscInfo");
}
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId  NetworkID;
}

//******************************************************************************
TradeTransTypeSetFromMiscInfo::TradeTransTypeSetFromMiscInfo(BFAbstractCBO &parent) 
: MFCanBFCbo (parent)
{
   TRACE_CONSTRUCTOR (CLASSNAME , NULL_STRING);
}

//******************************************************************************
TradeTransTypeSetFromMiscInfo::~TradeTransTypeSetFromMiscInfo()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}
//******************************************************************************
SEVERITY TradeTransTypeSetFromMiscInfo::init (const BFData &viewData)
{
   MAKEFRAME2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   attachDataObject (const_cast<BFData&> (viewData), false, true);
   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TradeTransTypeSetFromMiscInfo.cpp-arc  $
 
*/  