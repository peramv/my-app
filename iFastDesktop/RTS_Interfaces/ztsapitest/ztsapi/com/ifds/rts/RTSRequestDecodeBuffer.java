package com.ifds.rts;

import java.io.UnsupportedEncodingException;
import java.text.ParseException;

/**
 * <p>An object of this type is used to decode an RTS
 * request. The object is constructed by RTSReader.readRequest().
 * The header fields may be queried using the specific get methods.
 * These are decoded an construction.<p>
 * The data fields must be decoded in order using base classes
 * getField and decode methods. The following code sample gives
 * a typical usage.</p>
 * <code>
 * RTSReader reader( socket.getInputStream() );<br>
 * RTSRequestDecodeBuffer requestBuffer = reader.readRequest();<br>
 * if ( requestBuffer.getTransactionID().equals("00077") );<br>
 * {<br>
 * &nbsp;&nbsp;String fundID = responseBuffer.decodeString( responseBuffer.getField() );<br>
 * &nbsp;&nbsp;String fundClass = responseBuffer.decodeString( responseBuffer.getField() );<br>
 * &nbsp;&nbsp;Boolean active = responseBuffer.decodeBoolean( responseBuffer.getField() );<br>
 * }<br>
 * </code>
 */
public final class RTSRequestDecodeBuffer extends RTSDecodeBuffer
{
   private String _providerID    = null;
   private String _clientID      = null;
   private String _databaseID    = null;
   private String _transactionID = null;
   private String _userID        = null;
   private String _password      = null;
   private String _pHandleID     = null;
   private String _pThreadID     = null;
   private String _flags         = null;
   private String _instanceID    = null;

   public RTSRequestDecodeBuffer( byte[] bytes, String encoding ) throws ParseException, UnsupportedEncodingException
   {
      super( bytes, encoding );
      decodeHeader();
   }

   private final void decodeHeader() throws ParseException, UnsupportedEncodingException
   {
      _providerID    = decodeHeaderField(  2 );
      _clientID      = decodeHeaderField(  2 );
      _databaseID    = decodeHeaderField(  2 );
      _transactionID = decodeHeaderField(  5 );
      _userID        = decodeHeaderField(  8 );
      _password      = decodeHeaderField(  8 );
      _pHandleID     = decodeHeaderField(  5 );
      _pThreadID     = decodeHeaderField( 10 );
      _flags         = decodeHeaderField(  1 );
      _instanceID    = decodeHeaderField(  5 );
   }

   public final String getProviderID()
   {
      return _providerID;
   }

   public final String getClientID()
   {
      return _clientID;
   }

   public final String getDatabaseID()
   {
      return _databaseID;
   }

   public final String getTransactionID()
   {
      return _transactionID;
   }
   
   public final String getUserID()
   {
      return _userID;
   }
   
   public final String getPassword()
   {
      return _password;
   }
   
   public final String getPHandleID()
   {
      return _pHandleID;
   }

   public final String getPThreadID() 
   {
      return _pThreadID;
   }
   
   public final String getFlags()
   {
      return _flags;
   }

   public final String getInstanceID()
   {
      return _instanceID;
   }

}