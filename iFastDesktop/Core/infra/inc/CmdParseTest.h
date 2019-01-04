#ifndef CMDPARSETEXT_HPP
#define CMDPARSETEXT_HPP

#pragma message( "including "__FILE__ )

/*
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1999-2000 by DST Systems, Inc.
 */

#ifndef DSTRINGA_HPP
#include "DStringA.hpp"
#endif

#undef DITEST_LINKAGE
#ifdef DITEST_DLL
   #define DITEST_LINKAGE CLASS_EXPORT
#else
   #define DITEST_LINKAGE CLASS_IMPORT
#endif

class DITEST_LINKAGE AutoRunCommandLine
{

public:

   AutoRunCommandLine();
   virtual ~AutoRunCommandLine() {};
   virtual void ParseCmdLine( int argc, char * argv[] );

   bool VerifyInFilePath( const char * lpcszDefFile = "", 
                          const char * lpcszDefExt = "");
   bool VerifyOutFilePath( const char * lpcszDefFile = "",
                           const char * lpcszDefExt = "");
   bool VerifyExOutFilePath( const char * lpcszDefFile = "",
                             const char * lpcszDefExt = "");

   inline const bool getAutoRun()
   {
      return autoRunFlag;
   }

   inline const DStringA getInputFile()
   {
      return autoInputFile;
   }

   inline const DStringA getOutputFile()
   {
      return autoOutputFile;
   }

   inline const DStringA getExOutputFile()
   {
      return autoExOutputFile;
   }

   inline const int getFileWriteMode( void ) const
   {
      return _mode;
   }

private: // methods

   virtual void ParseParam( const char * lpszParam, 
                            bool bFlag, 
                            bool bLast );
   bool form_path( DStringA & rPath, 
                   const char * lpcszDefFile,
                   const char * lpcszDefExt);

private: // attributes

   bool autoRunFlag;
   DStringA autoInputFile;
   DStringA autoOutputFile;
   DStringA autoExOutputFile;
   int _mode;

};

//************************************************************************
//              Revision Control Entries
//************************************************************************
//
// Name:
//    %PM%
//    %PID%
//
// Description:
//    %PD%
//
// Design Parts:
//    %PIRP%
//
// Last Changed:
//    %PO%  -  %PRT%
//
// Changes:
//    %PLA%
//
//
// $Log:   Y:/VCS/iFastAWD/inc/CmdParseTest.h-arc  $
//
//   Rev 1.0   28 Jan 2008 13:30:26   kovacsro
//Initial revision.
//
//   Rev 1.2   13 Nov 2001 15:45:54   dt14177
//Added the testinputdata enhancement
//to get input from files
//
//   Rev 1.1   06 Feb 2001 09:14:42   dt14177
//file names are now ASCII
//
//   Rev 1.0   02 Feb 2001 09:11:26   dt14177
// 
//
#endif // CMDPARSETEXT_HPP