#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Canada, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2001 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : AcctSplitCommRep.hpp
// ^AUTHOR : 
// ^DATE   : Aug 22, 2001
//
// ^CLASS    : AcctSplitCommRep
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class AcctSplitCommList;
class Broker;

class IFASTCBO_LINKAGE AcctSplitCommRep : public MFCanBFCbo, private boost::noncopyable
{
public:

   /**
    * Constructor
    * @param   BFBase *parent - Pointer to the calling class.
    */
   AcctSplitCommRep( BFAbstractCBO &parent );

   /**
    * Destructor
    */
   ~AcctSplitCommRep();

   /**
    * Initializes the CBO based on the data object passed in.
    * @param   const Data& data - data passed in from the list class
    * @param   bool bBaseDelete - flag to determine who deletes the CBO
    * @return  SEVERITY if view call failed, NO_CONDITION if view passed.
    */
   SEVERITY init( const BFData& data, bool bBaseDelete = false );   

protected:
   SEVERITY doValidateField( const BFFieldId& idField, 
                             const DString& strValue, 
                             const BFDataGroupId& idDataGroup );

   SEVERITY doApplyRelatedChanges( const BFFieldId& idField, 
                                   const BFDataGroupId& idDataGroup );   

   void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );   

   SEVERITY validateBlockTransfer( const DString& brokerCode, 
                                   const DString& branchCode,
                                   const DString& slsRep, 
                                   const BFDataGroupId& idDataGroup );
   SEVERITY getServiceBroker ( Broker *&pBroker, 
                               const DString& dstrBrokerCode,
                               const BFDataGroupId &idDataGroup );
   SEVERITY getBroker ( Broker *&pBroker, 
                        const DString& dstrBrokerCode,
                        const BFDataGroupId &idDataGroup );
   SEVERITY validateSalesrepFund( const DString& dstrBroker,
                                  const DString& dstrBranch,
                                  const DString& dstrSlsRep,
                                  const DString& dstrFund, 
                                  const DString& dstrClass, 
                                  const BFDataGroupId& idDataGroup );
   SEVERITY updateSvcAgentRelatedChanges(const BFDataGroupId &idDataGroup); 
   SEVERITY validateServiceAgentUpdated(const BFDataGroupId &idDataGroup);

   virtual SEVERITY doValidateAll ( const BFDataGroupId &idDataGroup, 
                                    long lValidateGroup);   

private:

   bool slsRepByBranch ( const BFDataGroupId& idDataGroup );

   SEVERITY checkAgents( const DString& slsrepCode, 
                         const BFDataGroupId& idDataGroup,
                         bool condition_returned );

   SEVERITY checkBroker( const DString& brokerCode, 
                         const BFDataGroupId& idDataGroup,
                         bool condition_returned );

   SEVERITY checkBranches( const DString& branchCode, 
                           const BFDataGroupId& idDataGroup,
                           bool condition_returned );

   void allFieldsReadOnly( bool benable, const BFDataGroupId& idDataGroup );

   void setFieldsInvalid ( DString dstrCommEntType, const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   bool isSameCompensationServiceAgent( const BFDataGroupId& idDataGroup);

   DString _salesRepByBranch;
   DString _brokerName;
   DString _branchName;
   DString _branchCode;
   DString _agentName;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AcctSplitCommRep.hpp-arc  $
//
//   Rev 1.11   Jul 09 2012 19:20:20   dchatcha
//IN# 2994672 - Block Service Unit Transfers.
//
//   Rev 1.10   May 18 2012 15:22:38   dchatcha
//P0186479 FN10 -Gap 14G - Block Service Unit Transfers, revise code.
//
//   Rev 1.9   May 14 2012 15:41:36   dchatcha
//P0186479 FN10 -Gap 14G - Block Service Unit Transfers.
//
//   Rev 1.8   Mar 21 2003 17:56:12   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.7   Oct 09 2002 23:53:58   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.6   Aug 29 2002 12:51:40   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.5   Aug 08 2002 15:07:32   HSUCHIN
//added function setfieldsinvalid to set a group of fields to invalid state
//
//   Rev 1.4   22 May 2002 18:21:48   PURDYECH
//BFData Implementation
//
//   Rev 1.3   19 Mar 2002 13:14:56   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.2   25 Sep 2001 15:10:20   HSUCHIN
//removed dopresetfield and changed logic for renunciation calculation
//
//   Rev 1.1   29 Aug 2001 16:11:38   HSUCHIN
//added enhancements and validation
//
//   Rev 1.0   23 Aug 2001 14:51:40   HSUCHIN
//Initial revision.
*/
