#pragma once
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
//    Copyright 1997 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : MFCANCBOIncludeFirst.hpp
// ^AUTHOR : Chris Purdye
// ^DATE   : 15Dec2000
//
// This file should be included first by MFCANBP cpp files.

#pragma warning( disable : 4503 4786 )  

#define IFASTBP_DLL

#include <srcprag.h>
#include <commonport.h>
#include <conditionmanager.hpp>

namespace CND
{
   extern const I_CHAR *IFASTBP_CONDITION;
}

//for exporting classes
#define IFASTBP_DLL

#include <bfdata\bfdata.hpp>
#include <bfdata\bfdatafieldproperties.hpp>

#include <bfproc\bpglobal.h>
#include <bfproc\abstractprocess.hpp>
#include <bfcbo\bfcbo.hpp>
#include <bfcbo\bfobjiter.hpp>
#include <ifastcbo\dstcworksession.hpp>
#include <ifastcbo\dstcusersession.hpp>
#include <ifastcbo\dstcglobalsession.hpp>
#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastcbo\currencyclass.hpp>
#include <idistring.hpp>
#include <assert.h>

