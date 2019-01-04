
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Hypothetical Foreign Content view.
 * For additional view information see <A HREF="../../../../viewspecs/HypoFxContlnq.doc">HypoFxContlnq.doc</A>.
 * 
 * @author RTS Generated
 */
public class HypoFxContlnqView extends IFastView implements Serializable
{

   /**
    * Domestic ACB Amount Before member variable.
    */
   private String _DomesticACBAmtBefore = null;
   
   /**
    * Domestic Percent Before member variable.
    */
   private String _DomesticPrcntBefore = null;
   
   /**
    * Domestic ACB Amount After member variable.
    */
   private String _DomesticACBAmtAfter = null;
   
   /**
    * Domestic Percent After member variable.
    */
   private String _DomesticPrcntAfter = null;
   
   /**
    * Foreign ACB Amount Before member variable.
    */
   private String _FrgnACBAmtBefore = null;
   
   /**
    * Foreign Percent Before member variable.
    */
   private String _FrgnPrcntBefore = null;
   
   /**
    * Foreign ACB Amount After member variable.
    */
   private String _FrgnACBAmtAfter = null;
   
   /**
    * Foreign Percent After member variable.
    */
   private String _FrgnPrcntAfter = null;
   
   /**
    * Foreign Allowed Percent Before member variable.
    */
   private String _FrgnAllowedPrcntBefore = null;
   
   /**
    * Foreign Allowed Amount Before member variable.
    */
   private String _FrgnAllowedAmtBefore = null;
   
   /**
    * Rate member variable.
    */
   private String _Rate = null;
   
   /**
    * Total ACB Amount Before member variable.
    */
   private String _TotalACBAmtBefore = null;
   
   /**
    * Total ACB Amount After member variable.
    */
   private String _TotalACBAmtAfter = null;
   
   /**
    * Foreign Allowed Amount After member variable.
    */
   private String _FrgnAllowedAmtAfter = null;
   
   /**
    * Foreign Allowed Percent After member variable.
    */
   private String _FrgnAllowedPrcntAfter = null;
   

   /**
    * Constructs the HypoFxContlnqView object.
    * 
    */
   public HypoFxContlnqView()
   {
      super ( new HypoFxContlnqRequest() );
   }

   /**
    * Constructs the HypoFxContlnqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public HypoFxContlnqView( String hostEncoding )
   {
      super ( new HypoFxContlnqRequest( hostEncoding ) );
   }

   /**
    * Gets the HypoFxContlnqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The HypoFxContlnqRequest object.
    */
   public final HypoFxContlnqRequest getRequest()
   {
      return (HypoFxContlnqRequest)getIFastRequest();
   }
        
   /**
    * Gets the Domestic ACB Amount Before field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Domestic ACB Amount Before or null.
    */
   public final String getDomesticACBAmtBefore()
   {
      return _DomesticACBAmtBefore;
   }
	
   /**
    * Gets the Domestic ACB Amount Before field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Domestic ACB Amount Before or the specified default value.
    */
   public final String getDomesticACBAmtBefore( String defaultValue )
   {
      return _DomesticACBAmtBefore == null ? defaultValue : _DomesticACBAmtBefore;
   }
                  
   /**
    * Gets the Domestic Percent Before field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Domestic Percent Before or null.
    */
   public final String getDomesticPrcntBefore()
   {
      return _DomesticPrcntBefore;
   }
	
   /**
    * Gets the Domestic Percent Before field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Domestic Percent Before or the specified default value.
    */
   public final String getDomesticPrcntBefore( String defaultValue )
   {
      return _DomesticPrcntBefore == null ? defaultValue : _DomesticPrcntBefore;
   }
                  
   /**
    * Gets the Domestic ACB Amount After field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Domestic ACB Amount After or null.
    */
   public final String getDomesticACBAmtAfter()
   {
      return _DomesticACBAmtAfter;
   }
	
