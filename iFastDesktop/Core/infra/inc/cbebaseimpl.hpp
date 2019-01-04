#ifndef CBEBASEIMPL_HPP
#define CBEBASEIMPL_HPP

/** 
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1999 by DST Systems, Inc.
 */

/**@pkg DICBOCORE */ 

#ifndef INCLUDED_MAP
#include <map>
#define INCLUDED_MAP
#endif

#ifndef INCLUDED_VECTOR
#include <vector>
#define INCLUDED_VECTOR
#endif

#ifndef  DSTRING_HPP
#include "dstring.hpp"
#endif

#ifndef COMMONPORT_H
#include "commonport.h"
#endif

#ifndef COMMONPORT_H
#include "commonport.h"
#endif

#ifndef CONDITIONMANAGER_HPP
#include "conditionmanager.hpp"  
#endif

// Forward declarations
class CBOBase;
class Data;
class Updater;
class UpdatableListBase;

/**@#-*/
using namespace std;
/**@#+*/

// Import/Export resolution
#undef CBOBASE_LINKAGE
#ifdef DICBOCORE_DLL
    #define CBOBASE_LINKAGE CLASS_EXPORT
#else
    #define CBOBASE_LINKAGE CLASS_IMPORT
#endif

/**
 * A base (CBE - Common Business Event) class for
 * handling common business transactions.
 * 
 * The CBEBaseImpl class contains methods
 * used for field management and business data
 * gathering.
 * 
 * An instance of this class should contain either
 * a CBOBase pointer or an UpdatableListBase pointer
 * but not both.
 * 
 * CBEBaseImpl also will contain a collection of Data
 * objects that may or may not be filled with data for
 * an update.
 * 
 * Derived classes from CBEBase will need to either
 * set in a CBO or a Updatablelistbase derived class
 * upon initialization of the event. Also, in the
 * initialization step, the CBEBase derived class will
 * need to register one or more Data objects that
 * may be used for updates.
 *   
 * In the update process, CBEBase will iterate over
 * each of the registered Data objects and fill them
 * with data from the contained CBO or UpdatableList
 * data.  Before data gathering for an update can occur,
 * CBEBaseImpl will ask the contained CBO or UpdatableList
 * object if an update for the associated data object
 * should be built. CBEBaseImpl will then ask the
 * contained CBO or UpdatableList if it is in a valid
 * state.  And as the final step, CBEBase will get the
 * data from the contained CBO or UpdatableListBase
 * object.
 * 
 * The majority of these methods are considered pass-through
 * methods to methods of the same name in the contained CBO.
 * 
 * CBEBase is the interface class for CBEBaseImpl(implementation class)
 * 
 * The interface/implementation concept is known
 * as the "bridge" pattern or "handle/body" pattern
 * as found in the  Design Patterns(GOF95') book.
 * 
 * @see CBOBase
 * @see setDefaultCBO
 * @see setUpdateableList
 * @see registerView
 * @see buildUpdate
 */
class CBOBASE_LINKAGE CBEBaseImpl
{
   // public data structures and definitions
   public:
      enum VALIDATION_MODE { IMMEDIATE,
                             POSTPONED };

      enum ORIGIN
      {
         TELEPHONE_TRANSACTION,
         BACK_OFFICE_TRANSACTION
      };
                                 

   // public methods
   public:
      /** virtual Destructor */
      virtual ~CBEBaseImpl();

      /**
       * This method calls the containd CBO's method of the same name
       * which takes a "snapshot" of of a contained CBO
       * instanceFieldInfo for a potential rollback.
       * This method makes a full and complete copy of
       * anything related to instance fields. Any previous
       * checkpoint will be cleared.
       * 
       * @return true if successful / false on failure
       * @see rollbackFieldsToCheckpoint()
       */
      bool checkpointFields( void );

      /**
       * This method kicks of the update process for sending
       * data to the host.  It calls the following methods
       * to first check to see if there is any updated data
       * in the contained CBO or updatableList to send to
       * the host and then gather the data from the
       * contained CBO or updatableList and complete the
       * updates:
       * 
       * isUpdated
       * buildUpdate
       * 
       * @param updater A specific Updater object to use for getting the
       *                updated data to the host.
       * @param nUpdateStage
       *                A update stage is an integer value that specifies
       *                the order in which data will be gathered and
       *                thus sent to the host.
       *                For example. a Data object marked as a stage 1 update
       *                will be filled with data and thus submitted before any
       *                Data objects that are marked as stage 2 updates.
       *                All data goes to the host at the same time, but
       *                the stage 1 data will go before the stage 2 data.
       *                
       *                
       *                It defaults to a value of 1.
       * @return NO_CONDITION if successful
       * @see isUpdated
       * @see buildUpdate
       */
      virtual SEVERITY commitUpdate( Updater& updater, int nStage );

