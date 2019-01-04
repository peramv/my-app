#pragma once

#undef BFUTIL_LINKAGE
#ifdef BFUTIL_DLL
   #define BFUTIL_LINKAGE CLASS_EXPORT
#else
   #define BFUTIL_LINKAGE CLASS_IMPORT
#endif

#include <bf/log/abstractlogtarget.hpp>
#include <cstdio>
#include <assert.h>

namespace bf {
namespace log {
     
class BFUTIL_LINKAGE LogTargetDisk : public AbstractLogTarget {
protected:
   // need a file name to log to (for now), but we will eventually
   // want a ctor which accepts an ini file
   LogTargetDisk( const I_CHAR* pszPath, const I_CHAR* pszFile, bool bUnicode, bool bLinear = true, bool bActive = true )
   : pFile_( NULL )
//   , dstrFQP_(I_(""))
   , badFileName_( false )
   , dstrPath_( pszPath )
   , dstrFile_( pszFile )
   , bUnicode_( bUnicode )
   , bSuspend_( !bActive )
   , bAppend_( false )
   , bLinear_( bLinear )
   {
   }
   FILE* getFile() ;

   virtual const I_CHAR* getOpenMode( const DString& dstrFQP, bool bAppend, bool bUnicode ) const;

public:
   static LogTargetDisk* create( const I_CHAR* pszPath, const I_CHAR* pszFile );
   static LogTargetDisk* createUnicode( const I_CHAR* pszPath, const I_CHAR* pszFile );

   ~LogTargetDisk();

   void write( const DString& str );

   void suspend();
   bool isSuspended() const { return bSuspend_; }

   void restart();

   DString getRealFileName() const;
   const DString& getPathName() const { return dstrPath_; }
   const DString& getFileName() const { return dstrFile_; }

   void setFileName( const DString& dstrFile );
   void setPathName( const DString& dstrPath );
   void setFilePath( const DString& dstrPath, const DString& dstrFile );

protected:
   virtual DString getFileName( const I_CHAR* pszHint ) const;
private:
   void flush();

   FILE* pFile_;
   bool badFileName_;
//   DString dstrFQP_;
   DString dstrPath_;
   DString dstrFile_;
   bool bUnicode_;
   bool bSuspend_;
   bool bAppend_;
   bool bLinear_;
private:
   LogTargetDisk( const LogTargetDisk& rhs );
};

}  // namespace log
}  // namespace bf


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/core/bf/log/logtargetdisk.hpp-arc  $
//
//   Rev 1.4   Mar 24 2009 10:20:48   purdyech
//Changes for ZTS.  Release 9 for Phase II of POC
//
//   Rev 1.3   Feb 27 2009 08:48:56   purdyech
//ZTS Fixes prior to User Experience Test
//
//   Rev 1.2   Feb 20 2009 14:46:58   purdyech
//ZTS Revision 6
//
//   Rev 1.1   Mar 09 2004 10:55:04   PURDYECH
//Comment cleanup.
//
//   Rev 1.0   Aug 12 2003 10:14:12   PURDYECH
//Initial revision.
//
