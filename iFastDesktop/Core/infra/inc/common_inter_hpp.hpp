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

#ifndef  DSTRING_HPP
#include "dstring.hpp"
#endif

public:
    using $ParentClass$::getField;
    using $ParentClass$::setField;
    using $ParentClass$::isFieldUpdated;
    using $ParentClass$::resetField;
    using $ParentClass$::isOn;
    using $ParentClass$::isOff;
    using $ParentClass$::validate;

    virtual DString getFieldTag( FIELD fieldID ) const;
    virtual SEVERITY validate( FIELD fieldID ) const;
    virtual SEVERITY validate( FIELD fieldID, const DString& strValue ) const;
    virtual SEVERITY validateObject( OBJECT objectID ) const;
    virtual SEVERITY validateObject( OBJECT objectID, const CBOBase * pObject ) const;
    
    SEVERITY setField( FIELD fieldID, const DString& strValue );
    SEVERITY setField( FIELD fieldID, const MathString& mstrFieldValue );
    SEVERITY setObject( OBJECT objectID, CBOBase* pCBO );
    SEVERITY deleteObject( OBJECT objectID );
    bool isObjectDeleted( OBJECT objectID ) const;
    SEVERITY getField( FIELD fieldID, DString& strValue, bool fFormattedReturn = true ) const;
    SEVERITY getField( FIELD fieldID, MathString& mstrFieldValue ) const;
    DString getField( FIELD fieldID, bool fFormattedReturn = true ) const;
    SEVERITY getObject( OBJECT objectID, CBOBase& cboObject );
    CBOBase * getObject( OBJECT objectID );
    const CBOBase * getConstObject( OBJECT objectID ) const;
    int getMaxLength( FIELD fieldID ) const;
    bool isRequired( FIELD fieldID ) const;
    bool isReadOnly( FIELD fieldID ) const;
    bool isFieldGroupFlagSet( unsigned long ulGroupFlag ) const;
    bool isObjectGroupFlagSet( unsigned long ulGroupFlag ) const;
    static void getFieldTag( FIELD fieldID, DString& strFieldTag );
    static void getMaxLength( FIELD fieldID, int& nLength );
    static void checkRequired( FIELD fieldID, bool& fRequired );
    static void checkReadOnly( FIELD fieldID, bool& fReadOnly );
    virtual CBOBase * makeCopy( void ) const;
    virtual bool copy( CBOBase * pSrcObject );
    bool isFieldUpdated( FIELD fieldId ) const;
    bool resetField( FIELD nFieldId );
    bool isOn( FIELD fieldID ) const;
    bool isOff( FIELD fieldID ) const;
    bool doesObjectExist( OBJECT objectID ) const;
    bool isSameValue( FIELD fieldId, const DString& strValue ) const;


#include "cbo_all_inter_hpp.hpp"

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
// $Log:   Y:/VCS/iFastAWD/inc/common_inter_hpp.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:30:32   kovacsro
//Initial revision.
// 
//    Rev 1.2   Dec 30 1999 08:04:30   DT29758
// Modified comments to Java-Doc style
// 
//    Rev 1.1   Nov 12 1999 10:47:20   DT29758
// added unicode support & use of 
// DataDictionary indexes
// 
//    Rev 1.0.1.0   Aug 04 1999 17:31:00   DT22388
// Added two new validate() methods
// 
// SEVERITY validate( const string& strFieldTag,
//                                        const string& strValue );
// 
// SEVERITY validate( const string& strFieldTag,
//                                         const MathString& mstrFieldValue );
// and added a 'using $ParentClass$::validate;'
// so that the validate() method that takes
// an enum works with two or more
// derivations from CBOBase.
// 
//    Rev 1.0   Jun 21 1999 17:07:30   DT22388
//  
// 
//    Rev 1.5   Apr 19 1999 10:39:56   DT22388
// Made changes so the isSameValue()
// method can be called from the user
// interface. 
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


