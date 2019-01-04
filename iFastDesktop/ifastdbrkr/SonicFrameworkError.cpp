#pragma once

#include <srcprag.h>
#include <ifastdbrkr\SonicFrameworkError.hpp>
#include <sstream>
#include<boost/tokenizer.hpp>


void SonicFrameworkError::init( const std::string& str ) {
   if( 0 != str.length() ) {
      xercesc::XercesDOMParser* parser = new xercesc::XercesDOMParser();
      ErrorHandler eh;
      parser->setErrorHandler(&eh);
      parser->setValidationScheme( xercesc::XercesDOMParser::Val_Never );
      parser->setDoNamespaces( true );

      xercesc::MemBufInputSource* pMBIS = new xercesc::MemBufInputSource( (XMLByte*)str.c_str(), str.length(), "test", false );
      parser->parse( *pMBIS );
      delete pMBIS;

      doc_ = parser->adoptDocument();
      if ( doc_ != NULL ) {
         rootElem_ = doc_->getDocumentElement();
      }
   }
}

DString SonicFrameworkError::Errorize( int code, 
                                       const DStringA& dstr, 
                                       const char* pszDelimiter,
                                       const std::string& exception, 
                                       const std::string& details ) {
   bool bUseZTSFormat = true; // always use ZTS format now.  RTS is dead!  Long live ZTS!!

   std::stringstream ss;
   ss << "B0000000000-0002                    ";

   if( bUseZTSFormat ) {
      ss << pszDelimiter;
   }
   ss << "F";
   ss << code;
   ss << pszDelimiter;
   ss << "F";
   ss << dstr;
   if( exception != "" ) {
      ss << std::endl << "Exception=; " << exception;
   }
#ifdef _DEBUG
   if( details != "" ) {
      ss << std::endl << details;
   }
#endif
   std::string outStr = ss.str();
   size_t iBadChar = 0;
   while( std::string::npos != ( iBadChar = outStr.find_first_of( I_(';'), iBadChar ) ) ) {
      outStr.replace( iBadChar, 1, 1, I_(':') );
   }
   iBadChar = 0;
   while( std::string::npos != ( iBadChar = outStr.find_first_of( I_('='), iBadChar ) ) ) {
      outStr.replace( iBadChar, 1, 1, I_(':') );
   }
   return( outStr );
}


