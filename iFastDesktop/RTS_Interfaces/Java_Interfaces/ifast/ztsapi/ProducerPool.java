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

import java.util.LinkedList;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Properties;

import org.apache.log4j.Logger;
import org.w3c.dom.Document;

/**
 * <p>
 * A ProducerPool is a Producer that manages a pool of simple Producers. This allows
 * efficient, concurrent processing of messages.
 * </p>
 * <p>
 * This abstract class is extended by providing one or more constructors and 
 * implementing the abstract createProducer(). 
 * The constructors must ultimately call one of this classes constructors and the 
 * init() method.
 * The createProducer() method should return a newly costructed Producer object.
 * The code below gives a fully implemented concrete ProducerPool.
 * </p>
 * <code><pre>
 * public final class MyProducerPool extends ProducerPool {
 *    private final String myParameter;
 *  
 *    public MyProducerPool(int initialSize, String myParameter) {
 *       super(initialSize);
 *       this.myParameter = myParameter;
 *       init();
 *    }
 * 
 *    protected Producer createProducer() throws ProducerException {
 *       return new MyProducer(myParameter);
 *    }
 * }
 * </pre></code>
 * @author David Smith
 */
public abstract class ProducerPool implements Producer {
   /**
    * Constructs a ProducerPool of the gives size and the give waitThreshold. Classes
    * that extend ProducerPool are expected to have constructors that call this 
    * constructor followd by the init method.
    * 
    * @param initialSize the normal size of the pool.
    * @param waitThreshold
    *                   the amount of time in msec that the send/sendReceive method will wiat on the pool
    *                   before creating a new one.
    */
   protected ProducerPool(int initialSize, long waitThreshold ) {
      this.logger = Logger.getLogger(this.getClass());
      this.initialSize = initialSize;
      this.waitThreshold = waitThreshold;
   }

   /**
    * Constructs a ProducerPool of the gives size and the give waitThreshold. Classes
    * that extend ProducerPool are expected to have constructors that call this 
    * constructor followd by the init method.
    * 
    * This pool will have a default waitThreshold of 300ms.
    * 
    * @param initialSize the normal size of the pool.
    */
   protected ProducerPool(int initialSize ) {
      this(initialSize, 300);
   }

   /**
    * Must be implemented by concrete subclasses. It creates a new producer and must
    * throw a ProducerException if creation is impossible.
    * 
    * @return the newly created producer.
    * @exception ProducerException
    *                   thrown if Producer creation is impossible.
    */
   protected abstract Producer createProducer() throws ProducerException;

   /**
    * Initializes the pool. It adds new producers if the current size is less than
    * the normal size.
    * 
    * This should be called once by the constuctor of the derived class after other
    * initialization parameters are set. Calls are made to the createProducer
    * method that the derived class defines, so make sure any any instance members
    * that this method uses are initialized.
    */
   protected final void init() {
      try {
         // add new producers if required
         logger.debug( "Initializing Producer Pool..." );
         while (size() < initialSize) {
            createIdleProducer();
         }
      } catch ( Exception e ) {
         logger.error("ProducerPool initialization failed.", e);
      }
   }

   /**
    * Synchronous message processing. A message is sent to the host and the method waits 
    * for a response to be returned. If the message cannot be sent , a ProducerException 
    * is thrown. If an exception occurs while waiting for the response, null is returned.
    * 
    * @param doc        the W3C-DOM request document
    * @param properties the properties to attach to the message
    * @param timeToLive the time to wait for a response to return in msecs. 0ms will cause the receiver
    *                   to wait forever
    * @return a W3C-DOM containing the text of the response message, or null if no
    *         response was returned
    * @exception ProducerException
    *                   thrown if an exception occurred while setting up or sending the request message
    * @exception ProducerClosedException
    *                   throws if the producer is in the "closed" state when the method is called.
    */
   public final Document sendReceive( Document doc, Properties properties, long timeToLive ) 
         throws ProducerException, ProducerClosedException
   {
      Producer producer = get();
      try {
         try {
            return producer.sendReceive(doc, properties, timeToLive);
         } catch (TransientProducerException e) {
            logger.info("An exception occured trying to send a transaction using an existing producer. Trying to send again using a new producer...");
            release(producer);
            producer = createWorkingProducer();
            return producer.sendReceive(doc, properties, timeToLive);
         }
      } finally {
         release(producer);
      }
   }
   
