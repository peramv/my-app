#pragma once

//******************************************************************************
//
// COPYRIGHT:
//
// The computer systems, procedures, data bases and
// programs created and maintained by International Financial Data Services, Inc.,
// are proprietary in nature and as such are confIdential.
// Any unauthorized use or disclosure of such information
// may result in civil liabilities.
//
// Copyright 2009 by International Financial Data Services, Inc.
//
//
//******************************************************************************
//
// ^FILE   : InvestorAuthorization.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : June, 2009
//
// ^CLASS    : InvestorAuthorization
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

struct BankingEffectivePeriod;

class IFASTCBO_LINKAGE InvestorAuthorization : public MFCanBFCbo, private boost::noncopyable
{
public:

   InvestorAuthorization( BFAbstractCBO &parent );
   virtual ~InvestorAuthorization();

   SEVERITY init (const DString &accountNum);
   SEVERITY init( const DString &accountNum, const BFData& data );
   SEVERITY initNew ( const DString &strAccountNum,
                      const BFDataGroupId& idDataGroup );

   bool isResetRecord(const BFDataGroupId& idDataGroup);

protected:
   virtual SEVERITY doValidateField( const BFFieldId& idField, 
                                     const DString& strValue, 
                                     const BFDataGroupId& idDataGroup );
   virtual SEVERITY doApplyRelatedChanges( const BFFieldId& idField, 
                                           const BFDataGroupId& idDataGroup );

   SEVERITY doValidateAll ( const BFDataGroupId& idDataGroup, 
                            long lValidateGroup);

   SEVERITY validateEffectiveDate( const BFDataGroupId& idDataGroup );
   SEVERITY validateStopDate( const BFDataGroupId& idDataGroup );
   SEVERITY validateAgainstDDBankEffPeriod( const BFDataGroupId& idDataGroup );

private:
//helpers
   SEVERITY commonInit (const DString &accountNum, 
                        const BFDataGroupId& idDataGroup);

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
                                        
   static bool sortByEffectiveDate(const BankingEffectivePeriod& input1, 
                                   const BankingEffectivePeriod& input2);                                        
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
// 
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/InvestorAuthorization.hpp-arc  $
//
//   Rev 1.5   Nov 16 2009 05:46:24   dchatcha
//IN# 1896780 - Inactive Banking Warning Message.
//
//   Rev 1.4   Oct 19 2009 04:04:48   dchatcha
//IN# 1864779 - Rel95_PET156681_dlr_rep code, Fix issue found when reset button is pressed.
//
//   Rev 1.3   Jul 22 2009 08:51:40   dchatcha
//PET156681 FN14 H36 Investor Authorization, Code review. 
//
//   Rev 1.2   Jul 16 2009 19:36:48   dchatcha
//PET156681 FN14 H36 Investor Authorization, Integration issues.
//
//   Rev 1.1   Jul 09 2009 15:27:58   dchatcha
//PET156681 FN14 H36 Investor Authorization.
//
//   Rev 1.0   29 Jun 2009 16:26:00   popescu
//Initial revision.
//
*/
