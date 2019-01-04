// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * RRIF Unused Amount CalCulate request.
 * For additional view information see <A HREF="../../../../viewspecs/RRIFUnusedMax.doc">RRIFUnusedMax.doc</A>.
 * 
 * @author RTS Generated
 */
public class RRIFUnusedMaxRequest extends IFastRequest implements Serializable
{

   /**
    * Session Id member variable.
    */
   private String _SessionId = "";
            
   /**
    * User Id member variable.
    */
   private String _User_Id = "";
            
   /**
    * Language Code member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * Company Id member variable.
    */
   private String _CompanyId = "";
            
            
            
   /**
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * EffectiveDate member variable.
    */
   private Date _EffectiveDate = null;
            
   /**
    * RIFId member variable.
    */
   private Integer _RIFId = null;
            
   /**
    * OverrideUnusedMax member variable.
    */
   private Boolean _OverrideUnusedMax = new Boolean(false);
            
   /**
    * OverrideMndAmt member variable.
    */
   private String _OverrideMndAmt = "0";
            

   /**
    * Constructs the RRIFUnusedMaxRequest object.
    * 
    */
   RRIFUnusedMaxRequest()
   {
      super ( 375 );
   }

   /**
    * Constructs the RRIFUnusedMaxRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   RRIFUnusedMaxRequest( String hostEncoding )
   {
      super ( 375, hostEncoding );
   }

   /**
    * Sets the Session Id field for the request.
    * 
    * @param value  Value that the Session Id will be set to.
    */
   public final void setSessionId( String value )
   {
      assertUnsent();
      _SessionId = value;
   }
	
   /**
    * Sets the User Id field for the request.
    * 
    * @param value  Value that the User Id will be set to.
    */
   public final void setUser_Id( String value )
   {
      assertUnsent();
      _User_Id = value;
   }
	
   /**
    * Sets the Language Code field for the request.
    * 
    * @param value  Value that the Language Code will be set to.
    */
   public final void setLanguageCode( String value )
   {
      assertUnsent();
      _LanguageCode = value;
   }
	
   /**
    * Sets the Company Id field for the request.
    * 
    * @param value  Value that the Company Id will be set to.
    */
   public final void setCompanyId( String value )
   {
      assertUnsent();
      _CompanyId = value;
   }
	
   /**
    * Sets the Account Number field for the request.
    * 
    * @param value  Value that the Account Number will be set to.
    */
   public final void setAccountNum( String value )
   {
      assertUnsent();
      _AccountNum = value;
   }
	
   /**
    * Sets the EffectiveDate field for the request.
    * 
    * @param value  Value that the EffectiveDate will be set to.
    */
   public final void setEffectiveDate( Date value )
   {
      assertUnsent();
      _EffectiveDate = value;
   }
	
   /**
    * Sets the RIFId field for the request.
    * 
    * @param value  Value that the RIFId will be set to.
    */
   public final void setRIFId( Integer value )
   {
      assertUnsent();
      _RIFId = value;
   }
	
   /**
    * Sets the OverrideUnusedMax field for the request.
    * 
    * @param value  Value that the OverrideUnusedMax will be set to.
    */
   public final void setOverrideUnusedMax( Boolean value )
   {
      assertUnsent();
      _OverrideUnusedMax = value;
   }
	
   /**
    * Sets the OverrideMndAmt field for the request.
    * 
    * @param value  Value that the OverrideMndAmt will be set to.
    */
   public final void setOverrideMndAmt( String value )
   {
      assertUnsent();
      _OverrideMndAmt = value;
   }
	
   /**
    * Implements the abstract base method to encode
    * the host formatted request.
    * 
    * @param transaction
    *               Host formatted request object.
    */
   protected final void encodeFields( RTSRequestEncodeBuffer requestBuffer ) throws UnsupportedEncodingException
   {
      requestBuffer.appendField( _SessionId );
      requestBuffer.appendField( _User_Id );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyId );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _EffectiveDate );
      requestBuffer.appendField( _RIFId );
      requestBuffer.appendField( _OverrideUnusedMax );
      requestBuffer.appendField( _OverrideMndAmt );
   }

}

