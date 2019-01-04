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
//    Copyright 2007 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE      : Frequency.hpp
// ^AUTHOR    : Monica Porteanu
// ^DATE      : June 2007
//
// ^CLASS     : Frequency
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

class IFASTCBO_LINKAGE Frequency : public MFCanBFCbo, private boost::noncopyable
{
public:
   Frequency (BFAbstractCBO &parent);
   virtual ~Frequency();

   SEVERITY init( const BFData &viewData );   
protected:   
	
};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/Frequency.hpp-arc  $
//
//   Rev 1.1   Jun 22 2007 14:20:50   porteanm
//PET 2360 FN02 - AMS - work in progress.
//
//   Rev 1.0   Jun 20 2007 11:40:18   porteanm
//Initial revision.
//
