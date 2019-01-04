package com.ifds.iFast.api;

import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.util.Date;
import java.text.ParseException;
import java.net.Socket;
import com.ifds.rts.*;
import java.io.Serializable;

/**
 * Abstract base class for all iFast view objects.
 * The class provides a framework decoding and host
 * responses.
 */
public abstract class IFastView implements Serializable
{
   private final static int SYSTEM_RESPONSE = -1;
   private final static int ERROR_RESPONSE = 1;
   private final static int NORMAL_RESPONSE = 2;

   private final IFastRequest _request;

   private boolean _receivedFirst = false;
   private boolean _moreAvailable = false;
   
   private String _nextKey = "";

   private IFastErrorResponse _errorResponse = null;

   /**
    *
    */
   IFastView( IFastRequest request )
   {
      _request = request;
   }

   /**
    *
    */
   final IFastRequest getIFastRequest()
   {
      return _request;
   }

   /**
    * This method is called to retrieved data from the
    * host for attached request. This method will return
    * true if data was recieved, otherwise false is
    * returned and the host error response can be
    * retrieved using the getErrorResponse() method.<br><br>
    * 
    * Many views are large multi-record views and may
    * not return all records in one host request. If the 
    * number of records exceeds the host defined maximum
    * after the first receive() call, the isMoreAvailable() 
    * method will return true and subsequent receive() calls
    * may be made.<br><br>
    * 
    * @param ipAddress  The IP address of the iFast host.
    * @param portNumber The port of the iFast host.
    * @return false if an error response was received, otherwise
    *         true
    * @exception IOException
    * @exception ParseException
    * @exception IFastSystemResponseException
    */
   public final boolean receive( String ipAddress, int portNumber ) throws IOException, ParseException, IFastSystemResponseException
   {
      return rawReceive( ipAddress, portNumber, 0 );
   }

   /**
    * This method is called to retrieved data from the
    * host for attached request. This method will return
    * true if data was recieved, otherwise false is
    * returned and the host error response can be
    * retrieved using the getErrorResponse() method.<br><br>
    * 
    * Many views are large multi-record views and may
    * not return all records in one host request. If the 
    * number of records exceeds the host defined maximum
    * after the first receive() call, the isMoreAvailable() 
    * method will return true and subsequent receive() calls
    * may be made.<br><br>
    * 
    * @param socket An open socket to the iFast host.
    * @return false if an error response was received, otherwise
    *         true
    * @exception IOException
    * @exception ParseException
    * @exception IFastSystemResponseException
    */
   public final boolean receive( Socket socket ) throws IOException, ParseException, IFastSystemResponseException
   {
      return rawReceive( socket, 0 );
   }

   /**
    * This method is called to retrieved data from the
    * host for attached request. This method will return
    * true if data was recieved, otherwise false is
    * returned and the host error response can be
    * retrieved using the getErrorResponse() method.<br><br>
    * 
    * This method allows the caller to override the number 
    * of records in the repeating section to be returned. This
    * override is ignored if it exceeds the host defined 
    * maximum.<br><br>
    * 
    * If more records are available on the host than are 
    * returned, the isMoreAvailable() method will return true 
    * and subsequent receive() calls may be made.<br><br>
    * 
    * @param ipAddress  The IP address of the iFast host.
    * @param portNumber The port of the iFast host.
    * @param overrideRepeats
    *                   Number of records to return.
    * @return false if an error response was received, otherwise
    *         true
    * @exception IOException
    * @exception ParseException
    * @exception IFastSystemResponseException
    */
   public final boolean receive( String ipAddress, int portNumber, int overrideRepeats ) throws IOException, ParseException, IFastSystemResponseException
   {
      return rawReceive( ipAddress, portNumber, overrideRepeats );
   }

   /**
    * This method is called to retrieved data from the
    * host for attached request. This method will return
    * true if data was recieved, otherwise false is
    * returned and the host error response can be
    * retrieved using the getErrorResponse() method.<br><br>
    * 
    * This method allows the caller to override the number 
    * of records in the repeating section to be returned. This
    * override is ignored if it exceeds the host defined 
    * maximum.<br><br>
    * 
    * If more records are available on the host than are 
    * returned, the isMoreAvailable() method will return true 
    * and subsequent receive() calls may be made.<br><br>
    * 
    * @param socket An open socket to the iFast host.
    * @param overrideRepeats
    *               Number of records to return.
    * @return false if an error response was received, otherwise
    *         true
    * @exception IOException
    * @exception ParseException
    * @exception IFastSystemResponseException
    */
   public final boolean receive( Socket socket, int overrideRepeats ) throws IOException, ParseException, IFastSystemResponseException
   {
      return rawReceive( socket, overrideRepeats );
   }

