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
// ^FILE   : TransCancel.hpp
// ^AUTHOR :  
// ^DATE   : July 21, 2004
//
// ^CLASS    : TransCancel
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
class BatchInfoList;

class FundLmtOverrideList;

class IFASTCBO_LINKAGE TransCancel : public MFCanBFCbo, private boost::noncopyable
{
public:
   static void buildKey (const DString &TransNum, DString &strKeyOut);
public:
   // X-structors
   TransCancel (BFAbstractCBO &parent);
   virtual ~TransCancel();
   
   // Initialize function
   SEVERITY initNew ( const BFDataGroupId &idDataGroup,
                      const DString &transNum, /*, const DString &transId = NULL_STRING */ 
                      const DString &dstrTradeDate = NULL_STRING,
                      const DString &dstrSettleDate = NULL_STRING,
                      const DString &dstrTransType = NULL_STRING );

   virtual SEVERITY init( const BFData& data,
                          const DString &dstrTradeDate = NULL_STRING,
                          const DString &dstrSettleDate = NULL_STRING );

   virtual SEVERITY getDilutionAllocList ( const BFDataGroupId& idDataGroup, 
                                           DilutionAllocList *&pDilutionAllocList );

   void setReadOnlyFields ( bool readonly, const BFDataGroupId &idDataGroup);   

   SEVERITY ValidateAccountable( const BFDataGroupId& idDataGroup );

   virtual SEVERITY setField( const BFFieldId &fieldId,
                              const DString& strValue,
                              const BFDataGroupId& idDataGroup, 
                              bool  lFormatted = true,
                              bool  lSideEffect = false,
                              bool  bCheckCurrentValue = true);

   //SEVERITY ValidateAll( const BFDataGroupId& idDataGroup );

protected:
   virtual SEVERITY doApplyRelatedChanges ( const BFFieldId &idField, 
                                            const BFDataGroupId &idDataGroup);

   virtual SEVERITY doValidateField ( const BFFieldId &idField, 
                                      const DString &strValue, 
                                      const BFDataGroupId &idDataGroup);

   void commonInit ( const BFDataGroupId &idDataGroup,
                     const DString &transNum );

   virtual SEVERITY getBatchNum ( const BFDataGroupId &idDataGroup,
                                  const DString &track = I_("N"),
                                  const DString &pageName = NULL_STRING);  

   virtual SEVERITY setTransNum( const BFDataGroupId &idDataGroup );
   virtual SEVERITY setNewTransStatus( const BFDataGroupId &idDataGroup );
   virtual bool isModifiableBasedOnStatus( const BFDataGroupId &idDataGroup );

   virtual bool isIndividualTransCancelAllowed();
   
   virtual SEVERITY setDefaultSuppressIndicators( const BFDataGroupId &idDataGroup );
   virtual void setSuppressIndicatorsPerm(const BFDataGroupId &idDataGroup);
   virtual bool areSuppressIndicatorsModifiableBasedOnStatus( const BFDataGroupId &idDataGroup);
   virtual SEVERITY setSuppressIndicatorsReadOnlyFlags(const BFDataGroupId &idDataGroup);
   virtual SEVERITY setSuppressIndicatorsInactive(const BFDataGroupId &idDataGroup, const bool isNew);
   virtual SEVERITY setSuppressIndicatorsSet( const BFDataGroupId &idDataGroup );
   virtual SEVERITY doValidateAll ( const BFDataGroupId &idDataGroup, 
                                    long lValidateGroup);
  
   virtual SEVERITY SetRefundRVCDFields(const BFDataGroupId &idDataGroup);
   bool bIsEventReceiptDateTimeAppl(const BFDataGroupId &idDataGroup); 
   bool accountHasTradeAfterTradeDate(const BFDataGroupId &idDataGroup);
private:
   SEVERITY refreshDilution ( const BFFieldId &idField, 
                              const DString &strValue,
                              const BFDataGroupId &idDataGroup);

