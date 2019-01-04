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
//    Copyright 2018 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : IntraDayPricing.h
// ^AUTHOR : 
// ^DATE   : 03 July 2018
//
// ^CLASS    : IntraDayPricing
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
#define IFASTCBO_LINKAGE CLASS_EXPORT
#else
#define IFASTCBO_LINKAGE CLASS_IMPORT
#endif


class IFASTCBO_LINKAGE IntraDayPricing : public MFCanBFCbo, private boost::noncopyable
{

public:
	IntraDayPricing(BFAbstractCBO &parent);
	virtual ~IntraDayPricing();

	   SEVERITY init(  
					const DString &strRunMode,
					const DString &strFromFund,
					const DString &strFromClass, 
					const DString &strToFund, 
					const DString &strToClass, 
					const DString &strDealDate,
					const DString &strDealTime, 
					const DString &strTradeFromDate,
					const DString &strTradeInDate,				  
					const DString &strTransType,
					const DString &strCallingType = NULL_STRING,
					const DString &dstrTrack = I_("N"), 
					const DString &dstrPageName = NULL_STRING
				  );  

	
protected:

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:     $*/

//  Rev 1.0   July 03 2018 15:24:04   Amit k Mallick
//	Initial revision.