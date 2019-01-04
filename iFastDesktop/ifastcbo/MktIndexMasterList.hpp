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
//    Copyright 2003, By International Financial Data Service
//
//
//******************************************************************************
//
// ^FILE   : MktIndexMasterList.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : MktIndexMasterList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE MktIndexMasterList : public MFCanBFCbo
{
public:

   MktIndexMasterList( BFAbstractCBO &parent );
   virtual ~MktIndexMasterList();

   SEVERITY init(const BFDataGroupId& idDataGroup,
					  const DString& dstrTrack = I_("N"),
					  const DString& dstrPageName = NULL_STRING );
   SEVERITY reInit();
   SEVERITY getMore();
   bool isMktIndexCodeValid( DString& dstrMktIndexCode, const BFDataGroupId& idDataGroup );

protected:

   virtual SEVERITY doCreateObject( const BFData& data, BFCBO*& pObjOut );
   virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
	virtual SEVERITY doCreateNewObject(BFCBO *&pObjOut, DString &strKey, const BFDataGroupId& idDataGroup );
	virtual void  getStrKey( DString &strKey, const BFData *data  );

   BFData m_requestData;
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/MktIndexMasterList.hpp-arc  $
//
//   Rev 1.2   Nov 14 2004 14:50:36   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.1   Mar 21 2003 18:19:30   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.0   Jan 23 2003 10:32:00   HERNANDO
//Initial Revision
//