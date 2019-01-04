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
// ^FILE   : ReinvestPurchaseSchedule.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : October 2004
//
// ^CLASS    : ReinvestPurchaseSchedule
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

class IFASTCBO_LINKAGE ReinvestPurchaseSchedule : public MFCanBFCbo, private boost::noncopyable
{
public:
   static void buildKey (const DString &calendarYear, DString &strKeyOut);
public:
   ReinvestPurchaseSchedule (BFAbstractCBO &parent);
   virtual ~ReinvestPurchaseSchedule ();
   SEVERITY init ( const DString &fundCode,
                   const DString &dstrTrack = I_("N"), 
                   const DString &dstrPageName = NULL_STRING
                 );
   bool isDateWithinReinvestmentSchedule ( const DString &tradeDate,
                                           const BFDataGroupId &idDataGroup
                                         );
protected:
   virtual void getStrKey  (DString &strKey, const BFData *data);
};

///#endif
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ReinvestPurchaseSchedule.hpp-arc  $
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