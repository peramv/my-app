#pragma once

//******************************************************************************
//
// COPYRIGHT:
//
// The computer systems, procedures, data bases and
// programs created and maintained by International Financial Data Services,
// are proprietary in nature and as such are confIdential.
// Any unauthorized use or disclosure of such information
// may result in civil liabilities.
//
// Copyright 2009 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : SystemVerificationDetailsList.hpp
// ^AUTHOR : 
// ^DATE   : Nov 2009
//
// ^CLASS    : SystemVerificationDetailsList
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

class IFASTCBO_LINKAGE SystemVerificationDetailsList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   SystemVerificationDetailsList( BFAbstractCBO &parent );
   virtual ~SystemVerificationDetailsList(void);

// Initialize function
   SEVERITY init( const DString &dstrTrack     = I_( "N" ),
                  const DString &dstrPageName  = NULL_STRING );

   SEVERITY canVerify (const BFDataGroupId &idDataGroup, const DString &dstrVerifyCategory, 
	                   const DString &dstrVerifyLevel, DString &dstrActive, DString &dstrVerifyFilter);

protected:
    virtual SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );

private:
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/SystemVerificationDetailsList.hpp-arc  $
//
//   Rev 1.1   Nov 17 2009 15:14:48   jankovii
//PET0166583 FN01 Static Data Changes Banking 
//
//   Rev 1.0   Nov 16 2009 06:21:24   dchatcha
//Initial revision.
//
