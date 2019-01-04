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

class IFASTBP_LINKAGE UnitFactorProcess : public AbstractProcess
{
// Construction
public:

   void cboSetParameter(const DString& elementName, const DString& value );

   /**
    * Default constructor
    */
//CP20030319   UnitFactorProcess();
   UnitFactorProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~UnitFactorProcess();

protected:

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
   void *getPtrForContainer(
                           const BFContainerId& idContainer,
                           const BFDataGroupId& idDataGroup
                           );
private:

   FundMasterList   *_pFundMasterList;
   FundDetailList   *_pFundDetailList;
   FundList         *_pFundInfoList;
   UnitFactorList   *m_pUnitFactorsList;
   DString           _pFundCode;
   DString           _pClassCode;
   DString           _pFromDate;
   DString           _pToDate;
   DString           _pPrevDatePressed;
   DString           _pNextDatePressed;
   GenericInterface *_rpChildGI;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/UnitFactorProcess.hpp-arc  $
//
//   Rev 1.0   Sep 09 2004 10:40:52   HERNANDO
//Initial revision.
 */