   /**
    * Synchronous message processing. A message is sent to the host and the method waits 
    * for a response to be returned. If the message cannot be sent , a ProducerException 
    * is thrown. If an exception occurs while waiting for the response, null is returned.
    * 
    * @param doc        the dom4j request document
    * @param properties the properties to attach to the message
    * @param timeToLive the time to wait for a response to return in msecs. 0ms will cause the receiver
    *                   to wait forever
    * @return a dom4j doc containing the text of the response message, or null if no
    *         response was returned
    * @exception ProducerException
    *                   thrown if an exception occurred while setting up or sending the request message
    * @exception ProducerClosedException
    *                   throws if the producer is in the "closed" state when the method is called.
    */
   public final org.dom4j.Document sendReceive( org.dom4j.Document doc, Properties properties, long timeToLive ) 
      throws ProducerException, ProducerClosedException
   {
      Producer producer = get();
      try {
         try {
            return producer.sendReceive(doc, properties, timeToLive);
         } catch (TransientProducerException e) {
            logger.info("An exception occured trying to send a transaction using an existing producer. Trying to send again using a new producer...");
            release(producer);
            producer = createWorkingProducer();
            return producer.sendReceive(doc, properties, timeToLive);
         }
      } finally {
         release(producer);
      }
   }

   /**
    * Synchronous message processing. A message is sent to the host and the method waits 
    * for a response to be returned. If the message cannot be sent , a ProducerException 
    * is thrown. If an exception occurs while waiting for the response, null is returned.
    * 
    * @param string     the String request document
    * @param properties the properties to attach to the message
    * @param timeToLive the time to wait for a response to return in msecs. 0ms will cause the receiver
    *                   to wait forever
    * @return a string containing the text of the response message, or null if no
    *         response was returned
    * @exception ProducerException
    *                   thrown if an exception occurred while setting up or sending the request message
    * @exception ProducerClosedException
    *                   throws if the producer is in the "closed" state when the method is called.
    */
   public String sendReceive( String string, Properties properties, long timeToLive ) 
         throws ProducerException, ProducerClosedException
   {
      Producer producer = get();
      try {
         try {
            return producer.sendReceive(string, properties, timeToLive);
         } catch (TransientProducerException e) {
            logger.info("An exception occured trying to send a transaction using an existing producer. Trying to send again using a new producer...");
            release(producer);
            producer = createWorkingProducer();
            return producer.sendReceive(string, properties, timeToLive);
         }
      } finally {
         release(producer);
      }
   }

   /**
    * Synchronous message processing. A message is sent to the host and the method waits 
    * for a response to be returned. If the message cannot be sent , a ProducerException 
    * is thrown. If an exception occurs while waiting for the response, null is returned.
    * 
    * @param bytes      the byte array request message
    * @param properties the properties to attach to the message
    * @param timeToLive the time to wait for a response to return in msecs. 0ms will cause the receiver
    *                   to wait forever
    * @return a byte array containing the the response message, or null if no
    *         response was returned
    * @exception ProducerException
    *                   thrown if an exception occurred while setting up or sending the request message
    * @exception ProducerClosedException
    *                   throws if the producer is in the "closed" state when the method is called.
    */
   public byte[] sendReceive( byte[] bytes, Properties properties, long timeToLive ) 
         throws ProducerException, ProducerClosedException
   {
      Producer producer = get();
      try {
         try {
            return producer.sendReceive(bytes, properties, timeToLive);
         } catch (TransientProducerException e) {
            logger.info("An exception occured trying to send a transaction using an existing producer. Trying to send again using a new producer...");
            release(producer);
            producer = createWorkingProducer();
            return producer.sendReceive(bytes, properties, timeToLive);
         }
      } finally {
         release(producer);
      }
   }

   /**
    * Asynchronous message processing. A message is sent to the host and returns immediately. 
    * If an exception occurs before the message is sent or during the send, a 
    * ProducerException occurs.
    * 
    * @param doc        the W3C-DOM message
    * @param properties the properties to attach to the message
    * @return a string containing an JMSMessageID for the sent message
    * @exception ProducerException
    *                   thrown if an exception occurred while setting up or sending the messages
    * @exception ProducerClosedException
    *                   throws if the producer is in the "closed" state when the method is called.
    */
   public final String send( Document doc, Properties properties ) 
         throws ProducerException, ProducerClosedException 
   {
      Producer producer = get();
      try {
         try {
            return producer.send(doc, properties);
         } catch (TransientProducerException e) {
            logger.info("An exception occured trying to send a transaction using an existing producer. Trying to send again using a new producer...");
            release(producer);
            producer = createWorkingProducer();
            return producer.send(doc, properties);
         }
      } finally {
         release(producer);
      }
   }

