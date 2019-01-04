// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Trade Adjust Maint (Bulk Cancellation & Rebook) request.
 * For additional view information see <A HREF="../../../../viewspecs/TradeAdjBulkMaint.doc">TradeAdjBulkMaint.doc</A>.
 * 
 * @author RTS Generated
 */
public class TradeAdjBulkMaintRequest extends IFastRequest implements Serializable
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
    * Run Mode (A)dd, (M)odify, (D)elete member variable.
    */
   private String _RunMode = "";
            
   /**
    * Reversal Code as define in misc-info groupcode AZ member variable.
    */
   private String _RVCD = "";
            
   /**
    * Should the cancelled transaction be reported on stmts member variable.
    */
   private Boolean _ReportOnStmt = new Boolean(false);
            
   /**
    * Accountability Code for Cancelled transactions as defined in Misc-Info groupcode AZ member variable.
    */
   private String _AccountableCode = "";
            
   /**
    * should a confirmation be produced member variable.
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
   private String _Remarks_Line_2 = "";
            
   /**
    * Remarks for the cancelled transaction member variable.
    */
   private String _Remarks_Line_3 = "";
            
   /**
    * Batch used for transaction being cancelled member variable.
    */
   private String _BTBatch = "";
            
   /**
    * The trace number linked to the transaction and Batch member variable.
    */
   private Integer _BTTrace = null;
            
   /**
    * Status code, defined in misc-info groupcode SV member variable.
    */
   private String _TransStat = "";
            
   /**
    * Transaction Type of transaction to be settled member variable.
    */
   private String _TransType = "";
            
   /**
    * Version of TradeAdjust record member variable.
    */
   private Integer _TradeAdjVersion = null;
            
   /**
    * System generated unique trade adjust ID member variable.
    */
   private String _TradeAdjustID = "0";
            
   /**
    * Type of Cancellation (INDV, BULK) member variable.
    */
   private String _CancellationType = "";
            
   /**
    * Trade Date member variable.
    */
   private Date _TradeDate = null;
            
   /**
    * Fund member variable.
    */
   private String _Fund = "";
            
   /**
    * Class member variable.
    */
   private String _Class = "";
            
   /**
    * Rebook - Y/N member variable.
    */
   private Boolean _Rebook = new Boolean(false);
            
   /**
    * MCHFile member variable.
    */
   private String _MCHFile = "";
            
   /**
    * Sec Recon File member variable.
    */
   private String _SecRecFile = "";
            
   /**
    * Rbk MCH File member variable.
    */
   private String _RbkMCHFile = "";
            
   /**
    * Rbk Sec Recon File member variable.
    */
   private String _RbkSecRecFile = "";
            
   /**
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * A (Add), M (Modify), D (Delete) member array.
    */
   private String[] _DilRunMode = new String[25];
            
   /**
    * Accountability for backdated and cancelled transactions member array.
    */
   private String[] _AccCode = new String[25];
            
   /**
    * Reason Code member array.
    */
   private String[] _RsnCode = new String[25];
            
   /**
    * Responsibility From Date member array.
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
   private Integer[] _SplitAccCodeRID = new Integer[25];
            
   /**
    * System generated unique number split AccCode ID member array.
    */
   private String[] _SplitAccCodeID = new String[25];
            
   /**
    * External System Dilution Payment via FundSERV member array.
    */
   private String[] _ExSysDilPymtNSM = new String[25];
            

   /**
    * Constructs the TradeAdjBulkMaintRequest object.
    * 
    */
   TradeAdjBulkMaintRequest()
   {
      super ( 355 );
   }

   /**
    * Constructs the TradeAdjBulkMaintRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   TradeAdjBulkMaintRequest( String hostEncoding )
   {
      super ( 355, hostEncoding );
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
    * Sets the Run Mode (A)dd, (M)odify, (D)elete field for the request.
    * 
    * @param value  Value that the Run Mode (A)dd, (M)odify, (D)elete will be set to.
    */
   public final void setRunMode( String value )
   {
      assertUnsent();
      _RunMode = value;
   }
	
   /**
    * Sets the Reversal Code as define in misc-info groupcode AZ field for the request.
    * 
    * @param value  Value that the Reversal Code as define in misc-info groupcode AZ will be set to.
    */
   public final void setRVCD( String value )
   {
      assertUnsent();
      _RVCD = value;
   }
	
   /**
    * Sets the Should the cancelled transaction be reported on stmts field for the request.
    * 
    * @param value  Value that the Should the cancelled transaction be reported on stmts will be set to.
    */
   public final void setReportOnStmt( Boolean value )
   {
      assertUnsent();
      _ReportOnStmt = value;
   }
	
   /**
    * Sets the Accountability Code for Cancelled transactions as defined in Misc-Info groupcode AZ field for the request.
    * 
    * @param value  Value that the Accountability Code for Cancelled transactions as defined in Misc-Info groupcode AZ will be set to.
    */
   public final void setAccountableCode( String value )
   {
      assertUnsent();
      _AccountableCode = value;
   }
	
   /**
    * Sets the should a confirmation be produced field for the request.
    * 
    * @param value  Value that the should a confirmation be produced will be set to.
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
   public final void setRemarks_Line_2( String value )
   {
      assertUnsent();
      _Remarks_Line_2 = value;
   }
	
   /**
    * Sets the Remarks for the cancelled transaction field for the request.
    * 
    * @param value  Value that the Remarks for the cancelled transaction will be set to.
    */
   public final void setRemarks_Line_3( String value )
   {
      assertUnsent();
      _Remarks_Line_3 = value;
   }
	
   /**
    * Sets the Batch used for transaction being cancelled field for the request.
    * 
    * @param value  Value that the Batch used for transaction being cancelled will be set to.
    */
   public final void setBTBatch( String value )
   {
      assertUnsent();
      _BTBatch = value;
   }
	
   /**
    * Sets the The trace number linked to the transaction and Batch field for the request.
    * 
    * @param value  Value that the The trace number linked to the transaction and Batch will be set to.
    */
   public final void setBTTrace( Integer value )
   {
      assertUnsent();
      _BTTrace = value;
   }
	
   /**
    * Sets the Status code, defined in misc-info groupcode SV field for the request.
    * 
    * @param value  Value that the Status code, defined in misc-info groupcode SV will be set to.
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
    * Sets the Version of TradeAdjust record field for the request.
    * 
    * @param value  Value that the Version of TradeAdjust record will be set to.
    */
   public final void setTradeAdjVersion( Integer value )
   {
      assertUnsent();
      _TradeAdjVersion = value;
   }
	
   /**
    * Sets the System generated unique trade adjust ID field for the request.
    * 
    * @param value  Value that the System generated unique trade adjust ID will be set to.
    */
   public final void setTradeAdjustID( String value )
   {
      assertUnsent();
      _TradeAdjustID = value;
   }
	
   /**
    * Sets the Type of Cancellation (INDV, BULK) field for the request.
    * 
    * @param value  Value that the Type of Cancellation (INDV, BULK) will be set to.
    */
   public final void setCancellationType( String value )
   {
      assertUnsent();
      _CancellationType = value;
   }
	
   /**
    * Sets the Trade Date field for the request.
    * 
    * @param value  Value that the Trade Date will be set to.
    */
   public final void setTradeDate( Date value )
   {
      assertUnsent();
      _TradeDate = value;
   }
	
   /**
    * Sets the Fund field for the request.
    * 
    * @param value  Value that the Fund will be set to.
    */
   public final void setFund( String value )
   {
      assertUnsent();
      _Fund = value;
   }
	
   /**
    * Sets the Class field for the request.
    * 
    * @param value  Value that the Class will be set to.
    */
   public final void setClass( String value )
   {
      assertUnsent();
      _Class = value;
   }
	
   /**
    * Sets the Rebook - Y/N field for the request.
    * 
    * @param value  Value that the Rebook - Y/N will be set to.
    */
   public final void setRebook( Boolean value )
   {
      assertUnsent();
      _Rebook = value;
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
    * Sets the Rbk MCH File field for the request.
    * 
    * @param value  Value that the Rbk MCH File will be set to.
    */
   public final void setRbkMCHFile( String value )
   {
      assertUnsent();
      _RbkMCHFile = value;
   }
	
   /**
    * Sets the Rbk Sec Recon File field for the request.
    * 
    * @param value  Value that the Rbk Sec Recon File will be set to.
    */
   public final void setRbkSecRecFile( String value )
   {
      assertUnsent();
      _RbkSecRecFile = value;
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
    * Sets the A (Add), M (Modify), D (Delete) field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the A (Add), M (Modify), D (Delete) will be set to.
    */
   public final void setDilRunMode( int index, String value )
   {
      assertUnsent();
      _DilRunMode[index] = value;
   }
	
   /**
    * Sets the Accountability for backdated and cancelled transactions field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Accountability for backdated and cancelled transactions will be set to.
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
    * Sets the Responsibility From Date field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Responsibility From Date will be set to.
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
   public final void setSplitAccCodeRID( int index, Integer value )
   {
      assertUnsent();
      _SplitAccCodeRID[index] = value;
   }
	
   /**
    * Sets the System generated unique number split AccCode ID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the System generated unique number split AccCode ID will be set to.
    */
   public final void setSplitAccCodeID( int index, String value )
   {
      assertUnsent();
      _SplitAccCodeID[index] = value;
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
      requestBuffer.appendField( _RVCD );
      requestBuffer.appendField( _ReportOnStmt );
      requestBuffer.appendField( _AccountableCode );
      requestBuffer.appendField( _Confirmation );
      requestBuffer.appendField( _CancelCheque );
      requestBuffer.appendField( _Remarks_Line_1 );
      requestBuffer.appendField( _Remarks_Line_2 );
      requestBuffer.appendField( _Remarks_Line_3 );
      requestBuffer.appendField( _BTBatch );
      requestBuffer.appendField( _BTTrace );
      requestBuffer.appendField( _TransStat );
      requestBuffer.appendField( _TransType );
      requestBuffer.appendField( _TradeAdjVersion );
      requestBuffer.appendField( _TradeAdjustID );
      requestBuffer.appendField( _CancellationType );
      requestBuffer.appendField( _TradeDate );
      requestBuffer.appendField( _Fund );
      requestBuffer.appendField( _Class );
      requestBuffer.appendField( _Rebook );
      requestBuffer.appendField( _MCHFile );
      requestBuffer.appendField( _SecRecFile );
      requestBuffer.appendField( _RbkMCHFile );
      requestBuffer.appendField( _RbkSecRecFile );
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _DilRunMode[x] );
         requestBuffer.appendField( _AccCode[x] );
         requestBuffer.appendField( _RsnCode[x] );
         requestBuffer.appendField( _RespDate[x] );
         requestBuffer.appendField( _RspPrcnt[x] );
         requestBuffer.appendField( _DilVersion[x] );
         requestBuffer.appendField( _SplitAccCodeRID[x] );
         requestBuffer.appendField( _SplitAccCodeID[x] );
         requestBuffer.appendField( _ExSysDilPymtNSM[x] );
      }
   }

}

