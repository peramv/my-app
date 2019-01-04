#pragma once

//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1999 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : FeeModelSetupList.hpp
// ^AUTHOR :  
// ^DATE   : 
//
// ^CLASS    : FeeModelSetupList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <boost\utility.hpp>
#include <ifastcbo\mfcancbo.hpp>


#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE FeeModelSetupList : public MFCanBFCbo, private boost::noncopyable
{
public:

   // X-structors
   FeeModelSetupList( BFAbstractCBO &parent );
   virtual ~FeeModelSetupList();
   // Initialize function
   SEVERITY init(const DString& dstrTrack = I_("N"), const DString& dstrPageName = NULL_STRING );
   void getFeeModelSetup(BFAbstractCBO* &pFeeModelSetup, DString& dstrFeeModelType);
   void getAvailableFeeModelTypes(DString& dstrAvailableFeeModelTypes);


protected:
   //virtual SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );

private:
//	bool bDefault_;
};

