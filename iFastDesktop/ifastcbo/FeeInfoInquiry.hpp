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
//    Copyright 1997 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : FeeInfoInquiry.hpp
// ^AUTHOR : Shaobo Huang
// ^DATE   : Feb 11, 2000
//
// ^CLASS    : FeeInfoInquiry
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//       Acquisition Fee Calculation Inquiry
//

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

#undef IFASTCBO_LINKAGE 
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT 
#else 
   #define IFASTCBO_LINKAGE CLASS_IMPORT 
#endif

class IFASTCBO_LINKAGE FeeInfoInquiry : public MFCanBFCbo, private boost::noncopyable
{
public:

   FeeInfoInquiry( BFAbstractCBO &parent );
   virtual ~FeeInfoInquiry();

   SEVERITY init( const DString& dstrFundCode,
                  const DString& dstrClassCode,
                  const DString& FundSponsor,
                  const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING);

   static void buildKey( const DString& strFund,const DString& strClass, DString &strKeyOut );
   virtual void getStrKey( DString &strKey, const BFData *data );
   virtual void getField( const BFFieldId& idField, DString & strValue, const BFDataGroupId& idDataGroup, bool formattedReturn = false ) const;
   SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
   bool isChanged(const DString strFundCode, const DString strClassCode, const DString strFundSponsor);

private:
   BFData _requestData;

   DString m_strFundCode;
   DString m_strClassCode;
   DString m_strFundSponsor;

};

