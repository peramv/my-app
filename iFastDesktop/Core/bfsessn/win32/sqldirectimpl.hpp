#ifndef SQLDIRECTIMPL_HPP
#define SQLDIRECTIMPL_HPP

/*
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1996-2000 by DST Systems, Inc.
 */

// This is so that the interface class does not have to include stdafx.h
#include "stdafx.h"

#ifndef DSTRINGA_HPP
   #include <dstringa.hpp>
#endif

#ifndef DIODBC_HPP
   #include <diodbc.hpp>
#endif

#ifndef SQLCOLUMN_HPP
   #include <bfsessn\sqlcolumn.hpp>
#endif

#ifndef COMMONTEMPLATES_H
   #include <commontemplates.h>
#endif

class SQLDirectImpl
{
public:
   /**
    * Default constructor
    */
   SQLDirectImpl();

   /**
    * Constructor
    */
   SQLDirectImpl( const DString& );

   /**
    * Constructor
    */
   SQLDirectImpl( const DString&,
                  const DString&,
                  const DString& );

   /**
    * Destructor
    */
   virtual ~SQLDirectImpl();

   /**
    * Frees the previous SQL statement, removes
    * the columns from the column array, and
    * allocates a new SQL statement.
    */
   void Close( void );

   /**
    * Gets the SQL error message
    * 
    * @param strMsg SQL error message
    * @param pSqlState 
    */
   void GetError( DString& strMsg, SQLTCHAR *pSqlState = NULL );

   /**
    * Executes an SQL statement
    * 
    * @param strSQL SQL String to execute
    * @return 
    */
   int ExecuteSQL( const DString& strSQL );

   /**
    * Connects to an unsecured database
    * 
    * @param source - database
    * @return 
    */
   int Connect( const DString & source );

   /**
    * Connects to a secured database
    * 
    * @param source   - database
    * @param userId
    * @param password
    * @return 
    */
   int Connect( const DString & source,
                const DString & userId,
                const DString & password );

   /**
    * Executes an SQL fetch
    * 
    * @return 
    */
   int Fetch( void );

   /**
    * Maps the column name to the Id
    * 
    * @param name
    * @return Id = -1, if the name was not found 
    */
   int GetColumnID( const DString & name );

   /**
    * Wrapper for SQL
    * 
    * @param columnId
    * @return 
    */
   Odbc::Type GetColumnType( int columnId );

   Odbc::Type CheckForColumnInTable( const DString & column,
                                     const DString & table );

   /**
    * Returns the field value
    * 
    * @return the field value
    */
   DString GetCol( int );

   /**
    * Returns the column value
    * 
    * @param columnName
    * @return the column value
    */
   DString GetCol( const DString & columnName );

   /**
    * Maps the column Id to the name
    * 
    * @return the column name
    */
   DString GetColumnName( int );

private:
   void KillCols( void );
   Odbc::Type IntToOdbcType( int );
   int OdbcTypeToInt( Odbc::Type );

private:
   typedef std::map<int, SQLColumn * > ColumnMap;
   typedef std::map<DString, Odbc::Type > ColumnList;

   SQLTCHAR*     m_psvSQL;
   SQLTCHAR*     m_psvErrorMsg;
   HENV          m_hEnv;
   HDBC          m_hDBC;
   HSTMT         m_hStmt;
   ColumnMap     m_ColArray;
   ColumnList    m_ColumnList;
   string_vector m_TableList;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF Core/bfsessn/win32/sqldirectimpl.hpp-arc  $
//
//   Rev 1.3   Oct 22 2004 08:59:00   PURDYECH
//PET910 - .NET Conversion Fixes
//
//   Rev 1.2   Nov 27 2002 15:05:08   PURDYECH
//Documentation Changes
//
//   Rev 1.1   Oct 09 2002 17:41:08   PURDYECH
//New PVCS Database
//
//   Rev 1.0   28 May 2002 12:11:16   SMITHDAV
//Initial revision.
// 
//    Rev 1.1   07 Dec 2000 12:50:44   dt14177
// cleanup and documentation
// 
//    Rev 1.0   Apr 16 1999 17:51:32   DMUM
//  
//
//    Rev 1.1.1.0   Mar 30 1999 14:31:30   DMUM
//
//
//    Rev 1.1   Feb 08 1999 14:34:38   DMUM
// Connect will now re-try on timeout
//
//    Rev 1.0   Feb 08 1999 10:50:10   DMUM
//
//
//


#endif // SQLDIRECTIMPL_HPP
