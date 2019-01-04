/**
 *  -------------------------------------------------------------------------
 *                                 Copyright
 *
 *               International Financial Data Services Limited 2005
 *                            All rights reserved.
 *
 *
 *  No part of this document may be reproduced, stored in a retrieval
 *  system, or transmitted, in any form or by any means, electronic,
 *  mechanical, photocopying, networking or otherwise, without the prior
 *  written permission of International Financial Data Services Limited.
 *
 *  The computer system, procedures, data bases, and programs created and
 *  maintained by International Financial Data Services Limited are proprietary
 *  in nature and as such are confidential. Any unauthorised use, misuse, or
 *  disclosure of such items or information may result in civil liabilities
 *  and may be subject to criminal penalties under the applicable laws.
 *  -------------------------------------------------------------------------
 *
 */

package com.ifds.iFast.api;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.IOException;
import java.io.StringReader;
import java.io.StringWriter;
import java.util.Enumeration;
import java.util.Properties;

import javax.jms.BytesMessage;
import javax.jms.DeliveryMode;
import javax.jms.JMSException;
import javax.jms.Message;
import javax.jms.Queue;
import javax.jms.QueueConnection;
import javax.jms.QueueReceiver;
import javax.jms.QueueSender;
import javax.jms.QueueSession;
import javax.jms.TemporaryQueue;
import javax.jms.TextMessage;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;

import org.apache.log4j.Logger;
import org.apache.xml.serialize.OutputFormat;
import org.apache.xml.serialize.XMLSerializer;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.xml.sax.InputSource;
import org.xml.sax.SAXException;

import progress.message.jclient.QueueConnectionFactory;

/**
 *  SonicProducer - JMS message queue producer for communications with SonicMQ.
 * 
 * @author David Smith
 */
//@SuppressWarnings("deprecation")
public final class SonicProducer implements Producer {

   /**
    * Construct a SonicProducer initialized with a dedicated ConnectionFactory, 
    * Connection, QueueSession and Sender.
    * 
    * @param target    the SonicMQ target
    * @param user      the SonicMQ connection user
    * @param password  the SonicMQ connection password
    * @exception ProducerException
    *                   thrown if the SonicProducer cannot be initialized
    */
   public SonicProducer( SonicProducerTarget target, String user, String password ) 
         throws ProducerException {
      this(target, user, password, NO_USE_LIMIT, DEFAULT_BYTES_ENCODING);
   }
   
   /**
    * Construct a SonicProducer initialized with a dedicated ConnectionFactory, 
    * Connection, QueueSession and Sender.
    * 
    * @param target    the SonicMQ target
    * @param user      the SonicMQ connection user
    * @param password  the SonicMQ connection password
    * @param bytesEncoding
    *                  the char encoding for converting bytes message to String
    * @exception ProducerException
    *                   thrown if the SonicProducer cannot be initialized
    */
   public SonicProducer( SonicProducerTarget target, String user, String password, String bytesEncoding ) 
         throws ProducerException {
      this(target, user, password, NO_USE_LIMIT, bytesEncoding);
   }
   
   /**
    * Construct a SonicProducer initialized with a dedicated ConnectionFactory, 
    * Connection, QueueSession and Sender.
    * 
    * @param target    the SonicMQ target
    * @param user      the SonicMQ connection user
    * @param password  the SonicMQ connection password
    * @param useLimit  the max number of times the producer will be used
    * @exception ProducerException
    *                   thrown if the SonicProducer cannot be initialized
    */
   public SonicProducer( SonicProducerTarget target, String user, String password, long useLimit ) 
         throws ProducerException {
      this(target, user, password, useLimit, DEFAULT_BYTES_ENCODING);
   }
   
