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
#include <ifastbp\ifasthistoricalparameters.hpp>

class SettleLocationAcctLvlList;

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif


class IFASTBP_LINKAGE SettleLocationAcctLvlProcess : public AbstractProcess,
   public IFastHistoricalParameters
{
public:

   SettleLocationAcctLvlProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~SettleLocationAcctLvlProcess();

protected:

   virtual SEVERITY doInit();
   virtual bool doModelessChildComplete( const Command &cmd );
   virtual bool doModelessSetFocus( GenericInterface *rpGICaller );
   virtual E_COMMANDRETURN doProcess();
	void* getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup );
   virtual bool doSend(GenericInterface *rpGICaller, const I_CHAR *szMessage );
   virtual bool doOk(GenericInterface *rpGICaller);
   virtual void doGetField(
                          const GenericInterface *rpGICaller,
                          const BFContainerId& idContainer,
                          const BFFieldId& idField,
                          const BFDataGroupId& idDataGroup,
                          DString &strValueOut,
                          bool bFormatted
                          ) const;
	virtual SEVERITY getHistoricalParameters(const BFContainerId& idContainer, 
                                            BFFieldId &recordIdField, DString& tableId, DString& dstrKeys); 
   SEVERITY getHistoricalParameters( const BFContainerId& idContainer, HISTORICAL_VECTOR &vectorInput );

private:

   GenericInterface *m_rpChildGI;
   SettleLocationAcctLvlList *m_pSettleLocationAcctLvlList;
   DString m_dstrAccountNumber;
};


//***********************************************
//R E V I S I O N   C O N T R O L   E N T R I E S
//***********************************************
//  $Log:   Y:/VCS/BF iFAST/ifastbp/SettleLocationAcctLvlProcess.hpp-arc  $
//
//   Rev 1.2   Mar 10 2004 13:20:12   HERNANDO
//PET965 FN11 - Added getHistoricalParameters.
//
//   Rev 1.1   Nov 24 2003 18:19:16   HERNANDO
//Next revision.
//
//   Rev 1.0   Nov 20 2003 11:31:32   HERNANDO
//Initial revision.
