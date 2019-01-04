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
//    Copyright 1999 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : NetworkConfigDetail.cpp
// ^AUTHOR : Robbins Kuriakose
// ^DATE   : 04 April 2014
//
// ^CLASS    : NetworkConfigDetailList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :	Used to get the Network Config Details 
//
//******************************************************************************
#include "stdafx.h"
#include "NetworkConfigDetail.hpp"
#include "mgmtco.hpp"
#include <ifastdataimpl\dse_dstc0461_req.hpp>
#include <ifastdataimpl\dse_dstc0461_vw.hpp>
#include <ifastdataimpl\dse_dstc0461_vwrepeat_record.hpp>   
namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest NETWORK_CONFIG_DETAIL; 
}
namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME              = I_("NetworkConfigDetail");
}
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId  NetworkID;
}

//******************************************************************************
NetworkConfigDetail::NetworkConfigDetail(BFAbstractCBO &parent) 
: MFCanBFCbo (parent)
{
   TRACE_CONSTRUCTOR (CLASSNAME , NULL_STRING);
}

//******************************************************************************
NetworkConfigDetail::~NetworkConfigDetail()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}
//******************************************************************************
SEVERITY NetworkConfigDetail::init (const BFData &viewData)
{
   MAKEFRAME2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   attachDataObject (const_cast<BFData&> (viewData), false, true);
   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DefaultSysConfig.cpp-arc  $	 

*/