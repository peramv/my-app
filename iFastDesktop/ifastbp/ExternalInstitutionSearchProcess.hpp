#pragma once

//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by IFDS Co., Ltd.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2016 by IFDS Co., Ltd.
//
//******************************************************************************

#include <bfproc\AbstractProcess.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif
class ExternalInstitutionList;

class IFASTBP_LINKAGE ExternalInstitutionSearchProcess : public AbstractProcess
{
// Construction
public:

   ExternalInstitutionSearchProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~ExternalInstitutionSearchProcess();

protected:

   /**
   * Implementation for the refresh method.  Not implemented yet.
   * @param rpGICaller - A reference pointer to the calling object.
   * @param szOriginalCommand - A string literal representing the original
   * command issuing the refresh (which may provide a hint on whether this
   * object needs to check for refresh).
   * @returns true if successful, call getErrors for errors if false
   */
   virtual void doGetField(
                          const GenericInterface *rpGICaller, 
                          const BFContainerId& idContainer, 
                          const BFFieldId& idField,
                          const BFDataGroupId& idDataGroup, 
                          DString &strValueOut, 
                          bool bFormatted
                          ) const;

   virtual E_COMMANDRETURN doProcess();
   virtual SEVERITY performSearch(GenericInterface *rpGICaller, const BFContainerId& idSearch, E_SEARCHACTION eSearchAction);
   virtual bool doRefresh (GenericInterface *rpGICaller, const I_CHAR *szOriginalCommand) {
      return(false);
   }
   virtual SEVERITY doInit();
   virtual void doPostOk(GenericInterface *rpGICaller, bool bSuccessFlag );
   virtual bool doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idSearch );
   virtual SEVERITY doSetField(
                              const GenericInterface *rpGICaller,
                              const BFContainerId& idContainer,
                              const BFFieldId& idField,
                              const BFDataGroupId& idDataGroup,
                              const DString& strValue,
                              bool bFormatted
                              );
   const BFProperties *doGetFieldAttributes( const GenericInterface *rpGICaller, 
                                             const BFContainerId& idContainer, 
                                             const BFFieldId& idField, 
                                             const BFDataGroupId& idDataGroup );

   virtual void *getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup );

private:

   virtual bool doModelessSetFocus( GenericInterface *rpGICaller );
   virtual bool doModelessChildComplete( const Command &cmd );

   GenericInterface *m_rpChildGI;
   DString _searchExternalInstitution;
   DString _searchExternalInstitutionUsing;
   DString _searchKey;
   DString _TradeListKey;
   DString _caller;

   BFProperties* _fPropExternalInstitution;
   BFProperties* _fPropSearchExternalInstitution;
   BFProperties* _fPropSearchExternalInstitutionUsing;
   BFProperties* _fPropKeyString;

   ExternalInstitutionList* _pExternalInstitutionList;

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastbp/ExternalInstitutionSearchProcess.hpp-arc  $
// 
