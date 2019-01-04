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
#include "KeyHandler.hpp"
#include "ClassAttribute.hpp"
#include <bfproc\AbstractProcess.hpp>
#include <bfdata\BFData.hpp>

using namespace xp;

namespace
{
   const I_CHAR * const CLASSNAME  = I_("KeyHandler");
}

//******************************************************************************
KeyHandler::KeyHandler( ElementHandler *parentHandler, const DString &elementName ) :
ElementHandler( parentHandler, elementName, ClassAttribute::KEY ),
_fieldList()
{
}

//******************************************************************************
bool KeyHandler::executeLookup( AbstractProcess *process, const BFContainerId& idContainer, BFDocument &out )
{
   Writer writer( *this, out );

   BFData keyInfo;
   _fieldList.execute( keyInfo, out );

   try
   {
      process->setCurrentListItem( process, idContainer, &keyInfo );
   }
   catch( ... )
   {
      return(false);
   }

   return(true);
}

//******************************************************************************
void KeyHandler::executeSet( AbstractProcess *process, const BFContainerId& idContainer, BFDocument &out )
{
   Writer writer( *this, out );
   _fieldList.executeSet( process, idContainer, out );
}

//******************************************************************************
void KeyHandler::executeSet( AbstractProcess *process, const BFContainerId& idContainer )
{
   _fieldList.executeSet( process, idContainer );
}

//******************************************************************************
void KeyHandler::addHandler( FieldHandler *handler )
{
   _fieldList.add( handler );
}

//******************************************************************************
ElementAttributeList &KeyHandler::getAttributes( ElementAttributeList &attributes ) const
{
   attributes.add( getElementClass() );
   return(attributes);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/xparser/KeyHandler.cpp-arc  $
//
//   Rev 1.9   Mar 05 2004 13:28:32   SMITHDAV
//Fix stupid class initialization bugs.
// 
//    Rev 1.8   Jan 06 2003 16:47:38   PURDYECH
// BFContainerId changeover
// 
//    Rev 1.7   Oct 09 2002 17:43:16   PURDYECH
// New PVCS Database
// 
//    Rev 1.6   Sep 19 2002 09:28:36   IVESPAUL
// Adapted the transaction stats to write results using XML ElementWriter.  Moved ElementAttribute and ElementWriter to BFUtil.
//
//    Rev 1.5   Aug 02 2002 17:13:40   SMITHDAV
// Major EBF to deal with post-commit data outputs using abstract document model and random access document implementation.
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
//    Rev 1.1   30 Apr 2002 11:58:12   SMITHDAV
// Improve exception handling.
//
//    Rev 1.0   02 Apr 2002 13:50:06   SMITHDAV
// Initial revision.
 *
 */