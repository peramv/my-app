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
// ^FILE      : PayToEntity.hpp
// ^AUTHOR    : Serban Popescu
// ^DATE      : June 2003
//
// ^CLASS     : PayToEntity
// ^SUBCLASS  :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
///#endif

#include <ifastdataimpl\dse_dstc0258_vw.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class Broker;

class IFASTCBO_LINKAGE PayToEntity : public MFCanBFCbo, private boost::noncopyable
{
public:
   PayToEntity( BFAbstractCBO &parent );
   virtual ~PayToEntity();

   SEVERITY init (const BFData &viewData, const DString &searchTypeMgmt = NULL_STRING);
   SEVERITY init ( const DString &dstrBrokerCode, 
                   const BFDataGroupId &idDataGroup, 
                   const DString &searchTypeMgmt = NULL_STRING);
   SEVERITY validatePayToEntity (const BFDataGroupId &idDataGroup);

   virtual SEVERITY setField ( const BFFieldId &idField, 
                               const DString &dstrValue,
                               const BFDataGroupId &idDataGroup, 
                               bool bFormatted = true, 
                               bool bSideEffect = false, 
                               bool bCheckCurrentValue = true);

protected:
   virtual SEVERITY doValidateField ( const BFFieldId& idField, 
                                      const DString& strValue, 
                                      const BFDataGroupId& idDataGroup);
   virtual SEVERITY doApplyRelatedChanges ( const BFFieldId& idField, 
                                            const BFDataGroupId& idDataGroup);
   virtual void doInitWithDefaultValues (const BFDataGroupId& idDataGroup);
   void doReset (const BFDataGroupId &idDataGroup);

private:
   SEVERITY getBroker ( Broker *&pBroker,
                        const BFDataGroupId &idDataGroup);
   SEVERITY setPaymentForSubSet (const BFDataGroupId &idDataGroup);
   SEVERITY setBrokerName ( const DString &brokerCode, 
                            const BFDataGroupId &idDataGroup,
                            bool checkEffective = false);
   SEVERITY commonInit ( const DString &dstrBrokerCode, 
                         const BFDataGroupId &idDataGroup);
   SEVERITY duplicateCheck(const BFDataGroupId &idDataGroup); 

   bool isMgtCoPayToEntity ();
   bool _isNoSplitCommissionEnvironment;
   DString _searchType;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/PayToEntity.hpp-arc  $
//
//   Rev 1.8   Jun 11 2008 06:41:50   daechach
//in#1222106 - Stop Dates not picking up properly in Pay Entities and Pay Instructions
//
//   Rev 1.7   May 01 2007 10:27:10   jankovii
//IN 862766 - Payment instr.
//
//   Rev 1.6   Sep 07 2006 21:37:56   popescu
//STP 2192/02
//
//   Rev 1.5   Jul 27 2006 18:01:46   ZHANGCEL
//PET2192 FN11 - Commission Payments to MgmtCo related changes
//
//   Rev 1.4   Nov 14 2004 14:50:56   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.3   Apr 05 2004 17:29:48   FENGYONG
//PET944 FN01, release 56.1 NSCC Broker Matrix
//
//   Rev 1.2   Mar 04 2004 17:49:00   popescu
//PTS 10027865, fixed crash in Pay to entity search for inactive brokers. Disabled 'Instructions' button in pay to entity dialog if broker is inactive/not effective
//
//   Rev 1.1   Aug 07 2003 14:59:18   popescu
//PTS 10020472 and added validation for pay to entity. User cannot set-up a pay to entity record if there are no payment instructions records at the pay to entity level
//
//   Rev 1.0   Jun 27 2003 18:16:50   popescu
//Initial revision.
 */