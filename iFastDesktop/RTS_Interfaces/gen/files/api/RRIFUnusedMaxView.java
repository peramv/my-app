
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * RRIF Unused Amount CalCulate view.
 * For additional view information see <A HREF="../../../../viewspecs/RRIFUnusedMax.doc">RRIFUnusedMax.doc</A>.
 * 
 * @author RTS Generated
 */
public class RRIFUnusedMaxView extends IFastView implements Serializable
{

   /**
    * UnusedAmount member variable.
    */
   private String _UnusedAmount = null;
   
   /**
    * MaxAmount member variable.
    */
   private String _MaxAmount = null;
   

   /**
    * Constructs the RRIFUnusedMaxView object.
    * 
    */
   public RRIFUnusedMaxView()
   {
      super ( new RRIFUnusedMaxRequest() );
   }

   /**
    * Constructs the RRIFUnusedMaxView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public RRIFUnusedMaxView( String hostEncoding )
   {
      super ( new RRIFUnusedMaxRequest( hostEncoding ) );
   }

   /**
    * Gets the RRIFUnusedMaxRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The RRIFUnusedMaxRequest object.
    */
   public final RRIFUnusedMaxRequest getRequest()
   {
      return (RRIFUnusedMaxRequest)getIFastRequest();
   }
        
   /**
    * Gets the UnusedAmount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the UnusedAmount or null.
    */
   public final String getUnusedAmount()
   {
      return _UnusedAmount;
   }
	
   /**
    * Gets the UnusedAmount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the UnusedAmount or the specified default value.
    */
   public final String getUnusedAmount( String defaultValue )
   {
      return _UnusedAmount == null ? defaultValue : _UnusedAmount;
   }
                  
   /**
    * Gets the MaxAmount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the MaxAmount or null.
    */
   public final String getMaxAmount()
   {
      return _MaxAmount;
   }
	
   /**
    * Gets the MaxAmount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the MaxAmount or the specified default value.
    */
   public final String getMaxAmount( String defaultValue )
   {
      return _MaxAmount == null ? defaultValue : _MaxAmount;
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
      _UnusedAmount = responseBuffer.decodeString(responseBuffer.getNextField());
      _MaxAmount = responseBuffer.decodeString(responseBuffer.getNextField());
                  

   }

}
      
