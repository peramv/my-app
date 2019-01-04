#pragma once

//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2010 by International Financial Data Services.
//
//******************************************************************************
//
// ^FILE   : AcctGuaranteeGuardOptProcess.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : AcctGuaranteeGuardOptProcess
// 
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include <bfproc\abstractprocess.hpp>
#include <ifastbp\ifasthistoricalparameters.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

class AcctGuaranteeGuardOptList;

class IFASTBP_LINKAGE AcctGuaranteeGuardOptProcess : public AbstractProcess /*, public IFastHistoricalParameters*/
{
public:

   /**
   * Default constructor
   */
   AcctGuaranteeGuardOptProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~AcctGuaranteeGuardOptProcess(void);
    
protected:

   virtual SEVERITY doInit();
   virtual E_COMMANDRETURN doProcess();

   virtual  bool doRefresh( GenericInterface *rpGICaller,
                            const I_CHAR *szOriginalCommand );


   void *getPtrForContainer( const BFContainerId& idContainer, 
                             const BFDataGroupId& idDataGroup );

   virtual bool doModelessSetFocus( GenericInterface *rpGICaller );
   virtual bool doModelessChildComplete( const Command &cmd );
   virtual void doGetField( const GenericInterface *rpGICaller,
                            const BFContainerId& idContainer,
                            const BFFieldId& idField,
                            const BFDataGroupId& idDataGroup,
                            DString &strValueOut,
                            bool bFormatted ) const;

   virtual SEVERITY doSetField( const GenericInterface *rpGICaller,
                                const BFContainerId& idContainer,
                                const BFFieldId& idField,
                                const BFDataGroupId& idDataGroup,
                                const DString& strValue,
                                bool  bFormatted );

   virtual bool doOk( GenericInterface *rpGICaller );

   virtual SEVERITY performSearch( GenericInterface *rpGI, 
                                   const BFContainerId& idSearch, 
                                   E_SEARCHACTION eSearchAction );

   virtual bool doMoreRecordsExist( GenericInterface *rpGICaller, 
                                    const BFContainerId& idSearch );

private:

   GenericInterface* _rpChildGI;
   DString           _accountNum;
   AcctGuaranteeGuardOptList* _pAcctGuaranteeGuardOptList;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
// $Log:   Y:/VCS/BF iFAST/ifastbp/AcctGuaranteeGuardOptProcess.hpp-arc  $ 
//
//   Rev 1.1   Sep 17 2010 05:36:16   kitticha
//Cleaning the dirty comments.
//
//   Rev 1.0   Sep 17 2010 05:26:54   kitticha
//Initial revision.
//