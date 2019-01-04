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
// ^FILE   : TradeVerificationList.hpp
// ^AUTHOR : Robbins Kuriakose
// ^DATE   : JuLY 22 2014
//
//********************************************************************************
#include <ifastcbo\mfcancbo.hpp>
#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE TradeVerificationList : public MFCanBFCbo ,private boost::noncopyable
{
public:
   TradeVerificationList( BFAbstractCBO &parent );
   virtual ~TradeVerificationList();
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
   SEVERITY init(const BFDataGroupId& idDataGroup,
                 const DString& dstrTrack,
                 const DString& dstrPageName );
   SEVERITY initSearch(   const DString& strSearchType,
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
				          const DString& dstrTransType = I_("ALL") ,
                          const DString& dstrExcludeVerifiedTrades = I_("Y"),
                          const DString& dstrUserID = NULL_STRING,
                          const DString& dstrExcludeAggrOrd = I_("Y"),
						  const DString& dstrSponsorCode = NULL_STRING,
						  const DString& dstrPlatform = NULL_STRING); 


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
   int getNoOfPreviouslyRequestedItems();
   /*void getStrKey( DString& dstKey, const DString& dstrFund, 
                   const DString& dstrClass, const DString& dstrTransType );*/
   // copy constructor
   TradeVerificationList( const TradeVerificationList& copy ); //not implemented
   // = Operator
   TradeVerificationList& operator= ( const TradeVerificationList& copy );//not implemented   
   void prepareParameter(const BFDataGroupId& idDataGroup);
   SEVERITY markAllTradeToVerifyOrReject( const BFDataGroupId& idDataGroup );
   BFData& getRequestData(){ return(_requestData);}
   bool bMoreThanOne( const BFDataGroupId& idDataGroup );
   void clearUserActionFlag(const BFDataGroupId& idDataGroup);

protected:
   virtual SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
   
private:
   virtual void getStrKey( DString &strKey, const BFData *data = NULL );
   void markAllTradeToVerify( const BFDataGroupId& idDataGroup );
   void markAllTradeToDelete( const BFDataGroupId& idDataGroup );
   void clearAllFlags( const BFDataGroupId& idDataGroup );
   BFData _requestData;
   int nRequestedNoOfItems;

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/TradeVerificationProcess.cpp-arc  $
// 
//    Rev 1.0  22 July 2014
// Initial revision.
*/

