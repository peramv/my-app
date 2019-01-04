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
// ^FILE   : FundMasterList.hpp
// ^AUTHOR : Mike Metzger
// ^DATE   : March 5, 1999
//
// ^CLASS    : FundMasterList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
///#endif

class FundMaster;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE FundMasterList : public MFCanBFCbo, private boost::noncopyable
{
public:
   static void buildKey(const DString& strFund, DString &strKeyOut);
public:
   FundMasterList (BFAbstractCBO &parent);
   virtual ~FundMasterList();

   SEVERITY init( const DString &dstrTrack = I_("N"), 
                  const DString &dstrPageName = NULL_STRING);
   bool getFundMaster ( const DString &fundCode, 
                        const BFDataGroupId &idDataGroup, 
                        FundMaster *&pFundMaster);
//handy methods
   bool isMoneyMarketFund (const DString &fundCode);
   bool isGICFund (const DString &dfundCode);
   bool isMPSFund (const DString &fundCode);
   bool isLSIFFund (const DString &fundCode);
   bool isMutualFund (const DString &fundCode);
   bool isHedgeFund (const DString &fundCode);
   bool isWrapFund (const DString &fundCode);
   bool isSegregatedFund  (const DString &fundCode);
   bool isGIAFund (const DString &fundCode);
   bool isDIFFund (const DString &fundCode);
   bool isSEGFund (const DString &fundCode);
   bool isDepotFund (const DString &fundCode);
   bool is3rdPartyFund (const DString &fundCode);
   bool isUpToCertificateSpecialFund (const DString &fundCode);
   bool isGlobalCertificateSpecialFund (const DString &fundCode);
   bool isPUEVCapableFund (const DString &fundCode);
   bool isInvestroCapableFund (const DString &fundCode);
   SEVERITY getFundName ( const DString &fundCode,
                          DString &fundName);
   SEVERITY getFundName ( const DString &fundCode,
                          const BFFieldId &nameFieldId,
                          DString &fundName);
                           
   // check if dstrFundCode exist in the list
   bool IsFundExist(const DString& dstrFundCode, const BFDataGroupId& idDataGroup);
   //check if dstrFundCode is validate for the given effective date
   bool IsFundValidAtDate(const DString &dstrFundCode, 
                          const DString &dstrEffectiveDate, 
                          const BFDataGroupId &idDataGroup);
   DString getTaxType (const DString &fundCode);
   DString getPendTrdContractList ( const DString &fundCode );
 //P0186486FN09 - Employee and Agent Account Gap#8A
   DString getFundCategory(const DString &fundCode){ return fundCategory(fundCode);}; 
   
protected:
   virtual void getStrKey ( DString &strKey,
                            const BFData *data);
   virtual SEVERITY doCreateObject ( const BFData &data, 
                                     BFCBO *&pObjOut);
private:
   DString fundType (const DString &fundCode);
   DString otherFundType (const DString &fundCode);
   DString fundCategory (const DString &fundCode);
};

///#endif
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/fundmasterlist.hpp-arc  $
 * 
 *    Rev 1.30   Apr 06 2012 22:20:02   panatcha
 *  P0186486FN09 - Employee and Agent Account Gap#8A
 * 
 *    Rev 1.29   Mar 05 2012 11:49:22   dchatcha
 * P0186484 FN05 - SEG Trade Processing.
 * 
 *    Rev 1.28   Jan 20 2012 15:41:54   wp040027
 * P0188394_Performance Fees - Order Entry
 * 
 *    Rev 1.27   Dec 14 2011 15:45:26   jankovii
 * P0186477 FN03- GIA Maturity/Cash Sweep Instructions
 * 
 *    Rev 1.26   Oct 19 2011 22:22:22   popescu
 * P0186477/03 - GIA Trading Money In - prep work
 * 
 *    Rev 1.25   24 Jul 2008 12:00:58   popescu
 * Incident - 1190617 - set all the data init calls to be asynch
 * 
 *    Rev 1.24   Sep 16 2007 15:39:46   jankovii
 * IN #990336 - User is unable to process manual/adhoc MFR trades.
 * 
 *    Rev 1.23   Feb 24 2005 19:07:04   popescu
 * Incident# 243353, added boolean to flag if list has been fully loaded
 * 
 *    Rev 1.22   Nov 17 2004 16:15:06   popescu
 * PET 1117/06, Trade processing fees
 * 
 *    Rev 1.21   Nov 17 2004 15:20:20   popescu
 * PET 1117/56, removed 'getField' method at the fund master list level, added handy methods to determine if a fund is PUEV/Investro capabele, and getters for fund names
 * 
 *    Rev 1.20   Nov 14 2004 14:42:50   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.19   Nov 04 2004 17:37:46   popescu
 * PET 1117/06, Trade processing
 * 
 *    Rev 1.18   May 19 2004 14:24:36   popescu
 * PET 985, FN 01, added convenient methods to check for fund category and type
 * 
 *    Rev 1.17   May 11 2004 15:49:26   popescu
 * PET 985, FN 01, LSIF Trade Entry, added handy methods to fund master list, to check whether a fund is LSIF/Money Market, GIC
 * 
 *    Rev 1.16   Apr 14 2004 14:55:16   VADEANUM
 * PTS 10029064/10028846 - Cash Date.
 * 
 *    Rev 1.15   Oct 14 2003 17:12:22   HSUCHIN
 * PTS 10022556 - added new method isMPSFund and additional logic to isGICFund.
 * 
 *    Rev 1.14   Mar 21 2003 18:12:02   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.13   Oct 09 2002 23:54:34   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.12   Aug 29 2002 12:52:34   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.11   22 May 2002 18:20:58   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.10   19 Mar 2002 13:17:10   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.9   20 Feb 2002 17:56:42   WINNIE
 * add getfundmaster object method
 * 
 *    Rev 1.8   03 May 2001 14:04:14   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.7   Jan 18 2001 16:12:00   YINGBAOL
 * add etrack
 * 
 *    Rev 1.6   Jan 10 2001 18:02:46   WINNIE
 * add isGICFund method
 * 
 *    Rev 1.5   Nov 22 2000 10:30:32   JANKAREN
 * Add isCashDateUptable method
 * 
 *    Rev 1.4   Sep 11 2000 10:44:30   YINGBAOL
 * add IsFundExist and IsFundValidAtDate methods
 * 
 *    Rev 1.3   Aug 15 2000 10:14:06   WINNIE
 * Add Getfield method
 * 
 *    Rev 1.2   Aug 03 2000 16:41:22   BUZILA
 * locale stuff
 * 
*/