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
#include "ElementHandlerFactory.hpp"
#include "BatchHandler.hpp"
#include "ParmHandler.hpp"
#include "ProcessHandler.hpp"
#include "CBOHandler.hpp"
#include "KeyHandler.hpp"
#include "FieldHandler.hpp"

using namespace xp;

ElementHandlerFactory *ElementHandlerFactory::s_instance = NULL;

//******************************************************************************
void ElementHandlerFactory::registerInstance(ElementHandlerFactory *instance)
{
   delete s_instance;
   s_instance = instance;
}

//******************************************************************************
void ElementHandlerFactory::killInstance()
{
   delete s_instance;
   s_instance = NULL;
}

//******************************************************************************
ElementHandlerFactory *ElementHandlerFactory::getInstance()
{
   assert( s_instance != NULL );
   return(s_instance);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/xparser/ElementHandlerFactory.cpp-arc  $
// 
//    Rev 1.2   Oct 09 2002 17:43:14   PURDYECH
// New PVCS Database
// 
//    Rev 1.1   14 May 2002 16:42:56   SMITHDAV
// put xparser code namespace xp.
// 
//    Rev 1.0   02 Apr 2002 13:50:04   SMITHDAV
// Initial revision.
 * 
 */
