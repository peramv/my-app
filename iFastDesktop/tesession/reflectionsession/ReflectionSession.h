// ReflectionSession.h: interface for the ReflectionSession class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include <reflectionsession\r2700ex.h>
#include <tesession\TESession.h>

class ReflectionSession : public TESession  
{
public:
   ReflectionSession();
   virtual ~ReflectionSession();

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

//   virtual long setStreamTextWait(const std::string &text);
//   virtual long setDisplayTextWait(const std::string &text, TEPosition &position);
//   virtual long setCursorWait(TEPosition &position);
//   virtual long setSilenceWait(long duration);
//   virtual long setDoneWait();

//   virtual long wait(long timeout);

   virtual TEPosition &getCursorPosition(TEPosition &position);
   virtual TESelection &getCurrentSelection(TESelection &selection);

   virtual std::string &getDisplayText(const TESelection &selection, std::string &buffer);
   virtual bool findDisplayText(const std::string &text, TEPosition &position);

   virtual void invokeCancel();

private:

   static std::string &formatTimeoutString(long timeout, std::string &buffer);
   ReflectionDispatch::Reflection2 rsession;

   bool cancel;

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/tesession/reflectionsession/ReflectionSession.h-arc  $
 * 
 *    Rev 1.4   Nov 19 2004 09:21:44   PURDYECH
 * PET910 - .NET Conversion
 * 
 *    Rev 1.3   Nov 24 2003 15:58:44   HSUCHIN
 * PTS 10020087 - Enhanced to take host information and connect to reflections based on host passed in.
 */
