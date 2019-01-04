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
//    Copyright 2007 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : FrequencyList.hpp
// ^AUTHOR : Monica Porteanu
// ^DATE   : June 2007
//
// ^CLASS    : FrequencyList
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
class Frequency;

class IFASTCBO_LINKAGE FrequencyList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   FrequencyList(BFAbstractCBO &parent);
   virtual ~FrequencyList(void);

   // Initialize function   		
	SEVERITY init( const DString& dstrTrack = I_( "N" ), 
				      const DString &dstrPageName = NULL_STRING );		
	
	SEVERITY init( const BFDataGroupId &idDataGroup );	

	SEVERITY getFrequency( const DString &dstrSchedSetupFreqID, 
		                    const BFDataGroupId &idDataGroup,
						        Frequency *&pFrequency );
   SEVERITY getMore();

	SEVERITY getFrequencySubstitutionSet( DString &dstrFrequencySubstitutionSet,
		                                   const BFDataGroupId &idDataGroup = BF::HOST );
protected:

   virtual SEVERITY doCreateObject( const BFData& data, 
									         BFCBO *&pObjOut);
   
   virtual void getStrKey( DString &strKey, 
						         const BFData *data );
private:
   void buildKey( DString &dstrKey, 
				       const DString &dstrSchedSetupFreqID );

   BFData *_pRequestData;
};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/FrequencyList.hpp-arc  $
//
//   Rev 1.1   Jun 22 2007 14:21:16   porteanm
//PET 2360 FN02 - AMS - work in progress.
//
//   Rev 1.0   Jun 20 2007 11:40:30   porteanm
//Initial revision.
//
//

