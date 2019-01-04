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
// ^FILE      : InvDetlDeduction.hpp
// ^AUTHOR    : Amelia Aguila
// ^DATE      : Jan. 2005
//
// ^CLASS     : InvDetlDeduction
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

class IFASTCBO_LINKAGE InvDetlDeduction : public MFCanBFCbo, private boost::noncopyable
{
public:
   InvDetlDeduction (BFAbstractCBO &parent);
   virtual ~InvDetlDeduction();

   SEVERITY init( const BFData &viewData );   
protected:   
	
};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/InvDetlDeduction.hpp-arc  $
//
//   Rev 1.0   Jan 28 2005 13:52:50   aguilaam
//Initial revision.
//
