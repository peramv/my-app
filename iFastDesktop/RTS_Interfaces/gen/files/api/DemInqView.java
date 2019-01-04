
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * FundCom Demographics Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/DemInq.doc">DemInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class DemInqView extends IFastView implements Serializable
{

   /**
    * Intermediary Code member variable.
    */
   private String _IntermCode = null;
   
   /**
    * Address Line 1 member variable.
    */
   private String _AddrLine1 = null;
   
   /**
    * Address Line 2 member variable.
    */
   private String _AddrLine2 = null;
   
   /**
    * Address Line 3 member variable.
    */
   private String _AddrLine3 = null;
   
   /**
    * Address Line 4 member variable.
    */
   private String _AddrLine4 = null;
   
   /**
    * Address Line 5 member variable.
    */
   private String _AddrLine5 = null;
   
   /**
    * City member variable.
    */
   private String _City = null;
   
   /**
    * Country Description member variable.
    */
   private String _CountryDesc = null;
   
   /**
    * Country Code member variable.
    */
   private String _CountryCode = null;
   
   /**
    * Postal Code member variable.
    */
   private String _PostalCode = null;
   
   /**
    * Joint Survivor Type member variable.
    */
   private String _JointSurvivorType = null;
   
   /**
    * Tax Jurisdiction Code member variable.
    */
   private String _TaxCode = null;
   
   /**
    * Recipient Type member variable.
    */
   private String _RecipientType = null;
   
   /**
    * Account Type member variable.
    */
   private String _AccountType = null;
   
   /**
    * Registered Address Code member variable.
    */
   private String _RegAdcd = null;
   
   /**
    * FedBN member variable.
    */
   private String _BusinessNo = null;
   
   private int _RepeatCount = 0;
   
   /**
    * ESG Standard for Salutation member array.
    */
   private String[] _TitleCode = null;
   
   /**
    * Last Name member array.
    */
   private String[] _LastName = null;
   
   /**
    * First Name member array.
    */
   private String[] _FirstName = null;
   
   /**
    * Birth Date member array.
    */
   private Date[] _BirthDate = null;
   
   /**
    * Gender member array.
    */
   private String[] _Gender = null;
   
   /**
    * Language member array.
    */
   private String[] _Lang = null;
   
   /**
    * E-mail member array.
    */
   private String[] _Email = null;
   
   /**
    * Phone Number Allocation member array.
    */
   private String[] _PhoneLocation = null;
   
   /**
    * Phone Number Type member array.
    */
   private String[] _PhoneType = null;
   
   /**
    * Phone Number Area Code member array.
    */
   private String[] _PhoneAreaCode = null;
   
   /**
    * Phone Number member array.
    */
   private String[] _PhoneNum = null;
   
   /**
    * Phone Number Extension member array.
    */
   private String[] _PhoneNumExt = null;
   
   /**
    * Social Insurance Number member array.
    */
   private String[] _SIN = null;
   
   /**
    * Entity Type member array.
    */
   private String[] _EntityType = null;
   
   /**
    * BenType member array.
    */
   private Boolean[] _BenType = null;
   
   /**
    * BenRel member array.
    */
   private String[] _BenRel = null;
   
   /**
    * BenPercentage member array.
    */
   private String[] _BenPercentage = null;
   
   /**
    * Annuitant Address Line 1 member array.
    */
   private String[] _AnnuitantAddrLine1 = null;
   
   /**
    * Annuitant Address Line 2 member array.
    */
   private String[] _AnnuitantAddrLine2 = null;
   
   /**
    * Annuitant Address Line 3 member array.
    */
   private String[] _AnnuitantAddrLine3 = null;
   
   /**
    * Annuitant Address Line 4 member array.
    */
   private String[] _AnnuitantAddrLine4 = null;
   
   /**
    * Annuitant Address Line 5 member array.
    */
   private String[] _AnnuitantAddrLine5 = null;
   
   /**
    * Annuitant City member array.
    */
   private String[] _AnnuitantCity = null;
   
   /**
    * Annuitant Cntry Desc member array.
    */
   private String[] _AnnuitantCntryDesc = null;
   
   /**
    * Annuitant Cntry Code member array.
    */
   private String[] _AnnuitantCntryCode = null;
   
   /**
    * Postal Code member array.
    */
   private String[] _PSTLCode = null;
   
   /**
    * Annuitant Address Code member array.
    */
   private String[] _AnnuitantAddrCode = null;
   
   /**
    * IDVerify tag member array.
    */
   private Boolean[] _IDVerifyExists = null;
   
   /**
    * IDType member array.
    */
   private String[] _FcomIDType = null;
   
   /**
    * OtherDscrp member array.
    */
   private String[] _OtherDescription = null;
   
   /**
    * IDNum member array.
    */
   private String[] _FcomIDNum = null;
   
   /**
    * Country member array.
    */
   private String[] _IDCountry = null;
   
   /**
    * ProvState member array.
    */
   private String[] _IDProvState = null;
   

   /**
    * Constructs the DemInqView object.
    * 
    */
   public DemInqView()
   {
      super ( new DemInqRequest() );
   }

   /**
    * Constructs the DemInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public DemInqView( String hostEncoding )
   {
      super ( new DemInqRequest( hostEncoding ) );
   }

   /**
    * Gets the DemInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The DemInqRequest object.
    */
   public final DemInqRequest getRequest()
   {
      return (DemInqRequest)getIFastRequest();
   }
        
   /**
    * Gets the Intermediary Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Intermediary Code or null.
    */
   public final String getIntermCode()
   {
      return _IntermCode;
   }
	
   /**
    * Gets the Intermediary Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Intermediary Code or the specified default value.
    */
   public final String getIntermCode( String defaultValue )
   {
      return _IntermCode == null ? defaultValue : _IntermCode;
   }
                  
   /**
    * Gets the Address Line 1 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Address Line 1 or null.
    */
   public final String getAddrLine1()
   {
      return _AddrLine1;
   }
	
   /**
    * Gets the Address Line 1 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Line 1 or the specified default value.
    */
   public final String getAddrLine1( String defaultValue )
   {
      return _AddrLine1 == null ? defaultValue : _AddrLine1;
   }
                  
   /**
    * Gets the Address Line 2 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Address Line 2 or null.
    */
   public final String getAddrLine2()
   {
      return _AddrLine2;
   }
	
   /**
    * Gets the Address Line 2 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Line 2 or the specified default value.
    */
   public final String getAddrLine2( String defaultValue )
   {
      return _AddrLine2 == null ? defaultValue : _AddrLine2;
   }
                  
   /**
    * Gets the Address Line 3 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Address Line 3 or null.
    */
   public final String getAddrLine3()
   {
      return _AddrLine3;
   }
	
   /**
    * Gets the Address Line 3 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Line 3 or the specified default value.
    */
   public final String getAddrLine3( String defaultValue )
   {
      return _AddrLine3 == null ? defaultValue : _AddrLine3;
   }
                  
   /**
    * Gets the Address Line 4 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Address Line 4 or null.
    */
   public final String getAddrLine4()
   {
      return _AddrLine4;
   }
	
   /**
    * Gets the Address Line 4 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Line 4 or the specified default value.
    */
   public final String getAddrLine4( String defaultValue )
   {
      return _AddrLine4 == null ? defaultValue : _AddrLine4;
   }
                  
   /**
    * Gets the Address Line 5 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Address Line 5 or null.
    */
   public final String getAddrLine5()
   {
      return _AddrLine5;
   }
	
   /**
    * Gets the Address Line 5 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Line 5 or the specified default value.
    */
   public final String getAddrLine5( String defaultValue )
   {
      return _AddrLine5 == null ? defaultValue : _AddrLine5;
   }
                  
   /**
    * Gets the City field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the City or null.
    */
   public final String getCity()
   {
      return _City;
   }
	
   /**
    * Gets the City field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the City or the specified default value.
    */
   public final String getCity( String defaultValue )
   {
      return _City == null ? defaultValue : _City;
   }
                  
   /**
    * Gets the Country Description field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Country Description or null.
    */
   public final String getCountryDesc()
   {
      return _CountryDesc;
   }
	
   /**
    * Gets the Country Description field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Country Description or the specified default value.
    */
   public final String getCountryDesc( String defaultValue )
   {
      return _CountryDesc == null ? defaultValue : _CountryDesc;
   }
                  
   /**
    * Gets the Country Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Country Code or null.
    */
   public final String getCountryCode()
   {
      return _CountryCode;
   }
	
   /**
    * Gets the Country Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Country Code or the specified default value.
    */
   public final String getCountryCode( String defaultValue )
   {
      return _CountryCode == null ? defaultValue : _CountryCode;
   }
                  
   /**
    * Gets the Postal Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Postal Code or null.
    */
   public final String getPostalCode()
   {
      return _PostalCode;
   }
	
   /**
    * Gets the Postal Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Postal Code or the specified default value.
    */
   public final String getPostalCode( String defaultValue )
   {
      return _PostalCode == null ? defaultValue : _PostalCode;
   }
                  
   /**
    * Gets the Joint Survivor Type field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Joint Survivor Type or null.
    */
   public final String getJointSurvivorType()
   {
      return _JointSurvivorType;
   }
	
   /**
    * Gets the Joint Survivor Type field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Joint Survivor Type or the specified default value.
    */
   public final String getJointSurvivorType( String defaultValue )
   {
      return _JointSurvivorType == null ? defaultValue : _JointSurvivorType;
   }
                  
   /**
    * Gets the Tax Jurisdiction Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Tax Jurisdiction Code or null.
    */
   public final String getTaxCode()
   {
      return _TaxCode;
   }
	
   /**
    * Gets the Tax Jurisdiction Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Jurisdiction Code or the specified default value.
    */
   public final String getTaxCode( String defaultValue )
   {
      return _TaxCode == null ? defaultValue : _TaxCode;
   }
                  
   /**
    * Gets the Recipient Type field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Recipient Type or null.
    */
   public final String getRecipientType()
   {
      return _RecipientType;
   }
	
   /**
    * Gets the Recipient Type field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Recipient Type or the specified default value.
    */
   public final String getRecipientType( String defaultValue )
   {
      return _RecipientType == null ? defaultValue : _RecipientType;
   }
                  
   /**
    * Gets the Account Type field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Account Type or null.
    */
   public final String getAccountType()
   {
      return _AccountType;
   }
	
   /**
    * Gets the Account Type field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Type or the specified default value.
    */
   public final String getAccountType( String defaultValue )
   {
      return _AccountType == null ? defaultValue : _AccountType;
   }
                  
   /**
    * Gets the Registered Address Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Registered Address Code or null.
    */
   public final String getRegAdcd()
   {
      return _RegAdcd;
   }
	
   /**
    * Gets the Registered Address Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Registered Address Code or the specified default value.
    */
   public final String getRegAdcd( String defaultValue )
   {
      return _RegAdcd == null ? defaultValue : _RegAdcd;
   }
                  
   /**
    * Gets the FedBN field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the FedBN or null.
    */
   public final String getBusinessNo()
   {
      return _BusinessNo;
   }
	
   /**
    * Gets the FedBN field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FedBN or the specified default value.
    */
   public final String getBusinessNo( String defaultValue )
   {
      return _BusinessNo == null ? defaultValue : _BusinessNo;
   }
                  
   /**
    * Gets the Record Count for the repeatable response.
    * 
    * @return The number of records in the repeating fields.
    */
   public int getRecordCount()
   {
      return _RepeatCount;
   }

   /**
    * Gets the Record Count for the repeatable response.
    * 
    * @return The number of records in the repeating fields.
    */
   public final int getRepeatCount()
   {
      return _RepeatCount;
   }

   /**
    * Decodes the repeat count value from the host 
    * respones.
    * 
    * @param response Host formatted response object.
    * @exception ParseException
    */
   private final void decodeRepeatCount( RTSResponseDecodeBuffer responseBuffer ) throws ParseException, UnsupportedEncodingException
   {
      int receivedRecordCount = responseBuffer.decodeInteger(responseBuffer.getNextField()).intValue();
      _RepeatCount += receivedRecordCount;
   }

   /**
    * Gets the ESG Standard for Salutation field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ESG Standard for Salutation or null.
    */
   public final String getTitleCode( int index )
   {
      return _TitleCode[index];
   }
    
   /**
    * Gets the ESG Standard for Salutation field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ESG Standard for Salutation or the specified default value.
    */
   public final String getTitleCode( int index, String defaultValue )
   {
      return _TitleCode[index] == null ? defaultValue : _TitleCode[index];
   }
    
   /**
    * Gets the array of ESG Standard for Salutation fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ESG Standard for Salutation values.
    */
   public final String[] getTitleCodeArray()
   {
      return _TitleCode;
   }
    
   /**
    * Gets the Last Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Last Name or null.
    */
   public final String getLastName( int index )
   {
      return _LastName[index];
   }
    
   /**
    * Gets the Last Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Last Name or the specified default value.
    */
   public final String getLastName( int index, String defaultValue )
   {
      return _LastName[index] == null ? defaultValue : _LastName[index];
   }
    
   /**
    * Gets the array of Last Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Last Name values.
    */
   public final String[] getLastNameArray()
   {
      return _LastName;
   }
    
   /**
    * Gets the First Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the First Name or null.
    */
   public final String getFirstName( int index )
   {
      return _FirstName[index];
   }
    
   /**
    * Gets the First Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the First Name or the specified default value.
    */
   public final String getFirstName( int index, String defaultValue )
   {
      return _FirstName[index] == null ? defaultValue : _FirstName[index];
   }
    
   /**
    * Gets the array of First Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of First Name values.
    */
   public final String[] getFirstNameArray()
   {
      return _FirstName;
   }
    
   /**
    * Gets the Birth Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Birth Date or null.
    */
   public final Date getBirthDate( int index )
   {
      return _BirthDate[index];
   }
    
   /**
    * Gets the Birth Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Birth Date or the specified default value.
    */
   public final Date getBirthDate( int index, Date defaultValue )
   {
      return _BirthDate[index] == null ? defaultValue : _BirthDate[index];
   }
    
   /**
    * Gets the array of Birth Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Birth Date values.
    */
   public final Date[] getBirthDateArray()
   {
      return _BirthDate;
   }
    
   /**
    * Gets the Gender field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Gender or null.
    */
   public final String getGender( int index )
   {
      return _Gender[index];
   }
    
   /**
    * Gets the Gender field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Gender or the specified default value.
    */
   public final String getGender( int index, String defaultValue )
   {
      return _Gender[index] == null ? defaultValue : _Gender[index];
   }
    
   /**
    * Gets the array of Gender fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Gender values.
    */
   public final String[] getGenderArray()
   {
      return _Gender;
   }
    
   /**
    * Gets the Language field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Language or null.
    */
   public final String getLang( int index )
   {
      return _Lang[index];
   }
    
   /**
    * Gets the Language field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Language or the specified default value.
    */
   public final String getLang( int index, String defaultValue )
   {
      return _Lang[index] == null ? defaultValue : _Lang[index];
   }
    
   /**
    * Gets the array of Language fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Language values.
    */
   public final String[] getLangArray()
   {
      return _Lang;
   }
    
   /**
    * Gets the E-mail field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the E-mail or null.
    */
   public final String getEmail( int index )
   {
      return _Email[index];
   }
    
   /**
    * Gets the E-mail field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the E-mail or the specified default value.
    */
   public final String getEmail( int index, String defaultValue )
   {
      return _Email[index] == null ? defaultValue : _Email[index];
   }
    
   /**
    * Gets the array of E-mail fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of E-mail values.
    */
   public final String[] getEmailArray()
   {
      return _Email;
   }
    
   /**
    * Gets the Phone Number Allocation field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Phone Number Allocation or null.
    */
   public final String getPhoneLocation( int index )
   {
      return _PhoneLocation[index];
   }
    
   /**
    * Gets the Phone Number Allocation field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Phone Number Allocation or the specified default value.
    */
   public final String getPhoneLocation( int index, String defaultValue )
   {
      return _PhoneLocation[index] == null ? defaultValue : _PhoneLocation[index];
   }
    
   /**
    * Gets the array of Phone Number Allocation fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Phone Number Allocation values.
    */
   public final String[] getPhoneLocationArray()
   {
      return _PhoneLocation;
   }
    
   /**
    * Gets the Phone Number Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Phone Number Type or null.
    */
   public final String getPhoneType( int index )
   {
      return _PhoneType[index];
   }
    
   /**
    * Gets the Phone Number Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Phone Number Type or the specified default value.
    */
   public final String getPhoneType( int index, String defaultValue )
   {
      return _PhoneType[index] == null ? defaultValue : _PhoneType[index];
   }
    
   /**
    * Gets the array of Phone Number Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Phone Number Type values.
    */
   public final String[] getPhoneTypeArray()
   {
      return _PhoneType;
   }
    
   /**
    * Gets the Phone Number Area Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Phone Number Area Code or null.
    */
   public final String getPhoneAreaCode( int index )
   {
      return _PhoneAreaCode[index];
   }
    
   /**
    * Gets the Phone Number Area Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Phone Number Area Code or the specified default value.
    */
   public final String getPhoneAreaCode( int index, String defaultValue )
   {
      return _PhoneAreaCode[index] == null ? defaultValue : _PhoneAreaCode[index];
   }
    
   /**
    * Gets the array of Phone Number Area Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Phone Number Area Code values.
    */
   public final String[] getPhoneAreaCodeArray()
   {
      return _PhoneAreaCode;
   }
    
   /**
    * Gets the Phone Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Phone Number or null.
    */
   public final String getPhoneNum( int index )
   {
      return _PhoneNum[index];
   }
    
   /**
    * Gets the Phone Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Phone Number or the specified default value.
    */
   public final String getPhoneNum( int index, String defaultValue )
   {
      return _PhoneNum[index] == null ? defaultValue : _PhoneNum[index];
   }
    
   /**
    * Gets the array of Phone Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Phone Number values.
    */
   public final String[] getPhoneNumArray()
   {
      return _PhoneNum;
   }
    
   /**
    * Gets the Phone Number Extension field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Phone Number Extension or null.
    */
   public final String getPhoneNumExt( int index )
   {
      return _PhoneNumExt[index];
   }
    
   /**
    * Gets the Phone Number Extension field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Phone Number Extension or the specified default value.
    */
   public final String getPhoneNumExt( int index, String defaultValue )
   {
      return _PhoneNumExt[index] == null ? defaultValue : _PhoneNumExt[index];
   }
    
   /**
    * Gets the array of Phone Number Extension fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Phone Number Extension values.
    */
   public final String[] getPhoneNumExtArray()
   {
      return _PhoneNumExt;
   }
    
   /**
    * Gets the Social Insurance Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Social Insurance Number or null.
    */
   public final String getSIN( int index )
   {
      return _SIN[index];
   }
    
   /**
    * Gets the Social Insurance Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Social Insurance Number or the specified default value.
    */
   public final String getSIN( int index, String defaultValue )
   {
      return _SIN[index] == null ? defaultValue : _SIN[index];
   }
    
   /**
    * Gets the array of Social Insurance Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Social Insurance Number values.
    */
   public final String[] getSINArray()
   {
      return _SIN;
   }
    
   /**
    * Gets the Entity Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Entity Type or null.
    */
   public final String getEntityType( int index )
   {
      return _EntityType[index];
   }
    
   /**
    * Gets the Entity Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Entity Type or the specified default value.
    */
   public final String getEntityType( int index, String defaultValue )
   {
      return _EntityType[index] == null ? defaultValue : _EntityType[index];
   }
    
   /**
    * Gets the array of Entity Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Entity Type values.
    */
   public final String[] getEntityTypeArray()
   {
      return _EntityType;
   }
    
   /**
    * Gets the BenType field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the BenType or null.
    */
   public final Boolean getBenType( int index )
   {
      return _BenType[index];
   }
    
   /**
    * Gets the BenType field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the BenType or the specified default value.
    */
   public final boolean getBenType( int index, boolean defaultValue )
   {
      return _BenType[index] == null ? defaultValue : _BenType[index].booleanValue();
   }
    
   /**
    * Gets the array of BenType fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of BenType values.
    */
   public final Boolean[] getBenTypeArray()
   {
      return _BenType;
   }
    
   /**
    * Gets the BenRel field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the BenRel or null.
    */
   public final String getBenRel( int index )
   {
      return _BenRel[index];
   }
    
   /**
    * Gets the BenRel field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the BenRel or the specified default value.
    */
   public final String getBenRel( int index, String defaultValue )
   {
      return _BenRel[index] == null ? defaultValue : _BenRel[index];
   }
    
   /**
    * Gets the array of BenRel fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of BenRel values.
    */
   public final String[] getBenRelArray()
   {
      return _BenRel;
   }
    
   /**
    * Gets the BenPercentage field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the BenPercentage or null.
    */
   public final String getBenPercentage( int index )
   {
      return _BenPercentage[index];
   }
    
   /**
    * Gets the BenPercentage field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the BenPercentage or the specified default value.
    */
   public final String getBenPercentage( int index, String defaultValue )
   {
      return _BenPercentage[index] == null ? defaultValue : _BenPercentage[index];
   }
    
   /**
    * Gets the array of BenPercentage fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of BenPercentage values.
    */
   public final String[] getBenPercentageArray()
   {
      return _BenPercentage;
   }
    
   /**
    * Gets the Annuitant Address Line 1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Annuitant Address Line 1 or null.
    */
   public final String getAnnuitantAddrLine1( int index )
   {
      return _AnnuitantAddrLine1[index];
   }
    
   /**
    * Gets the Annuitant Address Line 1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Annuitant Address Line 1 or the specified default value.
    */
   public final String getAnnuitantAddrLine1( int index, String defaultValue )
   {
      return _AnnuitantAddrLine1[index] == null ? defaultValue : _AnnuitantAddrLine1[index];
   }
    
   /**
    * Gets the array of Annuitant Address Line 1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Annuitant Address Line 1 values.
    */
   public final String[] getAnnuitantAddrLine1Array()
   {
      return _AnnuitantAddrLine1;
   }
    
   /**
    * Gets the Annuitant Address Line 2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Annuitant Address Line 2 or null.
    */
   public final String getAnnuitantAddrLine2( int index )
   {
      return _AnnuitantAddrLine2[index];
   }
    
   /**
    * Gets the Annuitant Address Line 2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Annuitant Address Line 2 or the specified default value.
    */
   public final String getAnnuitantAddrLine2( int index, String defaultValue )
   {
      return _AnnuitantAddrLine2[index] == null ? defaultValue : _AnnuitantAddrLine2[index];
   }
    
   /**
    * Gets the array of Annuitant Address Line 2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Annuitant Address Line 2 values.
    */
   public final String[] getAnnuitantAddrLine2Array()
   {
      return _AnnuitantAddrLine2;
   }
    
   /**
    * Gets the Annuitant Address Line 3 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Annuitant Address Line 3 or null.
    */
   public final String getAnnuitantAddrLine3( int index )
   {
      return _AnnuitantAddrLine3[index];
   }
    
   /**
    * Gets the Annuitant Address Line 3 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Annuitant Address Line 3 or the specified default value.
    */
   public final String getAnnuitantAddrLine3( int index, String defaultValue )
   {
      return _AnnuitantAddrLine3[index] == null ? defaultValue : _AnnuitantAddrLine3[index];
   }
    
   /**
    * Gets the array of Annuitant Address Line 3 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Annuitant Address Line 3 values.
    */
   public final String[] getAnnuitantAddrLine3Array()
   {
      return _AnnuitantAddrLine3;
   }
    
   /**
    * Gets the Annuitant Address Line 4 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Annuitant Address Line 4 or null.
    */
   public final String getAnnuitantAddrLine4( int index )
   {
      return _AnnuitantAddrLine4[index];
   }
    
   /**
    * Gets the Annuitant Address Line 4 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Annuitant Address Line 4 or the specified default value.
    */
   public final String getAnnuitantAddrLine4( int index, String defaultValue )
   {
      return _AnnuitantAddrLine4[index] == null ? defaultValue : _AnnuitantAddrLine4[index];
   }
    
   /**
    * Gets the array of Annuitant Address Line 4 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Annuitant Address Line 4 values.
    */
   public final String[] getAnnuitantAddrLine4Array()
   {
      return _AnnuitantAddrLine4;
   }
    
   /**
    * Gets the Annuitant Address Line 5 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Annuitant Address Line 5 or null.
    */
   public final String getAnnuitantAddrLine5( int index )
   {
      return _AnnuitantAddrLine5[index];
   }
    
   /**
    * Gets the Annuitant Address Line 5 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Annuitant Address Line 5 or the specified default value.
    */
   public final String getAnnuitantAddrLine5( int index, String defaultValue )
   {
      return _AnnuitantAddrLine5[index] == null ? defaultValue : _AnnuitantAddrLine5[index];
   }
    
   /**
    * Gets the array of Annuitant Address Line 5 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Annuitant Address Line 5 values.
    */
   public final String[] getAnnuitantAddrLine5Array()
   {
      return _AnnuitantAddrLine5;
   }
    
   /**
    * Gets the Annuitant City field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Annuitant City or null.
    */
   public final String getAnnuitantCity( int index )
   {
      return _AnnuitantCity[index];
   }
    
   /**
    * Gets the Annuitant City field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Annuitant City or the specified default value.
    */
   public final String getAnnuitantCity( int index, String defaultValue )
   {
      return _AnnuitantCity[index] == null ? defaultValue : _AnnuitantCity[index];
   }
    
   /**
    * Gets the array of Annuitant City fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Annuitant City values.
    */
   public final String[] getAnnuitantCityArray()
   {
      return _AnnuitantCity;
   }
    
   /**
    * Gets the Annuitant Cntry Desc field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Annuitant Cntry Desc or null.
    */
   public final String getAnnuitantCntryDesc( int index )
   {
      return _AnnuitantCntryDesc[index];
   }
    
   /**
    * Gets the Annuitant Cntry Desc field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Annuitant Cntry Desc or the specified default value.
    */
   public final String getAnnuitantCntryDesc( int index, String defaultValue )
   {
      return _AnnuitantCntryDesc[index] == null ? defaultValue : _AnnuitantCntryDesc[index];
   }
    
   /**
    * Gets the array of Annuitant Cntry Desc fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Annuitant Cntry Desc values.
    */
   public final String[] getAnnuitantCntryDescArray()
   {
      return _AnnuitantCntryDesc;
   }
    
   /**
    * Gets the Annuitant Cntry Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Annuitant Cntry Code or null.
    */
   public final String getAnnuitantCntryCode( int index )
   {
      return _AnnuitantCntryCode[index];
   }
    
   /**
    * Gets the Annuitant Cntry Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Annuitant Cntry Code or the specified default value.
    */
   public final String getAnnuitantCntryCode( int index, String defaultValue )
   {
      return _AnnuitantCntryCode[index] == null ? defaultValue : _AnnuitantCntryCode[index];
   }
    
   /**
    * Gets the array of Annuitant Cntry Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Annuitant Cntry Code values.
    */
   public final String[] getAnnuitantCntryCodeArray()
   {
      return _AnnuitantCntryCode;
   }
    
   /**
    * Gets the Postal Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Postal Code or null.
    */
   public final String getPSTLCode( int index )
   {
      return _PSTLCode[index];
   }
    
   /**
    * Gets the Postal Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Postal Code or the specified default value.
    */
   public final String getPSTLCode( int index, String defaultValue )
   {
      return _PSTLCode[index] == null ? defaultValue : _PSTLCode[index];
   }
    
   /**
    * Gets the array of Postal Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Postal Code values.
    */
   public final String[] getPSTLCodeArray()
   {
      return _PSTLCode;
   }
    
   /**
    * Gets the Annuitant Address Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Annuitant Address Code or null.
    */
   public final String getAnnuitantAddrCode( int index )
   {
      return _AnnuitantAddrCode[index];
   }
    
   /**
    * Gets the Annuitant Address Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Annuitant Address Code or the specified default value.
    */
   public final String getAnnuitantAddrCode( int index, String defaultValue )
   {
      return _AnnuitantAddrCode[index] == null ? defaultValue : _AnnuitantAddrCode[index];
   }
    
   /**
    * Gets the array of Annuitant Address Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Annuitant Address Code values.
    */
   public final String[] getAnnuitantAddrCodeArray()
   {
      return _AnnuitantAddrCode;
   }
    
   /**
    * Gets the IDVerify tag field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the IDVerify tag or null.
    */
   public final Boolean getIDVerifyExists( int index )
   {
      return _IDVerifyExists[index];
   }
    
   /**
    * Gets the IDVerify tag field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the IDVerify tag or the specified default value.
    */
   public final boolean getIDVerifyExists( int index, boolean defaultValue )
   {
      return _IDVerifyExists[index] == null ? defaultValue : _IDVerifyExists[index].booleanValue();
   }
    
   /**
    * Gets the array of IDVerify tag fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of IDVerify tag values.
    */
   public final Boolean[] getIDVerifyExistsArray()
   {
      return _IDVerifyExists;
   }
    
   /**
    * Gets the IDType field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the IDType or null.
    */
   public final String getFcomIDType( int index )
   {
      return _FcomIDType[index];
   }
    
   /**
    * Gets the IDType field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the IDType or the specified default value.
    */
   public final String getFcomIDType( int index, String defaultValue )
   {
      return _FcomIDType[index] == null ? defaultValue : _FcomIDType[index];
   }
    
   /**
    * Gets the array of IDType fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of IDType values.
    */
   public final String[] getFcomIDTypeArray()
   {
      return _FcomIDType;
   }
    
   /**
    * Gets the OtherDscrp field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the OtherDscrp or null.
    */
   public final String getOtherDescription( int index )
   {
      return _OtherDescription[index];
   }
    
   /**
    * Gets the OtherDscrp field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the OtherDscrp or the specified default value.
    */
   public final String getOtherDescription( int index, String defaultValue )
   {
      return _OtherDescription[index] == null ? defaultValue : _OtherDescription[index];
   }
    
   /**
    * Gets the array of OtherDscrp fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of OtherDscrp values.
    */
   public final String[] getOtherDescriptionArray()
   {
      return _OtherDescription;
   }
    
   /**
    * Gets the IDNum field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the IDNum or null.
    */
   public final String getFcomIDNum( int index )
   {
      return _FcomIDNum[index];
   }
    
   /**
    * Gets the IDNum field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the IDNum or the specified default value.
    */
   public final String getFcomIDNum( int index, String defaultValue )
   {
      return _FcomIDNum[index] == null ? defaultValue : _FcomIDNum[index];
   }
    
   /**
    * Gets the array of IDNum fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of IDNum values.
    */
   public final String[] getFcomIDNumArray()
   {
      return _FcomIDNum;
   }
    
   /**
    * Gets the Country field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Country or null.
    */
   public final String getIDCountry( int index )
   {
      return _IDCountry[index];
   }
    
   /**
    * Gets the Country field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Country or the specified default value.
    */
   public final String getIDCountry( int index, String defaultValue )
   {
      return _IDCountry[index] == null ? defaultValue : _IDCountry[index];
   }
    
   /**
    * Gets the array of Country fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Country values.
    */
   public final String[] getIDCountryArray()
   {
      return _IDCountry;
   }
    
   /**
    * Gets the ProvState field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ProvState or null.
    */
   public final String getIDProvState( int index )
   {
      return _IDProvState[index];
   }
    
   /**
    * Gets the ProvState field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ProvState or the specified default value.
    */
   public final String getIDProvState( int index, String defaultValue )
   {
      return _IDProvState[index] == null ? defaultValue : _IDProvState[index];
   }
    
   /**
    * Gets the array of ProvState fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ProvState values.
    */
   public final String[] getIDProvStateArray()
   {
      return _IDProvState;
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
      decodeMoreAvailableField( responseBuffer );
      decodeNextKeyField( responseBuffer );
      _IntermCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _AddrLine1 = responseBuffer.decodeString(responseBuffer.getNextField());
      _AddrLine2 = responseBuffer.decodeString(responseBuffer.getNextField());
      _AddrLine3 = responseBuffer.decodeString(responseBuffer.getNextField());
      _AddrLine4 = responseBuffer.decodeString(responseBuffer.getNextField());
      _AddrLine5 = responseBuffer.decodeString(responseBuffer.getNextField());
      _City = responseBuffer.decodeString(responseBuffer.getNextField());
      _CountryDesc = responseBuffer.decodeString(responseBuffer.getNextField());
      _CountryCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _PostalCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _JointSurvivorType = responseBuffer.decodeString(responseBuffer.getNextField());
      _TaxCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _RecipientType = responseBuffer.decodeString(responseBuffer.getNextField());
      _AccountType = responseBuffer.decodeString(responseBuffer.getNextField());
      _RegAdcd = responseBuffer.decodeString(responseBuffer.getNextField());
      _BusinessNo = responseBuffer.decodeString(responseBuffer.getNextField());
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _TitleCode = resizeArray( _TitleCode, _RepeatCount );
      _LastName = resizeArray( _LastName, _RepeatCount );
      _FirstName = resizeArray( _FirstName, _RepeatCount );
      _BirthDate = resizeArray( _BirthDate, _RepeatCount );
      _Gender = resizeArray( _Gender, _RepeatCount );
      _Lang = resizeArray( _Lang, _RepeatCount );
      _Email = resizeArray( _Email, _RepeatCount );
      _PhoneLocation = resizeArray( _PhoneLocation, _RepeatCount );
      _PhoneType = resizeArray( _PhoneType, _RepeatCount );
      _PhoneAreaCode = resizeArray( _PhoneAreaCode, _RepeatCount );
      _PhoneNum = resizeArray( _PhoneNum, _RepeatCount );
      _PhoneNumExt = resizeArray( _PhoneNumExt, _RepeatCount );
      _SIN = resizeArray( _SIN, _RepeatCount );
      _EntityType = resizeArray( _EntityType, _RepeatCount );
      _BenType = resizeArray( _BenType, _RepeatCount );
      _BenRel = resizeArray( _BenRel, _RepeatCount );
      _BenPercentage = resizeArray( _BenPercentage, _RepeatCount );
      _AnnuitantAddrLine1 = resizeArray( _AnnuitantAddrLine1, _RepeatCount );
      _AnnuitantAddrLine2 = resizeArray( _AnnuitantAddrLine2, _RepeatCount );
      _AnnuitantAddrLine3 = resizeArray( _AnnuitantAddrLine3, _RepeatCount );
      _AnnuitantAddrLine4 = resizeArray( _AnnuitantAddrLine4, _RepeatCount );
      _AnnuitantAddrLine5 = resizeArray( _AnnuitantAddrLine5, _RepeatCount );
      _AnnuitantCity = resizeArray( _AnnuitantCity, _RepeatCount );
      _AnnuitantCntryDesc = resizeArray( _AnnuitantCntryDesc, _RepeatCount );
      _AnnuitantCntryCode = resizeArray( _AnnuitantCntryCode, _RepeatCount );
      _PSTLCode = resizeArray( _PSTLCode, _RepeatCount );
      _AnnuitantAddrCode = resizeArray( _AnnuitantAddrCode, _RepeatCount );
      _IDVerifyExists = resizeArray( _IDVerifyExists, _RepeatCount );
      _FcomIDType = resizeArray( _FcomIDType, _RepeatCount );
      _OtherDescription = resizeArray( _OtherDescription, _RepeatCount );
      _FcomIDNum = resizeArray( _FcomIDNum, _RepeatCount );
      _IDCountry = resizeArray( _IDCountry, _RepeatCount );
      _IDProvState = resizeArray( _IDProvState, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _TitleCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LastName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FirstName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BirthDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _Gender[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Lang[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Email[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PhoneLocation[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PhoneType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PhoneAreaCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PhoneNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PhoneNumExt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SIN[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EntityType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BenType[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _BenRel[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BenPercentage[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AnnuitantAddrLine1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AnnuitantAddrLine2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AnnuitantAddrLine3[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AnnuitantAddrLine4[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AnnuitantAddrLine5[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AnnuitantCity[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AnnuitantCntryDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AnnuitantCntryCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PSTLCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AnnuitantAddrCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IDVerifyExists[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _FcomIDType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _OtherDescription[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FcomIDNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IDCountry[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IDProvState[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
