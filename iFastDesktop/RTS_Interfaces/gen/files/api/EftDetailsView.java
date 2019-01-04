
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * EFT Payment Details view.
 * For additional view information see <A HREF="../../../../viewspecs/EftDetails.doc">EftDetails.doc</A>.
 * 
 * @author RTS Generated
 */
public class EftDetailsView extends IFastView implements Serializable
{

   /**
    * InstitutionCode member variable.
    */
   private Integer _InstCode = null;
   
   /**
    * InstitutionName member variable.
    */
   private String _InstName = null;
   
   /**
    * TransitCode member variable.
    */
   private Integer _TransitNo = null;
   
   /**
    * TransitName member variable.
    */
   private String _TransitName = null;
   
   /**
    * BankAccountNum member variable.
    */
   private String _BankAcctNum = null;
   
   /**
    * FeeAmt member variable.
    */
   private String _FeeAmt = null;
   
   /**
    * FedTaxAmt member variable.
    */
   private String _FedTax = null;
   
   /**
    * ProvTaxAmt member variable.
    */
   private String _ProvTax = null;
   
   /**
    * NetAmt member variable.
    */
   private String _NetAmt = null;
   
   /**
    * Bank Account Type member variable.
    */
   private String _BankAcctType = null;
   
   /**
    * Bank Account Type Description member variable.
    */
   private String _BankAcctTypeDesc = null;
   

   /**
    * Constructs the EftDetailsView object.
    * 
    */
   public EftDetailsView()
   {
      super ( new EftDetailsRequest() );
   }

   /**
    * Constructs the EftDetailsView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public EftDetailsView( String hostEncoding )
   {
      super ( new EftDetailsRequest( hostEncoding ) );
   }

   /**
    * Gets the EftDetailsRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The EftDetailsRequest object.
    */
   public final EftDetailsRequest getRequest()
   {
      return (EftDetailsRequest)getIFastRequest();
   }
        
   /**
    * Gets the InstitutionCode field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the InstitutionCode or null.
    */
   public final Integer getInstCode()
   {
      return _InstCode;
   }
	
   /**
    * Gets the InstitutionCode field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the InstitutionCode or the specified default value.
    */
   public final int getInstCode( int defaultValue )
   {
      return _InstCode == null ? defaultValue : _InstCode.intValue();
   }
                  
   /**
    * Gets the InstitutionName field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the InstitutionName or null.
    */
   public final String getInstName()
   {
      return _InstName;
   }
	
   /**
    * Gets the InstitutionName field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the InstitutionName or the specified default value.
    */
   public final String getInstName( String defaultValue )
   {
      return _InstName == null ? defaultValue : _InstName;
   }
                  
   /**
    * Gets the TransitCode field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the TransitCode or null.
    */
   public final Integer getTransitNo()
   {
      return _TransitNo;
   }
	
   /**
    * Gets the TransitCode field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the TransitCode or the specified default value.
    */
   public final int getTransitNo( int defaultValue )
   {
      return _TransitNo == null ? defaultValue : _TransitNo.intValue();
   }
                  
   /**
    * Gets the TransitName field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the TransitName or null.
    */
   public final String getTransitName()
   {
      return _TransitName;
   }
	
   /**
    * Gets the TransitName field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the TransitName or the specified default value.
    */
   public final String getTransitName( String defaultValue )
   {
      return _TransitName == null ? defaultValue : _TransitName;
   }
                  
   /**
    * Gets the BankAccountNum field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the BankAccountNum or null.
    */
   public final String getBankAcctNum()
   {
      return _BankAcctNum;
   }
	
   /**
    * Gets the BankAccountNum field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the BankAccountNum or the specified default value.
    */
   public final String getBankAcctNum( String defaultValue )
   {
      return _BankAcctNum == null ? defaultValue : _BankAcctNum;
   }
                  
   /**
    * Gets the FeeAmt field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the FeeAmt or null.
    */
   public final String getFeeAmt()
   {
      return _FeeAmt;
   }
	
   /**
    * Gets the FeeAmt field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FeeAmt or the specified default value.
    */
   public final String getFeeAmt( String defaultValue )
   {
      return _FeeAmt == null ? defaultValue : _FeeAmt;
   }
                  
   /**
    * Gets the FedTaxAmt field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the FedTaxAmt or null.
    */
   public final String getFedTax()
   {
      return _FedTax;
   }
	
   /**
    * Gets the FedTaxAmt field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FedTaxAmt or the specified default value.
    */
   public final String getFedTax( String defaultValue )
   {
      return _FedTax == null ? defaultValue : _FedTax;
   }
                  
   /**
    * Gets the ProvTaxAmt field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the ProvTaxAmt or null.
    */
   public final String getProvTax()
   {
      return _ProvTax;
   }
	
   /**
    * Gets the ProvTaxAmt field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ProvTaxAmt or the specified default value.
    */
   public final String getProvTax( String defaultValue )
   {
      return _ProvTax == null ? defaultValue : _ProvTax;
   }
                  
   /**
    * Gets the NetAmt field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the NetAmt or null.
    */
   public final String getNetAmt()
   {
      return _NetAmt;
   }
	
   /**
    * Gets the NetAmt field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the NetAmt or the specified default value.
    */
   public final String getNetAmt( String defaultValue )
   {
      return _NetAmt == null ? defaultValue : _NetAmt;
   }
                  
   /**
    * Gets the Bank Account Type field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Bank Account Type or null.
    */
   public final String getBankAcctType()
   {
      return _BankAcctType;
   }
	
   /**
    * Gets the Bank Account Type field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Account Type or the specified default value.
    */
   public final String getBankAcctType( String defaultValue )
   {
      return _BankAcctType == null ? defaultValue : _BankAcctType;
   }
                  
   /**
    * Gets the Bank Account Type Description field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Bank Account Type Description or null.
    */
   public final String getBankAcctTypeDesc()
   {
      return _BankAcctTypeDesc;
   }
	
   /**
    * Gets the Bank Account Type Description field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Account Type Description or the specified default value.
    */
   public final String getBankAcctTypeDesc( String defaultValue )
   {
      return _BankAcctTypeDesc == null ? defaultValue : _BankAcctTypeDesc;
   }
                  
   /**
    * Implements the abstract base method to decode
    * the host formatted response.
    * 
    * @param response Host formatted response object.
    * @exception ParseException
    */
   protected void decodeFields( RTSResponseDecodeBuffer responseBuffer ) throws ParseException, UnsupportedEncodingException
   {
      
      // single-record section
      _InstCode = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _InstName = responseBuffer.decodeString(responseBuffer.getNextField());
      _TransitNo = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _TransitName = responseBuffer.decodeString(responseBuffer.getNextField());
      _BankAcctNum = responseBuffer.decodeString(responseBuffer.getNextField());
      _FeeAmt = responseBuffer.decodeString(responseBuffer.getNextField());
      _FedTax = responseBuffer.decodeString(responseBuffer.getNextField());
      _ProvTax = responseBuffer.decodeString(responseBuffer.getNextField());
      _NetAmt = responseBuffer.decodeString(responseBuffer.getNextField());
      _BankAcctType = responseBuffer.decodeString(responseBuffer.getNextField());
      _BankAcctTypeDesc = responseBuffer.decodeString(responseBuffer.getNextField());
                  

   }

}
      