   /**
    * Asynchronous message processing. A message is sent to the host and returns immediately. 
    * If an exception occurs before the message is sent or during the send, a 
    * ProducerException occurs.
    * 
    * @param doc        the dom4j message
    * @param properties the properties to attach to the message
    * @return a string containing an JMSMessageID for the sent message
    * @exception ProducerException
    *                   thrown if an exception occurred while setting up or sending the messages
    * @exception ProducerClosedException
    *                   throws if the producer is in the "closed" state when the method is called.
    */
   public final String send( org.dom4j.Document doc, Properties properties ) 
         throws ProducerException, ProducerClosedException 
   {
      Producer producer = get();
      try {
         try {
            return producer.send(doc, properties);
         } catch (TransientProducerException e) {
            logger.info("An exception occured trying to send a transaction using an existing producer. Trying to send again using a new producer...");
            release(producer);
            producer = createWorkingProducer();
            return producer.send(doc, properties);
         }
      } finally {
         release(producer);
      }
   }

   /**
    * Asynchronous message processing. A message is sent to the host and returns immediately. 
    * If an exception occurs before the message is sent or during the send, a 
    * ProducerException occurs.
    * 
    * @param str        the string message
    * @param properties the properties to attach to the message
    * @return a string containing an JMSMessageID for the sent message
    * @exception ProducerException
    *                   thrown if an exception occurred while setting up or sending the messages
    * @exception ProducerClosedException
    *                   throws if the producer is in the "closed" state when the method is called.
    */
   public String send( String str, Properties properties ) 
      throws ProducerException, ProducerClosedException
   {
      Producer producer = get();
      try {
         try {
            return producer.send(str, properties);
         } catch (TransientProducerException e) {
            logger.info("An exception occured trying to send a transaction using an existing producer. Trying to send again using a new producer...");
            release(producer);
            producer = createWorkingProducer();
            return producer.send(str, properties);
         }
      } finally {
         release(producer);
      }
   }
   
   /**
    * Asynchronous message processing. A message is sent to the host and returns immediately. 
    * If an exception occurs before the message is sent or during the send, a 
    * ProducerException occurs.
    * 
    * @param bytes      the byte array message
    * @param properties the properties to attach to the message
    * @return a string containing an JMSMessageID for the sent message
    * @exception ProducerException
    *                   thrown if an exception occurred while setting up or sending the messages
    * @exception ProducerClosedException
    *                   throws if the producer is in the "closed" state when the method is called.
    */
   public String send( byte[] bytes, Properties properties ) 
      throws ProducerException, ProducerClosedException
   {
      Producer producer = get();
      try {
         try {
            return producer.send(bytes, properties);
         } catch (TransientProducerException e) {
            logger.info("An exception occured trying to send a transaction using an existing producer. Trying to send again using a new producer...");
            release(producer);
            producer = createWorkingProducer();
            return producer.send(bytes, properties);
         }
      } finally {
         release(producer);
      }
   }
   
   /**
    * Flags this pool as closed and notifies all waiting threads so they can exit. 
    * After the maint thread has exited, all producers are removed. A grace period 
    * of 10 seconds is given for working producers to be release, after which they 
    * are forcefully closed, and then removed.
    */
   public final synchronized void close() {
      closed = true;
      notifyAll(); // notify all waiting threads of close

      // Remove and close all producers.
      while (size() > 0) {
         if (!closeIdleProducer(10000)) {
            // after 10s wait, force working producers closed
            closeAllWorkingProducers();
         }
      }
   }
   
   /**
    * Closed this producer pool.
    */
   public void finalize() {
      close();
   }

   /**
    * Returns true if this pool has been flagged as closed.
    * 
    * @return true if the pool has been closed, otherwise false
    */
   public final boolean isClosed() {
      return closed;
   }

   /**
    * Retruns the current size of the pool. This include both working and idle producers.
    * 
    * @return The number of producers in the pool.
    */
   public final synchronized int size() {
      return idleProducers.size() + workingProducers.size();
   }

