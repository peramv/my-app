#include "stdafx.h"
#include "SiteConfig.h"

#include <xercesc\parsers\xercesdomparser.hpp>
#include <xercesc\sax\errorhandler.hpp>
#include <xercesc\sax\saxparseexception.hpp>
#include <xercesc\util\platformutils.hpp>
#include <xercesc\framework\MemBufInputSource.hpp>
#include <xercesc\dom\DOMImplementationRegistry.hpp>
#include <xercesc\dom\DOMImplementationLS.hpp>
#include <xercesc\dom\DOMLSSerializer.hpp>
#include <xercesc\dom\DOMText.hpp>
#include <xercesc\dom\DOMException.hpp>
#include <xercesc\dom\DOMConfiguration.hpp>
#include <xercesc\dom\DOMLSOutput.hpp>
#include <xercesc\framework\MemBufFormatTarget.hpp>
#include <xercesc\framework\MemBufInputSource.hpp>

#include<boost/tokenizer.hpp>

namespace {

   class ErrorHandler : public xercesc::ErrorHandler {
   public:
      virtual void warning(const xercesc::SAXParseException& exc) {
      }
      virtual void error(const xercesc::SAXParseException& exc) {
         throw exc;
      }
      virtual void fatalError(const xercesc::SAXParseException& exc) {
         throw exc;
      }
      virtual void resetErrors() {
      }
   };

}

static xercesc::MemBufInputSource& getDefaultDocument() {
   static std::string sDefDoc =
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n" \
      "<Site>\n" \
      "<Description>Description</Description>\n" \
      "<Market><Market>Lux</Market><ValidCompanies></ValidCompanies></Market>\n" \
      "<Csi><Host></Host><Type></Type><Param></Param></Csi>" \
      "<RTSHost>\n" \
      "  <RTSHostIP></RTSHostIP>\n" \
      "  <RTSHostPort></RTSHostPort>\n" \
      "  <PersistentConnections>0</PersistentConnections>\n" \
      "  <RecycleInterval></RecycleInterval>\n" \
      "  <SMQBrokerURLs></SMQBrokerURLs>\n" \
      "  <SMQSingleQueue></SMQSingleQueue>\n" \
      "  <SMQMultiQueue></SMQMultiQueue>\n" \
      "  <SMQLDAPQueue></SMQLDAPQueue>\n" \
      "  <SMQAWDQueue></SMQAWDQueue>\n" \
      "  <SMQUser></SMQUser>\n" \
      "  <SMQPassword></SMQPassword>\n" \
      "  <SMQWaitTimeout></SMQWaitTimeout>\n" \
      "  <LDAPUserNS></LDAPUserNS>\n" \
      "</RTSHost>\n" \
      "<Support>\n" \
      "  <!--\n" \
      "  <Log_Enable>0</Log_Enable>\n" \
      "  <Log_File></Log_File>\n" \
      "  <Log_Path></Log_Path>\n" \
      "  <Log_Level>2</Log_Level>\n" \
      "  <ViewLog_Append></ViewLog_Append>\n" \
      "  <ViewLog_Complete></ViewLog_Complete>\n" \
      "  <ViewLog_Enable>0</ViewLog_Enable>\n" \
      "  <ViewLog_Path></ViewLog_Path>\n" \
      "  <ViewLog_RawRequest></ViewLog_RawRequest>\n" \
      "  <ViewLog_RawResponse></ViewLog_RawResponse>\n" \
      "  <ViewTimeLog_Enable>0</ViewTimeLog_Enable>\n" \
      "  <ViewTimeLog_Path></ViewTimeLog_Path>\n" \
      "  <ViewTimeLog_Size></ViewTimeLog_Size>\n" \
      "  <ExceptionReport_Enable>0</ExceptionReport_Enable>\n" \
      "  <ExceptionReport_Path></ExceptionReport_Path>\n" \
      "  <ControlTextRewriter_Path></ControlTextRewriter_Path>\n" \
      "  <KeyPeek_Path></KeyPeek_Path>\n" \
      "  <ReportEMailAddress></ReportEMailAddress>\n" \
      "  -->\n" \
      "  <DisplayConnectionIcon>1</DisplayConnectionIcon>\n" \
      "  <DisplayConditionName>0</DisplayConditionName>\n" \
      "  <ShowClientNamePane>0</ShowClientNamePane>\n" \
      "  <ReportEMailAddress></ReportEMailAddress>\n" \
     "  <SpecialPasswordRules>0</SpecialPasswordRules>\n" \
      "</Support>\n" \
      "<AwdType>\n" \
      "  <InterfaceDll>DIAWD23</InterfaceDll>\n" \
      "  <AutoLogon>0</AutoLogon>\n" \
      "</AwdType>\n" \
      "<DataPath>\n" \
      "  <Path></Path>\n" \
      "  <FYIfile></FYIfile>\n" \
      "  <SysLoadPath></SysLoadPath>\n" \
      "  <RepositorySource></RepositorySource>\n" \
      "</DataPath>\n" \
      "</Site>\n";
   static XMLByte* sbDefDoc = (XMLByte*)sDefDoc.c_str();
   static xercesc::MemBufInputSource* s_is =
      new xercesc::MemBufInputSource( sbDefDoc,
                                      sDefDoc.size(),
                                      (XMLCh*)"blah" /*sID*/ );

   return *s_is;
}
site::SiteConfig* site::SiteConfig::s_mySiteConfig = NULL;

