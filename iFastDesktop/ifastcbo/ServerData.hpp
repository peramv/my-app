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
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : ServerData.hpp
// ^AUTHOR : Adrian Vasile
// ^DATE   : Oct 2, 2000
//
// ^CLASS  : ServerData
// ^PARENT : BFBase
//
// ^CLASS DESCRIPTION :
//  .
//
//******************************************************************************
#include <ifastcbo\verificationconf.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE ServerData : public VerificationConf
{
public:
   // X-structors
   ServerData( BFAbstractCBO &parent );
   virtual ~ServerData( void );

   // Initialize function
   SEVERITY init( DString& param );//PARAM_MAP& param );
   void getShareholderData( BFData **data );
   void getAccountData( BFData **data );
   bool getEntityData( BFData **data, long type = ENTITY_TYPE::ACCOUNT_OWNER_1 );
   bool getAddressData( BFData **data );
   void getTradesData( BFData **data );
   void getAccDistributionData( BFData **data );

private:
   VerificationStringProcessor *pVerificationStringProcessor;
};

