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
//    Copyright 2004 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : RemarkContainer.hpp
// ^AUTHOR : Yingbao  Li
// ^DATE   : 
//
// ^CLASS    : BrokerRemark
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

class BrokerRemarkList;
class IFASTCBO_LINKAGE RemarkContainer : public MFCanBFCbo, private boost::noncopyable
{
public:


   RemarkContainer( BFAbstractCBO &parent );
   virtual ~RemarkContainer(){};
   SEVERITY init(const DString& dstrBrokerCode, 
									const DString& dstrBranchCode,
								   const DString& dstrAgentCode, 
									const DString& date,
									const BFDataGroupId& idDataGroup, 
									const DString& dstrTrack= I_("N"),
									const DString& dstrPageName=NULL_STRING  );  
		
	SEVERITY getBrokerRemarkList( BrokerRemarkList*& pBrokerRemarkList,
		const BFDataGroupId& idDataGroup,unsigned int iType, bool bInq = true,
		bool bCreate = true );

private:

	void buildKey( DString &strKey, unsigned int uiListType );

	
private:

   DString _brokerCode;
   DString _branchCode;
	DString _agentCode;
	DString _date;
	DString _track;
	DString _pageName;
 
};

