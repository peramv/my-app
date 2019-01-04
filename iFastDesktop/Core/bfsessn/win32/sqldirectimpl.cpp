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
// ^FILE   : SQLDirectImpl.cpp
// ^AUTHOR : Mark Tarantino
// ^DATE   : 27 Jan 1999
//
// ----------------------------------------------------------
//
// ^CLASS    : SQLDirect
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************
//CP20040415#define DIODBC_DLL
#include "stdafx.h"

#include "sqldirectimpl.hpp"

#include <bfsessn\bfsessn.h>
#include <stringfunctions.hpp>
#include <conditionmanager.hpp>

namespace
{
   const int CONNECT_ATTEMPTS = 2;
   const int DATA_BUFFER      = 8192;
   const int NAME_BUFFER      = 256;
   const int STR_LEN          = 128+1;
   const int PW_LEN           = 32;

   const I_CHAR *IDI_SOURCE    = I_( "SOURCE=" );
   const I_CHAR *IDI_SQL_ERROR = I_( "SQL_ERROR=" );
}

//******************************************************************************
//              Public Methods
//******************************************************************************

SQLDirectImpl::SQLDirectImpl()
: m_psvSQL( NULL ),
m_psvErrorMsg( new SQLTCHAR[ SQL_MAX_MESSAGE_LENGTH-1 ] ),
m_hEnv( NULL ),
m_hDBC( NULL ),
m_hStmt( NULL )
{
}

SQLDirectImpl::SQLDirectImpl( const DString& strConnect )
: m_psvSQL( NULL ),
m_psvErrorMsg( new SQLTCHAR[ SQL_MAX_MESSAGE_LENGTH-1 ] ),
m_hEnv( NULL ),
m_hDBC( NULL ),
m_hStmt( NULL )
{
   Connect( strConnect );
}

SQLDirectImpl::SQLDirectImpl( const DString& strConnect,
                              const DString &strUser,
                              const DString &strPassword )
: m_psvSQL( NULL ),
m_psvErrorMsg( new SQLTCHAR[ SQL_MAX_MESSAGE_LENGTH-1 ] ),
m_hEnv( NULL ),
m_hDBC( NULL ),
m_hStmt( NULL )
{
   Connect( strConnect, strUser, strPassword );
}

SQLDirectImpl::~SQLDirectImpl()
{
   if( m_psvErrorMsg )
   {
      delete[] m_psvErrorMsg;
   }

   if( m_psvSQL )
   {
      delete[] m_psvSQL;
   }

   if( NULL != m_hStmt )
   {
      SQLFreeStmt( m_hStmt, SQL_DROP );
   }

   if( NULL != m_hDBC )
   {
      SQLDisconnect( m_hDBC );
      SQLFreeConnect( m_hDBC );
   }

   if( NULL != m_hEnv )
   {
      SQLFreeEnv( m_hEnv );
   }

   KillCols();
}

void SQLDirectImpl::Close( void )
{
   if( NULL != m_hStmt )
   {
      // Free
      SQLFreeStmt( m_hStmt, SQL_DROP );

      KillCols();

      // Allocate again.
      SQLAllocStmt( m_hDBC, &m_hStmt );
   }
}

void SQLDirectImpl::GetError( DString& strMsg, SQLTCHAR *pSqlState )
{
   bool bSqlStateNotPassedIn = NULL == pSqlState;

   if( bSqlStateNotPassedIn )
   {
      pSqlState = new SQLTCHAR[SQL_MAX_MESSAGE_LENGTH-1];
   }

   SDWORD NativeError;
   SWORD svErrorMsg;

   SQLError( m_hEnv,
             m_hDBC,
             m_hStmt,
             pSqlState,
             &NativeError,
             m_psvErrorMsg,
             SQL_MAX_MESSAGE_LENGTH-1,
             &svErrorMsg );

   if( bSqlStateNotPassedIn )
   {
      delete[] pSqlState;
   }

   strMsg = (I_CHAR *)m_psvErrorMsg;
}