DStringA SonicFrameworkError::getErrorMessage( void ) {
   DStringA errorMsg = "Unsupported Error Message";

   if( NULL == rootElem_ ) {
      return( Errorize(3, "The returned message is not valid.", pszDelimiter_) );
   }

   // is it a SonicESB exception?
   static XMLCh* XMLCH_AUTHRESPONSE = xercesc::XMLString::transcode("AuthResponse");
   static XMLCh* XMLCH_AUTHRESPONSE_CODE = xercesc::XMLString::transcode("code");
   static XMLCh* XMLCH_AUTHRESPONSE_SESSION_TOKEN_EXP = xercesc::XMLString::transcode("SESSION_TOKEN_EXP");
   static XMLCh* XMLCH_AUTHRESPONSE_SESSION_EXP = xercesc::XMLString::transcode("SESSION_EXP");
   static XMLCh* XMLCH_AUTHRESPONSE_DENIED = xercesc::XMLString::transcode("NOT_AUTHORIZED");
   static XMLCh* XMLCH_NO_AVAILABLE_SESSIONS = xercesc::XMLString::transcode("NoAvailableSessionsException");
   static XMLCh* XMLCH_EXCEPTION = xercesc::XMLString::transcode("exception");
   static XMLCh* XMLCH_MSGERROR = xercesc::XMLString::transcode("MsgError");
   static XMLCh* XMLCH_XMLNS = xercesc::XMLString::transcode("xmlns");
   static XMLCh* XMLCH_CONTAINER = xercesc::XMLString::transcode("container");
   static XMLCh* XMLCH_HOST = xercesc::XMLString::transcode("host");
   static XMLCh* XMLCH_PROCESS = xercesc::XMLString::transcode("process");
   static XMLCh* XMLCH_SERVICE_APPLICATION = xercesc::XMLString::transcode("serviceApplication");
   static XMLCh* XMLCH_STEP = xercesc::XMLString::transcode("step");
   static XMLCh* XMLCH_TOP_LEVEL_PROCESS = xercesc::XMLString::transcode("topLevelProcess");
   const XMLCh* pTagName = rootElem_->getTagName();
   if( xercesc::XMLString::equals( rootElem_->getTagName(), XMLCH_EXCEPTION ) ) {
      const XMLCh* xmlAttr = rootElem_->getAttribute( XMLCH_XMLNS );
      std::string strAttr = xercesc::XMLString::transcode( xmlAttr );
      if( strAttr == "http://www.sonicsw.com/sonicesb/exception" ) {
         std::stringstream details;
         std::string text;
         std::string exception;
         if( getTextForPath( I_("class"), exception ) ) {
            // keep everything after the last dot ... that's the exception name
            size_t iDot = std::string::npos;
            if( std::string::npos != ( iDot = exception.find_last_of( '.' ) ) ) {
               exception = exception.substr(++iDot);
            }
         } 
         else {
            exception = "Unknown exception class";
         }

         xercesc::DOMElement* pFaultDetails = getElementForPath(I_("detail/faultDetails") );

         if( NULL != pFaultDetails ) {
            details << "Container: "
                    << xercesc::XMLString::transcode( pFaultDetails->getAttribute(XMLCH_CONTAINER) )
                    << std::endl;
            details << "Host: "
                    << xercesc::XMLString::transcode( pFaultDetails->getAttribute(XMLCH_HOST) )
                    << std::endl;
            details << "Process: "
                    << xercesc::XMLString::transcode( pFaultDetails->getAttribute(XMLCH_PROCESS) )
                    << std::endl;
            details << "ServiceApplication: "
                    << xercesc::XMLString::transcode( pFaultDetails->getAttribute(XMLCH_SERVICE_APPLICATION) )
                    << std::endl;
            details << "Step: "
                    << xercesc::XMLString::transcode( pFaultDetails->getAttribute(XMLCH_STEP) )
                    << std::endl;
            details << "Top Level Process: "
                    << xercesc::XMLString::transcode( pFaultDetails->getAttribute(XMLCH_TOP_LEVEL_PROCESS) )
                    << std::endl;
         }
         if( exception == "NoAvailableSessionsException" ) {
            return( Errorize(8,"Application Server is not available for this database", pszDelimiter_, exception, details.str() ) );
         }
         else if( exception == "Open4GLException" ) {
            if( getTextForPath( I_("message"), text ) ) {
               if( text == "Fault String: Communication layer message: General Error: READPACKET IOException : java.io.EOFException (null). (7175)" ) {
                  // AppServer was restarted.  Tell user to retry
                  return(Errorize( 9, "Communication error to Application Server.", pszDelimiter_, exception, details.str()));
               }
               return( Errorize(10,"iFAST Database error",pszDelimiter_, exception,details.str() ) );
            }
         }
         else if( exception == "RunTime4GLErrorException" ) {
            return( Errorize(10,"iFAST Database error",pszDelimiter_, exception,details.str() ) );
         }
         else if( exception == "RunTime4GLStopException" ) {
            return( Errorize(10,"iFAST Database Application error",pszDelimiter_, exception,details.str() ) );
         }
         else if( getTextForPath( I_("message"), text ) ) {
            return( Errorize(1,text,pszDelimiter_, exception,details.str() ) );
         }
      }
   }
   else if( xercesc::XMLString::equals( rootElem_->getTagName(), XMLCH_MSGERROR ) ) {
      std::string text;
      if( getTextForPath( I_("Message"), text ) ) {
         return( Errorize(2, text, pszDelimiter_) );
      }
   }

/*
Condition: An error has occurred in the Sonic Framework.
Reference: ID:ffffffff9681ca12:6800007:124813E0281.

Fault String: SessionPool : NoAvailableSessions[Could not connect to the AppServer: General Error: Connection refused. (7203)]
Exception:: NoAvailableSessionsException
Container: ESB_DEV_UAT
Host: msgdevpri
Process: P.Srv_Dev_UAT.devslot59.ZTS.Single
ServiceApplication: S.devslot59.OpenEdge
Step: Call OpenEdge
Top Level Process: P.Srv_Dev_UAT.devslot59.ZTS.Single

code = 40002757 [condition], severity = 6, component name = IFASTDBRKR, method name = DSTCRequestor::receiveBuffer, in file c:\ifds\ifast\r95_unit\ifastdbrkr\dstcrequestor.cpp, at line 1924


*/

   else if( xercesc::XMLString::equals( rootElem_->getTagName(), XMLCH_AUTHRESPONSE ) ) {
      xercesc::DOMElement* pMessage = getElementForPath(I_("Message") );
      if( pMessage->getAttribute( XMLCH_AUTHRESPONSE_CODE ) ) {
         const XMLCh* code = pMessage->getAttribute(XMLCH_AUTHRESPONSE_CODE);
         if( xercesc::XMLString::equals( code, XMLCH_AUTHRESPONSE_SESSION_EXP ) ||
             xercesc::XMLString::equals( code, XMLCH_AUTHRESPONSE_SESSION_TOKEN_EXP ) ) {
            return( Errorize(6, "The session has expired.  You must logon again", pszDelimiter_) );
         } 
         else if( xercesc::XMLString::equals( code, XMLCH_AUTHRESPONSE_DENIED ) ) {
            return( Errorize(7, "Authorization Denied", pszDelimiter_) );
         }
      }
      std::string text;
      if( getTextForPath( I_("Message"), text ) ) {
         return( Errorize(5, text, pszDelimiter_) );
      }
   }
   return( Errorize(4,errorMsg, pszDelimiter_) );
}

xercesc::DOMElement* SonicFrameworkError::getElementForPath( const std::wstring &pathName, xercesc::DOMElement *parentElem ) {
   if ( parentElem == NULL ) {
      return NULL;
   }
   xercesc::DOMElement* currElem = parentElem;

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

xercesc::DOMElement* SonicFrameworkError::getElementFirstChild(const std::wstring &childName, xercesc::DOMElement *parentElem) {
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

xercesc::DOMElement* SonicFrameworkError::getElementNextSibling(const std::wstring &siblingName, xercesc::DOMElement *inSiblingElem ) {
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

bool SonicFrameworkError::getElementText(xercesc::DOMElement *elem, std::wstring& configText) {
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

bool SonicFrameworkError::getElementText(xercesc::DOMElement *elem, std::string& configText) {
   if ( elem != NULL ) {
      xercesc::DOMNode *childNode = elem->getFirstChild();
      while ( childNode != NULL ) {
         if ( childNode->getNodeType() == xercesc::DOMNode::TEXT_NODE ) {
            const XMLCh *nodeValue = childNode->getNodeValue();
            if ( nodeValue!=NULL ) {
                configText = DStringA( DString(nodeValue)).getImp();
               return( true );
            }
         }
         childNode = childNode->getNextSibling();
      }
   }
   configText = "";
   return( false );
}

