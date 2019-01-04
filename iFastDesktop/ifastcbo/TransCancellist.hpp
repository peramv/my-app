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
//    Copyright 2005 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : TransCancellist.hpp
// ^AUTHOR :  
// ^DATE   : July 21, 2004
//
// ^CLASS    : TransCancellist
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <boost\utility.hpp>
#include <ifastcbo\mfcancbo.hpp>

// Forward references

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class DilutionAllocList;
class TransCancel;

class IFASTCBO_LINKAGE TransCancellist : public MFCanBFCbo, private boost::noncopyable
{

public:
   // X-structors
   TransCancellist( BFAbstractCBO &parent );
   virtual ~TransCancellist();
   // Initialize function
   SEVERITY init ( const DString &transNum,
                   const DString& cashDivPaidAfter,
                   const BFDataGroupId& idDataGroup, 
				   const DString &dstrTradeDate = NULL_STRING,
				   const DString &dstrFundCode = NULL_STRING,
				   const DString &dstrClassCode = NULL_STRING,
				   const DString &dstrSearchType = NULL_STRING,
				   const DString &dstrTranStatus = NULL_STRING,
				   const DString &dstrAdjustType = NULL_STRING,
				   const DString &dstrTradeAdjustId = NULL_STRING,
				   const DString &dstrSettledate = NULL_STRING,	
				   const DString &dstrTransType = NULL_STRING,
	               const DString &dstrTrack = I_("N"),
                   const DString &dstrPageName = NULL_STRING);
   SEVERITY getTransCancel ( const DString &_TransNum, 
                             TransCancel *&_pTransCancel, 
                             const BFDataGroupId &idDataGroup);
	SEVERITY getMore();

protected:
   virtual SEVERITY doCreateObject (const BFData& data, BFCBO *&pObjOut);
   virtual SEVERITY doCreateNewObject (BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup);  
   virtual SEVERITY doValidateAll (const BFDataGroupId& idDataGroup, long lValidateGroup);   
   virtual SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );

public:
   DString getTradeDate() { return _dstrTradeDate; };
   DString getFund() { return _dstrFund; };
   DString getClass() { return _dstrClass; };

private:
	bool newCancellation;
	DString _transNum,
            _cashDivPaidAfter,
			_dstrTradeDate,
			_dstrFund,
			_dstrClass,
			_dstrSettleDate,
			_dstrTransType;

   BFData *_pRequestData;
};