   /**
    * Construct a SonicProducer initialized with a dedicated ConnectionFactory, 
    * Connection, QueueSession and Sender.
    * 
    * @param target    the SonicMQ target
    * @param user      the SonicMQ connection user
    * @param password  the SonicMQ connection password
    * @param useLimit  the max number of times the producer will be used
    * @param bytesEncoding
    *                  the char encoding for converting bytes message to String
    * @exception ProducerException
    *                   thrown if the SonicProducer cannot be initialized
    */
   public SonicProducer( SonicProducerTarget target, String user, String password, long useLimit, String bytesEncoding ) 
         throws ProducerException {
      
      this.targerStr = target.toString();
      this.useLimit = useLimit;
      this.bytesEncoding = bytesEncoding;

      logger = Logger.getLogger(this.getClass());
      logger.info( "Creating new SonicProducer for [" + targerStr + "]...");

      TimingProfiler tprofile = TimingProfiler.getSoft();
      tprofile.startProfile("SonicProducer.SonicProducer");
      
      try {
         QueueConnectionFactory connectFactory = new QueueConnectionFactory();
         connectFactory.setFaultTolerant(Boolean.TRUE);
         connectFactory.setConnectionURLs(target.getBrokerURLs());
         tprofile.markInterval("new QueueConnectionFactory");
         connectFactory.setDefaultUser(user);
         connectFactory.setDefaultPassword(password);
         connection = connectFactory.createQueueConnection(  );
         tprofile.markInterval("connectFactory.createQueueConnection");

         connection.start();
         tprofile.markInterval("connection.start");

         session = connection.createQueueSession( false, javax.jms.Session.AUTO_ACKNOWLEDGE );
         tprofile.markInterval("connection.createQueueSession");

         Queue sendQueue = session.createQueue( target.getSendQueueName() );
         tprofile.markInterval("session.createSendQueue");

         sender = session.createSender( sendQueue );
         tprofile.markInterval("session.createSender");

         if ( !target.hasReceiveQueue() ) {
            receiveQueue = session.createTemporaryQueue();
            tprofile.markInterval("session.createTemporaryQueue");
         } else {
            receiveQueue = session.createQueue( target.getReceiveQueueName() );
            tprofile.markInterval("session.createReceiveQueue");
         }
         
         queueReceiver = session.createReceiver( receiveQueue );
         tprofile.markInterval("session.createReceiver");

      } catch ( Exception e ) {
         if ( connection != null ) {
            if ( session != null ) {
               try {
                  session.close();
               } catch ( Exception ec ) {}
            }
            try {
               connection.close();
            } catch ( Exception ec ) {}
         }
         logger.error("Failed to construct SonicProducer.");
         throw new ProducerException("Failed to construct SonicProducer.", e);
      } finally {
         tprofile.endProfile();
      }
      
   }

   /**
    * Closes the QueueSession and Connection to the SonicMQ broker. Subsequent calls to
    * isClosed() will return true. Close is not synchronize; caller must ensure
    * close is not concurrent.
    */
   public void close() {

      logger.info( "Closing SonicProducer for [" + targerStr + "]...");
      TimingProfiler tprofile = TimingProfiler.getSoft();
      tprofile.startProfile("SonicProducer.close");
      try {
         if ( receiveQueue!=null && (receiveQueue instanceof TemporaryQueue)) {
            try {
               tprofile.markInterval("tempQueue.delete");
               ((TemporaryQueue)receiveQueue).delete();
            } catch ( Exception e ) {
               logger.error( "SonicProducer failed to delete temp queue. ", e );
            }
         }
         
         if ( session != null ) {
            try {
               tprofile.markInterval("session.close");
               session.close();
            } catch ( Exception e ) {
               logger.error( "SonicProducer failed on close. ", e );
            }
            session = null;
         }

         if ( connection != null ) {
            logger.debug( "Closing SonicProducer for [" + targerStr + "]...");
            try {
               tprofile.markInterval("connection.close");
               connection.close();
            } catch ( Exception e ) {
               logger.error( "SonicProducer failed on close. ", e );
            }
            connection = null;
         }
      } finally {
         tprofile.endProfile();
      }
   }
   
   /**
    * Closed this producer.
    */
   public void finalize() {
      close();
   }
   
   /**
    * Returns true if this producer has been explicitly closed.
    * 
    * @return true if this producer has been closed; otherwise false.
    */
   public boolean isClosed() {
      return (connection==null);
   }
   
   private void preSend() throws ProducerClosedException {
      if ( isClosed() ) {
         throw new ProducerClosedException();
      }
      ++useCount;
   }
   
   private TransientProducerException handleTransientException(String text, Exception e) {
       this.close();
       return new TransientProducerException(text, e);
   }
      
   private void postSend() throws ProducerClosedException {
      if ( !isClosed() && useLimit!=NO_USE_LIMIT && useCount >= useLimit ) {
         this.close();
      }
   }
   
   public String sendReceive( String string, Properties properties, long timeToLive ) 
      throws ProducerException, ProducerClosedException
   {
      preSend();
      try {
         return messageToString(sendReceive( requestToTextMessage(string), properties, timeToLive));
      } catch ( JMSException e ) {
       throw handleTransientException("SonicProducer failed on sync send/receive of message.", e);
      } finally {
          this.postSend();
       }
   }

