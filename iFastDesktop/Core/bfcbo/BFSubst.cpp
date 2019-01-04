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
// ^FILE   : BFSubst.cpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : March 30, 2000
//
// ----------------------------------------------------------
//
// ^CLASS : BFSubst
//
//******************************************************************************
#include <bfutil\RTRevisionDefines.hpp>
RT_SOURCE_REVISION( "$Archive:   //db3n5j11/d/scc/ifds/core/archives/bfcbo/BFSubst.cpp-arc  $", "$Revision:   1.3  $" )

#ifndef SRCPRAG_h
   #include <SrcPrag.h>
#endif

#ifndef BFSUBST_HPP
   #include "BFSubst.hpp"
#endif


//******************************************************************************
BFSubst::BFSubst()
{

}

//******************************************************************************
BFSubst::~BFSubst()
{
   clearSubst();
}

//******************************************************************************
void BFSubst::addSubst( const DString & dstCode, const DString & dstValue )
{
   SUBST_MAP::iterator iter = _substMap.find( dstCode );
   if( iter == _substMap.end( ) )
      _substMap.insert( SUBST_MAP::value_type( dstCode, new SubstMapEntry( dstValue, true )));
};

//******************************************************************************
void BFSubst::addSubst( const DString & dstCode, int iValue )
{
   SUBST_MAP::iterator iter = _substMap.find( dstCode );
   if( iter == _substMap.end( ) )
      _substMap.insert( SUBST_MAP::value_type( dstCode, new SubstMapEntry( DString::asString( iValue ), true )));
};

//******************************************************************************
void BFSubst::deleteSubst( const DString & dstCode )
{
   SUBST_MAP::iterator iter = _substMap.find( dstCode );
   if( iter != _substMap.end( ) )
      _substMap.erase(iter);
}

//******************************************************************************
void BFSubst::getList( DString & dstList )
{
   SUBST_MAP::iterator iter = _substMap.begin();

   dstList = NULL_STRING;
   while( iter != _substMap.end( ) )
   {
      if( (*iter).second->m_visible )
      {
         dstList += (*iter).first;
         dstList += I_("=");
         dstList += (*iter).second->m_dstValue;
         dstList += I_(";");
      };
      ++iter;
   };
}

//******************************************************************************
void BFSubst::hideSubst( const DString & dstCode )
{
   SUBST_MAP::iterator iter = _substMap.find( dstCode );
   if( iter != _substMap.end( ) )
      (*iter).second->m_visible = false;
}

//******************************************************************************
void BFSubst::showSubst( const DString & dstCode )
{
   SUBST_MAP::iterator iter = _substMap.find( dstCode );
   if( iter != _substMap.end( ) )
      (*iter).second->m_visible = true;
}

//******************************************************************************
void BFSubst::clearSubst( )
{
   SUBST_MAP::iterator iter = _substMap.begin( );
   while( iter != _substMap.end( ) )
   {
      delete (*iter).second;
      ++iter;
   };
   _substMap.clear();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/bfcbo/BFSubst.cpp-arc  $
 // 
 //    Rev 1.3   Oct 09 2002 17:40:10   PURDYECH
 // New PVCS Database
 // 
 //    Rev 1.2   03 Jul 2001 16:22:30   SMITHDAV
 // Add revision constants.
 // 
 //    Rev 1.1   03 May 2001 14:02:40   SMITHDAV
 // Session management restructuring.
 // 
 //    Rev 1.0   Apr 03 2000 08:57:28   BUZILA
 // Initial revision.
 * 
*/

