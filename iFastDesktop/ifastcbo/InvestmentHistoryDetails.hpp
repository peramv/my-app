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
// ^FILE   : InvestmentHistoryDetails.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : InvestmentHistoryDetails
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

class IFASTCBO_LINKAGE InvestmentHistoryDetails : public MFCanBFCbo
{
public:
   InvestmentHistoryDetails( BFAbstractCBO &parent );
   virtual ~InvestmentHistoryDetails();

   SEVERITY init( const BFData& data );


protected:

private:
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/InvestmentHistoryDetails.hpp-arc  $
//
//   Rev 1.1   Nov 25 2011 13:54:28   wp040100
//P0186477/FN03 - GIA - Investment History Changes
 * 
 * 
// 
*/
