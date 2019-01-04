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
// ^FILE   : stdafx.h
// ^AUTHOR :
// ^DATE   :
//
// .

#pragma warning( disable: 4503 ) 
#pragma warning( disable: 4275 )
#pragma warning( disable: 4786 )  

#define NOMINMAX
#include <srcprag.h>
#include <commonport.h>
#include <conditionmanager.hpp>

//for exporting classes
#define IFASTAWD_DLL

namespace CND
{
   extern const I_CHAR *IFASTAWD_CONDITION;
}

#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastcbo\currencyclass.hpp>
#include <configmanager.hpp>
#include <bfcbo\bfobjiter.hpp>
#include <bfcbo\bfsubst.hpp>
#include <bfdbrkr\bfdatabroker.hpp>
#include <ifastdbrkr\dstcrequestor.hpp>
#include <ifastdbrkr\dstcrequest.hpp>
#include <ifastdbrkr\dstchost.hpp>
#include <ifastdbrkr\dstcsecurity.hpp>
#include <assert.h>
#include <iostream>
#include <math.h>
#include <list>
#include <bfcbo\hosttransactioncontainer.hpp>
#include <ifastcbo\hostsubstitutionvalueslist.hpp>
#include <stringfunctions.hpp>
#include <ifastcbo\dstcglobalsession.hpp>
#include <ifastcbo\dstcworksession.hpp>
#include <ifastcbo\dstcusersession.hpp>
#include <bfdata\bfdatafielditer.hpp>

