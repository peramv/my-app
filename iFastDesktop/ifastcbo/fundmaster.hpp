#pragma once
#define DISABLE_MACRO_REDEFINITION_WARNINGS 1
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
// ^FILE   : FundMaster.hpp
// ^AUTHOR : Mike Metzger
// ^DATE   : March 5, 1999
//
// ^CLASS    : FundMaster
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

class ReinvestPurchaseSchedule;

class IFASTCBO_LINKAGE FundMaster : public MFCanBFCbo, private boost::noncopyable
{
public:
   FundMaster (BFAbstractCBO &parent);
   virtual ~FundMaster();

   SEVERITY init (const BFData &viewData);
   SEVERITY cappedFundRule (const DString &dstrEffectDate, const BFDataGroupId& idDataGroup );
   bool isCappedFund (const DString &dstrEffectDate, const BFDataGroupId &idDataGroup );
   SEVERITY getReinvestPurchaseSchedule ( ReinvestPurchaseSchedule *&pReinvestPurchaseSchedule,
                                          const BFDataGroupId& idDataGroup
                                        );
   void getField( const BFFieldId& idField, DString & strValue, const BFDataGroupId& idDataGroup, bool formattedReturn = false ) const;
};

///#endif
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/fundmaster.hpp-arc  $
//
//   Rev 1.15   Jun 06 2012 14:06:24   if991250
//INA: using French fund names when French locales are on
//
//   Rev 1.14   Nov 14 2004 14:42:46   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.13   Nov 04 2004 17:37:42   popescu
//PET 1117/06, Trade processing
//
//   Rev 1.12   May 11 2004 15:49:22   popescu
//PET 985, FN 01, LSIF Trade Entry, added handy methods to fund master list, to check whether a fund is LSIF/Money Market, GIC
//
//   Rev 1.11   Apr 14 2004 14:54:00   VADEANUM
//PTS 10029064/10028846 - Cash Date.
//
//   Rev 1.10   Mar 21 2003 18:11:56   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.9   Feb 06 2003 18:21:50   HSUCHIN
//added method iscappedfund
//
//   Rev 1.8   Oct 09 2002 23:54:34   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.7   Aug 29 2002 12:52:32   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.6   Jun 07 2002 17:37:04   KOVACSRO
//Removed doFormatField
//
//   Rev 1.5   22 May 2002 18:20:56   PURDYECH
//BFData Implementation
//
//   Rev 1.4   19 Mar 2002 13:17:10   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.3   20 Feb 2002 17:54:20   WINNIE
//add capped fund logic : logic to be removed from systematic and trade
//
//   Rev 1.2   10 May 2001 14:28:52   HSUCHIN
//Sync up with SSB (1.0.1.0)
//
//   Rev 1.1   03 May 2001 14:04:14   SMITHDAV
//Session management restructuring.
//
//   Rev 1.0   Aug 03 2000 16:39:52   BUZILA
//Initial revision.
 * 
*/