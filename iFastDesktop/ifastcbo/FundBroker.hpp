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
// ^FILE   : FundBroker.hpp
// ^AUTHOR : 
// ^DATE   : July 21, 2004
//
// ^CLASS    : FundBroker
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <boost\utility.hpp>
#include <ifastcbo\mfcancbo.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif
class FundBrokerFeeList;
class FundBrokerSettlementInstrList;
class FundMgmtSettlementInstrList;

class IFASTCBO_LINKAGE FundBroker : public MFCanBFCbo, private boost::noncopyable
{
public:
   FundBroker( BFAbstractCBO &parent );
   virtual ~FundBroker();

   SEVERITY Init(const BFData& data);

   SEVERITY InitNew( const BFDataGroupId& idDataGroup ); //for creating new object
   SEVERITY getFundBrokerFeeList( FundBrokerFeeList *&pFundBrokerFeeList, 
	   const BFDataGroupId& idDataGroup,
	   bool inquireDatabase = true 
	   );
   SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );

   virtual SEVERITY setField( const BFFieldId &fieldId,
                              const DString& strValue,
                              const BFDataGroupId& idDataGroup, 
                              bool  lFormatted = true,
                              bool  lSideEffect = false,
                              bool  bCheckCurrentValue = true);
   SEVERITY validateFundBrokerCode ( const DString& dstrFundBrokerCode, const BFDataGroupId& idDataGroup);
   SEVERITY validateEntityName ( const DString& dstrFundBrokerName, const BFDataGroupId& idDataGroup);
   SEVERITY getFndMgmtSettlementInstrList(   FundMgmtSettlementInstrList *&pFundMgmtSettlementInstrList, 
                                             const BFDataGroupId &idDataGroup,
                                             bool bInquireDatabase = true );
   SEVERITY getSettlementInstrList( FundBrokerSettlementInstrList *&pSettlementInstrList, 
                                    const BFDataGroupId &idDataGroup,
                                    bool bInquireDatabase = true );

protected:
	SEVERITY doValidateField( const BFFieldId& idField,
                                    const DString& strValue,
                                    const BFDataGroupId& idDataGroup );

   void setFieldsReadOnly(const BFDataGroupId& idDataGroup, bool bReadOnly); 
   SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );
   void RoutingTypeRelateChange( const BFDataGroupId& idDataGroup );
   SEVERITY getNextFundBrokerCode( const BFDataGroupId& idDataGroup );
   SEVERITY validateEffectiveStopDate( const BFDataGroupId& idDataGroup );
private:
   DString _initEffectiveDate;
   DString _initStopDate;
   DString _fundBrokerCode;
};