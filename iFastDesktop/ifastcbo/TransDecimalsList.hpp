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
// ^FILE   : TransDecimalsList.hpp
// ^AUTHOR : Amelia Aguila
// ^DATE   : Feb. 2005
//
// ^CLASS    : TransDecimalsList
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
class TransDecimals;

class IFASTCBO_LINKAGE TransDecimalsList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   TransDecimalsList(BFAbstractCBO &parent);
   virtual ~TransDecimalsList();

   // Initialize function   		
	SEVERITY init( const DString &dstrTransId,                 			
						const BFDataGroupId &idDataGroup = BF::HOST, 
						const DString& dstrTrack = I_( "N" ), 
						const DString &dstrPageName = NULL_STRING );							

	SEVERITY getTransDecimals( const DString &dstrDecimalType, 
										const BFDataGroupId &idDataGroup,
										TransDecimals *&pTransDecimals );

protected:

   virtual SEVERITY doCreateObject( const BFData& data, 
												BFCBO *&pObjOut);
   
   virtual void getStrKey( DString &strKey, 
									const BFData *data );
private:
   void buildKey( DString &dstrKey, 
						const DString &dstrDecimalType );

   BFData *_pRequestData;
};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/TransDecimalsList.hpp-arc  $
//
//   Rev 1.0   Mar 03 2005 14:42:34   aguilaam
//Initial revision.
//

