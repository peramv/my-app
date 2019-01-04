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
//    Copyright 2002 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : AbstractFundAllocList.hpp
// ^AUTHOR : Yingbao Li	
// ^DATE   : Nov. 13, 2002
//
// ^CLASS    : AbstractFundAllocList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : This is the base class for fund level
//								allocation list 
//
//******************************************************************************


#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE AbstractFundAllocList:public MFCanBFCbo,private boost::noncopyable
{
public:

   // X-structors
   AbstractFundAllocList( BFAbstractCBO &parent );
   virtual ~AbstractFundAllocList( void );

protected:


   SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
	// return true, if allocation list has to contain at least one item.
	// otherwise return false, sub class can override it.
	virtual bool bOneItemMustExit()
	{return false;}
		//calculate total percentage of each allocation
	double getTotalPercentage(const BFDataGroupId& idDataGroup);

private :


};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AbstractFundAllocList.hpp-arc  $
//
//   Rev 1.2   Mar 21 2003 17:53:44   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.1   Nov 27 2002 11:40:52   YINGBAOL
//add getTotalPercentage
//
//   Rev 1.0   Nov 13 2002 10:01:18   YINGBAOL
//Initial Revision
//

 * 
 *
*/