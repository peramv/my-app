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
//    Copyright by International Financial Data Service.
//
//******************************************************************************
#include <bfproc\AbstractProcess.hpp>
#include <ifastbp\ifasthistoricalparameters.hpp>

#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

class AcctCutOffTimesList;

class IFASTBP_LINKAGE AcctCutOffTimesProcess : public AbstractProcess, public IFastHistoricalParameters
{
public:

   AcctCutOffTimesProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~AcctCutOffTimesProcess();
   SEVERITY performSearch( GenericInterface *rpGICaller, const BFContainerId& idSearch, E_SEARCHACTION eSearchAction );
   SEVERITY getHistoricalParameters(const BFContainerId &idContainer, BFFieldId &recordIdField, DString &tableId, DString &dstrKeys);
   SEVERITY getHistoricalParameters(const BFContainerId& idContainer, HISTORICAL_VECTOR &vectorHistorical); 

protected:

   virtual SEVERITY doInit();
   virtual bool doModelessChildComplete( const Command &cmd );
   virtual bool doModelessSetFocus( GenericInterface *rpGICaller );
   virtual E_COMMANDRETURN doProcess();
   void* getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup );
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
   virtual SEVERITY doSetField( 
						const GenericInterface *rpGICaller,
                        const BFContainerId& idContainer,
                        const BFFieldId& idField,
                        const BFDataGroupId& idDataGroup,
                        const DString& strValue,
                        bool bFormatted );
   virtual bool doOk( GenericInterface *rpGICaller );

private:

   GenericInterface		*m_rpChildGI;
   AcctCutOffTimesList	*m_pCutOffTimesList;
   DString				m_dstrAccountNumber;
   DString				m_dstrEntityId;
   DString				m_dstrBrokerLevel;
   DString				m_dstrBrokerCode;
};


//***********************************************
//R E V I S I O N   C O N T R O L   E N T R I E S
//***********************************************
//  $Log:   Y:/VCS/BF iFAST/ifastbp/AcctCutOffTimesProcess.hpp-arc  $
//
//   Rev 1.2   Jul 25 2006 15:58:30   jankovii
//PET 2192 FN02 - Dealings Sender Cut Off Time.
//
//   Rev 1.1   Jul 21 2006 14:04:28   jankovii
//PET 2192 FN02 - Dealings-Sender Cut-Off Time.
//
//   Rev 1.0   Jul 05 2005 17:39:50   hernando
//Initial revision.
