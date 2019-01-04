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
// ^FILE   : ShrFundBrokerList.hpp
// ^AUTHOR : Monica Vadeanu
// ^DATE   : June, 2004
//
// ^CLASS    : ShrFundBrokerList
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
class ShrFundBroker;

class IFASTCBO_LINKAGE ShrFundBrokerList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   ShrFundBrokerList(BFAbstractCBO &parent);
   virtual ~ShrFundBrokerList();

   // Initialize function   		
	SEVERITY init( const DString &dstrShareholderNum,
                  const DString &dstrFund,   
						const DString &dstrFundBroker, 
						const DString &dstrDuplicateCheck = I_( "N" ), 
						const BFDataGroupId &idDataGroup = BF::HOST, 
						const DString& dstrTrack = I_( "N" ), 
						const DString &dstrPageName = NULL_STRING );							

	SEVERITY initNew( const DString &dstrShrNum, 
				 		   const BFDataGroupId& idDataGroup = BF::HOST );
   
   SEVERITY checkDuplicate( const ShrFundBroker *pShrFundBrokerToCheck, 
									 const BFDataGroupId &idDataGroup );	  

	SEVERITY getShrFundBroker( const DString &dstrFund, 
		                        const DString &dstrFundBroker, 
										const BFDataGroupId &idDataGroup,
										ShrFundBroker *&pShrFundBroker );

   SEVERITY getMore();
protected:

   virtual SEVERITY doCreateObject( const BFData& data, 
												BFCBO *&pObjOut);

   virtual SEVERITY doCreateNewObject( BFCBO *&pBase, 
													DString &dstrKey, 
													const BFDataGroupId& idDataGroup );

   virtual void getStrKey( DString &strKey, 
									const BFData *data );
private:
   void buildKey( DString &dstrKey, 
						const DString &dstrShareholderNum,
						const DString &dstrFund,
						const DString &dstrFundBroker );

   BFData *_pRequestData;
};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/ShrFundBrokerList.hpp-arc  $
//
//   Rev 1.2   Nov 28 2004 14:02:02   vadeanum
//PET1117 FN08 - Shareholder Fund Broker support.
//
//   Rev 1.1   Nov 11 2004 16:39:34   vadeanum
//PET1117 FN08 - Shareholder Fund Broker support - work in progress
//
//   Rev 1.0   Nov 04 2004 17:25:16   VADEANUM
//Initial revision.
//