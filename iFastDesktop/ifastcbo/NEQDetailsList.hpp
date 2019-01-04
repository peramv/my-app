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
// ^FILE   : NEQDetailsList.hpp
// ^AUTHOR : 
// ^DATE   : Nov 2009
//
// ^CLASS    : NEQDetailsList
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

class IFASTCBO_LINKAGE NEQDetailsList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   NEQDetailsList( BFAbstractCBO &parent );
   virtual ~NEQDetailsList(void);

// Initialize function
   SEVERITY init( const DString &dstrTrack     = I_( "N" ),
                  const DString &dstrPageName  = NULL_STRING );

	SEVERITY getNEQList(DString &dstrNEQList, const DString dstrWhereUse, const BFDataGroupId &idDataGroup);
	SEVERITY getNEQId( DString &dstrNEQId, const DString dstrWhereUse, const BFDataGroupId &idDataGroup);

protected:
    virtual SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );

private:
};


// $Log::  
//