   public byte[] sendReceive( byte[] bytes, Properties properties, long timeToLive ) 
         throws ProducerException, ProducerClosedException
   {
      preSend();
      try {
         return messageToBytes(sendReceive( requestToBytesMessage(bytes), properties, timeToLive));
      } catch ( JMSException e ) {
       throw handleTransientException("SonicProducer failed on sync send/receive of message.", e);
      } finally {
         this.postSend();
      }
   }

   /**
    * Synchronous message processing. A message is sent to the host and the method waits 
    * for a response to be returned. If the message cannot be sent , a ProducerException 
    * is thrown. If an exception occurs while waiting for the response, null is returned.
    * 
    * @param doc        the DOM/xml request message
    * @param properties the properties to attach to the message
    * @param timeToLive the time to wait for a response to return in msecs. 0ms will cause the receiver
    *                   to wait forever
    * @return a DOM containing the text of the response message, or null if no
    *         response was returned
    * @exception ProducerException
    *                   thrown if an exception occurred while setting up or sending the request message
    * @exception ProducerClosedException
    *                   throws if the producer is in the "closed" state when the method is called.
    */
   public Document sendReceive( Document doc, Properties properties, long timeToLive ) 
         throws ProducerException, ProducerClosedException
   {
      preSend();
      try {
         return messageToDOM(sendReceive( requestToTextMessage(doc), properties, timeToLive));
      } catch ( JMSException e ) {
       throw handleTransientException("SonicProducer failed on sync send/receive of message.", e);
      } finally {
         this.postSend();
      }
   }
   
   public org.dom4j.Document sendReceive( org.dom4j.Document doc, Properties properties, long timeToLive ) 
         throws ProducerException, ProducerClosedException
   {
      preSend();
      try {
         return messageToDom4j(sendReceive( requestToTextMessage(doc), properties, timeToLive));
      } catch ( JMSException e ) {
       throw handleTransientException("SonicProducer failed on sync send/receive of message.", e);
      } finally {
         this.postSend();
      }
   }
   
   /**
    * Synchronous message processing. A message is sent to the target request queue and
    * the method waits for a response to be returned on a temporary queue. If an
    * exception occurs before the message is sent or during the send, a ProducerException 
    * occurs. If there is a timeout or an exception occurs while waiting, null is returned.
    * 
    * @param msg        the request message
    * @param properties the properties to attach to the message
    * @param timeToLive the time to wait for a response to return in msecs. 0ms will cause the receiver
    *                   to wait forever
    * @return a string containing the text of the response message, or null if no
    *         response was returned (normally a timeout condition)
    * @exception ProducerException
    *                   thrown if an exception occurred while setting up or sending the request message
    * @exception ProducerClosedException
    *                   throws if the producer is in the "closed" state when the method is called.
    */
   private Message sendReceive( Message msg, Properties properties, long timeToLive ) 
         throws JMSException, NoResponseException
   {

      TimingProfiler tprofile = TimingProfiler.getSoft();
      tprofile.startProfile("SonicProducer.sendReceive");

      try {
         if ( properties != null ) {
            Enumeration nameEnum = properties.propertyNames();
            while ( nameEnum.hasMoreElements() ) {
               String name = (String)nameEnum.nextElement();
               msg.setStringProperty( name, properties.getProperty(name) );
            }
         }
         msg.setBooleanProperty( "JMS_SonicMQ_preserveUndelivered", true);
         msg.setBooleanProperty( "JMS_SonicMQ_notifyUndelivered", true);
         tprofile.markInterval("msg.set*Properties");

         String corrId = Long.toString(nextCorrID++);
         
         // set the reply to our temporary queue
         msg.setJMSReplyTo( receiveQueue );
         tprofile.markInterval("msg.setJMSReplyTo");

         // set the reply to our temporary queue
         msg.setJMSCorrelationID(corrId);
         tprofile.markInterval("msg.setJMSCorrelationID");

         // send the message and wait for the response                    
         sender.send( msg, DeliveryMode.NON_PERSISTENT, 4, timeToLive );
         tprofile.markInterval("sender.send");

         while (true) {
            Message response = null;
            try {
               response = (timeToLive == 0L) ? queueReceiver.receive()
                                             : queueReceiver.receive(timeToLive);
            } catch ( Exception e ) {
               tprofile.markInterval("queueReceiver.receive (exception)");
               throw new NoResponseException("No response received by producer.", e);
            }
            if (response == null) {
               tprofile.markInterval("queueReceiver.receive (no response)");
               throw new NoResponseException("No response received by producer." + (timeToLive==0L ? "" : " Possible timeout."));
            }
            try {
               String respCorrId = response.getJMSCorrelationID();
               if ( respCorrId!=null && respCorrId.equals(corrId) ) {
                  tprofile.markInterval("queueReceiver.receive (match)");
                  // update the property object with values from the message...
                  if ( properties != null ) {
                     properties.clear();
                     Enumeration nameEnum = response.getPropertyNames();
                     while (nameEnum.hasMoreElements()) {
                        String name = (String)nameEnum.nextElement();
                        if (name.startsWith("IFAST_")) {
                           properties.setProperty(name, response.getObjectProperty(name).toString());
                        }
                     }
                  }
                  return( response );
               }
            } catch ( Exception e ) {
               logger.warn("Failed to resolve corelation id", e);
            }
            tprofile.markInterval("queueReceiver.receive (no match)");
         } 
         
      } finally {
         tprofile.endProfile();
      }

   }
   
