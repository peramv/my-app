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
//    Copyright 2009 by International Financial Data Services.
//
//******************************************************************************
//
// ^FILE   : InvestorAuthorizationInfoProcess.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : InvestorAuthorizationInfoProcess
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

class IFASTBP_LINKAGE InvestorAuthorizationInfoProcess : public AbstractProcess , public IFastHistoricalParameters
{
public:

   /**
   * Default constructor
   */
   InvestorAuthorizationInfoProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~InvestorAuthorizationInfoProcess(void);
    
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

   virtual bool doOk( GenericInterface *rpGICaller );

   virtual SEVERITY getHistoricalParameters ( const BFContainerId &idContainer,
                                              BFFieldId &recordIdField, 
                                              DString &tableId, 
                                              DString &dstrKeys);

   virtual SEVERITY getHistoricalParameters( const BFContainerId& idContainer, 
                                             HISTORICAL_VECTOR &vectorInput );

private:

   GenericInterface* _rpChildGI;
   DString           _accountNum;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
// $Log:   Y:/VCS/BF iFAST/ifastbp/InvestorAuthorizationInfoProcess.hpp-arc  $ 
//
//   Rev 1.0   Jul 09 2009 14:41:46   dchatcha
//Initial revision.
//

