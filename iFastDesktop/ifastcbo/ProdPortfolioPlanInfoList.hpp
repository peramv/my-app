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
// ^FILE   : ProdPortfolioPlanInfoList.hpp
// ^AUTHOR : 
// ^DATE   : Aug, 2011
//
// ^CLASS    : ProdPortfolioPlanInfoList
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

class IFASTCBO_LINKAGE ProdPortfolioPlanInfoList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   ProdPortfolioPlanInfoList( BFAbstractCBO &parent );
   virtual ~ProdPortfolioPlanInfoList(void);

// Initialize function
   SEVERITY init( const DString &prodPortFolioUUID,
                  const BFDataGroupId& idDataGroup
);

   SEVERITY getMore();
   SEVERITY getSubstitutionList(DString& dstrSubstitutionList, const BFDataGroupId& idDataGroup);

protected:
   virtual SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );

private:
   BFData* requestData419;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/ProdPortfolioPlanInfoList.hpp-arc  $
//
//   Rev 1.1   Sep 16 2011 17:57:52   dchatcha
//P0186477 FN01 - GIA Enhancements, Create substitution list
//
//   Rev 1.0   Aug 25 2011 17:10:28   dchatcha
//Initial revision.
//