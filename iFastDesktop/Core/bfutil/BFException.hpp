#pragma once

// Import/Export resolution
#undef BFUTIL_LINKAGE
#ifdef BFUTIL_DLL
   #define BFUTIL_LINKAGE CLASS_EXPORT
#else
   #define BFUTIL_LINKAGE CLASS_IMPORT
#endif

//usually this exceptions are related to some internal server failure
//in handling the MT issues
class BFUTIL_LINKAGE BFException : public std::exception
{
protected:
   LPTSTR _lpMsgBuf;
public:
   BFException();
   BFException( LPTSTR message );
   ~BFException();
   LPTSTR getErrorMessage();
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/bfutil/BFException.hpp-arc  $
//
//   Rev 1.2   Oct 09 2002 17:41:12   PURDYECH
//New PVCS Database
//
//   Rev 1.1   03 Oct 2001 15:10:00   SMITHDAV
//Syncronization changes and Job Queue changes
//
//   Rev 1.0   Jun 28 2001 09:46:58   PURDYECH
//Initial revision.
//
//   Rev 1.0   Jun 26 2001 12:03:52   PURDYECH
//Initial revision.
 * 
 *    Rev 1.2   Feb 16 2000 13:09:44   POPESCUS
 * Initial revision
 * 
 * 
 */