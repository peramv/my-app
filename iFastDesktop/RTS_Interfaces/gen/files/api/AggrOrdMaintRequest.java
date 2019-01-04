// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Aggregated Orders Maintenance request.
 * For additional view information see <A HREF="../../../../viewspecs/AggrOrdMaint.doc">AggrOrdMaint.doc</A>.
 * 
 * @author RTS Generated
 */
public class AggrOrdMaintRequest extends IFastRequest implements Serializable
{

   /**
    * Session Id member variable.
    */
   private String _SessionID = "";
            
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
    * OmnibusId member variable.
    */
   private String _OmnibusId = "";
            
   /**
    * Broker Settlement Date member variable.
    */
   private Date _BrkSettlDate = null;
            
   /**
    * Broker Settlement Amount Units member variable.
    */
   private String _BrkSettlAmtUnits = "0";
            
   /**
    * Broker Settle PUD member variable.
    */
   private String _BrkSettlPUD = "";
            
   /**
    * Price member variable.
    */
   private String _Price = "0";
            
   /**
    * Price Type member variable.
    */
   private String _PriceType = "";
            
   /**
    * Commission Rate member variable.
    */
   private String _Commission = "0";
            
   /**
    * External Charge member variable.
    */
   private String _ExternCharge = "0";
            
   /**
    * Rebate Rate member variable.
    */
   private String _RebateRate = "0";
            
   /**
    * Order Status member variable.
    */
   private String _OrdStatus = "";
            
   /**
    * Delivery To member variable.
    */
   private String _DeliveryTo = "";
            
   /**
    * For Account member variable.
    */
   private String _ForAccount = "";
            
   /**
    * In Favour Of member variable.
    */
   private String _InFavourOf = "";
            
   /**
    * Clear Settlement Method member variable.
    */
   private String _ClrSettlMethod = "";
            
   /**
    * Settlement Instruction Code member variable.
    */
   private String _SettlInstrCode = "";
            
   /**
    * Settlement Location Code member variable.
    */
   private String _SettlLocCode = "";
            
   /**
    * Aggregation Order Id member variable.
    */
   private Integer _AggrOrdId = null;
            
   /**
    * Aggregate Order Version member variable.
    */
   private Integer _AggrOrdVer = null;
            
   /**
    * Recalculate member variable.
    */
   private Boolean _Recalculate = new Boolean(false);
            
   /**
    * Remarks member variable.
    */
   private String _Remarks = "";
            
   /**
    * Run Mode member variable.
    */
   private String _RunMode = "";
            
   /**
    * TradeDate member variable.
    */
   private Date _TradeDate = null;
            
   /**
    * Calculate Broker Amount member variable.
    */
   private Boolean _CalcBrkAmount = new Boolean(false);
            
   /**
    * Sec Recon File member variable.
    */
   private String _SecReconFile = "";
            
   /**
    * Broker Confirmed Amount member variable.
    */
   private String _Amount = "0";
            
   /**
    * CashMsgType member variable.
    */
   private String _CashMsgType = "";
            
   /**
    * IntermediaryBank member variable.
    */
   private String _IntermediaryBank = "";
            
   /**
    * ReceivingBank member variable.
    */
   private String _ReceivingBank = "";
            
   /**
    * Beneficiary member variable.
    */
   private String _Beneficiary = "";
            
   /**
    * SpecialInstructions member variable.
    */
   private String _SpecialInstructions = "";
            
   /**
    * InternalSettlementAccount member variable.
    */
   private String _InternalSettlementAccount = "";
            

   /**
    * Constructs the AggrOrdMaintRequest object.
    * 
    */
   AggrOrdMaintRequest()
   {
      super ( 324 );
   }

   /**
    * Constructs the AggrOrdMaintRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   AggrOrdMaintRequest( String hostEncoding )
   {
      super ( 324, hostEncoding );
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
    * Sets the OmnibusId field for the request.
    * 
    * @param value  Value that the OmnibusId will be set to.
    */
   public final void setOmnibusId( String value )
   {
      assertUnsent();
      _OmnibusId = value;
   }
	
   /**
    * Sets the Broker Settlement Date field for the request.
    * 
    * @param value  Value that the Broker Settlement Date will be set to.
    */
   public final void setBrkSettlDate( Date value )
   {
      assertUnsent();
      _BrkSettlDate = value;
   }
	
