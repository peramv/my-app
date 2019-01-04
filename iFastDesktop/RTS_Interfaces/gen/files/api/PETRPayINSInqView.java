
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Pay Entity Trade Payment Instruction Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/PETRPayINSInq.doc">PETRPayINSInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class PETRPayINSInqView extends IFastView implements Serializable
{

   /**
    * Other Payment For Exists member variable.
    */
   private Boolean _OthPaymentForExist = null;
   
   private int _RepeatCount = 0;
   
   /**
    * Payment For member array.
    */
   private String[] _rxPaymentFor = null;
   
   /**
    * Payment Type member array.
    */
   private String[] _PayType = null;
   
   /**
    * Payment Method member array.
    */
   private String[] _PayMethod = null;
   
   /**
    * ACH Processor member array.
    */
   private String[] _ACHProcessor = null;
   
   /**
    * Consolidation Type member array.
    */
   private String[] _ConsolType = null;
   
   /**
    * Direct To member array.
    */
   private String[] _DirectTo = null;
   
   /**
    * Bank Charge member array.
    */
   private String[] _BankCharge = null;
   
   /**
    * Currency Option member array.
    */
   private String[] _CurrOption = null;
   
   /**
    * Currency member array.
    */
   private String[] _Currency = null;
   
   /**
    * Effective Date member array.
    */
   private Date[] _rxDeff = null;
   
   /**
    * Stop Date member array.
    */
   private Date[] _StopDate = null;
   
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
    * Address Country member array.
    */
   private String[] _AddrCntry = null;
   
   /**
    * Address Postal member array.
    */
   private String[] _AddrPSTL = null;
   
   /**
    * User Pay Entity Address member array.
    */
   private Boolean[] _UserPayEntityAddr = null;
   
   /**
    * Trade Pay Instruct Version member array.
    */
   private Integer[] _TrdPayInstrVersion = null;
   
   /**
    * Trade Pay Instruct Recid member array.
    */
   private Integer[] _TrdPayInstrRecid = null;
   
   /**
    * Date Created member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * User Name member array.
    */
   private String[] _UserName = null;
   
   /**
    * Date Modified member array.
    */
   private Date[] _ModDate = null;
   
   /**
    * Mod User member array.
    */
   private String[] _ModUser = null;
   
   /**
    * Reinvest Account Number member array.
    */
   private String[] _ReinvAccount = null;
   
   /**
    * Payment Instructions ID member array.
    */
   private String[] _PayInstructId = null;
   

   /**
    * Constructs the PETRPayINSInqView object.
    * 
    */
   public PETRPayINSInqView()
   {
      super ( new PETRPayINSInqRequest() );
   }

   /**
    * Constructs the PETRPayINSInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public PETRPayINSInqView( String hostEncoding )
   {
      super ( new PETRPayINSInqRequest( hostEncoding ) );
   }

   /**
    * Gets the PETRPayINSInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The PETRPayINSInqRequest object.
    */
   public final PETRPayINSInqRequest getRequest()
   {
      return (PETRPayINSInqRequest)getIFastRequest();
   }
        
   /**
    * Gets the Other Payment For Exists field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Other Payment For Exists or null.
    */
   public final Boolean getOthPaymentForExist()
   {
      return _OthPaymentForExist;
   }
	
   /**
    * Gets the Other Payment For Exists field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Other Payment For Exists or the specified default value.
    */
   public final boolean getOthPaymentForExist( boolean defaultValue )
   {
      return _OthPaymentForExist == null ? defaultValue : _OthPaymentForExist.booleanValue();
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
    * Gets the Payment For field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Payment For or null.
    */
   public final String getrxPaymentFor( int index )
   {
      return _rxPaymentFor[index];
   }
    
   /**
    * Gets the Payment For field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Payment For or the specified default value.
    */
   public final String getrxPaymentFor( int index, String defaultValue )
   {
      return _rxPaymentFor[index] == null ? defaultValue : _rxPaymentFor[index];
   }
    
   /**
    * Gets the array of Payment For fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Payment For values.
    */
   public final String[] getrxPaymentForArray()
   {
      return _rxPaymentFor;
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
    * Gets the Payment Method field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Payment Method or null.
    */
   public final String getPayMethod( int index )
   {
      return _PayMethod[index];
   }
    
   /**
    * Gets the Payment Method field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Payment Method or the specified default value.
    */
   public final String getPayMethod( int index, String defaultValue )
   {
      return _PayMethod[index] == null ? defaultValue : _PayMethod[index];
   }
    
   /**
    * Gets the array of Payment Method fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Payment Method values.
    */
   public final String[] getPayMethodArray()
   {
      return _PayMethod;
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
    * Gets the Consolidation Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Consolidation Type or null.
    */
   public final String getConsolType( int index )
   {
      return _ConsolType[index];
   }
    
   /**
    * Gets the Consolidation Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Consolidation Type or the specified default value.
    */
   public final String getConsolType( int index, String defaultValue )
   {
      return _ConsolType[index] == null ? defaultValue : _ConsolType[index];
   }
    
   /**
    * Gets the array of Consolidation Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Consolidation Type values.
    */
   public final String[] getConsolTypeArray()
   {
      return _ConsolType;
   }
    
   /**
    * Gets the Direct To field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Direct To or null.
    */
   public final String getDirectTo( int index )
   {
      return _DirectTo[index];
   }
    
   /**
    * Gets the Direct To field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Direct To or the specified default value.
    */
   public final String getDirectTo( int index, String defaultValue )
   {
      return _DirectTo[index] == null ? defaultValue : _DirectTo[index];
   }
    
   /**
    * Gets the array of Direct To fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Direct To values.
    */
   public final String[] getDirectToArray()
   {
      return _DirectTo;
   }
    
   /**
    * Gets the Bank Charge field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Charge or null.
    */
   public final String getBankCharge( int index )
   {
      return _BankCharge[index];
   }
    
   /**
    * Gets the Bank Charge field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Charge or the specified default value.
    */
   public final String getBankCharge( int index, String defaultValue )
   {
      return _BankCharge[index] == null ? defaultValue : _BankCharge[index];
   }
    
   /**
    * Gets the array of Bank Charge fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Charge values.
    */
   public final String[] getBankChargeArray()
   {
      return _BankCharge;
   }
    
   /**
    * Gets the Currency Option field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Currency Option or null.
    */
   public final String getCurrOption( int index )
   {
      return _CurrOption[index];
   }
    
   /**
    * Gets the Currency Option field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Currency Option or the specified default value.
    */
   public final String getCurrOption( int index, String defaultValue )
   {
      return _CurrOption[index] == null ? defaultValue : _CurrOption[index];
   }
    
   /**
    * Gets the array of Currency Option fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Currency Option values.
    */
   public final String[] getCurrOptionArray()
   {
      return _CurrOption;
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
   public final Date getrxDeff( int index )
   {
      return _rxDeff[index];
   }
    
   /**
    * Gets the Effective Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Effective Date or the specified default value.
    */
   public final Date getrxDeff( int index, Date defaultValue )
   {
      return _rxDeff[index] == null ? defaultValue : _rxDeff[index];
   }
    
   /**
    * Gets the array of Effective Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Effective Date values.
    */
   public final Date[] getrxDeffArray()
   {
      return _rxDeff;
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
    * Gets the Address Country field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Country or null.
    */
   public final String getAddrCntry( int index )
   {
      return _AddrCntry[index];
   }
    
   /**
    * Gets the Address Country field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Country or the specified default value.
    */
   public final String getAddrCntry( int index, String defaultValue )
   {
      return _AddrCntry[index] == null ? defaultValue : _AddrCntry[index];
   }
    
   /**
    * Gets the array of Address Country fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Country values.
    */
   public final String[] getAddrCntryArray()
   {
      return _AddrCntry;
   }
    
   /**
    * Gets the Address Postal field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Postal or null.
    */
   public final String getAddrPSTL( int index )
   {
      return _AddrPSTL[index];
   }
    
   /**
    * Gets the Address Postal field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Postal or the specified default value.
    */
   public final String getAddrPSTL( int index, String defaultValue )
   {
      return _AddrPSTL[index] == null ? defaultValue : _AddrPSTL[index];
   }
    
   /**
    * Gets the array of Address Postal fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Postal values.
    */
   public final String[] getAddrPSTLArray()
   {
      return _AddrPSTL;
   }
    
   /**
    * Gets the User Pay Entity Address field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the User Pay Entity Address or null.
    */
   public final Boolean getUserPayEntityAddr( int index )
   {
      return _UserPayEntityAddr[index];
   }
    
   /**
    * Gets the User Pay Entity Address field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the User Pay Entity Address or the specified default value.
    */
   public final boolean getUserPayEntityAddr( int index, boolean defaultValue )
   {
      return _UserPayEntityAddr[index] == null ? defaultValue : _UserPayEntityAddr[index].booleanValue();
   }
    
   /**
    * Gets the array of User Pay Entity Address fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of User Pay Entity Address values.
    */
   public final Boolean[] getUserPayEntityAddrArray()
   {
      return _UserPayEntityAddr;
   }
    
   /**
    * Gets the Trade Pay Instruct Version field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Trade Pay Instruct Version or null.
    */
   public final Integer getTrdPayInstrVersion( int index )
   {
      return _TrdPayInstrVersion[index];
   }
    
   /**
    * Gets the Trade Pay Instruct Version field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Trade Pay Instruct Version or the specified default value.
    */
   public final int getTrdPayInstrVersion( int index, int defaultValue )
   {
      return _TrdPayInstrVersion[index] == null ? defaultValue : _TrdPayInstrVersion[index].intValue();
   }
    
   /**
    * Gets the array of Trade Pay Instruct Version fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Trade Pay Instruct Version values.
    */
   public final Integer[] getTrdPayInstrVersionArray()
   {
      return _TrdPayInstrVersion;
   }
    
   /**
    * Gets the Trade Pay Instruct Recid field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Trade Pay Instruct Recid or null.
    */
   public final Integer getTrdPayInstrRecid( int index )
   {
      return _TrdPayInstrRecid[index];
   }
    
   /**
    * Gets the Trade Pay Instruct Recid field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Trade Pay Instruct Recid or the specified default value.
    */
   public final int getTrdPayInstrRecid( int index, int defaultValue )
   {
      return _TrdPayInstrRecid[index] == null ? defaultValue : _TrdPayInstrRecid[index].intValue();
   }
    
   /**
    * Gets the array of Trade Pay Instruct Recid fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Trade Pay Instruct Recid values.
    */
   public final Integer[] getTrdPayInstrRecidArray()
   {
      return _TrdPayInstrRecid;
   }
    
   /**
    * Gets the Date Created field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Date Created or null.
    */
   public final Date getProcessDate( int index )
   {
      return _ProcessDate[index];
   }
    
   /**
    * Gets the Date Created field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Date Created or the specified default value.
    */
   public final Date getProcessDate( int index, Date defaultValue )
   {
      return _ProcessDate[index] == null ? defaultValue : _ProcessDate[index];
   }
    
   /**
    * Gets the array of Date Created fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Date Created values.
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
    * Gets the Date Modified field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Date Modified or null.
    */
   public final Date getModDate( int index )
   {
      return _ModDate[index];
   }
    
   /**
    * Gets the Date Modified field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Date Modified or the specified default value.
    */
   public final Date getModDate( int index, Date defaultValue )
   {
      return _ModDate[index] == null ? defaultValue : _ModDate[index];
   }
    
   /**
    * Gets the array of Date Modified fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Date Modified values.
    */
   public final Date[] getModDateArray()
   {
      return _ModDate;
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
    * Gets the Reinvest Account Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reinvest Account Number or null.
    */
   public final String getReinvAccount( int index )
   {
      return _ReinvAccount[index];
   }
    
   /**
    * Gets the Reinvest Account Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reinvest Account Number or the specified default value.
    */
   public final String getReinvAccount( int index, String defaultValue )
   {
      return _ReinvAccount[index] == null ? defaultValue : _ReinvAccount[index];
   }
    
   /**
    * Gets the array of Reinvest Account Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reinvest Account Number values.
    */
   public final String[] getReinvAccountArray()
   {
      return _ReinvAccount;
   }
    
   /**
    * Gets the Payment Instructions ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Payment Instructions ID or null.
    */
   public final String getPayInstructId( int index )
   {
      return _PayInstructId[index];
   }
    
   /**
    * Gets the Payment Instructions ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Payment Instructions ID or the specified default value.
    */
   public final String getPayInstructId( int index, String defaultValue )
   {
      return _PayInstructId[index] == null ? defaultValue : _PayInstructId[index];
   }
    
   /**
    * Gets the array of Payment Instructions ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Payment Instructions ID values.
    */
   public final String[] getPayInstructIdArray()
   {
      return _PayInstructId;
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
      _OthPaymentForExist = responseBuffer.decodeBoolean(responseBuffer.getNextField());
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _rxPaymentFor = resizeArray( _rxPaymentFor, _RepeatCount );
      _PayType = resizeArray( _PayType, _RepeatCount );
      _PayMethod = resizeArray( _PayMethod, _RepeatCount );
      _ACHProcessor = resizeArray( _ACHProcessor, _RepeatCount );
      _ConsolType = resizeArray( _ConsolType, _RepeatCount );
      _DirectTo = resizeArray( _DirectTo, _RepeatCount );
      _BankCharge = resizeArray( _BankCharge, _RepeatCount );
      _CurrOption = resizeArray( _CurrOption, _RepeatCount );
      _Currency = resizeArray( _Currency, _RepeatCount );
      _rxDeff = resizeArray( _rxDeff, _RepeatCount );
      _StopDate = resizeArray( _StopDate, _RepeatCount );
      _AddrLine1 = resizeArray( _AddrLine1, _RepeatCount );
      _AddrLine2 = resizeArray( _AddrLine2, _RepeatCount );
      _AddrLine3 = resizeArray( _AddrLine3, _RepeatCount );
      _AddrLine4 = resizeArray( _AddrLine4, _RepeatCount );
      _AddrLine5 = resizeArray( _AddrLine5, _RepeatCount );
      _AddrCntry = resizeArray( _AddrCntry, _RepeatCount );
      _AddrPSTL = resizeArray( _AddrPSTL, _RepeatCount );
      _UserPayEntityAddr = resizeArray( _UserPayEntityAddr, _RepeatCount );
      _TrdPayInstrVersion = resizeArray( _TrdPayInstrVersion, _RepeatCount );
      _TrdPayInstrRecid = resizeArray( _TrdPayInstrRecid, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _UserName = resizeArray( _UserName, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _ModUser = resizeArray( _ModUser, _RepeatCount );
      _ReinvAccount = resizeArray( _ReinvAccount, _RepeatCount );
      _PayInstructId = resizeArray( _PayInstructId, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxPaymentFor[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PayType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PayMethod[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ACHProcessor[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ConsolType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DirectTo[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankCharge[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CurrOption[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Currency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxDeff[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _StopDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _AddrLine1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine3[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine4[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine5[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrCntry[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrPSTL[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _UserPayEntityAddr[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TrdPayInstrVersion[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _TrdPayInstrRecid[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _UserName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ModUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ReinvAccount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PayInstructId[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
