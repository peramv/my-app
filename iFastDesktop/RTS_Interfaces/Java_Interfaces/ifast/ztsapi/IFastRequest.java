package com.ifds.iFast.api;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.net.Socket;
import java.text.ParseException;

import com.ifds.rts.RTSReader;
import com.ifds.rts.RTSRequestEncodeBuffer;
import com.ifds.rts.RTSResponseDecodeBuffer;
import com.ifds.rts.RTSWriter;
import com.ifds.iFast.api.ProducerClosedException;
import com.ifds.iFast.api.ProducerException;

/**
 * Abstract base class for all iFast request objects.
 * The class provides a framework encoding and host
 * request and submitting them.
 */
public abstract class IFastRequest implements Serializable
{
    /**
    * 
    */
   private static final long serialVersionUID = 1L;

   private final int _transactionId;

    private boolean unsent = true;

    private String _nextKey = "";
    private int _overrideRepeats = 0;
    private Boolean _track = Boolean.TRUE;
    private String _activity = null;

    private final String _hostEncoding;

    /*
     *  The following fields are for the persistent transaction
     */
    private byte _persistFlag = -1;
    private int _pHandleID = 0;
    private long _pThreadID = 0;


    /**
     *
     */
    IFastRequest( int transactionId )
    {
        _transactionId = transactionId;
        _hostEncoding = null;
    }

    /**
     *
     */
    IFastRequest( int transactionId, String hostEncoding  )
    {
        _transactionId = transactionId;
        _hostEncoding = hostEncoding;
    }

    /**
     * This method sets the string key that will be sent to the
     * host on the next call to receive() or receiveAll() to tell
     * the host where the last receive call left off.<br><br>
     *
     * The nextKey property will be updated appropriately after each 
     * receive call. This method is typically only used to support 
     * "stateless" implementations. That is, implementation for which 
     * the view object cannot be maintained between receive calls.<br><br>
     *
     * @param nextKey The key to be used in the next receive call.
     */
    public final void setNextKey( String nextKey )
    {
        assertUnsent();
        setNextKeyInternal( nextKey );
    }

    /**
     *
     */
    final void setNextKeyInternal( String nextKey )
    {
        if ( nextKey == null )
            _nextKey = "";
        else
            _nextKey = nextKey;
    }

    /**
     * This method returns the string key that will be sent to the
     * host on the next call to receive() or receiveAll() to tell
     * the host where the last receive call left off.<br><br>
     *
     * The nextKey property will be updated appropriately after each 
     * receive call. This method is typically only used to support 
     * "stateless" implementations. That is, implementation for which 
     * the view object cannot be maintained between receive calls.<br><br>
     *
     * @return The key of the next record to be retrieved.
     */
    public final String getNextKey()
    {
        return _nextKey;
    }

    /**
     * This method is intended for internal IFDS use only.<br><br>
     */
    public final void disableTracking()
    {
        _track = Boolean.FALSE;
        _activity = null;
    }

    /**
     * This method is intended for internal IFDS use only.<br><br>
     */
    public final void enableTracking( String activity )
    {
        _track = Boolean.TRUE;
        _activity = activity;
    }

    /**
     *
     */
    final void setOverrideRepeats( int overrideRepeats )
    {
        if ( overrideRepeats < 0 )
            throw new IllegalArgumentException( "Repeat override must be positive." );

        _overrideRepeats = overrideRepeats;
    }

    /**
     *
     */
    final int getOverrideRepeats()
    {
        return _overrideRepeats;
    }

    /**
     *
     */
    final RTSResponseDecodeBuffer send( String ipAddress, int portNumber ) throws IOException, ParseException
    {
        Socket socket = new Socket( ipAddress, portNumber );
        socket.setSoTimeout( 300000 ); //5 mins timeout

        RTSResponseDecodeBuffer response = send( socket );
        socket.close();

        return response;
    }

    /**
     *
     */
    final RTSResponseDecodeBuffer send( Socket socket ) throws IOException, ParseException
    {
        unsent = false;

        String encoding = (_hostEncoding==null)?"ISO8859-1":_hostEncoding;

        RTSRequestEncodeBuffer requestBuffer = null;

        //set the persistent information into the transaction header
        if (_persistFlag != -1)
        {
            requestBuffer = new RTSRequestEncodeBuffer( encoding, _transactionId, _pHandleID, _pThreadID, _persistFlag );
        }
        else
        {
            requestBuffer = new RTSRequestEncodeBuffer( encoding, _transactionId );
        }
        encodeFields( requestBuffer );

        RTSWriter writer = new RTSWriter( socket.getOutputStream() );
        RTSReader reader = new RTSReader( socket.getInputStream() );

        writer.write( requestBuffer );
        return reader.readResponse(encoding);

    }

    /**
     * Throws a IllegalStateException if the request has been sent
     * at least once. This is called by all set methods to prevent
     * users from modifying the request after the first send.<br><br>
     */
    protected final void assertUnsent()
    {
        if ( !unsent )
            throw new IllegalStateException( "Request has already been sent" );
    }

