/*******************************************************************************
 *
 * COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 2000 by DST Systems, Inc.
 *
*******************************************************************************/
#include "stdafx.h"
#include "ElementWriter.hpp"
#include <limits>
#ifdef _DEBUG
   #include "bfhrtimer.hpp"
#endif

#ifdef _DEBUG
//CP20030807   #include "logger.hpp"
   #include <bf/log/logstream.hpp>
#endif   

namespace
{
   const DString PREDEF_INDENTS[11] = { I_(""),  //0
      I_("   "),  //1
      I_("      "),  //2
      I_("         "),  //3
      I_("            "),  //4
      I_("               "),  //5
      I_("                  "),  //6
      I_("                     "),  //7
      I_("                        "),  //8
      I_("                           "),  //9
      I_("                              ")};  //10

   const unsigned int MAX_PREDEF_INDENTS = 10;
}

//******************************************************************************
//void BFDocument::writeElement( const DString &elementName,
//                               const DString &text /*= I_("")*/ )
//{
//   writeElementStart( elementName );
//   writeElementText( text );
//   writeElementEnd( elementName );
//}

//******************************************************************************
//void BFDocument::writeElement( const DString &elementName, const ElementAttribute &attribute, const DString &text /*= I_("")*/ )
//{
//   writeElementStart( elementName, attribute );
//   writeElementText( text );
//   writeElementEnd( elementName );
//}

//******************************************************************************
//void BFDocument::writeElement( const DString &elementName, const ElementAttributeList &attributes, const DString &text /*= I_("")*/ )
//{
//   writeElementStart( elementName, attributes );
//   writeElementText( text );
//   writeElementEnd( elementName );
//}

