
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * AMS Configuration Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/AMSConfigInq.doc">AMSConfigInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class AMSConfigInqView extends IFastView implements Serializable
{

   /**
    * DefaultRebalFreq member variable.
    */
   private String _DefaultRebalFreq = null;
   
   /**
    * DefaultRoundFund member variable.
    */
   private String _DefaultRoundFund = null;
   
   /**
    * DefaultRoundClass member variable.
    */
   private String _DefaultRoundClass = null;
   
   /**
    * UpdAMSOnNewAcct member variable.
    */
   private Boolean _UpdAMSOnNewAcct = null;
   
   /**
    * DefaultAllocOveride member variable.
    */
   private Boolean _DefaultAllocOveride = null;
   
   /**
    * PACSWPover member variable.
    */
   private Boolean _PACSWPover = null;
   
   /**
    * LastNextRebAppl member variable.
    */
   private Boolean _LastNextRebAppl = null;
   

   /**
    * Constructs the AMSConfigInqView object.
    * 
    */
   public AMSConfigInqView()
   {
      super ( new AMSConfigInqRequest() );
   }

   /**
    * Constructs the AMSConfigInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AMSConfigInqView( String hostEncoding )
   {
      super ( new AMSConfigInqRequest( hostEncoding ) );
   }

   /**
    * Gets the AMSConfigInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AMSConfigInqRequest object.
    */
   public final AMSConfigInqRequest getRequest()
   {
      return (AMSConfigInqRequest)getIFastRequest();
   }
        
   /**
    * Gets the DefaultRebalFreq field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the DefaultRebalFreq or null.
    */
   public final String getDefaultRebalFreq()
   {
      return _DefaultRebalFreq;
   }
	
   /**
    * Gets the DefaultRebalFreq field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the DefaultRebalFreq or the specified default value.
    */
   public final String getDefaultRebalFreq( String defaultValue )
   {
      return _DefaultRebalFreq == null ? defaultValue : _DefaultRebalFreq;
   }
                  
   /**
    * Gets the DefaultRoundFund field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the DefaultRoundFund or null.
    */
   public final String getDefaultRoundFund()
   {
      return _DefaultRoundFund;
   }
	
   /**
    * Gets the DefaultRoundFund field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the DefaultRoundFund or the specified default value.
    */
   public final String getDefaultRoundFund( String defaultValue )
   {
      return _DefaultRoundFund == null ? defaultValue : _DefaultRoundFund;
   }
                  
   /**
    * Gets the DefaultRoundClass field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the DefaultRoundClass or null.
    */
   public final String getDefaultRoundClass()
   {
      return _DefaultRoundClass;
   }
	
   /**
    * Gets the DefaultRoundClass field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the DefaultRoundClass or the specified default value.
    */
   public final String getDefaultRoundClass( String defaultValue )
   {
      return _DefaultRoundClass == null ? defaultValue : _DefaultRoundClass;
   }
                  
   /**
    * Gets the UpdAMSOnNewAcct field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the UpdAMSOnNewAcct or null.
    */
   public final Boolean getUpdAMSOnNewAcct()
   {
      return _UpdAMSOnNewAcct;
   }
	
   /**
    * Gets the UpdAMSOnNewAcct field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the UpdAMSOnNewAcct or the specified default value.
    */
   public final boolean getUpdAMSOnNewAcct( boolean defaultValue )
   {
      return _UpdAMSOnNewAcct == null ? defaultValue : _UpdAMSOnNewAcct.booleanValue();
   }
                  
   /**
    * Gets the DefaultAllocOveride field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the DefaultAllocOveride or null.
    */
   public final Boolean getDefaultAllocOveride()
   {
      return _DefaultAllocOveride;
   }
	
   /**
    * Gets the DefaultAllocOveride field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the DefaultAllocOveride or the specified default value.
    */
   public final boolean getDefaultAllocOveride( boolean defaultValue )
   {
      return _DefaultAllocOveride == null ? defaultValue : _DefaultAllocOveride.booleanValue();
   }
                  
   /**
    * Gets the PACSWPover field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the PACSWPover or null.
    */
   public final Boolean getPACSWPover()
   {
      return _PACSWPover;
   }
	
   /**
    * Gets the PACSWPover field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PACSWPover or the specified default value.
    */
   public final boolean getPACSWPover( boolean defaultValue )
   {
      return _PACSWPover == null ? defaultValue : _PACSWPover.booleanValue();
   }
                  
   /**
    * Gets the LastNextRebAppl field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the LastNextRebAppl or null.
    */
   public final Boolean getLastNextRebAppl()
   {
      return _LastNextRebAppl;
   }
	
   /**
    * Gets the LastNextRebAppl field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the LastNextRebAppl or the specified default value.
    */
   public final boolean getLastNextRebAppl( boolean defaultValue )
   {
      return _LastNextRebAppl == null ? defaultValue : _LastNextRebAppl.booleanValue();
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
      _DefaultRebalFreq = responseBuffer.decodeString(responseBuffer.getNextField());
      _DefaultRoundFund = responseBuffer.decodeString(responseBuffer.getNextField());
      _DefaultRoundClass = responseBuffer.decodeString(responseBuffer.getNextField());
      _UpdAMSOnNewAcct = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _DefaultAllocOveride = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _PACSWPover = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _LastNextRebAppl = responseBuffer.decodeBoolean(responseBuffer.getNextField());
                  

   }

}
      
