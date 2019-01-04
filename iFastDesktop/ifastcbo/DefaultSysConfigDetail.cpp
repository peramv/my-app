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
// ^FILE   : DefaultSysConfigDetail.hpp
// ^AUTHOR : Robbins Kuriakose
// ^DATE   : 26/08/13
//
// ^CLASS    : DefaultSysConfigDetail
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :	Used to get the defualt values for multiple keys
//
//******************************************************************************


#include "stdafx.h"
#include "DefaultSysConfigDetail.hpp"
#include "mgmtco.hpp"
#include <ifastdataimpl\dse_dstc0455_vw.hpp>
#include <ifastdataimpl\dse_dstc0455_req.hpp>
#include <ifastdataimpl\dse_dstc0455_vwrepeat_record.hpp> 

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME              = I_("DefaultSysConfigDetail");
}
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FldName;
   extern CLASS_IMPORT const BFTextFieldId DefValue;
}
//******************************************************************************
DefaultSysConfigDetail::DefaultSysConfigDetail (BFAbstractCBO &parent) 
: MFCanBFCbo (parent)
{
   TRACE_CONSTRUCTOR (CLASSNAME , NULL_STRING);
}

//******************************************************************************
DefaultSysConfigDetail::~DefaultSysConfigDetail()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}
//******************************************************************************
SEVERITY DefaultSysConfigDetail::init (const BFData &viewData)
{
   MAKEFRAME2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   attachDataObject (const_cast<BFData&> (viewData), false, true);
   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DefaultSysConfigDetail.cpp-arc  $  

*/