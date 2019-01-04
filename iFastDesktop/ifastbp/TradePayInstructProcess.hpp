#pragma once

//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1997 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : TradePayInstructProcess.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : August, 2006
//
// ----------------------------------------------------------
//
// ^CLASS    : TradePayInstructProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  
//
//******************************************************************************


#include <bfproc\AbstractProcess.hpp>
///#endif

// Forward references
class TradePayInstructList;
class Trade;
class MFAccount;

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

class IFASTBP_LINKAGE TradePayInstructProcess : public AbstractProcess
{
// Construction
public:
   TradePayInstructProcess ( GenericInterfaceContainer *pGIC, 
                             GenericInterface *pGIParent, 
                             const Command& rCommand);
   virtual ~TradePayInstructProcess();
protected:
   virtual void doGetField( const GenericInterface *rpGICaller,
                            const BFContainerId& idContainer,
                            const BFFieldId& idField,
                            const BFDataGroupId& idDataGroup,
                            DString &strValueOut,
                            bool bFormatted) const;
   virtual SEVERITY doInit();
   virtual E_COMMANDRETURN doProcess();
   virtual bool doModelessChildComplete (const Command &cmd);
   virtual bool doModelessSetFocus (GenericInterface *rpGICaller);
   virtual SEVERITY doSetField( const GenericInterface *rpGICaller,
                                const BFContainerId& idContainer,
                                const BFFieldId& idField,
                                const BFDataGroupId& idDataGroup,
                                const DString& strValue,
                                bool bFormatted);

   void * getPtrForContainer ( const BFContainerId &idContainer, 
                               const BFDataGroupId &idDataGroup);
   virtual bool doOk (GenericInterface *rpGICaller);
   virtual void doPostOk ( GenericInterface *rpGICaller, 
                           bool bSuccessFlag);
   virtual SEVERITY doValidateAll ( BFAbstractCBO *rpWSD, 
                                    const BFDataGroupId& idDataGroup); 

private:     
   GenericInterface *_rpChildGI;
   DString _transNum,
      _caller,
      _listKey,
      _accountNum;
   TradePayInstructList *_pTradePayInstructList;
   Trade *_pDummyTrade;
   MFAccount *_pMFAccount;
};

///#endif 
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/TradePayInstructProcess.hpp-arc  $
//
//   Rev 1.2   Sep 22 2006 00:46:52   popescu
//STP 2217/13
//
//   Rev 1.1   Sep 21 2006 01:50:10   popescu
//STP PET 2217/13
//
//   Rev 1.0   Aug 29 2006 18:25:56   popescu
//Initial revision.
//
 */
