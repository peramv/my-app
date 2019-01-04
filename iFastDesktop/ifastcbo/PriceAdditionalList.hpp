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
//    Copyright 2000 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : PriceAdditionalList.hpp
// ^AUTHOR : 
// ^DATE   : 03 May 2017
//
// ^CLASS    : PriceAdditionalList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

#include <list>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

using namespace std;

class IFASTCBO_LINKAGE PriceAdditionalList : public MFCanBFCbo, private boost::noncopyable
{
public:
	PriceAdditionalList(BFAbstractCBO &parent);
	virtual ~PriceAdditionalList();

    SEVERITY init(const DString &tradeDate, 
                  const DString &fundCode, 
                  const DString &classCode, 
                  list<map<DString, DString>> &priceList, 
                  const BFDataGroupId &idDataGroup);

protected:
    virtual SEVERITY doCreateNewObject(BFCBO *&pObjOut, DString &strKey, const BFDataGroupId &idDataGroup);

private:
};
