// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * FireFighter ID Validation request.
 * For additional view information see <A HREF="../../../../viewspecs/FFIDValidn.doc">FFIDValidn.doc</A>.
 * 
 * @author RTS Generated
 */
public class FFIDValidnRequest extends IFastRequest implements Serializable
{

   /**
    * SessionId member variable.
    */
   private String _SessionId = "";
            
   /**
    * UserId member variable.
    */
   private String _User_Id = "";
            
   /**
    * LanguageCode member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * CompanyId member variable.
    */
   private String _CompanyId = "";
            
            
            
   /**
    * Personal Firefighter ID member variable.
    */
   private String _FFId = "";
            
   /**
    * Personal Firefighter Password member variable.
    */
   private String _FFPassword = "";
            
   /**
    * PTS Number member variable.
    */
   private Integer _PTSNum = null;
            
   /**
    * Description Line 1 member variable.
    */
   private String _Description1 = "";
            
   /**
    * Description Line 2 member variable.
    */
   private String _Description2 = "";
            
   /**
    * Description  Line 3 member variable.
    */
   private String _Description3 = "";
            
   /**
    * Description Line 4 member variable.
    */
   private String _Description4 = "";
            

   /**
    * Constructs the FFIDValidnRequest object.
    * 
    */
   FFIDValidnRequest()
   {
      super ( 276 );
   }

   /**
    * Constructs the FFIDValidnRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   FFIDValidnRequest( String hostEncoding )
   {
      super ( 276, hostEncoding );
   }

   /**
    * Sets the SessionId field for the request.
    * 
    * @param value  Value that the SessionId will be set to.
    */
   public final void setSessionId( String value )
   {
      assertUnsent();
      _SessionId = value;
   }
	
   /**
    * Sets the UserId field for the request.
    * 
    * @param value  Value that the UserId will be set to.
    */
   public final void setUser_Id( String value )
   {
      assertUnsent();
      _User_Id = value;
   }
	
   /**
    * Sets the LanguageCode field for the request.
    * 
    * @param value  Value that the LanguageCode will be set to.
    */
   public final void setLanguageCode( String value )
   {
      assertUnsent();
      _LanguageCode = value;
   }
	
   /**
    * Sets the CompanyId field for the request.
    * 
    * @param value  Value that the CompanyId will be set to.
    */
   public final void setCompanyId( String value )
   {
      assertUnsent();
      _CompanyId = value;
   }
	
   /**
    * Sets the Personal Firefighter ID field for the request.
    * 
    * @param value  Value that the Personal Firefighter ID will be set to.
    */
   public final void setFFId( String value )
   {
      assertUnsent();
      _FFId = value;
   }
	
   /**
    * Sets the Personal Firefighter Password field for the request.
    * 
    * @param value  Value that the Personal Firefighter Password will be set to.
    */
   public final void setFFPassword( String value )
   {
      assertUnsent();
      _FFPassword = value;
   }
	
   /**
    * Sets the PTS Number field for the request.
    * 
    * @param value  Value that the PTS Number will be set to.
    */
   public final void setPTSNum( Integer value )
   {
      assertUnsent();
      _PTSNum = value;
   }
	
   /**
    * Sets the Description Line 1 field for the request.
    * 
    * @param value  Value that the Description Line 1 will be set to.
    */
   public final void setDescription1( String value )
   {
      assertUnsent();
      _Description1 = value;
   }
	
   /**
    * Sets the Description Line 2 field for the request.
    * 
    * @param value  Value that the Description Line 2 will be set to.
    */
   public final void setDescription2( String value )
   {
      assertUnsent();
      _Description2 = value;
   }
	
   /**
    * Sets the Description  Line 3 field for the request.
    * 
    * @param value  Value that the Description  Line 3 will be set to.
    */
   public final void setDescription3( String value )
   {
      assertUnsent();
      _Description3 = value;
   }
	
   /**
    * Sets the Description Line 4 field for the request.
    * 
    * @param value  Value that the Description Line 4 will be set to.
    */
   public final void setDescription4( String value )
   {
      assertUnsent();
      _Description4 = value;
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
      requestBuffer.appendField( _FFId );
      requestBuffer.appendField( _FFPassword );
      requestBuffer.appendField( _PTSNum );
      requestBuffer.appendField( _Description1 );
      requestBuffer.appendField( _Description2 );
      requestBuffer.appendField( _Description3 );
      requestBuffer.appendField( _Description4 );
   }

}

