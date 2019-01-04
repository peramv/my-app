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
// ^FILE   : FundClassHoldingsList.hpp
// ^AUTHOR : Adrian Vasile
// ^DATE   : 04/19/99
//
// ^CLASS    : ACBList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <srcprag.h>
#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
#include <commonport.h>
#include <bfdata\bfdata.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE FundClassHoldingsList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   FundClassHoldingsList( BFAbstractCBO &parent );
   virtual ~FundClassHoldingsList( void );

   SEVERITY init();

   void getStrKey( DString& dstKey, const DString& dstFund, const DString& dstClass );
   void getStrKey ( DString& strKey, const BFData* data );

   void createFundClassHoldingsObject( const BFData& data, const BFDataGroupId& idDataGroup );
   SEVERITY getTotalTenPercFree( DString& total );
   SEVERITY getTotalPercentage( DString& total );
   SEVERITY getTotalMarketValue( DString& total );
   SEVERITY getTotalBookValue( DString& total );

private:

};

///#endif