   /**
    * Asynchronous message processing. A message is sent to the host and returns immediately. 
    * If an exception occurs before the message is sent or during the send, a 
    * ProducerException occurs.
    * 
    * @param doc        the DOM/xml message
    * @param properties the properties to attach to the message
    * @return a string containing an JMSMessageID for the sent message
    * @exception ProducerException
    *                   thrown if an exception occurred while setting up or sending the messages
    * @exception ProducerClosedException
    *                   throws if the producer is in the "closed" state when the method is called.
    */
   public String send( Document doc, Properties properties ) 
         throws ProducerException, ProducerClosedException
   {
      preSend();
      try {
         return send( requestToTextMessage(doc), properties);
      } catch ( JMSException e ) {
       throw handleTransientException("SonicProducer failed on async send of message.", e);
      } finally {
         this.postSend();
      }
   }

   public String send( org.dom4j.Document doc, Properties properties ) 
         throws ProducerException, ProducerClosedException
   {
      preSend();
      try {
         return send( requestToTextMessage(doc), properties);
      } catch ( JMSException e ) {
          throw handleTransientException("SonicProducer failed on async send of message.", e);
      } finally {
         this.postSend();
      }
   }

   public String send( String string, Properties properties ) 
      throws ProducerException, ProducerClosedException
   {
      preSend();
      try {
         return send( requestToTextMessage(string), properties);
      } catch ( JMSException e ) {
          throw handleTransientException("SonicProducer failed on async send of message.", e);
      } finally {
         this.postSend();
      }
   }

   public String send( byte[] bytes, Properties properties ) 
   throws ProducerException, ProducerClosedException
   {
      preSend();
      try {
         return send( requestToBytesMessage(bytes), properties);
      } catch ( JMSException e ) {
          throw handleTransientException("SonicProducer failed on async send of message.", e);
      } finally {
         this.postSend();
      }
   }

   /**
    * Asynchronous message processing. A message is sent to the target request queue and 
    * returns immediately. If an exception occurs before the message is sent or during 
    * the send, a ProducerException occurs.
    * 
    * @param msg        the message
    * @param properties the properties to attach to the message
    * @return a string containing an JMSMessageID for the sent message
    * @exception ProducerException
    *                   thrown if an exception occurred while setting up or sending the messages
    * @exception ProducerClosedException
    *                   throws if the producer is in the "closed" state when the method is called.
    */
   private String send( Message msg, Properties properties )
         throws JMSException 
   {

      TimingProfiler tprofile = TimingProfiler.getSoft();
      tprofile.startProfile("SonicProducer.sendReceive");

      try {
         if ( properties != null ) {
            Enumeration nameEnum = properties.propertyNames();
            while ( nameEnum.hasMoreElements() ) {
               String name = (String)nameEnum.nextElement();
               if (name.equals("JMSReplyTo")) {
                  msg.setJMSReplyTo( session.createQueue(properties.getProperty(name)) );
               } else {
                  msg.setStringProperty( name, properties.getProperty(name) );
               }
            }
         }
         msg.setBooleanProperty( "JMS_SonicMQ_preserveUndelivered", true);
         msg.setBooleanProperty( "JMS_SonicMQ_notifyUndelivered", true);
         tprofile.markInterval("msg.set*Properties");

         // async send the data/message
         sender.send( msg );
         tprofile.markInterval("sender.send");

         String msgId = msg.getJMSMessageID();
         tprofile.markInterval("msg.getJMSMessageID");

         return  msgId;
         
      } finally {
         tprofile.endProfile();
      }

   }
   
