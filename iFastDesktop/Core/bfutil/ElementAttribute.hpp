#pragma once

#include <vector>

#undef BFUTIL_LINKAGE
#ifdef BFUTIL_DLL
   #define BFUTIL_LINKAGE CLASS_EXPORT
#else
   #define BFUTIL_LINKAGE CLASS_IMPORT
#endif

class BFUTIL_LINKAGE ElementAttribute
{
public:
   virtual ~ElementAttribute();
   virtual const DString &getTagName() const = 0;
   virtual const DString &getValue() const = 0;
   virtual bool hasDefaultValue() const = 0;

   virtual ElementAttribute *clone() const = 0;
};

class BFUTIL_LINKAGE BasicElementAttribute : public ElementAttribute
{
public:
   BasicElementAttribute( const DString &tag, const DString &value );
   virtual ~BasicElementAttribute();
   virtual const DString &getTagName() const;
   virtual const DString &getValue() const;
   virtual bool hasDefaultValue() const;

   virtual ElementAttribute *clone() const;
private:
   const DString _tag;
   const DString _value;

};

class ElementAttributeList : public std::vector<ElementAttribute *>
{
public:
   ElementAttributeList() {}
   ElementAttributeList( const ElementAttribute &attribute ) { add( attribute );}
   ElementAttributeList( const ElementAttributeList &copy )
   {
      for( const_iterator i = copy.begin(); i != copy.end(); i++ )
         add( *(*i) );
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
// $Log:   Y:/VCS/BF Core/bfutil/ElementAttribute.hpp-arc  $
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
