#pragma once
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

#include <commonport.h>
#include <bfproc\command.hpp>
#include <condition.hpp>
#include <bfcbo\bfdatagroupid.hpp>
#include <bfproc\bfcontainerid.hpp>

// Import/Export resolution
#undef BPBASE_LINKAGE
#ifdef BPBASE_DLL
   #define BPBASE_LINKAGE CLASS_EXPORT
#else
   #define BPBASE_LINKAGE CLASS_IMPORT
#endif

// Forward declare
class BFObserver;
class BFProperties;

class BFData;
class BFDataFieldProperties;

class GenericInterfaceContainer;
class InterProcessData;
class BFCPSession;
class BFSession;
class BFWorkSession;
class BFFieldId;

namespace GENERICINTERFACELITERALS
{
   // Trace literals
   extern BPBASE_LINKAGE const I_CHAR *DELETEITEMFROMLIST;
   extern BPBASE_LINKAGE const I_CHAR *DEREGISTEROBSERVER;
   extern BPBASE_LINKAGE const I_CHAR *DOGETDATA;
   extern BPBASE_LINKAGE const I_CHAR *DOGETERRORS;
   extern BPBASE_LINKAGE const I_CHAR *DOGETFIELD;
   extern BPBASE_LINKAGE const I_CHAR *DOGETFIELDATTRIBUTES;
   extern BPBASE_LINKAGE const I_CHAR *DOCANCEL;
   extern BPBASE_LINKAGE const I_CHAR *DOINIT;
   extern BPBASE_LINKAGE const I_CHAR *DOMODELESSCHILDCOMPLETE;
   extern BPBASE_LINKAGE const I_CHAR *DOMODELESSSETFOCUS;
   extern BPBASE_LINKAGE const I_CHAR *DOOK;
   extern BPBASE_LINKAGE const I_CHAR *DOPROCESS;
   extern BPBASE_LINKAGE const I_CHAR *DOREFRESH;
   extern BPBASE_LINKAGE const I_CHAR *DOSEND;
   extern BPBASE_LINKAGE const I_CHAR *DOSETFIELD;
   extern BPBASE_LINKAGE const I_CHAR *GETCURRENTLISTITEMKEY;
   extern BPBASE_LINKAGE const I_CHAR *GETALLERRORS;
   extern BPBASE_LINKAGE const I_CHAR *GETERRORS;
   extern BPBASE_LINKAGE const I_CHAR *GETERRORSTATE;
   extern BPBASE_LINKAGE const I_CHAR *GETFIELD;
   extern BPBASE_LINKAGE const I_CHAR *GETFIELD2;
   extern BPBASE_LINKAGE const I_CHAR *GETFIELDATTRIBUTES;
   extern BPBASE_LINKAGE const I_CHAR *GETFIRSTLISTITEMKEY;
   extern BPBASE_LINKAGE const I_CHAR *GETKEYFORNEWLISTITEM;
   extern BPBASE_LINKAGE const I_CHAR *GETNEXTLISTITEMKEY;
   extern BPBASE_LINKAGE const I_CHAR *GETNUMBEROFITEMSINLIST;
   extern BPBASE_LINKAGE const I_CHAR *INIT2;
   extern BPBASE_LINKAGE const I_CHAR *OK2;
   extern BPBASE_LINKAGE const I_CHAR *PROCESS;
   extern BPBASE_LINKAGE const I_CHAR *REGISTEROBSERVER;
   extern BPBASE_LINKAGE const I_CHAR *RESET;
   extern BPBASE_LINKAGE const I_CHAR *SETCURRENTLISTITEM;
   extern BPBASE_LINKAGE const I_CHAR *SETDATA;
   extern BPBASE_LINKAGE const I_CHAR *SETFIELD;
   extern BPBASE_LINKAGE const I_CHAR *SETFIELD2;
   extern BPBASE_LINKAGE const I_CHAR *DOVALIDATEALL;
}

// make available to processes
/**@#-*/
using namespace GENERICINTERFACELITERALS;
/**@#+*/

/**
  * Base class which establishes a generic interface used by several different
  * classes.
  *
  * The GenericInterface class represents a "small" interface that is 
  * consistently supported in process/dialog type objects.  This "small"
  * interface is represented by the public methods in this class.  This interface
  * is used to help decouple the gui code from the business logic.  All of these
  * types of objects communicate only via the GenericInterface.  This removes any
  * compile time coupling.  Two step construction is used by calling the default
  * constructor and then init.  Because the creation process is controlled by the
  * factory (manager) classes, there isn't any code to check that the object was
  * constructed properly. Any parameters passed to the object (via 
  * InterProcessData) must be saved during the subclasses handling of doInit
  * since the parameters will be cleared after initialization is performed.
  *
  * Derived classes must override the appropriate protected virtual doXXX methods
  * which are invoked from the base generic interface methods (methods with same 
  * name without the "do" in front of it) to allow subclasses to do their work.  
  * This allows the base framework to provide certain functionality and to
  * dictate some protocol.  The protocols includes making sure that the process 
  * method is only called once.  This also means that the derived classes should
  * not override any of the base generic interface methods (the class probably 
  * would not perform as expected anyway since only GenericInterface pointers are
  * stored throughout the system).
  *
  * For all methods working with lists, note that if the list is nested within 
  * other lists that the current item in each of the parent lists is used as the
  * context.  The current item is set either specifically (setCurrentListItem)
  * or indirectly by other methods which access a list like when the current item
  * is deleted.  Also, note that when changing the current item in a list that
  * has a nested list, the nested list will be cleared until needed.  Override
  * getPtrForContainer to provide logic for getting list CBO pointers.
  *
  * @author Jerry Leenerts
  * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 12/01/98</dd></dl>
  * @version 0.1
  */

