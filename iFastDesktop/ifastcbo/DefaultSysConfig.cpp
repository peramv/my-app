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
// ^FILE   : DefaultSysConfig.hpp
// ^AUTHOR : Robbins Kuriakose
// ^DATE   : 26/08/13
//
// ^CLASS    : DefaultSysConfig
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :	Used to get the defualt values for multiple keys
//
//******************************************************************************

#include "stdafx.h"
#include "DefaultSysConfig.hpp"
#include "mgmtco.hpp"
#include <ifastdataimpl\dse_dstc0454_req.hpp>
#include <ifastdataimpl\dse_dstc0454_vw.hpp>
#include <ifastdataimpl\dse_dstc0454_vwrepeat_record.hpp>    

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME              = I_("DefaultSysConfig");
}
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FldName;
   extern CLASS_IMPORT const BFTextFieldId DefValue;
}
//******************************************************************************
DefaultSysConfig::DefaultSysConfig (BFAbstractCBO &parent) 
: MFCanBFCbo (parent)
{
   TRACE_CONSTRUCTOR (CLASSNAME , NULL_STRING);
}

//******************************************************************************
DefaultSysConfig::~DefaultSysConfig()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}
//******************************************************************************
SEVERITY DefaultSysConfig::init (const BFData &viewData)
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