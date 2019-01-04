#pragma once

#include <dstring.hpp>
#include <string>
#include <eh.h>

// Import/Export resolution
#undef BFUTIL_LINKAGE
#ifdef BFUTIL_DLL
   #define BFUTIL_LINKAGE CLASS_EXPORT
#else
   #define BFUTIL_LINKAGE CLASS_IMPORT
#endif

extern BFUTIL_LINKAGE void setGlobalSeTranslator( _se_translator_function );

class SEH_Exception
{
private:
    unsigned long code_;
    DString strLogFile_;
public:
    SEH_Exception() 
    : code_( 0 ) 
    , strLogFile_( I_( "" ) )
    {}
    SEH_Exception( unsigned long code, const char* pszLogFile ) 
    : code_( code ) 
    , strLogFile_( std::string(pszLogFile) )
    {}
    unsigned long what() const { return code_; }
    const DString& getLogFile() const { return strLogFile_; }
    void setLogFile( const DString& strLogFile ) { strLogFile_ = strLogFile; }
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF Core/bfutil/seh_exception.hpp-arc  $
//
//   Rev 1.3   Feb 23 2004 11:19:14   PURDYECH
//Store logfile as a DString so that we can extract it more easily
//
//   Rev 1.2   Feb 12 2004 12:17:00   PURDYECH
//Added setGlobalSeTranslator() function to allow a general se_translator function to be specified for all threads.
//
//   Rev 1.1   Feb 11 2004 20:35:20   PURDYECH
//name of a corresponding logfile added as attribute
//
//   Rev 1.0   Feb 11 2004 18:47:54   PURDYECH
//Initial revision.
//
