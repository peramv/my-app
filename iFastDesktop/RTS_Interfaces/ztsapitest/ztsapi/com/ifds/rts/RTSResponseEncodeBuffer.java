package com.ifds.rts;

import java.text.DecimalFormat;

/**
 * <p>An object of this type is used to encode an RTS 
 * response. The object is constructed specifying header
 * data, and then fields are added using the base classes
 * appendField methods. The object is then typically written
 * to a output stream using an instance of RTSWriter. The 
 * following code sample gives a typical usage.</p>
 * <code>
 * RTSWriter writer( socket.getOutputStream() );<br>
 * RTSResponseEncodeBuffer responseBuffer = new RTSResponseEncodeBuffer(55,55,2);<br>
 * responseBuffer.appendField( clientID );<br>
 * responseBuffer.appendField( clientName );<br>
 * responseBuffer.appendField( isPreferred );<br>
 * writer.write(responseBuffer);
 * </code>
 */
public final class RTSResponseEncodeBuffer extends RTSEncodeBuffer
{
   private static final DecimalFormat idFormat2  = new DecimalFormat("00");
   private static final DecimalFormat idFormat5  = new DecimalFormat("00000");
   private static final DecimalFormat idFormat10 = new DecimalFormat("0000000000");

   public final String BUSINESS_RESPONSE = "B";
   public final String SYSTEM_RESPOSNE   = "S";
   
   /**
    *
    */
   public RTSResponseEncodeBuffer( String encoding,
                                   int transactionID, 
                                   int responseID, 
                                   int responseTypeID ) throws java.io.UnsupportedEncodingException
   {
      super( encoding );
      formatHeader( BUSINESS_RESPONSE, transactionID, responseID, responseTypeID, 0, 0, 0 );
   }
   
   /**
    *
    */
   public RTSResponseEncodeBuffer( String encoding,
                                   int transactionID, 
                                   int responseID, 
                                   int responseTypeID, 
                                   int pHandleID, 
                                   long pThreadID ) throws java.io.UnsupportedEncodingException
   {
      super( encoding );
      formatHeader( BUSINESS_RESPONSE, transactionID, responseID, responseTypeID, pHandleID, pThreadID, 0 );
   }
   
   /**
    *
    */
   public RTSResponseEncodeBuffer( String encoding,
                                   String msgType, 
                                   int    transactionID,
                                   int    responseID,
                                   int    responseTypeID,
                                   int    pHandleID,
                                   long   pThreadID,
                                   int    instanceID ) throws java.io.UnsupportedEncodingException
   {
      super( encoding );
      formatHeader( msgType, transactionID, responseID, responseTypeID, pHandleID, pThreadID, instanceID );
   }

   /**
    *
    */
   private final void formatHeader( String msgType,
                                    int    transactionID,
                                    int    responseID,
                                    int    responseTypeID,
                                    int    pHandleID,
                                    long   pThreadID,
                                    int    instanceID ) throws java.io.UnsupportedEncodingException
   {
      appendHeaderField( msgType );  
      appendHeaderField( idFormat5.format( transactionID ) );
      appendHeaderField( idFormat5.format( responseID ) );
      appendHeaderField( idFormat5.format( responseTypeID ) );
      appendHeaderField( idFormat5.format( pHandleID ) );
      appendHeaderField( idFormat10.format( pThreadID ) );
      appendHeaderField( idFormat5.format( instanceID ) );
   }

}
