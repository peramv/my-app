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


#ifndef COMMONPORT_H
#include "commonport.h"
#define COMMONPORT_H
#endif

public:
   using $ParentImplClass$::getField;
   using $ParentImplClass$::setField;
   using $ParentImplClass$::isFieldGroupFlagSet;
   using $ParentImplClass$::isObjectGroupFlagSet;
   using $ParentImplClass$::setObject;
   using $ParentImplClass$::getObject;
   using $ParentImplClass$::getConstObject;
   using $ParentImplClass$::resetField;
   using $ParentImplClass$::isOn;
   using $ParentImplClass$::isOff;
   using $ParentImplClass$::validate;

   // Field validation methods
   virtual SEVERITY validate( unsigned short usSubclassID,
                              int nFieldID,
                              bool bValidatorCallOnly=false );

   virtual SEVERITY validate( unsigned short usSubclassID,
                              int nFieldID,
                              const DString& strValue,
                              bool fRemoveFormat = true );
   
   SEVERITY validate( FIELD fieldID );
   virtual SEVERITY validate( FIELD fieldID,
                              const DString& strValue,
                              bool fRemoveFormat = true );
   
   // Object validation methods
   virtual SEVERITY validateObject( unsigned short usSubclassID,
                                    int nObjectID );
   virtual SEVERITY validateObject( unsigned short usSubclassID,
                                    int nObjectID,
                                    const CBOBase * pObject );
   SEVERITY validateObject( OBJECT objectID );
   SEVERITY validateObject( OBJECT objectID,
                        const CBOBase * pObject );



   SEVERITY setField( FIELD fieldID, const DString& strValue );
   SEVERITY setField( FIELD fieldID, const MathString& mstrFieldValue );
   SEVERITY setObject( OBJECT objectID,
                       CBOBase * pObject,
                       bool fDeleteOnFailure = false );

   SEVERITY deleteObject( OBJECT objectID );
   bool isObjectDeleted( OBJECT objectID ) const;

   bool doesOwnObject( OBJECT objectID ) const;

   DString getField( FIELD fieldID, bool fFormattedReturn ) const;
   SEVERITY getField( FIELD fieldID, DString& strValue, bool fFormattedReturn = false ) const;
   SEVERITY getField( FIELD fieldID, MathString& mstrFieldValue ) const;
   CBOBase * getObject( OBJECT objectID );
   SEVERITY getObject( OBJECT objectID, CBOBase& cboObject );
   const CBOBase * getConstObject( OBJECT objectID ) const;
   DString getFieldTag( FIELD fieldID ) const;
   int getMaxLength( FIELD fieldID ) const;
   bool isRequired( FIELD fieldID ) const;
   bool isReadOnly( FIELD fieldID ) const;
   static void getFieldTag( FIELD fieldID, DString& strFieldTag );
   static void getMaxLength( FIELD fieldID, int& nLength );
   static void checkRequired( FIELD fieldID, bool& fRequired );
   static void checkReadOnly( FIELD fieldID, bool& fReadOnly );
   bool isValidType( OBJECT objectID, CBOBase * pObject ) const;
   bool isValidContainedObjectDerivation( OBJECT objectID, CBOBase * pObject ) const;
   virtual bool isValidContainedObjectDerivation( unsigned short usSubclassID,
                                                  int nObjectID,
                                                  CBOBase * pObject ) const;
   bool isFieldGroupFlagSet( unsigned long ulGroupFlag ) const;
   bool isFieldFlagSet( CBOBaseImpl::FIELD_FLAG fieldFlag,
                        FIELD fieldId ) const;
   bool isObjectGroupFlagSet( unsigned long ulGroupFlag ) const;
   bool isObjectFlagSet( CBOBaseImpl::OBJECT_FLAG objectFlag,
                         OBJECT objectId ) const;

   // Static method to give out keys at a class level, starts with @1 and increments the
   // numeric portion for each call.
   static void getNextNewKey( DString &strKey );

   // Static method to reset the key generator start at @1.
   static void resetNewKey( );

   bool isFieldUpdated( FIELD fieldId ) const;

   bool resetField( FIELD nFieldId );

   bool isOn( FIELD fieldID ) const;
   bool isOff( FIELD fieldID ) const;

   bool doesObjectExist( OBJECT objectID ) const;
   
   bool isSameValue( FIELD fieldId, const DString& strValue ) const;


// protected methods
protected:
   const DString& _getField( FIELD fieldID ) const;

   bool addFieldFlagByGroup( unsigned long  ulGroupFlag,
                             FIELD_FLAG     fieldFlag );

   bool removeFieldFlagByGroup( unsigned long  ulGroupFlag,
                                FIELD_FLAG     fieldFlag );


