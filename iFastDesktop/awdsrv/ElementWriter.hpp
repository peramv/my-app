#pragma once


//PMI-20020918#include "classattribute.hpp"
#include <list>

#include "ElementAttribute.hpp"


//******************************************************************************
class  BFDocument
{
public:
//   void writeElement( const std::string &elementName, const std::string &text = I_("") );
//   void writeElement( const std::string &elementName, const ElementAttribute &attribute, const std::string &text = I_("") );
//   void writeElement( const std::string &elementName, const ElementAttributeList &attributes, const std::string &text = I_("") );

protected:
   virtual void writeElementStart( const std::string &elementName ) = 0;
   virtual void writeElementStart( const std::string &elementName, const ElementAttribute &attribute ) = 0;
   virtual void writeElementStart( const std::string &elementName, const ElementAttributeList &attributes ) = 0;

   virtual void writeElementEnd( const std::string &elementName ) = 0;
   virtual void writeElementText( const std::string& text ) = 0;

   friend class ElementWriter;
};

//******************************************************************************
class  BasicDocument : public BFDocument
{
public:
   BasicDocument( std::string &outStr );
   virtual ~BasicDocument();

protected:
   virtual void writeElementStart( const std::string &elementName );
   virtual void writeElementStart( const std::string &elementName, const ElementAttribute &attribute );
   virtual void writeElementStart( const std::string &elementName, const ElementAttributeList &attributes );

   virtual void writeElementEnd( const std::string &elementName );
   virtual void writeElementText( const std::string& text );

private:
   class Indent
   {
   public:
      Indent( unsigned int indentCount );
      Indent( const Indent& copy );
      ~Indent();

      const Indent &operator=( const Indent &rhs );

      const std::string &getValue() const;
      operator unsigned int() const { return(_indentCount);}

      const Indent &operator++();
      const Indent operator++(int);
      const Indent &operator--();
      const Indent operator--(int);

   private:
      void refreshLongIndentString();
      unsigned int _indentCount;
      std::string *_longIndentString;
   };

   void replace(std::string &str, const std::string &token, const std::string &replaceWith);

   void assureCapacity();

   std::string &outStr_;
   Indent indent_;
   bool leafNode_;
   bool rootNode_;
};

//******************************************************************************
class  RADocument : public BFDocument
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

      Element *add( const std::string &elementName, const ElementAttributeList &attributes );
      ElementContainer *getParent() { return(parent_);}

      virtual write( BFDocument &out );
   private:
      ElementContainer * const parent_;
      std::list<Element *> elements_;
   };

   //******************************************************************************
   class Element : public ElementContainer
   {
   public:
      Element( ElementContainer &parent, const std::string &elementName, const ElementAttributeList &attributes );
      void appendText( const std::string & text ) { text_ += text;}

      virtual write( BFDocument &out );
   private:
      const std::string elementName_;
      const ElementAttributeList attributes_;
      std::string text_;
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
   virtual void writeElementStart( const std::string &elementName );
   virtual void writeElementStart( const std::string &elementName, const ElementAttribute &attribute );
   virtual void writeElementStart( const std::string &elementName, const ElementAttributeList &attributes );

   virtual void writeElementEnd( const std::string &elementName );
   virtual void writeElementText( const std::string& text );

private:

   BFDocument &parent_;
   ElementContainer rootContainer_;
   Position position_;

};

class  ElementInterface
{
public:
   virtual const std::string &getName() const = 0;
   virtual ElementAttributeList & getAttributes( ElementAttributeList &attributes ) const = 0;
};

class  ElementWriter
{
public:
   ElementWriter( BFDocument &out,
                  const std::string &elementName );

   ElementWriter( BFDocument &out,
                  const std::string &elementName,
                  const ElementAttribute &attribute );

   ElementWriter( BFDocument &out,
                  const std::string &elementName,
                  const ElementAttributeList &attributes );

   ElementWriter( BFDocument &out,
                  const ElementInterface &element );

   ~ElementWriter();

   void writeText( const std::string &text = "" );

   const BFDocument &getOutputDoc() const {
      return out_;
   }

   BFDocument &getOutputDoc() {
      return out_;
   }

   static void write( BFDocument &out, 
                      const std::string &elementName,
                      const std::string &text = "" );

   static void write( BFDocument &out,
                      const std::string &elementName,
                      const ElementAttribute &attribute,
                      const std::string &text = "" );

   static void write( BFDocument &out,
                      const std::string &elementName,
                      const ElementAttributeList &attributes,
                      const std::string &text = "" );

   static void write( BFDocument &out,
                      const ElementInterface &element,
                      const std::string &text = "" );
private:
   BFDocument &out_;
   const std::string elementName_;
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/awdsrv/ElementWriter.hpp-arc  $
//
//   Rev 1.0   Nov 08 2005 14:04:18   yingbaol
//Initial revision.
//
//   Rev 1.4   Mar 09 2004 10:58:30   PURDYECH
//PET910 - Changed stored element name from std::string& to std::string.  This make the interface to the ctor more robust.
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
