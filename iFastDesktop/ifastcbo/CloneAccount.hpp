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
// ^FILE   : CloneAccount.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : October, 2006
//
// ^CLASS    : CloneAccount
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

class Agent;
class Branch;
class Broker;
class TaxTypeRule;

class IFASTCBO_LINKAGE CloneAccount : public MFCanBFCbo, private boost::noncopyable
{
public:
   CloneAccount (BFAbstractCBO &parent);
   virtual ~CloneAccount();
   SEVERITY init ( const DString &accountNum, 
                   const BFDataGroupId& idDataGroup);
protected:
	virtual SEVERITY doValidateField ( const BFFieldId& idField,
                                      const DString& strValue,
                                      const BFDataGroupId& idDataGroup);
   virtual SEVERITY doApplyRelatedChanges ( const BFFieldId& idField, 
                                            const BFDataGroupId& idDataGroup);
private:
   SEVERITY validateTaxType ( const DString &taxType, 
                              const BFDataGroupId &idDataGroup);
   SEVERITY validateAcctDesignationTaxType (const BFDataGroupId &idDataGroup);
//helpers
   SEVERITY getBroker (Broker *&broker,
                       const BFDataGroupId &idDataGroup);
   SEVERITY getBranch (Branch *&branch,
                       const BFDataGroupId &idDataGroup);
   SEVERITY getAgent (Agent *&agent,
                      const BFDataGroupId &idDataGroup);
   SEVERITY getAccountField ( const BFFieldId &idField, 
                              DString &value,
                              const BFDataGroupId &idDataGroup,
                              bool formatted = false);
   SEVERITY getAccountFieldDescription ( const BFFieldId &idField, 
                                        DString &value,
                                        const BFDataGroupId &idDataGroup);
   SEVERITY getShareholderField ( const BFFieldId &idField, 
                                  DString &value,
                                  const BFDataGroupId &idDataGroup,
                                  bool formatted = false);
   SEVERITY getShareholderFieldDescription ( const BFFieldId &idField, 
                                             DString &strValue,
                                             const BFDataGroupId &idDataGroup);
   SEVERITY getTaxTypeRule ( TaxTypeRule *&taxTypeRule, 
                             const BFDataGroupId &idDataGroup);

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/CloneAccount.hpp-arc  $
//
//   Rev 1.0   Nov 08 2006 17:33:06   popescu
//Initial revision.
//
*/
