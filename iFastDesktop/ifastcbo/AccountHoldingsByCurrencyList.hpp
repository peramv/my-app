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
// ^FILE   : AccountHoldingsByCurrencyList.hpp
// ^AUTHOR : Adrian Vasile
// ^DATE   : 04/19/99
//
// ^CLASS    : AccountHoldingsByCurrencyList
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

class IFASTCBO_LINKAGE AccountHoldingsByCurrencyList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   AccountHoldingsByCurrencyList( BFAbstractCBO &parent);
   virtual ~AccountHoldingsByCurrencyList( void );

   // Initialize function
   SEVERITY init();

   void getStrKey( DString& dstKey, const DString& currency );
   void getStrKey ( DString& strKey, const BFData* data );
   SEVERITY getFundCurrency( DString &currency, const BFData& data );

   SEVERITY createCurrencyObject( const BFData& data, const BFDataGroupId& idDataGroup );

private:
};

