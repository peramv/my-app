#ifndef INCLUDED_ASSERT_H
#include <assert.h>
#define INCLUDED_ASSERT_H
#endif

#ifndef INCLUDED_DSTRING_HPP
#include "dstring.hpp"
#define INCLUDED_DSTRING_HPP
#endif

DString $ThisClass$::getFieldTag( FIELD fieldID ) const
{
   assert (_pImpl);
   return static_cast<$ThisClassImpl$*>(_pImpl)->getFieldTag( ($ThisClassImpl$::FIELD) fieldID );
}


SEVERITY $ThisClass$::validate( FIELD fieldID ) const
{
   assert (_pImpl);
   return static_cast<$ThisClassImpl$*>(_pImpl)->validate( ($ThisClassImpl$::FIELD) fieldID );
}


SEVERITY $ThisClass$::validate( FIELD fieldID, const DString& strValue ) const
{
   assert (_pImpl);
   return static_cast<$ThisClassImpl$*>(_pImpl)->validate( ($ThisClassImpl$::FIELD) fieldID, strValue );
}


SEVERITY $ThisClass$::validateObject( OBJECT objectID ) const
{
   assert (_pImpl);
   return static_cast<$ThisClassImpl$*>(_pImpl)->validateObject( ($ThisClassImpl$::OBJECT) objectID );
}


SEVERITY $ThisClass$::validateObject( OBJECT objectID, const CBOBase * pObject ) const
{
   assert (_pImpl);
   return static_cast<$ThisClassImpl$*>(_pImpl)->validateObject( ($ThisClassImpl$::OBJECT) objectID, pObject );
}



SEVERITY $ThisClass$::setField( FIELD fieldID, const DString& strValue )
{
   assert (_pImpl);
   return static_cast<$ThisClassImpl$*>(_pImpl)->setField( ($ThisClassImpl$::FIELD) fieldID, strValue );
}


SEVERITY $ThisClass$::setField( FIELD fieldID, const MathString& mstrFieldValue )
{
   assert (_pImpl);
   return static_cast<$ThisClassImpl$*>(_pImpl)->setField( ($ThisClassImpl$::FIELD) fieldID, mstrFieldValue );
}



SEVERITY $ThisClass$::deleteObject( OBJECT objectID )
{
   assert (_pImpl);

   $ThisClassImpl$ * pImpl = static_cast<$ThisClassImpl$*>(_pImpl);

   return pImpl->deleteObject( ($ThisClassImpl$::OBJECT) objectID );
}

bool $ThisClass$::isObjectDeleted( OBJECT objectID ) const
{
   assert (_pImpl);

   $ThisClassImpl$ * pImpl = static_cast<$ThisClassImpl$*>(_pImpl);

   return pImpl->isObjectDeleted( ($ThisClassImpl$::OBJECT) objectID );
}


SEVERITY $ThisClass$::setObject( OBJECT objectID, CBOBase* pCBO )
{
   assert (_pImpl);

   $ThisClassImpl$ * pImpl = static_cast<$ThisClassImpl$*>(_pImpl);

   return pImpl->setObject( ($ThisClassImpl$::OBJECT) objectID,
                            pCBO,
                            false );   // The last parameter is IGNORED at this time.


/*
   // Do we own the object?
   if ( pImpl->doesOwnObject( ($ThisClassImpl$::OBJECT) objectID ) )
   {
      bool fDeleteObjectOnFailure = true;

      // non-NULL pointer?
      if ( pCBO )
      {
         // Yes, we own the object. Pass in a *COPY* of the object (using the
         // "virtual copy constructor" to make a copy). If the set fails for
         // any reason, delete the object (a copy).
         return pImpl->setObject( ($ThisClassImpl$::OBJECT) objectID,
                                  pCBO->makeCopy(),
                                  fDeleteObjectOnFailure );
      }
      else
      {
         return pImpl->setObject( ($ThisClassImpl$::OBJECT) objectID,
                                  pCBO,
                                  fDeleteObjectOnFailure );
      }
   }
   else
   {
      // No, we don't own the object. Pass in a *POINTER* to the object. If
      // the set fails for any reason, DO NOT attempt to delete the object
      // (since we don't own it).
      bool fDeleteObjectOnFailure = false;
      return pImpl->setObject( ($ThisClassImpl$::OBJECT) objectID,
                               pCBO,
                               fDeleteObjectOnFailure );
   }
*/
}



