
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Dilution Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/DilutionInq.doc">DilutionInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class DilutionInqView extends IFastView implements Serializable
{

   /**
    * Dilution Amount member variable.
    */
   private String _DilutionAmount = null;
   
   /**
    * Refund Amount member variable.
    */
   private String _RefundAmount = null;
   
   /**
    * Currency member variable.
    */
   private String _Currency = null;
   
   /**
    * FX Rate member variable.
    */
   private String _FXRate = null;
   
   /**
    * Refund Pay Type member variable.
    */
   private String _RefundPayType = null;
   
   /**
    * Refund Amount Option member variable.
    */
   private String _RefundAmountOption = null;
   
   /**
    * Dilution Available member variable.
    */
   private Boolean _DilutionAvail = null;
   
   /**
    * Settle Network member variable.
    */
   private String _SettleNetwork = null;
   
   private int _RepeatCount = 0;
   
   /**
    * TransID linking the dilution record to the trans-detl member array.
    */
   private String[] _rxTransID = null;
   
   /**
    * Accountability for backdated and cancelled transactions member array.
    */
   private String[] _AccCode = null;
   
   /**
    * Reason Code member array.
    */
   private String[] _RsnCode = null;
   
   /**
    * Responsibility from date member array.
    */
   private Date[] _RespDate = null;
   
   /**
    * Percentage of responsibility member array.
    */
   private String[] _RspPrcnt = null;
   
   /**
    * Version number of dilution record member array.
    */
   private Integer[] _DilutionVersion = null;
   
   /**
    * Recid of dilution record member array.
    */
   private Integer[] _SplitAccCodeRid = null;
   
   /**
    * Bill to Type (BROK/INTR/"") member array.
    */
   private String[] _BillToType = null;
   
   /**
    * Bill to Entity Code (Broker or Intr code) member array.
    */
   private String[] _BillToEntity = null;
   
   /**
    * Associated Bill to Account member array.
    */
   private String[] _BillToAccount = null;
   
   /**
    * Dilution Amount settle through FundServ member array.
    */
   private String[] _DilutionNSM = null;
   
   /**
    * External System Dilution Payment via FundSERV member array.
    */
   private String[] _ExSysDilPymtNSM = null;
   
   /**
    * ProcessDate member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * UserName member array.
    */
   private String[] _UserName = null;
   
   /**
    * ModDate member array.
    */
   private Date[] _ModDate = null;
   
   /**
    * ModUser member array.
    */
   private String[] _ModUser = null;
   

   /**
    * Constructs the DilutionInqView object.
    * 
    */
   public DilutionInqView()
   {
      super ( new DilutionInqRequest() );
   }

   /**
    * Constructs the DilutionInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public DilutionInqView( String hostEncoding )
   {
      super ( new DilutionInqRequest( hostEncoding ) );
   }

   /**
    * Gets the DilutionInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The DilutionInqRequest object.
    */
   public final DilutionInqRequest getRequest()
   {
      return (DilutionInqRequest)getIFastRequest();
   }
        
   /**
    * Gets the Dilution Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Dilution Amount or null.
    */
   public final String getDilutionAmount()
   {
      return _DilutionAmount;
   }
	
   /**
    * Gets the Dilution Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Dilution Amount or the specified default value.
    */
   public final String getDilutionAmount( String defaultValue )
   {
      return _DilutionAmount == null ? defaultValue : _DilutionAmount;
   }
                  
   /**
    * Gets the Refund Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Refund Amount or null.
    */
   public final String getRefundAmount()
   {
      return _RefundAmount;
   }
	
   /**
    * Gets the Refund Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Refund Amount or the specified default value.
    */
   public final String getRefundAmount( String defaultValue )
   {
      return _RefundAmount == null ? defaultValue : _RefundAmount;
   }
                  
   /**
    * Gets the Currency field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Currency or null.
    */
   public final String getCurrency()
   {
      return _Currency;
   }
	
   /**
    * Gets the Currency field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Currency or the specified default value.
    */
   public final String getCurrency( String defaultValue )
   {
      return _Currency == null ? defaultValue : _Currency;
   }
                  
   /**
    * Gets the FX Rate field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the FX Rate or null.
    */
   public final String getFXRate()
   {
      return _FXRate;
   }
	
   /**
    * Gets the FX Rate field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FX Rate or the specified default value.
    */
   public final String getFXRate( String defaultValue )
   {
      return _FXRate == null ? defaultValue : _FXRate;
   }
                  
   /**
    * Gets the Refund Pay Type field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Refund Pay Type or null.
    */
   public final String getRefundPayType()
   {
      return _RefundPayType;
   }
	
   /**
    * Gets the Refund Pay Type field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Refund Pay Type or the specified default value.
    */
   public final String getRefundPayType( String defaultValue )
   {
      return _RefundPayType == null ? defaultValue : _RefundPayType;
   }
                  
   /**
    * Gets the Refund Amount Option field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Refund Amount Option or null.
    */
   public final String getRefundAmountOption()
   {
      return _RefundAmountOption;
   }
	
   /**
    * Gets the Refund Amount Option field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Refund Amount Option or the specified default value.
    */
   public final String getRefundAmountOption( String defaultValue )
   {
      return _RefundAmountOption == null ? defaultValue : _RefundAmountOption;
   }
                  
   /**
    * Gets the Dilution Available field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Dilution Available or null.
    */
   public final Boolean getDilutionAvail()
   {
      return _DilutionAvail;
   }
	
   /**
    * Gets the Dilution Available field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Dilution Available or the specified default value.
    */
   public final boolean getDilutionAvail( boolean defaultValue )
   {
      return _DilutionAvail == null ? defaultValue : _DilutionAvail.booleanValue();
   }
                  
   /**
    * Gets the Settle Network field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Settle Network or null.
    */
   public final String getSettleNetwork()
   {
      return _SettleNetwork;
   }
	
   /**
    * Gets the Settle Network field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Settle Network or the specified default value.
    */
   public final String getSettleNetwork( String defaultValue )
   {
      return _SettleNetwork == null ? defaultValue : _SettleNetwork;
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
    * Gets the TransID linking the dilution record to the trans-detl field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the TransID linking the dilution record to the trans-detl or null.
    */
   public final String getrxTransID( int index )
   {
      return _rxTransID[index];
   }
    
   /**
    * Gets the TransID linking the dilution record to the trans-detl field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the TransID linking the dilution record to the trans-detl or the specified default value.
    */
   public final String getrxTransID( int index, String defaultValue )
   {
      return _rxTransID[index] == null ? defaultValue : _rxTransID[index];
   }
    
   /**
    * Gets the array of TransID linking the dilution record to the trans-detl fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of TransID linking the dilution record to the trans-detl values.
    */
   public final String[] getrxTransIDArray()
   {
      return _rxTransID;
   }
    
   /**
    * Gets the Accountability for backdated and cancelled transactions field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Accountability for backdated and cancelled transactions or null.
    */
   public final String getAccCode( int index )
   {
      return _AccCode[index];
   }
    
   /**
    * Gets the Accountability for backdated and cancelled transactions field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Accountability for backdated and cancelled transactions or the specified default value.
    */
   public final String getAccCode( int index, String defaultValue )
   {
      return _AccCode[index] == null ? defaultValue : _AccCode[index];
   }
    
   /**
    * Gets the array of Accountability for backdated and cancelled transactions fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Accountability for backdated and cancelled transactions values.
    */
   public final String[] getAccCodeArray()
   {
      return _AccCode;
   }
    
   /**
    * Gets the Reason Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reason Code or null.
    */
   public final String getRsnCode( int index )
   {
      return _RsnCode[index];
   }
    
   /**
    * Gets the Reason Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reason Code or the specified default value.
    */
   public final String getRsnCode( int index, String defaultValue )
   {
      return _RsnCode[index] == null ? defaultValue : _RsnCode[index];
   }
    
   /**
    * Gets the array of Reason Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reason Code values.
    */
   public final String[] getRsnCodeArray()
   {
      return _RsnCode;
   }
    
   /**
    * Gets the Responsibility from date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Responsibility from date or null.
    */
   public final Date getRespDate( int index )
   {
      return _RespDate[index];
   }
    
   /**
    * Gets the Responsibility from date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Responsibility from date or the specified default value.
    */
   public final Date getRespDate( int index, Date defaultValue )
   {
      return _RespDate[index] == null ? defaultValue : _RespDate[index];
   }
    
   /**
    * Gets the array of Responsibility from date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Responsibility from date values.
    */
   public final Date[] getRespDateArray()
   {
      return _RespDate;
   }
    
   /**
    * Gets the Percentage of responsibility field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Percentage of responsibility or null.
    */
   public final String getRspPrcnt( int index )
   {
      return _RspPrcnt[index];
   }
    
   /**
    * Gets the Percentage of responsibility field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Percentage of responsibility or the specified default value.
    */
   public final String getRspPrcnt( int index, String defaultValue )
   {
      return _RspPrcnt[index] == null ? defaultValue : _RspPrcnt[index];
   }
    
   /**
    * Gets the array of Percentage of responsibility fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Percentage of responsibility values.
    */
   public final String[] getRspPrcntArray()
   {
      return _RspPrcnt;
   }
    
   /**
    * Gets the Version number of dilution record field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Version number of dilution record or null.
    */
   public final Integer getDilutionVersion( int index )
   {
      return _DilutionVersion[index];
   }
    
   /**
    * Gets the Version number of dilution record field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Version number of dilution record or the specified default value.
    */
   public final int getDilutionVersion( int index, int defaultValue )
   {
      return _DilutionVersion[index] == null ? defaultValue : _DilutionVersion[index].intValue();
   }
    
   /**
    * Gets the array of Version number of dilution record fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Version number of dilution record values.
    */
   public final Integer[] getDilutionVersionArray()
   {
      return _DilutionVersion;
   }
    
   /**
    * Gets the Recid of dilution record field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Recid of dilution record or null.
    */
   public final Integer getSplitAccCodeRid( int index )
   {
      return _SplitAccCodeRid[index];
   }
    
   /**
    * Gets the Recid of dilution record field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Recid of dilution record or the specified default value.
    */
   public final int getSplitAccCodeRid( int index, int defaultValue )
   {
      return _SplitAccCodeRid[index] == null ? defaultValue : _SplitAccCodeRid[index].intValue();
   }
    
   /**
    * Gets the array of Recid of dilution record fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Recid of dilution record values.
    */
   public final Integer[] getSplitAccCodeRidArray()
   {
      return _SplitAccCodeRid;
   }
    
   /**
    * Gets the Bill to Type (BROK/INTR/"") field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bill to Type (BROK/INTR/"") or null.
    */
   public final String getBillToType( int index )
   {
      return _BillToType[index];
   }
    
   /**
    * Gets the Bill to Type (BROK/INTR/"") field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bill to Type (BROK/INTR/"") or the specified default value.
    */
   public final String getBillToType( int index, String defaultValue )
   {
      return _BillToType[index] == null ? defaultValue : _BillToType[index];
   }
    
   /**
    * Gets the array of Bill to Type (BROK/INTR/"") fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bill to Type (BROK/INTR/"") values.
    */
   public final String[] getBillToTypeArray()
   {
      return _BillToType;
   }
    
   /**
    * Gets the Bill to Entity Code (Broker or Intr code) field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bill to Entity Code (Broker or Intr code) or null.
    */
   public final String getBillToEntity( int index )
   {
      return _BillToEntity[index];
   }
    
   /**
    * Gets the Bill to Entity Code (Broker or Intr code) field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bill to Entity Code (Broker or Intr code) or the specified default value.
    */
   public final String getBillToEntity( int index, String defaultValue )
   {
      return _BillToEntity[index] == null ? defaultValue : _BillToEntity[index];
   }
    
   /**
    * Gets the array of Bill to Entity Code (Broker or Intr code) fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bill to Entity Code (Broker or Intr code) values.
    */
   public final String[] getBillToEntityArray()
   {
      return _BillToEntity;
   }
    
   /**
    * Gets the Associated Bill to Account field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Associated Bill to Account or null.
    */
   public final String getBillToAccount( int index )
   {
      return _BillToAccount[index];
   }
    
   /**
    * Gets the Associated Bill to Account field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Associated Bill to Account or the specified default value.
    */
   public final String getBillToAccount( int index, String defaultValue )
   {
      return _BillToAccount[index] == null ? defaultValue : _BillToAccount[index];
   }
    
   /**
    * Gets the array of Associated Bill to Account fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Associated Bill to Account values.
    */
   public final String[] getBillToAccountArray()
   {
      return _BillToAccount;
   }
    
   /**
    * Gets the Dilution Amount settle through FundServ field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Dilution Amount settle through FundServ or null.
    */
   public final String getDilutionNSM( int index )
   {
      return _DilutionNSM[index];
   }
    
   /**
    * Gets the Dilution Amount settle through FundServ field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Dilution Amount settle through FundServ or the specified default value.
    */
   public final String getDilutionNSM( int index, String defaultValue )
   {
      return _DilutionNSM[index] == null ? defaultValue : _DilutionNSM[index];
   }
    
   /**
    * Gets the array of Dilution Amount settle through FundServ fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Dilution Amount settle through FundServ values.
    */
   public final String[] getDilutionNSMArray()
   {
      return _DilutionNSM;
   }
    
   /**
    * Gets the External System Dilution Payment via FundSERV field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the External System Dilution Payment via FundSERV or null.
    */
   public final String getExSysDilPymtNSM( int index )
   {
      return _ExSysDilPymtNSM[index];
   }
    
   /**
    * Gets the External System Dilution Payment via FundSERV field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the External System Dilution Payment via FundSERV or the specified default value.
    */
   public final String getExSysDilPymtNSM( int index, String defaultValue )
   {
      return _ExSysDilPymtNSM[index] == null ? defaultValue : _ExSysDilPymtNSM[index];
   }
    
   /**
    * Gets the array of External System Dilution Payment via FundSERV fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of External System Dilution Payment via FundSERV values.
    */
   public final String[] getExSysDilPymtNSMArray()
   {
      return _ExSysDilPymtNSM;
   }
    
   /**
    * Gets the ProcessDate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ProcessDate or null.
    */
   public final Date getProcessDate( int index )
   {
      return _ProcessDate[index];
   }
    
   /**
    * Gets the ProcessDate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ProcessDate or the specified default value.
    */
   public final Date getProcessDate( int index, Date defaultValue )
   {
      return _ProcessDate[index] == null ? defaultValue : _ProcessDate[index];
   }
    
   /**
    * Gets the array of ProcessDate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ProcessDate values.
    */
   public final Date[] getProcessDateArray()
   {
      return _ProcessDate;
   }
    
   /**
    * Gets the UserName field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the UserName or null.
    */
   public final String getUserName( int index )
   {
      return _UserName[index];
   }
    
   /**
    * Gets the UserName field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the UserName or the specified default value.
    */
   public final String getUserName( int index, String defaultValue )
   {
      return _UserName[index] == null ? defaultValue : _UserName[index];
   }
    
   /**
    * Gets the array of UserName fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of UserName values.
    */
   public final String[] getUserNameArray()
   {
      return _UserName;
   }
    
   /**
    * Gets the ModDate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ModDate or null.
    */
   public final Date getModDate( int index )
   {
      return _ModDate[index];
   }
    
   /**
    * Gets the ModDate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ModDate or the specified default value.
    */
   public final Date getModDate( int index, Date defaultValue )
   {
      return _ModDate[index] == null ? defaultValue : _ModDate[index];
   }
    
   /**
    * Gets the array of ModDate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ModDate values.
    */
   public final Date[] getModDateArray()
   {
      return _ModDate;
   }
    
   /**
    * Gets the ModUser field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ModUser or null.
    */
   public final String getModUser( int index )
   {
      return _ModUser[index];
   }
    
   /**
    * Gets the ModUser field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ModUser or the specified default value.
    */
   public final String getModUser( int index, String defaultValue )
   {
      return _ModUser[index] == null ? defaultValue : _ModUser[index];
   }
    
   /**
    * Gets the array of ModUser fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ModUser values.
    */
   public final String[] getModUserArray()
   {
      return _ModUser;
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
      _DilutionAmount = responseBuffer.decodeString(responseBuffer.getNextField());
      _RefundAmount = responseBuffer.decodeString(responseBuffer.getNextField());
      _Currency = responseBuffer.decodeString(responseBuffer.getNextField());
      _FXRate = responseBuffer.decodeString(responseBuffer.getNextField());
      _RefundPayType = responseBuffer.decodeString(responseBuffer.getNextField());
      _RefundAmountOption = responseBuffer.decodeString(responseBuffer.getNextField());
      _DilutionAvail = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _SettleNetwork = responseBuffer.decodeString(responseBuffer.getNextField());
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _rxTransID = resizeArray( _rxTransID, _RepeatCount );
      _AccCode = resizeArray( _AccCode, _RepeatCount );
      _RsnCode = resizeArray( _RsnCode, _RepeatCount );
      _RespDate = resizeArray( _RespDate, _RepeatCount );
      _RspPrcnt = resizeArray( _RspPrcnt, _RepeatCount );
      _DilutionVersion = resizeArray( _DilutionVersion, _RepeatCount );
      _SplitAccCodeRid = resizeArray( _SplitAccCodeRid, _RepeatCount );
      _BillToType = resizeArray( _BillToType, _RepeatCount );
      _BillToEntity = resizeArray( _BillToEntity, _RepeatCount );
      _BillToAccount = resizeArray( _BillToAccount, _RepeatCount );
      _DilutionNSM = resizeArray( _DilutionNSM, _RepeatCount );
      _ExSysDilPymtNSM = resizeArray( _ExSysDilPymtNSM, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _UserName = resizeArray( _UserName, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _ModUser = resizeArray( _ModUser, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxTransID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AccCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RsnCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RespDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _RspPrcnt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DilutionVersion[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _SplitAccCodeRid[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _BillToType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BillToEntity[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BillToAccount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DilutionNSM[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ExSysDilPymtNSM[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _UserName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ModUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
