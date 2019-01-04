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
class FinancialInstitution;
class FinancialInstitutionList;
class FinancialInstitutionTransitList;

class IFASTBP_LINKAGE TransitsProcess : public AbstractProcess
{
// Construction
public:
   TransitsProcess (GenericInterfaceContainer* pGIC, 
      GenericInterface* pGIParent, const Command& rCommand);
   virtual ~TransitsProcess ();
protected:
   virtual SEVERITY doInit ();
   virtual E_COMMANDRETURN doProcess ();
   virtual bool doModelessChildComplete (const Command &cmd);
   virtual bool doMoreRecordsExist (GenericInterface *rpGICaller,
      const BFContainerId& idSearch);
   virtual bool doRefresh (GenericInterface *rpGICaller, 
      const I_CHAR *szOriginalCommand)
   {
      return true;
   }
   virtual void doGetField (const GenericInterface *rpGICaller,
      const BFContainerId& idContainer, const BFFieldId& idField,
      const BFDataGroupId& idDataGroup, DString &strValueOut,
      bool bFormatted) const;
   virtual SEVERITY doSetField (const GenericInterface *rpGICaller,
      const BFContainerId& idContainer, const BFFieldId& idField,
      const BFDataGroupId& idDataGroup, const DString& strValue,
      bool bFormatted);
   virtual SEVERITY doValidateAll (BFAbstractCBO *rpWSD,
      const BFDataGroupId &idDataGroup);
   void *getPtrForContainer (const BFContainerId &idContainer,
      const BFDataGroupId &idDataGroup);
   virtual bool doModelessSetFocus (GenericInterface *rpGICaller);
private:
   GenericInterface *_rpChildGI;
   FinancialInstitutionTransitList *_pTransitsList;
   FinancialInstitution *_pFinancialInstitution;
   DString _dstrFIListKey,
      _dstrTransitName,
      _dstrCaller;
   SEVERITY setTransitListContainer();
   SEVERITY processParameters ();
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/TransitsProcess.hpp-arc  $
//
//   Rev 1.2   Oct 27 2003 19:48:30   popescu
//CIBC PET809, FN 13, added Transit Search by name
//
//   Rev 1.1   Oct 24 2003 17:19:04   popescu
//CIBC PET 809, FN 13
//
//   Rev 1.0   Oct 04 2003 16:06:14   popescu
//Initial revision.
 *
 */
