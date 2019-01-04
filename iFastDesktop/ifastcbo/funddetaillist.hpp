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
// ^FILE   : FundDetailList.hpp
// ^AUTHOR : Mike Metzger
// ^DATE   : March 5, 1999
//
// ^CLASS    : FundDetailList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

class FundDetail;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

typedef std::map< DString, FundDetail* > FUND_MAP;
typedef FUND_MAP::iterator FUND_MAP_ITER;
typedef FUND_MAP::value_type FUND_MAP_VALUE_TYPE;

class IFASTCBO_LINKAGE FundDetailList : public MFCanBFCbo, private boost::noncopyable
{
public:
   FundDetailList( BFAbstractCBO &parent );
   virtual ~FundDetailList();

   SEVERITY init( const DString& dstrTrack= I_("N"), const DString& dstrPageName = NULL_STRING );
   SEVERITY init( const DString& dstrSearchType,
                  const DString& dstrFundCode,
                  const DString& dstrClassCode,
                  const DString& dstrFundName,
                  const DString& dstrFundNumber,
                  const DString& dstrWKN,
                  const DString& dstrISIN,
                  const DString& dstrTrack= I_("N"), 
                  const DString& dstrPageName = NULL_STRING );

   virtual void getStrKey ( DString& strKey, const BFData *data );
   static void getStrKey( DString& strKey, const DString&  dstFundCode, const DString&  dstClassCode );

   void getField( const DString& strFundCode, const DString& strClassCode,
                  const BFFieldId& idField, DString& strValue, 
                  const BFDataGroupId& idDataGroup, bool formattedReturn ) ;

   bool IsFundClassExist( const DString& dstrFundCode, const DString& dstrClassCode, const BFDataGroupId& idDataGroup );

   bool IsExchInFeeExist( const DString& dstrFundCode, const DString& dstrClassCode, const BFDataGroupId& idDataGroup ); 

   bool isFOFFund( const DString& dstrFundCode, const DString& dstrClassCode, const BFDataGroupId& idDataGroup ); 

   bool IsFundValidAtDate(const DString& dstrFundCode,
                          const DString& dstrClassCode,
                          const DString& dstrEffectiveDate, 
                          const BFDataGroupId& idDataGroup );

   bool getFundDetail( const DString& dstrFundCode, 
                       const DString& dstrClassCode, 
                       const BFDataGroupId& idDataGroup, 
                       FundDetail *&pFundDetail ); 
                      
   FundDetail* getFundDetailByWKN( const DString& dstrWKN );               // From BF::Host
   FundDetail* FundDetailList::getFundDetailByLFC( const DString& dstrLFC );
   FundDetail* getFundDetailByISIN( const DString& dstrISIN );             // From BF::HOST
   FundDetail* getFundDetailByFundNumber( const DString& dstrFundNumber ); // From BF::HOST                     

   SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
   bool isSameTradeDateLag(const DString& FrFundCode, const DString& FrClassCode, 
                           const DString& ToFundCode, const DString& ToClassCode);

