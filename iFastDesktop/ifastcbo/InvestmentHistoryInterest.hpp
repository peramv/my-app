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
// ^FILE   : InvestmentHistoryInterest.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : InvestmentHistoryInterest
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

class InvestmentHistoryInterestList;

class IFASTCBO_LINKAGE InvestmentHistoryInterest : public MFCanBFCbo
{
public:
   InvestmentHistoryInterest( BFAbstractCBO &parent );
   virtual ~InvestmentHistoryInterest();

   SEVERITY init( const BFData& data );

protected:

private:

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/InvestmentHistoryInterest.hpp-arc  $
//
//   Rev 1.1   Nov 25 2011 13:55:00   wp040100
//P0186477/FN03 - GIA - Investment History Changes
 * 
 * 
// 
*/
