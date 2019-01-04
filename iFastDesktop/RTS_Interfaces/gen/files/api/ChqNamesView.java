
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Cheque Names view.
 * For additional view information see <A HREF="../../../../viewspecs/ChqNames.doc">ChqNames.doc</A>.
 * 
 * @author RTS Generated
 */
public class ChqNamesView extends IFastView implements Serializable
{

   /**
    * Cheque Name first line member variable.
    */
   private String _Name1 = null;
   
   /**
    * Cheque Name 2nd line member variable.
    */
   private String _Name2 = null;
   

   /**
    * Constructs the ChqNamesView object.
    * 
    */
   public ChqNamesView()
   {
      super ( new ChqNamesRequest() );
   }

   /**
    * Constructs the ChqNamesView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public ChqNamesView( String hostEncoding )
   {
      super ( new ChqNamesRequest( hostEncoding ) );
   }

   /**
    * Gets the ChqNamesRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The ChqNamesRequest object.
    */
   public final ChqNamesRequest getRequest()
   {
      return (ChqNamesRequest)getIFastRequest();
   }
        
   /**
    * Gets the Cheque Name first line field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Cheque Name first line or null.
    */
   public final String getName1()
   {
      return _Name1;
   }
	
   /**
    * Gets the Cheque Name first line field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Cheque Name first line or the specified default value.
    */
   public final String getName1( String defaultValue )
   {
      return _Name1 == null ? defaultValue : _Name1;
   }
                  
   /**
    * Gets the Cheque Name 2nd line field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Cheque Name 2nd line or null.
    */
   public final String getName2()
   {
      return _Name2;
   }
	
   /**
    * Gets the Cheque Name 2nd line field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Cheque Name 2nd line or the specified default value.
    */
   public final String getName2( String defaultValue )
   {
      return _Name2 == null ? defaultValue : _Name2;
   }
                  
   /**
    * Implements the abstract base method to decode
    * the host formatted response.
    * 
    * @param response Host formatted response object.
    * @exception ParseException
    */
   protected void decodeFields( RTSResponseDecodeBuffer responseBuffer ) throws ParseException, UnsupportedEncodingException
   {
      
      // single-record section
      _Name1 = responseBuffer.decodeString(responseBuffer.getNextField());
      _Name2 = responseBuffer.decodeString(responseBuffer.getNextField());
                  

   }

}
      
