
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * MAT/INT/CSW Instruction List Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/InstructionListInquiry.doc">InstructionListInquiry.doc</A>.
 * 
 * @author RTS Generated
 */
public class InstructionListInquiryView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * InstructionType member array.
    */
   private String[] _InstructionType = null;
   
   /**
    * Account member array.
    */
   private String[] _Account = null;
   
   /**
    * Fund member array.
    */
   private String[] _Fund = null;
   
   /**
    * Class member array.
    */
   private String[] _Class = null;
   
   /**
    * SplitType member array.
    */
   private String[] _SplitType = null;
   
   /**
    * EffectiveDate member array.
    */
   private Date[] _EffectiveDate = null;
   
   /**
    * TransNum member array.
    */
   private Integer[] _TransNum = null;
   
   /**
    * CashSweepBal member array.
    */
   private String[] _CashSweepBal = null;
   
   /**
    * SelectedAmt member array.
    */
   private String[] _SelectedAmt = null;
   
   /**
    * IntInvestId member array.
    */
   private String[] _IntInvestId = null;
   
   /**
    * GBCD member array.
    */
   private Boolean[] _GBCD = null;
   
   /**
    * TransId member array.
    */
   private String[] _TransId = null;
   
   /**
    * TransSeq member array.
    */
   private Integer[] _TransSeq = null;
   

   /**
    * Constructs the InstructionListInquiryView object.
    * 
    */
   public InstructionListInquiryView()
   {
      super ( new InstructionListInquiryRequest() );
   }

   /**
    * Constructs the InstructionListInquiryView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public InstructionListInquiryView( String hostEncoding )
   {
      super ( new InstructionListInquiryRequest( hostEncoding ) );
   }

   /**
    * Gets the InstructionListInquiryRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The InstructionListInquiryRequest object.
    */
   public final InstructionListInquiryRequest getRequest()
   {
      return (InstructionListInquiryRequest)getIFastRequest();
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
    * Gets the InstructionType field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the InstructionType or null.
    */
   public final String getInstructionType( int index )
   {
      return _InstructionType[index];
   }
    
   /**
    * Gets the InstructionType field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the InstructionType or the specified default value.
    */
   public final String getInstructionType( int index, String defaultValue )
   {
      return _InstructionType[index] == null ? defaultValue : _InstructionType[index];
   }
    
   /**
    * Gets the array of InstructionType fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of InstructionType values.
    */
   public final String[] getInstructionTypeArray()
   {
      return _InstructionType;
   }
    
   /**
    * Gets the Account field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account or null.
    */
   public final String getAccount( int index )
   {
      return _Account[index];
   }
    
   /**
    * Gets the Account field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account or the specified default value.
    */
   public final String getAccount( int index, String defaultValue )
   {
      return _Account[index] == null ? defaultValue : _Account[index];
   }
    
   /**
    * Gets the array of Account fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account values.
    */
   public final String[] getAccountArray()
   {
      return _Account;
   }
    
   /**
    * Gets the Fund field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund or null.
    */
   public final String getFund( int index )
   {
      return _Fund[index];
   }
    
   /**
    * Gets the Fund field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund or the specified default value.
    */
   public final String getFund( int index, String defaultValue )
   {
      return _Fund[index] == null ? defaultValue : _Fund[index];
   }
    
   /**
    * Gets the array of Fund fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund values.
    */
   public final String[] getFundArray()
   {
      return _Fund;
   }
    
   /**
    * Gets the Class field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Class or null.
    */
   public final String getClass( int index )
   {
      return _Class[index];
   }
    
   /**
    * Gets the Class field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Class or the specified default value.
    */
   public final String getClass( int index, String defaultValue )
   {
      return _Class[index] == null ? defaultValue : _Class[index];
   }
    
   /**
    * Gets the array of Class fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Class values.
    */
   public final String[] getClassArray()
   {
      return _Class;
   }
    
   /**
    * Gets the SplitType field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the SplitType or null.
    */
   public final String getSplitType( int index )
   {
      return _SplitType[index];
   }
    
   /**
    * Gets the SplitType field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SplitType or the specified default value.
    */
   public final String getSplitType( int index, String defaultValue )
   {
      return _SplitType[index] == null ? defaultValue : _SplitType[index];
   }
    
   /**
    * Gets the array of SplitType fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of SplitType values.
    */
   public final String[] getSplitTypeArray()
   {
      return _SplitType;
   }
    
   /**
    * Gets the EffectiveDate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the EffectiveDate or null.
    */
   public final Date getEffectiveDate( int index )
   {
      return _EffectiveDate[index];
   }
    
   /**
    * Gets the EffectiveDate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the EffectiveDate or the specified default value.
    */
   public final Date getEffectiveDate( int index, Date defaultValue )
   {
      return _EffectiveDate[index] == null ? defaultValue : _EffectiveDate[index];
   }
    
   /**
    * Gets the array of EffectiveDate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of EffectiveDate values.
    */
   public final Date[] getEffectiveDateArray()
   {
      return _EffectiveDate;
   }
    
   /**
    * Gets the TransNum field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the TransNum or null.
    */
   public final Integer getTransNum( int index )
   {
      return _TransNum[index];
   }
    
   /**
    * Gets the TransNum field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the TransNum or the specified default value.
    */
   public final int getTransNum( int index, int defaultValue )
   {
      return _TransNum[index] == null ? defaultValue : _TransNum[index].intValue();
   }
    
   /**
    * Gets the array of TransNum fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of TransNum values.
    */
   public final Integer[] getTransNumArray()
   {
      return _TransNum;
   }
    
   /**
    * Gets the CashSweepBal field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the CashSweepBal or null.
    */
   public final String getCashSweepBal( int index )
   {
      return _CashSweepBal[index];
   }
    
   /**
    * Gets the CashSweepBal field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the CashSweepBal or the specified default value.
    */
   public final String getCashSweepBal( int index, String defaultValue )
   {
      return _CashSweepBal[index] == null ? defaultValue : _CashSweepBal[index];
   }
    
   /**
    * Gets the array of CashSweepBal fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of CashSweepBal values.
    */
   public final String[] getCashSweepBalArray()
   {
      return _CashSweepBal;
   }
    
   /**
    * Gets the SelectedAmt field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the SelectedAmt or null.
    */
   public final String getSelectedAmt( int index )
   {
      return _SelectedAmt[index];
   }
    
   /**
    * Gets the SelectedAmt field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SelectedAmt or the specified default value.
    */
   public final String getSelectedAmt( int index, String defaultValue )
   {
      return _SelectedAmt[index] == null ? defaultValue : _SelectedAmt[index];
   }
    
   /**
    * Gets the array of SelectedAmt fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of SelectedAmt values.
    */
   public final String[] getSelectedAmtArray()
   {
      return _SelectedAmt;
   }
    
   /**
    * Gets the IntInvestId field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the IntInvestId or null.
    */
   public final String getIntInvestId( int index )
   {
      return _IntInvestId[index];
   }
    
   /**
    * Gets the IntInvestId field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the IntInvestId or the specified default value.
    */
   public final String getIntInvestId( int index, String defaultValue )
   {
      return _IntInvestId[index] == null ? defaultValue : _IntInvestId[index];
   }
    
   /**
    * Gets the array of IntInvestId fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of IntInvestId values.
    */
   public final String[] getIntInvestIdArray()
   {
      return _IntInvestId;
   }
    
   /**
    * Gets the GBCD field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the GBCD or null.
    */
   public final Boolean getGBCD( int index )
   {
      return _GBCD[index];
   }
    
   /**
    * Gets the GBCD field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the GBCD or the specified default value.
    */
   public final boolean getGBCD( int index, boolean defaultValue )
   {
      return _GBCD[index] == null ? defaultValue : _GBCD[index].booleanValue();
   }
    
   /**
    * Gets the array of GBCD fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of GBCD values.
    */
   public final Boolean[] getGBCDArray()
   {
      return _GBCD;
   }
    
   /**
    * Gets the TransId field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the TransId or null.
    */
   public final String getTransId( int index )
   {
      return _TransId[index];
   }
    
   /**
    * Gets the TransId field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the TransId or the specified default value.
    */
   public final String getTransId( int index, String defaultValue )
   {
      return _TransId[index] == null ? defaultValue : _TransId[index];
   }
    
   /**
    * Gets the array of TransId fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of TransId values.
    */
   public final String[] getTransIdArray()
   {
      return _TransId;
   }
    
   /**
    * Gets the TransSeq field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the TransSeq or null.
    */
   public final Integer getTransSeq( int index )
   {
      return _TransSeq[index];
   }
    
   /**
    * Gets the TransSeq field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the TransSeq or the specified default value.
    */
   public final int getTransSeq( int index, int defaultValue )
   {
      return _TransSeq[index] == null ? defaultValue : _TransSeq[index].intValue();
   }
    
   /**
    * Gets the array of TransSeq fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of TransSeq values.
    */
   public final Integer[] getTransSeqArray()
   {
      return _TransSeq;
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
      
      _InstructionType = resizeArray( _InstructionType, _RepeatCount );
      _Account = resizeArray( _Account, _RepeatCount );
      _Fund = resizeArray( _Fund, _RepeatCount );
      _Class = resizeArray( _Class, _RepeatCount );
      _SplitType = resizeArray( _SplitType, _RepeatCount );
      _EffectiveDate = resizeArray( _EffectiveDate, _RepeatCount );
      _TransNum = resizeArray( _TransNum, _RepeatCount );
      _CashSweepBal = resizeArray( _CashSweepBal, _RepeatCount );
      _SelectedAmt = resizeArray( _SelectedAmt, _RepeatCount );
      _IntInvestId = resizeArray( _IntInvestId, _RepeatCount );
      _GBCD = resizeArray( _GBCD, _RepeatCount );
      _TransId = resizeArray( _TransId, _RepeatCount );
      _TransSeq = resizeArray( _TransSeq, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _InstructionType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Account[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Fund[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Class[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SplitType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EffectiveDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _TransNum[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _CashSweepBal[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SelectedAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IntInvestId[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GBCD[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TransId[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TransSeq[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
      }
      

   }

}
      