    /**
     * Abstract method that all request objects must
     * implement. Implementers will encode each field
     * in order, into the given host request object.<br><br>
     * 
     * @param requestBuffer
     *               Host encoded request object.
     */
    protected abstract void encodeFields( RTSRequestEncodeBuffer requestBuffer ) throws UnsupportedEncodingException;

    /**
     * Implementations of encodeFields() will call this
     * method to add the NextKey field to the host request.<br><br>
     * 
     * @param requestBuffer
     *               Host encoded request object.
     */
    protected final void encodeNextKeyField( RTSRequestEncodeBuffer requestBuffer ) throws UnsupportedEncodingException
    {
        requestBuffer.appendField( _nextKey );
    }

    /**
     * Implementations of encodeFields() will call this
     * method to add the OverrideRepeats field to the host request.<br><br>
     * 
     * @param requestBuffer
     *               Host encoded request object.
     */
    protected final void encodeOverrideRepeatsField( RTSRequestEncodeBuffer requestBuffer ) throws UnsupportedEncodingException
    {
        requestBuffer.appendField( new Integer(_overrideRepeats) );
    }

    /**
     * Implementations of encodeFields() will call this to
     * method to translate and add the LanguageCode field to 
     * the host request.<br><br>
     * 
     * @param requestBuffer
     *               Host encoded request object.
     */
    protected final void encodeLanguageCodeField( String languageCode, RTSRequestEncodeBuffer requestBuffer ) throws UnsupportedEncodingException
    {

        if ( languageCode == null )
            requestBuffer.appendField( "ENG" );

        else if ( languageCode.equals("en") )
            requestBuffer.appendField( "ENG" );

        else if ( languageCode.equals("fr") )
            requestBuffer.appendField( "FRN" );

        else if ( languageCode.equals("de") )
            requestBuffer.appendField( "DEU" );

        else if ( languageCode.equals("ja") )
            requestBuffer.appendField( "JAN" );

        else if ( languageCode.equals("es") )
            requestBuffer.appendField( "ESP" );
        
        else if ( languageCode.equals("nl") )
            requestBuffer.appendField( "NLD" );

        else  // defualt
            throw new IllegalArgumentException("Invalid or unsupported language code \"" + languageCode + "\" in request.");

    }

    /**
     * Implementations of encodeFields() will call this
     * method to add the Track field to the host request.<br><br>
     * 
     * @param requestBuffer
     *               Host encoded request object.
     */
    protected final void encodeTrackField( RTSRequestEncodeBuffer requestBuffer ) throws UnsupportedEncodingException
    {
        requestBuffer.appendField( _track );
    }

    /**
     * Implementations of encodeFields() will call this
     * method to add the Activity field to the host request.<br><br>
     * 
     * @param requestBuffer
     *               Host encoded request object.
     */
    protected final void encodeActivityField( RTSRequestEncodeBuffer requestBuffer ) throws UnsupportedEncodingException
    {
        if ( _track.equals(Boolean.TRUE) )
        {
            if ( _activity == null )
            {
                requestBuffer.appendField( "API-[" + getClass().getName() + "]" );
            }
            else
            {
                requestBuffer.appendField( _activity );
            }
        }
        else
        {
            requestBuffer.appendField( "" );
        }
    }

    /*
     *  The following methods are used for the persistent transaction
     *  The transaction header need to be changed for the persistent transaction
     */
    public final void setPersistFlag( byte persistFlag )
    {
        assertUnsent();
        _persistFlag = persistFlag;
    }
    public final void setHandleID( int pHandleID )
    {
        assertUnsent();
        _pHandleID = pHandleID;
    }
    public final void setThreadID( long pThreadID )
    {
        assertUnsent();
        _pThreadID = pThreadID;
    }
    public final void setInstanceID( String instanceID )
    {
        assertUnsent();
    }

   /**
    * This method send the request to SonicMQ using SonicManager and parse
    * the response to RTSResponseDecodeBuffer.
    * 
    * @return RTSResponseDecodeBuffer
    */
   public final RTSResponseDecodeBuffer send(String routingInstruction) throws ProducerException,
         ProducerClosedException, SonicConfigException, IOException,
         ParseException {
      unsent = false;

      String encoding = (_hostEncoding == null) ? "ISO8859-1" : _hostEncoding;

      RTSRequestEncodeBuffer requestBuffer = null;

      if (_persistFlag != -1) {
         requestBuffer = new RTSRequestEncodeBuffer(encoding,
               _transactionId, _pHandleID, _pThreadID, _persistFlag);
      } else {
         requestBuffer = new RTSRequestEncodeBuffer(encoding, _transactionId);
      }
      encodeFields(requestBuffer);

      byte[] decByte = SonicManager.getInstance().sendReceive(requestBuffer.toByteArray(), routingInstruction);

      ByteArrayInputStream bs = new ByteArrayInputStream(decByte);

      RTSReader reader = new RTSReader(bs);

      return reader.readResponse(encoding);
   }
}
