#pragma once

#include <bfutil\consoleinput.hpp>

// Import/Export resolution
#undef BFUTIL_LINKAGE
#ifdef BFUTIL_DLL
   #define BFUTIL_LINKAGE CLASS_EXPORT
#else
   #define BFUTIL_LINKAGE CLASS_IMPORT
#endif

class ConsoleCanvas;

class BFUTIL_LINKAGE Console
{
public:

   static Console *getInstance( bool bQuiet = false );
   static void killInstance();

   enum Mode
   {
      MAIN = 0,   // fancy-shmancy flashing light console
      MESSAGE     // standard cout console
   };

   ConsoleCanvas *createCanvas( int height, bool bBorder = true );
   enum Mode toggleModes();
   void setMode(Mode newMode);
   enum Mode getMode() const;

   void setTitle( const DString &title );

   inline bool isQuiet() const { return(_bQuiet);}

   ConsoleInput &getConsoleInput() { return(_consoleInput);}

private: 
   Console( bool bQuiet );
   Console( const Console &rhs );               // not implemented
   Console& operator=( const Console &rhs );    // not implemented
   ~Console();

   static Console *instance;

   bool _ownConsole;
   Mode eMode_;
   bool _bQuiet;

   int _nextStartLine;

   HANDLE _mainBufferHandle;
   HANDLE _messageBufferHandle;

   ConsoleInput _consoleInput;

};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF Core/bfutil/Console.hpp-arc  $
//
//   Rev 1.6   Jan 27 2005 10:40:18   smithdav
//Add setTitle method to set the console title bar text. 
//
//   Rev 1.5   Aug 14 2003 14:18:22   PURDYECH
//Provide inspection methods.
//
//   Rev 1.4   Oct 09 2002 17:41:24   PURDYECH
//New PVCS Database
//
//   Rev 1.3   22 Mar 2002 15:11:50   PURDYECH
//Removed compile-time "including..." message
//Use #pragma once as include guard
//Include files with lower-case only names
//
//   Rev 1.2   11 Oct 2001 17:42:16   SMITHDAV
//Add ConsoleInput support.
//
//   Rev 1.1   20 Sep 2001 09:56:26   PURDYECH
//Added a 'quiet' ctor parameter.  This allows the console to be created such that it doesn't do anything. 
//
//   Rev 1.0   Jun 26 2001 12:03:48   PURDYECH
//Initial revision.
//
