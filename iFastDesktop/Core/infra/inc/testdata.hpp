#ifndef TESTDATA_HPP
#define TESTDATA_HPP

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
 *    Copyright 2000-2001 by DST Systems, Inc.
 */

#ifndef COMMONTEMPLATES_H
   #include "commontemplates.h"
#endif

#ifndef DSTRING_HPP
   #include "dstring.hpp"
#endif

#ifndef TESTSECTION_HPP
/**@#-*/  // forward declarations
class TestData;
/**@#+*/
   #include "testsection.hpp"
   #include "testsectionEx.hpp"
#endif

#ifndef TESTINPUTDATA_HPP
#include "testinputdata.hpp"
#endif

#undef DITEST_LINKAGE
#ifdef DITEST_DLL
   #define DITEST_LINKAGE CLASS_EXPORT
#else
   #define DITEST_LINKAGE CLASS_IMPORT
#endif

/**
 * This class is passed to a test to accumalate results.  When used in multiple
 * threads, pass only a single instance to a single thread.  This class is
 * thread aware, but is not safe to pass a single instance to more than one
 * thread.
 *
 * <b>Example:</b>
 * <pre>
 *
 *    for ( int count = 0; count < 100; ++count )
 *    {
 *       // We have custom data to pass to a thread.
 *       void *pParam = (void *)count;
 *
 *       // Ask for a new TestData object
 *       TestData *pData = TestData::newTestDataObject( pParam );
 *
 *       // Pass the TestData object to the thread.
 *       ThreadCount::beginThread( worker, 0, pData, count < 60 );
 *    }
 *
 *</pre>
 */
class DITEST_LINKAGE TestData
{
public:
   /**
    * The method returns a pointer to a new TestData object.  Call this
    * method before starting each thread to pass each thread a different
    * TestData object.
    *
    * @param arglist - This allows custom data to be passed to the thread.
    *
    * @return Pointer to a newly created TestData object.
    */
   static TestData *newTestDataObject( void *arglist = NULL );

   /**
    * Call this method to get the vector of informational messages.
    *
    * @return The list of informational messages.
    */
   const string_vector &getInformationList();

   /**
    * Call this method to get the vector of error messages.
    *
    * @return The list of error messages.
    */
   const string_vector &getErrorList();

   /**
    * Call this method to get the vector of Condition messages.
    *
    * @return The list of Condition messages.
    */
   const string_vector &getConditionList();

   /**
    * This method will iterate through the list of informational messages
    * and send them to the consol output using std::cout.
    */
   void coutInformation();

   /**
    * This method will iterate through the list of error messages
    * and send them to the consol output using std::cout.
    */
   void coutErrors();

   /**
    * This method will iterate through the list of Condition messages
    * and send them to the consol output using std::cout.
    */
   void coutCondtions();

   /**
    * This method will iterate through the list of informational messages
    * and stream them to the ostream object passed in.
    */
   void streamInformation( std::ostream &ostr );

   /**
    * This method will iterate through the list of error messages
    * and stream them to the ostream object passed in.
    */
   void streamErrors( std::ostream &ostr );

   /**
    * This method will iterate through the list of Condition messages
    * and stream them to the ostream object passed in.
    */
   void streamConditions( std::ostream &ostr );

   /**
    * Call this method to determine if this particular test failed.
    *
    * @return True if the test failed.
    */
   bool getTestFailed() const;

   /**
    * Call this method to determine if this particular test completed.  A test
    * is only considered complete if the method TestSection::complete() is
    * called.
    *
    * @return True if the test completed.
    */
   bool getTestCompleted() const;

   /**
    * Operator overload provided so that a TestData * can be passed as a
    * void * in a function call.
    *
    * @return this - cast as a void *.
    */
   operator void * () { return (void *) this; }

   /**
    * getter
    * 
    * @return pointer to the input data object
    */
   TestInputData * getInputDataObject( void ) const
   {
      return m_TestInputData;
   }
   
   /**
    * This static method will return true if there are any outstanding tests.
    * A test is still outstanding if any TestSection objects are still around.
    *
    * @return True if one or more tests are outstanding.
    */
   static bool getTestsOutstanding();

   /**
    * The method will return the number of failed tests.  A test is considered
    * to have failed if the method TestSection::complete() is not called, or
    * either the method TestSection::addErrorMessage() or
    * TestSection::failImmediatly() is called.
    *
    * @return The count of failed tests.
    */
   static int getFailureCount();

   /**
    * This method sets the iterator to point at the first TestData object.  Call the
    * method getTestData() to iterate through the remainder of the TestData
    * objects.
    */
   static TestData * getFirstTestData();

