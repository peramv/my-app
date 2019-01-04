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
// ^FILE   : FeeScaleSysList.hpp
// ^AUTHOR :  Yingbao Li, May Lin
// ^DATE   : January 08, 2003
//
// ^CLASS    : FeeScaleSysList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\FeeScaleBaseList.hpp>
#include <boost\utility.hpp>

// Forward references
class FeeScaleSys;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE FeeScaleSysList : public FeeScaleBaseList
{
public:

   // X-structors
   FeeScaleSysList( BFAbstractCBO &parent );
   virtual ~FeeScaleSysList();
   // Initialize function
   SEVERITY init( const DString& AcctFeeParamId,bool bDefault = false, const DString& dstrTrack = I_("N"),
                             const DString& dstrPageName = NULL_STRING );
   SEVERITY initNew(const BFDataGroupId& idDataGroup);
   SEVERITY AddNewFeeScale( FeeScaleBaseList* pFeeScaleList, const DString& strKey, const BFDataGroupId& idDataGroup );
	virtual void  getStrKey( DString &strKey, const BFData *data  );
   SEVERITY clone(const BFDataGroupId& idDataGroup, FeeScaleSysList*& pFeeScaleSysList);

protected:
   virtual SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
   virtual SEVERITY doCreateNewObject( BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup );

private:
	bool bDefault_;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FeeScaleSysList.hpp-arc  $
//
//   Rev 1.7   Nov 14 2004 14:40:42   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.6   Jun 26 2003 10:17:40   linmay
//modified AddNewFeeScale 
//
//   Rev 1.5   Jun 20 2003 16:29:56   linmay
//PTS#10014935
//
//   Rev 1.4   Mar 21 2003 18:10:18   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.3   Jan 17 2003 14:11:50   YINGBAOL
//i mplement init and docreateobject
//
//   Rev 1.2   Jan 15 2003 15:17:58   linmay
//added log comment
*/