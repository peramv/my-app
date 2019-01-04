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
#include <bfproc\abstractprocessconstants.h>
#include <bfproc\genericinterface.hpp>
#include <bfcbo\bfabstractcbo.hpp>
#include <bfdata\bfdata.hpp>
#include <bfproc\bfcontainerid.hpp>


// Forward references
class AbstractListDetails;
class BFProperties;
class FieldDetails;
class ListDetails;
class UserSessionProcess;

typedef std::vector< DString > FIELD_NAMES;

// Import/Export resolution
#undef BPBASE_LINKAGE
#ifdef BPBASE_DLL
   #define BPBASE_LINKAGE CLASS_EXPORT
#else
   #define BPBASE_LINKAGE CLASS_IMPORT
#endif

/**
  * This is the abstract base class for all processes.
  *
  * This class may be used to add process specific (as opposed to dialog specific)
  * base code.  This class also determines which methods of the GenericInterface
  * are required by subclasses to implement and which ones are optional.
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
  * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 10/27/98</dd></dl>
  * @version 0.1
  */
class BPBASE_LINKAGE AbstractProcess : public GenericInterface
{
   friend ListDetails;
   friend UserSessionProcess;
public:
   /**
    * General use constructor for AbstractProcess.
    * 
    * @param rpGIC      Pointer to the GenericInterfaceContainer to which this AbstractProcess
    *                   belongs
    * @param rpGIParent Pointer to the creating GenericInterface.
    * @param cmd        A const reference to a Command object.
    * 
    * @see GenericInterfaceContainer
    * @see GenericInterface
    * @see Command
    */
   AbstractProcess( GenericInterfaceContainer *rpGIC,
                    GenericInterface* rpGIParent,
                    const Command &cmd);
private:
   /**
    * A plain constructor for use by friend classes.  This is necessary
    * for UserSessionProcess as it may need to create other objects with
    * nothing.
    */
   AbstractProcess();   

private:
   static const DString s_empty_;
public:
   /**
    * Return a reference to an empty DString.
    * 
    * @return A const reference to an empty DString (i.e. value of I_(""))
    */
   static const DString& emtpyString() { return s_empty_; }

   /**
    * Destructor
    */
   virtual ~AbstractProcess();

   /**
    * This method is used to deregister an observer.  An exception will be
    * thrown if the field or list cannot be found.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param idContainer
    *                   ID of the associated container to find.
    * @param fieldID    ID of the associated field to find.
    * @param idDataGroup
    *                   DataGroupID for commit/rollbackprocessing
    * @param rpObserver reference of observer to deregister
    */
   virtual void deregisterObserver( const GenericInterface* rpGICaller,
                                    const BFContainerId& idContainer,
                                    const BFFieldId &fieldID,
                                    const BFDataGroupId& idDataGroup,
                                    BFObserver &rpObserver );
   /**
    * Used to fire a specific cross-edit.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param idContainer
    *                   ID for the container CBO object.
    * @param crossEditID
    *                   ID for cross-edit to fire (-1 = validateAll)
    * @param lValidateGroup
    *                   specify which validate group to validate. 0 = all groups
    * 
    * @return highest severity encountered
    */
   virtual SEVERITY fireCrossEdit( const GenericInterface* rpGICaller,
                                   const BFContainerId& idContainer,
                                   const BFFieldId &crossEditID,
                                   long lValidateGroup = 0 );
   /**
    * This method returns the container ID associated with a specific
    * name.
    * 
    * @param name   Name to match on.
    * 
    * @return Matching container ID for BF::AllContainerIds if no matching container
    *         was found.  This error return value is retained for historical
    *         reasons.
    */
   const BFContainerId& getContainerID( const DString &name );
   /**
    * Used to get the fields associated with a cross-edit.
    * An exception will be thrown if any errors encountered.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param idContainer
    *                   ID for the container CBO object.
    * @param crossEditID
    *                   ID for cross-edit to retrieve.
    * @param fieldVector
    *                   vector to return fields in.
    */
   void getCrossEditFields( const GenericInterface* rpGICaller,
                            const BFContainerId& idContainer,
                            const BFFieldId &crossEditID,
                            std::vector< BFFieldId > &fieldVector );

