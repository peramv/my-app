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
// ^FILE   : FundBrokerList.hpp
// ^AUTHOR :  
// ^DATE   : July 21, 2004
//
// ^CLASS    : FundBrokerList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <boost\utility.hpp>
#include <ifastcbo\mfcancbo.hpp>

// Forward references

class FundBroker;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class FundBroker;

class IFASTCBO_LINKAGE FundBrokerList : public MFCanBFCbo, private boost::noncopyable
{
public:
   static void buildKey (const DString &fundBrokerCode, DString &strKeyOut);
public:
   // X-structors
   FundBrokerList( BFAbstractCBO &parent );
   virtual ~FundBrokerList();
   // Initialize function
   SEVERITY init ( const BFDataGroupId& idDataGroup, 
                   const DString &dstrTrack = I_("N"),
                   const DString &dstrPageName = NULL_STRING
                 );
   SEVERITY init ( const DString &fundBrokerCode,
				   const DString &fundBrokerName,
                   const BFDataGroupId& idDataGroup, 
                   const DString &dstrTrack = I_("N"),
                   const DString &dstrPageName = NULL_STRING,
				   const bool noDataIsErrorCondition = false
                 );
   SEVERITY getFundBrokerCodeSubstList( DString &dstrFundBrokerCodeSubstList );
   SEVERITY getFundBroker ( const DString &fundBrokerCode, 
                            const BFDataGroupId &idDataGroup, 
                            FundBroker *&pFundBroker 
                          );
   SEVERITY getMore();
protected:
	virtual SEVERITY doCreateObject ( const BFData &data, 
                                     BFCBO *&pObjOut
                                   );
	virtual SEVERITY doCreateNewObject ( BFCBO *&pBase, 
                                        DString &strKey, 
                                        const BFDataGroupId &idDataGroup
                                      );
   virtual void getStrKey ( DString &strKey, 
                            const BFData *data
                          );
   bool canDeleteObject ( const DString &strKey, 
                          const BFDataGroupId &idDataGroup
                        );
private:
	BFData * requestData326;
};

