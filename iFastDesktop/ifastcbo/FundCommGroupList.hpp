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
// ^FILE   : FundCommGroupList.hpp
// ^AUTHOR :  Yingbao Li, May Lin
// ^DATE   : Dec. 31, 2002
//
// ^CLASS    : FundCommGroupList
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

class IFASTCBO_LINKAGE FundCommGroupList : public MFCanBFCbo, private boost::noncopyable
{
public:

   // X-structors
   FundCommGroupList( BFAbstractCBO &parent );
   virtual ~FundCommGroupList();
   // Initialize function

   SEVERITY init(const DString& dstrComm,const DString& dstrTrack = I_("N"),
                 const DString& dstrPageName = NULL_STRING );

	void getCommGroupSubstitute(DString& dstrSubstitute,bool bAddEmpty = true);
	SEVERITY getFundGroupListByType(const DString& dstrFundGroupType, FundCommGroupList*& pFundGroupList);

protected: 
   virtual void  getStrKey( DString &strKey, const BFData *data  );

private:

   DString _dstrCommGroupCode;
   bool _bFirst;
   BFData* _pRequestData;


};

/******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FundCommGroupList.hpp-arc  $
//
//   Rev 1.5   Nov 14 2004 14:41:50   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.4   Mar 21 2003 18:10:54   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.3   Mar 10 2003 14:50:36   linmay
//added  getFundGroupListByType
//
//   Rev 1.2   Jan 09 2003 15:46:22   YINGBAOL
//add getCommGroupSubstitute(DString& dstrSubstitute,bool bAddEmpty)  method
//

*/