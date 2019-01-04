#pragma once
#include <vector>



class  ElementAttribute
{
public:
   virtual ~ElementAttribute();
   virtual const std::string &getTagName() const = 0;
   virtual const std::string &getValue() const = 0;
   virtual bool hasDefaultValue() const = 0;

   virtual ElementAttribute *clone() const = 0;
};

class  BasicElementAttribute : public ElementAttribute
{
public:
   BasicElementAttribute( const std::string &tag, const std::string &value );
   virtual ~BasicElementAttribute();
   virtual const std::string &getTagName() const;
   virtual const std::string &getValue() const;
   virtual bool hasDefaultValue() const;

   virtual ElementAttribute *clone() const;
private:
   const std::string _tag;
   const std::string _value;

};


class ElementAttributeList : public std::vector<ElementAttribute *>
{
public:
   ElementAttributeList() {}
   ElementAttributeList( const ElementAttribute &attribute ) { add( attribute );}
   ElementAttributeList( const ElementAttributeList &copy )
   {

      const_iterator stp = copy.begin();
      const_iterator endp = copy.end();
      for( const_iterator i = stp; i != endp; ++i )
      {
         add( *(*i) );
      }
   }

   ~ElementAttributeList()
   {
      for( iterator i = begin(); i != end(); i++ )
         delete (*i);
   }

   void add( const ElementAttribute &attribute )
   {
      push_back( attribute.clone() );
   }

};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/awdsrv/ElementAttribute.hpp-arc  $
//
//   Rev 1.0   Nov 08 2005 14:04:16   yingbaol
//Initial revision.
//
//   Rev 1.3   Mar 05 2004 13:23:12   SMITHDAV
//Added basic attribute class for simple attributes
//
//   Rev 1.2   Jan 27 2003 14:51:20   PURDYECH
//Fix compile warning messages.
//
//   Rev 1.1   Oct 09 2002 17:41:26   PURDYECH
//New PVCS Database
//
//   Rev 1.0   Sep 19 2002 09:38:38   IVESPAUL
//Initial revision.
//