   /**
    * Gets the Domestic ACB Amount After field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Domestic ACB Amount After or the specified default value.
    */
   public final String getDomesticACBAmtAfter( String defaultValue )
   {
      return _DomesticACBAmtAfter == null ? defaultValue : _DomesticACBAmtAfter;
   }
                  
   /**
    * Gets the Domestic Percent After field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Domestic Percent After or null.
    */
   public final String getDomesticPrcntAfter()
   {
      return _DomesticPrcntAfter;
   }
	
   /**
    * Gets the Domestic Percent After field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Domestic Percent After or the specified default value.
    */
   public final String getDomesticPrcntAfter( String defaultValue )
   {
      return _DomesticPrcntAfter == null ? defaultValue : _DomesticPrcntAfter;
   }
                  
   /**
    * Gets the Foreign ACB Amount Before field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Foreign ACB Amount Before or null.
    */
   public final String getFrgnACBAmtBefore()
   {
      return _FrgnACBAmtBefore;
   }
	
   /**
    * Gets the Foreign ACB Amount Before field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Foreign ACB Amount Before or the specified default value.
    */
   public final String getFrgnACBAmtBefore( String defaultValue )
   {
      return _FrgnACBAmtBefore == null ? defaultValue : _FrgnACBAmtBefore;
   }
                  
   /**
    * Gets the Foreign Percent Before field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Foreign Percent Before or null.
    */
   public final String getFrgnPrcntBefore()
   {
      return _FrgnPrcntBefore;
   }
	
   /**
    * Gets the Foreign Percent Before field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Foreign Percent Before or the specified default value.
    */
   public final String getFrgnPrcntBefore( String defaultValue )
   {
      return _FrgnPrcntBefore == null ? defaultValue : _FrgnPrcntBefore;
   }
                  
   /**
    * Gets the Foreign ACB Amount After field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Foreign ACB Amount After or null.
    */
   public final String getFrgnACBAmtAfter()
   {
      return _FrgnACBAmtAfter;
   }
	
   /**
    * Gets the Foreign ACB Amount After field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Foreign ACB Amount After or the specified default value.
    */
   public final String getFrgnACBAmtAfter( String defaultValue )
   {
      return _FrgnACBAmtAfter == null ? defaultValue : _FrgnACBAmtAfter;
   }
                  
   /**
    * Gets the Foreign Percent After field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Foreign Percent After or null.
    */
   public final String getFrgnPrcntAfter()
   {
      return _FrgnPrcntAfter;
   }
	
   /**
    * Gets the Foreign Percent After field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Foreign Percent After or the specified default value.
    */
   public final String getFrgnPrcntAfter( String defaultValue )
   {
      return _FrgnPrcntAfter == null ? defaultValue : _FrgnPrcntAfter;
   }
                  
   /**
    * Gets the Foreign Allowed Percent Before field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Foreign Allowed Percent Before or null.
    */
   public final String getFrgnAllowedPrcntBefore()
   {
      return _FrgnAllowedPrcntBefore;
   }
	
   /**
    * Gets the Foreign Allowed Percent Before field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Foreign Allowed Percent Before or the specified default value.
    */
   public final String getFrgnAllowedPrcntBefore( String defaultValue )
   {
      return _FrgnAllowedPrcntBefore == null ? defaultValue : _FrgnAllowedPrcntBefore;
   }
                  
   /**
    * Gets the Foreign Allowed Amount Before field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Foreign Allowed Amount Before or null.
    */
   public final String getFrgnAllowedAmtBefore()
   {
      return _FrgnAllowedAmtBefore;
   }
	
   /**
    * Gets the Foreign Allowed Amount Before field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Foreign Allowed Amount Before or the specified default value.
    */
   public final String getFrgnAllowedAmtBefore( String defaultValue )
   {
      return _FrgnAllowedAmtBefore == null ? defaultValue : _FrgnAllowedAmtBefore;
   }
                  
