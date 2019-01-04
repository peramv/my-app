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
// ^FILE   : FundBrokerDefault.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : November 2004
//
// ^CLASS    : FundBrokerDefault
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

class IFASTCBO_LINKAGE FundBrokerDefault : public MFCanBFCbo, private boost::noncopyable
{
public:
   FundBrokerDefault (BFAbstractCBO &parent);
   virtual ~FundBrokerDefault ();
   SEVERITY init ( const DString &fundCode,
                   const DString &accountNum,
                   const DString &dstrTrack = I_("N"), 
                   const DString &dstrPageName = NULL_STRING
                 );
   SEVERITY getDefaultFundBrokerCode ( DString &defaultFundBrokerCode, 
									   DString &dstrFdBrokerDefaultLevel,
                                       const BFDataGroupId &idDataGroup
                                     );
protected:
};

///#endif
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FundBrokerDefault.hpp-arc  $
//
//   Rev 1.2   Jul 10 2012 18:18:04   wp040039
//PETP0201166- SSBG- Fund Broker validation
//
//   Rev 1.1   Dec 08 2004 16:46:42   popescu
//PET 1117/56 fund broker defaul view 325, proved to be non-repeatable after all
//
//   Rev 1.0   Nov 18 2004 11:46:22   popescu
//Initial revision.
//
//   Rev 1.2   Nov 14 2004 14:51:48   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.1   Nov 04 2004 17:38:28   popescu
//PET 1117/06, Trade processing
//
//   Rev 1.0   Oct 29 2004 20:27:38   popescu
//Initial revision.
//
*/