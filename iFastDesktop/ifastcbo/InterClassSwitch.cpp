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
// ^FILE   : InterClassSwitch.cpp
// ^AUTHOR : 
// ^DATE   : June 2016
// ^CLASS  : InterClassSwitch
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : This CBO is EXACTLY like Exchange excepts its INDC is 45.
//                      Any validations or enhancements should apply to this CBO as well.
//
//******************************************************************************

#include "stdafx.h"
#include "InterClassSwitch.hpp"

namespace
{
    const I_CHAR * const CLASSNAME = I_ ("InterClassSwitch"); 
}

namespace ifds
{
    extern CLASS_IMPORT const BFTextFieldId InterClassSwitch;
}

namespace TRADETYPE
{
    extern CLASS_IMPORT I_CHAR * const INTER_CLASS_SWITCH;
}

//******************************************************************************
InterClassSwitch::InterClassSwitch(BFAbstractCBO &parent) 
    :Exchange(parent)
{
    TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING );
}
//******************************************************************************
InterClassSwitch::~InterClassSwitch()
{
    TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
SEVERITY InterClassSwitch::doInit(const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doInit"));

    Exchange::doInit(idDataGroup);
    setFieldNoValidate(ifds::TradesTransType, 
                       TRADETYPE::INTER_CLASS_SWITCH, 
                       idDataGroup, 
                       false);

    return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY InterClassSwitch::doInit(const BFData &data)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doInit"));

   Exchange::doInit(data);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void InterClassSwitch::doInitWithDefaultValues(const BFDataGroupId &idDataGroup)
{
   Exchange::doInitWithDefaultValues(idDataGroup);

   setFieldNoValidate(ifds::OrderSource, I_("F"), idDataGroup, false, false, false);
}