int SQLDirectImpl::ExecuteSQL( const DString& strSQL )
{
   TRACE_METHOD( I_( "SQLDirectImpl" ), I_( "ExecuteSQL( const DString&  )" ) )
   TRACE_CLASS_MSG( I_( "SQLDirectImpl" ),
                    I_( "ExecuteSQL( const DString&  )" ),
                    strSQL )

   if( m_psvSQL )
   {
      delete[] m_psvSQL;
   }

   if( NULL != m_hStmt )
   {
      Close();
   }

   m_psvSQL = new SQLTCHAR[ strSQL.size()+1 ];
   i_strcpy( ( I_CHAR * )m_psvSQL, strSQL.c_str() );

   int nRet=SQLExecDirect( m_hStmt, m_psvSQL, SQL_NTS );

   if( SQL_SUCCESS_WITH_INFO == nRet || SQL_SUCCESS != nRet )
   {
      DString strError;
      GetError( strError );
      int nCode = SQL_SUCCESS_WITH_INFO == nRet ? DIODBC_INFO : DIODBC_ERROR;

      MAKEFRAMENOTRACE( DISESSN_CONDITION, I_( "SQLDirectImpl::ExecuteSQL()" ) );

      DString idiMsg = IDI_SQL_ERROR;
      idiMsg += strError;

      ADDCONDITIONFROMFILEIDI( nCode, idiMsg );
   }

   return(nRet);
}

int SQLDirectImpl::Connect( const DString& strSource )
{
   DString strUser = I_( "sa" );
   DString strPassword = I_( "" );

   return(Connect( strSource, strUser, strPassword ));
}

int SQLDirectImpl::Connect( const DString &strSource,
                            const DString &strUser,
                            const DString &strPassword  )
{
   TRACE_METHOD( I_( "SQLDirectImpl" ),
                 I_( "Connect( const DString &, const " )
                 I_( "DString &, const DString &  )" ) )

   int nConnect = SQLAllocEnv( &m_hEnv );
   DString strConnectError;

   if( SQL_SUCCESS == nConnect )
   {
      nConnect=SQLAllocConnect( m_hEnv, &m_hDBC );

      if( SQL_SUCCESS == nConnect )
      {
         SQLSetConnectOption( m_hDBC, SQL_LOGIN_TIMEOUT, 5 );

         // Connect to the datasource.
         SQLTCHAR *pSqlState = new SQLTCHAR[SQL_MAX_MESSAGE_LENGTH-1];
         SQLTCHAR *psvSource = new SQLTCHAR[ strSource.size()+1 ];
         SQLTCHAR *psvUser = new SQLTCHAR[ PW_LEN ];
         SQLTCHAR *psvPassword = new SQLTCHAR[ PW_LEN ];

         i_strcpy( ( I_CHAR * )psvUser, strUser.c_str() );
         i_strcpy( ( I_CHAR * )psvPassword, strPassword.c_str() );
         i_strcpy( ( I_CHAR * )psvSource, strSource.c_str() );

         int nAttempt = 0;

         // If we get a timeout error, try again
         while( CONNECT_ATTEMPTS >= ++nAttempt )
         {
            nConnect = SQLConnect( m_hDBC,
                                   psvSource,
                                   SQL_NTS,
                                   psvUser,
                                   SQL_NTS,
                                   psvPassword,
                                   SQL_NTS );

            if( SQL_SUCCESS == nConnect || SQL_SUCCESS_WITH_INFO == nConnect )
            {
               // Now that the datasource is open, get our SQL statement handle.
               nConnect = SQLAllocStmt( m_hDBC, &m_hStmt );
               break;
            }
            else
            {
               // If we get a timeout, try again
               GetError( strConnectError, pSqlState );
               DString strSqlState = (I_CHAR *)pSqlState;
               stripTrailing( strSqlState );

#ifdef ENABLE_TRACING
               DString msg = I_( "SQL STATE = " );
               msg += strSqlState;
               TRACE_CLASS_MSG( I_( "SQLDirectImpl" ), I_( "Connect()" ), msg )
#endif

               if( I_( "S1T00" ) != strSqlState )
               {
                  // Not a timeout
                  break;
               }
            }

            // Clear out the error
            strConnectError = "";
         }

         delete[] pSqlState;
         delete[] psvSource;
         delete[] psvUser;
         delete[] psvPassword;
      }
   }

   if( ( SQL_SUCCESS_WITH_INFO == nConnect ) || ( SQL_SUCCESS != nConnect ) )
   {
      DString strError;

      if( strConnectError.empty() )
      {
         GetError( strError );
      }
      else
      {
         strError = strConnectError;
      }

      if( SQL_SUCCESS_WITH_INFO == nConnect )
      {
         MAKEFRAMENOTRACE( DISESSN_CONDITION, I_( "SQLDirectImpl::Connect()" ) );

         DString idiMsg = IDI_SQL_ERROR;
         idiMsg += DString( strError );

         ADDCONDITIONFROMFILEIDI( DIODBC_INFO, idiMsg );
      }
      else
      {
         DString idiMsg = IDI_SOURCE;
         idiMsg += I_( "\"" );
         idiMsg += DString( strSource );
         idiMsg += I_( "\"" );
         idiMsg += I_( ";" );
         idiMsg += IDI_SQL_ERROR;
         idiMsg += DString( strError );

         THROWFROMFILEIDI( DISESSN_CONDITION,
                           I_( "SQLDirectImpl::Connect()" ),
                           DIODBC_CONNECT_ERROR,
                           idiMsg );
      }
   }

   return(nConnect);
}

