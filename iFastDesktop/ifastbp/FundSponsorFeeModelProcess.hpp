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
// ^FILE   : FundSponsorFeeModelProcess.hpp
// ^AUTHOR : 
// ^DATE   : July 21, 2004  
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : FundSponsorFeeModelProcess
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

class   FeeModelList; 
class   FundSponsorFeeList;
class   Shareholder;


class IFASTBP_LINKAGE LlistParam
{
   public:
      LlistParam(BFContainerId idList);
      void setPrevKey(DString dstrPrevKey );
      const DString& getPrevKey();
      void setEndKey(DString dstrEndKey );
      const DString& getEndKey();

      UINT m_More;
      UINT m_dispNum;
      UINT m_totalNum;

   private:
      BFContainerId idList;
      DString m_dstrPrevKey;
      DString m_dstrEndKey;
};

class IFASTBP_LINKAGE FundSponsorFeeModelProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   FundSponsorFeeModelProcess();
   FundSponsorFeeModelProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~FundSponsorFeeModelProcess();


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


   virtual  bool doRefresh( GenericInterface *rpGICaller,
                            const I_CHAR *szOriginalCommand);


   void *getPtrForContainer ( const BFContainerId& idContainer, 
                              const BFDataGroupId& idDataGroup);
   virtual bool doModelessSetFocus (GenericInterface *rpGICaller);
   virtual bool doModelessChildComplete (const Command &cmd);
   virtual void doGetField( const GenericInterface *rpGICaller,
                            const BFContainerId& idContainer,
                            const BFFieldId& idField,
                            const BFDataGroupId& idDataGroup,
                            DString &strValueOut,
                            bool bFormatted) const;
   SEVERITY doSetField ( const GenericInterface *rpGICaller,
                         const BFContainerId& idContainer,
                         const BFFieldId& fieldID,
                         const BFDataGroupId& idDataGroup,
                         const DString& strValue,
                         bool bFormatted);
   virtual SEVERITY performSearch( GenericInterface *rpGI, 
                                   const BFContainerId& idSearch, 
                                   E_SEARCHACTION eSearchAction);
   virtual bool doMoreRecordsExist ( GenericInterface *rpGICaller,
                                     const BFContainerId& idSearch);
   virtual bool doOk (GenericInterface *rpGICaller);
   const DString& getFirstListItemKey( const GenericInterface *rpGICaller, const BFContainerId& idList );
   const DString& getNextListItemKey( const GenericInterface *rpGICaller, const BFContainerId& idList );
   void  adjustKey( const BFContainerId& idList );
   virtual bool doSend (GenericInterface *rpGICaller, const I_CHAR *szMessage);

private:
   void processParameters ();
   GenericInterface *_rpChildGI;
   FundSponsorFeeModelList* _pFundSponsorFeeModelList;    
   Shareholder* _pShareholder;

   DString m_frSCR,
      m_AcctNum,
      m_SearchType,
      m_FundSponsorCode,
      m_FeeModelCode,
      dstrAccountNumSubstList,
      m_AccountNumSubList;

   typedef std::map<DString, LlistParam*>LIST_MAP;
   typedef LIST_MAP::iterator LIST_MAP_ITER;
   typedef LIST_MAP::value_type LIST_MAP_VALUE_TYPE;

   LIST_MAP _listmap;

};



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/FundSponsorFeeModelProcess.hpp-arc  $
//
//   Rev 1.5   Jul 13 2005 17:37:54   popescu
//Incident 352435 - improved performance on the fund sponsor fee model screen - get rid of the wacky keys
//
//   Rev 1.4   Sep 24 2004 18:53:10   FENGYONG
//Add dosend function
//
//   Rev 1.3   Sep 21 2004 14:24:30   YINGBAOL
//PET1117 FN05  FeeModelCode for shareholder is mandatory based on the error set up
//
//   Rev 1.2   Aug 11 2004 18:40:16   FENGYONG
//PET 1117 FN05 Syncup after get files resource 
//
//   Rev 1.1   Aug 10 2004 11:12:10   FENGYONG
//PET117 FN5 - Client Condition Fee
//
//   Rev 1.0   Aug 09 2004 10:04:32   FENGYONG
//Initial revision.
//
 * 
 */
