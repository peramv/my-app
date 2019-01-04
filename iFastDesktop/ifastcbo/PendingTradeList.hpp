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
// ^FILE   : PendingTradeList.hpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 04/29/99
//
// ^CLASS    : PendingTradeList
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

class IFASTCBO_LINKAGE PendingTradeList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   PendingTradeList( BFAbstractCBO &parent );
   virtual ~PendingTradeList();

   /**
   * strOverrideRepeats should be less or equal to MaxRepeatCount (that's a backend rule)
    * if called with default -1 for strOverrideRepeats, the list will contain up to maxRepeatCount (25) elements
    * if called with 0 for strOverrideRepeats, the list will contain all the existing elements
    * if called with a positive number for strOverrideRepeats, the list will contain up to that number of elements
  */
   SEVERITY init( DString& AccountNum,
                  DString& strOverrideRepeats = DString(I_("-1")),
                  const DString& dstrTrack= I_("N"),
                  const DString& dstrPageName = NULL_STRING );
   /**
   * strOverrideRepeats should be less or equal to MaxRepeatCount (that's a backend rule)
    * if called with default -1 for strOverrideRepeats, the list will contain up to maxRepeatCount (25) elements
    * if called with 0 for strOverrideRepeats, the list will contain all the existing elements
    * if called with a positive number for strOverrideRepeats, the list will contain up to that number of elements
   */
   SEVERITY init( DString& AccountNum,
                  DString& BrokerCode, 
                  DString& BranchCode, 
                  DString& SlsrepCode, 
                  DString& strOverrideRepeats = DString(I_("-1")),
                  const DString& dstrTrack= I_("N"),
                  const DString& dstrPageName = NULL_STRING);
   //used for pending trade search
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
                  const DString& strNSCCControlNumber,
                  const DString& rebook = I_("N"),
                  const DString& dstrTrack= I_("N"),
                  const DString& dstrPageName = NULL_STRING,
				  const DString& dstrFundCode = NULL_STRING,
				  const DString& dstrClassCode = NULL_STRING,
				  const DString& dstrTransType = I_("ALL"),
                  const DString& dstrExcludeVerifiedTrade = I_("N"),
                  const DString& dstrUserID = NULL_STRING ); 

   SEVERITY anotherAccount( DString& AccountNum,DString& NumEntry );

   /**
   * strOverrideRepeats should be less or equal to MaxRepeatCount (that's a backend rule)
    * if called with default -1 for nNoOfNewItems, the list could grow up to maxRepeatCount (25) elements
    * if called with 0 for nNoOfNewItems, the list will grow to contain all the existing elements
    * if called with a positive number for nNoOfNewItems, the list could grow up to the specified number of elements
   */
   SEVERITY getMore(int nNoOfNewItems = -1);
   void getItem( const DString& strObjLabel, 
                 const BFDataGroupId& idDataGroup, 
                 const DString& IgnoreActiveBatch = I_("N"),
                 const DString& rebook = I_("N"));

   SEVERITY init();

/*   void getStrKey( DString& dstKey, const DString& dstrFund, 
                   const DString& dstrClass, const DString& dstrTransType,
                   const DString& dstrAmount, const DString& dstrAmtType );*/
   void buildFCKey( DString& dstKey, const DString& dstrFund, const DString& dstrClass );
   void buildFCTAAKey( DString& dstKey, const DString& dstrFund, const DString& dstrClass, 
                   const DString& dstrTransType, const DString& dstrAmtType );

   bool fundclassExist ( const DString& dstrFund, const DString& dstrClass, 
                         const BFDataGroupId& idDataGroup, const DString& TransType = NULL_STRING );
   bool dupTradeExist ( const DString& dstrFund, const DString& dstrClass, 
                        const DString& dstrTransType, const DString& dstrAmount, 
                        const DString& dstrAmtType, const DString& dstrTransNum, const BFDataGroupId& idDataGroup );
   int getNoOfPreviouslyRequestedItems();
   void getStrKey( DString& dstKey, const DString& dstrFund, 
                   const DString& dstrClass, const DString& dstrTransType );
   bool redemptionExist ( const DString& dstrFund, const DString& dstrClass, const BFDataGroupId& idDataGroup );
   virtual void getStrKey( DString &strKey, const BFData *data = NULL );
   bool PendingPACExist(const BFDataGroupId& idDataGroup );
   bool hasNonAMSFunds(const BFDataGroupId& idDataGroup);

protected:
   virtual SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );

private:
   BFData _requestData;
   DString _AccountNum;
   int nRequestedNoOfItems;

};

///#endif

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/PendingTradeList.hpp-arc  $
 * 
 *    Rev 1.30   Feb 02 2009 14:33:48   daechach
 * Revision Controls Entries.
 *
 *
 */

