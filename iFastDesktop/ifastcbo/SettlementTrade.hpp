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
//    Copyright 2002, By International Financial Data Service
//
//
//******************************************************************************
//
// ^FILE   : SettlementTrade.hpp
// ^AUTHOR : Yingbao Li
// ^DATE   : May 24,2002
//
// ^CLASS    : SettlementTrade
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <ifastcbo\Settlement.hpp>
#include "TransactionDetails.hpp"
#include "fundmaster.hpp"
#include "funddetail.hpp"

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class SettlementTradeBankInstructionsList;

class IFASTCBO_LINKAGE SettlementTrade : public MFCanBFCbo
{
public:
   SettlementTrade( BFAbstractCBO &parent );
   virtual ~SettlementTrade();

   SEVERITY init(const BFData&   data,const DString& dstrSearchType,const bool bInd );
   void setSetAllFlag(bool bSetAll = true)
   {
      _bSetAll = bSetAll;
   }
   SEVERITY copyAddress( const DString& dstrKey, const BFDataGroupId& idDataGroup );
   bool hasPermChangeAddrBank( );
   SEVERITY getBankInstructionsList(
      SettlementTradeBankInstructionsList *&pSettlementTradeBankInstructionsList, 
      const BFDataGroupId& idDataGroup, bool bCreate = true);
   void setSettledUpdated( const BFDataGroupId& idDataGroup, bool val );
   bool isSettleRedemptionAllowed(const BFDataGroupId& idDataGroup );
   void getField( const BFFieldId& idField, DString& strFieldValue, const BFDataGroupId& idDataGroup, 
                  bool formattedReturn = false ) const;
protected:
   virtual SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );
   //virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
   virtual SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   virtual SEVERITY doValidateAll ( const BFDataGroupId &idDataGroup, long lValidateGroup);
   SEVERITY buildPaymentRoutingSet(const BFDataGroupId &idDataGroup,DString &outdstrpymtLevelRoutingSet);
   SEVERITY setPaymentRoutingSetDefault( const BFDataGroupId &idDataGroup);

private:
   SEVERITY doPayTypeRelatedChange(const BFDataGroupId& idDataGroup );
   SEVERITY loadFileProcessor( const BFDataGroupId& idDataGroup );
   SEVERITY doBankRelatedChange( const BFDataGroupId& idDataGroup );
   SEVERITY doAddressRelatedChange( const BFDataGroupId& idDataGroup );
   SEVERITY validateValueDate( const DString& strValue, const BFDataGroupId& idDataGroup );
   SEVERITY validateInternationalWire (const BFDataGroupId& idDataGroup);
   SEVERITY doAddressCodeRelatedChanges(const BFDataGroupId& idDataGroup );
   SEVERITY validateStopRedemption(const BFDataGroupId& idDataGroup );
   bool userChangeFields(const BFDataGroupId& idDataGroup );
   SEVERITY validateBankVerifyStatus (const BFDataGroupId &idDataGroup);
   SEVERITY validateAddrVerifyStatus( const BFDataGroupId &idDataGroup );

   int getAddressLines(const BFFieldId& idField, const DString strLine,const BFDataGroupId& idDataGroup);

   SEVERITY validateAddress( const BFFieldId& idField,const DString strLine, const BFDataGroupId& idDataGroup );
   SEVERITY validateAddressCode( const DString dstrAddrCode, const BFDataGroupId& idDataGroup );
   SEVERITY validatePayTypeForEPATrade(const DString &strValue,const BFDataGroupId &idDataGroup);
   SEVERITY validateSettledForEPATrade(const DString& dstrValue, const BFDataGroupId &idDataGroup);
   SEVERITY validateStopTradeSettlement(const BFDataGroupId &idDataGroup);
   SEVERITY getTransactionDetails (TransactionDetails *&pTransactionDetails,
                                   const BFDataGroupId &idDataGroup);

   bool isSettleAll(){
      return(_bSetAll == true);
   }

   SEVERITY validateGNSettl( const DString& dstrValue, const BFDataGroupId& idDataGroup );
   bool isIndividual();
   void setIndividual(bool bInd){
      _bIndividual = bInd;
   }

   SEVERITY validateSettledUnitsForRedemption( const DString &dstrSettled, const BFDataGroupId& idDataGroup );
   bool isCheckSettledUnitsForRedemptionApplicable( const DString &dstrSettled, const BFDataGroupId& idDataGroup );
   bool isAddressRelatedUpdateable(const DString& dstrValue, const BFDataGroupId &idDataGroup);

   SEVERITY validateCashDate ( const DString &cashDate, 
	   const BFDataGroupId &idDataGroup);

   bool isCashDateUpdatable ( FundMaster *pFundMaster,
	   const BFDataGroupId &idDataGroup);

   SEVERITY getFundField ( const DString &fundCode, 
	   const DString &classCode, 
	   const BFFieldId &idField, 
	   DString &strValue);

   SEVERITY bankChrgsRelatedChanges (const BFDataGroupId &idDataGroup);
   // copy constructor
   SettlementTrade( const SettlementTrade& copy ); //not implemented
   // = Operator
   SettlementTrade& operator= ( const SettlementTrade& copy );//not implemented
   bool _bIndividual;
   bool _bSetAll;
   DString _dstrGNSettle; 
   DString _dstrSearchType;
   bool	hasTRXRs;

};

