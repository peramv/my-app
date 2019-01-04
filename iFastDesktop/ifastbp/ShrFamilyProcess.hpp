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
#include <ifastbp\ifasthistoricalparameters.hpp>

///#endif

// Forward references
class ShrFamilyList;
class FamilyCodeList;

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

/**
 * Class that manages the remarks process.
 *
 * @author Yakov Prager
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 03/09/1999</dd></dl>
 * @version 0.1
 */

class IFASTBP_LINKAGE ShrFamilyProcess : public AbstractProcess,
      public IFastHistoricalParameters
{
// Construction
public:
   /**
    * Default constructor
    */
   ShrFamilyProcess (GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
   virtual ~ShrFamilyProcess();

protected:
   bool doOk (GenericInterface *rpGICaller);

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
   virtual bool doModelessChildComplete (const Command &cmd);
   /**
      * Used to bring a modeless dialog (via parent process) to the top of the
      * window stack.
      * @param rpGICaller - A reference pointer to the calling object.
      * @returns true if successful, check conditions if false
      */
   virtual bool doModelessSetFocus(GenericInterface *rpGICaller);
   /**
     * Implementation to support the process method.
     * @returns an enum representing the return type
     */
   virtual E_COMMANDRETURN doProcess();
   void *getPtrForContainer( const BFContainerId& idContainer,
                             const BFDataGroupId& idDataGroup);

   SEVERITY getHistoricalParameters( const BFContainerId& idContainer, HISTORICAL_VECTOR &vectorInput );

private:
   GenericInterface *_rpChildGI;
   DString _strShrNum, 
      s_AcctNum;
   FamilyCodeList* _pFamilyCodeList;

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastbp/ShrFamilyProcess.hpp-arc  $
//
//   Rev 1.8   Mar 20 2012 18:54:16   popescu
//Incident 2889121 - shareholder family screen freeze
//
//   Rev 1.7   Mar 20 2012 18:36:08   popescu
//Incident 2889121 - shareholder family screen freeze
//
//   Rev 1.6   Nov 15 2011 18:39:24   dchatcha
//P0188902 FN02 - DYN Household Project
//
//   Rev 1.5   Nov 08 2011 11:54:06   dchatcha
//P0188902 FN02 - DYN Household Project
//
//   Rev 1.4   Mar 21 2003 17:48:16   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.3   Jan 15 2003 16:50:14   sanchez
//Added a DString member to class
//
//   Rev 1.2   Jan 14 2003 17:33:36   sanchez
//added
////******************************************************************************
////              Revision Control Entries
////******************************************************************************
///* $Log:   Y:/VCS/BF iFAST/ifastcbo/MFAccount.cpp-arc  $
// * /
 */