   private Message requestToTextMessage(Object req) throws ProducerException, JMSException {
      String strReq = null;
      try {
         if ( req instanceof Document ) {
            StringWriter stringOut = new StringWriter();
            OutputFormat format = new OutputFormat();
            format.setOmitXMLDeclaration(true);
            format.setIndenting(false);
            XMLSerializer serial = new XMLSerializer( stringOut, format );
            serial.asDOMSerializer();
            serial.serialize( ((Document)req).getDocumentElement() );
            strReq = stringOut.toString();
         } else if ( req instanceof org.dom4j.Document ) {
            StringWriter stringOut = new StringWriter();
            org.dom4j.io.OutputFormat format = org.dom4j.io.OutputFormat.createCompactFormat();
            format.setSuppressDeclaration(true);
            org.dom4j.io.XMLWriter writer =  new org.dom4j.io.XMLWriter(stringOut, format);
            writer.write((org.dom4j.Document)req);
            writer.flush();
            strReq = stringOut.toString();
         } else {
            strReq = req.toString();
         }
      } catch ( Exception ex ) {
         throw new ProducerException("Cannot serialize document to Message.", ex);
      }
      TextMessage message = session.createTextMessage();
      message.setText(strReq);
      logger.debug("Sending:" + strReq);
      return message;
   }
   
   private Message requestToBytesMessage(Object req) throws ProducerException, JMSException {
      byte[] bytesReq = null;
      try {
         if ( req instanceof Document ) {
            ByteArrayOutputStream bytesOut = new ByteArrayOutputStream();
            OutputFormat format = new OutputFormat();
            format.setEncoding(bytesEncoding);
            format.setIndenting(false);
            XMLSerializer serial = new XMLSerializer( bytesOut, new OutputFormat() );
            serial.asDOMSerializer();
            serial.serialize( ((Document)req).getDocumentElement() );
            bytesReq = bytesOut.toByteArray();
         } else if ( req instanceof org.dom4j.Document ) {
            ByteArrayOutputStream bytesOut = new ByteArrayOutputStream();
            org.dom4j.io.OutputFormat format = org.dom4j.io.OutputFormat.createCompactFormat();
            format.setEncoding(bytesEncoding);
            org.dom4j.io.XMLWriter writer =  new org.dom4j.io.XMLWriter(bytesOut, format);
            writer.write((org.dom4j.Document)req);
            writer.flush();
            bytesReq = bytesOut.toByteArray();
         } else if ( req instanceof byte[] ){
            bytesReq = (byte[])req;
         } else {
            bytesReq = req.toString().getBytes(bytesEncoding);
         }
      } catch ( Exception ex ) {
         throw new ProducerException("Cannot serialize document to Message.", ex);
      }
      BytesMessage message = session.createBytesMessage();
      message.writeBytes(bytesReq);
      logger.debug("Sending:" + bytesReq);
      return message;
   }
   
   private void handleMessageError(Message message) throws ProducerException {
      try {
         if (message.propertyExists("IFAST_MESSAGE_ERROR") 
                  && message.getBooleanProperty("IFAST_MESSAGE_ERROR")) {

            MsgError msgErr;
            if ( message instanceof TextMessage ) {
               msgErr = MsgError.forDocument(textMessageToDOM((TextMessage)message));
            } else if ( message instanceof BytesMessage ) {
               msgErr = MsgError.forDocument(bytesMessageToDOM((BytesMessage)message));
            } else {
               throw new ProducerException("Cannot parse error response message. Invalid message type.");
            }
            if (msgErr==null) {
               throw new ProducerException("Response flagged as Messaging Error, but content does not match.");
            }
            throw new ProducerException(msgErr);
         }
      } catch (ProducerException ex) {
         throw ex;
      } catch (Exception ex) {
         throw new ProducerException("Cannot handle Message Error.", ex);
      }
   }
   
   private String messageToString(Message message) throws ProducerException {
      handleMessageError(message);
      if ( message instanceof TextMessage ) {
         return messageToString((TextMessage)message);
      } else if ( message instanceof BytesMessage ) {
         return messageToString((BytesMessage)message);
      } else {
         throw new ProducerException("Cannot parse response message. Invalid message type.");
      }
   }

   private String messageToString(BytesMessage message) throws ProducerException {
      try {
         byte[] msgBytes = new byte[(int)message.getBodyLength()];
         message.readBytes(msgBytes);
         String str = new String(msgBytes, bytesEncoding);
         logger.debug("Received:" + str);
         return str;
      } catch ( Exception ex ) {
         throw new ProducerException("Cannot parse response message.", ex);
      }
   }
   
