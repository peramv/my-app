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
// ^FILE   : FundBrokerProcess.hpp
// ^AUTHOR : 
// ^DATE   : July 21, 2004  
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : FundBrokerProcess
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

class   FundBrokerList;
class   FundBrokerFeeList;
class   WorkSessionEntityList;

class IFASTBP_LINKAGE FundBrokerProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   FundBrokerProcess();
   FundBrokerProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~FundBrokerProcess();


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


   void *getPtrForContainer(
                           const BFContainerId& idContainer, const BFDataGroupId& idDataGroup
                           );

   virtual bool doModelessSetFocus( GenericInterface *rpGICaller );
   virtual bool doModelessChildComplete( const Command &cmd );
   virtual void doGetField(
                          const GenericInterface *rpGICaller,
                          const BFContainerId& idContainer,
                          const BFFieldId& idField,
                          const BFDataGroupId& idDataGroup,
                          DString &strValueOut,
                          bool bFormatted
                          ) const;
   SEVERITY doSetField( const GenericInterface *rpGICaller,
                                        const BFContainerId& idContainer,
                                        const BFFieldId& fieldID,
                                        const BFDataGroupId& idDataGroup,
                                        const DString& strValue,
                                        bool bFormatted );

   virtual SEVERITY performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, 
                                                    E_SEARCHACTION eSearchAction );

   virtual bool doMoreRecordsExist(GenericInterface *rpGICaller,
                                   const BFContainerId& idSearch );

   virtual bool doOk( GenericInterface *rpGICaller );
   const DString& getFirstListItemKey( const GenericInterface *rpGICaller, const BFContainerId& idList );
   const DString& getNextListItemKey( const GenericInterface *rpGICaller, const BFContainerId& idList );
   void  adjustKey( const BFContainerId& idList );
   virtual bool doSend(GenericInterface *rpGICaller, const I_CHAR *szMessage ) ;
   SEVERITY doValidateAll(BFAbstractCBO *rpWSD, const BFDataGroupId& idDataGroup);

private:
   GenericInterface *_rpChildGI;
   DString _pContact;
   FundBrokerList * _pFundBrokerList;
   WorkSessionEntityList* _pWorkSessionEntityList;
   FundBrokerFeeList * _pFundBrokerFeeList;
   
   DString m_SearchType;
   DString m_FundBrokerCode;
   DString m_FundBrokerName;

};



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/FundBrokerProcess.hpp-arc  $
//
//   Rev 1.3   Nov 30 2004 13:05:20   Fengyong
//Add setfundtoinvestor
//
//   Rev 1.2   Nov 18 2004 09:51:22   Fengyong
//Add parameters
//
//   Rev 1.1   Nov 04 2004 10:59:44   FENGYONG
//PET1117 FN54 - Fund broker static temp check in for 59 build
//
//   Rev 1.0   Oct 19 2004 14:41:50   FENGYONG
//Initial revision.
 * 
 */