   /**
    * This method is called to retrieve the specified
    * number of records from the host for attached 
    * request. This method will return true if all
    * data was recieved, without an error, otherwise 
    * false is returned and the host error response 
    * can be retrieved using the getErrorResponse() 
    * method.<br><br>
    * 
    * If the number of records avaiable on the host exceeds
    * the host defined maximum, this method will cause multiple
    * host transactions to occur, each returning the host
    * defined maximum, until the required number of records 
    * are retrieved. If fewer records are available that the 
    * specified number, all records are returned<br><br>
    * 
    * If more records are available on the host than are 
    * returned, the isMoreAvailable() method will return true 
    * and subsequent receive() calls may be made.<br><br>
    * 
    * @param ipAddress  The IP address of the iFast host.
    * @param portNumber The port of the iFast host.
    * @param repeats An open socket to the iFast host.
    * @return false if an error response was received, otherwise
    *         true
    * @exception IOException
    * @exception ParseException
    * @exception IFastSystemResponseException
    */
   public final boolean receiveSpecific( String ipAddress, int portNumber, int repeats ) throws IOException, ParseException, IFastSystemResponseException
   {
      while ( !_receivedFirst || _moreAvailable )
      {
         int repeatsRemaining = repeats - getRecordCount();
         if (repeatsRemaining == 0)
            break;

         if ( !rawReceive( ipAddress, portNumber, repeatsRemaining ) )
            return false;
      }

      return true;
   }

   /**
    * This method is called to retrieve the specified
    * number of records from the host for attached 
    * request. This method will return true if all
    * data was recieved, without an error, otherwise 
    * false is returned and the host error response 
    * can be retrieved using the getErrorResponse() 
    * method.<br><br>
    * 
    * If the number of records avaiable on the host exceeds
    * the host defined maximum, this method will cause multiple
    * host transactions to occur, each returning the host
    * defined maximum, until the required number of records 
    * are retrieved. If fewer records are available that the 
    * specified number, all records are returned<br><br>
    * 
    * If more records are available on the host than are 
    * returned, the isMoreAvailable() method will return true 
    * and subsequent receive() calls may be made.<br><br>
    * 
    * @param socket An open socket to the iFast host.
    * @param repeats An open socket to the iFast host.
    * @return false if an error response was received, otherwise
    *         true
    * @exception IOException
    * @exception ParseException
    * @exception IFastSystemResponseException
    */
   public final boolean receiveSpecific( Socket socket, int repeats ) throws IOException, ParseException, IFastSystemResponseException
   {
      while ( !_receivedFirst || _moreAvailable )
      {
         int repeatsRemaining = repeats - getRecordCount();
         if (repeatsRemaining == 0)
            break;

         if ( !rawReceive( socket, repeatsRemaining ) )
            return false;
      }

      return true;
   }

   /**
    * This method is called to retrieve all data from the
    * host for attached request. This method will return
    * true if all data was recieved, without an error,
    * otherwise false is returned and the host error
    * response can be retrieved using the
    * getErrorResponse() method.<br><br>
    * 
    * If the number of records avaiable on the host exceeds
    * the host defined maximum, this method will cause multiple
    * host transactions to occur, each returning the host
    * defined maximum, until all records are retrieved.<br><br>
    * 
    * After this method is called the isMoreAvailable() 
    * method will always return false.<br><br>
    * 
    * @param ipAddress  The IP address of the iFast host.
    * @param portNumber The port of the iFast host.
    * @return false if an error response was received, otherwise
    *         true
    * @exception IOException
    * @exception ParseException
    * @exception IFastSystemResponseException
    */
   public final boolean receiveAll( String ipAddress, int portNumber ) throws IOException, ParseException, IFastSystemResponseException
   {
      while ( !_receivedFirst || _moreAvailable )
      {
         if ( !rawReceive( ipAddress, portNumber, 0 ) )
            return false;
      }

      return true;
   }

