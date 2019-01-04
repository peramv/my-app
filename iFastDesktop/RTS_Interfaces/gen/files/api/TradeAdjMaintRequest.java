// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Trade Adjust Maint (Indivi. Cancellation & Rebook) request.
 * For additional view information see <A HREF="../../../../viewspecs/TradeAdjMaint.doc">TradeAdjMaint.doc</A>.
 * 
 * @author RTS Generated
 */
public class TradeAdjMaintRequest extends IFastRequest implements Serializable
{

   /**
    * Session ID member variable.
    */
   private String _SessionID = "";
            
   /**
    * User ID member variable.
    */
   private String _User_ID = "";
            
   /**
    * Language Code member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * Company ID member variable.
    */
   private String _CompanyID = "";
            
            
            
   /**
    * Run Mode member variable.
    */
   private String _RunMode = "";
            
   /**
    * Transaction Number linked to trans-detl to be cancelled member variable.
    */
   private Integer _TransNum = null;
            
   /**
    * Reversal Code as defined in misc-info groupcode RV member variable.
    */
   private String _RVCD = "";
            
   /**
    * Should the cancelled transaction be reported on statements member variable.
    */
   private Boolean _ReportOnStmt = new Boolean(false);
            
   /**
    * Accountability code for cancelled transactions as defined in misc-info groupcode AZ member variable.
    */
   private String _AccountableCode = "";
            
   /**
    * Should a confirmation be produced member variable.
    */
   private Boolean _Confirmation = new Boolean(false);
            
   /**
    * Does the cheque need to be cancelled member variable.
    */
   private Boolean _CancelCheque = new Boolean(false);
            
   /**
    * Remarks for the cancelled transaction member variable.
    */
   private String _Remarks_Line_1 = "";
            
   /**
    * Remarks for the cancelled transaction member variable.
    */
   private String _Remarks_line_2 = "";
            
   /**
    * Remarks for the cancelled transaction member variable.
    */
   private String _Remarks_line_3 = "";
            
   /**
    * The batch used for the transaction being cancelled member variable.
    */
   private String _BTBatch = "";
            
   /**
    * The trace number linked to the transaction and batch member variable.
    */
   private Integer _BTTrace = null;
            
   /**
    * Enter the code applicable to the status of the record member variable.
    */
   private String _TransStat = "";
            
   /**
    * Transaction Type of transaction to be settled member variable.
    */
   private String _TransType = "";
            
   /**
    * Version member variable.
    */
   private Integer _TradeAdjVersion = null;
            
   /**
    * MCHFile member variable.
    */
   private String _MCHFile = "";
            
   /**
    * Sec Recon File member variable.
    */
   private String _SecRecFile = "";
            
   /**
    * Flag indicate if the transaction  is to  be excluded from NSM file member variable.
    */
   private String _ESGSettle = "";
            
   /**
    * Cancel Contribution Receipt Flag member variable.
    */
   private Boolean _CancelContribRcpt = new Boolean(false);
            
   /**
    * Exclude Receipt Print Flag member variable.
    */
   private Boolean _ExcldRcptPrint = new Boolean(false);
            
   /**
    * Return to Sender Flag member variable.
    */
   private Boolean _RetToSender = new Boolean(false);
            
   /**
    * Flag indicating if the associated grant should also be cancelled member variable.
    */
   private Boolean _CancelGrant = new Boolean(false);
            
   /**
    * Refund Pay Type member variable.
    */
   private String _RefundPayType = "";
            
   /**
    * Refund Option member variable.
    */
   private String _RefundOption = "";
            
   /**
    * Event Receipt Date member variable.
    */
   private Date _EventReceiptDate = null;
            
   /**
    * Event Receipt Time member variable.
    */
   private String _EventReceiptTime = "";
            
   /**
    * Settle Network member variable.
    */
   private String _SettleNetwork = "";
            
   /**
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * A (Add), M(Modiy), D (Delete) member array.
    */
   private String[] _DilRunMode = new String[25];
            
