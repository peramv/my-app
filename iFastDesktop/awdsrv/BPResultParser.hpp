//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2005 by International Financial Data Services
//
//
//******************************************************************************
//******************************************************************************
//
// ^FILE   : BPResultParser.hpp
// ^AUTHOR : Yongmei Feng
// ^DATE   : Oct. 31, 2005
//
// ^CLASS    : BPResultParser
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//********************************************************************************

#pragma once

#include <xercesc/parsers/saxparser.hpp>
#include <xercesc/sax/handlerbase.hpp>
#include <list>
#include <xercesc/sax/AttributeList.hpp>
#include "elementattribute.hpp"
#include <string>
#include <iostream>
// Import/Export resolution
#pragma once

class BPResult;
class Element
   {

	  std::string name, attribute, value;

   public:
      virtual ~Element()
      {
      }
	
	  Element( const std::string& Name, xercesc::AttributeList &attributes )
	  {
		  name = Name;		
		  int attriLen = attributes.getLength();
		  if ( attriLen > 0 )
		  {
            
            Element::xmlChToStd(attribute,attributes.getValue( attriLen - 1 ) );

			   //attribute = attributes.getValue( attriLen - 1 );
		  }
	  }

	  Element()
	  {
		  name = "";
		  attribute = "";
	  }

	  void AppendValue( const XMLCh * const chars, const unsigned int length ) 
	  { 
        std::string target;
        xmlChToStd(target,chars);

		  value += target; 
	  }

     std::string& getName() { return name; }
	  std::string& getAttribute() { return attribute; }
	  std::string& getValue() { return value; }

      static void xmlChToStd(std::string& target, const XMLCh*const toWrite)
      {
         target.clear();
         if(toWrite){
            std::wstring tmp = (wchar_t*)toWrite;
            wstringToAsciistring( tmp,target);
         }
      }
      static void wstringToAsciistring( std::wstring&  wstr, std::string & str )
      {
         unsigned length = wstr.length();
         char * save = new char[ length + 1 ];

         for( unsigned i = 0; i < length; ++i )
         {
            save[ i ] = ( char ) wstr[ i ];
         }
         save[ i ] = '\0';
         str = save;
         delete [] save;         
      }
   };

template<class _Eh> class TElementList : public std::list<_Eh>
   {
   public:
      virtual ~TElementList()
      {
         while( begin() != end() )
         {
            delete (*begin());
            pop_front();
         }
      }

      void add( _Eh element )
      {
         assert( element != NULL );
         push_back( element );
      }
   };

class ElementList : public TElementList<class Element *>
{
   public:
	  Element * addElement( std::string &name, xercesc::AttributeList &attributes )
	  {
		  Element * element = new Element(name, attributes);
		  add( element );
		  return element;
	  }
};
class  BPResultParser : public xercesc::HandlerBase 
   {
      //void static parse( const std::string &xmlIn,BPResult& result );
      

   public:
      BPResultParser();
      virtual ~BPResultParser();
      virtual void parse( const std::string &xmlIn,BPResult& result );
      virtual void parse( const std::string &uri );
      // DocumentHandler overrides
      virtual void startElement( const XMLCh *const name, xercesc::AttributeList &attributes );
      virtual void characters( const XMLCh * const chars, const unsigned int length );
      virtual void endElement( const XMLCh * const name );
      // ErrorHandler methods
      virtual void warning( const xercesc::SAXParseException &e );
      virtual void error( const xercesc::SAXParseException &e );
      virtual void fatalError( const xercesc::SAXParseException &e );
	   void outPut( BPResult& result);



   private:   
      void parse( const xercesc::InputSource &input, BPResult& result );
      std::string convertIntToString(int iNum);

      xercesc::SAXParser _parser;
	   ElementList _elementList;
	   Element * _currentElement;
   };




//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/awdsrv/BPResultParser.hpp-arc  $
//
//   Rev 1.3   Nov 08 2005 14:37:48   yingbaol
//PET1332,FN09: Remove Infra
//
//   Rev 1.1   Oct 31 2005 15:34:02   yingbaol
//Code clean up....
// 
//    Rev 1.0   Oct 31 2005 13:14:14   yingbaol
// Initial revision.
 * 
 */