SEVERITY $ThisClass$::getField( FIELD fieldID, DString& strValue, bool fFormattedReturn ) const
{
   assert (_pImpl);
   return static_cast<$ThisClassImpl$*>(_pImpl)->getField( ($ThisClassImpl$::FIELD) fieldID, strValue, fFormattedReturn );
}



SEVERITY $ThisClass$::getField( FIELD fieldID, MathString& mstrFieldValue ) const
{
   assert (_pImpl);
   return static_cast<$ThisClassImpl$*>(_pImpl)->getField( ($ThisClassImpl$::FIELD) fieldID, mstrFieldValue );
}



DString $ThisClass$::getField( FIELD fieldID, bool fFormattedReturn ) const
{
   DString strFieldValue;
   getField( fieldID, strFieldValue, fFormattedReturn );
   return strFieldValue;
}



SEVERITY $ThisClass$::getObject( OBJECT objectID, CBOBase& cboObject )
{
   assert (_pImpl);

   $ThisClassImpl$ *pImpl = static_cast<$ThisClassImpl$*>( _pImpl );

   return pImpl->getObject( ($ThisClassImpl$::OBJECT) objectID, cboObject );

/*
   CBOBase * pObject = pImpl->getObject( ($ThisClassImpl$::OBJECT) objectID );

   // do we currently have an instance?
   if ( NULL != pObject )
   {
      // yes, we have an instance

      // is the passed-in object of the correct CBOBase-derived type?
      if ( pImpl->isValidType( ($ThisClassImpl$::OBJECT) objectID,
                               &cboObject ) )
      {
         // invoke copy operator
         cboObject.copy( pObject );
         // cboObject = *pObject;
         return NO_CONDITION;
      }
      else
      {
         // invalid derived type of passed-in argument!
         // Condition?
         return SEVERE_ERROR;
      }
   }
   else
   {
      // no, we don't have an instance
      // Condition?
      return SEVERE_ERROR;
   }
*/
}


bool $ThisClass$::doesObjectExist( OBJECT objectID ) const
{
   assert (_pImpl);

   $ThisClassImpl$ *pImpl = static_cast<$ThisClassImpl$*>( _pImpl );

   return pImpl->doesObjectExist( ($ImplClass$::OBJECT) objectID );
}


CBOBase * $ThisClass$::getObject( $ThisClass$::OBJECT objectId )
{
   assert (_pImpl);

   $ThisClassImpl$ *pImpl = static_cast<$ThisClassImpl$*>( _pImpl );

/*   if ( pImpl->isObjectFlagSet( CBOBaseImpl::INST_OBJ_COPY_ONLY,
                                ($ImplClass$::OBJECT) objectId ) )
   {
      // Add condition for object is copy only
      // ADDCONDITIONFROMFILE();
      return NULL;
   }
*/
   return pImpl->getObject( ($ImplClass$::OBJECT) objectId );
}



const CBOBase * $ThisClass$::getConstObject( OBJECT objectId ) const
{
   assert (_pImpl);

   $ThisClassImpl$ *pImpl = static_cast<$ThisClassImpl$*>( _pImpl );

   return pImpl->getConstObject( ($ImplClass$::OBJECT) objectId );
}


int $ThisClass$::getMaxLength( FIELD fieldID ) const
{
   assert (_pImpl);
   return static_cast<$ThisClassImpl$*>(_pImpl)->getMaxLength( ($ThisClassImpl$::FIELD) fieldID );
}


bool $ThisClass$::isRequired( FIELD fieldID ) const
{
   assert (_pImpl);
   return static_cast<$ThisClassImpl$*>(_pImpl)->isRequired( ($ThisClassImpl$::FIELD) fieldID );
}


bool $ThisClass$::isReadOnly( FIELD fieldID ) const
{
   assert (_pImpl);
   return static_cast<$ThisClassImpl$*>(_pImpl)->isReadOnly( ($ThisClassImpl$::FIELD) fieldID );
}


bool $ThisClass$::isFieldGroupFlagSet( unsigned long ulGroupFlag ) const
{
   assert (_pImpl);
   return static_cast<$ThisClassImpl$*>(_pImpl)->isFieldGroupFlagSet( ulGroupFlag );
}


bool $ThisClass$::isObjectGroupFlagSet( unsigned long ulGroupFlag ) const
{
   assert (_pImpl);
   return static_cast<$ThisClassImpl$*>(_pImpl)->isObjectGroupFlagSet( ulGroupFlag );
}


