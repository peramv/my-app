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
//
// ^FILE   : RegDocumentListProcess.hpp
// ^AUTHOR :  
// ^DATE   : 
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : RegDocumentListProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include <bfproc\AbstractProcess.hpp>
#include <ifastbp\ifasthistoricalparameters.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

class RegDocumentList;

class IFASTBP_LINKAGE RegDocumentListProcess : public AbstractProcess,
   public IFastHistoricalParameters
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   AcctCategoryProcess();
   RegDocumentListProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~RegDocumentListProcess();

   virtual SEVERITY doInit();
   virtual bool doModelessChildComplete (const Command &cmd);
   virtual bool doModelessSetFocus(GenericInterface *rpGICaller);
   virtual E_COMMANDRETURN doProcess();
   void *getPtrForContainer (const BFContainerId& idContainer,const BFDataGroupId& idDataGroup);

   virtual SEVERITY getHistoricalParameters ( const BFContainerId& idContainer, 
                                              BFFieldId &recordIdField,
                                              DString& tableId, 
                                              DString& dstrKeys); 
   virtual SEVERITY getHistoricalParameters (const BFContainerId& idContainer, HISTORICAL_VECTOR &vectorInput);
   virtual void doGetField ( const GenericInterface *rpGICaller,
                             const BFContainerId &idContainer, 
                             const BFFieldId &idField,
                             const BFDataGroupId &idDataGroup, 
                             DString &strValueOut,
                             bool bFormatted) const;
   virtual bool doOk (GenericInterface *rpGICaller);
   virtual SEVERITY doSetField ( const GenericInterface *rpGICaller,
                                 const BFContainerId &idContainer, 
                                 const BFFieldId &idField,
                                 const BFDataGroupId &idDataGroup, 
                                 const DString &strValue,
                                 bool bFormatted);
   const BFProperties *doGetFieldAttributes ( const GenericInterface *rpGICaller, 
                                              const BFContainerId &idContainer, 
                                              const BFFieldId &idField, 
                                              const BFDataGroupId &idDataGroup);
protected:
    virtual bool doMoreRecordsExist(GenericInterface *rpGICaller,
                                    const BFContainerId& idBFContainerId );
    SEVERITY performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, E_SEARCHACTION eSearchAction );

private:
   GenericInterface *_rpChildGI;
   DString m_strAcctNum,
           m_strEntityId,
           m_strNewShareholder,
           m_strNewAccount,
           m_strComplyRule;

   BFProperties *m_propEntityNames;
   RegDocumentList *m_pDummyRegulatoryStandardList;

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastbp/RegDocumentListProcess.hpp-arc  $
//
//   Rev 1.9   Jul 23 2012 12:23:32   wutipong
//PETP0179630_FN01 FATCA Account Entity Document Tracking
//
//   Rev 1.8   Apr 24 2009 04:19:38   dchatcha
//IN 1653090 - The KYC screen need to made mandatory in the NASU process.
//
//   Rev 1.7   03 Nov 2008 17:32:24   popescu
//KYC/AML - Joint accounts feature - after System Integrated Testing
//
//   Rev 1.6   31 Oct 2008 16:17:24   popescu
//KYC/AML - joint accounts feature
//
//   Rev 1.5   28 Oct 2008 13:11:56   popescu
//PET 59888 FN03 AML KYC - check in to fix complile issues
//
//   Rev 1.4   Oct 28 2008 08:27:06   jankovii
//PET 59888 FN03 AML KYC.
//
//   Rev 1.3   Aug 29 2008 14:30:48   jankovii
//IN 1388930.
//
//   Rev 1.2   Aug 01 2008 09:34:40   jankovii
//PET 59888 FN01 AML Enhancement.
 */
