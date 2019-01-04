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
//    Copyright 2005 by IFDS.
//
//******************************************************************************


#include <bfproc\AbstractProcess.hpp>
///#endif

// Forward references

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

#include "iFastHistoricalParameters.hpp"

/**
 * Class that manages the Transaction Link
 *
 * @author Yingbao Li
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 06/26/2005</dd></dl>
 * @version 0.1
 */

class TransactionLinkList;
class IFASTBP_LINKAGE TransactionLinkProcess : public AbstractProcess
{
public:
   /**
    * Default constructor
    */
   TransactionLinkProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~TransactionLinkProcess();

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
   bool doModelessSetFocus( GenericInterface *rpGICaller );
   bool doModelessChildComplete( const Command &cmd );
private:
   GenericInterface *_rpChildGI;
   DString account_,transNum_;
   TransactionLinkList* pTransactionLinkList_;

};
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/TransactionLinkProcess.hpp-arc  $
//
//   Rev 1.0   Jul 06 2005 16:40:24   Yingbaol
//Initial revision.
 * 
 */
