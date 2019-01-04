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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : AddrTaxJurisUpdateProcess.h
// ^AUTHOR : Wutipong W.
// ^DATE   : 14/10/2008
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : AddrTaxJurisUpdateProcess
//    
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************/



#include <bfproc\AbstractProcess.hpp>
///#endif

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

class IFASTBP_LINKAGE AddrTaxJurisUpdateProcess : public AbstractProcess  
{
public:
   AddrTaxJurisUpdateProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~AddrTaxJurisUpdateProcess();
   
protected:
   virtual void doGetField(
                          const GenericInterface *rpGICaller,
                          const BFContainerId& idContainer,
                          const BFFieldId& idField,
                          const BFDataGroupId& idDataGroup,
                          DString &strValueOut,
                          bool bFormatted
                          ) const;
   virtual SEVERITY doSetField( const GenericInterface* rpGICaller,
                                const BFContainerId& idContainer,
                                const BFFieldId &fieldID,
                                const BFDataGroupId& idDataGroup,
                                const DString &strValue,
                                bool bFormatted );
   virtual SEVERITY doInit();
   virtual bool doModelessChildComplete( const Command &cmd );
   virtual bool doModelessSetFocus( GenericInterface *rpGICaller );
   virtual E_COMMANDRETURN doProcess();
   virtual bool doOk (GenericInterface* rpGICaller);

private:
   DString m_dstrAcctNum;
   DString m_dstrShrNum;
   DString m_dstrEntityId;
   DString m_dstrSeqNum;
   
   DString m_dstrTaxJuris;
   DString m_dstrProvRes;
   
   Shareholder* m_pShareholder;
   GenericInterface *_rpChildGI;
};
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AddrTaxJurisUpdateProcess.hpp-arc  $ */
//
//   Rev 1.0   Oct 29 2008 21:14:28   wongsakw
//Initial revision.