   /**
    * Used to get the all of the current errors for a given object.
    * Exceptions will be thrown on errors.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param conditions CONDITIONVECTOR to return conditions in.
    * 
    * @return highest SEVERITY for field
    */
   virtual SEVERITY getAllErrors( GenericInterface* rpGICaller,
                                  CONDITIONVECTOR &conditions );
   /**
    * Used to get the current errors for a field, container, or all containers.
    * If both idContainer & fieldID are passed in as 0 then all non-field
    * specific errors will be returned.  If field is 0, then all errors for a
    * container will be returned.
    * Exceptions will be thrown on errors.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param idContainer
    *                   ID for the container object (often a CBO).
    * @param fieldID    ID for field.
    * @param conditions CONDITIONVECTOR to return conditions in.
    * 
    * @return highest SEVERITY for field
    */
   virtual SEVERITY getErrors( GenericInterface* rpGICaller,
                               const BFContainerId& idContainer,
                               const BFFieldId &fieldID,
                               CONDITIONVECTOR &conditions );

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
    * 
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
   virtual void getErrorState( GenericInterface* rpGICaller,
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
    * This method is used (typically by an associated GUI component) to get the
    * value for a field.
    * 
    * An exception will be thrown if field cannot be obtained.
    * 
    * This implementation should not be overridden.  Use the flags in the
    * FieldDetails structure to initiate alternative processing. Use
    * SUBCLASS_PROCESS if you want your subclass to process the set for a
    * specific field.  This flag will cause this method to call doGetField in
    * the subclass.  You can also use RELAY_TO_PARENT to send the setField to
    * your object's parent.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param fieldID    ID for field.
    * @param strValueOut
    *                   A string reference where value of the data field
    *                   will be returned.
    * @param bFormatted Flag indicating whether to get the data formatted.
    */
   virtual void getField( const GenericInterface* rpGICaller,
                          const BFFieldId &fieldID,
                          DString &strValueOut,
                          bool bFormatted = true );
   /**
    * This method is used (typically by an associated GUI component) to get the
    * value for a field from the specified container object.
    * An exception will be thrown if field cannot be obtained.
    * This implementation should not be overridden.  Use the flags in the
    * FieldDetails structure to initiate alternative processing. Use
    * SUBCLASS_PROCESS if you want your subclass to process the get for a
    * specific field.  This flag will cause this method to call doGetField in
    * the subclass.  You can also use RELAY_TO_PARENT to send the getField to
    * your object's parent.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param idContainer
    *                   ID for container object (usually a CBO)
    * @param fieldID    ID for field.
    * @param strValueOut
    *                   A string reference where value of the data field
    *                   will be returned.
    * @param bFormatted Flag indicating whether to get the data formatted.
    */
   virtual void getField( const GenericInterface* rpGICaller,
                          const BFContainerId& idContainer,
                          const BFFieldId &fieldID,
                          DString &strValueOut,
                          bool bFormatted = true );
   /**
    * This method is used (typically by an associated GUI component) to get the
    * attributes for a field.  An exception will be thrown if the
    * field or list cannot be found.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param idContainer
    *                   ID of container to find.
    * @param fieldID    ID of field to find.
    * 
    * @return constant reference pointer to BFProperties or NULL if none
    */
   virtual const BFProperties *getFieldAttributes( const GenericInterface* rpGICaller,
                                                   const BFContainerId& idContainer,
                                                   const BFFieldId &fieldID );
   /**
    * This method is used to invoke a command using this process as parent.
    * If the command is being invoked modally, the child's associated data
    * group will be used as the parent data group for the invoked process.
    * 
    * @param rpGICaller A reference pointer to the child's GenericInterface.
    * @param szCommand  A string literal representing the command to be
    *                   invoked.  This is used to lookup the command and create the command
    *                   object which is associated.
    * @param type       An enum representing the process type for the command.
    *                   This type is used to create the command object associated with this
    *                   command.
    * @param bModal     Flag where true is modal and false is modeless.
    * @param rpGIModelessOut
    *                   A pointer to a reference pointer which is set by
    *                   this method.  A non-null pointer means that a modeless process/dialog is
    *                   still in process.  This pointer may be used to communicate with the
    *                   process/dialog, but caution should be used since these pointers may
    *                   become invalid when the modeless process is shut down.  Always use
    *                   validateModelessPointer prior to use.
    * 
    * @return an enum representing the return type
    */
   E_COMMANDRETURN invokeProcessFromChild( GenericInterface* rpGICaller,
                                           const I_CHAR *szCommand,
                                           E_PROCESSTYPE type,
                                           bool bModal = true,
                                           GenericInterface **rpGIModelessOut = NULL );
   /**
    * Used to start the major functionality of an object - for modeless
    * successful return means normal stuff done, screen created or whatever
    * but still can't delete until something indicates so and then need to
    * indicate to whoever is collecting me so they can release my storage,
    * etc.
    * Derived classes must implement doProcess and should not override this
    * method.
    * 
    * @return an enum representing the return state
    */
   virtual E_COMMANDRETURN process();
   /**
    * This method is used to register an observer.  An exception will be
    * thrown if the field or list cannot be found.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param idContainer
    *                   ID of the associated container to find.
    * @param fieldID    ID of the associated field to find.
    * @param idDataGroup
    *                   idDataGroup for commit/rollbackprocessing
    * @param rpObserver reference of observer to register
    * 
    * @return true if successfully registered
    */
   virtual bool registerObserver( const GenericInterface* rpGICaller,
                                  const BFContainerId& idContainer,
                                  const BFFieldId &fieldID,
                                  const BFDataGroupId& idDataGroup,
                                  BFObserver &rpObserver );
   /**
    * This method is used (typically by an associated GUI component) to set a
    * value in a field.
    * An exception will be thrown if field cannot be obtained.
    * This implementation should not be overridden.  Use the flags in the
    * FieldDetails structure to initiate alternative processing. Use
    * SUBCLASS_PROCESS if you want your subclass to process the set for a
    * specific field.  This flag will cause this method to call doSetField in
    * the subclass.  You can also use RELAY_TO_PARENT to send the setField to
    * your object's parent.
    * This is usually not implemented in a dialog.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param fieldID    ID for field.
    * @param strValue   A const string reference to value for the data field.
    * @param bFormatted true = strValue is formatted,
    *                   false = strValue is raw host data.
    * 
    * @return SEVERITY noting any error/warning conditions
    */
   virtual SEVERITY setField( const GenericInterface* rpGICaller,
                              const BFFieldId &fieldID,
                              const DString &strValue,
                              bool bFormatted = true );
   /**
    * This method is used (typically by an associated GUI component) to set a
    * value in a field from the specified container object.
    * An exception will be thrown if field cannot be obtained.
    * This implementation should not be overridden.  Use the flags in the
    * FieldDetails structure to initiate alternative processing. Use
    * SUBCLASS_PROCESS if you want your subclass to process the set for a
    * specific field.  This flag will cause this method to call doSetField in
    * the subclass.  You can also use RELAY_TO_PARENT to send the setField to
    * your object's parent.
    * This is usually not implemented in a dialog.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param idContainer
    *                   ID for container object.
    * @param fieldID    ID for field.
    * @param strValue   A const string reference to value for the data field.
    * @param bFormatted true = strValue is formatted,
    *                   false = strValue is raw host data.
    * 
    * @return SEVERITY noting any error/warning conditions
    */
   virtual SEVERITY setField( const GenericInterface* rpGICaller,
                              const BFContainerId& idContainer,
                              const BFFieldId &fieldID,
                              const DString &strValue,
                              bool bFormatted = true );

   // ***************   List methods    *******************

   /**
    * This method is used (typically by a GUI object) to delete the current
    * item from a list.
    * An exception will be thrown if the list or item could not be found.
    * See note about lists in class document block.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param idList     ID of list we are using.
    * 
    * @return highest SEVERITY encountered, check conditions.
    */
   virtual SEVERITY deleteItemFromList( const GenericInterface* rpGICaller, const BFContainerId& idList );
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
   virtual const DString &getCurrentListItemKey( const GenericInterface* rpGICaller, const BFContainerId& idList );
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
   virtual const DString &getKeyForNewListItem( const GenericInterface* rpGICaller, const BFContainerId& idList );
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
   virtual const DString &getFirstListItemKey( const GenericInterface* rpGICaller, const BFContainerId& idList );
   /**
    * This method is used to get the key to the next item in a list.  This
    * will also set the item as the current item in the list.
    * An exception will be thrown if the list cannot be found.
    * See note about lists in class document block.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param idList     ID of list we are using.
    * 
    * @return the key to the next list item.  This will be an empty string
    *         if at the end of the list.
    */
   virtual const DString &getNextListItemKey( const GenericInterface* rpGICaller, const BFContainerId& idList );
   /**
    * This method will return the number of items in a specific list.  An
    * exception will be thrown if the list is not found.
    * See note about lists in class document block.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param idList     ID of list to use.
    * 
    * @return integer count of number of items in the list.
    */
   virtual int getNumberOfItemsInList( const GenericInterface* rpGICaller, const BFContainerId& idList );
   /**
    * This method is used to see if current list item is new (never been
    * saved).  An exception will be thrown if the list is not found.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param idList     ID for list container object.
    * 
    * @return true if new, false otherwise
    */
   bool isCurrentListItemNew( GenericInterface* rpGICaller, const BFContainerId& idList );
   /**
    * Used to reset (rollback) process data.  If idContainer = 0, the process
    * will reset all updatable containers.  If bCurrentItem = true, the process
    * will only reset the current item in the specified container, otherwise
    * the process will reset the specified container.
    * Exceptions will be thrown for invalid conditions.
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
   SEVERITY reset( GenericInterface* rpGICaller,
                   const BFContainerId& idContainer = BF::AllContainerIds,
                   bool bCurrentItem = false );
   /**
    * Used to reset current list item.
    * 
    * @param idContainer
    *               ID for the container to be reset.  ( 0 = all )
    * 
    * @return SEVERITY noting any error/warning conditions
    */
   SEVERITY resetCurrentItem( const BFContainerId& idContainer );
   /**
    * This method is used (typically by an associated GUI component) to set the
    * current item in a list.  An exception will be thrown if the item is not
    * found.
    * See note about lists in class document block.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param idList     ID of list we are using.
    * @param strListItemKey
    *                   The key to the list item.  This item will be set
    *                   as the current item in the list.
    */
   virtual void setCurrentListItem( const GenericInterface* rpGICaller,
                                    const BFContainerId& idList,
                                    const DString &strListItemKey );
   /**
    * This method is used (typically by an associated GUI component) to set the
    * current item in a list.  The field will be clear if the item does not exist
    * See note about lists in class document block.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param idList     ID of list we are using.
    * @param strListItemKey
    *                   The key to the list item.  This item will be set
    *                   as the current item in the list.
    */
   virtual void trySetCurrentListItem( const GenericInterface* rpGICaller,
                                       const BFContainerId& idList,
                                       const DString &strListItemKey );
   /**
    * This method is set the current list item of container idList
    * using the info provided in pKeyInfo
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param idList     ID of list we are using.
    * @param pKeyInfo   Pointer to a BFData object will be passed to associated BFCBO object's getStrKey function.
    */
   virtual void setCurrentListItem( const GenericInterface* rpGICaller,
                                    const BFContainerId& idList,
                                    const BFData* pKeyInfo );

   bool isRepeatable( const BFContainerId& idContainer );

   const ClientLocale &getClientLocale() const;

   /**
    * This method is used to see if current list item is dummy.
    * An exception will be thrown if the list is not found.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param idList     ID for list container object.
    * 
    * @return true if dummy, false otherwise
    */
   bool isCurrentListItemDummy( GenericInterface* rpGICaller, const BFContainerId& idList );
   /**
    * This method is used to get all the field names indicated in FieldDetail related to
    * idContainer.
    * 
    * @param idContainer
    *               ID of the container to get the fields for
    * @param containerFields
    *               Reference to a vector of field names.
    */
   void getFieldsInContainer( const BFContainerId& idContainer, FIELD_NAMES& containerFields) const;

   /**
    * A process will normally commit a datagroup during ok2() processing
    * if no conditions with a severity of WARNING <i>or greater</i>
    * were detected.  Calling this function with <b>true</b> will cause
    * this process to ignore WARNING conditions during ok2() processing.
    * Calling this function with <b>false</b> will cause WARNING
    * conditions to stop commit processing.
    * 
    * @param flag   true if WARNING conditions can be safely ignored.
    * 
    * @see #ok2
    * @see #getIgnoreWarningsOnOk2
    */
   void setIgnoreWarningsOnOk2( bool flag = true );

   /**
    * Determine if this process's WorkSession has any pending updates.
    * 
    * @return true if the associated worksession has pending updates.
    */
   bool workSessionHasUpdates();


   /**
    * Get the current behaviour for ok2() with respect to ignoring warnings.
    * 
    * @return true if ok2() will ignore WARNING conditions during commit processing.
    * @see #ok2
    * @see #setIgnoreWarningsOnOk2
    */
   bool getIgnoreWarningsOnOk2() { return bIgnoreWarningsOnOk2_;}

   /**
    * Determine if the specified container is valid for use.
    * 
    * @param idContainer
    *               The container in question.
    * 
    * @return true if valid, false otherwise.
    */
   bool isContainerValid( const BFContainerId& idContainer );

protected:

   /**
    * Use this method in derived class constructors to add a container to the
    * set of containers for the class.
    * 
    * @param idContainer
    *                   ID of container to add
    * @param bRepeatable
    *                   true if this is a list type container
    * @param idParentContainer
    *                   ID of the parent container.  Changes in the parent will cause a reset in this container.
    * @param bUpdatable true = container is updatable, false = read only
    * @param name       Name of container
    */
   void addContainer( const BFContainerId& idContainer,
                      bool bRepeatable,
                      const BFContainerId& idParentContainer = BF::NullContainerId,
                      bool bUpdatable = false,
                      const DString &name = NULL_STRING );

   /**
    * Use this method in derived class constructors to add field details to the
    * set of fields for the class.
    * 
    * @param fieldID ID of field to add.
    * @param idContainer
    *                ID of container the field belongs to, or NULL
    * @param eFieldProcessFlag
    *                Flag noting type of processing for field.
    * @param szTag   Name of field if not in the dictionary, NULL otherwise
    *                base class becomes the owner and WILL delete.
    */
   void addFieldDetails( const BFFieldId &fieldID,
                         const BFContainerId& idContainer,
                         E_FIELDPROCESSFLAG eFieldProcessFlag = NORMAL,
                         const I_CHAR *szTag = NULL );
   /**
    * Use this method in derived class constructors to add a substitute list
    * to the set of lists for the class.
    * 
    * @param fieldId field with substitution set
    * @param name    the name of the container
    */
   void addSubstituteList( const BFFieldId &fieldId, 
                           const DString &name = NULL_STRING );

   /**
    * This method provides a base implementation for cancel, including
    * prompting for save if changes and rollback of changes in associated
    * CBO's.
    * 
    * @param rpGICaller A reference pointer to the calling GenericInterface.
    *                   returns returns highest SEVERITY encountered, check conditions
    * 
    * @return Current highest SEVERITY for this frame.
    */
   SEVERITY cancel2( GenericInterface* rpGICaller );

   /**
    * This method is optional - override if subclass needs to implement.
    * 
    * @param rpGICaller A reference pointer to the calling GenericInterface.
    * 
    * @return true if cancel should continue, false if cancel should halt
    */
   virtual bool doCancel( GenericInterface* rpGICaller )
   {
      return(true);
   }

   /**
    * This method is optional - override if subclass needs to implement.
    * 
    * @param rpGICaller A reference pointer to the calling GenericInterface.
    * @param rpData     A reference pointer to Data object for data.
    * 
    * @return true if successful
    */

   virtual bool doGetData( GenericInterface* rpGICaller,
                           BFData* rpData ) const
   {
      return(false);
   }

   /**
    * This method is used to implement subclass overrides for getErrors.
    * The business process must determine where to locate the field.
    * Override this method and set appropriate flags via addFieldDetails,
    * if the derived class must process getErrors differently than this
    * base class does.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param idContainer
    *                   ID of container we are using.
    * @param fieldID    ID of field we are getting.
    * @param idDataGroup
    *                   group ID to use for any CBO processing.
    * @param conditions reference to vector to store conditions in
    * 
    * @return highest SEVERITY for field
    */
   virtual SEVERITY doGetErrors( const GenericInterface* rpGICaller,
                                 const BFContainerId& idContainer,
                                 const BFFieldId& fieldID,
                                 const BFDataGroupId& idDataGroup,
                                 CONDITIONVECTOR& conditions ) const;

   /**
    * This method is used to implement subclass overrides for getField.  The business
    * process must determine where to locate the field.
    * Override this method and set appropriate flags via addFieldDetails,
    * if the derived class must process getField differently than this
    * base class does.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param idContainer
    *                   ID of container we are using.
    * @param fieldID    ID of field we are getting.
    * @param idDataGroup
    *                   group ID to use for CBO processing
    * @param strValueOut
    *                   A string reference where value is returned.
    * @param bFormatted Flag where true means get data formatted.
    */
   virtual void doGetField( const GenericInterface* rpGICaller,
                            const BFContainerId& idContainer,
                            const BFFieldId &fieldID,
                            const BFDataGroupId& idDataGroup,
                            DString &strValueOut,
                            bool bFormatted ) const;

   /**
    * This method should be overridden to get field attributes for
    * SUBCLASS_PROCESS fields.  The default implementation returns NULL which
    * will cause any control associated with the field to be read-only.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param idContainer
    *                   ID of container to find.
    * @param fieldID    ID of field to find.
    * @param idDataGroup
    *                   group id to use for any CBO processing
    * 
    * @return constant reference pointer to BFProperties or NULL if none
    */
   virtual const BFProperties *doGetFieldAttributes( const GenericInterface* rpGICaller,
                                                     const BFContainerId& idContainer,
                                                     const BFFieldId &fieldID,
                                                     const BFDataGroupId& idDataGroup );

   /**
    * This method should be overridden in order to register observers for
    * SUBCLASS_PROCESS fields.  The default implementation returns false
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param idContainer
    *                   ID of container to find.
    * @param fieldID    ID of field to find.
    * @param idDataGroup
    *                   group id to use for any CBO processing
    * @param rpObserver Observer reference
    * 
    * @return true if registration is succesfull, otherwise false
    */
   virtual bool doRegisterObserver( const GenericInterface* rpGICaller,
                                    const BFContainerId& idContainer,
                                    const BFFieldId &fieldID,
                                    const BFDataGroupId& idDataGroup,
                                    BFObserver &rpObserver );

   /**
    * This method should be overridden in order to deregister observers for
    * SUBCLASS_PROCESS fields.  The default implementation does nothing
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param idContainer
    *                   ID of container to find.
    * @param fieldID    ID of field to find.
    * @param idDataGroup
    *                   group id to use for any CBO processing
    * @param rpObserver Observer reference
    */
   virtual void doDeRegisterObserver( const GenericInterface* rpGICaller,
                                      const BFContainerId& idContainer,
                                      const BFFieldId &fieldID,
                                      const BFDataGroupId& idDataGroup,
                                      BFObserver &rpObserver )
   {}

   /**
    * This method is used to implement subclass overrides for
    * getKeyForNewListItem.  The derive process is responsible for working
    * with the appropriate CBO to add an item to the specified list and get the
    * key for the new item.  The default implementation will throw an
    * exception if the method is invoked.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param idList     ID of list in which we want a new item.
    * @param strListItemKeyOut
    *                   A string reference where key to new item is returned.
    */
   virtual void doGetKeyForNewListItem( const GenericInterface* rpGICaller,
                                        const BFContainerId& idList,
                                        DString &strListItemKeyOut );

   /**
    * This method is optional - override if subclass needs to implement any
    * additional initialization processing.
    * 
    * @return SEVERITY noting any error/warning conditions
    */
   virtual SEVERITY doInit()  // Should implementation be required?
   {
      return(NO_CONDITION);
   }

   /**
    * This method is optional but must be overridden in the subclasses to
    * support modeless child dialogs calling the modelessChildComplete method.
    * This method should not ever be called if the subclass has not overridden
    * it.  modelessChildComplete is used by the GenericInterfaceContainer to
    * tell the parent that the modeless child has been destroyed.
    * 
    * @param cmd    A reference to a command representing the object that has
    *               been destroyed.
    * 
    * @return true if this modeless object should end as well, false if not
    *         done yet.  When returning true, the calling modelessChildComplete method
    *         will call GenericInterfaceContainer::modelessDestroySelf to delete and
    *         remove this object from the container
    */
   virtual bool doModelessChildComplete( const Command &cmd );

   /**
    * This method is optional - override if subclass needs to be able to
    * relay the set focus to a child dialog.
    * Used to bring a modeless dialog (via parent process) to the top of the
    * window stack.  Note that if the process needs to change its state due
    * to a change in input parameters, then this would occur here and the
    * process would notify the child dialog of the need to refresh.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * 
    * @return true if successful, check conditions if false
    */
   virtual bool doModelessSetFocus( GenericInterface* rpGICaller );

   /**
    * This method may be overridden if the derived process needs a chance to
    * process prior to the normal ok (ok2) processing.
    * 
    * @param rpGICaller A reference pointer to the calling GenericInterface.
    * 
    * @return true if successful causing ok processing to continue or false to
    *         halt ok processing.
    */
   virtual bool doOk( GenericInterface* rpGICaller )
   {
      return(true);
   }

   /**
    * This method may be overridden if the derived process needs a chance to
    * process after normal ok (ok2) processing.
    * 
    * @param rpGICaller A reference pointer to the calling GenericInterface.
    * @param bSuccessFlag
    *                   true = Ok processing successful
    */
   virtual void doPostOk( GenericInterface* rpGICaller, bool bSuccessFlag )
   {}

   /**
    * Virtualized method that must be overridden in the subclasses to
    * support the process method.
    * 
    * @return an enum representing the return type
    */
   virtual E_COMMANDRETURN doProcess() = 0;

   /**
    * This method implements the base funcitonality for refresh processing.
    * Basically, this method will check all containers to see if update
    * level has changed. If so, refresh will be invoked on associated child
    * GUI's.
    * This should be overridden if the derived class needs something else.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param szOriginalCommand
    *                   A string literal representing the original command issuing the
    *                   refresh (which may provide a hint on whether this object needs to check for refresh).
    * 
    * @return true if successful, check conditions if false
    */
   virtual bool doRefresh( GenericInterface* rpGICaller, const I_CHAR *szOriginalCommand );

   /**
    * This method is optional - override if subclass needs to implement.
    * 
    * @param rpGICaller A reference pointer to the calling GenericInterface.
    * @param szMessage  A string literal of the message to send.
    * 
    * @return true if successful
    */
   virtual bool doSend( GenericInterface* rpGICaller,
                        const I_CHAR * szMessage )
   {
      return(false);
   }

   /**
    * Used to set bulk data in the specified container.  If the container is
    * repeatable (ie a list), the caller is responsible for positioning the
    * list.
    * This is the base implementation.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param idContainer
    *                   ID for the container object (often a CBO).
    * @param rpData     A const reference pointer to data object for the data.
    * 
    * @return SEVERITY noting any error/warning conditions
    */
   virtual SEVERITY setData( GenericInterface* rpGICaller,
                             const BFContainerId& idContainer,
                             const BFData *rpData );

   /**
    * This method is used to implement subclass overrides for setField.  The business
    * process must determine where to locate the field.
    * Override this method and set appropriate flags via addFieldDetails,
    * if the derived class must process setField differently than this
    * base class does.
    * 
    * @param rpGICaller A reference pointer to the calling object.
    * @param idContainer
    *                   ID of container we are using.
    * @param fieldID    ID of field we are getting.
    * @param idDataGroup
    *                   group ID to use for CBO processing
    * @param strValue   A string reference for the value of the field to be set.
    * @param bFormatted Flag where true means incoming data is formatted.
    * 
    * @return SEVERITY indicating any errors/warnings encountered.
    */
   virtual SEVERITY doSetField( const GenericInterface* rpGICaller,
                                const BFContainerId& idContainer,
                                const BFFieldId &fieldID,
                                const BFDataGroupId& idDataGroup,
                                const DString &strValue,
                                bool bFormatted );

   /**
    * This method is used to implement subclass overrides for validateAll
    * during ok2 processing.  The method implementation must not use a
    * MAKEFRAME, or should make sure all conditions are promoted to its frame
    * prior to returning.
    * 
    * @param rpWSD  WorkSessionDetails pointer
    * @param idDataGroup
    *               group ID to use for CBO processing
    * 
    * @return SEVERITY indicating any errors/warnings encountered.
    */
   virtual SEVERITY doValidateAll( BFAbstractCBO *rpWSD, const BFDataGroupId& idDataGroup );

   /**
    * This method returns the current CBO item for the specified container.
    * Exceptions will be thrown if the container is not found.
    * 
    * @param idContainer
    *               ID of container we are using.
    * @param idDataGroup
    *               group ID currently being used.
    * 
    * @return BFAbstractCBO pointer, NULL if none available.
    */
   BFAbstractCBO* getCBOItem( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup, const DString* pKey = NULL );

   /**
    * This method returns the current CBO list item for the specified container.
    * Exceptions will be thrown if the container is not found.
    * 
    * @param idContainer
    *               ID of container we are using.
    * @param idDataGroup
    *               group ID currently being used.
    * 
    * @return BFAbstractCBO pointer, NULL if none available.
    */
   BFAbstractCBO* getCBOList( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup, const DString* pKey = NULL );

   /**
    * This is a method which may be overridden by a subclass to set container
    * pointers on demand.  This method is invoked whenever an attempt is
    * about to be made to use a container that hasn't been set yet.  The
    * pointer returned will be used to set the container pointer.
    * 
    * @param idContainer
    *               ID of list to set pointer for.
    * @param idDataGroup
    *               group ID currently being used.
    * 
    * @return void pointer of list to use.
    */
   virtual void *getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup )
   { return(NULL); }

