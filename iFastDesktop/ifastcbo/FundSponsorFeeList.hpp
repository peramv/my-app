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
// ^FILE   : FundSponsorFeeList.hpp
// ^AUTHOR :  
// ^DATE   : July 26, 2004
//
// ^CLASS    : FundSponsorFeeList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <boost\utility.hpp>

// Forward references

#include "FeeParamSysList.hpp"
class FundSponsorFee;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif



class IFASTCBO_LINKAGE FundSponsorFeeList : public FeeParamBaseList
{
public:

   // X-structors
   FundSponsorFeeList( BFAbstractCBO &parent );
   virtual ~FundSponsorFeeList();
   // Initialize function
   SEVERITY init ( const DString &dstrFeeModelCode, 
                   const DString &dstrFundSponsorCode, 
                   const BFDataGroupId &idDataGroup, 
                   const DString &dstrTrack = I_("N"),
                   const DString &dstrPageName = NULL_STRING);

   SEVERITY validateOverlapping( BFCBO *pCBO, const BFDataGroupId& idDataGroup );

   void InitNew (const BFDataGroupId &idDataGroup);
   void setFieldForAllRecords (const BFFieldId& idField, const DString value, const BFDataGroupId& idDataGroup);
   void setStopDateForAllRecords ( const BFDataGroupId& idDataGroup );
   void setFieldValidflag (const BFFieldId& idField, const BFDataGroupId& idDataGroup, const bool valid );
   bool Not100PercentDiscount (const BFDataGroupId& idDataGroup);
protected:
	SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
	SEVERITY doCreateNewObject( BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup );
   SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
	void getStrKey ( DString& strKey, const BFData* data );
   void getStrKeyForNewItem(DString & strKey);   

private:
   BFData *requestData230;
   bool bDefault_;
   int m_intKey;
   int m_intNewKey;
};

