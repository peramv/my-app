// TestSectionEx.hpp : Defines the entry point for the console application.
//

#ifndef TESTSECTIONEX_HPP
#define TESTSECTIONEX_HPP

#  pragma message( "including "__FILE__ )

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

/**@pkg DITEST */        


#ifndef TESTSECTION_HPP
#include "TestSectionEx.hpp"
#endif

#ifndef COMMONTEMPLATES_H
   #include "commontemplates.h"
#endif

#ifndef DSTRING_HPP
   #include "dstring.hpp"
#endif

#ifndef TESTDATA_HPP
/**@#-*/  // forward declarations
class TestData;
class TestSectionEx;
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


#define ADDINFORMATION( Message ) \
                           addInformation(__FILE__, \
                                          __LINE__, \
                                           Message, \
                                           I_(""));
#define ADDINFORMATIONLBL( CaseLabel, Message ) \
                           addInformation(NULL, \
                                          0, \
                                          Message, \
                                          CaseLabel);

#define ADDERRORMSG( Message ) \
                           addErrorMessage(__FILE__, \
                                          __LINE__, \
                                           Message, \
                                           I_(""));
#define ADDERRORMSGLBL( CaseLabel, Message ) \
                           addErrorMessage(NULL, \
                                          0, \
                                          Message, \
                                          CaseLabel);

#define ADDCONDITIONMSG( Condition ) \
                           addConditionMessage(Condition, \
                                                I_(""));
#define ADDCONDITIONMSGLBL( CaseLabel, Condition ) \
                           addConditionMessage(Condition, \
                                             CaseLabel);

#define ADDALLCONDITIONS( Frame ) \
                           addConditionMessages(Frame, \
                                                I_(""));
#define ADDALLCONDITIONSLBL( CaseLabel, Frame ) \
                           addConditionMessages(Frame, \
                                             CaseLabel);

#define FAILIMMEDIATE( Message ) \
                           failTestImmediately(__FILE__, \
                                          __LINE__, \
                                           Message, \
                                           I_(""));
#define FAILIMMEDIATELBL( CaseLabel, Message ) \
                           failTestImmediately(NULL, \
                                          0, \
                                          Message, \
                                          CaseLabel);

#define ADDRESULT( Res, Message ) \
                           addResult(Res, \
                                    __FILE__, \
                                    __LINE__, \
                                    Message, \
                                    I_(""));
#define ADDRESULTLBL( Res, CaseLabel, Message ) \
                           addResult(Res, \
                                    NULL, \
                                    0, \
                                    Message, \
                                    CaseLabel);

#define ADDPASSFAIL( Pass, Message ) \
                           addResult(Pass, \
                                    __FILE__, \
                                    __LINE__, \
                                    Message, \
                                    I_(""));
#define ADDPASSFAILLBL( Pass, CaseLabel, Message ) \
                           addResult(Pass, \
                                    NULL, \
                                    0, \
                                    Message, \
                                    CaseLabel);

//Severity,TimeStamp,File,LineNumber,TestCaseLabel,PassFail,Message


