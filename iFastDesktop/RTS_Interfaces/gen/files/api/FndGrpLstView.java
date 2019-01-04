
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Fund Group List/Type Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/FndGrpLst.doc">FndGrpLst.doc</A>.
 * 
 * @author RTS Generated
 */
public class FndGrpLstView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Response Fund Group Type member array.
    */
   private String[] _RxFundGroupType = null;
   
   /**
    * Fund Group Fund Group member array.
    */
   private String[] _FundGroupGroup = null;
   
   /**
    * FundCode member array.
    */
   private String[] _FundCode = null;
   
   /**
    * Class Code member array.
    */
   private String[] _ClassCode = null;
   
   /**
    * Class Required member array.
    */
   private Boolean[] _ClassReq = null;
   
   /**
    * Fund List member array.
    */
   private String[] _FundList = null;
   
   /**
    * Flag that indicates if Bank Account Exist member array.
    */
   private Boolean[] _BankAcctExist = null;
   
   /**
    * Bank Account Currency member array.
    */
   private String[] _BankAcctCurrency = null;
   

   /**
    * Constructs the FndGrpLstView object.
    * 
    */
   public FndGrpLstView()
   {
      super ( new FndGrpLstRequest() );
   }

   /**
    * Constructs the FndGrpLstView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public FndGrpLstView( String hostEncoding )
   {
      super ( new FndGrpLstRequest( hostEncoding ) );
   }

   /**
    * Gets the FndGrpLstRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The FndGrpLstRequest object.
    */
   public final FndGrpLstRequest getRequest()
   {
      return (FndGrpLstRequest)getIFastRequest();
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
    * Gets the Response Fund Group Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Response Fund Group Type or null.
    */
   public final String getRxFundGroupType( int index )
   {
      return _RxFundGroupType[index];
   }
    
   /**
    * Gets the Response Fund Group Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Response Fund Group Type or the specified default value.
    */
   public final String getRxFundGroupType( int index, String defaultValue )
   {
      return _RxFundGroupType[index] == null ? defaultValue : _RxFundGroupType[index];
   }
    
   /**
    * Gets the array of Response Fund Group Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Response Fund Group Type values.
    */
   public final String[] getRxFundGroupTypeArray()
   {
      return _RxFundGroupType;
   }
    
   /**
    * Gets the Fund Group Fund Group field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Group Fund Group or null.
    */
   public final String getFundGroupGroup( int index )
   {
      return _FundGroupGroup[index];
   }
    
   /**
    * Gets the Fund Group Fund Group field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Group Fund Group or the specified default value.
    */
   public final String getFundGroupGroup( int index, String defaultValue )
   {
      return _FundGroupGroup[index] == null ? defaultValue : _FundGroupGroup[index];
   }
    
   /**
    * Gets the array of Fund Group Fund Group fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Group Fund Group values.
    */
   public final String[] getFundGroupGroupArray()
   {
      return _FundGroupGroup;
   }
    
   /**
    * Gets the FundCode field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the FundCode or null.
    */
   public final String getFundCode( int index )
   {
      return _FundCode[index];
   }
    
   /**
    * Gets the FundCode field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FundCode or the specified default value.
    */
   public final String getFundCode( int index, String defaultValue )
   {
      return _FundCode[index] == null ? defaultValue : _FundCode[index];
   }
    
   /**
    * Gets the array of FundCode fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of FundCode values.
    */
   public final String[] getFundCodeArray()
   {
      return _FundCode;
   }
    
   /**
    * Gets the Class Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Class Code or null.
    */
   public final String getClassCode( int index )
   {
      return _ClassCode[index];
   }
    
   /**
    * Gets the Class Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Class Code or the specified default value.
    */
   public final String getClassCode( int index, String defaultValue )
   {
      return _ClassCode[index] == null ? defaultValue : _ClassCode[index];
   }
    
   /**
    * Gets the array of Class Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Class Code values.
    */
   public final String[] getClassCodeArray()
   {
      return _ClassCode;
   }
    
   /**
    * Gets the Class Required field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Class Required or null.
    */
   public final Boolean getClassReq( int index )
   {
      return _ClassReq[index];
   }
    
   /**
    * Gets the Class Required field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Class Required or the specified default value.
    */
   public final boolean getClassReq( int index, boolean defaultValue )
   {
      return _ClassReq[index] == null ? defaultValue : _ClassReq[index].booleanValue();
   }
    
   /**
    * Gets the array of Class Required fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Class Required values.
    */
   public final Boolean[] getClassReqArray()
   {
      return _ClassReq;
   }
    
   /**
    * Gets the Fund List field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund List or null.
    */
   public final String getFundList( int index )
   {
      return _FundList[index];
   }
    
   /**
    * Gets the Fund List field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund List or the specified default value.
    */
   public final String getFundList( int index, String defaultValue )
   {
      return _FundList[index] == null ? defaultValue : _FundList[index];
   }
    
   /**
    * Gets the array of Fund List fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund List values.
    */
   public final String[] getFundListArray()
   {
      return _FundList;
   }
    
   /**
    * Gets the Flag that indicates if Bank Account Exist field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag that indicates if Bank Account Exist or null.
    */
   public final Boolean getBankAcctExist( int index )
   {
      return _BankAcctExist[index];
   }
    
   /**
    * Gets the Flag that indicates if Bank Account Exist field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag that indicates if Bank Account Exist or the specified default value.
    */
   public final boolean getBankAcctExist( int index, boolean defaultValue )
   {
      return _BankAcctExist[index] == null ? defaultValue : _BankAcctExist[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag that indicates if Bank Account Exist fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag that indicates if Bank Account Exist values.
    */
   public final Boolean[] getBankAcctExistArray()
   {
      return _BankAcctExist;
   }
    
   /**
    * Gets the Bank Account Currency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Account Currency or null.
    */
   public final String getBankAcctCurrency( int index )
   {
      return _BankAcctCurrency[index];
   }
    
   /**
    * Gets the Bank Account Currency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Account Currency or the specified default value.
    */
   public final String getBankAcctCurrency( int index, String defaultValue )
   {
      return _BankAcctCurrency[index] == null ? defaultValue : _BankAcctCurrency[index];
   }
    
   /**
    * Gets the array of Bank Account Currency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Account Currency values.
    */
   public final String[] getBankAcctCurrencyArray()
   {
      return _BankAcctCurrency;
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
      
      _RxFundGroupType = resizeArray( _RxFundGroupType, _RepeatCount );
      _FundGroupGroup = resizeArray( _FundGroupGroup, _RepeatCount );
      _FundCode = resizeArray( _FundCode, _RepeatCount );
      _ClassCode = resizeArray( _ClassCode, _RepeatCount );
      _ClassReq = resizeArray( _ClassReq, _RepeatCount );
      _FundList = resizeArray( _FundList, _RepeatCount );
      _BankAcctExist = resizeArray( _BankAcctExist, _RepeatCount );
      _BankAcctCurrency = resizeArray( _BankAcctCurrency, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _RxFundGroupType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundGroupGroup[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ClassCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ClassReq[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _FundList[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAcctExist[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _BankAcctCurrency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
