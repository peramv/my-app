// CsiScreen.h: interface for the CsiScreen class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_CSISCREEN_H__INCLUDED_)
   #define _CSISCREEN_H__INCLUDED_

   #include <ifastcsi\xplatform.h>

   #include <ifastcsi\CsiContainer.h>

class CsiScreen : public CsiContainer  
{
public:
   CsiScreen(const std::string &componentName);
   virtual ~CsiScreen();

   virtual void wait(long timeout) const;
   virtual bool tryWait(long timeout) const;

};

#endif // !defined(_CSISCREEN_H__INCLUDED_)
