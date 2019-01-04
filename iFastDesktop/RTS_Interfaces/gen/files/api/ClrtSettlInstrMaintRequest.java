// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Clearing Settlement Instructions Maint request.
 * For additional view information see <A HREF="../../../../viewspecs/ClrtSettlInstrMaint.doc">ClrtSettlInstrMaint.doc</A>.
 * 
 * @author RTS Generated
 */
public class ClrtSettlInstrMaintRequest extends IFastRequest implements Serializable
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
   private String _CompanyID = "";
            
            
            
            
            
   /**
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Fund Broker Code member variable.
    */
   private String _FundBrokerCode = "";
            
   /**
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * Run Mode member array.
    */
   private String[] _RunMode = new String[25];
            
   /**
    * Version member array.
    */
   private Integer[] _ClrSettlInstrVer = new Integer[25];
            
   /**
    * Recid member array.
    */
   private Integer[] _ClrSettlInstrRid = new Integer[25];
            
   /**
    * Settlement Instruction Code member array.
    */
   private String[] _SettlInstrCode = new String[25];
            
   /**
    * Is Default Clearing Settlement Instruction member array.
    */
   private Boolean[] _IsDefault = new Boolean[25];
            
   /**
    * Delivery To member array.
    */
   private String[] _DeliveryTo = new String[25];
            
   /**
    * For Account member array.
    */
   private String[] _ForAccount = new String[25];
            
   /**
    * In Favour Of member array.
    */
   private String[] _InFavourOf = new String[25];
            
   /**
    * Settlement Instruction ID member array.
    */
   private Integer[] _SettleInstrId = new Integer[25];
            
   /**
    * Effective Date member array.
    */
   private Date[] _Deff = new Date[25];
            
   /**
    * Stop Date member array.
    */
   private Date[] _StopDate = new Date[25];
            
   /**
    * Clear Settlement Method member array.
    */
   private String[] _ClrSettlMethod = new String[25];
            
   /**
    * CashMsgType member array.
    */
   private String[] _CashMsgType = new String[25];
            
   /**
    * IntermediaryBank member array.
    */
   private String[] _IntermediaryBank = new String[25];
            
   /**
    * ReceivingBank member array.
    */
   private String[] _ReceivingBank = new String[25];
            
   /**
    * Beneficiary member array.
    */
   private String[] _Beneficiary = new String[25];
            
   /**
    * SpecialInstructions member array.
    */
   private String[] _SpecialInstructions = new String[25];
            

   /**
    * Constructs the ClrtSettlInstrMaintRequest object.
    * 
    */
   ClrtSettlInstrMaintRequest()
   {
      super ( 318 );
   }

   /**
    * Constructs the ClrtSettlInstrMaintRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   ClrtSettlInstrMaintRequest( String hostEncoding )
   {
      super ( 318, hostEncoding );
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
   public final void setCompanyID( String value )
   {
      assertUnsent();
      _CompanyID = value;
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
    * Sets the Fund Broker Code field for the request.
    * 
    * @param value  Value that the Fund Broker Code will be set to.
    */
   public final void setFundBrokerCode( String value )
   {
      assertUnsent();
      _FundBrokerCode = value;
   }
	
   /**
    * Sets the Record Count for the repeatable request.
    * 
    * @param value    Value that the Record Count will be set to.
    */
   public final void setRepeatCount( int value )
   {
      _RepeatCount = value;
   }
         
   /**
    * Sets the Run Mode field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Run Mode will be set to.
    */
   public final void setRunMode( int index, String value )
   {
      assertUnsent();
      _RunMode[index] = value;
   }
	
   /**
    * Sets the Version field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Version will be set to.
    */
   public final void setClrSettlInstrVer( int index, Integer value )
   {
      assertUnsent();
      _ClrSettlInstrVer[index] = value;
   }
	
   /**
    * Sets the Recid field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Recid will be set to.
    */
   public final void setClrSettlInstrRid( int index, Integer value )
   {
      assertUnsent();
      _ClrSettlInstrRid[index] = value;
   }
	
   /**
    * Sets the Settlement Instruction Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Settlement Instruction Code will be set to.
    */
   public final void setSettlInstrCode( int index, String value )
   {
      assertUnsent();
      _SettlInstrCode[index] = value;
   }
	
   /**
    * Sets the Is Default Clearing Settlement Instruction field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Is Default Clearing Settlement Instruction will be set to.
    */
   public final void setIsDefault( int index, Boolean value )
   {
      assertUnsent();
      _IsDefault[index] = value;
   }
	
   /**
    * Sets the Delivery To field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Delivery To will be set to.
    */
   public final void setDeliveryTo( int index, String value )
   {
      assertUnsent();
      _DeliveryTo[index] = value;
   }
	
   /**
    * Sets the For Account field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the For Account will be set to.
    */
   public final void setForAccount( int index, String value )
   {
      assertUnsent();
      _ForAccount[index] = value;
   }
	
   /**
    * Sets the In Favour Of field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the In Favour Of will be set to.
    */
   public final void setInFavourOf( int index, String value )
   {
      assertUnsent();
      _InFavourOf[index] = value;
   }
	
   /**
    * Sets the Settlement Instruction ID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Settlement Instruction ID will be set to.
    */
   public final void setSettleInstrId( int index, Integer value )
   {
      assertUnsent();
      _SettleInstrId[index] = value;
   }
	
   /**
    * Sets the Effective Date field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Effective Date will be set to.
    */
   public final void setDeff( int index, Date value )
   {
      assertUnsent();
      _Deff[index] = value;
   }
	
   /**
    * Sets the Stop Date field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Stop Date will be set to.
    */
   public final void setStopDate( int index, Date value )
   {
      assertUnsent();
      _StopDate[index] = value;
   }
	
   /**
    * Sets the Clear Settlement Method field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Clear Settlement Method will be set to.
    */
   public final void setClrSettlMethod( int index, String value )
   {
      assertUnsent();
      _ClrSettlMethod[index] = value;
   }
	
   /**
    * Sets the CashMsgType field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the CashMsgType will be set to.
    */
   public final void setCashMsgType( int index, String value )
   {
      assertUnsent();
      _CashMsgType[index] = value;
   }
	
   /**
    * Sets the IntermediaryBank field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the IntermediaryBank will be set to.
    */
   public final void setIntermediaryBank( int index, String value )
   {
      assertUnsent();
      _IntermediaryBank[index] = value;
   }
	
   /**
    * Sets the ReceivingBank field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the ReceivingBank will be set to.
    */
   public final void setReceivingBank( int index, String value )
   {
      assertUnsent();
      _ReceivingBank[index] = value;
   }
	
   /**
    * Sets the Beneficiary field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Beneficiary will be set to.
    */
   public final void setBeneficiary( int index, String value )
   {
      assertUnsent();
      _Beneficiary[index] = value;
   }
	
   /**
    * Sets the SpecialInstructions field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the SpecialInstructions will be set to.
    */
   public final void setSpecialInstructions( int index, String value )
   {
      assertUnsent();
      _SpecialInstructions[index] = value;
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
      requestBuffer.appendField( _CompanyID );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      encodeOverrideRepeatsField( requestBuffer );
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _FundBrokerCode );
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _RunMode[x] );
         requestBuffer.appendField( _ClrSettlInstrVer[x] );
         requestBuffer.appendField( _ClrSettlInstrRid[x] );
         requestBuffer.appendField( _SettlInstrCode[x] );
         requestBuffer.appendField( _IsDefault[x] );
         requestBuffer.appendField( _DeliveryTo[x] );
         requestBuffer.appendField( _ForAccount[x] );
         requestBuffer.appendField( _InFavourOf[x] );
         requestBuffer.appendField( _SettleInstrId[x] );
         requestBuffer.appendField( _Deff[x] );
         requestBuffer.appendField( _StopDate[x] );
         requestBuffer.appendField( _ClrSettlMethod[x] );
         requestBuffer.appendField( _CashMsgType[x] );
         requestBuffer.appendField( _IntermediaryBank[x] );
         requestBuffer.appendField( _ReceivingBank[x] );
         requestBuffer.appendField( _Beneficiary[x] );
         requestBuffer.appendField( _SpecialInstructions[x] );
      }
   }

}

