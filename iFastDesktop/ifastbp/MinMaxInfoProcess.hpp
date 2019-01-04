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
//    Copyright 2000 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : MinMaxInfoProcess.hpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 02/15/2000
//
// ----------------------------------------------------------
//
// ^CLASS    : MinMaxInfoProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  
//
//******************************************************************************


#include <bfproc\AbstractProcess.hpp>

// Forward references
class MinMaxInfoList;

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

class IFASTBP_LINKAGE MinMaxInfoProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   MinMaxInfoProcess();
   MinMaxInfoProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~MinMaxInfoProcess();

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
   virtual bool doRefresh(
                         GenericInterface *rpGICaller,
                         const I_CHAR *szOriginalCommand
                         );

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

   /**
   * Subclasses will implement this method to initiate a search.  The caller
   * is expected to have set up any search criteria  (via setField) prior to
   * calling this method.
   * @param rpGICaller - A reference pointer to the calling object.
   * @param idSearch - ID of specific search to perform.
   * @param eSearchType - Search action to perform.  (Start or next block). 
   * @returns SEVERITY noting any error/warning conditions
   */
   virtual SEVERITY performSearch( GenericInterface *rpGI, const BFContainerId& idSearch,
                                   E_SEARCHACTION  );

	virtual void *getPtrForContainer( const BFContainerId& idContainer,
                                           const BFDataGroupId& idDataGroup );


    virtual void doGetField ( const GenericInterface *rpGICaller,  
                             const BFContainerId &idContainer, 
                             const BFFieldId &idField, 
                             const BFDataGroupId &idDataGroup, 
                             DString &strValueOut, 
                             bool bFormtted) const;
/*
   virtual SEVERITY doSetField(
      const GenericInterface *rpGICaller,
      const BFContainerId& idContainer,
      const BFFieldId& idField,
      const DString& strValue,
      bool bFormatted
      );
*/
private:

   MinMaxInfoList *_pMinMaxInfoList;
   GenericInterface *_rpChildGI;
   DString _strAccountNum;
   DString _dstrAsofDate;
   DString _strTaxType;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/MinMaxInfoProcess.hpp-arc  $
 * 
 *    Rev 1.9   16 May 2008 16:07:52   kovacsro
 * PET2255_FN47 - show positive value for Last Unlocking amount, regardless.
 * 
 *    Rev 1.8   Jul 02 2003 16:03:34   YINGBAOL
 * promot error message if view call has error
 * 
 *    Rev 1.7   Mar 21 2003 17:45:18   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.6   Oct 09 2002 23:53:30   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.5   Aug 29 2002 12:53:08   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.4   22 May 2002 18:20:16   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.3   19 Mar 2002 13:18:02   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.2   Aug 02 2000 15:31:48   BUZILA
 * "locale" changes
 * 
 *    Rev 1.1   Mar 21 2000 14:31:56   ZHANGCEL
 * Milestone check in
 * 
 *    Rev 1.0   Mar 20 2000 15:48:38   ZHANGCEL
 * Initial revision.
// 
//    Rev 1.1   Feb 29 2000 15:38:00   ZHANGCEL
// Added a member data
 * 
 *
 */

///#endif 