      /**
       * Get a pointer to the CBEBaseImpl derived class.
       * 
       * @return A CBEBaseImpl pointer.
       */
      CBEBaseImpl * getCBEBaseImpl( void );

      /**
       * Retrieves a details object( the contained CBO )
       * of a business event
       * 
       * @return A CBOBase reference
       */
      const CBOBase& getDetails() const;

      /**
       * This method calls the contained CBO's method of the
       * same name which populates a string with the
       * requested field's value if found.
       * 
       * @param strFieldTag
       *                 A unique string tag indentifier for the registered field
       *                 used to index into the instancefieldinfo.
       *                 The string tag indentifier for a field is set up in
       *                 the CLASS_FIELD_INFO.
       * @param strValue The user supplied string to hold the field value
       * @return NO_CONDITION if successful
       * @see CLASS_FIELD_INFO
       * @see setField
       */
      virtual SEVERITY getField( const DString& strFieldTag,
                             DString& strValue ) const;

      /**
       * Retrieve the number of Data objects
       * that have been registered with CBEBaseImpl
       * 
       * A Data object can be registered with CBEBaseImpl
       * by making a call to registerView from the init
       * method of a class that is derived from CBEBaseImpl.
       * 
       * @return an integer value of the number of Data objects
       *         registered with CBEBaseImpl
       * @see registerView
       */
      int getNumberTransactionDataObjects( void ) const;

      /**
       * This method is called by an EventUpdateOrder object.
       * 
       * It gets the number of update stages in a business event.
       * A transaction stage is an integer value that specifies
       * the order in which data will be gathered and
       * thus sent to the host.
       * For example. a Data object marked as a stage 1 update
       * will be filled with data and thus submitted before any
       * Data objects that are marked as stage 2 updates.
       * All data goes to the host at the same time, but
       * the stage 1 data will go before the stage 2 data.
       * 
       * You can specify a transaction stage for each
       * Data object that you register with CBEBaseImpl.
       * The registerView method will store off the
       * corresponding stage number with the passed in
       * Data object.
       * 
       * @return an integer value of the number of stages associated
       *         with the current business event
       * @see registerView
       */
      int getNumTransactionStages( void ) const;

      /**
       * Retrieve a single Data object
       * that has been registered with CBEBaseImpl
       * 
       * A Data object can be registered with CBEBaseImpl
       * by making a call to registerView from the init
       * method of a class that is derived from CBEBaseImpl.
       * 
       * @param index   an integer value of the contained Data object
       * @param outData a Data reference to be filled with data
       * @return true if successful
       *         false if failure
       * @see registerView
       */
      bool getTransactionDataObject( int index, Data& outData  ) const;

      /**
       * This method calls the contained CBO's method of the same name
       * which returns the contained CBO's validation mode IMMEDIATE or POSTPONED.
       * Validation mode can be set for all instances of an object(class level)
       * or on a instance by instance basis(object level).
       * If the validation mode is immediate, error conditions
       * will be returned immediately from a call to setField.
       * 
       * If the validation mode is postponed, all conditions will
       * be ignored at the time of a setField call.
       * This means the user intends to collect all conditions
       * at a later time by making a call to the validateAll()
       * method.
       * The methods that check for validation mode are:
       * setObject
       * _authorizedSetObject
       * setField
       * 
       * @return An enumeration of the validation mode of the object
       *         (0 = IMMEDIATE or 1 = POSTPONED)
       * @see VALIDATION_MODE
       * @see setObject
       * @see _authorizedSetObject
       * @see setField
       */
      VALIDATION_MODE getValidationMode( void ) const;

      /**
       * A Pure virtual method
       * This method must be implemented in a derived class.
       * 
       * This method should be called from the update
       * method that is implemented in a CBEBaseImpl
       * derived class.
       * 
       * @return true if and operator is authorized to perform the
       *         transaction.
       *         
       *         false if not authorized
       * @see update
       */
      virtual bool isAuthorized( void ) const = 0;

