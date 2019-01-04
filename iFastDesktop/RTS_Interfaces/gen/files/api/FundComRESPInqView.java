
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * FUNDCom RESP Information Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/FundComRESPInq.doc">FundComRESPInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class FundComRESPInqView extends IFastView implements Serializable
{

   /**
    * Tax Year member variable.
    */
   private Integer _TaxYear = null;
   
   /**
    * YTD Amount member variable.
    */
   private String _YTDAmt = null;
   
   /**
    * YTD Grant member variable.
    */
   private String _YTDGrant = null;
   
   /**
    * Life Amount member variable.
    */
   private String _LifeAmt = null;
   
   /**
    * Life Grant member variable.
    */
   private String _LifeGrant = null;
   
   /**
    * YTD UnAssisted member variable.
    */
   private String _YTDUnAssisted = null;
   
   /**
    * YTD Assisted member variable.
    */
   private String _YTDAssisted = null;
   

   /**
    * Constructs the FundComRESPInqView object.
    * 
    */
   public FundComRESPInqView()
   {
      super ( new FundComRESPInqRequest() );
   }

   /**
    * Constructs the FundComRESPInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public FundComRESPInqView( String hostEncoding )
   {
      super ( new FundComRESPInqRequest( hostEncoding ) );
   }

   /**
    * Gets the FundComRESPInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The FundComRESPInqRequest object.
    */
   public final FundComRESPInqRequest getRequest()
   {
      return (FundComRESPInqRequest)getIFastRequest();
   }
        
   /**
    * Gets the Tax Year field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Tax Year or null.
    */
   public final Integer getTaxYear()
   {
      return _TaxYear;
   }
	
   /**
    * Gets the Tax Year field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Year or the specified default value.
    */
   public final int getTaxYear( int defaultValue )
   {
      return _TaxYear == null ? defaultValue : _TaxYear.intValue();
   }
                  
   /**
    * Gets the YTD Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the YTD Amount or null.
    */
   public final String getYTDAmt()
   {
      return _YTDAmt;
   }
	
   /**
    * Gets the YTD Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the YTD Amount or the specified default value.
    */
   public final String getYTDAmt( String defaultValue )
   {
      return _YTDAmt == null ? defaultValue : _YTDAmt;
   }
                  
   /**
    * Gets the YTD Grant field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the YTD Grant or null.
    */
   public final String getYTDGrant()
   {
      return _YTDGrant;
   }
	
   /**
    * Gets the YTD Grant field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the YTD Grant or the specified default value.
    */
   public final String getYTDGrant( String defaultValue )
   {
      return _YTDGrant == null ? defaultValue : _YTDGrant;
   }
                  
   /**
    * Gets the Life Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Life Amount or null.
    */
   public final String getLifeAmt()
   {
      return _LifeAmt;
   }
	
   /**
    * Gets the Life Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Life Amount or the specified default value.
    */
   public final String getLifeAmt( String defaultValue )
   {
      return _LifeAmt == null ? defaultValue : _LifeAmt;
   }
                  
   /**
    * Gets the Life Grant field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Life Grant or null.
    */
   public final String getLifeGrant()
   {
      return _LifeGrant;
   }
	
   /**
    * Gets the Life Grant field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Life Grant or the specified default value.
    */
   public final String getLifeGrant( String defaultValue )
   {
      return _LifeGrant == null ? defaultValue : _LifeGrant;
   }
                  
   /**
    * Gets the YTD UnAssisted field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the YTD UnAssisted or null.
    */
   public final String getYTDUnAssisted()
   {
      return _YTDUnAssisted;
   }
	
   /**
    * Gets the YTD UnAssisted field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the YTD UnAssisted or the specified default value.
    */
   public final String getYTDUnAssisted( String defaultValue )
   {
      return _YTDUnAssisted == null ? defaultValue : _YTDUnAssisted;
   }
                  
   /**
    * Gets the YTD Assisted field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the YTD Assisted or null.
    */
   public final String getYTDAssisted()
   {
      return _YTDAssisted;
   }
	
   /**
    * Gets the YTD Assisted field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the YTD Assisted or the specified default value.
    */
   public final String getYTDAssisted( String defaultValue )
   {
      return _YTDAssisted == null ? defaultValue : _YTDAssisted;
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
      _TaxYear = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _YTDAmt = responseBuffer.decodeString(responseBuffer.getNextField());
      _YTDGrant = responseBuffer.decodeString(responseBuffer.getNextField());
      _LifeAmt = responseBuffer.decodeString(responseBuffer.getNextField());
      _LifeGrant = responseBuffer.decodeString(responseBuffer.getNextField());
      _YTDUnAssisted = responseBuffer.decodeString(responseBuffer.getNextField());
      _YTDAssisted = responseBuffer.decodeString(responseBuffer.getNextField());
                  

   }

}
      