   private String messageToString(TextMessage message) throws ProducerException {
      try {
         String str = message.getText();
         logger.debug("Received:" + str);
         return str;
      } catch ( Exception ex ) {
         throw new ProducerException("Cannot parse response message.", ex);
      }
   }
   
   private byte[] messageToBytes(Message message) throws ProducerException {
      handleMessageError(message);
      if ( message instanceof TextMessage ) {
         return messageToBytes((TextMessage)message);
      } else if ( message instanceof BytesMessage ) {
         return messageToBytes((BytesMessage)message);
      } else {
         throw new ProducerException("Cannot parse response message. Invalid message type.");
      }
   }

   private byte[] messageToBytes(BytesMessage message) throws ProducerException {
      try {
         byte[] msgBytes = new byte[(int)message.getBodyLength()];
         message.readBytes(msgBytes);
         logger.debug("Received:" + msgBytes);
         return msgBytes;
      } catch ( Exception ex ) {
         throw new ProducerException("Cannot parse response message.", ex);
      }
   }
   
   private byte[] messageToBytes(TextMessage message) throws ProducerException {
      try {
         String str = message.getText();
         logger.debug("Received:" + str);
         return str.getBytes(bytesEncoding);
      } catch ( Exception ex ) {
         throw new ProducerException("Cannot parse response message.", ex);
      }
   }
   
   private Document messageToDOM(Message message) throws ProducerException {
      handleMessageError(message);
      if ( message instanceof TextMessage ) {
         return textMessageToDOM((TextMessage)message);
      } else if ( message instanceof BytesMessage ) {
         return bytesMessageToDOM((BytesMessage)message);
      } else {
         throw new ProducerException("Cannot parse response message. Invalid message type.");
      }
   }
   
   private Document bytesMessageToDOM(BytesMessage message) throws ProducerException {
      try {
         byte[] msgBytes = new byte[(int)message.getBodyLength()];
         message.readBytes(msgBytes);
         String str = new String(msgBytes, bytesEncoding);
         logger.debug("Received:" + str);
         ByteArrayInputStream is =  new ByteArrayInputStream(msgBytes);
         try {
            return respBuilderFactory.newDocumentBuilder().parse(new InputSource(is));
         } finally {
            is.close();
         }
      } catch ( Exception ex ) {
         throw new ProducerException("Cannot parse response message.", ex);
      }
   }
   
   private Document textMessageToDOM(TextMessage message) throws ProducerException {
      try {
         String str = message.getText();
         logger.debug("Received:" + str);
         StringReader reader = new StringReader(str);
         try {
            return respBuilderFactory.newDocumentBuilder().parse(new InputSource(reader));
         } finally {
            reader.close();
         }
      } catch ( Exception ex ) {
         throw new ProducerException("Cannot parse response message.", ex);
      }
   }
      
   private org.dom4j.Document messageToDom4j(Message message) throws ProducerException {
      handleMessageError(message);
      if ( message instanceof TextMessage ) {
         return textMessageToDom4j((TextMessage)message);
      } else if ( message instanceof BytesMessage ) {
         return bytesMessageToDom4j((BytesMessage)message);
      } else {
         throw new ProducerException("Cannot parse response message. Invalid message type.");
      }
   }
   
   private org.dom4j.Document bytesMessageToDom4j(BytesMessage message) throws ProducerException {
      try {
         byte[] msgBytes = new byte[(int)message.getBodyLength()];
         message.readBytes(msgBytes);
         String str = new String(msgBytes);
         logger.debug("Received:" + str);
         ByteArrayInputStream is =  new ByteArrayInputStream(msgBytes);
         try {
            return new org.dom4j.io.SAXReader().read(is); 
         } finally {
            is.close();
         }
      } catch ( Exception ex ) {
         throw new ProducerException("Cannot parse response message.", ex);
      }
   }
   
   private org.dom4j.Document textMessageToDom4j(TextMessage message) throws ProducerException {
      try {
         String str = message.getText();
         logger.debug("Received:" + str);
         StringReader reader = new StringReader(str);
         try {
            return new org.dom4j.io.SAXReader().read(reader); 
         } finally {
            reader.close();
         }
      } catch ( Exception ex ) {
         throw new ProducerException("Cannot parse response message.", ex);
      }
   }

