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
// ^FILE   : MFAccountHoldingList.hpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 03/26/99
//
// ^CLASS    : MFAccountHoldingList
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

class FundMasterList;
class IFASTCBO_LINKAGE MFAccountHoldingList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   MFAccountHoldingList( BFAbstractCBO &parent );
   virtual ~MFAccountHoldingList( void );

   // Initialize function
   SEVERITY init( const DString &AccountNum,
                  const DString &AsofDate, 
                  const DString &fundCode,
                  const DString &classCode,
						const DString &activeOnly = I_("N"),
                  const DString &dstrTrack = I_("N"),
                  const DString &dstrPageName = NULL_STRING,
                  const DString &accBalMode = NULL_STRING);

   SEVERITY init( BFData& InstData );
   SEVERITY init();

   SEVERITY initObject (const BFData &data);
   virtual void getField( const BFFieldId& idField, 
                          DString & strValue, 
                          const BFDataGroupId& idDataGroup, 
                          bool formattedReturn = false ) const;

   virtual void getStrKey ( DString &strKey, const BFData *data );
   void getStrKey ( DString& dstKey, const DString &dstrFundCategory, const DString &dstFund, const DString &dstClass);
   bool isFundInHoldings (const DString &dstrFundCode, const DString &dstrClassCode, const BFDataGroupId &idDataGroup);
   bool hasHeldGICFund (const BFDataGroupId& idDataGroup);
	bool hasHeldMultiCurrencyFund(const BFDataGroupId& idDataGroup );

   double getSettledFundBalanceForAmtType( const DString &dstrFundCode,
                                           const DString &dstrClassCode,
			 			                         const DString &dstrAmtType,
                                           const BFDataGroupId &idDataGroup);
   bool hasNonAMSFunds(const BFDataGroupId& idDataGroup);


protected:
   virtual SEVERITY doCreateObject (const BFData& data, BFCBO *&pObjOut);
private:
	double getBalance( BFAbstractCBO* bfcbo,const BFDataGroupId& idDataGroup );
   DString _accountNum;
   FundMasterList* _pFundMasterList;
};

///#endif

