#include "srcprag.h"
#include <dstring.hpp>
#include "exechist.hpp"
#include <boost/thread/recursive_mutex.hpp>
#include <bf/log/log.hpp>
#include <stdarg.h>

const int s_iExecHistGuard = 0xbaadf00d;
const int s_cExecHistQueueSize = 1000;

struct tagExecHistItem {
   tagExecHistItem()
   : iGuard_( s_iExecHistGuard )
   , iToken_( 0 )
   , bDone_( true )
   , bBreadcrumb_( false )
   , pszClass_( NULL )
   , pszFunction_( NULL )
   , pszMessage_( NULL )
   , pszFile_( NULL )
   {}
   ~tagExecHistItem()
   {
      delete[] pszMessage_;
	   delete pszClass_;
   }

   unsigned long iGuard_;
   unsigned long iToken_;
   int iDepth_;
   const I_CHAR* pszFile_;
   unsigned long ulLine_;
   bool bDone_;
   bool bBreadcrumb_;
   I_CHAR* pszClass_;
   const I_CHAR* pszFunction_;
   void addMessage( const I_CHAR* pszMessage )
   {
      delete[] pszMessage_;
      if( NULL != pszMessage ) {
         pszMessage_ = new I_CHAR[ i_strlen( pszMessage ) + 1 ];
         i_strcpy( pszMessage_, pszMessage );
      } else {
         pszMessage_ = NULL;
      }
   }
   const I_CHAR* getMessage() const { return pszMessage_; }
   
private:
   I_CHAR* pszMessage_;
};

static I_CHAR* apszWhiteSpace[] = 
{
   I_(""),
   I_(" "),
   I_("  "),
   I_("   "),
   I_("    "),
   I_("     "),
   I_("      "),
   I_("       "),
   I_("        "),
   I_("         "),
   I_("          "),
   I_("           "),
   I_("            "),
   I_("             "),
   I_("              "),
   I_("               "),
   I_("                "),
   I_("                 "),
   I_("                  "),
   I_("                   "),
   I_("                    "),
   I_("                     "),
   I_("                      "),
   I_("                       "),
   I_("                        "),
   I_("                         "),
   I_("                          "),
   I_("                           "),
   I_("                            "),
   I_("                             "),
   I_("                              "),
   I_("                               "),
   I_("                                "),
   I_("                                 "),
   I_("                                  "),
   I_("                                   "),
   I_("                                    "),
   I_("                                     "),
   I_("                                      "),
   I_("                                       "),
   I_("                                        "),
   I_("                                         "),
   I_("                                         !"),
};

const int cWhiteSpace = sizeof( apszWhiteSpace ) / sizeof( apszWhiteSpace[0] );

typedef struct tagExecHistItem EXECHISTITEM;

__declspec(thread) int t_iDepth = 0;
__declspec(thread) unsigned long t_iToken = 0;
__declspec(thread) unsigned int t_iHeadExecHistQueue = -1;
__declspec(thread) EXECHISTITEM* t_pExecHistQueue = NULL;
__declspec(thread) EXECHISTITEM* t_srHist = NULL;


EXECHISTITEM& getCurrentHistItem()
{
   if( NULL != t_pExecHistQueue ) {
      EXECHISTITEM& rHist = t_pExecHistQueue[ t_iHeadExecHistQueue ];
      if( rHist.iGuard_ != s_iExecHistGuard ) {
         *(int*)0 = 0;  // access violation will cause us to blow...
      }
      return( rHist );
   }
   return( *t_srHist );
}

I_CHAR* ExecutionHistory::getSourceFileName( const I_CHAR* pszSourceFile )
{
   I_CHAR* psz = NULL;
   I_CHAR achDrive[3];
   I_CHAR achDir[255];
   I_CHAR achFile[255];
   I_CHAR achExt[255];
   i_splitpath( pszSourceFile,
                achDrive,
                achDir,
                achFile,
                achExt );
   psz = (I_CHAR*)malloc( (i_strlen( achFile ) + i_strlen( achExt ) + 3) * sizeof(I_CHAR) );
   i_strcpy( psz, achFile );
   i_strcat( psz, achExt );
   return( psz );
}

DString ExecutionHistory::getClassName( const char* pszClassName ) 
{
   if( NULL == pszClassName ) {
	  return( DString( I_("NoClass") ) );
   } 
   else if( strlen( pszClassName ) > 6 ) {
	  if( 0 == strncmp( pszClassName, "class ", 6 ) ) {
        return( DString( DStringA( pszClassName + 6 ) ) );
	  }
   }
   return( DString( DStringA( pszClassName ) ) );
}

