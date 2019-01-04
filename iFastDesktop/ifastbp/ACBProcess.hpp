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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : ACBProcess.hpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 04/19/1999
//
// ----------------------------------------------------------
//
// ^CLASS    : ACBProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for the Transaction Details dialog
//
//******************************************************************************

#include <bfproc\abstractprocess.hpp>
#include <ifastbp\ifasthistoricalparameters.hpp>//P0185327_FN01 - ROC Depleting ACB

// Forward references
class ACBList;

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

/**
 * Class that manages the entity process.
 *
 * @author 
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 03/04/1999</dd></dl>
 * @version 0.1
 */

class IFASTBP_LINKAGE ACBProcess : public AbstractProcess, public IFastHistoricalParameters //P0185327_FN01 - ROC Depleting ACB
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   ACBProcess();
   ACBProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~ACBProcess();

protected:
   virtual bool doGetData(
                         GenericInterface * rpGICaller=NULL,
                         BFData * rpData=NULL
                         ) const;
   /**
     * Set up the list and get parameters.
     * @returns SEVERITY noting any error/warning conditions
     */
   virtual SEVERITY doInit();
   /**
     * Implementation to support the modelessChildComplete method.
     * modelessChildComplete is used by the GenericInterfaceContainer to tell
     * the parent that the modeless child has been destroyed.
     * @param cmd - A reference to a command representing the object that has
     * been destroyed.
     * @returns true if this modeless object should end as well, false if not
     * done yet.  When returning true, the calling modelessChildComplete method
     * will call GenericInterfaceContainer::modelessDestroySelf to delete and
     * remove this object from the container
     */
   virtual bool doModelessChildComplete(
                                       const Command &cmd
                                       );
   virtual bool doModelessSetFocus(
                                  GenericInterface *rpGICaller
                                  );
   virtual bool doMoreRecordsExist(
                                  GenericInterface *rpGICaller,
                                  const BFContainerId& idContainer 
                                  );
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
                         );
   virtual void doGetField(const GenericInterface *rpGICaller, 
                           const BFContainerId& idContainer,
                           const BFFieldId& idField, 
                           const BFDataGroupId& idDataGroup, 
                           DString &strValueOut, 
                           bool bFormatted) const;
   virtual SEVERITY doSetField (const GenericInterface *rpGICaller,
                                const BFContainerId& idContainer,
                                const BFFieldId& idField,
                                const BFDataGroupId& idDataGroup,
                                const DString& strValue,
                                bool bFormatted );

   virtual const BFProperties* doGetFieldAttributes ( const GenericInterface *rpGICaller, 
                                                      const BFContainerId &idContainer, 
                                                      const BFFieldId &idField, 
                                                      const BFDataGroupId &idDataGroup );

   //P0185327_FN01 - ROC Depleting ACB
   virtual SEVERITY getHistoricalParameters ( const BFContainerId &idContainer,
                                              BFFieldId &recordIdField, 
                                              DString &tableId, 
                                              DString &dstrKeys);

   virtual SEVERITY getHistoricalParameters( const BFContainerId& idContainer, 
                                             HISTORICAL_VECTOR &vectorInput );

   virtual void *getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup ) override;

   //----
private:
   ACBList *_pACBListList;
   DString _AccountNum,
      _AccountCurrency,
      _FundCode,
      _ClassCode;

   GenericInterface *_rpChildGI;
   SEVERITY performSearch( GenericInterface *rpGI, 
                           const BFContainerId& idSearch, 
                           E_SEARCHACTION eSearchAction );
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/ACBProcess.hpp-arc  $
 * 
 *    Rev 1.7   Sep 14 2011 10:07:42   panatcha
 * P0185327_FN01 - ROC Depleting ACB
 * 
 *    Rev 1.6   Mar 21 2003 17:33:36   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.5   Feb 05 2003 11:08:14   popescu
 * Displaying the ACB string when ACB cannot be calculated
 * 
 *    Rev 1.4   Oct 09 2002 23:52:54   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.3   22 May 2002 18:22:08   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.2   19 Mar 2002 13:14:40   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.1   Feb 15 2000 18:56:08   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:58:52   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.2   Nov 01 1999 17:59:02   DT24433
 * removed doOk/doCancel
 * 
 *    Rev 1.1   Jul 08 1999 10:03:22   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