   /**
    * Sets the Broker Settlement Amount Units field for the request.
    * 
    * @param value  Value that the Broker Settlement Amount Units will be set to.
    */
   public final void setBrkSettlAmtUnits( String value )
   {
      assertUnsent();
      _BrkSettlAmtUnits = value;
   }
	
   /**
    * Sets the Broker Settle PUD field for the request.
    * 
    * @param value  Value that the Broker Settle PUD will be set to.
    */
   public final void setBrkSettlPUD( String value )
   {
      assertUnsent();
      _BrkSettlPUD = value;
   }
	
   /**
    * Sets the Price field for the request.
    * 
    * @param value  Value that the Price will be set to.
    */
   public final void setPrice( String value )
   {
      assertUnsent();
      _Price = value;
   }
	
   /**
    * Sets the Price Type field for the request.
    * 
    * @param value  Value that the Price Type will be set to.
    */
   public final void setPriceType( String value )
   {
      assertUnsent();
      _PriceType = value;
   }
	
   /**
    * Sets the Commission Rate field for the request.
    * 
    * @param value  Value that the Commission Rate will be set to.
    */
   public final void setCommission( String value )
   {
      assertUnsent();
      _Commission = value;
   }
	
   /**
    * Sets the External Charge field for the request.
    * 
    * @param value  Value that the External Charge will be set to.
    */
   public final void setExternCharge( String value )
   {
      assertUnsent();
      _ExternCharge = value;
   }
	
   /**
    * Sets the Rebate Rate field for the request.
    * 
    * @param value  Value that the Rebate Rate will be set to.
    */
   public final void setRebateRate( String value )
   {
      assertUnsent();
      _RebateRate = value;
   }
	
   /**
    * Sets the Order Status field for the request.
    * 
    * @param value  Value that the Order Status will be set to.
    */
   public final void setOrdStatus( String value )
   {
      assertUnsent();
      _OrdStatus = value;
   }
	
   /**
    * Sets the Delivery To field for the request.
    * 
    * @param value  Value that the Delivery To will be set to.
    */
   public final void setDeliveryTo( String value )
   {
      assertUnsent();
      _DeliveryTo = value;
   }
	
   /**
    * Sets the For Account field for the request.
    * 
    * @param value  Value that the For Account will be set to.
    */
   public final void setForAccount( String value )
   {
      assertUnsent();
      _ForAccount = value;
   }
	
   /**
    * Sets the In Favour Of field for the request.
    * 
    * @param value  Value that the In Favour Of will be set to.
    */
   public final void setInFavourOf( String value )
   {
      assertUnsent();
      _InFavourOf = value;
   }
	
   /**
    * Sets the Clear Settlement Method field for the request.
    * 
    * @param value  Value that the Clear Settlement Method will be set to.
    */
   public final void setClrSettlMethod( String value )
   {
      assertUnsent();
      _ClrSettlMethod = value;
   }
	
   /**
    * Sets the Settlement Instruction Code field for the request.
    * 
    * @param value  Value that the Settlement Instruction Code will be set to.
    */
   public final void setSettlInstrCode( String value )
   {
      assertUnsent();
      _SettlInstrCode = value;
   }
	
   /**
    * Sets the Settlement Location Code field for the request.
    * 
    * @param value  Value that the Settlement Location Code will be set to.
    */
   public final void setSettlLocCode( String value )
   {
      assertUnsent();
      _SettlLocCode = value;
   }
	
   /**
    * Sets the Aggregation Order Id field for the request.
    * 
    * @param value  Value that the Aggregation Order Id will be set to.
    */
   public final void setAggrOrdId( Integer value )
   {
      assertUnsent();
      _AggrOrdId = value;
   }
	
   /**
    * Sets the Aggregate Order Version field for the request.
    * 
    * @param value  Value that the Aggregate Order Version will be set to.
    */
   public final void setAggrOrdVer( Integer value )
   {
      assertUnsent();
      _AggrOrdVer = value;
   }
	
   /**
    * Sets the Recalculate field for the request.
    * 
    * @param value  Value that the Recalculate will be set to.
    */
   public final void setRecalculate( Boolean value )
   {
      assertUnsent();
      _Recalculate = value;
   }
	
   /**
    * Sets the Remarks field for the request.
    * 
    * @param value  Value that the Remarks will be set to.
    */
   public final void setRemarks( String value )
   {
      assertUnsent();
      _Remarks = value;
   }
	
