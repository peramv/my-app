
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Trade Adjust Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/TradeAdjustInq.doc">TradeAdjustInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class TradeAdjustInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Transaction Number linked to trans-detl to be cancelled member array.
    */
   private Integer[] _RxTransNum = null;
   
   /**
    * Reversal Code as defined in Misc-info GroupCode RV member array.
    */
   private String[] _RVCD = null;
   
   /**
    * Should the cancelled transaction to be reported on statements member array.
    */
   private Boolean[] _ReportOnStmt = null;
   
   /**
    * Accountability code for cancelled transactions as defined in misc-info GroupCode AZ member array.
    */
   private String[] _AccountableCode = null;
   
   /**
    * Should a confirmation be produced member array.
    */
   private Boolean[] _Confirmation = null;
   
   /**
    * Does the cheque need to be cancelled member array.
    */
   private Boolean[] _CancelCheque = null;
   
   /**
    * Remarks for the cancelled transaction member array.
    */
   private String[] _Remarks_Line_1 = null;
   
   /**
    * Remarks for the cancelled transaction member array.
    */
   private String[] _Remarks_Line_2 = null;
   
   /**
    * Remarks for the cancelled transaction member array.
    */
   private String[] _Remarks_Line_3 = null;
   
   /**
    * Batch Number member array.
    */
   private String[] _BTBatch = null;
   
   /**
    * The trace number linked to the transaction and batch member array.
    */
   private Integer[] _BTTrace = null;
   
   /**
    * Transaction Type member array.
    */
   private String[] _TransType = null;
   
   /**
    * Enter the code applicable to the status of  the record. Defined in misc-info groupcode SV member array.
    */
   private String[] _rxTransStat = null;
   
   /**
    * User Name member array.
    */
   private String[] _UserName = null;
   
   /**
    * Modified by member array.
    */
   private String[] _ModUser = null;
   
   /**
    * Modification Date member array.
    */
   private Date[] _ModDate = null;
   
   /**
    * Verified by Whom member array.
    */
   private String[] _VerifiedBy = null;
   
   /**
    * Verification Date member array.
    */
   private Date[] _VerifyDate = null;
   
   /**
    * Process Date member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * TransID linked to trans-detl member array.
    */
   private String[] _TransID = null;
   
   /**
    * Version number of Trade adjust member array.
    */
   private Integer[] _TradeAdjVersion = null;
   
   /**
    * Permission level of user, 1 indicates user can update, 2 user can update and verify member array.
    */
   private String[] _ModPerm = null;
   
   /**
    * Cancellation Type member array.
    */
   private String[] _rxAdjustType = null;
   
   /**
    * Effective Date of Trade member array.
    */
   private Date[] _rxTradeDate = null;
   
   /**
    * Fund Code member array.
    */
   private String[] _rxFundCode = null;
   
   /**
    * Class Code member array.
    */
   private String[] _rxClassCode = null;
   
   /**
    * Inidcates if rebook is part of cancellation request member array.
    */
   private Boolean[] _Rebook = null;
   
   /**
    * ISIN Number member array.
    */
   private String[] _FundISIN = null;
   
   /**
    * WKN Number member array.
    */
   private String[] _FundWKN = null;
   
   /**
    * Trade Adjust ID member array.
    */
   private String[] _rxTradeAdjustID = null;
   
   /**
    * MCH File member array.
    */
   private String[] _MCHFile = null;
   
   /**
    * Sec Recon File member array.
    */
   private String[] _SecRecFile = null;
   
   /**
    * Rbk MCH File member array.
    */
   private String[] _RbkMCHFile = null;
   
   /**
    * Rbk Sec Rec File member array.
    */
   private String[] _RbkSecRecFile = null;
   
   /**
    * Flag indicating if a transaction is excluded from NSM file member array.
    */
   private String[] _ESGSettle = null;
   
   /**
    * Refund Pay Type member array.
    */
   private String[] _RefundPayType = null;
   
   /**
    * Refund Amount Option member array.
    */
   private String[] _RefundAmountOption = null;
   
   /**
    * Event Receipt Date member array.
    */
   private Date[] _EventReceiptDate = null;
   
   /**
    * Event Receipt Time member array.
    */
   private String[] _EventReceiptTime = null;
   

   /**
    * Constructs the TradeAdjustInqView object.
    * 
    */
   public TradeAdjustInqView()
   {
      super ( new TradeAdjustInqRequest() );
   }

   /**
    * Constructs the TradeAdjustInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public TradeAdjustInqView( String hostEncoding )
   {
      super ( new TradeAdjustInqRequest( hostEncoding ) );
   }

   /**
    * Gets the TradeAdjustInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The TradeAdjustInqRequest object.
    */
   public final TradeAdjustInqRequest getRequest()
   {
      return (TradeAdjustInqRequest)getIFastRequest();
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
    * Gets the Transaction Number linked to trans-detl to be cancelled field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transaction Number linked to trans-detl to be cancelled or null.
    */
   public final Integer getRxTransNum( int index )
   {
      return _RxTransNum[index];
   }
    
   /**
    * Gets the Transaction Number linked to trans-detl to be cancelled field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transaction Number linked to trans-detl to be cancelled or the specified default value.
    */
   public final int getRxTransNum( int index, int defaultValue )
   {
      return _RxTransNum[index] == null ? defaultValue : _RxTransNum[index].intValue();
   }
    
   /**
    * Gets the array of Transaction Number linked to trans-detl to be cancelled fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transaction Number linked to trans-detl to be cancelled values.
    */
   public final Integer[] getRxTransNumArray()
   {
      return _RxTransNum;
   }
    
   /**
    * Gets the Reversal Code as defined in Misc-info GroupCode RV field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reversal Code as defined in Misc-info GroupCode RV or null.
    */
   public final String getRVCD( int index )
   {
      return _RVCD[index];
   }
    
   /**
    * Gets the Reversal Code as defined in Misc-info GroupCode RV field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reversal Code as defined in Misc-info GroupCode RV or the specified default value.
    */
   public final String getRVCD( int index, String defaultValue )
   {
      return _RVCD[index] == null ? defaultValue : _RVCD[index];
   }
    
   /**
    * Gets the array of Reversal Code as defined in Misc-info GroupCode RV fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reversal Code as defined in Misc-info GroupCode RV values.
    */
   public final String[] getRVCDArray()
   {
      return _RVCD;
   }
    
   /**
    * Gets the Should the cancelled transaction to be reported on statements field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Should the cancelled transaction to be reported on statements or null.
    */
   public final Boolean getReportOnStmt( int index )
   {
      return _ReportOnStmt[index];
   }
    
   /**
    * Gets the Should the cancelled transaction to be reported on statements field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Should the cancelled transaction to be reported on statements or the specified default value.
    */
   public final boolean getReportOnStmt( int index, boolean defaultValue )
   {
      return _ReportOnStmt[index] == null ? defaultValue : _ReportOnStmt[index].booleanValue();
   }
    
   /**
    * Gets the array of Should the cancelled transaction to be reported on statements fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Should the cancelled transaction to be reported on statements values.
    */
   public final Boolean[] getReportOnStmtArray()
   {
      return _ReportOnStmt;
   }
    
   /**
    * Gets the Accountability code for cancelled transactions as defined in misc-info GroupCode AZ field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Accountability code for cancelled transactions as defined in misc-info GroupCode AZ or null.
    */
   public final String getAccountableCode( int index )
   {
      return _AccountableCode[index];
   }
    
   /**
    * Gets the Accountability code for cancelled transactions as defined in misc-info GroupCode AZ field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Accountability code for cancelled transactions as defined in misc-info GroupCode AZ or the specified default value.
    */
   public final String getAccountableCode( int index, String defaultValue )
   {
      return _AccountableCode[index] == null ? defaultValue : _AccountableCode[index];
   }
    
   /**
    * Gets the array of Accountability code for cancelled transactions as defined in misc-info GroupCode AZ fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Accountability code for cancelled transactions as defined in misc-info GroupCode AZ values.
    */
   public final String[] getAccountableCodeArray()
   {
      return _AccountableCode;
   }
    
   /**
    * Gets the Should a confirmation be produced field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Should a confirmation be produced or null.
    */
   public final Boolean getConfirmation( int index )
   {
      return _Confirmation[index];
   }
    
   /**
    * Gets the Should a confirmation be produced field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Should a confirmation be produced or the specified default value.
    */
   public final boolean getConfirmation( int index, boolean defaultValue )
   {
      return _Confirmation[index] == null ? defaultValue : _Confirmation[index].booleanValue();
   }
    
   /**
    * Gets the array of Should a confirmation be produced fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Should a confirmation be produced values.
    */
   public final Boolean[] getConfirmationArray()
   {
      return _Confirmation;
   }
    
   /**
    * Gets the Does the cheque need to be cancelled field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Does the cheque need to be cancelled or null.
    */
   public final Boolean getCancelCheque( int index )
   {
      return _CancelCheque[index];
   }
    
   /**
    * Gets the Does the cheque need to be cancelled field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Does the cheque need to be cancelled or the specified default value.
    */
   public final boolean getCancelCheque( int index, boolean defaultValue )
   {
      return _CancelCheque[index] == null ? defaultValue : _CancelCheque[index].booleanValue();
   }
    
   /**
    * Gets the array of Does the cheque need to be cancelled fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Does the cheque need to be cancelled values.
    */
   public final Boolean[] getCancelChequeArray()
   {
      return _CancelCheque;
   }
    
   /**
    * Gets the Remarks for the cancelled transaction field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Remarks for the cancelled transaction or null.
    */
   public final String getRemarks_Line_1( int index )
   {
      return _Remarks_Line_1[index];
   }
    
   /**
    * Gets the Remarks for the cancelled transaction field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Remarks for the cancelled transaction or the specified default value.
    */
   public final String getRemarks_Line_1( int index, String defaultValue )
   {
      return _Remarks_Line_1[index] == null ? defaultValue : _Remarks_Line_1[index];
   }
    
   /**
    * Gets the array of Remarks for the cancelled transaction fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Remarks for the cancelled transaction values.
    */
   public final String[] getRemarks_Line_1Array()
   {
      return _Remarks_Line_1;
   }
    
   /**
    * Gets the Remarks for the cancelled transaction field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Remarks for the cancelled transaction or null.
    */
   public final String getRemarks_Line_2( int index )
   {
      return _Remarks_Line_2[index];
   }
    
   /**
    * Gets the Remarks for the cancelled transaction field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Remarks for the cancelled transaction or the specified default value.
    */
   public final String getRemarks_Line_2( int index, String defaultValue )
   {
      return _Remarks_Line_2[index] == null ? defaultValue : _Remarks_Line_2[index];
   }
    
   /**
    * Gets the array of Remarks for the cancelled transaction fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Remarks for the cancelled transaction values.
    */
   public final String[] getRemarks_Line_2Array()
   {
      return _Remarks_Line_2;
   }
    
   /**
    * Gets the Remarks for the cancelled transaction field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Remarks for the cancelled transaction or null.
    */
   public final String getRemarks_Line_3( int index )
   {
      return _Remarks_Line_3[index];
   }
    
   /**
    * Gets the Remarks for the cancelled transaction field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Remarks for the cancelled transaction or the specified default value.
    */
   public final String getRemarks_Line_3( int index, String defaultValue )
   {
      return _Remarks_Line_3[index] == null ? defaultValue : _Remarks_Line_3[index];
   }
    
   /**
    * Gets the array of Remarks for the cancelled transaction fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Remarks for the cancelled transaction values.
    */
   public final String[] getRemarks_Line_3Array()
   {
      return _Remarks_Line_3;
   }
    
   /**
    * Gets the Batch Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Batch Number or null.
    */
   public final String getBTBatch( int index )
   {
      return _BTBatch[index];
   }
    
   /**
    * Gets the Batch Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Batch Number or the specified default value.
    */
   public final String getBTBatch( int index, String defaultValue )
   {
      return _BTBatch[index] == null ? defaultValue : _BTBatch[index];
   }
    
   /**
    * Gets the array of Batch Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Batch Number values.
    */
   public final String[] getBTBatchArray()
   {
      return _BTBatch;
   }
    
   /**
    * Gets the The trace number linked to the transaction and batch field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the The trace number linked to the transaction and batch or null.
    */
   public final Integer getBTTrace( int index )
   {
      return _BTTrace[index];
   }
    
   /**
    * Gets the The trace number linked to the transaction and batch field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the The trace number linked to the transaction and batch or the specified default value.
    */
   public final int getBTTrace( int index, int defaultValue )
   {
      return _BTTrace[index] == null ? defaultValue : _BTTrace[index].intValue();
   }
    
   /**
    * Gets the array of The trace number linked to the transaction and batch fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of The trace number linked to the transaction and batch values.
    */
   public final Integer[] getBTTraceArray()
   {
      return _BTTrace;
   }
    
   /**
    * Gets the Transaction Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transaction Type or null.
    */
   public final String getTransType( int index )
   {
      return _TransType[index];
   }
    
   /**
    * Gets the Transaction Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transaction Type or the specified default value.
    */
   public final String getTransType( int index, String defaultValue )
   {
      return _TransType[index] == null ? defaultValue : _TransType[index];
   }
    
   /**
    * Gets the array of Transaction Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transaction Type values.
    */
   public final String[] getTransTypeArray()
   {
      return _TransType;
   }
    
   /**
    * Gets the Enter the code applicable to the status of  the record. Defined in misc-info groupcode SV field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Enter the code applicable to the status of  the record. Defined in misc-info groupcode SV or null.
    */
   public final String getrxTransStat( int index )
   {
      return _rxTransStat[index];
   }
    
   /**
    * Gets the Enter the code applicable to the status of  the record. Defined in misc-info groupcode SV field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Enter the code applicable to the status of  the record. Defined in misc-info groupcode SV or the specified default value.
    */
   public final String getrxTransStat( int index, String defaultValue )
   {
      return _rxTransStat[index] == null ? defaultValue : _rxTransStat[index];
   }
    
   /**
    * Gets the array of Enter the code applicable to the status of  the record. Defined in misc-info groupcode SV fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Enter the code applicable to the status of  the record. Defined in misc-info groupcode SV values.
    */
   public final String[] getrxTransStatArray()
   {
      return _rxTransStat;
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
    * Gets the Modified by field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Modified by or null.
    */
   public final String getModUser( int index )
   {
      return _ModUser[index];
   }
    
   /**
    * Gets the Modified by field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Modified by or the specified default value.
    */
   public final String getModUser( int index, String defaultValue )
   {
      return _ModUser[index] == null ? defaultValue : _ModUser[index];
   }
    
   /**
    * Gets the array of Modified by fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Modified by values.
    */
   public final String[] getModUserArray()
   {
      return _ModUser;
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
    * Gets the Verified by Whom field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Verified by Whom or null.
    */
   public final String getVerifiedBy( int index )
   {
      return _VerifiedBy[index];
   }
    
   /**
    * Gets the Verified by Whom field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Verified by Whom or the specified default value.
    */
   public final String getVerifiedBy( int index, String defaultValue )
   {
      return _VerifiedBy[index] == null ? defaultValue : _VerifiedBy[index];
   }
    
   /**
    * Gets the array of Verified by Whom fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Verified by Whom values.
    */
   public final String[] getVerifiedByArray()
   {
      return _VerifiedBy;
   }
    
   /**
    * Gets the Verification Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Verification Date or null.
    */
   public final Date getVerifyDate( int index )
   {
      return _VerifyDate[index];
   }
    
   /**
    * Gets the Verification Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Verification Date or the specified default value.
    */
   public final Date getVerifyDate( int index, Date defaultValue )
   {
      return _VerifyDate[index] == null ? defaultValue : _VerifyDate[index];
   }
    
   /**
    * Gets the array of Verification Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Verification Date values.
    */
   public final Date[] getVerifyDateArray()
   {
      return _VerifyDate;
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
    * Gets the TransID linked to trans-detl field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the TransID linked to trans-detl or null.
    */
   public final String getTransID( int index )
   {
      return _TransID[index];
   }
    
   /**
    * Gets the TransID linked to trans-detl field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the TransID linked to trans-detl or the specified default value.
    */
   public final String getTransID( int index, String defaultValue )
   {
      return _TransID[index] == null ? defaultValue : _TransID[index];
   }
    
   /**
    * Gets the array of TransID linked to trans-detl fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of TransID linked to trans-detl values.
    */
   public final String[] getTransIDArray()
   {
      return _TransID;
   }
    
   /**
    * Gets the Version number of Trade adjust field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Version number of Trade adjust or null.
    */
   public final Integer getTradeAdjVersion( int index )
   {
      return _TradeAdjVersion[index];
   }
    
   /**
    * Gets the Version number of Trade adjust field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Version number of Trade adjust or the specified default value.
    */
   public final int getTradeAdjVersion( int index, int defaultValue )
   {
      return _TradeAdjVersion[index] == null ? defaultValue : _TradeAdjVersion[index].intValue();
   }
    
   /**
    * Gets the array of Version number of Trade adjust fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Version number of Trade adjust values.
    */
   public final Integer[] getTradeAdjVersionArray()
   {
      return _TradeAdjVersion;
   }
    
   /**
    * Gets the Permission level of user, 1 indicates user can update, 2 user can update and verify field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Permission level of user, 1 indicates user can update, 2 user can update and verify or null.
    */
   public final String getModPerm( int index )
   {
      return _ModPerm[index];
   }
    
   /**
    * Gets the Permission level of user, 1 indicates user can update, 2 user can update and verify field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Permission level of user, 1 indicates user can update, 2 user can update and verify or the specified default value.
    */
   public final String getModPerm( int index, String defaultValue )
   {
      return _ModPerm[index] == null ? defaultValue : _ModPerm[index];
   }
    
   /**
    * Gets the array of Permission level of user, 1 indicates user can update, 2 user can update and verify fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Permission level of user, 1 indicates user can update, 2 user can update and verify values.
    */
   public final String[] getModPermArray()
   {
      return _ModPerm;
   }
    
   /**
    * Gets the Cancellation Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Cancellation Type or null.
    */
   public final String getrxAdjustType( int index )
   {
      return _rxAdjustType[index];
   }
    
   /**
    * Gets the Cancellation Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Cancellation Type or the specified default value.
    */
   public final String getrxAdjustType( int index, String defaultValue )
   {
      return _rxAdjustType[index] == null ? defaultValue : _rxAdjustType[index];
   }
    
   /**
    * Gets the array of Cancellation Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Cancellation Type values.
    */
   public final String[] getrxAdjustTypeArray()
   {
      return _rxAdjustType;
   }
    
   /**
    * Gets the Effective Date of Trade field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Effective Date of Trade or null.
    */
   public final Date getrxTradeDate( int index )
   {
      return _rxTradeDate[index];
   }
    
   /**
    * Gets the Effective Date of Trade field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Effective Date of Trade or the specified default value.
    */
   public final Date getrxTradeDate( int index, Date defaultValue )
   {
      return _rxTradeDate[index] == null ? defaultValue : _rxTradeDate[index];
   }
    
   /**
    * Gets the array of Effective Date of Trade fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Effective Date of Trade values.
    */
   public final Date[] getrxTradeDateArray()
   {
      return _rxTradeDate;
   }
    
   /**
    * Gets the Fund Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Code or null.
    */
   public final String getrxFundCode( int index )
   {
      return _rxFundCode[index];
   }
    
   /**
    * Gets the Fund Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Code or the specified default value.
    */
   public final String getrxFundCode( int index, String defaultValue )
   {
      return _rxFundCode[index] == null ? defaultValue : _rxFundCode[index];
   }
    
   /**
    * Gets the array of Fund Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Code values.
    */
   public final String[] getrxFundCodeArray()
   {
      return _rxFundCode;
   }
    
   /**
    * Gets the Class Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Class Code or null.
    */
   public final String getrxClassCode( int index )
   {
      return _rxClassCode[index];
   }
    
   /**
    * Gets the Class Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Class Code or the specified default value.
    */
   public final String getrxClassCode( int index, String defaultValue )
   {
      return _rxClassCode[index] == null ? defaultValue : _rxClassCode[index];
   }
    
   /**
    * Gets the array of Class Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Class Code values.
    */
   public final String[] getrxClassCodeArray()
   {
      return _rxClassCode;
   }
    
   /**
    * Gets the Inidcates if rebook is part of cancellation request field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Inidcates if rebook is part of cancellation request or null.
    */
   public final Boolean getRebook( int index )
   {
      return _Rebook[index];
   }
    
   /**
    * Gets the Inidcates if rebook is part of cancellation request field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Inidcates if rebook is part of cancellation request or the specified default value.
    */
   public final boolean getRebook( int index, boolean defaultValue )
   {
      return _Rebook[index] == null ? defaultValue : _Rebook[index].booleanValue();
   }
    
   /**
    * Gets the array of Inidcates if rebook is part of cancellation request fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Inidcates if rebook is part of cancellation request values.
    */
   public final Boolean[] getRebookArray()
   {
      return _Rebook;
   }
    
   /**
    * Gets the ISIN Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ISIN Number or null.
    */
   public final String getFundISIN( int index )
   {
      return _FundISIN[index];
   }
    
   /**
    * Gets the ISIN Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ISIN Number or the specified default value.
    */
   public final String getFundISIN( int index, String defaultValue )
   {
      return _FundISIN[index] == null ? defaultValue : _FundISIN[index];
   }
    
   /**
    * Gets the array of ISIN Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ISIN Number values.
    */
   public final String[] getFundISINArray()
   {
      return _FundISIN;
   }
    
   /**
    * Gets the WKN Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the WKN Number or null.
    */
   public final String getFundWKN( int index )
   {
      return _FundWKN[index];
   }
    
   /**
    * Gets the WKN Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the WKN Number or the specified default value.
    */
   public final String getFundWKN( int index, String defaultValue )
   {
      return _FundWKN[index] == null ? defaultValue : _FundWKN[index];
   }
    
   /**
    * Gets the array of WKN Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of WKN Number values.
    */
   public final String[] getFundWKNArray()
   {
      return _FundWKN;
   }
    
   /**
    * Gets the Trade Adjust ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Trade Adjust ID or null.
    */
   public final String getrxTradeAdjustID( int index )
   {
      return _rxTradeAdjustID[index];
   }
    
   /**
    * Gets the Trade Adjust ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Trade Adjust ID or the specified default value.
    */
   public final String getrxTradeAdjustID( int index, String defaultValue )
   {
      return _rxTradeAdjustID[index] == null ? defaultValue : _rxTradeAdjustID[index];
   }
    
   /**
    * Gets the array of Trade Adjust ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Trade Adjust ID values.
    */
   public final String[] getrxTradeAdjustIDArray()
   {
      return _rxTradeAdjustID;
   }
    
   /**
    * Gets the MCH File field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the MCH File or null.
    */
   public final String getMCHFile( int index )
   {
      return _MCHFile[index];
   }
    
   /**
    * Gets the MCH File field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the MCH File or the specified default value.
    */
   public final String getMCHFile( int index, String defaultValue )
   {
      return _MCHFile[index] == null ? defaultValue : _MCHFile[index];
   }
    
   /**
    * Gets the array of MCH File fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of MCH File values.
    */
   public final String[] getMCHFileArray()
   {
      return _MCHFile;
   }
    
   /**
    * Gets the Sec Recon File field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Sec Recon File or null.
    */
   public final String getSecRecFile( int index )
   {
      return _SecRecFile[index];
   }
    
   /**
    * Gets the Sec Recon File field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Sec Recon File or the specified default value.
    */
   public final String getSecRecFile( int index, String defaultValue )
   {
      return _SecRecFile[index] == null ? defaultValue : _SecRecFile[index];
   }
    
   /**
    * Gets the array of Sec Recon File fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Sec Recon File values.
    */
   public final String[] getSecRecFileArray()
   {
      return _SecRecFile;
   }
    
   /**
    * Gets the Rbk MCH File field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Rbk MCH File or null.
    */
   public final String getRbkMCHFile( int index )
   {
      return _RbkMCHFile[index];
   }
    
   /**
    * Gets the Rbk MCH File field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Rbk MCH File or the specified default value.
    */
   public final String getRbkMCHFile( int index, String defaultValue )
   {
      return _RbkMCHFile[index] == null ? defaultValue : _RbkMCHFile[index];
   }
    
   /**
    * Gets the array of Rbk MCH File fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Rbk MCH File values.
    */
   public final String[] getRbkMCHFileArray()
   {
      return _RbkMCHFile;
   }
    
   /**
    * Gets the Rbk Sec Rec File field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Rbk Sec Rec File or null.
    */
   public final String getRbkSecRecFile( int index )
   {
      return _RbkSecRecFile[index];
   }
    
   /**
    * Gets the Rbk Sec Rec File field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Rbk Sec Rec File or the specified default value.
    */
   public final String getRbkSecRecFile( int index, String defaultValue )
   {
      return _RbkSecRecFile[index] == null ? defaultValue : _RbkSecRecFile[index];
   }
    
   /**
    * Gets the array of Rbk Sec Rec File fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Rbk Sec Rec File values.
    */
   public final String[] getRbkSecRecFileArray()
   {
      return _RbkSecRecFile;
   }
    
   /**
    * Gets the Flag indicating if a transaction is excluded from NSM file field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicating if a transaction is excluded from NSM file or null.
    */
   public final String getESGSettle( int index )
   {
      return _ESGSettle[index];
   }
    
   /**
    * Gets the Flag indicating if a transaction is excluded from NSM file field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if a transaction is excluded from NSM file or the specified default value.
    */
   public final String getESGSettle( int index, String defaultValue )
   {
      return _ESGSettle[index] == null ? defaultValue : _ESGSettle[index];
   }
    
   /**
    * Gets the array of Flag indicating if a transaction is excluded from NSM file fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicating if a transaction is excluded from NSM file values.
    */
   public final String[] getESGSettleArray()
   {
      return _ESGSettle;
   }
    
   /**
    * Gets the Refund Pay Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Refund Pay Type or null.
    */
   public final String getRefundPayType( int index )
   {
      return _RefundPayType[index];
   }
    
   /**
    * Gets the Refund Pay Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Refund Pay Type or the specified default value.
    */
   public final String getRefundPayType( int index, String defaultValue )
   {
      return _RefundPayType[index] == null ? defaultValue : _RefundPayType[index];
   }
    
   /**
    * Gets the array of Refund Pay Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Refund Pay Type values.
    */
   public final String[] getRefundPayTypeArray()
   {
      return _RefundPayType;
   }
    
   /**
    * Gets the Refund Amount Option field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Refund Amount Option or null.
    */
   public final String getRefundAmountOption( int index )
   {
      return _RefundAmountOption[index];
   }
    
   /**
    * Gets the Refund Amount Option field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Refund Amount Option or the specified default value.
    */
   public final String getRefundAmountOption( int index, String defaultValue )
   {
      return _RefundAmountOption[index] == null ? defaultValue : _RefundAmountOption[index];
   }
    
   /**
    * Gets the array of Refund Amount Option fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Refund Amount Option values.
    */
   public final String[] getRefundAmountOptionArray()
   {
      return _RefundAmountOption;
   }
    
   /**
    * Gets the Event Receipt Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Event Receipt Date or null.
    */
   public final Date getEventReceiptDate( int index )
   {
      return _EventReceiptDate[index];
   }
    
   /**
    * Gets the Event Receipt Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Event Receipt Date or the specified default value.
    */
   public final Date getEventReceiptDate( int index, Date defaultValue )
   {
      return _EventReceiptDate[index] == null ? defaultValue : _EventReceiptDate[index];
   }
    
   /**
    * Gets the array of Event Receipt Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Event Receipt Date values.
    */
   public final Date[] getEventReceiptDateArray()
   {
      return _EventReceiptDate;
   }
    
   /**
    * Gets the Event Receipt Time field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Event Receipt Time or null.
    */
   public final String getEventReceiptTime( int index )
   {
      return _EventReceiptTime[index];
   }
    
   /**
    * Gets the Event Receipt Time field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Event Receipt Time or the specified default value.
    */
   public final String getEventReceiptTime( int index, String defaultValue )
   {
      return _EventReceiptTime[index] == null ? defaultValue : _EventReceiptTime[index];
   }
    
   /**
    * Gets the array of Event Receipt Time fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Event Receipt Time values.
    */
   public final String[] getEventReceiptTimeArray()
   {
      return _EventReceiptTime;
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
      
      _RxTransNum = resizeArray( _RxTransNum, _RepeatCount );
      _RVCD = resizeArray( _RVCD, _RepeatCount );
      _ReportOnStmt = resizeArray( _ReportOnStmt, _RepeatCount );
      _AccountableCode = resizeArray( _AccountableCode, _RepeatCount );
      _Confirmation = resizeArray( _Confirmation, _RepeatCount );
      _CancelCheque = resizeArray( _CancelCheque, _RepeatCount );
      _Remarks_Line_1 = resizeArray( _Remarks_Line_1, _RepeatCount );
      _Remarks_Line_2 = resizeArray( _Remarks_Line_2, _RepeatCount );
      _Remarks_Line_3 = resizeArray( _Remarks_Line_3, _RepeatCount );
      _BTBatch = resizeArray( _BTBatch, _RepeatCount );
      _BTTrace = resizeArray( _BTTrace, _RepeatCount );
      _TransType = resizeArray( _TransType, _RepeatCount );
      _rxTransStat = resizeArray( _rxTransStat, _RepeatCount );
      _UserName = resizeArray( _UserName, _RepeatCount );
      _ModUser = resizeArray( _ModUser, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _VerifiedBy = resizeArray( _VerifiedBy, _RepeatCount );
      _VerifyDate = resizeArray( _VerifyDate, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _TransID = resizeArray( _TransID, _RepeatCount );
      _TradeAdjVersion = resizeArray( _TradeAdjVersion, _RepeatCount );
      _ModPerm = resizeArray( _ModPerm, _RepeatCount );
      _rxAdjustType = resizeArray( _rxAdjustType, _RepeatCount );
      _rxTradeDate = resizeArray( _rxTradeDate, _RepeatCount );
      _rxFundCode = resizeArray( _rxFundCode, _RepeatCount );
      _rxClassCode = resizeArray( _rxClassCode, _RepeatCount );
      _Rebook = resizeArray( _Rebook, _RepeatCount );
      _FundISIN = resizeArray( _FundISIN, _RepeatCount );
      _FundWKN = resizeArray( _FundWKN, _RepeatCount );
      _rxTradeAdjustID = resizeArray( _rxTradeAdjustID, _RepeatCount );
      _MCHFile = resizeArray( _MCHFile, _RepeatCount );
      _SecRecFile = resizeArray( _SecRecFile, _RepeatCount );
      _RbkMCHFile = resizeArray( _RbkMCHFile, _RepeatCount );
      _RbkSecRecFile = resizeArray( _RbkSecRecFile, _RepeatCount );
      _ESGSettle = resizeArray( _ESGSettle, _RepeatCount );
      _RefundPayType = resizeArray( _RefundPayType, _RepeatCount );
      _RefundAmountOption = resizeArray( _RefundAmountOption, _RepeatCount );
      _EventReceiptDate = resizeArray( _EventReceiptDate, _RepeatCount );
      _EventReceiptTime = resizeArray( _EventReceiptTime, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _RxTransNum[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _RVCD[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ReportOnStmt[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _AccountableCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Confirmation[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _CancelCheque[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _Remarks_Line_1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Remarks_Line_2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Remarks_Line_3[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BTBatch[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BTTrace[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _TransType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxTransStat[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _UserName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _VerifiedBy[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _VerifyDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _TransID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TradeAdjVersion[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _ModPerm[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxAdjustType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxTradeDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _rxFundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxClassCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Rebook[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _FundISIN[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundWKN[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxTradeAdjustID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MCHFile[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SecRecFile[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RbkMCHFile[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RbkSecRecFile[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ESGSettle[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RefundPayType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RefundAmountOption[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EventReceiptDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _EventReceiptTime[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
