const unsigned short $ImplClass$::SUBCLASS_ID = $ParentImplClass$::SUBCLASS_ID + 1;

// Static int used for new key generation
int $ImplClass$::nNextKey = 1;

#ifndef INCLUDED_ASSERT_H
#include <assert.h>
#define INCLUDED_ASSERT_H
#endif

#ifndef INCLUDED_DSTRING_HPP
#include "dstring.hpp"
#define INCLUDED_DSTRING_HPP
#endif

#ifndef COMMONPORT_H
#include "commonport.h"
#define COMMONPORT_H
#endif

#ifndef STRINGFUNCTIONS_HPP
#include "stringfunctions.hpp"
#endif


#ifndef NO_VALIDATE
SEVERITY $ImplClass$::validate( unsigned short usSubclassId,
                                int nFieldId,
                                bool bValidatorCallOnly )
{
#ifdef $ImplClassStr$
   MAKEFRAMEAUTOPROMOTE( $ImplClassStr$, I_("validate( unsigned short, int )") );
#else
   MAKEFRAMEAUTOPROMOTE( I_("$ImplClass$"), I_("validate( unsigned short, int )") );
#endif

   // Does the field belong to one of our parent classes?
   if ( usSubclassId < $ImplClass$::SUBCLASS_ID )
   {
      // Field belongs to one of the parent classes, so route it to our
      // parent class
      return $ParentImplClass$::validate( usSubclassId,
                                          nFieldId,
                                          bValidatorCallOnly );
   }
   else if ( usSubclassId > $ImplClass$::SUBCLASS_ID )
   {
      throw DString( I_("Subclass Id of validate method exceeds current class subclass Id!") );
      return SEVERE_ERROR;
   }
   else
   {
      // Subclass ID matches ours -- field belongs to us
      //We may have been called from validateField for cross field validation purposes
      //so we do not want to perform our normal field validate() method
      if( bValidatorCallOnly )
      {
         //If the field has a validator method then call it
         if ( $ImplClass$::validators[static_cast< FIELD >(nFieldId)].fptr != NULL )
         {
            // Perform instance validation.
            (this->*$ImplClass$::validators[static_cast< FIELD >(nFieldId)].fptr)( CBOBaseImpl::_getField( $ImplClass$::SUBCLASS_ID, nFieldId ) );
         }
      }
      else
      {
         //do both the CBOBaseImpl validate method and the validator method
         CBOBaseImpl::validate( $ImplClass$::SUBCLASS_ID, static_cast< int >( nFieldId ), CBOBaseImpl::_getField( $ImplClass$::SUBCLASS_ID, nFieldId ) );

         //If the field has a validator method then call it
         if ( $ImplClass$::validators[static_cast< FIELD >(nFieldId)].fptr != NULL )
         {
            // Perform instance validation.
            (this->*$ImplClass$::validators[static_cast< FIELD >(nFieldId)].fptr)( CBOBaseImpl::_getField( $ImplClass$::SUBCLASS_ID, nFieldId ) );
         }

      }
      
      // Turn on the validate flag if our edits worked
      if ( GETCURRENTHIGHESTSEVERITY() < SEVERE_ERROR ) 
      {
           // Turn on the validated flag for this field
          setFieldFlag(usSubclassId, nFieldId, CBOBaseImpl::INST_FLD_VALIDATED);
      }

      // Return the highest severity from the two calls
      return GETCURRENTHIGHESTSEVERITY();      
   }
}
#endif


