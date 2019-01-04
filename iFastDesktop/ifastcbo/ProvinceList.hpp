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
// ^FILE   : ProvinceList.hpp
// ^AUTHOR : Monica Porteanu
// ^DATE   : February 2005
//
// ^CLASS    : ProvinceList
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
class Province;

class IFASTCBO_LINKAGE ProvinceList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   ProvinceList(BFAbstractCBO &parent);
   virtual ~ProvinceList();

   // Initialize function   		
	SEVERITY init( const DString &dstrCountryCode,                 			
				   const BFDataGroupId &idDataGroup = BF::HOST, 
				   const DString& dstrTrack = I_( "N" ), 
				   const DString &dstrPageName = NULL_STRING );		

	// For the cases when CountryCode is blank (see AddressProcess::getPtrForContainer() )
	SEVERITY init( const BFDataGroupId &idDataGroup );	

    SEVERITY getMore();

	SEVERITY getProvinceSubstitutionSet( DString &dstrProvinceSubstitutionSet,
		                                 const BFDataGroupId &idDataGroup = BF::HOST );
protected:

   virtual SEVERITY doCreateObject( const BFData& data, 
									BFCBO *&pObjOut);
   
private:

   BFData *_pRequestData;
};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/ProvinceList.hpp-arc  $
//
//   Rev 1.2   06 Nov 2007 13:47:14   kovacsro
//IN#1057338 - province CanadaUS substitution set read from view 252 now, rather than the DD
//
//   Rev 1.1   Mar 15 2005 10:44:40   porteanm
//PET 1171 FN01 - EUSD Entity Address Update support.
//
//   Rev 1.0   Feb 22 2005 14:30:56   porteanm
//Initial revision.
//

