// ExtraEalSession.h: interface for the ExtraEalSession class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include <tesession\TESession.h>

class ExtraEalText;

class ExtraEalSession : public TESession  
{
public:
   ExtraEalSession( HWND hWnd );
   virtual ~ExtraEalSession();

   bool init(const char *param, const char *host);

   virtual bool getVisible();
   virtual void setVisible(bool set=true);

   virtual bool getConnected();
   virtual void setConnected(bool set=true);

   virtual void sendKeyboardString(const std::string &input);
   virtual void sendKeyboardSpecial(keys key);

   virtual long streamTextWait(long timeout, const std::string &text);
   virtual long displayTextWait(long timeout, const std::string &text, TEPosition &position);
   virtual long displayTextWait(long timeout, const std::string &text, TEPosition &startPos, TEPosition &endPos);

   virtual long cursorWait(long timeout, TEPosition &position);
   virtual long silenceWait(long timeout, long duration);
   virtual long doneWait(long timeout);

   virtual TEPosition &getCursorPosition(TEPosition &position);
   virtual bool ExtraEalSession::isCursorAt(TEPosition &position);
   virtual TESelection &getCurrentSelection(TESelection &selection);

   virtual std::string &getDisplayText(const TEPosition &position, int length, std::string &buffer) const;
   virtual bool findDisplayText(const std::string &text, TEPosition &position);

   virtual void invokeCancel();

private:

   long transformTimeout( long timeout ) const;

   HWND _hWnd;
   HWND _hSessionWnd;
   HWND _hPSWnd;
   bool _connected;
   bool _visible;
   bool _cancel;

   friend ExtraEalText;
};

class ExtraEalText
{
public:
   ExtraEalText( const std::string &origText, const ExtraEalSession &session );

   bool find( TEPosition &position ) const;
   bool find( TEPosition &position, TEPosition &endPos ) const;
   long wait(long timeout, TEPosition &position) const;
   long wait(long timeout, TEPosition &startPos, TEPosition &endPos) const;
private:

   bool verifyText( TEPosition &position ) const;

   static const int BORDER_NO;
   static const int BORDER_TL;
   static const int BORDER_TR;
   static const int BORDER_BL;
   static const int BORDER_BR;

   std::string _text;
   int _border;
   const ExtraEalSession &_session;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/tesession/extraealsession/ExtraEalSession.h-arc  $
//
//   Rev 1.3   Nov 19 2004 09:23:32   PURDYECH
//PET910 - .NET Conversion
//
//   Rev 1.2   Nov 24 2003 15:55:58   HSUCHIN
//PTS 10020087 - Enhanced to pass host information to TeSession
 */