      /**
       * This method calls the contained CBO's method of the same name
       * which checks to see if an instance field is marked with INST_FLD_READ_ONLY.
       * If a instance field is marked as INST_FLD_READ_ONLY
       * then the field cannot be set from the user interface
       * without generating a "field read only" error message.
       * A read only field can be set by using one of the _authorizedSet
       * methods from within a derived class.
       * 
       * Fields can initially start out with INST_FLD_READ_ONLY marked
       * based on the field entry in the CLASS_FIELD_INFO.
       * (Use CLASS_FLD_READ_ONLY in the CLASS_FIELD_INFO field entry.
       * 
       * The INST_FLD_READ_ONLY flag can be turned off and on
       * many times during the lifetime of an object.
       * 
       * @param strFieldTag
       *               A unique string tag indentifier for the registered field
       *               used to index into the instancefieldinfo.
       *               The string tag indentifier for a field is set up in
       *               the CLASS_FIELD_INFO.
       * @return true if field is marked with INST_FLD_READ_ONLY
       *         false if field is not marked as INST_FLD_READ_ONLY
       * @see CLASS_FIELD_INFO
       * @see FIELD_FLAG
       * @see setFieldFlag
       * @see clearFieldFlag
       * @see isFieldFlagSet
       */
      bool isFieldReadOnly( const DString& strFieldTag ) const;

      /**
       * This method calls the contained CBO's method of the same name
       * which checks to see if field has been updated
       * (determined by checking the INST_FLD_UPDATED field flag ).
       * 
       * If an instance field is marked as INST_FLD_UPDATED
       * then the field has been changed from it's original value.
       * 
       * Fields initially start out with the INST_FLD_UPDATED
       * flag turned off.
       * 
       * The methods that will cause this flag to get turn on
       * are:
       * 
       * setField <-- only if all validations pass or in postponed validation mode
       * applyActiveGroup
       * 
       * The INST_FLD_UPDATED flag can be turned off and on
       * many times during the lifetime of an object.
       * 
       * @param strFieldTag
       *               A unique string tag indentifier for the registered field
       *               used to index into the instancefieldinfo.
       *               The string tag indentifier for a field is set up in
       *               the CLASS_FIELD_INFO.
       * @return true if field is marked with INST_FLD_UPDATED
       *         false if field is not marked as INST_FLD_UPDATED
       * @see setField
       * @see applyActiveGroup
       * @see setFieldFlag
       * @see clearFieldFlag
       * @see isFieldFlagSet
       */
      bool isFieldUpdated( const DString& strFieldTag ) const;

      /**
       * This method checks to see if atleast one Data object
       * has been registered with CBEBaseImpl.
       * 
       * A Data object can be registered with CBEBaseImpl
       * by making a call to registerView from the init
       * method of a class that is derived from CBEBaseImpl.
       * 
       * @return true if a Data object has been registered
       *         false if not
       * @see registerView
       */
      virtual bool isInitialized( void ) const;

      /**
       * This a method specific to TA2000.
       * It is called by TA2000WorkOrder.
       * 
       * A SPOT transaction is considered a
       * financial transaction which uses
       * the J360p0 COBOL subroutine for updates
       * to the host.  A non-financial transaction
       * will use the H260p0 COBOL subroutine
       * for updates to the host. The J360p0 is
       * the new updater routine. The H260p0 is
       * the old updater routine. 
       * 
       * @return true if the business event uses the new updater
       *         routine
       *         false if the business event uses the old updater
       *         routine
       */
      virtual bool isSPOTTransaction () const;

      /**
       * This method calls the contained CBO's method of the same name
       * which should be implemented in a CBOBaseImpl
       * derived class.
       * 
       * This method is part of rework functionality
       * implemented in EventUpdateOrder.
       * 
       * If an event(CBE) is removed from an
       * EventUpdateOrder notification can be sent
       * to any contained CBOs associated with the
       * event.
       * 
       * @return NO_CONDITION if successful
       * @see notifyOnCommit
       * @see notifyOnUpdate
       * @see EventUpdateOrder
       * @see Updater
       */
      virtual SEVERITY notifyOnBackout();

      /**
       * This method calls the contained CBO's method of the same name
       * which should be implemented in a CBOBaseImpl
       * derived class.
       * 
       * This method is part of rework functionality
       * implemented in EventUpdateOrder.
       * 
       * If the business data contained within a CBE
       * is committed(sent to the host) from an
       * EventUpdateOrder, notification can be sent
       * to any contained CBOs associated with the
       * common business event.
       * 
       * @see notifyOnUpdate
       * @see notifyOnBackout
       * @see EventUpdateOrder
       * @see Updater
       */
      virtual void notifyOnCommit();

