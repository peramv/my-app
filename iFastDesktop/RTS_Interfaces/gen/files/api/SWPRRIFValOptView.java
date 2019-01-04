
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * SWP/RRIF validations for GWA/LWA option view.
 * For additional view information see <A HREF="../../../../viewspecs/SWPRRIFValOpt.doc">SWPRRIFValOpt.doc</A>.
 * 
 * @author RTS Generated
 */
public class SWPRRIFValOptView extends IFastView implements Serializable
{

   /**
    * ErrorNum member variable.
    */
   private Integer _ErrorNum = null;
   
   /**
    * Error Severity member variable.
    */
   private String _EWI = null;
   
   /**
    * Flag the indicates if Gross/Net PreTax default to NetOfFees member variable.
    */
   private Boolean _NetOfFeesFlag = null;
   

   /**
    * Constructs the SWPRRIFValOptView object.
    * 
    */
   public SWPRRIFValOptView()
   {
      super ( new SWPRRIFValOptRequest() );
   }

   /**
    * Constructs the SWPRRIFValOptView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public SWPRRIFValOptView( String hostEncoding )
   {
      super ( new SWPRRIFValOptRequest( hostEncoding ) );
   }

   /**
    * Gets the SWPRRIFValOptRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The SWPRRIFValOptRequest object.
    */
   public final SWPRRIFValOptRequest getRequest()
   {
      return (SWPRRIFValOptRequest)getIFastRequest();
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
    * Gets the Error Severity field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Error Severity or null.
    */
   public final String getEWI()
   {
      return _EWI;
   }
	
   /**
    * Gets the Error Severity field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Error Severity or the specified default value.
    */
   public final String getEWI( String defaultValue )
   {
      return _EWI == null ? defaultValue : _EWI;
   }
                  
   /**
    * Gets the Flag the indicates if Gross/Net PreTax default to NetOfFees field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Flag the indicates if Gross/Net PreTax default to NetOfFees or null.
    */
   public final Boolean getNetOfFeesFlag()
   {
      return _NetOfFeesFlag;
   }
	
   /**
    * Gets the Flag the indicates if Gross/Net PreTax default to NetOfFees field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag the indicates if Gross/Net PreTax default to NetOfFees or the specified default value.
    */
   public final boolean getNetOfFeesFlag( boolean defaultValue )
   {
      return _NetOfFeesFlag == null ? defaultValue : _NetOfFeesFlag.booleanValue();
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
      _EWI = responseBuffer.decodeString(responseBuffer.getNextField());
      _NetOfFeesFlag = responseBuffer.decodeBoolean(responseBuffer.getNextField());
                  

   }

}
      
