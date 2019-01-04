#ifndef TESTINPUTDATA_HPP
#define TESTINPUTDATA_HPP

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
 *    Copyright 2001 by DST Systems, Inc.
 */


#ifndef COMMONTEMPLATES_H
   #include "commontemplates.h"
#endif

#ifndef DSTRING_HPP
   #include "dstring.hpp"
#endif

#undef DITEST_LINKAGE
#ifdef DITEST_DLL
   #define DITEST_LINKAGE CLASS_EXPORT
#else
   #define DITEST_LINKAGE CLASS_IMPORT
#endif

/**
 * This class is used to accumulate test input data.
 */

class DITEST_LINKAGE TestInputData
{
public:
   /**
    * default constructor
    */
   TestInputData()
   {
   }

   /**
    * setter
    * 
    * @param name   the name of the function (used as a key)
    */
   void setMethodName( const DString & name )
   {
      m_methodName = name;
   }

   /**
    * setter
    * 
    * @param name   the name of the particular test case
    */
   void setCaseName( const DString & name )
   {
      m_caseName = name;
   }

   /**
    * getter
    * 
    * @return the method name
    */
   const DString & getMethodName( void ) const
   {
      return m_methodName;
   }

   /**
    * getter
    * 
    * @return the test case name
    */
   const DString & getCaseName( void ) const
   {
      return m_caseName;
   }

   /**
    * getter
    * 
    * @return a reference to a vector containing the data values
    */
   string_vector & getInputDataValues( void )
   {
      return m_inputDataValues;
   }

private: // hidden, unimplemented methods
   
   /**
    * Copy constructor
    */
   TestInputData( const TestInputData & );
   
   /**
    * assignment operator
    */
   TestInputData & operator=( const TestInputData & ) const;

private: // attributes
   
   DString m_methodName; // a key to the table
   DString m_caseName;   // used to build a failure report
   string_vector m_inputDataValues;
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
// $Log:   Y:/VCS/iFastAWD/inc/testinputdata.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:33:04   kovacsro
//Initial revision.
//
//   Rev 1.1   13 Nov 2001 15:45:58   dt14177
//Added the testinputdata enhancement
//to get input from files
//
//   Rev 1.0   23 Jan 2001 13:31:12   dt14177
//initial check in; not yet code-reviewed
//
#endif // TESTINPUTDATA_HPP
