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
//    Copyright 1999 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : TransFeeList.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : July 2004
//
// ^CLASS    : TransFeeList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

//Forward declarations
class TransFee;
class TransFeeContext;

class IFASTCBO_LINKAGE TransFeeList : public MFCanBFCbo, public BFObserver, private boost::noncopyable
{
   friend class Trade;
public:
   static void buildKey (const DString &feeCode, const DString& fundCode, const DString& classCode, DString &strKey);
   bool getForcingRefresh(){return _forcingRefresh;}
   void setForcingRefresh(bool forcingRefresh) {_forcingRefresh = forcingRefresh;}
public:
   // X-structors
   TransFeeList (BFAbstractCBO &parent);
   virtual ~TransFeeList();

   // Initialize function
   SEVERITY initNew ( const DString &transType,
                      const DString &accountNum,
                      const BFDataGroupId &idDataGroup);
   SEVERITY init ( const DString &transNum,
                   const DString &accountNum,
                   const BFDataGroupId &idDataGroup,
                   const DString &dstrTrack = I_("N"), 
                   const DString &dstrPageName = NULL_STRING);
   void setContext (const TransFeeContext &context);
   virtual void onNotify ( E_EVENT_GROUP eEventCateg, 
                           E_EVENT eEventId, 
                           const DString &hint);
   SEVERITY getTransFee ( const DString &feeCode,
                          TransFee *&pTransFee,
                          const BFDataGroupId &idDataGroup);                          
   SEVERITY getTransFeeRate ( const DString &feeCode, DString &feeRate, const BFDataGroupId &idDataGroup);                          
   SEVERITY setTransFeeRate ( const DString &feeCode, const DString &feeRate, const BFDataGroupId &idDataGroup);                          

   SEVERITY calculateDiscountRate (const BFDataGroupId &idDataGroup);
   void changeFieldsForRebook ();
   void setDataGroupForRefresh (const BFDataGroupId &idDataGroup);
   SEVERITY applyTransFeeRateToAllocation(const BFDataGroupId &idDataGroup);
protected:
   virtual SEVERITY doCreateObject ( const BFData& data, 
                                     BFCBO *&pObjOut);
   virtual SEVERITY doCreateNewObject ( BFCBO *&pBase, 
                                        DString &strKey, 
                                        const BFDataGroupId &idDataGroup);
   virtual void getStrKey ( DString &strKey, 
                            const BFData *data);

   virtual void doCommitDataGroup( const BFDataGroupId& idDataGroup );
   

private:
   TransFee *makeFee ( const DString &feeCode,
                       const BFDataGroupId &idDataGroup);
   SEVERITY refresh (const BFDataGroupId &idDataGroup);
   SEVERITY refreshContext ( const BFDataGroupId &idDataGroup,
                             bool bRestore = false);
   SEVERITY refreshFeeCodes (const BFDataGroupId &idDataGroup);
   DString _strKey;
   TransFeeContext *_context;
   BFDataGroupId _idDataGroup; //have to store this, due to refresh
   std::vector <DString> _feeCodes;
   bool _forcingRefresh;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TransFeeList.hpp-arc  $
//
//   Rev 1.14   Jul 06 2012 17:04:26   if991250
//IN2984281 Split commission refresh for GI Attrib changes
//
//   Rev 1.13   Jan 27 2012 12:32:34   if991250
//fix deadlock on changing GI attributes for a pending purchase
//
//   Rev 1.12   Sep 12 2005 14:00:54   popescu
//Incident #399924 - refresh the fees list for rebooks, pending trades.
//
//   Rev 1.11   Jul 08 2005 09:34:28   Yingbaol
//PET1235,FN01:transaction cancellation rebook
//
//   Rev 1.10   Mar 03 2005 08:13:46   popescu
//PET 1117/06 added restore functionality for fees, when modifying a pending trade, even if the TransFee table is not populated
//
//   Rev 1.9   Feb 17 2005 10:22:02   popescu
//PTS 243445, refresh of Discount Rate was not properly done for pending trades; made the view call with the proper datagroupid
//
//   Rev 1.8   Jan 13 2005 18:33:28   popescu
//PTS 10037865, refresh fee codes if for trades in pending mode
//
//   Rev 1.7   Dec 14 2004 09:59:54   popescu
//PET 1117/06, refresh trans fee list in pending mode
//
//   Rev 1.6   Dec 11 2004 11:48:10   popescu
//PET 1117/56 more fixes, pending trade mods
//
//   Rev 1.5   Nov 29 2004 20:30:58   popescu
//PET 1117/06/56 fees/trades processing
//
//   Rev 1.4   Nov 17 2004 16:16:00   popescu
//PET 1117/06, Trade processing fees
//
//   Rev 1.3   Nov 15 2004 16:24:18   popescu
//PET 1117/06, more synch to .NET changes
//
//   Rev 1.1   Nov 09 2004 16:51:16   popescu
//PET 1117/06, Trade processing
//
//   Rev 1.0   Nov 05 2004 21:30:28   popescu
//Initial revision.
//
//Initial revision.
//
 */
