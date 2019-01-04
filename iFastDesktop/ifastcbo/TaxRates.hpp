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
//    Copyright 2000 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : TaxRates.hpp
// ^AUTHOR : Cristina Oltean
// ^DATE   : 24/11/2000
//
// ^CLASS    : TaxRates
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************



#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
///#endif

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE TaxRates : public MFCanBFCbo, private boost::noncopyable
{
public:
   //TODO: enter specific field enumerations
   enum FIELD
   {
      UNUSED_FIELD,
      MAX_FIELDS
   };

   //TODO: enter specific contained object enumerations
   enum OBJECT
   {
      UNUSED_OBJECT,
      MAX_OBJECTS
   };

   TaxRates( BFAbstractCBO &parent );
   virtual ~TaxRates();

   SEVERITY init( const BFData& InstData );

private:
};

///#endif
