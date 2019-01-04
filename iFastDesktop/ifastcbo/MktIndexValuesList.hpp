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
// ^FILE   : MktIndexValuesList.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : MktIndexValuesList
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

class IFASTCBO_LINKAGE MktIndexValuesList : public MFCanBFCbo
{

friend class MktIndexValues;

public:

   MktIndexValuesList( BFAbstractCBO &parent );
   virtual ~MktIndexValuesList();

   SEVERITY init(const BFDataGroupId& idDataGroup,
				 const DString& dstrTrack = I_("N"),
				 const DString& dstrPageName = NULL_STRING,
                 const DString& dstrSearchType = I_("ALL"),
				 const DString& dstrIndexCode= NULL_STRING,
                 const DString& dstrFromDate = NULL_STRING,
                 const DString& dstrToDate = NULL_STRING ); 
   DString getInputDataType(DString indexCode,const BFDataGroupId& idDataGroup,bool bIndexName=FALSE );

   SEVERITY reInit();
   SEVERITY getMore();

protected:

   virtual SEVERITY doCreateObject( const BFData& data, BFCBO*& pObjOut );
   virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
	virtual SEVERITY doCreateNewObject(BFCBO *&pObjOut, DString &strKey, const BFDataGroupId& idDataGroup );
	virtual void  getStrKey( DString &strKey, const BFData *data  );

   BFData m_requestData;

private:

   bool isDuplicate( DString &, DString &, const BFDataGroupId& idDataGroup );

   DString m_dstrIndexCodeSubstitution;
   DString m_dstrInitialIndexCode;
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/MktIndexValuesList.hpp-arc  $
//
//   Rev 1.6   Jan 16 2012 14:34:58   wp040027
//P0188394_Performance Fees - Benchmark Upload
//
//   Rev 1.5   Nov 14 2004 14:50:42   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.4   May 16 2003 17:34:04   HERNANDO
//Initialize IndexCode.
//
//   Rev 1.3   Mar 21 2003 18:19:40   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.2   Feb 06 2003 10:41:06   HERNANDO
//Revised.
//
//   Rev 1.1   Jan 29 2003 18:35:34   HERNANDO
//Revised.
//
//   Rev 1.0   Jan 29 2003 11:49:44   HERNANDO
//Initial Revision
//