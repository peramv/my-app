package com.ifds.rts;

import java.io.UnsupportedEncodingException;
import java.text.ParseException;

/**
 * <p>An object of this type is used to decode an RTS
 * response. The object is constructed by RTSReader.readResponse().
 * The header fields may be queried using the specific get methods.
 * These are decoded an construction.<p>
 * The data fields must be decoded in order using base classes
 * getField and decode methods. The following code sample gives
 * a typical usage.</p>
 * <code>
 * RTSReader reader( socket.getInputStream() );<br>
 * RTSResponseDecodeBuffer responseBuffer = reader.readResponse();<br>
 * if ( responseBuffer.getResponseID().equals("00055") &&<br>
 * &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;responseBuffer.getResponseTypeID().equals("00002"));<br>
 * {<br>
 * &nbsp;&nbsp;String clientID = responseBuffer.decodeString( responseBuffer.getField() );<br>
 * &nbsp;&nbsp;String clientName = responseBuffer.decodeString( responseBuffer.getField() );<br>
 * &nbsp;&nbsp;Boolean isPreferred = responseBuffer.decodeBoolean( responseBuffer.getField() );<br>
 * }<br>
 * </code>
 */
public final class RTSResponseDecodeBuffer extends RTSDecodeBuffer
{
   private String _msgType = null;
   private String _transactionID = null;
   private String _responseID = null;
   private String _responseTypeID = null;
   private int _pHandleID = 0;
   private long _pThreadID = 0;
   private String _instanceID = null;

   public RTSResponseDecodeBuffer( byte[] bytes, String encoding ) throws ParseException, UnsupportedEncodingException
   {
      super( bytes, encoding );
      decodeHeader();
   }

   private final void decodeHeader() throws ParseException, UnsupportedEncodingException
   {
      _msgType        = decodeHeaderField(  1 );
      _transactionID  = decodeHeaderField(  5 );
      _responseID     = decodeHeaderField(  5 );
      _responseTypeID = decodeHeaderField(  5 );
      String pHandleID      = decodeHeaderField(  5 );
      String pThreadID      = decodeHeaderField( 10 );
      _instanceID     = decodeHeaderField(  5 );
      
      // skip one extra char
      decodeHeaderField( 1 );

      try
      {
          _pHandleID = Integer.parseInt(pHandleID);
      }
      catch ( NumberFormatException nfe )
      {
          throw new ParseException("Unable to parse int value for PHandleID: " + nfe.getMessage(), 5);
      }

      try
      {
          _pThreadID = Long.parseLong(pThreadID);
      }
      catch ( NumberFormatException nfe )
      {
          throw new ParseException("Unable to parse long value for PThreadID: " + nfe.getMessage(), 10);
      }


   }

   public final String getMsgType()
   {
      return _msgType;
   }

   public final String getTransactionID()
   {
      return _transactionID;
   }
   
   public final String getResponseID()
   {
      return _responseID;
   }

   public final String getResponseTypeID()
   {
      return _responseTypeID;
   }

   public final int getPHandleID()
   {
      return _pHandleID;
   }

   public final long getPThreadID() 
   {
      return _pThreadID;
   }
   
   public final String getInstanceID()
   {
      return _instanceID;
   }


}