#ifndef NO_VALIDATE
SEVERITY $ImplClass$::validate( unsigned short usSubclassId,
                                int nFieldId,
                                const DString& strValue,
                                bool fRemoveFormat )
{
#ifdef $ImplClassStr$
   MAKEFRAMEAUTOPROMOTE( $ImplClassStr$, I_("validate( unsigned short, int )") );
#else
   MAKEFRAMEAUTOPROMOTE( I_("$ImplClass$"), I_("validate( unsigned short, int )") );
#endif

   // Does the field belong to one of our parent classes?
   if ( usSubclassId < $ImplClass$::SUBCLASS_ID )
   {
      // Field belongs to one of the parent classes, so route it to our
      // parent class
      return $ParentImplClass$::validate( usSubclassId,
                                          nFieldId,
                                          strValue,
                                          fRemoveFormat );
   }
   else if ( usSubclassId > $ImplClass$::SUBCLASS_ID )
   {
      throw DString( I_("Subclass Id of validate method exceeds current class subclass Id!") );
      return SEVERE_ERROR;
   }
   else
   {
		SEVERITY sev = NO_CONDITION;

		// Check if field is cross field
		sev = validateIfCrossField( $ImplClass$::SUBCLASS_ID, static_cast< int >( nFieldId ) );

		if( NO_CONDITION == sev )
		{
			// Subclass ID matches ours -- field belongs to us
			// do both the CBOBaseImpl validate method and the validator method
			// Copy our DString in case its formatted
			DString strPotentialValue  = strValue;

			// CBOBase in setField() does some massaging up front, therefore he may not want the derived class
			// to do the work twice!
			if ( fRemoveFormat )
			{
				// Unformat the DString if its a data object substitution value
				reFormatValue( $ImplClass$::SUBCLASS_ID, static_cast< int >(nFieldId), strPotentialValue, fRemoveFormat );
				fRemoveFormat = false;//set to false so that the validate() method call does not fire the unformatString again
			}

			CBOBaseImpl::validate( $ImplClass$::SUBCLASS_ID, static_cast< int >( nFieldId ), strPotentialValue, fRemoveFormat );

			//If the field has a validator method then call it
			if ( $ImplClass$::validators[static_cast< int >(nFieldId)].fptr != NULL )
			{
				// Perform instance validation.
				(this->*$ImplClass$::validators[static_cast< int >(nFieldId)].fptr)( strPotentialValue );
			}
      
			// Return the highest severity from the two calls
			return GETCURRENTHIGHESTSEVERITY();
		}

		return GETCURRENTHIGHESTSEVERITY();
   }
}
#endif


#ifndef NO_VALIDATE
SEVERITY $ImplClass$::validate( FIELD fieldId )
{
#ifdef $ImplClassStr$
   MAKEFRAMEAUTOPROMOTE( $ImplClassStr$, I_("validate( int )") );
#else
   MAKEFRAMEAUTOPROMOTE( I_("$ImplClass$"), I_("validate( int )") );
#endif

   SEVERITY sev = NO_CONDITION;

	// Check if field is cross field
	sev = validateIfCrossField( $ImplClass$::SUBCLASS_ID, static_cast< int >( fieldId ) );

	if( NO_CONDITION == sev )
	{
		// check value against the READ_ONLY or REQUIRED field attribute
		sev = validateReadOnlyRequired( $ImplClass$::SUBCLASS_ID, static_cast< int >( fieldId ),
                                   CBOBaseImpl::_getField( $ImplClass$::SUBCLASS_ID, fieldId ),
                                   true ); // pass true to not do the read only check
		if( NO_CONDITION == sev )
		{
			validate( $ImplClass$::SUBCLASS_ID, static_cast< int >( fieldId ) );
		}
	}
   
   // Return the highest severity from the two calls
   return GETCURRENTHIGHESTSEVERITY();
}
#endif


#ifndef NO_VALIDATE
SEVERITY $ImplClass$::validate( FIELD fieldId,
                                const DString& strValue,
                                bool fRemoveFormat )
{

#ifdef $ImplClassStr$
   MAKEFRAMEAUTOPROMOTE( $ImplClassStr$, I_("validate( FIELD, const DString&, bool )") );
#else
   MAKEFRAMEAUTOPROMOTE( I_("$ImplClass$"), I_("validate( FIELD, const DString&, bool )") );
#endif
   
   //check value against the READ_ONLY or REQUIRED field attribute
   SEVERITY sev = NO_CONDITION;

   sev = validateReadOnlyRequired( $ImplClass$::SUBCLASS_ID, static_cast< int >( fieldId ), strValue );

   if ( NO_CONDITION == sev ) 
   {
      validate( $ImplClass$::SUBCLASS_ID, static_cast< int >( fieldId ), strValue, fRemoveFormat );      
   }

   // Return the highest severity from the two calls
   return GETCURRENTHIGHESTSEVERITY();      

}
#endif

