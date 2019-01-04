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
// ^FILE   : BFViewTimeLog.hpp
// ^AUTHOR : Chris Purdye
// ^DATE   : September 2001
//
// ^CLASS    : BFViewTimeLog
// ^INHERITS FROM :          
//
// ^CLASS DESCRIPTION : 
//  This class manages the ViewTimeLog.  This log is controlled by ConfigManager
//  entries.  It creates a rolling log in files named vwtlog.001, .002, and .003.
//  The file vwtlog.001 is the 'active' log file; .002 and .003 are older versions
//  of .001.  When .001 exceeds a certain size the logfiles are rolled over, with
//  .003 being deleted, .002 being renamed .003, and .001 being renamed .002
//
//******************************************************************************
#include <win32\platform.h>
#include <dstring.hpp>
#include <bfdbrkr\bfviewtimelog.hpp>
#include <bfutil\bfcritsec.hpp>
#include <fstream>
#include <deque>

// Import/Export resolution
#undef BFDBRKR_LINKAGE
#ifdef BFDBRKR_DLL
   #define BFDBRKR_LINKAGE CLASS_EXPORT
#else
   #define BFDBRKR_LINKAGE CLASS_IMPORT
#endif

class BFDBRKR_LINKAGE ViewTimeEntry {
public:
   ViewTimeEntry( const DStringA& viewName,
            const DStringA& msgId,
            unsigned long sendTime, 
            unsigned long receiveTime,
            unsigned long unitOfWorkTime,
            unsigned long networkTime,
            unsigned long oeInvocationTime,
            unsigned long viewTime,
            unsigned long preViewTime,
            unsigned long postViewTime )
   : viewName_(viewName)
   , msgId_(msgId)
   , sendTime_(sendTime)
   , receiveTime_(receiveTime)
   , unitOfWorkTime_(unitOfWorkTime)
   , networkTime_(networkTime)
   , oeInvocationTime_(oeInvocationTime)
   , viewTime_(viewTime)
   , preViewTime_(preViewTime)
   , postViewTime_(postViewTime)
   {
      GetSystemTime(&timeStamp_);
   }
   
   inline const DStringA& getViewName() const {return viewName_;}
   inline const DStringA& getMsgId() const {return msgId_;}
   inline const unsigned long getSendTime() const {return sendTime_;}
   inline const unsigned long getReceiveTime() const {return receiveTime_;}
   inline const unsigned long getUnitOfWorkTime() const {return unitOfWorkTime_;}
   inline const unsigned long getNetworkTime() const {return networkTime_;}
   inline const unsigned long getOEInvocationTime() const {return oeInvocationTime_;}
   inline const unsigned long getViewTime() const {return viewTime_;}
   inline const unsigned long getPreViewTime() const {return preViewTime_;}
   inline const unsigned long getPostViewTime() const {return postViewTime_;}
   inline const SYSTEMTIME& getTimeStamp() const { return timeStamp_; }

   static const ViewTimeEntry* getViewTimeEntry( const ViewTimeEntry* p = NULL);

   static void recordViewTimeEntry( const DStringA& viewName,
                                    const DStringA& msgId,
                                    unsigned long sendTime, 
                                    unsigned long receiveTime,
                                    unsigned long unitOfWorkTime,
                                    unsigned long networkTime,
                                    unsigned long oeInvocationTime,
                                    unsigned long viewTime,
                                    unsigned long preViewTime,
                                    unsigned long postViewTime );

private:
   const DStringA viewName_;
   const DStringA msgId_;
   unsigned long sendTime_;
   unsigned long receiveTime_;
   unsigned long unitOfWorkTime_;
   unsigned long networkTime_;
   unsigned long oeInvocationTime_;
   unsigned long viewTime_;
   unsigned long preViewTime_;
   unsigned long postViewTime_;
   SYSTEMTIME timeStamp_;
};

class BFDBRKR_LINKAGE BFViewTimeLog
{
private:
   BFViewTimeLog( const DString &dstrPath, int maxSize );
   ~BFViewTimeLog();

public:

   static BFViewTimeLog& getInstance();
   static void killInstance();


   /**
    * write an entry in the most recent logfile if logging is active.
    * The entry consists of the current date and time (as UTC),
    * the view name, and the time the view took to execute (in msec).
    * 
    * @param viewName The view name, as a DString
    * @param requestTime
    *                 the time the view took to execute, in msec.
    */
   void log( const DString& viewName, int requestTime );
   void log( const DStringA& viewName, 
             const DStringA& msgid,
             unsigned long sendTime, 
             unsigned long receiveTime,
             unsigned long unitOfWorkTime,
             unsigned long networkTime,
             unsigned long viewTime,
             const char* pszNote = NULL );
   void log( const DStringA& viewName, 
             const DStringA& msgid,
             unsigned long sendTime, 
             unsigned long receiveTime,
             unsigned long unitOfWorkTime,
             unsigned long networkTime,
             unsigned long oeInvocationTime,
             unsigned long viewTime,
             unsigned long preViewTime,
             unsigned long postViewTime,
             const char* pszNote = NULL );

   bool isEnabled() const { return s_bActive_; }
   const DString& getPath() const { return dstrPath_; }
   void setPath( const DString& dstrPath ) { dstrPath_ = dstrPath; }
   int getMaxSize() const { return maxSize_; }

   void enable( bool b );
private:
   /**
    * open the logfile for appending
    * 
    * @param of     an ofstream object which will be opened to the logfile
    * @return a reference to the ofstream object which was passed in
    */
   std::ofstream& openFile( std::ofstream &of );

   /**
    * The logfile has a maximum size.  When that size is reached 
    * this method should be called to rollover the logfiles.  The
    * logfiles are numbered sequentially with .001 being the most
    * recent.  This method will delete the .003 logfile, rename the
    * .002 logfile to .003, and rename the .002 logfile to .001
    * 
    * @param iFile  The index of the file to rollover.  Defaults to 3
    * @return true if the rollover was successful.
    */
   bool rolloverFile( int iFile  = 3 );

   /**
    * return the size of the logfile with the specfied index.
    * 
    * @param iFile  the index of the logfile to query.  To get the size of the
    *               active logfile pass in 1
    * @return the size of the logfile, in bytes.
    */
   int getFileSize( int iFile );


   static BFCritSec      s_csViewTimeLog_;
   static BFViewTimeLog *s_pInstance_;
   static bool           s_bActive_;
   DString               dstrPath_;
   int                   maxSize_;

};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/core/bfdbrkr/BFViewTimeLog.hpp-arc  $
//
//   Rev 1.6   Dec 12 2010 17:32:54   purdyech
//IN2350361 - Performance enhancements
//
//   Rev 1.5   Dec 02 2010 07:14:02   purdyech
//Changes to implement view performance and crash-handling
//
//   Rev 1.4   Feb 20 2009 14:48:10   purdyech
//ZTS Revision 6
//
//   Rev 1.3   Aug 15 2008 08:19:30   purdyech
//ZTS Integration Changes
//
//   Rev 1.2   Oct 09 2002 17:40:40   PURDYECH
//New PVCS Database
//
//   Rev 1.1   22 Mar 2002 15:11:46   PURDYECH
//Removed compile-time "including..." message
//Use #pragma once as include guard
//Include files with lower-case only names
//
//   Rev 1.0   26 Sep 2001 10:23:30   PURDYECH
//Initial revision.
//
