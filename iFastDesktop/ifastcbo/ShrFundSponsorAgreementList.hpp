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
// ^FILE   : ShrFundSponsorAgreementList.hpp
// ^AUTHOR : Monica Vadeanu
// ^DATE   : June, 2004
//
// ^CLASS    : ShrFundSponsorAgreementList
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
class ShrFundSponsorAgreement;

class IFASTCBO_LINKAGE ShrFundSponsorAgreementList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   ShrFundSponsorAgreementList(BFAbstractCBO &parent);
   virtual ~ShrFundSponsorAgreementList();

   // Initialize function
   /*
	SEVERITY init( const DString &dstrRecordType,
						const DString &dstrFeeCode,
						const DString &dstrFundCode,
						const DString &dstrClassCode,
						const DString &dstrEffectiveDate,
						const DString &dstrStopDate = I_( "9999/12/31" ),
						const DString &dstrRecId = I_( "0" ),
						const DString &dstrDuplicateCheck = I_("N"),
						const BFDataGroupId &idDataGroup  = BF::HOST, 
						const DString &dstrTrack = I_("N"), 
						const DString &dstrPageName = NULL_STRING 
	*/					
						
	SEVERITY init( const DString &dstrFundGroup, 
						const BFDataGroupId &idDataGroup = BF::HOST, 
						const DString& dstrTrack = I_("N"), 
						const DString &dstrPageName = NULL_STRING );

	SEVERITY initNew( const DString &dstrShrNum, 
				 		   const BFDataGroupId& idDataGroup = BF::HOST );
   
   SEVERITY checkDuplicate( const ShrFundSponsorAgreement *pShrFundSponsorAgreementToCheck, 
									 const BFDataGroupId &idDataGroup );	  

	SEVERITY getShrFundSponsorAgreement( const DString &dstrFundGroup, 
													 const BFDataGroupId &idDataGroup,
												    ShrFundSponsorAgreement *&pShrFundSponsorAgreement );
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
						const DString &dstrFundGroup );

   BFData *_pRequestData;
};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/ShrFundSponsorAgreementList.hpp-arc  $
//
//   Rev 1.1   Nov 14 2004 14:56:06   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.0   Jul 26 2004 10:18:14   VADEANUM
//Initial revision.
//
