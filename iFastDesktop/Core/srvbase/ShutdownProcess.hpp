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

#undef SRVBASE_LINKAGE
#ifdef SRVBASE_DLL
   #define SRVBASE_LINKAGE CLASS_EXPORT
#else
   #define SRVBASE_LINKAGE CLASS_IMPORT
#endif

extern SRVBASE_LINKAGE const I_CHAR *CMD_SPROC_SHUTDOWN;

class SRVBASE_LINKAGE ShutdownProcess : public AbstractProcess
{
public:
   ShutdownProcess( GenericInterfaceContainer* pGIC,
                    GenericInterface* pGIParent,
                    const Command& rCommand );
   virtual ~ShutdownProcess();

protected:
   virtual SEVERITY doInit();
   virtual E_COMMANDRETURN doProcess();
private:
   bool _restart;

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/srvbase/ShutdownProcess.hpp-arc  $
//
//   Rev 1.4   Jan 14 2003 11:04:56   PURDYECH
//DataGroupid parentage knowledge
//
//   Rev 1.3   Oct 09 2002 17:42:28   PURDYECH
//New PVCS Database
//
//   Rev 1.2   27 Mar 2002 19:44:10   PURDYECH
//Process/WindowFactory overhaul
//
//   Rev 1.1   22 Mar 2002 15:05:42   PURDYECH
//Removed compile-time "including..." message
//Use #pragma once as include guard
//Include files with lower-case only names
//
//   Rev 1.0   11 Oct 2001 17:53:26   SMITHDAV
//Initial revision.
 */
