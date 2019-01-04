// KEASession.h: interface for the KEASession class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_KEASESSION_H__INCLUDED_)
#define _KEASESSION_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "stdafx.h"
#include <keasession\keavt.h>
#include <tesession\tesession.h>
#include <keasession\keascreen.h>

class KEASession : public TESession
{
public:
   KEASession();
   virtual ~KEASession();

   bool init(const char *host);

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

   virtual long setStreamTextWait(const std::string &text);
   virtual long setDisplayTextWait(const std::string &text, TEPosition &position);
   virtual long setCursorWait(TEPosition &position);
   virtual long setDoneWait();
   virtual long setSilenceWait(long duration);
   virtual long wait(long timeout);

   virtual TEPosition &getCursorPosition(TEPosition &position);
   virtual TESelection &getCurrentSelection(TESelection &selection);

   virtual std::string &getDisplayText(const TESelection &selection, std::string &buffer);
   virtual bool findDisplayText(const std::string &text, TEPosition &position);

   virtual void invokeCancel();

private:
   KEAScreen *screen;
   KEADispatch::Session ksession;

};

#endif // !defined(_KEASESSION_H__INCLUDED_)