#ifndef NO_VALIDATEOBJECT
SEVERITY $ImplClass$::validateObject( unsigned short usSubclassId, int nObjectId )
{
#ifdef $ImplClassStr$
   TRACE_METHOD( $ImplClassStr$, I_("validateObject( unsigned short, int )") );
#else
   TRACE_METHOD( I_("$ImplClass$"), I_("validateObject( unsigned short, int )") );
#endif

   // Does the object belong to one of our parent classes?
   if ( usSubclassId < $ImplClass$::SUBCLASS_ID )
   {
      // Object belongs to one of the parent classes, so route it to our
      // parent class
      return $ParentImplClass$::validateObject( usSubclassId,
                                                nObjectId );
   }
   else if ( usSubclassId > $ImplClass$::SUBCLASS_ID )
   {
      throw DString( I_("Subclass Id of validate method exceeds current class subclass Id!") );
      return SEVERE_ERROR;
   }
   else
   {
      // Subclass ID matches ours -- object belongs to us
      if ( $ImplClass$::objectValidators[nObjectId].fptr != NULL )
      {
         return (this->*$ImplClass$::objectValidators[nObjectId].fptr)(
            getConstObject( usSubclassId, nObjectId ) );
      }
      else
      {
         // No validation routine registered for this object -- so we assume
         // that any object is OK.
         return NO_CONDITION;
      }
   }
}
#endif



#ifndef NO_VALIDATEOBJECT
SEVERITY $ImplClass$::validateObject( unsigned short usSubclassId,
                                      int nObjectId,
                                      const CBOBase * pObject )
{
#ifdef $ImplClassStr$
   TRACE_METHOD( $ImplClassStr$, I_("validateObject( unsigned short, int, const CBOBase * )") );
#else
   TRACE_METHOD( I_("$ImplClass$"), I_("validateObject( unsigned short, int, const CBOBase * )") );
#endif

   // Does the object belong to one of our parent classes?
   if ( usSubclassId < $ImplClass$::SUBCLASS_ID )
   {
      // Field belongs to one of the parent classes, so route it to our
      // parent class
      return $ParentImplClass$::validateObject( usSubclassId,
                                                nObjectId,
                                                pObject );
   }
   else if ( usSubclassId > $ImplClass$::SUBCLASS_ID )
   {
      throw DString( I_("Subclass Id of validate method exceeds current class subclass Id!") );
      return SEVERE_ERROR;
   }
   else
   {
      // Subclass ID matches ours -- object belongs to us
      if ( $ImplClass$::objectValidators[nObjectId].fptr != NULL )
      {
         return (this->*$ImplClass$::objectValidators[nObjectId].fptr)( pObject );
      }
      else
      {
         // No validation routine registered for this object -- so we assume
         // that any object is OK.
         return NO_CONDITION;
      }
   }
}
#endif


#ifndef NO_VALIDATEOBJECT
SEVERITY $ImplClass$::validateObject( OBJECT objectId )
{
   return validateObject( $ImplClass$::SUBCLASS_ID, static_cast< int >( objectId ) );
}
#endif


#ifndef NO_VALIDATEOBJECT
SEVERITY $ImplClass$::validateObject( OBJECT objectId, const CBOBase * pObject )
{
   return validateObject( $ImplClass$::SUBCLASS_ID, static_cast< int >( objectId ), pObject );
}
#endif


#ifndef NO_SETFIELD
SEVERITY $ImplClass$::setField( FIELD fieldId, const DString& strValue )
{
   return setField( $ImplClass$::SUBCLASS_ID, fieldId, strValue );
}
#endif


#ifndef NO_SETFIELD
SEVERITY $ImplClass$::setField( FIELD fieldId, const MathString& mstrFieldValue )
{
   return CBOBaseImpl::setField( $ImplClass$::SUBCLASS_ID, fieldId, mstrFieldValue );
}
#endif


SEVERITY $ImplClass$::deleteObject( OBJECT objectID )
{
   return CBOBaseImpl::deleteObject( $ImplClass$::SUBCLASS_ID, objectID );
}

bool $ImplClass$::isObjectDeleted( OBJECT objectID ) const
{
   return CBOBaseImpl::isObjectDeleted( $ImplClass$::SUBCLASS_ID, objectID );
}


#ifndef NO_SETOBJECT
SEVERITY $ImplClass$::setObject( OBJECT objectId, CBOBase * pObject, bool fDeleteOnFailure )
{
   return setObject( $ImplClass$::SUBCLASS_ID, objectId, pObject, fDeleteOnFailure );
}
#endif


bool $ImplClass$::doesOwnObject( OBJECT objectId ) const
{
   return CBOBaseImpl::doesOwnObject( $ImplClass$::SUBCLASS_ID, objectId );
}



