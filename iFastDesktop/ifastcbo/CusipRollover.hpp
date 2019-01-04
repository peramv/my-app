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
//    Copyright 2000 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : CusipRollover.hpp
// ^AUTHOR : 
// ^DATE   : Jan, 2010
//
// ^CLASS    : CusipRollover
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\purchase.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

//Forward declarations

class IFASTCBO_LINKAGE CusipRollover : public Purchase
{
public:
	CusipRollover (BFAbstractCBO &parent);
	virtual ~CusipRollover();

protected:
	virtual SEVERITY doInit (const BFDataGroupId &idDataGroup);
private:
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/CusipRollover.hpp-arc  $
//
//   Rev 1.0   Jan 29 2010 14:16:14   popescu
//Initial revision.
* 
*/