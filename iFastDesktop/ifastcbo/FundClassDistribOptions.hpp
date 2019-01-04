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
// ^FILE   : FundClassDistribOptions.hpp
// ^AUTHOR : Chatchai Daecha
// ^DATE   : 05/28/07
//
// ^CLASS    : FundClassDistribOptions
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
#include <ifastcbo\FundClassDistribOptionsList.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE FundClassDistribOptions : public MFCanBFCbo, private boost::noncopyable
{
public:
	FundClassDistribOptions (BFAbstractCBO &parent);
	virtual ~FundClassDistribOptions(void);

	SEVERITY init (const BFData& data);
	bool isCashAllowed( const BFDataGroupId &idDataGroup );
	bool isReinvestmentAllowed (const BFDataGroupId &idDataGroup);
	bool isRedistributionAllowed (const BFDataGroupId &idDataGroup);
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FundClassDistribOptions.hpp-arc  $
//
//   Rev 1.1   24 Jul 2007 20:12:54   popescu
//GAP 20 -22 AIM
 * 
 */