/**
 * This class is to be used in conjunction with TestData.  While in the test,
 * this class is the only interface with a TestData object.  To interact with
 * a TestData object, instantiate a TestSectionEx object at the beginning of the
 * test function.  This should be done on the stack and <i>not</i> dynamically.
 * At the end of the test function, the method testComplete() should be called
 * to indicate that the test is done.  If testComplete() is not called, then
 * this test will be considered to have failed.
 *
 * <b>Example:</b>
 * <pre>
 * void worker( void *pData )
 * {
 *    // Construct a TestSectionEx object passing it the thread data where
 *    // pData is really a pointer to a TestData object.
 *    TestSectionEx section( pData );
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
class DITEST_LINKAGE TestSectionEx
{
public:
   /**
    * Constructor.  Pass in a pointer to a TestData object as a void *.
    *
    * @param pTestData - Pointer to a TestData object.
    */
   TestSectionEx( void *pTestData );

   /**
    * Destructor.  If testComplete() is not called, then the test will be
    * set as having failed.
    */
   ~TestSectionEx();

   /**
    * Provides access to custom data passed to the test (thread).
    *
    * @return
    */
   void *getArgList();

   /**
    * formats and writes a CSV file style column header.
    *
    * @return
    */
   static void outputCSVHeader( std::ostream &ostr );

   /**
    * Used to add an informational message.  This allows informational
    * messages to accumilate to be displayed when the test(s) are complete.
    * This avoids the synchronization required for sending messages to the
    * console during the test from multiple threads.
    *
    * @param pMsg - Message to be stored.
    */
   virtual void addInformation( const char * fileName, unsigned lineNumber,
                                 const I_CHAR *pMsg, const I_CHAR *pCaseLabel );

   /**
    * Used to add an informational message.  This allows informational
    * messages to accumilate to be displayed when the test(s) are complete.
    * This avoids the synchronization required for sending messages to the
    * console during the test from multiple threads.
    *
    * @param pMsg - Message to be stored.
    */
   virtual void addInformation( const char * fileName, unsigned lineNumber,
                                 const DString &strMsg, const I_CHAR *pCaseLabel );

   /**
    * Used to add an error message.  This allows error messages to accumilate
    * to be displayed when the test(s) are complete.  Calling this method
    * will also set the test as failed.
    *
    * @param pMsg - Message to be stored.
    */
   virtual void addErrorMessage( const char * fileName, unsigned lineNumber,
                                 const I_CHAR *pMsg, const I_CHAR *pCaseLabel );

   /**
    * Used to add an error message.  This allows error messages to accumilate
    * to be displayed when the test(s) are complete.  Calling this method
    * will also set the test as failed.
    *
    * @param pMsg - Message to be stored.
    */
   virtual void addErrorMessage( const char * fileName, unsigned lineNumber,
                                 const DString &strMsg, const I_CHAR *pCaseLabel );

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
   virtual void addResult( const int result, const char * fileName, unsigned lineNumber,
                                 const I_CHAR *pMsg, const I_CHAR *pCaseLabel );

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
   virtual void addResult( const int result, const char * fileName, unsigned lineNumber,
                                 const DString &strMsg, const I_CHAR *pCaseLabel );

   /**
    * Used to add a message of success or failure.  This method will determine,
    * based on the first parameter, whether the message is an informational or
    * an error message.
    *
    * @param pass - True indicates informational and false indicates failure.
    *
    * @param pMsg - The message
    */
   virtual void addPassFail( const bool pass, const char * fileName, unsigned lineNumber,
                                 const I_CHAR *pMsg, const I_CHAR *pCaseLabel );

   /**
    * Used to add a message of success or failure.  This method will determine,
    * based on the first parameter, whether the message is an informational or
    * an error message.
    *
    * @param pass - True indicates informational and false indicates failure.
    *
    * @param strMsg - The message
    */
   virtual void addPassFail( const bool pass, const char * fileName, unsigned lineNumber,
                                 const DString &strMsg, const I_CHAR *pCaseLabel );

   /**
    * This method will add all conditions in a Frame as an informational
    * message.
    *
    * @param pFrame Pointer to a Frame.
    */
   virtual void addConditionMessage( const Condition *pCond, const I_CHAR *pCaseLabel );

   /**
    * This method will add all conditions in a Frame as an informational
    * message.
    *
    * @param pFrame Pointer to a Frame.
    */
   virtual void addConditionMessages( Frame *pFrame, const I_CHAR *pCaseLabel  );

   /**
    * Call this method to fail the test immediately.  The test will be set as
    * failed and a ConditionException will be thrown.  Make sure that the code
    * that calls the test function has a try - catch block to catch
    * ConditionExceptions.  The classes ThreadCount and ThreadTest do provide
    * for this.
    */
   void failTestImmediately(const char * fileName, unsigned lineNumber, const I_CHAR *pCaseLabel);

   /**
    * Call this method to fail the test immediately with an error message.  The
    * test will be set as failed and a ConditionException will be thrown.  Make
    * sure that the code that calls the test function has a try - catch block
    * to catch ConditionExceptions.  The classes ThreadCount and ThreadTest
    * do provide for this.
    */
   void failTestImmediately( const char * fileName, unsigned lineNumber,
                                const I_CHAR *pMsg, const I_CHAR *pCaseLabel );

   /**
    * Call this method to fail the test immediately with an error message.  The
    * test will be set as failed and a ConditionException will be thrown.  Make
    * sure that the code that calls the test function has a try - catch block
    * to catch ConditionExceptions.  The classes ThreadCount and ThreadTest
    * do provide for this.
    */
   void failTestImmediately( const char * fileName, unsigned lineNumber,
                                 const DString &strMsg, const I_CHAR *pCaseLabel );

   /**
    * This method should be called at the end of the test.  This lets the
    * TestData object know that the test has completed.  Failure to call
    * testComplete() will set the test as having failed.
    */
   void testComplete();

   void setCaseLabel( I_CHAR *pCaseLabelIn ) { pCaseLabel = pCaseLabelIn; }

private:
   void setError();

   TestData *m_pTestData;
   I_CHAR *pCaseLabel;
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
// $Log:   Y:/VCS/iFastAWD/inc/TestSectionEx.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:33:06   kovacsro
//Initial revision.
//
//   Rev 1.1   Jun 28 2001 17:17:50   dt20842
//Add setCaseLabel method to allow for it be set once per method
//
//   Rev 1.0   01 Feb 2001 14:54:00   dt14177
// 
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
#endif // TESTSECTIONEX_HPP

