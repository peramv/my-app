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
//    Copyright 2002 by International Financial.
//
//******************************************************************************

//******************************************************************************
//
// ^FILE   : HoldingCompProcess.hpp
// ^AUTHOR : 
// ^DATE   : July 21, 2004  
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : HoldingCompProcess
//    This class manages the Fee Parameters process.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include <bfproc/abstractprocess.hpp>
#include <ifastbp/ifasthistoricalparameters.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

class   HoldingCompList; 

class IFASTBP_LINKAGE HoldingCompProcess : public AbstractProcess, public IFastHistoricalParameters
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   HoldingCompProcess();
   HoldingCompProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~HoldingCompProcess();
	virtual bool setCommitDataGroupAsHost()
	{
		return(true);
	};

   virtual void doGetField(const GenericInterface *rpGICaller,
                  const BFContainerId& idContainer,
                  const BFFieldId& idField,
                  const BFDataGroupId& idDataGroup, 
                  DString &strValueOut,
                  bool bFormatted) const;

   virtual SEVERITY doSetField(const GenericInterface *rpGICaller,
                        const BFContainerId& idContainer,
                        const BFFieldId& idField,
                        const BFDataGroupId& idDataGroup,
                        const DString& strValue,
                        bool bFormatted);
   SEVERITY getHistoricalParameters(const BFContainerId &idContainer, BFFieldId &recordIdField, DString &tableId, DString &dstrKeys);
   SEVERITY getHistoricalParameters(const BFContainerId& idContainer, HISTORICAL_VECTOR &vectorHistorical);
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


   virtual  bool doRefresh(
                          GenericInterface *rpGICaller,
                          const I_CHAR *szOriginalCommand
                          );


   void *getPtrForContainer(const BFContainerId& idContainer, const BFDataGroupId& idDataGroup);

   virtual bool doModelessSetFocus( GenericInterface *rpGICaller );
   virtual bool doModelessChildComplete( const Command &cmd );
   virtual SEVERITY HoldingCompProcess::performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, 
                                                    E_SEARCHACTION eSearchAction );

   virtual bool doMoreRecordsExist(GenericInterface *rpGICaller,
                                   const BFContainerId& idSearch );

   virtual bool doOk( GenericInterface *rpGICaller );
   const DString& getFirstListItemKey( const GenericInterface *rpGICaller, const BFContainerId& idList );
   const DString& getNextListItemKey( const GenericInterface *rpGICaller, const BFContainerId& idList );
   void  adjustKey();
   void  doPostOk(GenericInterface *rpGICaller, bool bSuccessFlag);
private:
   GenericInterface *_rpChildGI;
   HoldingCompList* _pHoldingCompList; 
   DString m_dstrEndKey;
   DString m_dstrPrevKey;
   double m_dispNum;
   double m_More;
   double m_totalNum;
   DString m_frSCR;
	DString m_dstrEmptykey;   
   DString m_SrcHoldingCompCode;
   DString m_SrcHoldingCompName;
   DString m_SearchAll;
   DString m_AsofDate;
   bool m_bHasMore;
   bool isProcSupport;
};