      /**
       * This method calls the contained CBO's method of the same name
       * which should be implemented in a CBOBaseImpl
       * derived class.
       * 
       * This method is part of rework functionality
       * implemented in EventUpdateOrder.
       * 
       * If the business data contained within a CBE
       * has been collected in an Updater object
       * but not committed(sent to the host) from an
       * EventUpdateOrder, notification can be sent
       * to any contained CBOs associated with the
       * common business event.
       * 
       * @return NO_CONDITION if successful
       * @see notifyOnCommit
       * @see notifyOnBackout
       * @see EventUpdateOrder
       * @see Updater
       */
      virtual SEVERITY notifyOnUpdate();

      /** Assignment operator */
      CBEBaseImpl& operator=( const CBEBaseImpl& copy );

      /**
       * This method calls the contained CBO's method of the same name
       * which should be implemented in a CBOBaseImpl
       * derived class.
       * 
       * CBOBaseImpl will only increment the updateLevel
       * of the current object.
       * 
       * This method is usually overridden in the derived
       * class to implement code that will grab the latest
       * data for the instancefieldinfo.  The refresh is
       * usually called after updates to the host have
       * occurred.
       * 
       * @return NO_CONDITION if successful
       * @see getUpdateLevel
       */
      virtual SEVERITY refresh( );

      /**
       * This method calls the contained CBO's method of the same name
       * which resets the specified field to its default value(if one exists)
       * and resets its corresponding object state flags to
       * the original values.
       * 
       * The reset is based on the values contained in
       * the CLASS_FIELD_INFO.
       * 
       * @param strFieldTag
       *               A unique string tag indentifier for the registered field
       *               used to index into the instancefieldinfo.
       *               The string tag indentifier for a field is set up in
       *               the CLASS_FIELD_INFO.
       * @return true for successs
       *         false for failure
       * @see CLASS_FIELD_INFO
       * @see setField
       * @see getField
       */
      bool resetField( const DString &strFieldTag);

      /**
       * This method calls the contained CBO's method of the same name
       * which attempts to roll back the instancefieldinfo to the previous "snapshot"
       * taken by calling the checkpointFields method.
       * This removes the current instancefieldinfo
       * from existance.
       * 
       * @return true for successs
       *         false for failure
       * @see checkpointFields
       */
      bool rollbackFieldsToCheckpoint( void );

      /**
       * This method calls the contained CBO's method of the same name
       * which sets the specified instance field with the
       * supplied string value. This method will call
       * another setField overload to actually perform
       * the validations and storage. It needs to figure
       * out the subclass id we are currently working with
       * first.
       * 
       * @param strFieldTag
       *                 A unique string tag indentifier for the registered field
       *                 used to index into the instancefieldinfo.
       *                 The string tag indentifier for a field is set up in
       *                 the CLASS_FIELD_INFO.
       * @param strValue A string value that will be validated and stored
       * @return NO_CONDITION if successful
       * @see getField
       * @see validate
       * @see resetField
       */
      virtual SEVERITY setField( const DString& strFieldTag,
                             const DString& strValue );

      /**
       * This method calls the contained CBO's method of the same name
       * which sets the object's validation mode to IMMEDIATE or POSTPONED.
       * Validation mode can be set for all instances of an object(class level)
       * or on a instance by instance basis(object level).
       * 
       * If an objects's validation mode is set to IMMEDIATE,
       * then any "set" method that is called on this object
       * will generate a condition and return it immediately
       * to the user if the data being set is invalid.
       * 
       * If an objects's validation mode is set to POSTPONED,
       * then any data can be set into the object whether the
       * data is invalid or not.  The validateAll method or
       * the validate method should be called at a later
       * time to kick off any validations needed. The
       * only field validations performed by CBOBaseImpl
       * are the read only and required checks.
       * 
       * The methods that check the validation mode are:
       * setObject
       * _authorizedSetObject
       * setField
       * 
       * @param validationMode
       *               An enumeration stating which mode is needed for
       *               this object.  Valid values are IMMEDIATE or POSTPONED
       * @see VALIDATION_MODE
       * @see getValidationMode
       * @see setObject
       * @see _authorizedSetObject
       * @see setField
       * @see validateAll
       * @see validate
       */
      void setValidationMode( VALIDATION_MODE validationMode );

