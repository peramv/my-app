// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * AFB Order Recieved Detail Update request.
 * For additional view information see <A HREF="../../../../viewspecs/AFBDetailUpd.doc">AFBDetailUpd.doc</A>.
 * 
 * @author RTS Generated
 */
public class AFBDetailUpdRequest extends IFastRequest implements Serializable
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
    * Detail Record Type member variable.
    */
   private String _RegTypeDetl = "";
            
   /**
    * Order Code member variable.
    */
   private String _OrderCode = "";
            
   /**
    * Order Type member variable.
    */
   private String _OrderType = "";
            
   /**
    * Distributor Code member variable.
    */
   private Integer _DistribCode = null;
            
   /**
    * Distributor Description member variable.
    */
   private String _DistribDesc = "";
            
   /**
    * Account Number member variable.
    */
   private String _AbAccount = "";
            
   /**
    * Alternate Account member variable.
    */
   private String _ECSubAccount = "";
            
   /**
    * Unitary Account member variable.
    */
   private String _UniAccount = "";
            
   /**
    * Currency member variable.
    */
   private String _Currency = "";
            
   /**
    * Trade Date member variable.
    */
   private String _TradeDate = "";
            
   /**
    * Settle Date member variable.
    */
   private String _SettleDate = "";
            
   /**
    * ISIN Number member variable.
    */
   private String _ISINNumber = "";
            
   /**
    * Payment Code member variable.
    */
   private String _PaymentCode = "";
            
   /**
    * Charge member variable.
    */
   private String _Charge = "0";
            
   /**
    * Shares member variable.
    */
   private String _Shares = "0";
            
   /**
    * Client Name member variable.
    */
   private String _ClientName = "";
            
   /**
    * Correspondent Bank member variable.
    */
   private String _CorrespBank = "";
            
   /**
    * Mgmt Fund Company Code member variable.
    */
   private String _FundCodAgCo = "";
            
   /**
    * Conf. Trade Date member variable.
    */
   private String _ConTradedate = "";
            
   /**
    * Conf. Settle Date member variable.
    */
   private String _ConSettleDate = "";
            
   /**
    * Conf. Charge member variable.
    */
   private String _ConCharge = "0";
            
   /**
    * Conf. Shares member variable.
    */
   private String _ConShares = "0";
            
   /**
    * Liquidation Value member variable.
    */
   private String _LV = "0";
            
   /**
    * Designation member variable.
    */
   private String _Designation = "";
            
   /**
    * Fund Commission member variable.
    */
   private String _FundCom = "0";
            
   /**
    * Gross Amount member variable.
    */
   private String _ConGrossCharge = "0";
            
   /**
    * Liquidation Value member variable.
    */
   private String _LVApplied = "0";
            
   /**
    * Order Code 2 member variable.
    */
   private String _OrderCode2 = "";
            
   /**
    * Exchange Rate member variable.
    */
   private String _ExchRate = "0";
            
   /**
    * Switch Commission member variable.
    */
   private String _SwitchCom = "0";
            
   /**
    * Agency Commission member variable.
    */
   private String _AgCoCom = "0";
            
   /**
    * NetworkID member variable.
    */
   private String _NetworkID = "";
            
   /**
    * OrdeFileName member variable.
    */
   private String _OrderFileName = "";
            

   /**
    * Constructs the AFBDetailUpdRequest object.
    * 
    */
   AFBDetailUpdRequest()
   {
      super ( 278 );
   }

   /**
    * Constructs the AFBDetailUpdRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   AFBDetailUpdRequest( String hostEncoding )
   {
      super ( 278, hostEncoding );
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
    * Sets the Detail Record Type field for the request.
    * 
    * @param value  Value that the Detail Record Type will be set to.
    */
   public final void setRegTypeDetl( String value )
   {
      assertUnsent();
      _RegTypeDetl = value;
   }
	
   /**
    * Sets the Order Code field for the request.
    * 
    * @param value  Value that the Order Code will be set to.
    */
   public final void setOrderCode( String value )
   {
      assertUnsent();
      _OrderCode = value;
   }
	
   /**
    * Sets the Order Type field for the request.
    * 
    * @param value  Value that the Order Type will be set to.
    */
   public final void setOrderType( String value )
   {
      assertUnsent();
      _OrderType = value;
   }
	
   /**
    * Sets the Distributor Code field for the request.
    * 
    * @param value  Value that the Distributor Code will be set to.
    */
   public final void setDistribCode( Integer value )
   {
      assertUnsent();
      _DistribCode = value;
   }
	
   /**
    * Sets the Distributor Description field for the request.
    * 
    * @param value  Value that the Distributor Description will be set to.
    */
   public final void setDistribDesc( String value )
   {
      assertUnsent();
      _DistribDesc = value;
   }
	
   /**
    * Sets the Account Number field for the request.
    * 
    * @param value  Value that the Account Number will be set to.
    */
   public final void setAbAccount( String value )
   {
      assertUnsent();
      _AbAccount = value;
   }
	
   /**
    * Sets the Alternate Account field for the request.
    * 
    * @param value  Value that the Alternate Account will be set to.
    */
   public final void setECSubAccount( String value )
   {
      assertUnsent();
      _ECSubAccount = value;
   }
	
   /**
    * Sets the Unitary Account field for the request.
    * 
    * @param value  Value that the Unitary Account will be set to.
    */
   public final void setUniAccount( String value )
   {
      assertUnsent();
      _UniAccount = value;
   }
	
   /**
    * Sets the Currency field for the request.
    * 
    * @param value  Value that the Currency will be set to.
    */
   public final void setCurrency( String value )
   {
      assertUnsent();
      _Currency = value;
   }
	
   /**
    * Sets the Trade Date field for the request.
    * 
    * @param value  Value that the Trade Date will be set to.
    */
   public final void setTradeDate( String value )
   {
      assertUnsent();
      _TradeDate = value;
   }
	
   /**
    * Sets the Settle Date field for the request.
    * 
    * @param value  Value that the Settle Date will be set to.
    */
   public final void setSettleDate( String value )
   {
      assertUnsent();
      _SettleDate = value;
   }
	
   /**
    * Sets the ISIN Number field for the request.
    * 
    * @param value  Value that the ISIN Number will be set to.
    */
   public final void setISINNumber( String value )
   {
      assertUnsent();
      _ISINNumber = value;
   }
	
   /**
    * Sets the Payment Code field for the request.
    * 
    * @param value  Value that the Payment Code will be set to.
    */
   public final void setPaymentCode( String value )
   {
      assertUnsent();
      _PaymentCode = value;
   }
	
   /**
    * Sets the Charge field for the request.
    * 
    * @param value  Value that the Charge will be set to.
    */
   public final void setCharge( String value )
   {
      assertUnsent();
      _Charge = value;
   }
	
   /**
    * Sets the Shares field for the request.
    * 
    * @param value  Value that the Shares will be set to.
    */
   public final void setShares( String value )
   {
      assertUnsent();
      _Shares = value;
   }
	
   /**
    * Sets the Client Name field for the request.
    * 
    * @param value  Value that the Client Name will be set to.
    */
   public final void setClientName( String value )
   {
      assertUnsent();
      _ClientName = value;
   }
	
   /**
    * Sets the Correspondent Bank field for the request.
    * 
    * @param value  Value that the Correspondent Bank will be set to.
    */
   public final void setCorrespBank( String value )
   {
      assertUnsent();
      _CorrespBank = value;
   }
	
   /**
    * Sets the Mgmt Fund Company Code field for the request.
    * 
    * @param value  Value that the Mgmt Fund Company Code will be set to.
    */
   public final void setFundCodAgCo( String value )
   {
      assertUnsent();
      _FundCodAgCo = value;
   }
	
   /**
    * Sets the Conf. Trade Date field for the request.
    * 
    * @param value  Value that the Conf. Trade Date will be set to.
    */
   public final void setConTradedate( String value )
   {
      assertUnsent();
      _ConTradedate = value;
   }
	
   /**
    * Sets the Conf. Settle Date field for the request.
    * 
    * @param value  Value that the Conf. Settle Date will be set to.
    */
   public final void setConSettleDate( String value )
   {
      assertUnsent();
      _ConSettleDate = value;
   }
	
   /**
    * Sets the Conf. Charge field for the request.
    * 
    * @param value  Value that the Conf. Charge will be set to.
    */
   public final void setConCharge( String value )
   {
      assertUnsent();
      _ConCharge = value;
   }
	
   /**
    * Sets the Conf. Shares field for the request.
    * 
    * @param value  Value that the Conf. Shares will be set to.
    */
   public final void setConShares( String value )
   {
      assertUnsent();
      _ConShares = value;
   }
	
   /**
    * Sets the Liquidation Value field for the request.
    * 
    * @param value  Value that the Liquidation Value will be set to.
    */
   public final void setLV( String value )
   {
      assertUnsent();
      _LV = value;
   }
	
   /**
    * Sets the Designation field for the request.
    * 
    * @param value  Value that the Designation will be set to.
    */
   public final void setDesignation( String value )
   {
      assertUnsent();
      _Designation = value;
   }
	
   /**
    * Sets the Fund Commission field for the request.
    * 
    * @param value  Value that the Fund Commission will be set to.
    */
   public final void setFundCom( String value )
   {
      assertUnsent();
      _FundCom = value;
   }
	
   /**
    * Sets the Gross Amount field for the request.
    * 
    * @param value  Value that the Gross Amount will be set to.
    */
   public final void setConGrossCharge( String value )
   {
      assertUnsent();
      _ConGrossCharge = value;
   }
	
   /**
    * Sets the Liquidation Value field for the request.
    * 
    * @param value  Value that the Liquidation Value will be set to.
    */
   public final void setLVApplied( String value )
   {
      assertUnsent();
      _LVApplied = value;
   }
	
   /**
    * Sets the Order Code 2 field for the request.
    * 
    * @param value  Value that the Order Code 2 will be set to.
    */
   public final void setOrderCode2( String value )
   {
      assertUnsent();
      _OrderCode2 = value;
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
    * Sets the Switch Commission field for the request.
    * 
    * @param value  Value that the Switch Commission will be set to.
    */
   public final void setSwitchCom( String value )
   {
      assertUnsent();
      _SwitchCom = value;
   }
	
   /**
    * Sets the Agency Commission field for the request.
    * 
    * @param value  Value that the Agency Commission will be set to.
    */
   public final void setAgCoCom( String value )
   {
      assertUnsent();
      _AgCoCom = value;
   }
	
   /**
    * Sets the NetworkID field for the request.
    * 
    * @param value  Value that the NetworkID will be set to.
    */
   public final void setNetworkID( String value )
   {
      assertUnsent();
      _NetworkID = value;
   }
	
   /**
    * Sets the OrdeFileName field for the request.
    * 
    * @param value  Value that the OrdeFileName will be set to.
    */
   public final void setOrderFileName( String value )
   {
      assertUnsent();
      _OrderFileName = value;
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
      requestBuffer.appendField( _RegTypeDetl );
      requestBuffer.appendField( _OrderCode );
      requestBuffer.appendField( _OrderType );
      requestBuffer.appendField( _DistribCode );
      requestBuffer.appendField( _DistribDesc );
      requestBuffer.appendField( _AbAccount );
      requestBuffer.appendField( _ECSubAccount );
      requestBuffer.appendField( _UniAccount );
      requestBuffer.appendField( _Currency );
      requestBuffer.appendField( _TradeDate );
      requestBuffer.appendField( _SettleDate );
      requestBuffer.appendField( _ISINNumber );
      requestBuffer.appendField( _PaymentCode );
      requestBuffer.appendField( _Charge );
      requestBuffer.appendField( _Shares );
      requestBuffer.appendField( _ClientName );
      requestBuffer.appendField( _CorrespBank );
      requestBuffer.appendField( _FundCodAgCo );
      requestBuffer.appendField( _ConTradedate );
      requestBuffer.appendField( _ConSettleDate );
      requestBuffer.appendField( _ConCharge );
      requestBuffer.appendField( _ConShares );
      requestBuffer.appendField( _LV );
      requestBuffer.appendField( _Designation );
      requestBuffer.appendField( _FundCom );
      requestBuffer.appendField( _ConGrossCharge );
      requestBuffer.appendField( _LVApplied );
      requestBuffer.appendField( _OrderCode2 );
      requestBuffer.appendField( _ExchRate );
      requestBuffer.appendField( _SwitchCom );
      requestBuffer.appendField( _AgCoCom );
      requestBuffer.appendField( _NetworkID );
      requestBuffer.appendField( _OrderFileName );
   }

}

