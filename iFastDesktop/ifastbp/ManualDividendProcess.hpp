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
//    AUTHOR : 
//    DATE   : 
//
//
//    Copyright 2003 by International Financial Data Service.
//
//******************************************************************************
#include <bfproc\AbstractProcess.hpp>
///#endif

class ManualDividendList;

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif


class IFASTBP_LINKAGE ManualDividendProcess : public AbstractProcess
{
// Construction
public:

//CP20030319   ManualDividendProcess();
   ManualDividendProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~ManualDividendProcess();

protected:

   virtual SEVERITY doInit();
   virtual bool doModelessChildComplete( const Command &cmd );
   virtual bool doModelessSetFocus( GenericInterface *rpGICaller );
   virtual E_COMMANDRETURN doProcess();
	void* getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup );
   virtual bool doSend(GenericInterface *rpGICaller, const I_CHAR *szMessage ) ;
   virtual bool doOk(GenericInterface *rpGICaller);
   virtual void doGetField(const GenericInterface *rpGICaller,
                          const BFContainerId& idContainer,
                          const BFFieldId& idField,
                          const BFDataGroupId& idDataGroup,
                          DString &strValueOut,
                          bool bFormatted
                          ) const;

private:

   GenericInterface *m_rpChildGI;
   ManualDividendList *m_pManualDividendList;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/*  $Log:   Y:/VCS/BF iFAST/ifastbp/ManualDividendProcess.hpp-arc  $
//
//   Rev 1.0   May 22 2003 17:01:14   HERNANDO
//Initial revision.
 */