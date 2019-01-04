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
//    Copyright 2006 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE      : RRIFUnusedMaxAmt.hpp
// ^AUTHOR    : Monica Porteanu
// ^DATE      : Sept 05, 2006
//
// ^CLASS     : RRIFUnusedMaxAmt
// ^SUBCLASS  :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
///#endif

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE RRIFUnusedMaxAmt : public MFCanBFCbo, private boost::noncopyable
{
public:
   RRIFUnusedMaxAmt (BFAbstractCBO &parent);
   virtual ~RRIFUnusedMaxAmt();

   SEVERITY init( const DString &dstrAccount,
				  const DString &dstrEffectiveDate,
				  const DString &dstrRRIFId,
				  const DString &dstrOverrideUnusedMax,
				  const DString &dstrOverrideMndAmt,								 
				  const BFDataGroupId &idDataGroup );   
private:
	BFData *_pRequestData;
};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/RRIFUnusedMaxAmt.hpp-arc  $
//
//   Rev 1.0   Sep 06 2006 11:08:40   porteanm
//Initial revision.
//
//
