// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * EUSD Override Maintenance request.
 * For additional view information see <A HREF="../../../../viewspecs/EUSDOvMaint.doc">EUSDOvMaint.doc</A>.
 * 
 * @author RTS Generated
 */
public class EUSDOvMaintRequest extends IFastRequest implements Serializable
{

   /**
    * Session ID member variable.
    */
   private String _SessionID = "";
            
   /**
    * User ID member variable.
    */
   private String _User_ID = "";
            
   /**
    * Language Code member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * Company ID member variable.
    */
   private String _CompanyID = "";
            
            
            
   /**
    * Transaction ID member variable.
    */
   private String _TransID = "0";
            
   /**
    * Average Cost Per Unit member variable.
    */
   private String _Cost = "0";
            
   /**
    * Average TIS Per Unit member variable.
    */
   private String _TIS = "0";
            
   /**
    * EUSDOverride Version Number member variable.
    */
   private Integer _EUSDOverrideVer = null;
            
   /**
    * Cost Type member variable.
    */
   private String _CostType = "";
            
   /**
    * TIS Type member variable.
    */
   private String _TISType = "";
            

   /**
    * Constructs the EUSDOvMaintRequest object.
    * 
    */
   EUSDOvMaintRequest()
   {
      super ( 358 );
   }

   /**
    * Constructs the EUSDOvMaintRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   EUSDOvMaintRequest( String hostEncoding )
   {
      super ( 358, hostEncoding );
   }

   /**
    * Sets the Session ID field for the request.
    * 
    * @param value  Value that the Session ID will be set to.
    */
   public final void setSessionID( String value )
   {
      assertUnsent();
      _SessionID = value;
   }
	
   /**
    * Sets the User ID field for the request.
    * 
    * @param value  Value that the User ID will be set to.
    */
   public final void setUser_ID( String value )
   {
      assertUnsent();
      _User_ID = value;
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
    * Sets the Company ID field for the request.
    * 
    * @param value  Value that the Company ID will be set to.
    */
   public final void setCompanyID( String value )
   {
      assertUnsent();
      _CompanyID = value;
   }
	
   /**
    * Sets the Transaction ID field for the request.
    * 
    * @param value  Value that the Transaction ID will be set to.
    */
   public final void setTransID( String value )
   {
      assertUnsent();
      _TransID = value;
   }
	
   /**
    * Sets the Average Cost Per Unit field for the request.
    * 
    * @param value  Value that the Average Cost Per Unit will be set to.
    */
   public final void setCost( String value )
   {
      assertUnsent();
      _Cost = value;
   }
	
   /**
    * Sets the Average TIS Per Unit field for the request.
    * 
    * @param value  Value that the Average TIS Per Unit will be set to.
    */
   public final void setTIS( String value )
   {
      assertUnsent();
      _TIS = value;
   }
	
   /**
    * Sets the EUSDOverride Version Number field for the request.
    * 
    * @param value  Value that the EUSDOverride Version Number will be set to.
    */
   public final void setEUSDOverrideVer( Integer value )
   {
      assertUnsent();
      _EUSDOverrideVer = value;
   }
	
   /**
    * Sets the Cost Type field for the request.
    * 
    * @param value  Value that the Cost Type will be set to.
    */
   public final void setCostType( String value )
   {
      assertUnsent();
      _CostType = value;
   }
	
   /**
    * Sets the TIS Type field for the request.
    * 
    * @param value  Value that the TIS Type will be set to.
    */
   public final void setTISType( String value )
   {
      assertUnsent();
      _TISType = value;
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
      requestBuffer.appendField( _SessionID );
      requestBuffer.appendField( _User_ID );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyID );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _TransID );
      requestBuffer.appendField( _Cost );
      requestBuffer.appendField( _TIS );
      requestBuffer.appendField( _EUSDOverrideVer );
      requestBuffer.appendField( _CostType );
      requestBuffer.appendField( _TISType );
   }

}

