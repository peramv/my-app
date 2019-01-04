
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Fund Master Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/FundMasterInquiry.doc">FundMasterInquiry.doc</A>.
 * 
 * @author RTS Generated
 */
public class FundMasterInquiryView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Fund Code member array.
    */
   private String[] _FundCode = null;
   
   /**
    * English Long Name1 member array.
    */
   private String[] _ElongName1 = null;
   
   /**
    * English Long Name2 member array.
    */
   private String[] _ElongName2 = null;
   
   /**
    * English Short Name member array.
    */
   private String[] _EShortName = null;
   
   /**
    * French Long Name1 member array.
    */
   private String[] _FLongName = null;
   
   /**
    * French Long Name2 member array.
    */
   private String[] _FLongName2 = null;
   
   /**
    * French Short Name member array.
    */
   private String[] _FShortName = null;
   
   /**
    * Fund Type member array.
    */
   private String[] _FundType = null;
   
   /**
    * Fund Type Description member array.
    */
   private String[] _FundTypeDesc = null;
   
   /**
    * Cusip Number member array.
    */
   private String[] _CusipNum = null;
   
   /**
    * Price At Class member array.
    */
   private Boolean[] _PriceAtClass = null;
   
   /**
    * Effective Date member array.
    */
   private Date[] _EffectiveDate = null;
   
   /**
    * Stop Date member array.
    */
   private Date[] _StopDate = null;
   
   /**
    * Is Fund Eligible for PAC member array.
    */
   private Boolean[] _PACavail = null;
   
   /**
    * Is Fund Eligible for SWP member array.
    */
   private Boolean[] _SWPavail = null;
   
   /**
    * Fund Status Code member array.
    */
   private String[] _FundStatus = null;
   
   /**
    * Effective Date of Fund Status member array.
    */
   private Date[] _StatusDate = null;
   
   /**
    * Dividend Type member array.
    */
   private String[] _DividendType = null;
   
   /**
    * DateType(cash/trade) int is from for div member array.
    */
   private String[] _IntFromDateType = null;
   
   /**
    * DateType(cash/trade) int is to for red member array.
    */
   private String[] _IntToDateType = null;
   
   /**
    * Should issue cert or not member array.
    */
   private String[] _CertIssued = null;
   
   /**
    * Settlement Days for Purchase member array.
    */
   private Integer[] _SettlePurDays = null;
   
   /**
    * Settlement Days for Redemption member array.
    */
   private Integer[] _SettleRedDays = null;
   
   /**
    * Sponsor Code member array.
    */
   private String[] _FundGroup = null;
   
   /**
    * Indicates when unallocated income is paid member array.
    */
   private String[] _PayIntOn = null;
   
   /**
    * Pay Interest On Description member array.
    */
   private String[] _PayIntOnDesc = null;
   
   /**
    * Net Allowed member array.
    */
   private Boolean[] _NetAllowed = null;
   
   /**
    * Currency List member array.
    */
   private String[] _CurrList = null;
   
   /**
    * Fund Category member array.
    */
   private String[] _FundCategory = null;
   
   /**
    * Domestic member array.
    */
   private Boolean[] _Domestic = null;
   
   /**
    * Money Market Fund member array.
    */
   private Boolean[] _MoneyMktFund = null;
   
   /**
    * Investment Prod member array.
    */
   private String[] _InvestProd = null;
   
   /**
    * Interest Accrual Method member array.
    */
   private Integer[] _IntAccrualMthd = null;
   
   /**
    * PUEV Capable member array.
    */
   private Boolean[] _PUEVCapable = null;
   
   /**
    * Investro Capable member array.
    */
   private Boolean[] _InvestroCapable = null;
   
   /**
    * Other Fund Type member array.
    */
   private String[] _OtherFundType = null;
   
   /**
    * Fund Confirmation member array.
    */
   private Boolean[] _FundConfirm = null;
   
   /**
    * Tax Type member array.
    */
   private String[] _TaxType = null;
   
   /**
    * Unit Rounding Method member array.
    */
   private String[] _UnitRoundMethod = null;
   
   /**
    * Pend Trd Contr Trans List member array.
    */
   private String[] _PendTrdContrTransList = null;
   

   /**
    * Constructs the FundMasterInquiryView object.
    * 
    */
   public FundMasterInquiryView()
   {
      super ( new FundMasterInquiryRequest() );
   }

   /**
    * Constructs the FundMasterInquiryView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public FundMasterInquiryView( String hostEncoding )
   {
      super ( new FundMasterInquiryRequest( hostEncoding ) );
   }

   /**
    * Gets the FundMasterInquiryRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The FundMasterInquiryRequest object.
    */
   public final FundMasterInquiryRequest getRequest()
   {
      return (FundMasterInquiryRequest)getIFastRequest();
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
    * Gets the Fund Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Code or null.
    */
   public final String getFundCode( int index )
   {
      return _FundCode[index];
   }
    
   /**
    * Gets the Fund Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Code or the specified default value.
    */
   public final String getFundCode( int index, String defaultValue )
   {
      return _FundCode[index] == null ? defaultValue : _FundCode[index];
   }
    
   /**
    * Gets the array of Fund Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Code values.
    */
   public final String[] getFundCodeArray()
   {
      return _FundCode;
   }
    
   /**
    * Gets the English Long Name1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the English Long Name1 or null.
    */
   public final String getElongName1( int index )
   {
      return _ElongName1[index];
   }
    
   /**
    * Gets the English Long Name1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the English Long Name1 or the specified default value.
    */
   public final String getElongName1( int index, String defaultValue )
   {
      return _ElongName1[index] == null ? defaultValue : _ElongName1[index];
   }
    
   /**
    * Gets the array of English Long Name1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of English Long Name1 values.
    */
   public final String[] getElongName1Array()
   {
      return _ElongName1;
   }
    
   /**
    * Gets the English Long Name2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the English Long Name2 or null.
    */
   public final String getElongName2( int index )
   {
      return _ElongName2[index];
   }
    
   /**
    * Gets the English Long Name2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the English Long Name2 or the specified default value.
    */
   public final String getElongName2( int index, String defaultValue )
   {
      return _ElongName2[index] == null ? defaultValue : _ElongName2[index];
   }
    
   /**
    * Gets the array of English Long Name2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of English Long Name2 values.
    */
   public final String[] getElongName2Array()
   {
      return _ElongName2;
   }
    
   /**
    * Gets the English Short Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the English Short Name or null.
    */
   public final String getEShortName( int index )
   {
      return _EShortName[index];
   }
    
   /**
    * Gets the English Short Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the English Short Name or the specified default value.
    */
   public final String getEShortName( int index, String defaultValue )
   {
      return _EShortName[index] == null ? defaultValue : _EShortName[index];
   }
    
   /**
    * Gets the array of English Short Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of English Short Name values.
    */
   public final String[] getEShortNameArray()
   {
      return _EShortName;
   }
    
   /**
    * Gets the French Long Name1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the French Long Name1 or null.
    */
   public final String getFLongName( int index )
   {
      return _FLongName[index];
   }
    
   /**
    * Gets the French Long Name1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the French Long Name1 or the specified default value.
    */
   public final String getFLongName( int index, String defaultValue )
   {
      return _FLongName[index] == null ? defaultValue : _FLongName[index];
   }
    
   /**
    * Gets the array of French Long Name1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of French Long Name1 values.
    */
   public final String[] getFLongNameArray()
   {
      return _FLongName;
   }
    
   /**
    * Gets the French Long Name2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the French Long Name2 or null.
    */
   public final String getFLongName2( int index )
   {
      return _FLongName2[index];
   }
    
   /**
    * Gets the French Long Name2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the French Long Name2 or the specified default value.
    */
   public final String getFLongName2( int index, String defaultValue )
   {
      return _FLongName2[index] == null ? defaultValue : _FLongName2[index];
   }
    
   /**
    * Gets the array of French Long Name2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of French Long Name2 values.
    */
   public final String[] getFLongName2Array()
   {
      return _FLongName2;
   }
    
   /**
    * Gets the French Short Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the French Short Name or null.
    */
   public final String getFShortName( int index )
   {
      return _FShortName[index];
   }
    
   /**
    * Gets the French Short Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the French Short Name or the specified default value.
    */
   public final String getFShortName( int index, String defaultValue )
   {
      return _FShortName[index] == null ? defaultValue : _FShortName[index];
   }
    
   /**
    * Gets the array of French Short Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of French Short Name values.
    */
   public final String[] getFShortNameArray()
   {
      return _FShortName;
   }
    
   /**
    * Gets the Fund Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Type or null.
    */
   public final String getFundType( int index )
   {
      return _FundType[index];
   }
    
   /**
    * Gets the Fund Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Type or the specified default value.
    */
   public final String getFundType( int index, String defaultValue )
   {
      return _FundType[index] == null ? defaultValue : _FundType[index];
   }
    
   /**
    * Gets the array of Fund Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Type values.
    */
   public final String[] getFundTypeArray()
   {
      return _FundType;
   }
    
   /**
    * Gets the Fund Type Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Type Description or null.
    */
   public final String getFundTypeDesc( int index )
   {
      return _FundTypeDesc[index];
   }
    
   /**
    * Gets the Fund Type Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Type Description or the specified default value.
    */
   public final String getFundTypeDesc( int index, String defaultValue )
   {
      return _FundTypeDesc[index] == null ? defaultValue : _FundTypeDesc[index];
   }
    
   /**
    * Gets the array of Fund Type Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Type Description values.
    */
   public final String[] getFundTypeDescArray()
   {
      return _FundTypeDesc;
   }
    
   /**
    * Gets the Cusip Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Cusip Number or null.
    */
   public final String getCusipNum( int index )
   {
      return _CusipNum[index];
   }
    
   /**
    * Gets the Cusip Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Cusip Number or the specified default value.
    */
   public final String getCusipNum( int index, String defaultValue )
   {
      return _CusipNum[index] == null ? defaultValue : _CusipNum[index];
   }
    
   /**
    * Gets the array of Cusip Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Cusip Number values.
    */
   public final String[] getCusipNumArray()
   {
      return _CusipNum;
   }
    
   /**
    * Gets the Price At Class field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Price At Class or null.
    */
   public final Boolean getPriceAtClass( int index )
   {
      return _PriceAtClass[index];
   }
    
   /**
    * Gets the Price At Class field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Price At Class or the specified default value.
    */
   public final boolean getPriceAtClass( int index, boolean defaultValue )
   {
      return _PriceAtClass[index] == null ? defaultValue : _PriceAtClass[index].booleanValue();
   }
    
   /**
    * Gets the array of Price At Class fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Price At Class values.
    */
   public final Boolean[] getPriceAtClassArray()
   {
      return _PriceAtClass;
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
    * Gets the Is Fund Eligible for PAC field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Is Fund Eligible for PAC or null.
    */
   public final Boolean getPACavail( int index )
   {
      return _PACavail[index];
   }
    
   /**
    * Gets the Is Fund Eligible for PAC field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Is Fund Eligible for PAC or the specified default value.
    */
   public final boolean getPACavail( int index, boolean defaultValue )
   {
      return _PACavail[index] == null ? defaultValue : _PACavail[index].booleanValue();
   }
    
   /**
    * Gets the array of Is Fund Eligible for PAC fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Is Fund Eligible for PAC values.
    */
   public final Boolean[] getPACavailArray()
   {
      return _PACavail;
   }
    
   /**
    * Gets the Is Fund Eligible for SWP field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Is Fund Eligible for SWP or null.
    */
   public final Boolean getSWPavail( int index )
   {
      return _SWPavail[index];
   }
    
   /**
    * Gets the Is Fund Eligible for SWP field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Is Fund Eligible for SWP or the specified default value.
    */
   public final boolean getSWPavail( int index, boolean defaultValue )
   {
      return _SWPavail[index] == null ? defaultValue : _SWPavail[index].booleanValue();
   }
    
   /**
    * Gets the array of Is Fund Eligible for SWP fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Is Fund Eligible for SWP values.
    */
   public final Boolean[] getSWPavailArray()
   {
      return _SWPavail;
   }
    
   /**
    * Gets the Fund Status Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Status Code or null.
    */
   public final String getFundStatus( int index )
   {
      return _FundStatus[index];
   }
    
   /**
    * Gets the Fund Status Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Status Code or the specified default value.
    */
   public final String getFundStatus( int index, String defaultValue )
   {
      return _FundStatus[index] == null ? defaultValue : _FundStatus[index];
   }
    
   /**
    * Gets the array of Fund Status Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Status Code values.
    */
   public final String[] getFundStatusArray()
   {
      return _FundStatus;
   }
    
   /**
    * Gets the Effective Date of Fund Status field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Effective Date of Fund Status or null.
    */
   public final Date getStatusDate( int index )
   {
      return _StatusDate[index];
   }
    
   /**
    * Gets the Effective Date of Fund Status field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Effective Date of Fund Status or the specified default value.
    */
   public final Date getStatusDate( int index, Date defaultValue )
   {
      return _StatusDate[index] == null ? defaultValue : _StatusDate[index];
   }
    
   /**
    * Gets the array of Effective Date of Fund Status fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Effective Date of Fund Status values.
    */
   public final Date[] getStatusDateArray()
   {
      return _StatusDate;
   }
    
   /**
    * Gets the Dividend Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Dividend Type or null.
    */
   public final String getDividendType( int index )
   {
      return _DividendType[index];
   }
    
   /**
    * Gets the Dividend Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Dividend Type or the specified default value.
    */
   public final String getDividendType( int index, String defaultValue )
   {
      return _DividendType[index] == null ? defaultValue : _DividendType[index];
   }
    
   /**
    * Gets the array of Dividend Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Dividend Type values.
    */
   public final String[] getDividendTypeArray()
   {
      return _DividendType;
   }
    
   /**
    * Gets the DateType(cash/trade) int is from for div field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the DateType(cash/trade) int is from for div or null.
    */
   public final String getIntFromDateType( int index )
   {
      return _IntFromDateType[index];
   }
    
   /**
    * Gets the DateType(cash/trade) int is from for div field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the DateType(cash/trade) int is from for div or the specified default value.
    */
   public final String getIntFromDateType( int index, String defaultValue )
   {
      return _IntFromDateType[index] == null ? defaultValue : _IntFromDateType[index];
   }
    
   /**
    * Gets the array of DateType(cash/trade) int is from for div fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of DateType(cash/trade) int is from for div values.
    */
   public final String[] getIntFromDateTypeArray()
   {
      return _IntFromDateType;
   }
    
   /**
    * Gets the DateType(cash/trade) int is to for red field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the DateType(cash/trade) int is to for red or null.
    */
   public final String getIntToDateType( int index )
   {
      return _IntToDateType[index];
   }
    
   /**
    * Gets the DateType(cash/trade) int is to for red field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the DateType(cash/trade) int is to for red or the specified default value.
    */
   public final String getIntToDateType( int index, String defaultValue )
   {
      return _IntToDateType[index] == null ? defaultValue : _IntToDateType[index];
   }
    
   /**
    * Gets the array of DateType(cash/trade) int is to for red fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of DateType(cash/trade) int is to for red values.
    */
   public final String[] getIntToDateTypeArray()
   {
      return _IntToDateType;
   }
    
   /**
    * Gets the Should issue cert or not field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Should issue cert or not or null.
    */
   public final String getCertIssued( int index )
   {
      return _CertIssued[index];
   }
    
   /**
    * Gets the Should issue cert or not field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Should issue cert or not or the specified default value.
    */
   public final String getCertIssued( int index, String defaultValue )
   {
      return _CertIssued[index] == null ? defaultValue : _CertIssued[index];
   }
    
   /**
    * Gets the array of Should issue cert or not fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Should issue cert or not values.
    */
   public final String[] getCertIssuedArray()
   {
      return _CertIssued;
   }
    
   /**
    * Gets the Settlement Days for Purchase field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Settlement Days for Purchase or null.
    */
   public final Integer getSettlePurDays( int index )
   {
      return _SettlePurDays[index];
   }
    
   /**
    * Gets the Settlement Days for Purchase field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Settlement Days for Purchase or the specified default value.
    */
   public final int getSettlePurDays( int index, int defaultValue )
   {
      return _SettlePurDays[index] == null ? defaultValue : _SettlePurDays[index].intValue();
   }
    
   /**
    * Gets the array of Settlement Days for Purchase fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Settlement Days for Purchase values.
    */
   public final Integer[] getSettlePurDaysArray()
   {
      return _SettlePurDays;
   }
    
   /**
    * Gets the Settlement Days for Redemption field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Settlement Days for Redemption or null.
    */
   public final Integer getSettleRedDays( int index )
   {
      return _SettleRedDays[index];
   }
    
   /**
    * Gets the Settlement Days for Redemption field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Settlement Days for Redemption or the specified default value.
    */
   public final int getSettleRedDays( int index, int defaultValue )
   {
      return _SettleRedDays[index] == null ? defaultValue : _SettleRedDays[index].intValue();
   }
    
   /**
    * Gets the array of Settlement Days for Redemption fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Settlement Days for Redemption values.
    */
   public final Integer[] getSettleRedDaysArray()
   {
      return _SettleRedDays;
   }
    
   /**
    * Gets the Sponsor Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Sponsor Code or null.
    */
   public final String getFundGroup( int index )
   {
      return _FundGroup[index];
   }
    
   /**
    * Gets the Sponsor Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Sponsor Code or the specified default value.
    */
   public final String getFundGroup( int index, String defaultValue )
   {
      return _FundGroup[index] == null ? defaultValue : _FundGroup[index];
   }
    
   /**
    * Gets the array of Sponsor Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Sponsor Code values.
    */
   public final String[] getFundGroupArray()
   {
      return _FundGroup;
   }
    
   /**
    * Gets the Indicates when unallocated income is paid field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Indicates when unallocated income is paid or null.
    */
   public final String getPayIntOn( int index )
   {
      return _PayIntOn[index];
   }
    
   /**
    * Gets the Indicates when unallocated income is paid field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Indicates when unallocated income is paid or the specified default value.
    */
   public final String getPayIntOn( int index, String defaultValue )
   {
      return _PayIntOn[index] == null ? defaultValue : _PayIntOn[index];
   }
    
   /**
    * Gets the array of Indicates when unallocated income is paid fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Indicates when unallocated income is paid values.
    */
   public final String[] getPayIntOnArray()
   {
      return _PayIntOn;
   }
    
   /**
    * Gets the Pay Interest On Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Pay Interest On Description or null.
    */
   public final String getPayIntOnDesc( int index )
   {
      return _PayIntOnDesc[index];
   }
    
   /**
    * Gets the Pay Interest On Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Pay Interest On Description or the specified default value.
    */
   public final String getPayIntOnDesc( int index, String defaultValue )
   {
      return _PayIntOnDesc[index] == null ? defaultValue : _PayIntOnDesc[index];
   }
    
   /**
    * Gets the array of Pay Interest On Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Pay Interest On Description values.
    */
   public final String[] getPayIntOnDescArray()
   {
      return _PayIntOnDesc;
   }
    
   /**
    * Gets the Net Allowed field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Net Allowed or null.
    */
   public final Boolean getNetAllowed( int index )
   {
      return _NetAllowed[index];
   }
    
   /**
    * Gets the Net Allowed field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Net Allowed or the specified default value.
    */
   public final boolean getNetAllowed( int index, boolean defaultValue )
   {
      return _NetAllowed[index] == null ? defaultValue : _NetAllowed[index].booleanValue();
   }
    
   /**
    * Gets the array of Net Allowed fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Net Allowed values.
    */
   public final Boolean[] getNetAllowedArray()
   {
      return _NetAllowed;
   }
    
   /**
    * Gets the Currency List field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Currency List or null.
    */
   public final String getCurrList( int index )
   {
      return _CurrList[index];
   }
    
   /**
    * Gets the Currency List field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Currency List or the specified default value.
    */
   public final String getCurrList( int index, String defaultValue )
   {
      return _CurrList[index] == null ? defaultValue : _CurrList[index];
   }
    
   /**
    * Gets the array of Currency List fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Currency List values.
    */
   public final String[] getCurrListArray()
   {
      return _CurrList;
   }
    
   /**
    * Gets the Fund Category field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Category or null.
    */
   public final String getFundCategory( int index )
   {
      return _FundCategory[index];
   }
    
   /**
    * Gets the Fund Category field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Category or the specified default value.
    */
   public final String getFundCategory( int index, String defaultValue )
   {
      return _FundCategory[index] == null ? defaultValue : _FundCategory[index];
   }
    
   /**
    * Gets the array of Fund Category fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Category values.
    */
   public final String[] getFundCategoryArray()
   {
      return _FundCategory;
   }
    
   /**
    * Gets the Domestic field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Domestic or null.
    */
   public final Boolean getDomestic( int index )
   {
      return _Domestic[index];
   }
    
   /**
    * Gets the Domestic field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Domestic or the specified default value.
    */
   public final boolean getDomestic( int index, boolean defaultValue )
   {
      return _Domestic[index] == null ? defaultValue : _Domestic[index].booleanValue();
   }
    
   /**
    * Gets the array of Domestic fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Domestic values.
    */
   public final Boolean[] getDomesticArray()
   {
      return _Domestic;
   }
    
   /**
    * Gets the Money Market Fund field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Money Market Fund or null.
    */
   public final Boolean getMoneyMktFund( int index )
   {
      return _MoneyMktFund[index];
   }
    
   /**
    * Gets the Money Market Fund field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Money Market Fund or the specified default value.
    */
   public final boolean getMoneyMktFund( int index, boolean defaultValue )
   {
      return _MoneyMktFund[index] == null ? defaultValue : _MoneyMktFund[index].booleanValue();
   }
    
   /**
    * Gets the array of Money Market Fund fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Money Market Fund values.
    */
   public final Boolean[] getMoneyMktFundArray()
   {
      return _MoneyMktFund;
   }
    
   /**
    * Gets the Investment Prod field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Investment Prod or null.
    */
   public final String getInvestProd( int index )
   {
      return _InvestProd[index];
   }
    
   /**
    * Gets the Investment Prod field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Investment Prod or the specified default value.
    */
   public final String getInvestProd( int index, String defaultValue )
   {
      return _InvestProd[index] == null ? defaultValue : _InvestProd[index];
   }
    
   /**
    * Gets the array of Investment Prod fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Investment Prod values.
    */
   public final String[] getInvestProdArray()
   {
      return _InvestProd;
   }
    
   /**
    * Gets the Interest Accrual Method field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Interest Accrual Method or null.
    */
   public final Integer getIntAccrualMthd( int index )
   {
      return _IntAccrualMthd[index];
   }
    
   /**
    * Gets the Interest Accrual Method field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Interest Accrual Method or the specified default value.
    */
   public final int getIntAccrualMthd( int index, int defaultValue )
   {
      return _IntAccrualMthd[index] == null ? defaultValue : _IntAccrualMthd[index].intValue();
   }
    
   /**
    * Gets the array of Interest Accrual Method fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Interest Accrual Method values.
    */
   public final Integer[] getIntAccrualMthdArray()
   {
      return _IntAccrualMthd;
   }
    
   /**
    * Gets the PUEV Capable field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the PUEV Capable or null.
    */
   public final Boolean getPUEVCapable( int index )
   {
      return _PUEVCapable[index];
   }
    
   /**
    * Gets the PUEV Capable field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PUEV Capable or the specified default value.
    */
   public final boolean getPUEVCapable( int index, boolean defaultValue )
   {
      return _PUEVCapable[index] == null ? defaultValue : _PUEVCapable[index].booleanValue();
   }
    
   /**
    * Gets the array of PUEV Capable fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of PUEV Capable values.
    */
   public final Boolean[] getPUEVCapableArray()
   {
      return _PUEVCapable;
   }
    
   /**
    * Gets the Investro Capable field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Investro Capable or null.
    */
   public final Boolean getInvestroCapable( int index )
   {
      return _InvestroCapable[index];
   }
    
   /**
    * Gets the Investro Capable field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Investro Capable or the specified default value.
    */
   public final boolean getInvestroCapable( int index, boolean defaultValue )
   {
      return _InvestroCapable[index] == null ? defaultValue : _InvestroCapable[index].booleanValue();
   }
    
   /**
    * Gets the array of Investro Capable fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Investro Capable values.
    */
   public final Boolean[] getInvestroCapableArray()
   {
      return _InvestroCapable;
   }
    
   /**
    * Gets the Other Fund Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Other Fund Type or null.
    */
   public final String getOtherFundType( int index )
   {
      return _OtherFundType[index];
   }
    
   /**
    * Gets the Other Fund Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Other Fund Type or the specified default value.
    */
   public final String getOtherFundType( int index, String defaultValue )
   {
      return _OtherFundType[index] == null ? defaultValue : _OtherFundType[index];
   }
    
   /**
    * Gets the array of Other Fund Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Other Fund Type values.
    */
   public final String[] getOtherFundTypeArray()
   {
      return _OtherFundType;
   }
    
   /**
    * Gets the Fund Confirmation field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Confirmation or null.
    */
   public final Boolean getFundConfirm( int index )
   {
      return _FundConfirm[index];
   }
    
   /**
    * Gets the Fund Confirmation field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Confirmation or the specified default value.
    */
   public final boolean getFundConfirm( int index, boolean defaultValue )
   {
      return _FundConfirm[index] == null ? defaultValue : _FundConfirm[index].booleanValue();
   }
    
   /**
    * Gets the array of Fund Confirmation fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Confirmation values.
    */
   public final Boolean[] getFundConfirmArray()
   {
      return _FundConfirm;
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
    * Gets the Unit Rounding Method field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Unit Rounding Method or null.
    */
   public final String getUnitRoundMethod( int index )
   {
      return _UnitRoundMethod[index];
   }
    
   /**
    * Gets the Unit Rounding Method field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Unit Rounding Method or the specified default value.
    */
   public final String getUnitRoundMethod( int index, String defaultValue )
   {
      return _UnitRoundMethod[index] == null ? defaultValue : _UnitRoundMethod[index];
   }
    
   /**
    * Gets the array of Unit Rounding Method fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Unit Rounding Method values.
    */
   public final String[] getUnitRoundMethodArray()
   {
      return _UnitRoundMethod;
   }
    
   /**
    * Gets the Pend Trd Contr Trans List field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Pend Trd Contr Trans List or null.
    */
   public final String getPendTrdContrTransList( int index )
   {
      return _PendTrdContrTransList[index];
   }
    
   /**
    * Gets the Pend Trd Contr Trans List field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Pend Trd Contr Trans List or the specified default value.
    */
   public final String getPendTrdContrTransList( int index, String defaultValue )
   {
      return _PendTrdContrTransList[index] == null ? defaultValue : _PendTrdContrTransList[index];
   }
    
   /**
    * Gets the array of Pend Trd Contr Trans List fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Pend Trd Contr Trans List values.
    */
   public final String[] getPendTrdContrTransListArray()
   {
      return _PendTrdContrTransList;
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
      
      _FundCode = resizeArray( _FundCode, _RepeatCount );
      _ElongName1 = resizeArray( _ElongName1, _RepeatCount );
      _ElongName2 = resizeArray( _ElongName2, _RepeatCount );
      _EShortName = resizeArray( _EShortName, _RepeatCount );
      _FLongName = resizeArray( _FLongName, _RepeatCount );
      _FLongName2 = resizeArray( _FLongName2, _RepeatCount );
      _FShortName = resizeArray( _FShortName, _RepeatCount );
      _FundType = resizeArray( _FundType, _RepeatCount );
      _FundTypeDesc = resizeArray( _FundTypeDesc, _RepeatCount );
      _CusipNum = resizeArray( _CusipNum, _RepeatCount );
      _PriceAtClass = resizeArray( _PriceAtClass, _RepeatCount );
      _EffectiveDate = resizeArray( _EffectiveDate, _RepeatCount );
      _StopDate = resizeArray( _StopDate, _RepeatCount );
      _PACavail = resizeArray( _PACavail, _RepeatCount );
      _SWPavail = resizeArray( _SWPavail, _RepeatCount );
      _FundStatus = resizeArray( _FundStatus, _RepeatCount );
      _StatusDate = resizeArray( _StatusDate, _RepeatCount );
      _DividendType = resizeArray( _DividendType, _RepeatCount );
      _IntFromDateType = resizeArray( _IntFromDateType, _RepeatCount );
      _IntToDateType = resizeArray( _IntToDateType, _RepeatCount );
      _CertIssued = resizeArray( _CertIssued, _RepeatCount );
      _SettlePurDays = resizeArray( _SettlePurDays, _RepeatCount );
      _SettleRedDays = resizeArray( _SettleRedDays, _RepeatCount );
      _FundGroup = resizeArray( _FundGroup, _RepeatCount );
      _PayIntOn = resizeArray( _PayIntOn, _RepeatCount );
      _PayIntOnDesc = resizeArray( _PayIntOnDesc, _RepeatCount );
      _NetAllowed = resizeArray( _NetAllowed, _RepeatCount );
      _CurrList = resizeArray( _CurrList, _RepeatCount );
      _FundCategory = resizeArray( _FundCategory, _RepeatCount );
      _Domestic = resizeArray( _Domestic, _RepeatCount );
      _MoneyMktFund = resizeArray( _MoneyMktFund, _RepeatCount );
      _InvestProd = resizeArray( _InvestProd, _RepeatCount );
      _IntAccrualMthd = resizeArray( _IntAccrualMthd, _RepeatCount );
      _PUEVCapable = resizeArray( _PUEVCapable, _RepeatCount );
      _InvestroCapable = resizeArray( _InvestroCapable, _RepeatCount );
      _OtherFundType = resizeArray( _OtherFundType, _RepeatCount );
      _FundConfirm = resizeArray( _FundConfirm, _RepeatCount );
      _TaxType = resizeArray( _TaxType, _RepeatCount );
      _UnitRoundMethod = resizeArray( _UnitRoundMethod, _RepeatCount );
      _PendTrdContrTransList = resizeArray( _PendTrdContrTransList, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _FundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ElongName1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ElongName2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EShortName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FLongName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FLongName2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FShortName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CusipNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PriceAtClass[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _EffectiveDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _StopDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _PACavail[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _SWPavail[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _FundStatus[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _StatusDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _DividendType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IntFromDateType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IntToDateType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CertIssued[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SettlePurDays[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _SettleRedDays[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _FundGroup[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PayIntOn[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PayIntOnDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _NetAllowed[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _CurrList[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundCategory[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Domestic[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _MoneyMktFund[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _InvestProd[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IntAccrualMthd[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _PUEVCapable[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _InvestroCapable[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _OtherFundType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundConfirm[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TaxType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _UnitRoundMethod[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PendTrdContrTransList[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