// protected members
protected:
   static const unsigned short SUBCLASS_ID;

private://methods


private:
   static int nNextKey;


   // validator struct definition
   typedef struct
   {
      FIELD field;
      SEVERITY ($ImplClass$::*fptr)(const DString&);
   } VALIDATOR;

   typedef struct
   {
      OBJECT object;
      SEVERITY ($ImplClass$::*fptr)(const CBOBase *);
   } OBJECT_VALIDATOR;

   static const VALIDATOR validators[MAX_FIELDS];
   static const OBJECT_VALIDATOR objectValidators[MAX_OBJECTS];

   // Array of field information structs
   static const CLASS_FIELD_INFO classFieldInfo[MAX_FIELDS];
   static const CLASS_OBJECT_INFO classObjectInfo[MAX_OBJECTS];

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
// $Log:   Y:/VCS/iFastAWD/inc/common_impl_hpp.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:30:30   kovacsro
//Initial revision.
// 
//    Rev 1.4   Jan 26 2001 10:22:42   dt39990
// Removed the _validate() method. It was
// duplicating effort for no reason.
// 
//    Rev 1.3   Sep 21 2000 07:41:26   DT29758
// added a getField that returns
// a DString
// 
//    Rev 1.2   Dec 30 1999 08:04:28   DT29758
// Modified comments to Java-Doc style
// 
//    Rev 1.1   Nov 12 1999 10:47:14   DT29758
// added unicode support & use of 
// DataDictionary indexes
// 
//    Rev 1.0.1.3   Sep 14 1999 14:13:56   DT22388
// Added new method validateReadOnlyRequired()
// Added a validate() method override so
// that the setField() and validate() method
// that takes a value can take a separate
// path from a validateAll() method call.
// The validate method that takes a value
// now calls the validateReadOnlyRequired().
// 
// 
// 
//    Rev 1.0.1.2   Aug 31 1999 15:18:20   DT22388
// Fixed the validate() method to handle
// a bool bValidatorCallOnly so that a call
// from validateField() will only kick off the
// associated validator() method in the
// derived class and not the CBOBaseImpl
// validate().  The validateField() is concerned
// with cross-field validations only. 
// 
//    Rev 1.0.1.1   Aug 02 1999 10:47:26   DT22388
// Made the _validate() method protected
// and added subclassid as a parameter.
// 
//    Rev 1.0.1.0   Jul 30 1999 13:32:22   DT22388
// Added a new method reFormatValue()
// Added a new method _validate()
// Added new code to the validate() method
// These new methods are needed as
// a part of fixing the issues with the 
// validate() method.
// The validate() method was not behaving
// exactly like the setField in the validation
// process.
// 
//    Rev 1.0   Jun 21 1999 17:07:20   DT22388
//  
// 
//    Rev 1.3   Apr 19 1999 10:39:52   DT22388
// Made changes so the isSameValue()
// method can be called from the user
// interface. 
// 
//    Rev 1.2   Mar 08 1999 14:42:08   DT22388
// Added a new method isSameValue()
// for tracker ticket #6467.
// 
//    Rev 1.1   Feb 23 1999 17:05:22   DT21815
//  
// 
//    Rev 1.0   29 Jul 1998 23:58:14   dt14596
// DLMG New Archives for TA2000NTDT
// 
//    Rev 1.21   Jul 13 1998 10:34:28   djoo
//  
// 
//    Rev 1.20   Jul 11 1998 11:44:46   djoo
// Made doesObjectExist a const method.
// 
//    Rev 1.19   Jul 10 1998 16:15:06   djoo
// Added method doesObjectExist.
// 
//    Rev 1.18   May 28 1998 15:22:26   djoo
// Added method isObjectDeleted.
// 
//    Rev 1.17   May 27 1998 10:47:12   djoo
// Added method deleteObject.
// 
//    Rev 1.16   Apr 08 1998 14:49:36   djoo
// Removed isInitialized methods.
// They have been moved to CBOBase.
// 
//    Rev 1.15   Mar 27 1998 11:03:38   djoo
// Added isOn and isOff methods.
// 
//    Rev 1.14   Mar 25 1998 08:30:34   djoo
// Made resetField public to expose on interface.
// 
//    Rev 1.13   Feb 09 1998 12:15:14   djoo
// Added overload method isFieldUpdated.
// 
//    Rev 1.12   Jan 06 1998 15:08:46   djoo
// Removed static member from common_impl_*.hpp files
// and moved it to CBOBaseImpl.hpp as const.
// 

