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
// ^FILE   : SetDataServerProcess.hpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 04/19/1999
//
// ----------------------------------------------------------
//
// ^CLASS    : SetDataServerProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for the Transaction Details dialog
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

class IFASTBP_LINKAGE SetDataServerProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   SetDataServerProcess();
   SetDataServerProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~SetDataServerProcess();

protected:
   SEVERITY doInit();
   virtual E_COMMANDRETURN doProcess();

private:
   GenericInterface *_rpChildGI;
};

///#endif 

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/SetDataServerProcess.hpp-arc  $
//
//   Rev 1.4   Mar 21 2003 17:47:56   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.3   Oct 09 2002 23:53:36   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.2   22 May 2002 18:20:00   PURDYECH
//BFData Implementation
//
//   Rev 1.1   19 Mar 2002 13:18:28   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.0   Oct 16 2000 11:15:46   VASILEAD
//Initial revision.
 * 
 *    Rev 1.1   Feb 15 2000 18:56:08   MCNABBGL
 * changed comment format
 * 
 *
 */