   /**
    * This method implements the base functionality for ok processing,
    * including committing all updated groups and submitting a transaction,
    * if required.  This may be overridden if the derived process needs more
    * than the base functionality.
    * 
    * The function setIgnoreWarningsOnOk2 influences how the base
    * functionality treats conditions with a severity of WARNING when
    * committing data groups and submitting transactions.
    * 
    * @param rpGICaller A reference pointer to the calling GenericInterface.
    *                   returns returns highest SEVERITY encountered, check conditions
    * 
    * @return Highest SEVERITY of all of the conditions currently on the frame.
    * @see #setIgnoreWarningsOnOk2
    */
   virtual SEVERITY ok2( GenericInterface* rpGICaller );

   /**
    * This method is used by derived classes to set/change the container to use
    * for all fields that are currently mapped to the container ID.
    * 
    * @param idContainer
    *               The container ID to set.
    * @param rpContainer
    *               The reference pointer to the new container to be substituted in.
    */
   void setContainer( const BFContainerId& idContainer, void *rpContainer );

   /**
    * This method is used ( by a derived process ) to filter a
    * container (CBO) based on stringKey
    * filter is a string made by sub strings separated by ";"
    * 
    * @param idContainer
    *               ID of container to be filtered
    * @param filter string containing the filter
    * 
    * @return true if the filter was set.
    */
   bool setKeyFilter( const BFContainerId& idContainer, const DString& filter );

