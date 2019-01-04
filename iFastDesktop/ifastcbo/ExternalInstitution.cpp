//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by IFDS Co., Ltd.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2016 by IFDS Co., Ltd.
//
//
//******************************************************************************
//
// ^FILE   : ExternalInstitution.cpp
// ^AUTHOR : 
// ^DATE   : Mar, 2016
//
// ^CLASS    : ExternalInstitution
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "ExternalInstitution.hpp"
#include "mgmtco.hpp"

namespace DSTC_REQUEST
{
}

namespace ifds
{
    extern CLASS_IMPORT const BFTextFieldId CompanyName;
    extern CLASS_IMPORT const BFTextFieldId CompanyCode;
}

namespace CND
{  

}

namespace IFASTERR
{
   
}

namespace
{
    const I_CHAR * const CLASSNAME                     = I_("ExternalInstitution");
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,              State Flags,            Group Flags 
    {ifds::CompanyCode,       BFCBO::NOT_ON_HOST,        0},
    {ifds::CompanyName,       BFCBO::NOT_ON_HOST,        0},
};

static const int NUM_FIELDS = sizeof (classFieldInfo) / sizeof (BFCBO::CLASS_FIELD_INFO);

//******************************************************************************
ExternalInstitution::ExternalInstitution(BFAbstractCBO &parent)
:MFCanBFCbo (parent)
{
    TRACE_CONSTRUCTOR(CLASSNAME , NULL_STRING);
    registerMemberData(NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL);
}

//******************************************************************************
ExternalInstitution::~ExternalInstitution()
{
    TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************
SEVERITY ExternalInstitution::init(const BFData& data)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

    //attachDataObject(const_cast<BFData&>(data), false, true);
    DString strCompanyCode, strCompanyDesc;
    data.getElementValue(ifds::CompanyCode,strCompanyCode);
    data.getElementValue(ifds::CompanyName,strCompanyDesc);
    strCompanyCode.strip().upperCase();
    strCompanyDesc.strip();
    setFieldNoValidate (ifds::CompanyCode, strCompanyCode, BF::HOST, false);   
    setFieldNoValidate (ifds::CompanyName, strCompanyDesc, BF::HOST, false);   

    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/ExternalInstitution.cpp-arc  $
// 
