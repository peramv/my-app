// TESession.h: interface for the TESession class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include <windows.h>
#include <string>

namespace tes
{
   static const int CAP_SET_VISIBLE            = 0x00000001;
   static const int CAP_SET_CONNECTED          = 0x00000002;
   static const int CAP_SEND_KEYBOARD_STRING   = 0x00000004;
   static const int CAP_SEND_KEYBOARD_SPECIAL  = 0x00000008;
   static const int CAP_STREAM_TEXT_WAIT       = 0x00000010;
   static const int CAP_DISPLAY_TEXT_WAIT      = 0x00000020;
   static const int CAP_CURSOR_WAIT            = 0x00000040;
   static const int CAP_SILENCE_WAIT           = 0x00000080;
   static const int CAP_DONE_WAIT              = 0x00000100;
   static const int CAP_MULTIPLE_WAIT          = 0x00000200;
   static const int CAP_GET_CURSOR_POSITION    = 0x00000400;
   static const int CAP_GET_CURRENT_SELECTION  = 0x00000800;
   static const int CAP_GET_DISPLAY_TEXT       = 0x00001000;
   static const int CAP_FIND_DISPLAY_TEXT      = 0x00002000;
   static const int CAP_USED                   = 0x00003FFF;
   static const int CAP_UNUSED                 = 0xFFFFFFFF & CAP_USED;

   static const long EVENT_CANCEL  = -2L;
   static const long EVENT_TIMEOUT = -1L;
   static const long EVENT_SUCCESS = 0L;

   static const long TIMEOUT_INFINITE = -1L;

   static const int POSITION_ANY = 0;

   static const int TERMINAL_HEIGHT = 24;
   static const int TERMINAL_WIDTH = 80;
}

class TEPosition
{
public:
   TEPosition() : row(1), column(1) {}
   TEPosition(int r, int c) : row(r), column(c) {}
   TEPosition(TEPosition &copy) : row(copy.row), column(copy.column) {}

   TEPosition &operator++() 
   { 
      if( column==tes::TERMINAL_WIDTH )
      {
         column=1; 
         if( row==tes::TERMINAL_HEIGHT ) row=1;
         else row++;
      }
      else column++;

      return(*this);
   }

   TEPosition &operator--() 
   { 
      if( column==1 )
      {
         column=tes::TERMINAL_WIDTH; 
         if( row==1 ) row=tes::TERMINAL_HEIGHT;
         else row--;
      }
      else column--;

      return(*this);
   }

   int row;
   int column;
};

class TESelection
{
public:
   TESelection(TEPosition &start, TEPosition &end) 
   : startPosition(start), endPosition(end) {}

   TESelection(int startRow, int startColumn, int endRow, int endColumn) 
   : startPosition(startRow, startColumn), endPosition(endRow, endColumn) {}

   TESelection() 
   : startPosition(), endPosition() {}

   TESelection(TESelection &copy) 
   : startPosition(copy.startPosition), endPosition(copy .endPosition) {}

   TEPosition startPosition;
   TEPosition endPosition;
};

class TESession  
{
public:
   virtual ~TESession() {}

   enum keys
   {
      ESC_Key = 0,
      F1_Key,
      F2_Key,
      F3_Key,
      F4_Key,
      F5_Key,
      F6_Key,
      F7_Key,
      F8_Key,
      F9_Key,
      F10_Key,
      F11_Key,
      F12_Key,
      Tab_Key,
      Return_Key,
      BS_Key,
      INSERT_Key,
      DELETE_Key,
      HOME_Key,
      END_Key,
      PGUP_Key,
      PGDN_Key,
      UP_Key,
      DOWN_Key,
      LEFT_Key,
      RIGHT_Key
   }; // if you add to this enumeration please update the Keystr array in TESession.cpp

   virtual bool getVisible() = 0;
   virtual void setVisible(bool set=true) = 0;

   virtual bool getConnected() = 0;
   virtual void setConnected(bool set=true) = 0;

   virtual void sendKeyboardString(const std::string &input) = 0;
   virtual void sendKeyboardSpecial(keys key) = 0;

   virtual long streamTextWait(long timeout, const std::string &text) = 0;
   virtual long displayTextWait(long timeout, const std::string &text, TEPosition &position) = 0;
   virtual long displayTextWait(long timeout, const std::string &text, TEPosition &startPos, TEPosition &endPos) = 0;

   virtual long cursorWait(long timeout, TEPosition &position) =0;
   virtual long silenceWait(long timeout, long duration) = 0;
   virtual long doneWait(long timeout) = 0;

//   virtual long setStreamTextWait(const std::string &text) = 0;
//   virtual long setDisplayTextWait(const std::string &text, TEPosition &position) = 0;
//   virtual long setCursorWait(TEPosition &position) =0;
//   virtual long setSilenceWait(long duration) = 0;
//   virtual long setDoneWait() = 0;

//   virtual long wait(long timeout) = 0;

   virtual TEPosition &getCursorPosition(TEPosition &position) = 0;
   virtual TESelection &getCurrentSelection(TESelection &selection) = 0;

//   virtual std::string &getDisplayText(const TEPosition &position, int length, std::string &buffer) = 0;
   virtual bool findDisplayText(const std::string &text, TEPosition &position) = 0;

   virtual void invokeCancel() =0;

private:

   HINSTANCE hModule;
   void (* releaseProc)(TESession *);


   friend class TESessionFactory;
};
