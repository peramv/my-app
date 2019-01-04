#include "stdafx.h"
#include ".\GuiConfig.h"

#include <xercesc\parsers\xercesdomparser.hpp>
#include <xercesc\sax\errorhandler.hpp>
#include <xercesc\sax\saxparseexception.hpp>
#include <xercesc\util\platformutils.hpp>

#include<boost/tokenizer.hpp>

namespace {

   class ErrorHandler : public xercesc::ErrorHandler {
   public:
      virtual void warning(const xercesc::SAXParseException& exc) {}
      virtual void error(const xercesc::SAXParseException& exc) {}
      virtual void fatalError(const xercesc::SAXParseException& exc) { throw exc; }
      virtual void resetErrors() {}
   };

}
gui::GuiConfig* gui::GuiConfig::getInstance()
{
   if( myGuiConfig == NULL )
   {
		myGuiConfig = new gui::GuiConfig();
   }
   return(myGuiConfig);
}

gui::GuiConfig::GuiConfig() 
: doc_(NULL) 
, rootElem_(NULL) 
{
	myGuiConfig = NULL;
}

/*
gui::GuiConfig::GuiConfig( std::string &opts ) 
: doc_(NULL) 
, rootElem_(NULL) 
{

      std::string configFile  = opts;

      xercesc::XercesDOMParser* parser = new xercesc::XercesDOMParser();
      ErrorHandler eh;
      parser->setErrorHandler(&eh);
      parser->setValidationScheme( xercesc::XercesDOMParser::Val_Never );
      parser->setDoNamespaces( true );

      parser->parse( configFile.c_str() );

      doc_ = parser->adoptDocument();
      if ( doc_ != NULL ) {
         rootElem_ = doc_->getDocumentElement();
      }
}
*/
void gui::GuiConfig::init( std::string &opts ) 
{

	  doc_ = NULL;
	  rootElem_ = NULL;
      std::string configFile  = opts;

      xercesc::XercesDOMParser* parser = new xercesc::XercesDOMParser();
      ErrorHandler eh;
      parser->setErrorHandler(&eh);
      parser->setValidationScheme( xercesc::XercesDOMParser::Val_Never );
      parser->setDoNamespaces( true );

      parser->parse( configFile.c_str() );

      doc_ = parser->adoptDocument();
      if ( doc_ != NULL ) {
         rootElem_ = doc_->getDocumentElement();
      }
}
gui::GuiConfig::~GuiConfig() {
   delete doc_;
}

std::wstring gui::GuiConfig::getTextForPath(const std::wstring &pathName) const {
   return getElementText( getElementForPath( pathName ) );
}

xercesc::DOMElement *gui::GuiConfig::getElementForPath( const std::wstring &pathName ) const {
   return getElementForPath( pathName, rootElem_ );
}

std::wstring gui::GuiConfig::getTextForPath(const std::wstring &pathName, xercesc::DOMElement *parentElem) {
   return getElementText( getElementForPath( pathName, parentElem ) );
}

xercesc::DOMElement *gui::GuiConfig::getElementForPath( const std::wstring &pathName, xercesc::DOMElement *parentElem ) {

   if ( parentElem == NULL ) {
      return NULL;
   }
   xercesc::DOMElement *currElem = parentElem;

   typedef boost::char_separator<wchar_t> Separator;
   typedef boost::tokenizer< Separator, std::wstring::const_iterator, std::wstring > Tokenizer;
   Tokenizer tok(pathName, Separator(L"\\/"));

   for(Tokenizer::iterator iter=tok.begin(); iter!=tok.end();++iter){
      const std::wstring& elemName = (*iter);
      if ( elemName.size() > 0  ) {
         currElem = getElementFirstChild( elemName, currElem );
         if ( currElem == NULL ) {
            return NULL;
         }
      }
   }

   return currElem;

}

xercesc::DOMElement *gui::GuiConfig::getElementFirstChild(const std::wstring &childName, xercesc::DOMElement *parentElem) {
   if ( parentElem != NULL ) {
      xercesc::DOMNode *childNode = parentElem->getFirstChild();
      while( childNode != NULL ) {
         if ( childNode->getNodeType() == xercesc::DOMNode::ELEMENT_NODE ) {
            const XMLCh *nodeName = childNode->getNodeName();
            if ( nodeName!=NULL && childName == nodeName ) {
               return static_cast<xercesc::DOMElement *>(childNode);
            }
         }
         childNode = childNode->getNextSibling();
      }
   }
   return NULL;
}

xercesc::DOMElement *gui::GuiConfig::getElementNextSibling(const std::wstring &siblingName, xercesc::DOMElement *inSiblingElem ) {
   if ( inSiblingElem != NULL ) {
      xercesc::DOMNode *siblingNode = inSiblingElem->getNextSibling();
      while( siblingNode != NULL ) {
         if ( siblingNode->getNodeType() == xercesc::DOMNode::ELEMENT_NODE ) {
            const XMLCh *nodeName = siblingNode->getNodeName();
            if ( nodeName!=NULL && siblingName == nodeName ) {
               return static_cast<xercesc::DOMElement *>(siblingNode);
            }
         }
         siblingNode = siblingNode->getNextSibling();
      }
   }
   return NULL;
}

std::wstring gui::GuiConfig::getElementText(xercesc::DOMElement *elem) {
   if ( elem != NULL ) {
      xercesc::DOMNode *childNode = elem->getFirstChild();
      while( childNode != NULL ) {
         if ( childNode->getNodeType() == xercesc::DOMNode::TEXT_NODE ) {
            const XMLCh *nodeValue = childNode->getNodeValue();
            if ( nodeValue!=NULL ) {
               return nodeValue;
            }
         }
         childNode = childNode->getNextSibling();
      }
   }
   return L"";
}

gui::ConfigIterator gui::GuiConfig::iterator( const std::wstring &pathName, 
                                                            const std::wstring &iterElementName ) const {
   return ( gui::ConfigIterator( getElementFirstChild(iterElementName, getElementForPath( pathName )), iterElementName ) ) ;
}

bool gui::GuiConfig::next( ConfigIterator &iter ) {
   if ( iter.started_ ) {
      iter.currElem_ = getElementNextSibling( iter.iterElementName_, iter.currElem_ );
   } else {
      iter.started_ = true;
   }
   return iter.currElem_!=NULL;
}

gui::ConfigIterator gui::GuiConfig::iteratorchildren( gui::ConfigIterator iterParent, 
                                                            const std::wstring &iterElementName ) const {
   xercesc::DOMElement *parentElem = iterParent.currElem_;
   return ( gui::ConfigIterator( getElementFirstChild(iterElementName, parentElem), iterElementName ) ) ;
}
