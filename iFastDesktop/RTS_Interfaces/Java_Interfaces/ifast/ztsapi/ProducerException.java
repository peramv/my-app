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
 * This exception is throw by Producers when unrecoverable exceptions occur.
 * 
 * @author David Smith
 */
public class ProducerException extends Exception{
	
   /**
    * Create an instance with the given message.
    * 
    * @param msg    the exception message.
    */
	public ProducerException(String msg) { 
		super(msg);
	}

   /**
    * Create an instance with the given MsgError.
    * 
    * @param error    the MsgError.
    */
   public ProducerException(MsgError error) { 
      super(error.getOrigin() + ": " + error.getMessage() );
   }

   /**
    * Create an instance with the given message, and the given cause exception.
    * 
    * @param msg    the exception message.
    * @param cause  the exception that caused this exception to be thrown.
    */
	public ProducerException(String msg, Throwable cause) { 
		super(msg, cause);
	}

   /**
    * Create an instance with the given cause exception.
    * 
    * @param cause  the exception that caused this exception to be thrown.
    */
	public ProducerException(Throwable cause) { 
		super(cause);
	}
  
	private static final long serialVersionUID = 1L;   
}

/**
 *  -------------------------------------------------------------------------
 *
 * CHANGE LOG:
 *
 *   $Log:   Y:/VCS/RTS Interfaces/Java Interfaces/ifast/ztsapi/ProducerException.java-arc  $
 * 
 *    Rev 1.0   Oct 05 2009 13:11:40   yingz
 * Initial revision.
 * 
 *    Rev 1.1   Jul 16 2009 06:59:14   serverbu
 * Changed package to com.ifds.iFast.api
 * 
 *    Rev 1.0   Jul 15 2009 15:40:14   purdyech
 * Initial revision.
 * 
 *    Rev 1.5   Nov 28 2008 15:08:52   smithdav
 * Use new style errors.
 * 
 *    Rev 1.4   Aug 19 2008 16:15:48   smithdav
 * Java 5 cleanup.
 * 
 *    Rev 1.3   May 22 2008 17:19:52   smithdav
 * Add dom4j support to Producer
 * 
 *    Rev 1.2   May 30 2007 11:10:28   smithdav
 * Fix javadoc problem.
 * 
 *    Rev 1.1   May 25 2007 10:23:22   smithdav
 * Added MsgError response handling and improved error handling.
 * 
 *    Rev 1.0   Apr 24 2007 12:55:14   smithdav
 * Initial revision.
 * 
 *    Rev 1.0   Nov 14 2006 14:04:38   SMITHDAV
 * Initial revision.
 *
 */