      /**
       * A Pure virtual method
       * This method must be implemented in a derived class.
       * This method is called by an EventUpdateOrder object.
       * 
       * Use this method as a place to call an isAuthorized
       * implementation or perform any other security checks
       * needed.
       * 
       * Also place a  call to the CBEBaseImpl commitUpdate method
       * to kick of the data gathering and update process.
       * 
       * @param updater A Updater object to hold the Data that is
       *                gathered and to be used for updating the host
       * @param nUpdateStage
       *                A update stage is an integer value that specifies
       *                the order in which data will be gathered and
       *                thus sent to the host.
       *                For example. a Data object marked as a stage 1 update
       *                will be filled with data and thus submitted before any
       *                Data objects that are marked as stage 2 updates.
       *                All data goes to the host at the same time, but
       *                the stage 1 data will go before the stage 2 data.
       *                
       *                
       *                It defaults to a value of 1.
       * @return NO_CONDITION if successful
       * @see commitUpdate
       * @see isAuthorized
       */
      virtual SEVERITY update( Updater& updater, int nUpdateStage ) = 0;

      /**
       * This method calls the contained CBO's method of the same name
       * which attempts to validate the entire object and
       * return a severity designating the state of
       * this object.
       * 
       * Contained(aggregate) objects are also validated.
       * 
       * This method will check ALL fields and objects
       * adding conditions for each invalid item.
       * If an item (field or object) is not in a
       * valid state, an attempt to validate it will occur.
       * 
       * This method will be called by the CBOBase
       * validateAll method or it can be called directly
       * from a derived class.
       * 
       * @return NO_CONDITION if successful
       * @see performIsValidForUpdateEdits
       * @see setValidationMode
       * @see setField
       * @see setObject
       * @see _authorizedSetObject
       */
      virtual SEVERITY validateAll( void );

      /**
       * This method calls the contained CBO's method of the same name
       * which attempts to cross-validate two or more
       * fields.  It will kick off a cross-field validator
       * that is defined in the derived class.
       * 
       * Call this method after setting values for
       * a related group of fields.
       * 
       * Or let validateAll/validate kick off the
       * cross-field validator for you.
       * 
       * @param strFieldTag
       *               A unique string tag indentifier for the registered field
       *               used to index into the instancefieldinfo.
       *               The string tag indentifier for a field is set up in
       *               the CLASS_FIELD_INFO.
       * @return NO_CONDTION if successful
       * @see setField
       * @see setData
       */
      virtual SEVERITY validateField( const DString& strFieldTag );

   
   // protected data structures and definitions
   protected:


   // protected methods
   protected:
       
      CBEBaseImpl( VALIDATION_MODE validationMode=IMMEDIATE );

      /**
       * This method performs the work for gathering data
       * from the contained CBO or the contained UpdatableList.
       * For this method to work a call to one of the following methods
       * should already have been made from a derive
       * object's init() method:
       * 
       * setDefaultCBO
       * setUpdateableList
       * 
       * For each Data object that has been registered the
       * following methods are called as a part of the
       * data gathering process:
       * 
       * For the contained CBO
       * 1. shouldUpdateBeBuilt - if this method call
       *    returns false, then the Data object in question
       *    will not be filled with business data
       * 2. performIsValidForUpdateEdits - if this method call
       *    returns SEVERE_ERROR, then the Data object in question
       *    will not be filled with business data and the
       *    condition messages will be returned.
       * 3. getData or getContainedDetailUpdates - this
       *    method will fill the Data object in question
       *    with the business data contained in a CBO.
       * 
       * For the contained UpdatableList
       * these methods will be called for each
       * position in the list
       * 1. shouldUpdateBeBuilt - if this method call
       *    returns false, then the Data object in question
       *    will not be filled with business data
       * 2. performIsValidForUpdateEdits - if this method call
       *    returns SEVERE_ERROR, then the Data object in question
       *    will not be filled with business data and the
       *    condition messages will be returned.
       * 3. getData - this
       *    method will fill the Data object in question
       *    with the business data contained in a CBO.
       * 
       * The above methods need to be implemented in
       * a derived class from CBOBase/CBOBaseImpl
       * or UpdatableListBase/UpdatableListBaseImpl.
       * 
       * A Data object can be registered with CBEBaseImpl
       * by making a call to registerView from the init
       * method of a class that is derived from CBEBaseImpl.
       * 
       * @param updater A Updater object to hold the Data that is
       *                gathered and to be used for updating the host
       * @param nStage  A update stage is an integer value that specifies
       *                the order in which data will be gathered and
       *                thus sent to the host.
       *                For example. a Data object marked as a stage 1 update
       *                will be filled with data and thus submitted before any
       *                Data objects that are marked as stage 2 updates.
       *                All data goes to the host at the same time, but
       *                the stage 1 data will go before the stage 2 data.
       * @return NO_CONDITION if successful
       * @see registerView
       * @see setDefaultCBO
       * @see setUpdateableList
       */
      virtual SEVERITY buildUpdate( Updater& updater, int nStage );

