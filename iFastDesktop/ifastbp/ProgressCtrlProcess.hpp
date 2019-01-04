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

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

/**
 * Implementation class for caller id process.
 *
 * The ProgressCtrlProcess class represents the processing for id caller.
 *
 * @author Serban Popescu
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 17/07/2008</dd></dl>
 * @version 0.1
 */

class IFASTBP_LINKAGE ProgressCtrlProcess : public AbstractProcess
{
// Construction
public:
   ProgressCtrlProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~ProgressCtrlProcess();

protected:
   virtual bool doModelessChildComplete(const Command &cmd);
   virtual bool doModelessSetFocus(GenericInterface *rpGICaller);
   virtual E_COMMANDRETURN doProcess();
private:
   GenericInterface *_rpChildGI;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/ProgressCtrlProcess.hpp-arc  $
//
//   Rev 1.0   17 Jul 2008 15:05:46   popescu
//Initial revision.
 */
