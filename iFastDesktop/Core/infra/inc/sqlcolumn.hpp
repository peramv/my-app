#ifndef SQLCOLUMN_HPP
#define SQLCOLUMN_HPP

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
 *    Copyright 1996-2000 by DST Systems, Inc.
 */

/**@pkg DICORE */    

#ifndef DIODBC_HPP
   #include "diodbc.hpp"
#endif

/**
 * SQLCloumn represents a single column for a single row of data.
 */
class SQLColumn
{
   public:
      /**
       * Default Constuctor
       */
      SQLColumn();

      /**
       * Copy Constructor (required since this is used in a 
       * collection)
       *
       * @param copy - SQLColumn object to copy
       */
      SQLColumn( const SQLColumn &copy );

      /**
       * Constructor to initialize all members.
       *
       * @param strValue - Data value
       * @param col - column ID
       * @param type - Column type
       */
      SQLColumn( const DString &strValue, int col, Odbc::Type type );

      /**
       * Destructor
       */
      virtual ~SQLColumn();

   public:
      /**
       * Gets the value.
       *
       * @return The value.
       */
      const DString &getValue() const { return m_strValue; };

      /**
       * Sets the value.
       *
       * @param strValue - The value to set.
       */
      void setValue( const DString &strValue );

      /**
       * Returns the column ID.
       *
       * @return The column ID.
       */
      int getColoumn() const { return m_nCol; };

      /**
       * Sets the column ID
       *
       * @param col - The new column ID.
       */
      void setColumn( int col );

      /**
       * Returns the data type.
       *
       * @return The data type.
       */
      Odbc::Type getType() const { return m_tType; };

      /**
       * Sets the data type.
       *
       * @param type - The new data type.
       */
      void setType( Odbc::Type type );

      /**
       * Assignment operator.
       *
       * @param copy - The SQLColumn object to copy
       *
       * @return Reference to self.
       */
      SQLColumn &operator=( const SQLColumn &copy );

   private:
      DString      m_strValue;
      Odbc::Type   m_tType;
      int          m_nCol;
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
// $Log:   Y:/VCS/iFastAWD/inc/sqlcolumn.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:32:44   kovacsro
//Initial revision.
// 
//    Rev 1.3   28 Nov 2000 09:27:26   dt14177
// cleanup
// 
//    Rev 1.2   Apr 18 2000 12:55:32   DMUM
// Comments to JavaDoc
//
//    Rev 1.1   Apr 19 1999 12:59:14   DTWK
//
//
//    Rev 1.0   Apr 16 1999 17:50:46   DMUM
//
//
//    Rev 1.0   Feb 08 1999 10:51:42   DMUM
//
//
//

#endif // SQLColumn_HPP