   //returns true if at least one fund/class has FCRebalElig = 'Y'
   bool isFundFCRebalElig(const DString& strFundCode);
   //returns false if there is at least one fund/class for which StopSysGenTrnfrIn = 'N'
   bool isStopSysGenTrfrIn(const DString& strFundCode);
   SEVERITY getMore();
	bool isInScope (const DString& dstrFundCode, const DString &dstrClassCode, const DString &dstrTradeDate) ;
	bool isLookThru (const DString& dstrFundCode, const DString &dstrClassCode, const DString &dstrTradeDate) ;
	FundDetail* getFundDetailByTDCC ( const DString& dstrTDCC  ); 
    FundDetail* getFundDetailByCUSIP( const DString& dstrCUSIP ); 
    FundDetail* getFundDetailByVAL  ( const DString& dstrVAL   ); 
	SEVERITY insertFundIdValues(DString& dstrFundIDValues, FundDetail *ptrFundDetail,const BFDataGroupId& idDataGroup);

protected:

private:
   bool _bDoneLoading;
   BFData   m_requestData;
   FUND_MAP m_FundNumberMap;
   FUND_MAP m_WKNMap;
   FUND_MAP m_ISINMap;
   FUND_MAP m_VALORENMap;
   FUND_MAP m_CUSIPMap;
   FUND_MAP m_TDCCMap;
   FUND_MAP m_LFCMap;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/funddetaillist.hpp-arc  $
 * 
 *    Rev 1.29   24 Jul 2008 12:00:54   popescu
 * Incident - 1190617 - set all the data init calls to be asynch
 * 
 *    Rev 1.28   Jun 25 2007 11:35:38   porteanm
 * PET 2360 FN02 - Added isFOF()
 * 
 *    Rev 1.27   Nov 29 2005 15:23:32   AGUILAAM
 * PET_1228_FN02: EUSD Phase 2
 * 
 *    Rev 1.26   Feb 24 2005 19:06:56   popescu
 * Incident# 243353, added boolean to flag if list has been fully loaded
 * 
 *    Rev 1.25   Nov 29 2004 13:23:40   hernando
 * PET1117 - Tuning Project - Revised use of FundDetailList.
 * 
 *    Rev 1.24   Nov 14 2004 14:41:58   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.23   Sep 09 2004 11:39:00   HERNANDO
 * PET1117 FN22 - WKN & ISIN Enhancement.
 * 
 *    Rev 1.22   Mar 21 2003 18:11:04   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.21   Jan 14 2003 17:28:36   KOVACSRO
 * Added isFundFCRebalElig() and  isStopSysGenTrfrIn()
 * 
 *    Rev 1.20   Oct 09 2002 23:54:32   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.19   Aug 29 2002 12:52:32   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.18   22 May 2002 18:20:56   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.17   19 Mar 2002 13:17:08   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.16   12 Dec 2001 16:08:58   KOVACSRO
 * Added isSameTradeDateLag()
 * 
 *    Rev 1.15   Jun 16 2001 15:34:34   ZHANGCEL
 * Added a new function isExchInFeeExist()
 * 
 *    Rev 1.14   03 May 2001 14:04:12   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.13   Feb 06 2001 09:54:14   WINNIE
 * uncomment isFundClassExists
 * 
 *    Rev 1.12   Jan 31 2001 11:30:58   JANKAREN
 * Add getFundDetail & doCreateObject methods. Moved fundClassForPlanType, checkMinInitAmt, checkMinSubAmt methods to FundDetail CBO
 * 
 *    Rev 1.11   Jan 30 2001 10:07:40   VASILEAD
 * Added workSessionId for getUnitPrice()
 * 
 *    Rev 1.10   Jan 18 2001 16:11:58   YINGBAOL
 * add etrack
 * 
 *    Rev 1.9   Jan 12 2001 13:37:26   ZHANGCEL
 * Added a new funtion getUnitPrice()
 * 
 *    Rev 1.8   Dec 20 2000 09:44:40   WINNIE
 * New methods to check minimum at fund level
 * 
 *    Rev 1.7   Dec 04 2000 13:21:18   VASILEAD
 * Made building the key a static function for the class
 * 
 *    Rev 1.6   Nov 17 2000 11:40:02   YINGZ
 * make the return value of fundClassForPlanType right
 * 
 *    Rev 1.5   Nov 17 2000 11:22:28   YINGZ
 * add fundClassForPlanType to make it compilable
 * 
 *    Rev 1.4   Sep 11 2000 10:44:28   YINGBAOL
 * add IsFundExist and IsFundValidAtDate methods
 * 
 *    Rev 1.4   Sep 01 2000 14:34:04   ZHANGCEL
 * GetField problem
 * 
 *    Rev 1.3   Aug 15 2000 10:12:52   WINNIE
 * Add Getfield method
 * 
 *    Rev 1.2   Apr 20 2000 16:38:44   BUZILA
 * changed to MgmtCoId
 * 
 *    Rev 1.1   Apr 13 2000 10:39:32   BUZILA
 * added :getStrKey( strKey, dstFundCode, dstClassCode )
 * 
 *    Rev 1.0   Feb 15 2000 10:59:58   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.7   Jan 05 2000 20:10:46   BUZILA
 * adding list flag
 * 
 *    Rev 1.6   Dec 12 1999 16:25:22   POPESCUS
 * Xchgdata issue; create and delete the object in the CBO
// 
*/