class BPBASE_LINKAGE GenericInterface
{
protected:
   /**
    * Ctor
    * 
    * @param rpGIC      A reference pointer to the GenericInterfaceContainer to
    *                   be used.
    * @param rpGIParent A reference pointer to the parent object.
    * @param cmd        A reference to the command to be associated with this
    *                   object.
    * 
    */
   GenericInterface( GenericInterfaceContainer *rpGIC,
                     GenericInterface *rpGIParent,
                     const Command &cmd );

   /**
    * Ctor
    * 
    */
   GenericInterface();

public:
   virtual ~GenericInterface();

   /**
    * Used by child process to indicate it is cancelled.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * 
    * @return true if successful, check conditions if false
    */
   bool cancel( GenericInterface *rpGICaller );

   /**
    * Pass-through method to clear global values for either a user session
    * or work session.  (Note that clearing user session globals will also
    * clear work session globals.)
    * 
    * @param gType  Type of globals to clear (either user or work session).
    */
   void clearGlobals( E_GLOBALTYPE gType );

   /**
    * Pass-through method to clear parameter values for a work session.
    * This method should only need to be used after invoking modal commands.
    * Parameters are not automatically cleared during ok/cancel for modal
    * commands.
    */
   void clearParameters();

   /**
    * This method is used to deregister an observer.  An exception will be
    * thrown if the field or list cannot be found.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param idContainer
    *                   ID of the associated container to find.
    * @param idField    ID of the associated field to find.
    * @param idDataGroup    idDataGroup for commit/rollbackprocessing
    * @param rpObserver reference of observer to deregister
    */
   virtual void deregisterObserver( const GenericInterface *rpGICaller,
                                    const BFContainerId& idContainer,
                                    const BFFieldId &idField,
                                    const BFDataGroupId& idDataGroup,
                                    BFObserver &rpObserver );

   /**
    * Subclasses will implement this method to reflect state of a search.
    * Used by child to check if more records exist in a search.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param idSearch   ID of search to check for more records.
    * 
    * @return true if more exist
    */
   virtual bool doMoreRecordsExist( GenericInterface *rpGICaller,
                                    const BFContainerId& idSearch );

   /**
    * Get the associated command.
    * 
    * @return a const reference to the associated command.
    */
   const Command &getCommand() const
   {
      return(cmd_);
   }

   const DString& getCommandName() const;
   /**
    * Get data from another GenericInterface via generic data passing
    * mechanism.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param rpData     A reference pointer to data object for the data.
    * 
    * @return true if successful, check conditions if false
    */
   bool getData( GenericInterface *rpGICaller, 
                 BFData *rpData ) const;

   virtual SEVERITY getAllErrors( GenericInterface *rpGICaller,
                                  CONDITIONVECTOR &conditions );
   /**
    * Used to get the current errors for a field.
    * An exception will be thrown if field cannot be obtained.
    * Override to provide functionality.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param idContainer
    *                      ID for the container object (often a CBO).
    * @param idField       ID for field.  ifds::NullFieldId will get all 
    *                      conditions for the specified container.
    * @param vConditions   CONDITIONVECTOR to return conditions in.
    * 
    * @return highest SEVERITY for field
    */
   virtual SEVERITY getErrors( GenericInterface *rpGICaller,
                               const BFContainerId& idContainer,
                               const BFFieldId &idField,
                               CONDITIONVECTOR &vConditions );

   /**
    * Used to get the errors for a field in a specified container item
    * An exception will be thrown if field cannot be obtained.
    * Override to provide functionality.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param idContainer
    *                      ID for the container object (often a CBO).
    * @param pKey          pointer to key for container.  Current item
    *                      will *not* be changed to this key, but the 
    *                      conditions for that item will be returned.
    * @param idField       ID for field.  ifds::NullFieldId will get all 
    *                      conditions for the specified container.
    * @param vConditions   CONDITIONVECTOR to return conditions in.
    * 
    * @return highest SEVERITY for field
    */
   virtual SEVERITY getItemErrors( GenericInterface *rpGICaller,
                                   const BFContainerId& idContainer,
                                   const DString* pKey,
                                   const BFFieldId &idField,
                                   CONDITIONVECTOR &vConditions );

   /**
    * Used to get the current error state (from last validation) for a
    * container.
    * Exceptions will be thrown on errors.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param idContainer
    *                   ID for the container object (often a CBO).
    * @param bCurrentItem
    *                   true = get error state for current item in
    *                   repeatable list, false = get error state for container.
    * @param sevObject  returned max error state of object
    * @param sevChildren
    *                   returned max error state of children
    */
   virtual void getErrorState( GenericInterface *rpGICaller,
                               const BFContainerId& idContainer,
                               bool bCurrentItem,
                               SEVERITY &sevObject,
                               SEVERITY &sevChildren );