   /**
    * This method is called to retrieve all data from the
    * host for attached request. This method will return
    * true if all data was recieved, without an error,
    * otherwise false is returned and the host error
    * response can be retrieved using the
    * getErrorResponse() method.<br><br>
    * 
    * If the number of records avaiable on the host exceeds
    * the host defined maximum, this method will cause multiple
    * host transactions to occur, each returning the host
    * defined maximum, until all records are retrieved.<br><br>
    * 
    * After this method is called the isMoreAvailable() 
    * method will always return false.<br><br>
    * 
    * @param socket An open socket to the iFast host.
    * @return false if an error response was received, otherwise
    *         true
    * @exception IOException
    * @exception ParseException
    * @exception IFastSystemResponseException
    */
   public final boolean receiveAll( Socket socket ) throws IOException, ParseException, IFastSystemResponseException
   {
      while ( !_receivedFirst || _moreAvailable )
      {
         if ( !rawReceive( socket, 0 ) )
            return false;
      }

      return true;
   }

   /**
    *
    */
   private final boolean rawReceive( Socket socket, int overrideRepeats ) throws IOException, ParseException, IFastSystemResponseException
   {
      if ( _receivedFirst && !_moreAvailable )
         throw new IllegalStateException( "Unable to receive view - no records available." );

      _request.setOverrideRepeats( overrideRepeats );
      return processResponse ( _request.send( socket ) );
   }

   /**
    *
    */
   private final boolean rawReceive( String ipAddress, int portNumber,int overrideRepeats ) throws IOException, ParseException, IFastSystemResponseException
   {
      if ( _receivedFirst && !_moreAvailable )
         throw new IllegalStateException( "Unable to receive view - no records available." );

      _request.setOverrideRepeats( overrideRepeats );
      return processResponse ( _request.send( ipAddress, portNumber ) );
   }

   /**
    *
    */
   private final boolean processResponse( RTSResponseDecodeBuffer responseBuffer ) throws ParseException, IOException, IFastSystemResponseException
   {

      _receivedFirst = true;

      switch ( Integer.parseInt( responseBuffer.getResponseTypeID() ) )
      {
      case SYSTEM_RESPONSE:
         throw new IFastSystemResponseException( responseBuffer );

      case ERROR_RESPONSE:
         IFastErrorResponse er = new IFastErrorResponse( responseBuffer );
         if ( _receivedFirst && er.getCode() == _errorResponse.DATA_NOT_FOUND) {
            _moreAvailable = false;
            return true;
         } else {
            _errorResponse = er;
            _moreAvailable = false;
            return false;
         }

      case NORMAL_RESPONSE:
//         _receivedFirst = true;
         decodeFields( responseBuffer );

         if ( _moreAvailable )
         {
            if ( _request.getNextKey().equals(_nextKey) )
            {
               _moreAvailable = false;
               throw new IllegalStateException( "NextKey in response is identical to that of request -- [" + _nextKey + "]" );
            }

            _request.setNextKeyInternal(_nextKey);
         }

         return true;
      
      default:
         throw new IFastSystemResponseException( "Unknown response type [" + responseBuffer.getResponseTypeID() + "]." );
      
      }

   }

   /**
    * Tests for the availablity of more records at the
    * host for the attached request. This state is
    * unknown until after the first receive call, and
    * will throw an exception if call prior to receive()
    * or receiveAll().<br><br>
    * 
    * This state should be tested before all subsequent
    * receive calls. If receive() or receiveAll() are
    * called when the moreAvaiable state if false, an
    * exception is thrown.<br><br>
    * 
    * @return true if there are more records avaialble, false
    *         otherwise.
    */
   public final boolean isMoreAvailable()
   {
      if ( !_receivedFirst )
         throw new IllegalStateException( "Unable to test for more avaialable before recieve is called." );
      
      return _moreAvailable;
   }

   /**
    *
    */
   public final String getNextKey()
   {
      return _nextKey;
   }

   /**
    *
    */
   public int getRecordCount() 
   {
      return 0;
   }

   /**
    * Gets the host error associated with the view. If no
    * error has occurred, null is returned.<br><br>
    * 
    * Typically this will be as a result of data not
    * being found for the given request, or inappropriate
    * field data in the request.<br><br>
    *
    * @return The host error associated with the view, or null.
    */
   public final IFastErrorResponse getErrorResponse()
   {
      return _errorResponse;
   }

   /**
    * Abstract method that all view objects must
    * implement. Implementers will decode each field
    * in order, from the given host response object.<br><br>
    * 
    * @param response
    *               Host encoded response object.
    */
   protected abstract void decodeFields( RTSResponseDecodeBuffer responseBuffer ) throws ParseException, UnsupportedEncodingException;

   /**
    * Implementations of decodeFields() will call this
    * method get the MoreAvailable field from the host response.<br><br>
    * 
    * @param response
    *               Host encoded response object.
    */
   protected final void decodeMoreAvailableField( RTSResponseDecodeBuffer responseBuffer ) throws ParseException, UnsupportedEncodingException
   {
      
      Boolean field = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      
       if ( field == null )
         throw new NullPointerException("MoreAvailable decodes to null field.");

      _moreAvailable = field.booleanValue();

   }
   
