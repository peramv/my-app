#include "stdafx.h"
#include ".\configprovider.hpp"

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

bps::ConfigProvider::ConfigProvider( const bf::opts::ProgramOptions &opts ) 
: programOpts_(opts)
, doc_(NULL) 
, rootElem_(NULL) 
{
   if ( opts.isSet('C') ) {

      std::string configFile  = opts.getStringValue('C');

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
}

bps::ConfigProvider::~ConfigProvider() {
   delete doc_;
}

std::wstring bps::ConfigProvider::getTextForPath(const std::wstring &pathName) const {
   return getElementText( getElementForPath( pathName ) );
}

xercesc::DOMElement *bps::ConfigProvider::getElementForPath( const std::wstring &pathName ) const {
   return getElementForPath( pathName, rootElem_ );
}

std::wstring bps::ConfigProvider::getTextForPath(const std::wstring &pathName, xercesc::DOMElement *parentElem) {
   return getElementText( getElementForPath( pathName, parentElem ) );
}

xercesc::DOMElement *bps::ConfigProvider::getElementForPath( const std::wstring &pathName, xercesc::DOMElement *parentElem ) {

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

xercesc::DOMElement *bps::ConfigProvider::getElementFirstChild(const std::wstring &childName, xercesc::DOMElement *parentElem) {
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

xercesc::DOMElement *bps::ConfigProvider::getElementNextSibling(const std::wstring &siblingName, xercesc::DOMElement *inSiblingElem ) {
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

std::wstring bps::ConfigProvider::getElementText(xercesc::DOMElement *elem) {
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

bps::ConfigIterator bps::ConfigProvider::iterator( const std::wstring &pathName, 
                                                            const std::wstring &iterElementName ) const {
   return ( bps::ConfigIterator( getElementFirstChild(iterElementName, getElementForPath( pathName )), iterElementName ) ) ;
}

bool bps::ConfigProvider::next( ConfigIterator &iter ) {
   if ( iter.started_ ) {
      iter.currElem_ = getElementNextSibling( iter.iterElementName_, iter.currElem_ );
   } else {
      iter.started_ = true;
   }
   return iter.currElem_!=NULL;
}
