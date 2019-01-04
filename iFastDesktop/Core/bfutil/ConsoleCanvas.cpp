#include "stdafx.h"

#include "ConsoleCanvas.hpp"
#include "Console.hpp"
#include <stdio.h>
#include <stdarg.h>

#include <vector>
using std::vector;

const ConsoleColor ConsoleColor::BLACK(0L, 0L);
const ConsoleColor ConsoleColor::BRIGHT_WHITE(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
const ConsoleColor ConsoleColor::WHITE(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

const ConsoleColor ConsoleColor::RED(BACKGROUND_RED | BACKGROUND_INTENSITY, FOREGROUND_RED | FOREGROUND_INTENSITY);
const ConsoleColor ConsoleColor::GREEN(BACKGROUND_GREEN | BACKGROUND_INTENSITY, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
const ConsoleColor ConsoleColor::BLUE(BACKGROUND_BLUE | BACKGROUND_INTENSITY, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
const ConsoleColor ConsoleColor::CYAN(BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
const ConsoleColor ConsoleColor::MAGENTA(BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
const ConsoleColor ConsoleColor::YELLOW(BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);

const ConsoleColor ConsoleColor::DARK_RED(BACKGROUND_RED, FOREGROUND_RED);
const ConsoleColor ConsoleColor::DARK_GREEN(BACKGROUND_GREEN, FOREGROUND_GREEN);
const ConsoleColor ConsoleColor::DARK_BLUE(BACKGROUND_BLUE, FOREGROUND_BLUE);
const ConsoleColor ConsoleColor::DARK_CYAN(BACKGROUND_GREEN | BACKGROUND_BLUE, FOREGROUND_GREEN | FOREGROUND_BLUE);
const ConsoleColor ConsoleColor::DARK_MAGENTA(BACKGROUND_BLUE | BACKGROUND_RED, FOREGROUND_BLUE | FOREGROUND_RED);
const ConsoleColor ConsoleColor::DARK_YELLOW(BACKGROUND_GREEN | BACKGROUND_RED, FOREGROUND_GREEN | FOREGROUND_RED);

ConsoleColor::ConsoleColor(WORD bgAttrs, WORD fgAttrs )
:  _bgAttrs(bgAttrs),
_fgAttrs(fgAttrs)
{
}

ConsoleCanvas::ConsoleCanvas(HANDLE displayBuffer, int startLine, int width, int height, bool bQuiet /*=false*/ )
: _displayBuffer(displayBuffer)
, _workBuffer( INVALID_HANDLE_VALUE )
, _bQuiet( bQuiet )
, _startLine(startLine)
, _width(width)
, _height(height)
, _defaultForgroundColor(ConsoleColor::WHITE)
, _defaultBackgroundColor(ConsoleColor::BLACK)
{
   if( false == isQuiet() )
   {
      _workBuffer = ::CreateConsoleScreenBuffer( GENERIC_WRITE | GENERIC_READ , 
                                                 0, 
                                                 NULL, 
                                                 CONSOLE_TEXTMODE_BUFFER, 
                                                 NULL);

      // turn the cursor off
      CONSOLE_CURSOR_INFO cursorInfo;
      cursorInfo.bVisible = FALSE; 
      cursorInfo.dwSize = 100;
      ::SetConsoleCursorInfo(_workBuffer,  &cursorInfo);

      ::SetConsoleTextAttribute( _workBuffer, _defaultBackgroundColor._bgAttrs | _defaultForgroundColor._fgAttrs );
   }
}


ConsoleCanvas::~ConsoleCanvas()
{
   if( INVALID_HANDLE_VALUE != _workBuffer )
   {
      ::CloseHandle(_workBuffer);
   }
}

void 
ConsoleCanvas::setDefaultForgroundColor( const ConsoleColor &color )
{
   _defaultForgroundColor=color;
}

void
ConsoleCanvas::setDefaultBackgroundColor( const ConsoleColor &color )
{
   _defaultBackgroundColor=color;
}

void
ConsoleCanvas::write(int col, int row, const ConsoleColor &bgColor, const ConsoleColor &fgColor, const char *format, ...)
{
   if( true == isQuiet() ) return;

   va_list argptr;
   char buffer [256];

   va_start( argptr, format );     

   _vsnprintf( buffer, _width, format, argptr ); 
   buffer[_width] = (char)0;

   va_end( argptr );              

   ::SetConsoleTextAttribute( _workBuffer, bgColor._bgAttrs | fgColor._fgAttrs );

   COORD coord = {col, row};
   ::SetConsoleCursorPosition( _workBuffer, coord);

   DWORD written;
   ::WriteConsole( _workBuffer, buffer, strlen(buffer), &written, NULL);

   ::SetConsoleTextAttribute( _workBuffer, _defaultBackgroundColor._bgAttrs | _defaultForgroundColor._fgAttrs );

}

void
ConsoleCanvas::write(int col, int row, const char *format, ...)
{
   if( true == isQuiet() ) return;

   va_list argptr;
   char buffer [256];

   va_start( argptr, format );     

   _vsnprintf( buffer, _width, format, argptr ); 
   buffer[_width] = (char)0;

   va_end( argptr );              

   COORD coord = {col, row};
   ::SetConsoleCursorPosition( _workBuffer, coord);

   DWORD written;
   ::WriteConsole( _workBuffer, buffer, strlen(buffer), &written, NULL);

}

void 
ConsoleCanvas::highlight(int col, int row, int length, const ConsoleColor &bgColor, const ConsoleColor &fgColor)
{
   if( true == isQuiet() ) return;

   COORD coord = {col, row};
   DWORD written;

   vector< WORD > vAttrs;
   vAttrs.reserve( _width );

   int i;
   for( i=0; i<length && i< _width; i++ )
      vAttrs[i] = bgColor._bgAttrs | fgColor._fgAttrs;

   ::WriteConsoleOutputAttribute(_workBuffer, &vAttrs[0], i, coord, &written);
}

void 
ConsoleCanvas::clear( int col1, int row1, int col2, int row2 )
{
   if( true == isQuiet() ) return;

   for( int y=row1; y < row2; y++ )
   {
      write( col1, 
             y, 
             _defaultBackgroundColor,
             _defaultForgroundColor,
             "%.*s",
             col2 - col1, 
             "" );
   }   
}

void 
ConsoleCanvas::clearLine( int row, int lines /*= 1 */ )
{
   if( true == isQuiet() ) return;

   for( int y=0; y < lines; y++ )
   {
      write( 0, 
             row + y, 
             _defaultBackgroundColor,
             _defaultForgroundColor,
             "%*.*s",
             _width, _width,
             "" );
   }   
}

void 
ConsoleCanvas::clearAll()
{
   if( true == isQuiet() ) return;

   for( int y=0; y < _height; y++ )
   {
      write( 0, 
             y, 
             _defaultBackgroundColor,
             _defaultForgroundColor,
             "%.*s",
             _width, 
             "" );
   }   
}

void
ConsoleCanvas::update()
{
   if( true == isQuiet() ) return;

   PCHAR_INFO transBuffer = new CHAR_INFO[_width*_height];

   COORD bufferSize = {_width, _height};
   COORD position = {0, 0};
   SMALL_RECT readRegion = {0, 0, _width-1, _height-1};
   SMALL_RECT writeRegion = {0, _startLine, _width-1, _startLine+_height};
   DWORD error;

   if( FALSE ==ReadConsoleOutput( _workBuffer, transBuffer, bufferSize, position, &readRegion) )
      error = GetLastError();

   if( FALSE == WriteConsoleOutput(_displayBuffer, transBuffer, bufferSize, position, &writeRegion) )
      error = GetLastError();

   delete [] transBuffer;
}
