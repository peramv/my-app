#pragma once

//******************************************************************************
//
// COPYRIGHT:
//
// The computer systems, procedures, data bases and
// programs created and maintained by International Financial Data Services, Inc.,
// are proprietary in nature and as such are confIdential.
// Any unauthorized use or disclosure of such information
// may result in civil liabilities.
//
// Copyright 2011 by International Financial Data Services, Inc.
//
//
//******************************************************************************
//
// ^FILE   : ProdPortfolioInfo.hpp
// ^AUTHOR : 
// ^DATE   : Aug, 2011
//
// ^CLASS    : ProdPortfolioInfo
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

class IFASTCBO_LINKAGE ProdPortfolioInfo : public MFCanBFCbo, private boost::noncopyable
{
public:

   ProdPortfolioInfo( BFAbstractCBO &parent );
   virtual ~ProdPortfolioInfo();

   SEVERITY init (const BFData& data );

protected:

private:

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
// 
// $Log:   Y:/VCS/BF iFAST/ifastcbo/ProdPortfolioInfo.hpp-arc  $
//
//   Rev 1.0   Aug 25 2011 17:08:42   dchatcha
//Initial revision.
//

