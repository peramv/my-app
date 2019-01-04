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


#include <bfproc\AbstractProcess.hpp>
///#endif

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

class BranchList;
class GroupFundList;
class FundDetailList;
class FundDetailListLite;

class IFASTBP_LINKAGE FundClassProcess : public AbstractProcess
{
// Construction
public:

//CP20030319   FundClassProcess();
   FundClassProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~FundClassProcess();

protected:

   /**
   * Implementation for the refresh method.  Not implemented yet.
   * @param rpGICaller - A reference pointer to the calling object.
   * @param szOriginalCommand - A string literal representing the original
   * command issuing the refresh (which may provide a hint on whether this
   * object needs to check for refresh).
   * @returns true if successful, call getErrors for errors if false
   */
   virtual void doGetField(
                          const GenericInterface *rpGICaller, 
                          const BFContainerId& idContainer, 
                          const BFFieldId& idField,
                          const BFDataGroupId& idDataGroup, 
                          DString &strValueOut, 
                          bool bFormatted
                          ) const;




   virtual E_COMMANDRETURN doProcess();
   virtual SEVERITY performSearch(GenericInterface *rpGICaller, const BFContainerId& idSearch, E_SEARCHACTION eSearchAction);
   virtual bool doRefresh (GenericInterface *rpGICaller, const I_CHAR *szOriginalCommand) {
      return(false);
   }
   virtual SEVERITY doInit();
   virtual void doPostOk(GenericInterface *rpGICaller, bool bSuccessFlag );
   virtual bool doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idSearch );
   virtual SEVERITY doSetField(
                              const GenericInterface *rpGICaller,
                              const BFContainerId& idContainer,
                              const BFFieldId& idField,
                              const BFDataGroupId& idDataGroup,
                              const DString& strValue,
                              bool bFormatted
                              );
   const BFProperties *doGetFieldAttributes( const GenericInterface *rpGICaller, const BFContainerId& idContainer, const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   void  removeItemFromSubtList( const DString &dstrSubList, const DString &dstrIDValue, DString &dstrOutSubList );

private:

   GroupFundList    *m_pGroupFundList;
   FundDetailList *m_pFundDetailList;
   FundDetailListLite *m_pFundDetailListLite;
   GenericInterface  *m_rpChildGI;   
   DString m_dstrBaseFilter;
   DString m_dstrFundCode;
   DString m_dstrFundNumber;
   DString m_dstrFundClass;
   DString m_strOnlyESoPEligible;
   DString m_strManagementFee;
   DString m_strManagementFeeRebate;
   DString m_fundCategory;
   DString m_dstrSearchType;
   DString m_dstrValue;
   DString m_dstrSearchFund;
   DString m_dstrGroupCode;
   BFProperties *m_propSearchFundType;
};


///#endif 

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/*
*/