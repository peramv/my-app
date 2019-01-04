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
//    Copyright 2005 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE      : Province.hpp
// ^AUTHOR    : Monica Porteanu
// ^DATE      : February 2005
//
// ^CLASS     : Province
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

class IFASTCBO_LINKAGE Province : public MFCanBFCbo, private boost::noncopyable
{
public:
   Province (BFAbstractCBO &parent);
   virtual ~Province();

   SEVERITY init( const BFData &viewData );   
protected:   
	
};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/Province.hpp-arc  $
//
//   Rev 1.0   Feb 22 2005 14:30:24   porteanm
//Initial revision.
//