   /**
    * Used to get the current error state (from last validation) for a
    * container.
    * Exceptions will be thrown on errors.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param pKey       pointer to key for container.  Current item
    *                   will *not* be changed to this key, but the 
    *                   error state for that item will be returned.
    * @param idContainer
    *                   ID for the container object (often a CBO).
    * @param sevObject  returned max error state of object
    * @param sevChildren
    *                   returned max error state of children
    */
   virtual void getItemErrorState( GenericInterface *rpGICaller,
                                   const BFContainerId& idContainer,
                                   const DString* pKey,
                                   SEVERITY &sevObject,
                                   SEVERITY &sevChildren );
   /**
    * Used to get value of a field from another GenericInterface.  An
    * exception will be thrown if field cannot be obtained.
    * This is a pure virtual method that must be overridden.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param idField    ID for field.
    * @param strValueOut
    *                   A string reference where value of the data field
    *                   will be returned.
    * @param bFormatted Flag indicating whether to get the data formatted.
    */
   virtual void getField( const GenericInterface *rpGICaller,
                          const BFFieldId &idField,
                          DString &strValueOut,
                          bool bFormatted = true );
   /**
    * Used to get the value of a field from the specified container object from
    * another GenericInterface.  If the CBO is repeatable, the caller is
    * responsible for managing the repeats.  (See list methods outlined below.)
    * An exception will be thrown if field cannot be obtained.
    * This is a pure virtual method that must be overridden.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param idContainer
    *                   ID for the container object (often a CBO).
    * @param idField    ID for field.
    * @param strValueOut
    *                   A string reference where value of the data field
    *                   will be returned.
    * @param bFormatted Flag indicating whether to get the data formatted.
    */
   virtual void getField( const GenericInterface *rpGICaller,
                          const BFContainerId& idContainer,
                          const BFFieldId &idField,
                          DString &strValueOut,
                          bool bFormatted = true );
   /**
    * Used to get field attributes for the specified field.  An
    * exception will be thrown if the field attributes cannot be obtained.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param idField    ID for field.
    * 
    * @return 
    * @deprecated Prefer getFieldAttributes( const GenericInterface*, long, const BFFieldId& );
    */
   virtual const BFDataFieldProperties* getFieldAttributes( const GenericInterface *rpGICaller,
                                                            const BFFieldId &idField ) const;
   /**
    * This method is used (typically by an associated GUI component) to get the
    * attributes for a field.  An exception will be thrown if the
    * field or list cannot be found.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param idContainer
    *                   ID of container to find.
    * @param idField    ID of field to find.
    * 
    * @return constant reference pointer to BFProperties or NULL if none
    */
   virtual const BFProperties *getFieldAttributes( const GenericInterface *rpGICaller,
                                                   const BFContainerId& idContainer,
                                                   const BFFieldId &idField );

   /**
    * This method returns the associated GenericInterfaceContainer (by userID).
    * 
    * @return pointer to GenericInterfaceContainer
    */
   GenericInterfaceContainer *getGIContainer()
   {
      return(_rpGIContainer);
   }

   /**
    * Pass-through method to get global value for a given field from the
    * InterProcessData.  These global fields must exist in DSTCGLOB.vw.
    * 
    * @param gType   Type of global to set.
    * @param idField Data dictionary ID for the global field.
    * @param strValueOut
    *                A string reference that will be filled with the
    *                global value.
    */
   void getGlobal( E_GLOBALTYPE gType,
                   const BFFieldId &idField,
                   DString &strValueOut ) const;

   /**
     * This method returns the group ID being used.
     * @return group id
     */
   const BFDataGroupId& getDataGroupId() const
   {
      return( idDataGroup_ );
   }

   /**
    * Pass-through method to get parameter value for a given tag from the
    * InterProcessData.
    * 
    * @param strTag A const string reference with the tag name for the
    *               parameter.
    * @param strValueOut
    *               A string reference that will be filled with the
    *               parameter value.
    */
   void getParameter( const DString &strTag,
                      DString &strValueOut ) const;

   /**
    * Get the parent object of this object.
    * 
    * @return reference pointer to the parent object
    */
   GenericInterface *getParent() const
   {
      return(_rpGIParent);
   }

   /**
    * Get the session for this object.
    * 
    * @return reference pointer to the session
    */
   BFCPSession *getSession() const
   {
      return(_pSession);
   }

   /**
    * Get pointer to the associated business framework session.
    * 
    * @return the BFSession pointer
    */
   BFSession *getBFSession() const;
   /**
    * Get pointer to the associated BFSession if it is a work session otherwise an error is thrown.
    * 
    * @return the BFWorkSession pointer
    */
   BFWorkSession *getBFWorkSession() const;

   /**
    * This method is used to check whether the user has "create" access to
    * a function. The request is passed on to the underlying BFWorkSession.
    * If this GI is at the user session level an exception will be thrown by
    * getBFWorkSession().
    * 
    * @param userAccessFunctionCode
    *               the function user want to access.
    * 
    * @return 
    */
   bool hasCreatePermission( const I_CHAR *userAccessFunctionCode ) const;

   /**
    * This method is used to check whether the user has "read" access to
    * a function. The request is passed on to the underlying BFWorkSession.
    * If this GI is at the user session level an exception will be thrown by
    * getBFWorkSession().
    * 
    * @param userAccessFunctionCode
    *               the function user want to access.
    * 
    * @return 
    */
   bool hasReadPermission( const I_CHAR *userAccessFunctionCode ) const;

