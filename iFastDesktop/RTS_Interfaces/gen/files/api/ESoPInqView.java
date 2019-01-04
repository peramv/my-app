
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * ESoP Plan Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/ESoPInq.doc">ESoPInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class ESoPInqView extends IFastView implements Serializable
{

   /**
    * Administrating Institution of the ESoP member variable.
    */
   private String _IFASNumber = null;
   
   /**
    * Intial Purchase Date member variable.
    */
   private Date _InitPurchDate = null;
   
   /**
    * Initial Investment Date member variable.
    */
   private Date _InitInvestDate = null;
   
   /**
    * Start date of Contract member variable.
    */
   private Date _ContStartDate = null;
   
   /**
    * Contract End Date member variable.
    */
   private Date _ContEndDate = null;
   
   /**
    * Flag indicating if new acct is created member variable.
    */
   private Boolean _AutoCreate = null;
   
   /**
    * ESoP Status member variable.
    */
   private String _EspStatus = null;
   
   /**
    * Inactive Date member variable.
    */
   private Date _InactiveDate = null;
   
   /**
    * Block Start Date member variable.
    */
   private Date _BlockStartDate = null;
   
   /**
    * Block End Date member variable.
    */
   private Date _BlockEndDate = null;
   
   /**
    * Contract Expire Date member variable.
    */
   private Date _ContExpireDate = null;
   
   /**
    * Interruption Date member variable.
    */
   private Date _InterruptDate = null;
   
   /**
    * Interruption Code member variable.
    */
   private String _InterruptCode = null;
   
   /**
    * Banking  record effective Date member variable.
    */
   private Date _BankEffectiveDate = null;
   
   /**
    * Fund Code member variable.
    */
   private String _FundCode = null;
   
   /**
    * Class Code member variable.
    */
   private String _ClassCode = null;
   
   /**
    * Amount member variable.
    */
   private String _Amount = null;
   
   /**
    * Currency member variable.
    */
   private String _Currency = null;
   
   /**
    * Version Number member variable.
    */
   private Integer _EsopVersion = null;
   
   /**
    * Esop RecId member variable.
    */
   private Integer _EsopRid = null;
   

   /**
    * Constructs the ESoPInqView object.
    * 
    */
   public ESoPInqView()
   {
      super ( new ESoPInqRequest() );
   }

   /**
    * Constructs the ESoPInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public ESoPInqView( String hostEncoding )
   {
      super ( new ESoPInqRequest( hostEncoding ) );
   }

   /**
    * Gets the ESoPInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The ESoPInqRequest object.
    */
   public final ESoPInqRequest getRequest()
   {
      return (ESoPInqRequest)getIFastRequest();
   }
        
   /**
    * Gets the Administrating Institution of the ESoP field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Administrating Institution of the ESoP or null.
    */
   public final String getIFASNumber()
   {
      return _IFASNumber;
   }
	
   /**
    * Gets the Administrating Institution of the ESoP field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Administrating Institution of the ESoP or the specified default value.
    */
   public final String getIFASNumber( String defaultValue )
   {
      return _IFASNumber == null ? defaultValue : _IFASNumber;
   }
                  
   /**
    * Gets the Intial Purchase Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Intial Purchase Date or null.
    */
   public final Date getInitPurchDate()
   {
      return _InitPurchDate;
   }
	
   /**
    * Gets the Intial Purchase Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Intial Purchase Date or the specified default value.
    */
   public final Date getInitPurchDate( Date defaultValue )
   {
      return _InitPurchDate == null ? defaultValue : _InitPurchDate;
   }
                  
   /**
    * Gets the Initial Investment Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Initial Investment Date or null.
    */
   public final Date getInitInvestDate()
   {
      return _InitInvestDate;
   }
	
   /**
    * Gets the Initial Investment Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Initial Investment Date or the specified default value.
    */
   public final Date getInitInvestDate( Date defaultValue )
   {
      return _InitInvestDate == null ? defaultValue : _InitInvestDate;
   }
                  
   /**
    * Gets the Start date of Contract field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Start date of Contract or null.
    */
   public final Date getContStartDate()
   {
      return _ContStartDate;
   }
	
   /**
    * Gets the Start date of Contract field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Start date of Contract or the specified default value.
    */
   public final Date getContStartDate( Date defaultValue )
   {
      return _ContStartDate == null ? defaultValue : _ContStartDate;
   }
                  
   /**
    * Gets the Contract End Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Contract End Date or null.
    */
   public final Date getContEndDate()
   {
      return _ContEndDate;
   }
	
   /**
    * Gets the Contract End Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Contract End Date or the specified default value.
    */
   public final Date getContEndDate( Date defaultValue )
   {
      return _ContEndDate == null ? defaultValue : _ContEndDate;
   }
                  
   /**
    * Gets the Flag indicating if new acct is created field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Flag indicating if new acct is created or null.
    */
   public final Boolean getAutoCreate()
   {
      return _AutoCreate;
   }
	
   /**
    * Gets the Flag indicating if new acct is created field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if new acct is created or the specified default value.
    */
   public final boolean getAutoCreate( boolean defaultValue )
   {
      return _AutoCreate == null ? defaultValue : _AutoCreate.booleanValue();
   }
                  
   /**
    * Gets the ESoP Status field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the ESoP Status or null.
    */
   public final String getEspStatus()
   {
      return _EspStatus;
   }
	
   /**
    * Gets the ESoP Status field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ESoP Status or the specified default value.
    */
   public final String getEspStatus( String defaultValue )
   {
      return _EspStatus == null ? defaultValue : _EspStatus;
   }
                  
   /**
    * Gets the Inactive Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Inactive Date or null.
    */
   public final Date getInactiveDate()
   {
      return _InactiveDate;
   }
	
   /**
    * Gets the Inactive Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Inactive Date or the specified default value.
    */
   public final Date getInactiveDate( Date defaultValue )
   {
      return _InactiveDate == null ? defaultValue : _InactiveDate;
   }
                  
   /**
    * Gets the Block Start Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Block Start Date or null.
    */
   public final Date getBlockStartDate()
   {
      return _BlockStartDate;
   }
	
   /**
    * Gets the Block Start Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Block Start Date or the specified default value.
    */
   public final Date getBlockStartDate( Date defaultValue )
   {
      return _BlockStartDate == null ? defaultValue : _BlockStartDate;
   }
                  
   /**
    * Gets the Block End Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Block End Date or null.
    */
   public final Date getBlockEndDate()
   {
      return _BlockEndDate;
   }
	
   /**
    * Gets the Block End Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Block End Date or the specified default value.
    */
   public final Date getBlockEndDate( Date defaultValue )
   {
      return _BlockEndDate == null ? defaultValue : _BlockEndDate;
   }
                  
   /**
    * Gets the Contract Expire Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Contract Expire Date or null.
    */
   public final Date getContExpireDate()
   {
      return _ContExpireDate;
   }
	
   /**
    * Gets the Contract Expire Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Contract Expire Date or the specified default value.
    */
   public final Date getContExpireDate( Date defaultValue )
   {
      return _ContExpireDate == null ? defaultValue : _ContExpireDate;
   }
                  
   /**
    * Gets the Interruption Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Interruption Date or null.
    */
   public final Date getInterruptDate()
   {
      return _InterruptDate;
   }
	
   /**
    * Gets the Interruption Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Interruption Date or the specified default value.
    */
   public final Date getInterruptDate( Date defaultValue )
   {
      return _InterruptDate == null ? defaultValue : _InterruptDate;
   }
                  
   /**
    * Gets the Interruption Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Interruption Code or null.
    */
   public final String getInterruptCode()
   {
      return _InterruptCode;
   }
	
   /**
    * Gets the Interruption Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Interruption Code or the specified default value.
    */
   public final String getInterruptCode( String defaultValue )
   {
      return _InterruptCode == null ? defaultValue : _InterruptCode;
   }
                  
   /**
    * Gets the Banking  record effective Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Banking  record effective Date or null.
    */
   public final Date getBankEffectiveDate()
   {
      return _BankEffectiveDate;
   }
	
   /**
    * Gets the Banking  record effective Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Banking  record effective Date or the specified default value.
    */
   public final Date getBankEffectiveDate( Date defaultValue )
   {
      return _BankEffectiveDate == null ? defaultValue : _BankEffectiveDate;
   }
                  
   /**
    * Gets the Fund Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Fund Code or null.
    */
   public final String getFundCode()
   {
      return _FundCode;
   }
	
   /**
    * Gets the Fund Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Code or the specified default value.
    */
   public final String getFundCode( String defaultValue )
   {
      return _FundCode == null ? defaultValue : _FundCode;
   }
                  
   /**
    * Gets the Class Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Class Code or null.
    */
   public final String getClassCode()
   {
      return _ClassCode;
   }
	
   /**
    * Gets the Class Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Class Code or the specified default value.
    */
   public final String getClassCode( String defaultValue )
   {
      return _ClassCode == null ? defaultValue : _ClassCode;
   }
                  
   /**
    * Gets the Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Amount or null.
    */
   public final String getAmount()
   {
      return _Amount;
   }
	
   /**
    * Gets the Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Amount or the specified default value.
    */
   public final String getAmount( String defaultValue )
   {
      return _Amount == null ? defaultValue : _Amount;
   }
                  
   /**
    * Gets the Currency field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Currency or null.
    */
   public final String getCurrency()
   {
      return _Currency;
   }
	
   /**
    * Gets the Currency field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Currency or the specified default value.
    */
   public final String getCurrency( String defaultValue )
   {
      return _Currency == null ? defaultValue : _Currency;
   }
                  
   /**
    * Gets the Version Number field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Version Number or null.
    */
   public final Integer getEsopVersion()
   {
      return _EsopVersion;
   }
	
   /**
    * Gets the Version Number field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Version Number or the specified default value.
    */
   public final int getEsopVersion( int defaultValue )
   {
      return _EsopVersion == null ? defaultValue : _EsopVersion.intValue();
   }
                  
   /**
    * Gets the Esop RecId field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Esop RecId or null.
    */
   public final Integer getEsopRid()
   {
      return _EsopRid;
   }
	
   /**
    * Gets the Esop RecId field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Esop RecId or the specified default value.
    */
   public final int getEsopRid( int defaultValue )
   {
      return _EsopRid == null ? defaultValue : _EsopRid.intValue();
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
      _IFASNumber = responseBuffer.decodeString(responseBuffer.getNextField());
      _InitPurchDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _InitInvestDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _ContStartDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _ContEndDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _AutoCreate = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _EspStatus = responseBuffer.decodeString(responseBuffer.getNextField());
      _InactiveDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _BlockStartDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _BlockEndDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _ContExpireDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _InterruptDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _InterruptCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _BankEffectiveDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _FundCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _ClassCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _Amount = responseBuffer.decodeString(responseBuffer.getNextField());
      _Currency = responseBuffer.decodeString(responseBuffer.getNextField());
      _EsopVersion = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _EsopRid = responseBuffer.decodeInteger(responseBuffer.getNextField());
                  

   }

}
      
