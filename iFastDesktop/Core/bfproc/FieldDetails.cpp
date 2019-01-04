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
//
// ^FILE   : FieldDetails.cpp
// ^AUTHOR : Jerry Leenerts
// ^DATE   : 03/02/1999
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : FieldDetails
//    
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

// BPBASE_DLL not defined here because should not be used outside of this dll

#include "BPGlobal.h"
#include "FieldDetails.hpp"
#include <bfcbo\BFAbstractCBO.hpp>
#include <bfcbo\BFProperties.hpp>
#include <IDIString.hpp>

#include <bfdata\bfdatafieldproperties.hpp>
#include <bfutil\clientlocalecontext.hpp>

#include <assert.h>

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "FieldDetails" );

   const I_CHAR * const COPYCONSTRUCTOR = I_( "( FieldDetails & )" );
   const I_CHAR * const GETCBOINSTANCE = I_( "getCBOInstance" );
   const I_CHAR * const GETERRORS = I_( "getErrors" );
   const I_CHAR * const GETFIELD = I_( "getField" );
   const I_CHAR * const GETFIELDATTRIBUTES = I_( "getFieldAttributes" );
   const I_CHAR * const SETFIELD = I_( "setField" );

   const I_CHAR *  const FIELD = I_( "FIELD" );
   const I_CHAR * const ID = I_( "ID" );
}

namespace CND
{  // Conditions used
   extern const long BP_ERR_CANNOT_SET_CBO;
   extern const long BP_ERR_CBO_NOT_SET;
   extern const long BP_ERR_FIELD_DEFINED_IN_LIST_AND_CBO;
   extern const long BP_ERR_GETFIELD_FAILED;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

FieldDetails::FieldDetails( const BFContainerId& idContainer,
                            const BFFieldId &fieldID,
                            E_FIELDPROCESSFLAG flag,
                            const I_CHAR *szTag ) 
: _eProcessFlags( flag )
, idContainer_( idContainer )
, idField_( fieldID )
, _strName( szTag )
{  // Make sure ID within range
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}

//******************************************************************************

FieldDetails::FieldDetails( const FieldDetails &rhs ) 
: _eProcessFlags( rhs._eProcessFlags )
, idContainer_( rhs.idContainer_ )
, idField_( rhs.idField_ )
, _strName( rhs._strName )
{
   TRACE_CONSTRUCTOR( CLASSNAME, COPYCONSTRUCTOR );
}

//******************************************************************************

FieldDetails::~FieldDetails()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************

SEVERITY FieldDetails::getErrors( BFAbstractCBO *rpPtr,
                                  const BFDataGroupId& idDataGroup,
                                  CONDITIONVECTOR &conditions )
{
   if( rpPtr )
   {
      return(rpPtr->getErrors( idField_, idDataGroup, conditions )); 
   }
   else
   {
      assert( 0 );
      DString strIDI;
      addIDITagValue( strIDI, FIELD, getFieldName() );
      THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, GETERRORS,
                         CND::BP_ERR_GETFIELD_FAILED, strIDI );
   }
}

//******************************************************************************

void FieldDetails::getField( BFAbstractCBO *rpPtr,
                             bool bFormattedFlag,
                             DString &strValueOut,
                             const BFDataGroupId& idDataGroup )
{
   if( rpPtr )
   {
      rpPtr->getField( idField_, strValueOut, idDataGroup, bFormattedFlag ); 
   }
   else
   {
      assert( 0 );
      DString strIDI;
      addIDITagValue( strIDI, FIELD, getFieldName() );
      THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, GETFIELD,
                         CND::BP_ERR_GETFIELD_FAILED, strIDI );
   }
}

//******************************************************************************

const BFProperties *FieldDetails::getFieldAttributes( BFAbstractCBO *rpPtr,
                                                      const BFDataGroupId& idDataGroup )
{
   if( rpPtr )
   {
      return(rpPtr->getFieldProperties( idField_, idDataGroup )); 
   }
   else
   {
      assert( 0 );
      DString strIDI;
      addIDITagValue( strIDI, FIELD, getFieldName() );
      THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, GETFIELDATTRIBUTES,
                         CND::BP_ERR_GETFIELD_FAILED, strIDI );
   }
}

//******************************************************************************

const DString &FieldDetails::getFieldName()
{
   if( _strName == NULL_STRING )
   {  // lazy initialization is used here - try to get from data dictionary
//CP20041210      const BFDataFieldProperties* pProps = BFDataFieldProperties::get( getFieldID() );
//CP20041210      if( NULL != pProps )
//CP20041210      {
//CP20041210         _strName = pProps->getLabel( ClientLocaleContext::get() );
//CP20041210      }
      _strName = idField_.getName();
   }
   return(_strName);
}

//******************************************************************************

SEVERITY FieldDetails::setField( void *rpPtr,
                                 bool bFormattedFlag,
                                 const DString &strValue,
                                 const BFDataGroupId& idDataGroup )
{
   BFAbstractCBO *rpBase = static_cast< BFAbstractCBO *>( rpPtr );
   if( rpBase )
   {
      return(rpBase->setField( idField_, strValue, idDataGroup , bFormattedFlag, false ));
   }
   assert( 0 );
   DString strIDI;
   addIDITagValue( strIDI, FIELD, getFieldName() );
   THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, SETFIELD,
                      CND::BP_ERR_GETFIELD_FAILED, strIDI );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/bfproc/FieldDetails.cpp-arc  $
//
//   Rev 1.10   Dec 10 2004 10:42:50   purdyech
//PET910 - get the proper field name when one is not specified
 * 
 *    Rev 1.9   Jan 06 2003 16:43:40   PURDYECH
 * BFDataGroupId and BFContainerId changeover
 * 
 *    Rev 1.8   Oct 09 2002 17:40:56   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.7   Aug 29 2002 14:05:22   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.6   Aug 29 2002 12:51:10   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.5   May 28 2002 12:16:14   PURDYECH
 * BFData Implementation - Phase II
 * 
 *    Rev 1.4   22 May 2002 17:57:02   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.3   Aug 02 2000 15:31:32   BUZILA
 * "locale" changes
 * 
 *    Rev 1.2   Jun 13 2000 17:41:30   DT24433
 * new Infra interfaces use ClientLocale
 * 
 *    Rev 1.1   Apr 13 2000 09:54:02   BUZILA
 * added #define BPBASE_DLL
 * 
 *    Rev 1.0   Feb 15 2000 10:57:36   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.11   Jan 20 2000 14:38:06   DT24433
 * added formatting parm to BFBase::setField call
 * 
 *    Rev 1.10   Nov 19 1999 17:30:42   DT24433
 * changed return on getErrors
 * 
 *    Rev 1.9   Nov 11 1999 08:50:08   DT24433
 * added getFieldAttributes
 * 
 *    Rev 1.8   Nov 05 1999 15:23:08   DT24433
 * added getErrors
 * 
 *    Rev 1.7   21 Oct 1999 08:41:56   HSUCHIN
 * Changed getField parm from void * to BFBase *.
 * 
 *    Rev 1.6   Sep 21 1999 11:23:12   DT24433
 * removed unused constructor
 * 
 *    Rev 1.5   Sep 20 1999 10:19:46   BUZILA
 * changet get field to return void
 * 
 *    Rev 1.4   Aug 05 1999 15:29:36   DT24433
 * misc
 * 
 *    Rev 1.3   Aug 03 1999 15:00:14   DT24433
 * container changes
 * 
 *    Rev 1.2   Jul 20 1999 11:14:04   VASILEAD
 * New conditions update
 * 
 *    Rev 1.1   Jul 08 1999 10:02:02   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