   public static void main( String[] args )
   {
      String brokerUrl = args[0];
      String queue     = args[1];
      String user      = args[2];
      String password  = args[3];
      String envName   = args[4];
 
      Logging.configure(); // simple console configuration
      Logger testLogger = Logger.getLogger(SonicProducer.class);
      
      File reqFile = null;
      if (args.length >5) {
         reqFile = new File(args[5]);
      }
      
      testLogger.info("Executing test:");
      testLogger.info("  Broker URL = " + brokerUrl);
      testLogger.info("  Queue      = " + queue);
      testLogger.info("  User       = " + user);
      testLogger.info("  Password   = " + password);
      testLogger.info("  iFast Env. = " + envName);
      
      Properties properties =  new Properties();
      properties.setProperty("envName", envName);

      testSync(brokerUrl, queue, user, password, properties, reqFile );
   }
   
   public static void testSync(String brokerUrl, String queue, String user, String password, Properties properties, File reqFile) {
      Logger testLogger = Logger.getLogger(SonicProducer.class);
      try {
         SonicProducer producer = new SonicProducer( new SonicProducerTarget(brokerUrl, queue), user, password );

         try {
            Document request = reqFile == null ? createTestDocument("SYNC")
                                               : parseTestFile(reqFile);
            Document response = producer.sendReceive( request, properties, 10000 );
            testLogger.info("Receive reply: \"" + documentToString(response) + "\"");
         } catch ( ProducerClosedException e ) {
            testLogger.error( "Producer is closed.");
         } finally {
            producer.close();
         }
      } catch ( Exception e ) {
         testLogger.error( "Test failed.", e);
      }
   }
  
   public static void testAsync(String brokerUrl, String queue, String user, String password, Properties properties, File reqFile) {
      Logger testLogger = Logger.getLogger(SonicProducer.class);
      try {
         SonicProducer producer = new SonicProducer( new SonicProducerTarget(brokerUrl, queue), user, password );

         try {
            Document request = reqFile == null ? createTestDocument("ASYNC")
                  : parseTestFile(reqFile);
            String msgId = producer.send( request, properties );
            testLogger.info("Sent message: \"" + msgId + "\"");
         } catch ( ProducerClosedException e ) {
            testLogger.error( "Producer is closed.");
         } finally {
            producer.close();
         }
      } catch ( Exception e ) {
         testLogger.error( "Test failed.", e);
      }
   }
  
   private static Document createTestDocument(String mode) throws ParserConfigurationException {
      Document doc = DocumentBuilderFactory.newInstance().newDocumentBuilder().newDocument();
      Element root = doc.createElement("message");
      
      Element item = doc.createElement("sentBy");
      item.appendChild( doc.createTextNode(SonicProducer.class.getName()) );
      root.appendChild( item );
      
      item = doc.createElement("mode");
      item.appendChild( doc.createTextNode(mode) );
      root.appendChild( item );
      
      doc.appendChild( root );
      return doc;
   }
   
   private static Document parseTestFile(File file) throws SAXException, IOException, ParserConfigurationException {
      return DocumentBuilderFactory.newInstance().newDocumentBuilder().parse(file);
   }
   
   private static String documentToString(Document doc) throws IOException {
      if ( doc==null ) {
         return null;
      }
      StringWriter stringOut = new StringWriter();
      XMLSerializer serial = new XMLSerializer( stringOut, new OutputFormat() );
      serial.asDOMSerializer();
      serial.serialize( doc.getDocumentElement() );
      return stringOut.toString();
   }
   
   public static String DEFAULT_BYTES_ENCODING = "ISO8859_1";
   public static long DEFAULT_USE_LIMIT = 500L;
   public static long NO_USE_LIMIT = 0L;

   private final String bytesEncoding;
   private QueueConnection     connection = null;
   private QueueSession        session = null;
   private final QueueSender   sender;
   private final Queue         receiveQueue;
   private final QueueReceiver queueReceiver;
   
   private final long useLimit;
   private long useCount = 0;
   
   long nextCorrID = 0;
   
   private final DocumentBuilderFactory respBuilderFactory = DocumentBuilderFactory.newInstance();

   private final Logger logger;
   private final String targerStr;
   
}

