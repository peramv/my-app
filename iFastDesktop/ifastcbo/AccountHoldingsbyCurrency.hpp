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
// ^FILE   : AccountHoldingsByCurrency.hpp
// ^AUTHOR : Adrian Vasile
// ^DATE   : 04/19/99
//
// ^CLASS    : ACBList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

class FundClassHoldingsList;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE AccountHoldingsByCurrency : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   AccountHoldingsByCurrency( BFAbstractCBO &parent );
   virtual ~AccountHoldingsByCurrency( void );

   // Initialize function
   SEVERITY init( const BFData& data, const DString& strCurrency );

   SEVERITY getFundClassHoldingsList( FundClassHoldingsList *&pFundClassHoldingsList, const BFDataGroupId& idDataGroup );
   void getCurrency( DString& strCurrency );
   SEVERITY getTotalTenPercFree( DString& total );
   SEVERITY getTotalMarketValue( DString& total );
   SEVERITY getTotalBookValue( DString& total );
   SEVERITY getTotalPercentage( DString& total );

private:

   DString _currency;
};