static enum ExecutionHistory::Status s_LoggingStatus = ExecutionHistory::Status::full;
void ExecutionHistory::setStatus( enum ExecutionHistory::Status eStatus )
{
#if defined(BFRELSYM)
   s_LoggingStatus = eStatus;
#endif
}

enum ExecutionHistory::Status ExecutionHistory::getStatus()
{
#if defined(BFRELSYM)
   return( s_LoggingStatus );
#else
   return( ExecutionHistory::Status::off );
#endif
}

void ExecutionHistory::init()
{
#if defined(BFRELSYM)
   if( NULL == t_pExecHistQueue ) {
      t_pExecHistQueue = new EXECHISTITEM[ s_cExecHistQueueSize ];
   }
   t_srHist = new EXECHISTITEM;
#else
   t_pExecHistQueue = NULL;
   t_srHist = NULL;
#endif
}

void ExecutionHistory::finalize()
{
#if defined(BFRELSYM)
   if( NULL != t_pExecHistQueue ) {
      delete[] t_pExecHistQueue;
      t_pExecHistQueue = NULL;
   }
   delete t_srHist;
#endif
}

void dumpEntry( int iItem, EXECHISTITEM& rItem, FILE* pFile )
{
   I_CHAR szDrive[ _MAX_DRIVE ];
   I_CHAR szDir[ _MAX_DIR ];
   I_CHAR szFName[ _MAX_FNAME ] = I_("");
   I_CHAR szExt[ _MAX_EXT ] = I_("");
   if( NULL != rItem.pszFile_ ) {
      i_splitpath( rItem.pszFile_, szDrive, szDir, szFName, szExt );
   }
   int iDepth = rItem.iDepth_ >= cWhiteSpace ? cWhiteSpace - 1 : rItem.iDepth_;

   if( true == rItem.bBreadcrumb_ ) {
      i_fprintf( pFile, I_("%30.30s%-4.4s(%5d) %5d(%2d)"),
                 szFName, szExt, rItem.ulLine_, 
                 iItem,
                 rItem.iDepth_
             );
      i_fprintf( pFile, I_("b %s%s \n"),
               apszWhiteSpace[ iDepth ],
               rItem.getMessage() != NULL ? ( DStringA( rItem.getMessage() ).c_str() ) : "This is a breadcrumb."
             );
   } else if( NULL != rItem.pszFunction_ ) {
      i_fprintf( pFile, I_("%30.30s%-4.4s(%5d) %5d(%2d)"),
               szFName, szExt, rItem.ulLine_, 
               iItem,
               rItem.iDepth_
             );
      if( NULL == rItem.pszClass_ ) {
         fprintf( pFile, "%c %s%s %s \n", 
                  rItem.bDone_ ? ' ' : '*',
                  apszWhiteSpace[ iDepth ],
                  DStringA( rItem.pszFunction_ ).c_str(),
                  rItem.getMessage() != NULL ? ( DStringA( rItem.getMessage() ).c_str() ) : ""
                );
      } else {
         fprintf( pFile, "%c %s%s::%s %s \n", 
                  rItem.bDone_ ? ' ' : '*',
                  apszWhiteSpace[ iDepth ],
                  DStringA( rItem.pszClass_ ).c_str(), 
                  DStringA( rItem.pszFunction_ ).c_str(),
                  rItem.getMessage() != NULL ? ( DStringA( rItem.getMessage() ).c_str() ) : ""
                );
      }
   }
}

static boost::recursive_mutex cs_;
void ExecutionHistory::dump( FILE* pFile )
{
   boost::recursive_mutex::scoped_lock g( cs_ );
   fprintf( pFile, "Execution History\n" );
   fprintf( pFile, "=======================================================================================================\n" );
   fprintf( pFile, "                       Source File( line) Index Dp ? Function Name \n" );
   fprintf( pFile, "                                                   * = function is still active (i.e. has not returned)\n" );
   fprintf( pFile, "                                                   b = entry is a \"breadcrumb\" message\n" );
   fprintf( pFile, "=======================================================================================================\n" );
   if( NULL != t_pExecHistQueue ) {
      int iItem = 1;
      unsigned int iQueue = t_iHeadExecHistQueue;
      unsigned int iLast = t_iHeadExecHistQueue + 1;
      if( s_cExecHistQueueSize <= t_iHeadExecHistQueue ) {
         iLast = s_cExecHistQueueSize;
      }
      while( true ) {
         dumpEntry( iItem, t_pExecHistQueue[ iQueue ], pFile );
         if( iQueue == iLast ) {
            break;
         }
         --iQueue;   // unsigned int will rollover to 0xffffffff
         if( iQueue >= s_cExecHistQueueSize ) {
            iQueue = s_cExecHistQueueSize - 1;
         }
         ++iItem;
         if( s_cExecHistQueueSize < iItem ) {
            break;
         }

      }
   }
   else {
      fprintf(pFile, "Not recorded.  BFRELSYM is" );
#if !defined(BFRELSYM)
      fprintf(pFile, " not");
#endif
      fprintf(pFile," defined\n");
   }
}

