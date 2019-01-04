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
//    Copyright 1999 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : DefaultRegulatoryStandard.hpp
// ^AUTHOR : Aurkarn Mongkonrat
// ^DATE   : 01 August 2013
//
// ^CLASS    : DefaultRegulatoryStandard
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
#include <srcprag.h>

class BFData;

class MgmtCoOptions;
class MFAccount;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
#define IFASTCBO_LINKAGE CLASS_EXPORT
#else
#define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE DefaultRegulatoryStandard : public MFCanBFCbo, private boost::noncopyable
{
public:
	DefaultRegulatoryStandard (BFAbstractCBO &parent);
	virtual ~DefaultRegulatoryStandard();
	SEVERITY DefaultRegulatoryStandard::init(const BFDataGroupId& idDataGroup,
										  const DString& dstrAcctType,
										  const DString& dstrTaxType,
										  const DString& dstrAcctDesignation,
										  const DString& dstrTaxJurisCode,
										  const DString& dstrTypeOfInvestor,
										  const DString& dstrInvestingOnBehalf,
										  const DString& dstrTrack = I_("N"), 
										  const DString& dstrPageName = NULL_STRING);

protected:

private:

};