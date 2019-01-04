/**
 *  -------------------------------------------------------------------------
 *                                 Copyright
 *
 *               International Financial Data Services Limited 2006
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

/**
 * 
 * @author David Smith
 */
public final class SonicProducerPool extends ProducerPool {

   /**
    * Creates a new fully initialized instance of SonicProducerPool.
    * 
    * @param initialSize the normal size of the pool.
    * @param target    the SonicMQ target
    * @param user      the SonicMQ connection user
    * @param password  the SonicMQ connection password
    */
   public SonicProducerPool(int initialSize, SonicProducerTarget target, String user, String password) {
      this(initialSize, target, user, password, SonicProducer.DEFAULT_USE_LIMIT, SonicProducer.DEFAULT_BYTES_ENCODING);
   }

   /**
    * Creates a new fully initialized instance of SonicProducerPool.
    * 
    * @param initialSize the normal size of the pool.
    * @param target    the SonicMQ target
    * @param user      the SonicMQ connection user
    * @param password  the SonicMQ connection password
    * @param bytesEncoding encoding used for bytes messages.
    */
   public SonicProducerPool(int initialSize, SonicProducerTarget target, String user, String password, String bytesEncoding) {
      this(initialSize, target, user, password, SonicProducer.DEFAULT_USE_LIMIT, bytesEncoding);
   }

   /**
    * Creates a new fully initialized instance of SonicProducerPool.
    * 
    * @param initialSize the normal size of the pool.
    * @param target    the SonicMQ target
    * @param user      the SonicMQ connection user
    * @param password  the SonicMQ connection password
    * @param useLimit  the max number of times the producer will be used
    */
   public SonicProducerPool(int initialSize, SonicProducerTarget target, String user, String password, long useLimit) {
      this(initialSize, target, user, password, useLimit, SonicProducer.DEFAULT_BYTES_ENCODING);
   }

   /**
    * Creates a new fully initialized instance of SonicProducerPool.
    * 
    * @param initialSize the normal size of the pool.
    * @param target    the SonicMQ target
    * @param user      the SonicMQ connection user
    * @param password  the SonicMQ connection password
    * @param useLimit  the max number of times the producer will be used
    * @param bytesEncoding encoding used for bytes messages.
    */
   public SonicProducerPool(int initialSize, SonicProducerTarget target, String user, String password, long useLimit, String bytesEncoding) {
      super(initialSize);
      this.target = target;
      this.user = user;
      this.password = password;
      this.useLimit = useLimit;
      this.bytesEncoding = bytesEncoding; 
      init();
   }

   /**
    * Returns a newly create SonicProducer.
    * 
    * @return the new SonicProducer
    * @exception ProducerException
    *                   thrown if the producer cannot be created
    * @see com.ifds.iFast.api.ProducerPool#createProducer()
    */
   protected Producer createProducer() throws ProducerException {
      SonicProducer producer = new SonicProducer(target, user, password, useLimit, bytesEncoding);
      return producer;
   }

   private final SonicProducerTarget target;   
   private final String user;
   private final String password;
   private final long useLimit;
   private final String bytesEncoding;
}

/**
 * -------------------------------------------------------------------------
 * 
 * CHANGE LOG:
 * 
 * $Log:   Y:/VCS/RTS Interfaces/Java Interfaces/ifast/ztsapi/SonicProducerPool.java-arc  $
 * 
 *    Rev 1.0   Oct 05 2009 13:05:28   yingz
 * Initial revision.
 * 
 *    Rev 1.2   Jul 16 2009 07:22:28   purdyech
 * Changed references to com.ifdsgroup.* to com.ifds.iFast.api
 * 
 *    Rev 1.1   Jul 16 2009 06:59:50   serverbu
 * Changed package to com.ifds.iFast.api
 * 
 *    Rev 1.0   Jul 15 2009 15:53:08   purdyech
 * Initial revision.
 * 
 *    Rev 1.7   Oct 10 2008 13:39:02   smithdav
 * Add use limit for producers and handle config not found errors better.
 * 
 *    Rev 1.6   Jun 26 2008 11:42:42   smithdav
 * Rename normalSize variables to initialSize.
 * 
 *    Rev 1.5   Jun 04 2008 17:18:22   smithdav
 * Add SonicProducerTarget and support for sending byte[] as BytesMessages.
 * 
 *    Rev 1.4   May 26 2008 15:48:12   smithdav
 * Fix. make class public.
 * 
 *    Rev 1.3   May 22 2008 17:38:42   smithdav
 * javadoc fixes
 * 
 *    Rev 1.2   May 22 2008 17:19:52   smithdav
 * Add dom4j support to Producer
 * 
 *    Rev 1.1   May 14 2007 15:30:46   smithdav
 * Minor javadoc fix...
 * 
 *    Rev 1.0   Apr 24 2007 12:55:14   smithdav
 * Initial revision.
 * 
 */