   /**
    * Gets the Rate field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Rate or null.
    */
   public final String getRate()
   {
      return _Rate;
   }
	
   /**
    * Gets the Rate field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Rate or the specified default value.
    */
   public final String getRate( String defaultValue )
   {
      return _Rate == null ? defaultValue : _Rate;
   }
                  
   /**
    * Gets the Total ACB Amount Before field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Total ACB Amount Before or null.
    */
   public final String getTotalACBAmtBefore()
   {
      return _TotalACBAmtBefore;
   }
	
   /**
    * Gets the Total ACB Amount Before field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Total ACB Amount Before or the specified default value.
    */
   public final String getTotalACBAmtBefore( String defaultValue )
   {
      return _TotalACBAmtBefore == null ? defaultValue : _TotalACBAmtBefore;
   }
                  
   /**
    * Gets the Total ACB Amount After field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Total ACB Amount After or null.
    */
   public final String getTotalACBAmtAfter()
   {
      return _TotalACBAmtAfter;
   }
	
   /**
    * Gets the Total ACB Amount After field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Total ACB Amount After or the specified default value.
    */
   public final String getTotalACBAmtAfter( String defaultValue )
   {
      return _TotalACBAmtAfter == null ? defaultValue : _TotalACBAmtAfter;
   }
                  
   /**
    * Gets the Foreign Allowed Amount After field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Foreign Allowed Amount After or null.
    */
   public final String getFrgnAllowedAmtAfter()
   {
      return _FrgnAllowedAmtAfter;
   }
	
   /**
    * Gets the Foreign Allowed Amount After field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Foreign Allowed Amount After or the specified default value.
    */
   public final String getFrgnAllowedAmtAfter( String defaultValue )
   {
      return _FrgnAllowedAmtAfter == null ? defaultValue : _FrgnAllowedAmtAfter;
   }
                  
   /**
    * Gets the Foreign Allowed Percent After field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Foreign Allowed Percent After or null.
    */
   public final String getFrgnAllowedPrcntAfter()
   {
      return _FrgnAllowedPrcntAfter;
   }
	
   /**
    * Gets the Foreign Allowed Percent After field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Foreign Allowed Percent After or the specified default value.
    */
   public final String getFrgnAllowedPrcntAfter( String defaultValue )
   {
      return _FrgnAllowedPrcntAfter == null ? defaultValue : _FrgnAllowedPrcntAfter;
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
      _DomesticACBAmtBefore = responseBuffer.decodeString(responseBuffer.getNextField());
      _DomesticPrcntBefore = responseBuffer.decodeString(responseBuffer.getNextField());
      _DomesticACBAmtAfter = responseBuffer.decodeString(responseBuffer.getNextField());
      _DomesticPrcntAfter = responseBuffer.decodeString(responseBuffer.getNextField());
      _FrgnACBAmtBefore = responseBuffer.decodeString(responseBuffer.getNextField());
      _FrgnPrcntBefore = responseBuffer.decodeString(responseBuffer.getNextField());
      _FrgnACBAmtAfter = responseBuffer.decodeString(responseBuffer.getNextField());
      _FrgnPrcntAfter = responseBuffer.decodeString(responseBuffer.getNextField());
      _FrgnAllowedPrcntBefore = responseBuffer.decodeString(responseBuffer.getNextField());
      _FrgnAllowedAmtBefore = responseBuffer.decodeString(responseBuffer.getNextField());
      _Rate = responseBuffer.decodeString(responseBuffer.getNextField());
      _TotalACBAmtBefore = responseBuffer.decodeString(responseBuffer.getNextField());
      _TotalACBAmtAfter = responseBuffer.decodeString(responseBuffer.getNextField());
      _FrgnAllowedAmtAfter = responseBuffer.decodeString(responseBuffer.getNextField());
      _FrgnAllowedPrcntAfter = responseBuffer.decodeString(responseBuffer.getNextField());
                  

   }

}
      