   /**
    * Adds a new producer to the idle producer list and returns it.
    * 
    * @return the new Producer.
    * @exception ProducerException
    *                   thrown if the Producer could not be created.
    * @exception ProducerClosedException
    *                   thrown if this producer pool is closed.
    */
   private final Producer createIdleProducer() 
         throws ProducerException, ProducerClosedException 
   {
      if (isClosed()) {
         throw new ProducerClosedException();
      }

      Producer producer = createProducer();

      synchronized(this) {
         if (isClosed() ) {
            producer.close();
            throw new ProducerClosedException();
         }
         idleProducers.addLast(producer);
         notify();
         return producer;
      }
   }

   /**
    * Adds a new producer to the working producer list and returns it.
    * 
    * @return the new Producer.
    * @exception ProducerException
    *                   thrown if the Producer could not be created.
    * @exception ProducerClosedException
    *                   thrown if this producer pool is closed.
    */
   private final Producer createWorkingProducer() 
         throws ProducerException, ProducerClosedException 
   {
      if (isClosed()) {
         throw new ProducerClosedException();
      }
      
      Producer producer = createProducer();
      synchronized(this) {
         if (isClosed() || !workingProducers.add(producer) ) {
            producer.close();
            return null;
         }
         return producer;
      }
   }

   /**
    * Removes the first idle producer from the pool and closes it.
    * 
    * If there are no idle producers the given timeout is waited. If the timout expires
    * false is returned and no producer is closed or removed from the pool.
    * 
    * @param timeout the time to wait for an idle producer.
    * @return true if a producer was removed from the pool and closed; false if a timed out occurred.
    */
   private final boolean closeIdleProducer(long timeout) {
      Producer producer = null;
      synchronized(this) {
         if ( size()==0 || !waitForIdleProducer(timeout) ) {
            return false;
         }
         producer = (Producer)idleProducers.removeFirst();
      }
      try {
         producer.close();
      } catch (Exception e) {
         // producer should handle close exceptions, but just in case catch it.
         e.printStackTrace();
      }
      
      return true;
   }

   /**
    * Iterates through the workingProducers set removing and closing each of them.
    */
   private final synchronized void closeAllWorkingProducers() {
      Iterator iter = workingProducers.iterator();
      while ( iter.hasNext() ) {
         Producer producer = (Producer)iter.next();
         iter.remove();
         try {
            producer.close();
         } catch (Exception e) {
            // producer should handle close exceptions, but just in case handle it.
            e.printStackTrace();
         }
      }
   }

   /**
    * Waits the given timout for an idle producer. This method is synchronized,
    * but callers should also synchronize blocks of code that depend on this state for
    * modifying the idle list.
    * 
    * @param timeout the amount of time to wait for an idle producer
    * @return true if there is an idle producer before the timeout, otherwise false
    */
   private final  synchronized boolean waitForIdleProducer( long timeout ) {
      if ( idleProducers.size()==0 ) {
         logger.debug("No idle producers. Waiting for notification.");
         try {
            wait(timeout);
         } catch ( InterruptedException ex ) {
            logger.error("Interrupted waiting for an idle producer.", ex);
         }
      }
      logger.debug("Returning from waitForIdleProducer(" + timeout+ ") with " + idleProducers.size() + " idle producers.");
      return ( idleProducers.size()>0 );
   }

   /**
    * Returns a the next producer from the the idle producer queue. If no producer
    * is available before the waitThreshold is reached, a new producer is created and
    * returned.
    * 
    * The caller must release the producer back to the pool when done by calling the
    * release method.
    * 
    * @return a producer from the pool.
    * @exception ProducerException
    *                   if an exception occurs
    * @exception ProducerClosedException
    *                   thrown if this producer pool is closed.
    */
   private final Producer get() 
         throws ProducerException, ProducerClosedException 
   {
      Producer producer = get(waitThreshold);
      if ( producer == null ) {
         // timed-out. Just create a new one.
         logger.debug( "Timeout getting producer from pool.");
         producer = createWorkingProducer();
      }
      return producer;
   }

