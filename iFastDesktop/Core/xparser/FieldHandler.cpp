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
#include "FieldHandler.hpp"
#include "ClassAttribute.hpp"
#include <bfproc\AbstractProcess.hpp>
#include <bfdata\bffieldid.hpp>

using namespace xp;

namespace
{
   const I_CHAR * const CLASSNAME  = I_("FieldHandler");
}

namespace CND
{
   extern const long ERR_FIELD_NOT_DEFINED;
}

//******************************************************************************
FieldHandler::FieldHandler( ElementHandler *parentHandler,
                            const DString &elementName,
                            xercesc::AttributeList &attributes,
                            bool bFieldFormatting ) :
ElementHandler( parentHandler, elementName, ClassAttribute::FIELD ),
_cache( attributes ),
_formatted( I_("formatted"), attributes, bFieldFormatting ),
_text()
{
   _text.reserve(64);
}

//******************************************************************************
void FieldHandler::execute( BFData &data, BFDocument &out )
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

   data.setElementValue( getName(), _text, true, false );

}

//******************************************************************************
void FieldHandler::executeSet( AbstractProcess *process, const BFContainerId& idContainer )
{

   switch( _cache )
   {
      case CacheAttribute::CACHE_GET:
         _text = cacheGet();
         break;
      case CacheAttribute::CACHE_PUT:
         cachePut( _text );
         break;
   }

   try
   {
      process->setField( process, idContainer, BFFieldId::getId( getName() ), _text, _formatted );
   }
   catch( BFFieldIdUnknownException )
   {
      DString strIDI;
      addIDITagValue( strIDI, I_("NAME"), getName() );

      THROWFROMFILEIDI2( CND::XPARSER_CONDITION, CLASSNAME, I_("executeSet"), CND::ERR_FIELD_NOT_DEFINED, strIDI );
   }

}

//******************************************************************************
void FieldHandler::executeSet( AbstractProcess *process, const BFContainerId& idContainer, BFDocument &out )
{
   Writer writer( *this, out );
   executeSet( process, idContainer );
}

//******************************************************************************
void FieldHandler::executeGet( AbstractProcess *process, const BFContainerId& idContainer, BFDocument &out )
{
   Writer writer( *this, out );

//DS   long fieldId = BFFieldId::getId( getName() );
//DS   if ( fieldId > 0 )
//DS   {
//DS      process->getField( process, idContainer, fieldId, _text, _formatted );
//DS   }
//DS   else
//DS   {
//DS      DString strIDI;
//DS      addIDITagValue( strIDI, I_("NAME"), getName() );
//DS
//DS      THROWFROMFILE2( CND::XPARSER_CONDITION, CLASSNAME, I_("executeSet"), CND::ERR_FIELD_NOT_DEFINED );
//DS   }

   process->getField( process, idContainer, BFFieldId::getId( getName() ), _text, _formatted );

   if( _cache == CacheAttribute::CACHE_PUT )
   {
      cachePut( _text );
   }

}

//******************************************************************************
const DString &FieldHandler::getText() const
{
   return(_text);
}

//******************************************************************************
ElementAttributeList &FieldHandler::getAttributes( ElementAttributeList &attributes ) const
{
   attributes.add( getElementClass() );
   attributes.add( _formatted );
   attributes.add( _cache );
   return(attributes);
}

//******************************************************************************
void FieldHandler::appendText( const XMLCh * const chars, const unsigned int length )
{
    _text += (wchar_t*)chars;
}

//******************************************************************************
void FieldHandlerList::execute( BFData &data, BFDocument &out )
{
   iterator i = begin();
   while( i != end() )
   {
      (*i)->execute( data, out );
      i++;
   }
}

//******************************************************************************
void FieldHandlerList::executeSet( AbstractProcess *process, const BFContainerId& idContainer )
{
   iterator i = begin();
   while( i != end() )
   {
      (*i)->executeSet( process, idContainer );
      i++;
   }
}

//******************************************************************************
void FieldHandlerList::executeSet( AbstractProcess *process, const BFContainerId& idContainer, BFDocument &out )
{
   iterator i = begin();
   while( i != end() )
   {
      (*i)->executeSet( process, idContainer, out );
      i++;
   }
}

//******************************************************************************
void FieldHandlerList::executeGet( AbstractProcess *process, const BFContainerId& idContainer, BFDocument &out )
{
   iterator i = begin();
   while( i != end() )
   {
      (*i)->executeGet( process, idContainer, out );
      i++;
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/xparser/FieldHandler.cpp-arc  $
//
//   Rev 1.13   Mar 09 2004 11:00:52   PURDYECH
//PET910 - Xerces2 support.
//
//   Rev 1.12   Mar 05 2004 13:28:28   SMITHDAV
//Fix stupid class initialization bugs.
// 
//    Rev 1.11   Jan 06 2003 16:47:32   PURDYECH
// BFContainerId changeover
// 
//    Rev 1.10   Oct 09 2002 17:43:14   PURDYECH
// New PVCS Database
// 
//    Rev 1.9   Sep 19 2002 09:28:36   IVESPAUL
// Adapted the transaction stats to write results using XML ElementWriter.  Moved ElementAttribute and ElementWriter to BFUtil.
//
//    Rev 1.8   Sep 03 2002 18:03:50   IVESPAUL
// Added "Package Level" attribute fieldFormatting, default is 'yes'.
//
//    Rev 1.7   Aug 29 2002 12:57:40   SMITHDAV
// ClientLocale and typed field changes.
//
//    Rev 1.6   Aug 02 2002 17:13:40   SMITHDAV
// Major EBF to deal with post-commit data outputs using abstract document model and random access document implementation.
//
//    Rev 1.5   Jul 05 2002 11:31:58   PURDYECH
// Include file fixups
//
//    Rev 1.4   07 Jun 2002 10:55:28   SMITHDAV
// Sync-up with Chris' changes.
//
//    Rev 1.3   14 May 2002 16:42:56   SMITHDAV
// put xparser code namespace xp.
//
//    Rev 1.2   01 May 2002 17:16:48   SMITHDAV
// Simple writer changes. Add TxnStats. And Fix key handling for CBO add and replace ations.
//
//    Rev 1.1   30 Apr 2002 11:55:10   SMITHDAV
// Add support for field writing and sub-class field writing.
//
//    Rev 1.0   02 Apr 2002 13:50:04   SMITHDAV
// Initial revision.
 *
 */