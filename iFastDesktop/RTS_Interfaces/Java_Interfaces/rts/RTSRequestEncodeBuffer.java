package com.ifds.rts;

import java.text.DecimalFormat;

/**
 * <p>An object of this type is used to encode an RTS 
 * request. The object is constructed specifying header
 * data, and then fields are added using the base classes
 * appendField methods. The object is then typically written
 * to a output stream using an instance of RTSWriter. The 
 * following code sample gives a typical usage.</p>
 * <code>
 * RTSWriter writer( socket.getOutputStream() );<br>
 * RTSRequestEncodeBuffer requestBuffer = new RTSRequestEncodeBuffer(77);<br>
 * requestBuffer.appendField( fundID );<br>
 * requestBuffer.appendField( fundClass );<br>
 * requestBuffer.appendField( Boolean.TRUE );<br>
 * writer.write(requestBuffer);
 * </code>
 */
public final class RTSRequestEncodeBuffer extends RTSEncodeBuffer
{
   private static final DecimalFormat idFormat1  = new DecimalFormat("0");
   private static final DecimalFormat idFormat2  = new DecimalFormat("00");
   private static final DecimalFormat idFormat5  = new DecimalFormat("00000");
   private static final DecimalFormat idFormat10 = new DecimalFormat("0000000000");

   public static final byte NO_PERSIST_CHANGE = 0;
   public static final byte START_PERSIST     = 3;
   public static final byte END_PERSIST       = 1;
   
   /**
    *
    */
   public RTSRequestEncodeBuffer( String encoding, 
                                  int transactionID ) throws java.io.UnsupportedEncodingException
   {
      super( encoding );
      formatHeader( 1, 0, 0, transactionID, 0, 0, NO_PERSIST_CHANGE, 0 );
   }
   
   /**
    *
    */
   public RTSRequestEncodeBuffer( String encoding, 
                                  int    transactionID,
                                  int    pHandleID,
                                  long   pThreadID,
                                  byte   flags ) throws java.io.UnsupportedEncodingException
   {
      super( encoding );
      formatHeader( 1, 0, 0, transactionID, pHandleID, pThreadID, flags, 0 );
   }
   
   /**
    *
    */
   public RTSRequestEncodeBuffer( String encoding, 
                                  int    providerID,
                                  int    clientID,
                                  int    databaseID,
                                  int    transactionID,
                                  int    pHandleID,
                                  long   pThreadID,
                                  byte   flags,
                                  int    instanceID ) throws java.io.UnsupportedEncodingException
   {
      super( encoding );
      formatHeader( providerID, clientID, databaseID, transactionID, pHandleID, pThreadID, flags, instanceID );
   }

   /**
    *
    */
   private final void formatHeader( int    providerID,
                                    int    clientID,
                                    int    databaseID,
                                    int    transactionID,
                                    int    pHandleID,
                                    long   pThreadID,
                                    byte   flags,
                                    int    instanceID ) throws java.io.UnsupportedEncodingException 
   {
      appendHeaderField( idFormat2.format( providerID ) );  
      appendHeaderField( idFormat2.format( clientID ) );  
      appendHeaderField( idFormat2.format( databaseID ) );  
      appendHeaderField( idFormat5.format( transactionID ) );
      appendHeaderField( "                " );  
      appendHeaderField( idFormat5.format( pHandleID ) );
      appendHeaderField( idFormat10.format( pThreadID ) );
      appendHeaderField( idFormat1.format( flags ) );
      appendHeaderField( idFormat5.format( instanceID ) );
   }


}