   /**
    * Accountability for backdated and cancel transactions member array.
    */
   private String[] _AccCode = new String[25];
            
   /**
    * Reason Code member array.
    */
   private String[] _RsnCode = new String[25];
            
   /**
    * Responsibility from date member array.
    */
   private Date[] _RespDate = new Date[25];
            
   /**
    * Percentage of responsibility member array.
    */
   private String[] _RspPrcnt = new String[25];
            
   /**
    * Version number of dilution record member array.
    */
   private Integer[] _DilVersion = new Integer[25];
            
   /**
    * Recid of dilution records member array.
    */
   private Integer[] _SplitAccCodeRid = new Integer[25];
            
   /**
    * Billing to type (BROK/INTR/"") member array.
    */
   private String[] _BillToType = new String[25];
            
   /**
    * Billing To Entity (Broker or Inter code) member array.
    */
   private String[] _BillToEntity = new String[25];
            
   /**
    * Associated bill to account member array.
    */
   private String[] _BillToAccount = new String[25];
            
   /**
    * Dilution Amount settle through FundServ member array.
    */
   private String[] _DilutionNSM = new String[25];
            
   /**
    * External System Dilution Payment via FundSERV member array.
    */
   private String[] _ExSysDilPymtNSM = new String[25];
            

   /**
    * Constructs the TradeAdjMaintRequest object.
    * 
    */
   TradeAdjMaintRequest()
   {
      super ( 338 );
   }

   /**
    * Constructs the TradeAdjMaintRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   TradeAdjMaintRequest( String hostEncoding )
   {
      super ( 338, hostEncoding );
   }

   /**
    * Sets the Session ID field for the request.
    * 
    * @param value  Value that the Session ID will be set to.
    */
   public final void setSessionID( String value )
   {
      assertUnsent();
      _SessionID = value;
   }
	
   /**
    * Sets the User ID field for the request.
    * 
    * @param value  Value that the User ID will be set to.
    */
   public final void setUser_ID( String value )
   {
      assertUnsent();
      _User_ID = value;
   }
	
   /**
    * Sets the Language Code field for the request.
    * 
    * @param value  Value that the Language Code will be set to.
    */
   public final void setLanguageCode( String value )
   {
      assertUnsent();
      _LanguageCode = value;
   }
	
   /**
    * Sets the Company ID field for the request.
    * 
    * @param value  Value that the Company ID will be set to.
    */
   public final void setCompanyID( String value )
   {
      assertUnsent();
      _CompanyID = value;
   }
	
   /**
    * Sets the Run Mode field for the request.
    * 
    * @param value  Value that the Run Mode will be set to.
    */
   public final void setRunMode( String value )
   {
      assertUnsent();
      _RunMode = value;
   }
	
   /**
    * Sets the Transaction Number linked to trans-detl to be cancelled field for the request.
    * 
    * @param value  Value that the Transaction Number linked to trans-detl to be cancelled will be set to.
    */
   public final void setTransNum( Integer value )
   {
      assertUnsent();
      _TransNum = value;
   }
	
   /**
    * Sets the Reversal Code as defined in misc-info groupcode RV field for the request.
    * 
    * @param value  Value that the Reversal Code as defined in misc-info groupcode RV will be set to.
    */
   public final void setRVCD( String value )
   {
      assertUnsent();
      _RVCD = value;
   }
	
   /**
    * Sets the Should the cancelled transaction be reported on statements field for the request.
    * 
    * @param value  Value that the Should the cancelled transaction be reported on statements will be set to.
    */
   public final void setReportOnStmt( Boolean value )
   {
      assertUnsent();
      _ReportOnStmt = value;
   }
	
   /**
    * Sets the Accountability code for cancelled transactions as defined in misc-info groupcode AZ field for the request.
    * 
    * @param value  Value that the Accountability code for cancelled transactions as defined in misc-info groupcode AZ will be set to.
    */
   public final void setAccountableCode( String value )
   {
      assertUnsent();
      _AccountableCode = value;
   }
	
