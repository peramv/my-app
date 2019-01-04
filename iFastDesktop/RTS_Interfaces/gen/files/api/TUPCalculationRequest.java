// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * TUP Calculation request.
 * For additional view information see <A HREF="../../../../viewspecs/TUPCalculation.doc">TUPCalculation.doc</A>.
 * 
 * @author RTS Generated
 */
public class TUPCalculationRequest extends IFastRequest implements Serializable
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
    * Transaction Number member variable.
    */
   private Integer _TransNum = null;
            
   /**
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * FundCode member variable.
    */
   private String _FundCode = "";
            
   /**
    * ClassCode member variable.
    */
   private String _ClassCode = "";
            
   /**
    * TransType member variable.
    */
   private String _TransType = "";
            
   /**
    * TradeDate member variable.
    */
   private Date _TradeDate = null;
            
   /**
    * SettleDate member variable.
    */
   private Date _SettleDate = null;
            
   /**
    * Amount member variable.
    */
   private String _Amount = "0";
            
   /**
    * AmountType member variable.
    */
   private String _AmountType = "";
            
   /**
    * Settle Currency member variable.
    */
   private String _SettleCurr = "";
            
   /**
    * Order Type member variable.
    */
   private Boolean _OrderType = new Boolean(false);
            
   /**
    * Transaction Id member variable.
    */
   private String _TransId = "0";
            
   /**
    * Exchange Rate member variable.
    */
   private String _ExchRate = "0";
            
   /**
    * Redemption Code member variable.
    */
   private String _RedCode = "";
            
   /**
    * Account To Number member variable.
    */
   private Integer _AccountTo = null;
            

   /**
    * Constructs the TUPCalculationRequest object.
    * 
    */
   TUPCalculationRequest()
   {
      super ( 401 );
   }

   /**
    * Constructs the TUPCalculationRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   TUPCalculationRequest( String hostEncoding )
   {
      super ( 401, hostEncoding );
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
    * Sets the Transaction Number field for the request.
    * 
    * @param value  Value that the Transaction Number will be set to.
    */
   public final void setTransNum( Integer value )
   {
      assertUnsent();
      _TransNum = value;
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
    * Sets the FundCode field for the request.
    * 
    * @param value  Value that the FundCode will be set to.
    */
   public final void setFundCode( String value )
   {
      assertUnsent();
      _FundCode = value;
   }
	
   /**
    * Sets the ClassCode field for the request.
    * 
    * @param value  Value that the ClassCode will be set to.
    */
   public final void setClassCode( String value )
   {
      assertUnsent();
      _ClassCode = value;
   }
	
   /**
    * Sets the TransType field for the request.
    * 
    * @param value  Value that the TransType will be set to.
    */
   public final void setTransType( String value )
   {
      assertUnsent();
      _TransType = value;
   }
	
   /**
    * Sets the TradeDate field for the request.
    * 
    * @param value  Value that the TradeDate will be set to.
    */
   public final void setTradeDate( Date value )
   {
      assertUnsent();
      _TradeDate = value;
   }
	
   /**
    * Sets the SettleDate field for the request.
    * 
    * @param value  Value that the SettleDate will be set to.
    */
   public final void setSettleDate( Date value )
   {
      assertUnsent();
      _SettleDate = value;
   }
	
   /**
    * Sets the Amount field for the request.
    * 
    * @param value  Value that the Amount will be set to.
    */
   public final void setAmount( String value )
   {
      assertUnsent();
      _Amount = value;
   }
	
   /**
    * Sets the AmountType field for the request.
    * 
    * @param value  Value that the AmountType will be set to.
    */
   public final void setAmountType( String value )
   {
      assertUnsent();
      _AmountType = value;
   }
	
   /**
    * Sets the Settle Currency field for the request.
    * 
    * @param value  Value that the Settle Currency will be set to.
    */
   public final void setSettleCurr( String value )
   {
      assertUnsent();
      _SettleCurr = value;
   }
	
   /**
    * Sets the Order Type field for the request.
    * 
    * @param value  Value that the Order Type will be set to.
    */
   public final void setOrderType( Boolean value )
   {
      assertUnsent();
      _OrderType = value;
   }
	
   /**
    * Sets the Transaction Id field for the request.
    * 
    * @param value  Value that the Transaction Id will be set to.
    */
   public final void setTransId( String value )
   {
      assertUnsent();
      _TransId = value;
   }
	
   /**
    * Sets the Exchange Rate field for the request.
    * 
    * @param value  Value that the Exchange Rate will be set to.
    */
   public final void setExchRate( String value )
   {
      assertUnsent();
      _ExchRate = value;
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
    * Sets the Account To Number field for the request.
    * 
    * @param value  Value that the Account To Number will be set to.
    */
   public final void setAccountTo( Integer value )
   {
      assertUnsent();
      _AccountTo = value;
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
      requestBuffer.appendField( _TransNum );
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _FundCode );
      requestBuffer.appendField( _ClassCode );
      requestBuffer.appendField( _TransType );
      requestBuffer.appendField( _TradeDate );
      requestBuffer.appendField( _SettleDate );
      requestBuffer.appendField( _Amount );
      requestBuffer.appendField( _AmountType );
      requestBuffer.appendField( _SettleCurr );
      requestBuffer.appendField( _OrderType );
      requestBuffer.appendField( _TransId );
      requestBuffer.appendField( _ExchRate );
      requestBuffer.appendField( _RedCode );
      requestBuffer.appendField( _AccountTo );
   }

}

