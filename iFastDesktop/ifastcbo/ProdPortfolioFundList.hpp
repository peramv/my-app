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
// Copyright 2011 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : ProdPortfolioFundList.hpp
// ^AUTHOR : 
// ^DATE   : Dec 2011
//
// ^CLASS    : ProdPortfolioFundList
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

class IFASTCBO_LINKAGE ProdPortfolioFundList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   ProdPortfolioFundList( BFAbstractCBO &parent );
   virtual ~ProdPortfolioFundList(void);

// Initialize function
   SEVERITY init( const DString& dstrGroupCode,
                  const DString &dstrProdPortfolioUUID,
                  const DString &dstrTrack     = I_( "N" ),
                  const DString &dstrPageName  = NULL_STRING);

protected:

private:

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/ProdPortfolioFundList.hpp-arc  $
//
//   Rev 1.0   Dec 14 2011 18:07:58   dchatcha
//Initial revision.
//