   /**
    * This method is used to check whether the user has "update" access to
    * a function. The request is passed on to the underlying BFWorkSession.
    * If this GI is at the user session level an exception will be thrown by
    * getBFWorkSession().
    * 
    * @param userAccessFunctionCode
    *               the function user want to access.
    * 
    * @return 
    */
   bool hasUpdatePermission( const I_CHAR *userAccessFunctionCode ) const;

   /**
    * This method is used to check whether the user has "delete" access to
    * a function. The request is passed on to the underlying BFWorkSession.
    * If this GI is at the user session level an exception will be thrown by
    * getBFWorkSession().
    * 
    * @param userAccessFunctionCode
    *               the function user want to access.
    * 
    * @return 
    */
   bool hasDeletePermission( const I_CHAR *userAccessFunctionCode ) const;

   /**
    * This method completes the two step construction.
    * 
    * @return SEVERITY noting any error/warning conditions
    */
   SEVERITY init();
   /**
    * Get the modality of this object.
    * 
    * @return true if modal, false if modeless
    */
   bool isModal() const
   {
      return(cmd_.isModal());
   }

   /**
    * This method is used by the GenericInterfaceContainer to tell the parent
    * that the modeless child has been destroyed.
    * 
    * @param cmd    A reference to a command representing the object that has
    *               been destroyed.
    */
   void modelessChildComplete( const Command &cmd );
   /**
    * Used to bring a modeless dialog (via parent process) to the top of the
    * window stack.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * 
    * @return true if successful, check conditions if false
    */
   bool modelessSetFocus( GenericInterface *rpGICaller );
   /**
    * Used by child process to indicate final ok processing.
    * 
    * @param rpGI   A reference pointer to the calling object.
    * 
    * @return true if successful, check conditions if false
    */
   bool ok( GenericInterface *rpGI );
   /**
    * Subclasses will implement this method to initiate a search.  The caller
    * is expected to have set up any search criteria  (via setField) prior to
    * calling this method.
    * 
    * @param rpGI     A reference pointer to the calling object.
    * @param idSearch ID of specific search to perform.
    * @param eSearchAction
    *                 Search action to perform.  (Start or next block).
    * 
    * @return SEVERITY noting any error/warning conditions
    */
   virtual SEVERITY performSearch( GenericInterface *rpGI,
                                   const BFContainerId& idSearch,
                                   E_SEARCHACTION eSearchAction );
   /**
    * This method allows for a two step destruction of GenericInterface objects.
    * This is used by dialog objects in particular so DestroyWindow may be
    * invoked even when being directly deleted.  The GenericInterfaceContainer
    * performs this two step process.  To make this process consistent, this
    * two step process should be implemented wherever deletes occur.
    */
   virtual void predelete()
   {
   }
   /**
    * Used to start the major functionality of an object - for modeless
    * successful return means normal stuff done, screen created or whatever
    * but still can't delete until something indicates so and then need to
    * indicate to whoever is collecting me so they can release my storage,
    * etc.
    * This virtual method must be overridden.
    * 
    * @return an enum representing the return state
    */
   virtual E_COMMANDRETURN process() = 0;
   /**
    * Used by child, parent or GenericInterfaceContainer to tell another
    * object to check for refresh.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param szOriginalCommand
    *                   A string literal representing the original
    *                   command issuing the refresh (which may provide a hint on whether this
    *                   object needs to check for refresh).
    * 
    * @return true if successful, check conditions if false
    */
   bool refresh( GenericInterface *rpGICaller,
                 const I_CHAR *szOriginalCommand );
   /**
    * This method is used to register an observer.  An exception will be thrown
    * if the field or list cannot be found.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param idContainer
    *                   ID of the associated container to find.
    * @param idField    ID of the associated field to find.
    * @param idDataGroup    idDataGroup for commit/rollbackprocessing
    * @param rpObserver reference of observer to register
    * 
    * @return bool - true = successful
    */
   virtual bool registerObserver( const GenericInterface *rpGICaller,
                                  const BFContainerId& idContainer,
                                  const BFFieldId &idField,
                                  const BFDataGroupId& idDataGroup,
                                  BFObserver &rpObserver );

   /**
    * Used to reset (rollback) process data.  If idContainer = BF::AllContainerIds, the process
    * will reset all updatable containers.  If bCurrentItem = true, the process
    * will only reset the current item in the specified container, otherwise
    * the process will reset the specified container.
    * Exceptions will be thrown for invalid conditions.
    * This is a pure virtual method that must be overridden.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param idContainer
    *                   ID for the container to be reset.  ( 0 = all )
    * @param bCurrentItem
    *                   true = reset current item only, false = reset whole
    *                   container.  This parm should be false if the container is not repeatable.
    * 
    * @return SEVERITY noting any error/warning conditions
    */
   virtual SEVERITY reset( GenericInterface *rpGICaller,
                           const BFContainerId& idContainer = BF::AllContainerIds,
                           bool bCurrentItem = false );

   /**
    * Used to reset current list item.
    * 
    * @param idContainer
    *               ID for the container to be reset.
    * 
    * @return SEVERITY noting any error/warning conditions
    */
   virtual SEVERITY resetCurrentItem( const BFContainerId& idContainer );

