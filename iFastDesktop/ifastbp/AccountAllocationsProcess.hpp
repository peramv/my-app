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

#include <bfproc\abstractprocess.hpp>

// Forward references
class ShrAllocTypeList;
class DefAcctAllocList;
class DefFundAllocList;
class MFAccount;
class Shareholder;

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

/**
 * Class that manages the Allocations process.
 *
 * @author Yakov Prager
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 03/09/1999</dd></dl>
 * @version 0.1
 */

class IFASTBP_LINKAGE AccountAllocationsProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   AccountAllocationsProcess();
   AccountAllocationsProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~AccountAllocationsProcess();

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
      * This method may be overridden if the derived process needs a chance to
      * process prior to the normal ok (ok2) processing.
      * @param rpGICaller - A reference pointer to the calling GenericInterface.
      * @return true if successful causing ok processing to continue or false to 
      * halt ok processing.
      */
   virtual bool doOk( GenericInterface *rpGICaller );
   /**
      * This method is used to implement subclass overrides for validateAll
      * during ok2 processing.  The method implementation must not use a 
      * MAKEFRAME, or should make sure all conditions are promoted to its frame
      * prior to returning.
      * @param rpWSD - WorkSessionDetails pointer
      * @param idDataGroup - group ID to use for CBO processing
      * @returns SEVERITY indicating any errors/warnings encountered.
      */
   virtual SEVERITY doValidateAll( BFAbstractCBO *rpWSD, const BFDataGroupId& idDataGroup );
   /**
      * This method is used (typically by a GUI object) to delete the current
      * item from a list.
      * An exception will be thrown if the list or item could not be found.
      * See note about lists in class document block.
      * @param rpGICaller - A reference pointer to the calling object.
      * @param idList - ID of list we are using.
      * @returns highest SEVERITY encountered, check conditions.
      */
   virtual SEVERITY deleteItemFromList( const GenericInterface *rpGICaller, const BFContainerId& idList );

   void *getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup );

private:
   SEVERITY setContainers( const BFDataGroupId& idDataGroup );
   SEVERITY filterContainer( const BFDataGroupId& idDataGroup );

   MFAccount *_pMFAccount;                            // Not owned by this class!
   Shareholder *_pShareholder;                        // Not owned by this class!
   ShrAllocTypeList *_pShrAllocationsList;
   DefAcctAllocList *_pAcctAllocationsList;
   DefFundAllocList *_pFundAllocationsList;

   DString _dstrAccountNum;
   DString _dstrShare;
   DString _dstrTransType;
   DString _dstrEffectiveDate;
   DString dstrShareholderNum;

   GenericInterface *_rpChildGI;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AccountAllocationsProcess.hpp-arc  $
//
//   Rev 1.6   Mar 21 2003 17:34:00   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.5   Oct 09 2002 23:52:56   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.4   Jun 03 2002 16:55:08   HSUCHIN
//bug fix to doValidateAll to use BFAbstractCBO rather than BFCBO
//
//   Rev 1.3   22 May 2002 18:22:12   PURDYECH
//BFData Implementation
//
//   Rev 1.2   22 Apr 2002 10:15:02   KOVACSRO
//Rel.47 : new design for allocations.
//
//   Rev 1.1   19 Mar 2002 13:14:42   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.0   Dec 20 2001 18:19:48   FENGYONG
//Initial revision.
 *
 */
