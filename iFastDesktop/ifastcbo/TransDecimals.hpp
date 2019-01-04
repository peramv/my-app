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
//    Copyright 2004 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE      : TransDecimals.hpp
// ^AUTHOR    : Amelia Aguila
// ^DATE      : Feb. 2005
//
// ^CLASS     : TransDecimals
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

class IFASTCBO_LINKAGE TransDecimals : public MFCanBFCbo, private boost::noncopyable
{
public:
   TransDecimals (BFAbstractCBO &parent);
   virtual ~TransDecimals();

   SEVERITY init( const BFData &viewData );   
protected:   
	
};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/TransDecimals.hpp-arc  $
//
//   Rev 1.0   Mar 03 2005 14:42:36   aguilaam
//Initial revision.
//