   /**
    * This method returns a pointer to the next TestData object.  This is used
    * to iterate through the all the TestData objects instantiated by the
    * method newTestDataObject().  When the end of the list is reached, a NULL
    * is returned.
    *
    * @return Pointer to a TestData object or NULL.
    */
   static TestData * getNextTestData();

   /**
    * This method returns a pointer to the first TestData object that failed.
    * Call the method getNextFailedTest() to iterate through the remainder of
    * the failed TestData objects. If there are no failures, this method will
    * return a NULL.
    *
    * @return Pointer to a TestData object or NULL.
    */
   static TestData *getFirstFailedTest();

   /**
    * This method returns a pointer to the next failed TestData object.  This
    * is used to iterate through the all the TestData objects that have been
    * set as failed.  When the end of the list is reached, a NULL is returned.
    *
    * @return Pointer to a TestData object or NULL.
    */
   static TestData *getNextFailedTest();

   /**
    * This method deletes all the TestData objects and clears all lists of
    * TestData objects.  Call this method to reset TestData before invoking
    * another test.  If there are any outstanding tests, then no reset will
    * occure.
    *
    * @return False if there were any outstanding tests.
    */
   static bool cleanup();
   
   /**
    * reads the input data file and creates TestData
    * objects associated with each input data row
    * 
    * @param inputFile
    */
   static void getInputData( const DStringA & inputFile );

   /**
    * getter
    * 
    * @return a reference to the error message string
    */
   static const DString & getInputErrorMessage( void )
   {
      return s_inputErrorMessage;
   }

   /**
    * setter
    * 
    * @return a reference to the error message string
    */
   static void setInputErrorMessage( const DString & message )
   {
      s_inputErrorMessage = message;
   }

   /**
    * getter
    * 
    * @return whether there was an error reading or parsing
    *         the input file
    */
   static bool isDataInputError( void )
   {
      return s_fInputError;
   }

   /**
    * Tests for a file open error
    * 
    * @return 
    */
   bool isFileOpenError( void ) const
   {
      return s_fFileOpenError;
   }

   /**
    * getter for the member TestInputData data values
    * vector's iterator
    * 
    * @param data   the TestData object
    * @return the input data values iterator
    */
   string_vector_iterator getInputDataValuesIterator( void * data );

private:
   
   bool parseFileInputLine( I_CHAR * rawBuf );

   bool readTestInputDataElement( i_ifstream & ifStream );

private:
   
   TestData( void *arglist, int createID );

   ~TestData();

   void streamList( string_vector &list, std::ostream &ostr );

private:
   typedef std::vector<TestData *> TestDataList;

   friend class TestSection;
   friend class TestSectionEx;

   void *m_pArglist;
   int m_createID;
   int m_testID;
   bool m_success;
   bool m_completed;

   string_vector m_svInfoList;
   string_vector m_svErrorList;
   string_vector m_svConditionList;
   string_vector m_svDummyList;
   
   int m_linecount;
   TestInputData * m_TestInputData;

   static int s_testCount;
   static bool s_testFailed;
   static bool s_initialized;

   static TestDataList s_testDataList;
   static TestDataList s_failedTestList;
   static TestDataList::iterator s_testDataIter;
   static TestDataList::iterator s_failedTestIter;

   static DString s_inputErrorMessage;
   static bool s_fInputError;
   static bool s_fFileOpenError;
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
// $Log:   Y:/VCS/iFastAWD/inc/testdata.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:33:02   kovacsro
//Initial revision.
//
//   Rev 1.9   16 Nov 2001 07:52:48   dt14177
//fixed Unicode build
//
//   Rev 1.8   13 Nov 2001 15:45:56   dt14177
//Added the testinputdata enhancement
//to get input from files
//
//   Rev 1.7   01 Feb 2001 14:46:14   dt14177
//added testsectionex
//
//   Rev 1.6   28 Nov 2000 13:53:38   dt14177
//cleanup
//
//   Rev 1.5   Aug 28 2000 15:19:18   DMUM
//Added the streamXXX() methods to allow the calling program to determine where the 
//Informational, Condition and Error messages are output.
//
//   Rev 1.4   Mar 10 2000 13:15:36   DMUM
//More enhancements / fixes
//
//   Rev 1.3   Mar 09 2000 14:37:50   DMUM
//Moved TestSection into seperate source files
//
//   Rev 1.2   Mar 08 2000 17:06:54   DMUM
//Added Comments
//
//   Rev 1.0   Mar 08 2000 13:58:14   DMUM
//
//
#endif // TESTDATA_HPP