site::SiteConfig* site::SiteConfig::getInstance() {
   if ( s_mySiteConfig == NULL ) {
      s_mySiteConfig = new site::SiteConfig();
   }
   return(s_mySiteConfig);
}

site::SiteConfig::SiteConfig()
: doc_(NULL)
, rootElem_(NULL) {
}

void site::SiteConfig::init( const std::string& opts, ConfigManager* pDSTCMgr ) {
   pDSTCMgr_ = pDSTCMgr;
   doc_ = NULL;
   rootElem_ = NULL;
   std::string configFile  = opts;

   xercesc::XercesDOMParser* parser = new xercesc::XercesDOMParser();
   ErrorHandler eh;
   parser->setErrorHandler(&eh);
   parser->setValidationScheme( xercesc::XercesDOMParser::Val_Never );
   parser->setDoNamespaces( true );

   if( configFile != "" ) {
      parser->parse(configFile.c_str());
   }
   else {
      parser->parse(getDefaultDocument());
   }
   doc_ = parser->adoptDocument();
   if ( doc_ != NULL ) {
      rootElem_ = doc_->getDocumentElement();
   }
}

site::SiteConfig::~SiteConfig() {
   delete doc_;
}

DString site::SiteConfig::getDescription() const {
   std::wstring strDescription;
   getTextForPath(I_("Description"), strDescription);
   return( DString(strDescription.c_str()));
}

bool site::SiteConfig::getTextForPath(const std::wstring &pathName, std::wstring& configText ) const {
   return getElementText( getElementForPath( pathName ), configText );
}

bool site::SiteConfig::setTextForPath(const std::wstring &pathName, const std::wstring& configText ) {
   xercesc::DOMElement* pElem = getElementForPath( pathName );
   if( NULL == pElem ) {
      pElem = addElementForPath( pathName );
   }
   return( setElementText( pElem, configText ) );
}

xercesc::DOMElement* site::SiteConfig::getElementForPath( const std::wstring &pathName ) const {
   return getElementForPath( pathName, rootElem_ );
}

xercesc::DOMElement* site::SiteConfig::addElementForPath( const std::wstring &pathName ) {
   return addElementForPath( pathName, rootElem_ );
}

