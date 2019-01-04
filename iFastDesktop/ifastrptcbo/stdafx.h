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
// This file should be included first by MFCANCBO cpp files.

#pragma warning( disable: 4503 ) 
#pragma warning( disable: 4275 )
#pragma warning( disable: 4786 )  

#include <srcprag.h>
#include <commonport.h>
#include <conditionmanager.hpp>

#define Y   I_( "Y" )

//for exporting classes
#define IFASTRPTCBO_DLL

namespace CND
{
   extern CLASS_IMPORT const I_CHAR *IFASTCBO_CONDITION;
}

#include <criticalsection.hpp>
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
#include <mutexsemaphore.hpp>
#include <stringfunctions.hpp>
#include <ifastcbo\dstcglobalsession.hpp>
#include <ifastcbo\dstcworksession.hpp>
#include <ifastcbo\dstcusersession.hpp>
#include <bfdata\bfdatafielditer.hpp>

