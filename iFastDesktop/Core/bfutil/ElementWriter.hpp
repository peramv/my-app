#pragma once

//PMI-20020918#include "classattribute.hpp"
#include <list>

#include <bfutil\ElementAttribute.hpp>

// Import/Export resolution
#undef BFUTIL_LINKAGE
#ifdef BFUTIL_DLL
   #define BFUTIL_LINKAGE CLASS_EXPORT
#else
   #define BFUTIL_LINKAGE CLASS_IMPORT
#endif

//******************************************************************************
class BFUTIL_LINKAGE BFDocument
{
public:
//   void writeElement( const DString &elementName, const DString &text = I_("") );
//   void writeElement( const DString &elementName, const ElementAttribute &attribute, const DString &text = I_("") );
//   void writeElement( const DString &elementName, const ElementAttributeList &attributes, const DString &text = I_("") );

protected:
   virtual void writeElementStart( const DString &elementName ) = 0;
   virtual void writeElementStart( const DString &elementName, const ElementAttribute &attribute ) = 0;
   virtual void writeElementStart( const DString &elementName, const ElementAttributeList &attributes ) = 0;

   virtual void writeElementEnd( const DString &elementName ) = 0;
   virtual void writeElementText( const DString& text ) = 0;

   friend class ElementWriter;
};

//******************************************************************************
class BFUTIL_LINKAGE BasicDocument : public BFDocument
{
public:
   BasicDocument( DString &outStr );
   virtual ~BasicDocument();

protected:
   virtual void writeElementStart( const DString &elementName );
   virtual void writeElementStart( const DString &elementName, const ElementAttribute &attribute );
   virtual void writeElementStart( const DString &elementName, const ElementAttributeList &attributes );

   virtual void writeElementEnd( const DString &elementName );
   virtual void writeElementText( const DString& text );

private:
   class Indent
   {
   public:
      Indent( unsigned int indentCount );
      Indent( const Indent& copy );
      ~Indent();

      const Indent &operator=( const Indent &rhs );

      const DString &getValue() const;
      operator unsigned int() const { return(_indentCount);}

      const Indent &operator++();
      const Indent operator++(int);
      const Indent &operator--();
      const Indent operator--(int);

   private:
      void refreshLongIndentString();
      unsigned int _indentCount;
      DString *_longIndentString;
   };

   void replace(DString &str, const DString &token, const DString &replaceWith);

   void assureCapacity();

   DString &outStr_;
   Indent indent_;
   bool leafNode_;
   bool rootNode_;
};

//******************************************************************************
class BFUTIL_LINKAGE RADocument : public BFDocument
{
public:
   RADocument( BFDocument &parent );
   virtual ~RADocument();

   class Element;
   //******************************************************************************
   class ElementContainer
   {
   public:
      ElementContainer() : parent_(NULL) {}
      ElementContainer(ElementContainer *parent) : parent_(parent) {}
      virtual ~ElementContainer();

      Element *add( const DString &elementName, const ElementAttributeList &attributes );
      ElementContainer *getParent() { return(parent_);}

      virtual void write( BFDocument &out );
   private:
      ElementContainer * const parent_;
      std::list<Element *> elements_;
   };

   //******************************************************************************
   class Element : public ElementContainer
   {
   public:
      Element( ElementContainer &parent, const DString &elementName, const ElementAttributeList &attributes );
      void appendText( const DString & text ) { text_ += text;}

      virtual void write( BFDocument &out );
   private:
      const DString elementName_;
      const ElementAttributeList attributes_;
      DString text_;
   };

   //******************************************************************************
   class Position
   {
   public:
      Position ()
      : container_(NULL)
//         , position_(NULL)      
      {}

      Position ( ElementContainer *container )//, const Element *position )
      : container_(container)
//         , position_(position)      
      {}

      friend RADocument;
   private:
      ElementContainer * container_;
//         Element * const position_;
   };

   const Position tellPosition() const;
   void seekPosition( const Position &position );

protected:
   virtual void writeElementStart( const DString &elementName );
   virtual void writeElementStart( const DString &elementName, const ElementAttribute &attribute );
   virtual void writeElementStart( const DString &elementName, const ElementAttributeList &attributes );

   virtual void writeElementEnd( const DString &elementName );
   virtual void writeElementText( const DString& text );

private:

   BFDocument &parent_;
   ElementContainer rootContainer_;
   Position position_;

};

class BFUTIL_LINKAGE ElementInterface
{
public:
   virtual const DString &getName() const = 0;
   virtual ElementAttributeList & getAttributes( ElementAttributeList &attributes ) const = 0;
};

class BFUTIL_LINKAGE ElementWriter
{
public:
   ElementWriter( BFDocument &out,
                  const DString &elementName );

   ElementWriter( BFDocument &out,
                  const DString &elementName,
                  const ElementAttribute &attribute );

   ElementWriter( BFDocument &out,
                  const DString &elementName,
                  const ElementAttributeList &attributes );

   ElementWriter( BFDocument &out,
                  const ElementInterface &element );

   ~ElementWriter();

   void writeText( const DString &text = I_("") );

   const BFDocument &getOutputDoc() const {
      return out_;
   }

   BFDocument &getOutputDoc() {
      return out_;
   }

   static void write( BFDocument &out, 
                      const DString &elementName,
                      const DString &text = I_("") );

   static void write( BFDocument &out,
                      const DString &elementName,
                      const ElementAttribute &attribute,
                      const DString &text = I_("") );

   static void write( BFDocument &out,
                      const DString &elementName,
                      const ElementAttributeList &attributes,
                      const DString &text = I_("") );

   static void write( BFDocument &out,
                      const ElementInterface &element,
                      const DString &text = I_("") );
private:
   BFDocument &out_;
   const DString elementName_;
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF Core/bfutil/ElementWriter.hpp-arc  $
//
//   Rev 1.4   Mar 09 2004 10:58:30   PURDYECH
//PET910 - Changed stored element name from DString& to DString.  This make the interface to the ctor more robust.
//
//   Rev 1.3   Mar 02 2004 10:55:58   SMITHDAV
//Change element writers to make them mor robust.
//
//   Rev 1.2   Dec 05 2002 10:04:32   PURDYECH
//Added assureCapacity() method.
//
//   Rev 1.1   Oct 09 2002 17:41:28   PURDYECH
//New PVCS Database
//
//   Rev 1.0   Sep 19 2002 09:38:38   IVESPAUL
//Initial revision.
//
