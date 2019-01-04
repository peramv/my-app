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
// ^FILE   : UnitFactor.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : UnitFactor
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

class IFASTCBO_LINKAGE UnitFactor : public MFCanBFCbo
{
public:

   UnitFactor( BFAbstractCBO &parent );
   virtual ~UnitFactor();

   SEVERITY init(const BFData&   data );
	void		initNew(const BFDataGroupId& idDataGroup );

};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/UnitFactor.hpp-arc  $
//
//   Rev 1.1   Nov 14 2004 14:59:08   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.0   Sep 09 2004 11:27:50   HERNANDO
//Initial revision.