   /**
    * Implementations of decodeFields() will call this
    * method get the NextKey field from the host response.<br><br>
    * 
    * @param response
    *               Host encoded response object.
    */
   protected final void decodeNextKeyField( RTSResponseDecodeBuffer responseBuffer ) throws ParseException, UnsupportedEncodingException
   {
      String field = responseBuffer.decodeString(responseBuffer.getNextField());

      if ( field == null )
         throw new NullPointerException("NextKey decodes to null field.");

      _nextKey = field;

   }

   /**
    * Implementations of decodeFields() will call this
    * method get and translate the LanguageCode field from 
    * the host response.<br><br>
    * 
    * @param response
    *               Host encoded response object.
    */
   protected static String decodeLanguageCodeField( RTSResponseDecodeBuffer responseBuffer ) throws ParseException, UnsupportedEncodingException
   {
      String languageCode =  responseBuffer.decodeString(responseBuffer.getNextField());
   
      if ( languageCode == null || languageCode.equals("ENG") )
         return "en";

      else if ( languageCode.equals("FRN") )
         return "fr";
      
      else if ( languageCode.equals("GEM") )
         return "de";
      
      else if ( languageCode.equals("JAN") )
         return "ja";

      else if ( languageCode.equals("NLD") )
         return "nl";

      else  // defualt
         return "en";

   }

   /**
    * Resizes the given array of Boolean objects to the
    * given size.<br><br>
    * 
    * @param array  Array to be resized.
    * @param recordCount
    *               New size of the array.
    * @return The enlarged array.
    */
   protected static Boolean[] resizeArray( Boolean[] array, int recordCount )
   {
      if ( array == null )
         return new Boolean[recordCount];
      
      if ( array.length < recordCount )
      {
         Boolean[] newArray = new Boolean[recordCount];

         for ( int i = 0; i < array.length; i++ )
         {
            newArray[i] = array[i];
         }
         array = newArray;
      }
      return array;
   }

   /**
    * Resizes the given array of Date objects to the
    * given size.<br><br>
    * 
    * @param array  Array to be resized.
    * @param recordCount
    *               New size of the array.
    * @return The enlarged array.
    */
   protected static Date[] resizeArray( Date[] array, int recordCount )
   {
      if ( array == null )
         return new Date[recordCount];
      
      if ( array.length < recordCount )
      {
         Date[] newArray = new Date[recordCount];

         for ( int i = 0; i < array.length; i++ )
         {
            newArray[i] = array[i];
         }
         array = newArray;
      }
      return array;
   }

   /**
    * Resizes the given array of Double objects to the
    * given size.<br><br>
    * 
    * @param array  Array to be resized.
    * @param recordCount
    *               New size of the array.
    * @return The enlarged array.
    */
   protected static Double[] resizeArray( Double[] array, int recordCount )
   {
      if ( array == null )
         return new Double[recordCount];
      
      if ( array.length < recordCount )
      {
         Double[] newArray = new Double[recordCount];

         for ( int i = 0; i < array.length; i++ )
         {
            newArray[i] = array[i];
         }
         array = newArray;
      }
      return array;
   }

   /**
    * Resizes the given array of Integer objects to the
    * given size.<br><br>
    * 
    * @param array  Array to be resized.
    * @param recordCount
    *               New size of the array.
    * @return The enlarged array.
    */
   protected static Integer[] resizeArray( Integer[] array, int recordCount )
   {
      if ( array == null )
         return new Integer[recordCount];
      
      if ( array.length < recordCount )
      {
         Integer[] newArray = new Integer[recordCount];

         for ( int i = 0; i < array.length; i++ )
         {
            newArray[i] = array[i];
         }
         array = newArray;
      }
      return array;
   }

   /**
    * Resizes the given array of String objects to the
    * given size.<br><br>
    * 
    * @param array  Array to be resized.
    * @param recordCount
    *               New size of the array.
    * @return The enlarged array.
    */
   protected static String[] resizeArray( String[] array, int recordCount )
   {
      if ( array == null )
         return new String[recordCount];

      
      if ( array.length < recordCount )
      {
         String[] newArray = new String[recordCount];

         for ( int i = 0; i < array.length; i++ )
         {
            newArray[i] = array[i];
         }
         array = newArray;
      }
      return array;
   }

}
