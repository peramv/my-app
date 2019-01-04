/*
 * Created on Jul 28, 2008
 *
 * TODO To change the template for this generated file go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
package com.ifds.iFast.api;

/**
 */
public class NoResponseException extends ProducerException {

   /**
    * @param msg
    */
   public NoResponseException(String msg) {
      super(msg);
   }

   /**
    * @param msg
    */
   public NoResponseException(String msg, Throwable cause) {
      super(msg, cause);
   }

   private static final long serialVersionUID = 1L;   
}
