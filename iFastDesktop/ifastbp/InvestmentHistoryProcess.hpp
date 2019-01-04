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
//
// ^FILE   : InvestmentHistoryProcess.hpp
// ^AUTHOR :  
// ^DATE   : 
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : InvestmentHistoryProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include <bfproc\AbstractProcess.hpp>
#include <ifastbp\ifasthistoricalparameters.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

class InvestmentHistoryList;
class InvestmentHistoryDetailsList;
class InvestmentHistoryInterestList;

class IFASTBP_LINKAGE InvestmentHistoryProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
   InvestmentHistoryProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~InvestmentHistoryProcess();

   virtual bool doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idSearch );
   
protected:
   void *getPtrForContainer (const BFContainerId& idContainer,const BFDataGroupId& idDataGroup);
   virtual SEVERITY doInit();
   virtual bool doModelessChildComplete (const Command &cmd);
   virtual bool doModelessSetFocus(GenericInterface *rpGICaller);
   virtual E_COMMANDRETURN doProcess();
   virtual bool doRefresh(GenericInterface *rpGICaller, const I_CHAR *szOriginalCommand);

   virtual SEVERITY performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, E_SEARCHACTION eSearchAction );

   //Add on method
   virtual SEVERITY doValidateAll (BFAbstractCBO *rpWSD,const BFDataGroupId& idDataGroup);   

   virtual SEVERITY doSetField ( const GenericInterface *rpGICaller,
                                 const BFContainerId &idContainer, 
                                 const BFFieldId &idField,
                                 const BFDataGroupId &idDataGroup, 
                                 const DString &strValue,
                                 bool bFormatted);

private:
   void readSearchParameters ();
   GenericInterface *_rpChildGI;
   InvestmentHistoryList *m_pHistoryList,
	                     *m_pSearchHistoryList;
   InvestmentHistoryDetailsList *m_pDetailsList;
   InvestmentHistoryInterestList *m_pInterestList;

   DString	m_strAcctNum,
			m_strTransId,
			m_strFund,
			m_strClass,
			m_strInvestmentNo,
			m_strStatus,
			m_strSearchBy,
			m_strInvHisInvestId;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastbp/InvestmentHistoryProcess.hpp-arc  $
//
//   Rev 1.3   Dec 01 2011 18:03:36   wp040100
//P0186477/FN03 - GIA - Investment History Changes
//
//   Rev 1.2   Nov 25 2011 17:40:02   wp040100
//P0186477/FN03 - GIA - Investment History Changes
//
//   Rev 1.1   Nov 17 2011 15:47:22   wp040100
//P0186477/FN03 - GIA - Investment History Changes
//
//   Rev 1.0   Nov 10 2011 19:06:10   wp040100
//Initial revision.
//
 */
