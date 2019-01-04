// CsiComponent.h: interface for the CsiComponent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_CSICOMPONENT_H__INCLUDED_)
   #define _CSICOMPONENT_H__INCLUDED_

   #include <ifastcsi\xplatform.h>
   #include <ifastcsi\CsiException.h>

   #include <tesession\TESession.h>
   #include <string>

class CsiComponent  
{
public:
   CsiComponent(const std::string &componentName);
   virtual ~CsiComponent();

   virtual bool isContainer() const {return(false);}
   virtual void init() const {}
   virtual void select() const {}
   virtual void wait(long timeout) const {}
   virtual bool trySelect() const {return(true);}
   virtual bool tryWait(long timeout) const {return(true);}

   const std::string &getName() const {return(name);}

private:
   std::string name;
};

class CsiComponentWaitTimeout : public CsiException
{
public:
   CsiComponentWaitTimeout(const std::string &componentName)
   : _componentName(componentName) {}

   virtual const std::string getMessage() {return("Timeout on wait for component " + _componentName);}
private:
   std::string _componentName;
};

class CsiComponentWaitFailure : public CsiException
{
public:
   CsiComponentWaitFailure(const std::string &componentName)
   : _componentName(componentName) {}

   virtual const std::string getMessage() {return("Failure on wait for component " + _componentName);}
private:
   std::string _componentName;
};

#endif // !defined(_CSICOMPONENT_H__INCLUDED_)
