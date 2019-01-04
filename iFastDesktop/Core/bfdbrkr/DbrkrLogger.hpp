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
//
//******************************************************************************
//
// ^FILE   : DbrkrLogger.hpp
// ^AUTHOR : Chin Hsu
// ^DATE   : June 2001
//
// ^CLASS    : DbrkrLogger
// ^INHERITS FROM :          
//
// ^CLASS DESCRIPTION : 
//    This class provides an abstract interface for the project specific WriteBuffer 
//    classes.
//
//******************************************************************************
#include <win32\platform.h>
#include <fstream>

// Import/Export resolution
#undef BFDBRKR_LINKAGE
#ifdef BFDBRKR_DLL
   #define BFDBRKR_LINKAGE CLASS_EXPORT
#else
   #define BFDBRKR_LINKAGE CLASS_IMPORT
#endif

class BFData;
class DString;
class DStringA;
class BFReadBuffer;
class BFWriteBuffer;
class BFFieldId;

class BFDBRKR_LINKAGE DbrkrLogger 
{

public:
   DbrkrLogger();
   DbrkrLogger( const DString& fileName, bool bAppend = false );
   virtual ~DbrkrLogger();   
   void logData( const BFData& data, const BFFieldId& idField );
   void logData( const DString& fieldName, const DString& fieldValue );
   void logData( const DString& dstrOutput );   
   void logData( const BFWriteBuffer* pRequestBuffer, const BFReadBuffer* pResponseBuffer, const DString& dstrLabel );
   bool setFileName( const DString &fileName, bool bAppend = false );

   static bool isEnabled();
   static void enable( bool b );
   static const DString& getLogDir();
   static void setLogDir( const DString& s );
   static bool isCompleteLogging();
   static void setCompleteLogging( bool b );
   static bool isAppending();
   static void setAppending( bool b );
   static bool logRequest();
   static void setLogRequest( bool b );
   static bool logResponse();
   static void setLogResponse( bool b );

private:
   void writeData( const DString& output );
   bool           _bLogging;
   bool           _bFixedOutFile;
   bool           _requestOut;
   bool           _responseOut;   
   std::ofstream  _outFile;   
   std::ofstream  _fixedOutFile;
   std::ofstream  _rawLog;   

   bool openFile( const DString &fileName, bool bAppend );

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/core/bfdbrkr/DbrkrLogger.hpp-arc  $
//
//   Rev 1.13   Feb 20 2009 14:48:18   purdyech
//ZTS Revision 6
//
//   Rev 1.12   Oct 09 2002 17:40:42   PURDYECH
//New PVCS Database
//
//   Rev 1.11   Aug 29 2002 12:51:16   PURDYECH
//ClientLocale and Field corrections
//
//   Rev 1.10   May 28 2002 12:17:22   PURDYECH
//BFData Implementation - Phase II
//
//   Rev 1.9   22 Mar 2002 15:11:52   PURDYECH
//Removed compile-time "including..." message
//Use #pragma once as include guard
//Include files with lower-case only names
//
//   Rev 1.8   26 Oct 2001 11:04:36   HSUCHIN
//added support to log raw transaction request/response.  New logData function which takes BFWriteBuffer/BFReadBuffer as params.
//
//   Rev 1.7   18 Sep 2001 15:20:52   PURDYECH
//Get STUB_DATA working again.
//
//   Rev 1.6   19 Jul 2001 11:56:58   HSUCHIN
//added boolean flag in contructor to override append mode
//
//   Rev 1.5   28 Jun 2001 14:23:18   HSUCHIN
//added fixed log capabilities and other enhancements
//
//   Rev 1.4   Jun 26 2001 12:54:44   PURDYECH
//Infrastructure Release 1.9 Integration.
//
//   Rev 1.3   14 Jun 2001 14:39:10   HSUCHIN
//new override and reduced number of output files
//
//   Rev 1.2   13 Jun 2001 17:35:16   HSUCHIN
//second attempt to pvcs fix
*/
