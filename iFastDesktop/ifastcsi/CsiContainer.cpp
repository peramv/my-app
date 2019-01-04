// CsiContainer.cpp: implementation of the CsiContainer class.
//
//////////////////////////////////////////////////////////////////////

#include "CsiContainer.h"
#include <assert.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CsiContainer::CsiContainer(const std::string &componentName)
:CsiComponent(componentName)
{
}

CsiContainer::~CsiContainer()
{
   removeAllComponents();
}

bool 
CsiContainer::contains(const std::string &componentName) const
{
   ComponentIterator &iterator = componentMap.find(componentName);
   if( iterator == componentMap.end() )
      return(false);

   return(true);
}

void 
CsiContainer::select(const std::string &componentName) const
{
   ComponentIterator &iterator = componentMap.find(componentName);
   if( iterator == componentMap.end() )
      throw CsiComponentNotFound(componentName, getName());

   (*iterator).second->select();
}


bool 
CsiContainer::trySelect(const std::string &componentName) const
{
   ComponentIterator &iterator = componentMap.find(componentName);
   if( iterator == componentMap.end() )
      throw CsiComponentNotFound(componentName, getName());

   return(*iterator).second->trySelect();
}

void 
CsiContainer::addComponent(CsiComponent *component)
{
   componentMap.insert( ComponentPair(component->getName(), component) );
}

void 
CsiContainer::removeComponent(const std::string &componentName)
{
   std::map<std::string, CsiComponent*>::iterator &i = componentMap.begin();

   while( (i = componentMap.find(componentName)) != componentMap.end() )
   {
      delete (*i).second;
      componentMap.erase(i);
   }

}

void 
CsiContainer::removeAllComponents()
{
   std::map<std::string, CsiComponent*>::iterator &i = componentMap.begin();

   while( i != componentMap.end() )
   {
      CsiComponent *comp = (*i).second;
      delete comp;
      i++;
//      i = componentMap.erase(i);
   }

   componentMap.clear();
}

const CsiComponent *
CsiContainer::getComponent(const std::string &componentName) const
{
   ComponentIterator &iterator = componentMap.find(componentName);
   if( iterator == componentMap.end() )
      throw CsiComponentNotFound(componentName, componentName);

   return(*iterator).second;
}


CsiComponentIterator::CsiComponentIterator(const CsiContainer *c)
:it(c->componentMap.begin()), container(c)
{
}

bool 
CsiComponentIterator::hasNext() const
{
   return(it != container->componentMap.end());
}

const CsiComponent *
CsiComponentIterator::getNext()
{
   if( it == container->componentMap.end() )
      throw CsiComponentIteratorAtEnd(container->getName());

   return(*(it++)).second;
}