   /**
    * Used to send a message synchronously.  By passing a generic interface
    * pointer, callbacks can be performed.  Messages would include SUBMIT,
    * ROLLBACK ??
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param szMessage  A string literal representing the message.
    * 
    * @return true if successful, check conditions if false
    */
   bool send( GenericInterface *rpGICaller,
              const I_CHAR *szMessage );

   /**
    * Used to set bulk data in the specified container.  If the container is
    * repeatable (ie a list), the caller is responsible for positioning the
    * list.
    * This is a pure virtual method that must be overridden.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param idContainer
    *                   ID for the container object (often a CBO).
    * @param rpData     A const reference pointer to data object for the data.
    * 
    * @return SEVERITY noting any error/warning conditions
    */
   virtual SEVERITY setData( GenericInterface *rpGICaller,
                             const BFContainerId& idContainer,
                             const BFData *rpData );

   /**
    * Used to set an individual field.  An exception will be thrown if the
    * field is not found.
    * This is a pure virtual method that must be overridden.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param idField    ID for field.
    * @param strValue   A const string reference to value for the data field.
    * @param bFormatted true = strValue is formatted,
    *                   false = strValue is raw host data.
    * 
    * @return SEVERITY noting any error/warning conditions
    */
   virtual SEVERITY setField( const GenericInterface *rpGICaller,
                              const BFFieldId &idField,
                              const DString &strValue,
                              bool bFormatted = true);

   /**
    * Used to set a value into a field in the specified container object.  If
    * the object is repeatable (ie a list), the caller is responsible for
    * positioning the list.  (See list methods outlined below.)
    * An exception will be thrown if the field is not found.
    * This is a pure virtual method that must be overridden.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param idContainer
    *                   ID for the container object (often a CBO).
    * @param idField    ID for field.
    * @param strValue   A const string reference to value for the data field.
    * @param bFormatted true = strValue is formatted,
    *                   false = strValue is raw host data.
    * 
    * @return SEVERITY noting any error/warning conditions
    */
   virtual SEVERITY setField( const GenericInterface *rpGICaller,
                              const BFContainerId& idContainer,
                              const BFFieldId &idField,
                              const DString &strValue,
                              bool bFormatted = true );

   /**
    * Pass-through method to set global value for a given field from the
    * InterProcessData.  These global fields must exist in DSTCGLOB.vw.
    * 
    * @param gType    Type of global to set.
    * @param idField  Data dictionary ID for the global field.
    * @param strValue A string with the value to be passed.
    */
   void setGlobal( E_GLOBALTYPE gType,
                   const BFFieldId &idField,
                   const DString &strValue );

   /**
    * Pass-through method to set parameter value for a given tag from the
    * InterProcessData.  This is used to pass values to an object you are about
    * to initiate through a command. This is public so outsiders can set
    * parameters.
    * 
    * @param strTag   A string with the tag name for the parameter.
    * @param strValue A string with the value to be passed.
    */
   void setParameter( const DString &strTag,
                      const DString &strValue );


   // ***************   List methods    *******************

   /**
    * This method is used to delete the current item from a list.
    * An exception will be thrown if the list or item could not be found.
    * See note about lists in class document block.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param idList     ID of list we are using.
    * 
    * @return highest SEVERITY encountered, check conditions.
    */
   virtual SEVERITY deleteItemFromList( const GenericInterface *rpGICaller,
                                        const BFContainerId& idList );

   /**
    * This method is used to get the key of the current item in a list.
    * An exception will be thrown if the list cannot be found.
    * See note about lists in class document block.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param idList     ID of list we are using.
    * 
    * @return the key to the current list item.  This will be an empty string
    *         if the list is empty.
    */
   virtual const DString &getCurrentListItemKey( const GenericInterface *rpGICaller,
                                                 const BFContainerId& idList );

   /**
    * This method is used to get the key to the first item in a list.  This
    * will also set the first item as the current item in the list.
    * An exception will be thrown if the list cannot be found.
    * See note about lists in class document block.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param idList     ID of list we are using.
    * 
    * @return the key to the first list item.  This will be an empty string
    *         if the list is empty.
    */
   virtual const DString &getFirstListItemKey( const GenericInterface *rpGICaller,
                                               const BFContainerId& idList );

   /**
    * This method is used (typically by an associated GUI component) to get a
    * key to a new list item.
    * Exceptions will be thrown for any failure.
    * See note about lists in class document block.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param idList     ID of list we are using.
    * 
    * @return reference to const DString key to the new list item.
    *         This item will be set as the current item in the list.
    */
   virtual const DString &getKeyForNewListItem( const GenericInterface *rpGICaller,
                                                const BFContainerId& idList );

   /**
    * This method is used to get the key to the next item in a list.  This
    * will also set the first item as the current item in the list.
    * An exception will be thrown if the list cannot be found.
    * See note about lists in class document block.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param idList     ID of list we are using.
    * 
    * @return the key to the next list item.  This will be an empty string
    *         if at the end of the list.
    */
   virtual const DString &getNextListItemKey( const GenericInterface *rpGICaller,
                                              const BFContainerId& idList );

