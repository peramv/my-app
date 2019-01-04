#include "stdafx.h"
#include <srcprag.h>
#include "smqtest.h"
#include <sstream>
#include <atlrx.h>
#include <bfutil\bfhrtimer.hpp>


using namespace progress::message::jclient;

static DString asDString( StringRef s ) {
   WStringRef wStr = s->toWide();
   std::wstring w;
   w.append( (const I_CHAR*)/*(const unsigned short*)*/wStr, wStr->length() );
   return( DString(w) );
}

static DStringA asDStringA( StringRef s ) {
   AStringRef aStr = s->toAscii();
   std::string a;
   a.append( (const char*)aStr, aStr->length() );
   return( DStringA(a) );
}


static DString GetJMSException(  JMSExceptionRef e ) {
   StringRef strCode = e->getErrorCode();
   DString dstrCode = DString( asDStringA(strCode) );
   StringRef s = e->getMessage();
   DString msg = DString( asDStringA( s ) );
   std::wstringstream wss;
   wss << msg.c_str();
   if( dstrCode != I_("") ) {
      wss << I_(" (") << dstrCode.c_str() << I_(")");
   }
   return( wss.str() );
}


SMQTest::SMQTest(void)
    : MessageServiceTest(),
	  connFactory_(null),
      connection_(null),
      session_(null),
      singleSender_(null),
      multiSender_(null),
      authSender_(null),
      awdSender_(null),
      receiver_(null),
      tempQueue_(null)
{
}

SMQTest::~SMQTest(void)
{
   try {
      if ( session_ != null ) {
         try {
            session_->close();
         }
         catch (...) {
         }
         session_=null; 
      }
      if ( connection_ != null ) {
         try {
            connection_->close();
         }
         catch (...) {
         }
         connection_=null; 
      }
   }
   catch ( progress::message::jclient::JMSExceptionRef e ) {
   }
}

bool SMQTest::doSingleQTest( DString& message )
{
   bool bRc = true;
   try {
      singleSender_ = session_->createSender(createQueue(createString(getSingleQ().c_str())));
   }
   catch ( progress::message::jclient::JMSExceptionRef e ) {
      message = GetJMSException( e );
      bRc = false;
   }
   return( bRc );
}

bool SMQTest::doMultiQTest( DString& message )
{
   bool bRc = true;
   try {
      multiSender_ = session_->createSender(createQueue(createString(getMultiQ().c_str())));
   }
   catch ( progress::message::jclient::JMSExceptionRef e ) {
      message = GetJMSException( e );
      bRc = false;
   }
   return( bRc );
}

bool SMQTest::doAuthQTest( DString& message ) {
   bool bRc = true;
   try {
      authSender_ = session_->createSender(createQueue(createString(getAuthQ().c_str())));
   }
   catch ( progress::message::jclient::JMSExceptionRef e ) {
      message = GetJMSException( e );
      bRc = false;
   }
   return( bRc );
}

bool SMQTest::doAwdQTest( DString& message ) {
   bool bRc = true;
   try {
      awdSender_ = session_->createSender(createQueue(createString(getAwdQ().c_str())));
   }
   catch ( progress::message::jclient::JMSExceptionRef e ) {
      message = GetJMSException( e );
      bRc = false;
   }
   return( bRc );
}

bool SMQTest::doHeartbeatTest( DString& message )
{
   return( true );
}

void SMQTest::parseBrokerURL(
      DString& hostPrimary,
      int& portPrimary,
      DString& hostBackup,
      int& portBackup
      )
{
   CAtlRegExp<> reSingleUrl;
   CAtlRegExp<> reDoubleUrl;

   // three match groups: scheme, host, port
   REParseError status1 = reSingleUrl.Parse(_T("{[a-z]+}://{[A-Za-z0-9_\\.\\-]+}:{[0-9]+}") );
   REParseError status2 = reDoubleUrl.Parse(_T("{[a-z]+}://{[A-Za-z0-9_\\.\\-]+}:{[0-9]+},{[a-z]+}://{[A-Za-z0-9_\\.\\-]+}:{[0-9]+}") );
   if (REPARSE_ERROR_OK == status1 &&
       REPARSE_ERROR_OK == status2 ) {
      CAtlREMatchContext<> mcUrl;
      BOOL b = reDoubleUrl.Match(getBrokerURL().c_str(), &mcUrl);
      if( !b ) {
         b = reSingleUrl.Match(getBrokerURL().c_str(), &mcUrl);
      }
      if( b ) {
         std::wstring p;
         for (UINT nGroupIndex = 0; nGroupIndex < mcUrl.m_uNumGroups; ++nGroupIndex) {
            const CAtlREMatchContext<>::RECHAR* szStart = 0;
            const CAtlREMatchContext<>::RECHAR* szEnd = 0;
            mcUrl.GetMatch(nGroupIndex, &szStart, &szEnd);
            ptrdiff_t nLength = szEnd - szStart;
            p.assign( szStart, nLength);
            switch( nGroupIndex ) {
               case 0: break;
               case 1: hostPrimary = p.c_str(); break;
               case 2: portPrimary = _ttoi( p.c_str() ); break;
               case 3: break;
               case 4: hostBackup = p.c_str(); break;
               case 5: portBackup = _ttoi( p.c_str() ); break;
            }
         }
      }
   }
}

bool SMQTest::createConnectionFactory( DString& message )
{
   bool bRc = true;
   try {
      connFactory_ = createQueueConnectionFactory( null, 
                                                   createString(getSMQUser().c_str()), 
                                                   createString(getSMQPassword().c_str()) );
      connFactory_->setFaultTolerant(jtrue);
      connFactory_->setConnectionURLs( createString(getBrokerURL().c_str()) );
   }
   catch ( progress::message::jclient::JMSExceptionRef e ) {
      message = GetJMSException( e );
      bRc = false;
   }
   return( bRc );
}

bool SMQTest::createConnection( DString& message ) {
   bool bRc = true;
   try {
	   connFactory_->setInitialConnectTimeout(5);

      connection_ = connFactory_->createQueueConnection();
      connection_->start();
   }
   catch ( progress::message::jclient::JMSExceptionRef e ) {
      message = GetJMSException( e );
      bRc = false;
   }
   return( bRc );
}

bool SMQTest::createSession( DString& message ) {
   bool bRc = true;
   try {
      session_ = connection_->createQueueSession(jfalse, Session_AUTO_ACKNOWLEDGE);
   }
   catch ( progress::message::jclient::JMSExceptionRef e ) {
      message = GetJMSException( e );
      bRc = false;
   }
   return( bRc );
}