   /**
    * Sets the Should a confirmation be produced field for the request.
    * 
    * @param value  Value that the Should a confirmation be produced will be set to.
    */
   public final void setConfirmation( Boolean value )
   {
      assertUnsent();
      _Confirmation = value;
   }
	
   /**
    * Sets the Does the cheque need to be cancelled field for the request.
    * 
    * @param value  Value that the Does the cheque need to be cancelled will be set to.
    */
   public final void setCancelCheque( Boolean value )
   {
      assertUnsent();
      _CancelCheque = value;
   }
	
   /**
    * Sets the Remarks for the cancelled transaction field for the request.
    * 
    * @param value  Value that the Remarks for the cancelled transaction will be set to.
    */
   public final void setRemarks_Line_1( String value )
   {
      assertUnsent();
      _Remarks_Line_1 = value;
   }
	
   /**
    * Sets the Remarks for the cancelled transaction field for the request.
    * 
    * @param value  Value that the Remarks for the cancelled transaction will be set to.
    */
   public final void setRemarks_line_2( String value )
   {
      assertUnsent();
      _Remarks_line_2 = value;
   }
	
   /**
    * Sets the Remarks for the cancelled transaction field for the request.
    * 
    * @param value  Value that the Remarks for the cancelled transaction will be set to.
    */
   public final void setRemarks_line_3( String value )
   {
      assertUnsent();
      _Remarks_line_3 = value;
   }
	
   /**
    * Sets the The batch used for the transaction being cancelled field for the request.
    * 
    * @param value  Value that the The batch used for the transaction being cancelled will be set to.
    */
   public final void setBTBatch( String value )
   {
      assertUnsent();
      _BTBatch = value;
   }
	
   /**
    * Sets the The trace number linked to the transaction and batch field for the request.
    * 
    * @param value  Value that the The trace number linked to the transaction and batch will be set to.
    */
   public final void setBTTrace( Integer value )
   {
      assertUnsent();
      _BTTrace = value;
   }
	
   /**
    * Sets the Enter the code applicable to the status of the record field for the request.
    * 
    * @param value  Value that the Enter the code applicable to the status of the record will be set to.
    */
   public final void setTransStat( String value )
   {
      assertUnsent();
      _TransStat = value;
   }
	
   /**
    * Sets the Transaction Type of transaction to be settled field for the request.
    * 
    * @param value  Value that the Transaction Type of transaction to be settled will be set to.
    */
   public final void setTransType( String value )
   {
      assertUnsent();
      _TransType = value;
   }
	
   /**
    * Sets the Version field for the request.
    * 
    * @param value  Value that the Version will be set to.
    */
   public final void setTradeAdjVersion( Integer value )
   {
      assertUnsent();
      _TradeAdjVersion = value;
   }
	
   /**
    * Sets the MCHFile field for the request.
    * 
    * @param value  Value that the MCHFile will be set to.
    */
   public final void setMCHFile( String value )
   {
      assertUnsent();
      _MCHFile = value;
   }
	
   /**
    * Sets the Sec Recon File field for the request.
    * 
    * @param value  Value that the Sec Recon File will be set to.
    */
   public final void setSecRecFile( String value )
   {
      assertUnsent();
      _SecRecFile = value;
   }
	
   /**
    * Sets the Flag indicate if the transaction  is to  be excluded from NSM file field for the request.
    * 
    * @param value  Value that the Flag indicate if the transaction  is to  be excluded from NSM file will be set to.
    */
   public final void setESGSettle( String value )
   {
      assertUnsent();
      _ESGSettle = value;
   }
	
   /**
    * Sets the Cancel Contribution Receipt Flag field for the request.
    * 
    * @param value  Value that the Cancel Contribution Receipt Flag will be set to.
    */
   public final void setCancelContribRcpt( Boolean value )
   {
      assertUnsent();
      _CancelContribRcpt = value;
   }
	