#ifndef NO_GETFIELD
DString $ImplClass$::getField( FIELD fieldID, bool fFormattedReturn ) const
{
   DString strFieldValue;
   getField( fieldID, strFieldValue, fFormattedReturn );
   return strFieldValue;
}
#endif



#ifndef NO_GETFIELD
SEVERITY $ImplClass$::getField( FIELD fieldId, DString& strValue, bool fFormattedReturn ) const
{
   return getField( $ImplClass$::SUBCLASS_ID, fieldId, strValue, fFormattedReturn );
}
#endif



#ifndef NO_GETFIELD
SEVERITY $ImplClass$::getField( FIELD fieldId, MathString& mstrFieldValue ) const
{
   return getField( $ImplClass$::SUBCLASS_ID, fieldId, mstrFieldValue );
}
#endif


#ifndef NO_GETOBJECT
CBOBase * $ImplClass$::getObject( OBJECT objectId )
{
    return getObject( $ImplClass$::SUBCLASS_ID, objectId );
}
#endif


bool $ImplClass$::doesObjectExist( OBJECT objectID ) const
{
   return CBOBaseImpl::doesObjectExist( $ImplClass$::SUBCLASS_ID, objectID );
}


#ifndef NO_GETOBJECT
SEVERITY $ImplClass$::getObject( OBJECT objectId, CBOBase& cboObject )
{

   return getObject( $ImplClass$::SUBCLASS_ID, objectId, cboObject );

}
#endif


#ifndef NO_GETCONSTOBJECT
const CBOBase * $ImplClass$::getConstObject( OBJECT objectId ) const
{
   return getConstObject( $ImplClass$::SUBCLASS_ID, objectId );
}
#endif


DString $ImplClass$::getFieldTag( FIELD fieldId ) const
{
   return CBOBaseImpl::getFieldTag( $ImplClass$::SUBCLASS_ID, fieldId );
}


int $ImplClass$::getMaxLength( FIELD fieldId ) const
{
   return CBOBaseImpl::getMaxLength( $ImplClass$::SUBCLASS_ID, fieldId );
}


// static method
void $ImplClass$::getMaxLength( FIELD fieldId, int& nLength )
{
   assert( fieldId >=0 && fieldId < MAX_FIELDS );
   nLength = $ImplClass$::classFieldInfo[ fieldId ].nMaxLength;
}


bool $ImplClass$::isRequired( FIELD fieldId ) const
{
   return CBOBaseImpl::isRequired( $ImplClass$::SUBCLASS_ID, fieldId );
}


// static method
void $ImplClass$::getFieldTag( FIELD fieldId, DString& strFieldTag )
{
   assert( fieldId >= 0 && fieldId < MAX_FIELDS );
   strFieldTag = $ImplClass$::classFieldInfo[ fieldId ].pcszTag;
}


void $ImplClass$::checkRequired( FIELD fieldId, bool& fRequired )
{
   assert( fieldId >=0 && fieldId < MAX_FIELDS );
   fRequired = ( $ImplClass$::classFieldInfo[ fieldId ].ulFlags |
                 CBOBaseImpl::CLASS_FLD_REQUIRED   ? true : false );
}


bool $ImplClass$::isReadOnly( FIELD fieldId ) const
{
   return CBOBaseImpl::isReadOnly( $ImplClass$::SUBCLASS_ID, fieldId );
}


bool $ImplClass$::resetField( FIELD fieldID )
{
   return CBOBaseImpl::resetField( $ImplClass$::SUBCLASS_ID, fieldID );
}

// static method
void $ImplClass$::checkReadOnly( FIELD fieldId, bool& fReadOnly )
{
   assert( fieldId >= 0 && fieldId < MAX_FIELDS );
   fReadOnly = ( $ImplClass$::classFieldInfo[ fieldId ].ulFlags |
                 CBOBaseImpl::CLASS_FLD_READ_ONLY ? true : false );
}


bool $ImplClass$::isValidType( OBJECT objectId,
                               CBOBase * pObject ) const
{
   return CBOBaseImpl::isValidType( $ImplClass$::SUBCLASS_ID, objectId, pObject );
}


bool $ImplClass$::isValidContainedObjectDerivation( OBJECT objectId, CBOBase * pObject ) const
{
   return isValidContainedObjectDerivation( $ImplClass$::SUBCLASS_ID, objectId, pObject );
}


