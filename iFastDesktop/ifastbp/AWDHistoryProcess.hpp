#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2013 by International Financial, Inc.
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

class AWDHistoryWorkList;

class IFASTBP_LINKAGE AWDHistoryProcess : public AbstractProcess
{
public:
   AWDHistoryProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   ~AWDHistoryProcess(void);

protected:
   virtual SEVERITY doInit();
   virtual E_COMMANDRETURN doProcess();

   virtual void doGetField(
                          const GenericInterface *rpGICaller,
                          const BFContainerId& idContainer,
                          const BFFieldId& idField,
                          const BFDataGroupId& idDataGroup,
                          DString &strValueOut,
                          bool bFormatted
                          ) const;

   void * getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup );

   virtual void setCurrentListItem(
                                  const GenericInterface *rpGICaller,
                                  const BFContainerId& idList,
                                  const DString& strListItemKey
                                  );

private:
   GenericInterface *_rpChildGI;
   DString _accountNum;
   AWDHistoryWorkList *_pAWDHistoryWorkList;

};