   /**
    * Returns a the next producer from the the idle producer queue. If there are no
    * idle producers, the given timeout period is waited. If the wait times out
    * null is returned.
    * 
    * The caller must release the producer back to the pool when done by calling the
    * release method.
    * 
    * @param timeout the amount of time to wait.
    * @return a producer or null if the wait times out
    * @exception ProducerException
    *                   if an exception occurs
    * @exception ProducerClosedException
    *                   thrown if this producer pool is closed.
    */
   private final synchronized Producer get(long timeout) 
         throws ProducerException, ProducerClosedException 
   {
      if ( isClosed() ) {
         throw new ProducerClosedException();
      }
      
      boolean hasIdleProducers =  waitForIdleProducer(timeout); 
      
      //may have closed while waiting
      if ( isClosed() ) {
         throw new ProducerClosedException();
      }

      if (!hasIdleProducers) {
         logger.debug("Timeout (" + timeout + ") waiting for idle producers.");
         return null;
      }
      
      try {
         
         Producer producer = (Producer)idleProducers.removeFirst();
         if (!workingProducers.add(producer)) {
            throw new java.lang.IllegalStateException("Retrieved producer already in use.");
         }
         logger.debug("Retrieved producer from queue of idle producers.");
         return producer;
      } catch (Exception e) {
         logger.error("Failed to get producer from pool. ", e);
         throw new ProducerException("Failed to get producer from pool.", e);
      }
   }

   /**
    * Release the given producer back to the pool, and notify waiting threads. 
    * If the producer is closed it is discarded. 
    * 
    * @param producer the producer to be released.
    */
   private final synchronized void release(Producer producer) {
      
      if ( producer != null && workingProducers.remove(producer) && !producer.isClosed() ) {
         logger.debug("Releasing producer " + producer + " to idle producer queue.");
         idleProducers.addLast(producer);
         notify();
      } else {
         logger.debug("Releasing producer " + producer + " and discarding.");
      }
      
   }

   /**
    * Private data members
    */

   private final Logger logger;
   private final int initialSize;
   private final long waitThreshold;

   private final LinkedList idleProducers = new LinkedList();
   private final HashSet    workingProducers = new HashSet();

   private boolean closed = false;
}

/**
 * -------------------------------------------------------------------------
 * 
 * CHANGE LOG:
 * 
 * $Log:   Y:/VCS/RTS Interfaces/Java Interfaces/ifast/ztsapi/ProducerPool.java-arc  $
 * 
 *    Rev 1.0   Oct 05 2009 13:11:50   yingz
 * Initial revision.
 * 
 *    Rev 1.1   Jul 16 2009 06:59:26   serverbu
 * Changed package to com.ifds.iFast.api
 * 
 *    Rev 1.0   Jul 15 2009 15:41:38   purdyech
 * Initial revision.
 * 
 *    Rev 1.12   Mar 31 2009 16:26:32   smithdav
 * Removed commented code.
 * 
 *    Rev 1.11   Oct 10 2008 13:39:02   smithdav
 * Add use limit for producers and handle config not found errors better.
 * 
 *    Rev 1.10   Jun 26 2008 11:42:42   smithdav
 * Rename normalSize variables to initialSize.
 * 
 *    Rev 1.9   Jun 04 2008 17:18:22   smithdav
 * Add SonicProducerTarget and support for sending byte[] as BytesMessages.
 * 
 *    Rev 1.8   May 22 2008 17:19:52   smithdav
 * Add dom4j support to Producer
 * 
 *    Rev 1.7   May 07 2008 14:18:46   smithdav
 * Close producer during retry so that they get removed from pool.
 * 
 *    Rev 1.6   Apr 29 2008 15:33:00   smithdav
 * Reduce logging level on some messages to DEBUG.
 * 
 *    Rev 1.5   Apr 17 2008 11:54:12   smithdav
 * Add support for String (non-xml) send and sendReceive methods. Also add support for JMSReplyTo.
 * 
 *    Rev 1.4   Aug 13 2007 21:46:22   smithdav
 * Update to use JAXP and log4j.
 * 
 *    Rev 1.3   May 25 2007 10:23:22   smithdav
 * Added MsgError response handling and improved error handling.
 * 
 *    Rev 1.2   May 14 2007 15:24:56   smithdav
 * Minor javadoc fix..
 * 
 *    Rev 1.1   May 02 2007 18:36:08   smithdav
 * Added overloads of send and sendReceive to take a DOM Documents and a Properies object.  Deprecate the others.
 * Also added DOM parsing and serializing code.
 * 
 *    Rev 1.0   Apr 24 2007 12:55:14   smithdav
 * Initial revision.
 * 
 */
