
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Search for shareholder/account Enitty view.
 * For additional view information see <A HREF="../../../../viewspecs/ShareholderSearch.doc">ShareholderSearch.doc</A>.
 * 
 * @author RTS Generated
 */
public class ShareholderSearchView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Account Number member array.
    */
   private String[] _AccountNum = null;
   
   /**
    * Shareholder Number member array.
    */
   private String[] _ShrNum = null;
   
   /**
    * Last Name member array.
    */
   private String[] _LastName = null;
   
   /**
    * First Name member array.
    */
   private String[] _FirstName = null;
   
   /**
    * Birth Last Name member array.
    */
   private String[] _BirthLastName = null;
   
   /**
    * Birth First Name member array.
    */
   private String[] _BirthFirstName = null;
   
   /**
    * S.I.N. Number member array.
    */
   private String[] _SIN = null;
   
   /**
    * Date of Birth member array.
    */
   private Date[] _BirthDate = null;
   
   /**
    * Tax Type member array.
    */
   private String[] _TaxType = null;
   
   /**
    * Tax Type Description member array.
    */
   private String[] _TaxTypeDesc = null;
   
   /**
    * Home Phone Number member array.
    */
   private String[] _HomePhone = null;
   
   /**
    * Multiple Account Relationship member array.
    */
   private Boolean[] _MultipleReln = null;
   
   /**
    * Entity ID member array.
    */
   private String[] _EntityId = null;
   
   /**
    * Address Line 1 member array.
    */
   private String[] _Address1 = null;
   
   /**
    * Address Line 2 member array.
    */
   private String[] _Address2 = null;
   
   /**
    * Address Line 3 member array.
    */
   private String[] _Address3 = null;
   
   /**
    * Address Line 4 member array.
    */
   private String[] _Address4 = null;
   
   /**
    * Address Line 5 member array.
    */
   private String[] _Address5 = null;
   
   /**
    * Postal Code member array.
    */
   private String[] _PostalCode = null;
   
   /**
    * Kana Address Line1 member array.
    */
   private String[] _kAddrLine1 = null;
   
   /**
    * Kana Address Line2 member array.
    */
   private String[] _kAddrLine2 = null;
   
   /**
    * Kana Address Line3 member array.
    */
   private String[] _kAddrLine3 = null;
   
   /**
    * Kana Address Line4 member array.
    */
   private String[] _kAddrLine4 = null;
   
   /**
    * Kana Address Line5 member array.
    */
   private String[] _kAddrLine5 = null;
   
   /**
    * Kana Postal Code member array.
    */
   private String[] _kPostalCode = null;
   
   /**
    * ID Type  1 member array.
    */
   private String[] _IdType1 = null;
   
   /**
    * ID Value 1 member array.
    */
   private String[] _IdValue1 = null;
   
   /**
    * ID Type  2 member array.
    */
   private String[] _IdType2 = null;
   
   /**
    * ID Value 2 member array.
    */
   private String[] _IdValue2 = null;
   
   /**
    * ID Type  3 member array.
    */
   private String[] _IdType3 = null;
   
   /**
    * ID Value 3 member array.
    */
   private String[] _IdValue3 = null;
   
   /**
    * ID Type  4 member array.
    */
   private String[] _IdType4 = null;
   
   /**
    * ID Value 4 member array.
    */
   private String[] _IdValue4 = null;
   
   /**
    * ID Type  5 member array.
    */
   private String[] _IdType5 = null;
   
   /**
    * ID Value 5 member array.
    */
   private String[] _IdValue5 = null;
   
   /**
    * ID Type  6 member array.
    */
   private String[] _IdType6 = null;
   
   /**
    * ID Value 6 member array.
    */
   private String[] _IdValue6 = null;
   
   /**
    * ID Type  7 member array.
    */
   private String[] _IdType7 = null;
   
   /**
    * ID Value 7 member array.
    */
   private String[] _IdValue7 = null;
   
   /**
    * ID Type  8 member array.
    */
   private String[] _IdType8 = null;
   
   /**
    * ID Value 8 member array.
    */
   private String[] _IdValue8 = null;
   
   /**
    * ID Type  9 member array.
    */
   private String[] _IdType9 = null;
   
   /**
    * ID Value 9 member array.
    */
   private String[] _IdValue9 = null;
   
   /**
    * ID Type  10 member array.
    */
   private String[] _IdType10 = null;
   
   /**
    * ID Value 10 member array.
    */
   private String[] _IdValue10 = null;
   
   /**
    * Entity Type member array.
    */
   private String[] _EntityType = null;
   
   /**
    * Entity Type Sequence member array.
    */
   private Integer[] _EntityTypeSeq = null;
   
   /**
    * Account Type member array.
    */
   private String[] _AcctType = null;
   
   /**
    * Country Code member array.
    */
   private String[] _CountryCode = null;
   
   /**
    * Social Code member array.
    */
   private String[] _SocialCode = null;
   
   /**
    * Social Code description member array.
    */
   private String[] _SocialCodeDesc = null;
   
   /**
    * Account Designation member array.
    */
   private String[] _AcctDes = null;
   
   /**
    * Account Status member array.
    */
   private String[] _AcctStatus = null;
   
   /**
    * Alternate Account Number member array.
    */
   private String[] _AltAccount = null;
   
   /**
    * Account In Trust For or Joint member array.
    */
   private String[] _InTrustJoint = null;
   
   /**
    * Fund Company Code member array.
    */
   private String[] _CompanyCode = null;
   
   /**
    * Shareholder Group member array.
    */
   private String[] _AcctGroup = null;
   
   /**
    * Account Type Description member array.
    */
   private String[] _AcctTypeDesc = null;
   
   /**
    * Stop Purchase member array.
    */
   private Boolean[] _StopPurchase = null;
   
   /**
    * Stop Transfer in to the fund and class member array.
    */
   private Boolean[] _StopXferIn = null;
   
   /**
    * Stop Transfer out of the fund and class member array.
    */
   private Boolean[] _StopXferOut = null;
   
   /**
    * Stop Redemption member array.
    */
   private Boolean[] _StopRed = null;
   
   /**
    * Entity Type Description member array.
    */
   private String[] _EntityTypeDesc = null;
   
   /**
    * Wrap Account flag member array.
    */
   private Boolean[] _WrapAccount = null;
   
   /**
    * Registration Information member array.
    */
   private String[] _RegistrationInfo = null;
   
   /**
    * Entity Status member array.
    */
   private Boolean[] _EntStatus = null;
   
   /**
    * Valid RA TaxType member array.
    */
   private String[] _ValidRATaxType = null;
   

   /**
    * Constructs the ShareholderSearchView object.
    * 
    */
   public ShareholderSearchView()
   {
      super ( new ShareholderSearchRequest() );
   }

   /**
    * Constructs the ShareholderSearchView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public ShareholderSearchView( String hostEncoding )
   {
      super ( new ShareholderSearchRequest( hostEncoding ) );
   }

   /**
    * Gets the ShareholderSearchRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The ShareholderSearchRequest object.
    */
   public final ShareholderSearchRequest getRequest()
   {
      return (ShareholderSearchRequest)getIFastRequest();
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
    * Gets the Account Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Number or null.
    */
   public final String getAccountNum( int index )
   {
      return _AccountNum[index];
   }
    
   /**
    * Gets the Account Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Number or the specified default value.
    */
   public final String getAccountNum( int index, String defaultValue )
   {
      return _AccountNum[index] == null ? defaultValue : _AccountNum[index];
   }
    
   /**
    * Gets the array of Account Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Number values.
    */
   public final String[] getAccountNumArray()
   {
      return _AccountNum;
   }
    
   /**
    * Gets the Shareholder Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Shareholder Number or null.
    */
   public final String getShrNum( int index )
   {
      return _ShrNum[index];
   }
    
   /**
    * Gets the Shareholder Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Shareholder Number or the specified default value.
    */
   public final String getShrNum( int index, String defaultValue )
   {
      return _ShrNum[index] == null ? defaultValue : _ShrNum[index];
   }
    
   /**
    * Gets the array of Shareholder Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Shareholder Number values.
    */
   public final String[] getShrNumArray()
   {
      return _ShrNum;
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
    * Gets the Birth Last Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Birth Last Name or null.
    */
   public final String getBirthLastName( int index )
   {
      return _BirthLastName[index];
   }
    
   /**
    * Gets the Birth Last Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Birth Last Name or the specified default value.
    */
   public final String getBirthLastName( int index, String defaultValue )
   {
      return _BirthLastName[index] == null ? defaultValue : _BirthLastName[index];
   }
    
   /**
    * Gets the array of Birth Last Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Birth Last Name values.
    */
   public final String[] getBirthLastNameArray()
   {
      return _BirthLastName;
   }
    
   /**
    * Gets the Birth First Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Birth First Name or null.
    */
   public final String getBirthFirstName( int index )
   {
      return _BirthFirstName[index];
   }
    
   /**
    * Gets the Birth First Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Birth First Name or the specified default value.
    */
   public final String getBirthFirstName( int index, String defaultValue )
   {
      return _BirthFirstName[index] == null ? defaultValue : _BirthFirstName[index];
   }
    
   /**
    * Gets the array of Birth First Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Birth First Name values.
    */
   public final String[] getBirthFirstNameArray()
   {
      return _BirthFirstName;
   }
    
   /**
    * Gets the S.I.N. Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the S.I.N. Number or null.
    */
   public final String getSIN( int index )
   {
      return _SIN[index];
   }
    
   /**
    * Gets the S.I.N. Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the S.I.N. Number or the specified default value.
    */
   public final String getSIN( int index, String defaultValue )
   {
      return _SIN[index] == null ? defaultValue : _SIN[index];
   }
    
   /**
    * Gets the array of S.I.N. Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of S.I.N. Number values.
    */
   public final String[] getSINArray()
   {
      return _SIN;
   }
    
   /**
    * Gets the Date of Birth field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Date of Birth or null.
    */
   public final Date getBirthDate( int index )
   {
      return _BirthDate[index];
   }
    
   /**
    * Gets the Date of Birth field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Date of Birth or the specified default value.
    */
   public final Date getBirthDate( int index, Date defaultValue )
   {
      return _BirthDate[index] == null ? defaultValue : _BirthDate[index];
   }
    
   /**
    * Gets the array of Date of Birth fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Date of Birth values.
    */
   public final Date[] getBirthDateArray()
   {
      return _BirthDate;
   }
    
   /**
    * Gets the Tax Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Tax Type or null.
    */
   public final String getTaxType( int index )
   {
      return _TaxType[index];
   }
    
   /**
    * Gets the Tax Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Type or the specified default value.
    */
   public final String getTaxType( int index, String defaultValue )
   {
      return _TaxType[index] == null ? defaultValue : _TaxType[index];
   }
    
   /**
    * Gets the array of Tax Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Tax Type values.
    */
   public final String[] getTaxTypeArray()
   {
      return _TaxType;
   }
    
   /**
    * Gets the Tax Type Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Tax Type Description or null.
    */
   public final String getTaxTypeDesc( int index )
   {
      return _TaxTypeDesc[index];
   }
    
   /**
    * Gets the Tax Type Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Type Description or the specified default value.
    */
   public final String getTaxTypeDesc( int index, String defaultValue )
   {
      return _TaxTypeDesc[index] == null ? defaultValue : _TaxTypeDesc[index];
   }
    
   /**
    * Gets the array of Tax Type Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Tax Type Description values.
    */
   public final String[] getTaxTypeDescArray()
   {
      return _TaxTypeDesc;
   }
    
   /**
    * Gets the Home Phone Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Home Phone Number or null.
    */
   public final String getHomePhone( int index )
   {
      return _HomePhone[index];
   }
    
   /**
    * Gets the Home Phone Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Home Phone Number or the specified default value.
    */
   public final String getHomePhone( int index, String defaultValue )
   {
      return _HomePhone[index] == null ? defaultValue : _HomePhone[index];
   }
    
   /**
    * Gets the array of Home Phone Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Home Phone Number values.
    */
   public final String[] getHomePhoneArray()
   {
      return _HomePhone;
   }
    
   /**
    * Gets the Multiple Account Relationship field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Multiple Account Relationship or null.
    */
   public final Boolean getMultipleReln( int index )
   {
      return _MultipleReln[index];
   }
    
   /**
    * Gets the Multiple Account Relationship field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Multiple Account Relationship or the specified default value.
    */
   public final boolean getMultipleReln( int index, boolean defaultValue )
   {
      return _MultipleReln[index] == null ? defaultValue : _MultipleReln[index].booleanValue();
   }
    
   /**
    * Gets the array of Multiple Account Relationship fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Multiple Account Relationship values.
    */
   public final Boolean[] getMultipleRelnArray()
   {
      return _MultipleReln;
   }
    
   /**
    * Gets the Entity ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Entity ID or null.
    */
   public final String getEntityId( int index )
   {
      return _EntityId[index];
   }
    
   /**
    * Gets the Entity ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Entity ID or the specified default value.
    */
   public final String getEntityId( int index, String defaultValue )
   {
      return _EntityId[index] == null ? defaultValue : _EntityId[index];
   }
    
   /**
    * Gets the array of Entity ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Entity ID values.
    */
   public final String[] getEntityIdArray()
   {
      return _EntityId;
   }
    
   /**
    * Gets the Address Line 1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Line 1 or null.
    */
   public final String getAddress1( int index )
   {
      return _Address1[index];
   }
    
   /**
    * Gets the Address Line 1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Line 1 or the specified default value.
    */
   public final String getAddress1( int index, String defaultValue )
   {
      return _Address1[index] == null ? defaultValue : _Address1[index];
   }
    
   /**
    * Gets the array of Address Line 1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Line 1 values.
    */
   public final String[] getAddress1Array()
   {
      return _Address1;
   }
    
   /**
    * Gets the Address Line 2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Line 2 or null.
    */
   public final String getAddress2( int index )
   {
      return _Address2[index];
   }
    
   /**
    * Gets the Address Line 2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Line 2 or the specified default value.
    */
   public final String getAddress2( int index, String defaultValue )
   {
      return _Address2[index] == null ? defaultValue : _Address2[index];
   }
    
   /**
    * Gets the array of Address Line 2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Line 2 values.
    */
   public final String[] getAddress2Array()
   {
      return _Address2;
   }
    
   /**
    * Gets the Address Line 3 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Line 3 or null.
    */
   public final String getAddress3( int index )
   {
      return _Address3[index];
   }
    
   /**
    * Gets the Address Line 3 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Line 3 or the specified default value.
    */
   public final String getAddress3( int index, String defaultValue )
   {
      return _Address3[index] == null ? defaultValue : _Address3[index];
   }
    
   /**
    * Gets the array of Address Line 3 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Line 3 values.
    */
   public final String[] getAddress3Array()
   {
      return _Address3;
   }
    
   /**
    * Gets the Address Line 4 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Line 4 or null.
    */
   public final String getAddress4( int index )
   {
      return _Address4[index];
   }
    
   /**
    * Gets the Address Line 4 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Line 4 or the specified default value.
    */
   public final String getAddress4( int index, String defaultValue )
   {
      return _Address4[index] == null ? defaultValue : _Address4[index];
   }
    
   /**
    * Gets the array of Address Line 4 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Line 4 values.
    */
   public final String[] getAddress4Array()
   {
      return _Address4;
   }
    
   /**
    * Gets the Address Line 5 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Line 5 or null.
    */
   public final String getAddress5( int index )
   {
      return _Address5[index];
   }
    
   /**
    * Gets the Address Line 5 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Line 5 or the specified default value.
    */
   public final String getAddress5( int index, String defaultValue )
   {
      return _Address5[index] == null ? defaultValue : _Address5[index];
   }
    
   /**
    * Gets the array of Address Line 5 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Line 5 values.
    */
   public final String[] getAddress5Array()
   {
      return _Address5;
   }
    
   /**
    * Gets the Postal Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Postal Code or null.
    */
   public final String getPostalCode( int index )
   {
      return _PostalCode[index];
   }
    
   /**
    * Gets the Postal Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Postal Code or the specified default value.
    */
   public final String getPostalCode( int index, String defaultValue )
   {
      return _PostalCode[index] == null ? defaultValue : _PostalCode[index];
   }
    
   /**
    * Gets the array of Postal Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Postal Code values.
    */
   public final String[] getPostalCodeArray()
   {
      return _PostalCode;
   }
    
   /**
    * Gets the Kana Address Line1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Kana Address Line1 or null.
    */
   public final String getkAddrLine1( int index )
   {
      return _kAddrLine1[index];
   }
    
   /**
    * Gets the Kana Address Line1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Kana Address Line1 or the specified default value.
    */
   public final String getkAddrLine1( int index, String defaultValue )
   {
      return _kAddrLine1[index] == null ? defaultValue : _kAddrLine1[index];
   }
    
   /**
    * Gets the array of Kana Address Line1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Kana Address Line1 values.
    */
   public final String[] getkAddrLine1Array()
   {
      return _kAddrLine1;
   }
    
   /**
    * Gets the Kana Address Line2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Kana Address Line2 or null.
    */
   public final String getkAddrLine2( int index )
   {
      return _kAddrLine2[index];
   }
    
   /**
    * Gets the Kana Address Line2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Kana Address Line2 or the specified default value.
    */
   public final String getkAddrLine2( int index, String defaultValue )
   {
      return _kAddrLine2[index] == null ? defaultValue : _kAddrLine2[index];
   }
    
   /**
    * Gets the array of Kana Address Line2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Kana Address Line2 values.
    */
   public final String[] getkAddrLine2Array()
   {
      return _kAddrLine2;
   }
    
   /**
    * Gets the Kana Address Line3 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Kana Address Line3 or null.
    */
   public final String getkAddrLine3( int index )
   {
      return _kAddrLine3[index];
   }
    
   /**
    * Gets the Kana Address Line3 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Kana Address Line3 or the specified default value.
    */
   public final String getkAddrLine3( int index, String defaultValue )
   {
      return _kAddrLine3[index] == null ? defaultValue : _kAddrLine3[index];
   }
    
   /**
    * Gets the array of Kana Address Line3 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Kana Address Line3 values.
    */
   public final String[] getkAddrLine3Array()
   {
      return _kAddrLine3;
   }
    
   /**
    * Gets the Kana Address Line4 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Kana Address Line4 or null.
    */
   public final String getkAddrLine4( int index )
   {
      return _kAddrLine4[index];
   }
    
   /**
    * Gets the Kana Address Line4 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Kana Address Line4 or the specified default value.
    */
   public final String getkAddrLine4( int index, String defaultValue )
   {
      return _kAddrLine4[index] == null ? defaultValue : _kAddrLine4[index];
   }
    
   /**
    * Gets the array of Kana Address Line4 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Kana Address Line4 values.
    */
   public final String[] getkAddrLine4Array()
   {
      return _kAddrLine4;
   }
    
   /**
    * Gets the Kana Address Line5 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Kana Address Line5 or null.
    */
   public final String getkAddrLine5( int index )
   {
      return _kAddrLine5[index];
   }
    
   /**
    * Gets the Kana Address Line5 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Kana Address Line5 or the specified default value.
    */
   public final String getkAddrLine5( int index, String defaultValue )
   {
      return _kAddrLine5[index] == null ? defaultValue : _kAddrLine5[index];
   }
    
   /**
    * Gets the array of Kana Address Line5 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Kana Address Line5 values.
    */
   public final String[] getkAddrLine5Array()
   {
      return _kAddrLine5;
   }
    
   /**
    * Gets the Kana Postal Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Kana Postal Code or null.
    */
   public final String getkPostalCode( int index )
   {
      return _kPostalCode[index];
   }
    
   /**
    * Gets the Kana Postal Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Kana Postal Code or the specified default value.
    */
   public final String getkPostalCode( int index, String defaultValue )
   {
      return _kPostalCode[index] == null ? defaultValue : _kPostalCode[index];
   }
    
   /**
    * Gets the array of Kana Postal Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Kana Postal Code values.
    */
   public final String[] getkPostalCodeArray()
   {
      return _kPostalCode;
   }
    
   /**
    * Gets the ID Type  1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ID Type  1 or null.
    */
   public final String getIdType1( int index )
   {
      return _IdType1[index];
   }
    
   /**
    * Gets the ID Type  1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ID Type  1 or the specified default value.
    */
   public final String getIdType1( int index, String defaultValue )
   {
      return _IdType1[index] == null ? defaultValue : _IdType1[index];
   }
    
   /**
    * Gets the array of ID Type  1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ID Type  1 values.
    */
   public final String[] getIdType1Array()
   {
      return _IdType1;
   }
    
   /**
    * Gets the ID Value 1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ID Value 1 or null.
    */
   public final String getIdValue1( int index )
   {
      return _IdValue1[index];
   }
    
   /**
    * Gets the ID Value 1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ID Value 1 or the specified default value.
    */
   public final String getIdValue1( int index, String defaultValue )
   {
      return _IdValue1[index] == null ? defaultValue : _IdValue1[index];
   }
    
   /**
    * Gets the array of ID Value 1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ID Value 1 values.
    */
   public final String[] getIdValue1Array()
   {
      return _IdValue1;
   }
    
   /**
    * Gets the ID Type  2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ID Type  2 or null.
    */
   public final String getIdType2( int index )
   {
      return _IdType2[index];
   }
    
   /**
    * Gets the ID Type  2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ID Type  2 or the specified default value.
    */
   public final String getIdType2( int index, String defaultValue )
   {
      return _IdType2[index] == null ? defaultValue : _IdType2[index];
   }
    
   /**
    * Gets the array of ID Type  2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ID Type  2 values.
    */
   public final String[] getIdType2Array()
   {
      return _IdType2;
   }
    
   /**
    * Gets the ID Value 2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ID Value 2 or null.
    */
   public final String getIdValue2( int index )
   {
      return _IdValue2[index];
   }
    
   /**
    * Gets the ID Value 2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ID Value 2 or the specified default value.
    */
   public final String getIdValue2( int index, String defaultValue )
   {
      return _IdValue2[index] == null ? defaultValue : _IdValue2[index];
   }
    
   /**
    * Gets the array of ID Value 2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ID Value 2 values.
    */
   public final String[] getIdValue2Array()
   {
      return _IdValue2;
   }
    
   /**
    * Gets the ID Type  3 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ID Type  3 or null.
    */
   public final String getIdType3( int index )
   {
      return _IdType3[index];
   }
    
   /**
    * Gets the ID Type  3 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ID Type  3 or the specified default value.
    */
   public final String getIdType3( int index, String defaultValue )
   {
      return _IdType3[index] == null ? defaultValue : _IdType3[index];
   }
    
   /**
    * Gets the array of ID Type  3 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ID Type  3 values.
    */
   public final String[] getIdType3Array()
   {
      return _IdType3;
   }
    
   /**
    * Gets the ID Value 3 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ID Value 3 or null.
    */
   public final String getIdValue3( int index )
   {
      return _IdValue3[index];
   }
    
   /**
    * Gets the ID Value 3 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ID Value 3 or the specified default value.
    */
   public final String getIdValue3( int index, String defaultValue )
   {
      return _IdValue3[index] == null ? defaultValue : _IdValue3[index];
   }
    
   /**
    * Gets the array of ID Value 3 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ID Value 3 values.
    */
   public final String[] getIdValue3Array()
   {
      return _IdValue3;
   }
    
   /**
    * Gets the ID Type  4 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ID Type  4 or null.
    */
   public final String getIdType4( int index )
   {
      return _IdType4[index];
   }
    
   /**
    * Gets the ID Type  4 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ID Type  4 or the specified default value.
    */
   public final String getIdType4( int index, String defaultValue )
   {
      return _IdType4[index] == null ? defaultValue : _IdType4[index];
   }
    
   /**
    * Gets the array of ID Type  4 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ID Type  4 values.
    */
   public final String[] getIdType4Array()
   {
      return _IdType4;
   }
    
   /**
    * Gets the ID Value 4 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ID Value 4 or null.
    */
   public final String getIdValue4( int index )
   {
      return _IdValue4[index];
   }
    
   /**
    * Gets the ID Value 4 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ID Value 4 or the specified default value.
    */
   public final String getIdValue4( int index, String defaultValue )
   {
      return _IdValue4[index] == null ? defaultValue : _IdValue4[index];
   }
    
   /**
    * Gets the array of ID Value 4 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ID Value 4 values.
    */
   public final String[] getIdValue4Array()
   {
      return _IdValue4;
   }
    
   /**
    * Gets the ID Type  5 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ID Type  5 or null.
    */
   public final String getIdType5( int index )
   {
      return _IdType5[index];
   }
    
   /**
    * Gets the ID Type  5 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ID Type  5 or the specified default value.
    */
   public final String getIdType5( int index, String defaultValue )
   {
      return _IdType5[index] == null ? defaultValue : _IdType5[index];
   }
    
   /**
    * Gets the array of ID Type  5 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ID Type  5 values.
    */
   public final String[] getIdType5Array()
   {
      return _IdType5;
   }
    
   /**
    * Gets the ID Value 5 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ID Value 5 or null.
    */
   public final String getIdValue5( int index )
   {
      return _IdValue5[index];
   }
    
   /**
    * Gets the ID Value 5 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ID Value 5 or the specified default value.
    */
   public final String getIdValue5( int index, String defaultValue )
   {
      return _IdValue5[index] == null ? defaultValue : _IdValue5[index];
   }
    
   /**
    * Gets the array of ID Value 5 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ID Value 5 values.
    */
   public final String[] getIdValue5Array()
   {
      return _IdValue5;
   }
    
   /**
    * Gets the ID Type  6 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ID Type  6 or null.
    */
   public final String getIdType6( int index )
   {
      return _IdType6[index];
   }
    
   /**
    * Gets the ID Type  6 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ID Type  6 or the specified default value.
    */
   public final String getIdType6( int index, String defaultValue )
   {
      return _IdType6[index] == null ? defaultValue : _IdType6[index];
   }
    
   /**
    * Gets the array of ID Type  6 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ID Type  6 values.
    */
   public final String[] getIdType6Array()
   {
      return _IdType6;
   }
    
   /**
    * Gets the ID Value 6 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ID Value 6 or null.
    */
   public final String getIdValue6( int index )
   {
      return _IdValue6[index];
   }
    
   /**
    * Gets the ID Value 6 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ID Value 6 or the specified default value.
    */
   public final String getIdValue6( int index, String defaultValue )
   {
      return _IdValue6[index] == null ? defaultValue : _IdValue6[index];
   }
    
   /**
    * Gets the array of ID Value 6 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ID Value 6 values.
    */
   public final String[] getIdValue6Array()
   {
      return _IdValue6;
   }
    
   /**
    * Gets the ID Type  7 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ID Type  7 or null.
    */
   public final String getIdType7( int index )
   {
      return _IdType7[index];
   }
    
   /**
    * Gets the ID Type  7 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ID Type  7 or the specified default value.
    */
   public final String getIdType7( int index, String defaultValue )
   {
      return _IdType7[index] == null ? defaultValue : _IdType7[index];
   }
    
   /**
    * Gets the array of ID Type  7 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ID Type  7 values.
    */
   public final String[] getIdType7Array()
   {
      return _IdType7;
   }
    
   /**
    * Gets the ID Value 7 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ID Value 7 or null.
    */
   public final String getIdValue7( int index )
   {
      return _IdValue7[index];
   }
    
   /**
    * Gets the ID Value 7 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ID Value 7 or the specified default value.
    */
   public final String getIdValue7( int index, String defaultValue )
   {
      return _IdValue7[index] == null ? defaultValue : _IdValue7[index];
   }
    
   /**
    * Gets the array of ID Value 7 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ID Value 7 values.
    */
   public final String[] getIdValue7Array()
   {
      return _IdValue7;
   }
    
   /**
    * Gets the ID Type  8 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ID Type  8 or null.
    */
   public final String getIdType8( int index )
   {
      return _IdType8[index];
   }
    
   /**
    * Gets the ID Type  8 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ID Type  8 or the specified default value.
    */
   public final String getIdType8( int index, String defaultValue )
   {
      return _IdType8[index] == null ? defaultValue : _IdType8[index];
   }
    
   /**
    * Gets the array of ID Type  8 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ID Type  8 values.
    */
   public final String[] getIdType8Array()
   {
      return _IdType8;
   }
    
   /**
    * Gets the ID Value 8 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ID Value 8 or null.
    */
   public final String getIdValue8( int index )
   {
      return _IdValue8[index];
   }
    
   /**
    * Gets the ID Value 8 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ID Value 8 or the specified default value.
    */
   public final String getIdValue8( int index, String defaultValue )
   {
      return _IdValue8[index] == null ? defaultValue : _IdValue8[index];
   }
    
   /**
    * Gets the array of ID Value 8 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ID Value 8 values.
    */
   public final String[] getIdValue8Array()
   {
      return _IdValue8;
   }
    
   /**
    * Gets the ID Type  9 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ID Type  9 or null.
    */
   public final String getIdType9( int index )
   {
      return _IdType9[index];
   }
    
   /**
    * Gets the ID Type  9 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ID Type  9 or the specified default value.
    */
   public final String getIdType9( int index, String defaultValue )
   {
      return _IdType9[index] == null ? defaultValue : _IdType9[index];
   }
    
   /**
    * Gets the array of ID Type  9 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ID Type  9 values.
    */
   public final String[] getIdType9Array()
   {
      return _IdType9;
   }
    
   /**
    * Gets the ID Value 9 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ID Value 9 or null.
    */
   public final String getIdValue9( int index )
   {
      return _IdValue9[index];
   }
    
   /**
    * Gets the ID Value 9 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ID Value 9 or the specified default value.
    */
   public final String getIdValue9( int index, String defaultValue )
   {
      return _IdValue9[index] == null ? defaultValue : _IdValue9[index];
   }
    
   /**
    * Gets the array of ID Value 9 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ID Value 9 values.
    */
   public final String[] getIdValue9Array()
   {
      return _IdValue9;
   }
    
   /**
    * Gets the ID Type  10 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ID Type  10 or null.
    */
   public final String getIdType10( int index )
   {
      return _IdType10[index];
   }
    
   /**
    * Gets the ID Type  10 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ID Type  10 or the specified default value.
    */
   public final String getIdType10( int index, String defaultValue )
   {
      return _IdType10[index] == null ? defaultValue : _IdType10[index];
   }
    
   /**
    * Gets the array of ID Type  10 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ID Type  10 values.
    */
   public final String[] getIdType10Array()
   {
      return _IdType10;
   }
    
   /**
    * Gets the ID Value 10 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ID Value 10 or null.
    */
   public final String getIdValue10( int index )
   {
      return _IdValue10[index];
   }
    
   /**
    * Gets the ID Value 10 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ID Value 10 or the specified default value.
    */
   public final String getIdValue10( int index, String defaultValue )
   {
      return _IdValue10[index] == null ? defaultValue : _IdValue10[index];
   }
    
   /**
    * Gets the array of ID Value 10 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ID Value 10 values.
    */
   public final String[] getIdValue10Array()
   {
      return _IdValue10;
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
    * Gets the Entity Type Sequence field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Entity Type Sequence or null.
    */
   public final Integer getEntityTypeSeq( int index )
   {
      return _EntityTypeSeq[index];
   }
    
   /**
    * Gets the Entity Type Sequence field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Entity Type Sequence or the specified default value.
    */
   public final int getEntityTypeSeq( int index, int defaultValue )
   {
      return _EntityTypeSeq[index] == null ? defaultValue : _EntityTypeSeq[index].intValue();
   }
    
   /**
    * Gets the array of Entity Type Sequence fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Entity Type Sequence values.
    */
   public final Integer[] getEntityTypeSeqArray()
   {
      return _EntityTypeSeq;
   }
    
   /**
    * Gets the Account Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Type or null.
    */
   public final String getAcctType( int index )
   {
      return _AcctType[index];
   }
    
   /**
    * Gets the Account Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Type or the specified default value.
    */
   public final String getAcctType( int index, String defaultValue )
   {
      return _AcctType[index] == null ? defaultValue : _AcctType[index];
   }
    
   /**
    * Gets the array of Account Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Type values.
    */
   public final String[] getAcctTypeArray()
   {
      return _AcctType;
   }
    
   /**
    * Gets the Country Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Country Code or null.
    */
   public final String getCountryCode( int index )
   {
      return _CountryCode[index];
   }
    
   /**
    * Gets the Country Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Country Code or the specified default value.
    */
   public final String getCountryCode( int index, String defaultValue )
   {
      return _CountryCode[index] == null ? defaultValue : _CountryCode[index];
   }
    
   /**
    * Gets the array of Country Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Country Code values.
    */
   public final String[] getCountryCodeArray()
   {
      return _CountryCode;
   }
    
   /**
    * Gets the Social Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Social Code or null.
    */
   public final String getSocialCode( int index )
   {
      return _SocialCode[index];
   }
    
   /**
    * Gets the Social Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Social Code or the specified default value.
    */
   public final String getSocialCode( int index, String defaultValue )
   {
      return _SocialCode[index] == null ? defaultValue : _SocialCode[index];
   }
    
   /**
    * Gets the array of Social Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Social Code values.
    */
   public final String[] getSocialCodeArray()
   {
      return _SocialCode;
   }
    
   /**
    * Gets the Social Code description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Social Code description or null.
    */
   public final String getSocialCodeDesc( int index )
   {
      return _SocialCodeDesc[index];
   }
    
   /**
    * Gets the Social Code description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Social Code description or the specified default value.
    */
   public final String getSocialCodeDesc( int index, String defaultValue )
   {
      return _SocialCodeDesc[index] == null ? defaultValue : _SocialCodeDesc[index];
   }
    
   /**
    * Gets the array of Social Code description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Social Code description values.
    */
   public final String[] getSocialCodeDescArray()
   {
      return _SocialCodeDesc;
   }
    
   /**
    * Gets the Account Designation field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Designation or null.
    */
   public final String getAcctDes( int index )
   {
      return _AcctDes[index];
   }
    
   /**
    * Gets the Account Designation field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Designation or the specified default value.
    */
   public final String getAcctDes( int index, String defaultValue )
   {
      return _AcctDes[index] == null ? defaultValue : _AcctDes[index];
   }
    
   /**
    * Gets the array of Account Designation fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Designation values.
    */
   public final String[] getAcctDesArray()
   {
      return _AcctDes;
   }
    
   /**
    * Gets the Account Status field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Status or null.
    */
   public final String getAcctStatus( int index )
   {
      return _AcctStatus[index];
   }
    
   /**
    * Gets the Account Status field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Status or the specified default value.
    */
   public final String getAcctStatus( int index, String defaultValue )
   {
      return _AcctStatus[index] == null ? defaultValue : _AcctStatus[index];
   }
    
   /**
    * Gets the array of Account Status fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Status values.
    */
   public final String[] getAcctStatusArray()
   {
      return _AcctStatus;
   }
    
   /**
    * Gets the Alternate Account Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Alternate Account Number or null.
    */
   public final String getAltAccount( int index )
   {
      return _AltAccount[index];
   }
    
   /**
    * Gets the Alternate Account Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Alternate Account Number or the specified default value.
    */
   public final String getAltAccount( int index, String defaultValue )
   {
      return _AltAccount[index] == null ? defaultValue : _AltAccount[index];
   }
    
   /**
    * Gets the array of Alternate Account Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Alternate Account Number values.
    */
   public final String[] getAltAccountArray()
   {
      return _AltAccount;
   }
    
   /**
    * Gets the Account In Trust For or Joint field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account In Trust For or Joint or null.
    */
   public final String getInTrustJoint( int index )
   {
      return _InTrustJoint[index];
   }
    
   /**
    * Gets the Account In Trust For or Joint field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account In Trust For or Joint or the specified default value.
    */
   public final String getInTrustJoint( int index, String defaultValue )
   {
      return _InTrustJoint[index] == null ? defaultValue : _InTrustJoint[index];
   }
    
   /**
    * Gets the array of Account In Trust For or Joint fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account In Trust For or Joint values.
    */
   public final String[] getInTrustJointArray()
   {
      return _InTrustJoint;
   }
    
   /**
    * Gets the Fund Company Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Company Code or null.
    */
   public final String getCompanyCode( int index )
   {
      return _CompanyCode[index];
   }
    
   /**
    * Gets the Fund Company Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Company Code or the specified default value.
    */
   public final String getCompanyCode( int index, String defaultValue )
   {
      return _CompanyCode[index] == null ? defaultValue : _CompanyCode[index];
   }
    
   /**
    * Gets the array of Fund Company Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Company Code values.
    */
   public final String[] getCompanyCodeArray()
   {
      return _CompanyCode;
   }
    
   /**
    * Gets the Shareholder Group field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Shareholder Group or null.
    */
   public final String getAcctGroup( int index )
   {
      return _AcctGroup[index];
   }
    
   /**
    * Gets the Shareholder Group field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Shareholder Group or the specified default value.
    */
   public final String getAcctGroup( int index, String defaultValue )
   {
      return _AcctGroup[index] == null ? defaultValue : _AcctGroup[index];
   }
    
   /**
    * Gets the array of Shareholder Group fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Shareholder Group values.
    */
   public final String[] getAcctGroupArray()
   {
      return _AcctGroup;
   }
    
   /**
    * Gets the Account Type Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Type Description or null.
    */
   public final String getAcctTypeDesc( int index )
   {
      return _AcctTypeDesc[index];
   }
    
   /**
    * Gets the Account Type Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Type Description or the specified default value.
    */
   public final String getAcctTypeDesc( int index, String defaultValue )
   {
      return _AcctTypeDesc[index] == null ? defaultValue : _AcctTypeDesc[index];
   }
    
   /**
    * Gets the array of Account Type Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Type Description values.
    */
   public final String[] getAcctTypeDescArray()
   {
      return _AcctTypeDesc;
   }
    
   /**
    * Gets the Stop Purchase field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Stop Purchase or null.
    */
   public final Boolean getStopPurchase( int index )
   {
      return _StopPurchase[index];
   }
    
   /**
    * Gets the Stop Purchase field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stop Purchase or the specified default value.
    */
   public final boolean getStopPurchase( int index, boolean defaultValue )
   {
      return _StopPurchase[index] == null ? defaultValue : _StopPurchase[index].booleanValue();
   }
    
   /**
    * Gets the array of Stop Purchase fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Stop Purchase values.
    */
   public final Boolean[] getStopPurchaseArray()
   {
      return _StopPurchase;
   }
    
   /**
    * Gets the Stop Transfer in to the fund and class field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Stop Transfer in to the fund and class or null.
    */
   public final Boolean getStopXferIn( int index )
   {
      return _StopXferIn[index];
   }
    
   /**
    * Gets the Stop Transfer in to the fund and class field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stop Transfer in to the fund and class or the specified default value.
    */
   public final boolean getStopXferIn( int index, boolean defaultValue )
   {
      return _StopXferIn[index] == null ? defaultValue : _StopXferIn[index].booleanValue();
   }
    
   /**
    * Gets the array of Stop Transfer in to the fund and class fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Stop Transfer in to the fund and class values.
    */
   public final Boolean[] getStopXferInArray()
   {
      return _StopXferIn;
   }
    
   /**
    * Gets the Stop Transfer out of the fund and class field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Stop Transfer out of the fund and class or null.
    */
   public final Boolean getStopXferOut( int index )
   {
      return _StopXferOut[index];
   }
    
   /**
    * Gets the Stop Transfer out of the fund and class field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stop Transfer out of the fund and class or the specified default value.
    */
   public final boolean getStopXferOut( int index, boolean defaultValue )
   {
      return _StopXferOut[index] == null ? defaultValue : _StopXferOut[index].booleanValue();
   }
    
   /**
    * Gets the array of Stop Transfer out of the fund and class fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Stop Transfer out of the fund and class values.
    */
   public final Boolean[] getStopXferOutArray()
   {
      return _StopXferOut;
   }
    
   /**
    * Gets the Stop Redemption field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Stop Redemption or null.
    */
   public final Boolean getStopRed( int index )
   {
      return _StopRed[index];
   }
    
   /**
    * Gets the Stop Redemption field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stop Redemption or the specified default value.
    */
   public final boolean getStopRed( int index, boolean defaultValue )
   {
      return _StopRed[index] == null ? defaultValue : _StopRed[index].booleanValue();
   }
    
   /**
    * Gets the array of Stop Redemption fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Stop Redemption values.
    */
   public final Boolean[] getStopRedArray()
   {
      return _StopRed;
   }
    
   /**
    * Gets the Entity Type Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Entity Type Description or null.
    */
   public final String getEntityTypeDesc( int index )
   {
      return _EntityTypeDesc[index];
   }
    
   /**
    * Gets the Entity Type Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Entity Type Description or the specified default value.
    */
   public final String getEntityTypeDesc( int index, String defaultValue )
   {
      return _EntityTypeDesc[index] == null ? defaultValue : _EntityTypeDesc[index];
   }
    
   /**
    * Gets the array of Entity Type Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Entity Type Description values.
    */
   public final String[] getEntityTypeDescArray()
   {
      return _EntityTypeDesc;
   }
    
   /**
    * Gets the Wrap Account flag field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Wrap Account flag or null.
    */
   public final Boolean getWrapAccount( int index )
   {
      return _WrapAccount[index];
   }
    
   /**
    * Gets the Wrap Account flag field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Wrap Account flag or the specified default value.
    */
   public final boolean getWrapAccount( int index, boolean defaultValue )
   {
      return _WrapAccount[index] == null ? defaultValue : _WrapAccount[index].booleanValue();
   }
    
   /**
    * Gets the array of Wrap Account flag fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Wrap Account flag values.
    */
   public final Boolean[] getWrapAccountArray()
   {
      return _WrapAccount;
   }
    
   /**
    * Gets the Registration Information field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Registration Information or null.
    */
   public final String getRegistrationInfo( int index )
   {
      return _RegistrationInfo[index];
   }
    
   /**
    * Gets the Registration Information field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Registration Information or the specified default value.
    */
   public final String getRegistrationInfo( int index, String defaultValue )
   {
      return _RegistrationInfo[index] == null ? defaultValue : _RegistrationInfo[index];
   }
    
   /**
    * Gets the array of Registration Information fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Registration Information values.
    */
   public final String[] getRegistrationInfoArray()
   {
      return _RegistrationInfo;
   }
    
   /**
    * Gets the Entity Status field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Entity Status or null.
    */
   public final Boolean getEntStatus( int index )
   {
      return _EntStatus[index];
   }
    
   /**
    * Gets the Entity Status field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Entity Status or the specified default value.
    */
   public final boolean getEntStatus( int index, boolean defaultValue )
   {
      return _EntStatus[index] == null ? defaultValue : _EntStatus[index].booleanValue();
   }
    
   /**
    * Gets the array of Entity Status fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Entity Status values.
    */
   public final Boolean[] getEntStatusArray()
   {
      return _EntStatus;
   }
    
   /**
    * Gets the Valid RA TaxType field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Valid RA TaxType or null.
    */
   public final String getValidRATaxType( int index )
   {
      return _ValidRATaxType[index];
   }
    
   /**
    * Gets the Valid RA TaxType field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Valid RA TaxType or the specified default value.
    */
   public final String getValidRATaxType( int index, String defaultValue )
   {
      return _ValidRATaxType[index] == null ? defaultValue : _ValidRATaxType[index];
   }
    
   /**
    * Gets the array of Valid RA TaxType fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Valid RA TaxType values.
    */
   public final String[] getValidRATaxTypeArray()
   {
      return _ValidRATaxType;
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
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _AccountNum = resizeArray( _AccountNum, _RepeatCount );
      _ShrNum = resizeArray( _ShrNum, _RepeatCount );
      _LastName = resizeArray( _LastName, _RepeatCount );
      _FirstName = resizeArray( _FirstName, _RepeatCount );
      _BirthLastName = resizeArray( _BirthLastName, _RepeatCount );
      _BirthFirstName = resizeArray( _BirthFirstName, _RepeatCount );
      _SIN = resizeArray( _SIN, _RepeatCount );
      _BirthDate = resizeArray( _BirthDate, _RepeatCount );
      _TaxType = resizeArray( _TaxType, _RepeatCount );
      _TaxTypeDesc = resizeArray( _TaxTypeDesc, _RepeatCount );
      _HomePhone = resizeArray( _HomePhone, _RepeatCount );
      _MultipleReln = resizeArray( _MultipleReln, _RepeatCount );
      _EntityId = resizeArray( _EntityId, _RepeatCount );
      _Address1 = resizeArray( _Address1, _RepeatCount );
      _Address2 = resizeArray( _Address2, _RepeatCount );
      _Address3 = resizeArray( _Address3, _RepeatCount );
      _Address4 = resizeArray( _Address4, _RepeatCount );
      _Address5 = resizeArray( _Address5, _RepeatCount );
      _PostalCode = resizeArray( _PostalCode, _RepeatCount );
      _kAddrLine1 = resizeArray( _kAddrLine1, _RepeatCount );
      _kAddrLine2 = resizeArray( _kAddrLine2, _RepeatCount );
      _kAddrLine3 = resizeArray( _kAddrLine3, _RepeatCount );
      _kAddrLine4 = resizeArray( _kAddrLine4, _RepeatCount );
      _kAddrLine5 = resizeArray( _kAddrLine5, _RepeatCount );
      _kPostalCode = resizeArray( _kPostalCode, _RepeatCount );
      _IdType1 = resizeArray( _IdType1, _RepeatCount );
      _IdValue1 = resizeArray( _IdValue1, _RepeatCount );
      _IdType2 = resizeArray( _IdType2, _RepeatCount );
      _IdValue2 = resizeArray( _IdValue2, _RepeatCount );
      _IdType3 = resizeArray( _IdType3, _RepeatCount );
      _IdValue3 = resizeArray( _IdValue3, _RepeatCount );
      _IdType4 = resizeArray( _IdType4, _RepeatCount );
      _IdValue4 = resizeArray( _IdValue4, _RepeatCount );
      _IdType5 = resizeArray( _IdType5, _RepeatCount );
      _IdValue5 = resizeArray( _IdValue5, _RepeatCount );
      _IdType6 = resizeArray( _IdType6, _RepeatCount );
      _IdValue6 = resizeArray( _IdValue6, _RepeatCount );
      _IdType7 = resizeArray( _IdType7, _RepeatCount );
      _IdValue7 = resizeArray( _IdValue7, _RepeatCount );
      _IdType8 = resizeArray( _IdType8, _RepeatCount );
      _IdValue8 = resizeArray( _IdValue8, _RepeatCount );
      _IdType9 = resizeArray( _IdType9, _RepeatCount );
      _IdValue9 = resizeArray( _IdValue9, _RepeatCount );
      _IdType10 = resizeArray( _IdType10, _RepeatCount );
      _IdValue10 = resizeArray( _IdValue10, _RepeatCount );
      _EntityType = resizeArray( _EntityType, _RepeatCount );
      _EntityTypeSeq = resizeArray( _EntityTypeSeq, _RepeatCount );
      _AcctType = resizeArray( _AcctType, _RepeatCount );
      _CountryCode = resizeArray( _CountryCode, _RepeatCount );
      _SocialCode = resizeArray( _SocialCode, _RepeatCount );
      _SocialCodeDesc = resizeArray( _SocialCodeDesc, _RepeatCount );
      _AcctDes = resizeArray( _AcctDes, _RepeatCount );
      _AcctStatus = resizeArray( _AcctStatus, _RepeatCount );
      _AltAccount = resizeArray( _AltAccount, _RepeatCount );
      _InTrustJoint = resizeArray( _InTrustJoint, _RepeatCount );
      _CompanyCode = resizeArray( _CompanyCode, _RepeatCount );
      _AcctGroup = resizeArray( _AcctGroup, _RepeatCount );
      _AcctTypeDesc = resizeArray( _AcctTypeDesc, _RepeatCount );
      _StopPurchase = resizeArray( _StopPurchase, _RepeatCount );
      _StopXferIn = resizeArray( _StopXferIn, _RepeatCount );
      _StopXferOut = resizeArray( _StopXferOut, _RepeatCount );
      _StopRed = resizeArray( _StopRed, _RepeatCount );
      _EntityTypeDesc = resizeArray( _EntityTypeDesc, _RepeatCount );
      _WrapAccount = resizeArray( _WrapAccount, _RepeatCount );
      _RegistrationInfo = resizeArray( _RegistrationInfo, _RepeatCount );
      _EntStatus = resizeArray( _EntStatus, _RepeatCount );
      _ValidRATaxType = resizeArray( _ValidRATaxType, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _AccountNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ShrNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LastName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FirstName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BirthLastName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BirthFirstName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SIN[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BirthDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _TaxType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TaxTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _HomePhone[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MultipleReln[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _EntityId[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Address1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Address2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Address3[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Address4[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Address5[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PostalCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _kAddrLine1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _kAddrLine2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _kAddrLine3[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _kAddrLine4[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _kAddrLine5[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _kPostalCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IdType1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IdValue1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IdType2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IdValue2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IdType3[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IdValue3[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IdType4[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IdValue4[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IdType5[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IdValue5[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IdType6[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IdValue6[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IdType7[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IdValue7[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IdType8[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IdValue8[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IdType9[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IdValue9[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IdType10[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IdValue10[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EntityType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EntityTypeSeq[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _AcctType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CountryCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SocialCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SocialCodeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctDes[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctStatus[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AltAccount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _InTrustJoint[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CompanyCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctGroup[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _StopPurchase[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _StopXferIn[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _StopXferOut[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _StopRed[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _EntityTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _WrapAccount[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _RegistrationInfo[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EntStatus[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ValidRATaxType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
