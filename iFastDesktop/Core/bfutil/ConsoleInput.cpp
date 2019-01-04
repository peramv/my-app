#include "stdafx.h"

#include "ConsoleInput.hpp"
#include "bfexception.hpp"

ConsoleInput::ConsoleInput()
{
   _handle = ::GetStdHandle( STD_INPUT_HANDLE );

   if( _handle == INVALID_HANDLE_VALUE )
      throw BFException();
}

ConsoleInput::~ConsoleInput()
{
}

int ConsoleInput::getChar()
{
   DWORD readCount;
   INPUT_RECORD inRecord;

   while( wait(0) )
   {

      if( FALSE == ::ReadConsoleInput( _handle, &inRecord, 1, &readCount ) || readCount == 0 )
         throw BFException();

      if( inRecord.EventType == KEY_EVENT && !inRecord.Event.KeyEvent.bKeyDown )
         return(inRecord.Event.KeyEvent.uChar.AsciiChar);

   }

   return(-1);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/bfutil/ConsoleInput.cpp-arc  $
// 
//    Rev 1.2   Oct 09 2002 17:41:26   PURDYECH
// New PVCS Database
// 
//    Rev 1.1   May 28 2002 12:15:58   PURDYECH
// BFData Implementation - Phase II
// 
//    Rev 1.0   11 Oct 2001 17:50:48   SMITHDAV
// Initial revision.
 */