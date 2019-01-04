
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Trade Limitation Override Enquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/TradeLmtOverInq.doc">TradeLmtOverInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class TradeLmtOverInqView extends IFastView implements Serializable
{

   /**
    * ErrorNum member variable.
    */
   private Integer _ErrorNum = null;
   
   /**
    * ErrorMsg member variable.
    */
   private String _ErrorMsg = null;
   
   /**
    * EWI member variable.
    */
   private String _EWI = null;
   

   /**
    * Constructs the TradeLmtOverInqView object.
    * 
    */
   public TradeLmtOverInqView()
   {
      super ( new TradeLmtOverInqRequest() );
   }

   /**
    * Constructs the TradeLmtOverInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public TradeLmtOverInqView( String hostEncoding )
   {
      super ( new TradeLmtOverInqRequest( hostEncoding ) );
   }

   /**
    * Gets the TradeLmtOverInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The TradeLmtOverInqRequest object.
    */
   public final TradeLmtOverInqRequest getRequest()
   {
      return (TradeLmtOverInqRequest)getIFastRequest();
   }
        
   /**
    * Gets the ErrorNum field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the ErrorNum or null.
    */
   public final Integer getErrorNum()
   {
      return _ErrorNum;
   }
	
   /**
    * Gets the ErrorNum field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ErrorNum or the specified default value.
    */
   public final int getErrorNum( int defaultValue )
   {
      return _ErrorNum == null ? defaultValue : _ErrorNum.intValue();
   }
                  
   /**
    * Gets the ErrorMsg field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the ErrorMsg or null.
    */
   public final String getErrorMsg()
   {
      return _ErrorMsg;
   }
	
   /**
    * Gets the ErrorMsg field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ErrorMsg or the specified default value.
    */
   public final String getErrorMsg( String defaultValue )
   {
      return _ErrorMsg == null ? defaultValue : _ErrorMsg;
   }
                  
   /**
    * Gets the EWI field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the EWI or null.
    */
   public final String getEWI()
   {
      return _EWI;
   }
	
   /**
    * Gets the EWI field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the EWI or the specified default value.
    */
   public final String getEWI( String defaultValue )
   {
      return _EWI == null ? defaultValue : _EWI;
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
      _ErrorNum = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _ErrorMsg = responseBuffer.decodeString(responseBuffer.getNextField());
      _EWI = responseBuffer.decodeString(responseBuffer.getNextField());
                  

   }

}
      