   /**
    * This method is used ( by a derived process ) to retrieve the
    * stringKey filtering on a container (CBO)
    * filter is a string made by sub strings separated by ";"
    * 
    * @param idContainer
    *               ID of filtered container
    * @param filter reference to a string in which the filter will be stored
    */
   void getKeyFilter( const BFContainerId& idContainer, DString& filter );

   /**
    * This method is used ( by a derived process ) to remove the
    * stringKey filtering on a container (CBO)
    * 
    * @param idContainer
    *               ID of filtered container
    */
   void clearKeyFilter( const BFContainerId& idContainer ); 

   /**
    * This method is used ( by a derived process ) to filter a
    * container (CBO) based on data content
    * filter condition is a string made form subconditions like
    * fieldId=fieldValue, separated by ";"
    * 
    * @param idContainer
    *               ID of container to be filtered
    * @param filter string containing the filter
    * 
    * @return true if the filter was set.
    */
   bool setDataFilter( const BFContainerId& idContainer, const DString& filter );

   /**
    * This method is used ( by a derived process ) to retrieve the
    * data content filtering on a container (CBO)
    * filter condition is a string made form subconditions like
    * fieldId=fieldValue, separated by ";"
    * 
    * @param idContainer
    *               ID of filtered container
    * @param filter reference to a string in which the filter will be stored
    */
   void getDataFilter( const BFContainerId& idContainer, DString& filter );