int SQLDirectImpl::Fetch( void )
{
   // Start with a fresh batch of columns.
   KillCols();

   // Fetch the next row.
   int nRet = SQLFetch( m_hStmt );

   return(nRet);
}

int SQLDirectImpl::GetColumnID( const DString& strField )
{
   SQLTCHAR svColName[NAME_BUFFER];
   SWORD swCol,swType,swScale,swNull;
   UDWORD pcbColDef;
   SDWORD wColLen;
   DString strName;
   DString strOwner;

   memset( &svColName, 0, NAME_BUFFER );

   int nCol = -1;
   int nMaxCols = 0;

   // Get the total # of columns in this query.
   int nRet = SQLColAttributes( m_hStmt,
                                0,
                                SQL_COLUMN_COUNT,
                                svColName,
                                NAME_BUFFER,
                                &swScale,
                                &wColLen );

   if( SQL_SUCCESS == nRet || SQL_SUCCESS_WITH_INFO == nRet )
   {
      nCol = 1;
      nMaxCols = (int)wColLen;

      while( nCol <= nMaxCols )
      {
         nRet = SQLDescribeCol( m_hStmt,
                                nCol,
                                svColName,
                                NAME_BUFFER,
                                &swCol,
                                &swType,
                                &pcbColDef,
                                &swScale,
                                &swNull );

         // If we hit this condition, then our field is not in the dataset.
         if( ! ( SQL_SUCCESS == nRet || SQL_SUCCESS_WITH_INFO == nRet ) )
         {
            nCol = -1;
            break;
         }

         strName = (I_CHAR *)svColName;

         stripTrailing( strName );

         if( strName == strField )
         {
            break;
         }
         else
         {
            nCol++;
         }
      }

      if( nCol > nMaxCols )
      {
         nCol = -1;
      }
   }

   if( SQL_SUCCESS_WITH_INFO == nRet || SQL_SUCCESS != nRet )
   {
      DString strError;
      GetError( strError );
      int nCode = SQL_SUCCESS_WITH_INFO == nRet ? DIODBC_INFO : DIODBC_ERROR;

      MAKEFRAMENOTRACE( DISESSN_CONDITION, I_( "SQLDirectImpl::GetColumnID()" ) );

      DString idiMsg = IDI_SQL_ERROR;
      idiMsg += DString( strError );

      ADDCONDITIONFROMFILEIDI( nCode, idiMsg );
   }

   return(nCol);
}

Odbc::Type SQLDirectImpl::GetColumnType( int nCol )
{
   Odbc::Type tType = Odbc::sqlDefault;

   // Due to the nature of the SQL API, repeated calls to the same column will
   // result in a NULL value passed back into svData. We need to keep track of
   // the columns that have been used already and if so, pass back
   // the data stored in our array.

   ColumnMap::iterator iter = m_ColArray.find( nCol );

   if( m_ColArray.end() == iter )
   {
      // Get the column from the SQL cursor.
      SQLTCHAR svColName[NAME_BUFFER];
      SWORD swCol,swType,swScale,swNull;
      UDWORD pcbColDef;

      SQLDescribeCol( m_hStmt,
                      nCol,
                      svColName,
                      NAME_BUFFER,
                      &swCol,
                      &swType,
                      &pcbColDef,
                      &swScale,
                      &swNull );

      tType = IntToOdbcType( (int)swType );
   }
   else
   {
      // Get the value from the column array.
      tType = ( ( *iter ).second )->getType();
   }

   return(tType);
}

