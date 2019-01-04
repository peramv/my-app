#define DICORE_DLL


#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif

#ifndef TRACERCLIENT_HPP
   #include "tracerclient.hpp"
#endif


TracerClient::TracerClient(const DString& classNameIn):
_debugManager(0),
_className(classNameIn),
_threadId(0),
_processId(0),
_classLevelTracing(false),
_supportOldTracing( false)
{
   init();
}


TracerClient::TracerClient():
_debugManager(0),
_className(I_("")),
_threadId(0),
_processId(0),
_classLevelTracing(false),
_supportOldTracing( false)
{
   init();
}

void TracerClient::init()
{

   _threadId = DSTGetCurrentThreadId();
   _processId = DSTGetCurrentProcessId();

   _debugManager = DebugMgr::getInstance();


}

TracerClient::~TracerClient()
{

   // Old style uses an instance of the tracer class for every
   //   trace message, so prevent double messages by preventing
   //   the destructor message
   // The class can be used stand-alone for such things as changing the state of the 
   //   global trace flag
   //  So to prevent sending a blank destructor message, check for a valid className
   if( isTracing() && (!_supportOldTracing) && _className.length() )
   {

      logDestroy();

   }

}

void TracerClient::logCreate(const DString& constructorSignatureIn)
{

   int parenPos = constructorSignatureIn.find('(');

   if( 0 == parenPos )
      parenPos = constructorSignatureIn.length();
   _className = constructorSignatureIn.substr(0, parenPos);

   _debugManager -> log(DebugMgr::CONSTRUCTOR, _className, _processId, _threadId, constructorSignatureIn);


}

void TracerClient::logDestroy()
{

   _debugManager -> log(DebugMgr::DESTRUCTOR, _className, _processId, _threadId);

}

void TracerClient::logMethod(const DString& methodNameIn)
{

   _debugManager -> log(DebugMgr::METHOD, _className, _processId, _threadId, methodNameIn);

}

void TracerClient::logMessage(const DString& messageIn)
{

   _debugManager -> log(DebugMgr::MESSAGE, _className, _processId, _threadId, messageIn);

}

void TracerClient::logError(const DString& errorMessageIn)
{

   _debugManager -> connectTrace();
   _debugManager -> log(DebugMgr::MESSAGE, _className, _processId, _threadId, errorMessageIn);

}

void TracerClient::setClassTracing(bool classTracingIn)
{

   _classLevelTracing = classTracingIn;

   if( true == _classLevelTracing )
   {

      _debugManager -> connectTrace();

   }

}