      /**
       * This method  gets the current transaction stage for a business event.
       * A transaction stage is an integer value that specifies
       * the order in which data will be gathered and
       * thus sent to the host.
       * For example. a Data object marked as a stage 1 update
       * will be filled with data and thus submitted before any
       * Data objects that are marked as stage 2 updates.
       * All data goes to the host at the same time, but
       * the stage 1 data will go before the stage 2 data.
       * 
       * You can specfiy a transaction stage for each
       * Data object that you register with CBEBaseImpl.
       * The registerView method will store off the
       * corresponding stage number with the passed in
       * Data object.
       * 
       * @param nView  an integer value of the index of a registered
       *               Data object
       * @return an integer value of the transaction stage
       * @see registerView
       * @see setNumTransactionStages
       * @see getNumTransactionStages
       */
      int getTransactionStage( int nView );
      
      /**
       * This method gets the string label that has been
       * registered with a Data object.
       * 
       * @param nView  an integer value of the index of a registered
       *               Data object
       * @return a string value of the label for a registered Data
       *         object
       * @see registerView
       */
      DString getViewDataLabel( int nView );
      
      /**
       * A utility method to check if the registered Data
       * object will need to be flattend out used as a
       * parameter for the Updater object addData method
       * that takes a string.
       * 
       * @param nView  an integer value of the index of a registered
       *               Data object
       * @return true if using the addData method that takes a string
       *         false if using the addData method that takes a Data
       *         object
       * @see registerView
       */
      bool isAddViewUsingString( int nView );
      
      /**
       * This method calls the containd CBO's or List's method of the same name
       * which is the start of the update proccess.  CBEBaseImpl
       * must call this method to see if there are any updates
       * to apply to the host.  If there are no updates to
       * apply then he will not continue to build any
       * transactions.
       * 
       * CBOBaseImpl determines if the object has been updated by
       * performing the following steps.
       * 
       * 1.  Spin through the instancefieldinfo
       * checking if the INST_FLD_UPDATED flag is on
       * for any field.
       * 
       * 2.  Spin through the instanceobjectinfo
       * checking if the INST_OBJ_UPDATED or the
       * INST_OBJ_DELETED flag is on for any object.
       * 
       * 3.  Call the isUpdated method on any contained
       * object(s) if the pointer(s) exist.
       * 
       * @return true if the object or contained objects
       *         have been updated
       *         false if the objects or contained objects
       *         have not been updated
       * @see setField
       * @see setObject
       * @see deleteObject
       */
      bool isUpdated( void ) const;

      /**
       * Use this method to register a Data object with
       * CBEBaseImpl.  This method should be called from
       * the init() method of a derived class.  This method
       * will also mark a CBEBaseImpl derived object as
       * being initialized.
       * 
       * You may call this method multiple times to 
       * register multiple Data objects for a business event.
       * 
       * The data will be gathered and thus sent to the
       * host based on the ordering of your calls to
       * the registerView() method.
       * 
       * If you want a different ordering for the data
       * gathering, then pass in a transaction stage
       * value for each Data object that you register
       * with CBEBaseImpl.
       * 
       * @param strView  The name of the .vw or .req file to use for mapping
       *                 the Data object.
       * @param strLabel A string value that is an arbitrary name
       *                 that describes the data that will be updated
       *                 to the host.
       * @param nTransactionStage
       *                 A transaction stage is an integer value that specifies
       *                 the order in which data will be gathered and
       *                 thus sent to the host.
       *                 For example. a Data object marked as a stage 1 update
       *                 will be filled with data and thus submitted before any
       *                 Data objects that are marked as stage 2 updates.
       *                 All data goes to the host at the same time, but
       *                 the stage 1 data will go before the stage 2 data.
       *                 
       *                 
       *                 It defaults to a value of 1.
       * @param bAddViewUsingString
       *                 a boolean value used to specify which Updater object
       *                 addData method to use.
       *                 
       *                 if true the addData method that takes a string will
       *                 be used to store the business data
       *                 
       *                 if false the addData method that takes a Data
       *                 object will be used to store the business data
       *                 
       *                 it defaults to false
       * @param bGetContainedDetailUpdates
       *                 a boolean value to specify if the corresponding
       *                 Data object should be filled with data by
       *                 making a call to the getContainedDetailUpdates
       *                 method that is implemented in a CBOBase/CBOBaseImpl
       *                 derived classs.
       *                 
       *                 If true the getContainedDetailUpdates method will
       *                 be called instead of the regular getData method.
       *                 
       *                 If false the getContainedDetailUpdates method will
       *                 not be called. The regular getData method will
       *                 be called.
       *                 
       *                 It defaults to false.
       * @param bBuildBeforeImage
       *                 A boolean value to specify if the corresponding
       *                 Data object should be built with it's corresponding
       *                 before image that is contained in a CBO.  This
       *                 flag is set only for a contained UpdatableList.
       *                 
       *                 The before image data will be gathered before the
       *                 after image data
       *                 
       *                 It defaults to false.
       * @see buildUpdate
       * @see setNumTransactionStages
       * @see getNumTransactionStages
       * @see getTransactionStage
       */
      void registerView( const DString& strView,
                         const DString& strLabel = I_(""),
                         int nTransactionStage = 1,
                         bool bAddViewUsingString = false,
                         bool bGetContainedDetailUpdates = false,
                         bool bBuildBeforeImage = false );

