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
// ^FILE   : AbstractListDetails.cpp
// ^AUTHOR : Jerry Leenerts
// ^DATE   : 03/02/1999
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : AbstractListDetails
//    
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "bpglobal.h"
#include "abstractlistdetails.hpp"
#include <bfcbo\bfcbo.hpp>
#include <idistring.hpp>
#include <assert.h>

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "AbstractListDetails" );

   const I_CHAR * const COPYCONSTRUCTOR = I_( "AbstractListDetails &" );
   const I_CHAR * const ADDITEM= I_( "addItem" );
   const I_CHAR * const COMMIT = I_( "commit" );
   const I_CHAR * const DELETEITEM = I_( "deleteItem" );
   const I_CHAR * const GETCONTAINER = I_( "getContainer" );
   const I_CHAR * const ISNEWITEM = I_( "isNewItem" );
   const I_CHAR * const RESET = I_( "reset" );
   const I_CHAR * const SETKEYFILTER     = I_("setKeyFilter");
   const I_CHAR * const GETKEYFILTER     = I_("getKeyFilter");
   const I_CHAR * const CLEARKEYFILTER   = I_("clearKeyFilter");
   const I_CHAR * const SETDATAFILTER    = I_("setDataFilter");
   const I_CHAR * const GETDATAFILTER    = I_("getDataFilter");
   const I_CHAR * const CLEARDATAFILTER  = I_("clearDataFilter");
   const I_CHAR * const ISDUMMYCURRENTITEM = I_( "isDummyCurrentItem" );
   const I_CHAR * const RESETCURRENTITEM = I_( "resetCurrentItem" );
   // Literals
   const I_CHAR * const ID = I_( "ID" );
}

namespace CND
{  // Conditions used
   extern const long BP_ERR_ID_OUT_OF_RANGE;
   extern const long BP_ERR_LIST_NOT_VALID;
   extern const long BP_ERR_INVALID_METHOD_CALL;
}

const DString AbstractListDetails::_strEmpty;

//******************************************************************************
//              Public Methods
//******************************************************************************

AbstractListDetails::AbstractListDetails( const BFContainerId& idContainer,
                                          const BFContainerId& idParentContainer,
                                          bool bRepeatable,
                                          bool bUpdatable,
                                          const DString &name ) 
: _bHasChildren( false )
, _bRepeatable( bRepeatable )
, _bUpdatable( bUpdatable )
, idContainer_( idContainer )
, _name( name )
, idParentContainer_( idParentContainer )
, _rpContainer( NULL )
{  // Make sure ID within range
//   EXECHIST2( I_("AbstractListDetails"), 
//              I_( "AbstractListDetails( const BFContainerId &, const BFContainerId &, bool, bool, const DString & )" ) );


   if( idContainer_ == BF::NullContainerId )
   {  // Container ID must not be 0
      assert( 0 );
      DString strIDI;
      addIDITagValue( strIDI, ID, idContainer_.getId() );
      THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, CLASSNAME,
                         CND::BP_ERR_ID_OUT_OF_RANGE, strIDI );
   }
}

//******************************************************************************

AbstractListDetails::~AbstractListDetails()
{
//   EXECHIST2( I_("AbstractListDetails"), 
//              I_( "~AbstractListDetails(  )" ) );


   _rpContainer = NULL;
}

//******************************************************************************

const DString &AbstractListDetails::addItem( const BFDataGroupId& idDataGroup )
{  // Default processing is to fail
   assert( 0 );   
   THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, ADDITEM,
                   CND::BP_ERR_INVALID_METHOD_CALL );
}

//******************************************************************************

SEVERITY AbstractListDetails::commit( const BFDataGroupId& idDataGroup )
{  // Default processing is to fail
   assert( 0 );   
   THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, COMMIT,
                   CND::BP_ERR_INVALID_METHOD_CALL );
}

//******************************************************************************

SEVERITY AbstractListDetails::deleteItem( const BFDataGroupId& idDataGroup )
{  // Default processing is to fail
   assert( 0 );   
   THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DELETEITEM,
                   CND::BP_ERR_INVALID_METHOD_CALL );
}

//******************************************************************************

void *AbstractListDetails::getItem( const BFDataGroupId& idDataGroup, const DString* pKey )
{
   if( _rpContainer )
   {
      return(_rpContainer);
   }

   // Not valid - no container
   assert( 0 );
   DString strIDI;
   addIDITagValue( strIDI, ID, getContainerID().getId() ) ;
   THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, GETCONTAINER,
                      CND::BP_ERR_LIST_NOT_VALID, strIDI );
}

//******************************************************************************

void *AbstractListDetails::getContainer()
{
   return(_rpContainer);
}

//******************************************************************************

bool AbstractListDetails::isNewItem( const BFDataGroupId& idDataGroup )
{  // Default processing is to fail
   assert( 0 );   
   THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, ISNEWITEM,
                   CND::BP_ERR_INVALID_METHOD_CALL );
}

//******************************************************************************

bool AbstractListDetails::isDummyCurrentItem( const BFDataGroupId& idDataGroup )
{
   assert( 0 );   
   THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, ISDUMMYCURRENTITEM,
                   CND::BP_ERR_INVALID_METHOD_CALL );
}

