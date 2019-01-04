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
//    Copyright 1999 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : FundClassDistribOptionsList.hpp
// ^AUTHOR : Chatchai Daecha
// ^DATE   : 06/04/07
//
// ^CLASS    : FundClassDistribOptionsList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

class FundClassDistribOptions;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE FundClassDistribOptionsList : public MFCanBFCbo, private boost::noncopyable
{
public:
	FundClassDistribOptionsList( BFAbstractCBO &parent );
	virtual ~FundClassDistribOptionsList(void);

	void getStrKey( DString &strKey, const BFData *data = NULL );

	SEVERITY init( const DString &strDistribType,
		           const DString &strFundCode,
		           const DString &strClassCode
		);

	SEVERITY getFundClassDistribOptions( const DString &strDistribType,
										 const BFDataGroupId& idDataGroup,
										 FundClassDistribOptions *&fundClassDistribOptions);


protected:
	SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
private:

};
