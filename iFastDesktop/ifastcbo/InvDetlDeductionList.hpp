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
// ^FILE   : InvDetlDeductionList.hpp
// ^AUTHOR : Amelia Aguila
// ^DATE   : Jan. 2005
//
// ^CLASS    : InvDetlDeductionList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

//Forward declarations
class InvDetlDeduction;

class IFASTCBO_LINKAGE InvDetlDeductionList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   InvDetlDeductionList(BFAbstractCBO &parent);
   virtual ~InvDetlDeductionList();

   // Initialize function   		
	SEVERITY init( const DString &dstrTransId,                 			
						const BFDataGroupId &idDataGroup = BF::HOST, 
						const DString& dstrTrack = I_( "N" ), 
						const DString &dstrPageName = NULL_STRING );							

	SEVERITY getInvDetlDeduction( const DString &dstrInvDetlId, 
		                           const DString &dstrDeductCode, 
										   const BFDataGroupId &idDataGroup,
										   InvDetlDeduction *&pInvDetlDeduction );

   SEVERITY getMore();
protected:

   virtual SEVERITY doCreateObject( const BFData& data, 
												BFCBO *&pObjOut);
   
   virtual void getStrKey( DString &strKey, 
									const BFData *data );
private:
   void buildKey( DString &dstrKey, 
						const DString &dstrInvDetlId,
						const DString &dstrDeductCode );

   BFData *_pRequestData;
};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/InvDetlDeductionList.hpp-arc  $
//
//   Rev 1.1   Feb 17 2005 13:16:02   aguilaam
//PET1198_FN01: LSIF Reason Code enhancement. 
//
//   Rev 1.0   Jan 28 2005 13:53:24   aguilaam
//Initial revision.
//
