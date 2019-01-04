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
// ^FILE   : TradePayInstruct.hpp
// ^AUTHOR : 
// ^DATE   : August, 2006
//
// ^CLASS    : TradePayInstruct
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <boost\utility.hpp>
#include <ifastcbo\mfcancbo.hpp>

//trade pay instruct view definition
#include <ifastdataimpl\dse_dstc0374_req.hpp>
#include <ifastdataimpl\dse_dstc0374_vw.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE TradePayInstruct : public MFCanBFCbo, private boost::noncopyable
{
public:
   TradePayInstruct (BFAbstractCBO &parent);
   virtual ~TradePayInstruct();
   SEVERITY init ( const DString &payToEntity, 
                   const BFData& data,
                   const BFDataGroupId& idDataGroup = BF::HOST,
                   bool bSetFieldsReadOnly = false);
   SEVERITY initNew ( const DString &payToEntity, 
                      const BFDataGroupId& idDataGroup); //for creating new object
   bool isBankingAllowed (const BFDataGroupId &idDataGroup);
   bool isAddressInfoAllowed (const BFDataGroupId &idDataGroup);
   bool isSuppressAllowed (const BFDataGroupId &idDataGroup);
protected:
   virtual void doInitWithDefaultValues (const BFDataGroupId& idDataGroup);
	virtual SEVERITY doValidateField ( const BFFieldId& idField,
                                      const DString& strValue,
                                      const BFDataGroupId& idDataGroup);
   virtual SEVERITY doApplyRelatedChanges ( const BFFieldId& idField, 
                                            const BFDataGroupId& idDataGroup);
private:
   SEVERITY validatePercent (const BFDataGroupId& idDataGroup);
   SEVERITY commonInit ( const DString &payToEntity,
                         const BFDataGroupId& idDataGroup);
   SEVERITY fillAddressInfo ( const BFDataGroupId &idDataGroup, 
                              bool bDataNotFound = false);
   SEVERITY loadCurrencySet (const BFDataGroupId &idDataGroup);
   SEVERITY loadFileProcessorSet (const BFDataGroupId &idDataGroup);
   SEVERITY addressInfoRelatedChanges (const BFDataGroupId &idDataGroup);
   SEVERITY payTypeRelatedChanges ( const BFDataGroupId &idDataGroup,
                                    bool bDataNotFound = false);
   DString _hostCurrenciesSet;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TradePayInstruct.hpp-arc  $
//
//   Rev 1.6   Oct 20 2006 18:15:00   popescu
//Incident# 731541 reviewed the way related changes for  fields is working in paym instruct
//
//   Rev 1.5   Sep 22 2006 00:46:58   popescu
//STP 2217/13
//
//   Rev 1.4   Sep 15 2006 19:43:20   popescu
//STP 2217/13 - fixes
//
//   Rev 1.3   Sep 13 2006 19:11:34   popescu
//STP 2192/FN 13
//
//   Rev 1.2   Sep 10 2006 18:00:36   popescu
//STP 2192/12
*/
