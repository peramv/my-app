#include "stdafx.h"

#include "Console.hpp"
#include "ConsoleCanvas.hpp"


Console *Console::instance = NULL;

Console *
Console::getInstance( bool bQuiet /* = false */ )
{
   if( NULL == instance )
      instance = new Console( bQuiet );

   return(instance);
}

void 
Console::killInstance()
{
   delete instance;
   instance = NULL;
}

ConsoleCanvas *
Console::createCanvas( int height, bool bBorder /*=true*/ )
{
   if( true == _bQuiet )
   {
      // whole console is 'quiet', so make this canvas quiet also
      return( new ConsoleCanvas( INVALID_HANDLE_VALUE, 0, 0, 0, true ) );
   }

   int iBorderHeight = bBorder == true ? 1 : 0;

   // increase the size if neccessary
   CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
   ::GetConsoleScreenBufferInfo( _mainBufferHandle, &screenBufferInfo );

   int width = screenBufferInfo.dwSize.X;
   if( screenBufferInfo.dwSize.Y < _nextStartLine+height+2 )
   {
      screenBufferInfo.dwSize.Y = _nextStartLine+height+2;
      ::SetConsoleScreenBufferSize( _mainBufferHandle, screenBufferInfo.dwSize );

      SMALL_RECT windowRect = {0, 0, screenBufferInfo.dwSize.X-1, screenBufferInfo.dwSize.Y-1};
      ::SetConsoleWindowInfo(_mainBufferHandle, TRUE, &windowRect);
   }

   if( true == bBorder )
   {
      DWORD written;
      COORD coord = {0, _nextStartLine+height};
      ::SetConsoleCursorPosition( _mainBufferHandle, coord);

      char* pszDashes = new char[ width + 1 ];
      memset( pszDashes, '-', width );
      pszDashes[ width ] = 0x00;

      ::WriteConsole( _mainBufferHandle,
                      pszDashes,
                      width,
                      &written, 
                      NULL);
      delete[] pszDashes;
   }

   ConsoleCanvas *canvas = new ConsoleCanvas(_mainBufferHandle, _nextStartLine, width, height);
   _nextStartLine+= height + iBorderHeight;

   return(canvas);
}

enum Console::Mode 
Console::toggleModes()
{
   if( isQuiet() ) return MESSAGE;

   enum Mode eOrigMode = eMode_;
   if( eMode_ == MAIN )
      setMode(MESSAGE);
   else
      setMode(MAIN);
   return( eOrigMode );
}

void
Console::setMode(Mode newMode)
{
   if( isQuiet() ) return;

   if( newMode == MESSAGE )
   {
      ::SetConsoleActiveScreenBuffer(_messageBufferHandle);
      eMode_ = MESSAGE;
   }
   else
   {
      ::SetConsoleActiveScreenBuffer(_mainBufferHandle);
      eMode_ = MAIN;
   }
}

enum Console::Mode Console::getMode() const
{
   return eMode_;
}

void Console::setTitle( const DString &title ) {
   ::SetConsoleTitle( title.asA().c_str() );

}

Console::Console( bool bQuiet )
: _ownConsole( false )
, eMode_( MESSAGE )
, _bQuiet( bQuiet )
, _nextStartLine( 0 )
{
   if( false == isQuiet() )
   {
      _messageBufferHandle = ::GetStdHandle(STD_OUTPUT_HANDLE);
      _mainBufferHandle = ::CreateConsoleScreenBuffer( GENERIC_WRITE | GENERIC_READ, 
                                                       0, 
                                                       NULL, 
                                                       CONSOLE_TEXTMODE_BUFFER, 
                                                       NULL);


      // turn the cursor off
      CONSOLE_CURSOR_INFO cursorInfo;
      cursorInfo.bVisible = FALSE; 
      cursorInfo.dwSize = 100;
      ::SetConsoleCursorInfo(_mainBufferHandle,  &cursorInfo);
      ::SetConsoleCursorInfo(_messageBufferHandle,  &cursorInfo);

      ::SetConsoleActiveScreenBuffer(_mainBufferHandle);
      eMode_ = MAIN;
   }
}

Console::~Console()
{
   if( false == isQuiet() )
   {
      // turn the cursor on
      CONSOLE_CURSOR_INFO cursorInfo;
      cursorInfo.bVisible = TRUE; 
      cursorInfo.dwSize = 25;
      ::SetConsoleCursorInfo(_messageBufferHandle,  &cursorInfo);

      ::SetConsoleActiveScreenBuffer(_messageBufferHandle);
      eMode_ = MESSAGE;

      ::CloseHandle(_mainBufferHandle);
   }
}

