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
//    Copyright 2003 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : MktIndexFundsList.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : MktIndexFundsList
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

class IFASTCBO_LINKAGE MktIndexFundsList : public MFCanBFCbo, private boost::noncopyable
{
public:

   MktIndexFundsList( BFAbstractCBO &parent );
   virtual ~MktIndexFundsList( void );
   SEVERITY initNew( const BFDataGroupId& idDataGroup,
                             bool bGetDefault = true,
                             const DString& dstrTrack = I_("N"),
                             const DString& dstrPageName = NULL_STRING,
                             const DString& dstrIndexCode = NULL_STRING );                
   SEVERITY initExisting( const DString& dstrTrack = I_("N"),
                          const DString& dstrPageName = NULL_STRING,
                          const DString& dstrIndexCode = NULL_STRING );

protected:

   SEVERITY doCreateNewObject( BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup );
   SEVERITY doCreateObject( const BFData &data, BFCBO *&pObjOut );
   SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/MktIndexFundsList.hpp-arc  $
//
//   Rev 1.4   Nov 14 2004 14:50:32   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.3   Mar 21 2003 18:19:20   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.2   Feb 03 2003 15:54:16   HERNANDO
//Modified initExisting.
//
//   Rev 1.1   Jan 29 2003 14:10:56   HERNANDO
//Revised.
//
//   Rev 1.0   Jan 23 2003 10:31:56   HERNANDO
//Initial Revision
*/