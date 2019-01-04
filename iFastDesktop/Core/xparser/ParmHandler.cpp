/*******************************************************************************
 *
 * COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 2000 by DST Systems, Inc.
 *
*******************************************************************************/
#include "stdafx.h"
#include "ParmHandler.hpp"
#include "ClassAttribute.hpp"
#include <bfproc\GenericInterfaceContainer.hpp>
#include <bfproc\InterProcessData.hpp>
#include <bfproc\AbstractProcess.hpp>

using namespace xp;

//******************************************************************************
ParmHandler::ParmHandler( ElementHandler *parentHandler, const DString &elementName, xercesc::AttributeList &attributes ) :
ElementHandler( parentHandler, elementName, ClassAttribute::PARM ),
_cache( attributes ),
_formatted( I_("formatted"), attributes, true ),
_text()
{
   _text.reserve(64);
}

//******************************************************************************
void ParmHandler::execute( GenericInterfaceContainer& gic, BFDocument &out )
{
   Writer writer( *this, out );

   switch( _cache )
   {
      case CacheAttribute::CACHE_GET:
         _text = cacheGet();
         break;
      case CacheAttribute::CACHE_PUT:
         cachePut( _text );
         break;
   }

   gic.getInterProcessData().setParameter( getName(), _text );

}

//******************************************************************************
void ParmHandler::executeAndCache( GenericInterfaceContainer& gic, BFDocument &out )
{
   Writer writer( *this, out );

   cachePut( _text );

   gic.getInterProcessData().setParameter( getName(), _text );
}

//******************************************************************************
void ParmHandler::executeAndCache( BFDocument &out )
{
   Writer writer( *this, out );

   cachePut( _text );
}


//******************************************************************************
const DString &ParmHandler::getText() const
{
   return(_text);
}

//******************************************************************************
ElementAttributeList &ParmHandler::getAttributes( ElementAttributeList &attributes ) const
{
   attributes.add( getElementClass() );
   attributes.add( _formatted );
   attributes.add( _cache );
   return(attributes);
}

//******************************************************************************
void ParmHandler::appendText( const XMLCh * const chars, const unsigned int length )
{
   _text += (wchar_t*)chars;
}

//******************************************************************************
void ParmHandlerList::execute( GenericInterfaceContainer& gic, BFDocument &out )
{
   iterator i = begin();
   while( i != end() )
   {
      (*i)->execute( gic, out );
      i++;
   }
}

//******************************************************************************
void ParmHandlerList::executeAndCache( GenericInterfaceContainer& gic, BFDocument &out )
{
   iterator i = begin();
   while( i != end() )
   {
      (*i)->executeAndCache( gic, out );
      i++;
   }
}

//******************************************************************************
void ParmHandlerList::executeAndCache( BFDocument &out )
{
   iterator i = begin();
   while( i != end() )
   {
      (*i)->executeAndCache( out );
      i++;
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/xparser/ParmHandler.cpp-arc  $
//
//   Rev 1.8   May 14 2004 16:15:36   SMITHDAV
//Made changes related to GIC interface changes, and made Process object const correct.
//
//   Rev 1.7   Mar 09 2004 11:01:02   PURDYECH
//PET910 - Xerces2 support.
//
//   Rev 1.6   Mar 05 2004 13:28:32   SMITHDAV
//Fix stupid class initialization bugs.
// 
//    Rev 1.5   Oct 09 2002 17:43:16   PURDYECH
// New PVCS Database
// 
//    Rev 1.4   Sep 19 2002 09:28:36   IVESPAUL
// Adapted the transaction stats to write results using XML ElementWriter.  Moved ElementAttribute and ElementWriter to BFUtil.
//
//    Rev 1.3   Aug 02 2002 17:13:40   SMITHDAV
// Major EBF to deal with post-commit data outputs using abstract document model and random access document implementation.
//
//    Rev 1.2   14 May 2002 16:42:58   SMITHDAV
// put xparser code namespace xp.
//
//    Rev 1.1   01 May 2002 17:16:48   SMITHDAV
// Simple writer changes. Add TxnStats. And Fix key handling for CBO add and replace ations.
//
//    Rev 1.0   02 Apr 2002 13:50:06   SMITHDAV
// Initial revision.
 *
 */