//*****************************************************************************
//              Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/SettlementTrade.hpp-arc  $
//
//   Rev 1.29   Jan 22 2011 10:54:32   dchatcha
//IN# 2398106 - R11.2-PETP0175716FN02-EPA Futured dated trade got settled
//
//   Rev 1.28   Dec 02 2010 23:26:16   dchatcha
//P0175716 FN02 - Client Name Redemption - EPA Auto Settlement.
//
//   Rev 1.27   Dec 01 2010 06:06:56   dchatcha
//P0175716 FN02 - Client Name Redemption - EPA Auto Settlement.
//
//   Rev 1.26   Dec 03 2009 02:56:28   dchatcha
//PET0166583 FN02 FN03 - Static Verification Phase 2.
//
//   Rev 1.25   Nov 26 2009 13:41:48   jankovii
//PET0166583 FN01 Static Data Changes Banking 
//
//   Rev 1.24   Mar 21 2007 13:24:54   jankovii
//PET 2292 FN01 - Switch Settlement.
//
//   Rev 1.23   Aug 03 2005 11:46:52   ZHANGCEL
//PET1280 -- Enhancement for SSBL Barclays bank charge field
//
//   Rev 1.22   Apr 12 2005 10:31:02   porteanm
//PET1190 FN14 - Wire order redemption against unsettled units.
//
//   Rev 1.21   Nov 14 2004 14:54:14   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.20   Oct 12 2004 13:43:34   YINGBAOL
//PET10034502: add logic to issue critical error when user select "SettleAll" and all records are not allowed to settle.
//
//   Rev 1.19   Aug 31 2004 12:01:46   YINGBAOL
//PET1124:raise critical error if user change anything for concrate settlement.
//
//   Rev 1.18   Aug 13 2004 13:56:22   YINGBAOL
//PET1027:StopRedemtionSettlement
//
//   Rev 1.17   Feb 09 2004 10:15:44   FENGYONG
//PET965.FN1 SSB Profile restriction
//
//   Rev 1.16   Sep 10 2003 14:39:44   YINGBAOL
//add dstrGNSettleFlag.
//
//   Rev 1.15   Jun 10 2003 16:11:20   popescu
//Changed the SettlementTrade bank instructions files to match new design for bank instructions that are not on host
//
//   Rev 1.14   Apr 24 2003 16:44:24   YINGBAOL
//change   doAddressRelatedChanges(... ) to doAddressCodeRelatedChanges;
//
//   Rev 1.13   Mar 21 2003 18:24:10   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.12   Dec 11 2002 16:53:38   YINGBAOL
//fix individual Settlement
//
//   Rev 1.11   Oct 09 2002 23:54:58   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.10   Aug 29 2002 12:53:38   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.9   Aug 16 2002 13:53:36   YINGBAOL
//add permission check
//
//   Rev 1.8   Aug 08 2002 16:42:04   YINGBAOL
//address code enhancement
//
//   Rev 1.7   Jun 28 2002 13:39:26   YINGBAOL
//add validation for Address Line
//
//   Rev 1.6   Jun 16 2002 14:08:20   HSUCHIN
//added international wire validation
//
//   Rev 1.5   Jun 15 2002 15:49:04   YINGBAOL
//add validate valuedate
//
//   Rev 1.4   Jun 13 2002 09:47:46   VASILEAD
//Added setSettleUpdated()
//
//   Rev 1.3   Jun 13 2002 09:22:34   HSUCHIN
//added settlementtradebanklist
//
//   Rev 1.2   Jun 11 2002 11:43:50   YINGBAOL
//more business rules added
//
//   Rev 1.1   Jun 06 2002 16:07:50   YINGBAOL
//save work
//



//