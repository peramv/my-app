// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Acquisition Fee Calculation Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/AcquisitionFeeCalculation.doc">AcquisitionFeeCalculation.doc</A>.
 * 
 * @author RTS Generated
 */
public class AcquisitionFeeCalculationRequest extends IFastRequest implements Serializable
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
    * Taxation Type: RSP, RRIF, non-registered, etc. member variable.
    */
   private String _TaxType = "";
            
   /**
    * Transaction Type member variable.
    */
   private String _TransType = "";
            
   /**
    * Effective Date member variable.
    */
   private Date _EffectiveDate = null;
            
   /**
    * Amount member variable.
    */
   private String _Amount = "0";
            
   /**
    * Amount Type member variable.
    */
   private String _AmountType = "";
            
   /**
    * Fund Code member variable.
    */
   private String _FundCode = "";
            
   /**
    * Class Code member variable.
    */
   private String _ClassCode = "";
            
   /**
    * Currency member variable.
    */
   private String _Currency = "";
            
   /**
    * Exchange Rate member variable.
    */
   private String _ExchRate = "0";
            
   /**
    * Broker Code member variable.
    */
   private String _BrokerCode = "";
            
   /**
    * Fund To Code (for transfer) member variable.
    */
   private String _FundToCode = "";
            
   /**
    * Class To Code (for transfer) member variable.
    */
   private String _ClassToCode = "";
            
            
            
   /**
    * Flat or Percent member variable.
    */
   private Boolean _FlatPercent = new Boolean(false);
            
   /**
    * To Account TaxType member variable.
    */
   private String _ToAcctTaxType = "";
            
   /**
    * Account member variable.
    */
   private String _Account = "0";
            

   /**
    * Constructs the AcquisitionFeeCalculationRequest object.
    * 
    */
   AcquisitionFeeCalculationRequest()
   {
      super ( 121 );
   }

   /**
    * Constructs the AcquisitionFeeCalculationRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   AcquisitionFeeCalculationRequest( String hostEncoding )
   {
      super ( 121, hostEncoding );
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
    * Sets the Taxation Type: RSP, RRIF, non-registered, etc. field for the request.
    * 
    * @param value  Value that the Taxation Type: RSP, RRIF, non-registered, etc. will be set to.
    */
   public final void setTaxType( String value )
   {
      assertUnsent();
      _TaxType = value;
   }
	
   /**
    * Sets the Transaction Type field for the request.
    * 
    * @param value  Value that the Transaction Type will be set to.
    */
   public final void setTransType( String value )
   {
      assertUnsent();
      _TransType = value;
   }
	
   /**
    * Sets the Effective Date field for the request.
    * 
    * @param value  Value that the Effective Date will be set to.
    */
   public final void setEffectiveDate( Date value )
   {
      assertUnsent();
      _EffectiveDate = value;
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
    * Sets the Amount Type field for the request.
    * 
    * @param value  Value that the Amount Type will be set to.
    */
   public final void setAmountType( String value )
   {
      assertUnsent();
      _AmountType = value;
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
    * Sets the Broker Code field for the request.
    * 
    * @param value  Value that the Broker Code will be set to.
    */
   public final void setBrokerCode( String value )
   {
      assertUnsent();
      _BrokerCode = value;
   }
	
   /**
    * Sets the Fund To Code (for transfer) field for the request.
    * 
    * @param value  Value that the Fund To Code (for transfer) will be set to.
    */
   public final void setFundToCode( String value )
   {
      assertUnsent();
      _FundToCode = value;
   }
	
   /**
    * Sets the Class To Code (for transfer) field for the request.
    * 
    * @param value  Value that the Class To Code (for transfer) will be set to.
    */
   public final void setClassToCode( String value )
   {
      assertUnsent();
      _ClassToCode = value;
   }
	
   /**
    * Sets the Flat or Percent field for the request.
    * 
    * @param value  Value that the Flat or Percent will be set to.
    */
   public final void setFlatPercent( Boolean value )
   {
      assertUnsent();
      _FlatPercent = value;
   }
	
   /**
    * Sets the To Account TaxType field for the request.
    * 
    * @param value  Value that the To Account TaxType will be set to.
    */
   public final void setToAcctTaxType( String value )
   {
      assertUnsent();
      _ToAcctTaxType = value;
   }
	
   /**
    * Sets the Account field for the request.
    * 
    * @param value  Value that the Account will be set to.
    */
   public final void setAccount( String value )
   {
      assertUnsent();
      _Account = value;
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
      requestBuffer.appendField( _TaxType );
      requestBuffer.appendField( _TransType );
      requestBuffer.appendField( _EffectiveDate );
      requestBuffer.appendField( _Amount );
      requestBuffer.appendField( _AmountType );
      requestBuffer.appendField( _FundCode );
      requestBuffer.appendField( _ClassCode );
      requestBuffer.appendField( _Currency );
      requestBuffer.appendField( _ExchRate );
      requestBuffer.appendField( _BrokerCode );
      requestBuffer.appendField( _FundToCode );
      requestBuffer.appendField( _ClassToCode );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _FlatPercent );
      requestBuffer.appendField( _ToAcctTaxType );
      requestBuffer.appendField( _Account );
   }

}

