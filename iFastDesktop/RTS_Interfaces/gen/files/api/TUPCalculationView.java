
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * TUP Calculation view.
 * For additional view information see <A HREF="../../../../viewspecs/TUPCalculation.doc">TUPCalculation.doc</A>.
 * 
 * @author RTS Generated
 */
public class TUPCalculationView extends IFastView implements Serializable
{

   /**
    * Indicates if there is full money out trade in the system or trade closing account member variable.
    */
   private Boolean _FullMoneyOutFound = null;
   
   /**
    * Indicates if TUP tolerance is exceedeed member variable.
    */
   private Boolean _ToleranceAmtExceeded = null;
   
   /**
    * Calculated TUP amount not including inputted money out trade member variable.
    */
   private String _TUPUnits = null;
   
   /**
    * Tolerance rate defined in Fund-Detl and GC member variable.
    */
   private String _TUPToleranceRate = null;
   
   /**
    * Tolerance units member variable.
    */
   private String _TUPToleranceUnits = null;
   
   /**
    * Estimated units of pending trade member variable.
    */
   private String _TradeEstimatedUnits = null;
   
   /**
    * TUPUnits – EstUnits member variable.
    */
   private String _TUPOversellUnits = null;
   
   /**
    * Indicates if TUP is in oversell position member variable.
    */
   private Boolean _TUPOversell = null;
   
   /**
    * Indicates if TUP calculation is successful member variable.
    */
   private Boolean _TUPCalcFailed = null;
   

   /**
    * Constructs the TUPCalculationView object.
    * 
    */
   public TUPCalculationView()
   {
      super ( new TUPCalculationRequest() );
   }

   /**
    * Constructs the TUPCalculationView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public TUPCalculationView( String hostEncoding )
   {
      super ( new TUPCalculationRequest( hostEncoding ) );
   }

   /**
    * Gets the TUPCalculationRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The TUPCalculationRequest object.
    */
   public final TUPCalculationRequest getRequest()
   {
      return (TUPCalculationRequest)getIFastRequest();
   }
        
   /**
    * Gets the Indicates if there is full money out trade in the system or trade closing account field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Indicates if there is full money out trade in the system or trade closing account or null.
    */
   public final Boolean getFullMoneyOutFound()
   {
      return _FullMoneyOutFound;
   }
	
   /**
    * Gets the Indicates if there is full money out trade in the system or trade closing account field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Indicates if there is full money out trade in the system or trade closing account or the specified default value.
    */
   public final boolean getFullMoneyOutFound( boolean defaultValue )
   {
      return _FullMoneyOutFound == null ? defaultValue : _FullMoneyOutFound.booleanValue();
   }
                  
   /**
    * Gets the Indicates if TUP tolerance is exceedeed field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Indicates if TUP tolerance is exceedeed or null.
    */
   public final Boolean getToleranceAmtExceeded()
   {
      return _ToleranceAmtExceeded;
   }
	
   /**
    * Gets the Indicates if TUP tolerance is exceedeed field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Indicates if TUP tolerance is exceedeed or the specified default value.
    */
   public final boolean getToleranceAmtExceeded( boolean defaultValue )
   {
      return _ToleranceAmtExceeded == null ? defaultValue : _ToleranceAmtExceeded.booleanValue();
   }
                  
   /**
    * Gets the Calculated TUP amount not including inputted money out trade field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Calculated TUP amount not including inputted money out trade or null.
    */
   public final String getTUPUnits()
   {
      return _TUPUnits;
   }
	
   /**
    * Gets the Calculated TUP amount not including inputted money out trade field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Calculated TUP amount not including inputted money out trade or the specified default value.
    */
   public final String getTUPUnits( String defaultValue )
   {
      return _TUPUnits == null ? defaultValue : _TUPUnits;
   }
                  
   /**
    * Gets the Tolerance rate defined in Fund-Detl and GC field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Tolerance rate defined in Fund-Detl and GC or null.
    */
   public final String getTUPToleranceRate()
   {
      return _TUPToleranceRate;
   }
	
   /**
    * Gets the Tolerance rate defined in Fund-Detl and GC field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tolerance rate defined in Fund-Detl and GC or the specified default value.
    */
   public final String getTUPToleranceRate( String defaultValue )
   {
      return _TUPToleranceRate == null ? defaultValue : _TUPToleranceRate;
   }
                  
   /**
    * Gets the Tolerance units field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Tolerance units or null.
    */
   public final String getTUPToleranceUnits()
   {
      return _TUPToleranceUnits;
   }
	
   /**
    * Gets the Tolerance units field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tolerance units or the specified default value.
    */
   public final String getTUPToleranceUnits( String defaultValue )
   {
      return _TUPToleranceUnits == null ? defaultValue : _TUPToleranceUnits;
   }
                  
   /**
    * Gets the Estimated units of pending trade field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Estimated units of pending trade or null.
    */
   public final String getTradeEstimatedUnits()
   {
      return _TradeEstimatedUnits;
   }
	
   /**
    * Gets the Estimated units of pending trade field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Estimated units of pending trade or the specified default value.
    */
   public final String getTradeEstimatedUnits( String defaultValue )
   {
      return _TradeEstimatedUnits == null ? defaultValue : _TradeEstimatedUnits;
   }
                  
   /**
    * Gets the TUPUnits – EstUnits field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the TUPUnits – EstUnits or null.
    */
   public final String getTUPOversellUnits()
   {
      return _TUPOversellUnits;
   }
	
   /**
    * Gets the TUPUnits – EstUnits field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the TUPUnits – EstUnits or the specified default value.
    */
   public final String getTUPOversellUnits( String defaultValue )
   {
      return _TUPOversellUnits == null ? defaultValue : _TUPOversellUnits;
   }
                  
   /**
    * Gets the Indicates if TUP is in oversell position field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Indicates if TUP is in oversell position or null.
    */
   public final Boolean getTUPOversell()
   {
      return _TUPOversell;
   }
	
   /**
    * Gets the Indicates if TUP is in oversell position field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Indicates if TUP is in oversell position or the specified default value.
    */
   public final boolean getTUPOversell( boolean defaultValue )
   {
      return _TUPOversell == null ? defaultValue : _TUPOversell.booleanValue();
   }
                  
   /**
    * Gets the Indicates if TUP calculation is successful field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Indicates if TUP calculation is successful or null.
    */
   public final Boolean getTUPCalcFailed()
   {
      return _TUPCalcFailed;
   }
	
   /**
    * Gets the Indicates if TUP calculation is successful field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Indicates if TUP calculation is successful or the specified default value.
    */
   public final boolean getTUPCalcFailed( boolean defaultValue )
   {
      return _TUPCalcFailed == null ? defaultValue : _TUPCalcFailed.booleanValue();
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
      _FullMoneyOutFound = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _ToleranceAmtExceeded = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _TUPUnits = responseBuffer.decodeString(responseBuffer.getNextField());
      _TUPToleranceRate = responseBuffer.decodeString(responseBuffer.getNextField());
      _TUPToleranceUnits = responseBuffer.decodeString(responseBuffer.getNextField());
      _TradeEstimatedUnits = responseBuffer.decodeString(responseBuffer.getNextField());
      _TUPOversellUnits = responseBuffer.decodeString(responseBuffer.getNextField());
      _TUPOversell = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _TUPCalcFailed = responseBuffer.decodeBoolean(responseBuffer.getNextField());
                  

   }

}
      
