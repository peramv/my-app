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
// ^FILE   : TradePayInstructList.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : August, 2006
//
// ^CLASS    : TradePayInstructList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <boost\utility.hpp>
#include <ifastcbo\mfcancbo.hpp>

// Forward references
class SplitPayments;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE TradePayInstructList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   TradePayInstructList (BFAbstractCBO &parent);
   virtual ~TradePayInstructList ();
   // Initialize function
   SEVERITY init ( const DString &payToEntity,
                   const DString &transNum,
                   const BFDataGroupId &idDataGroup, 
                   bool bSetFieldsReadOnly = false,
                   const DString &dstrTrack = I_("N"),
                   const DString &dstrPageName = NULL_STRING);
   SEVERITY initNew ( const DString &payToEntity,
                      const DString &transNum,
                      const BFDataGroupId& idDataGroup);
   SEVERITY init ( const DString &payToEntity,
                   const DString &broker,
                   const DString &branch,
                   const DString &salesRepCode,
                   const DString &effectiveDate,
                   const DString &paymentFor,
                   const BFDataGroupId& idDataGroup,
                   const DString &dstrTrack = I_("N"),
                   const DString &dstrPageName = NULL_STRING);
   virtual SEVERITY addNewAllocation( const DString &paymentFor, 
                                      const DString &payType,
											     const DString &payMethod,
                                      const DString &currency,
                                      const DString &achProcessor,
                                      const BFDataGroupId &idDataGroup);
   SEVERITY otherBrokerPaymentForExist (const BFDataGroupId &idDataGroup);
protected:
	virtual SEVERITY doCreateObject ( const BFData &data, 
                                     BFCBO *&pObjOut);
	virtual SEVERITY doCreateNewObject ( BFCBO *&pBase, 
                                        DString &strKey, 
                                        const BFDataGroupId &idDataGroup);
   virtual SEVERITY doValidateAll ( const BFDataGroupId &idDataGroup, 
                                    long lValidateGroup);
private:
   BFDataGroupId _idDataGroup;
   bool _bSetFieldsReadOnly;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TradePayInstructList.hpp-arc  $
//
//   Rev 1.7   Oct 03 2006 22:26:02   popescu
//Incident #722094 - raise warn msgs if payment instr missing for either pw or id
//
//   Rev 1.6   Sep 30 2006 00:54:52   popescu
//Incident 720294 - pay entity eff. dates
//
//   Rev 1.5   Sep 22 2006 00:47:02   popescu
//STP 2217/13
//
//   Rev 1.4   Sep 15 2006 19:43:24   popescu
//STP 2217/13 - fixes
//
//   Rev 1.3   Sep 13 2006 19:11:36   popescu
//STP 2192/FN 13
//
//   Rev 1.2   Sep 10 2006 18:00:40   popescu
//STP 2192/12
//
//   Rev 1.1   Sep 07 2006 21:38:40   popescu
//STP 2192/02
//
//   Rev 1.0   Aug 29 2006 18:27:04   popescu
//Initial revision.
*/
