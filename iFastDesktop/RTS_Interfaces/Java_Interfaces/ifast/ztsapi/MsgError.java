package com.ifds.iFast.api;

import javax.xml.xpath.XPathExpression;
import javax.xml.xpath.XPathExpressionException;
import javax.xml.xpath.XPathFactory;

import org.w3c.dom.Document;

public class MsgError {

   private static final XPathFactory xpFactory = XPathFactory.newInstance();
   private static final XPathExpression xpOriginText;
   private static final XPathExpression xpMessageText;
   private static final XPathExpression xpMessageCode;

   static {
      try {
         xpOriginText  = xpFactory.newXPath().compile("/MsgError/Origin/text()");
         xpMessageText = xpFactory.newXPath().compile("/MsgError/Message/text()");
         xpMessageCode = xpFactory.newXPath().compile("/MsgError/Message/@code");
      } catch (Exception e) {
         throw new java.lang.ExceptionInInitializerError(e);
      }
   }

   public static MsgError forDocument(Document doc) {
      if ( !doc.getDocumentElement().getNodeName().equals("MsgError") ) {
         return null;
      }
      return new MsgError(doc);
   }

   private final Document doc;
   
   private MsgError( Document doc ) {
      this.doc = doc;
   }

   public String getOrigin() {
      try {
         return (String)xpOriginText.evaluate(doc);
      } catch (XPathExpressionException e) {
         // TODO: log stack trace...
         return null;
      }
   }
   
   public String getMessage() {
      try {
         return (String)xpMessageText.evaluate(doc);
      } catch (XPathExpressionException e) {
         // TODO: log stack trace...
         return null;
      }
   }

   public String getMessageCode() {
      try {
         return (String)xpMessageCode.evaluate(doc);
      } catch (XPathExpressionException e) {
         // TODO: log stack trace...
         return null;
      }
   }
   
}
