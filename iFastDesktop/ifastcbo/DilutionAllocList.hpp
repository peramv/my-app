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
// ^FILE   : DilutionAllocList.hpp
// ^AUTHOR :  
// ^DATE   : July 21, 2004
//
// ^CLASS    : DilutionAllocList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <boost\utility.hpp>
#include <ifastcbo\mfcancbo.hpp>

// Forward references
class DilutionAlloc;
class TransactionList;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE DilutionAllocList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   DilutionAllocList( BFAbstractCBO &parent );
   virtual ~DilutionAllocList();
   // Initialize function
   SEVERITY init ( const DString &transId,
                   const BFDataGroupId& idDataGroup, 
                   const DString &dstrTradeDate = NULL_STRING,
                   const DString &dstrSettleDate = NULL_STRING,
                   const DString &dstrTransNum = NULL_STRING,
                   const DString &dstrTrack = I_("N"),
                   const DString &dstrPageName = NULL_STRING);
   SEVERITY initNew ( const BFDataGroupId& idDataGroup, 
                      const DString &dstrTradeDate = NULL_STRING,
                      const DString &dstrSettleDate = NULL_STRING,
                      const DString &dstrTrack = I_("N"),
                      const DString &dstrPageName = NULL_STRING);
   virtual SEVERITY setField( const BFFieldId &fieldId,
                              const DString& strValue,
                              const BFDataGroupId& idDataGroup, 
                              bool  lFormatted = true,
                              bool  lSideEffect = false,
                              bool  bCheckCurrentValue = true);
   virtual SEVERITY addNewAllocation( const DString& accountable, 
                                      const DString& backDatedReason, 
                                      const BFDataGroupId& idDataGroup);

   SEVERITY getDilutionSplitMethod( DString &dstrSplitMethod, const BFDataGroupId& idDataGroup );

   DString getTransHistTradeDate() { return _dstrTransHistTradeDate; };
   DString getTransHistSettleDate() { return _dstrTransHistSettleDate; };
   void setTradeDate( const DString &dstrTradeDate ) { _dstrTransHistTradeDate = dstrTradeDate; };
   void setSettleDate( const DString &dstrSettleDate ) { _dstrTransHistSettleDate = dstrSettleDate; };
   DString getTransId() { return _dstrTransId; };
   DString getTransNum() { return _dstrTransNum; };

   SEVERITY refreshNSMEligibility(const BFFieldId& idField, const BFDataGroupId& idDataGroup);
   SEVERITY refreshIsSettleNetworkEligible (DString& eligibility, const BFDataGroupId &idDataGroup);
   SEVERITY cloneForReebokWithNewTransId (const DString& transId, DilutionAllocList* pDilutionAllocList, const BFDataGroupId& idDataGroup);
   TransactionList* getTransactionList(const BFDataGroupId& idDataGroup);
   SEVERITY settleNetworkRelateChanges(const BFDataGroupId& idDataGroup);
protected:
   virtual SEVERITY doCreateObject ( const BFData &data, 
                                     BFCBO *&pObjOut);
   virtual SEVERITY doCreateNewObject ( BFCBO *&pBase, 
                                        DString &strKey, 
                                        const BFDataGroupId &idDataGroup);
   virtual SEVERITY doApplyRelatedChanges ( const BFFieldId &idField, 
                                            const BFDataGroupId &idDataGroup);
   SEVERITY doValidateField (const BFFieldId& idField,
                             const DString& strValue,
                             const BFDataGroupId& idDataGroup);
   SEVERITY doValidateAll (const BFDataGroupId& idDataGroup, long lValidateGroup);

// member function
private:
   bool checkRespDate( const BFDataGroupId& idDataGroup );
   SEVERITY initCPFRefundRelatedFields(const BFDataGroupId& idDataGroup);

// member variable
private:
   DString _dstrTransId;
   DString _dstrTransNum;
   DString _dstrTransHistTradeDate;
   DString _dstrTransHistSettleDate;

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/DilutionAllocList.hpp-arc  $
//
//   Rev 1.10   Aug 03 2009 18:52:54   dchatcha
//PET 157825 - FN 13 - Dilution Allocation Enhancements.
// 
