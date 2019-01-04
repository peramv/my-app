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
// ^FILE      : TransFee.hpp
// ^AUTHOR    : Serban Popescu
// ^DATE      : July 2004
//
// ^CLASS     : TransFee
// ^SUBCLASS  :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
#include <ifastcbo\transfeecontext.hpp>
///#endif
//trans fee view
#include <ifastdataimpl\dse_dstc0298_vw.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

//Forward declarations
class Trade;
class TransFeeContext;
class FundFeeList;

class IFASTCBO_LINKAGE TransFee : public MFCanBFCbo, private boost::noncopyable
{
public:
   TransFee (BFAbstractCBO &parent, const DString &feeCode);
   virtual ~TransFee();

   virtual SEVERITY init (const BFData &viewData);
   virtual SEVERITY init ( const BFDataGroupId &idDataGroup, 
                           bool bDelyaInit = false);
   SEVERITY reInit (const BFDataGroupId &idDataGroup);
   virtual SEVERITY restore ( BFCBO &rpParent, 
                              const BFDataGroupId &idDataGroup);
//each derived class should know whether the fee is applicable at the system level
//method should be used to check mgtco level options
   virtual bool isSystemApplicable (const BFDataGroupId &idDataGroup) = 0;
//each derived class should know whether the fee can be overriden in the current trade context
   virtual bool isContextApplicable (const BFDataGroupId &idDataGroup) = 0;
   virtual bool hasContextChanged (const BFDataGroupId &idDataGroup) = 0;
//should respond whether the fee is a yes/no charge type of fee
   virtual bool isChargeFee (const BFDataGroupId &idDataGroup) = 0;
   void setContext (const TransFeeContext &context);
   void applyModPerm ( const DString &modPerm,
                       const BFDataGroupId &idDataGroup);
   void changeFieldsForRebook();
   virtual SEVERITY applyTransFeeRateToAllocation(const BFDataGroupId &idDataGroup);
   DString& get_FeeCode() {return _feeCode;}

protected:
   virtual SEVERITY doValidateField ( const BFFieldId &idField, 
                                      const DString &strValue, 
                                      const BFDataGroupId &idDataGroup);
   virtual SEVERITY doApplyRelatedChanges ( const BFFieldId &idField, 
                                            const BFDataGroupId &idDataGroup);
   virtual void doInitWithDefaultValues (const BFDataGroupId &idDataGroup);
   virtual void doReset (const BFDataGroupId &idDataGroup);
   virtual void getFeeConfigDefaults ( bool bChargeOptionDefaultsRead,
                                       bool bChargeTradeFeeOptionDefaultsRead,
                                       bool bChargeFeeTypeOptionDefaultsRead,
                                       const BFDataGroupId &idDataGroup);
   virtual SEVERITY setFeeDefault (const BFDataGroupId &idDataGroup) = 0;
   virtual SEVERITY setFeeType (const BFDataGroupId &idDataGroup);
   virtual SEVERITY setFeeProperties (const BFDataGroupId &idDataGroup);
   virtual SEVERITY setChargeOption (const BFDataGroupId &idDataGroup);
   virtual bool useFeeModelCode ();
   virtual bool useToSide ();
   SEVERITY getFeeParams ( FundFeeList *&pFundFeeList, 
                           const BFDataGroupId &idDataGroup);
   SEVERITY getFeeParams ( const DString &fundCode,
                           const DString &classCode,
                           FundFeeList *&pFundFeeList, 
                           const BFDataGroupId &idDataGroup);
   bool hasFeeParams ( const BFDataGroupId &idDataGroup);
   bool hasFeeParams ( const DString &fundCode,
                       const DString &classCode,
                       const BFDataGroupId &idDataGroup);
   bool hasFeeParamsContextChanged (const BFDataGroupId &idDataGroup);
   TransFeeContext &getContext();
   bool hasFieldContextChanged ( const BFFieldId &idField,
                                 const BFDataGroupId &idDataGroup);
   bool isFeeWaivedForAccount (const BFDataGroupId &idDataGroup);
   bool canBeInitialized (const BFDataGroupId &idDataGroup);
   DString charge2Rate (const DString &charge);
   SEVERITY getFeeModelCode ( const DString &accountNum,
                              DString &feeModelCode,
                              const BFDataGroupId &idDataGroup);
private:
   SEVERITY validateTradeFeeOption ( const DString &strValue, 
                                     const BFDataGroupId &idDataGroup);
   SEVERITY validateFeeType ( const DString &strValue, 
                              const BFDataGroupId &idDataGroup);
   SEVERITY getFeeParamConfigDefaults (const BFDataGroupId &idDataGroup);
   DString _feeCode;
//the fee context
   TransFeeContext *_context,
      *_oldContext;
   bool _bDelayInit;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TransFee.hpp-arc  $
//
//   Rev 1.17   Jul 08 2005 09:34:20   Yingbaol
//PET1235,FN01:transaction cancellation rebook
//
//   Rev 1.16   Apr 10 2005 17:56:48   popescu
//Incident 276992 - no need to override setField in this class
//
//   Rev 1.15   Apr 09 2005 14:06:34   porteanm
//Incident 276992 - FeeRate not saved with the right precision.
//
//   Rev 1.14   Mar 03 2005 08:13:38   popescu
//PET 1117/06 added restore functionality for fees, when modifying a pending trade, even if the TransFee table is not populated
//
//   Rev 1.13   Mar 02 2005 08:31:26   popescu
//PET 1117/56, added virtual method meant to let the base class know which side (from or to) should be used when fee params are called
//
//   Rev 1.12   Jan 31 2005 18:19:48   popescu
//PET 1117/06/56, set the acq fee related fields to read only if shareholder has a fee model. Also, set option '1' for TradeFeeOption (Charge per system calculated)
//
//   Rev 1.11   Jan 14 2005 10:31:06   popescu
//PTS 10037865, charge option field should be 'Charge' and locked for Conditionrate and all other fees, but TrxnFee where user should be allowed to change its value.
//
//   Rev 1.10   Jan 12 2005 14:42:50   popescu
//PTS 10037788, fee charge option default value fix
//
//   Rev 1.9   Jan 10 2005 10:38:54   popescu
//PTS 10037553, fixed fees properties in pending mode and trade reset of the trans type combo
//
//   Rev 1.8   Dec 09 2004 12:37:50   popescu
//PET 1117/56, more fees work /pending trade
//
//   Rev 1.7   Dec 08 2004 22:08:28   popescu
//PET 1117/06, more fees
//
//   Rev 1.6   Dec 02 2004 20:59:40   popescu
//PET 1117/06, more fee fixes
//
//   Rev 1.5   Nov 24 2004 21:36:30   popescu
//PET 1117/06/56. trade processing, settle location
//
//   Rev 1.4   Nov 17 2004 16:15:48   popescu
//PET 1117/06, Trade processing fees
//
//   Rev 1.3   Nov 15 2004 16:23:36   popescu
//PET 1117/06, more synch to .NET changes
//
//   Rev 1.1   Nov 09 2004 16:50:58   popescu
//PET 1117/06, Trade processing
//
//   Rev 1.0   Nov 05 2004 21:30:20   popescu
//Initial revision.
//
 */