   /**
    * Sets the Exclude Receipt Print Flag field for the request.
    * 
    * @param value  Value that the Exclude Receipt Print Flag will be set to.
    */
   public final void setExcldRcptPrint( Boolean value )
   {
      assertUnsent();
      _ExcldRcptPrint = value;
   }
	
   /**
    * Sets the Return to Sender Flag field for the request.
    * 
    * @param value  Value that the Return to Sender Flag will be set to.
    */
   public final void setRetToSender( Boolean value )
   {
      assertUnsent();
      _RetToSender = value;
   }
	
   /**
    * Sets the Flag indicating if the associated grant should also be cancelled field for the request.
    * 
    * @param value  Value that the Flag indicating if the associated grant should also be cancelled will be set to.
    */
   public final void setCancelGrant( Boolean value )
   {
      assertUnsent();
      _CancelGrant = value;
   }
	
   /**
    * Sets the Refund Pay Type field for the request.
    * 
    * @param value  Value that the Refund Pay Type will be set to.
    */
   public final void setRefundPayType( String value )
   {
      assertUnsent();
      _RefundPayType = value;
   }
	
   /**
    * Sets the Refund Option field for the request.
    * 
    * @param value  Value that the Refund Option will be set to.
    */
   public final void setRefundOption( String value )
   {
      assertUnsent();
      _RefundOption = value;
   }
	
   /**
    * Sets the Event Receipt Date field for the request.
    * 
    * @param value  Value that the Event Receipt Date will be set to.
    */
   public final void setEventReceiptDate( Date value )
   {
      assertUnsent();
      _EventReceiptDate = value;
   }
	
   /**
    * Sets the Event Receipt Time field for the request.
    * 
    * @param value  Value that the Event Receipt Time will be set to.
    */
   public final void setEventReceiptTime( String value )
   {
      assertUnsent();
      _EventReceiptTime = value;
   }
	
   /**
    * Sets the Settle Network field for the request.
    * 
    * @param value  Value that the Settle Network will be set to.
    */
   public final void setSettleNetwork( String value )
   {
      assertUnsent();
      _SettleNetwork = value;
   }
	
   /**
    * Sets the Record Count for the repeatable request.
    * 
    * @param value    Value that the Record Count will be set to.
    */
   public final void setRepeatCount( int value )
   {
      _RepeatCount = value;
   }
         
   /**
    * Sets the A (Add), M(Modiy), D (Delete) field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the A (Add), M(Modiy), D (Delete) will be set to.
    */
   public final void setDilRunMode( int index, String value )
   {
      assertUnsent();
      _DilRunMode[index] = value;
   }
	
   /**
    * Sets the Accountability for backdated and cancel transactions field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Accountability for backdated and cancel transactions will be set to.
    */
   public final void setAccCode( int index, String value )
   {
      assertUnsent();
      _AccCode[index] = value;
   }
	
   /**
    * Sets the Reason Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Reason Code will be set to.
    */
   public final void setRsnCode( int index, String value )
   {
      assertUnsent();
      _RsnCode[index] = value;
   }
	
   /**
    * Sets the Responsibility from date field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Responsibility from date will be set to.
    */
   public final void setRespDate( int index, Date value )
   {
      assertUnsent();
      _RespDate[index] = value;
   }
	
   /**
    * Sets the Percentage of responsibility field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Percentage of responsibility will be set to.
    */
   public final void setRspPrcnt( int index, String value )
   {
      assertUnsent();
      _RspPrcnt[index] = value;
   }
	
   /**
    * Sets the Version number of dilution record field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Version number of dilution record will be set to.
    */
   public final void setDilVersion( int index, Integer value )
   {
      assertUnsent();
      _DilVersion[index] = value;
   }
	
