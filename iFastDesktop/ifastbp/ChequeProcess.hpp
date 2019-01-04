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
//    AUTHOR : Mihai Virgil Buzila
//    DATE   : 16/04/99
//
//
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************


#include <bfproc\AbstractProcess.hpp>
///#endif

// Forward references
class ChequeList;
class FundMasterList;

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

#include <ifastbp\ifasthistoricalparameters.hpp>

class IFASTBP_LINKAGE ChequeProcess : public AbstractProcess , public IFastHistoricalParameters
{
// Construction
public:
   /**
    * Default constructor
    */
   ChequeProcess (
                  GenericInterfaceContainer* pGIC, 
                  GenericInterface* pGIParent, 
                  const Command& rCommand);
   virtual ~ChequeProcess();
    
   virtual bool doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idSearch );

	
   SEVERITY performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, E_SEARCHACTION eSearchAction );

protected:
   void *getPtrForContainer (const BFContainerId &idContainer, const BFDataGroupId &dDataGroup );
   virtual SEVERITY doInit();
   virtual bool doModelessChildComplete (const Command &cmd);
   virtual bool doModelessSetFocus (GenericInterface *rpGICaller);
   virtual E_COMMANDRETURN doProcess();
   virtual bool doRefresh(GenericInterface *rpGICaller, const I_CHAR *szOriginalCommand);
   virtual void doGetField(
                           const GenericInterface *rpGICaller,
                           const BFContainerId& idContainer,
                           const BFFieldId& idField,
                           const BFDataGroupId& idDataGroup,
                           DString &strValueOut,
                           bool bFormatted
                          ) const;
   virtual const BFProperties *doGetFieldAttributes (
                           const GenericInterface *rpGICaller, 
                           const BFContainerId &idContainer, 
                           const BFFieldId &idField, 
                           const BFDataGroupId &idDataGroup);

   virtual SEVERITY getHistoricalParameters (const BFContainerId& idContainer, BFFieldId &recordIdField,
	                                         DString& tableId, DString& dstrKeys); 

   virtual SEVERITY getHistoricalParameters( const BFContainerId& idContainer, HISTORICAL_VECTOR &vectorInput );
   bool doOk( GenericInterface *rpGICaller );

private:
   void getEntityName (
         const BFDataGroupId &idDataGroup, 
         DString &dstrAcctNum, 
         DString &dstrEntityName);
   ChequeList *_pChequeList;
   GenericInterface *_rpChildGI;
   BFProperties *_propChequesListHeadingSet;
   DString m_dstrTransId,
      m_dstrAccountNum,
      m_dstrInChequeNum,
      m_dstrEntityName,
	  m_dstrBroker,
	  m_dstrStatus,
      m_dstrIgnoreDataNotFound,
	  m_dstrIgnoreUnknAcc;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/ChequeProcess.hpp-arc  $
 * 
 *    Rev 1.16   08 Jan 2009 14:30:08   kovacsro
 * IN#1521695 - GL #1541 - Users received an internal problem error msg from Desktop
 * 
 *    Rev 1.15   Nov 12 2008 16:25:46   jankovii
 * IN 1482694 - cheque info.
 * 
 *    Rev 1.14   Sep 11 2008 16:32:14   jankovii
 * PET 5517 FN71 Stale Cheque.
 * 
 *    Rev 1.13   Sep 08 2008 15:57:28   jankovii
 * PET 5517 FN71 - Stale Cheque.
 * 
 *    Rev 1.12   May 13 2004 21:06:08   popescu
 * PET 985, FN 01, LSIF Trade entry
 * 
 *    Rev 1.11   Mar 21 2003 17:37:52   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.10   Oct 09 2002 23:53:08   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.9   Sep 25 2002 14:51:16   HERNANDO
 * Bug fix - Display details list; clean-up, minor fixes.
 * 
 *    Rev 1.8   Aug 29 2002 12:52:00   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.7   22 May 2002 18:21:34   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.6   19 Mar 2002 13:15:24   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.5   May 16 2001 14:07:52   JANKAREN
 * Add doSetField()
 * 
 *    Rev 1.4   Aug 02 2000 15:31:38   BUZILA
 * "locale" changes
 * 
 *    Rev 1.3   Jun 19 2000 14:43:20   HUANGSHA
 * add doGetField(...) for getting ShrNum and EntityName
 * 
 *    Rev 1.2   Jun 09 2000 11:47:26   BUZILA
 * cheque fix
 * 
 *    Rev 1.1   Feb 15 2000 18:56:18   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:59:00   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.4   Oct 28 1999 17:55:38   DT24433
 * removed doOk/doCancel
 * 
 *    Rev 1.3   Oct 18 1999 11:40:02   BUZILA
 * Update transaction stuff
 * 
 *    Rev 1.2   Aug 08 1999 14:50:42   VASILEAD
 * changed to allow proper refresh
 * 
 *    Rev 1.1   Jul 08 1999 10:03:34   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