   /**
    * This method will return the number of items in a specific list.  An
    * exception will be thrown if the list is not found.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param idList     ID of list to use.
    * 
    * @return integer count of number of items in the list.
    */
   virtual int getNumberOfItemsInList( const GenericInterface *rpGICaller,
                                       const BFContainerId& idList );

   /**
    * This method is used to set the current item in a list.
    * An exception will be thrown if the item is not found.
    * See note about lists in class document block.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param idList     ID of list we are using.
    * @param strListItemKey
    *                   The key to the list item.  This item will be set
    *                   as the current item in the list.
    */
   virtual void setCurrentListItem( const GenericInterface *rpGICaller,
                                    const BFContainerId& idList,
                                    const DString &strListItemKey );

   /**
    * this function checks whether current work session has updates
    * 
    * @return true if there are updates.
    */
   virtual bool workSessionHasUpdates( );

   class ProcessObserver {
   public:
      virtual void notifyOk( const GenericInterface *rpGICaller,
                             AbstractProcess *process) = 0;
   };

   ProcessObserver* getProcessObserver(void) {
      return _procObserver;
   }

   void setProcessObserver(ProcessObserver* newProcObserver) {
      _procObserver=newProcObserver;
   }



protected:
   /**
    * `Virtualized method that must be overridden in the subclasses to
    * support the ok method.  This is typically overridden in another base
    * class.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * 
    * @return highest SEVERITY encountered, check conditions
    */
   virtual SEVERITY cancel2( GenericInterface *rpGICaller ) = 0;
   /**
    * Virtualized method that must be overridden in the subclasses to support
    * the getData method.
    * Used to get data from another GenericInterface via generic data passing
    * mechanism.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param rpData     A reference pointer to data object for the data.
    * 
    * @return true if successful, check conditions if false
    */
   virtual bool doGetData( GenericInterface *rpGICaller,
                           BFData *rpData ) const = 0;

   /**
    * Virtualized method that must be overridden in the subclasses to support
    * the modelessChildComplete method.
    * modelessChildComplete is used by the GenericInterfaceContainer to tell
    * the parent that the modeless child has been destroyed.
    * 
    * @param cmd    A reference to a command representing the object that has
    *               been destroyed.  This is not valid outside the scope of this call.
    * 
    * @return true if this modeless object should end as well, false if not
    *         done yet.  When returning true, the calling modelessChildComplete method
    *         will call GenericInterfaceContainer::modelessDestroySelf to delete and
    *         remove this object from the container
    */
   virtual bool doModelessChildComplete( const Command& cmd ) = 0;
   
   /**
    * Virtualized method that must be overridden in the subclasses to support
    * the modelessSetFocus method.
    * Used to bring a modeless dialog (via parent process) to the top of the
    * window stack.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * 
    * @return true if successful, check conditions if false
    */
   virtual bool doModelessSetFocus( GenericInterface *rpGICaller ) = 0;

   /**
    * Virtualized method that must be overridden in the subclasses to support
    * the refresh method.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param szOriginalCommand
    *                   A string literal representing the original
    *                   command issuing the refresh (which may provide a hint on whether this
    *                   object needs to check for refresh).
    * 
    * @return true if successful, check conditions if false
    */
   virtual bool doRefresh( GenericInterface *rpGICaller,
                           const I_CHAR *szOriginalCommand ) = 0;

   /**
    * Virtualized method that must be overridden in the subclasses to
    * support the send method.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param szMessage  A string literal representing the message.
    * 
    * @return true if successful, check conditions if false
    */
   virtual bool doSend( GenericInterface *rpGICaller,
                        const I_CHAR *szMessage ) = 0;

   /**
    * Get the process type associated with this object's command
    * 
    * @return enum of the process type
    */
   E_PROCESSTYPE getProcessType() const
   {
      return(cmd_.getProcessType());
   }

   /**
    * This method returns the associated work session GI pointer for all
    * processes except the UserSessionProcess.
    * 
    * @return work session pointer (NULL if called from UserSessionProcess)
    */
   GenericInterface *getWorkSession()
   {
      return(_rpGIWorkSession);
   }

   /**
    * This method indicates if the process method has been run.
    * 
    * @return true if the process method has run.
    */
   bool hasProcessRun() const
   {
      return(_bProcessHasRun);
   }

   /**
    * Virtualized method that must be overridden in the subclasses to support
    * the init method.  The override should perform any initialization
    * required, including getting parameters from InterProcessData (they get
    * cleared after this call).
    * 
    * @return SEVERITY noting any error/warning conditions
    */

   virtual SEVERITY init2() = 0;
   /**
    * This method is used to invoke any command from any of the derived
    * subclasses.
    * 
    * @param rpGIParent A reference pointer to the parent for this command.
    * @param szCommand  The string literal associated with the command.
    * @param type       The enum for the process type.
    * @param bModal     Flag where true is modal and false is modeless.
    * @param rpModelessOut
    *                   A pointer to a reference pointer which is set by
    *                   this method.  A non-null pointer means that a modeless process/dialog is
    *                   still in process.  This pointer may be used to communicate with the
    *                   process/dialog, but caution should be used since these pointers may
    *                   become invalid when the modeless process is shut down.  Always use
    *                   validateModelessPointer prior to use.
    * 
    * @return an enum representing the return type
    */
   E_COMMANDRETURN invokeCommand( GenericInterface *rpGIParent,
                                  const I_CHAR *szCommand,
                                  E_PROCESSTYPE type,
                                  bool bModal,
                                  GenericInterface **rpModelessOut );

