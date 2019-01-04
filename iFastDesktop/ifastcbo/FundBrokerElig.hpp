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
//    Copyright 1998 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : FundBrokerElig.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : November 2004
//
// ^CLASS    : FundBrokerElig
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

class IFASTCBO_LINKAGE FundBrokerElig : public MFCanBFCbo, private boost::noncopyable
{
public:
   static void buildKey ( const DString &fundBrokerCode, 
                          const DString &fundCode, 
                          DString &strKeyOut
                        );
public:
   FundBrokerElig (BFAbstractCBO &parent);
   virtual ~FundBrokerElig ();
   SEVERITY init ( const DString &fundBrokerCode,
                   const DString &fundCode = NULL_STRING,
                   const DString &dstrTrack = I_("N"), 
                   const DString &dstrPageName = NULL_STRING
                 );
   bool isFundBrokerEligToTradeFund ( const DString &fundBrokerCode, 
                                      const DString &fundCode, 
                                      const BFDataGroupId &idDataGroup
                                    );
protected:
   virtual void getStrKey  (DString &strKey, const BFData *data);
};

///#endif
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FundBrokerElig.hpp-arc  $
//
//   Rev 1.0   Nov 18 2004 11:46:18   popescu
//Initial revision.
//
//
*/