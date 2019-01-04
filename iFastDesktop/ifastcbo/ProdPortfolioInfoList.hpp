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
// ^FILE   : ProdPortfolioInfoList.hpp
// ^AUTHOR : 
// ^DATE   : Aug, 2011
//
// ^CLASS    : ProdPortfolioInfoList
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

class IFASTCBO_LINKAGE ProdPortfolioInfoList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   ProdPortfolioInfoList( BFAbstractCBO &parent );
   virtual ~ProdPortfolioInfoList(void);

// Initialize function
   SEVERITY init(const DString& dstrShGroup, const BFDataGroupId& idDataGroup);

   SEVERITY getMore();
   SEVERITY getSubstitutionList(DString& dstrSubstitutionList, const BFDataGroupId& idDataGroup);
   SEVERITY getPortfolioUUIDbyPortfolioCode (DString& portfolioCode, 
                                             DString*& prodPortfolioUUID,
                                             const BFDataGroupId& idDataGroup);
   SEVERITY getPortfolioCodebyPortfolioUUID (DString& _portfolioUUID, 
                                             DString*& _prodPortfolioCode,
                                             const BFDataGroupId& idDataGroup);
   bool hasPortfolioSegFunds ( const DString& _prodPortfolioUUID,
                               const BFDataGroupId& idDataGroup);
   bool isCommitmentApplicable ( const DString& _prodPortfolioUUID,
                                 const BFDataGroupId& idDataGroup);

protected:
   virtual SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );

private:
   BFData* requestData418;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/ProdPortfolioInfoList.hpp-arc  $
//
//   Rev 1.6   Feb 24 2012 16:07:04   popescu
//NASU - Added commitment.
//
//   Rev 1.5   Jan 21 2012 09:00:54   dchatcha
//IN# 2799812 - Contract Screen issues.
//
//   Rev 1.4   Dec 19 2011 23:32:48   popescu
//P0186484 - FN 05 - work on Contract Information Screen
//
//   Rev 1.3   Sep 30 2011 10:07:50   popescu
//P0186477 FN01 - GIA Enhancements
//
//   Rev 1.2   Sep 16 2011 17:55:48   dchatcha
//P0186477 FN01 - GIA Enhancements, Create substitution list
//
//   Rev 1.1   Aug 30 2011 14:45:44   dchatcha
//P0186477 FN01 - GIA Enhancements, put 'ShGroup' as query parameter.
//
//   Rev 1.0   Aug 25 2011 17:09:16   dchatcha
//Initial revision.
//
