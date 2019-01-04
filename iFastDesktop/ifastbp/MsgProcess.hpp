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

#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

class MsgProcessCBOList;

class IFASTBP_LINKAGE MsgProcess : public AbstractProcess
{
public:

   MsgProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~MsgProcess();

protected:

   virtual SEVERITY doInit();
   virtual bool doModelessChildComplete( const Command &cmd );
   virtual bool doModelessSetFocus( GenericInterface *rpGICaller );
   virtual E_COMMANDRETURN doProcess();
	void* getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup );
   SEVERITY performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, E_SEARCHACTION eSearchAction );
   bool doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idSearch );
   virtual bool doSend(GenericInterface *rpGICaller, const I_CHAR *szMessage ) ;
   virtual void doGetField(
                          const GenericInterface *rpGICaller,
                          const BFContainerId& idContainer,
                          const BFFieldId& idField,
                          const BFDataGroupId& idDataGroup,
                          DString &strValueOut,
                          bool bFormatted
                          ) const;

private:

   GenericInterface *m_rpChildGI;
   MsgProcessCBOList *m_pMsgProcessList;
   DString DisableAggrOrder;
   DString DisableTrade;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//  $Log:   Y:/VCS/BF iFAST/ifastbp/MsgProcess.hpp-arc  $
//
//   Rev 1.1   Feb 22 2005 14:49:02   hernando
//PET1117 FN66-68 - Added DisableTrade and DisableAggrOrder parameters.
//
//   Rev 1.0   Feb 21 2005 11:09:10   hernando
//Initial revision.
