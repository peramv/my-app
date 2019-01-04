// CsiContainer.h: interface for the CsiContainer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_CSICONTAINER_H__INCLUDED_)
   #define _CSICONTAINER_H__INCLUDED_

   #include <ifastcsi\xplatform.h>
   #include <ifastcsi\CsiException.h>

   #include <ifastcsi\CsiComponent.h>
   #include <map>
   #include <string>

class CsiComponentIterator;

// Container class
class CsiContainer : public CsiComponent  
{
public:
   CsiContainer(const std::string &componentName);
   virtual ~CsiContainer();

   virtual bool isContainer() const {return(true);}
   virtual void select(const std::string &componentName) const;
   virtual bool trySelect(const std::string &componentName) const;
   virtual bool contains(const std::string &componentName) const;

   void addComponent(CsiComponent *component);

   void removeComponent(const std::string &componentName);
   void removeAllComponents();

   const CsiComponent *getComponent(const std::string &componentName) const;

   typedef std::map<std::string, CsiComponent*>::value_type ComponentPair;
   typedef std::map<std::string, CsiComponent*>::const_iterator ComponentIterator;
   typedef std::map<std::string, CsiComponent*> ComponentMap;

private:
   ComponentMap componentMap;

   friend CsiComponentIterator;
};

// Component Iterator class for Container
class CsiComponentIterator
{
public:
   CsiComponentIterator(const CsiContainer *container);

   bool hasNext() const;
   const CsiComponent *getNext();
private:
   CsiContainer::ComponentIterator it;
   const CsiContainer *container;


};

class CsiComponentNotFound : public CsiException
{
public:
   CsiComponentNotFound(const std::string &componentName, const std::string &containerName)
   : _componentName(componentName), _containerName(containerName) {}

   virtual const std::string getMessage() {return("Component " + _componentName + " not found in Container " + _containerName);}
private:
   std::string _componentName;
   std::string _containerName;
};

class CsiComponentIteratorAtEnd : public CsiException
{
public:
   CsiComponentIteratorAtEnd(const std::string &containerName)
   : _containerName(containerName) {}

   virtual const std::string getMessage() {return("Next component requested ended iterator: " + _containerName);}
private:
   std::string _containerName;
};


#endif // !defined_CSICONTAINER_H__INCLUDED_)
