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
//    Copyright 2000 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : AggregatedOrderList.hpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 13/07/2004
//
// ^CLASS    : AggregatedOrderList
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

class IFASTCBO_LINKAGE AggregatedOrderList : public MFCanBFCbo, private boost::noncopyable
{
public:
   static void buildKey ( const DString &omnibusID,
                          DString &strKey);
public:
   // X-structors
   AggregatedOrderList( BFAbstractCBO &parent );
   virtual ~AggregatedOrderList( void );
   virtual SEVERITY getMore();
// Initialize function
   SEVERITY init( const DString &dstrFromDate, 
                  const DString &dstrToDate,
                  const DString &dstrStatus,
                  const DString &dstrBrokerCode,
                  const DString &dstrFundCode,
                  const DString &dstrAggrOrderNum,
                  const DString &dstrRoutingRefNum,
                  const DString &dstrSearchType,
                  const DString &dstrTrack = I_("N"),
                  const DString &dstrPageName = NULL_STRING,
                  const DString &dstrFundKvBrkKvNum = NULL_STRING,
                  const DString &dstrFundIDType = NULL_STRING,
                  const DString &dstrFundIDValue = NULL_STRING,
                  const DString &dstrAmountType = NULL_STRING,
                  const DString &dstrAmount = NULL_STRING,
                  const DString &dstrTransType  = NULL_STRING);
	bool allowEnableOk (const BFDataGroupId& idDataGroup);
protected:
    virtual SEVERITY doCreateObject(const BFData &data, BFCBO *&pObjOut);
    virtual SEVERITY doValidateAll (const BFDataGroupId &idDataGroup, long lValidateGroup);
    virtual void getStrKey (DString &strKey, const BFData *data = NULL);
private:
	BFData *_pRequestData;                //Stores the request data object to be used by getMore
	BFData *_pResponseData;
};

///#endif

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AggregatedOrderList.hpp-arc  $
//
//   Rev 1.4   Feb 10 2005 11:35:30   zhangcel
//PTS 10038581 -- Synch-up from 1.1.1.1
//
//   Rev 1.3   Jan 28 2005 13:45:12   popescu
//PTS 10038381, synch-up from release 59.0.1
//
//   Rev 1.2   Jan 26 2005 11:01:26   yingbaol
//PET1117 FN67 enhance Aggregate order for API
//
//   Rev 1.1   Nov 19 2004 14:13:28   zhangcel
//PET 1117 FN 08 -- Bug fix for getMore and init
//
//   Rev 1.0   Nov 18 2004 13:57:26   zhangcel
//Initial revision.
//
 * 
 */