#ifndef TESTSECTION_HPP
#define TESTSECTION_HPP

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

/**@pkg DITEST */    

#ifndef COMMONTEMPLATES_H
   #include "commontemplates.h"
#endif

#ifndef DSTRING_HPP
   #include "dstring.hpp"
#endif

#ifndef TESTDATA_HPP
/**@#-*/  // forward declarations
class TestData;
class TestSection;
/**@#+*/
   #include "testdata.hpp"
#endif

#ifndef CONDITIONMANAGER_HPP
   #include "conditionmanager.hpp"
#endif

#undef DITEST_LINKAGE
#ifdef DITEST_DLL
   #define DITEST_LINKAGE CLASS_EXPORT
#else
   #define DITEST_LINKAGE CLASS_IMPORT
#endif

/**
 * This class is to be used in conjunction with TestData.  While in the test,
 * this class is the only interface with a TestData object.  To interact with
 * a TestData object, instantiate a TestSection object at the beginning of the
 * test function.  This should be done on the stack and <i>not</i> dynamically.
 * At the end of the test function, the method testComplete() should be called
 * to indicate that the test is done.  If testComplete() is not called, then
 * this test will be considered to have failed.
 *
 * <b>Example:</b>
 * <pre>
 * void worker( void *pData )
 * {
 *    // Construct a TestSection object passing it the thread data where
 *    // pData is really a pointer to a TestData object.
 *    TestSection section( pData );
 *
 *    // Get the custom data that was passed.
 *    int count = (int)section.getArgList();
 *
 *    // DO TESTING HERE ...
 *
 *    if ( bSomethingFailed )
 *    {
 *       section.addErrorMessage( I_("Something failed") );
 *    }
 *
 *    if ( bSomethingReallyBadFailed )
 *    {
 *       // NOTE: calling failTestImmediately() will cause a ConditionException
 *       // to be thrown, and consequently the test will indicate that it was
 *       // not completed.
 *       section.failTestImmediately( I_("Something failed") );
 *    }
 *
 *    // Call testComplete() to indicate the test is complete
 *    section.testComplete();
 * }
 *</pre>
 */
class DITEST_LINKAGE TestSection
{
public:
   /**
    * Constructor.  Pass in a pointer to a TestData object as a void *.
    *
    * @param pTestData - Pointer to a TestData object.
    */
   TestSection( void *pTestData );

   /**
    * Destructor.  If testComplete() is not called, then the test will be
    * set as having failed.
    */
   ~TestSection();

   /**
    * Provides access to custom data passed to the test (thread).
    *
    * @return
    */
   void *getArgList();

   /**
    * Used to add an informational message.  This allows informational
    * messages to accumilate to be displayed when the test(s) are complete.
    * This avoids the synchronization required for sending messages to the
    * console during the test from multiple threads.
    *
    * @param pMsg - Message to be stored.
    */
   void addInformation( const I_CHAR *pMsg );

   /**
    * Used to add an informational message.  This allows informational
    * messages to accumilate to be displayed when the test(s) are complete.
    * This avoids the synchronization required for sending messages to the
    * console during the test from multiple threads.
    *
    * @param pMsg - Message to be stored.
    */
   void addInformation( const DString &strMsg );

   /**
    * Used to add an error message.  This allows error messages to accumilate
    * to be displayed when the test(s) are complete.  Calling this method
    * will also set the test as failed.
    *
    * @param pMsg - Message to be stored.
    */
   void addErrorMessage( const I_CHAR *pMsg );

   /**
    * Used to add an error message.  This allows error messages to accumilate
    * to be displayed when the test(s) are complete.  Calling this method
    * will also set the test as failed.
    *
    * @param pMsg - Message to be stored.
    */
   void addErrorMessage( const DString &strMsg );

   /**
    * Used to add a message of success or failure.  This method will determine,
    * based on the first parameter, whether the message is an informational or
    * an error message.
    *
    * @param result - 0 indicates failure, any other value indicates an
    *                 informational message
    *
    * @param pMsg - The message
    */
   void addResult( const int result, const I_CHAR *pMsg );

   /**
    * Used to add a message of success or failure.  This method will determine,
    * based on the first parameter, whether the message is an informational or
    * an error message.
    *
    * @param result - 0 indicates failure, any other value indicates an
    *                 informational message
    *
    * @param strMsg - The message
    */
   void addResult( const int result, const DString &strMsg );

   /**
    * Used to add a message of success or failure.  This method will determine,
    * based on the first parameter, whether the message is an informational or
    * an error message.
    *
    * @param pass - True indicates informational and false indicates failure.
    *
    * @param pMsg - The message
    */
   void addPassFail( const bool pass, const I_CHAR *pMsg );

   /**
    * Used to add a message of success or failure.  This method will determine,
    * based on the first parameter, whether the message is an informational or
    * an error message.
    *
    * @param pass - True indicates informational and false indicates failure.
    *
    * @param strMsg - The message
    */
   void addPassFail( const bool pass, const DString &strMsg );

   /**
    * This method will add all conditions in a Frame as an informational
    * message.
    *
    * @param pFrame Pointer to a Frame.
    */
   void addConditionMessage( const Condition *pCond );

   /**
    * This method will add all conditions in a Frame as an informational
    * message.
    *
    * @param pFrame Pointer to a Frame.
    */
   void addConditionMessages( Frame *pFrame );

   /**
    * Call this method to fail the test immediately.  The test will be set as
    * failed and a ConditionException will be thrown.  Make sure that the code
    * that calls the test function has a try - catch block to catch
    * ConditionExceptions.  The classes ThreadCount and ThreadTest do provide
    * for this.
    */
   void failTestImmediately();

   /**
    * Call this method to fail the test immediately with an error message.  The
    * test will be set as failed and a ConditionException will be thrown.  Make
    * sure that the code that calls the test function has a try - catch block
    * to catch ConditionExceptions.  The classes ThreadCount and ThreadTest
    * do provide for this.
    */
   void failTestImmediately( const I_CHAR *pMsg );

   /**
    * Call this method to fail the test immediately with an error message.  The
    * test will be set as failed and a ConditionException will be thrown.  Make
    * sure that the code that calls the test function has a try - catch block
    * to catch ConditionExceptions.  The classes ThreadCount and ThreadTest
    * do provide for this.
    */
   void failTestImmediately( const DString &strMsg );

   /**
    * This method should be called at the end of the test.  This lets the
    * TestData object know that the test has completed.  Failure to call
    * testComplete() will set the test as having failed.
    */
   void testComplete();

private:
   void setError();

   TestData *m_pTestData;
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
// $Log:   Y:/VCS/iFastAWD/inc/testsection.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:33:04   kovacsro
//Initial revision.
//
//   Rev 1.4   28 Nov 2000 14:19:26   dt14177
//cleanup
//
//   Rev 1.3   28 Aug 2000 17:34:50   dt20842
//Condition getters const again
//
//   Rev 1.2   Aug 24 2000 09:44:00   dtwk
//Condition getters are now non const
//
//   Rev 1.1   Mar 10 2000 13:15:38   DMUM
//More enhancements / fixes
//
//   Rev 1.0   Mar 09 2000 14:34:36   DMUM
//
//
//   Rev 1.0.1.0   Mar 08 2000 17:09:00   DMUM
//Added Comments
//
//   Rev 1.0   Mar 08 2000 13:58:14   DMUM
//
//
#endif // TESTSECTION_HPP
