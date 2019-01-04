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


#include <bfproc\AbstractProcess.hpp>
///#endif

// Forward references
class FundList;
class FundMasterList;
class FundDetailList;
class UnitFactorList;

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

/**
 * Class that manages the search process, which defines the search criterias
 * and builds a list of accounts.
 *
 * @author Serban Popescu
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 03/08/1999</dd></dl>
 * @version 0.1
 */

class IFASTBP_LINKAGE FundInfoProcess : public AbstractProcess
{
// Construction
public:
   void cboSetParameter(const DString& elementName, const DString& value );

   /**
    * Default constructor
    */
//CP20030319   FundInfoProcess();
   FundInfoProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~FundInfoProcess();
protected:
   /**
     * Provide class specific implementation for some fields.
     * An exception will be thrown if the field cannot be found.
     * @param rpGICaller - A reference pointer to the calling object.
     * @param idContainer - ID of container we are using.
     * @param idField - ID of field we are getting.
     * @param strValue - A string reference where value is returned.
     * @param bFormatted - Flag where true means get data formatted.
     */
   virtual void doGetField(
                          const GenericInterface *rpGICaller,
                          const BFContainerId& idContainer,
                          const BFFieldId& idField,
                          const BFDataGroupId& idDataGroup,
                          DString &strValueOut,
                          bool bFormatted
                          ) const;
   /**
     * Set up the list and get parameters.
     * @returns SEVERITY noting any error/warning conditions
     */
   virtual SEVERITY doInit();
   /**
     * Used to bring a modeless dialog (via parent process) to the top of the
     * window stack.
     * @param rpGICaller - A reference pointer to the calling object.
     * @returns true if successful, check conditions if false
     */
   virtual bool doModelessSetFocus(
                                  GenericInterface *rpGICaller
                                  );
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
   bool doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idSearch );
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
                         )
   {
      return(true);
   }
   /**
     * Provide class specific implementation for some fields.
     * An exception will be thrown if the field is not found.
     * @param rpGICaller - A reference pointer to the calling object.
     * @param idContainer - ID of container we are using.
     * @param idField - ID of field we are getting.
     * @param strValue - A string reference for the value of the field to be
     * set.
     * @param bFormatted - Flag where true means incoming data is formatted.
     * @returns SEVERITY indicating any errors/warnings encountered.
     */
   virtual SEVERITY doSetField(
                              const GenericInterface *rpGICaller,
                              const BFContainerId& idContainer,
                              const BFFieldId& idField,
                              const BFDataGroupId& idDataGroup,
                              const DString& strValue,
                              bool bFormatted
                              );
   void *getPtrForContainer(
                           const BFContainerId& idContainer,
                           const BFDataGroupId& idDataGroup
                           );
   SEVERITY performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, 
                           E_SEARCHACTION eSearchAction );
   virtual bool doSend( GenericInterface* rpGICaller,
                        const I_CHAR * szMessage );
private:
   FundMasterList   *_pFundMasterList;
   FundDetailList   *_pFundDetailList;
   FundList         *_pFundInfoList;
   DString m_dstrFundCode;
   DString m_dstrFromDate;
   DString m_dstrPrevDatePressed;
   DString m_dstrNextDatePressed;
   DString m_dstrClassCode;
   DString m_dstrFundWKN;
   DString m_dstrFundISIN;
   DString m_dstrToDate;
   GenericInterface *_rpChildGI;
   DString m_dstrFundCUSIP;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/FundInfoProcess.hpp-arc  $
 * 
 *    Rev 1.10   Sep 17 2004 13:38:56   popescu
 * PET1117 FN22 - revert fund factors dialog display to old logic
 * 
 *    Rev 1.9   Sep 09 2004 11:36:02   HERNANDO
 * PET1117 FN22 - WKN & ISIN Enhancement.
 * 
 *    Rev 1.8   Nov 20 2003 16:31:56   AGUILAAM
 * PET859_FN17: added factors screen - daily equalization.
 * 
 *    Rev 1.7   Mar 21 2003 17:40:28   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.6   Oct 09 2002 23:53:16   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.5   Aug 29 2002 12:52:32   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.4   22 May 2002 18:20:56   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.3   19 Mar 2002 13:17:08   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.2   Aug 02 2000 15:31:42   BUZILA
 * "locale" changes
 * 
 *    Rev 1.1   Feb 15 2000 18:56:30   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:59:08   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.7   Dec 08 1999 12:16:24   BUZILA
 * added idDataGroup parameter to doGetField and doSetField
 * 
 *    Rev 1.6   Nov 06 1999 16:38:12   BUZILA
 * fix getPtrForContainer(...)
 * 
 *    Rev 1.5   Oct 29 1999 10:17:08   DT24433
 * removed doOk/doCancel
 * 
 *    Rev 1.4   Aug 30 1999 19:04:56   DT24433
 * changed dogetfield/dosetfield parms
 * 
 *    Rev 1.3   Aug 05 1999 14:23:02   DT24433
 * lazy initialization
 * 
 *    Rev 1.2   Jul 15 1999 16:39:26   BUZILA
 * Fixing Mgmt Detail
 * 
 *    Rev 1.1   Jul 08 1999 10:03:44   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
