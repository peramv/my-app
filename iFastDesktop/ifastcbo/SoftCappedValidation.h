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
//    Copyright 1997 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : SoftCappedValidation.hpp
// ^AUTHOR : 
// ^DATE   : Jan, 2016
//
// ^CLASS    : SoftCappedValidation
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

class IFASTCBO_LINKAGE SoftCappedValidation : public MFCanBFCbo, private boost::noncopyable
{
public:

   SoftCappedValidation( BFAbstractCBO &parent );
   virtual ~SoftCappedValidation();
   
   SEVERITY init( const DString &strAccountNum, 
                  const DString &strFundCode, 
                  const DString &strClassCode, 
                  const DString &strTransType,
                  const DString &strEffectiveDate);   

   SEVERITY addConditions();

private:
    DString _fundCode;
    DString _classCode;
    DString _tradeDate;
};