Odbc::Type SQLDirectImpl::CheckForColumnInTable( const DString &strField,
                                                 const DString &strTable )
{
   Odbc::Type tType = Odbc::sqlUnknown;

   if( strField.empty() || strTable.empty() )
   {
      return(tType);
   }

   // First see if we've checked this table already
   bool bNotFound = true;
   string_vector_iterator svIter = m_TableList.begin();

   // If the number of tables become extensively large, then a 'set' of strings
   // should be used in place of a 'vector' of strings.  'set' has the method
   // find() and the strings are stored in a btree.
   while( bNotFound && svIter != m_TableList.end() )
   {
      bNotFound = strTable != *svIter;
      ++svIter;
   }

   if( bNotFound )
   {
      SQLTCHAR  szTableName[STR_LEN], szColName[STR_LEN];
      SWORD    dataType;
      SDWORD   cbTableName, cbColName, cbDataType;

      DString strColumnTable;

      int nSize = strTable.size();
      SQLTCHAR *psvTable = new SQLTCHAR[++nSize];

      i_strcpy( ( I_CHAR * )psvTable, strTable.c_str() );

      // We have not yet looked at this table
      // Since will will look, add it to the list
      m_TableList.push_back( strTable );

      if( NULL != m_hStmt )
      {
         Close();
      }

      int nRet = SQLColumns( m_hStmt,
                             NULL, 0,
                             NULL, 0,
                             psvTable, nSize,
                             NULL, 0 );

      if( SQL_SUCCESS == nRet || SQL_SUCCESS_WITH_INFO == nRet )
      {
         SQLBindCol(m_hStmt, 3, SQL_C_TCHAR, szTableName, STR_LEN,&cbTableName);
         SQLBindCol(m_hStmt, 4, SQL_C_TCHAR, szColName, STR_LEN, &cbColName);
         SQLBindCol(m_hStmt, 5, SQL_C_SSHORT, &dataType, 0, &cbDataType);

         bool bFetching = true;

         while( bFetching )
         {
            nRet = SQLFetch( m_hStmt );

            if( SQL_ERROR == nRet || SQL_SUCCESS_WITH_INFO == nRet )
            {
               DString strError;
               GetError( strError );
               int nCode = SQL_SUCCESS_WITH_INFO == nRet ? DIODBC_INFO :
                           DIODBC_ERROR;

               MAKEFRAMENOTRACE( DISESSN_CONDITION,
                                 I_( "SQLDirectImpl::CheckForColumnInTable()" ) );

               DString idiMsg = IDI_SQL_ERROR;
               idiMsg += DString( strError );

               ADDCONDITIONFROMFILEIDI( nCode, idiMsg );
            }

            bFetching = SQL_SUCCESS == nRet || SQL_SUCCESS_WITH_INFO == nRet;

            if( bFetching )
            {
               strColumnTable = (I_CHAR *)szColName;
               strColumnTable += I_( ":" );
               strColumnTable += (I_CHAR *)szTableName;

               m_ColumnList[ strColumnTable ] = IntToOdbcType( (int)dataType );
            }
         }
      }

      delete[] psvTable;
   }

   DString strLookup = strField;
   strLookup += I_( ":" );
   strLookup += strTable;

   ColumnList::iterator clIter = m_ColumnList.find( strLookup );

   if( clIter != m_ColumnList.end() )
   {
      tType = ( *clIter ).second;
   }

   return(tType);
}

DString SQLDirectImpl::GetCol( int nCol )
{
   DString strValue;

   // Due to the nature of the SQL API, repeated calls to the same column will
   // result in a NULL value passed back into svData. We need to keep track of
   // the columns that have been used already and if so, pass back
   // the data stored in our array.

   if( 0 < nCol )
   {
      ColumnMap::iterator iter = m_ColArray.find( nCol );

      if( m_ColArray.end() == iter )
      {
         // Get the column from the SQL cursor.
         SQLTCHAR svData[DATA_BUFFER];
         SDWORD cbDataLen;
         Odbc::Type tType = GetColumnType( nCol );
         int nType = OdbcTypeToInt( tType );

         SQLGetData( m_hStmt,
                     nCol,
                     nType,
                     &svData,
                     DATA_BUFFER,
                     &cbDataLen );

         strValue = (I_CHAR *)svData;
         stripTrailing( strValue );
         m_ColArray[ nCol ] = new SQLColumn( strValue, nCol, tType );
      }
      else
      {
         // Get the value from the column array.
         strValue = ( ( *iter ).second )->getValue();
      }
   }

   return(strValue);
}

DString SQLDirectImpl::GetCol( const DString& strName )
{
   return(GetCol( GetColumnID( strName ) ));
}

DString SQLDirectImpl::GetColumnName( int nCol )
{
   SQLTCHAR svColName[NAME_BUFFER];
   SWORD swCol,swType,swScale,swNull;
   UDWORD pcbColDef;

   SQLDescribeCol( m_hStmt,
                   nCol,
                   svColName,
                   NAME_BUFFER,
                   &swCol,
                   &swType,
                   &pcbColDef,
                   &swScale,
                   &swNull );

   DString strName = (I_CHAR *)svColName;
   stripTrailing( strName );

   return(strName);
}

