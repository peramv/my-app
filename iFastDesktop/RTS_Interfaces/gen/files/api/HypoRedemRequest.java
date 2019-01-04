// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Hypothetical Redemption Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/HypoRedem.doc">HypoRedem.doc</A>.
 * 
 * @author RTS Generated
 */
public class HypoRedemRequest extends IFastRequest implements Serializable
{

            
   /**
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Fund Code member variable.
    */
   private String _FundCode = "";
            
   /**
    * Class Code member variable.
    */
   private String _ClassCode = "";
            
   /**
    * Trade Date member variable.
    */
   private Date _TradeDate = null;
            
   /**
    * Gross Or Net member variable.
    */
   private Boolean _GrossOrNet = new Boolean(false);
            
   /**
    * Dollars Or Units member variable.
    */
   private String _AmountType = "";
            
   /**
    * Full Redemption member variable.
    */
   private Boolean _FullRedem = new Boolean(false);
            
   /**
    * Redemption Code member variable.
    */
   private String _RedCode = "";
            
   /**
    * Redemption Amount Or Units member variable.
    */
   private String _Amount = "0";
            
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
    * FundCom Amount Types member variable.
    */
   private String _FCAmountType = "";
            
   /**
    * Baycom member variable.
    */
   private String _Baycom = "";
            

   /**
    * Constructs the HypoRedemRequest object.
    * 
    */
   HypoRedemRequest()
   {
      super ( 137 );
   }

   /**
    * Constructs the HypoRedemRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   HypoRedemRequest( String hostEncoding )
   {
      super ( 137, hostEncoding );
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
    * Sets the Gross Or Net field for the request.
    * 
    * @param value  Value that the Gross Or Net will be set to.
    */
   public final void setGrossOrNet( Boolean value )
   {
      assertUnsent();
      _GrossOrNet = value;
   }
	
   /**
    * Sets the Dollars Or Units field for the request.
    * 
    * @param value  Value that the Dollars Or Units will be set to.
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
   public final void setFullRedem( Boolean value )
   {
      assertUnsent();
      _FullRedem = value;
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
    * Sets the FundCom Amount Types field for the request.
    * 
    * @param value  Value that the FundCom Amount Types will be set to.
    */
   public final void setFCAmountType( String value )
   {
      assertUnsent();
      _FCAmountType = value;
   }
	
   /**
    * Sets the Baycom field for the request.
    * 
    * @param value  Value that the Baycom will be set to.
    */
   public final void setBaycom( String value )
   {
      assertUnsent();
      _Baycom = value;
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
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _FundCode );
      requestBuffer.appendField( _ClassCode );
      requestBuffer.appendField( _TradeDate );
      requestBuffer.appendField( _GrossOrNet );
      requestBuffer.appendField( _AmountType );
      requestBuffer.appendField( _FullRedem );
      requestBuffer.appendField( _RedCode );
      requestBuffer.appendField( _Amount );
      requestBuffer.appendField( _SessionID );
      requestBuffer.appendField( _User_ID );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyID );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _FCAmountType );
      requestBuffer.appendField( _Baycom );
   }

}

