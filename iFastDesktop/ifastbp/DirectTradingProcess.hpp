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
//    DATE   : May 24, 2002
//
//
//    Copyright 2002 by International Financial Data Service.
//
//******************************************************************************


#include <bfproc\AbstractProcess.hpp>
///#endif

// Forward references
class DirectTrading;
// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif


class IFASTBP_LINKAGE DirectTradingProcess : public AbstractProcess
{
// Construction
public:
//CP20030319   DirectTradingProcess();
   DirectTradingProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~DirectTradingProcess();

protected:

   virtual void doGetField(
                          const GenericInterface *rpGICaller,
                          const BFContainerId& idContainer,
                          const BFFieldId& idField,
                          const BFDataGroupId& idDataGroup,
                          DString &strValueOut,
                          bool bFormatted
                          ) const;
   virtual SEVERITY doInit();
   virtual bool doModelessChildComplete(
                                       const Command &cmd
                                       );
   virtual bool doModelessSetFocus(
                                  GenericInterface *rpGICaller
                                  );

   virtual bool doSend(
                      GenericInterface *rpGICaller,
                      const I_CHAR *szMessage
                      ) ;
   virtual E_COMMANDRETURN doProcess();
   //virtual SEVERITY ok2( GenericInterface *rpGICaller );
   // virtual void *getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup );
   virtual SEVERITY doSetField(
                              const GenericInterface *rpGICaller,
                              const BFContainerId& idContainer,
                              const BFFieldId& idField,
                              const BFDataGroupId& idDataGroup,
                              const DString& strValue,
                              bool bFormatted
                              );
   virtual bool doOk(
                    GenericInterface *rpGICaller
                    );

   void* getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup );
   virtual SEVERITY doValidateAll(BFAbstractCBO *rpWSD,
      const BFDataGroupId& idDataGroup);

private:

   GenericInterface* _rpChildGI;
   DString _dstrAccountNum;
   DString _dstrShrNum;
   DirectTrading* _pDirectTrading;

};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/DirectTradingProcess.hpp-arc  $
//
//   Rev 1.3   Oct 28 2003 10:35:20   FENGYONG
//Override dovalidateall 
//
//   Rev 1.2   Oct 16 2003 12:09:32   FENGYONG
//no change 
//
//   Rev 1.1   Oct 16 2003 12:03:40   FENGYONG
//PET809 FN08 Direct trading enhancement
//
//   Rev 1.0   Oct 07 2003 10:13:26   FENGYONG
//Initial Revision
 */