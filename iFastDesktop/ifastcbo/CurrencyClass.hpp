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
// ^FILE   : DeductionList.hpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 03/22/99
//
// ^CLASS    : DeductionList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <dstring.hpp>
#include <boost\utility.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class DSTCWorkSession;

class IFASTCBO_LINKAGE CurrencyClass : private boost::noncopyable
{
public:
   static void FormatValue( const DString& currencyCode, const DString& rawValue, DString& formatValue );

   static void getFundCurrency( const DSTCWorkSession &workSession, 
                                const DString& fundCode, 
                                const DString& classCode, 
                                DString& currency );

   static int getPrecision( const DSTCWorkSession &workSession, const DString& dstrCurrency );

   static DString& getFormattedValue( const DSTCWorkSession &workSession, 
                                      DString &dstrValue, 
                                      const DString& dstrCurrency = NULL_STRING, 
                                      const DString& dstrAmountType = I_("D"));

private:
   static void FormatField( const DString& currencyCode, const DString& rawValue, DString& formatValue);
};

