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
// ^FILE   : RESPAcctInfoProcess.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : RESPAcctInfoProcess
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

class InvestorAuthorizationList;

class IFASTBP_LINKAGE RESPAcctInfoProcess : public AbstractProcess
{
public:

   /**
   * Default constructor
   */
   RESPAcctInfoProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~RESPAcctInfoProcess(void);
    
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

   virtual SEVERITY ok2( GenericInterface *rpGICaller );
   virtual bool doCancel (GenericInterface *rpGICaller);
   
private:

   GenericInterface* _rpChildGI;
   DString           _accountNum;
   bool _bSuccessFlag;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
// $Log:   Y:/VCS/BF iFAST/ifastbp/RESPAcctInfoProcess.hpp-arc  $ 
//
//   Rev 1.2   Apr 09 2010 21:08:32   popescu
//PET165541_FN01_QESI - RESP Gap_Dsk_NASU
//
//   Rev 1.1   Mar 26 2010 09:32:46   dchatcha
//PET165541_FN01_QESI - RESP Gap_Dsk_NASU
//
//   Rev 1.0   Mar 12 2010 14:22:34   dchatcha
//Initial revision.
//


