
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * AMSCode view.
 * For additional view information see <A HREF="../../../../viewspecs/AMSCodeInq.doc">AMSCodeInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class AMSCodeInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * AMS Code member array.
    */
   private String[] _rxAMSCode = null;
   
   /**
    * Rebalance Percent member array.
    */
   private String[] _RBLPrcnt = null;
   
   /**
    * Currency member array.
    */
   private String[] _Currency = null;
   
   /**
    * Effective Date member array.
    */
   private Date[] _EffectiveDate = null;
   
   /**
    * AMS Code Version member array.
    */
   private Integer[] _AMSCodeVer = null;
   
   /**
    * AMS Code currently used by at least 1 account member array.
    */
   private Boolean[] _CodeInUse = null;
   
   /**
    * AMS Name member array.
    */
   private String[] _AMSDesc = null;
   
   /**
    * AMS Type - response member array.
    */
   private String[] _rxAMSType = null;
   
   /**
    * Default Allocation required ? member array.
    */
   private Boolean[] _DefaultAlloc = null;
   
   /**
    * Fund Allocations required ? member array.
    */
   private Boolean[] _FundAlloc = null;
   
   /**
    * English Short Name member array.
    */
   private String[] _EnglishShortName = null;
   
   /**
    * English Long Name member array.
    */
   private String[] _EnglishLongName = null;
   
   /**
    * English Name member array.
    */
   private String[] _EnglishName = null;
   
   /**
    * French Short Name member array.
    */
   private String[] _FrenchShortName = null;
   
   /**
    * French Long Name member array.
    */
   private String[] _FrenchLongName = null;
   
   /**
    * French Name member array.
    */
   private String[] _FrenchName = null;
   
   /**
    * Foreign Rel Fund member array.
    */
   private String[] _ForeignRelfund = null;
   
   /**
    * Foreign Rel Class member array.
    */
   private String[] _ForeignRelClass = null;
   
   /**
    * Rounding Fund member array.
    */
   private String[] _ForeignRelFund = null;
   
   /**
    * Rounding Class member array.
    */
   private String[] _RoundingClass = null;
   
   /**
    * GrandFathered Date AsofDate member array.
    */
   private Date[] _GrandFatheredDate = null;
   
   /**
    * Next Rebal Date member array.
    */
   private Date[] _NextRebalDate = null;
   
   /**
    * Last Rebal Date member array.
    */
   private Date[] _LastRebalDate = null;
   
   /**
    * Thres Hold Amount member array.
    */
   private String[] _ThresholdAmt = null;
   
   /**
    * Wire Eligible member array.
    */
   private Boolean[] _WireElig = null;
   
   /**
    * Mod User member array.
    */
   private String[] _ModUser = null;
   
   /**
    * Process Date member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * Modify Date member array.
    */
   private Date[] _ModDate = null;
   
   /**
    * User Name member array.
    */
   private String[] _UserName = null;
   
   /**
    * Day of the Week member array.
    */
   private Integer[] _DayofWeek = null;
   
   /**
    * AMSRecId member array.
    */
   private Integer[] _AMSRecId = null;
   
   /**
    * Verify  Precreate member array.
    */
   private Boolean[] _VerifyPrecreate = null;
   
   /**
    * Last Deff Date member array.
    */
   private Date[] _LastDeffDate = null;
   
   /**
    * GrandFatherStamped member array.
    */
   private Boolean[] _GrandFatherStamped = null;
   
   /**
    * Associated Fund member array.
    */
   private String[] _AssocFund = null;
   
   /**
    * Associated Class member array.
    */
   private String[] _AssocClass = null;
   
   /**
    * SchedSetupFreqID member array.
    */
   private Integer[] _SchedSetupFreqID = null;
   
   /**
    * Amount member array.
    */
   private String[] _Amount = null;
   
   /**
    * Flag to indicate if traded via parent fund class member array.
    */
   private String[] _ParentFndClsTrdg = null;
   

   /**
    * Constructs the AMSCodeInqView object.
    * 
    */
   public AMSCodeInqView()
   {
      super ( new AMSCodeInqRequest() );
   }

   /**
    * Constructs the AMSCodeInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AMSCodeInqView( String hostEncoding )
   {
      super ( new AMSCodeInqRequest( hostEncoding ) );
   }

   /**
    * Gets the AMSCodeInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AMSCodeInqRequest object.
    */
   public final AMSCodeInqRequest getRequest()
   {
      return (AMSCodeInqRequest)getIFastRequest();
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
    * Gets the AMS Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AMS Code or null.
    */
   public final String getrxAMSCode( int index )
   {
      return _rxAMSCode[index];
   }
    
   /**
    * Gets the AMS Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AMS Code or the specified default value.
    */
   public final String getrxAMSCode( int index, String defaultValue )
   {
      return _rxAMSCode[index] == null ? defaultValue : _rxAMSCode[index];
   }
    
   /**
    * Gets the array of AMS Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AMS Code values.
    */
   public final String[] getrxAMSCodeArray()
   {
      return _rxAMSCode;
   }
    
   /**
    * Gets the Rebalance Percent field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Rebalance Percent or null.
    */
   public final String getRBLPrcnt( int index )
   {
      return _RBLPrcnt[index];
   }
    
   /**
    * Gets the Rebalance Percent field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Rebalance Percent or the specified default value.
    */
   public final String getRBLPrcnt( int index, String defaultValue )
   {
      return _RBLPrcnt[index] == null ? defaultValue : _RBLPrcnt[index];
   }
    
   /**
    * Gets the array of Rebalance Percent fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Rebalance Percent values.
    */
   public final String[] getRBLPrcntArray()
   {
      return _RBLPrcnt;
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
    * Gets the AMS Code Version field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AMS Code Version or null.
    */
   public final Integer getAMSCodeVer( int index )
   {
      return _AMSCodeVer[index];
   }
    
   /**
    * Gets the AMS Code Version field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AMS Code Version or the specified default value.
    */
   public final int getAMSCodeVer( int index, int defaultValue )
   {
      return _AMSCodeVer[index] == null ? defaultValue : _AMSCodeVer[index].intValue();
   }
    
   /**
    * Gets the array of AMS Code Version fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AMS Code Version values.
    */
   public final Integer[] getAMSCodeVerArray()
   {
      return _AMSCodeVer;
   }
    
   /**
    * Gets the AMS Code currently used by at least 1 account field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AMS Code currently used by at least 1 account or null.
    */
   public final Boolean getCodeInUse( int index )
   {
      return _CodeInUse[index];
   }
    
   /**
    * Gets the AMS Code currently used by at least 1 account field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AMS Code currently used by at least 1 account or the specified default value.
    */
   public final boolean getCodeInUse( int index, boolean defaultValue )
   {
      return _CodeInUse[index] == null ? defaultValue : _CodeInUse[index].booleanValue();
   }
    
   /**
    * Gets the array of AMS Code currently used by at least 1 account fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AMS Code currently used by at least 1 account values.
    */
   public final Boolean[] getCodeInUseArray()
   {
      return _CodeInUse;
   }
    
   /**
    * Gets the AMS Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AMS Name or null.
    */
   public final String getAMSDesc( int index )
   {
      return _AMSDesc[index];
   }
    
   /**
    * Gets the AMS Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AMS Name or the specified default value.
    */
   public final String getAMSDesc( int index, String defaultValue )
   {
      return _AMSDesc[index] == null ? defaultValue : _AMSDesc[index];
   }
    
   /**
    * Gets the array of AMS Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AMS Name values.
    */
   public final String[] getAMSDescArray()
   {
      return _AMSDesc;
   }
    
   /**
    * Gets the AMS Type - response field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AMS Type - response or null.
    */
   public final String getrxAMSType( int index )
   {
      return _rxAMSType[index];
   }
    
   /**
    * Gets the AMS Type - response field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AMS Type - response or the specified default value.
    */
   public final String getrxAMSType( int index, String defaultValue )
   {
      return _rxAMSType[index] == null ? defaultValue : _rxAMSType[index];
   }
    
   /**
    * Gets the array of AMS Type - response fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AMS Type - response values.
    */
   public final String[] getrxAMSTypeArray()
   {
      return _rxAMSType;
   }
    
   /**
    * Gets the Default Allocation required ? field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Default Allocation required ? or null.
    */
   public final Boolean getDefaultAlloc( int index )
   {
      return _DefaultAlloc[index];
   }
    
   /**
    * Gets the Default Allocation required ? field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Default Allocation required ? or the specified default value.
    */
   public final boolean getDefaultAlloc( int index, boolean defaultValue )
   {
      return _DefaultAlloc[index] == null ? defaultValue : _DefaultAlloc[index].booleanValue();
   }
    
   /**
    * Gets the array of Default Allocation required ? fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Default Allocation required ? values.
    */
   public final Boolean[] getDefaultAllocArray()
   {
      return _DefaultAlloc;
   }
    
   /**
    * Gets the Fund Allocations required ? field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Allocations required ? or null.
    */
   public final Boolean getFundAlloc( int index )
   {
      return _FundAlloc[index];
   }
    
   /**
    * Gets the Fund Allocations required ? field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Allocations required ? or the specified default value.
    */
   public final boolean getFundAlloc( int index, boolean defaultValue )
   {
      return _FundAlloc[index] == null ? defaultValue : _FundAlloc[index].booleanValue();
   }
    
   /**
    * Gets the array of Fund Allocations required ? fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Allocations required ? values.
    */
   public final Boolean[] getFundAllocArray()
   {
      return _FundAlloc;
   }
    
   /**
    * Gets the English Short Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the English Short Name or null.
    */
   public final String getEnglishShortName( int index )
   {
      return _EnglishShortName[index];
   }
    
   /**
    * Gets the English Short Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the English Short Name or the specified default value.
    */
   public final String getEnglishShortName( int index, String defaultValue )
   {
      return _EnglishShortName[index] == null ? defaultValue : _EnglishShortName[index];
   }
    
   /**
    * Gets the array of English Short Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of English Short Name values.
    */
   public final String[] getEnglishShortNameArray()
   {
      return _EnglishShortName;
   }
    
   /**
    * Gets the English Long Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the English Long Name or null.
    */
   public final String getEnglishLongName( int index )
   {
      return _EnglishLongName[index];
   }
    
   /**
    * Gets the English Long Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the English Long Name or the specified default value.
    */
   public final String getEnglishLongName( int index, String defaultValue )
   {
      return _EnglishLongName[index] == null ? defaultValue : _EnglishLongName[index];
   }
    
   /**
    * Gets the array of English Long Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of English Long Name values.
    */
   public final String[] getEnglishLongNameArray()
   {
      return _EnglishLongName;
   }
    
   /**
    * Gets the English Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the English Name or null.
    */
   public final String getEnglishName( int index )
   {
      return _EnglishName[index];
   }
    
   /**
    * Gets the English Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the English Name or the specified default value.
    */
   public final String getEnglishName( int index, String defaultValue )
   {
      return _EnglishName[index] == null ? defaultValue : _EnglishName[index];
   }
    
   /**
    * Gets the array of English Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of English Name values.
    */
   public final String[] getEnglishNameArray()
   {
      return _EnglishName;
   }
    
   /**
    * Gets the French Short Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the French Short Name or null.
    */
   public final String getFrenchShortName( int index )
   {
      return _FrenchShortName[index];
   }
    
   /**
    * Gets the French Short Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the French Short Name or the specified default value.
    */
   public final String getFrenchShortName( int index, String defaultValue )
   {
      return _FrenchShortName[index] == null ? defaultValue : _FrenchShortName[index];
   }
    
   /**
    * Gets the array of French Short Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of French Short Name values.
    */
   public final String[] getFrenchShortNameArray()
   {
      return _FrenchShortName;
   }
    
   /**
    * Gets the French Long Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the French Long Name or null.
    */
   public final String getFrenchLongName( int index )
   {
      return _FrenchLongName[index];
   }
    
   /**
    * Gets the French Long Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the French Long Name or the specified default value.
    */
   public final String getFrenchLongName( int index, String defaultValue )
   {
      return _FrenchLongName[index] == null ? defaultValue : _FrenchLongName[index];
   }
    
   /**
    * Gets the array of French Long Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of French Long Name values.
    */
   public final String[] getFrenchLongNameArray()
   {
      return _FrenchLongName;
   }
    
   /**
    * Gets the French Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the French Name or null.
    */
   public final String getFrenchName( int index )
   {
      return _FrenchName[index];
   }
    
   /**
    * Gets the French Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the French Name or the specified default value.
    */
   public final String getFrenchName( int index, String defaultValue )
   {
      return _FrenchName[index] == null ? defaultValue : _FrenchName[index];
   }
    
   /**
    * Gets the array of French Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of French Name values.
    */
   public final String[] getFrenchNameArray()
   {
      return _FrenchName;
   }
    
   /**
    * Gets the Foreign Rel Fund field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Foreign Rel Fund or null.
    */
   public final String getForeignRelfund( int index )
   {
      return _ForeignRelfund[index];
   }
    
   /**
    * Gets the Foreign Rel Fund field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Foreign Rel Fund or the specified default value.
    */
   public final String getForeignRelfund( int index, String defaultValue )
   {
      return _ForeignRelfund[index] == null ? defaultValue : _ForeignRelfund[index];
   }
    
   /**
    * Gets the array of Foreign Rel Fund fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Foreign Rel Fund values.
    */
   public final String[] getForeignRelfundArray()
   {
      return _ForeignRelfund;
   }
    
   /**
    * Gets the Foreign Rel Class field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Foreign Rel Class or null.
    */
   public final String getForeignRelClass( int index )
   {
      return _ForeignRelClass[index];
   }
    
   /**
    * Gets the Foreign Rel Class field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Foreign Rel Class or the specified default value.
    */
   public final String getForeignRelClass( int index, String defaultValue )
   {
      return _ForeignRelClass[index] == null ? defaultValue : _ForeignRelClass[index];
   }
    
   /**
    * Gets the array of Foreign Rel Class fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Foreign Rel Class values.
    */
   public final String[] getForeignRelClassArray()
   {
      return _ForeignRelClass;
   }
    
   /**
    * Gets the Rounding Fund field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Rounding Fund or null.
    */
   public final String getForeignRelFund( int index )
   {
      return _ForeignRelFund[index];
   }
    
   /**
    * Gets the Rounding Fund field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Rounding Fund or the specified default value.
    */
   public final String getForeignRelFund( int index, String defaultValue )
   {
      return _ForeignRelFund[index] == null ? defaultValue : _ForeignRelFund[index];
   }
    
   /**
    * Gets the array of Rounding Fund fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Rounding Fund values.
    */
   public final String[] getForeignRelFundArray()
   {
      return _ForeignRelFund;
   }
    
   /**
    * Gets the Rounding Class field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Rounding Class or null.
    */
   public final String getRoundingClass( int index )
   {
      return _RoundingClass[index];
   }
    
   /**
    * Gets the Rounding Class field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Rounding Class or the specified default value.
    */
   public final String getRoundingClass( int index, String defaultValue )
   {
      return _RoundingClass[index] == null ? defaultValue : _RoundingClass[index];
   }
    
   /**
    * Gets the array of Rounding Class fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Rounding Class values.
    */
   public final String[] getRoundingClassArray()
   {
      return _RoundingClass;
   }
    
   /**
    * Gets the GrandFathered Date AsofDate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the GrandFathered Date AsofDate or null.
    */
   public final Date getGrandFatheredDate( int index )
   {
      return _GrandFatheredDate[index];
   }
    
   /**
    * Gets the GrandFathered Date AsofDate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the GrandFathered Date AsofDate or the specified default value.
    */
   public final Date getGrandFatheredDate( int index, Date defaultValue )
   {
      return _GrandFatheredDate[index] == null ? defaultValue : _GrandFatheredDate[index];
   }
    
   /**
    * Gets the array of GrandFathered Date AsofDate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of GrandFathered Date AsofDate values.
    */
   public final Date[] getGrandFatheredDateArray()
   {
      return _GrandFatheredDate;
   }
    
   /**
    * Gets the Next Rebal Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Next Rebal Date or null.
    */
   public final Date getNextRebalDate( int index )
   {
      return _NextRebalDate[index];
   }
    
   /**
    * Gets the Next Rebal Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Next Rebal Date or the specified default value.
    */
   public final Date getNextRebalDate( int index, Date defaultValue )
   {
      return _NextRebalDate[index] == null ? defaultValue : _NextRebalDate[index];
   }
    
   /**
    * Gets the array of Next Rebal Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Next Rebal Date values.
    */
   public final Date[] getNextRebalDateArray()
   {
      return _NextRebalDate;
   }
    
   /**
    * Gets the Last Rebal Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Last Rebal Date or null.
    */
   public final Date getLastRebalDate( int index )
   {
      return _LastRebalDate[index];
   }
    
   /**
    * Gets the Last Rebal Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Last Rebal Date or the specified default value.
    */
   public final Date getLastRebalDate( int index, Date defaultValue )
   {
      return _LastRebalDate[index] == null ? defaultValue : _LastRebalDate[index];
   }
    
   /**
    * Gets the array of Last Rebal Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Last Rebal Date values.
    */
   public final Date[] getLastRebalDateArray()
   {
      return _LastRebalDate;
   }
    
   /**
    * Gets the Thres Hold Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Thres Hold Amount or null.
    */
   public final String getThresholdAmt( int index )
   {
      return _ThresholdAmt[index];
   }
    
   /**
    * Gets the Thres Hold Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Thres Hold Amount or the specified default value.
    */
   public final String getThresholdAmt( int index, String defaultValue )
   {
      return _ThresholdAmt[index] == null ? defaultValue : _ThresholdAmt[index];
   }
    
   /**
    * Gets the array of Thres Hold Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Thres Hold Amount values.
    */
   public final String[] getThresholdAmtArray()
   {
      return _ThresholdAmt;
   }
    
   /**
    * Gets the Wire Eligible field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Wire Eligible or null.
    */
   public final Boolean getWireElig( int index )
   {
      return _WireElig[index];
   }
    
   /**
    * Gets the Wire Eligible field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Wire Eligible or the specified default value.
    */
   public final boolean getWireElig( int index, boolean defaultValue )
   {
      return _WireElig[index] == null ? defaultValue : _WireElig[index].booleanValue();
   }
    
   /**
    * Gets the array of Wire Eligible fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Wire Eligible values.
    */
   public final Boolean[] getWireEligArray()
   {
      return _WireElig;
   }
    
   /**
    * Gets the Mod User field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Mod User or null.
    */
   public final String getModUser( int index )
   {
      return _ModUser[index];
   }
    
   /**
    * Gets the Mod User field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Mod User or the specified default value.
    */
   public final String getModUser( int index, String defaultValue )
   {
      return _ModUser[index] == null ? defaultValue : _ModUser[index];
   }
    
   /**
    * Gets the array of Mod User fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Mod User values.
    */
   public final String[] getModUserArray()
   {
      return _ModUser;
   }
    
   /**
    * Gets the Process Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Process Date or null.
    */
   public final Date getProcessDate( int index )
   {
      return _ProcessDate[index];
   }
    
   /**
    * Gets the Process Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Process Date or the specified default value.
    */
   public final Date getProcessDate( int index, Date defaultValue )
   {
      return _ProcessDate[index] == null ? defaultValue : _ProcessDate[index];
   }
    
   /**
    * Gets the array of Process Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Process Date values.
    */
   public final Date[] getProcessDateArray()
   {
      return _ProcessDate;
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
    * Gets the User Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the User Name or null.
    */
   public final String getUserName( int index )
   {
      return _UserName[index];
   }
    
   /**
    * Gets the User Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the User Name or the specified default value.
    */
   public final String getUserName( int index, String defaultValue )
   {
      return _UserName[index] == null ? defaultValue : _UserName[index];
   }
    
   /**
    * Gets the array of User Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of User Name values.
    */
   public final String[] getUserNameArray()
   {
      return _UserName;
   }
    
   /**
    * Gets the Day of the Week field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Day of the Week or null.
    */
   public final Integer getDayofWeek( int index )
   {
      return _DayofWeek[index];
   }
    
   /**
    * Gets the Day of the Week field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Day of the Week or the specified default value.
    */
   public final int getDayofWeek( int index, int defaultValue )
   {
      return _DayofWeek[index] == null ? defaultValue : _DayofWeek[index].intValue();
   }
    
   /**
    * Gets the array of Day of the Week fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Day of the Week values.
    */
   public final Integer[] getDayofWeekArray()
   {
      return _DayofWeek;
   }
    
   /**
    * Gets the AMSRecId field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AMSRecId or null.
    */
   public final Integer getAMSRecId( int index )
   {
      return _AMSRecId[index];
   }
    
   /**
    * Gets the AMSRecId field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AMSRecId or the specified default value.
    */
   public final int getAMSRecId( int index, int defaultValue )
   {
      return _AMSRecId[index] == null ? defaultValue : _AMSRecId[index].intValue();
   }
    
   /**
    * Gets the array of AMSRecId fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AMSRecId values.
    */
   public final Integer[] getAMSRecIdArray()
   {
      return _AMSRecId;
   }
    
   /**
    * Gets the Verify  Precreate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Verify  Precreate or null.
    */
   public final Boolean getVerifyPrecreate( int index )
   {
      return _VerifyPrecreate[index];
   }
    
   /**
    * Gets the Verify  Precreate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Verify  Precreate or the specified default value.
    */
   public final boolean getVerifyPrecreate( int index, boolean defaultValue )
   {
      return _VerifyPrecreate[index] == null ? defaultValue : _VerifyPrecreate[index].booleanValue();
   }
    
   /**
    * Gets the array of Verify  Precreate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Verify  Precreate values.
    */
   public final Boolean[] getVerifyPrecreateArray()
   {
      return _VerifyPrecreate;
   }
    
   /**
    * Gets the Last Deff Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Last Deff Date or null.
    */
   public final Date getLastDeffDate( int index )
   {
      return _LastDeffDate[index];
   }
    
   /**
    * Gets the Last Deff Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Last Deff Date or the specified default value.
    */
   public final Date getLastDeffDate( int index, Date defaultValue )
   {
      return _LastDeffDate[index] == null ? defaultValue : _LastDeffDate[index];
   }
    
   /**
    * Gets the array of Last Deff Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Last Deff Date values.
    */
   public final Date[] getLastDeffDateArray()
   {
      return _LastDeffDate;
   }
    
   /**
    * Gets the GrandFatherStamped field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the GrandFatherStamped or null.
    */
   public final Boolean getGrandFatherStamped( int index )
   {
      return _GrandFatherStamped[index];
   }
    
   /**
    * Gets the GrandFatherStamped field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the GrandFatherStamped or the specified default value.
    */
   public final boolean getGrandFatherStamped( int index, boolean defaultValue )
   {
      return _GrandFatherStamped[index] == null ? defaultValue : _GrandFatherStamped[index].booleanValue();
   }
    
   /**
    * Gets the array of GrandFatherStamped fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of GrandFatherStamped values.
    */
   public final Boolean[] getGrandFatherStampedArray()
   {
      return _GrandFatherStamped;
   }
    
   /**
    * Gets the Associated Fund field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Associated Fund or null.
    */
   public final String getAssocFund( int index )
   {
      return _AssocFund[index];
   }
    
   /**
    * Gets the Associated Fund field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Associated Fund or the specified default value.
    */
   public final String getAssocFund( int index, String defaultValue )
   {
      return _AssocFund[index] == null ? defaultValue : _AssocFund[index];
   }
    
   /**
    * Gets the array of Associated Fund fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Associated Fund values.
    */
   public final String[] getAssocFundArray()
   {
      return _AssocFund;
   }
    
   /**
    * Gets the Associated Class field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Associated Class or null.
    */
   public final String getAssocClass( int index )
   {
      return _AssocClass[index];
   }
    
   /**
    * Gets the Associated Class field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Associated Class or the specified default value.
    */
   public final String getAssocClass( int index, String defaultValue )
   {
      return _AssocClass[index] == null ? defaultValue : _AssocClass[index];
   }
    
   /**
    * Gets the array of Associated Class fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Associated Class values.
    */
   public final String[] getAssocClassArray()
   {
      return _AssocClass;
   }
    
   /**
    * Gets the SchedSetupFreqID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the SchedSetupFreqID or null.
    */
   public final Integer getSchedSetupFreqID( int index )
   {
      return _SchedSetupFreqID[index];
   }
    
   /**
    * Gets the SchedSetupFreqID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SchedSetupFreqID or the specified default value.
    */
   public final int getSchedSetupFreqID( int index, int defaultValue )
   {
      return _SchedSetupFreqID[index] == null ? defaultValue : _SchedSetupFreqID[index].intValue();
   }
    
   /**
    * Gets the array of SchedSetupFreqID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of SchedSetupFreqID values.
    */
   public final Integer[] getSchedSetupFreqIDArray()
   {
      return _SchedSetupFreqID;
   }
    
   /**
    * Gets the Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Amount or null.
    */
   public final String getAmount( int index )
   {
      return _Amount[index];
   }
    
   /**
    * Gets the Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Amount or the specified default value.
    */
   public final String getAmount( int index, String defaultValue )
   {
      return _Amount[index] == null ? defaultValue : _Amount[index];
   }
    
   /**
    * Gets the array of Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Amount values.
    */
   public final String[] getAmountArray()
   {
      return _Amount;
   }
    
   /**
    * Gets the Flag to indicate if traded via parent fund class field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag to indicate if traded via parent fund class or null.
    */
   public final String getParentFndClsTrdg( int index )
   {
      return _ParentFndClsTrdg[index];
   }
    
   /**
    * Gets the Flag to indicate if traded via parent fund class field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag to indicate if traded via parent fund class or the specified default value.
    */
   public final String getParentFndClsTrdg( int index, String defaultValue )
   {
      return _ParentFndClsTrdg[index] == null ? defaultValue : _ParentFndClsTrdg[index];
   }
    
   /**
    * Gets the array of Flag to indicate if traded via parent fund class fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag to indicate if traded via parent fund class values.
    */
   public final String[] getParentFndClsTrdgArray()
   {
      return _ParentFndClsTrdg;
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
      
      _rxAMSCode = resizeArray( _rxAMSCode, _RepeatCount );
      _RBLPrcnt = resizeArray( _RBLPrcnt, _RepeatCount );
      _Currency = resizeArray( _Currency, _RepeatCount );
      _EffectiveDate = resizeArray( _EffectiveDate, _RepeatCount );
      _AMSCodeVer = resizeArray( _AMSCodeVer, _RepeatCount );
      _CodeInUse = resizeArray( _CodeInUse, _RepeatCount );
      _AMSDesc = resizeArray( _AMSDesc, _RepeatCount );
      _rxAMSType = resizeArray( _rxAMSType, _RepeatCount );
      _DefaultAlloc = resizeArray( _DefaultAlloc, _RepeatCount );
      _FundAlloc = resizeArray( _FundAlloc, _RepeatCount );
      _EnglishShortName = resizeArray( _EnglishShortName, _RepeatCount );
      _EnglishLongName = resizeArray( _EnglishLongName, _RepeatCount );
      _EnglishName = resizeArray( _EnglishName, _RepeatCount );
      _FrenchShortName = resizeArray( _FrenchShortName, _RepeatCount );
      _FrenchLongName = resizeArray( _FrenchLongName, _RepeatCount );
      _FrenchName = resizeArray( _FrenchName, _RepeatCount );
      _ForeignRelfund = resizeArray( _ForeignRelfund, _RepeatCount );
      _ForeignRelClass = resizeArray( _ForeignRelClass, _RepeatCount );
      _ForeignRelFund = resizeArray( _ForeignRelFund, _RepeatCount );
      _RoundingClass = resizeArray( _RoundingClass, _RepeatCount );
      _GrandFatheredDate = resizeArray( _GrandFatheredDate, _RepeatCount );
      _NextRebalDate = resizeArray( _NextRebalDate, _RepeatCount );
      _LastRebalDate = resizeArray( _LastRebalDate, _RepeatCount );
      _ThresholdAmt = resizeArray( _ThresholdAmt, _RepeatCount );
      _WireElig = resizeArray( _WireElig, _RepeatCount );
      _ModUser = resizeArray( _ModUser, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _UserName = resizeArray( _UserName, _RepeatCount );
      _DayofWeek = resizeArray( _DayofWeek, _RepeatCount );
      _AMSRecId = resizeArray( _AMSRecId, _RepeatCount );
      _VerifyPrecreate = resizeArray( _VerifyPrecreate, _RepeatCount );
      _LastDeffDate = resizeArray( _LastDeffDate, _RepeatCount );
      _GrandFatherStamped = resizeArray( _GrandFatherStamped, _RepeatCount );
      _AssocFund = resizeArray( _AssocFund, _RepeatCount );
      _AssocClass = resizeArray( _AssocClass, _RepeatCount );
      _SchedSetupFreqID = resizeArray( _SchedSetupFreqID, _RepeatCount );
      _Amount = resizeArray( _Amount, _RepeatCount );
      _ParentFndClsTrdg = resizeArray( _ParentFndClsTrdg, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxAMSCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RBLPrcnt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Currency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EffectiveDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _AMSCodeVer[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _CodeInUse[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _AMSDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxAMSType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DefaultAlloc[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _FundAlloc[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _EnglishShortName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EnglishLongName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EnglishName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FrenchShortName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FrenchLongName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FrenchName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ForeignRelfund[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ForeignRelClass[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ForeignRelFund[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RoundingClass[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GrandFatheredDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _NextRebalDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _LastRebalDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ThresholdAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _WireElig[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ModUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _UserName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DayofWeek[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _AMSRecId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _VerifyPrecreate[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _LastDeffDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _GrandFatherStamped[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _AssocFund[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AssocClass[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SchedSetupFreqID[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _Amount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ParentFndClsTrdg[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
