
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Agent List Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/AgentList.doc">AgentList.doc</A>.
 * 
 * @author RTS Generated
 */
public class AgentListView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * rx Sales Rep member array.
    */
   private String[] _rxSlsRep = null;
   
   /**
    * Sales Rep Name member array.
    */
   private String[] _SalesRepName = null;
   
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
    * Address Line 4 member array.
    */
   private String[] _AddrLine4 = null;
   
   /**
    * Address Line 5 member array.
    */
   private String[] _AddrLine5 = null;
   
   /**
    * Country Code member array.
    */
   private String[] _AddrCntryCode = null;
   
   /**
    * Phone Number member array.
    */
   private String[] _PhoneNumber = null;
   
   /**
    * Mod Date member array.
    */
   private Date[] _ModDate = null;
   
   /**
    * Stop Date member array.
    */
   private Date[] _StopDate = null;
   
   /**
    * Trailer Fee Eligible member array.
    */
   private Boolean[] _TrailEligible = null;
   
   /**
    * Payment Type member array.
    */
   private String[] _PayType = null;
   
   /**
    * Payment Type Description member array.
    */
   private String[] _PayTypeDesc = null;
   
   /**
    * Currency member array.
    */
   private String[] _Currency = null;
   
   /**
    * Currency Name member array.
    */
   private String[] _CurrencyName = null;
   
   /**
    * Payment Frequency member array.
    */
   private String[] _PayFreq = null;
   
   /**
    * Payment Frequency Description member array.
    */
   private String[] _PayFreqDesc = null;
   
   /**
    * Resp Broker Code member array.
    */
   private String[] _rxBrokerCode = null;
   
   /**
    * Resp Branch Code member array.
    */
   private String[] _rxBranchCode = null;
   
   /**
    * Sales Rep Type member array.
    */
   private String[] _SlsRepType = null;
   
   /**
    * Sales Rep Type Description member array.
    */
   private String[] _SlsRepTypeDesc = null;
   
   /**
    * Effective Date member array.
    */
   private Date[] _EffectiveDate = null;
   
   /**
    * Agent's Alternate Name member array.
    */
   private String[] _SlsRepAltName = null;
   
   /**
    * Provinces where rep can sell seg funds member array.
    */
   private String[] _SegLicenseProvList = null;
   
   /**
    * Slsperson can deal with new product or not member array.
    */
   private Boolean[] _NewBusiness = null;
   
   /**
    * Broker's Name member array.
    */
   private String[] _BrokerName = null;
   
   /**
    * Branch's Name member array.
    */
   private String[] _BranchName = null;
   
   /**
    * Postal Code member array.
    */
   private String[] _PostalCode = null;
   
   /**
    * Email Address member array.
    */
   private String[] _Email = null;
   
   /**
    * Fax Number member array.
    */
   private String[] _FaxNumber = null;
   
   /**
    * Country Name member array.
    */
   private String[] _AddrCntry = null;
   
   /**
    * Sales Rep Country Code (phone) member array.
    */
   private String[] _SlsRepCntry = null;
   
   /**
    * Sales Rep Area Code (phone) member array.
    */
   private String[] _SlsRepArea = null;
   
   /**
    * Fax Country Code member array.
    */
   private String[] _FaxCntryCode = null;
   
   /**
    * Fax Area Code member array.
    */
   private String[] _FaxAreaCode = null;
   
   /**
    * Flag indicating if SlsRep passed validation member array.
    */
   private Boolean[] _ValidationPassed = null;
   
   /**
    * Payment Instructions for Trailers Avail member array.
    */
   private Boolean[] _PayInstrTrailer = null;
   
   /**
    * Payment Instructions for Comm Avail member array.
    */
   private Boolean[] _PayInstrComm = null;
   
   /**
    * Sales Rep Level member array.
    */
   private Integer[] _RepLevel = null;
   
   /**
    * Agent Status member array.
    */
   private Boolean[] _AgentStat = null;
   

   /**
    * Constructs the AgentListView object.
    * 
    */
   public AgentListView()
   {
      super ( new AgentListRequest() );
   }

   /**
    * Constructs the AgentListView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AgentListView( String hostEncoding )
   {
      super ( new AgentListRequest( hostEncoding ) );
   }

   /**
    * Gets the AgentListRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AgentListRequest object.
    */
   public final AgentListRequest getRequest()
   {
      return (AgentListRequest)getIFastRequest();
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
    * Gets the rx Sales Rep field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the rx Sales Rep or null.
    */
   public final String getrxSlsRep( int index )
   {
      return _rxSlsRep[index];
   }
    
   /**
    * Gets the rx Sales Rep field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the rx Sales Rep or the specified default value.
    */
   public final String getrxSlsRep( int index, String defaultValue )
   {
      return _rxSlsRep[index] == null ? defaultValue : _rxSlsRep[index];
   }
    
   /**
    * Gets the array of rx Sales Rep fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of rx Sales Rep values.
    */
   public final String[] getrxSlsRepArray()
   {
      return _rxSlsRep;
   }
    
   /**
    * Gets the Sales Rep Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Sales Rep Name or null.
    */
   public final String getSalesRepName( int index )
   {
      return _SalesRepName[index];
   }
    
   /**
    * Gets the Sales Rep Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Sales Rep Name or the specified default value.
    */
   public final String getSalesRepName( int index, String defaultValue )
   {
      return _SalesRepName[index] == null ? defaultValue : _SalesRepName[index];
   }
    
   /**
    * Gets the array of Sales Rep Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Sales Rep Name values.
    */
   public final String[] getSalesRepNameArray()
   {
      return _SalesRepName;
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
    * Gets the Address Line 4 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Line 4 or null.
    */
   public final String getAddrLine4( int index )
   {
      return _AddrLine4[index];
   }
    
   /**
    * Gets the Address Line 4 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Line 4 or the specified default value.
    */
   public final String getAddrLine4( int index, String defaultValue )
   {
      return _AddrLine4[index] == null ? defaultValue : _AddrLine4[index];
   }
    
   /**
    * Gets the array of Address Line 4 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Line 4 values.
    */
   public final String[] getAddrLine4Array()
   {
      return _AddrLine4;
   }
    
   /**
    * Gets the Address Line 5 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Line 5 or null.
    */
   public final String getAddrLine5( int index )
   {
      return _AddrLine5[index];
   }
    
   /**
    * Gets the Address Line 5 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Line 5 or the specified default value.
    */
   public final String getAddrLine5( int index, String defaultValue )
   {
      return _AddrLine5[index] == null ? defaultValue : _AddrLine5[index];
   }
    
   /**
    * Gets the array of Address Line 5 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Line 5 values.
    */
   public final String[] getAddrLine5Array()
   {
      return _AddrLine5;
   }
    
   /**
    * Gets the Country Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Country Code or null.
    */
   public final String getAddrCntryCode( int index )
   {
      return _AddrCntryCode[index];
   }
    
   /**
    * Gets the Country Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Country Code or the specified default value.
    */
   public final String getAddrCntryCode( int index, String defaultValue )
   {
      return _AddrCntryCode[index] == null ? defaultValue : _AddrCntryCode[index];
   }
    
   /**
    * Gets the array of Country Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Country Code values.
    */
   public final String[] getAddrCntryCodeArray()
   {
      return _AddrCntryCode;
   }
    
   /**
    * Gets the Phone Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Phone Number or null.
    */
   public final String getPhoneNumber( int index )
   {
      return _PhoneNumber[index];
   }
    
   /**
    * Gets the Phone Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Phone Number or the specified default value.
    */
   public final String getPhoneNumber( int index, String defaultValue )
   {
      return _PhoneNumber[index] == null ? defaultValue : _PhoneNumber[index];
   }
    
   /**
    * Gets the array of Phone Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Phone Number values.
    */
   public final String[] getPhoneNumberArray()
   {
      return _PhoneNumber;
   }
    
   /**
    * Gets the Mod Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Mod Date or null.
    */
   public final Date getModDate( int index )
   {
      return _ModDate[index];
   }
    
   /**
    * Gets the Mod Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Mod Date or the specified default value.
    */
   public final Date getModDate( int index, Date defaultValue )
   {
      return _ModDate[index] == null ? defaultValue : _ModDate[index];
   }
    
   /**
    * Gets the array of Mod Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Mod Date values.
    */
   public final Date[] getModDateArray()
   {
      return _ModDate;
   }
    
   /**
    * Gets the Stop Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Stop Date or null.
    */
   public final Date getStopDate( int index )
   {
      return _StopDate[index];
   }
    
   /**
    * Gets the Stop Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stop Date or the specified default value.
    */
   public final Date getStopDate( int index, Date defaultValue )
   {
      return _StopDate[index] == null ? defaultValue : _StopDate[index];
   }
    
   /**
    * Gets the array of Stop Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Stop Date values.
    */
   public final Date[] getStopDateArray()
   {
      return _StopDate;
   }
    
   /**
    * Gets the Trailer Fee Eligible field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Trailer Fee Eligible or null.
    */
   public final Boolean getTrailEligible( int index )
   {
      return _TrailEligible[index];
   }
    
   /**
    * Gets the Trailer Fee Eligible field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Trailer Fee Eligible or the specified default value.
    */
   public final boolean getTrailEligible( int index, boolean defaultValue )
   {
      return _TrailEligible[index] == null ? defaultValue : _TrailEligible[index].booleanValue();
   }
    
   /**
    * Gets the array of Trailer Fee Eligible fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Trailer Fee Eligible values.
    */
   public final Boolean[] getTrailEligibleArray()
   {
      return _TrailEligible;
   }
    
   /**
    * Gets the Payment Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Payment Type or null.
    */
   public final String getPayType( int index )
   {
      return _PayType[index];
   }
    
   /**
    * Gets the Payment Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Payment Type or the specified default value.
    */
   public final String getPayType( int index, String defaultValue )
   {
      return _PayType[index] == null ? defaultValue : _PayType[index];
   }
    
   /**
    * Gets the array of Payment Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Payment Type values.
    */
   public final String[] getPayTypeArray()
   {
      return _PayType;
   }
    
   /**
    * Gets the Payment Type Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Payment Type Description or null.
    */
   public final String getPayTypeDesc( int index )
   {
      return _PayTypeDesc[index];
   }
    
   /**
    * Gets the Payment Type Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Payment Type Description or the specified default value.
    */
   public final String getPayTypeDesc( int index, String defaultValue )
   {
      return _PayTypeDesc[index] == null ? defaultValue : _PayTypeDesc[index];
   }
    
   /**
    * Gets the array of Payment Type Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Payment Type Description values.
    */
   public final String[] getPayTypeDescArray()
   {
      return _PayTypeDesc;
   }
    
   /**
    * Gets the Currency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Currency or null.
    */
   public final String getCurrency( int index )
   {
      return _Currency[index];
   }
    
   /**
    * Gets the Currency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Currency or the specified default value.
    */
   public final String getCurrency( int index, String defaultValue )
   {
      return _Currency[index] == null ? defaultValue : _Currency[index];
   }
    
   /**
    * Gets the array of Currency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Currency values.
    */
   public final String[] getCurrencyArray()
   {
      return _Currency;
   }
    
   /**
    * Gets the Currency Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Currency Name or null.
    */
   public final String getCurrencyName( int index )
   {
      return _CurrencyName[index];
   }
    
   /**
    * Gets the Currency Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Currency Name or the specified default value.
    */
   public final String getCurrencyName( int index, String defaultValue )
   {
      return _CurrencyName[index] == null ? defaultValue : _CurrencyName[index];
   }
    
   /**
    * Gets the array of Currency Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Currency Name values.
    */
   public final String[] getCurrencyNameArray()
   {
      return _CurrencyName;
   }
    
   /**
    * Gets the Payment Frequency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Payment Frequency or null.
    */
   public final String getPayFreq( int index )
   {
      return _PayFreq[index];
   }
    
   /**
    * Gets the Payment Frequency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Payment Frequency or the specified default value.
    */
   public final String getPayFreq( int index, String defaultValue )
   {
      return _PayFreq[index] == null ? defaultValue : _PayFreq[index];
   }
    
   /**
    * Gets the array of Payment Frequency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Payment Frequency values.
    */
   public final String[] getPayFreqArray()
   {
      return _PayFreq;
   }
    
   /**
    * Gets the Payment Frequency Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Payment Frequency Description or null.
    */
   public final String getPayFreqDesc( int index )
   {
      return _PayFreqDesc[index];
   }
    
   /**
    * Gets the Payment Frequency Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Payment Frequency Description or the specified default value.
    */
   public final String getPayFreqDesc( int index, String defaultValue )
   {
      return _PayFreqDesc[index] == null ? defaultValue : _PayFreqDesc[index];
   }
    
   /**
    * Gets the array of Payment Frequency Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Payment Frequency Description values.
    */
   public final String[] getPayFreqDescArray()
   {
      return _PayFreqDesc;
   }
    
   /**
    * Gets the Resp Broker Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Resp Broker Code or null.
    */
   public final String getrxBrokerCode( int index )
   {
      return _rxBrokerCode[index];
   }
    
   /**
    * Gets the Resp Broker Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Resp Broker Code or the specified default value.
    */
   public final String getrxBrokerCode( int index, String defaultValue )
   {
      return _rxBrokerCode[index] == null ? defaultValue : _rxBrokerCode[index];
   }
    
   /**
    * Gets the array of Resp Broker Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Resp Broker Code values.
    */
   public final String[] getrxBrokerCodeArray()
   {
      return _rxBrokerCode;
   }
    
   /**
    * Gets the Resp Branch Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Resp Branch Code or null.
    */
   public final String getrxBranchCode( int index )
   {
      return _rxBranchCode[index];
   }
    
   /**
    * Gets the Resp Branch Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Resp Branch Code or the specified default value.
    */
   public final String getrxBranchCode( int index, String defaultValue )
   {
      return _rxBranchCode[index] == null ? defaultValue : _rxBranchCode[index];
   }
    
   /**
    * Gets the array of Resp Branch Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Resp Branch Code values.
    */
   public final String[] getrxBranchCodeArray()
   {
      return _rxBranchCode;
   }
    
   /**
    * Gets the Sales Rep Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Sales Rep Type or null.
    */
   public final String getSlsRepType( int index )
   {
      return _SlsRepType[index];
   }
    
   /**
    * Gets the Sales Rep Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Sales Rep Type or the specified default value.
    */
   public final String getSlsRepType( int index, String defaultValue )
   {
      return _SlsRepType[index] == null ? defaultValue : _SlsRepType[index];
   }
    
   /**
    * Gets the array of Sales Rep Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Sales Rep Type values.
    */
   public final String[] getSlsRepTypeArray()
   {
      return _SlsRepType;
   }
    
   /**
    * Gets the Sales Rep Type Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Sales Rep Type Description or null.
    */
   public final String getSlsRepTypeDesc( int index )
   {
      return _SlsRepTypeDesc[index];
   }
    
   /**
    * Gets the Sales Rep Type Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Sales Rep Type Description or the specified default value.
    */
   public final String getSlsRepTypeDesc( int index, String defaultValue )
   {
      return _SlsRepTypeDesc[index] == null ? defaultValue : _SlsRepTypeDesc[index];
   }
    
   /**
    * Gets the array of Sales Rep Type Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Sales Rep Type Description values.
    */
   public final String[] getSlsRepTypeDescArray()
   {
      return _SlsRepTypeDesc;
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
    * Gets the Agent's Alternate Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Agent's Alternate Name or null.
    */
   public final String getSlsRepAltName( int index )
   {
      return _SlsRepAltName[index];
   }
    
   /**
    * Gets the Agent's Alternate Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Agent's Alternate Name or the specified default value.
    */
   public final String getSlsRepAltName( int index, String defaultValue )
   {
      return _SlsRepAltName[index] == null ? defaultValue : _SlsRepAltName[index];
   }
    
   /**
    * Gets the array of Agent's Alternate Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Agent's Alternate Name values.
    */
   public final String[] getSlsRepAltNameArray()
   {
      return _SlsRepAltName;
   }
    
   /**
    * Gets the Provinces where rep can sell seg funds field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Provinces where rep can sell seg funds or null.
    */
   public final String getSegLicenseProvList( int index )
   {
      return _SegLicenseProvList[index];
   }
    
   /**
    * Gets the Provinces where rep can sell seg funds field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Provinces where rep can sell seg funds or the specified default value.
    */
   public final String getSegLicenseProvList( int index, String defaultValue )
   {
      return _SegLicenseProvList[index] == null ? defaultValue : _SegLicenseProvList[index];
   }
    
   /**
    * Gets the array of Provinces where rep can sell seg funds fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Provinces where rep can sell seg funds values.
    */
   public final String[] getSegLicenseProvListArray()
   {
      return _SegLicenseProvList;
   }
    
   /**
    * Gets the Slsperson can deal with new product or not field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Slsperson can deal with new product or not or null.
    */
   public final Boolean getNewBusiness( int index )
   {
      return _NewBusiness[index];
   }
    
   /**
    * Gets the Slsperson can deal with new product or not field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Slsperson can deal with new product or not or the specified default value.
    */
   public final boolean getNewBusiness( int index, boolean defaultValue )
   {
      return _NewBusiness[index] == null ? defaultValue : _NewBusiness[index].booleanValue();
   }
    
   /**
    * Gets the array of Slsperson can deal with new product or not fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Slsperson can deal with new product or not values.
    */
   public final Boolean[] getNewBusinessArray()
   {
      return _NewBusiness;
   }
    
   /**
    * Gets the Broker's Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Broker's Name or null.
    */
   public final String getBrokerName( int index )
   {
      return _BrokerName[index];
   }
    
   /**
    * Gets the Broker's Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Broker's Name or the specified default value.
    */
   public final String getBrokerName( int index, String defaultValue )
   {
      return _BrokerName[index] == null ? defaultValue : _BrokerName[index];
   }
    
   /**
    * Gets the array of Broker's Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Broker's Name values.
    */
   public final String[] getBrokerNameArray()
   {
      return _BrokerName;
   }
    
   /**
    * Gets the Branch's Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Branch's Name or null.
    */
   public final String getBranchName( int index )
   {
      return _BranchName[index];
   }
    
   /**
    * Gets the Branch's Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Branch's Name or the specified default value.
    */
   public final String getBranchName( int index, String defaultValue )
   {
      return _BranchName[index] == null ? defaultValue : _BranchName[index];
   }
    
   /**
    * Gets the array of Branch's Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Branch's Name values.
    */
   public final String[] getBranchNameArray()
   {
      return _BranchName;
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
    * Gets the Email Address field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Email Address or null.
    */
   public final String getEmail( int index )
   {
      return _Email[index];
   }
    
   /**
    * Gets the Email Address field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Email Address or the specified default value.
    */
   public final String getEmail( int index, String defaultValue )
   {
      return _Email[index] == null ? defaultValue : _Email[index];
   }
    
   /**
    * Gets the array of Email Address fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Email Address values.
    */
   public final String[] getEmailArray()
   {
      return _Email;
   }
    
   /**
    * Gets the Fax Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fax Number or null.
    */
   public final String getFaxNumber( int index )
   {
      return _FaxNumber[index];
   }
    
   /**
    * Gets the Fax Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fax Number or the specified default value.
    */
   public final String getFaxNumber( int index, String defaultValue )
   {
      return _FaxNumber[index] == null ? defaultValue : _FaxNumber[index];
   }
    
   /**
    * Gets the array of Fax Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fax Number values.
    */
   public final String[] getFaxNumberArray()
   {
      return _FaxNumber;
   }
    
   /**
    * Gets the Country Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Country Name or null.
    */
   public final String getAddrCntry( int index )
   {
      return _AddrCntry[index];
   }
    
   /**
    * Gets the Country Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Country Name or the specified default value.
    */
   public final String getAddrCntry( int index, String defaultValue )
   {
      return _AddrCntry[index] == null ? defaultValue : _AddrCntry[index];
   }
    
   /**
    * Gets the array of Country Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Country Name values.
    */
   public final String[] getAddrCntryArray()
   {
      return _AddrCntry;
   }
    
   /**
    * Gets the Sales Rep Country Code (phone) field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Sales Rep Country Code (phone) or null.
    */
   public final String getSlsRepCntry( int index )
   {
      return _SlsRepCntry[index];
   }
    
   /**
    * Gets the Sales Rep Country Code (phone) field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Sales Rep Country Code (phone) or the specified default value.
    */
   public final String getSlsRepCntry( int index, String defaultValue )
   {
      return _SlsRepCntry[index] == null ? defaultValue : _SlsRepCntry[index];
   }
    
   /**
    * Gets the array of Sales Rep Country Code (phone) fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Sales Rep Country Code (phone) values.
    */
   public final String[] getSlsRepCntryArray()
   {
      return _SlsRepCntry;
   }
    
   /**
    * Gets the Sales Rep Area Code (phone) field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Sales Rep Area Code (phone) or null.
    */
   public final String getSlsRepArea( int index )
   {
      return _SlsRepArea[index];
   }
    
   /**
    * Gets the Sales Rep Area Code (phone) field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Sales Rep Area Code (phone) or the specified default value.
    */
   public final String getSlsRepArea( int index, String defaultValue )
   {
      return _SlsRepArea[index] == null ? defaultValue : _SlsRepArea[index];
   }
    
   /**
    * Gets the array of Sales Rep Area Code (phone) fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Sales Rep Area Code (phone) values.
    */
   public final String[] getSlsRepAreaArray()
   {
      return _SlsRepArea;
   }
    
   /**
    * Gets the Fax Country Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fax Country Code or null.
    */
   public final String getFaxCntryCode( int index )
   {
      return _FaxCntryCode[index];
   }
    
   /**
    * Gets the Fax Country Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fax Country Code or the specified default value.
    */
   public final String getFaxCntryCode( int index, String defaultValue )
   {
      return _FaxCntryCode[index] == null ? defaultValue : _FaxCntryCode[index];
   }
    
   /**
    * Gets the array of Fax Country Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fax Country Code values.
    */
   public final String[] getFaxCntryCodeArray()
   {
      return _FaxCntryCode;
   }
    
   /**
    * Gets the Fax Area Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fax Area Code or null.
    */
   public final String getFaxAreaCode( int index )
   {
      return _FaxAreaCode[index];
   }
    
   /**
    * Gets the Fax Area Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fax Area Code or the specified default value.
    */
   public final String getFaxAreaCode( int index, String defaultValue )
   {
      return _FaxAreaCode[index] == null ? defaultValue : _FaxAreaCode[index];
   }
    
   /**
    * Gets the array of Fax Area Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fax Area Code values.
    */
   public final String[] getFaxAreaCodeArray()
   {
      return _FaxAreaCode;
   }
    
   /**
    * Gets the Flag indicating if SlsRep passed validation field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicating if SlsRep passed validation or null.
    */
   public final Boolean getValidationPassed( int index )
   {
      return _ValidationPassed[index];
   }
    
   /**
    * Gets the Flag indicating if SlsRep passed validation field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if SlsRep passed validation or the specified default value.
    */
   public final boolean getValidationPassed( int index, boolean defaultValue )
   {
      return _ValidationPassed[index] == null ? defaultValue : _ValidationPassed[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicating if SlsRep passed validation fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicating if SlsRep passed validation values.
    */
   public final Boolean[] getValidationPassedArray()
   {
      return _ValidationPassed;
   }
    
   /**
    * Gets the Payment Instructions for Trailers Avail field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Payment Instructions for Trailers Avail or null.
    */
   public final Boolean getPayInstrTrailer( int index )
   {
      return _PayInstrTrailer[index];
   }
    
   /**
    * Gets the Payment Instructions for Trailers Avail field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Payment Instructions for Trailers Avail or the specified default value.
    */
   public final boolean getPayInstrTrailer( int index, boolean defaultValue )
   {
      return _PayInstrTrailer[index] == null ? defaultValue : _PayInstrTrailer[index].booleanValue();
   }
    
   /**
    * Gets the array of Payment Instructions for Trailers Avail fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Payment Instructions for Trailers Avail values.
    */
   public final Boolean[] getPayInstrTrailerArray()
   {
      return _PayInstrTrailer;
   }
    
   /**
    * Gets the Payment Instructions for Comm Avail field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Payment Instructions for Comm Avail or null.
    */
   public final Boolean getPayInstrComm( int index )
   {
      return _PayInstrComm[index];
   }
    
   /**
    * Gets the Payment Instructions for Comm Avail field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Payment Instructions for Comm Avail or the specified default value.
    */
   public final boolean getPayInstrComm( int index, boolean defaultValue )
   {
      return _PayInstrComm[index] == null ? defaultValue : _PayInstrComm[index].booleanValue();
   }
    
   /**
    * Gets the array of Payment Instructions for Comm Avail fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Payment Instructions for Comm Avail values.
    */
   public final Boolean[] getPayInstrCommArray()
   {
      return _PayInstrComm;
   }
    
   /**
    * Gets the Sales Rep Level field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Sales Rep Level or null.
    */
   public final Integer getRepLevel( int index )
   {
      return _RepLevel[index];
   }
    
   /**
    * Gets the Sales Rep Level field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Sales Rep Level or the specified default value.
    */
   public final int getRepLevel( int index, int defaultValue )
   {
      return _RepLevel[index] == null ? defaultValue : _RepLevel[index].intValue();
   }
    
   /**
    * Gets the array of Sales Rep Level fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Sales Rep Level values.
    */
   public final Integer[] getRepLevelArray()
   {
      return _RepLevel;
   }
    
   /**
    * Gets the Agent Status field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Agent Status or null.
    */
   public final Boolean getAgentStat( int index )
   {
      return _AgentStat[index];
   }
    
   /**
    * Gets the Agent Status field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Agent Status or the specified default value.
    */
   public final boolean getAgentStat( int index, boolean defaultValue )
   {
      return _AgentStat[index] == null ? defaultValue : _AgentStat[index].booleanValue();
   }
    
   /**
    * Gets the array of Agent Status fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Agent Status values.
    */
   public final Boolean[] getAgentStatArray()
   {
      return _AgentStat;
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
      
      _rxSlsRep = resizeArray( _rxSlsRep, _RepeatCount );
      _SalesRepName = resizeArray( _SalesRepName, _RepeatCount );
      _AddrLine1 = resizeArray( _AddrLine1, _RepeatCount );
      _AddrLine2 = resizeArray( _AddrLine2, _RepeatCount );
      _AddrLine3 = resizeArray( _AddrLine3, _RepeatCount );
      _AddrLine4 = resizeArray( _AddrLine4, _RepeatCount );
      _AddrLine5 = resizeArray( _AddrLine5, _RepeatCount );
      _AddrCntryCode = resizeArray( _AddrCntryCode, _RepeatCount );
      _PhoneNumber = resizeArray( _PhoneNumber, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _StopDate = resizeArray( _StopDate, _RepeatCount );
      _TrailEligible = resizeArray( _TrailEligible, _RepeatCount );
      _PayType = resizeArray( _PayType, _RepeatCount );
      _PayTypeDesc = resizeArray( _PayTypeDesc, _RepeatCount );
      _Currency = resizeArray( _Currency, _RepeatCount );
      _CurrencyName = resizeArray( _CurrencyName, _RepeatCount );
      _PayFreq = resizeArray( _PayFreq, _RepeatCount );
      _PayFreqDesc = resizeArray( _PayFreqDesc, _RepeatCount );
      _rxBrokerCode = resizeArray( _rxBrokerCode, _RepeatCount );
      _rxBranchCode = resizeArray( _rxBranchCode, _RepeatCount );
      _SlsRepType = resizeArray( _SlsRepType, _RepeatCount );
      _SlsRepTypeDesc = resizeArray( _SlsRepTypeDesc, _RepeatCount );
      _EffectiveDate = resizeArray( _EffectiveDate, _RepeatCount );
      _SlsRepAltName = resizeArray( _SlsRepAltName, _RepeatCount );
      _SegLicenseProvList = resizeArray( _SegLicenseProvList, _RepeatCount );
      _NewBusiness = resizeArray( _NewBusiness, _RepeatCount );
      _BrokerName = resizeArray( _BrokerName, _RepeatCount );
      _BranchName = resizeArray( _BranchName, _RepeatCount );
      _PostalCode = resizeArray( _PostalCode, _RepeatCount );
      _Email = resizeArray( _Email, _RepeatCount );
      _FaxNumber = resizeArray( _FaxNumber, _RepeatCount );
      _AddrCntry = resizeArray( _AddrCntry, _RepeatCount );
      _SlsRepCntry = resizeArray( _SlsRepCntry, _RepeatCount );
      _SlsRepArea = resizeArray( _SlsRepArea, _RepeatCount );
      _FaxCntryCode = resizeArray( _FaxCntryCode, _RepeatCount );
      _FaxAreaCode = resizeArray( _FaxAreaCode, _RepeatCount );
      _ValidationPassed = resizeArray( _ValidationPassed, _RepeatCount );
      _PayInstrTrailer = resizeArray( _PayInstrTrailer, _RepeatCount );
      _PayInstrComm = resizeArray( _PayInstrComm, _RepeatCount );
      _RepLevel = resizeArray( _RepLevel, _RepeatCount );
      _AgentStat = resizeArray( _AgentStat, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxSlsRep[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SalesRepName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine3[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine4[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine5[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrCntryCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PhoneNumber[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _StopDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _TrailEligible[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _PayType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PayTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Currency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CurrencyName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PayFreq[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PayFreqDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxBrokerCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxBranchCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SlsRepType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SlsRepTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EffectiveDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _SlsRepAltName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SegLicenseProvList[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _NewBusiness[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _BrokerName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BranchName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PostalCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Email[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FaxNumber[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrCntry[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SlsRepCntry[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SlsRepArea[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FaxCntryCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FaxAreaCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ValidationPassed[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _PayInstrTrailer[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _PayInstrComm[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _RepLevel[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _AgentStat[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      }
      

   }

}
      
