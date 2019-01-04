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
// ^FILE      : OPCConfirmReprint.hpp
// ^AUTHOR    : Monica Porteanu
// ^DATE      : May, 2005
//
// ^CLASS     : OPCConfirmReprint
// ^SUBCLASS  :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\confirmreprint.hpp>

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
///#endif

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

#include <ifastdataimpl\dse_dstc0004_vw.hpp>      // MFAccount 
#include <ifastdataimpl\dse_dstc0090_vw.hpp>      // Broker


class IFASTCBO_LINKAGE OPCConfirmReprint : public ConfirmReprint
{
public:
   OPCConfirmReprint (BFAbstractCBO &parent);
   virtual ~OPCConfirmReprint();            

   virtual void reprintReset( const BFDataGroupId &idDataGroup );     
protected:
   virtual SEVERITY doApplyRelatedChanges( const BFFieldId &idField, 
										   const BFDataGroupId &idDataGroup );	
    
   virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
   
   virtual SEVERITY setExistingRecord( const BFDataGroupId &idDataGroup );
   virtual SEVERITY setNewRecord( const BFDataGroupId &idDataGroup ); 	
   
private:   	   
  SEVERITY setAcctRelatedParameters( const BFDataGroupId &idDataGroup );  
  SEVERITY getCopyParameters( const BFDataGroupId &idDataGroup,
							  DString &dstrDefaultClientCopy,
							  DString &dstrDefaultBrokerCopy,
							  DString &dstrDefaultSalesRepCopy );

  DString _dstrAcctDesignation;
  DString _dstrAcctBroker;
};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/OPCConfirmReprint.hpp-arc  $
//
//   Rev 1.5   May 31 2005 15:54:06   porteanm
//PET OPC Confirm Reprint - Commit and Reset.
//
//   Rev 1.4   May 26 2005 17:56:16   porteanm
//PET OPC Confirm Reprint - Cleanup.
//
//   Rev 1.3   May 26 2005 10:25:06   porteanm
//PET OPC Confirm Reprint - Setting fields properties.
//
//   Rev 1.2   May 25 2005 15:00:42   porteanm
//PET OPC Confirm Reprint - Commit and Reset.
//
//   Rev 1.1   May 24 2005 12:37:26   porteanm
//PET OPC Confirm Reprint - Renamed OPC files. Changed class hierarchy.
//



