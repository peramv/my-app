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
// ^FILE   : AlertMessageList.hpp
// ^AUTHOR : 
// ^DATE   : 04 April 2016
//
// ^CLASS    : AlertMessageList
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

class IFASTCBO_LINKAGE AlertMessageList : public MFCanBFCbo, private boost::noncopyable
{
public:
	AlertMessageList(BFAbstractCBO &parent);
	virtual ~AlertMessageList();

	//SEVERITY init(const BFData& data);
	SEVERITY init(const DString &accountNum,
                  const DString &effectiveDate,
                  const DString &fromScreen,
                  const DString &dstrTrack = I_("N"), 
		          const DString &dstrPageName = NULL_STRING);

protected:

private:
};