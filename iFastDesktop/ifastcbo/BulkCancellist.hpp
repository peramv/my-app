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
// ^FILE   : BulkCancelList.hpp
// ^AUTHOR : Monica Porteanu
// ^DATE   : November 2005
//
// ^CLASS    : BulkCancelList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <boost\utility.hpp>
#include <ifastcbo\mfcancbo.hpp>
#include <ifastcbo\TransCancellist.hpp>

// Forward references
#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class DilutionAllocList;
class BulkCancel;

class IFASTCBO_LINKAGE BulkCancellist : public TransCancellist
{
public:
   // X-structors
   BulkCancellist( BFAbstractCBO &parent );
   virtual ~BulkCancellist();
   
   /*
   // Initialize function
   SEVERITY init ( const DString &transNum,
                   const DString& cashDivPaidAfter,
                   const BFDataGroupId& idDataGroup, 
						 const DString &dstrTradeDate = NULL_STRING,
						 const DString &dstrFundCode = NULL_STRING,
						 const DString &dstrClassCode = NULL_STRING,
						 const DString &dstrSearchType = NULL_STRING,
						 const DString &dstrTranStatus = NULL_STRING,
						 const DString &dstrAdjustType = NULL_STRING,
                   const DString &dstrTrack = I_("N"),
                   const DString &dstrPageName = NULL_STRING);
   */
   SEVERITY getBulkCancel( const DString &dstrTradeDate, 
	                       const DString &dstrFund,
						   const DString &dstrClass,
                           BulkCancel *&pBulkCancel, 
                           const BFDataGroupId &idDataGroup );
   SEVERITY getMore();

protected:
   SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
   SEVERITY doCreateNewObject( BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup );  
   SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );  
   virtual void getStrKey( DString &strKey, 
						   const BFData *data );
private:	 
	void buildKey( DString &dstrKey, 
  				   const DString &dstrTradeDate,
				   const DString &dstrFund,
				   const DString &dstrClass );
};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/BulkCancellist.hpp-arc  $
//
//   Rev 1.1   Nov 06 2005 14:01:16   porteanm
//PET 1286 FN01 - Bulk Cancellation - work in progress.
//
//   Rev 1.0   Nov 05 2005 15:08:00   porteanm
//Initial revision.
// 
*/