   /**
    * Sets the Run Mode field for the request.
    * 
    * @param value  Value that the Run Mode will be set to.
    */
   public final void setRunMode( String value )
   {
      assertUnsent();
      _RunMode = value;
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
    * Sets the Calculate Broker Amount field for the request.
    * 
    * @param value  Value that the Calculate Broker Amount will be set to.
    */
   public final void setCalcBrkAmount( Boolean value )
   {
      assertUnsent();
      _CalcBrkAmount = value;
   }
	
   /**
    * Sets the Sec Recon File field for the request.
    * 
    * @param value  Value that the Sec Recon File will be set to.
    */
   public final void setSecReconFile( String value )
   {
      assertUnsent();
      _SecReconFile = value;
   }
	
   /**
    * Sets the Broker Confirmed Amount field for the request.
    * 
    * @param value  Value that the Broker Confirmed Amount will be set to.
    */
   public final void setAmount( String value )
   {
      assertUnsent();
      _Amount = value;
   }
	
   /**
    * Sets the CashMsgType field for the request.
    * 
    * @param value  Value that the CashMsgType will be set to.
    */
   public final void setCashMsgType( String value )
   {
      assertUnsent();
      _CashMsgType = value;
   }
	
   /**
    * Sets the IntermediaryBank field for the request.
    * 
    * @param value  Value that the IntermediaryBank will be set to.
    */
   public final void setIntermediaryBank( String value )
   {
      assertUnsent();
      _IntermediaryBank = value;
   }
	
   /**
    * Sets the ReceivingBank field for the request.
    * 
    * @param value  Value that the ReceivingBank will be set to.
    */
   public final void setReceivingBank( String value )
   {
      assertUnsent();
      _ReceivingBank = value;
   }
	
   /**
    * Sets the Beneficiary field for the request.
    * 
    * @param value  Value that the Beneficiary will be set to.
    */
   public final void setBeneficiary( String value )
   {
      assertUnsent();
      _Beneficiary = value;
   }
	
   /**
    * Sets the SpecialInstructions field for the request.
    * 
    * @param value  Value that the SpecialInstructions will be set to.
    */
   public final void setSpecialInstructions( String value )
   {
      assertUnsent();
      _SpecialInstructions = value;
   }
	
   /**
    * Sets the InternalSettlementAccount field for the request.
    * 
    * @param value  Value that the InternalSettlementAccount will be set to.
    */
   public final void setInternalSettlementAccount( String value )
   {
      assertUnsent();
      _InternalSettlementAccount = value;
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
      requestBuffer.appendField( _User_Id );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyId );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _OmnibusId );
      requestBuffer.appendField( _BrkSettlDate );
      requestBuffer.appendField( _BrkSettlAmtUnits );
      requestBuffer.appendField( _BrkSettlPUD );
      requestBuffer.appendField( _Price );
      requestBuffer.appendField( _PriceType );
      requestBuffer.appendField( _Commission );
      requestBuffer.appendField( _ExternCharge );
      requestBuffer.appendField( _RebateRate );
      requestBuffer.appendField( _OrdStatus );
      requestBuffer.appendField( _DeliveryTo );
      requestBuffer.appendField( _ForAccount );
      requestBuffer.appendField( _InFavourOf );
      requestBuffer.appendField( _ClrSettlMethod );
      requestBuffer.appendField( _SettlInstrCode );
      requestBuffer.appendField( _SettlLocCode );
      requestBuffer.appendField( _AggrOrdId );
      requestBuffer.appendField( _AggrOrdVer );
      requestBuffer.appendField( _Recalculate );
      requestBuffer.appendField( _Remarks );
      requestBuffer.appendField( _RunMode );
      requestBuffer.appendField( _TradeDate );
      requestBuffer.appendField( _CalcBrkAmount );
      requestBuffer.appendField( _SecReconFile );
      requestBuffer.appendField( _Amount );
      requestBuffer.appendField( _CashMsgType );
      requestBuffer.appendField( _IntermediaryBank );
      requestBuffer.appendField( _ReceivingBank );
      requestBuffer.appendField( _Beneficiary );
      requestBuffer.appendField( _SpecialInstructions );
      requestBuffer.appendField( _InternalSettlementAccount );
   }

}

