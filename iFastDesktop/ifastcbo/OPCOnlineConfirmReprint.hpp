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
// ^FILE      : OPCOnlineConfirmReprint.hpp
// ^AUTHOR    : Monica Porteanu
// ^DATE      : May, 2005
//
// ^CLASS     : OPCOnlineConfirmReprint
// ^SUBCLASS  :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\opcconfirmreprint.hpp>

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
///#endif

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif


class IFASTCBO_LINKAGE OPCOnlineConfirmReprint : virtual public OPCConfirmReprint
{
public:
   OPCOnlineConfirmReprint (BFAbstractCBO &parent);
   virtual ~OPCOnlineConfirmReprint();
      
protected:
   virtual SEVERITY doApplyRelatedChanges( const BFFieldId &idField, 
										   const BFDataGroupId &idDataGroup );
	virtual void doInitWithDefaultValues( const BFDataGroupId &idDataGroup );
   virtual SEVERITY doValidateField( const BFFieldId &idField, 
									 const DString &strValue, 
									 const BFDataGroupId &idDataGroup );

   virtual void doReset( const BFDataGroupId &idDataGroup );
private:   
};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/OPCOnlineConfirmReprint.hpp-arc  $
//
//   Rev 1.0   May 06 2005 11:55:22   porteanm
//Initial revision.
//


