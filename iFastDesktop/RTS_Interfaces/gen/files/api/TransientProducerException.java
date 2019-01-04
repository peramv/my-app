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
 * This exception is throw by Producers when transient exceptions occur.
 * A ProducerPool will retry once with an new Producer if this is encountered.
 * 
 * @author David Smith
 */
public class TransientProducerException extends ProducerException {

   public TransientProducerException(String msg) {
      super(msg);
   }

   public TransientProducerException(String msg, Throwable cause) {
      super(msg, cause);
   }

   public TransientProducerException(Throwable cause) {
      super(cause);
   }

	private static final long serialVersionUID = 1L;   
}