   /**
    * Sets the Recid of dilution records field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Recid of dilution records will be set to.
    */
   public final void setSplitAccCodeRid( int index, Integer value )
   {
      assertUnsent();
      _SplitAccCodeRid[index] = value;
   }
	
   /**
    * Sets the Billing to type (BROK/INTR/"") field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Billing to type (BROK/INTR/"") will be set to.
    */
   public final void setBillToType( int index, String value )
   {
      assertUnsent();
      _BillToType[index] = value;
   }
	
   /**
    * Sets the Billing To Entity (Broker or Inter code) field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Billing To Entity (Broker or Inter code) will be set to.
    */
   public final void setBillToEntity( int index, String value )
   {
      assertUnsent();
      _BillToEntity[index] = value;
   }
	
   /**
    * Sets the Associated bill to account field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Associated bill to account will be set to.
    */
   public final void setBillToAccount( int index, String value )
   {
      assertUnsent();
      _BillToAccount[index] = value;
   }
	
   /**
    * Sets the Dilution Amount settle through FundServ field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Dilution Amount settle through FundServ will be set to.
    */
   public final void setDilutionNSM( int index, String value )
   {
      assertUnsent();
      _DilutionNSM[index] = value;
   }
	
   /**
    * Sets the External System Dilution Payment via FundSERV field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the External System Dilution Payment via FundSERV will be set to.
    */
   public final void setExSysDilPymtNSM( int index, String value )
   {
      assertUnsent();
      _ExSysDilPymtNSM[index] = value;
   }
	
   /**
    * Implements the abstract base method to encode
    * the host formatted request.
    * 
    * @param transaction
    *               Host formatted request object.
    */
   protected final void encodeFields( RTSRequestEncodeBuffer requestBuffer ) throws UnsupportedEncodingException
   {
      requestBuffer.appendField( _SessionID );
      requestBuffer.appendField( _User_ID );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyID );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _RunMode );
      requestBuffer.appendField( _TransNum );
      requestBuffer.appendField( _RVCD );
      requestBuffer.appendField( _ReportOnStmt );
      requestBuffer.appendField( _AccountableCode );
      requestBuffer.appendField( _Confirmation );
      requestBuffer.appendField( _CancelCheque );
      requestBuffer.appendField( _Remarks_Line_1 );
      requestBuffer.appendField( _Remarks_line_2 );
      requestBuffer.appendField( _Remarks_line_3 );
      requestBuffer.appendField( _BTBatch );
      requestBuffer.appendField( _BTTrace );
      requestBuffer.appendField( _TransStat );
      requestBuffer.appendField( _TransType );
      requestBuffer.appendField( _TradeAdjVersion );
      requestBuffer.appendField( _MCHFile );
      requestBuffer.appendField( _SecRecFile );
      requestBuffer.appendField( _ESGSettle );
      requestBuffer.appendField( _CancelContribRcpt );
      requestBuffer.appendField( _ExcldRcptPrint );
      requestBuffer.appendField( _RetToSender );
      requestBuffer.appendField( _CancelGrant );
      requestBuffer.appendField( _RefundPayType );
      requestBuffer.appendField( _RefundOption );
      requestBuffer.appendField( _EventReceiptDate );
      requestBuffer.appendField( _EventReceiptTime );
      requestBuffer.appendField( _SettleNetwork );
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _DilRunMode[x] );
         requestBuffer.appendField( _AccCode[x] );
         requestBuffer.appendField( _RsnCode[x] );
         requestBuffer.appendField( _RespDate[x] );
         requestBuffer.appendField( _RspPrcnt[x] );
         requestBuffer.appendField( _DilVersion[x] );
         requestBuffer.appendField( _SplitAccCodeRid[x] );
         requestBuffer.appendField( _BillToType[x] );
         requestBuffer.appendField( _BillToEntity[x] );
         requestBuffer.appendField( _BillToAccount[x] );
         requestBuffer.appendField( _DilutionNSM[x] );
         requestBuffer.appendField( _ExSysDilPymtNSM[x] );
      }
   }

}