bool $ImplClass$::isFieldGroupFlagSet( unsigned long ulGroupFlag ) const
{
   return isFieldGroupFlagSet( $ImplClass$::SUBCLASS_ID, ulGroupFlag );
}


bool $ImplClass$::isObjectGroupFlagSet( unsigned long ulGroupFlag ) const
{
   return isObjectGroupFlagSet( $ImplClass$::SUBCLASS_ID, ulGroupFlag );
}


bool $ImplClass$::isFieldFlagSet( CBOBaseImpl::FIELD_FLAG fieldFlag, FIELD fieldId ) const
{
   return CBOBaseImpl::isFieldFlagSet( $ImplClass$::SUBCLASS_ID, fieldFlag, fieldId );
}


bool $ImplClass$::isObjectFlagSet( CBOBaseImpl::OBJECT_FLAG objectFlag, OBJECT objectId ) const
{
   return CBOBaseImpl::isObjectFlagSet( $ImplClass$::SUBCLASS_ID, objectFlag, objectId );
}


#ifndef NO_GETFIELD
const DString& $ImplClass$::_getField( FIELD fieldId ) const
{
   return CBOBaseImpl::_getField( $ImplClass$::SUBCLASS_ID, fieldId );
}
#endif


bool $ImplClass$::addFieldFlagByGroup( unsigned long  ulGroupFlag, FIELD_FLAG fieldFlag )
{
   return CBOBaseImpl::addFieldFlagByGroup( $ImplClass$::SUBCLASS_ID, ulGroupFlag, fieldFlag );
}


bool $ImplClass$::removeFieldFlagByGroup( unsigned long  ulGroupFlag, FIELD_FLAG fieldFlag )
{
   return CBOBaseImpl::removeFieldFlagByGroup( $ImplClass$::SUBCLASS_ID, ulGroupFlag, fieldFlag );
}


bool $ImplClass$::isFieldUpdated( FIELD fieldId ) const
{
   return CBOBaseImpl::isFieldUpdated( $ImplClass$::SUBCLASS_ID, fieldId );
}


bool $ImplClass$::isOn( FIELD fieldID ) const
{
   return CBOBaseImpl::isOn( $ImplClass$::SUBCLASS_ID, fieldID );
}


bool $ImplClass$::isOff( FIELD fieldID ) const
{
   return CBOBaseImpl::isOff( $ImplClass$::SUBCLASS_ID, fieldID );
}


// Static method 
// Used to generate new keys at a class level, starts with @1 and increments the numeric
// portion after each call.
void $ImplClass$::getNextNewKey( DString &strKey )
{
#ifdef $ImplClassStr$
   TRACE_METHOD( $ImplClassStr$, I_("getNextNewKey( DString$ )") );
#else
   TRACE_METHOD( I_("$ImplClass$"), I_("getNextNewKey( DString$ )") );
#endif

   strKey = I_("@");
   strKey += asString( nNextKey );

   ++nNextKey;
}

// Static method 
// Used to reset the new key at a class level.  Resets the key to 1.
void $ImplClass$::resetNewKey()
{
#ifdef $ImplClassStr$
   TRACE_METHOD( $ImplClassStr$, I_("resetNewKey( )") );
#else
   TRACE_METHOD( I_("$ImplClass$"), I_("resetNewKey( )") );
#endif

    nNextKey = 1;
}


bool $ImplClass$::isSameValue( FIELD fieldId, const DString& strValue ) const
{
   return CBOBaseImpl::isSameValue( $ImplClass$::SUBCLASS_ID, fieldId, strValue );
}