      /**
       * Set a CBO into CBEBaseImpl from a derived class.
       * Call this method from the init() method of a
       * derived class.
       * 
       * 
       * CBEBaseImpl will not delete the pointer upon
       * destruction.
       * 
       * @param pDefaultCBO
       *               A pointer to a CBO that will be used for
       *               gathering data for updates to the host.
       * @see setUpdateableList
       * @see buildUpdate
       */
      void setDefaultCBO( CBOBase * pDefaultCBO );
      
      /**
       * Sets the initialized flag to true or false
       * Use this method if deferring the registerView
       * method calls to a later time. ie you are not
       * calling the registerView method from the init()
       * method in the derived class.
       * 
       * @param fInitialized
       *               a boolean value
       * @see registerView
       */
      void setInitialized( bool fInitialized );
   
      /**
       * This method sets the number of update stages in a business event.
       * A transaction stage is an integer value that specifies
       * the order in which data will be gathered and
       * thus sent to the host.
       * For example. a Data object marked as a stage 1 update
       * will be filled with data and thus submitted before any
       * Data objects that are marked as stage 2 updates.
       * All data goes to the host at the same time, but
       * the stage 1 data will go before the stage 2 data.
       * 
       * You can specify a transaction stage for each
       * Data object that you register with CBEBaseImpl.
       * The registerView method will store off the
       * corresponding stage number with the passed in
       * Data object.
       * 
       * @param numStages an integer value of the number of stages associated
       *                  with the current business event
       * @return true if successful
       *         false if failure
       * @see getNumTransactionStages
       * @see getTransactionStage
       */
      bool setNumTransactionStages( int numStages );
      
      /**
       * Set a UpdatableListBase derived object
       * into CBEBaseImpl from a derived class.
       * Call this method from the init() method of a
       * derived class.
       * 
       * 
       * CBEBaseImpl will not delete the pointer upon
       * destruction.
       * 
       * @param pUpdateableList
       *               A pointer to an UpdatableListBase derived object
       *               that will be used for gathering data for updates
       *               to the host.
       * @see setDefaultCBO
       * @see buildUpdate
       */
      void setUpdatableList( UpdatableListBase * pUpdatableList );


   // private methods
   private:


