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
//    DATE   : June 2003
//
//
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************

#include <bfproc\abstractprocess.hpp>
#include <ifastbp\ifasthistoricalparameters.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

//Forward declarations
class PayToEntityList;

class IFASTBP_LINKAGE PayToEntityProcess : public AbstractProcess,
   public IFastHistoricalParameters
{
// Construction
public:
   PayToEntityProcess(GenericInterfaceContainer* pGIC, 
      GenericInterface* pGIParent, const Command& rCommand);
   virtual ~PayToEntityProcess();
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
   SEVERITY doValidateAll(BFAbstractCBO *rpWSD,
      const BFDataGroupId &idDataGroup);
   bool doModelessSetFocus(GenericInterface *rpGICaller);
   void doGetField(const GenericInterface *rpGICaller,
      const BFContainerId& idContainer, const BFFieldId& idField,
      const BFDataGroupId& idDataGroup, DString &strValueOut,
      bool bFormatted) const;
   void *getPtrForContainer(const BFContainerId& idContainer,
      const BFDataGroupId& idDataGroup);
   virtual SEVERITY getHistoricalParameters(const BFContainerId& idContainer,
      BFFieldId &recordIdField, DString& tableId, DString& dstrKeys);
   SEVERITY getHistoricalParameters( const BFContainerId& idContainer, HISTORICAL_VECTOR &vectorInput );

private:
   SEVERITY processParameters();
   GenericInterface *_rpChildGI;
   DString _dstrBrokerCode;
	DString _dstrSearchTypeMgmt;
   PayToEntityList *_pPayToEntityList;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/PayToEntityProcess.hpp-arc  $
//
//   Rev 1.6   Jul 27 2006 17:58:12   ZHANGCEL
//PET2192 FN11 - Commission Payments to MgmtCo related changes
//
//   Rev 1.5   Mar 10 2004 13:18:40   HERNANDO
//PET965 FN11 - Added getHistoricalParameters.
//
//   Rev 1.4   Aug 19 2003 16:16:40   HERNANDO
//Added keys to getHistoricalParameters.
//
//   Rev 1.3   Jul 31 2003 21:59:04   popescu
//Added support for PayType 'X' and support for Historical Info at the process level
//
//   Rev 1.2   Jul 23 2003 18:20:40   popescu
//Capitalized the parameters
//
//   Rev 1.1   Jul 09 2003 21:56:46   popescu
//Payment Instructiuons work, business rules implementation SSB_PET_821_FN17
//
//   Rev 1.0   Jun 27 2003 18:15:20   popescu
//Initial revision.
 *
 */
