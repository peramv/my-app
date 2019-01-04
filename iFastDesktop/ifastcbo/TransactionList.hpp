#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2004 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : TransactionList.hpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 03/22/99
//
// ^CLASS    : TransactionList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
#include <set>


#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class TransactionDetails;

class IFASTCBO_LINKAGE TransactionList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   TransactionList( BFAbstractCBO &parent );
   virtual ~TransactionList();

   // Initialize function
   SEVERITY init( const DString& AccountNum,
                  const DString& FundCode,
                  const DString& ClassCode,
                  const DString& NumEntry,
                  const DString& AllFundMode,
                  const DString& ReqTransid = NULL_STRING,
                  const DString& UseDateFlag = I_("N"),
                  const DString& FromDate = NULL_STRING,
                  const DString& ToDate = NULL_STRING,
                  const DString& dstrTrack= I_("N"),
                  const DString& dstrPageName = NULL_STRING,
                  const DString& dstrNextKey = NULL_STRING,
				  const DString& dstrExcludeReversal = I_( "N" ),
				  const DString& dstrTransType = NULL_STRING,
				  const DString& dstrEUSDScope = NULL_STRING,
				  const DString& dstrSearchType = NULL_STRING,
				  bool reciveAll = false );
   //used for transaction search
   SEVERITY initSearch( 
                  const DString& strSearchType,
						const DString& strAccountNum,
                  const DString& strTransNum,
                  const DString& strWireOrdNum, 
                  const DString& strNetworkID, 
                  const DString& strExtTransNum, 
                  const DString& strSendRefNum,
                  const DString& strMasterRefNum, 
                  const DString& strPartRefNum,
                  const DString& strFromDate, 
                  const DString& strToDate,
						const DString& strExternalIdType,
						const DString& strExternalId,
						const DString& strAltAccount,
						const DString& strFundIDType,
						const DString& strFundIDValue,
						const DString& strTransType,
						const DString& strUnits,
						const DString& strNSCCControlNumber,
						const DString& strTradeDate = NULL_STRING,
						const DString& strFundCode = NULL_STRING,
						const DString& strClassCode = NULL_STRING,
                  const DString& dstrTrack= I_("N"),
                  const DString& dstrPageName = NULL_STRING);
    //used for advnaced historical trade serach..Has got more customized filtering 
    //used for transaction search
   SEVERITY initSearch(	const DString& dstrSearchType,
						const DString& dstrAccountNum,
						const DString& dstrTransNum,
						const DString& dstrWireOrdNum, 
						const DString& dstrNetworkID, 
						const DString& dstrExtTransNum, 
						const DString& dstrSendRefNum,
						const DString& dstrMasterRefNum, 
						const DString& dstrPartRefNum,
						const DString& dstrFromDate, 
						const DString& dstrToDate,
						const DString& dstrExternalIdType,
						const DString& dstrExternalId,
						const DString& dstrAltAccount,
						const DString& dstrFundIDType,
						const DString& dstrFundIDValue,
						const DString& dstrTransType,
						const DString& dstrUnits,
						const DString& dstrNSCCControlNumber,
						const DString& dstrTradeDate,
						const DString& dstrFundCode,
						const DString& dstrClassCode,
						const DString& dstrAllFundMode,
						const DString& dstrTradeStatus,
						const DString& dstrEUSDScope,
						const DString& dstrReportingCurrency,
						const DString& dstrExcludeReversal   = I_("N") ,
						const DString& dstrExcludeCancelled  = I_("N") ,
						const DString& dstrTrack             = I_("N") ,
						const DString& dstrPageName          = NULL_STRING);

   SEVERITY anotherAccount( DString& AccountNum,
                            DString& FundCode,
                            DString& ClassCode,
                            DString& NumEntry,
                            DString& AllFundMode,
                            const DString& UseDateFlag = I_("N"),
                            const DString& FromDate = NULL_STRING,
                            const DString& ToDate = NULL_STRING,
                            const DString& dstrTrack= I_("N"),
                            const DString& dstrPageName = NULL_STRING );

   SEVERITY getMore();

   TransactionDetails* getItem( const DString& strObjLabel, const BFDataGroupId& idDataGroup );

   SEVERITY init();
   void getStrKey( DString& dstKey, const DString& dstrFund, 
                   const DString& dstrClass, const DString& dstrTransType=NULL_STRING);
   void getStrKey( DString& dstKey, const DString& dstrFund, const DString& dstrClass, 
								 const DString& dstrTransNum, const DString& dstrTransType);
   void getStrKey( DString &strKey, const BFData *data = NULL );
   bool fundclasstrxExist ( const DString& dstrFund, const DString& dstrClass, const DString& dstrTransType,
                            const BFDataGroupId& idDataGroup );

protected:
   virtual SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
   SEVERITY doCreateNewObject(BFCBO *& pBase, DString & strKey );
private:
   BFData _queryData;
   std::set< DString > setDuplication;
};

///#endif
//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TransactionList.hpp-arc  $
 * 
 *    Rev 1.27   Mar 02 2006 16:28:28   jankovii
 * PET 2072 FN01- NSCC Control Number.
 * 
 *    Rev 1.26   Nov 04 2005 15:36:28   ZHANGCEL
 * PET1286 FN01 -- Fix signature problem of the initSearch()
 * 
 *    Rev 1.25   Nov 04 2005 10:59:12   ZHANGCEL
 * PET 1286  FN01 -- Add TradeDate search related issue
 * 
 *    Rev 1.24   Sep 20 2005 12:51:46   fengyong
 * Incident 402113 - In Transaction history screen:
 * All fund mode and select fund combo box, do not need check transId.
 * 
 *    Rev 1.23   Jul 19 2005 16:55:46   porteanm
 * PET1171 EUSD 1B - Added parameters to init().
 * 
 *    Rev 1.22   Jul 06 2005 16:29:38   porteanm
 * PET1171 EUSD 1B - Added parameters to init().
 * 
 *    Rev 1.21   Feb 03 2005 13:38:52   Fengyong
 * PET1117 FN66 - Trade reconcile API
 * 
 *    Rev 1.20   Nov 14 2004 14:58:22   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.19   Sep 07 2004 14:29:34   VADEANUM
 * PET 1094 FN4 - Activest Bank File Interface.
 * 
 *    Rev 1.18   May 11 2004 11:07:48   ZHANGCEL
 * PET1046_FN02 -- Trade Search by account enhancement
 * 
 *    Rev 1.17   Apr 10 2003 09:32:08   FENGYONG
 * Add getstrKey
 * 
 *    Rev 1.16   Mar 21 2003 18:27:46   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.15   Mar 03 2003 09:45:44   KOVACSRO
 * Added initSearch
 * 
 *    Rev 1.14   Oct 09 2002 23:55:12   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.13   Aug 29 2002 12:53:58   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.12   13 Jun 2002 14:40:42   YINGZ
 * add reqtransid to support settlement
 * 
 *    Rev 1.11   22 May 2002 22:22:28   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.10   22 May 2002 18:19:12   PURDYECH
 * BFData Implementation
 */
