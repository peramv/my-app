#pragma once

// Import/Export resolution
#undef BFUTIL_LINKAGE
#ifdef BFUTIL_DLL
   #define BFUTIL_LINKAGE CLASS_EXPORT
#else
   #define BFUTIL_LINKAGE CLASS_IMPORT
#endif

class Console;

class BFUTIL_LINKAGE ConsoleColor
{
public:
   ConsoleColor(WORD bgAttrs, WORD fgAttrs);

   static const ConsoleColor BLACK;
   static const ConsoleColor BRIGHT_WHITE;
   static const ConsoleColor WHITE;

   static const ConsoleColor RED;
   static const ConsoleColor GREEN;
   static const ConsoleColor BLUE;
   static const ConsoleColor CYAN;
   static const ConsoleColor MAGENTA;
   static const ConsoleColor YELLOW;

   static const ConsoleColor DARK_RED;
   static const ConsoleColor DARK_GREEN;
   static const ConsoleColor DARK_BLUE;
   static const ConsoleColor DARK_CYAN;
   static const ConsoleColor DARK_MAGENTA;
   static const ConsoleColor DARK_YELLOW;

private:

   WORD _bgAttrs;
   WORD _fgAttrs;

   friend class ConsoleCanvas;
};

class BFUTIL_LINKAGE ConsoleCanvas
{
public:
   ~ConsoleCanvas();

   void setDefaultForgroundColor( const ConsoleColor &color );
   void setDefaultBackgroundColor( const ConsoleColor &color );

   int getWidth() { return(_width);}
   int getHeight()  { return(_height);}
   void write(int col, int row, const ConsoleColor &bgColor, const ConsoleColor &fgColor, const char *format, ...);
   void write(int col, int row, const char *format, ...);

   void highlight(int col, int row, int length, const ConsoleColor &bgColor, const ConsoleColor &fgColor);

   void clear( int col1, int row1, int col2, int row2 );
   void clearLine( int row, int lines = 1 );
   void clearAll();

   void update();

   inline bool isQuiet() const { return(_bQuiet);}

private: 
   ConsoleCanvas(HANDLE displayBuffer, int startLine, int width, int height, bool bQuiet = false );

   HANDLE   _displayBuffer;
   HANDLE   _workBuffer;
   bool     _bQuiet;
   int      _startLine;
   int      _width;
   int      _height;

   friend class Console;
   ConsoleColor _defaultForgroundColor;
   ConsoleColor _defaultBackgroundColor;
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   //db3n5j11/d/scc/ifds/core/archives/bfutil/ConsoleCanvas.hpp-arc  $
//
//   Rev 1.3   Oct 09 2002 17:41:26   PURDYECH
//New PVCS Database
//
//   Rev 1.2   20 Sep 2001 09:56:26   PURDYECH
//Added a 'quiet' ctor parameter.  This allows the console to be created such that it doesn't do anything. 
//
//   Rev 1.1   Jul 03 2001 15:34:46   PURDYECH
//added clear* methods from FAST
//
//   Rev 1.0   Jun 26 2001 12:03:48   PURDYECH
//Initial revision.
//