   // private data
   private:
      VALIDATION_MODE        _validationMode;
      CBOBase           * _pDefaultCBO;
      UpdatableListBase * _pUpdatableList;
      vector< Data * > _vecDataPointer;
      vector< DString > _vecViewLabel;
      vector< int >    _vecTransactionStage;
      vector< bool >   _vecAddViewUsingString;
      vector< bool >   _vecGetContainedDetailUpdates;
      vector< bool >   _vecBuildBeforeImage;
      int              _nViews;
      bool             _fIsInitialized;
      int              _numTransactionStages;
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
// $Log:   Y:/VCS/iFastAWD/inc/cbebaseimpl.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:30:12   kovacsro
//Initial revision.
// 
//    Rev 1.7   28 Nov 2001 12:41:34   dt14177
// fixed linkage define
// 
//    Rev 1.6   Dec 28 2000 18:16:18   dt39990
// Added more documentation and 
// organized methods in alphabetical listing
// 
//    Rev 1.5   Dec 31 1999 06:27:36   DT29758
// Minor Edits to Java-Doc comments
// 
//    Rev 1.3   Dec 06 1999 10:21:38   DT29758
// added ccdoc code tag directives for using 
// namespaces
// 
//    Rev 1.2   Dec 02 1999 09:10:06   DT29758
// added ccdoc style comments and
// corrected spelling of  _pUdatableListBase
// attribute
// 
// 
//    Rev 1.1   Nov 11 1999 16:31:10   DT29758
// added unicode support and utilization of
// indexes for data object fields
// 
//    Rev 1.0.1.0   Jul 15 1999 18:30:34   DT22388
// Removed the pure vitual mechanism
// from the isSPOTTransaction() method.
// Added method isSPOTTrasaction()
// as a pseudo-virtual method in the .cpp
// 
//    Rev 1.0   Jun 21 1999 17:06:54   DT22388
//  
// 
//    Rev 1.8   Jan 28 1999 14:39:32   DT22388
// Added new functionality for using
// updatablelist with events.  An even
// can now have either a default CBO or
// an updatablelist but not both. Added
// code to the buildUpdate() method to 
// walk through the list and build an update
// for any updated item in the list.
// 
// 
// 
//    Rev 1.7   Jan 14 1999 12:50:02   DT21815
// Changed #include file names to lower case.
// 
//    Rev 1.6   Jan 07 1999 09:18:56   DMAL
// added the methods, notifyonbackout, notifiyonupdate,
// and notifyoncommit.  All code changes were 
// made for the 3.4.0.0 code sync up.
//
//    Rev 1.5   Sep 22 1998 11:20:16   dt22388
// Added method getContainedDetailUpdates()
// for financial events that contain a list of CBOs
// used for updates.
// 
//    Rev 1.4   Sep 18 1998 12:14:32   dt22388
// Added get methods for data set in the
// registerview method.  These methods
// are used when overriding the buildupdate method
// in a derived class.
// 
//    Rev 1.3   Sep 17 1998 16:08:52   djoo
// Added method setInitialized.  Removed data
// forward declare and added #include.
// 
//    Rev 1.2   Jul 31 1998 08:33:58   dt22388
// Added a new parameter to the registerView()
// method.  bAddViewUsingString will allow views
// to be added to the update buffer bypassing the updater
// objects hard coded view headers.  A call to the
// addView() method using a string instead of a data object
// will be made.
// 
// 
//    Rev 1.1   Jul 30 1998 14:22:36   djoo
// Made getNumTransactionStages const.
// 
//    Rev 1.0   29 Jul 1998 23:58:08   dt14596
// DLMG New Archives for TA2000NTDT
// 
//    Rev 1.17   Mar 25 1998 11:28:06   djoo
// Added method resetField.
// 
//    Rev 1.16   Mar 03 1998 12:23:50   djoo
// Removed method clearUpdatedLabels and addUpdatedLabel.
// Renamed refreshUpdatedCBOs to refresh.
// 
//    Rev 1.15   Feb 27 1998 13:33:12   djoo
// Added methods clearUpdatedLabels() and
// addUpdatedLabel.
// 
//    Rev 1.14   Feb 19 1998 11:08:42   djoo
// Added methods isFieldReadOnly and getDetails.
// 
//    Rev 1.13   Feb 09 1998 12:13:02   djoo
// Added support for refreshing CBOs.
// Added method refreshUpdatedCBOs.
// 
//    Rev 1.12   Jan 17 1998 11:29:50   djoo
// Added support for stages during transactions.
// Added method getNumTransactionStages.
// Added method setNumTransactionStages.
// 
//    Rev 1.11   Dec 09 1997 08:41:52   djoo
// Added methods isFieldUpdated, checkpointFields & rollbackFieldsToCheckpoint.
// 
//    Rev 1.10   Dec 01 1997 16:44:44   djoo
//  
// 
//    Rev 1.9   Nov 20 1997 13:44:00   djoo
// Added validateField method that passes thru to defaultCBO (details).
// 
//    Rev 1.8   Nov 11 1997 08:14:46   djoo
// Added redundant include guards, dll import/export protection and removed extraneous
// code dealing with the vector of cbos.
// 
//    Rev 1.7   Sep 04 1997 12:42:00   djoo
// Added assert macros and enhancements for retrieving data objects.
// 
//    Rev 1.6   Sep 02 1997 16:06:22   djoo
// Intermediate Check-in for CBO8. (Condition Manager enhancements)
// 
//    Rev 1.5   Aug 26 1997 12:50:16   djoo
// Initial SEVERITY enhancements.
// 
//    Rev 1.4   16 Aug 1997 12:01:34   dmal
//  
// 
//    Rev 1.3   11 Aug 1997 09:55:10   dlkt
// Added init method for initialization.
// 
//    Rev 1.2   Jul 10 1997 15:40:28   DPQD
// Added header and revision control comment blocks.
// 
// Removed methods for ErrorList and ErrorList related instance variables.
//
//


#endif