   /**
    * This method is used to invoke any command from any of the derived
    * subclasses with the parent being the associated work session.
    * 
    * @param szCommand The string literal associated with the command.
    * @param type      The enum for the process type.
    * @param bModal    Flag where true is modal and false is modeless.
    * @param rpModelessOut
    *                  A pointer to a reference pointer which is set by
    *                  this method.  A non-null pointer means that a modeless process/dialog is
    *                  still in process.  This pointer may be used to communicate with the
    *                  process/dialog, but caution should be used since these pointers may
    *                  become invalid when the modeless process is shut down.  Always use
    *                  validateModelessPointer prior to use.
    * 
    * @return an enum representing the return type
    */
   E_COMMANDRETURN invokeCommand( const I_CHAR *szCommand,
                                  E_PROCESSTYPE type,
                                  bool bModal,
                                  GenericInterface **rpModelessOut );

   /**
    * This method returns the XMLAPI context.  If true, no GUI commands should
    * be invoked.
    * 
    * @return true = running for XMLAPI.
    */
   bool isXMLAPIContext()
   {
      return(_bXMLAPIContext);
   }

   /**
    * This method is used to validate that a modeless GenericInterface pointer
    * (not the current object) is still valid for use.  This should be used
    * every time prior to invoking a method on a GenericInterface pointer
    * returned from invokeCommand.
    * 
    * @param rpGI   A reference pointer to the object to validate.
    * 
    * @return true if valid, if false failed (no errors)
    */
   bool isValidModelessInterface( GenericInterface *rpGI );

   /**
    * Virtualized method that must be overridden in the subclasses to
    * support the ok method.  This is typically overridden in another base
    * class.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * 
    * @return highest SEVERITY encountered, check conditions
    */
   virtual SEVERITY ok2( GenericInterface *rpGICaller ) = 0;

   /**
    * This method sets the associated GenericInterfaceContainer (by userID).
    * 
    * @param rpGIC  A reference pointer to GenericInterfaceContainer to set.
    */
   void setGIContainer( GenericInterfaceContainer *rpGIC )
   {
      _rpGIContainer = rpGIC;
   }

   /**
    * This method is used to set our group ID.
    * 
    * @param id     The group ID to set.
    */
   virtual void setDataGroupId( const BFDataGroupId& idDataGroup );

   /**
    * This method sets the flag to indicate if the process method has been run.
    * 
    * @param bRun   set to true if the process method has run.
    */
   void setProcessHasRun( bool bRun )
   {
      _bProcessHasRun = bRun;
   }

   /**
    * This method sets the flag to indicate if running in XMLAPI context.
    *  (no GUI)
    * 
    * @param bXMLAPIContext
    *               set to true if running in XMLAPI context.
    *               Note, in NASU, server context use gui implementation, so api needs its own context
    */
   void setXMLAPIContext( bool bXMLAPIContext )
   {
      _bXMLAPIContext = bXMLAPIContext;
   }

   /**
    * This method is used to set a new Session object.  By doing this, the
    * assumption is that this object owns the Session object and will delete
    * it when this object is deleted.
    * 
    * @param pSession A pointer to the Session object to set.
    * @param bOwn     true = object owns Session object and must delete
    */
   void setSession( BFCPSession *pSession,
                    bool bOwn )
   {
      _pSession = pSession;
      _bOwnsSession = bOwn;
   }

   /**
    * This method sets the associated work session.  This should only be
    * used by the WorkSessionProcess.  Otherwise, the work session id is
    * initialized in this classes constructor.
    * 
    * @param bfSession The work session pointer.
    * @param rpGIWorkSession
    *                  Reference pointer to work session.
    */
   void setWorkSession( BFSession *bfSession,
                        GenericInterface *rpGIWorkSession );

   /**
    * This method sets the user session ID.
    * 
    * @param bfSession The user session pointer.
    */
   void setBFSession( BFSession *bfSession )
   {
      _bfSession = bfSession;
   }
private:

   GenericInterface::ProcessObserver* _procObserver;

   /**
    * _bOwnsSession indicates whether or not this object owns the associated
    * Session object (_pSession).  This defaults to false but may be set when
    * setting a new Session object in the setSession method.  During the
    * destructor, if this flag is true then _pSession will be deleted.
    */
   bool _bOwnsSession;               
   bool _bProcessHasRun;
   bool _bXMLAPIContext;     // True = XMLAPI mode (no GUI)
   Command cmd_;
   BFDataGroupId idDataGroup_;
   GenericInterfaceContainer* _rpGIContainer;
   GenericInterface* _rpGIParent;
   GenericInterface* _rpGIWorkSession;
   BFCPSession* _pSession;

