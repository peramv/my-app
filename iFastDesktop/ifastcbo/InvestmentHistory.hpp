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
//    Copyright 2010, By International Financial Data Service
//
//
//******************************************************************************
//
// ^FILE   : InvestmentHistory.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : InvestmentHistory
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class InvestmentHistoryDetailsList;
class InvestmentHistoryInterestList;

class IFASTCBO_LINKAGE InvestmentHistory : public MFCanBFCbo
{
public:
   InvestmentHistory( BFAbstractCBO &parent );
   virtual ~InvestmentHistory();

   SEVERITY init( const BFData& data );

   SEVERITY getInvestmentDetails ( InvestmentHistoryDetailsList *&pInvestmentHistoryDetailsList, 
									const BFDataGroupId& idDataGroup );
   SEVERITY getInvestmentInterestList( InvestmentHistoryInterestList *&pInvestmentHistoryInterestList, 
									   const BFDataGroupId& idDataGroup );

protected:

private:
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/InvestmentHistory.hpp-arc  $
//
//   Rev 1.2   Nov 25 2011 17:40:52   wp040100
//P0186477/FN03 - GIA - Investment History Changes
 * 
 * 
// 
*/
