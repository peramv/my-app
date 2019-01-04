
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Entity Address Information Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/EntAddr.doc">EntAddr.doc</A>.
 * 
 * @author RTS Generated
 */
public class EntAddrView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Effective Date member array.
    */
   private Date[] _EffectiveDate = null;
   
   /**
    * Date of Creation member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * User Name member array.
    */
   private String[] _Username = null;
   
   /**
    * Modify User member array.
    */
   private String[] _ModUser = null;
   
   /**
    * Modify Date member array.
    */
   private Date[] _ModDate = null;
   
   /**
    * Address Code member array.
    */
   private String[] _AddrCode = null;
   
   /**
    * Address Description member array.
    */
   private String[] _AddrDesc = null;
   
   /**
    * Address ID member array.
    */
   private String[] _AddrId = null;
   
   /**
    * Address Line 1 member array.
    */
   private String[] _AddrLine1 = null;
   
   /**
    * Address Line 2 member array.
    */
   private String[] _AddrLine2 = null;
   
   /**
    * Address Line 3 member array.
    */
   private String[] _AddrLine3 = null;
   
   /**
    * City member array.
    */
   private String[] _City = null;
   
   /**
    * Province member array.
    */
   private String[] _Province = null;
   
   /**
    * Province Name member array.
    */
   private String[] _ProvinceName = null;
   
   /**
    * Country member array.
    */
   private String[] _Country = null;
   
   /**
    * Country Name member array.
    */
   private String[] _CountryName = null;
   
   /**
    * Postal Code member array.
    */
   private String[] _PostalCode = null;
   
   /**
    * Hold Mail member array.
    */
   private Boolean[] _HoldMail = null;
   
   /**
    * Entity-Addr Version Number member array.
    */
   private Integer[] _EntityAddrVer = null;
   
   /**
    * Entity-Addr Record Id member array.
    */
   private Integer[] _EntityAddrRid = null;
   
   /**
    * Entity-Addr-Xref Version Number member array.
    */
   private Integer[] _EntityAddrXrefVer = null;
   
   /**
    * Entity-Addr-Xref Record Id member array.
    */
   private Integer[] _EntityAddrXrefRid = null;
   
   /**
    * Entity ID member array.
    */
   private String[] _rxEntityId = null;
   
   /**
    * Entity's Last Name member array.
    */
   private String[] _LastName = null;
   
   /**
    * Entity's First Name member array.
    */
   private String[] _FirstName = null;
   
   /**
    * RetMailFlag member array.
    */
   private Boolean[] _RetMailFlag = null;
   
   /**
    * RetMailDate member array.
    */
   private Date[] _RetMailDate = null;
   
   /**
    * RetMailReasonCode member array.
    */
   private String[] _RetMailReasonCode = null;
   
   /**
    * RetMailComment member array.
    */
   private String[] _RetMailComment = null;
   

   /**
    * Constructs the EntAddrView object.
    * 
    */
   public EntAddrView()
   {
      super ( new EntAddrRequest() );
   }

   /**
    * Constructs the EntAddrView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public EntAddrView( String hostEncoding )
   {
      super ( new EntAddrRequest( hostEncoding ) );
   }

   /**
    * Gets the EntAddrRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The EntAddrRequest object.
    */
   public final EntAddrRequest getRequest()
   {
      return (EntAddrRequest)getIFastRequest();
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
    * Gets the Effective Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Effective Date or null.
    */
   public final Date getEffectiveDate( int index )
   {
      return _EffectiveDate[index];
   }
    
   /**
    * Gets the Effective Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Effective Date or the specified default value.
    */
   public final Date getEffectiveDate( int index, Date defaultValue )
   {
      return _EffectiveDate[index] == null ? defaultValue : _EffectiveDate[index];
   }
    
   /**
    * Gets the array of Effective Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Effective Date values.
    */
   public final Date[] getEffectiveDateArray()
   {
      return _EffectiveDate;
   }
    
   /**
    * Gets the Date of Creation field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Date of Creation or null.
    */
   public final Date getProcessDate( int index )
   {
      return _ProcessDate[index];
   }
    
   /**
    * Gets the Date of Creation field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Date of Creation or the specified default value.
    */
   public final Date getProcessDate( int index, Date defaultValue )
   {
      return _ProcessDate[index] == null ? defaultValue : _ProcessDate[index];
   }
    
   /**
    * Gets the array of Date of Creation fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Date of Creation values.
    */
   public final Date[] getProcessDateArray()
   {
      return _ProcessDate;
   }
    
   /**
    * Gets the User Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the User Name or null.
    */
   public final String getUsername( int index )
   {
      return _Username[index];
   }
    
   /**
    * Gets the User Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the User Name or the specified default value.
    */
   public final String getUsername( int index, String defaultValue )
   {
      return _Username[index] == null ? defaultValue : _Username[index];
   }
    
   /**
    * Gets the array of User Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of User Name values.
    */
   public final String[] getUsernameArray()
   {
      return _Username;
   }
    
   /**
    * Gets the Modify User field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Modify User or null.
    */
   public final String getModUser( int index )
   {
      return _ModUser[index];
   }
    
   /**
    * Gets the Modify User field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Modify User or the specified default value.
    */
   public final String getModUser( int index, String defaultValue )
   {
      return _ModUser[index] == null ? defaultValue : _ModUser[index];
   }
    
   /**
    * Gets the array of Modify User fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Modify User values.
    */
   public final String[] getModUserArray()
   {
      return _ModUser;
   }
    
   /**
    * Gets the Modify Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Modify Date or null.
    */
   public final Date getModDate( int index )
   {
      return _ModDate[index];
   }
    
   /**
    * Gets the Modify Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Modify Date or the specified default value.
    */
   public final Date getModDate( int index, Date defaultValue )
   {
      return _ModDate[index] == null ? defaultValue : _ModDate[index];
   }
    
   /**
    * Gets the array of Modify Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Modify Date values.
    */
   public final Date[] getModDateArray()
   {
      return _ModDate;
   }
    
   /**
    * Gets the Address Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Code or null.
    */
   public final String getAddrCode( int index )
   {
      return _AddrCode[index];
   }
    
   /**
    * Gets the Address Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Code or the specified default value.
    */
   public final String getAddrCode( int index, String defaultValue )
   {
      return _AddrCode[index] == null ? defaultValue : _AddrCode[index];
   }
    
   /**
    * Gets the array of Address Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Code values.
    */
   public final String[] getAddrCodeArray()
   {
      return _AddrCode;
   }
    
   /**
    * Gets the Address Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Description or null.
    */
   public final String getAddrDesc( int index )
   {
      return _AddrDesc[index];
   }
    
   /**
    * Gets the Address Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Description or the specified default value.
    */
   public final String getAddrDesc( int index, String defaultValue )
   {
      return _AddrDesc[index] == null ? defaultValue : _AddrDesc[index];
   }
    
   /**
    * Gets the array of Address Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Description values.
    */
   public final String[] getAddrDescArray()
   {
      return _AddrDesc;
   }
    
   /**
    * Gets the Address ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address ID or null.
    */
   public final String getAddrId( int index )
   {
      return _AddrId[index];
   }
    
   /**
    * Gets the Address ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address ID or the specified default value.
    */
   public final String getAddrId( int index, String defaultValue )
   {
      return _AddrId[index] == null ? defaultValue : _AddrId[index];
   }
    
   /**
    * Gets the array of Address ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address ID values.
    */
   public final String[] getAddrIdArray()
   {
      return _AddrId;
   }
    
   /**
    * Gets the Address Line 1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Line 1 or null.
    */
   public final String getAddrLine1( int index )
   {
      return _AddrLine1[index];
   }
    
   /**
    * Gets the Address Line 1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Line 1 or the specified default value.
    */
   public final String getAddrLine1( int index, String defaultValue )
   {
      return _AddrLine1[index] == null ? defaultValue : _AddrLine1[index];
   }
    
   /**
    * Gets the array of Address Line 1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Line 1 values.
    */
   public final String[] getAddrLine1Array()
   {
      return _AddrLine1;
   }
    
   /**
    * Gets the Address Line 2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Line 2 or null.
    */
   public final String getAddrLine2( int index )
   {
      return _AddrLine2[index];
   }
    
   /**
    * Gets the Address Line 2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Line 2 or the specified default value.
    */
   public final String getAddrLine2( int index, String defaultValue )
   {
      return _AddrLine2[index] == null ? defaultValue : _AddrLine2[index];
   }
    
   /**
    * Gets the array of Address Line 2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Line 2 values.
    */
   public final String[] getAddrLine2Array()
   {
      return _AddrLine2;
   }
    
   /**
    * Gets the Address Line 3 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Line 3 or null.
    */
   public final String getAddrLine3( int index )
   {
      return _AddrLine3[index];
   }
    
   /**
    * Gets the Address Line 3 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Line 3 or the specified default value.
    */
   public final String getAddrLine3( int index, String defaultValue )
   {
      return _AddrLine3[index] == null ? defaultValue : _AddrLine3[index];
   }
    
   /**
    * Gets the array of Address Line 3 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Line 3 values.
    */
   public final String[] getAddrLine3Array()
   {
      return _AddrLine3;
   }
    
   /**
    * Gets the City field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the City or null.
    */
   public final String getCity( int index )
   {
      return _City[index];
   }
    
   /**
    * Gets the City field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the City or the specified default value.
    */
   public final String getCity( int index, String defaultValue )
   {
      return _City[index] == null ? defaultValue : _City[index];
   }
    
   /**
    * Gets the array of City fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of City values.
    */
   public final String[] getCityArray()
   {
      return _City;
   }
    
   /**
    * Gets the Province field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Province or null.
    */
   public final String getProvince( int index )
   {
      return _Province[index];
   }
    
   /**
    * Gets the Province field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Province or the specified default value.
    */
   public final String getProvince( int index, String defaultValue )
   {
      return _Province[index] == null ? defaultValue : _Province[index];
   }
    
   /**
    * Gets the array of Province fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Province values.
    */
   public final String[] getProvinceArray()
   {
      return _Province;
   }
    
   /**
    * Gets the Province Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Province Name or null.
    */
   public final String getProvinceName( int index )
   {
      return _ProvinceName[index];
   }
    
   /**
    * Gets the Province Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Province Name or the specified default value.
    */
   public final String getProvinceName( int index, String defaultValue )
   {
      return _ProvinceName[index] == null ? defaultValue : _ProvinceName[index];
   }
    
   /**
    * Gets the array of Province Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Province Name values.
    */
   public final String[] getProvinceNameArray()
   {
      return _ProvinceName;
   }
    
   /**
    * Gets the Country field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Country or null.
    */
   public final String getCountry( int index )
   {
      return _Country[index];
   }
    
   /**
    * Gets the Country field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Country or the specified default value.
    */
   public final String getCountry( int index, String defaultValue )
   {
      return _Country[index] == null ? defaultValue : _Country[index];
   }
    
   /**
    * Gets the array of Country fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Country values.
    */
   public final String[] getCountryArray()
   {
      return _Country;
   }
    
   /**
    * Gets the Country Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Country Name or null.
    */
   public final String getCountryName( int index )
   {
      return _CountryName[index];
   }
    
   /**
    * Gets the Country Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Country Name or the specified default value.
    */
   public final String getCountryName( int index, String defaultValue )
   {
      return _CountryName[index] == null ? defaultValue : _CountryName[index];
   }
    
   /**
    * Gets the array of Country Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Country Name values.
    */
   public final String[] getCountryNameArray()
   {
      return _CountryName;
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
    * Gets the Hold Mail field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Hold Mail or null.
    */
   public final Boolean getHoldMail( int index )
   {
      return _HoldMail[index];
   }
    
   /**
    * Gets the Hold Mail field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Hold Mail or the specified default value.
    */
   public final boolean getHoldMail( int index, boolean defaultValue )
   {
      return _HoldMail[index] == null ? defaultValue : _HoldMail[index].booleanValue();
   }
    
   /**
    * Gets the array of Hold Mail fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Hold Mail values.
    */
   public final Boolean[] getHoldMailArray()
   {
      return _HoldMail;
   }
    
   /**
    * Gets the Entity-Addr Version Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Entity-Addr Version Number or null.
    */
   public final Integer getEntityAddrVer( int index )
   {
      return _EntityAddrVer[index];
   }
    
   /**
    * Gets the Entity-Addr Version Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Entity-Addr Version Number or the specified default value.
    */
   public final int getEntityAddrVer( int index, int defaultValue )
   {
      return _EntityAddrVer[index] == null ? defaultValue : _EntityAddrVer[index].intValue();
   }
    
   /**
    * Gets the array of Entity-Addr Version Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Entity-Addr Version Number values.
    */
   public final Integer[] getEntityAddrVerArray()
   {
      return _EntityAddrVer;
   }
    
   /**
    * Gets the Entity-Addr Record Id field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Entity-Addr Record Id or null.
    */
   public final Integer getEntityAddrRid( int index )
   {
      return _EntityAddrRid[index];
   }
    
   /**
    * Gets the Entity-Addr Record Id field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Entity-Addr Record Id or the specified default value.
    */
   public final int getEntityAddrRid( int index, int defaultValue )
   {
      return _EntityAddrRid[index] == null ? defaultValue : _EntityAddrRid[index].intValue();
   }
    
   /**
    * Gets the array of Entity-Addr Record Id fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Entity-Addr Record Id values.
    */
   public final Integer[] getEntityAddrRidArray()
   {
      return _EntityAddrRid;
   }
    
   /**
    * Gets the Entity-Addr-Xref Version Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Entity-Addr-Xref Version Number or null.
    */
   public final Integer getEntityAddrXrefVer( int index )
   {
      return _EntityAddrXrefVer[index];
   }
    
   /**
    * Gets the Entity-Addr-Xref Version Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Entity-Addr-Xref Version Number or the specified default value.
    */
   public final int getEntityAddrXrefVer( int index, int defaultValue )
   {
      return _EntityAddrXrefVer[index] == null ? defaultValue : _EntityAddrXrefVer[index].intValue();
   }
    
   /**
    * Gets the array of Entity-Addr-Xref Version Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Entity-Addr-Xref Version Number values.
    */
   public final Integer[] getEntityAddrXrefVerArray()
   {
      return _EntityAddrXrefVer;
   }
    
   /**
    * Gets the Entity-Addr-Xref Record Id field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Entity-Addr-Xref Record Id or null.
    */
   public final Integer getEntityAddrXrefRid( int index )
   {
      return _EntityAddrXrefRid[index];
   }
    
   /**
    * Gets the Entity-Addr-Xref Record Id field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Entity-Addr-Xref Record Id or the specified default value.
    */
   public final int getEntityAddrXrefRid( int index, int defaultValue )
   {
      return _EntityAddrXrefRid[index] == null ? defaultValue : _EntityAddrXrefRid[index].intValue();
   }
    
   /**
    * Gets the array of Entity-Addr-Xref Record Id fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Entity-Addr-Xref Record Id values.
    */
   public final Integer[] getEntityAddrXrefRidArray()
   {
      return _EntityAddrXrefRid;
   }
    
   /**
    * Gets the Entity ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Entity ID or null.
    */
   public final String getrxEntityId( int index )
   {
      return _rxEntityId[index];
   }
    
   /**
    * Gets the Entity ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Entity ID or the specified default value.
    */
   public final String getrxEntityId( int index, String defaultValue )
   {
      return _rxEntityId[index] == null ? defaultValue : _rxEntityId[index];
   }
    
   /**
    * Gets the array of Entity ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Entity ID values.
    */
   public final String[] getrxEntityIdArray()
   {
      return _rxEntityId;
   }
    
   /**
    * Gets the Entity's Last Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Entity's Last Name or null.
    */
   public final String getLastName( int index )
   {
      return _LastName[index];
   }
    
   /**
    * Gets the Entity's Last Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Entity's Last Name or the specified default value.
    */
   public final String getLastName( int index, String defaultValue )
   {
      return _LastName[index] == null ? defaultValue : _LastName[index];
   }
    
   /**
    * Gets the array of Entity's Last Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Entity's Last Name values.
    */
   public final String[] getLastNameArray()
   {
      return _LastName;
   }
    
   /**
    * Gets the Entity's First Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Entity's First Name or null.
    */
   public final String getFirstName( int index )
   {
      return _FirstName[index];
   }
    
   /**
    * Gets the Entity's First Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Entity's First Name or the specified default value.
    */
   public final String getFirstName( int index, String defaultValue )
   {
      return _FirstName[index] == null ? defaultValue : _FirstName[index];
   }
    
   /**
    * Gets the array of Entity's First Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Entity's First Name values.
    */
   public final String[] getFirstNameArray()
   {
      return _FirstName;
   }
    
   /**
    * Gets the RetMailFlag field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RetMailFlag or null.
    */
   public final Boolean getRetMailFlag( int index )
   {
      return _RetMailFlag[index];
   }
    
   /**
    * Gets the RetMailFlag field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RetMailFlag or the specified default value.
    */
   public final boolean getRetMailFlag( int index, boolean defaultValue )
   {
      return _RetMailFlag[index] == null ? defaultValue : _RetMailFlag[index].booleanValue();
   }
    
   /**
    * Gets the array of RetMailFlag fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RetMailFlag values.
    */
   public final Boolean[] getRetMailFlagArray()
   {
      return _RetMailFlag;
   }
    
   /**
    * Gets the RetMailDate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RetMailDate or null.
    */
   public final Date getRetMailDate( int index )
   {
      return _RetMailDate[index];
   }
    
   /**
    * Gets the RetMailDate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RetMailDate or the specified default value.
    */
   public final Date getRetMailDate( int index, Date defaultValue )
   {
      return _RetMailDate[index] == null ? defaultValue : _RetMailDate[index];
   }
    
   /**
    * Gets the array of RetMailDate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RetMailDate values.
    */
   public final Date[] getRetMailDateArray()
   {
      return _RetMailDate;
   }
    
   /**
    * Gets the RetMailReasonCode field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RetMailReasonCode or null.
    */
   public final String getRetMailReasonCode( int index )
   {
      return _RetMailReasonCode[index];
   }
    
   /**
    * Gets the RetMailReasonCode field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RetMailReasonCode or the specified default value.
    */
   public final String getRetMailReasonCode( int index, String defaultValue )
   {
      return _RetMailReasonCode[index] == null ? defaultValue : _RetMailReasonCode[index];
   }
    
   /**
    * Gets the array of RetMailReasonCode fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RetMailReasonCode values.
    */
   public final String[] getRetMailReasonCodeArray()
   {
      return _RetMailReasonCode;
   }
    
   /**
    * Gets the RetMailComment field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RetMailComment or null.
    */
   public final String getRetMailComment( int index )
   {
      return _RetMailComment[index];
   }
    
   /**
    * Gets the RetMailComment field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RetMailComment or the specified default value.
    */
   public final String getRetMailComment( int index, String defaultValue )
   {
      return _RetMailComment[index] == null ? defaultValue : _RetMailComment[index];
   }
    
   /**
    * Gets the array of RetMailComment fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RetMailComment values.
    */
   public final String[] getRetMailCommentArray()
   {
      return _RetMailComment;
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
      
      _EffectiveDate = resizeArray( _EffectiveDate, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _Username = resizeArray( _Username, _RepeatCount );
      _ModUser = resizeArray( _ModUser, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _AddrCode = resizeArray( _AddrCode, _RepeatCount );
      _AddrDesc = resizeArray( _AddrDesc, _RepeatCount );
      _AddrId = resizeArray( _AddrId, _RepeatCount );
      _AddrLine1 = resizeArray( _AddrLine1, _RepeatCount );
      _AddrLine2 = resizeArray( _AddrLine2, _RepeatCount );
      _AddrLine3 = resizeArray( _AddrLine3, _RepeatCount );
      _City = resizeArray( _City, _RepeatCount );
      _Province = resizeArray( _Province, _RepeatCount );
      _ProvinceName = resizeArray( _ProvinceName, _RepeatCount );
      _Country = resizeArray( _Country, _RepeatCount );
      _CountryName = resizeArray( _CountryName, _RepeatCount );
      _PostalCode = resizeArray( _PostalCode, _RepeatCount );
      _HoldMail = resizeArray( _HoldMail, _RepeatCount );
      _EntityAddrVer = resizeArray( _EntityAddrVer, _RepeatCount );
      _EntityAddrRid = resizeArray( _EntityAddrRid, _RepeatCount );
      _EntityAddrXrefVer = resizeArray( _EntityAddrXrefVer, _RepeatCount );
      _EntityAddrXrefRid = resizeArray( _EntityAddrXrefRid, _RepeatCount );
      _rxEntityId = resizeArray( _rxEntityId, _RepeatCount );
      _LastName = resizeArray( _LastName, _RepeatCount );
      _FirstName = resizeArray( _FirstName, _RepeatCount );
      _RetMailFlag = resizeArray( _RetMailFlag, _RepeatCount );
      _RetMailDate = resizeArray( _RetMailDate, _RepeatCount );
      _RetMailReasonCode = resizeArray( _RetMailReasonCode, _RepeatCount );
      _RetMailComment = resizeArray( _RetMailComment, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _EffectiveDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _Username[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _AddrCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrId[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine3[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _City[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Province[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProvinceName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Country[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CountryName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PostalCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _HoldMail[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _EntityAddrVer[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _EntityAddrRid[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _EntityAddrXrefVer[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _EntityAddrXrefRid[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _rxEntityId[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LastName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FirstName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RetMailFlag[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _RetMailDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _RetMailReasonCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RetMailComment[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