   BFSession* _bfSession;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/bfproc/GenericInterface.hpp-arc  $
//
//   Rev 1.29   May 14 2004 16:13:14   SMITHDAV
//Removed "global data areas" from InterProcessData" and cleaned up the related interfaces. They are now in the BFSession objects.
//
//   Rev 1.28   May 24 2003 14:56:48   PURDYECH
//Added getItemErrors and getItemErrorState
 * 
 *    Rev 1.27   Mar 20 2003 15:07:54   PURDYECH
 * performSearch and doMoreRecordsExist had bad method signatures.
 * 
 *    Rev 1.26   Feb 12 2003 14:08:28   PURDYECH
 * ServerContext code moved to BFUtil
 * 
 *    Rev 1.25   Jan 14 2003 11:04:26   PURDYECH
 * DataGroupid parentage knowledge
 * 
 *    Rev 1.24   Jan 06 2003 16:43:52   PURDYECH
 * BFDataGroupId and BFContainerId changeover
 * 
 *    Rev 1.23   Nov 27 2002 15:04:38   PURDYECH
 * Documentation Changes
 * 
 *    Rev 1.22   Oct 09 2002 17:40:56   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.21   Aug 29 2002 12:51:16   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.20   May 28 2002 12:17:22   PURDYECH
 * BFData Implementation - Phase II
 * 
 *    Rev 1.19   22 May 2002 18:08:52   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.18   27 Mar 2002 19:52:46   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.17   22 Mar 2002 15:11:52   PURDYECH
 * Removed compile-time "including..." message
 * Use #pragma once as include guard
 * Include files with lower-case only names
 * 
 *    Rev 1.16   25 Oct 2001 14:02:44   SMITHDAV
 * hasPermission changes...
 * 
 *    Rev 1.15   16 Aug 2001 17:10:12   PURDYECH
 * Made the serverContext methods public.
 * 
 *    Rev 1.14   26 Jul 2001 13:43:16   YINGZ
 * fix reset, cancel problems
 * 
 *    Rev 1.13   04 Jul 2001 15:16:52   YINGZ
 * cleanup
 * 
 *    Rev 1.12   29 Jun 2001 10:55:52   YINGZ
 * add canCancel to support cancel machenism
 * 
 *    Rev 1.11   03 May 2001 14:03:28   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.10   Mar 27 2001 13:57:40   YINGZ
 * add workSessionHasUpdates
 * 
 *    Rev 1.9   Feb 21 2001 11:31:48   YINGZ
 * add xmlapi context
 * 
 *    Rev 1.8   Nov 08 2000 12:21:08   DT24433
 * added server context flag
 * 
 *    Rev 1.7   Oct 26 2000 10:39:46   DT24433
 * Change to pass GIC instead of session
 * 
 *    Rev 1.6   16 Aug 2000 11:48:02   PURDYECH
 * Added getAllErrors method to retrieve all errors for the caller (both field level and object level).
 * 
 *    Rev 1.5   Aug 02 2000 15:31:36   BUZILA
 * "locale" changes
 * 
 *    Rev 1.4   Jun 23 2000 12:46:02   DT24433
 * changes to support setData
 * 
 *    Rev 1.3   Apr 04 2000 14:41:26   DT24433
 * changed to store associated GIContainer and make available
 * 
 *    Rev 1.2   Mar 09 2000 10:59:44   DT24433
 * made haspermission virtual
 * 
 *    Rev 1.1   Feb 15 2000 18:55:00   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:57:48   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.19   Jan 28 2000 15:22:14   PRAGERYA
 * For release
 * 
 *    Rev 1.18   Jan 19 2000 15:17:14   DT24433
 * added getErrorState
 * 
 *    Rev 1.17   Jan 11 2000 11:26:20   DT24433
 * changed to return bool for registerObserver
 * 
 *    Rev 1.16   Jan 06 2000 15:02:38   DT24433
 * added clearParameters
 * 
 *    Rev 1.15   Dec 22 1999 12:27:54   DT24433
 * parm changed in register/deregister
 * 
 *    Rev 1.14   Dec 21 1999 13:45:28   DT24433
 * initial notification changes
 * 
 *    Rev 1.13   Dec 16 1999 18:16:32   VASILEAD
 * Made reset a virtual method
 * 
 *    Rev 1.12   Dec 16 1999 12:38:10   YINGZ
 * add hasPermission
 * 
 *    Rev 1.11   Nov 19 1999 17:33:02   DT24433
 * added new doxxx literals
 * 
 *    Rev 1.10   Nov 11 1999 08:51:28   DT24433
 * changed getFieldAttributes interface
 * 
 *    Rev 1.9   Nov 05 1999 15:25:32   DT24433
 * added getErrors
 * 
 *    Rev 1.8   Oct 28 1999 16:45:30   DT24433
 * replaced doOk/doCancel with ok2/cancel2 since these will typically be overridden in another base class
 * 
 *    Rev 1.7   Oct 28 1999 13:48:24   VASILEAD
 * add/delete/reset & group processing
 * 
 *    Rev 1.6   Oct 25 1999 10:28:30   DT24433
 * changed return for getKeyForNewListItem
 * 
 *    Rev 1.5   Oct 25 1999 09:57:38   DT24433
 * changed interface for getKeyForNewListItem
 * 
 *    Rev 1.4   Aug 26 1999 16:38:54   DT24433
 * removed getFieldFromCurrentListItem
 * 
 *    Rev 1.3   Aug 03 1999 14:20:04   DT24433
 * container changes
 * 
 *    Rev 1.2   Jul 16 1999 10:32:30   PRAGERYA
 * afds
 * 
 *    Rev 1.1   Jul 08 1999 10:03:44   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
