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
//    AUTHOR : Serban Popescu
//    DATE   : October 2003
//
//
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************

#include <bfproc\abstractprocess.hpp>


// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

//Forward declarations
class FillSearchCriteria;
class FinancialInstitutionList;
class FinancialInstitutionTransitList;

class IFASTBP_LINKAGE FinancialInstitutionSearchProcess : public AbstractProcess
{
// Construction
public:
   FinancialInstitutionSearchProcess(GenericInterfaceContainer* pGIC, 
      GenericInterface* pGIParent, const Command& rCommand);
   virtual ~FinancialInstitutionSearchProcess();
protected:
   virtual SEVERITY doInit();
   virtual E_COMMANDRETURN doProcess();
   virtual bool doModelessChildComplete(const Command &cmd);
   virtual SEVERITY performSearch(GenericInterface *rpGI, 
      const BFContainerId& idSearch, E_SEARCHACTION eSearchAction);
   virtual bool doMoreRecordsExist(GenericInterface *rpGICaller,
      const BFContainerId& idSearch);
   virtual bool doRefresh(GenericInterface *rpGICaller, 
      const I_CHAR *szOriginalCommand)
   {
      return true;
   }
private:
   GenericInterface *_rpChildGI;
   FillSearchCriteria *_pFillSearchCriteria;
   FinancialInstitutionList *_pFinancialInstitutionList;
   FinancialInstitutionTransitList *_pFinancialInstitutionTransitList;
   DString _dstrFICategory,
      _dstrFIType, 
      _dstrFICode,
      _dstrFIName;
   SEVERITY processParameters();
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/FinancialInstitutionSearchProcess.hpp-arc  $
//
//   Rev 1.2   Jan 20 2004 18:27:48   popescu
//PET 809, FN 13,
//part backing-out bank master, 
//display the bank name in the FinancialSearchDialog caption if searching for transits
//
//   Rev 1.1   Oct 24 2003 17:18:54   popescu
//CIBC PET 809, FN 13
//
//   Rev 1.0   Oct 04 2003 16:06:12   popescu
//Initial revision.
 *
 */