   /**
    * This method is used ( by a derived process ) to clear out
    * data content filtering on a container (CBO)
    * 
    * @param idContainer
    *               ID of filtered container
    */
   void clearDataFilter( const BFContainerId& idContainer ); 

   /**
    * override to return true if you want to commit the data to the host group
    * only used in nasu and coa which are the special case
    * 
    * @return true if this process should commit its data to the host DataGroup (BF::HOST).
    *         false if this process should commit its data to the DataGroup of this process's parent process.
    */
   virtual bool setCommitDataGroupAsHost()
   {
      return(bfutil::isServerContext());
   };

private:

   // Class used as key to FIELDS map
   class FieldKey
   {
   public:
      BFContainerId _idContainer;
      BFFieldId _idField;

      FieldKey( const BFContainerId& idContainer, const BFFieldId &idField ) :
      _idContainer( idContainer ),
      _idField( idField )
      {}
   };
   // Class used for comparison of field key in map
   class less_FieldKey
   {
   public:
      bool operator() ( const FieldKey &a, const FieldKey &b ) const
      {
         if( a._idContainer != b._idContainer )
         {
            return(a._idContainer < b._idContainer);
         }
         else
         {
            return(a._idField < b._idField);
         }
      }
   };

   typedef std::map< BFContainerId, AbstractListDetails *, std::less< BFContainerId > > CONTAINERS;
   typedef std::vector< BFFieldId > DUPLICATES;
   typedef std::map< FieldKey, FieldDetails *, less_FieldKey > FIELDS;
#if _MSC_VER >= 1300
   typedef std::map< FieldKey, FieldDetails *, less_FieldKey >::const_iterator FIELDS_CONST_ITER;
#else
   typedef std::map< FieldKey, FieldDetails *, less_FieldKey >::iterator FIELDS_CONST_ITER;
#endif