//******************************************************************************
BasicDocument::BasicDocument( DString &outStr )
: outStr_(outStr)
, indent_(0)
, leafNode_(true)
, rootNode_(true)
{
   outStr_ = I_("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
}

//******************************************************************************
BasicDocument::~BasicDocument()
{
}

//******************************************************************************
void BasicDocument::writeElementStart( const DString &elementName )
{
   writeElementStart( elementName, ElementAttributeList() );
}

//******************************************************************************
void BasicDocument::writeElementStart( const DString &elementName, const ElementAttribute &attribute )
{
   ElementAttributeList attributeList;
   attributeList.add( attribute );
   writeElementStart( elementName, attributeList );
}

//******************************************************************************
void BasicDocument::writeElementStart( const DString &elementName, const ElementAttributeList &attributes )
{
   assureCapacity();

   if( !rootNode_ )
   {
      outStr_ += I_("\n");
   }
   else
   {
      rootNode_ = false;
   }

   outStr_ += indent_.getValue();
   outStr_ += I_("<");
   outStr_ += elementName;

   ElementAttributeList::const_iterator i = attributes.begin();
   for( ; i != attributes.end(); ++i )
   {
      if( !(*i)->hasDefaultValue() )
      {
         outStr_ += I_(" ");
         outStr_ += (*i)->getTagName();
         outStr_ += I_("=\"");
         outStr_ += (*i)->getValue();
         outStr_ += I_("\"");
      }
   }

   outStr_ += I_(">");

   ++indent_;
   leafNode_ = true;
}

//******************************************************************************
void BasicDocument::writeElementEnd( const DString &elementName )
{
   assureCapacity();
   --indent_;
   if( leafNode_ )
   {
      outStr_ += I_("</");
      outStr_ += elementName;
      outStr_ += I_(">");
   }
   else
   {
      outStr_ += I_("\n");
      outStr_ += indent_.getValue();
      outStr_ += I_("</");
      outStr_ += elementName;
      outStr_ += I_(">");
   }

   leafNode_ = false;
}

//******************************************************************************
void BasicDocument::writeElementText( const DString& text )
{
   assureCapacity();

   DString xmlText = text;

   replace( xmlText, I_( "&" ), I_("&amp;") );
   replace( xmlText, I_( "<" ), I_("&lt;") );
   replace( xmlText, I_( ">" ), I_("&gt;") );
   replace( xmlText, I_( "'" ), I_("&apos;") );
   replace( xmlText, I_( "\"" ), I_("&quot;") );

   outStr_ += xmlText;
}

//******************************************************************************
// this function is versatile for all the tokens, but the token we use has only 1 char, probably
// to expensive
void BasicDocument::replace(DString &str, const DString &token, const DString &replaceWith)
{
   int pos = str.find( token );
   while( pos != DString::npos )
   {
      str.replace( pos, token.length(), replaceWith );
      pos = str.find( token, pos + token.length() );
   }
}

//******************************************************************************
BasicDocument::Indent::Indent( unsigned int indentCount )
: _indentCount(indentCount)
, _longIndentString(NULL)
{
   refreshLongIndentString();
}

//******************************************************************************
BasicDocument::Indent::Indent( const Indent& copy )
: _indentCount(copy._indentCount)
, _longIndentString(NULL)
{
   refreshLongIndentString();
}

//******************************************************************************
BasicDocument::Indent::~Indent()
{
   delete _longIndentString;
}

//******************************************************************************
void BasicDocument::Indent::refreshLongIndentString()
{
   delete _longIndentString;
   _longIndentString = NULL;

   if( _indentCount > MAX_PREDEF_INDENTS )
   {
      // build long indent string
      DString tempString( PREDEF_INDENTS[MAX_PREDEF_INDENTS] );

      unsigned int remainer = _indentCount % MAX_PREDEF_INDENTS;
      while( remainer > MAX_PREDEF_INDENTS )
      {
         tempString += PREDEF_INDENTS[MAX_PREDEF_INDENTS];
         remainer = remainer % MAX_PREDEF_INDENTS;
      }
      tempString += PREDEF_INDENTS[remainer];

      _longIndentString = new DString( tempString );
   }

}

//******************************************************************************
const BasicDocument::Indent &BasicDocument::Indent::operator=( const BasicDocument::Indent &rhs )
{
   _indentCount = rhs._indentCount;
   refreshLongIndentString();
   return(*this);
}

//******************************************************************************
const DString &BasicDocument::Indent::getValue() const
{
   if( _indentCount <= MAX_PREDEF_INDENTS )
      return(PREDEF_INDENTS[_indentCount]);
   else
      return(*_longIndentString);
}

//******************************************************************************
const BasicDocument::Indent &BasicDocument::Indent::operator++()
{
   ++_indentCount;
   refreshLongIndentString();
   return(*this);
}

//******************************************************************************
const BasicDocument::Indent BasicDocument::Indent::operator++(int)
{
   Indent tmp(*this);
   ++_indentCount;
   refreshLongIndentString();
   return(tmp);
}

//******************************************************************************
const BasicDocument::Indent &BasicDocument::Indent::operator--()
{
   --_indentCount;
   refreshLongIndentString();
   return(*this);
}

//******************************************************************************
const BasicDocument::Indent BasicDocument::Indent::operator--(int)
{
   Indent tmp(*this);
   --_indentCount;
   refreshLongIndentString();
   return(tmp);
}

//******************************************************************************
void BasicDocument::assureCapacity()
{
   // There is a Debatable Design Issue in std::string:  
   //   When a std::string has to increase in size due to an append operation
   //   the capacity of the std::string's buffer is increased to 31 characters more than
   //   is needed to hold the new value of the buffer.  This causes *ALOT* of reallocations
   //   when many appends are performed on large strings.  Some of our XML documents were
   //   in excess of 700K in size and the document was taking 7 - 8 seconds to generate
   //   because of all of the reallocaitons.  We could rewrite std::string, or we could fix
   //   it in this specific case ... Door Number 2, please Monty.
   //       CP 20021205
   if( outStr_.capacity() < ( outStr_.size() + 256 ) 
      && outStr_.capacity() < ( std::numeric_limits< long >::max() / 2 ) ) 
   {
      outStr_.reserve( outStr_.capacity() * 2 );
   }
}

//******************************************************************************
RADocument::RADocument( BFDocument &parent )
: parent_( parent )
, rootContainer_()
, position_( &rootContainer_ )//, NULL )
{
}

//******************************************************************************
RADocument::~RADocument()
{
#ifdef _DEBUG
   BFHRTimer t;
#endif
   rootContainer_.write(parent_);
#ifdef _DEBUG
   bf::log::LogStream s( bf::log::xml );
   s << bf::log::information << I_( "Document preparation took " ) << t.elapsed() << I_( " ms." ) << bf::log::endl;
//CP20030807   LOGTOFILE( INFORMAL_L, , t.elapsed() ) ;
#endif
}

//******************************************************************************
void RADocument::writeElementStart( const DString &elementName )
{
   writeElementStart( elementName, ElementAttributeList() );
}

//******************************************************************************
void RADocument::writeElementStart( const DString &elementName, const ElementAttribute &attribute )
{
   writeElementStart( elementName, ElementAttributeList( attribute ) );
}

//******************************************************************************
void RADocument::writeElementStart( const DString &elementName, const ElementAttributeList &attributes )
{
   RADocument::Element *newElement = position_.container_->add( elementName, attributes );
   position_ =  RADocument::Position( newElement ); //, NULL ); // set position to the end of the new element
}

//******************************************************************************
void RADocument::writeElementEnd( const DString &elementName )
{
   assert( position_.container_->getParent() != NULL );
   position_ = RADocument::Position( position_.container_->getParent() ); //, NULL ); // set position to the end of the current parent container
}

//******************************************************************************
void RADocument::writeElementText( const DString& text )
{
   RADocument::Element *cElement = dynamic_cast<RADocument::Element *>(position_.container_);
   assert( cElement != NULL );

   cElement->appendText( text );
}

//******************************************************************************
const RADocument::Position RADocument::tellPosition() const
{
   return(position_);
}

//******************************************************************************
void RADocument::seekPosition( const RADocument::Position &position )
{
   position_ = position;
   if( position_.container_ == NULL )
   {
      position_.container_ = &rootContainer_;
   }
}


//******************************************************************************
RADocument::ElementContainer::~ElementContainer()
{
   for( std::list<RADocument::Element *>::iterator i = elements_.begin();
      i != elements_.end();
      i++ )
   {
      delete (*i);
   }
}

//******************************************************************************
void RADocument::ElementContainer::write( BFDocument &out )
{
   for( std::list<RADocument::Element *>::iterator i = elements_.begin();
      i != elements_.end();
      i++ )
   {
      (*i)->write( out );
   }

}

//******************************************************************************
RADocument::Element *RADocument::ElementContainer::add( const DString &elementName, const ElementAttributeList &attributes )
{
   RADocument::Element *newElement = new Element( *this, elementName, attributes);
   elements_.push_back( newElement );
   return(newElement);
}

//******************************************************************************
RADocument::Element::Element( ElementContainer &parent, const DString &elementName, const ElementAttributeList &attributes )
: ElementContainer( &parent )
, elementName_( elementName )
, attributes_( attributes )
, text_()
{
}

//******************************************************************************
void RADocument::Element::write( BFDocument &out )
{
   ElementWriter eWriter( out, elementName_, attributes_ );
   eWriter.writeText( text_ );
   ElementContainer::write( out );
}

//******************************************************************************
ElementWriter::ElementWriter( BFDocument &out,
                              const DString &elementName )
: out_(out)
, elementName_(elementName)
{
   out_.writeElementStart( elementName_ );
}

//******************************************************************************
ElementWriter::ElementWriter( BFDocument &out,
                              const DString &elementName,
                              const ElementAttribute &attribute )
: out_(out)
, elementName_(elementName)
{
   out_.writeElementStart( elementName_, attribute );
}

//******************************************************************************
ElementWriter::ElementWriter( BFDocument &out,
                              const DString &elementName,
                              const ElementAttributeList &attributes )
: out_(out)
, elementName_(elementName)
{
   out_.writeElementStart( elementName_, attributes );
}

//******************************************************************************
ElementWriter::ElementWriter( BFDocument &out,
                              const ElementInterface &element )
: out_(out)
, elementName_( element.getName() )
{
   ElementAttributeList attributes;
   out_.writeElementStart( elementName_, element.getAttributes(attributes) );
}

//******************************************************************************
ElementWriter::~ElementWriter()
{
   out_.writeElementEnd( elementName_ );
}

//******************************************************************************
void ElementWriter::writeText( const DString &text /*= I_("")*/ )
{
   out_.writeElementText( text );
}

//******************************************************************************
void ElementWriter::write( BFDocument &out, 
                           const DString &elementName,
                           const DString &text /*= I_("")*/ )
{
   ElementWriter( out, elementName ).writeText( text );
}

//******************************************************************************
void ElementWriter::write( BFDocument &out,
                           const DString &elementName,
                           const ElementAttribute &attribute,
                           const DString &text /*= I_("")*/ )
{
   ElementWriter( out, elementName, attribute ).writeText( text );
}

//******************************************************************************
void ElementWriter::write( BFDocument &out,
                           const DString &elementName,
                           const ElementAttributeList &attributes,
                           const DString &text /*= I_("")*/ )
{
   ElementWriter( out, elementName, attributes ).writeText( text );
}

//******************************************************************************
void ElementWriter::write( BFDocument &out,
                           const ElementInterface &element,
                           const DString &text /*= I_("")*/ )
{
   ElementWriter( out, element ).writeText( text );
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF Core/bfutil/ElementWriter.cpp-arc  $
//
//   Rev 1.6   Mar 02 2004 10:55:50   SMITHDAV
//Change element writers to make them mor robust.
//
//   Rev 1.5   Aug 12 2003 10:08:06   PURDYECH
//Added new logging method (bf::log::...)
// 
//    Rev 1.4   Dec 05 2002 10:04:12   PURDYECH
// Fix performance problem related to std::string append operation.
// 
//    Rev 1.3   Oct 09 2002 17:41:28   PURDYECH
// New PVCS Database
// 
//    Rev 1.2   Oct 03 2002 11:56:24   SMITHDAV
// Fix declaration.
// 
//    Rev 1.1   Oct 03 2002 11:49:04   SMITHDAV
// Add xml declarations.
// 
//    Rev 1.0   Sep 19 2002 09:40:24   IVESPAUL
// Initial revision.
//
