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
// ^FILE   : TransactionExternalLinksList.hpp
// ^AUTHOR : Monica Vadeanu
// ^DATE   : August, 2004
//
// ^CLASS    : TransactionExternalLinksList
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


class IFASTCBO_LINKAGE TransactionExternalLinksList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   TransactionExternalLinksList(BFAbstractCBO &parent);
   virtual ~TransactionExternalLinksList();

   // Initialize function  					
	SEVERITY init( const DString &dstrTransNum,
						const DString &dstrTransId,
						const BFDataGroupId &idDataGroup = BF::HOST, 
						const DString& dstrTrack = I_("N"), 
						const DString &dstrPageName = NULL_STRING );
	
	SEVERITY getTransactionExternalLink( const DString &dstrExternalIdType,
						                      const DString &dstrExternalId, 
												    const BFDataGroupId &idDataGroup,
												    BFAbstractCBO *&pTransactionExternalLink );
protected:   
   virtual void getStrKey( DString &strKey, 
									const BFData *data );
private:
   void buildKey( DString &dstrKey, 
						const DString &dstrExternalIdType,
						const DString &dstrExternalId );

   BFData *_pRequestData;
};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/TransactionExternalLinksList.hpp-arc  $
//
//   Rev 1.1   Nov 14 2004 14:58:20   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.0   Aug 30 2004 14:16:36   VADEANUM
//Initial revision.
//
