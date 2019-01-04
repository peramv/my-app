#pragma once

#undef BFUTIL_LINKAGE
#ifdef BFUTIL_DLL
   #define BFUTIL_LINKAGE CLASS_EXPORT
#else
   #define BFUTIL_LINKAGE CLASS_IMPORT
#endif

#include <map>
#include <dstring.hpp>

/** 
 * Server Context     
 *
 * Some actions and logic are dealt with differently if we are operating
 * in the context of the GUI or the context of the BPServer.  The application
 * will set a global "ServerContext" indicator to determine if the application
 * is currently a GUI or a Server.  By default the server context is GUI
 *
 */
namespace bfutil
{
   /**
    * An application is either running as a server application or as a desktop application.
    * This function will indicate if the application is currently running as a server.
    * 
    * @return true if running as a Server or false if the application is running as a GUI.
    * 
    */
   BFUTIL_LINKAGE bool isServerContext();

   /**
    * This method sets the flag to indicate if the application is running in server context.
    * 
    * @param bServerContext
    *               set to true if running in server context.
    */
   BFUTIL_LINKAGE void setServerContext( bool bServerContext );

   BFUTIL_LINKAGE bool isRetry();
   BFUTIL_LINKAGE void setRetry( bool bRetry );
}
               
               
/**
 * Base class for a class which is to be attached to an execution context.
 * 
 * @author Chris Purdye
 * @see BFExecutionContext
 */
class BFUTIL_LINKAGE BFExecutionContextImpl
{
public:
   friend class BFExecutionContext;
protected:
   virtual ~BFExecutionContextImpl();
   BFExecutionContextImpl();      // can't be instantiated directly ... must be derived

   /**
    * This member function is called whenever a thread is attached to this
    * execution context.  Override this to provide special functionality.
    */
   virtual void notifyAttach()    // we have attached to a new thread!
   { return;}
};

#include <DString.hpp>
#include <bfutil\bfcritsec.hpp>

#pragma warning( disable: 4251 4786 )

/**
 * An execution context is typically defined as a logical unit of work.
 * Each thread in the application has an associated execution context.  This
 * context may be shared by other threads in the application.  An
 * execution context object has the ability to associate other objects
 * to itself.  This allows a thread to share specific objects with 
 * other threads which constitute a unit of work.
 * 
 * @author Chris Purdye
 */
class BFUTIL_LINKAGE BFExecutionContext
{
public:

   BFExecutionContext();
   ~BFExecutionContext();

   /**
    * Create a new BFExecutionContext object for the current thread.  
    * 
    * @return Pointer to the created BFExecutionContext object.
    */
   static BFExecutionContext* create();

   /**
    * Retrieve the BFExecutionContext object for the current thread.
    * 
    * @return The BFExecutionContext object of the current thread.
    */
   static BFExecutionContext* get();

   /**
    * Attach the specified BFExecutionContext object to the current thread.
    * 
    * @param pBFExecutionContext
    *               The execution context to join.
    */
   static void attach( BFExecutionContext* pBFExecutionContext );

   /**
    * Attach the BFExecutionContext object of the specified thread to the current thread.
    * 
    * @param idMasterThread
    *               The system thread identifier of the thread to join to.
    * 
    * @return The BFExecutionContext object to which this thread is now attached.
    */
   static BFExecutionContext* attach( unsigned long idMasterThread );

   /**
    * Remove the current thread's association to its BFExecutionContext object.
    * If this is the last thread to which that BFExecutionContext object
    * is associated then that BFExecutionContext object is destroyed.
    */
   static void detach();

   /**
    * Add an object to the current thread's execution context.
    * 
    * @param dstrKey The unique string key.
    * @param BFExecutionContextImpl
    *                A pointer to a BFExecutionContextImpl object which represents the
    *                information to localize to the execution context.
    *                
    *                This object should be created on the free store (i.e. with new).
    *                Unless the BFExecutionContextImpl object is explicitly removed from
    *                the execution context with the removeObject() function then
    *                BFExecutionContext object will delete the BFExecutionContextImpl object
    *                when it is destroyed.
    * 
    * @return true if the object was added to the current execution context. 
    *         false if the object could not be added.  Typically the
    *         BFExecutionContextImpl object already exists in this execution context
    *         object when false is returned.
    * @see #getObject
    * @see #removeObject
    * @see BFExecutionContextImpl
    */
   bool addObject( const DString &dstrKey, BFExecutionContextImpl* );

   /**
    * Get a pointer to a specific BFExecutionContextImpl object which
    * was previously added to this execution context.
    * 
    * @param dstrKey The case-sensitive key of the BFExecutionContextImpl object.
    * 
    * @return A pointer to the BFExecutionContextImpl object.
    * @see #addObject
    * @see #removeObject
    */
   BFExecutionContextImpl* getObject( const DString &dstrKey ) const;

   /**
    * Remove the BFExecutionContextImpl object associated with a specific key.
    * 
    * If an application calls removeObject() then it must delete the
    * associated object. A pointer to that object can be obtained by
    * calling {@link #getObject( const DString& dstrKey ) getObject}
    * 
    * @param dstrKey The case-sensitive key of the BFExecutionContextImpl object to remove.
    * 
    * @return true if the BFExecutionContextImpl object was removed from this execution context.
    * @see #getObject
    * @see #addObject
    */
   bool removeObject( const DString &dstrKey );

   /**
    * Reset this BFExecutionContext object to its base state.  This will
    * affect other threads which may be attached to this context, but
    * those threads will not be notified that the reset has occurred.
    */
   void reset();

private:
   typedef std::map< DString, BFExecutionContextImpl* > BFEXECUTIONCONTEXTIMPL_MAP;
   typedef std::map< DString, BFExecutionContextImpl* >::iterator BFEXECUTIONCONTEXTIMPL_ITER;
   typedef std::map< DString, BFExecutionContextImpl* >::const_iterator BFEXECUTIONCONTEXTIMPL_CITER;

   BFEXECUTIONCONTEXTIMPL_MAP _mapImpl;

   mutable BFCritSec   _cs;
};

