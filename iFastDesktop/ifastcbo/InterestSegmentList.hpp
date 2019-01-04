#pragma once

//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2004 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : InterestSegmentList.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : InterestSegmentList
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

class IFASTCBO_LINKAGE InterestSegmentList : public MFCanBFCbo, private boost::noncopyable
{
public:
   InterestSegmentList( BFAbstractCBO &parent );
   virtual ~InterestSegmentList();

	SEVERITY init (	const DString& dstrAccountNum,
					const DString& dstrIntInvestId,
					const BFDataGroupId& idDataGroup);

	SEVERITY init (const BFDataGroupId& idDataGroup);

private:
	BFData m_requestData;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/InterestSegmentList.hpp-arc  $
//
//   Rev 1.0   Dec 09 2011 19:46:10   wp040100
//Initial revision.
//
//
//
 * 
 * 
// 
*/