#undef $ParentImplClassStr$  
#undef $ImplClassStr$  

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
// $Log:   Y:/VCS/iFastAWD/inc/common_impl_cpp.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:30:30   kovacsro
//Initial revision.
// 
//    Rev 1.6   Nov 01 2001 15:00:52   dt39990
// Added statement validateIfCrossField() 
// in validate() method to check if the field 
// is crossfield. 
// 
// 
//    Rev 1.5   Jan 30 2001 10:01:02   dt39990
// cleanup
// 
//    Rev 1.4   Jan 26 2001 10:30:34   dt39990
// Added a call to the 
// validateReadOnlyRequired method in
// validate methods.
// 
// Removed the _validate() method. It was
// duplicating effort for no reason.
// 
//    Rev 1.3   Sep 25 2000 07:53:26   DT29758
// corrected getfield override 
// to read $implclass$ 
// 
//    Rev 1.2   Sep 21 2000 07:41:24   DT29758
// added a getField that returns
// a DString
// 
//    Rev 1.1   Nov 12 1999 10:47:12   DT29758
// added unicode support & use of 
// DataDictionary indexes
// 
//    Rev 1.0.1.4   Sep 14 1999 14:13:54   DT22388
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
//    Rev 1.0.1.3   Aug 31 1999 15:18:16   DT22388
// Fixed the validate() method to handle
// a bool bValidatorCallOnly so that a call
// from validateField() will only kick off the
// associated validator() method in the
// derived class and not the CBOBaseImpl
// validate().  The validateField() is concerned
// with cross-field validations only. 
// 
//    Rev 1.0.1.2   Aug 25 1999 18:54:30   DT22388
// Fixed the validate() method that is called
// in the validateAll() method call path.
// The validate() method  that takes a field id only also calls
// the fixed validate() method.  The fixed validate() method
// is mainly used for postponed validation mode.
// It now funnels a call down to the main
// validation() method inside CBOBaseImpl
// so that all validations will be performed.
// 
// 
//    Rev 1.0.1.1   Aug 02 1999 10:47:22   DT22388
// Made the _validate() method protected
// and added subclassid as a parameter.
// 
//    Rev 1.0.1.0   Jul 30 1999 13:32:18   DT22388
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
//    Rev 1.0   Jun 21 1999 17:07:18   DT22388
//  
// 
//    Rev 1.4   Mar 17 1999 10:16:58   DT21815
// Minor cleanup.
// 
//    Rev 1.3   Mar 08 1999 14:42:06   DT22388
// Added a new method isSameValue()
// for tracker ticket #6467.
// 
//    Rev 1.2   Mar 04 1999 17:17:10   DT22388
// Removed method calls to TRACE_METHOD
// and removed pure virtual methods that
// were taking an int as a parameter. The usage
// of an int would not work for CBOs with more
// than one subclass.  Also
// added two new validateObject() methods.
// 
// 
// 
// 
//    Rev 1.1   Feb 23 1999 17:05:22   DT21815
// Made getConstObject method const.
// 
//    Rev 1.0   29 Jul 1998 23:58:14   dt14596
// DLMG New Archives for TA2000NTDT
// 
//    Rev 1.29   Jul 13 1998 10:34:26   djoo
// Modifed validate signature.
// 
//    Rev 1.28   Jul 11 1998 11:44:44   djoo
// Made doesObjectExist a const method.
// 
//    Rev 1.27   Jul 10 1998 16:15:04   djoo
// Added method doesObjectExist.
// 
//    Rev 1.26   Jun 19 1998 17:09:22   djoo
// Added scope resolution for the setField that utilizes
// mathstring.  CBOBase converts the mathstring to a 
// regular string and calls the setField that utilizes strings.
// 
//    Rev 1.25   Jun 19 1998 16:27:50   djoo
// Removed scope resolution for 2 setField calls.
// 
//    Rev 1.24   Jun 01 1998 09:48:06   djoo
// Removed scope resolution for 2 getField calls.
// 
//    Rev 1.23   May 28 1998 15:22:24   djoo
// Added method isObjectDeleted.
// 
//    Rev 1.22   May 27 1998 10:47:08   djoo
// Added method deleteObject.
// 
//    Rev 1.21   Apr 10 1998 12:19:56   djoo
// Modified validate that validates "potential"
// new field values to remove any Data object
// string substitution.
// 
//    Rev 1.20   Apr 08 1998 14:49:32   djoo
// Removed isInitialized methods.
// They have been moved to CBOBase.
// 
//    Rev 1.19   Apr 02 1998 14:33:04   djoo
// Added additional TRACE macro calls to 
// support actual string class names.
// 
//    Rev 1.18   Mar 27 1998 11:03:36   djoo
// Added isOn and isOff methods.
// 
//    Rev 1.17   Feb 09 1998 12:15:12   djoo
// Added overload method isFieldUpdated.
// 
//    Rev 1.16   Jan 06 1998 15:08:44   djoo
// Removed static member from common_impl_*.hpp files
// and moved it to CBOBaseImpl.hpp as const.
// 

