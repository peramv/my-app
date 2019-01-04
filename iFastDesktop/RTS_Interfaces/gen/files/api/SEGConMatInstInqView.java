
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * SEG Contract Maturity Instruction Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/SEGConMatInstInq.doc">SEGConMatInstInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class SEGConMatInstInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Instruction ID member array.
    */
   private String[] _InstId = null;
   
   /**
    * Account ID member array.
    */
   private String[] _AcctID = null;
   
   /**
    * Policy Year member array.
    */
   private Integer[] _PolicyYear = null;
   
   /**
    * Policy Term member array.
    */
   private Integer[] _PolicyTerm = null;
   
   /**
    * Maturity Date member array.
    */
   private Date[] _MaturityDate = null;
   
   /**
    * Redemption Code member array.
    */
   private String[] _RedCode = null;
   
   /**
    * Redemption Code Description member array.
    */
   private String[] _RedCodeDesc = null;
   
   /**
    * Address Code member array.
    */
   private String[] _Adcd = null;
   
   /**
    * Instruction Percentage member array.
    */
   private String[] _Amount = null;
   
   /**
    * Percentage/Dollar member array.
    */
   private String[] _PUD = null;
   
   /**
    * Source Of Fund member array.
    */
   private String[] _SourceOfFund = null;
   
   /**
    * Payment Type member array.
    */
   private String[] _PayType = null;
   
   /**
    * Modification Date member array.
    */
   private Date[] _ModDate = null;
   
   /**
    * User Name member array.
    */
   private String[] _Username = null;
   
   /**
    * User that modified record member array.
    */
   private String[] _Username2 = null;
   
   /**
    * SEGMATINSTDETAILUUID member array.
    */
   private String[] _SEGMATINSTDETAILUUID = null;
   
   /**
    * Institution Name member array.
    */
   private String[] _InstName = null;
   
   /**
    * Swfit Code member array.
    */
   private Integer[] _SwiftCode = null;
   
   /**
    * Reference Number member array.
    */
   private Integer[] _RefNumber = null;
   
   /**
    * Transit Number member array.
    */
   private Integer[] _TransitNo = null;
   
   /**
    * Bank ID Number member array.
    */
   private Integer[] _BankIDNum = null;
   
   /**
    * Bank ID member array.
    */
   private String[] _BankID = null;
   
   /**
    * Bank Account Number member array.
    */
   private String[] _BankAcctNum = null;
   
   /**
    * Bank Account Name member array.
    */
   private String[] _BankAcctName = null;
   
   /**
    * Bank Account Type member array.
    */
   private String[] _BankAcctType = null;
   
   /**
    * Bank Account Type Desc member array.
    */
   private String[] _BankAcctTypeDesc = null;
   
   /**
    * Bank Account Currency member array.
    */
   private String[] _BankAcctCurr = null;
   
   /**
    * Bank Account Currency Description member array.
    */
   private String[] _BankAcctCurrDesc = null;
   
   /**
    * Bank Address 1 member array.
    */
   private String[] _BankAddr1 = null;
   
   /**
    * Bank Address 2 member array.
    */
   private String[] _BankAddr2 = null;
   
   /**
    * Bank Address 3 member array.
    */
   private String[] _BankAddr3 = null;
   
   /**
    * Bank Address 4 member array.
    */
   private String[] _BankAddr4 = null;
   
   /**
    * Bank Address 5 member array.
    */
   private String[] _BankAddr5 = null;
   
   /**
    * Bank Contract member array.
    */
   private String[] _BankContact = null;
   
   /**
    * Bank Country member array.
    */
   private String[] _BankCntry = null;
   
   /**
    * Bank Postal Code member array.
    */
   private String[] _BankPstl = null;
   
   /**
    * Bank Type member array.
    */
   private String[] _BankType = null;
   
   /**
    * Pay Reason 1 member array.
    */
   private String[] _PayReason1 = null;
   
   /**
    * Pay Reason 2 member array.
    */
   private String[] _PayReason2 = null;
   
   /**
    * ACH Processor member array.
    */
   private String[] _ACHProcessor = null;
   
   /**
    * Correspondent Bank Type member array.
    */
   private String[] _CorrespBankType = null;
   
   /**
    * Correspondent Bank ID Num member array.
    */
   private String[] _CorrespBankIDNum = null;
   
   /**
    * Credit Info Line 1 member array.
    */
   private String[] _CreditInfoLine1 = null;
   
   /**
    * Credit Info Line 2 member array.
    */
   private String[] _CreditInfoLine2 = null;
   
   /**
    * Correspondent Bank ID member array.
    */
   private String[] _CorrespBankId = null;
   
   /**
    * Correspondent Transit Number member array.
    */
   private Integer[] _CorrespTransitNo = null;
   
   /**
    * Correspondent Institution Name member array.
    */
   private String[] _CorrespInstName = null;
   
   /**
    * Correspondent Bank Contract member array.
    */
   private String[] _CorrespBankContact = null;
   
   /**
    * Corresponded Bank Country member array.
    */
   private String[] _CorrespBankCntry = null;
   
   /**
    * Corresponded Bank Postal Code member array.
    */
   private String[] _CorrespBankPstl = null;
   
   /**
    * Correspondent  Bank Address 1 member array.
    */
   private String[] _CorrespBankAddr1 = null;
   
   /**
    * Correspondent  Bank Address 2 member array.
    */
   private String[] _CorrespBankAddr2 = null;
   
   /**
    * Correspondent  Bank Address 3 member array.
    */
   private String[] _CorrespBankAddr3 = null;
   
   /**
    * Correspondent  Bank Address 4 member array.
    */
   private String[] _CorrespBankAddr4 = null;
   
   /**
    * Correspondent  Bank Address 5 member array.
    */
   private String[] _CorrespBankAddr5 = null;
   
   /**
    * Bank Account Effective Date member array.
    */
   private Date[] _EffectiveDate = null;
   
   /**
    * Bank Account Stop Date member array.
    */
   private Date[] _StopDate = null;
   
   /**
    * Bank Account record version number member array.
    */
   private Integer[] _BankAcctVer = null;
   
   /**
    * Account Use Code member array.
    */
   private String[] _AcctUseCode = null;
   

   /**
    * Constructs the SEGConMatInstInqView object.
    * 
    */
   public SEGConMatInstInqView()
   {
      super ( new SEGConMatInstInqRequest() );
   }

   /**
    * Constructs the SEGConMatInstInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public SEGConMatInstInqView( String hostEncoding )
   {
      super ( new SEGConMatInstInqRequest( hostEncoding ) );
   }

   /**
    * Gets the SEGConMatInstInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The SEGConMatInstInqRequest object.
    */
   public final SEGConMatInstInqRequest getRequest()
   {
      return (SEGConMatInstInqRequest)getIFastRequest();
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
    * Gets the Instruction ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Instruction ID or null.
    */
   public final String getInstId( int index )
   {
      return _InstId[index];
   }
    
   /**
    * Gets the Instruction ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Instruction ID or the specified default value.
    */
   public final String getInstId( int index, String defaultValue )
   {
      return _InstId[index] == null ? defaultValue : _InstId[index];
   }
    
   /**
    * Gets the array of Instruction ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Instruction ID values.
    */
   public final String[] getInstIdArray()
   {
      return _InstId;
   }
    
   /**
    * Gets the Account ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account ID or null.
    */
   public final String getAcctID( int index )
   {
      return _AcctID[index];
   }
    
   /**
    * Gets the Account ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account ID or the specified default value.
    */
   public final String getAcctID( int index, String defaultValue )
   {
      return _AcctID[index] == null ? defaultValue : _AcctID[index];
   }
    
   /**
    * Gets the array of Account ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account ID values.
    */
   public final String[] getAcctIDArray()
   {
      return _AcctID;
   }
    
   /**
    * Gets the Policy Year field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Policy Year or null.
    */
   public final Integer getPolicyYear( int index )
   {
      return _PolicyYear[index];
   }
    
   /**
    * Gets the Policy Year field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Policy Year or the specified default value.
    */
   public final int getPolicyYear( int index, int defaultValue )
   {
      return _PolicyYear[index] == null ? defaultValue : _PolicyYear[index].intValue();
   }
    
   /**
    * Gets the array of Policy Year fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Policy Year values.
    */
   public final Integer[] getPolicyYearArray()
   {
      return _PolicyYear;
   }
    
   /**
    * Gets the Policy Term field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Policy Term or null.
    */
   public final Integer getPolicyTerm( int index )
   {
      return _PolicyTerm[index];
   }
    
   /**
    * Gets the Policy Term field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Policy Term or the specified default value.
    */
   public final int getPolicyTerm( int index, int defaultValue )
   {
      return _PolicyTerm[index] == null ? defaultValue : _PolicyTerm[index].intValue();
   }
    
   /**
    * Gets the array of Policy Term fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Policy Term values.
    */
   public final Integer[] getPolicyTermArray()
   {
      return _PolicyTerm;
   }
    
   /**
    * Gets the Maturity Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Maturity Date or null.
    */
   public final Date getMaturityDate( int index )
   {
      return _MaturityDate[index];
   }
    
   /**
    * Gets the Maturity Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Maturity Date or the specified default value.
    */
   public final Date getMaturityDate( int index, Date defaultValue )
   {
      return _MaturityDate[index] == null ? defaultValue : _MaturityDate[index];
   }
    
   /**
    * Gets the array of Maturity Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Maturity Date values.
    */
   public final Date[] getMaturityDateArray()
   {
      return _MaturityDate;
   }
    
   /**
    * Gets the Redemption Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Redemption Code or null.
    */
   public final String getRedCode( int index )
   {
      return _RedCode[index];
   }
    
   /**
    * Gets the Redemption Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Redemption Code or the specified default value.
    */
   public final String getRedCode( int index, String defaultValue )
   {
      return _RedCode[index] == null ? defaultValue : _RedCode[index];
   }
    
   /**
    * Gets the array of Redemption Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Redemption Code values.
    */
   public final String[] getRedCodeArray()
   {
      return _RedCode;
   }
    
   /**
    * Gets the Redemption Code Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Redemption Code Description or null.
    */
   public final String getRedCodeDesc( int index )
   {
      return _RedCodeDesc[index];
   }
    
   /**
    * Gets the Redemption Code Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Redemption Code Description or the specified default value.
    */
   public final String getRedCodeDesc( int index, String defaultValue )
   {
      return _RedCodeDesc[index] == null ? defaultValue : _RedCodeDesc[index];
   }
    
   /**
    * Gets the array of Redemption Code Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Redemption Code Description values.
    */
   public final String[] getRedCodeDescArray()
   {
      return _RedCodeDesc;
   }
    
   /**
    * Gets the Address Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Code or null.
    */
   public final String getAdcd( int index )
   {
      return _Adcd[index];
   }
    
   /**
    * Gets the Address Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Code or the specified default value.
    */
   public final String getAdcd( int index, String defaultValue )
   {
      return _Adcd[index] == null ? defaultValue : _Adcd[index];
   }
    
   /**
    * Gets the array of Address Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Code values.
    */
   public final String[] getAdcdArray()
   {
      return _Adcd;
   }
    
   /**
    * Gets the Instruction Percentage field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Instruction Percentage or null.
    */
   public final String getAmount( int index )
   {
      return _Amount[index];
   }
    
   /**
    * Gets the Instruction Percentage field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Instruction Percentage or the specified default value.
    */
   public final String getAmount( int index, String defaultValue )
   {
      return _Amount[index] == null ? defaultValue : _Amount[index];
   }
    
   /**
    * Gets the array of Instruction Percentage fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Instruction Percentage values.
    */
   public final String[] getAmountArray()
   {
      return _Amount;
   }
    
   /**
    * Gets the Percentage/Dollar field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Percentage/Dollar or null.
    */
   public final String getPUD( int index )
   {
      return _PUD[index];
   }
    
   /**
    * Gets the Percentage/Dollar field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Percentage/Dollar or the specified default value.
    */
   public final String getPUD( int index, String defaultValue )
   {
      return _PUD[index] == null ? defaultValue : _PUD[index];
   }
    
   /**
    * Gets the array of Percentage/Dollar fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Percentage/Dollar values.
    */
   public final String[] getPUDArray()
   {
      return _PUD;
   }
    
   /**
    * Gets the Source Of Fund field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Source Of Fund or null.
    */
   public final String getSourceOfFund( int index )
   {
      return _SourceOfFund[index];
   }
    
   /**
    * Gets the Source Of Fund field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Source Of Fund or the specified default value.
    */
   public final String getSourceOfFund( int index, String defaultValue )
   {
      return _SourceOfFund[index] == null ? defaultValue : _SourceOfFund[index];
   }
    
   /**
    * Gets the array of Source Of Fund fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Source Of Fund values.
    */
   public final String[] getSourceOfFundArray()
   {
      return _SourceOfFund;
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
    * Gets the Modification Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Modification Date or null.
    */
   public final Date getModDate( int index )
   {
      return _ModDate[index];
   }
    
   /**
    * Gets the Modification Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Modification Date or the specified default value.
    */
   public final Date getModDate( int index, Date defaultValue )
   {
      return _ModDate[index] == null ? defaultValue : _ModDate[index];
   }
    
   /**
    * Gets the array of Modification Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Modification Date values.
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
    * Gets the User that modified record field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the User that modified record or null.
    */
   public final String getUsername2( int index )
   {
      return _Username2[index];
   }
    
   /**
    * Gets the User that modified record field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the User that modified record or the specified default value.
    */
   public final String getUsername2( int index, String defaultValue )
   {
      return _Username2[index] == null ? defaultValue : _Username2[index];
   }
    
   /**
    * Gets the array of User that modified record fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of User that modified record values.
    */
   public final String[] getUsername2Array()
   {
      return _Username2;
   }
    
   /**
    * Gets the SEGMATINSTDETAILUUID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the SEGMATINSTDETAILUUID or null.
    */
   public final String getSEGMATINSTDETAILUUID( int index )
   {
      return _SEGMATINSTDETAILUUID[index];
   }
    
   /**
    * Gets the SEGMATINSTDETAILUUID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SEGMATINSTDETAILUUID or the specified default value.
    */
   public final String getSEGMATINSTDETAILUUID( int index, String defaultValue )
   {
      return _SEGMATINSTDETAILUUID[index] == null ? defaultValue : _SEGMATINSTDETAILUUID[index];
   }
    
   /**
    * Gets the array of SEGMATINSTDETAILUUID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of SEGMATINSTDETAILUUID values.
    */
   public final String[] getSEGMATINSTDETAILUUIDArray()
   {
      return _SEGMATINSTDETAILUUID;
   }
    
   /**
    * Gets the Institution Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Institution Name or null.
    */
   public final String getInstName( int index )
   {
      return _InstName[index];
   }
    
   /**
    * Gets the Institution Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Institution Name or the specified default value.
    */
   public final String getInstName( int index, String defaultValue )
   {
      return _InstName[index] == null ? defaultValue : _InstName[index];
   }
    
   /**
    * Gets the array of Institution Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Institution Name values.
    */
   public final String[] getInstNameArray()
   {
      return _InstName;
   }
    
   /**
    * Gets the Swfit Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Swfit Code or null.
    */
   public final Integer getSwiftCode( int index )
   {
      return _SwiftCode[index];
   }
    
   /**
    * Gets the Swfit Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Swfit Code or the specified default value.
    */
   public final int getSwiftCode( int index, int defaultValue )
   {
      return _SwiftCode[index] == null ? defaultValue : _SwiftCode[index].intValue();
   }
    
   /**
    * Gets the array of Swfit Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Swfit Code values.
    */
   public final Integer[] getSwiftCodeArray()
   {
      return _SwiftCode;
   }
    
   /**
    * Gets the Reference Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reference Number or null.
    */
   public final Integer getRefNumber( int index )
   {
      return _RefNumber[index];
   }
    
   /**
    * Gets the Reference Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reference Number or the specified default value.
    */
   public final int getRefNumber( int index, int defaultValue )
   {
      return _RefNumber[index] == null ? defaultValue : _RefNumber[index].intValue();
   }
    
   /**
    * Gets the array of Reference Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reference Number values.
    */
   public final Integer[] getRefNumberArray()
   {
      return _RefNumber;
   }
    
   /**
    * Gets the Transit Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transit Number or null.
    */
   public final Integer getTransitNo( int index )
   {
      return _TransitNo[index];
   }
    
   /**
    * Gets the Transit Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transit Number or the specified default value.
    */
   public final int getTransitNo( int index, int defaultValue )
   {
      return _TransitNo[index] == null ? defaultValue : _TransitNo[index].intValue();
   }
    
   /**
    * Gets the array of Transit Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transit Number values.
    */
   public final Integer[] getTransitNoArray()
   {
      return _TransitNo;
   }
    
   /**
    * Gets the Bank ID Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank ID Number or null.
    */
   public final Integer getBankIDNum( int index )
   {
      return _BankIDNum[index];
   }
    
   /**
    * Gets the Bank ID Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank ID Number or the specified default value.
    */
   public final int getBankIDNum( int index, int defaultValue )
   {
      return _BankIDNum[index] == null ? defaultValue : _BankIDNum[index].intValue();
   }
    
   /**
    * Gets the array of Bank ID Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank ID Number values.
    */
   public final Integer[] getBankIDNumArray()
   {
      return _BankIDNum;
   }
    
   /**
    * Gets the Bank ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank ID or null.
    */
   public final String getBankID( int index )
   {
      return _BankID[index];
   }
    
   /**
    * Gets the Bank ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank ID or the specified default value.
    */
   public final String getBankID( int index, String defaultValue )
   {
      return _BankID[index] == null ? defaultValue : _BankID[index];
   }
    
   /**
    * Gets the array of Bank ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank ID values.
    */
   public final String[] getBankIDArray()
   {
      return _BankID;
   }
    
   /**
    * Gets the Bank Account Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Account Number or null.
    */
   public final String getBankAcctNum( int index )
   {
      return _BankAcctNum[index];
   }
    
   /**
    * Gets the Bank Account Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Account Number or the specified default value.
    */
   public final String getBankAcctNum( int index, String defaultValue )
   {
      return _BankAcctNum[index] == null ? defaultValue : _BankAcctNum[index];
   }
    
   /**
    * Gets the array of Bank Account Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Account Number values.
    */
   public final String[] getBankAcctNumArray()
   {
      return _BankAcctNum;
   }
    
   /**
    * Gets the Bank Account Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Account Name or null.
    */
   public final String getBankAcctName( int index )
   {
      return _BankAcctName[index];
   }
    
   /**
    * Gets the Bank Account Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Account Name or the specified default value.
    */
   public final String getBankAcctName( int index, String defaultValue )
   {
      return _BankAcctName[index] == null ? defaultValue : _BankAcctName[index];
   }
    
   /**
    * Gets the array of Bank Account Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Account Name values.
    */
   public final String[] getBankAcctNameArray()
   {
      return _BankAcctName;
   }
    
   /**
    * Gets the Bank Account Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Account Type or null.
    */
   public final String getBankAcctType( int index )
   {
      return _BankAcctType[index];
   }
    
   /**
    * Gets the Bank Account Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Account Type or the specified default value.
    */
   public final String getBankAcctType( int index, String defaultValue )
   {
      return _BankAcctType[index] == null ? defaultValue : _BankAcctType[index];
   }
    
   /**
    * Gets the array of Bank Account Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Account Type values.
    */
   public final String[] getBankAcctTypeArray()
   {
      return _BankAcctType;
   }
    
   /**
    * Gets the Bank Account Type Desc field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Account Type Desc or null.
    */
   public final String getBankAcctTypeDesc( int index )
   {
      return _BankAcctTypeDesc[index];
   }
    
   /**
    * Gets the Bank Account Type Desc field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Account Type Desc or the specified default value.
    */
   public final String getBankAcctTypeDesc( int index, String defaultValue )
   {
      return _BankAcctTypeDesc[index] == null ? defaultValue : _BankAcctTypeDesc[index];
   }
    
   /**
    * Gets the array of Bank Account Type Desc fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Account Type Desc values.
    */
   public final String[] getBankAcctTypeDescArray()
   {
      return _BankAcctTypeDesc;
   }
    
   /**
    * Gets the Bank Account Currency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Account Currency or null.
    */
   public final String getBankAcctCurr( int index )
   {
      return _BankAcctCurr[index];
   }
    
   /**
    * Gets the Bank Account Currency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Account Currency or the specified default value.
    */
   public final String getBankAcctCurr( int index, String defaultValue )
   {
      return _BankAcctCurr[index] == null ? defaultValue : _BankAcctCurr[index];
   }
    
   /**
    * Gets the array of Bank Account Currency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Account Currency values.
    */
   public final String[] getBankAcctCurrArray()
   {
      return _BankAcctCurr;
   }
    
   /**
    * Gets the Bank Account Currency Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Account Currency Description or null.
    */
   public final String getBankAcctCurrDesc( int index )
   {
      return _BankAcctCurrDesc[index];
   }
    
   /**
    * Gets the Bank Account Currency Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Account Currency Description or the specified default value.
    */
   public final String getBankAcctCurrDesc( int index, String defaultValue )
   {
      return _BankAcctCurrDesc[index] == null ? defaultValue : _BankAcctCurrDesc[index];
   }
    
   /**
    * Gets the array of Bank Account Currency Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Account Currency Description values.
    */
   public final String[] getBankAcctCurrDescArray()
   {
      return _BankAcctCurrDesc;
   }
    
   /**
    * Gets the Bank Address 1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Address 1 or null.
    */
   public final String getBankAddr1( int index )
   {
      return _BankAddr1[index];
   }
    
   /**
    * Gets the Bank Address 1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Address 1 or the specified default value.
    */
   public final String getBankAddr1( int index, String defaultValue )
   {
      return _BankAddr1[index] == null ? defaultValue : _BankAddr1[index];
   }
    
   /**
    * Gets the array of Bank Address 1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Address 1 values.
    */
   public final String[] getBankAddr1Array()
   {
      return _BankAddr1;
   }
    
   /**
    * Gets the Bank Address 2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Address 2 or null.
    */
   public final String getBankAddr2( int index )
   {
      return _BankAddr2[index];
   }
    
   /**
    * Gets the Bank Address 2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Address 2 or the specified default value.
    */
   public final String getBankAddr2( int index, String defaultValue )
   {
      return _BankAddr2[index] == null ? defaultValue : _BankAddr2[index];
   }
    
   /**
    * Gets the array of Bank Address 2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Address 2 values.
    */
   public final String[] getBankAddr2Array()
   {
      return _BankAddr2;
   }
    
   /**
    * Gets the Bank Address 3 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Address 3 or null.
    */
   public final String getBankAddr3( int index )
   {
      return _BankAddr3[index];
   }
    
   /**
    * Gets the Bank Address 3 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Address 3 or the specified default value.
    */
   public final String getBankAddr3( int index, String defaultValue )
   {
      return _BankAddr3[index] == null ? defaultValue : _BankAddr3[index];
   }
    
   /**
    * Gets the array of Bank Address 3 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Address 3 values.
    */
   public final String[] getBankAddr3Array()
   {
      return _BankAddr3;
   }
    
   /**
    * Gets the Bank Address 4 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Address 4 or null.
    */
   public final String getBankAddr4( int index )
   {
      return _BankAddr4[index];
   }
    
   /**
    * Gets the Bank Address 4 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Address 4 or the specified default value.
    */
   public final String getBankAddr4( int index, String defaultValue )
   {
      return _BankAddr4[index] == null ? defaultValue : _BankAddr4[index];
   }
    
   /**
    * Gets the array of Bank Address 4 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Address 4 values.
    */
   public final String[] getBankAddr4Array()
   {
      return _BankAddr4;
   }
    
   /**
    * Gets the Bank Address 5 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Address 5 or null.
    */
   public final String getBankAddr5( int index )
   {
      return _BankAddr5[index];
   }
    
   /**
    * Gets the Bank Address 5 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Address 5 or the specified default value.
    */
   public final String getBankAddr5( int index, String defaultValue )
   {
      return _BankAddr5[index] == null ? defaultValue : _BankAddr5[index];
   }
    
   /**
    * Gets the array of Bank Address 5 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Address 5 values.
    */
   public final String[] getBankAddr5Array()
   {
      return _BankAddr5;
   }
    
   /**
    * Gets the Bank Contract field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Contract or null.
    */
   public final String getBankContact( int index )
   {
      return _BankContact[index];
   }
    
   /**
    * Gets the Bank Contract field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Contract or the specified default value.
    */
   public final String getBankContact( int index, String defaultValue )
   {
      return _BankContact[index] == null ? defaultValue : _BankContact[index];
   }
    
   /**
    * Gets the array of Bank Contract fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Contract values.
    */
   public final String[] getBankContactArray()
   {
      return _BankContact;
   }
    
   /**
    * Gets the Bank Country field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Country or null.
    */
   public final String getBankCntry( int index )
   {
      return _BankCntry[index];
   }
    
   /**
    * Gets the Bank Country field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Country or the specified default value.
    */
   public final String getBankCntry( int index, String defaultValue )
   {
      return _BankCntry[index] == null ? defaultValue : _BankCntry[index];
   }
    
   /**
    * Gets the array of Bank Country fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Country values.
    */
   public final String[] getBankCntryArray()
   {
      return _BankCntry;
   }
    
   /**
    * Gets the Bank Postal Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Postal Code or null.
    */
   public final String getBankPstl( int index )
   {
      return _BankPstl[index];
   }
    
   /**
    * Gets the Bank Postal Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Postal Code or the specified default value.
    */
   public final String getBankPstl( int index, String defaultValue )
   {
      return _BankPstl[index] == null ? defaultValue : _BankPstl[index];
   }
    
   /**
    * Gets the array of Bank Postal Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Postal Code values.
    */
   public final String[] getBankPstlArray()
   {
      return _BankPstl;
   }
    
   /**
    * Gets the Bank Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Type or null.
    */
   public final String getBankType( int index )
   {
      return _BankType[index];
   }
    
   /**
    * Gets the Bank Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Type or the specified default value.
    */
   public final String getBankType( int index, String defaultValue )
   {
      return _BankType[index] == null ? defaultValue : _BankType[index];
   }
    
   /**
    * Gets the array of Bank Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Type values.
    */
   public final String[] getBankTypeArray()
   {
      return _BankType;
   }
    
   /**
    * Gets the Pay Reason 1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Pay Reason 1 or null.
    */
   public final String getPayReason1( int index )
   {
      return _PayReason1[index];
   }
    
   /**
    * Gets the Pay Reason 1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Pay Reason 1 or the specified default value.
    */
   public final String getPayReason1( int index, String defaultValue )
   {
      return _PayReason1[index] == null ? defaultValue : _PayReason1[index];
   }
    
   /**
    * Gets the array of Pay Reason 1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Pay Reason 1 values.
    */
   public final String[] getPayReason1Array()
   {
      return _PayReason1;
   }
    
   /**
    * Gets the Pay Reason 2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Pay Reason 2 or null.
    */
   public final String getPayReason2( int index )
   {
      return _PayReason2[index];
   }
    
   /**
    * Gets the Pay Reason 2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Pay Reason 2 or the specified default value.
    */
   public final String getPayReason2( int index, String defaultValue )
   {
      return _PayReason2[index] == null ? defaultValue : _PayReason2[index];
   }
    
   /**
    * Gets the array of Pay Reason 2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Pay Reason 2 values.
    */
   public final String[] getPayReason2Array()
   {
      return _PayReason2;
   }
    
   /**
    * Gets the ACH Processor field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ACH Processor or null.
    */
   public final String getACHProcessor( int index )
   {
      return _ACHProcessor[index];
   }
    
   /**
    * Gets the ACH Processor field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ACH Processor or the specified default value.
    */
   public final String getACHProcessor( int index, String defaultValue )
   {
      return _ACHProcessor[index] == null ? defaultValue : _ACHProcessor[index];
   }
    
   /**
    * Gets the array of ACH Processor fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ACH Processor values.
    */
   public final String[] getACHProcessorArray()
   {
      return _ACHProcessor;
   }
    
   /**
    * Gets the Correspondent Bank Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Correspondent Bank Type or null.
    */
   public final String getCorrespBankType( int index )
   {
      return _CorrespBankType[index];
   }
    
   /**
    * Gets the Correspondent Bank Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Correspondent Bank Type or the specified default value.
    */
   public final String getCorrespBankType( int index, String defaultValue )
   {
      return _CorrespBankType[index] == null ? defaultValue : _CorrespBankType[index];
   }
    
   /**
    * Gets the array of Correspondent Bank Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Correspondent Bank Type values.
    */
   public final String[] getCorrespBankTypeArray()
   {
      return _CorrespBankType;
   }
    
   /**
    * Gets the Correspondent Bank ID Num field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Correspondent Bank ID Num or null.
    */
   public final String getCorrespBankIDNum( int index )
   {
      return _CorrespBankIDNum[index];
   }
    
   /**
    * Gets the Correspondent Bank ID Num field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Correspondent Bank ID Num or the specified default value.
    */
   public final String getCorrespBankIDNum( int index, String defaultValue )
   {
      return _CorrespBankIDNum[index] == null ? defaultValue : _CorrespBankIDNum[index];
   }
    
   /**
    * Gets the array of Correspondent Bank ID Num fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Correspondent Bank ID Num values.
    */
   public final String[] getCorrespBankIDNumArray()
   {
      return _CorrespBankIDNum;
   }
    
   /**
    * Gets the Credit Info Line 1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Credit Info Line 1 or null.
    */
   public final String getCreditInfoLine1( int index )
   {
      return _CreditInfoLine1[index];
   }
    
   /**
    * Gets the Credit Info Line 1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Credit Info Line 1 or the specified default value.
    */
   public final String getCreditInfoLine1( int index, String defaultValue )
   {
      return _CreditInfoLine1[index] == null ? defaultValue : _CreditInfoLine1[index];
   }
    
   /**
    * Gets the array of Credit Info Line 1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Credit Info Line 1 values.
    */
   public final String[] getCreditInfoLine1Array()
   {
      return _CreditInfoLine1;
   }
    
   /**
    * Gets the Credit Info Line 2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Credit Info Line 2 or null.
    */
   public final String getCreditInfoLine2( int index )
   {
      return _CreditInfoLine2[index];
   }
    
   /**
    * Gets the Credit Info Line 2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Credit Info Line 2 or the specified default value.
    */
   public final String getCreditInfoLine2( int index, String defaultValue )
   {
      return _CreditInfoLine2[index] == null ? defaultValue : _CreditInfoLine2[index];
   }
    
   /**
    * Gets the array of Credit Info Line 2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Credit Info Line 2 values.
    */
   public final String[] getCreditInfoLine2Array()
   {
      return _CreditInfoLine2;
   }
    
   /**
    * Gets the Correspondent Bank ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Correspondent Bank ID or null.
    */
   public final String getCorrespBankId( int index )
   {
      return _CorrespBankId[index];
   }
    
   /**
    * Gets the Correspondent Bank ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Correspondent Bank ID or the specified default value.
    */
   public final String getCorrespBankId( int index, String defaultValue )
   {
      return _CorrespBankId[index] == null ? defaultValue : _CorrespBankId[index];
   }
    
   /**
    * Gets the array of Correspondent Bank ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Correspondent Bank ID values.
    */
   public final String[] getCorrespBankIdArray()
   {
      return _CorrespBankId;
   }
    
   /**
    * Gets the Correspondent Transit Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Correspondent Transit Number or null.
    */
   public final Integer getCorrespTransitNo( int index )
   {
      return _CorrespTransitNo[index];
   }
    
   /**
    * Gets the Correspondent Transit Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Correspondent Transit Number or the specified default value.
    */
   public final int getCorrespTransitNo( int index, int defaultValue )
   {
      return _CorrespTransitNo[index] == null ? defaultValue : _CorrespTransitNo[index].intValue();
   }
    
   /**
    * Gets the array of Correspondent Transit Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Correspondent Transit Number values.
    */
   public final Integer[] getCorrespTransitNoArray()
   {
      return _CorrespTransitNo;
   }
    
   /**
    * Gets the Correspondent Institution Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Correspondent Institution Name or null.
    */
   public final String getCorrespInstName( int index )
   {
      return _CorrespInstName[index];
   }
    
   /**
    * Gets the Correspondent Institution Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Correspondent Institution Name or the specified default value.
    */
   public final String getCorrespInstName( int index, String defaultValue )
   {
      return _CorrespInstName[index] == null ? defaultValue : _CorrespInstName[index];
   }
    
   /**
    * Gets the array of Correspondent Institution Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Correspondent Institution Name values.
    */
   public final String[] getCorrespInstNameArray()
   {
      return _CorrespInstName;
   }
    
   /**
    * Gets the Correspondent Bank Contract field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Correspondent Bank Contract or null.
    */
   public final String getCorrespBankContact( int index )
   {
      return _CorrespBankContact[index];
   }
    
   /**
    * Gets the Correspondent Bank Contract field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Correspondent Bank Contract or the specified default value.
    */
   public final String getCorrespBankContact( int index, String defaultValue )
   {
      return _CorrespBankContact[index] == null ? defaultValue : _CorrespBankContact[index];
   }
    
   /**
    * Gets the array of Correspondent Bank Contract fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Correspondent Bank Contract values.
    */
   public final String[] getCorrespBankContactArray()
   {
      return _CorrespBankContact;
   }
    
   /**
    * Gets the Corresponded Bank Country field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Corresponded Bank Country or null.
    */
   public final String getCorrespBankCntry( int index )
   {
      return _CorrespBankCntry[index];
   }
    
   /**
    * Gets the Corresponded Bank Country field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Corresponded Bank Country or the specified default value.
    */
   public final String getCorrespBankCntry( int index, String defaultValue )
   {
      return _CorrespBankCntry[index] == null ? defaultValue : _CorrespBankCntry[index];
   }
    
   /**
    * Gets the array of Corresponded Bank Country fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Corresponded Bank Country values.
    */
   public final String[] getCorrespBankCntryArray()
   {
      return _CorrespBankCntry;
   }
    
   /**
    * Gets the Corresponded Bank Postal Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Corresponded Bank Postal Code or null.
    */
   public final String getCorrespBankPstl( int index )
   {
      return _CorrespBankPstl[index];
   }
    
   /**
    * Gets the Corresponded Bank Postal Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Corresponded Bank Postal Code or the specified default value.
    */
   public final String getCorrespBankPstl( int index, String defaultValue )
   {
      return _CorrespBankPstl[index] == null ? defaultValue : _CorrespBankPstl[index];
   }
    
   /**
    * Gets the array of Corresponded Bank Postal Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Corresponded Bank Postal Code values.
    */
   public final String[] getCorrespBankPstlArray()
   {
      return _CorrespBankPstl;
   }
    
   /**
    * Gets the Correspondent  Bank Address 1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Correspondent  Bank Address 1 or null.
    */
   public final String getCorrespBankAddr1( int index )
   {
      return _CorrespBankAddr1[index];
   }
    
   /**
    * Gets the Correspondent  Bank Address 1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Correspondent  Bank Address 1 or the specified default value.
    */
   public final String getCorrespBankAddr1( int index, String defaultValue )
   {
      return _CorrespBankAddr1[index] == null ? defaultValue : _CorrespBankAddr1[index];
   }
    
   /**
    * Gets the array of Correspondent  Bank Address 1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Correspondent  Bank Address 1 values.
    */
   public final String[] getCorrespBankAddr1Array()
   {
      return _CorrespBankAddr1;
   }
    
   /**
    * Gets the Correspondent  Bank Address 2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Correspondent  Bank Address 2 or null.
    */
   public final String getCorrespBankAddr2( int index )
   {
      return _CorrespBankAddr2[index];
   }
    
   /**
    * Gets the Correspondent  Bank Address 2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Correspondent  Bank Address 2 or the specified default value.
    */
   public final String getCorrespBankAddr2( int index, String defaultValue )
   {
      return _CorrespBankAddr2[index] == null ? defaultValue : _CorrespBankAddr2[index];
   }
    
   /**
    * Gets the array of Correspondent  Bank Address 2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Correspondent  Bank Address 2 values.
    */
   public final String[] getCorrespBankAddr2Array()
   {
      return _CorrespBankAddr2;
   }
    
   /**
    * Gets the Correspondent  Bank Address 3 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Correspondent  Bank Address 3 or null.
    */
   public final String getCorrespBankAddr3( int index )
   {
      return _CorrespBankAddr3[index];
   }
    
   /**
    * Gets the Correspondent  Bank Address 3 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Correspondent  Bank Address 3 or the specified default value.
    */
   public final String getCorrespBankAddr3( int index, String defaultValue )
   {
      return _CorrespBankAddr3[index] == null ? defaultValue : _CorrespBankAddr3[index];
   }
    
   /**
    * Gets the array of Correspondent  Bank Address 3 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Correspondent  Bank Address 3 values.
    */
   public final String[] getCorrespBankAddr3Array()
   {
      return _CorrespBankAddr3;
   }
    
   /**
    * Gets the Correspondent  Bank Address 4 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Correspondent  Bank Address 4 or null.
    */
   public final String getCorrespBankAddr4( int index )
   {
      return _CorrespBankAddr4[index];
   }
    
   /**
    * Gets the Correspondent  Bank Address 4 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Correspondent  Bank Address 4 or the specified default value.
    */
   public final String getCorrespBankAddr4( int index, String defaultValue )
   {
      return _CorrespBankAddr4[index] == null ? defaultValue : _CorrespBankAddr4[index];
   }
    
   /**
    * Gets the array of Correspondent  Bank Address 4 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Correspondent  Bank Address 4 values.
    */
   public final String[] getCorrespBankAddr4Array()
   {
      return _CorrespBankAddr4;
   }
    
   /**
    * Gets the Correspondent  Bank Address 5 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Correspondent  Bank Address 5 or null.
    */
   public final String getCorrespBankAddr5( int index )
   {
      return _CorrespBankAddr5[index];
   }
    
   /**
    * Gets the Correspondent  Bank Address 5 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Correspondent  Bank Address 5 or the specified default value.
    */
   public final String getCorrespBankAddr5( int index, String defaultValue )
   {
      return _CorrespBankAddr5[index] == null ? defaultValue : _CorrespBankAddr5[index];
   }
    
   /**
    * Gets the array of Correspondent  Bank Address 5 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Correspondent  Bank Address 5 values.
    */
   public final String[] getCorrespBankAddr5Array()
   {
      return _CorrespBankAddr5;
   }
    
   /**
    * Gets the Bank Account Effective Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Account Effective Date or null.
    */
   public final Date getEffectiveDate( int index )
   {
      return _EffectiveDate[index];
   }
    
   /**
    * Gets the Bank Account Effective Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Account Effective Date or the specified default value.
    */
   public final Date getEffectiveDate( int index, Date defaultValue )
   {
      return _EffectiveDate[index] == null ? defaultValue : _EffectiveDate[index];
   }
    
   /**
    * Gets the array of Bank Account Effective Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Account Effective Date values.
    */
   public final Date[] getEffectiveDateArray()
   {
      return _EffectiveDate;
   }
    
   /**
    * Gets the Bank Account Stop Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Account Stop Date or null.
    */
   public final Date getStopDate( int index )
   {
      return _StopDate[index];
   }
    
   /**
    * Gets the Bank Account Stop Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Account Stop Date or the specified default value.
    */
   public final Date getStopDate( int index, Date defaultValue )
   {
      return _StopDate[index] == null ? defaultValue : _StopDate[index];
   }
    
   /**
    * Gets the array of Bank Account Stop Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Account Stop Date values.
    */
   public final Date[] getStopDateArray()
   {
      return _StopDate;
   }
    
   /**
    * Gets the Bank Account record version number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Account record version number or null.
    */
   public final Integer getBankAcctVer( int index )
   {
      return _BankAcctVer[index];
   }
    
   /**
    * Gets the Bank Account record version number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Account record version number or the specified default value.
    */
   public final int getBankAcctVer( int index, int defaultValue )
   {
      return _BankAcctVer[index] == null ? defaultValue : _BankAcctVer[index].intValue();
   }
    
   /**
    * Gets the array of Bank Account record version number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Account record version number values.
    */
   public final Integer[] getBankAcctVerArray()
   {
      return _BankAcctVer;
   }
    
   /**
    * Gets the Account Use Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Use Code or null.
    */
   public final String getAcctUseCode( int index )
   {
      return _AcctUseCode[index];
   }
    
   /**
    * Gets the Account Use Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Use Code or the specified default value.
    */
   public final String getAcctUseCode( int index, String defaultValue )
   {
      return _AcctUseCode[index] == null ? defaultValue : _AcctUseCode[index];
   }
    
   /**
    * Gets the array of Account Use Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Use Code values.
    */
   public final String[] getAcctUseCodeArray()
   {
      return _AcctUseCode;
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
      
      _InstId = resizeArray( _InstId, _RepeatCount );
      _AcctID = resizeArray( _AcctID, _RepeatCount );
      _PolicyYear = resizeArray( _PolicyYear, _RepeatCount );
      _PolicyTerm = resizeArray( _PolicyTerm, _RepeatCount );
      _MaturityDate = resizeArray( _MaturityDate, _RepeatCount );
      _RedCode = resizeArray( _RedCode, _RepeatCount );
      _RedCodeDesc = resizeArray( _RedCodeDesc, _RepeatCount );
      _Adcd = resizeArray( _Adcd, _RepeatCount );
      _Amount = resizeArray( _Amount, _RepeatCount );
      _PUD = resizeArray( _PUD, _RepeatCount );
      _SourceOfFund = resizeArray( _SourceOfFund, _RepeatCount );
      _PayType = resizeArray( _PayType, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _Username = resizeArray( _Username, _RepeatCount );
      _Username2 = resizeArray( _Username2, _RepeatCount );
      _SEGMATINSTDETAILUUID = resizeArray( _SEGMATINSTDETAILUUID, _RepeatCount );
      _InstName = resizeArray( _InstName, _RepeatCount );
      _SwiftCode = resizeArray( _SwiftCode, _RepeatCount );
      _RefNumber = resizeArray( _RefNumber, _RepeatCount );
      _TransitNo = resizeArray( _TransitNo, _RepeatCount );
      _BankIDNum = resizeArray( _BankIDNum, _RepeatCount );
      _BankID = resizeArray( _BankID, _RepeatCount );
      _BankAcctNum = resizeArray( _BankAcctNum, _RepeatCount );
      _BankAcctName = resizeArray( _BankAcctName, _RepeatCount );
      _BankAcctType = resizeArray( _BankAcctType, _RepeatCount );
      _BankAcctTypeDesc = resizeArray( _BankAcctTypeDesc, _RepeatCount );
      _BankAcctCurr = resizeArray( _BankAcctCurr, _RepeatCount );
      _BankAcctCurrDesc = resizeArray( _BankAcctCurrDesc, _RepeatCount );
      _BankAddr1 = resizeArray( _BankAddr1, _RepeatCount );
      _BankAddr2 = resizeArray( _BankAddr2, _RepeatCount );
      _BankAddr3 = resizeArray( _BankAddr3, _RepeatCount );
      _BankAddr4 = resizeArray( _BankAddr4, _RepeatCount );
      _BankAddr5 = resizeArray( _BankAddr5, _RepeatCount );
      _BankContact = resizeArray( _BankContact, _RepeatCount );
      _BankCntry = resizeArray( _BankCntry, _RepeatCount );
      _BankPstl = resizeArray( _BankPstl, _RepeatCount );
      _BankType = resizeArray( _BankType, _RepeatCount );
      _PayReason1 = resizeArray( _PayReason1, _RepeatCount );
      _PayReason2 = resizeArray( _PayReason2, _RepeatCount );
      _ACHProcessor = resizeArray( _ACHProcessor, _RepeatCount );
      _CorrespBankType = resizeArray( _CorrespBankType, _RepeatCount );
      _CorrespBankIDNum = resizeArray( _CorrespBankIDNum, _RepeatCount );
      _CreditInfoLine1 = resizeArray( _CreditInfoLine1, _RepeatCount );
      _CreditInfoLine2 = resizeArray( _CreditInfoLine2, _RepeatCount );
      _CorrespBankId = resizeArray( _CorrespBankId, _RepeatCount );
      _CorrespTransitNo = resizeArray( _CorrespTransitNo, _RepeatCount );
      _CorrespInstName = resizeArray( _CorrespInstName, _RepeatCount );
      _CorrespBankContact = resizeArray( _CorrespBankContact, _RepeatCount );
      _CorrespBankCntry = resizeArray( _CorrespBankCntry, _RepeatCount );
      _CorrespBankPstl = resizeArray( _CorrespBankPstl, _RepeatCount );
      _CorrespBankAddr1 = resizeArray( _CorrespBankAddr1, _RepeatCount );
      _CorrespBankAddr2 = resizeArray( _CorrespBankAddr2, _RepeatCount );
      _CorrespBankAddr3 = resizeArray( _CorrespBankAddr3, _RepeatCount );
      _CorrespBankAddr4 = resizeArray( _CorrespBankAddr4, _RepeatCount );
      _CorrespBankAddr5 = resizeArray( _CorrespBankAddr5, _RepeatCount );
      _EffectiveDate = resizeArray( _EffectiveDate, _RepeatCount );
      _StopDate = resizeArray( _StopDate, _RepeatCount );
      _BankAcctVer = resizeArray( _BankAcctVer, _RepeatCount );
      _AcctUseCode = resizeArray( _AcctUseCode, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _InstId[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PolicyYear[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _PolicyTerm[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _MaturityDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _RedCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RedCodeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Adcd[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Amount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PUD[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SourceOfFund[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PayType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _Username[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Username2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SEGMATINSTDETAILUUID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _InstName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SwiftCode[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _RefNumber[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _TransitNo[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _BankIDNum[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _BankID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAcctNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAcctName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAcctType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAcctTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAcctCurr[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAcctCurrDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAddr1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAddr2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAddr3[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAddr4[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAddr5[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankContact[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankCntry[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankPstl[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PayReason1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PayReason2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ACHProcessor[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CorrespBankType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CorrespBankIDNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CreditInfoLine1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CreditInfoLine2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CorrespBankId[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CorrespTransitNo[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _CorrespInstName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CorrespBankContact[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CorrespBankCntry[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CorrespBankPstl[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CorrespBankAddr1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CorrespBankAddr2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CorrespBankAddr3[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CorrespBankAddr4[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CorrespBankAddr5[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EffectiveDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _StopDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _BankAcctVer[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _AcctUseCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