//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************
//
// ^PRIVATE METHOD      : SQLDirectImpl::KillCols
//
// ^DESCRIPTION :
//
// ^PARAMETERS  : none
//
// ^RETURNS     : void -
//
// ^THROWS      : < description of all possible thrown exceptions >
//
// ^EXAMPLE     : < if the use of this member is not obvious,
//                  give an example >
//
//******************************************************************************
void SQLDirectImpl::KillCols()
{
   ColumnMap::iterator iter = m_ColArray.begin();

   while( iter != m_ColArray.end() )
   {
      SQLColumn *pCol = ( *iter ).second;
      delete pCol;
      ++iter;
   }

   m_ColArray.erase( m_ColArray.begin(), m_ColArray.end() );
}

//******************************************************************************
//
// ^PRIVATE METHOD      : SQLDirectImpl::IntToOdbcType
//
// ^DESCRIPTION :
//
// ^PARAMETERS  :
//   ^^ int nType -
//
// ^RETURNS     : Odbc::Type -
//
// ^THROWS      : < description of all possible thrown exceptions >
//
// ^EXAMPLE     : < if the use of this member is not obvious,
//                  give an example >
//
//******************************************************************************
Odbc::Type SQLDirectImpl::IntToOdbcType( int nType )
{
   Odbc::Type tType;

   // For now we only care about these two types.  Should ask Mark why
   switch( nType )
   {
      case SQL_C_DEFAULT:
      case SQL_LONGVARBINARY:
         tType = Odbc::sqlDefault;
         break;

      case SQL_CHAR:
         tType = Odbc::sqlChar;
         break;

      case SQL_INTEGER:
         tType = Odbc::sqlInteger;
         break;

      case SQL_SMALLINT:
         tType = Odbc::sqlSmallint;
         break;

      case SQL_REAL:
         tType = Odbc::sqlReal;
         break;

      case SQL_DOUBLE:
         tType = Odbc::sqlDouble;
         break;

      default:
         tType = Odbc::sqlChar;
         break;
   }

   return(tType);
}

//******************************************************************************
//
// ^PRIVATE METHOD      : SQLDirectImpl::OdbcTypeToInt
//
// ^DESCRIPTION :
//
// ^PARAMETERS  :
//   ^^ Odbc::Type tType -
//
// ^RETURNS     : int -
//
// ^THROWS      : < description of all possible thrown exceptions >
//
// ^EXAMPLE     : < if the use of this member is not obvious,
//                  give an example >
//
//******************************************************************************
int SQLDirectImpl::OdbcTypeToInt( Odbc::Type tType )
{
   int nType;

   switch( tType )
   {
      case Odbc::sqlChar:
         nType = SQL_CHAR;
         break;
      case Odbc::sqlInteger:
         nType = SQL_INTEGER;
         break;
      case Odbc::sqlSmallint:
         nType = SQL_SMALLINT;
         break;
      case Odbc::sqlReal:
         nType = SQL_REAL;
         break;
      case Odbc::sqlDouble:
         nType = SQL_DOUBLE;
         break;
      case Odbc::sqlDefault:
         nType = SQL_C_DEFAULT;
         break;
   }

   return(nType);
}



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF Core/bfsessn/win32/sqldirectimpl.cpp-arc  $
//
//   Rev 1.3   Oct 22 2004 08:58:58   PURDYECH
//PET910 - .NET Conversion Fixes
//
//   Rev 1.2   Apr 20 2004 10:47:44   PURDYECH
//PTS10024114 - Integrate changes from KC to deal with Double Locking in AWD.
// 
//    Rev 1.1   Oct 09 2002 17:41:08   PURDYECH
// New PVCS Database
// 
//    Rev 1.0   28 May 2002 12:11:16   SMITHDAV
// Initial revision.
// 
//    Rev 1.2   13 Jan 2000 16:29:32   dt20842
// Added back in ODBC support
// 
//    Rev 1.1   Apr 22 1999 15:56:48   DMUM
// condition message changes
//
//    Rev 1.0   Apr 16 1999 17:51:28   DMUM
//
//
//    Rev 1.1.1.0   Mar 30 1999 14:31:28   DMUM
// Sync Up with latest 1.6.x
//
//    Rev 1.1   Feb 08 1999 14:34:38   DMUM
// Connect will now re-try on timeout
//
//    Rev 1.0   Feb 08 1999 10:50:08   DMUM
//
//
//