//******************************************************************************

SEVERITY AbstractListDetails::reset( const BFDataGroupId& idDataGroup, bool bCurrentItem )
{  // Default processing is to fail
   assert( 0 );   
   THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, RESET,
                   CND::BP_ERR_INVALID_METHOD_CALL );
}

//******************************************************************************

SEVERITY AbstractListDetails::resetCurrentItem( const BFDataGroupId& idDataGroup )
{  // Default processing is to fail
   assert( 0 );   
   THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, RESETCURRENTITEM,
                   CND::BP_ERR_INVALID_METHOD_CALL );
}

//******************************************************************************

bool AbstractListDetails::setContainer( void *rpContainer )
{
   bool bRtn = false;

   if( _rpContainer != rpContainer )
   {  // Make sure something changing
      _rpContainer = rpContainer;
      bRtn = true;
      if( _rpContainer && isRepeatable() )
      {  // Non-NULL, Try to set iterator to first of list
         const DString *rpStr = NULL;    // For dummy argument
         getFirstKey( &rpStr, BF::HOST );
      }
   }
   return(bRtn);
}

//******************************************************************************

bool AbstractListDetails::setKeyFilter( const DString& filter )
{
   // Default implementation should not ever be called
   assert( 0 );
   THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, SETKEYFILTER,
                   CND::BP_ERR_INVALID_METHOD_CALL );
   return(false);
}

//******************************************************************************

void AbstractListDetails::getKeyFilter( DString& filter )
{
   // Default implementation should not ever be called
   assert( 0 );
   THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETKEYFILTER,
                   CND::BP_ERR_INVALID_METHOD_CALL );
}

//******************************************************************************

void AbstractListDetails::clearKeyFilter()
{
   // Default implementation should not ever be called
   assert( 0 );
   THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, CLEARKEYFILTER,
                   CND::BP_ERR_INVALID_METHOD_CALL );
}

//******************************************************************************

bool AbstractListDetails::setDataFilter( const DString& filter )
{
   // Default implementation should not ever be called
   assert( 0 );
   THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, SETDATAFILTER,
                   CND::BP_ERR_INVALID_METHOD_CALL );
   return(false);
}

//******************************************************************************

void AbstractListDetails::getDataFilter( DString& filter )
{
   // Default implementation should not ever be called
   assert( 0 );
   THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETDATAFILTER,
                   CND::BP_ERR_INVALID_METHOD_CALL );
}

//******************************************************************************

void AbstractListDetails::clearDataFilter( )
{
   // Default implementation should not ever be called
   assert( 0 );
   THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, CLEARDATAFILTER,
                   CND::BP_ERR_INVALID_METHOD_CALL );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/core/bfproc/AbstractListDetails.cpp-arc  $
//
//   Rev 1.12   Feb 20 2009 14:48:26   purdyech
//ZTS Revision 6
//
//   Rev 1.11   May 24 2003 14:55:38   PURDYECH
//Add facility to get item by key without altering "current" item
 * 
 *    Rev 1.10   Jan 06 2003 16:42:58   PURDYECH
 * BFDataGroupId and BFContainerId changeover
 * 
 *    Rev 1.9   Oct 09 2002 17:40:48   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.8   Aug 29 2002 13:51:50   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.7   22 May 2002 17:57:00   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.6   Jul 27 2001 17:24:18   ROSIORUC
 * Modified getContainer() method that can return also
 * a null pointer.
 * 
 *    Rev 1.5   26 Jul 2001 13:43:44   YINGZ
 * fix reset, cancel problems
 * 
 *    Rev 1.4   Dec 13 2000 13:21:32   KOVACSRO
 * Added a method to check if current item is dummy.
 * 
 *    Rev 1.3   Nov 08 2000 19:54:16   DT24433
 * added list name support
 * 
 *    Rev 1.2   Apr 13 2000 09:54:34   BUZILA
 * uncommented #define BPBASE_DLL
 * 
 *    Rev 1.1   Mar 23 2000 16:23:44   BUZILA
 * CBO filtering implemented
 * 
 *    Rev 1.0   Feb 15 2000 10:57:34   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.11   Dec 08 1999 16:14:44   DT24433
 * added isNewItem
 * 
 *    Rev 1.10   Nov 22 1999 17:59:06   DT24433
 * performance improvements
 * 
 *    Rev 1.9   Oct 28 1999 16:47:06   DT24433
 * added commit method
 * 
 *    Rev 1.8   Oct 28 1999 13:48:22   VASILEAD
 * add/delete/reset & group processing
 * 
 *    Rev 1.7   Aug 06 1999 10:10:06   DT24433
 * support change item detection
 * 
 *    Rev 1.6   Aug 05 1999 15:09:50   DT24433
 * added bool return to setContainer
 * 
 *    Rev 1.5   Aug 03 1999 14:40:52   DT24433
 * container changes
 * 
 *    Rev 1.4   Jul 20 1999 11:13:26   VASILEAD
 * New conditions update
 * 
 *    Rev 1.3   Jul 08 1999 10:01:44   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