// static method
void $ThisClass$::getFieldTag( FIELD fieldID, DString& strFieldTag )
{
   $ThisClassImpl$::getFieldTag( ($ThisClassImpl$::FIELD) fieldID, strFieldTag );
}


void $ThisClass$::getMaxLength( FIELD fieldID, int& nLength )
{
   $ThisClassImpl$::getMaxLength( ($ThisClassImpl$::FIELD) fieldID, nLength );
}


// static method
void $ThisClass$::checkRequired( FIELD fieldID, bool& fRequired )
{
   $ThisClassImpl$::checkRequired( ($ThisClassImpl$::FIELD) fieldID, fRequired );
}


// static method
void $ThisClass$::checkReadOnly( FIELD fieldID, bool& fReadOnly )
{
   $ThisClassImpl$::checkReadOnly( ($ThisClassImpl$::FIELD) fieldID, fReadOnly );
}


CBOBase * $ThisClass$::makeCopy( void ) const
{
   TRACE_METHOD( $ThisClassStr$, I_("makeCopy()") );

#ifndef NO_CBO_COPY
   return new $ThisClass$( *this );
#else
   // Condition?
   throw DString( I_("No copy constructor defined!") );
   return NULL;
#endif
}


bool $ThisClass$::copy( CBOBase * pSrcObject )
{
   TRACE_METHOD( $ThisClassStr$, I_("copy( const CBOBase * )") );

#ifndef NO_CBO_COPY
   // is the source object of the correct type?
   $ThisClass$ *pObject = dynamic_cast<$ThisClass$*>( pSrcObject );

   if ( ! pObject )
   {
      // invalid type
      // Condition?
      return false;
   }

   *this = *pObject;

   return true;
#else
   // Condition?
   throw DString( I_("No copy operator defined!") );
   return false;
#endif
}


bool $ThisClass$::isFieldUpdated( FIELD fieldID ) const
{
   return static_cast<$ThisClassImpl$*>(_pImpl)->isFieldUpdated( ($ThisClassImpl$::FIELD) fieldID );
}

bool $ThisClass$::resetField( FIELD fieldID )
{
   assert (_pImpl);
   return static_cast<$ThisClassImpl$*>(_pImpl)->resetField( ($ThisClassImpl$::FIELD) fieldID );
}


bool $ThisClass$::isOn( FIELD fieldID ) const
{
   assert (_pImpl);
   return static_cast<$ThisClassImpl$*>(_pImpl)->isOn( ($ThisClassImpl$::FIELD) fieldID );
}


bool $ThisClass$::isOff( FIELD fieldID ) const
{
   assert (_pImpl);
   return static_cast<$ThisClassImpl$*>(_pImpl)->isOff( ($ThisClassImpl$::FIELD) fieldID );
}


bool $ThisClass$::isSameValue( FIELD fieldID, const DString& strValue ) const
{
   assert (_pImpl);
   return static_cast<$ThisClassImpl$*>(_pImpl)->isSameValue( ($ThisClassImpl$::FIELD) fieldID, strValue );
}



#include "cbo_all_inter_cpp.hpp"


#undef $ParentClassStr$
#undef $ThisClassStr$  
#undef $ThisClassImplStr$

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
// $Log:   Y:/VCS/iFastAWD/inc/common_inter_cpp.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:30:32   kovacsro
//Initial revision.
// 
//    Rev 1.1   Nov 12 1999 10:47:18   DT29758
// added unicode support & use of 
// DataDictionary indexes
// 
//    Rev 1.0   Jun 21 1999 17:07:26   DT22388
//  
// 
//    Rev 1.6   Apr 19 1999 10:39:54   DT22388
// Made changes so the isSameValue()
// method can be called from the user
// interface. 
// 
//    Rev 1.5   Mar 17 1999 09:37:52   DT21815
// Removed outdated tracing calls and those for
// pass-through methods.
// 
//    Rev 1.4   Mar 15 1999 14:00:44   DT22388
// Added back the changes made for removing
// any base method that takes an int as a parm
// (i.e. setField() and getField()).
// The previous revision was a rollback of
// these changes. A rollback was peformed
// since the GUI code was not ready for our
// changes.
// 
//    Rev 1.2   Mar 04 1999 17:17:12   DT22388
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



