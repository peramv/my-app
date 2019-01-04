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
//    Copyright 2000 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : AggregatedOrderProcess.hpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 07/15/2004
//
// ----------------------------------------------------------
//
// ^CLASS    : AggregatedOrderProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  
//
//******************************************************************************


#include <bfproc\AbstractProcess.hpp>
#include <ifastbp/ifasthistoricalparameters.hpp>


// Forward references
class AggregatedOrderList;
class PendingTradeList;
// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

/**
 * Class that manages the entity process.
 *
 * @author 
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 03/04/1999</dd></dl>
 * @version 0.1
 */

class AggregatedOrderList;
class AggregatedOrder;
class PendingTradeList;
class FundDetailList;
class IFASTBP_LINKAGE AggregatedOrderProcess : public AbstractProcess, public IFastHistoricalParameters
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   AggregatedOrderProcess();
   AggregatedOrderProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~AggregatedOrderProcess();

protected:
   /**
    * Set up the list and get parameters.
    * @returns SEVERITY noting any error/warning conditions
    */
   virtual SEVERITY doInit();
   /**
     * Implementation to support the process method.
     * @returns an enum representing the return type
     */
   virtual E_COMMANDRETURN doProcess();
   /**
     * Implementation for the refresh method.  Not implemented yet.
     * @param rpGICaller - A reference pointer to the calling object.
     * @param szOriginalCommand - A string literal representing the original
     * command issuing the refresh (which may provide a hint on whether this
     * object needs to check for refresh).
     * @returns true if successful, call getErrors for errors if false
     */
   virtual bool doRefresh(
                         GenericInterface *rpGICaller,
                         const I_CHAR *szOriginalCommand
                         );

   virtual bool doModelessSetFocus(
                                  GenericInterface *rpGICaller
                                  );
   /**
     * Implementation to support the modelessChildComplete method.
     * modelessChildComplete is used by the GenericInterfaceContainer to tell
     * the parent that the modeless child has been destroyed.
     * @param cmd - A reference to a command representing the object that has
     * been destroyed.
     * @returns true if this modeless object should end as well, false if not
     * done yet.  When returning true, the calling modelessChildComplete method
     * will call GenericInterfaceContainer::modelessDestroySelf to delete and
     * remove this object from the container
     */
   virtual bool doModelessChildComplete(
                                       const Command &cmd
                                       );
      
   virtual void doGetField(
                          const GenericInterface *rpGICaller,
                          const BFContainerId& idContainer,
                          const BFFieldId& idField,
                          const BFDataGroupId& idDataGroup,
                          DString &strValueOut,
                          bool bFormatted
                          ) const;


	virtual void *getPtrForContainer(const BFContainerId &idContainer,
												const BFDataGroupId &idDataGroup );
	virtual bool doMoreRecordsExist( GenericInterface *rpGICaller,
												const BFContainerId &idSearch);
	virtual SEVERITY performSearch(GenericInterface *rpGICaller, 
												const BFContainerId& idSearch, E_SEARCHACTION eSearchAction);
	//virtual SEVERITY doValidateAll(BFAbstractCBO *rpWSD, const BFDataGroupId &idDataGroup);

	virtual bool doSend( GenericInterface* rpGICaller,const I_CHAR* szMessage );
	virtual bool doOk( GenericInterface *rpGICaller );

	virtual SEVERITY getHistoricalParameters (	const BFContainerId &idContainer, 
																BFFieldId &recordIdField, 
																DString &tableId, 
                                                DString &dstrKeys ) ;
	virtual SEVERITY getHistoricalParameters (	const BFContainerId &idContainer, 
                                                HISTORICAL_VECTOR &vectorHistorical ) ; 
                                                        
public:

	FundDetailList* _pFundDetailList;
	PendingTradeList* _pPendingTradeList;
	DString _dstrAggrOrderNum;

private:

   // Private member function

	SEVERITY processParameters();
   // Private member data
   AggregatedOrderList *_pAggregatedOrderList;
	AggregatedOrder * _pAggregatedOrder;
   GenericInterface *_rpChildGI;
	DString _dstrBrokerCode;
	DString _dstrStatus;
	DString _dstrFundCode;
	DString _dstrSearchType;
	DString _dstrRoutingRefNum;
	DString _dstrFromDate;
	DString _dstrToDate;
	DString strKey;
   DString _DisableMsg;
};


///#endif 

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AggregatedOrderProcess.hpp-arc  $
//
//   Rev 1.8   Oct 05 2005 10:37:14   AGUILAAM
//PET1286_FN02_Verification of Aggregated Order Fund Price
//
//   Rev 1.7   May 04 2005 16:48:48   hernando
//Incident 303637 - Added parameter, DisableMsg.
//
//   Rev 1.6   Feb 22 2005 15:14:46   ZHANGCEL
//Incident #248320 -- Disable <Refresh> button on Confirmation screen for AggaregatedOrder
//
//   Rev 1.5   Feb 02 2005 15:50:42   zhangcel
//PTS Ticket 10038398 -- fix crash when hit <Cancel> on Confirmation Screen
//
//   Rev 1.4   Dec 10 2004 13:59:10   zhangcel
//PET1117 FN8 -- Refresh PendingTrade list issue
//
//   Rev 1.3   Dec 09 2004 17:57:52   zhangcel
//PET1117 FN08 -- More code
//
//   Rev 1.2   Dec 07 2004 09:51:14   zhangcel
//PET1117 - FN8 -- Added PerformeSearch 
//
//   Rev 1.1   Dec 06 2004 11:40:36   zhangcel
//PET1117 FN8 -- More code for the enhancement
//
//   Rev 1.0   Nov 18 2004 17:22:04   zhangcel
//Initial revision.
//
 *
 */
