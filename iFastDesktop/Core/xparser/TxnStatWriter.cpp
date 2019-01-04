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
#include "TxnStatWriter.hpp"
#include <bfutil\TxnStats.hpp>

using namespace xp;

namespace
{
//PMI-20020918   const DString STR_TXNSTATS = I_("TxnStats");
   const DString STR_ELEMENTTIME = I_("ElementTime");
}

//******************************************************************************
TxnStatWriter::TxnStatWriter( BFDocument &out, bool quiet )
: out_( out )
, quiet_( quiet )
{
}

//******************************************************************************
TxnStatWriter::~TxnStatWriter()
{
   if( !quiet_ )
   {
      TxnStats::get()->writeXML(out_);
   }
}

//******************************************************************************
ElementTimeWriter::ElementTimeWriter( BFDocument &out, bool quiet )
: timer_()
, out_( out )
, quiet_( quiet )
{
}

//******************************************************************************
ElementTimeWriter::~ElementTimeWriter()
{
   if( !quiet_ )
   {
      ElementWriter::write( out_, STR_ELEMENTTIME, asString( timer_.elapsed() ) );
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/xparser/TxnStatWriter.cpp-arc  $
//
//   Rev 1.7   Mar 02 2004 10:56:40   SMITHDAV
//Change element writers to make them mor robust.
// 
//    Rev 1.6   Oct 09 2002 17:43:24   PURDYECH
// New PVCS Database
// 
//    Rev 1.5   Sep 19 2002 09:28:44   IVESPAUL
// Adapted the transaction stats to write results using XML ElementWriter.  Moved ElementAttribute and ElementWriter to BFUtil.
//
//    Rev 1.4   Aug 02 2002 17:13:42   SMITHDAV
// Major EBF to deal with post-commit data outputs using abstract document model and random access document implementation.
//
//    Rev 1.3   07 Jun 2002 17:08:58   SMITHDAV
// Add support for root level attributes to turn on statistics writing and verbose conditions.
//
//    Rev 1.2   07 Jun 2002 10:55:28   SMITHDAV
// Sync-up with Chris' changes.
//
//    Rev 1.1   14 May 2002 16:43:00   SMITHDAV
// put xparser code namespace xp.
//
//    Rev 1.0   01 May 2002 17:18:10   SMITHDAV
// Initial revision.
 *
 */


