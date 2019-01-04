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
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************
#include <bfproc/AbstractProcess.hpp>
#include <ifastbp/ifasthistoricalparameters.hpp>

// Forward references
class MFAccount;
class FundAllocList;
class AmsFundAllocList;
class DefFundAllocList;
class AmsMstrInfo;

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

class IFASTBP_LINKAGE AMSAcctLvlProcess : public AbstractProcess, public IFastHistoricalParameters
{

public:

   AMSAcctLvlProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~AMSAcctLvlProcess();

   virtual SEVERITY setField( const GenericInterface* rpGICaller,
                              const BFContainerId& idContainer,
                              const BFFieldId &fieldID,
                              const DString &strValue,
                              bool bFormatted = true );
   
protected:

   virtual bool doModelessChildComplete (const Command &cmd);
   virtual bool doModelessSetFocus (GenericInterface *rpGICaller);
   
   virtual void doGetField( const GenericInterface *rpGICaller,
                            const BFContainerId& idContainer,
                            const BFFieldId& idField,
                            const BFDataGroupId& idDataGroup,
                            DString &strValueOut,
                            bool bFormatted) const;

   virtual const BFProperties *doGetFieldAttributes ( const GenericInterface *rpGICaller, 
                                                      const BFContainerId &idContainer, 
                                                      const BFFieldId &idField, 
                                                      const BFDataGroupId &idDataGroup
                                                    );

   virtual SEVERITY doSetField(
                              const GenericInterface *rpGICaller,
                              const BFContainerId& idContainer,
                              const BFFieldId& idField,
                              const BFDataGroupId& idDataGroup,
                              const DString& strValue,
                              bool bFormatted
                              );

   virtual SEVERITY doInit();
   virtual bool doCancel( GenericInterface *rpGICaller );
   bool doOk (GenericInterface *rpGICaller);
   virtual E_COMMANDRETURN doProcess();
   void *getPtrForContainer( const BFContainerId& idContainer,
                             const BFDataGroupId& idDataGroup);

   virtual bool doSend(GenericInterface *rpGICaller, const I_CHAR *szMessage ) ;
   SEVERITY getHistoricalParameters (const BFContainerId& idContainer, HISTORICAL_VECTOR &vectorInput);

private:
   void getMasterInfoField(const BFDataGroupId& idDataGroup, const BFFieldId& idField, DString  &dstrFieldOut) const;
   AmsMstrInfo* getMasterInfo(const BFDataGroupId& idDataGroup) const;

   BFAbstractCBO *getSchedSetupFreqObj () const;

   SEVERITY getUserDefinedAMSFundAllocList (FundAllocList*& pFundAllocList, const BFDataGroupId& idDataGroup);
   
   GenericInterface *m_rpChildGI;
   DString m_dstrAccountNumber;
   DString m_dstrShrNum;
   DString m_dstrCaller;
   AmsFundAllocList *m_pAMSFundAllocList;
   DefFundAllocList *m_pAMSDefFundAllocList;
   Condition *m_pCondition;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AMSAcctLvlProcess.hpp-arc  $
//
//   Rev 1.13   Nov 25 2010 13:55:22   jankovii
//PET175778FN01 - Upstreaming Phase 2
//
//   Rev 1.12   Sep 28 2007 16:34:06   smithdav
//PET 2360  FN02 - Display AMSMaster frequency when FreqOverride is not selected.
//
//   Rev 1.11   11 Sep 2007 16:54:28   popescu
//Incident 979244 - remove the override for doValidateAll - now it validates the worksession - 
//
//   Rev 1.10   Jul 27 2007 10:26:12   smithdav
//PET 2360 FN02 - Historical Button support.
//
//   Rev 1.9   Jun 27 2007 14:48:38   porteanm
//PET 2360 FN02 - AMS acct level historical support.
//
//   Rev 1.8   Feb 04 2005 15:01:44   porteanm
//PTS 10033798 - "Should this Account be rebalanced in the next cycle" support.
//
//   Rev 1.7   Aug 18 2003 16:00:00   YINGBAOL
//add dovalidateAll
//
//   Rev 1.6   Apr 02 2003 11:59:36   HERNANDO
//Sync'd with 1.4.1.1
//
//   Rev 1.5   Mar 21 2003 17:35:50   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.4   Feb 03 2003 13:31:22   sanchez
//Define doGetErrors()
//
//   Rev 1.3   Jan 08 2003 16:37:46   sanchez
//Rebalancing Target Mix
//
//   Rev 1.2   Dec 19 2002 16:11:16   HERNANDO
//Added doModelessSetFocus.
//
//   Rev 1.1   Dec 06 2002 17:53:42   HERNANDO
//Added doCancel.
//
//   Rev 1.0   Nov 28 2002 18:35:38   HERNANDO
//Initial revision.
 * 
 */
