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

class MktIndexMasterList;
class FundMasterList;

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif


class IFASTBP_LINKAGE MktIndexMasterMaintProcess : public AbstractProcess
{
// Construction
public:

//CP20030319   MktIndexMasterMaintProcess();
   MktIndexMasterMaintProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~MktIndexMasterMaintProcess();

protected:

   virtual SEVERITY doInit();
   virtual bool doModelessChildComplete( const Command &cmd );
   virtual bool doModelessSetFocus( GenericInterface *rpGICaller );
   virtual E_COMMANDRETURN doProcess();
   virtual void doGetField(
                          const GenericInterface *rpGICaller,
                          const BFContainerId& idContainer,
                          const BFFieldId& idField,
                          const BFDataGroupId& idDataGroup,
                          DString &strValueOut,
                          bool bFormatted
                          ) const;
	void* getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup );
   virtual bool doOk(GenericInterface *rpGICaller);

private:

   GenericInterface *m_rpChildGI;
   MktIndexMasterList *m_pMktIndexMasterList;
   FundMasterList *m_pFundMasterList;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/*  $Log:   Y:/VCS/BF iFAST/ifastbp/MktIndexMasterMaintProcess.hpp-arc  $
//
//   Rev 1.3   Mar 21 2003 17:45:26   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.2   Feb 07 2003 14:14:04   HERNANDO
//Added Fund Master List.
//
//   Rev 1.1   Jan 31 2003 11:26:46   HERNANDO
//Added doOk.
//
//   Rev 1.0   Jan 23 2003 10:29:04   HERNANDO
//Initial Revision
 */