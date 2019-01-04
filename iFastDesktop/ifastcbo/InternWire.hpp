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
// ^FILE   : InternWire.hpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 08/14/2000
//
// ^CLASS    : InternWire
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

class IFASTCBO_LINKAGE InternWire : public MFCanBFCbo, private boost::noncopyable
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

   InternWire( BFAbstractCBO &parent );
   virtual ~InternWire();

   SEVERITY init( const DString& strFundCode, 
                  const DString& strClassCode,
                  const DString& strSettleCurr, 
                  const DString& strCountryCode,
                  const DString& dstrTrack= I_("N"),
                  const DString& dstrPageName = NULL_STRING );

   bool isInternationalWire();

private:

   DString m_strFund;
   DString m_strClass;
   DString m_strSettleCurr;
   DString m_strCountryCode;
   bool m_bInternationalWire;

};

