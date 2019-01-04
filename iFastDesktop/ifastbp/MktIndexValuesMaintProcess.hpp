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

class MktIndexValuesList;
class FundMasterList;

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif


class IFASTBP_LINKAGE MktIndexValuesMaintProcess : public AbstractProcess
{
// Construction
public:

//CP20030319   MktIndexValuesMaintProcess();
   MktIndexValuesMaintProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~MktIndexValuesMaintProcess();

protected:

   virtual SEVERITY doInit();
   virtual bool doModelessChildComplete( const Command &cmd );
   virtual bool doModelessSetFocus( GenericInterface *rpGICaller );
   virtual E_COMMANDRETURN doProcess();
	void* getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup );
   SEVERITY performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, E_SEARCHACTION eSearchAction );
   bool doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idSearch );
   virtual bool doSend(GenericInterface *rpGICaller, const I_CHAR *szMessage ) ;
   virtual bool doOk(GenericInterface *rpGICaller);
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
   MktIndexValuesList *m_pMktIndexValuesList;
   FundMasterList *m_pFundMasterList;
      
   DString m_strSearchType;
   DString	m_strIndexCode;
   DString m_strSearchFromDate;	
   MktIndexValuesList *m_pSearchMktIndexList;
   void readSearchParameters ();
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/*  $Log:   Y:/VCS/BF iFAST/ifastbp/MktIndexValuesMaintProcess.hpp-arc  $
//
//   Rev 1.6   Jan 16 2012 14:39:16   wp040027
//P0188394_Performance Fees - Benchmark Upload
//
//   Rev 1.5   Mar 21 2003 17:45:34   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.4   Feb 07 2003 14:15:22   HERNANDO
//Added Fund Master List and doGetField.
//
//   Rev 1.3   Feb 06 2003 18:16:50   HERNANDO
//Removed doGetField.
//
//   Rev 1.2   Jan 31 2003 11:27:24   HERNANDO
//Added doOk.
//
//   Rev 1.1   Jan 29 2003 18:33:14   HERNANDO
//Added doSend.
//
//   Rev 1.0   Jan 29 2003 12:51:30   HERNANDO
//Initial Revision
//
//   Rev 1.0   Jan 23 2003 10:29:04   HERNANDO
//Initial Revision
 */