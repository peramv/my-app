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

/**
 * @author smithdav
 *
 */
public class SonicProducerTarget {
   private final String brokerURLs;
   private final String sendQueueName;
   private final String receiveQueueName;
   
   public SonicProducerTarget(String brokerURLs, String sendQueueName) {
      this(brokerURLs, sendQueueName, null); 
   }
   
   public SonicProducerTarget(String brokerURLs, String sendQueueName, String receiveQueueName) {
      this.brokerURLs=brokerURLs;
      this.sendQueueName=sendQueueName;
      this.receiveQueueName=receiveQueueName;
   }
   
   public String getBrokerURLs() {
      return brokerURLs;
   }
   
   public String getSendQueueName() {
      return sendQueueName;
   }
   
   public String getReceiveQueueName() {
      return receiveQueueName;
   }
   
   public boolean hasReceiveQueue() {
      return receiveQueueName!=null;
   }
   
   public String toString() {
      if (receiveQueueName==null) {
         return brokerURLs + "@" + sendQueueName;
      } else {
         return brokerURLs + "@" + sendQueueName + "/" + receiveQueueName;
      }
   }
   
   public boolean equals(Object other) {
      if ((other instanceof SonicProducerTarget)) {
         SonicProducerTarget otherTarget=(SonicProducerTarget)other;
         if (this.brokerURLs.equals(otherTarget.brokerURLs) && this.sendQueueName.equals(otherTarget.sendQueueName)) {
            if (this.receiveQueueName!=null) {
               return this.receiveQueueName.equals(otherTarget.receiveQueueName);
            } else {
               return otherTarget.receiveQueueName==null;
            }
         }
      }
      return false;
   }
   
   public int hashCode() {
      return this.brokerURLs.hashCode() +
             this.sendQueueName.hashCode() +
             ( this.receiveQueueName==null ? 0
                                           : this.receiveQueueName.hashCode() );
   }

}

/**
 * -------------------------------------------------------------------------
 * 
 * CHANGE LOG:
 * 
 * $Log:   Y:/VCS/RTS Interfaces/Java Interfaces/ifast/ztsapi/SonicProducerTarget.java-arc  $
 * 
 *    Rev 1.0   Oct 05 2009 13:05:30   yingz
 * Initial revision.
 * 
 *    Rev 1.1   Jul 16 2009 07:00:06   serverbu
 * Changed package to com.ifds.iFast.api
 * 
 *    Rev 1.0   Jul 15 2009 15:51:54   purdyech
 * Initial revision.
 * 
 *    Rev 1.1   Jul 07 2008 15:24:26   smithdav
 * Small bug fix.
 * 
 *    Rev 1.0   Jun 04 2008 17:23:26   smithdav
 * Initial revision.
 * 
 */
