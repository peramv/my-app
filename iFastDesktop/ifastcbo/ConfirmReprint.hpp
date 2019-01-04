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
// ^FILE      : ConfirmReprint.hpp
// ^AUTHOR    : Monica Porteanu
// ^DATE      : May, 2005
//
// ^CLASS     : ConfirmReprint
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

#include <ifastdataimpl\dse_dstc0149_vw.hpp>      // System Configuration 
#include <ifastdataimpl\dse_dstc0345_req.hpp>     // OPC Confirm Reprint Inquiry
#include <ifastdataimpl\dse_dstc0345_vw.hpp>      // OPC Confirm Reprint Inquiry

class IFASTCBO_LINKAGE ConfirmReprint : public MFCanBFCbo, private boost::noncopyable
{
public:
   ConfirmReprint (BFAbstractCBO &parent);
   virtual ~ConfirmReprint();

   virtual SEVERITY init( const DString &dstrTransId, 
				  const DString &dstrAccountNum,
                  const BFDataGroupId &idDataGroup, 
				  const DString &dstrTrack = I_( "N" ), 
				  const DString &dstrPageName = NULL_STRING );

   virtual SEVERITY initNew ( const DString &dstrTransId, 
					  const DString &dstrAccountNum,
	                  const BFDataGroupId &idDataGroup );

   virtual void reprintReset( const BFDataGroupId &idDataGroup );   

   inline DString getTransId() { return _dstrTransId; };
   inline DString getAccountNum() { return _dstrAccountNum; };
   inline DString getRunMode() { return _dstrRunMode; };  
protected:   
   virtual SEVERITY doApplyRelatedChanges( const BFFieldId &idField, 
										   const BFDataGroupId &idDataGroup );
   virtual void doInitWithDefaultValues( const BFDataGroupId &idDataGroup );
   virtual SEVERITY doValidateField( const BFFieldId &idField, 
									 const DString &strValue, 
									 const BFDataGroupId &idDataGroup );  
   virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
   virtual void doReset( const BFDataGroupId& idDataGroup );
       
   virtual SEVERITY setExistingRecord( const BFDataGroupId &idDataGroup );
   virtual SEVERITY setNewRecord( const BFDataGroupId &idDataGroup ); 	
   
   inline void setTransId( const DString &dstrTransId ) { _dstrTransId = dstrTransId; };
   inline void setAccountNum( const DString &dstrAccountNum) { _dstrAccountNum = dstrAccountNum; };   
   inline void setRunMode( const DString &dstrRunMode) { _dstrRunMode = dstrRunMode; };	

private:        
   BFData *_pRequestData;     
   BFData *_pResponse;

   DString _dstrTransId;
   DString _dstrAccountNum;
   DString _dstrRunMode;
};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/ConfirmReprint.hpp-arc  $
//
//   Rev 1.2   May 31 2005 15:53:08   porteanm
//PET OPC Confirm Reprint - Commit and Reset.
//
//   Rev 1.1   May 25 2005 14:59:52   porteanm
//PET OPC Confirm Reprint - Commit and Reset.
//
//   Rev 1.0   May 24 2005 12:33:22   porteanm
//Initial revision.
//


