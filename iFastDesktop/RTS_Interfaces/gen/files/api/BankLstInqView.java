
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Bank List Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/BankLstInq.doc">BankLstInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class BankLstInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * TransitCode member array.
    */
   private String[] _rxTransitCode = null;
   
   /**
    * Name member array.
    */
   private String[] _Name = null;
   
   /**
    * Swift Code member array.
    */
   private Integer[] _SwiftCode = null;
   
   /**
    * Reference Number member array.
    */
   private Integer[] _RefNumber = null;
   
   /**
    * Currency member array.
    */
   private String[] _Currency = null;
   
   /**
    * Branch Name member array.
    */
   private String[] _BranchName = null;
   
   /**
    * Generic Bank ID number member array.
    */
   private String[] _rxBankIDNum = null;
   
   /**
    * Bank Addr line 1 member array.
    */
   private String[] _BankAddr1 = null;
   
   /**
    * Bank Addr line 2 member array.
    */
   private String[] _BankAddr2 = null;
   
   /**
    * Bank Addr line 3 member array.
    */
   private String[] _BankAddr3 = null;
   
   /**
    * Bank Addr line 4 member array.
    */
   private String[] _BankAddr4 = null;
   
   /**
    * Bank Addr line 5 member array.
    */
   private String[] _BankAddr5 = null;
   
   /**
    * Bank contact person member array.
    */
   private String[] _BankContact = null;
   
   /**
    * Bank address country code member array.
    */
   private String[] _BankCntry = null;
   
   /**
    * Bank address pstl code member array.
    */
   private String[] _BankPstl = null;
   
   /**
    * Bank Type member array.
    */
   private String[] _rxBankType = null;
   
   /**
    * Bank Id member array.
    */
   private Integer[] _rxBankId = null;
   
   /**
    * Telex member array.
    */
   private String[] _Telex = null;
   
   /**
    * Fax Nunber member array.
    */
   private String[] _FaxNumber = null;
   
   /**
    * Phone Number member array.
    */
   private String[] _PhoneNumber = null;
   
   /**
    * Short Name member array.
    */
   private String[] _ShortName = null;
   
   /**
    * Parent Bank member array.
    */
   private Integer[] _ParentBank = null;
   
   /**
    * City member array.
    */
   private String[] _City = null;
   
   /**
    * Province member array.
    */
   private String[] _Province = null;
   
   /**
    * Process Date member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * Mod Name member array.
    */
   private String[] _ModName = null;
   
   /**
    * Mod Date member array.
    */
   private Date[] _ModDate = null;
   
   /**
    * User Name member array.
    */
   private String[] _UserName = null;
   
   /**
    * InstRole member array.
    */
   private Integer[] _InstRole = null;
   
   /**
    * Version Number member array.
    */
   private Integer[] _VersionNum = null;
   
   /**
    * Bank Rec ID member array.
    */
   private Integer[] _BankRid = null;
   
   /**
    * Code Page member array.
    */
   private String[] _CodePage = null;
   
   /**
    * Account Number member array.
    */
   private String[] _AcctNumber = null;
   
   /**
    * Parent Gen Bank Code member array.
    */
   private String[] _ParentGenBankCode = null;
   
   /**
    * Financial Year End member array.
    */
   private Date[] _FinancialYearEnd = null;
   
   /**
    * Status Code member array.
    */
   private Integer[] _StatusCode = null;
   
   /**
    * Inst Category member array.
    */
   private String[] _rxInstCategory = null;
   

   /**
    * Constructs the BankLstInqView object.
    * 
    */
   public BankLstInqView()
   {
      super ( new BankLstInqRequest() );
   }

   /**
    * Constructs the BankLstInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public BankLstInqView( String hostEncoding )
   {
      super ( new BankLstInqRequest( hostEncoding ) );
   }

   /**
    * Gets the BankLstInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The BankLstInqRequest object.
    */
   public final BankLstInqRequest getRequest()
   {
      return (BankLstInqRequest)getIFastRequest();
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
    * Gets the TransitCode field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the TransitCode or null.
    */
   public final String getrxTransitCode( int index )
   {
      return _rxTransitCode[index];
   }
    
   /**
    * Gets the TransitCode field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the TransitCode or the specified default value.
    */
   public final String getrxTransitCode( int index, String defaultValue )
   {
      return _rxTransitCode[index] == null ? defaultValue : _rxTransitCode[index];
   }
    
   /**
    * Gets the array of TransitCode fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of TransitCode values.
    */
   public final String[] getrxTransitCodeArray()
   {
      return _rxTransitCode;
   }
    
   /**
    * Gets the Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Name or null.
    */
   public final String getName( int index )
   {
      return _Name[index];
   }
    
   /**
    * Gets the Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Name or the specified default value.
    */
   public final String getName( int index, String defaultValue )
   {
      return _Name[index] == null ? defaultValue : _Name[index];
   }
    
   /**
    * Gets the array of Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Name values.
    */
   public final String[] getNameArray()
   {
      return _Name;
   }
    
   /**
    * Gets the Swift Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Swift Code or null.
    */
   public final Integer getSwiftCode( int index )
   {
      return _SwiftCode[index];
   }
    
   /**
    * Gets the Swift Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Swift Code or the specified default value.
    */
   public final int getSwiftCode( int index, int defaultValue )
   {
      return _SwiftCode[index] == null ? defaultValue : _SwiftCode[index].intValue();
   }
    
   /**
    * Gets the array of Swift Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Swift Code values.
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
    * Gets the Branch Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Branch Name or null.
    */
   public final String getBranchName( int index )
   {
      return _BranchName[index];
   }
    
   /**
    * Gets the Branch Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Branch Name or the specified default value.
    */
   public final String getBranchName( int index, String defaultValue )
   {
      return _BranchName[index] == null ? defaultValue : _BranchName[index];
   }
    
   /**
    * Gets the array of Branch Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Branch Name values.
    */
   public final String[] getBranchNameArray()
   {
      return _BranchName;
   }
    
   /**
    * Gets the Generic Bank ID number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Generic Bank ID number or null.
    */
   public final String getrxBankIDNum( int index )
   {
      return _rxBankIDNum[index];
   }
    
   /**
    * Gets the Generic Bank ID number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Generic Bank ID number or the specified default value.
    */
   public final String getrxBankIDNum( int index, String defaultValue )
   {
      return _rxBankIDNum[index] == null ? defaultValue : _rxBankIDNum[index];
   }
    
   /**
    * Gets the array of Generic Bank ID number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Generic Bank ID number values.
    */
   public final String[] getrxBankIDNumArray()
   {
      return _rxBankIDNum;
   }
    
   /**
    * Gets the Bank Addr line 1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Addr line 1 or null.
    */
   public final String getBankAddr1( int index )
   {
      return _BankAddr1[index];
   }
    
   /**
    * Gets the Bank Addr line 1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Addr line 1 or the specified default value.
    */
   public final String getBankAddr1( int index, String defaultValue )
   {
      return _BankAddr1[index] == null ? defaultValue : _BankAddr1[index];
   }
    
   /**
    * Gets the array of Bank Addr line 1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Addr line 1 values.
    */
   public final String[] getBankAddr1Array()
   {
      return _BankAddr1;
   }
    
   /**
    * Gets the Bank Addr line 2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Addr line 2 or null.
    */
   public final String getBankAddr2( int index )
   {
      return _BankAddr2[index];
   }
    
   /**
    * Gets the Bank Addr line 2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Addr line 2 or the specified default value.
    */
   public final String getBankAddr2( int index, String defaultValue )
   {
      return _BankAddr2[index] == null ? defaultValue : _BankAddr2[index];
   }
    
   /**
    * Gets the array of Bank Addr line 2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Addr line 2 values.
    */
   public final String[] getBankAddr2Array()
   {
      return _BankAddr2;
   }
    
   /**
    * Gets the Bank Addr line 3 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Addr line 3 or null.
    */
   public final String getBankAddr3( int index )
   {
      return _BankAddr3[index];
   }
    
   /**
    * Gets the Bank Addr line 3 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Addr line 3 or the specified default value.
    */
   public final String getBankAddr3( int index, String defaultValue )
   {
      return _BankAddr3[index] == null ? defaultValue : _BankAddr3[index];
   }
    
   /**
    * Gets the array of Bank Addr line 3 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Addr line 3 values.
    */
   public final String[] getBankAddr3Array()
   {
      return _BankAddr3;
   }
    
   /**
    * Gets the Bank Addr line 4 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Addr line 4 or null.
    */
   public final String getBankAddr4( int index )
   {
      return _BankAddr4[index];
   }
    
   /**
    * Gets the Bank Addr line 4 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Addr line 4 or the specified default value.
    */
   public final String getBankAddr4( int index, String defaultValue )
   {
      return _BankAddr4[index] == null ? defaultValue : _BankAddr4[index];
   }
    
   /**
    * Gets the array of Bank Addr line 4 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Addr line 4 values.
    */
   public final String[] getBankAddr4Array()
   {
      return _BankAddr4;
   }
    
   /**
    * Gets the Bank Addr line 5 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Addr line 5 or null.
    */
   public final String getBankAddr5( int index )
   {
      return _BankAddr5[index];
   }
    
   /**
    * Gets the Bank Addr line 5 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Addr line 5 or the specified default value.
    */
   public final String getBankAddr5( int index, String defaultValue )
   {
      return _BankAddr5[index] == null ? defaultValue : _BankAddr5[index];
   }
    
   /**
    * Gets the array of Bank Addr line 5 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Addr line 5 values.
    */
   public final String[] getBankAddr5Array()
   {
      return _BankAddr5;
   }
    
   /**
    * Gets the Bank contact person field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank contact person or null.
    */
   public final String getBankContact( int index )
   {
      return _BankContact[index];
   }
    
   /**
    * Gets the Bank contact person field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank contact person or the specified default value.
    */
   public final String getBankContact( int index, String defaultValue )
   {
      return _BankContact[index] == null ? defaultValue : _BankContact[index];
   }
    
   /**
    * Gets the array of Bank contact person fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank contact person values.
    */
   public final String[] getBankContactArray()
   {
      return _BankContact;
   }
    
   /**
    * Gets the Bank address country code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank address country code or null.
    */
   public final String getBankCntry( int index )
   {
      return _BankCntry[index];
   }
    
   /**
    * Gets the Bank address country code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank address country code or the specified default value.
    */
   public final String getBankCntry( int index, String defaultValue )
   {
      return _BankCntry[index] == null ? defaultValue : _BankCntry[index];
   }
    
   /**
    * Gets the array of Bank address country code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank address country code values.
    */
   public final String[] getBankCntryArray()
   {
      return _BankCntry;
   }
    
   /**
    * Gets the Bank address pstl code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank address pstl code or null.
    */
   public final String getBankPstl( int index )
   {
      return _BankPstl[index];
   }
    
   /**
    * Gets the Bank address pstl code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank address pstl code or the specified default value.
    */
   public final String getBankPstl( int index, String defaultValue )
   {
      return _BankPstl[index] == null ? defaultValue : _BankPstl[index];
   }
    
   /**
    * Gets the array of Bank address pstl code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank address pstl code values.
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
   public final String getrxBankType( int index )
   {
      return _rxBankType[index];
   }
    
   /**
    * Gets the Bank Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Type or the specified default value.
    */
   public final String getrxBankType( int index, String defaultValue )
   {
      return _rxBankType[index] == null ? defaultValue : _rxBankType[index];
   }
    
   /**
    * Gets the array of Bank Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Type values.
    */
   public final String[] getrxBankTypeArray()
   {
      return _rxBankType;
   }
    
   /**
    * Gets the Bank Id field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Id or null.
    */
   public final Integer getrxBankId( int index )
   {
      return _rxBankId[index];
   }
    
   /**
    * Gets the Bank Id field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Id or the specified default value.
    */
   public final int getrxBankId( int index, int defaultValue )
   {
      return _rxBankId[index] == null ? defaultValue : _rxBankId[index].intValue();
   }
    
   /**
    * Gets the array of Bank Id fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Id values.
    */
   public final Integer[] getrxBankIdArray()
   {
      return _rxBankId;
   }
    
   /**
    * Gets the Telex field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Telex or null.
    */
   public final String getTelex( int index )
   {
      return _Telex[index];
   }
    
   /**
    * Gets the Telex field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Telex or the specified default value.
    */
   public final String getTelex( int index, String defaultValue )
   {
      return _Telex[index] == null ? defaultValue : _Telex[index];
   }
    
   /**
    * Gets the array of Telex fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Telex values.
    */
   public final String[] getTelexArray()
   {
      return _Telex;
   }
    
   /**
    * Gets the Fax Nunber field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fax Nunber or null.
    */
   public final String getFaxNumber( int index )
   {
      return _FaxNumber[index];
   }
    
   /**
    * Gets the Fax Nunber field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fax Nunber or the specified default value.
    */
   public final String getFaxNumber( int index, String defaultValue )
   {
      return _FaxNumber[index] == null ? defaultValue : _FaxNumber[index];
   }
    
   /**
    * Gets the array of Fax Nunber fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fax Nunber values.
    */
   public final String[] getFaxNumberArray()
   {
      return _FaxNumber;
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
    * Gets the Short Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Short Name or null.
    */
   public final String getShortName( int index )
   {
      return _ShortName[index];
   }
    
   /**
    * Gets the Short Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Short Name or the specified default value.
    */
   public final String getShortName( int index, String defaultValue )
   {
      return _ShortName[index] == null ? defaultValue : _ShortName[index];
   }
    
   /**
    * Gets the array of Short Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Short Name values.
    */
   public final String[] getShortNameArray()
   {
      return _ShortName;
   }
    
   /**
    * Gets the Parent Bank field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Parent Bank or null.
    */
   public final Integer getParentBank( int index )
   {
      return _ParentBank[index];
   }
    
   /**
    * Gets the Parent Bank field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Parent Bank or the specified default value.
    */
   public final int getParentBank( int index, int defaultValue )
   {
      return _ParentBank[index] == null ? defaultValue : _ParentBank[index].intValue();
   }
    
   /**
    * Gets the array of Parent Bank fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Parent Bank values.
    */
   public final Integer[] getParentBankArray()
   {
      return _ParentBank;
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
    * Gets the Mod Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Mod Name or null.
    */
   public final String getModName( int index )
   {
      return _ModName[index];
   }
    
   /**
    * Gets the Mod Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Mod Name or the specified default value.
    */
   public final String getModName( int index, String defaultValue )
   {
      return _ModName[index] == null ? defaultValue : _ModName[index];
   }
    
   /**
    * Gets the array of Mod Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Mod Name values.
    */
   public final String[] getModNameArray()
   {
      return _ModName;
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
    * Gets the InstRole field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the InstRole or null.
    */
   public final Integer getInstRole( int index )
   {
      return _InstRole[index];
   }
    
   /**
    * Gets the InstRole field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the InstRole or the specified default value.
    */
   public final int getInstRole( int index, int defaultValue )
   {
      return _InstRole[index] == null ? defaultValue : _InstRole[index].intValue();
   }
    
   /**
    * Gets the array of InstRole fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of InstRole values.
    */
   public final Integer[] getInstRoleArray()
   {
      return _InstRole;
   }
    
   /**
    * Gets the Version Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Version Number or null.
    */
   public final Integer getVersionNum( int index )
   {
      return _VersionNum[index];
   }
    
   /**
    * Gets the Version Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Version Number or the specified default value.
    */
   public final int getVersionNum( int index, int defaultValue )
   {
      return _VersionNum[index] == null ? defaultValue : _VersionNum[index].intValue();
   }
    
   /**
    * Gets the array of Version Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Version Number values.
    */
   public final Integer[] getVersionNumArray()
   {
      return _VersionNum;
   }
    
   /**
    * Gets the Bank Rec ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Rec ID or null.
    */
   public final Integer getBankRid( int index )
   {
      return _BankRid[index];
   }
    
   /**
    * Gets the Bank Rec ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Rec ID or the specified default value.
    */
   public final int getBankRid( int index, int defaultValue )
   {
      return _BankRid[index] == null ? defaultValue : _BankRid[index].intValue();
   }
    
   /**
    * Gets the array of Bank Rec ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Rec ID values.
    */
   public final Integer[] getBankRidArray()
   {
      return _BankRid;
   }
    
   /**
    * Gets the Code Page field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Code Page or null.
    */
   public final String getCodePage( int index )
   {
      return _CodePage[index];
   }
    
   /**
    * Gets the Code Page field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Code Page or the specified default value.
    */
   public final String getCodePage( int index, String defaultValue )
   {
      return _CodePage[index] == null ? defaultValue : _CodePage[index];
   }
    
   /**
    * Gets the array of Code Page fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Code Page values.
    */
   public final String[] getCodePageArray()
   {
      return _CodePage;
   }
    
   /**
    * Gets the Account Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Number or null.
    */
   public final String getAcctNumber( int index )
   {
      return _AcctNumber[index];
   }
    
   /**
    * Gets the Account Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Number or the specified default value.
    */
   public final String getAcctNumber( int index, String defaultValue )
   {
      return _AcctNumber[index] == null ? defaultValue : _AcctNumber[index];
   }
    
   /**
    * Gets the array of Account Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Number values.
    */
   public final String[] getAcctNumberArray()
   {
      return _AcctNumber;
   }
    
   /**
    * Gets the Parent Gen Bank Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Parent Gen Bank Code or null.
    */
   public final String getParentGenBankCode( int index )
   {
      return _ParentGenBankCode[index];
   }
    
   /**
    * Gets the Parent Gen Bank Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Parent Gen Bank Code or the specified default value.
    */
   public final String getParentGenBankCode( int index, String defaultValue )
   {
      return _ParentGenBankCode[index] == null ? defaultValue : _ParentGenBankCode[index];
   }
    
   /**
    * Gets the array of Parent Gen Bank Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Parent Gen Bank Code values.
    */
   public final String[] getParentGenBankCodeArray()
   {
      return _ParentGenBankCode;
   }
    
   /**
    * Gets the Financial Year End field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Financial Year End or null.
    */
   public final Date getFinancialYearEnd( int index )
   {
      return _FinancialYearEnd[index];
   }
    
   /**
    * Gets the Financial Year End field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Financial Year End or the specified default value.
    */
   public final Date getFinancialYearEnd( int index, Date defaultValue )
   {
      return _FinancialYearEnd[index] == null ? defaultValue : _FinancialYearEnd[index];
   }
    
   /**
    * Gets the array of Financial Year End fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Financial Year End values.
    */
   public final Date[] getFinancialYearEndArray()
   {
      return _FinancialYearEnd;
   }
    
   /**
    * Gets the Status Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Status Code or null.
    */
   public final Integer getStatusCode( int index )
   {
      return _StatusCode[index];
   }
    
   /**
    * Gets the Status Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Status Code or the specified default value.
    */
   public final int getStatusCode( int index, int defaultValue )
   {
      return _StatusCode[index] == null ? defaultValue : _StatusCode[index].intValue();
   }
    
   /**
    * Gets the array of Status Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Status Code values.
    */
   public final Integer[] getStatusCodeArray()
   {
      return _StatusCode;
   }
    
   /**
    * Gets the Inst Category field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Inst Category or null.
    */
   public final String getrxInstCategory( int index )
   {
      return _rxInstCategory[index];
   }
    
   /**
    * Gets the Inst Category field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Inst Category or the specified default value.
    */
   public final String getrxInstCategory( int index, String defaultValue )
   {
      return _rxInstCategory[index] == null ? defaultValue : _rxInstCategory[index];
   }
    
   /**
    * Gets the array of Inst Category fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Inst Category values.
    */
   public final String[] getrxInstCategoryArray()
   {
      return _rxInstCategory;
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
      
      _rxTransitCode = resizeArray( _rxTransitCode, _RepeatCount );
      _Name = resizeArray( _Name, _RepeatCount );
      _SwiftCode = resizeArray( _SwiftCode, _RepeatCount );
      _RefNumber = resizeArray( _RefNumber, _RepeatCount );
      _Currency = resizeArray( _Currency, _RepeatCount );
      _BranchName = resizeArray( _BranchName, _RepeatCount );
      _rxBankIDNum = resizeArray( _rxBankIDNum, _RepeatCount );
      _BankAddr1 = resizeArray( _BankAddr1, _RepeatCount );
      _BankAddr2 = resizeArray( _BankAddr2, _RepeatCount );
      _BankAddr3 = resizeArray( _BankAddr3, _RepeatCount );
      _BankAddr4 = resizeArray( _BankAddr4, _RepeatCount );
      _BankAddr5 = resizeArray( _BankAddr5, _RepeatCount );
      _BankContact = resizeArray( _BankContact, _RepeatCount );
      _BankCntry = resizeArray( _BankCntry, _RepeatCount );
      _BankPstl = resizeArray( _BankPstl, _RepeatCount );
      _rxBankType = resizeArray( _rxBankType, _RepeatCount );
      _rxBankId = resizeArray( _rxBankId, _RepeatCount );
      _Telex = resizeArray( _Telex, _RepeatCount );
      _FaxNumber = resizeArray( _FaxNumber, _RepeatCount );
      _PhoneNumber = resizeArray( _PhoneNumber, _RepeatCount );
      _ShortName = resizeArray( _ShortName, _RepeatCount );
      _ParentBank = resizeArray( _ParentBank, _RepeatCount );
      _City = resizeArray( _City, _RepeatCount );
      _Province = resizeArray( _Province, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _ModName = resizeArray( _ModName, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _UserName = resizeArray( _UserName, _RepeatCount );
      _InstRole = resizeArray( _InstRole, _RepeatCount );
      _VersionNum = resizeArray( _VersionNum, _RepeatCount );
      _BankRid = resizeArray( _BankRid, _RepeatCount );
      _CodePage = resizeArray( _CodePage, _RepeatCount );
      _AcctNumber = resizeArray( _AcctNumber, _RepeatCount );
      _ParentGenBankCode = resizeArray( _ParentGenBankCode, _RepeatCount );
      _FinancialYearEnd = resizeArray( _FinancialYearEnd, _RepeatCount );
      _StatusCode = resizeArray( _StatusCode, _RepeatCount );
      _rxInstCategory = resizeArray( _rxInstCategory, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxTransitCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Name[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SwiftCode[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _RefNumber[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _Currency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BranchName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxBankIDNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAddr1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAddr2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAddr3[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAddr4[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAddr5[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankContact[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankCntry[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankPstl[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxBankType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxBankId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _Telex[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FaxNumber[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PhoneNumber[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ShortName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ParentBank[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _City[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Province[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ModName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _UserName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _InstRole[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _VersionNum[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _BankRid[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _CodePage[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctNumber[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ParentGenBankCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FinancialYearEnd[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _StatusCode[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _rxInstCategory[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
