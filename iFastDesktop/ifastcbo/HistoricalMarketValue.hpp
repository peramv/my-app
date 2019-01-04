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
//    Copyright 2002 by International Financial.
//
//
//******************************************************************************
//
// ^FILE   : HistoricalMarketValue.hpp
// ^AUTHOR : Yingbao Li
// ^DATE   : Feb. 4, 2002
//
// ^CLASS    : HistoricalMarketValue
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

class HistoricalMarketValueList;

class IFASTCBO_LINKAGE HistoricalMarketValue : public MFCanBFCbo, private boost::noncopyable
{
public:
   //TODO: enter specific field enumerations

   HistoricalMarketValue( BFAbstractCBO &parent );
   virtual ~HistoricalMarketValue();

   SEVERITY init(  const BFData& InstData );
   bool amountInventoryAppl();
private:

   void CalculatePrcnt( const BFFieldId& fieldFZ, const BFFieldId& fieldFM, const BFFieldId& fieldPrcnt);

};
