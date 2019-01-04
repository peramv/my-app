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
//    Copyright 2000 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : FundToList.hpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : March 31, 2000
//
// ^CLASS    : FundToList
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


class IFASTCBO_LINKAGE FundToList : public MFCanBFCbo, private boost::noncopyable
{
public:
   FundToList( BFAbstractCBO &parent );
   virtual ~FundToList();
   bool isTransferAllowed(DString& FundCode,DString& ClassCode, 
                          DString& FundToCode,
                          DString& ClassToCode,
                          const DString& dstrTrack = I_("N"),
                          const DString& dstrPageName = NULL_STRING );

   bool isTransferAllowed(DString& FundCode,
                          DString& ClassCode, 
                          DString& FundToCode,
                          DString& ClassToCode, 
                          DString& dstrFullPartial,
                          const DString& dstrTrack = I_("N"),
                          const DString& dstrPageName = NULL_STRING);

   bool isBuySell (DString& FundCode, 
                   DString& ClassCode,
                   DString& FundToCode,
                   DString& ClassToCode,
                   const DString& dstrTrack = I_("N"),
                   const DString& dstrPageName = NULL_STRING);

   DString getShortTermFee(DString& FundCode, 
                           DString& ClassCode,
                           DString& FundToCode,
                           DString& ClassToCode,
                           const DString& dstrTrack = I_("N"),
                           const DString& dstrPageName = NULL_STRING);

   bool isExchangeAllowed(const DString& frFund,
                          const DString& frClass,
                          const DString& toFund,
                          const DString& toClass, 
                          const DString& dstrTrack = I_("N"),
                          const DString& dstrPageName = NULL_STRING);

   DString getApplySrcOfFund(const DString& frFund,
							 const DString& frClass,
                             const DString& toFund,
                             const DString& toClass, 
                             const DString& dstrTrack = I_("N"),
                             const DString& dstrPageName = NULL_STRING);


private:
   bool isSameFundClass(DString& frFund,DString& frClass, DString& toFund,DString& toClass);
   SEVERITY init( );

   DString frFund_ ,
      frClass_,
      toFund_, 
      toClass_, 
      track_,
      pageName_,
      buySell_, 
      fullPartial_,
      shortTernFee_, 
      tradeAllowed_,
	  applySrcOfFund_;

   bool bHasRecord_;
};

///#endif

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FundToList.hpp-arc  $
//
//   Rev 1.21   Nov 24 2004 14:16:02   popescu
//PET 1117, passed the correct request object to Receive, and fixed typo
//
//   Rev 1.20   Nov 18 2004 14:58:32   YINGBAOL
//PET1117: performance tunning, add getShotTermFee method
//
//   Rev 1.19   Nov 18 2004 13:28:14   YINGBAOL
//PET1117: Perfermance Tunning
//
//   Rev 1.18   Nov 14 2004 14:43:20   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.17   Mar 21 2003 18:12:16   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.16   Jan 16 2003 18:55:34   WINNIE
//Add new method to take parameter to check if partial or full exchange is allowed. Enhancement for DCAF fund
//
//   Rev 1.15   Oct 09 2002 23:54:34   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.14   Aug 29 2002 12:52:34   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.13   22 May 2002 18:20:58   PURDYECH
//BFData Implementation
//
//   Rev 1.12   19 Mar 2002 13:17:14   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.11   20 Nov 2001 19:48:36   WINNIE
//new method isBuySell for NFEL enhancement : fee only charge when BuySell = Y
//
//   Rev 1.10   03 May 2001 14:04:16   SMITHDAV
//Session management restructuring.
//
//   Rev 1.9   Mar 21 2001 15:07:12   YINGZ
//delete one of the init
//
//   Rev 1.8   Mar 21 2001 13:00:32   FENGYONG
//get fundtolist by fromfund,fromclass or sponsorcode
//
//   Rev 1.7   Mar 12 2001 14:59:42   FENGYONG
//Getlist by from sponsorcode
//
//   Rev 1.6   Mar 10 2001 15:14:30   WINNIE
//fund detail own the fundlist instead having master list : to improve performance for transfer/exchange
//
//   Rev 1.5   Jan 18 2001 16:12:08   YINGBAOL
//add etrack
//
//   Rev 1.4   Dec 04 2000 13:21:14   VASILEAD
//Made building the key a static function for the class
//
//   Rev 1.3   May 31 2000 16:16:30   YINGBAOL
//more validation added
//
//   Rev 1.2   Apr 15 2000 15:26:18   WINNIE
//fix for index set up in funtolist; fix allowable exchange edit chk; fix account balance ;
//
//   Rev 1.1   Apr 07 2000 18:24:16   WINNIE
//add index
//
//   Rev 1.0   Apr 03 2000 08:50:16   BUZILA
//Initial revision.
 * 
*/