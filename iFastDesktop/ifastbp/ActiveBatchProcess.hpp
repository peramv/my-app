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
//    AUTHOR : Robert Kovacs
//    DATE   : 27/09/07
//
//
//    Copyright 2007 by IFDS Canada
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

/**
 * Class that cleans up all!
 *
 * @author Robert Kovacs
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 27/09/2007</dd></dl>
 * @version 1.0
 */

class IFASTBP_LINKAGE ActiveBatchProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
// ActiveBatchProcess();
   ActiveBatchProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~ActiveBatchProcess();
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
   virtual bool doRefresh( GenericInterface *rpGICaller, 
                           const I_CHAR *szOriginalCommand )
   {
      return(true);
   }

};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/ActiveBatchProcess.hpp-arc  $
//
//   Rev 1.0   27 Sep 2007 14:41:08   kovacsro
//Initial revision.
 * 
 *
 */