/**
 * -------------------------------------------------------------------------
 * 
 * CHANGE LOG:
 * 
 * $Log:   Y:/VCS/RTS Interfaces/Java Interfaces/ifast/ztsapi/SonicProducer.java-arc  $
 * 
 *    Rev 1.0   Oct 05 2009 13:05:24   yingz
 * Initial revision.
 * 
 *    Rev 1.3   Jul 16 2009 08:15:28   purdyech
 * asdfasdfasdf
 * 
 *    Rev 1.2   Jul 16 2009 07:23:56   purdyech
 * Changed references to com.ifdsgroup.* to com.ifds.iFast.api
 * 
 *    Rev 1.1   Jul 16 2009 06:59:38   serverbu
 * Changed package to com.ifds.iFast.api
 * 
 *    Rev 1.0   Jul 15 2009 15:54:22   purdyech
 * Initial revision.
 * 
 *    Rev 1.29   Jun 02 2009 12:12:56   smithdav
 * Remove original request fsproperties before adding response properties.
 * 
 *    Rev 1.28   May 29 2009 10:49:28   smithdav
 * Fix call stack overflow problem caused by a recusion bug.
 * 
 *    Rev 1.27   May 14 2009 14:45:10   smithdav
 * Extend ErrorMsg handling.  Handle response properties.
 * 
 *    Rev 1.26   Apr 24 2009 19:55:06   smithdav
 * Add logic to clear mismatched messages instead of using a correlation id.
 * 
 *    Rev 1.25   Mar 31 2009 16:27:40   smithdav
 * Remove some logging that is misleading.
 * 
 *    Rev 1.24   Jan 30 2009 12:58:00   smithdav
 * Allow JMSExceptions to be thrown unhandled from creataeMessage calls. This will cause ProducerPool to retry the message on a fresh Producer.
 * 
 *    Rev 1.23   Jan 07 2009 13:14:40   smithdav
 * Fix use limit in non-pooled case.
 * 
 *    Rev 1.22   Dec 05 2008 15:00:24   smithdav
 * Revert to deprecated XML serialization mechanism to be compatabe with iFastWeb parser.
 * 
 *    Rev 1.20   Oct 10 2008 13:39:02   smithdav
 * Add use limit for producers and handle config not found errors better.
 * 
 *    Rev 1.19   Jul 18 2008 12:39:58   smithdav
 * TimingProfiler improvements.
 * 
 *    Rev 1.18   Jul 17 2008 19:48:24   smithdav
 * Change from CLIENT_ACK to AUTO_ACK
 * 
 *    Rev 1.17   Jul 17 2008 19:38:42   smithdav
 * Timing profiler changes.
 * 
 *    Rev 1.16   Jun 04 2008 17:18:22   smithdav
 * Add SonicProducerTarget and support for sending byte[] as BytesMessages.
 * 
 *    Rev 1.15   May 22 2008 17:38:42   smithdav
 * javadoc fixes
 * 
 *    Rev 1.14   May 22 2008 17:19:52   smithdav
 * Add dom4j support to Producer
 * 
 *    Rev 1.13   May 20 2008 14:39:08   smithdav
 * Add code to support fault-tolerance, and add additional trace messages for response data.
 * 
 *    Rev 1.12   Apr 29 2008 15:33:00   smithdav
 * Reduce logging level on some messages to DEBUG.
 * 
 *    Rev 1.11   Apr 29 2008 14:50:08   smithdav
 * Fix selector.
 * 
 *    Rev 1.10   Apr 29 2008 13:23:12   smithdav
 * Reuse temporary queue, and add a simple selector.
 * 
 *    Rev 1.9   Apr 28 2008 18:00:46   smithdav
 * Add debug logging that prints the send and recieve message text.
 * 
 *    Rev 1.8   Apr 17 2008 11:54:12   smithdav
 * Add support for String (non-xml) send and sendReceive methods. Also add support for JMSReplyTo.
 * 
 *    Rev 1.7   Aug 13 2007 21:46:22   smithdav
 * Update to use JAXP and log4j.
 * 
 *    Rev 1.6   Jul 05 2007 16:29:58   smithdav
 * Label Change...
 * 
 *    Rev 1.5   May 25 2007 12:04:10   smithdav
 * Allow response paring and response error mesages to be thrown.
 * 
 *    Rev 1.4   May 25 2007 10:23:22   smithdav
 * Added MsgError response handling and improved error handling.
 * 
 *    Rev 1.3   May 24 2007 15:50:04   smithdav
 * Updated testing code to allow a file argument to be passed optionally.
 * 
 *    Rev 1.2   May 23 2007 11:24:00   smithdav
 * Moved the static testing methods from Test.java to SonicProducer.java.
 * 
 *    Rev 1.1   May 02 2007 18:36:08   smithdav
 * Added overloads of send and sendReceive to take a DOM Documents and a Properies object.  Deprecate the others.
 * Also added DOM parsing and serializing code.
 * 
 *    Rev 1.0   Apr 24 2007 12:55:14   smithdav
 * Initial revision.
 * 
 */
