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
// ^FILE   : TradeVerificationError.cpp
// ^AUTHOR : Robbins Kuriakose
// ^DATE   : Aug-2014
//
// ^CLASS    : TradeVerificationError
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :	Used to get the defualt values for multiple keys
//
//******************************************************************************

#include "stdafx.h"
#include "TradeVerificationError.hpp"
#include "mgmtco.hpp"
#include <dataimpl\dse_dstc0463_vw.hpp>
#include <dataimpl\dse_dstc0463_vwrepeat_record.hpp> 

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME              = I_("TradeVerificationError");
}
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FldName;
   extern CLASS_IMPORT const BFTextFieldId DefValue;
}
//******************************************************************************
TradeVerificationError::TradeVerificationError (BFAbstractCBO &parent) 
: MFCanBFCbo (parent)
{
   TRACE_CONSTRUCTOR (CLASSNAME , NULL_STRING);
}

//******************************************************************************
TradeVerificationError::~TradeVerificationError()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}
//******************************************************************************
SEVERITY TradeVerificationError::init (const BFData &viewData)
{
   MAKEFRAME2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));
   attachDataObject (const_cast<BFData&> (viewData), false, true);
   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TradeVerificationError.cpp-arc  $  

*/