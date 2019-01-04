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
// ^FILE   : HostSubstitutionValuesList.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : 03/11/99
//
// ^CLASS    : HostSubstitutionValuesList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
///#endif

class BFData;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

namespace STOPPERSTAGS
{
   extern const I_CHAR * const KEYTYPE;
   extern const I_CHAR * const TEMPVALUE;
}

class IFASTCBO_LINKAGE HostSubstitutionValuesList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   HostSubstitutionValuesList( BFAbstractCBO &parent );
   virtual ~HostSubstitutionValuesList();
   // Initialize function
   SEVERITY init();
   void addSubstitutionData( BFData *substitutionData );

   //building the keys
   static void buildHostSubstValueKeyForTempAccount( DString &strKey, const DString& accountNum );
   static void buildHostSubstValueKeyForTempEntity( DString &strKey, const DString& entityId );
   static void buildHostSubstValueKeyForTempShareholder( DString &strKey, const DString& shareholder );
   static void buildHostSubstValueKey( DString& strKey, const DString& keyType, const DString& tempValue );
   static void buildHostSubstValueKeyForTempFundSponsorModelId( DString &strKey, const DString& dstrSponsorModelID );
protected:
   virtual void getStrKey( DString &strKey, const BFData *data = NULL );
};

///#endif

