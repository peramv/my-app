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
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************


#include "BrokerAMSProcess.hpp"
///#endif

// Forward references
class BrokerAMSList;
class BrokerList;
class amsmstrList;
class BrokerAMSsearch;
class AMSFundAllocList;

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

/**
 * Class that manages the Historical Market Value process.
 *
 * @author Yakov Prager
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 03/09/1999</dd></dl>
 * @version 0.1
 */

class IFASTBP_LINKAGE BrokerAMSProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   BrokerAMSProcess();
   BrokerAMSProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~BrokerAMSProcess();
   SEVERITY performSearch( GenericInterface *rpGI, const BFContainerId& idSearch,E_SEARCHACTION eSearchAction);

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
                         )
   {
      return(false);
   }

   virtual void setCurrentListItem(
                                  const GenericInterface *rpGICaller,
                                  const BFContainerId& idList,
                                  const DString& strListItemKey
                                  );
   /**
     * Implementation to support the ok method.  This method would be invoked
     * when the user completes the logon screen.  The logon process will 
     * attempt to logon and return accordingly.
     * @param rpGICaller - A reference pointer to the calling object.
     * @returns true if successful, call getErrors for errors if false
     */
   virtual void doPostOk(
                        GenericInterface *rpGICaller,
                        bool bSuccessFlag
                        );
   virtual void *getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup );
	virtual bool setCommitDataGroupAsHost()
	{
		return(true);
	};
   virtual bool doMoreRecordsExist(
                                  GenericInterface *rpGICaller, 
                                  const BFContainerId& idSearch );

	virtual bool doSend(GenericInterface *rpGICaller, const I_CHAR *szMessage ); 

	virtual void doGetField( const GenericInterface *rpGICaller,
                            const BFContainerId& idContainer,
                            const BFFieldId& idField,
                            const BFDataGroupId& idDataGroup,
                            DString &strValueOut,
                            bool bFormatted ) const;



private:

   BrokerAMSList*_pBrokerAMSList;
   BrokerList* _pBrokerList;
   AMSMstrList* _pamsmstrList;
   BrokerAMSsearch* _pBrokerAMSsearch;
   AMSFundAllocList* _pAMSFundAllocList;
   GenericInterface *_rpChildGI;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//