   SEVERITY initBatchList (const BFDataGroupId &idDataGroup);

   bool isDilutionAllowed (const BFDataGroupId &idDataGroup);
   bool hasAllocatedDilution (const BFDataGroupId &idDataGroup);
 
   bool bIsRefundCalcReq( const BFDataGroupId &idDataGroup);
   SEVERITY validateRESPInfoUpdate ( const BFDataGroupId &idDataGroup );
   SEVERITY getFundLmtOverrideList ( FundLmtOverrideList *&pFundLmtOverrideList, 
                                                 const BFDataGroupId &idDataGroup);
   bool bIsRuleTypeEnabled4FundLimit(FundLmtOverrideList *pFundLmtOverrideList,
									 const DString RuleType,const BFDataGroupId &idDataGroup);


   bool isRefundOptAndPayTypeAvailable( const BFDataGroupId &idDataGroup, DString &stopFlag,DString &defaultRefundOption);  

   DString _dstrTradeDate,
      _dstrSettleDate,
      _dstrTransType;
   BatchInfoList *pBatchInfoList;

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TransCancel.hpp-arc  $
//
//   Rev 1.22   May 29 2012 13:48:08   wp040027
//IN 2956475 – Enabling RefundPayType for Rule type 49
//
//   Rev 1.21   May 07 2012 14:28:32   wp040027
//PETP0187485-CPF-Trade Cancellation
//
//   Rev 1.20   Oct 29 2010 05:38:26   kitticha
//PET0165541 FN03 - QESI Phase3.
//
//   Rev 1.19   Jun 01 2010 23:31:54   dchatcha
//IN#2128812 - PETP0165541 FN 01 - Cancellation of processed transaction for RESP Accounts.
//
//   Rev 1.18   May 14 2009 13:38:06   jankovii
//PET 159770 FN05 Auto Batching.
//
//   Rev 1.17   Nov 14 2006 16:50:10   porteanm
//Incident 676881 - Pass TransType to 338 (TransCancel).
//
//   Rev 1.16   Mar 10 2006 13:49:28   porteanm
//Incident 563764 - TradeDate/SettleDate validation support for a cancelled transaction.
//
//   Rev 1.15   Mar 06 2006 16:21:46   ZHANGCEL
//PET1334 - FN01 -- Code clean up
//
//   Rev 1.14   Mar 02 2006 17:34:28   ZHANGCEL
//PET1334 - FN01 -- ESG Settlement enhancement
//
//   Rev 1.13   Jan 12 2006 15:55:52   zhengcon
//PET1295_FN01: Trade Suppress Indicator for MCH and SR Files -- Trade Cancellation: Individual and rebook 
//
//   Rev 1.12   Nov 26 2005 17:31:56   porteanm
//PET1286 FN01 - Bulk Cancellation.
//
//   Rev 1.11   Nov 23 2005 17:13:12   porteanm
//PET1286 FN01 - Bulk Cancellation.
//
//   Rev 1.10   Nov 12 2005 13:44:16   porteanm
//PET 1286 FN01 - Bulk Cancellation.
//
//   Rev 1.9   Nov 12 2005 11:53:46   porteanm
//PET 1286 FN01 - Bulk Cancellation.
//
//   Rev 1.8   Nov 11 2005 17:16:34   porteanm
//PET 1286 FN01 - Bulk Cancellation.
//
//   Rev 1.7   Nov 09 2005 19:52:00   porteanm
//PET 1286 FN01 - Bulk Cancellation.
//
//   Rev 1.6   Nov 08 2005 19:17:06   porteanm
//PET 1286 FN01 - Bulk Cancellation.
//
//   Rev 1.5   Nov 06 2005 13:56:46   porteanm
//PET 1286 FN01 - Bulk Cancellation - work in progress.
// 
//    Rev 1.14   Sep 01 2005 16:53:50   popescu
// Incident# 388632 - trans cancel screen code overhaul
// 
*/