ExecutionHistory::ExecutionHistory( const I_CHAR* pszFunction, 
                                    const I_CHAR* pszFile, 
                                    unsigned long ulLine )
: iGuard_( s_iExecHistGuard )
, iHist_( -1 )
, iToken_( ++t_iToken )
, pszFile_( pszFile )
{
#if defined(BFRELSYM)
   if( s_LoggingStatus != ExecutionHistory::Status::off ) {
      ++t_iDepth;
      push( NULL, pszFunction, pszFile, ulLine, NULL, false );
   }
#endif
}

ExecutionHistory::ExecutionHistory( const I_CHAR* pszClass, 
                                    const I_CHAR* pszFunction, 
                                    const I_CHAR* pszFile, 
                                    unsigned long ulLine )
: iGuard_( s_iExecHistGuard )
, iHist_( -1 )
, iToken_( ++t_iToken )
, pszFile_( pszFile )
{
#if defined(BFRELSYM)
   if( s_LoggingStatus != ExecutionHistory::Status::off ) {
      ++t_iDepth;
      push( pszClass, pszFunction, pszFile, ulLine, NULL, false );
   }
#endif
}

void ExecutionHistory::push( const I_CHAR* pszClass, 
                             const I_CHAR* pszFunction,
                             const I_CHAR* pszFile,
                             unsigned long ulLine,
                             const I_CHAR* pszMessage,
                             bool bBreadcrumb )
{
#if defined(BFRELSYM)
   if( ++t_iHeadExecHistQueue >= s_cExecHistQueueSize ) {
      t_iHeadExecHistQueue = 0;
   }
   iHist_ = t_iHeadExecHistQueue;

   EXECHISTITEM& rHist = t_pExecHistQueue[ iHist_ ];
   if( rHist.iGuard_ != s_iExecHistGuard ) {
      *(int*)0 = 0;  // access violation will cause us to blow...
   }
   rHist.iToken_ = iToken_;
   rHist.pszFile_ = pszFile;
   rHist.ulLine_ = ulLine;
   rHist.bDone_ = false;
   rHist.bBreadcrumb_ = bBreadcrumb;
   rHist.pszFunction_ = pszFunction;
   free(rHist.pszClass_);
   rHist.pszClass_ = i_strdup(pszClass);
   rHist.addMessage( pszMessage );
   rHist.iDepth_ = t_iDepth;

   DString dstrFile = DStringA(pszFile);
   if( bf::log::theLog.getReportingThreshold() >= bf::log::LogStream::e_trace ) {
      bf::log::theLog << bf::log::ltrace
                      << I_("-->(") << rHist.iDepth_ << I_(") ") << dstrFile
                      << I_(" [") << ulLine << I_("] ")
                      << (NULL == pszClass ? I_("") : pszClass )
                      << I_("::") 
                      << pszFunction
				         << bf::log::endlf;
   }
#endif
}

ExecutionHistory::~ExecutionHistory()
{
#if defined( BFRELSYM )
   if( s_LoggingStatus != ExecutionHistory::Status::off ) {
      --t_iDepth;
      if( 0 > t_iDepth ) t_iDepth = 0;
      EXECHISTITEM& rHist = t_pExecHistQueue[ iHist_ ];
      if( false == rHist.bDone_ && rHist.iToken_ == iToken_ ) {
         rHist.bDone_ = true;
         rHist.iToken_ = 0;
         DString dstrFile = DStringA(rHist.pszFile_);
         bf::log::theLog << bf::log::ltrace 
                         << I_("<--(") << t_iDepth << I_(") ") << dstrFile << I_(" ")
                         << (NULL == rHist.pszClass_ ? I_("") : rHist.pszClass_ )
                         << I_("::") 
                         << rHist.pszFunction_
					          << bf::log::endlf;

      }
   }
#endif
}

void ExecutionHistory::addMessage( const I_CHAR* pszMask, ... )
{
#if defined(BFRELSYM)
   if( s_LoggingStatus != ExecutionHistory::Status::off ) {
      I_CHAR szBuf[4096];
      va_list arg_ptr;

      va_start(arg_ptr, pszMask);
      i_vsnprintf(szBuf, sizeof(szBuf) / sizeof( szBuf[0] ), pszMask, arg_ptr);
      va_end(arg_ptr);

      getCurrentHistItem().addMessage( szBuf );
   }
#endif
   return;
}