   // Field Container Map maps Fields to Containers
   typedef std::map< BFFieldId, BFContainerId, std::less< BFFieldId > > FIELDCONTAINERMAP;
#if _MSC_VER >= 1300
   typedef std::map< BFFieldId, BFContainerId, std::less< BFFieldId > >::const_iterator FIELDCONTAINERMAP_CONST_ITER;
#else
   typedef std::map< BFFieldId, BFContainerId, std::less< BFFieldId > >::iterator FIELDCONTAINERMAP_CONST_ITER;
#endif

   CONTAINERS _containers;
   DUPLICATES _duplicateFieldIDs;
   FIELDS _fields;
   FIELDCONTAINERMAP _fieldContainerMap;

   AbstractListDetails &findContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup );

   FieldDetails*findField( BFContainerId idContainer, const BFFieldId &fieldID ) const;

   void getContainerPtr( AbstractListDetails &container, const BFContainerId& idContainer, const BFDataGroupId& idDataGroup );

   /**
     * Implementation to support the init method.
     * Subclasses should implement doInit to perform any initialization
     * required, including getting parameters from InterProcessData (they get
     * cleared after this call) and setting up cbos.
     * @return SEVERITY noting any error/warning conditions
     */
   virtual SEVERITY init2();
   void resetChildContainers( const BFContainerId& idContainer );
   bool setParentContainers( AbstractListDetails &container, const BFDataGroupId& idDataGroup );

   bool bIgnoreWarningsOnOk2_;
