#pragma once

#include <bfconmgr\bfconnection.hpp>

class BFData;
class BFSecurity;

// Import/Export resolution
#undef BFCONMGR_LINKAGE
#ifdef BFCONMGR_DLL
   #define BFCONMGR_LINKAGE CLASS_EXPORT
#else
   #define BFCONMGR_LINKAGE CLASS_IMPORT
#endif

class BFCONMGR_LINKAGE BFRecordConnection : public BFConnection
{
public:
   virtual ~BFRecordConnection()
   {}

   virtual void putRequest( const DStringA &viewName, const DStringA &request, bool bCanRecycle, const BFData* pQuery, BFSecurity* pSecurity = NULL ) = 0;
   virtual const DStringA &getResponse() = 0;
};




//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/core/bfconmgr/bfrecordconnection.hpp-arc  $
//
//   Rev 1.3   Oct 21 2009 10:37:24   purdyech
//LDAP Authorization Support
//
//   Rev 1.2   Mar 27 2009 10:27:30   purdyech
//Added more JMSProperties to ZTS request messages.
//
//   Rev 1.1   Jan 27 2004 16:03:44   PURDYECH
//Added a bool to indicate if the connection can be recycled after a failed receive
//
//   Rev 1.0   Jan 27 2003 14:45:26   PURDYECH
//Initial Revision
//
