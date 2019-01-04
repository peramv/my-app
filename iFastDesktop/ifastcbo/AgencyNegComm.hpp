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
// ^FILE      : AgencyNegComm.hpp
// ^AUTHOR    : Monica Porteanu
// ^DATE      : May 29, 2006
//
// ^CLASS     : AgencyNegComm
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

class IFASTCBO_LINKAGE AgencyNegComm : public MFCanBFCbo, private boost::noncopyable
{
public:
   AgencyNegComm (BFAbstractCBO &parent);
   virtual ~AgencyNegComm();

   SEVERITY init( const DString &dstrPayInstructRID,	              
	              const BFDataGroupId &idDataGroup );

   bool hasNegativeCommission( const BFDataGroupId &idDataGroup );
private:
	BFData *_pRequestData;
};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/AgencyNegComm.hpp-arc  $
//
//   Rev 1.0   May 31 2006 17:52:48   porteanm
//Initial revision.
//
