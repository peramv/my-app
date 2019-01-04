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
//    Copyright 1999 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : BFSession.cpp
// ^AUTHOR : David Smith
// ^DATE   : 
//
//******************************************************************************

#include <srcprag.h>
#include "bfsession.hpp"

//******************************************************************************
BFSessionTempData::BFSessionTempData(long workDataSetId)
: _tempData( workDataSetId )
{
}

//******************************************************************************
BFSessionTempData::~BFSessionTempData() {
}

//******************************************************************************
void BFSessionTempData::getField( const BFFieldId &fieldID, DString &strValueOut ) const
{
   _tempData.getElementValue( fieldID, strValueOut );
   strValueOut.stripTrailing();
}

//******************************************************************************
void BFSessionTempData::clear()
{  // Clear everything except properties of global data set
   _tempData.resetValue();
}

//******************************************************************************
void BFSessionTempData::setField( const BFFieldId &fieldID, const DString &strValue )
{
   bool bRtn = false;

   bRtn = _tempData.setElementValue( fieldID, strValue );

   if( !bRtn )
   {
      assert( 0 );
      DString strIDI;
      addIDITagValue( strIDI, I_( "FIELD" ), strValue ); 
      //THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, SETGLOBAL,
                         //CND::BP_ERR_SETFIELD_FAILED, strIDI );
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/bfcbo/bfsession.cpp-arc  $
// 
//    Rev 1.0   May 14 2004 13:25:50   SMITHDAV
// Initial revision.
*/
