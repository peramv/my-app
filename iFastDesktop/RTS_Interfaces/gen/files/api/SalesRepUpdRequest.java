// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * SalesRep Update request.
 * For additional view information see <A HREF="../../../../viewspecs/SalesRepUpd.doc">SalesRepUpd.doc</A>.
 * 
 * @author RTS Generated
 */
public class SalesRepUpdRequest extends IFastRequest implements Serializable
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
    * CompanyId member variable.
    */
   private String _CompanyId = "";
            
   /**
    * Language member variable.
    */
   private String _LanguageCode = "";
            
            
            
   /**
    * BrokerCode member variable.
    */
   private String _BrokerCode = "";
            
   /**
    * Sales Rep Code member variable.
    */
   private String _SlsRepCode = "";
            
   /**
    * Sales Rep Email member variable.
    */
   private String _SlsRepEmail = "";
            
   /**
    * Sales Rep Phone Number member variable.
    */
   private String _SlsRepPhone = "";
            
   /**
    * Sales Rep Country Code member variable.
    */
   private String _SlsRepCntry = "";
            
   /**
    * Sales Rep Area Code member variable.
    */
   private String _SlsRepArea = "";
            

   /**
    * Constructs the SalesRepUpdRequest object.
    * 
    */
   SalesRepUpdRequest()
   {
      super ( 191 );
   }

   /**
    * Constructs the SalesRepUpdRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   SalesRepUpdRequest( String hostEncoding )
   {
      super ( 191, hostEncoding );
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
    * Sets the Language field for the request.
    * 
    * @param value  Value that the Language will be set to.
    */
   public final void setLanguageCode( String value )
   {
      assertUnsent();
      _LanguageCode = value;
   }
	
   /**
    * Sets the BrokerCode field for the request.
    * 
    * @param value  Value that the BrokerCode will be set to.
    */
   public final void setBrokerCode( String value )
   {
      assertUnsent();
      _BrokerCode = value;
   }
	
   /**
    * Sets the Sales Rep Code field for the request.
    * 
    * @param value  Value that the Sales Rep Code will be set to.
    */
   public final void setSlsRepCode( String value )
   {
      assertUnsent();
      _SlsRepCode = value;
   }
	
   /**
    * Sets the Sales Rep Email field for the request.
    * 
    * @param value  Value that the Sales Rep Email will be set to.
    */
   public final void setSlsRepEmail( String value )
   {
      assertUnsent();
      _SlsRepEmail = value;
   }
	
   /**
    * Sets the Sales Rep Phone Number field for the request.
    * 
    * @param value  Value that the Sales Rep Phone Number will be set to.
    */
   public final void setSlsRepPhone( String value )
   {
      assertUnsent();
      _SlsRepPhone = value;
   }
	
   /**
    * Sets the Sales Rep Country Code field for the request.
    * 
    * @param value  Value that the Sales Rep Country Code will be set to.
    */
   public final void setSlsRepCntry( String value )
   {
      assertUnsent();
      _SlsRepCntry = value;
   }
	
   /**
    * Sets the Sales Rep Area Code field for the request.
    * 
    * @param value  Value that the Sales Rep Area Code will be set to.
    */
   public final void setSlsRepArea( String value )
   {
      assertUnsent();
      _SlsRepArea = value;
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
      requestBuffer.appendField( _CompanyId );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _BrokerCode );
      requestBuffer.appendField( _SlsRepCode );
      requestBuffer.appendField( _SlsRepEmail );
      requestBuffer.appendField( _SlsRepPhone );
      requestBuffer.appendField( _SlsRepCntry );
      requestBuffer.appendField( _SlsRepArea );
   }

}