bool site::SiteConfig::removeElementForPath( const std::wstring &pathName ) {
   if ( rootElem_ == NULL ) {
      return false;
   }
   xercesc::DOMElement* currElem = rootElem_;
   xercesc::DOMElement* parentElem = NULL;

   typedef boost::char_separator<wchar_t> Separator;
   typedef boost::tokenizer< Separator, std::wstring::const_iterator, std::wstring > Tokenizer;
   Tokenizer tok(pathName, Separator(L"\\/"));

   for (Tokenizer::iterator iter=tok.begin(); iter!=tok.end();++iter) {
      const std::wstring& elemName = (*iter);
      if ( elemName.size() > 0  ) {
         parentElem = currElem;
         currElem = getElementFirstChild( elemName, currElem );
         if ( currElem == NULL ) {
            return false;
         }
      }
   }
   if( NULL != parentElem &&
       NULL != currElem ) {
      parentElem->removeChild( currElem );
      return( true );
   }
   return false;
}

bool site::SiteConfig::getTextForPath(const std::wstring &pathName, xercesc::DOMElement *parentElem, std::wstring& configText) {
   return getElementText( getElementForPath( pathName, parentElem ), configText );
}

xercesc::DOMElement *site::SiteConfig::getElementForPath( const std::wstring &pathName, xercesc::DOMElement *parentElem ) {

   if ( parentElem == NULL ) {
      return NULL;
   }
   xercesc::DOMElement *currElem = parentElem;

   typedef boost::char_separator<wchar_t> Separator;
   typedef boost::tokenizer< Separator, std::wstring::const_iterator, std::wstring > Tokenizer;
   Tokenizer tok(pathName, Separator(L"\\/"));

   for (Tokenizer::iterator iter=tok.begin(); iter!=tok.end();++iter) {
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

xercesc::DOMElement* site::SiteConfig::addElementForPath( const std::wstring &pathName, xercesc::DOMElement *parentElem ) {

   if ( parentElem == NULL ) {
      return NULL;
   }
   xercesc::DOMElement *currElem = parentElem;

   typedef boost::char_separator<wchar_t> Separator;
   typedef boost::tokenizer< Separator, std::wstring::const_iterator, std::wstring > Tokenizer;
   Tokenizer tok(pathName, Separator(L"\\/"));

   for (Tokenizer::iterator iter=tok.begin(); iter!=tok.end();++iter) {
      const std::wstring& elemName = (*iter);
      if ( elemName.size() > 0  ) {
         currElem = getElementFirstChild( elemName, currElem );
         if ( currElem == NULL ) {
            XMLCh tStr[100];
            DString d(elemName.c_str());
            xercesc::XMLString::transcode( DStringA(d).c_str(), tStr, 99 );
            xercesc::DOMElement* aNode = doc_->createElement( tStr );
            parentElem->appendChild( aNode );
            parentElem = aNode;
            xercesc::XMLString::transcode( "", tStr, 99 );
            xercesc::DOMText* pTextNode = doc_->createTextNode( tStr );
            parentElem->appendChild( (xercesc::DOMNode*)pTextNode );
            currElem = parentElem;
         }
         else {
            parentElem = currElem;
         }
      }
   }

   return currElem;

}
xercesc::DOMElement* site::SiteConfig::getElementFirstChild(const std::wstring &childName, xercesc::DOMElement *parentElem) {
   if ( parentElem != NULL ) {
      xercesc::DOMNode *childNode = parentElem->getFirstChild();
      while ( childNode != NULL ) {
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

xercesc::DOMElement* site::SiteConfig::getElementNextSibling(const std::wstring &siblingName, xercesc::DOMElement *inSiblingElem ) {
   if ( inSiblingElem != NULL ) {
      xercesc::DOMNode *siblingNode = inSiblingElem->getNextSibling();
      while ( siblingNode != NULL ) {
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

bool site::SiteConfig::getElementText(xercesc::DOMElement *elem, std::wstring& configText) {
   if ( elem != NULL ) {
      xercesc::DOMNode *childNode = elem->getFirstChild();
      while ( childNode != NULL ) {
         if ( childNode->getNodeType() == xercesc::DOMNode::TEXT_NODE ) {
            const XMLCh *nodeValue = childNode->getNodeValue();
            if ( nodeValue!=NULL ) {
               configText = nodeValue;
               return( true );
            }
         }
         childNode = childNode->getNextSibling();
      }
   }
   configText = L"";
   return( false );
}

bool site::SiteConfig::setElementText(xercesc::DOMElement *elem, const std::wstring& configText) {
   if ( elem != NULL ) {
      xercesc::DOMNode *childNode = elem->getFirstChild();
      while ( childNode != NULL ) {
         if ( childNode->getNodeType() == xercesc::DOMNode::TEXT_NODE ) {
            childNode->setNodeValue((XMLCh*)configText.c_str());
            return( true );
         }
         childNode = childNode->getNextSibling();
      }
      XMLCh tStr[100];
      xercesc::XMLString::transcode( "", tStr, 99 );
      xercesc::DOMText* pTextNode = doc_->createTextNode( tStr );
      pTextNode->setNodeValue((XMLCh*)configText.c_str());
      elem->appendChild( (xercesc::DOMNode*)pTextNode );
      return( true );
   }
   return( false );
}
site::ConfigIterator site::SiteConfig::iterator( const std::wstring &pathName,
                                                 const std::wstring &iterElementName ) const {
   return( site::ConfigIterator( getElementFirstChild(iterElementName, getElementForPath( pathName )), iterElementName ) ) ;
}

bool site::SiteConfig::next( ConfigIterator &iter ) {
   if ( iter.started_ ) {
      iter.currElem_ = getElementNextSibling( iter.iterElementName_, iter.currElem_ );
   } else {
      iter.started_ = true;
   }
   return iter.currElem_!=NULL;
}

std::string site::SiteConfig::asString() const
{
   XMLCh tempStr[100];
   xercesc::XMLString::transcode("LS", tempStr, 99);
   xercesc::DOMImplementation* impl = xercesc::DOMImplementationRegistry::getDOMImplementation(tempStr);
   xercesc::DOMLSSerializer* myWriter = ((xercesc::DOMImplementationLS*)impl)->createLSSerializer();
   // optionally you can set some features on this serializer
   xercesc::DOMConfiguration* dc = myWriter->getDomConfig();
   if (dc->canSetParameter(xercesc::XMLUni::fgDOMWRTDiscardDefaultContent, true))
       dc->setParameter(xercesc::XMLUni::fgDOMWRTDiscardDefaultContent, true);

   if (dc->canSetParameter(xercesc::XMLUni::fgDOMWRTFormatPrettyPrint, true))
       dc->setParameter(xercesc::XMLUni::fgDOMWRTFormatPrettyPrint, true);



//// set the byte-order-mark feature
//   if (myWriter->canSetFeature(XMLUni::fgDOMWRTBOM, true))
//      myWriter->setFeature(XMLUni::fgDOMWRTBOM, true);

// serialize the DOMNode to a UTF-8 string
   xercesc::XMLString::transcode("UTF-8", tempStr, 99);
   xercesc::DOMLSOutput* theOutputDesc = NULL;
   theOutputDesc = ((xercesc::DOMImplementationLS*)impl)->createLSOutput();
   theOutputDesc->setEncoding(tempStr);
   xercesc::XMLFormatTarget* myFormatTarget = new xercesc::MemBufFormatTarget();

   myWriter->write(doc_, theOutputDesc);
   char* theXMLString_Encoded =
      (char*)((xercesc::MemBufFormatTarget*)myFormatTarget)->getRawBuffer();

   std::string outStr = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
   outStr += theXMLString_Encoded;

   // release the memory
   myWriter->release();
   return outStr;


}

site::ConfigIterator site::SiteConfig::iteratorchildren( site::ConfigIterator iterParent,
                                                         const std::wstring &iterElementName ) const {
   xercesc::DOMElement *parentElem = iterParent.currElem_;
   return( site::ConfigIterator( getElementFirstChild(iterElementName, parentElem), iterElementName ) ) ;
}

