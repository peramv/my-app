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
// ^FILE   : RevisionListControl.cpp
// ^AUTHOR : David Smith
// ^DATE   : 
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : RevisionListControl
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#define WIN32UIBASE_DLL

#include "stdafx.h"

#ifndef REVISIONLISTCONTROL_HPP
   #include "RevisionListControl.hpp"
#endif

#include <bfutil\RTSourceRevision.hpp>
#include <bfutil\RTHeaderRevision.hpp>

namespace
{
   const I_CHAR *REV_HEADER1 = I_( "Achive Path" );
   const I_CHAR *REV_HEADER2 = I_( "Revision" );
}

RevisionListControl::RevisionListControl() :
CListCtrl(),
RTRevisionReport(),
_itemCount(0)
{
}

RevisionListControl::~RevisionListControl()
{
}

void RevisionListControl::Init()
{
   InsertColumn( 0, REV_HEADER1, LVCFMT_LEFT, 450 );
   InsertColumn( 1, REV_HEADER2, LVCFMT_LEFT, 100 );

   report();
}

void RevisionListControl::reportSourceRevision( const RTRevision * const revsion )
{
   int idx = InsertItem( _itemCount++, I_( "" ) );

   SetItemText( idx, 0, DString( DStringA( revsion->getArchiveFile() ) ).c_str() );
   SetItemText( idx, 1, DString( DStringA( revsion->getRevision() ) ).c_str() );
   idx++;
}

void RevisionListControl::reportHeaderRevision( const RTRevision * const revsion )
{
   int idx = InsertItem( _itemCount++, I_( "" ) );

   SetItemText( idx, 0, DString( DStringA( revsion->getArchiveFile() ) ).c_str() );
   SetItemText( idx, 1, DString( DStringA( revsion->getRevision() ) ).c_str() );
   idx++;
}

void RevisionListControl::DrawItem(LPDRAWITEMSTRUCT)
{
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/uibase/RevisionListControl.cpp-arc  $
// 
//    Rev 1.1   Oct 09 2002 17:42:54   PURDYECH
// New PVCS Database
// 
//    Rev 1.0   03 Jul 2001 15:51:50   SMITHDAV
// Initial revision.
 */