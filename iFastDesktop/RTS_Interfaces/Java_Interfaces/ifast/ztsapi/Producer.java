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

import java.util.Properties;

import org.w3c.dom.Document;

/**
 * An abstract interface for all Producers. Producers provide for synchronous 
 * or asynchronous communication with a host.
 *
 * @author David Smith
 */
public interface Producer
{
   /**
    * Implementations must must cause the Producer to close. After a call to this 
    * method, subsequent calls to isClosed() must return true.
    */
   void close();
   
   /**
    * Implementations will return true if the Producer is in the closed state. True must 
    * be returned if the Producer has been explicitly closed using the close() method. 
    * 
    * @return true if the Producer is in the closed state; otherwise false.
    */
   boolean isClosed();
   
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
   Document sendReceive( Document doc, Properties properties, long timeToLive ) 
         throws ProducerException, ProducerClosedException;
   
   org.dom4j.Document sendReceive( org.dom4j.Document doc, Properties properties, long timeToLive ) 
         throws ProducerException, ProducerClosedException;

   String sendReceive( String string, Properties properties, long timeToLive ) 
         throws ProducerException, ProducerClosedException;

   byte[] sendReceive( byte[] bytes, Properties properties, long timeToLive ) 
         throws ProducerException, ProducerClosedException;

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
   String send( Document doc, Properties properties ) 
         throws ProducerException, ProducerClosedException;

   String send( org.dom4j.Document doc, Properties properties ) 
         throws ProducerException, ProducerClosedException;
   
   String send( String string, Properties properties ) 
         throws ProducerException, ProducerClosedException;

   String send( byte[] bytes, Properties properties ) 
         throws ProducerException, ProducerClosedException;
}

/**
 *  -------------------------------------------------------------------------
 *
 * CHANGE LOG:
 *
 *   $Log:   Y:/VCS/RTS Interfaces/Java Interfaces/ifast/ztsapi/Producer.java-arc  $
 * 
 *    Rev 1.0   Oct 05 2009 13:11:20   yingz
 * Initial revision.
 * 
 *    Rev 1.1   Jul 16 2009 06:58:40   serverbu
 * Changed package to com.ifds.iFast.api
 * 
 *    Rev 1.0   Jul 15 2009 15:39:00   purdyech
 * Initial revision.
 * 
 *    Rev 1.5   Jun 04 2008 17:18:22   smithdav
 * Add SonicProducerTarget and support for sending byte[] as BytesMessages.
 * 
 *    Rev 1.4   May 22 2008 17:19:50   smithdav
 * Add dom4j support to Producer
 * 
 *    Rev 1.3   Apr 17 2008 11:54:12   smithdav
 * Add support for String (non-xml) send and sendReceive methods. Also add support for JMSReplyTo.
 * 
 *    Rev 1.2   Aug 13 2007 21:46:22   smithdav
 * Update to use JAXP and log4j.
 * 
 *    Rev 1.1   May 02 2007 18:36:08   smithdav
 * Added overloads of send and sendReceive to take a DOM Documents and a Properies object.  Deprecate the others.
 * Also added DOM parsing and serializing code.
 * 
 *    Rev 1.0   Apr 24 2007 12:55:14   smithdav
 * Initial revision.
 * 
 */