//CP20030526   /**
//CP20030526    * Flag which controls Ok2 processing.  If true this process will only execute validation code during Ok2()
//CP20030526    * 
//CP20030526    * @see #ok2
//CP20030526    */
//CP20030526   bool bValidateOnlyOnOk2_;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF Core/bfproc/AbstractProcess.hpp-arc  $
//
//   Rev 1.50   Oct 22 2004 08:57:26   PURDYECH
//PET910 - .NET Conversion Fixes
//
//   Rev 1.49   May 26 2003 14:24:10   PURDYECH
//The ActionTypeOnOk2 mess has been replaced with the ValidationControl BFExecutionContext mess.
//
//   Rev 1.48   May 24 2003 14:56:44   PURDYECH
//Added getItemErrors and getItemErrorState
//
//   Rev 1.47   May 01 2003 15:21:26   PURDYECH
//workSessionHasUpdates had inadvertent signature change.
//
//   Rev 1.46   Apr 24 2003 12:14:20   PURDYECH
//Documentation Cleanup
//
//   Rev 1.45   Apr 24 2003 10:53:14   PURDYECH
//Added class function emptyString() which returns a reference to the class member s_emptyString_
//
//   Rev 1.44   Apr 23 2003 14:21:16   PURDYECH
//Added class member s_empty_ so that empty strings are easily available.
// 
//    Rev 1.43   Feb 12 2003 14:11:38   PURDYECH
// ServerContext logic is now in bfutil namespace.
// 
//    Rev 1.42   Jan 14 2003 11:03:52   PURDYECH
// DataGroupid parentage knowledge
// 
//    Rev 1.41   Jan 06 2003 16:43:08   PURDYECH
// BFDataGroupId and BFContainerId changeover
// 
//    Rev 1.40   Nov 27 2002 15:04:24   PURDYECH
// Documentation Changes
// 
//    Rev 1.39   Nov 14 2002 10:48:56   SMITHDAV
// Sync-up from old source database.
// 
//    Rev 1.38   Oct 09 2002 17:40:48   PURDYECH
// New PVCS Database
// 
//    Rev 1.37   Sep 19 2002 09:28:14   IVESPAUL
// Adapted the transaction stats to write results using XML ElementWriter.  Moved ElementAttribute and ElementWriter to BFUtil.
//
//    Rev 1.36   Sep 02 2002 17:32:42   PURDYECH
// FieldDetail was storing a reference to a field instead of the field itself.
//
//    Rev 1.35   Aug 29 2002 12:51:12   SMITHDAV
// ClientLocale and typed field changes.
//
//    Rev 1.33   Jul 05 2002 08:49:46   PURDYECH
// Fixed include files
//
//    Rev 1.32   05 Jun 2002 13:55:16   SMITHDAV
// Fix grid refresh bug. Added trySetCurrentKey functions.
//
//    Rev 1.31   22 May 2002 18:08:42   PURDYECH
// BFData Implementation
//
//    Rev 1.30   22 Mar 2002 15:11:20   PURDYECH
// Removed compile-time "including..." message
// Use #pragma once as include guard
// Include files with lower-case only names
//
//    Rev 1.29   Jan 04 2002 15:09:54   ROSIORUC
// Added getCBOList method
//
//    Rev 1.28   04 Aug 2001 17:30:46   KOVACSRO
// For server context always commit to host.
//
//    Rev 1.27   26 Jul 2001 13:43:16   YINGZ
// fix reset, cancel problems
//
//    Rev 1.26   04 Jul 2001 15:16:52   YINGZ
// cleanup
//
//    Rev 1.25   29 Jun 2001 10:55:52   YINGZ
// add canCancel to support cancel machenism
//
//    Rev 1.24   15 May 2001 15:40:08   YINGZ
// data group id clean up
//
//    Rev 1.23   May 08 2001 11:18:48   FENGYONG
// Add name for API
//
//    Rev 1.22   03 May 2001 14:03:16   SMITHDAV
// Session management restructuring.
//
//    Rev 1.21   Apr 06 2001 12:06:46   YINGZ
// make changes to datagroup
//
//    Rev 1.20   Mar 27 2001 13:57:38   YINGZ
// add workSessionHasUpdates
//
//    Rev 1.19   Feb 28 2001 15:41:28   YINGZ
// make fireCrossEdit virtual and add parm lValidateGroup
//
//    Rev 1.18   Feb 06 2001 14:01:54   YINGZ
// add another version of setCurrentListItem for api use
//
//    Rev 1.17   Jan 09 2001 13:25:30   YINGZ
// delete setContainerValidationMode since it is not needed anymore
//
//    Rev 1.16   Dec 22 2000 13:53:26   YINGZ
// move setIgnoreWarningsOnOk2 to public for xml api use
//
//    Rev 1.15   Dec 21 2000 11:10:24   YINGZ
// add validate only
//
//    Rev 1.14   Dec 15 2000 13:44:44   YINGZ
// add getFieldsInContainer, still the better way 8))
//
//    Rev 1.13   Dec 15 2000 10:33:34   YINGZ
// remove getFieldsInContainer
//
//    Rev 1.12   Dec 13 2000 15:26:10   YINGZ
// add getFieldsInContainer for xml
//
//    Rev 1.11   Dec 13 2000 13:22:50   KOVACSRO
// Added isCurrentItemDummy()
//
//    Rev 1.10   Nov 27 2000 11:35:12   VASILEAD
// Added setIgnoreWarningsOnOk2() to give the process a chance to not launch ConfirmationProcess if we got warnings in the validation
//
//    Rev 1.9   Nov 08 2000 20:04:48   DT24433
// added name support for containers
//
//    Rev 1.8   16 Aug 2000 11:48:38   PURDYECH
// Added getAllErrors method to retrieve all errors for the caller, both field and object level.
//
//    Rev 1.7   Aug 15 2000 14:00:40   YINGZ
// multi locale support
//
//    Rev 1.6   Aug 02 2000 15:31:34   BUZILA
// "locale" changes
//
//    Rev 1.5   Jun 23 2000 12:46:02   DT24433
// changes to support setData
//
//    Rev 1.4   Mar 23 2000 16:23:46   BUZILA
// CBO filtering implemented
//
//    Rev 1.3   Mar 08 2000 16:21:42   YINGZ
// add isRepeatable
//
//    Rev 1.2   Mar 01 2000 17:20:38   BUZILA
// added doRegisterObserver and doDeRegister observer methods
//
//    Rev 1.1   Feb 15 2000 18:54:56   MCNABBGL
// changed comment format
//
//    Rev 1.0   Feb 15 2000 10:57:44   SMITHDAV
// Initial revision.
//
//    Rev 1.32   Jan 21 2000 07:19:16   DT24433
// changed comments for doGetFieldAttributes
//
//    Rev 1.31   Jan 19 2000 15:37:52   DT24433
// added getErrorState, doValidateAll
//
//    Rev 1.30   Jan 12 2000 19:01:12   DT24433
// added observer for CBO destruction
//
//    Rev 1.29   Jan 11 2000 11:31:16   DT24433
// changed to return bool for registerObserver
//
//    Rev 1.28   Jan 05 2000 17:55:02   DT24433
// added cross-edit & validation calls, removed read only group processing
//
//    Rev 1.27   Dec 22 1999 12:21:22   DT24433
// parm changed in register/deregister
//
//    Rev 1.26   Dec 21 1999 13:45:28   DT24433
// initial notification changes
//
//    Rev 1.25   Dec 17 1999 17:58:46   DT24433
// changes to OK2 for new confirmation model
//
//    Rev 1.24   Dec 09 1999 11:26:30   DT24433
// refresh support
//
//    Rev 1.23   Dec 08 1999 16:17:18   DT24433
// added isCurrentListItemNew & changed commit processing
//
//    Rev 1.22   Dec 07 1999 10:37:04   DT24433
// removed old doGet/SetField methods
//
//    Rev 1.21   Dec 03 1999 13:59:42   DT24433
// added support to start processes off of child data group
//
//    Rev 1.20   Dec 02 1999 10:10:00   DT24433
// removed ConfirmSave & setUpdateGroup
//
//    Rev 1.19   Dec 01 1999 10:39:08   BUZILA
// changes for metagroups
//
//    Rev 1.18   Nov 19 1999 17:33:02   DT24433
// added several doxxx methods and add group parm to doxxx methods
//
//    Rev 1.17   Nov 11 1999 08:53:04   DT24433
// changed getFieldAttributes interface
//
//    Rev 1.16   Nov 09 1999 16:55:36   DT24433
// group processing changes
//
//    Rev 1.15   Nov 05 1999 15:24:44   DT24433
// added getErrors
//
//    Rev 1.14   Nov 02 1999 12:46:32   DT24433
// added group to getPtrForContainer, getCBOItem, and findContainer
//
//    Rev 1.13   Oct 28 1999 16:45:36   DT24433
// added start of implementation for ok/cancel processing and commit method
//
//    Rev 1.12   Oct 28 1999 12:44:54   DT24433
// add/delete/reset & group processing
//
//    Rev 1.11   Oct 25 1999 10:30:52   DT24433
// changed return for getKeyForNewListItem
//
//    Rev 1.10   Oct 25 1999 10:00:32   DT24433
// changed interface for getKeyForNewListItem
//
//    Rev 1.9   21 Oct 1999 08:44:44   HSUCHIN
// Changes for better  support of getPtrForContainer and added getCBOItem.
//
//    Rev 1.8   Sep 17 1999 07:10:06   DT24433
// initial group processing code
//
//    Rev 1.7   Sep 01 1999 17:49:14   DT24433
// removed original doGetField/doSetField implementations
//
//    Rev 1.6   Aug 30 1999 18:08:12   DT24433
// added new dosetfield/dogetfield methods
//
//    Rev 1.5   Aug 26 1999 16:41:36   DT24433
// removed getFieldFromCurrentListItem
//
//    Rev 1.4   Aug 26 1999 11:11:10   DT24433
// removed old functionality
//
//    Rev 1.3   Aug 05 1999 15:22:50   DT24433
// altered functionality
//
//    Rev 1.2   Aug 03 1999 14:28:14   DT24433
// container changes
//
//    Rev 1.1   Jul 08 1999 10:03:20   SMITHDAV
// Modify revision history commaent format to old
// style comment -- I can't seem to get new style comments to work.
//

