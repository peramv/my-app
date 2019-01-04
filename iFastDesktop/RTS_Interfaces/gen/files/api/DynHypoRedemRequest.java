// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Dynamic Hypothetical Redemption Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/DynHypoRedem.doc">DynHypoRedem.doc</A>.
 * 
 * @author RTS Generated
 */
public class DynHypoRedemRequest extends IFastRequest implements Serializable
{

            
   /**
    * Session Id member variable.
    */
   private String _SessionID = "";
            
   /**
    * User Id member variable.
    */
   private String _User_ID = "";
            
   /**
    * Language Code member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * Company Id member variable.
    */
   private String _CompanyID = "";
            
            
            
   /**
    * AccountNum member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Trade Date member variable.
    */
   private Date _TradeDate = null;
            
   /**
    * Gross or Net member variable.
    */
   private Boolean _GrossOrnet = new Boolean(false);
            
   /**
    * Dollars or Units member variable.
    */
   private String _AmountType = "";
            
   /**
    * Full Redemption member variable.
    */
   private Boolean _FullRedeem = new Boolean(false);
            
   /**
    * Redemption Code member variable.
    */
   private String _RedCode = "";
            
   /**
    * Fund Code member variable.
    */
   private String _FundCode = "";
            
   /**
    * Class Code member variable.
    */
   private String _ClassCode = "";
            
   /**
    * Redemption Amount Or Units member variable.
    */
   private String _Amount = "0";
            

   /**
    * Constructs the DynHypoRedemRequest object.
    * 
    */
   DynHypoRedemRequest()
   {
      super ( 303 );
   }

   /**
    * Constructs the DynHypoRedemRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   DynHypoRedemRequest( String hostEncoding )
   {
      super ( 303, hostEncoding );
   }

   /**
    * Sets the Session Id field for the request.
    * 
    * @param value  Value that the Session Id will be set to.
    */
   public final void setSessionID( String value )
   {
      assertUnsent();
      _SessionID = value;
   }
	
   /**
    * Sets the User Id field for the request.
    * 
    * @param value  Value that the User Id will be set to.
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
    * Sets the Company Id field for the request.
    * 
    * @param value  Value that the Company Id will be set to.
    */
   public final void setCompanyID( String value )
   {
      assertUnsent();
      _CompanyID = value;
   }
	
   /**
    * Sets the AccountNum field for the request.
    * 
    * @param value  Value that the AccountNum will be set to.
    */
   public final void setAccountNum( String value )
   {
      assertUnsent();
      _AccountNum = value;
   }
	
   /**
    * Sets the Trade Date field for the request.
    * 
    * @param value  Value that the Trade Date will be set to.
    */
   public final void setTradeDate( Date value )
   {
      assertUnsent();
      _TradeDate = value;
   }
	
   /**
    * Sets the Gross or Net field for the request.
    * 
    * @param value  Value that the Gross or Net will be set to.
    */
   public final void setGrossOrnet( Boolean value )
   {
      assertUnsent();
      _GrossOrnet = value;
   }
	
   /**
    * Sets the Dollars or Units field for the request.
    * 
    * @param value  Value that the Dollars or Units will be set to.
    */
   public final void setAmountType( String value )
   {
      assertUnsent();
      _AmountType = value;
   }
	
   /**
    * Sets the Full Redemption field for the request.
    * 
    * @param value  Value that the Full Redemption will be set to.
    */
   public final void setFullRedeem( Boolean value )
   {
      assertUnsent();
      _FullRedeem = value;
   }
	
   /**
    * Sets the Redemption Code field for the request.
    * 
    * @param value  Value that the Redemption Code will be set to.
    */
   public final void setRedCode( String value )
   {
      assertUnsent();
      _RedCode = value;
   }
	
   /**
    * Sets the Fund Code field for the request.
    * 
    * @param value  Value that the Fund Code will be set to.
    */
   public final void setFundCode( String value )
   {
      assertUnsent();
      _FundCode = value;
   }
	
   /**
    * Sets the Class Code field for the request.
    * 
    * @param value  Value that the Class Code will be set to.
    */
   public final void setClassCode( String value )
   {
      assertUnsent();
      _ClassCode = value;
   }
	
   /**
    * Sets the Redemption Amount Or Units field for the request.
    * 
    * @param value  Value that the Redemption Amount Or Units will be set to.
    */
   public final void setAmount( String value )
   {
      assertUnsent();
      _Amount = value;
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
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( _SessionID );
      requestBuffer.appendField( _User_ID );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyID );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _TradeDate );
      requestBuffer.appendField( _GrossOrnet );
      requestBuffer.appendField( _AmountType );
      requestBuffer.appendField( _FullRedeem );
      requestBuffer.appendField( _RedCode );
      requestBuffer.appendField( _FundCode );
      requestBuffer.appendField( _ClassCode );
      requestBuffer.appendField( _Amount );
   }

}

